// SPDX-License-Identifier: GPL-2.0

//! Core AI subsystem types and constants.

pub mod memory;
pub mod monitor;
pub mod scheduler;

/// AI workload classification.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum WorkloadType {
    Unknown = 0,
    Inference = 1,
    Training = 2,
    Embedding = 3,
}

impl WorkloadType {
    pub fn from_u32(v: u32) -> Self {
        match v {
            1 => Self::Inference,
            2 => Self::Training,
            3 => Self::Embedding,
            _ => Self::Unknown,
        }
    }

    pub fn to_u32(self) -> u32 {
        self as u32
    }
}

/// AI task priority (0–7, higher = more resources).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Priority(u8);

impl Priority {
    pub const MIN: Priority = Priority(0);
    pub const MAX: Priority = Priority(7);
    pub const DEFAULT: Priority = Priority(4);

    pub fn new(v: u8) -> Self {
        match v {
            0..=7 => Priority(v),
            _ => Priority::DEFAULT,
        }
    }

    pub fn to_nice_offset(self) -> i32 {
        -((self.0 as i32) - 4) * 2
    }

    pub fn value(self) -> u8 {
        self.0
    }
}

/// Memory policy for AI workload regions.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum MemoryPolicy {
    Default = 0,
    HugePage = 1,
    Locked = 2,
    Compressed = 3,
}

impl MemoryPolicy {
    pub fn from_u32(v: u32) -> Self {
        match v {
            1 => Self::HugePage,
            2 => Self::Locked,
            3 => Self::Compressed,
            _ => Self::Default,
        }
    }
}

/// Describes an AI process known to the subsystem.
#[derive(Debug, Clone)]
pub struct AiProcess {
    pub pid: i32,
    pub workload: WorkloadType,
    pub priority: Priority,
    pub memory_policy: MemoryPolicy,
    pub is_local: bool,
}
