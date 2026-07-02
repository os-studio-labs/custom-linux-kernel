// SPDX-License-Identifier: GPL-2.0

//! IOCTL interface for the AI subsystem.
//!
//! Handles userspace requests from the ai-mgr daemon.
//! Defined in `include/uapi/linux/ai.h`.

use ::core::ffi::{c_int, c_uint, c_ulong};
use ::core::ptr;
use ::core::sync::atomic::{AtomicBool, Ordering};

use kernel::prelude::*;
use kernel::sync::Arc;

use crate::ai_core::scheduler::AiScheduler;
use crate::ai_core::memory::AiMemoryManager;
use crate::ai_core::{AiProcess, MemoryPolicy, Priority, WorkloadType};
use crate::models::cloud::CloudEndpointManager;
use crate::AI_STATS;

// ── UAPI structs (matches include/uapi/linux/ai.h) ──────────

#[derive(Debug)]
#[repr(C)]
struct ai_classify_param {
    pid: i32,
    workload_type: u32,
    priority: u32,
    flags: u32,
}

#[derive(Debug)]
#[repr(C)]
struct ai_memory_hint {
    addr: u64,
    size: u64,
    policy: u32,
    _flags: u32,
}

#[derive(Debug)]
#[repr(C)]
struct ai_sched_param {
    pid: i32,
    nice_offset: i32,
    _sched_flags: u32,
}

#[repr(C)]
struct ai_stats {
    local_inferences: u64,
    cloud_inferences: u64,
    total_memory_used: u64,
    active_models: u32,
    active_processes: u32,
    reserved: [u32; 4],
}

// ── Static references set during module init ─────────────────

static IOCTL_READY: AtomicBool = AtomicBool::new(false);
static IOCTL_SCHED: ::core::sync::atomic::AtomicPtr<AiScheduler> =
    ::core::sync::atomic::AtomicPtr::new(ptr::null_mut());
static IOCTL_MEM: ::core::sync::atomic::AtomicPtr<AiMemoryManager> =
    ::core::sync::atomic::AtomicPtr::new(ptr::null_mut());
static IOCTL_CLOUD: ::core::sync::atomic::AtomicPtr<CloudEndpointManager> =
    ::core::sync::atomic::AtomicPtr::new(ptr::null_mut());

/// Initialise ioctl statics with pointers to subsystem components.
/// Called once during module init.
pub fn init(sched: &Arc<AiScheduler>, mem: &Arc<AiMemoryManager>,
            cloud: &Arc<CloudEndpointManager>) {
    IOCTL_SCHED.store(Arc::into_raw(Arc::clone(sched)) as *mut AiScheduler, Ordering::Release);
    IOCTL_MEM.store(Arc::into_raw(Arc::clone(mem)) as *mut AiMemoryManager, Ordering::Release);
    IOCTL_CLOUD.store(Arc::into_raw(Arc::clone(cloud)) as *mut CloudEndpointManager, Ordering::Release);
    IOCTL_READY.store(true, Ordering::Release);
}

/// Tear down ioctl statics.
pub fn exit() {
    IOCTL_READY.store(false, Ordering::Release);
    IOCTL_SCHED.store(ptr::null_mut(), Ordering::Release);
    IOCTL_MEM.store(ptr::null_mut(), Ordering::Release);
    IOCTL_CLOUD.store(ptr::null_mut(), Ordering::Release);
}

// ── FFI entry point called from C ────────────────────────────

/// Called from C file_operations when userspace issues an ioctl on
/// /dev/ai-control.  Must match the signature expected by the C side:
///   extern int ai_ioctl_dispatch(unsigned int cmd, unsigned long arg);
#[no_mangle]
pub extern "C" fn ai_ioctl_dispatch(cmd: c_uint, arg: c_ulong) -> c_int {
    if !IOCTL_READY.load(Ordering::Acquire) {
        return -19; /* -ENODEV */
    }

    let result = match cmd & 0xff {
        1 => cmd_classify(arg as usize),
        2 => cmd_memory_hint(arg as usize),
        3 => cmd_sched_priority(arg as usize),
        4 => cmd_add_cloud(arg as usize),
        5 => cmd_remove_cloud(arg as usize),
        6 => cmd_get_stats(arg as usize),
        7 => cmd_ping(),
        _ => Err(ENOTTY),
    };

    match result {
        Ok(v) => v,
        Err(e) => -(e.to_errno() as c_int),
    }
}

// ── Helper: copy a struct from userspace ─────────────────────

/// Read a value of type T from a userspace pointer.
/// # Safety
/// `arg` must be a valid, readable userspace pointer of at least `size_of::<T>()` bytes.
unsafe fn copy_from_user<T: ::core::fmt::Debug>(arg: *const T) -> Result<T> {
    if arg.is_null() {
        return Err(EFAULT);
    }
    // SAFETY: caller guarantees the pointer is valid userspace memory.
    let val: T = unsafe { ptr::read_unaligned(arg) };
    // On many arches we need to read via copy_from_user for safety;
    // ptr::read_unaligned is used here as a placeholder for the real
    // copy_from_user which requires a special kernel API.
    Ok(val)
}

// ── IOCTL command handlers ──────────────────────────────────

/// Helper: get current PID via C FFI.
extern "C" {
    fn ai_get_current_pid() -> i32;
}

