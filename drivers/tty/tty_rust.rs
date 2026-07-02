// SPDX-License-Identifier: GPL-2.0

//! SentraOS TTY/CONSOLE — modern Rust replacement for drivers/tty/
//!
//! Architecture:
//!   ┌──────────────────────────────────────────────────┐
//!   │  Userspace Terminal Daemon (termd)               │
//!   │  ┌──────────┐ ┌──────────┐ ┌────────────┐      │
//!   │  │ Line     │ │ Terminal │ │ PTY        │      │
//!   │  │ Disc.    │ │ Emulation│ │ Manager    │      │
//!   │  └────┬─────┘ └────┬─────┘ └─────┬──────┘      │
//!   │       │            │             │              │
//!   └───────┼────────────┼─────────────┼──────────────┘
//!           │            │             │  sentraos_bridge
//!   ┌───────┼────────────┼─────────────┼──────────────┐
//!   │  Ring 0: Minimal TTY Core                         │
//!   │  ┌──────────────────────────────────────────┐    │
//!   │  │ tty_open / tty_close / tty_read /        │    │
//!   │  │ tty_write — thin transport layer          │    │
//!   │  │ No line discipline. No canonical mode.   │    │
//!   │  │ Raw byte pipe to userspace daemon.       │    │
//!   │  └──────────────────────────────────────────┘    │
//!   │  ┌──────────────────────────────────────────┐    │
//!   │  │ Console: framebuffer print (emergency    │    │
//!   │  │ output when daemon is unavailable)       │    │
//!   │  └──────────────────────────────────────────┘    │
//!   └──────────────────────────────────────────────────┘

#![no_std]

use core::ffi::{c_char, c_int, c_uint, c_ulong, c_void};
use core::ptr;
use core::sync::atomic::{AtomicU64, Ordering};

// ── Constants ────────────────────────────────────────────

const MAX_TTYS: usize = 256;
const TTY_NAME_LEN: usize = 32;
const TTY_BUF_SIZE: usize = 4096;

// GFP flags: copied from bindings to avoid dependency on kernel crate
const GFP_KERNEL: c_uint = 0xCC0;
const GFP_ATOMIC: c_uint = 0xC20;

// ── TTY flags ──────────────────────────────────────────

const TTY_OPEN: u32 = 1 << 0;
const TTY_CLOSING: u32 = 1 << 1;
const TTY_RAW: u32 = 1 << 2;     // no line discipline processing
const TTY_CONSOLE: u32 = 1 << 3;
const TTY_PTY: u32 = 1 << 4;

// ── TTY instance ──────────────────────────────────────

#[repr(C)]
struct SentraosTty {
    index: u32,
    name: [u8; TTY_NAME_LEN],
    flags: AtomicU64,
    pid_open: AtomicU64,             // PID that has this TTY open
    sandbox_id: u32,
    // Ring buffer for raw I/O (simplified)
    buf: [u8; TTY_BUF_SIZE],
    buf_head: AtomicU64,
    buf_tail: AtomicU64,
    // Callbacks to userspace daemon
    daemon_connected: u32,
    // Console emergency output
    is_console: u32,
}

// ── Global TTY table ──────────────────────────────────

// Protected by tty_table_lock (spinlock) — all read/write to the table
// must hold the lock in IRQ-safe mode.
static mut TTY_TABLE: [*mut SentraosTty; MAX_TTYS] = [ptr::null_mut(); MAX_TTYS];
static TTY_COUNT: AtomicU64 = AtomicU64::new(0);
static NEXT_TTY_INDEX: AtomicU64 = AtomicU64::new(0);
static CONSOLE_TTY: AtomicU64 = AtomicU64::new(0); // index of console tty

/// Opaque spinlock structure matching Linux's spinlock_t.
#[repr(C)]
struct SpinLock {
    _data: [u64; 1], // spinlock_t is architecture-dependent; use opaque lock
}

extern "C" {
    fn printk(fmt: *const c_char, ...) -> c_int;
    fn kzalloc(size: c_ulong, flags: c_uint) -> *mut c_void;
    fn kfree(ptr: *mut c_void);
    fn __raw_spin_lock_init(lock: *mut SpinLock, name: *const c_char, key: *mut c_void);
    fn spin_lock_irqsave(lock: *mut SpinLock) -> c_ulong;
    fn spin_unlock_irqrestore(lock: *mut SpinLock, flags: c_ulong);
}

static mut TTY_TABLE_LOCK: SpinLock = SpinLock { _data: [0] };

// ── Lock helpers ───────────────────────────────────────

struct TtyTableGuard {
    lock: *mut SpinLock,
    flags: c_ulong,
}

impl TtyTableGuard {
    fn lock() -> Self {
        unsafe {
            let flags = spin_lock_irqsave(&mut TTY_TABLE_LOCK);
            TtyTableGuard { lock: &mut TTY_TABLE_LOCK, flags }
        }
    }
}

impl Drop for TtyTableGuard {
    fn drop(&mut self) {
        unsafe { spin_unlock_irqrestore(self.lock, self.flags) };
    }
}

// ── TTY lifecycle ─────────────────────────────────────

