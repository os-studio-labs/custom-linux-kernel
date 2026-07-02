// SPDX-License-Identifier: GPL-2.0

//! AI workload monitor.
//!
//! Tracks running AI processes and feeds data to the
//! scheduler and memory manager.

use alloc::vec::Vec;
use ::core::sync::atomic::{AtomicBool, Ordering};

use kernel::prelude::*;
use kernel::sync::{new_spinlock, SpinLock};

use super::AiProcess;

#[derive(Debug, Clone)]
struct MonitoredProcess {
    proc: AiProcess,
    cpu_usage_pct: u32,
    memory_bytes: u64,
    inference_count: u64,
}

/// Global AI monitor.
#[pin_data]
pub struct AiMonitor {
    enabled: AtomicBool,
    #[pin]
    monitored: SpinLock<Vec<MonitoredProcess>>,
}

impl AiMonitor {
    pub fn new() -> impl PinInit<Self> {
        pin_init!(Self {
            enabled: AtomicBool::new(true),
            monitored <- new_spinlock!(Vec::new()),
        })
    }

    pub fn is_enabled(&self) -> bool {
        self.enabled.load(Ordering::Relaxed)
    }

    pub fn set_enabled(&self, val: bool) {
        self.enabled.store(val, Ordering::Relaxed);
    }

    pub fn track_process(&self, proc: AiProcess) {
        let mut guard = self.monitored.lock();
        guard.retain(|m| m.proc.pid != proc.pid);
        let _ = guard.try_push(MonitoredProcess {
            proc,
            cpu_usage_pct: 0,
            memory_bytes: 0,
            inference_count: 0,
        });
    }

    pub fn untrack_process(&self, pid: i32) {
        let mut guard = self.monitored.lock();
        guard.retain(|m| m.proc.pid != pid);
    }

    pub fn record_inference(&self, pid: i32) {
        let mut guard = self.monitored.lock();
        if let Some(m) = guard.iter_mut().find(|m| m.proc.pid == pid) {
            m.inference_count += 1;
        }
    }

    pub fn active_count(&self) -> usize {
        self.monitored.lock().len()
    }

    pub fn snapshot(&self) -> Vec<AiProcess> {
        let mut out = Vec::new();
        for m in self.monitored.lock().iter() {
            let _ = out.try_push(m.proc.clone());
        }
        out
    }

    pub fn total_memory(&self) -> u64 {
        self.monitored.lock().iter().map(|m| m.memory_bytes).sum()
    }

    pub fn total_inferences(&self) -> u64 {
        self.monitored.lock().iter().map(|m| m.inference_count).sum()
    }
}

unsafe impl Send for AiMonitor {}
unsafe impl Sync for AiMonitor {}
