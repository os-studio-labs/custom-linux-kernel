// SPDX-License-Identifier: GPL-2.0

//! KUnit tests for the AI subsystem core.
//!
//! Run with: `kunit.py run --kunitconfig=usr/ai/tests/`

use crate::core::{AiProcess, MemoryPolicy, Priority, WorkloadType};
use kernel::prelude::*;

#[kunit_test]
fn ai_test_workload_classification() {
    let cases = [
        (0, WorkloadType::Unknown),
        (1, WorkloadType::Inference),
        (2, WorkloadType::Training),
        (3, WorkloadType::Embedding),
    ];
    for (input, expected) in &cases {
        kunit_assert_eq!(WorkloadType::from_u32(*input), *expected);
    }
}

#[kunit_test]
fn ai_test_priority_conversion() {
    // Priority 4 (default) -> 0 nice offset
    kunit_assert_eq!(Priority::new(4).to_nice_offset(), 0);
    // Priority 7 (max) -> -6 nice offset (boost)
    kunit_assert_eq!(Priority::new(7).to_nice_offset(), -6);
    // Priority 0 (min) -> +8 nice offset (de-prioritise)
    kunit_assert_eq!(Priority::new(0).to_nice_offset(), 8);
}

#[kunit_test]
fn ai_test_memory_policy_roundtrip() {
    kunit_assert_eq!(MemoryPolicy::from_u32(1), MemoryPolicy::HugePage);
    kunit_assert_eq!(MemoryPolicy::from_u32(2), MemoryPolicy::Locked);
    kunit_assert_eq!(MemoryPolicy::from_u32(0), MemoryPolicy::Default);
}

kunit_test_suite!("ai_core", ai_test_workload_classification, ai_test_priority_conversion, ai_test_memory_policy_roundtrip);