/// Allocate a new TTY. Returns index or 0 on failure.
#[no_mangle]
pub extern "C" fn sentraos_tty_alloc(
    name: *const c_char,
    is_console: u32,
    sandbox_id: u32,
) -> u32 {
    let idx = NEXT_TTY_INDEX.fetch_add(1, Ordering::Relaxed);
    if idx as usize >= MAX_TTYS {
        return 0;
    }

    unsafe {
        let tty = kzalloc(
            core::mem::size_of::<SentraosTty>() as c_ulong,
            GFP_KERNEL,
        ) as *mut SentraosTty;

        if tty.is_null() {
            return 0;
        }

        (*tty).index = idx as u32;
        (*tty).flags = AtomicU64::new(TTY_RAW as u64);
        (*tty).pid_open = AtomicU64::new(0);
        (*tty).sandbox_id = sandbox_id;
        (*tty).buf_head = AtomicU64::new(0);
        (*tty).buf_tail = AtomicU64::new(0);
        (*tty).daemon_connected = 0;
        (*tty).is_console = is_console;

        if !name.is_null() {
            let mut i = 0;
            while *name.add(i) != 0 && i < TTY_NAME_LEN - 1 {
                (*tty).name[i] = *name.add(i) as u8;
                i += 1;
            }
            (*tty).name[i] = 0;
        }

        let _guard = TtyTableGuard::lock();
        TTY_TABLE[idx as usize] = tty;
    }
    TTY_COUNT.fetch_add(1, Ordering::Relaxed);

    if is_console != 0 {
        CONSOLE_TTY.store(idx, Ordering::Relaxed);
    }

    idx as u32
}

#[no_mangle]
pub extern "C" fn sentraos_tty_free(index: u32) {
    if index as usize >= MAX_TTYS {
        return;
    }
    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        let tty = TTY_TABLE[index as usize];
        TTY_TABLE[index as usize] = ptr::null_mut();
        tty
    };
    if !tty.is_null() {
        TTY_COUNT.fetch_sub(1, Ordering::Relaxed);
        unsafe { kfree(tty as *mut c_void) };
    }
}

// ── TTY open/close ────────────────────────────────────

/// Open a TTY (called from /dev/ttyX file_operations).
#[no_mangle]
pub extern "C" fn sentraos_tty_open(
    index: u32,
    pid: u32,
) -> c_int {
    if index as usize >= MAX_TTYS {
        return -22; // -EINVAL
    }

    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        TTY_TABLE[index as usize]
    };

    if tty.is_null() {
        return -22;
    }

    // Mark open
    let flags = unsafe { (*tty).flags.fetch_or(TTY_OPEN as u64, Ordering::Acquire) };
    if flags & TTY_OPEN as u64 != 0 {
        return -16; // -EBUSY
    }

    unsafe { (*tty).pid_open.store(pid as u64, Ordering::Release) };

    // Notify userspace daemon
    sentraos_tty_notify_daemon(index, 1); // 1 = opened

    0
}

#[no_mangle]
pub extern "C" fn sentraos_tty_close(index: u32) {
    if index as usize >= MAX_TTYS {
        return;
    }

    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        TTY_TABLE[index as usize]
    };

    if tty.is_null() {
        return;
    }

    unsafe {
        (*tty).flags.fetch_and(!(TTY_OPEN as u64), Ordering::Release);
        (*tty).pid_open.store(0, Ordering::Release);
    }

    sentraos_tty_notify_daemon(index, 2); // 2 = closed
}

// ── TTY I/O ──────────────────────────────────────────────

/// Write to a TTY.
#[no_mangle]
pub extern "C" fn sentraos_tty_write(
    index: u32,
    data: *const u8,
    len: u32,
) -> u32 {
    if index as usize >= MAX_TTYS || data.is_null() || len == 0 {
        return 0;
    }

    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        TTY_TABLE[index as usize]
    };

    if tty.is_null() {
        return 0;
    }

    let head = unsafe { (*tty).buf_head.load(Ordering::Relaxed) as usize };
    let tail = unsafe { (*tty).buf_tail.load(Ordering::Relaxed) as usize };

    let mut written = 0u32;
    for i in 0..(len as usize) {
        let next_head = (head + written as usize + 1) % TTY_BUF_SIZE;
        if next_head == tail {
            break; // buffer full
        }
        let idx = (head + written as usize) % TTY_BUF_SIZE;
        unsafe { (*tty).buf[idx] = *data.add(i) };
        written += 1;
    }

    if written > 0 {
        unsafe {
            (*tty).buf_head.store(
                ((head + written as usize) % TTY_BUF_SIZE) as u64,
                Ordering::Release,
            );
        }
    }

    // If we're the console and daemon isn't running, print directly
    if unsafe { (*tty).is_console != 0 && (*tty).daemon_connected == 0 } {
        let fmt = b"%s\0" as *const u8 as *const c_char;
        unsafe { printk(fmt, data) };
    }

    written
}

