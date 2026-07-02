// SPDX-License-Identifier: GPL-2.0

//! AI subsystem — kernel-level AI workload management.
//!
//! This crate provides the kernel portion of the AI subsystem:
//!   - Process classification (inference, training, embedding)
//!   - Memory optimisation (hugepages, locking, hints)
//!   - CPU scheduler priority adjustments for AI processes
//!   - Sysfs control interface at `/sys/kernel/ai/`
//!   - IOCTL interface for the ai-mgr userspace daemon
//!   - Local model acceleration (ollama, opencode)
//!   - Cloud AI endpoint routing

#![no_std]
#![allow(dead_code, unused_imports, stable_features, unused_attributes, unused_doc_comments, unreachable_pub, missing_docs)]

use ::core::sync::atomic::{AtomicU64, Ordering};

use kernel::prelude::*;
use kernel::str::CStr;
use kernel::sync::Arc;

mod ai_core;
mod ioctl;
mod models;

#[cfg(CONFIG_AI_SYSFS)]
pub(crate) mod sysfs;

module! {
    type: AiSubsystem,
    name: "ai_subsystem",
    author: "SentraOS Kernel Team",
    description: "AI workload management and optimisation subsystem",
    license: "GPL",
}

static AI_STATS: AiStats = AiStats::new();

struct AiStats {
    pub(crate) local_inferences: AtomicU64,
    pub(crate) cloud_inferences: AtomicU64,
    pub(crate) total_memory_used: AtomicU64,
    pub(crate) active_models: AtomicU64,
    pub(crate) active_processes: AtomicU64,
}

impl AiStats {
    const fn new() -> Self {
        Self {
            local_inferences: AtomicU64::new(0),
            cloud_inferences: AtomicU64::new(0),
            total_memory_used: AtomicU64::new(0),
            active_models: AtomicU64::new(0),
            active_processes: AtomicU64::new(0),
        }
    }

    fn record_local_inference(&self) {
        self.local_inferences.fetch_add(1, Ordering::Relaxed);
    }

    fn record_cloud_inference(&self) {
        self.cloud_inferences.fetch_add(1, Ordering::Relaxed);
    }
}

// ── C helpers for miscdevice registration ────────────────────

extern "C" {
    fn ai_misc_register() -> i32;
    fn ai_misc_unregister();
}

// ── Stats / classify accessors for C sysfs code ──────────────

#[no_mangle]
pub extern "C" fn ai_stats_local_inferences() -> u64 {
    AI_STATS.local_inferences.load(Ordering::Relaxed)
}

#[no_mangle]
pub extern "C" fn ai_stats_cloud_inferences() -> u64 {
    AI_STATS.cloud_inferences.load(Ordering::Relaxed)
}

#[no_mangle]
pub extern "C" fn ai_stats_active_models() -> u64 {
    AI_STATS.active_models.load(Ordering::Relaxed)
}

#[no_mangle]
pub extern "C" fn ai_stats_active_processes() -> u64 {
    AI_STATS.active_processes.load(Ordering::Relaxed)
}

/// Kernel-space classify entry point called from sysfs.
/// `pid`, `workload_type`, and `priority` are already parsed from the sysfs buffer.
#[no_mangle]
pub extern "C" fn ai_classify_from_kernel(pid: i32, workload_type: u32, priority: i32) -> i32 {
    let wload = crate::ai_core::WorkloadType::from_u32(workload_type);
    let prio = crate::ai_core::Priority::new(priority as u8);
    let proc = crate::ai_core::AiProcess {
        pid,
        workload: wload,
        priority: prio,
        memory_policy: crate::ai_core::MemoryPolicy::Default,
        is_local: true,
    };

    if let Some(sched) = crate::ioctl::get_scheduler() {
        let _ = sched.register_process(proc);
    }

    AI_STATS.active_processes.fetch_add(1, Ordering::Relaxed);
    0
}

