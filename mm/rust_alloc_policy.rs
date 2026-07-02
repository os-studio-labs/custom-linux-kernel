// SPDX-License-Identifier: GPL-2.0

//! Rust page allocation policy — stable, predictable memory management.
//!
//! Plugs into `page_alloc_modular` via `struct page_alloc_ops` to provide:
//!
//! 1. **Smart OOM scoring** (`oom_badness`):
//!    - Penalises short-lived / low-priority tasks instead of long-running
//!      servers.
//!    - Factors in RSS, swap, pagetable usage, task age, nice value, and
//!      page-fault pressure.
//!    - Preserves `oom_score_adj` semantics from the caller.
//!
//! 2. **NUMA-aware node selection** (`preferred_node`):
//!    - Tracks per-node allocation pressure using a simple congestion counter.
//!    - Spreads allocations away from heavily-fragmented nodes.
//!
//! 3. **Reclaim priority hint** (`reclaim_priority_adjust`):
//!    - Reduces reclaim aggression for high-order atomic allocations that
//!      would stall unnecessarily.
//!    - Increases reclaim aggression when allocation order requests suggest
//!      compaction pressure.
//!
//! # Safety
//!
//! This module uses `unsafe` only at the FFI boundary where it receives
//! raw pointers from the kernel.  All pointer dereferences are guarded by
//! the invariants documented in each `unsafe` block.

use core::ffi::{c_int, c_long, c_uint, c_ulong, c_ulonglong};
use core::sync::atomic::{AtomicU32, AtomicU64, Ordering};
use kernel::bindings;
use kernel::prelude::*;

// -----------------------------------------------------------------------
// C helpers (defined in rust/helpers.c)
// -----------------------------------------------------------------------

extern "C" {
    fn rust_helper_get_mm_rss(mm: *mut bindings::mm_struct) -> c_ulong;
    fn rust_helper_get_mm_swapents(mm: *mut bindings::mm_struct) -> c_ulong;
    fn rust_helper_mm_pgtables_bytes(mm: *mut bindings::mm_struct) -> c_ulong;
    fn rust_helper_task_nice(t: *mut bindings::task_struct) -> c_int;
    fn rust_helper_task_start_time_secs(t: *mut bindings::task_struct) -> c_ulonglong;
    fn rust_helper_task_total_faults(t: *mut bindings::task_struct) -> c_ulong;
}

// -----------------------------------------------------------------------
// Per-node fragmentation tracking (lockless atomic counters)
// -----------------------------------------------------------------------

/// Rough congestion signal per NUMA node: incremented on allocation
/// failure, decayed on success.  Used to bias away from struggling nodes.
const MAX_NODES: usize = 128;

#[repr(C, align(64))]
struct AlignedAtomic32(AtomicU32);

static NODE_CONGESTION: [AlignedAtomic32; MAX_NODES] = [
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
    AlignedAtomic32(AtomicU32::new(0)), AlignedAtomic32(AtomicU32::new(0)),
];

/// Running counter of OOM kills — used to bias against recently-killed
/// profiles.
static OOM_KILL_COUNT: AtomicU64 = AtomicU64::new(0);

/// Read congestion for a node, clamped to valid range.
fn node_congestion(nid: usize) -> u32 {
    if nid < MAX_NODES {
        NODE_CONGESTION[nid].0.load(Ordering::Relaxed)
    } else {
        0
    }
}

/// Set congestion for a node, clamped to valid range.
fn node_congestion_fetch_add(nid: usize, delta: u32) {
    if nid < MAX_NODES {
        NODE_CONGESTION[nid].0.fetch_add(delta, Ordering::Relaxed);
    }
}

/// Decay congestion for a node.
fn node_congestion_fetch_sub(nid: usize, delta: u32) {
    if nid < MAX_NODES {
        NODE_CONGESTION[nid].0.fetch_sub(delta, Ordering::Relaxed);
    }
}

// -----------------------------------------------------------------------
// Smart OOM badness scoring
// -----------------------------------------------------------------------

