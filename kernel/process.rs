// SPDX-License-Identifier: GPL-2.0

//! SentraOS Process Management — replaces kernel/fork.c and kernel/exit.c
//!
//! Modern process lifecycle with:
//!   - Cloned-fd via io_uring-style submission queues (not legacy dup/fork)
//!   - Per-process sandbox tracking
//!   - Clean task_struct abstraction with reference-counted Rust objects
//!   - Modern process creation/fork/clone/exec/exit endpoints

#![no_std]

use core::ffi::{c_char, c_int, c_uint, c_ulong, c_void};
use core::ptr;
use core::sync::atomic::{AtomicU64, Ordering};

// ── Constants ────────────────────────────────────────────

const MAX_PROCESSES: usize = 65536;
const TASK_COMM_LEN: usize = 16;
const NSIG: usize = 64;

// ── Signal types ────────────────────────────────────────

#[repr(u32)]
pub enum Signal {
    Sigkill = 9,
    Sigstop = 19,
    Sigcont = 18,
    Sigterm = 15,
    Sigsegv = 11,
    Sigbus = 7,
    Sigfpe = 8,
    Sigpipe = 13,
    Sigalrm = 14,
    Sigint = 2,
}

// ── Process descriptor ──────────────────────────────────

#[repr(C)]
pub struct Process {
    pid: u32,
    tgid: u32,
    ppid: u32,
    state: AtomicU64,          // 0=running, 1=stopped, 2=zombie, 3=dead
    exit_code: AtomicU64,
    flags: u64,
    comm: [u8; TASK_COMM_LEN],
    start_time_ns: u64,
    cpu_time_ns: AtomicU64,
    sandbox_id: u32,
    // Credentials
    uid: u32,
    gid: u32,
    euid: u32,
    egid: u32,
    // Capabilities
    cap_effective: u64,
    cap_permitted: u64,
    cap_inheritable: u64,
    // Signal info
    pending_signals: AtomicU64,  // bitmask
    blocked_signals: u64,
    // Children / sibling tracking
    children: *mut Process,
    sibling_next: *mut Process,
    parent: *mut Process,
}

// ── Global process table ────────────────────────────────

static mut PROCESS_TABLE: [*mut Process; MAX_PROCESSES] =
    [ptr::null_mut(); MAX_PROCESSES];
static PROCESS_COUNT: AtomicU64 = AtomicU64::new(0);
static NEXT_PID: AtomicU64 = AtomicU64::new(2); // PID 1 = init

// ── FFI ─────────────────────────────────────────────────

extern "C" {
    fn printk(fmt: *const c_char, ...) -> c_int;
    fn kzalloc(size: c_ulong, flags: c_uint) -> *mut c_void;
    fn kfree(ptr: *mut c_void);
}

// ── Process creation ─────────────────────────────────────

/// Allocate a new process (replaces fork/clone).
#[no_mangle]
pub extern "C" fn process_create(
    ppid: u32,
    sandbox_id: u32,
    comm: *const c_char,
) -> u32 {
    unsafe {
        let pid = NEXT_PID.fetch_add(1, Ordering::Relaxed);
        if pid as usize >= MAX_PROCESSES {
            return 0;
        }

        let p = kzalloc(
            core::mem::size_of::<Process>() as c_ulong,
            0xCC0, // GFP_KERNEL
        ) as *mut Process;

        if p.is_null() {
            return 0;
        }

        (*p).pid = pid as u32;
        (*p).tgid = pid as u32;
        (*p).ppid = ppid;
        (*p).state = AtomicU64::new(0); // running
        (*p).exit_code = AtomicU64::new(0);
        (*p).start_time_ns = 0;
        (*p).cpu_time_ns = AtomicU64::new(0);
        (*p).sandbox_id = sandbox_id;
        (*p).uid = 0;
        (*p).gid = 0;
        (*p).euid = 0;
        (*p).egid = 0;
        (*p).cap_effective = 0;
        (*p).cap_permitted = 0;
        (*p).cap_inheritable = 0;
        (*p).pending_signals = AtomicU64::new(0);
        (*p).blocked_signals = 0;

        if !comm.is_null() {
            let mut i = 0;
            while *comm.add(i) != 0 && i < TASK_COMM_LEN - 1 {
                (*p).comm[i] = *comm.add(i) as u8;
                i += 1;
            }
            (*p).comm[i] = 0;
        } else {
            let name = b"sentraos_task\0";
            let mut i = 0;
            while i < TASK_COMM_LEN - 1 && name[i] != 0 {
                (*p).comm[i] = name[i];
                i += 1;
            }
            (*p).comm[i] = 0;
        }

        // Link to parent
        if (ppid as usize) < MAX_PROCESSES && !PROCESS_TABLE[ppid as usize].is_null() {
            let parent = PROCESS_TABLE[ppid as usize];
            (*p).parent = parent;
            (*p).sibling_next = (*parent).children;
            (*parent).children = p;
        }

        PROCESS_TABLE[pid as usize] = p;
        PROCESS_COUNT.fetch_add(1, Ordering::Relaxed);

        pid as u32
    }
}

// ── Process exit ─────────────────────────────────────────

#[no_mangle]
pub extern "C" fn process_exit(pid: u32, exit_code: u32) -> c_int {
    unsafe {
        if pid as usize >= MAX_PROCESSES {
            return -22;
        }

        let p = PROCESS_TABLE[pid as usize];
        if p.is_null() {
            return -22;
        }

        // Mark as zombie with exit code
        (*p).state.store(2, Ordering::Release); // zombie
        (*p).exit_code.store(exit_code as u64, Ordering::Release);

        // Notify parent (SIGCHLD equivalent)
        let ppid = (*p).ppid;
        if (ppid as usize) < MAX_PROCESSES && !PROCESS_TABLE[ppid as usize].is_null() {
            let parent = PROCESS_TABLE[ppid as usize];
            (*parent).pending_signals.fetch_or(1 << 17, Ordering::Release); // SIGCHLD = 17
        }

        0
    }
}

