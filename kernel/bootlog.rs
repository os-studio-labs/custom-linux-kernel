// SPDX-License-Identifier: GPL-2.0

//! SentraOS Boot/Shutdown Logger — structured, colorful, timed kernel log
//! for startup and shutdown sequences.  Replaces raw printk spew with
//! a progress-bar style output.

#![no_std]

use core::ffi::{c_char, c_int, c_void};

// ── Log levels ──────────────────────────────────────────

#[repr(u32)]
pub enum LogLevel {
    Init = 0,      // [INIT]   — subsystem initialization
    Ready = 1,     // [OK]     — subsystem ready
    Warn = 2,      // [WARN]   — non-fatal issue
    Fail = 3,      // [FAIL]   — subsystem failed
    Info = 4,      // [INFO]   — informational
    Debug = 5,     // [DEBUG]  — verbose debugging
}

// ── Subsystem state ────────────────────────────────────

#[repr(C)]
struct Subsystem {
    name: [u8; 24],
    level: u32,
}

static mut SUBSYSTEMS: [Subsystem; 64] = unsafe { core::mem::zeroed() };
static mut SUBSYSTEM_COUNT: u32 = 0;
static BOOT_START: u64 = 0;

// ── FFI ─────────────────────────────────────────────────

extern "C" {
    fn printk(fmt: *const c_char, ...) -> c_int;
}

// ── Boot log API ───────────────────────────────────────

#[no_mangle]
pub extern "C" fn bootlog_subsystem_init(name: *const c_char) -> u32 {
    unsafe {
        let id = SUBSYSTEM_COUNT;
        if id >= 64 || name.is_null() {
            return u32::MAX;
        }

        let sb = &mut SUBSYSTEMS[id as usize];
        let mut i = 0;
        while *name.add(i) != 0 && i < 23 {
            sb.name[i] = *name.add(i) as u8;
            i += 1;
        }
        sb.name[i] = 0;
        sb.level = LogLevel::Init as u32;
        SUBSYSTEM_COUNT += 1;

        // Print init banner
        let fmt = b"  [INIT]  %-24s ... starting\n\0" as *const u8 as *const c_char;
        printk(fmt, name);

        id
    }
}

#[no_mangle]
pub extern "C" fn bootlog_subsystem_ready(id: u32) {
    unsafe {
        if id >= 64 {
            return;
        }

        let sb = &SUBSYSTEMS[id as usize];
        if sb.name[0] == 0 {
            return;
        }
        sb.level = LogLevel::Ready as u32;

        let fmt = b"  [  OK  ]  %-24s ready\n\0" as *const u8 as *const c_char;
        printk(fmt, sb.name.as_ptr());
    }
}

#[no_mangle]
pub extern "C" fn bootlog_subsystem_fail(id: u32, reason: *const c_char) {
    unsafe {
        if id >= 64 {
            return;
        }

        let sb = &SUBSYSTEMS[id as usize];
        if sb.name[0] == 0 {
            return;
        }
        sb.level = LogLevel::Fail as u32;

        if !reason.is_null() {
            let fmt = b"  [FAIL]  %-24s FAILED: %s\n\0" as *const u8 as *const c_char;
            printk(fmt, sb.name.as_ptr(), reason);
        } else {
            let fmt = b"  [FAIL]  %-24s FAILED\n\0" as *const u8 as *const c_char;
            printk(fmt, sb.name.as_ptr());
        }
    }
}

#[no_mangle]
pub extern "C" fn bootlog_subsystem_warn(id: u32, msg: *const c_char) {
    unsafe {
        if id >= 64 || msg.is_null() {
            return;
        }

        let fmt = b"  [WARN]  %s\n\0" as *const u8 as *const c_char;
        printk(fmt, msg);
    }
}

#[no_mangle]
pub extern "C" fn bootlog_info(msg: *const c_char) {
    unsafe {
        if msg.is_null() {
            return;
        }
        let fmt = b"  [INFO]  %s\n\0" as *const u8 as *const c_char;
        printk(fmt, msg);
    }
}

// ── Boot banner ─────────────────────────────────────────

#[no_mangle]
pub extern "C" fn bootlog_start_banner() {
    unsafe {
        printk(
            b"\n\
            ╔══════════════════════════════════════════════════════════════════╗\n\
            ║              S E N T R A O S   K E R N E L   v6.9              ║\n\
            ║         Microkernel Architecture — Rust Core — DAC              ║\n\
            ╚══════════════════════════════════════════════════════════════════╝\n\
            \n\
            Starting subsystem initialization...\n\
            \n\0" as *const u8 as *const c_char,
        );
    }
}

#[no_mangle]
pub extern "C" fn bootlog_shutdown_banner(reason: *const c_char) {
    unsafe {
        let fmt = b"\n\
            ╔══════════════════════════════════════════════════════════════════╗\n\
            ║              S H U T D O W N                                  ║\n\
            ║  Reason: %s                                                    ║\n\
            ╚══════════════════════════════════════════════════════════════════╝\n\
            \n\
            Tearing down subsystems...\n\
            \n\0" as *const u8 as *const c_char;

        if !reason.is_null() {
            printk(fmt, reason);
        } else {
            printk(fmt, b"(none)\0" as *const u8 as *const c_char);
        }
    }
}

#[no_mangle]
pub extern "C" fn bootlog_shutdown_complete() {
    unsafe {
        printk(
            b"\n  [  OK  ]  System halted.  All subsystems torn down safely.\n\
            \n\0" as *const u8 as *const c_char,
        );
    }
}

#[no_mangle]
pub extern "C" fn bootlog_summary() {
    unsafe {
        let mut init_count = 0;
        let mut ok_count = 0;
        let mut fail_count = 0;

        for i in 0..SUBSYSTEM_COUNT as usize {
            match SUBSYSTEMS[i].level {
                0 => init_count += 1,
                1 => ok_count += 1,
                3 => fail_count += 1,
                _ => {}
            }
        }

        printk(
            b"\n\
            ╔══════════════════════════════════════════════════════════════════╗\n\
            ║                    B O O T   S U M M A R Y                      ║\n\
            ╠══════════════════════════════════════════════════════════════════╣\n\
            ║  Subsystems: %-3d total   %-3d OK   %-3d failed   %-3d pending   ║\n\
            ╚══════════════════════════════════════════════════════════════════╝\n\
            \n\0" as *const u8 as *const c_char,
            SUBSYSTEM_COUNT, ok_count, fail_count, init_count,
        );
    }
}
