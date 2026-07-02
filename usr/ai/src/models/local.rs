// SPDX-License-Identifier: GPL-2.0

//! Local AI model management.
//!
//! Detects, registers, and optimises locally-running AI models
//! (e.g., ollama, opencode).  Applies memory and CPU priority
//! boosts so local inference stays responsive.

use kernel::prelude::*;
use kernel::str::CStr;
use kernel::sync::Arc;

use super::ModelRegistry;
use crate::ai_core::memory::AiMemoryManager;
use crate::ai_core::MemoryPolicy;
use crate::ai_core::scheduler::AiScheduler;
use crate::ai_core::{AiProcess, Priority, WorkloadType};

/// Manages locally-running AI model processes.
pub struct LocalModelManager {
    registry: Arc<ModelRegistry>,
    scheduler: Arc<AiScheduler>,
    memory: Arc<AiMemoryManager>,
}

impl LocalModelManager {
    pub fn new(
        registry: Arc<ModelRegistry>,
        scheduler: Arc<AiScheduler>,
        memory: Arc<AiMemoryManager>,
    ) -> Self {
        Self {
            registry,
            scheduler,
            memory,
        }
    }

    /// Register a local model process (e.g., ollama serving).
    pub fn register_local_process(&self, pid: i32, model_name: &CStr) -> Result {
        let _model_id = self.registry.register(model_name, true);

        let proc = AiProcess {
            pid,
            workload: WorkloadType::Inference,
            priority: Priority::new(6),
            memory_policy: MemoryPolicy::HugePage,
            is_local: true,
        };

        self.scheduler.register_process(proc)?;

        #[cfg(CONFIG_AI_DEBUG)]
        pr_debug!("ai_local: pid {} model id {} registered\n", pid, model_id);

        Ok(())
    }

    /// Hint that a local model's memory should use huge pages.
    pub fn hint_hugepages(&self, pid: i32, addr: u64, size: u64) -> Result {
        self.memory
            .apply_hint(pid, addr, size, MemoryPolicy::HugePage)
    }

    /// Prioritise this local model's CPU scheduling.
    #[cfg(CONFIG_AI_LOCAL_PRIORITY)]
    pub fn boost_priority(&self, pid: i32) -> Result {
        self.scheduler.register_process(AiProcess {
            pid,
            workload: WorkloadType::Inference,
            priority: Priority::new(7),
            memory_policy: MemoryPolicy::HugePage,
            is_local: true,
        })
    }

    /// Remove a local model from tracking.
    pub fn unregister_process(&self, pid: i32) {
        self.scheduler.unregister_process(pid);
        self.memory.release_process(pid);
    }
}
