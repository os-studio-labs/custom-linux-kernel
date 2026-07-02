// SPDX-License-Identifier: GPL-2.0

//! SentraOS Object Manager — NT-style unified object management.
#![no_std]

use core::ffi::{c_char, c_int, c_uint, c_ulong, c_void};
use core::ptr;
use core::sync::atomic::{AtomicBool, AtomicU64, Ordering};

// ── Constants ────────────────────────────────────────────

const MAX_OBJECTS: usize = 4096;
const MAX_HANDLES: usize = 65536;
const MAX_DIR_CHILDREN: usize = 256;
const MAX_NAME_LEN: usize = 64;
const ROOT_DIR_ID: u32 = 1;

pub const OB_TYPE_DIRECTORY: u32 = 1;
pub const OB_TYPE_PROCESS: u32 = 2;
pub const OB_TYPE_THREAD: u32 = 3;
pub const OB_TYPE_EVENT: u32 = 4;
pub const OB_TYPE_MUTANT: u32 = 5;
pub const OB_TYPE_SEMAPHORE: u32 = 6;
pub const OB_TYPE_TIMER: u32 = 7;
pub const OB_TYPE_PORT: u32 = 8;
pub const OB_TYPE_ENDPOINT: u32 = 9;
pub const OB_TYPE_NOTIFICATION: u32 = 10;
pub const OB_TYPE_FILE: u32 = 11;
pub const OB_TYPE_DEVICE: u32 = 12;
pub const OB_TYPE_IO_COMPLETION: u32 = 13;
pub const OB_TYPE_CUSTOM: u32 = 255;

pub const ACCESS_READ: u32 = 0x0001;
pub const ACCESS_WRITE: u32 = 0x0002;
pub const ACCESS_EXECUTE: u32 = 0x0004;
pub const ACCESS_DELETE: u32 = 0x0008;
pub const ACCESS_READ_CONTROL: u32 = 0x0010;
pub const ACCESS_WRITE_DAC: u32 = 0x0020;
pub const ACCESS_WRITE_OWNER: u32 = 0x0040;
pub const ACCESS_SYNCHRONIZE: u32 = 0x0080;
pub const ACCESS_ALL: u32 = 0xFFFF;
pub const ACCESS_GENERIC_READ: u32 = 0x0100;
pub const ACCESS_GENERIC_WRITE: u32 = 0x0200;
pub const ACCESS_GENERIC_EXECUTE: u32 = 0x0400;
pub const ACCESS_GENERIC_ALL: u32 = 0x0800;

const HANDLE_FLAG_INHERIT: u32 = 0x0001;
const HANDLE_FLAG_PROTECT: u32 = 0x0002;
const OBJ_FLAG_PERMANENT: u32 = 0x0001;
const OBJ_FLAG_KERNEL: u32 = 0x0002;
const OBJ_FLAG_PROTECTED: u32 = 0x0004;
const OBJ_STATUS_ACTIVE: u32 = 0;
const OBJ_STATUS_DELETED: u32 = 1;

extern "C" {
    fn printk(fmt: *const c_char, ...) -> c_int;
    fn kzalloc(size: c_ulong, flags: c_uint) -> *mut c_void;
    fn kfree(ptr: *mut c_void);
    fn memset(s: *mut c_void, c: c_int, n: c_ulong) -> *mut c_void;
    fn memcpy(dest: *mut c_void, src: *const c_void, n: c_ulong) -> *mut c_void;
}

// ── Ticket lock ─────────────────────────────────────────

struct TicketLock {
    next: AtomicU64,
    now_serving: AtomicU64,
}

impl TicketLock {
    const fn new() -> Self {
        TicketLock { next: AtomicU64::new(0), now_serving: AtomicU64::new(0) }
    }

    fn acquire(&self) {
        let ticket = self.next.fetch_add(1, Ordering::Relaxed);
        while self.now_serving.load(Ordering::Acquire) != ticket {
            core::hint::spin_loop();
        }
    }

