// SPDX-License-Identifier: GPL-2.0

//! SentraOS Mach IPC — port-based message passing subsystem.
//!
//! Inspired by the Mach microkernel, this module provides:
//!   - Port-based IPC with message passing
//!   - Port rights (send, receive, send-once)
//!   - Port sets for multiplexed receive
//!   - Message queues with timeout support
//!   - Backpressure via queue depth limits
//!
//! Ports are first-class objects managed by the SentraOS Object Manager,
//! providing unified reference counting, naming, and security.

#![no_std]

use core::ffi::{c_char, c_int, c_uint, c_ulong, c_void};
use core::ptr;
use core::sync::atomic::{AtomicBool, AtomicU32, AtomicU64, Ordering};

// ── Constants ────────────────────────────────────────────

const MAX_PORTS: usize = 2048;
const MAX_PORT_SETS: usize = 256;
const MAX_MSG_QUEUE: usize = 128;
const MAX_MSG_SIZE: usize = 4096;
const MAX_PORT_NAME: usize = 48;
const MAX_RIGHTS_PER_PORT: usize = 64;

// Port status
const PORT_STATUS_IDLE: u32 = 0;
const PORT_STATUS_ACTIVE: u32 = 1;
const PORT_STATUS_DESTROYED: u32 = 2;

// Port right types
const RIGHT_SEND: u32 = 1;
const RIGHT_RECEIVE: u32 = 2;
const RIGHT_SEND_ONCE: u32 = 3;

// Message flags
const MSG_FLAG_NONE: u32 = 0;
const MSG_FLAG_URGENT: u32 = 0x0001;
const MSG_FLAG_NONBLOCKING: u32 = 0x0002;
const MSG_FLAG_NOTIFY: u32 = 0x0004;

// Return codes
const MACH_MSG_SUCCESS: c_int = 0;
const MACH_MSG_TIMEOUT: c_int = -110; // -ETIMEDOUT
const MACH_MSG_NO_SPACE: c_int = -12; // -ENOMEM
const MACH_MSG_INVALID: c_int = -22;  // -EINVAL
const MACH_MSG_PORT_DIED: c_int = -32; // -EPIPE
const MACH_MSG_SEND_ONCE: c_int = 1;

// ── FFI to kernel ───────────────────────────────────────

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

// ── Message structure ───────────────────────────────────

#[repr(C)]
#[derive(Clone, Copy)]
struct MachMsgHeader {
    msg_id: u64,
    msg_size: u64,
    flags: u32,
    remote_port: u32,
    local_port: u32,
    seqno: u64,
}

#[repr(C)]
struct MachMessage {
    in_use: bool,
    header: MachMsgHeader,
    data: [u8; MAX_MSG_SIZE],
    sender_pid: u32,
    send_time: u64,
}

// ── Port right descriptor ───────────────────────────────

#[repr(C)]
#[derive(Clone, Copy)]
struct PortRight {
    right_type: u32,
    pid: u32,
}

// ── Port structure ──────────────────────────────────────

#[repr(C)]
struct MachPort {
    in_use: AtomicBool,
    name: [u8; MAX_PORT_NAME],
    status: AtomicU32,
    flags: u32,
    msg_queue: [MachMessage; MAX_MSG_QUEUE],
    msg_count: u32,
    msg_head: u32,
    msg_tail: u32,
    rights: [PortRight; MAX_RIGHTS_PER_PORT],
    right_count: u32,
    seqno: AtomicU64,
    owner_pid: u32,
    om_obj_id: u32,
    port_set: u32,
}

// ── Port set structure ──────────────────────────────────

#[repr(C)]
struct PortSet {
    in_use: bool,
    name: [u8; MAX_PORT_NAME],
    ports: [u32; MAX_PORTS],
    port_count: u32,
    owner_pid: u32,
}

// ── Global state ────────────────────────────────────────

static LOCK: TicketLock = TicketLock::new();
static INIT_DONE: AtomicBool = AtomicBool::new(false);

static mut PORTS: [MachPort; MAX_PORTS] = unsafe { core::mem::zeroed() };
static mut PORT_SETS: [PortSet; MAX_PORT_SETS] = unsafe { core::mem::zeroed() };
static mut PORT_COUNT: u32 = 0;
static mut PORT_SET_COUNT: u32 = 0;