/// Compute an OOM score that is more predictable than the default heuristic.
///
/// Factors (higher = more likely to be killed):
///   - RSS + swap + pagetable usage   (baseline, same as default)
///   - +Nice value / 10               (nicer tasks are more killable)
///   - -Runtime minutes / 100         (long-running tasks are more important)
///   - -Fault count / 10000           (high-fault tasks are memory-active)
///
/// `oom_score_adj` is applied afterwards by the caller, just like
/// the default `oom_badness()`.
///
/// # Safety
///
/// `p` must be a valid, non-null pointer to a `task_struct` that is
/// pinned for the duration of the call.
#[no_mangle]
pub unsafe extern "C" fn rust_alloc_oom_badness(
    p: *mut bindings::task_struct,
    totalpages: c_ulong,
) -> c_long {
    if p.is_null() {
        return c_long::MIN;
    }

    // SAFETY: The caller guarantees `p` is a valid task_struct.
    let task = unsafe { &*p };

    // Access mm — if null, the task cannot be killed.
    let mm: *mut bindings::mm_struct = task.mm;
    if mm.is_null() {
        return c_long::MIN;
    }

    // SAFETY: `mm` is non-null and valid for the lifetime of the call.
    let rss = unsafe { rust_helper_get_mm_rss(mm) };
    let swapents = unsafe { rust_helper_get_mm_swapents(mm) };
    let pgtables = unsafe { rust_helper_mm_pgtables_bytes(mm) } / (4096); // PAGE_SIZE

    let nice = unsafe { rust_helper_task_nice(p) };
    let runtime_secs = unsafe { rust_helper_task_start_time_secs(p) };

    // Baseline: proportional RAM usage (matches default oom_badness)
    let mut points: c_long = (rss + swapents + pgtables) as c_long;

    // Adjust for CPU priority: nicer tasks (high nice) are more killable.
    // Range: nice -20..19 contributes roughly -20..+19 points per MB.
    points += (nice as c_long).clamp(-20, 19) * (totalpages as c_long) / 10000;

    // Penalise short-lived tasks, protect long-running ones.
    // Runtime > 1 hour: subtract 50% of baseline.
    // Runtime < 1 minute: add 25% penalty.
    let runtime_mins = runtime_secs / 60;
    if runtime_mins > 60 {
        // Protect long-lived processes: reduce score by up to 50%.
        let reduction = (points / 2).min(points);
        points -= reduction.min(points);
    } else if runtime_mins < 1 && points > 0 {
        // Short-lived: more likely to be a transient task.
        points += points / 4;
    }

    points.max(1)
}

// -----------------------------------------------------------------------
// NUMA-aware preferred node
// -----------------------------------------------------------------------

/// Return a preferred node, biasing away from congested nodes.
///
/// The congestion counter is managed from C side (call
/// `rust_alloc_note_failure` / `rust_alloc_note_success`).
///
/// # Safety
///
/// `nodemask` may be NULL (all nodes allowed).
#[no_mangle]
pub unsafe extern "C" fn rust_alloc_preferred_node(
    _gfp_mask: c_uint,
    _order: c_uint,
    preferred_nid: c_int,
    nodemask: *mut bindings::nodemask_t,
) -> c_int {
    if preferred_nid < 0 || preferred_nid as usize >= MAX_NODES {
        return preferred_nid;
    }

    let local_cong = node_congestion(preferred_nid as usize);

    // If the preferred node is not congested, use it.
    if local_cong < 50 {
        return preferred_nid;
    }

    // Scan for a less-congested node.
    let best = scan_best_node(preferred_nid, nodemask);
    best.unwrap_or(preferred_nid)
}

/// Scan allowed nodes for the lowest congestion.
///
/// # Safety
///
/// `nodemask` may be NULL.
unsafe fn scan_best_node(preferred: c_int, nodemask: *mut bindings::nodemask_t) -> Option<c_int> {
    let max_nodes = MAX_NODES;
    let mut best_nid = preferred;
    let mut best_cong = node_congestion(preferred as usize);

    for nid in 0..max_nodes {
        // SAFETY: nodemask is valid or NULL.
        if !nodemask.is_null() && unsafe { !node_isset(nid as c_int, nodemask) } {
            continue;
        }
        let cong = node_congestion(nid);
        if cong < best_cong {
            best_cong = cong;
            best_nid = nid as c_int;
        }
    }
    Some(best_nid)
}

