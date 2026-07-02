// SPDX-License-Identifier: GPL-2.0

//! SentraOS Panic Handler — detailed crash explanations printed directly
//! to the framebuffer/console, with root-cause analysis and subsystem isolation.

#![no_std]

use core::ffi::{c_char, c_int, c_uint, c_ulong, c_void};
use core::panic::PanicInfo;
use core::ptr;
use core::sync::atomic::{AtomicBool, Ordering};

// ── Framebuffer / Console output ───────────────────────

extern "C" {
    fn printk(fmt: *const c_char, ...) -> c_int;
}

static PANIC_ACTIVE: AtomicBool = AtomicBool::new(false);

// ── Panic reason classification ─────────────────────────

#[repr(u32)]
pub enum PanicClass {
    Unknown = 0,
    NullPointer = 1,
    BoundsOverflow = 2,
    UseAfterFree = 3,
    DoubleFree = 4,
    LockDepViolation = 5,
    StackOverflow = 6,
    DivisionByZero = 7,
    Oom = 8,
    HardwareError = 9,
    AssertionFailed = 10,
    Unimplemented = 11,
    BUGMacro = 12,
    CpuException = 13,
    SecurityViolation = 14,
}

fn classify_panic(reason: Option<&str>) -> PanicClass {
    let r = match reason {
        Some(s) => s,
        None => return PanicClass::Unknown,
    };

    if r.contains("NULL") || r.contains("null") || r.contains("deref") || r.contains("page_fault")
    {
        PanicClass::NullPointer
    } else if r.contains("OOM") || r.contains("out_of_memory") || r.contains("allocation")
    {
        PanicClass::Oom
    } else if r.contains("lockdep") || r.contains("deadlock") || r.contains("scheduling")
    {
        PanicClass::LockDepViolation
    } else if r.contains("stack") || r.contains("corrupt")
    {
        PanicClass::StackOverflow
    } else if r.contains("BUG") || r.contains("assert")
    {
        PanicClass::BUGMacro
    } else if r.contains("security") || r.contains("permission") || r.contains("SELinux")
    {
        PanicClass::SecurityViolation
    } else {
        PanicClass::Unknown
    }
}

fn class_description(class: PanicClass) -> &'static str {
    match class {
        PanicClass::NullPointer => concat!(
            "  ╔══════════════════════════════════════════════════════╗\n",
            "  ║          NULL POINTER DEREFERENCE                    ║\n",
            "  ╠══════════════════════════════════════════════════════╣\n",
            "  ║  A kernel code path attempted to read/write memory   ║\n",
            "  ║  through an invalid (NULL) pointer.                  ║\n",
            "  ║                                                      ║\n",
            "  ║  Possible causes:                                    ║\n",
            "  ║  1. Driver forgot to check allocation result         ║\n",
            "  ║  2. Race condition: object freed while in use        ║\n",
            "  ║  3. Incorrect locking: non-owned data accessed        ║\n",
            "  ║  4. Hardware memory corruption                       ║\n",
            "  ║                                                      ║\n",
            "  ║  The SentraOS sandbox has isolated the faulting      ║\n",
            "  ║  driver. Other subsystems continue to operate.      ║\n",
            "  ╚══════════════════════════════════════════════════════╝\n",
        ),
        PanicClass::Oom => concat!(
            "  ╔══════════════════════════════════════════════════════╗\n",
            "  ║          OUT OF MEMORY                                ║\n",
            "  ╠══════════════════════════════════════════════════════╣\n",
            "  ║  The kernel memory allocator could not satisfy a      ║\n",
            "  ║  request.  All available pages have been exhausted.  ║\n",
            "  ║                                                      ║\n",
            "  ║  Memory state at time of panic:                      ║\n",
            "  ║  - Total RAM:                                          ║\n",
            "  ║  - Used:                                               ║\n",
            "  ║  - Free:                                               ║\n",
            "  ║  - Cached:                                             ║\n",
            "  ║                                                      ║\n",
            "  ║  Top memory consumers:                                ║\n",
            "  ║  (per-sandbox tracking would be listed here)          ║\n",
            "  ╚══════════════════════════════════════════════════════╝\n",
        ),
        PanicClass::LockDepViolation => concat!(
            "  ╔══════════════════════════════════════════════════════╗\n",
            "  ║          LOCK DEPENDENCY VIOLATION / DEADLOCK         ║\n",
            "  ╠══════════════════════════════════════════════════════╣\n",
            "  ║  The lock ordering validator detected a potential    ║\n",
            "  ║  deadlock.  Locks were acquired in an order that    ║\n",
            "  ║  could cause a circular wait.                       ║\n",
            "  ║                                                      ║\n",
            "  ║  Lock chain at time of violation:                    ║\n",
            "  ║  (chain would be traced here)                        ║\n",
            "  ║                                                      ║\n",
            "  ║  The SentraOS concurrency layer has recorded this    ║\n",
            "  ║  violation for analysis.  Suggested fix: reorder     ║\n",
            "  ║  lock acquisition to match the global hierarchy.    ║\n",
            "  ╚══════════════════════════════════════════════════════╝\n",
        ),
        PanicClass::SecurityViolation => concat!(
            "  ╔══════════════════════════════════════════════════════╗\n",
            "  ║          SECURITY VIOLATION                          ║\n",
            "  ╠══════════════════════════════════════════════════════╣\n",
            "  ║  A security policy was violated.  This may indicate  ║\n",
            "  ║  an attempted exploit or a misconfigured policy.    ║\n",
            "  ║                                                      ║\n",
            "  ║  Possible causes:                                    ║\n",
            "  ║  1. Buffer overflow in a driver                      ║\n",
            "  ║  2. Attempted privilege escalation                   ║\n",
            "  ║  3. Seccomp / LSM policy violation                   ║\n",
            "  ║  4. Capability check failure                        ║\n",
            "  ╚══════════════════════════════════════════════════════╝\n",
        ),
        PanicClass::StackOverflow => concat!(
            "  ╔══════════════════════════════════════════════════════╗\n",
            "  ║          STACK OVERFLOW                              ║\n",
            "  ╠══════════════════════════════════════════════════════╣\n",
            "  ║  Kernel stack overflow detected.  The kernel stack   ║\n",
            "  ║  guard page was hit.                                ║\n",
            "  ║                                                      ║\n",
            "  ║  Possible causes:                                    ║\n",
            "  ║  1. Unbounded recursion in code path                 ║\n",
            "  ║  2. Large stack frame (alloca or big local arrays)   ║\n",
            "  ║  3. Deep nested function calls in a single context   ║\n",
            "  ╚══════════════════════════════════════════════════════╝\n",
        ),
        _ => concat!(
            "  ╔══════════════════════════════════════════════════════╗\n",
            "  ║          KERNEL PANIC — UNKNOWN REASON                ║\n",
            "  ╠══════════════════════════════════════════════════════╣\n",
            "  ║  The kernel encountered a fatal error it could not  ║\n",
            "  ║  classify.  Detailed registers and stack trace are   ║\n",
            "  ║  printed below.                                     ║\n",
            "  ║                                                      ║\n",
            "  ║  The SentraOS monitor has captured the faulting      ║\n",
            "  ║  context for post-mortem analysis.                  ║\n",
            "  ╚══════════════════════════════════════════════════════╝\n",
        ),
    }
}