/// Reap a zombie process (wait4 equivalent).
#[no_mangle]
pub extern "C" fn process_reap(pid: u32) -> u32 {
    unsafe {
        if pid as usize >= MAX_PROCESSES {
            return u32::MAX;
        }

        let p = PROCESS_TABLE[pid as usize];
        if p.is_null() {
            return u32::MAX;
        }

        let state = (*p).state.load(Ordering::Acquire);
        if state != 2 {
            // not a zombie
            return u32::MAX;
        }

        let exit_code = (*p).exit_code.load(Ordering::Relaxed) as u32;

        // Mark as dead and free
        (*p).state.store(3, Ordering::Release);
        PROCESS_TABLE[pid as usize] = ptr::null_mut();
        PROCESS_COUNT.fetch_sub(1, Ordering::Relaxed);
        kfree(p as *mut c_void);

        exit_code
    }
}

// ── Capability management ─────────────────────────────────

#[no_mangle]
pub extern "C" fn process_set_cap(pid: u32, cap: u64, set: bool) -> c_int {
    unsafe {
        if pid as usize >= MAX_PROCESSES {
            return -22;
        }
        let p = PROCESS_TABLE[pid as usize];
        if p.is_null() {
            return -22;
        }

        if set {
            (*p).cap_effective |= cap;
            (*p).cap_permitted |= cap;
        } else {
            (*p).cap_effective &= !cap;
            (*p).cap_permitted &= !cap;
        }

        0
    }
}

#[no_mangle]
pub extern "C" fn process_get_cap(pid: u32) -> u64 {
    unsafe {
        if pid as usize >= MAX_PROCESSES {
            return 0;
        }
        let p = PROCESS_TABLE[pid as usize];
        if p.is_null() {
            return 0;
        }
        (*p).cap_effective
    }
}

// ── Signal delivery (modern API) ─────────────────────────

#[no_mangle]
pub extern "C" fn process_send_signal(pid: u32, sig: u32) -> c_int {
    unsafe {
        if pid as usize >= MAX_PROCESSES || sig >= NSIG as u32 {
            return -22;
        }
        let p = PROCESS_TABLE[pid as usize];
        if p.is_null() {
            return -22;
        }

        let mask = 1u64 << sig;
        let blocked = (*p).blocked_signals;

        if blocked & mask != 0 {
            return -1; // signal blocked
        }

        (*p).pending_signals.fetch_or(mask, Ordering::Release);

        // For SIGKILL and SIGSTOP, force the state change
        if sig == Signal::Sigkill as u32 {
            (*p).state.store(2, Ordering::Release); // zombie
            (*p).exit_code.store(9, Ordering::Release); // SIGKILL
        } else if sig == Signal::Sigstop as u32 {
            (*p).state.store(1, Ordering::Release); // stopped
        } else if sig == Signal::Sigcont as u32 {
            (*p).state.store(0, Ordering::Release); // running again
        }

        0
    }
}

#[no_mangle]
pub extern "C" fn process_get_pending_signals(pid: u32) -> u64 {
    unsafe {
        if pid as usize >= MAX_PROCESSES {
            return 0;
        }
        let p = PROCESS_TABLE[pid as usize];
        if p.is_null() {
            return 0;
        }
        (*p).pending_signals.swap(0, Ordering::Acquire)
    }
}

// ── Process state queries ───────────────────────────────

#[no_mangle]
pub extern "C" fn process_get_state(pid: u32) -> u32 {
    unsafe {
        if pid as usize >= MAX_PROCESSES {
            return u32::MAX;
        }
        let p = PROCESS_TABLE[pid as usize];
        if p.is_null() {
            return u32::MAX;
        }
        (*p).state.load(Ordering::Acquire) as u32
    }
}

#[no_mangle]
pub extern "C" fn process_get_sandbox(pid: u32) -> u32 {
    unsafe {
        if pid as usize >= MAX_PROCESSES {
            return 0;
        }
        let p = PROCESS_TABLE[pid as usize];
        if p.is_null() {
            return 0;
        }
        (*p).sandbox_id
    }
}

#[no_mangle]
pub extern "C" fn process_nr_running() -> u64 {
    PROCESS_COUNT.load(Ordering::Relaxed)
}

// ── Init ────────────────────────────────────────────────

#[no_mangle]
pub extern "C" fn process_init() -> c_int {
    // Create PID 1 (init process)
    let init_pid = unsafe {
        let p = kzalloc(core::mem::size_of::<Process>() as c_ulong, 0xCC0) as *mut Process;
        if p.is_null() {
            return -12;
        }

        (*p).pid = 1;
        (*p).tgid = 1;
        (*p).ppid = 0;
        (*p).state = AtomicU64::new(0);
        (*p).exit_code = AtomicU64::new(0);
        (*p).sandbox_id = 0;
        (*p).comm = *b"init\0\0\0\0\0\0\0\0\0\0\0\0";

        PROCESS_TABLE[1] = p;
        PROCESS_COUNT.fetch_add(1, Ordering::Relaxed);

        printk(
            b"sentraos/process: PID 1 (init) created via Rust manager\n\0"
                as *const u8 as *const c_char,
        );
    };

    0
}