/// Read from a TTY.
#[no_mangle]
pub extern "C" fn sentraos_tty_read(
    index: u32,
    buf: *mut u8,
    len: u32,
) -> u32 {
    if index as usize >= MAX_TTYS || buf.is_null() || len == 0 {
        return 0;
    }

    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        TTY_TABLE[index as usize]
    };

    if tty.is_null() {
        return 0;
    }

    let head = unsafe { (*tty).buf_head.load(Ordering::Acquire) as usize };
    let tail = unsafe { (*tty).buf_tail.load(Ordering::Relaxed) as usize };

    if tail == head {
        return 0; // nothing available
    }

    let mut read_count = 0u32;
    while tail != head && read_count < len {
        unsafe { *buf.add(read_count as usize) = (*tty).buf[tail] };
        let new_tail = (tail + 1) % TTY_BUF_SIZE;
        read_count += 1;
    }
    if read_count > 0 {
        let new_tail = (tail + read_count as usize) % TTY_BUF_SIZE;
        unsafe { (*tty).buf_tail.store(new_tail as u64, Ordering::Release) };
    }

    read_count
}

// ── Console emergency output ────────────────────────────

/// Write a string to the console TTY directly (emergency path,
/// used during early boot and panic).
#[no_mangle]
pub extern "C" fn sentraos_console_write(msg: *const c_char) -> c_int {
    if msg.is_null() {
        return 0;
    }

    let console_idx = CONSOLE_TTY.load(Ordering::Relaxed) as usize;
    if console_idx >= MAX_TTYS {
        return -22;
    }

    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        TTY_TABLE[console_idx]
    };
    if tty.is_null() {
        return -22;
    }

    // Measure string length
    let mut len = 0;
    unsafe {
        while *msg.add(len) != 0 {
            len += 1;
        }
    }
    if len == 0 {
        return 0;
    }

    // Write to buffer
    let head = unsafe { (*tty).buf_head.load(Ordering::Relaxed) as usize };
    let mut written: usize = 0;
    for i in 0..len {
        let next_head = (head + written + 1) % TTY_BUF_SIZE;
        let tail = unsafe { (*tty).buf_tail.load(Ordering::Relaxed) as usize };
        if next_head == tail {
            break;
        }
        let idx = (head + written) % TTY_BUF_SIZE;
        unsafe { (*tty).buf[idx] = *msg.add(i) };
        written += 1;
    }
    if written > 0 {
        let new_head = (head + written) % TTY_BUF_SIZE;
        unsafe { (*tty).buf_head.store(new_head as u64, Ordering::Release) };
    }

    // Write to framebuffer/console directly for visibility
    unsafe {
        printk(
            b"[console] %s\n\0" as *const u8 as *const c_char,
            msg,
        );
    }

    len as c_int
}

// ── Daemon communication ───────────────────────────────

fn sentraos_tty_notify_daemon(_tty_index: u32, _event: u32) {
    // In real implementation: write event to /dev/sentraos_bridge
    // for the userspace terminal daemon to process.
    //
    // Events:
    //   1 = TTY opened (daemon should attach line discipline)
    //   2 = TTY closed (daemon should detach)
    //   3 = Data available for reading
    //   4 = PTY master activity
}

#[no_mangle]
pub extern "C" fn sentraos_tty_daemon_connected(index: u32) -> c_int {
    if index as usize >= MAX_TTYS {
        return -22;
    }
    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        TTY_TABLE[index as usize]
    };
    if tty.is_null() {
        return -22;
    }
    unsafe { (*tty).daemon_connected = 1 };
    0
}

#[no_mangle]
pub extern "C" fn sentraos_tty_daemon_disconnected(index: u32) -> c_int {
    if index as usize >= MAX_TTYS {
        return -22;
    }
    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        TTY_TABLE[index as usize]
    };
    if tty.is_null() {
        return -22;
    }
    unsafe { (*tty).daemon_connected = 0 };
    0
}

// ── Statistics ──────────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_tty_count() -> u32 {
    TTY_COUNT.load(Ordering::Relaxed) as u32
}

#[no_mangle]
pub extern "C" fn sentraos_tty_open_count(index: u32) -> u32 {
    if index as usize >= MAX_TTYS {
        return 0;
    }
    let tty = unsafe {
        let _guard = TtyTableGuard::lock();
        TTY_TABLE[index as usize]
    };
    if tty.is_null() {
        return 0;
    }
    if unsafe { (*tty).flags.load(Ordering::Relaxed) & TTY_OPEN as u64 != 0 } {
        1
    } else {
        0
    }
}

// ── Init ────────────────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_tty_init() -> c_int {
    // Initialize the TTY table spinlock
    unsafe {
        __raw_spin_lock_init(
            &mut TTY_TABLE_LOCK,
            b"tty_table_lock\0" as *const u8 as *const c_char,
            ptr::null_mut(),
        );
    }

    // Allocate console TTY (index 0)
    let idx = sentraos_tty_alloc(
        b"console\0" as *const u8 as *const c_char,
        1,  // is_console
        0,  // sandbox_id (core)
    );

    unsafe {
        printk(
            b"\n\
            SentraOS TTY: console at index %u\n\0"
                as *const u8 as *const c_char,
            idx,
        );
    }

    0
}