/// Kernel-space priority entry point called from sysfs.
#[no_mangle]
pub extern "C" fn ai_priority_from_kernel(pid: i32, nice_offset: i32) -> i32 {
    if let Some(_sched) = crate::ioctl::get_scheduler() {
        let target_nice = if nice_offset < -20 { -20 } else if nice_offset > 19 { 19 } else { nice_offset };
        let ret = unsafe { crate::ai_core::scheduler::ai_sched_set_nice(pid, target_nice) };
        if ret < 0 {
            return ret;
        }
    }
    0
}

/// The AI subsystem kernel module.
struct AiSubsystem {
    _sched: Arc<crate::ai_core::scheduler::AiScheduler>,
    _mem_mgr: Arc<crate::ai_core::memory::AiMemoryManager>,
    _monitor: Arc<crate::ai_core::monitor::AiMonitor>,
    _model_reg: Arc<models::ModelRegistry>,
    _local_mgr: models::local::LocalModelManager,
    _cloud_mgr: Arc<models::cloud::CloudEndpointManager>,
    #[cfg(CONFIG_AI_SYSFS)]
    _sysfs_reg: sysfs::SysfsRegistrar,
}

impl kernel::Module for AiSubsystem {
    fn init(_module: &'static ThisModule) -> Result<Self> {
        pr_info!("AI subsystem initialising\n");

        let sched = Arc::pin_init(crate::ai_core::scheduler::AiScheduler::new())
            .map_err(|_| ENOMEM)?;

        let mem_mgr = Arc::pin_init(crate::ai_core::memory::AiMemoryManager::new())
            .map_err(|_| ENOMEM)?;

        let monitor = Arc::pin_init(crate::ai_core::monitor::AiMonitor::new())
            .map_err(|_| ENOMEM)?;

        let model_reg = Arc::pin_init(models::ModelRegistry::new())
            .map_err(|_| ENOMEM)?;

        let local_mgr = models::local::LocalModelManager::new(
            model_reg.clone(),
            sched.clone(),
            mem_mgr.clone(),
        );

        let cloud_mgr = Arc::pin_init(models::cloud::CloudEndpointManager::new())
            .map_err(|_| ENOMEM)?;

        // ── Initialise ioctl dispatch statics ─────
        ioctl::init(&sched, &mem_mgr, &cloud_mgr);

        // ── Register miscdevice /dev/ai-control ──
        let ret = unsafe { ai_misc_register() };
        if ret < 0 {
            ioctl::exit();
            return Err(ENODEV);
        }

        // ── Register AI scheduling policy domain ──
        let _ = crate::ai_core::scheduler::register_ai_policy_domain();

        #[cfg(CONFIG_AI_SYSFS)]
        let sysfs_reg = sysfs::SysfsRegistrar::register()?;

        let ollama_name = CStr::from_bytes_with_nul(b"ollama\0")
            .map_err(|_| EINVAL)?;
        model_reg.register(ollama_name, true);

        let opencode_name = CStr::from_bytes_with_nul(b"opencode\0")
            .map_err(|_| EINVAL)?;
        model_reg.register(opencode_name, true);

        pr_info!("AI subsystem ready\n");

        Ok(Self {
            _sched: sched,
            _mem_mgr: mem_mgr,
            _monitor: monitor,
            _model_reg: model_reg,
            _local_mgr: local_mgr,
            _cloud_mgr: cloud_mgr,
            #[cfg(CONFIG_AI_SYSFS)]
            _sysfs_reg: sysfs_reg,
        })
    }
}

unsafe impl Send for AiSubsystem {}
unsafe impl Sync for AiSubsystem {}

impl Drop for AiSubsystem {
    fn drop(&mut self) {
        pr_info!("AI subsystem shutting down\n");
        crate::ai_core::scheduler::unregister_ai_policy_domain();
        ioctl::exit();
        unsafe { ai_misc_unregister() };
    }
}