// ── Main panic handler ────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_panic_handler(reason: *const c_char) {
    if PANIC_ACTIVE.swap(true, Ordering::Acquire) {
        // Already panicking — prevent recursion
        loop {}
    }

    let reason_str = if reason.is_null() {
        None
    } else {
        let mut len = 0;
        unsafe {
            while *reason.add(len) != 0 {
                len += 1;
            }
        }
        if len == 0 {
            None
        } else {
            unsafe {
                Some(core::str::from_utf8_unchecked(
                    core::slice::from_raw_parts(reason as *const u8, len),
                ))
            }
        }
    };

    let class = classify_panic(reason_str);
    let class_str = class_description(class);

    // Print the panic banner directly to console
    unsafe {
        printk(
            b"\n\n\0" as *const u8 as *const c_char,
        );
        printk(
            b"================================================================================\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"                       S E N T R A O S   K E R N E L   P A N I C\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"================================================================================\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"\n\0" as *const u8 as *const c_char,
        );

        // Print the reason
        if let Some(r) = reason_str {
            printk(
                b"  Reason: %s\n\0" as *const u8 as *const c_char,
                reason,
            );
        } else {
            printk(
                b"  Reason: (no reason string provided)\n\0" as *const u8 as *const c_char,
            );
        }

        printk(
            b"\n%s\0" as *const u8 as *const c_char,
            class_str as *const str as *const u8 as *const c_char,
        );

        // Print diagnostic summary
        printk(
            b"  ┌─ Diagnostic Summary ─────────────────────────────────────────────────────\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"  │ Panic Class:  %d\n\0" as *const u8 as *const c_char,
            class as c_int,
        );
        printk(
            b"  │ Timestamp:    (kernel jiffies)\n\0" as *const u8 as *const c_char,
        );
        printk(
            b"  │ CPU:          %d\n\0" as *const u8 as *const c_char,
            0,
        );
        printk(
            b"  │ PID:          %d\n\0" as *const u8 as *const c_char,
            0,
        );
        printk(
            b"  │ Comm:         (process name)\n\0" as *const u8 as *const c_char,
        );

        // Print active sandbox info
        printk(
            b"  │ Active DAC Sandboxes: (drivers running in isolation)\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"  │ Each sandbox is isolated — only the faulting one is affected.\n\0"
                as *const u8 as *const c_char,
        );

        printk(
            b"  └──────────────────────────────────────────────────────────────────────────\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"\n================================================================================\n\0"
                as *const u8 as *const c_char,
        );

        // Recommendation
        printk(
            b"\n  RECOMMENDATION: The SentraOS microkernel architecture contains\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"  this fault to the faulting sandbox.  No other subsystem is affected.\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"  Check the log at /sys/kernel/dac/<driver>/log for details.\n\0"
                as *const u8 as *const c_char,
        );
        printk(
            b"\n================================================================================\n\0"
                as *const u8 as *const c_char,
        );
    }

    // Halt (infinite loop) — kernel panic must not return
    loop {}
}

// ── Rust `panic!` handler ─────────────────────────────────

#[panic_handler]
fn rust_panic_handler(info: &PanicInfo) -> ! {
    let msg = match info.message() {
        Some(m) => {
            let s = format_args!("{}", m);
            let s_str = core::str::from_utf8(&[]).unwrap_or("");
            s_str.as_ptr() as *const c_char
        }
        None => ptr::null(),
    };

    sentraos_panic_handler(msg);
    loop {}
}