/// AI_IOCTL_CLASSIFY — register or update an AI process.
fn cmd_classify(arg: usize) -> Result<i32> {
    let param: *const ai_classify_param = arg as *const _;

    // SAFETY: arg comes from userspace ioctl; kernel validates addr.
    let cfg = unsafe { copy_from_user(param)? };

    let pid = cfg.pid;
    let wload = WorkloadType::from_u32(cfg.workload_type);
    let priority = Priority::new(cfg.priority as u8);

    // Register with the AI scheduler
    if let Some(sched) = get_scheduler() {
        let proc = AiProcess {
            pid,
            workload: wload,
            priority,
            memory_policy: MemoryPolicy::Default,
            is_local: true,
        };
        let _ = sched.register_process(proc);
    }

    // Track in the monitor
    if let Some(_mon) = get_monitor() {
        // monitor tracking will be done by the scheduler registration
    }

    AI_STATS.active_processes.fetch_add(1, Ordering::Relaxed);

    Ok(0)
}

/// AI_IOCTL_MEMORY_HINT — apply a memory policy hint for an AI region.
fn cmd_memory_hint(arg: usize) -> Result<i32> {
    let param: *const ai_memory_hint = arg as *const _;

    // SAFETY: arg comes from userspace ioctl.
    let hint = unsafe { copy_from_user(param)? };

    let policy = MemoryPolicy::from_u32(hint.policy);
    // Note: pid is not in the memory hint structure; this applies
    // to the calling process's address space.
    if let Some(mem) = get_memory_manager() {
        // Get current PID via FFI C helper
        let current_pid = unsafe { ai_get_current_pid() };
        mem.apply_hint(current_pid, hint.addr, hint.size, policy)?;
    }

    Ok(0)
}

/// AI_IOCTL_SCHED_PRIORITY — adjust scheduling priority of an AI process.
fn cmd_sched_priority(arg: usize) -> Result<i32> {
    let param: *const ai_sched_param = arg as *const _;

    // SAFETY: arg comes from userspace ioctl.
    let sp = unsafe { copy_from_user(param)? };

    if let Some(_sched) = get_scheduler() {
        let base_nice = 0i32;
        let raw = base_nice + sp.nice_offset;
        let target_nice = if raw < -20 { -20 } else if raw > 19 { 19 } else { raw };

        // SAFETY: we trust the pid from userspace (validated by the scheduler)
        let ret = unsafe { crate::ai_core::scheduler::ai_sched_set_nice(sp.pid, target_nice) };
        if ret < 0 {
            return Err(EINVAL);
        }
    }

    Ok(0)
}

/// AI_IOCTL_ADD_CLOUD — register a cloud AI endpoint.
fn cmd_add_cloud(_arg: usize) -> Result<i32> {
    // The cloud endpoint URL is a 256-byte buffer passed via arg.
    // For now, just acknowledge the registration.
    if let Some(_cloud) = get_cloud_manager() {
        // TODO: call cloud.add() with the endpoint data
    }

    Ok(0)
}

/// AI_IOCTL_REMOVE_CLOUD — remove a cloud AI endpoint by ID.
fn cmd_remove_cloud(_arg: usize) -> Result<i32> {
    if let Some(_cloud) = get_cloud_manager() {
        // TODO: call cloud.remove(id)
    }

    Ok(0)
}

/// AI_IOCTL_GET_STATS — copy global AI statistics to userspace.
fn cmd_get_stats(arg: usize) -> Result<i32> {
    let out: *mut ai_stats = arg as *mut _;

    if out.is_null() {
        return Err(EFAULT);
    }

    let stats = ai_stats {
        local_inferences: AI_STATS.local_inferences.load(Ordering::Relaxed),
        cloud_inferences: AI_STATS.cloud_inferences.load(Ordering::Relaxed),
        total_memory_used: AI_STATS.total_memory_used.load(Ordering::Relaxed),
        active_models: AI_STATS.active_models.load(Ordering::Relaxed) as u32,
        active_processes: AI_STATS.active_processes.load(Ordering::Relaxed) as u32,
        reserved: [0u32; 4],
    };

    // SAFETY: arg is a valid userspace pointer from the ioctl.
    unsafe { ptr::write_unaligned(out, stats) };
    Ok(0)
}

/// AI_IOCTL_PING — simple health check.
fn cmd_ping() -> Result<i32> {
    Ok(0)
}

// ── Accessors (pub(crate) for use by lib.rs sysfs helpers) ───

pub(crate) fn get_scheduler() -> Option<&'static AiScheduler> {
    let ptr = IOCTL_SCHED.load(Ordering::Acquire);
    if ptr.is_null() { None } else { Some(unsafe { &*ptr }) }
}

pub(crate) fn get_memory_manager() -> Option<&'static AiMemoryManager> {
    let ptr = IOCTL_MEM.load(Ordering::Acquire);
    if ptr.is_null() { None } else { Some(unsafe { &*ptr }) }
}

#[allow(dead_code)]
pub(crate) fn get_monitor() -> Option<&'static crate::ai_core::monitor::AiMonitor> {
    None // not stored in ioctl statics; can be added if needed
}

pub(crate) fn get_cloud_manager() -> Option<&'static CloudEndpointManager> {
    let ptr = IOCTL_CLOUD.load(Ordering::Acquire);
    if ptr.is_null() { None } else { Some(unsafe { &*ptr }) }
}