// ── Port set iteration state ────────────────────────────

static mut NEXT_PORT_SET_ID: u32 = 1;

// ── Object Manager FFI ──────────────────────────────────

extern "C" {
    fn sentraos_om_init() -> c_int;
    fn sentraos_om_create_object(
        name: *const c_char, type_id: u32, default_access: u32,
        data: *mut c_void, data_size: u64,
    ) -> u32;
    fn sentraos_om_delete_object(obj_id: u32) -> c_int;
    fn sentraos_om_ref(obj_id: u32);
    fn sentraos_om_deref(obj_id: u32);
    fn sentraos_om_get_type(obj_id: u32) -> u32;
    fn sentraos_om_set_data(obj_id: u32, data: *mut c_void, data_size: u64) -> c_int;
    fn sentraos_om_get_data(obj_id: u32) -> *mut c_void;
    fn sentraos_om_set_security(obj_id: u32, security_ctx: u64) -> c_int;
    fn sentraos_om_check_access(obj_id: u32, desired_access: u32, subject_ctx: u64) -> c_int;
    fn sentraos_om_is_init() -> c_int;
}

// ── Internal helpers ────────────────────────────────────

unsafe fn alloc_port() -> u32 {
    for i in 0..MAX_PORTS {
        if !PORTS[i].in_use.load(Ordering::Acquire) {
            PORTS[i].in_use.store(true, Ordering::Release);
            PORTS[i].status.store(PORT_STATUS_ACTIVE, Ordering::Release);
            PORTS[i].msg_count = 0;
            PORTS[i].msg_head = 0;
            PORTS[i].msg_tail = 0;
            PORTS[i].right_count = 0;
            PORTS[i].seqno = AtomicU64::new(0);
            PORTS[i].port_set = 0;
            PORTS[i].flags = 0;
            PORT_COUNT += 1;
            return (i + 1) as u32;
        }
    }
    0
}

unsafe fn free_port(port_id: u32) {
    let idx = port_id as usize - 1;
    PORTS[idx].in_use.store(false, Ordering::Release);
    PORTS[idx].status.store(PORT_STATUS_DESTROYED, Ordering::Release);
    PORTS[idx].msg_count = 0;
    PORTS[idx].right_count = 0;
    PORT_COUNT -= 1;
}

unsafe fn port_ref(port_id: u32) -> *mut MachPort {
    if port_id == 0 || port_id as usize > MAX_PORTS { return ptr::null_mut(); }
    let p = &mut PORTS[port_id as usize - 1];
    if !p.in_use.load(Ordering::Acquire) { return ptr::null_mut(); }
    p
}

unsafe fn enqueue_msg(port_id: u32, msg: &MachMessage) -> c_int {
    let p = &mut PORTS[port_id as usize - 1];
    if p.msg_count >= MAX_MSG_QUEUE as u32 {
        return MACH_MSG_NO_SPACE;
    }
    p.msg_queue[p.msg_tail as usize] = *msg;
    p.msg_tail = (p.msg_tail + 1) % MAX_MSG_QUEUE as u32;
    p.msg_count += 1;
    0
}

unsafe fn dequeue_msg(port_id: u32, buf: *mut c_void, size: *mut u64) -> c_int {
    let p = &mut PORTS[port_id as usize - 1];
    if p.msg_count == 0 {
        return MACH_MSG_TIMEOUT;
    }
    let msg = &p.msg_queue[p.msg_head as usize];
    let copy_size = if msg.header.msg_size < *size { msg.header.msg_size } else { *size };
    memcpy(buf, msg.data.as_ptr() as *const c_void, copy_size as c_ulong);
    *size = msg.header.msg_size;

    p.msg_head = (p.msg_head + 1) % MAX_MSG_QUEUE as u32;
    p.msg_count -= 1;
    0
}

fn name_from_c(dst: &mut [u8], src: *const c_char) {
    if src.is_null() { return; }
    let max = if dst.len() < MAX_PORT_NAME { dst.len() } else { MAX_PORT_NAME };
    unsafe {
        for i in 0..max - 1 {
            let c = *src.add(i) as u8;
            dst[i] = c;
            if c == 0 { break; }
        }
        dst[max - 1] = 0;
    }
}