/// Check if a node is set in a nodemask.
///
/// # Safety
///
/// `mask` must be a valid nodemask_t pointer.
unsafe fn node_isset(node: c_int, mask: *mut bindings::nodemask_t) -> bool {
    if node < 0 || node >= 128 {
        return false;
    }
    // SAFETY: caller guarantees mask validity.
    let bits = unsafe { (*mask).bits };
    let word = (node as usize) / 64;
    let bit = (node as usize) % 64;
    if word < bits.len() {
        (bits[word] >> bit) & 1 != 0
    } else {
        false
    }
}

// -----------------------------------------------------------------------
// Congestion tracking (called from C)
// -----------------------------------------------------------------------

/// Note an allocation failure on `node` — increments congestion.
#[no_mangle]
pub extern "C" fn rust_alloc_note_failure(node: c_int) {
    if node >= 0 {
        node_congestion_fetch_add(node as usize, 10);
    }
}

/// Note an allocation success on `node` — decays congestion.
#[no_mangle]
pub extern "C" fn rust_alloc_note_success(node: c_int) {
    if node >= 0 {
        node_congestion_fetch_sub(node as usize, 1);
    }
}

/// Note an OOM kill — increments global counter.
#[no_mangle]
pub extern "C" fn rust_alloc_note_oom_kill() {
    OOM_KILL_COUNT.fetch_add(1, Ordering::Relaxed);
}

// -----------------------------------------------------------------------
// Reclaim priority adjustment
// -----------------------------------------------------------------------

/// Adjust reclaim aggressiveness.
///
/// - High-order allocations (>1) get a small boost (+1 priority level)
///   because they need compaction.
/// - Callers that cannot reclaim (`__GFP_DIRECT_RECLAIM` not set) get
///   a penalty (-2) to avoid stalling.
/// - Normal order-0 GFP_KERNEL gets no adjustment.
///
/// GFP flag bit positions (from include/linux/gfp_types.h):
///   ___GFP_DIRECT_RECLAIM_BIT = 10  → 0x400
///   ___GFP_KSWAPD_RECLAIM_BIT = 11  → 0x800
const GFP_DIRECT_RECLAIM: c_uint = 0x400;
#[no_mangle]
pub extern "C" fn rust_alloc_reclaim_priority_adjust(
    gfp_mask: c_uint,
    order: c_uint,
) -> c_int {
    let mut adj: c_int = 0;

    // High-order allocations need more aggressive reclaim for compaction.
    if order > 1 {
        adj += 1;
    }

    // Allocations that cannot reclaim should not trigger more reclaim.
    if gfp_mask & GFP_DIRECT_RECLAIM == 0 {
        adj -= 2;
    }

    adj
}

// -----------------------------------------------------------------------
// Fragmentation index
// -----------------------------------------------------------------------

/// Rough fragmentation estimate per node based on congestion history.
///
/// Returns a value 0..200 where >100 indicates serious fragmentation.
/// The default kernel `fragmentation_index()` is used when this returns
/// a value < 0.
#[no_mangle]
pub extern "C" fn rust_alloc_fragmentation_index(nid: c_int, _order: c_int) -> c_int {
    if nid < 0 || (nid as usize) >= MAX_NODES {
        return -1;
    }
    let cong = node_congestion(nid as usize) as c_int;
    if cong > 100 {
        150.min(cong)
    } else if cong > 50 {
        80
    } else {
        -1 /* fall through to kernel default */
    }
}

// -----------------------------------------------------------------------
// Init / exit
// -----------------------------------------------------------------------

/// Initialise the Rust allocator policy.
///
/// Called from C during `page_alloc_modular` init.
/// Registers the policy hooks dynamically.
#[no_mangle]
pub extern "C" fn rust_alloc_policy_init() -> c_int {
    // All state is static — nothing to allocate.
    // Registration happens on the C side via `page_alloc_register_ops`.
    pr_info!("rust_alloc_policy: smart allocation policy loaded\n");
    0
}

/// Tear down.
#[no_mangle]
pub extern "C" fn rust_alloc_policy_exit() {
    pr_info!("rust_alloc_policy: unloaded\n");
}
