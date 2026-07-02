// SPDX-License-Identifier: GPL-2.0

//! Firmware health monitor — lockless state machine for WiFi drivers.
//!
//! Maintains firmware health state using atomic operations so that
//! fast-paths (TX/RX) never block.  The C side owns the watchdog
//! timer; the Rust side tracks state transitions and statistics.

#![no_std]

use core::ffi::{c_int, c_uint, c_ulong, c_void};
use core::sync::atomic::{AtomicI32, AtomicU32, AtomicU64, Ordering};

// ── FFI imports from the C side ──────────────────────────────

extern "C" {
    fn rust_helper_get_jiffies() -> c_ulong;
    fn rust_helper_time_after(a: c_ulong, b: c_ulong) -> c_int;
}

// ── State constants (matching fw_health.h) ───────────────────

const FW_HEALTH_OK: i32 = 0;
const FW_HEALTH_HUNG: i32 = 1;
const FW_HEALTH_CRASHED: i32 = 2;
const FW_HEALTH_RECOVERING: i32 = 3;
const FW_HEALTH_DEAD: i32 = 4;

// ── Core health structure ────────────────────────────────────

/// Must match the layout expected by the C side (opaque pointer).
#[repr(C)]
pub struct FwHealth {
    state: AtomicI32,
    crash_count: AtomicU32,
    recovery_count: AtomicU32,
    timeout_jiffies: c_ulong,
    last_heartbeat: AtomicU64,
    ops: *mut c_void,    // points to struct fw_health_ops
    priv_data: *mut c_void,
    dev: *mut c_void,    // struct device *
}

// SAFETY: all fields are atomics or raw pointers that are never
// dereferenced concurrently without proper synchronization.
unsafe impl Send for FwHealth {}
unsafe impl Sync for FwHealth {}

// ── Allocation (called from C bridge) ────────────────────────

#[no_mangle]
pub extern "C" fn rust_fw_health_alloc(
    dev: *mut c_void,
    timeout_ms: c_ulong,
    ops: *mut c_void,
    priv_data: *mut c_void,
) -> *mut FwHealth {
    let jiffies_per_ms = unsafe { rust_helper_get_jiffies() / 1000 }.max(1);
    let timeout_jiffies = timeout_ms * jiffies_per_ms;

    // Allocate via C's kzalloc to keep the allocator consistent.
    extern "C" {
        fn kzalloc(size: c_ulong, flags: c_uint) -> *mut c_void;
    }

    // GFP_KERNEL = 0xCC0 (roughly)
    let ptr = unsafe { kzalloc(core::mem::size_of::<FwHealth>() as c_ulong, 0xCC0u32) };
    if ptr.is_null() {
        return core::ptr::null_mut();
    }

    let h = ptr as *mut FwHealth;
    unsafe {
        (*h).state = AtomicI32::new(FW_HEALTH_OK);
        (*h).crash_count = AtomicU32::new(0);
        (*h).recovery_count = AtomicU32::new(0);
        (*h).timeout_jiffies = timeout_jiffies;
        (*h).last_heartbeat = AtomicU64::new(unsafe { rust_helper_get_jiffies() as u64 });
        (*h).ops = ops;
        (*h).priv_data = priv_data;
        (*h).dev = dev;
    }
    h
}

#[no_mangle]
pub extern "C" fn rust_fw_health_free(h: *mut FwHealth) {
    if h.is_null() {
        return;
    }
    extern "C" {
        fn kfree(ptr: *mut c_void);
    }
    unsafe { kfree(h as *mut c_void) };
}

// ── State transitions ────────────────────────────────────────

