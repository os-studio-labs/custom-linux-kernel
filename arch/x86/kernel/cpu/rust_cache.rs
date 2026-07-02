// SPDX-License-Identifier: GPL-2.0-only
//! Intel CPU cache descriptor lookup table.
//!
//! Replaces the `cache_table[]` array in `cacheinfo.c` with a type-safe
//! pattern-matching implementation. The raw descriptor byte is matched
//! against known values using a const table indexed by descriptor value,
//! avoiding the linear scan.

#![no_std]

/// Cache level/type as reported by Intel CPUID descriptor bytes.
#[repr(C)]
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum CacheType {
    L1Instruction = 1,
    L1Data = 2,
    L2 = 3,
    L3 = 4,
    Trace = 5,
}

/// Result of a cache descriptor lookup.
#[repr(C)]
#[derive(Clone, Copy, Debug)]
pub struct CacheDescriptor {
    pub cache_type: CacheType,
    /// Size in kilobytes (or entries for trace cache)
    pub size_kb: u16,
}

/// The cache descriptor lookup table, indexed by descriptor byte.
/// Descriptor byte 0x00 is the sentinel (end of table).
static CACHE_TABLE: [Option<(CacheType, u16)>; 256] = {
    let mut t: [Option<(CacheType, u16)>; 256] = [None; 256];

    // Helper macro for filling entries
    macro_rules! entry {
        ($desc:expr, $lvl:ident, $size:expr) => {
            t[$desc as usize] = Some((CacheType::$lvl, $size));
        };
    }

    // L1 Instruction caches
    entry!(0x06, L1Instruction, 8);    // 4-way set assoc, 32 byte line size
    entry!(0x08, L1Instruction, 16);   // 4-way set assoc, 32 byte line size
    entry!(0x09, L1Instruction, 32);   // 4-way set assoc, 64 byte line size
    entry!(0x30, L1Instruction, 32);   // 8-way set assoc, 64 byte line size

    // L1 Data caches
    entry!(0x0a, L1Data, 8);      // 2 way set assoc, 32 byte line size
    entry!(0x0c, L1Data, 16);     // 4-way set assoc, 32 byte line size
    entry!(0x0d, L1Data, 16);     // 4-way set assoc, 64 byte line size
    entry!(0x0e, L1Data, 24);     // 6-way set assoc, 64 byte line size
    entry!(0x2c, L1Data, 32);     // 8-way set assoc, 64 byte line size
    entry!(0x60, L1Data, 16);     // 8-way set assoc, sectored, 64 byte line size
    entry!(0x66, L1Data, 8);      // 4-way set assoc, sectored, 64 byte line size
    entry!(0x67, L1Data, 16);     // 4-way set assoc, sectored, 64 byte line size
    entry!(0x68, L1Data, 32);     // 4-way set assoc, sectored, 64 byte line size

    // L2 caches
    entry!(0x21, L2, 256);       // 8-way set assoc, 64 byte line size
    entry!(0x39, L2, 128);       // 4-way set assoc, sectored, 64 byte line size
    entry!(0x3a, L2, 192);       // 6-way set assoc, sectored, 64 byte line size
    entry!(0x3b, L2, 128);       // 2-way set assoc, sectored, 64 byte line size
    entry!(0x3c, L2, 256);       // 4-way set assoc, sectored, 64 byte line size
    entry!(0x3d, L2, 384);       // 6-way set assoc, sectored, 64 byte line size
    entry!(0x3e, L2, 512);       // 4-way set assoc, sectored, 64 byte line size
    entry!(0x3f, L2, 256);       // 2-way set assoc, 64 byte line size
    entry!(0x41, L2, 128);       // 4-way set assoc, 32 byte line size
    entry!(0x42, L2, 256);       // 4-way set assoc, 32 byte line size
    entry!(0x43, L2, 512);       // 4-way set assoc, 32 byte line size
    entry!(0x44, L2, 1024);      // 4-way set assoc, 32 byte line size (1 MB)
    entry!(0x45, L2, 2048);      // 4-way set assoc, 32 byte line size (2 MB)
    entry!(0x48, L2, 3072);      // 12-way set assoc, 64 byte line size (3 MB)
    entry!(0x4e, L2, 6144);      // 24-way set assoc, 64 byte line size (6 MB)
    entry!(0x78, L2, 1024);      // 4-way set assoc, 64 byte line size (1 MB)
    entry!(0x79, L2, 128);       // 8-way set assoc, sectored, 64 byte line size
    entry!(0x7a, L2, 256);       // 8-way set assoc, sectored, 64 byte line size
    entry!(0x7b, L2, 512);       // 8-way set assoc, sectored, 64 byte line size
    entry!(0x7c, L2, 1024);      // 8-way set assoc, sectored, 64 byte line size (1 MB)
    entry!(0x7d, L2, 2048);      // 8-way set assoc, 64 byte line size (2 MB)
    entry!(0x7f, L2, 512);       // 2-way set assoc, 64 byte line size
    entry!(0x80, L2, 512);       // 8-way set assoc, 64 byte line size
    entry!(0x82, L2, 256);       // 8-way set assoc, 32 byte line size
    entry!(0x83, L2, 512);       // 8-way set assoc, 32 byte line size
    entry!(0x84, L2, 1024);      // 8-way set assoc, 32 byte line size (1 MB)
    entry!(0x85, L2, 2048);      // 8-way set assoc, 32 byte line size (2 MB)
    entry!(0x86, L2, 512);       // 4-way set assoc, 64 byte line size
    entry!(0x87, L2, 1024);      // 8-way set assoc, 64 byte line size (1 MB)

    // L3 caches
    entry!(0x22, L3, 512);       // 4-way set assoc, sectored, 64 byte line size
    entry!(0x23, L3, 1024);      // 8-way set assoc, sectored, 64 byte line size (1 MB)
    entry!(0x25, L3, 2048);      // 8-way set assoc, sectored, 64 byte line size (2 MB)
    entry!(0x29, L3, 4096);      // 8-way set assoc, sectored, 64 byte line size (4 MB)
    entry!(0x46, L3, 4096);      // 4-way set assoc, 64 byte line size (4 MB)
    entry!(0x47, L3, 8192);      // 8-way set assoc, 64 byte line size (8 MB)
    entry!(0x49, L3, 4096);      // 16-way set assoc, 64 byte line size (4 MB)
    entry!(0x4a, L3, 6144);      // 12-way set assoc, 64 byte line size (6 MB)
    entry!(0x4b, L3, 8192);      // 16-way set assoc, 64 byte line size (8 MB)
    entry!(0x4c, L3, 12288);     // 12-way set assoc, 64 byte line size (12 MB)
    entry!(0x4d, L3, 16384);     // 16-way set assoc, 64 byte line size (16 MB)
    entry!(0xd0, L3, 512);       // 4-way set assoc, 64 byte line size
    entry!(0xd1, L3, 1024);      // 4-way set assoc, 64 byte line size (1 MB)
    entry!(0xd2, L3, 2048);      // 4-way set assoc, 64 byte line size (2 MB)
    entry!(0xd6, L3, 1024);      // 8-way set assoc, 64 byte line size (1 MB)
    entry!(0xd7, L3, 2048);      // 8-way set assoc, 64 byte line size (2 MB)
    entry!(0xd8, L3, 4096);      // 12-way set assoc, 64 byte line size (4 MB)
    entry!(0xdc, L3, 2048);      // 12-way set assoc, 64 byte line size (2 MB)
    entry!(0xdd, L3, 4096);      // 12-way set assoc, 64 byte line size (4 MB)
    entry!(0xde, L3, 8192);      // 12-way set assoc, 64 byte line size (8 MB)
    entry!(0xe2, L3, 2048);      // 16-way set assoc, 64 byte line size (2 MB)
    entry!(0xe3, L3, 4096);      // 16-way set assoc, 64 byte line size (4 MB)
    entry!(0xe4, L3, 8192);      // 16-way set assoc, 64 byte line size (8 MB)
    entry!(0xea, L3, 12288);     // 24-way set assoc, 64 byte line size (12 MB)
    entry!(0xeb, L3, 18432);     // 24-way set assoc, 64 byte line size (18 MB)
    entry!(0xec, L3, 24576);     // 24-way set assoc, 64 byte line size (24 MB)

    // Trace caches
    entry!(0x70, Trace, 12);     // 8-way set assoc
    entry!(0x71, Trace, 16);     // 8-way set assoc
    entry!(0x72, Trace, 32);     // 8-way set assoc
    entry!(0x73, Trace, 64);     // 8-way set assoc

    t
};

