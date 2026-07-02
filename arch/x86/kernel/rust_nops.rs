// SPDX-License-Identifier: GPL-2.0-only
//! Type-safe NOP instruction generation for x86 alternatives patching.
//!
//! Replaces `add_nop()` and the `x86_nops[]` table in `alternative.c`
//! with a memory-safe, enum-based implementation.
//!
//! NOP instruction selection for 64-bit:
//! - 1 byte:  0x90                          (NOP)
//! - 2 bytes: 0x66 0x90                     (66 NOP)
//! - 3 bytes: 0x0f 0x1f 0x00               (NOP 3)
//! - 4 bytes: 0x0f 0x1f 0x40 0x00          (NOP 4)
//! - 5 bytes: 0x0f 0x1f 0x44 0x00 0x00     (NOP 5)
//! - 6 bytes: 0x66 0x0f 0x1f 0x44 0x00 0x00 (66 NOP 5)
//! - 7 bytes: 0x0f 0x1f 0x80 0x00 0x00 0x00 0x00 (NOP 7)
//! - 8 bytes: 0x0f 0x1f 0x84 0x00 0x00 0x00 0x00 0x00 (NOP 8)
//! - 9 bytes: 0x2e 0x0f 0x1f 0x84 0x00 0x00 0x00 0x00 0x00 (CS NOP 8)
//! - 10 bytes: 0x66 0x2e 0x0f 0x1f 0x84 0x00 0x00 0x00 0x00 0x00 (66 CS NOP 8)
//! - 11 bytes: 0x66 0x66 0x2e 0x0f 0x1f 0x84 0x00 0x00 0x00 0x00 0x00 (66 66 CS NOP 8)

#![no_std]

/// Maximum NOP instruction size on x86-64.
const ASM_NOP_MAX: usize = 11;

/// NOP sequences indexed by length (1..=ASM_NOP_MAX).
/// Each entry is a byte array of the exact NOP bytes for that length.
static X86_NOPS: [&[u8]; ASM_NOP_MAX + 1] = {
    const NOP1: [u8; 1] = [0x90u8];
    const NOP2: [u8; 2] = [0x66u8, 0x90];
    const NOP3: [u8; 3] = [0x0fu8, 0x1f, 0x00];
    const NOP4: [u8; 4] = [0x0fu8, 0x1f, 0x40, 0x00];
    const NOP5: [u8; 5] = [0x0fu8, 0x1f, 0x44, 0x00, 0x00];
    const NOP6: [u8; 6] = [0x66u8, 0x0f, 0x1f, 0x44, 0x00, 0x00];
    const NOP7: [u8; 7] = [0x0fu8, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00];
    const NOP8: [u8; 8] = [0x0fu8, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00];
    const NOP9: [u8; 9] = [0x2eu8, 0x0f, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00];
    const NOP10: [u8; 10] = [0x66u8, 0x2e, 0x0f, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00];
    const NOP11: [u8; 11] = [0x66u8, 0x66, 0x2e, 0x0f, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00];

    [
        &[],        // index 0: zero-length (invalid)
        &NOP1,      // index 1
        &NOP2,      // index 2
        &NOP3,      // index 3
        &NOP4,      // index 4
        &NOP5,      // index 5
        &NOP6,      // index 6
        &NOP7,      // index 7
        &NOP8,      // index 8
        &NOP9,      // index 9
        &NOP10,     // index 10
        &NOP11,     // index 11
    ]
};

/// JMP opcodes for padding.
const JMP8_OPCODE: u8 = 0xEB;   // 2-byte short jump
const JMP32_OPCODE: u8 = 0xE9;  // 5-byte near jump
const INT3_OPCODE: u8 = 0xCC;   // debug trap

/// Generate a relative jump instruction at `instr` targeting `target`.
///
/// Returns the number of bytes written. The jump can be either short (2 bytes, ±127 range)
/// or near (5 bytes, ±2G range).
///
/// # Safety
///
/// `instr` and `target` must be valid pointers to code within the kernel text section.
unsafe fn gen_jump(instr: &mut [u8], target: *const u8) -> usize {
    let instr_ptr = instr.as_ptr();
    let offset = (target as usize).wrapping_sub(instr_ptr as usize) as isize;

    if offset >= -128 && offset <= 127 {
        // Short jump
        instr[0] = JMP8_OPCODE;
        instr[1] = offset as u8;
        2
    } else {
        // Near jump
        instr[0] = JMP32_OPCODE;
        let offset32 = offset as i32;
        instr[1..5].copy_from_slice(&offset32.to_le_bytes());
        5
    }
}

