// SPDX-License-Identifier: GPL-2.0-only
//! Type-safe CPU feature detection for scattered CPUID leaves.
//!
//! Replaces `arch/x86/kernel/cpu/scattered.c` with a const-generic,
//! type-safe table where each entry's register field is an enum
//! rather than a raw integer. The compiler rejects out-of-range
//! register indices at compile time.

#![no_std]

/// Register selection for CPUID output.
#[repr(C)]
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum CpuidReg {
    Eax = 0,
    Ebx = 1,
    Ecx = 2,
    Edx = 3,
}

/// A single scattered CPUID feature entry.
/// Maps a feature bit to a specific CPUID leaf/subleaf/register/bit position.
#[repr(C)]
#[derive(Clone, Copy, Debug)]
pub struct CpuidBit {
    pub feature: u16,
    pub reg: CpuidReg,
    pub bit: u8,
    pub level: u32,
    pub sub_leaf: u32,
}

// Helper to construct CpuidBit entries more ergonomically.
macro_rules! bit {
    ($feature:ident, $reg:ident, $bit:expr, $leaf:expr, $sub:expr) => {
        CpuidBit {
            feature: x86_features::$feature as u16,
            reg: CpuidReg::$reg,
            bit: $bit,
            level: $leaf,
            sub_leaf: $sub,
        }
    };
}

/// Feature constants matching the kernel's X86_FEATURE_* values.
#[allow(non_snake_case, dead_code)]
pub mod x86_features {
    // Scattered features (from scattered.c)
    pub const APERFMPERF: u16 = 0;
    pub const EPB: u16 = 1;
    pub const INTEL_PPIN: u16 = 2;
    pub const RRSBA_CTRL: u16 = 3;
    pub const BHI_CTRL: u16 = 4;
    pub const CQM_LLC: u16 = 5;
    pub const CQM_OCCUP_LLC: u16 = 6;
    pub const CQM_MBM_TOTAL: u16 = 7;
    pub const CQM_MBM_LOCAL: u16 = 8;
    pub const CAT_L3: u16 = 9;
    pub const CAT_L2: u16 = 10;
    pub const CDP_L3: u16 = 11;
    pub const CDP_L2: u16 = 12;
    pub const MBA: u16 = 13;
    pub const PER_THREAD_MBA: u16 = 14;
    pub const SGX1: u16 = 15;
    pub const SGX2: u16 = 16;
    pub const SGX_EDECCSSA: u16 = 17;
    pub const HW_PSTATE: u16 = 18;
    pub const CPB: u16 = 19;
    pub const PROC_FEEDBACK: u16 = 20;
    pub const SMBA: u16 = 21;
    pub const BMEC: u16 = 22;
    pub const PERFMON_V2: u16 = 23;
    pub const AMD_LBR_V2: u16 = 24;
    pub const AMD_LBR_PMC_FREEZE: u16 = 25;
}

/// The full table of scattered CPUID features.
/// Sorted by CPUID level for faster search.
const CPUID_BITS: &[CpuidBit] = &[
    bit!(APERFMPERF, Ecx, 0, 0x00000006, 0),
    bit!(EPB, Ecx, 3, 0x00000006, 0),
    bit!(INTEL_PPIN, Ebx, 0, 0x00000007, 1),
    bit!(RRSBA_CTRL, Edx, 2, 0x00000007, 2),
    bit!(BHI_CTRL, Edx, 4, 0x00000007, 2),
    bit!(CQM_LLC, Edx, 1, 0x0000000f, 0),
    bit!(CQM_OCCUP_LLC, Edx, 0, 0x0000000f, 1),
    bit!(CQM_MBM_TOTAL, Edx, 1, 0x0000000f, 1),
    bit!(CQM_MBM_LOCAL, Edx, 2, 0x0000000f, 1),
    bit!(CAT_L3, Ebx, 1, 0x00000010, 0),
    bit!(CAT_L2, Ebx, 2, 0x00000010, 0),
    bit!(CDP_L3, Ecx, 2, 0x00000010, 1),
    bit!(CDP_L2, Ecx, 2, 0x00000010, 2),
    bit!(MBA, Ebx, 3, 0x00000010, 0),
    bit!(PER_THREAD_MBA, Ecx, 0, 0x00000010, 3),
    bit!(SGX1, Eax, 0, 0x00000012, 0),
    bit!(SGX2, Eax, 1, 0x00000012, 0),
    bit!(SGX_EDECCSSA, Eax, 11, 0x00000012, 0),
    bit!(HW_PSTATE, Edx, 7, 0x80000007, 0),
    bit!(CPB, Edx, 9, 0x80000007, 0),
    bit!(PROC_FEEDBACK, Edx, 11, 0x80000007, 0),
    bit!(MBA, Ebx, 6, 0x80000008, 0),
    bit!(SMBA, Ebx, 2, 0x80000020, 0),
    bit!(BMEC, Ebx, 3, 0x80000020, 0),
    bit!(PERFMON_V2, Eax, 0, 0x80000022, 0),
    bit!(AMD_LBR_V2, Eax, 1, 0x80000022, 0),
    bit!(AMD_LBR_PMC_FREEZE, Eax, 2, 0x80000022, 0),
];

