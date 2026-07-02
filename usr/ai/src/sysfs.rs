// SPDX-License-Identifier: GPL-2.0

//! Sysfs interface for the AI subsystem.
//!
//! Uses C helpers to create `/sys/kernel/ai/` and attribute files
//! for runtime control and statistics.

#![allow(stable_features, missing_docs)]

use kernel::prelude::*;

#[used]
#[doc(hidden)]
static __LOG_PREFIX: &[u8] = b"ai_sysfs\0";

extern "C" {
    fn ai_sysfs_init() -> i32;
    fn ai_sysfs_exit();
}

pub struct SysfsRegistrar;

impl SysfsRegistrar {
    pub fn register() -> Result<Self> {
        let ret = unsafe { ai_sysfs_init() };
        if ret < 0 {
            return Err(EFAULT);
        }
        pr_info!("ai_sysfs: /sys/kernel/ai/ created\n");
        Ok(Self)
    }
}

impl Drop for SysfsRegistrar {
    fn drop(&mut self) {
        unsafe { ai_sysfs_exit() };
    }
}
