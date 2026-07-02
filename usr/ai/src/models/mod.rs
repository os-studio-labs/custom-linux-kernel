// SPDX-License-Identifier: GPL-2.0

//! AI model management — local and cloud-backed models.

pub mod cloud;
pub mod local;

use alloc::vec::Vec;
use ::core::sync::atomic::{AtomicU32, Ordering};

use kernel::prelude::*;
use kernel::str::CStr;
use kernel::sync::{new_spinlock, SpinLock};

/// Descriptor for an AI model known to the subsystem.
#[derive(Debug, Clone)]
pub struct ModelInfo {
    pub id: u32,
    pub name: [u8; 64],
    pub name_len: usize,
    pub is_local: bool,
    pub memory_usage: u64,
    pub parameter_count: u64,
    pub priority: u8,
}

/// Global model registry.
#[pin_data]
pub struct ModelRegistry {
    #[pin]
    models: SpinLock<Vec<ModelInfo>>,
    next_id: AtomicU32,
}

impl ModelRegistry {
    pub fn new() -> impl PinInit<Self> {
        pin_init!(Self {
            models <- new_spinlock!(Vec::new()),
            next_id: AtomicU32::new(1),
        })
    }

    pub fn register(&self, name: &CStr, is_local: bool) -> u32 {
        let id = self.next_id.fetch_add(1, Ordering::Relaxed);
        let bytes = name.as_bytes();
        let len = ::core::cmp::min(bytes.len(), 63);

        let mut name_buf = [0u8; 64];
        name_buf[..len].copy_from_slice(&bytes[..len]);
        name_buf[len] = 0;

        let mut guard = self.models.lock();
        let _ = guard.try_push(ModelInfo {
            id,
            name: name_buf,
            name_len: len,
            is_local,
            memory_usage: 0,
            parameter_count: 0,
            priority: 4,
        });
        id
    }

    pub fn unregister(&self, id: u32) {
        let mut guard = self.models.lock();
        guard.retain(|m| m.id != id);
    }

    pub fn count(&self) -> usize {
        self.models.lock().len()
    }

    pub fn update_memory(&self, id: u32, bytes: u64) {
        let mut guard = self.models.lock();
        if let Some(m) = guard.iter_mut().find(|m| m.id == id) {
            m.memory_usage = bytes;
        }
    }

    pub fn snapshot(&self) -> Vec<ModelInfo> {
        let mut out = Vec::new();
        for m in self.models.lock().iter() {
            let _ = out.try_push(m.clone());
        }
        out
    }

    pub fn total_local_memory(&self) -> u64 {
        self.models
            .lock()
            .iter()
            .filter(|m| m.is_local)
            .map(|m| m.memory_usage)
            .sum()
    }

    pub fn total_cloud_memory(&self) -> u64 {
        self.models
            .lock()
            .iter()
            .filter(|m| !m.is_local)
            .map(|m| m.memory_usage)
            .sum()
    }
}

unsafe impl Send for ModelRegistry {}
unsafe impl Sync for ModelRegistry {}