/// Callback type for `set_cpu_cap`.
/// The C side provides this function pointer so Rust can set feature bits
/// on the `struct cpuinfo_x86` without needing to know its layout.
type SetCpuCapFn = unsafe extern "C" fn(cpu_data: *mut core::ffi::c_void, feature: u16);

/// Callback type for `cpuid_eax`.
type CpuidEaxFn = unsafe extern "C" fn(leaf: u32) -> u32;

/// Callback type for `cpuid_count`.
type CpuidCountFn = unsafe extern "C" fn(
    leaf: u32,
    subleaf: u32,
    eax: *mut u32,
    ebx: *mut u32,
    ecx: *mut u32,
    edx: *mut u32,
);

/// Validate that a CPUID leaf is valid for a given level.
/// Returns true if `level` is within the CPU's reported maximum for that leaf's bank.
fn is_cpuid_level_valid(level: u32, cpuid_eax: unsafe extern "C" fn(u32) -> u32) -> bool {
    let max_level = unsafe { cpuid_eax(level & 0xffff0000) };
    if max_level < level {
        return false;
    }
    // The upper bound check allows some permissiveness for CPUs that report
    // extended levels with high upper bits, but ensures we don't probe
    // completely invalid ranges.
    if max_level > (level | 0xffff) {
        return false;
    }
    true
}

/// Check if a specific bit is set in the register value array.
fn bit_is_set(regs: &[u32; 4], reg: CpuidReg, bit: u8) -> bool {
    let idx = reg as usize;
    if idx >= 4 {
        return false;
    }
    (regs[idx] & (1u32 << bit)) != 0
}

/// Detect all scattered CPU features for a given CPU.
///
/// # Safety
///
/// `cpu_data` must be a valid pointer to `struct cpuinfo_x86`. The callbacks
/// `set_cpu_cap`, `cpuid_eax_fn`, and `cpuid_count_fn` must be safe to call
/// and must behave correctly for all inputs passed by this function.
#[no_mangle]
pub unsafe extern "C" fn rust_init_scattered_features_raw(
    cpu_data: *mut core::ffi::c_void,
    set_cpu_cap: SetCpuCapFn,
    cpuid_eax_fn: CpuidEaxFn,
    cpuid_count_fn: CpuidCountFn,
) {
    for entry in CPUID_BITS {
        if !is_cpuid_level_valid(entry.level, cpuid_eax_fn) {
            continue;
        }

        let mut regs: [u32; 4] = [0; 4];
        cpuid_count_fn(
            entry.level,
            entry.sub_leaf,
            &mut regs[0],
            &mut regs[1],
            &mut regs[2],
            &mut regs[3],
        );

        if bit_is_set(&regs, entry.reg, entry.bit) {
            set_cpu_cap(cpu_data, entry.feature);
        }
    }
}

/// Return the number of scattered CPUID feature entries.
/// Can be used by C code to iterate the feature table.
#[no_mangle]
pub extern "C" fn rust_cpuid_bit_count() -> u32 {
    CPUID_BITS.len() as u32
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_table_not_empty() {
        assert!(!CPUID_BITS.is_empty());
        assert_eq!(CPUID_BITS.len() as u32, rust_cpuid_bit_count());
    }

    #[test]
    fn test_reg_enum_values() {
        assert_eq!(CpuidReg::Eax as u32, 0);
        assert_eq!(CpuidReg::Ebx as u32, 1);
        assert_eq!(CpuidReg::Ecx as u32, 2);
        assert_eq!(CpuidReg::Edx as u32, 3);
    }

    #[test]
    fn test_no_invalid_register_indices() {
        for entry in CPUID_BITS {
            let idx = entry.reg as usize;
            assert!(idx < 4, "Register index {} out of range for feature", idx);
        }
    }

    #[test]
    fn test_all_features_have_bit_in_0_31() {
        for entry in CPUID_BITS {
            assert!(
                entry.bit < 32,
                "Bit {} out of range for feature",
                entry.bit
            );
        }
    }

    #[test]
    fn test_feature_constants_are_distinct() {
        let mut seen = [false; 256];
        for entry in CPUID_BITS {
            let f = entry.feature as usize;
            assert!(
                f < 256,
                "Feature constant {} exceeds test array size",
                f
            );
            // MBA appears twice (Intel and AMD leaves) — that's expected
            if seen[f] {
                // Only MBA should be duplicated
                let is_mba = entry.feature == x86_features::MBA;
                assert!(is_mba, "Feature {} appears twice!", entry.feature);
            }
            seen[f] = true;
        }
    }

    #[test]
    fn test_bit_is_set_works() {
        let regs = [0x00000001u32, 0x00000002, 0x00000004, 0x00000008];
        assert!(bit_is_set(&regs, CpuidReg::Eax, 0));
        assert!(!bit_is_set(&regs, CpuidReg::Eax, 1));
        assert!(bit_is_set(&regs, CpuidReg::Ebx, 1));
        assert!(bit_is_set(&regs, CpuidReg::Ecx, 2));
        assert!(bit_is_set(&regs, CpuidReg::Edx, 3));
    }
}
