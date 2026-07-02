// SPDX-License-Identifier: GPL-2.0

//! AI-aware process scheduler.
//!
//! Adjusts scheduling policy and nice values for processes
//! classified as AI workloads.  Local models receive a
//! priority boost.

use alloc::vec::Vec;
use ::core::sync::atomic::{AtomicBool, Ordering};

use kernel::prelude::*;
use kernel::sync::{new_spinlock, SpinLock};

use super::AiProcess;

extern "C" {
    /// Set the nice value of a process by PID.
    /// Returns 0 on success, -ESRCH if the PID is not found.
    pub fn ai_sched_set_nice(pid: i32, nice: i32) -> i32;
    fn ai_sched_register_policy_domain() -> i32;
    fn ai_sched_unregister_policy_domain();
}

/// Register the AI scheduling policy domain.
/// Called once during module init.  Returns -ENOSYS if policy domains
/// are not configured.
pub fn register_ai_policy_domain() -> Result {
    let ret = unsafe { ai_sched_register_policy_domain() };
    if ret != 0 {
        pr_warn!("ai: could not register policy domain: {}\n", ret);
    }
    Ok(())
}

/// Unregister the AI scheduling policy domain.
/// Called during module shutdown.
pub fn unregister_ai_policy_domain() {
    unsafe { ai_sched_unregister_policy_domain() };
}

/// Global AI scheduler.
#[pin_data]
pub struct AiScheduler {
    enabled: AtomicBool,
    #[pin]
    processes: SpinLock<Vec<AiProcess>>,
}

impl AiScheduler {
    pub fn new() -> impl PinInit<Self> {
        pin_init!(Self {
            enabled: AtomicBool::new(true),
            processes <- new_spinlock!(Vec::new()),
        })
    }

    pub fn is_enabled(&self) -> bool {
        self.enabled.load(Ordering::Relaxed)
    }

    pub fn set_enabled(&self, val: bool) {
        self.enabled.store(val, Ordering::Relaxed);
    }

    pub fn register_process(&self, proc: AiProcess) -> Result {
        let mut guard = self.processes.lock();

        guard.retain(|p| p.pid != proc.pid);

        let nice_offset = if proc.is_local {
            proc.priority.to_nice_offset() - 2
        } else {
            proc.priority.to_nice_offset()
        };

        let base_nice = 0i32;
        let raw = base_nice + nice_offset;
        let target_nice = if raw < -20 { -20 } else if raw > 19 { 19 } else { raw };

        let ret = unsafe { ai_sched_set_nice(proc.pid, target_nice) };
        if ret < 0 {
            return Err(EINVAL);
        }

        guard.try_push(proc)?;
        Ok(())
    }

    pub fn unregister_process(&self, pid: i32) {
        let mut guard = self.processes.lock();
        guard.retain(|p| p.pid != pid);
    }

    pub fn managed_count(&self) -> usize {
        self.processes.lock().len()
    }

    #[cfg(CONFIG_AI_LOCAL_PRIORITY)]
    pub fn boost_local(&self, pid: i32) -> Result {
        let nice = -15i32;
        let ret = unsafe { ai_sched_set_nice(pid, nice) };
        if ret < 0 {
            return Err(EINVAL);
        }
        Ok(())
    }
}

// SAFETY: All fields are Send+Sync (AtomicBool, SpinLock).
unsafe impl Send for AiScheduler {}
unsafe impl Sync for AiScheduler {}