// ── Initialization ──────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_ipc_init() -> c_int {
    if INIT_DONE.load(Ordering::Acquire) { return 0; }
    LOCK.acquire();

    // Ensure Object Manager is initialized first
    if sentraos_om_is_init() == 0 {
        let ret = sentraos_om_init();
        if ret != 0 {
            LOCK.release();
            return ret;
        }
    }

    LOCK.release();
    INIT_DONE.store(true, Ordering::Release);
    0
}

// ── Port lifecycle ──────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_allocate(name: *const c_char, port_name: *mut u32) -> c_int {
    if port_name.is_null() || !INIT_DONE.load(Ordering::Acquire) { return MACH_MSG_INVALID; }

    LOCK.acquire();

    let pid = unsafe { alloc_port() };
    if pid == 0 { LOCK.release(); return MACH_MSG_NO_SPACE; }

    unsafe {
        let p = &mut PORTS[pid as usize - 1];
        name_from_c(&mut p.name, name);
        p.owner_pid = 0;
        p.om_obj_id = 0;

        // Register with Object Manager
        let om_id = sentraos_om_create_object(name, 8, 0xFFFF, ptr::null_mut(), 0);
        if om_id != 0 {
            p.om_obj_id = om_id;
            sentraos_om_set_data(om_id, &mut PORTS[pid as usize - 1] as *mut _ as *mut c_void, 0);
            // Grant send+receive right to creator
            if p.right_count < MAX_RIGHTS_PER_PORT as u32 {
                p.rights[p.right_count as usize] = PortRight { right_type: RIGHT_SEND, pid: 0 };
                p.right_count += 1;
                p.rights[p.right_count as usize] = PortRight { right_type: RIGHT_RECEIVE, pid: 0 };
                p.right_count += 1;
            }
        }

        *port_name = pid;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_deallocate(port_name: u32) -> c_int {
    if port_name == 0 || !INIT_DONE.load(Ordering::Acquire) { return MACH_MSG_INVALID; }

    LOCK.acquire();

    unsafe {
        if port_ref(port_name).is_null() { LOCK.release(); return MACH_MSG_PORT_DIED; }

        let p = &mut PORTS[port_name as usize - 1];

        // Remove from port set if part of one
        if p.port_set != 0 {
            let set_idx = p.port_set as usize - 1;
            let set = &mut PORT_SETS[set_idx];
            for i in 0..set.port_count as usize {
                if set.ports[i] == port_name {
                    for j in i..set.port_count as usize - 1 {
                        set.ports[j] = set.ports[j + 1];
                    }
                    set.port_count -= 1;
                    break;
                }
            }
        }

        // Clean up OM object
        if p.om_obj_id != 0 {
            sentraos_om_delete_object(p.om_obj_id);
        }

        free_port(port_name);
    }

    LOCK.release();
    0
}

// ── Message sending / receiving ─────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_ipc_msg_send(
    port_name: u32, msg: *const c_void, size: u64, flags: u32,
) -> c_int {
    if msg.is_null() || size == 0 || !INIT_DONE.load(Ordering::Acquire) {
        return MACH_MSG_INVALID;
    }
    if size > MAX_MSG_SIZE as u64 { return MACH_MSG_NO_SPACE; }

    LOCK.acquire();

    unsafe {
        let p = port_ref(port_name);
        if p.is_null() { LOCK.release(); return MACH_MSG_PORT_DIED; }

        // Check send right
        let mut has_right = false;
        for i in 0..(*p).right_count as usize {
            if (*p).rights[i].right_type == RIGHT_SEND || (*p).rights[i].right_type == RIGHT_SEND_ONCE {
                has_right = true;
                // Consume send-once right
                if (*p).rights[i].right_type == RIGHT_SEND_ONCE {
                    for j in i..(*p).right_count as usize - 1 {
                        (*p).rights[j] = (*p).rights[j + 1];
                    }
                    (*p).right_count -= 1;
                }
                break;
            }
        }
        if !has_right { LOCK.release(); return MACH_MSG_INVALID; }

        let mut kmsg = MachMessage {
            in_use: true,
            header: MachMsgHeader {
                msg_id: 0,
                msg_size: size,
                flags,
                remote_port: port_name,
                local_port: 0,
                seqno: (*p).seqno.fetch_add(1, Ordering::Relaxed),
            },
            data: [0u8; MAX_MSG_SIZE],
            sender_pid: (*p).owner_pid,
            send_time: 0,
        };

        // If queue is full and nonblocking flag set, return immediately
        if (*p).msg_count >= MAX_MSG_QUEUE as u32 && (flags & MSG_FLAG_NONBLOCKING) != 0 {
            LOCK.release();
            // If send-once was consumed above, return success anyway
            return 0;
        }

        memcpy(kmsg.data.as_mut_ptr() as *mut c_void, msg, size as c_ulong);

        let ret = enqueue_msg(port_name, &kmsg);
        LOCK.release();
        ret
    }
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_msg_receive(
    port_name: u32, buf: *mut c_void, size: *mut u64, timeout_ms: u64,
) -> c_int {
    if buf.is_null() || size.is_null() || !INIT_DONE.load(Ordering::Acquire) {
        return MACH_MSG_INVALID;
    }

    // For now, simple polling receive with no blocking
    // Future: add wait queue integration for true blocking receive
    LOCK.acquire();

    unsafe {
        let p = port_ref(port_name);
        if p.is_null() { LOCK.release(); return MACH_MSG_PORT_DIED; }

        // If this port is part of a port set, try to receive from any port in the set
        if (*p).port_set != 0 {
            let set_idx = (*p).port_set as usize - 1;
            let set = &PORT_SETS[set_idx];
            for i in 0..set.port_count as usize {
                let member_port = set.ports[i];
                if member_port == 0 || member_port == port_name { continue; }
                if PORTS[member_port as usize - 1].msg_count > 0 {
                    let ret = dequeue_msg(member_port, buf, size);
                    LOCK.release();
                    return ret;
                }
            }
        }

        let ret = dequeue_msg(port_name, buf, size);
        LOCK.release();
        ret
    }
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_msg_send_receive(
    reply_port: u32, port_name: u32,
    msg: *const c_void, size: u64,
    reply_buf: *mut c_void, reply_size: *mut u64,
) -> c_int {
    if msg.is_null() || reply_buf.is_null() || reply_size.is_null() {
        return MACH_MSG_INVALID;
    }

    // Send the message
    let ret = sentraos_ipc_msg_send(port_name, msg, size, MSG_FLAG_NONE);
    if ret != 0 { return ret; }

    // Wait for reply on the reply port (simplified: poll once)
    sentraos_ipc_msg_receive(reply_port, reply_buf, reply_size, 0)
}

// ── Port rights management ──────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_ipc_give_send_right(port_name: u32, target_pid: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        let p = port_ref(port_name);
        if p.is_null() { LOCK.release(); return MACH_MSG_PORT_DIED; }

        if (*p).right_count >= MAX_RIGHTS_PER_PORT as u32 {
            LOCK.release(); return MACH_MSG_NO_SPACE;
        }

        (*p).rights[(*p).right_count as usize] = PortRight { right_type: RIGHT_SEND, pid: target_pid };
        (*p).right_count += 1;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_give_receive_right(port_name: u32, target_pid: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        let p = port_ref(port_name);
        if p.is_null() { LOCK.release(); return MACH_MSG_PORT_DIED; }

        if (*p).right_count >= MAX_RIGHTS_PER_PORT as u32 {
            LOCK.release(); return MACH_MSG_NO_SPACE;
        }

        (*p).rights[(*p).right_count as usize] = PortRight { right_type: RIGHT_RECEIVE, pid: target_pid };
        (*p).right_count += 1;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_revoke_right(port_name: u32, target_pid: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        let p = port_ref(port_name);
        if p.is_null() { LOCK.release(); return MACH_MSG_PORT_DIED; }

        let mut i = 0;
        while i < (*p).right_count as usize {
            if (*p).rights[i].pid == target_pid {
                for j in i..(*p).right_count as usize - 1 {
                    (*p).rights[j] = (*p).rights[j + 1];
                }
                (*p).right_count -= 1;
            } else {
                i += 1;
            }
        }
    }

    LOCK.release();
    0
}

// ── Port set operations ─────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_set_create(set_name: *const c_char, set_id: *mut u32) -> c_int {
    if set_id.is_null() || !INIT_DONE.load(Ordering::Acquire) { return MACH_MSG_INVALID; }

    LOCK.acquire();

    unsafe {
        for i in 0..MAX_PORT_SETS {
            if !PORT_SETS[i].in_use {
                PORT_SETS[i].in_use = true;
                name_from_c(&mut PORT_SETS[i].name, set_name);
                PORT_SETS[i].port_count = 0;
                PORT_SETS[i].owner_pid = 0;
                PORT_SET_COUNT += 1;
                *set_id = (i + 1) as u32;
                LOCK.release();
                return 0;
            }
        }
    }

    LOCK.release();
    MACH_MSG_NO_SPACE
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_set_add(set_id: u32, port_name: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        let set = &mut PORT_SETS[set_id as usize - 1];
        if !set.in_use { LOCK.release(); return MACH_MSG_INVALID; }
        if set.port_count >= MAX_PORTS as u32 { LOCK.release(); return MACH_MSG_NO_SPACE; }

        // Check port exists
        if port_ref(port_name).is_null() { LOCK.release(); return MACH_MSG_PORT_DIED; }

        set.ports[set.port_count as usize] = port_name;
        set.port_count += 1;

        // Link port to this set
        PORTS[port_name as usize - 1].port_set = set_id;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_set_remove(set_id: u32, port_name: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        let set = &mut PORT_SETS[set_id as usize - 1];
        if !set.in_use { LOCK.release(); return MACH_MSG_INVALID; }

        for i in 0..set.port_count as usize {
            if set.ports[i] == port_name {
                for j in i..set.port_count as usize - 1 {
                    set.ports[j] = set.ports[j + 1];
                }
                set.port_count -= 1;

                if port_name as usize <= MAX_PORTS {
                    PORTS[port_name as usize - 1].port_set = 0;
                }
                LOCK.release();
                return 0;
            }
        }
    }

    LOCK.release();
    MACH_MSG_INVALID
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_set_poll(
    set_id: u32, port_name: *mut u32, timeout_ms: u64,
) -> c_int {
    if port_name.is_null() { return MACH_MSG_INVALID; }

    LOCK.acquire();

    unsafe {
        let set = &PORT_SETS[set_id as usize - 1];
        if !set.in_use { LOCK.release(); return MACH_MSG_INVALID; }

        for i in 0..set.port_count as usize {
            let pid = set.ports[i];
            if pid == 0 { continue; }
            let port = &PORTS[pid as usize - 1];
            if port.msg_count > 0 {
                *port_name = pid;
                LOCK.release();
                return 0;
            }
        }
    }

    LOCK.release();
    MACH_MSG_TIMEOUT
}

// ── Port set destruction ────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_set_destroy(set_id: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        let set = &mut PORT_SETS[set_id as usize - 1];
        if !set.in_use { LOCK.release(); return MACH_MSG_INVALID; }

        // Unlink all ports
        for i in 0..set.port_count as usize {
            let pid = set.ports[i];
            if pid != 0 && pid as usize <= MAX_PORTS {
                PORTS[pid as usize - 1].port_set = 0;
            }
        }

        set.in_use = false;
        set.port_count = 0;
        PORT_SET_COUNT -= 1;
    }

    LOCK.release();
    0
}

// ── Status queries ──────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_status(port_name: u32) -> u32 {
    unsafe {
        let p = port_ref(port_name);
        if p.is_null() { return PORT_STATUS_DESTROYED; }
        (*p).status.load(Ordering::Acquire)
    }
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_port_msg_count(port_name: u32) -> u32 {
    unsafe {
        let p = port_ref(port_name);
        if p.is_null() { return 0; }
        (*p).msg_count
    }
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_stats_ports() -> u32 {
    unsafe { PORT_COUNT }
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_stats_port_sets() -> u32 {
    unsafe { PORT_SET_COUNT }
}

#[no_mangle]
pub extern "C" fn sentraos_ipc_is_init() -> c_int {
    if INIT_DONE.load(Ordering::Acquire) { 1 } else { 0 }
}