    fn release(&self) {
        self.now_serving.fetch_add(1, Ordering::Release);
    }
}

// ── Object type descriptor ──────────────────────────────

#[repr(C)]
struct ObTypeDescriptor {
    type_id: u32,
    name: [u8; 32],
    default_access: u32,
    supports_wait: bool,
    supports_signal: bool,
    pool_tag: u32,
}

// ── Core object structure ───────────────────────────────

#[repr(C)]
struct ObObject {
    in_use: AtomicBool,
    ref_count: AtomicU64,
    type_id: u32,
    status: u32,
    name: [u8; MAX_NAME_LEN],
    flags: u32,
    default_access: u32,
    security_ctx: u64,
    data: *mut c_void,
    data_size: u64,
    owner_pid: u32,
    creator_pid: u32,
    dir_parent: u32,
    dir_children: [u32; MAX_DIR_CHILDREN],
    child_count: u32,
}

// ── Handle entry ────────────────────────────────────────

#[repr(C)]
struct HandleEntry {
    in_use: bool,
    object_id: u32,
    granted_access: u32,
    flags: u32,
    owner_pid: u32,
}

// ── Global state ────────────────────────────────────────

static LOCK: TicketLock = TicketLock::new();
static INIT_DONE: AtomicBool = AtomicBool::new(false);

static mut OBJECTS: [ObObject; MAX_OBJECTS] = unsafe { core::mem::zeroed() };
static mut HANDLE_TABLE: [HandleEntry; MAX_HANDLES] = unsafe { core::mem::zeroed() };
static mut NEXT_HANDLE: u32 = 1;
static mut OBJECT_COUNT: u32 = 0;
static mut TYPE_DESCRIPTORS: [ObTypeDescriptor; 256] = unsafe { core::mem::zeroed() };

// ── Internal helpers ────────────────────────────────────

unsafe fn obj_ref(obj_id: u32) -> *mut ObObject {
    if obj_id == 0 || obj_id as usize > MAX_OBJECTS {
        return ptr::null_mut();
    }
    let obj = &mut OBJECTS[obj_id as usize - 1];
    if !obj.in_use.load(Ordering::Acquire) {
        return ptr::null_mut();
    }
    obj
}

unsafe fn alloc_object() -> u32 {
    for i in 0..MAX_OBJECTS {
        let obj = &mut OBJECTS[i];
        if !obj.in_use.load(Ordering::Acquire) {
            obj.in_use.store(true, Ordering::Release);
            obj.ref_count = AtomicU64::new(1);
            obj.status = OBJ_STATUS_ACTIVE;
            obj.flags = 0;
            obj.default_access = ACCESS_ALL;
            obj.security_ctx = 0;
            obj.data = ptr::null_mut();
            obj.data_size = 0;
            obj.owner_pid = 0;
            obj.creator_pid = 0;
            obj.dir_parent = 0;
            obj.child_count = 0;
            OBJECT_COUNT += 1;
            return (i + 1) as u32;
        }
    }
    0
}

unsafe fn free_object(obj_id: u32) {
    let obj = &mut OBJECTS[obj_id as usize - 1];
    if !obj.data.is_null() {
        kfree(obj.data);
        obj.data = ptr::null_mut();
    }
    obj.in_use.store(false, Ordering::Release);
    obj.ref_count = AtomicU64::new(0);
    OBJECT_COUNT -= 1;
}

unsafe fn alloc_handle() -> u32 {
    let start = NEXT_HANDLE;
    loop {
        let h = NEXT_HANDLE;
        NEXT_HANDLE = if h >= MAX_HANDLES as u32 - 1 { 1 } else { h + 1 };
        if h == 0 { continue; }
        if !HANDLE_TABLE[h as usize].in_use { return h; }
        if NEXT_HANDLE == start { return 0; }
    }
}

