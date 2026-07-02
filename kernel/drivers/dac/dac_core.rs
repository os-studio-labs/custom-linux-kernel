// SPDX-License-Identifier: GPL-2.0

//! Driver API Centre core — Rust validation engine, driver context,
//! key registry, and logging.  Compiled as part of the kernel image.

#![no_std]

use core::ffi::{c_char, c_int, c_uint, c_ulong, c_void};
use core::ptr;
use core::sync::atomic::{AtomicU64, Ordering};

// ── Constants ────────────────────────────────────────────

const KEY_NONE: u64 = 0;
const KEY_MAGIC: u64 = 0xDAACA5E_0000_0000;
const MAX_DRIVERS: usize = 4096;
const LOG_RING_SIZE: usize = 512;
const LOG_LINE_MAX: usize = 240;

// ── API Key types ────────────────────────────────────────

#[repr(u32)]
enum ApiAccess {
    Public = 0,
    Restricted = 1,
    KernelOnly = 2,
}

#[repr(C)]
struct ApiKeyEntry {
    key: u64,
    name: [u8; 64],
    module_name: [u8; 32],
    access: u32,
    rate_limit_ms: u32,
    deprecated: u32,
    next: *mut ApiKeyEntry,
}

// ── Driver sandbox context ────────────────────────────────

#[repr(i32)]
enum SandboxState {
    Unregistered = 0,
    Active = 1,
    Faulted = 2,
    Recovering = 3,
    Dead = 4,
}

#[repr(C)]
struct LogEntry {
    timestamp: u64,
    severity: u32,
    msg: [u8; LOG_LINE_MAX],
}

#[repr(C)]
struct DriverContext {
    driver_id: u32,
    name: [u8; 48],
    state: AtomicU64,
    heartbeat_jiffies: AtomicU64,
    timeout_jiffies: u64,
    log_tail: AtomicU64,
    log_head: AtomicU64,
    log_buf: *mut LogEntry,
    allowed_keys: *mut ApiKeyEntry,
}

// ── Global driver array (lockless index lookup) ────────────

static mut DRIVER_CTX: [*mut DriverContext; MAX_DRIVERS] = [ptr::null_mut(); MAX_DRIVERS];
static DRIVER_COUNT: AtomicU64 = AtomicU64::new(0);

// ── API key list ─────────────────────────────────────────

static API_KEY_HEAD: AtomicU64 = AtomicU64::new(0);

// ── Kernel FFI (minimal; bindgen provides these in kernel crate) ──

extern "C" {
    fn kzalloc(size: c_ulong, flags: c_uint) -> *mut c_void;
    fn kfree(ptr: *mut c_void);
    fn printk(fmt: *const c_char, ...) -> c_int;
}

// ── Hash helpers ─────────────────────────────────────────

fn hash_key(name: &[u8]) -> u64 {
    let mut h = KEY_MAGIC;
    for &b in name {
        h = h.wrapping_mul(0x100000001b3).wrapping_add(b as u64);
    }
    h
}

fn cstr_to_bytes<'a>(ptr: *const c_char) -> &'a [u8] {
    if ptr.is_null() {
        return &[];
    }
    let mut len = 0;
    unsafe {
        while *ptr.add(len) != 0 {
            len += 1;
        }
        core::slice::from_raw_parts(ptr as *const u8, len)
    }
}

// ── API Key Registration ─────────────────────────────────

#[no_mangle]
pub extern "C" fn dac_register_api_key(
    name: *const c_char,
    module: *const c_char,
    access: u32,
    rate_limit_ms: u32,
) -> u64 {
    if name.is_null() {
        return KEY_NONE;
    }

    let name_bytes = cstr_to_bytes(name);
    let key = hash_key(name_bytes);

    let entry = unsafe {
        kzalloc(
            core::mem::size_of::<ApiKeyEntry>() as c_ulong,
            0xCC0, // GFP_KERNEL
        ) as *mut ApiKeyEntry
    };

    if entry.is_null() {
        return KEY_NONE;
    }

    unsafe {
        (*entry).key = key;
        let nlen = name_bytes.len().min(63);
        ptr::copy_nonoverlapping(name_bytes.as_ptr(), (*entry).name.as_mut_ptr(), nlen);
        (*entry).name[nlen] = 0;

        if !module.is_null() {
            let mbytes = cstr_to_bytes(module);
            let mlen = mbytes.len().min(31);
            ptr::copy_nonoverlapping(mbytes.as_ptr(), (*entry).module_name.as_mut_ptr(), mlen);
            (*entry).module_name[mlen] = 0;
        }

        (*entry).access = access;
        (*entry).rate_limit_ms = rate_limit_ms;
    }

    // Push to head of linked list (lockless CAS)
    loop {
        let cur = API_KEY_HEAD.load(Ordering::Acquire) as *mut ApiKeyEntry;
        unsafe { (*entry).next = cur; }
        if API_KEY_HEAD.compare_exchange_weak(
            cur as u64,
            entry as u64,
            Ordering::Release,
            Ordering::Relaxed,
        ).is_ok() {
            break;
        }
    }

    key
}

// ── Call Validation ──────────────────────────────────────