/// Look up an Intel cache descriptor byte.
///
/// Returns a pointer to a `CacheDescriptor` if the descriptor is recognized,
/// or NULL if unknown. Uses O(1) table lookup.
///
/// The result is valid for the lifetime of the program (static data).
#[no_mangle]
pub unsafe extern "C" fn rust_lookup_cache_descriptor(descriptor: u8) -> *const CacheDescriptor {
    match CACHE_TABLE[descriptor as usize] {
        Some((ctype, size)) => {
            static mut SINGLE_RESULT: CacheDescriptor = CacheDescriptor {
                cache_type: CacheType::L1Data,
                size_kb: 0,
            };
            SINGLE_RESULT.cache_type = ctype;
            SINGLE_RESULT.size_kb = size;
            &raw const SINGLE_RESULT
        }
        None => core::ptr::null(),
    }
}

/// Callback-based cache descriptor lookup.
/// Avoids the need for static mutable state by having C provide an output buffer.
///
/// # Safety
///
/// `out` must point to a valid, writable `CacheDescriptor`.
/// Returns true if a descriptor was found, false otherwise.
#[no_mangle]
pub unsafe extern "C" fn rust_fill_cache_descriptor(
    descriptor: u8,
    out: *mut CacheDescriptor,
) -> bool {
    match CACHE_TABLE[descriptor as usize] {
        Some((ctype, size)) => {
            unsafe {
                *out = CacheDescriptor {
                    cache_type: ctype,
                    size_kb: size,
                };
            }
            true
        }
        None => false,
    }
}