unsafe fn name_from_c(dst: &mut [u8; MAX_NAME_LEN], src: *const c_char) {
    if src.is_null() { return; }
    for i in 0..MAX_NAME_LEN - 1 {
        let c = *src.add(i) as u8;
        dst[i] = c;
        if c == 0 { break; }
    }
    dst[MAX_NAME_LEN - 1] = 0;
}

fn name_cmp(obj_name: &[u8; MAX_NAME_LEN], src: *const c_char) -> bool {
    if src.is_null() { return obj_name[0] == 0; }
    unsafe {
        for i in 0..MAX_NAME_LEN - 1 {
            let c = *src.add(i) as u8;
            if obj_name[i] != c { return false; }
            if c == 0 { return true; }
        }
    }
    obj_name[MAX_NAME_LEN - 1] == 0
}

fn names_eq(a: &[u8; MAX_NAME_LEN], b: &[u8; MAX_NAME_LEN]) -> bool {
    for i in 0..MAX_NAME_LEN {
        if a[i] != b[i] { return false; }
        if a[i] == 0 { return true; }
    }
    true
}

// ── Initialization ──────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_om_init() -> c_int {
    if INIT_DONE.load(Ordering::Acquire) { return 0; }

    LOCK.acquire();

    unsafe {
        let root = &mut OBJECTS[0];
        root.in_use.store(true, Ordering::Release);
        root.ref_count = AtomicU64::new(1);
        root.type_id = OB_TYPE_DIRECTORY;
        root.status = OBJ_STATUS_ACTIVE;
        root.name = [0u8; MAX_NAME_LEN];
        root.name[0] = b'\\';
        root.flags = OBJ_FLAG_KERNEL;
        root.default_access = ACCESS_ALL;
        root.security_ctx = 0;
        root.data = ptr::null_mut();
        root.data_size = 0;
        root.owner_pid = 0;
        root.creator_pid = 0;
        root.dir_parent = 0;
        root.child_count = 0;
        OBJECT_COUNT = 1;
        NEXT_HANDLE = 1;

        let types: [(u32, [u8; 32], u32, bool, bool); 12] = [
            (OB_TYPE_DIRECTORY,  *b"Directory\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, false, false),
            (OB_TYPE_PROCESS,    *b"Process\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, true),
            (OB_TYPE_THREAD,     *b"Thread\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, true),
            (OB_TYPE_EVENT,      *b"Event\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, true),
            (OB_TYPE_MUTANT,     *b"Mutant\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, false),
            (OB_TYPE_SEMAPHORE,  *b"Semaphore\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, true),
            (OB_TYPE_TIMER,      *b"Timer\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, false),
            (OB_TYPE_PORT,       *b"Port\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, true),
            (OB_TYPE_ENDPOINT,   *b"Endpoint\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, true),
            (OB_TYPE_NOTIFICATION, *b"Notification\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, true, true),
            (OB_TYPE_FILE,       *b"File\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, false, false),
            (OB_TYPE_DEVICE,     *b"Device\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", ACCESS_ALL, false, false),
        ];
        for (type_id, name, default_access, supports_wait, supports_signal) in types {
            TYPE_DESCRIPTORS[type_id as usize] = ObTypeDescriptor {
                type_id, name, default_access, supports_wait, supports_signal, pool_tag: 0,
            };
        }
    }

    LOCK.release();
    INIT_DONE.store(true, Ordering::Release);
    0
}

// ── Object lifecycle ────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_om_create_object(
    name: *const c_char, type_id: u32, default_access: u32,
    data: *mut c_void, data_size: u64,
) -> u32 {
    if !INIT_DONE.load(Ordering::Acquire) { return 0; }

    LOCK.acquire();

    let obj_id = unsafe { alloc_object() };
    if obj_id == 0 { LOCK.release(); return 0; }

    unsafe {
        let obj = &mut OBJECTS[obj_id as usize - 1];
        obj.type_id = type_id;
        name_from_c(&mut obj.name, name);
        obj.default_access = if default_access != 0 { default_access }
            else { TYPE_DESCRIPTORS[type_id as usize].default_access };
        obj.flags = OBJ_FLAG_KERNEL;
        obj.data = data;
        obj.data_size = data_size;
        obj.owner_pid = 0;
        obj.creator_pid = 0;
        obj.dir_parent = ROOT_DIR_ID;
    }

    LOCK.release();
    obj_id
}

#[no_mangle]
pub extern "C" fn sentraos_om_delete_object(obj_id: u32) -> c_int {
    if obj_id == 0 || obj_id == ROOT_DIR_ID || !INIT_DONE.load(Ordering::Acquire) {
        return -22;
    }

    LOCK.acquire();

    unsafe {
        if obj_ref(obj_id).is_null() { LOCK.release(); return -2; }

        let parent_id = OBJECTS[obj_id as usize - 1].dir_parent;
        if parent_id != 0 {
            let idx = parent_id as usize - 1;
            for i in 0..OBJECTS[idx].child_count as usize {
                if OBJECTS[idx].dir_children[i] == obj_id {
                    for j in i..OBJECTS[idx].child_count as usize - 1 {
                        OBJECTS[idx].dir_children[j] = OBJECTS[idx].dir_children[j + 1];
                    }
                    OBJECTS[idx].child_count -= 1;
                    break;
                }
            }
        }

        if OBJECTS[obj_id as usize - 1].ref_count.load(Ordering::Relaxed) > 1 {
            OBJECTS[obj_id as usize - 1].status = OBJ_STATUS_DELETED;
            LOCK.release();
            return 0;
        }

        free_object(obj_id);
    }

    LOCK.release();
    0
}

// ── Reference counting ──────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_om_ref(obj_id: u32) {
    unsafe {
        if !obj_ref(obj_id).is_null() {
            OBJECTS[obj_id as usize - 1].ref_count.fetch_add(1, Ordering::Relaxed);
        }
    }
}

#[no_mangle]
pub extern "C" fn sentraos_om_deref(obj_id: u32) {
    unsafe {
        if obj_ref(obj_id).is_null() { return; }
        let prev = OBJECTS[obj_id as usize - 1].ref_count.fetch_sub(1, Ordering::Release);
        if prev == 1 {
            LOCK.acquire();
            if OBJECTS[obj_id as usize - 1].ref_count.load(Ordering::Acquire) == 0 {
                free_object(obj_id);
            }
            LOCK.release();
        }
    }
}

#[no_mangle]
pub extern "C" fn sentraos_om_ref_count(obj_id: u32) -> u64 {
    unsafe {
        if obj_ref(obj_id).is_null() { 0 }
        else { OBJECTS[obj_id as usize - 1].ref_count.load(Ordering::Relaxed) }
    }
}

// ── Handle management ───────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_om_open_handle(
    obj_id: u32, desired_access: u32, handle: *mut u32,
) -> c_int {
    if handle.is_null() || !INIT_DONE.load(Ordering::Acquire) { return -22; }

    LOCK.acquire();

    unsafe {
        if obj_ref(obj_id).is_null() { LOCK.release(); return -2; }

        let obj = &OBJECTS[obj_id as usize - 1];
        if (desired_access & !obj.default_access) != 0 {
            LOCK.release(); return -13;
        }

        let h = alloc_handle();
        if h == 0 { LOCK.release(); return -12; }

        HANDLE_TABLE[h as usize] = HandleEntry {
            in_use: true, object_id: obj_id, granted_access: desired_access,
            flags: 0, owner_pid: 0,
        };
        OBJECTS[obj_id as usize - 1].ref_count.fetch_add(1, Ordering::Relaxed);
        *handle = h;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_om_close_handle(handle: u32) -> c_int {
    if handle == 0 || handle as usize >= MAX_HANDLES { return -22; }

    LOCK.acquire();

    unsafe {
        let entry = &mut HANDLE_TABLE[handle as usize];
        if !entry.in_use { LOCK.release(); return -2; }

        let obj_id = entry.object_id;
        entry.in_use = false;

        if obj_ref(obj_id).is_null() { LOCK.release(); return 0; }
        let prev = OBJECTS[obj_id as usize - 1].ref_count.fetch_sub(1, Ordering::Release);
        if prev == 1 { free_object(obj_id); }
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_om_handle_to_obj(handle: u32) -> u32 {
    if handle == 0 || handle as usize >= MAX_HANDLES { return 0; }
    unsafe {
        if HANDLE_TABLE[handle as usize].in_use {
            HANDLE_TABLE[handle as usize].object_id
        } else { 0 }
    }
}

// ── Directory / namespace operations ────────────────────

#[no_mangle]
pub extern "C" fn sentraos_om_create_directory(name: *const c_char) -> u32 {
    if !INIT_DONE.load(Ordering::Acquire) { return 0; }

    LOCK.acquire();

    let obj_id = unsafe { alloc_object() };
    if obj_id == 0 { LOCK.release(); return 0; }

    unsafe {
        let obj = &mut OBJECTS[obj_id as usize - 1];
        obj.type_id = OB_TYPE_DIRECTORY;
        name_from_c(&mut obj.name, name);
        obj.default_access = ACCESS_ALL;
        obj.flags = OBJ_FLAG_KERNEL;
        obj.dir_parent = ROOT_DIR_ID;
    }

    let root = &mut OBJECTS[0];
    if root.child_count < MAX_DIR_CHILDREN as u32 {
        root.dir_children[root.child_count as usize] = obj_id;
        root.child_count += 1;
    }

    LOCK.release();
    obj_id
}

#[no_mangle]
pub extern "C" fn sentraos_om_link(dir_id: u32, obj_id: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        if obj_ref(dir_id).is_null() || obj_ref(obj_id).is_null() {
            LOCK.release(); return -2;
        }
        if OBJECTS[dir_id as usize - 1].type_id != OB_TYPE_DIRECTORY {
            LOCK.release(); return -22;
        }
        if OBJECTS[dir_id as usize - 1].child_count >= MAX_DIR_CHILDREN as u32 {
            LOCK.release(); return -12;
        }

        let idx = dir_id as usize - 1;
        OBJECTS[idx].dir_children[OBJECTS[idx].child_count as usize] = obj_id;
        OBJECTS[idx].child_count += 1;
        OBJECTS[obj_id as usize - 1].dir_parent = dir_id;
        OBJECTS[obj_id as usize - 1].ref_count.fetch_add(1, Ordering::Relaxed);
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_om_unlink(dir_id: u32, obj_id: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        if obj_ref(dir_id).is_null() || OBJECTS[dir_id as usize - 1].type_id != OB_TYPE_DIRECTORY {
            LOCK.release(); return -22;
        }

        let d = &mut OBJECTS[dir_id as usize - 1];
        let mut found = false;
        for i in 0..d.child_count as usize {
            if d.dir_children[i] == obj_id {
                for j in i..d.child_count as usize - 1 {
                    d.dir_children[j] = d.dir_children[j + 1];
                }
                d.child_count -= 1;
                found = true;
                break;
            }
        }
        if !found { LOCK.release(); return -2; }

        OBJECTS[obj_id as usize - 1].dir_parent = 0;
        let prev = OBJECTS[obj_id as usize - 1].ref_count.fetch_sub(1, Ordering::Release);
        if prev == 1 { free_object(obj_id); }
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_om_lookup(name: *const c_char) -> u32 {
    if name.is_null() || !INIT_DONE.load(Ordering::Acquire) { return 0; }

    LOCK.acquire();

    let result = unsafe {
        let root = &OBJECTS[0];
        for i in 0..root.child_count as usize {
            let child_id = root.dir_children[i];
            if child_id == 0 || child_id as usize > MAX_OBJECTS { continue; }
            if name_cmp(&OBJECTS[child_id as usize - 1].name, name) {
                LOCK.release();
                return child_id;
            }
        }
        0
    };

    LOCK.release();
    result
}

#[no_mangle]
pub extern "C" fn sentraos_om_enumerate(dir_id: u32, buf: *mut u32, buf_size: u32) -> c_int {
    if buf.is_null() || buf_size == 0 { return -22; }

    LOCK.acquire();

    unsafe {
        if obj_ref(dir_id).is_null() || OBJECTS[dir_id as usize - 1].type_id != OB_TYPE_DIRECTORY {
            LOCK.release(); return -22;
        }

        let count = if OBJECTS[dir_id as usize - 1].child_count < buf_size {
            OBJECTS[dir_id as usize - 1].child_count
        } else { buf_size };

        for i in 0..count as usize {
            *buf.add(i) = OBJECTS[dir_id as usize - 1].dir_children[i];
        }

        LOCK.release();
        count as c_int
    }
}

// ── Security / access control ───────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_om_set_security(obj_id: u32, security_ctx: u64) -> c_int {
    LOCK.acquire();

    unsafe {
        if obj_ref(obj_id).is_null() { LOCK.release(); return -2; }
        OBJECTS[obj_id as usize - 1].security_ctx = security_ctx;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_om_check_access(
    obj_id: u32, desired_access: u32, subject_ctx: u64,
) -> c_int {
    unsafe {
        if obj_ref(obj_id).is_null() { return -2; }

        let obj = &OBJECTS[obj_id as usize - 1];
        if obj.flags & OBJ_FLAG_KERNEL != 0 { return 0; }
        if subject_ctx != 0 && subject_ctx == obj.security_ctx { return 0; }
        if (desired_access & !obj.default_access) != 0 { return -13; }
    }
    0
}

#[no_mangle]
pub extern "C" fn sentraos_om_set_default_access(obj_id: u32, access: u32) -> c_int {
    LOCK.acquire();
    unsafe {
        if obj_ref(obj_id).is_null() { LOCK.release(); return -2; }
        OBJECTS[obj_id as usize - 1].default_access = access;
    }
    LOCK.release();
    0
}

// ── Query / introspection ───────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_om_get_type(obj_id: u32) -> u32 {
    unsafe {
        if obj_ref(obj_id).is_null() { 0 }
        else { OBJECTS[obj_id as usize - 1].type_id }
    }
}

#[no_mangle]
pub extern "C" fn sentraos_om_get_data(obj_id: u32) -> *mut c_void {
    unsafe {
        if obj_ref(obj_id).is_null() { ptr::null_mut() }
        else { OBJECTS[obj_id as usize - 1].data }
    }
}

#[no_mangle]
pub extern "C" fn sentraos_om_set_data(obj_id: u32, data: *mut c_void, data_size: u64) -> c_int {
    LOCK.acquire();
    unsafe {
        if obj_ref(obj_id).is_null() { LOCK.release(); return -2; }
        let obj = &mut OBJECTS[obj_id as usize - 1];
        if !obj.data.is_null() { kfree(obj.data); }
        obj.data = data;
        obj.data_size = data_size;
    }
    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_om_get_name(obj_id: u32, buf: *mut c_char, buf_size: u32) -> c_int {
    if buf.is_null() || buf_size == 0 { return -22; }

    unsafe {
        if obj_ref(obj_id).is_null() { return -2; }
        let len = if buf_size as usize > MAX_NAME_LEN { MAX_NAME_LEN } else { buf_size as usize };
        memcpy(buf as *mut c_void, OBJECTS[obj_id as usize - 1].name.as_ptr() as *const c_void, len as c_ulong);
        *buf.add(len - 1) = 0;
    }
    0
}

#[no_mangle]
pub extern "C" fn sentraos_om_stats() -> u32 {
    unsafe { OBJECT_COUNT }
}

#[no_mangle]
pub extern "C" fn sentraos_om_is_init() -> c_int {
    if INIT_DONE.load(Ordering::Acquire) { 1 } else { 0 }
}