#[no_mangle]
pub extern "C" fn dac_validate_call(
    key: u64,
    driver_id: u32,
    _caller: *mut c_void,
) -> c_int {
    if key == KEY_NONE {
        return -22; // -EINVAL
    }

    let ctx = find_driver(driver_id);
    if ctx.is_null() {
        return -22;
    }

    let packed = unsafe { (*ctx).state.load(Ordering::Acquire) };
    let state = (packed & 0xFFFF_FFFF) as i32;
    match state {
        s if s == SandboxState::Dead as i32 => return -5,    // -EIO
        s if s == SandboxState::Faulted as i32 => return -16, // -EBUSY
        _ => {}
    }

    // Key must exist in registry
    if find_key(key).is_null() {
        return -38; // -ENOSYS
    }

    0
}

// ── Driver Registration ──────────────────────────────────

#[no_mangle]
pub extern "C" fn dac_register_driver(
    name: *const c_char,
    timeout_ms: c_ulong,
) -> u32 {
    let ctx = unsafe {
        kzalloc(
            core::mem::size_of::<DriverContext>() as c_ulong,
            0xCC0,
        ) as *mut DriverContext
    };

    if ctx.is_null() {
        return 0;
    }

    let name_bytes = if name.is_null() {
        b"unknown\0" as &[u8]
    } else {
        cstr_to_bytes(name)
    };

    unsafe {
        let nlen = name_bytes.len().min(47);
        ptr::copy_nonoverlapping(name_bytes.as_ptr(), (*ctx).name.as_mut_ptr(), nlen);
        (*ctx).name[nlen] = 0;

        (*ctx).state = AtomicU64::new(SandboxState::Active as u64);
        (*ctx).heartbeat_jiffies = AtomicU64::new(0);
        (*ctx).timeout_jiffies = if timeout_ms > 0 { timeout_ms as u64 } else { 5000 };

        let log_sz = (core::mem::size_of::<LogEntry>() * LOG_RING_SIZE) as c_ulong;
        (*ctx).log_buf = kzalloc(log_sz, 0xCC0) as *mut LogEntry;
    }

    if unsafe { (*ctx).log_buf.is_null() } {
        unsafe { kfree(ctx as *mut c_void) };
        return 0;
    }

    // Assign ID
    let id = DRIVER_COUNT.fetch_add(1, Ordering::Relaxed) as u32 + 1;
    if id as usize >= MAX_DRIVERS {
        unsafe { kfree(ctx as *mut c_void) };
        return 0;
    }

    unsafe {
        (*ctx).driver_id = id;
        DRIVER_CTX[id as usize] = ctx;
    }

    id
}

#[no_mangle]
pub extern "C" fn dac_deregister_driver(driver_id: u32) {
    if driver_id == 0 || driver_id as usize >= MAX_DRIVERS {
        return;
    }
    unsafe {
        let ctx = DRIVER_CTX[driver_id as usize];
        if !ctx.is_null() {
            (*ctx).state.store(SandboxState::Dead as u64, Ordering::Release);
        }
    }
}

#[no_mangle]
pub extern "C" fn dac_driver_heartbeat(driver_id: u32) {
    let ctx = find_driver(driver_id);
    if !ctx.is_null() {
        unsafe {
            (*ctx).heartbeat_jiffies.store(1, Ordering::Release);
        }
    }
}

#[no_mangle]
pub extern "C" fn dac_driver_faulted(driver_id: u32) {
    let ctx = find_driver(driver_id);
    if !ctx.is_null() {
        unsafe {
            let v = (*ctx).state.load(Ordering::Acquire);
            let crashes = (v >> 32) + 1;
            (*ctx).state
                .store((SandboxState::Faulted as u64) | (crashes << 32), Ordering::Release);
        }
    }
}

// ── State accessors (for sysfs) ──────────────────────────

#[no_mangle]
pub extern "C" fn dac_driver_state_read(driver_id: u32) -> c_int {
    let ctx = find_driver(driver_id);
    if ctx.is_null() {
        return -1;
    }
    unsafe {
        let packed = (*ctx).state.load(Ordering::Acquire);
        (packed & 0xFFFF_FFFF) as c_int
    }
}

#[no_mangle]
pub extern "C" fn dac_driver_crash_count(driver_id: u32) -> u32 {
    let ctx = find_driver(driver_id);
    if ctx.is_null() {
        return 0;
    }
    unsafe {
        let packed = (*ctx).state.load(Ordering::Acquire);
        (packed >> 32) as u32
    }
}

// ── Internal lookup ──────────────────────────────────────

fn find_key(key: u64) -> *mut ApiKeyEntry {
    let head = API_KEY_HEAD.load(Ordering::Acquire) as *mut ApiKeyEntry;
    let mut cur = head;
    while !cur.is_null() {
        unsafe {
            if (*cur).key == key {
                return cur;
            }
            cur = (*cur).next;
        }
    }
    ptr::null_mut()
}

fn find_driver(driver_id: u32) -> *mut DriverContext {
    if driver_id == 0 || driver_id as usize >= MAX_DRIVERS {
        return ptr::null_mut();
    }
    unsafe { DRIVER_CTX[driver_id as usize] }
}