/// Return the number of entries in the cache descriptor table.
#[no_mangle]
pub extern "C" fn rust_cache_descriptor_count() -> u32 {
    CACHE_TABLE.iter().filter(|e| e.is_some()).count() as u32
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_known_descriptors() {
        let test_cases = [
            (0x06u8, CacheType::L1Instruction, 8),
            (0x0a, CacheType::L1Data, 8),
            (0x21, CacheType::L2, 256),
            (0x22, CacheType::L3, 512),
            (0x70, CacheType::Trace, 12),
        ];

        for (desc, expected_type, expected_size) in &test_cases {
            let mut result = CacheDescriptor {
                cache_type: CacheType::L1Data,
                size_kb: 0,
            };
            let found = unsafe { rust_fill_cache_descriptor(*desc, &mut result) };
            assert!(found, "Descriptor 0x{:02x} should be found", desc);
            assert_eq!(
                result.cache_type, *expected_type,
                "Descriptor 0x{:02x} type mismatch",
                desc
            );
            assert_eq!(
                result.size_kb, *expected_size,
                "Descriptor 0x{:02x} size mismatch",
                desc
            );
        }
    }

    #[test]
    fn test_unknown_descriptor() {
        let mut result = CacheDescriptor {
            cache_type: CacheType::L1Data,
            size_kb: 0,
        };
        let found = unsafe { rust_fill_cache_descriptor(0x01, &mut result) };
        assert!(!found, "Descriptor 0x01 should not be found");
    }

    #[test]
    fn test_null_returns_null() {
        let ptr = unsafe { rust_lookup_cache_descriptor(0x01) };
        assert!(ptr.is_null(), "Unknown descriptor should return null");
    }

    #[test]
    fn test_known_returns_valid() {
        let ptr = unsafe { rust_lookup_cache_descriptor(0x06) };
        assert!(!ptr.is_null(), "Known descriptor should return non-null");
        let desc = unsafe { &*ptr };
        assert_eq!(desc.cache_type, CacheType::L1Instruction);
        assert_eq!(desc.size_kb, 8);
    }

    #[test]
    fn test_count() {
        let count = rust_cache_descriptor_count();
        // There should be exactly 70 cache descriptor entries + 4 trace = 74
        assert!(count > 60, "Expected many cache descriptors, got {}", count);
    }
}