#[no_mangle]
pub extern "C" fn rust_fw_health_report_ok(h: *mut FwHealth) {
    if h.is_null() {
        return;
    }
    unsafe {
        let h = &*h;
        h.last_heartbeat.store(unsafe { rust_helper_get_jiffies() as u64 }, Ordering::Release);
        // If we were recovering, transition back to OK
        h.state.compare_exchange(
            FW_HEALTH_RECOVERING, FW_HEALTH_OK,
            Ordering::AcqRel, Ordering::Relaxed,
        ).ok();
        // Also transition from HUNG back to OK if heartbeat resumes
        h.state.compare_exchange(
            FW_HEALTH_HUNG, FW_HEALTH_OK,
            Ordering::AcqRel, Ordering::Relaxed,
        ).ok();
    }
}

#[no_mangle]
pub extern "C" fn rust_fw_health_report_hung(h: *mut FwHealth) {
    if h.is_null() {
        return;
    }
    unsafe {
        let h = &*h;
        h.state.store(FW_HEALTH_HUNG, Ordering::Release);
    }
}

#[no_mangle]
pub extern "C" fn rust_fw_health_report_crash(h: *mut FwHealth) {
    if h.is_null() {
        return;
    }
    unsafe {
        let h = &*h;
        h.state.store(FW_HEALTH_CRASHED, Ordering::Release);
        h.crash_count.fetch_add(1, Ordering::Relaxed);
    }
}

// ── Queries ──────────────────────────────────────────────────

#[no_mangle]
pub extern "C" fn rust_fw_health_get_state(h: *mut FwHealth) -> c_int {
    if h.is_null() {
        return FW_HEALTH_DEAD;
    }
    unsafe { (*h).state.load(Ordering::Acquire) }
}

#[no_mangle]
pub extern "C" fn rust_fw_health_get_crash_count(h: *mut FwHealth) -> c_uint {
    if h.is_null() {
        return 0;
    }
    unsafe { (*h).crash_count.load(Ordering::Relaxed) }
}

#[no_mangle]
pub extern "C" fn rust_fw_health_get_recovery_count(h: *mut FwHealth) -> c_uint {
    if h.is_null() {
        return 0;
    }
    unsafe { (*h).recovery_count.load(Ordering::Relaxed) }
}

// ── Periodic health check (called FROM C TIMER) ──────────────

/// Called by the C-side watchdog timer.  Returns 1 if the firmware
/// is healthy, 0 if hung (needs recovery), -1 if already dead.
#[no_mangle]
pub extern "C" fn rust_fw_health_check(h: *mut FwHealth) -> c_int {
    if h.is_null() {
        return -1;
    }
    let h = unsafe { &*h };

    let current_state = h.state.load(Ordering::Acquire);
    match current_state {
        FW_HEALTH_OK | FW_HEALTH_RECOVERING => {}
        FW_HEALTH_DEAD => return -1,
        _ => return 0, // already in error state
    }

    let last = h.last_heartbeat.load(Ordering::Acquire);
    let now = unsafe { rust_helper_get_jiffies() } as u64;

    // Check if timeout has elapsed since last heartbeat
    if now.wrapping_sub(last) >= h.timeout_jiffies as u64 {
        // Firmware appears hung — transition to HUNG state
        h.state.compare_exchange(
            FW_HEALTH_OK, FW_HEALTH_HUNG,
            Ordering::AcqRel, Ordering::Relaxed,
        ).ok();
        0
    } else {
        1
    }
}

/// Called by the C side after successful recovery.
#[no_mangle]
pub extern "C" fn rust_fw_health_recovery_succeeded(h: *mut FwHealth) {
    if h.is_null() {
        return;
    }
    let h = unsafe { &*h };
    h.state.store(FW_HEALTH_OK, Ordering::Release);
    h.recovery_count.fetch_add(1, Ordering::Relaxed);
    h.last_heartbeat.store(unsafe { rust_helper_get_jiffies() as u64 }, Ordering::Release);
}

/// Called by the C side after recovery failure.
#[no_mangle]
pub extern "C" fn rust_fw_health_recovery_failed(h: *mut FwHealth) {
    if h.is_null() {
        return;
    }
    let h = unsafe { &*h };
    h.state.store(FW_HEALTH_DEAD, Ordering::Release);
}