/// Fill a buffer with NOP instructions.
///
/// For lengths <= ASM_NOP_MAX, uses the optimal multi-byte NOP from the table.
/// For lengths > ASM_NOP_MAX, emits a jump over INT3 padding to avoid long NOPs
/// that would bloat ORC unwind tables.
///
/// # Safety
///
/// `instr` must point to a valid writable memory region of at least `len` bytes.
/// This function is typically called during kernel patching where code pages are
/// made writable via `text_poke_early()`.
#[no_mangle]
pub unsafe extern "C" fn rust_add_nop(instr: *mut u8, len: u32) {
    let len = len as usize;
    if len == 0 {
        return;
    }

    let target = unsafe { instr.add(len) };
    let buf = unsafe { core::slice::from_raw_parts_mut(instr, len) };

    if len <= ASM_NOP_MAX {
        let nop = X86_NOPS[len];
        buf[..len].copy_from_slice(nop);
    } else {
        // Emit a jump over INT3 padding
        let jump_size = unsafe { gen_jump(buf, target) };
        let remaining = len - jump_size;
        for byte in buf[jump_size..].iter_mut() {
            *byte = INT3_OPCODE;
        }
        let _ = remaining; // INT3 padding (unused but semantically important)
    }
}

/// Return a pointer to the NOP byte for a given length.
///
/// This allows C code to look up NOP bytes if needed.
/// Returns NULL for length 0 or lengths exceeding ASM_NOP_MAX.
#[no_mangle]
pub unsafe extern "C" fn rust_get_nop(len: u32) -> *const u8 {
    let len = len as usize;
    if len == 0 || len > ASM_NOP_MAX {
        return core::ptr::null();
    }
    X86_NOPS[len].as_ptr()
}

/// Return the effective NOP fill length for a given size.
/// Returns 0 for invalid input, otherwise the input length.
#[no_mangle]
pub extern "C" fn rust_nop_len(len: u32) -> u32 {
    if len == 0 {
        0
    } else {
        len
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_nop_table_sizes() {
        for i in 1..=ASM_NOP_MAX {
            assert_eq!(X86_NOPS[i].len(), i, "NOP size {} mismatch", i);
        }
    }

    #[test]
    fn test_nop_zero_len() {
        let mut buf = [0u8; 16];
        unsafe { rust_add_nop(buf.as_mut_ptr(), 0) };
        assert_eq!(buf, [0u8; 16], "zero-length NOP should not modify buffer");
    }

    #[test]
    fn test_nop_short() {
        for len in 1..=ASM_NOP_MAX {
            let mut buf = [0u8; 16];
            unsafe { rust_add_nop(buf.as_mut_ptr(), len as u32) };
            assert_eq!(&buf[..len], X86_NOPS[len], "NOP of size {}", len);
        }
    }

    #[test]
    fn test_nop_long_jump_padding() {
        let len = 20usize;
        let mut buf = [0u8; 32];
        unsafe { rust_add_nop(buf.as_mut_ptr(), len as u32) };
        // First 2 bytes should be a short jump
        assert_eq!(buf[0], JMP8_OPCODE, "should start with short jump");
        // The offset should be 0x12 (18 = 20 - 2)
        assert_eq!(buf[1], (len - 2) as u8, "jump offset should cover remaining bytes");
        // Remaining bytes should be INT3
        for i in 2..len {
            assert_eq!(buf[i], INT3_OPCODE, "padding byte {} should be INT3", i);
        }
    }

    #[test]
    fn test_get_nop() {
        for i in 1..=ASM_NOP_MAX {
            let ptr = unsafe { rust_get_nop(i as u32) };
            assert!(!ptr.is_null(), "NOP pointer for size {} should not be null", i);
            let slice = unsafe { core::slice::from_raw_parts(ptr, i) };
            assert_eq!(slice, X86_NOPS[i], "NOP data for size {}", i);
        }
    }

    #[test]
    fn test_get_nop_invalid() {
        assert!(unsafe { rust_get_nop(0).is_null() });
        assert!(unsafe { rust_get_nop(ASM_NOP_MAX as u32 + 1).is_null() });
    }

    #[test]
    fn test_nop_len() {
        assert_eq!(rust_nop_len(0), 0);
        assert_eq!(rust_nop_len(5), 5);
        assert_eq!(rust_nop_len(20), 20);
    }
}
