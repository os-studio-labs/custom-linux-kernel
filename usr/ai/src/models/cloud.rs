// SPDX-License-Identifier: GPL-2.0

//! Cloud AI endpoint management.
//!
//! Tracks configured cloud AI endpoints for the userspace
//! ai-mgr daemon to use.

use alloc::vec::Vec;
use ::core::cmp;
use ::core::sync::atomic::{AtomicU32, Ordering};

use kernel::prelude::*;
use kernel::sync::{new_spinlock, SpinLock};

/// A cloud AI endpoint.
#[derive(Debug, Clone)]
pub struct CloudEndpoint {
    pub id: u32,
    pub url: [u8; 256],
    pub url_len: usize,
    pub timeout_ms: u32,
    pub priority: u32,
}

/// Cloud endpoint registry.
#[pin_data]
pub struct CloudEndpointManager {
    #[pin]
    endpoints: SpinLock<Vec<CloudEndpoint>>,
    next_id: AtomicU32,
}

impl CloudEndpointManager {
    pub fn new() -> impl PinInit<Self> {
        pin_init!(Self {
            endpoints <- new_spinlock!(Vec::new()),
            next_id: AtomicU32::new(1),
        })
    }

    pub fn add(&self, raw_url: &[u8], timeout_ms: u32, priority: u32) -> u32 {
        let id = self.next_id.fetch_add(1, Ordering::Relaxed);

        let mut url = [0u8; 256];
        let len = cmp::min(raw_url.len(), 255);
        url[..len].copy_from_slice(&raw_url[..len]);
        url[len] = 0;

        let mut guard = self.endpoints.lock();
        let _ = guard.try_push(CloudEndpoint {
            id,
            url,
            url_len: len,
            timeout_ms,
            priority,
        });

        id
    }

    pub fn remove(&self, id: u32) -> Result {
        let mut guard = self.endpoints.lock();
        let len_before = guard.len();
        guard.retain(|e| e.id != id);
        if guard.len() == len_before {
            return Err(ENOENT);
        }
        Ok(())
    }

    pub fn count(&self) -> usize {
        self.endpoints.lock().len()
    }

    pub fn snapshot(&self) -> Vec<CloudEndpoint> {
        let mut out = Vec::new();
        for e in self.endpoints.lock().iter() {
            let _ = out.try_push(e.clone());
        }
        out
    }
}

unsafe impl Send for CloudEndpointManager {}
unsafe impl Sync for CloudEndpointManager {}
