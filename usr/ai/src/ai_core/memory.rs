// SPDX-License-Identifier: GPL-2.0

//! AI-aware memory management.
//!
//! Tracks per-process AI memory regions and issues memory policy
//! advice (hugepages, locking) via C helper wrappers.

use alloc::vec::Vec;
use ::core::sync::atomic::{AtomicBool, Ordering};

use kernel::prelude::*;
use kernel::sync::{new_spinlock, SpinLock};
use crate::ai_core::MemoryPolicy;

extern "C" {
    fn ai_mem_hint_madvise(pid: i32, addr: u64, size: u64, advice: i32) -> i32;
    fn ai_mem_mlock(addr: u64, size: u64) -> i32;
}

#[derive(Debug, Clone)]
struct AiMemoryRegion {
    addr: u64,
    size: u64,
    policy: MemoryPolicy,
    pid: i32,
}

/// Global AI memory manager.
#[pin_data]
pub struct AiMemoryManager {
    enabled: AtomicBool,
    #[pin]
    regions: SpinLock<Vec<AiMemoryRegion>>,
}

impl AiMemoryManager {
    pub fn new() -> impl PinInit<Self> {
        pin_init!(Self {
            enabled: AtomicBool::new(true),
            regions <- new_spinlock!(Vec::new()),
        })
    }

    pub fn is_enabled(&self) -> bool {
        self.enabled.load(Ordering::Relaxed)
    }

    pub fn apply_hint(&self, pid: i32, addr: u64, size: u64, policy: MemoryPolicy) -> Result {
        self.hint_kernel(pid, addr, size, policy)?;

        let mut guard = self.regions.lock();
        guard.retain(|r| r.pid != pid || r.addr != addr);
        guard.try_push(AiMemoryRegion {
            addr,
            size,
            policy,
            pid,
        })?;

        Ok(())
    }

    fn hint_kernel(&self, pid: i32, addr: u64, size: u64, policy: MemoryPolicy) -> Result {
        match policy {
            MemoryPolicy::HugePage => {
                const MADV_HUGEPAGE: i32 = 14;
        let ret = unsafe { ai_mem_hint_madvise(pid, addr, size,
                    MADV_HUGEPAGE) };
                if ret < 0 {
                    return Err(EINVAL);
                }
            }
            MemoryPolicy::Locked => {
                let ret = unsafe { ai_mem_mlock(addr, size) };
                if ret < 0 {
                    return Err(EINVAL);
                }
            }
            MemoryPolicy::Compressed => {
                const MADV_PAGEOUT: i32 = 21;
                let ret = unsafe { ai_mem_hint_madvise(pid, addr, size,
                    MADV_PAGEOUT) };
                if ret < 0 {
                    return Err(EINVAL);
                }
            }
            MemoryPolicy::Default => {}
        }
        Ok(())
    }

    pub fn release_process(&self, pid: i32) {
        let mut guard = self.regions.lock();
        guard.retain(|r| r.pid != pid);
    }

    pub fn total_tracked(&self) -> u64 {
        self.regions.lock().iter().map(|r| r.size).sum()
    }

    pub fn region_count(&self) -> usize {
        self.regions.lock().len()
    }
}

unsafe impl Send for AiMemoryManager {}
unsafe impl Sync for AiMemoryManager {}
