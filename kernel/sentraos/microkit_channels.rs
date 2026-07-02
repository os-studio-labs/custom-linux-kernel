// SPDX-License-Identifier: GPL-2.0

//! SentraOS Microkit Channels — seL4-inspired microkernel IPC.
//!
//! Provides lightweight, capability-controlled communication:
//!   - Endpoints for synchronous IPC (call/wait/reply pattern)
//!   - Notifications for asynchronous event signaling
//!   - Capability-based access control with grant/revoke
//!   - Word-register message passing (fast, fixed-size)
//!   - Mathematically clean seL4-style primitives
//!
//! Like Mach IPC, endpoints and notifications are first-class objects
//! managed by the SentraOS Object Manager.

#![no_std]

use core::ffi::{c_char, c_int, c_uint, c_ulong, c_void};
use core::ptr;
use core::sync::atomic::{AtomicBool, AtomicU32, AtomicU64, Ordering};

// ── Constants ────────────────────────────────────────────

const MAX_ENDPOINTS: usize = 2048;
const MAX_NOTIFICATIONS: usize = 1024;
const MAX_MSG_WORDS: usize = 8;
const MAX_EP_NAME: usize = 48;
const MAX_CALLERS_PER_EP: usize = 64;

// Endpoint status
const EP_STATUS_IDLE: u32 = 0;
const EP_STATUS_WAITING: u32 = 1;
const EP_STATUS_REPLYING: u32 = 2;
const EP_STATUS_DESTROYED: u32 = 3;

// Notification state
const NOTIF_CLEAR: u32 = 0;
const NOTIF_SIGNALED: u32 = 1;

// Capability rights
pub const CAP_SEND: u32 = 0x0001;
pub const CAP_RECEIVE: u32 = 0x0002;
pub const CAP_CALL: u32 = 0x0004;
pub const CAP_REPLY: u32 = 0x0008;
pub const CAP_ALL: u32 = CAP_SEND | CAP_RECEIVE | CAP_CALL | CAP_REPLY;

// Error codes
const CHAN_SUCCESS: c_int = 0;
const CHAN_INVALID: c_int = -22;
const CHAN_NO_MEM: c_int = -12;
const CHAN_DESTROYED: c_int = -32;
const CHAN_TIMEOUT: c_int = -110;
const CHAN_BUSY: c_int = -16;
const CHAN_NO_CALLER: c_int = -61;
const CHAN_DENIED: c_int = -13;

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

// ── Capability entry ────────────────────────────────────

#[repr(C)]
#[derive(Clone, Copy)]
struct CapEntry {
    rights: u32,
    pid: u32,
}

// ── Caller state (waiting for reply) ────────────────────

#[repr(C)]
#[derive(Clone, Copy)]
struct CallerState {
    active: bool,
    caller_pid: u32,
    msg: [u64; MAX_MSG_WORDS],
    msg_words: u64,
}

// ── Endpoint structure (seL4-style) ─────────────────────

#[repr(C)]
struct Endpoint {
    in_use: AtomicBool,
    name: [u8; MAX_EP_NAME],
    status: AtomicU32,
    flags: u32,
    om_obj_id: u32,
    owner_pid: u32,

    // Capability table
    caps: [CapEntry; 64],
    cap_count: u32,

    // Caller tracking (for synchronous call/reply)
    callers: [CallerState; MAX_CALLERS_PER_EP],
    caller_count: u32,

    // Waiting message (for recv when someone already called)
    pending_msg: [u64; MAX_MSG_WORDS],
    pending_words: u64,
    pending_valid: bool,
    pending_caller_pid: u32,

    // Endpoint data
    data: *mut c_void,
    data_size: u64,
}

// ── Notification structure (seL4-style) ─────────────────

#[repr(C)]
struct Notification {
    in_use: AtomicBool,
    name: [u8; MAX_EP_NAME],
    state: AtomicU32,
    flags: u32,
    om_obj_id: u32,
    owner_pid: u32,

    // Capability table
    caps: [CapEntry; 64],
    cap_count: u32,
}

// ── Global state ────────────────────────────────────────

static LOCK: TicketLock = TicketLock::new();
static INIT_DONE: AtomicBool = AtomicBool::new(false);

static mut ENDPOINTS: [Endpoint; MAX_ENDPOINTS] = unsafe { core::mem::zeroed() };
static mut NOTIFICATIONS: [Notification; MAX_NOTIFICATIONS] = unsafe { core::mem::zeroed() };
static mut EP_COUNT: u32 = 0;
static mut NOTIF_COUNT: u32 = 0;

// ── Object Manager FFI ──────────────────────────────────

extern "C" {
    fn sentraos_om_init() -> c_int;
    fn sentraos_om_is_init() -> c_int;
    fn sentraos_om_create_object(
        name: *const c_char, type_id: u32, default_access: u32,
        data: *mut c_void, data_size: u64,
    ) -> u32;
    fn sentraos_om_delete_object(obj_id: u32) -> c_int;
    fn sentraos_om_set_data(obj_id: u32, data: *mut c_void, data_size: u64) -> c_int;
}

// ── Internal helpers ────────────────────────────────────

unsafe fn alloc_endpoint() -> u32 {
    for i in 0..MAX_ENDPOINTS {
        if !ENDPOINTS[i].in_use.load(Ordering::Acquire) {
            ENDPOINTS[i].in_use.store(true, Ordering::Release);
            ENDPOINTS[i].status.store(EP_STATUS_IDLE, Ordering::Release);
            ENDPOINTS[i].cap_count = 0;
            ENDPOINTS[i].caller_count = 0;
            ENDPOINTS[i].pending_valid = false;
            ENDPOINTS[i].pending_words = 0;
            ENDPOINTS[i].data = ptr::null_mut();
            ENDPOINTS[i].data_size = 0;
            ENDPOINTS[i].om_obj_id = 0;
            ENDPOINTS[i].flags = 0;
            EP_COUNT += 1;
            return (i + 1) as u32;
        }
    }
    0
}

unsafe fn alloc_notification() -> u32 {
    for i in 0..MAX_NOTIFICATIONS {
        if !NOTIFICATIONS[i].in_use.load(Ordering::Acquire) {
            NOTIFICATIONS[i].in_use.store(true, Ordering::Release);
            NOTIFICATIONS[i].state.store(NOTIF_CLEAR, Ordering::Release);
            NOTIFICATIONS[i].cap_count = 0;
            NOTIFICATIONS[i].om_obj_id = 0;
            NOTIFICATIONS[i].flags = 0;
            NOTIF_COUNT += 1;
            return (i + 1) as u32;
        }
    }
    0
}

unsafe fn ep_ref(ep_id: u32) -> *mut Endpoint {
    if ep_id == 0 || ep_id as usize > MAX_ENDPOINTS { return ptr::null_mut(); }
    let ep = &mut ENDPOINTS[ep_id as usize - 1];
    if !ep.in_use.load(Ordering::Acquire) { return ptr::null_mut(); }
    ep
}

unsafe fn notif_ref(notif_id: u32) -> *mut Notification {
    if notif_id == 0 || notif_id as usize > MAX_NOTIFICATIONS { return ptr::null_mut(); }
    let n = &mut NOTIFICATIONS[notif_id as usize - 1];
    if !n.in_use.load(Ordering::Acquire) { return ptr::null_mut(); }
    n
}

fn name_from_c(dst: &mut [u8], src: *const c_char) {
    if src.is_null() { return; }
    let max = if dst.len() < MAX_EP_NAME { dst.len() } else { MAX_EP_NAME };
    unsafe {
        for i in 0..max - 1 {
            let c = *src.add(i) as u8;
            dst[i] = c;
            if c == 0 { break; }
        }
        dst[max - 1] = 0;
    }
}

unsafe fn check_ep_cap(ep_id: u32, rights: u32, pid: u32) -> bool {
    let ep = &ENDPOINTS[ep_id as usize - 1];
    for i in 0..ep.cap_count as usize {
        if ep.caps[i].pid == pid && (ep.caps[i].rights & rights) == rights {
            return true;
        }
    }
    false
}

unsafe fn check_notif_cap(notif_id: u32, rights: u32, pid: u32) -> bool {
    let n = &NOTIFICATIONS[notif_id as usize - 1];
    for i in 0..n.cap_count as usize {
        if n.caps[i].pid == pid && (n.caps[i].rights & rights) == rights {
            return true;
        }
    }
    false
}

// ── Initialization ──────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_chan_init() -> c_int {
    if INIT_DONE.load(Ordering::Acquire) { return 0; }

    LOCK.acquire();

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

// ── Endpoint lifecycle ──────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_chan_endpoint_create(
    name: *const c_char, ep_name: *mut u32,
) -> c_int {
    if ep_name.is_null() || !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    let ep_id = unsafe { alloc_endpoint() };
    if ep_id == 0 { LOCK.release(); return CHAN_NO_MEM; }

    unsafe {
        let ep = &mut ENDPOINTS[ep_id as usize - 1];
        name_from_c(&mut ep.name, name);
        ep.owner_pid = 0;

        // Register with Object Manager
        let om_id = sentraos_om_create_object(name, 9, CAP_ALL, ptr::null_mut(), 0);
        if om_id != 0 {
            ep.om_obj_id = om_id;
            sentraos_om_set_data(om_id, &mut ENDPOINTS[ep_id as usize - 1] as *mut _ as *mut c_void, 0);

            // Grant all caps to creator
            if ep.cap_count < 64 {
                ep.caps[ep.cap_count as usize] = CapEntry { rights: CAP_ALL, pid: 0 };
                ep.cap_count += 1;
            }
        }

        *ep_name = ep_id;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_endpoint_delete(ep_name: u32) -> c_int {
    if ep_name == 0 || !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    unsafe {
        if ep_ref(ep_name).is_null() { LOCK.release(); return CHAN_DESTROYED; }

        let ep = &mut ENDPOINTS[ep_name as usize - 1];

        // Clean up OM object
        if ep.om_obj_id != 0 {
            sentraos_om_delete_object(ep.om_obj_id);
        }

        // Free endpoint data
        if !ep.data.is_null() {
            kfree(ep.data);
            ep.data = ptr::null_mut();
        }

        ep.in_use.store(false, Ordering::Release);
        ep.status.store(EP_STATUS_DESTROYED, Ordering::Release);
        EP_COUNT -= 1;
    }

    LOCK.release();
    0
}

// ── Synchronous IPC: Call / Wait / Reply ────────────────

#[no_mangle]
pub extern "C" fn sentraos_chan_call(
    ep_name: u32, msg: *const u64, msg_words: u64,
    reply: *mut u64, reply_words: *mut u64,
) -> c_int {
    if msg.is_null() || reply.is_null() || reply_words.is_null() {
        return CHAN_INVALID;
    }
    if msg_words > MAX_MSG_WORDS as u64 { return CHAN_INVALID; }
    if !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    unsafe {
        let ep = ep_ref(ep_name);
        if ep.is_null() { LOCK.release(); return CHAN_DESTROYED; }

        // Check CALL capability
        if !check_ep_cap(ep_name, CAP_CALL, 0) {
            LOCK.release(); return CHAN_DENIED;
        }

        // Store message for the receiver
        for i in 0..msg_words as usize {
            ENDPOINTS[ep_name as usize - 1].pending_msg[i] = *msg.add(i);
        }
        ENDPOINTS[ep_name as usize - 1].pending_words = msg_words;
        ENDPOINTS[ep_name as usize - 1].pending_valid = true;
        ENDPOINTS[ep_name as usize - 1].pending_caller_pid = 0;
        ENDPOINTS[ep_name as usize - 1].status.store(EP_STATUS_WAITING, Ordering::Release);

        // In a full implementation, this would block and wait for reply.
        // For now, the caller registers as waiting and returns immediately.
        // The actual reply dispatch would be driven by an external event loop.

        // Register as a caller waiting for reply
        let ep = &mut ENDPOINTS[ep_name as usize - 1];
        if ep.caller_count < MAX_CALLERS_PER_EP as u32 {
            let idx = ep.caller_count as usize;
            ep.callers[idx] = CallerState {
                active: true,
                caller_pid: 0,
                msg: [0u64; MAX_MSG_WORDS],
                msg_words: 0,
            };
            for i in 0..msg_words as usize {
                ep.callers[idx].msg[i] = *msg.add(i);
            }
            ep.callers[idx].msg_words = msg_words;
            ep.caller_count += 1;
        }
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_reply(
    ep_name: u32, reply_data: *const u64, reply_words: u64,
) -> c_int {
    if reply_data.is_null() || reply_words > MAX_MSG_WORDS as u64 {
        return CHAN_INVALID;
    }
    if !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    unsafe {
        let ep = ep_ref(ep_name);
        if ep.is_null() { LOCK.release(); return CHAN_DESTROYED; }

        // Check REPLY capability
        if !check_ep_cap(ep_name, CAP_REPLY, 0) {
            LOCK.release(); return CHAN_DENIED;
        }

        // In a full implementation, this would wake up the waiting caller.
        // For now, we clear the pending flag and store reply data.

        ENDPOINTS[ep_name as usize - 1].pending_valid = false;
        ENDPOINTS[ep_name as usize - 1].status.store(EP_STATUS_REPLYING, Ordering::Release);

        // Remove first waiting caller
        let ep = &mut ENDPOINTS[ep_name as usize - 1];
        if ep.caller_count > 0 {
            for j in 0..ep.caller_count as usize - 1 {
                ep.callers[j] = ep.callers[j + 1];
            }
            ep.caller_count -= 1;
        }

        if ep.caller_count == 0 {
            ep.status.store(EP_STATUS_IDLE, Ordering::Release);
        }
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_wait(
    ep_name: u32, msg: *mut u64, msg_words: *mut u64, timeout_ms: u64,
) -> c_int {
    if msg.is_null() || msg_words.is_null() { return CHAN_INVALID; }
    if !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    unsafe {
        let ep = ep_ref(ep_name);
        if ep.is_null() { LOCK.release(); return CHAN_DESTROYED; }

        // Check RECEIVE capability
        if !check_ep_cap(ep_name, CAP_RECEIVE, 0) {
            LOCK.release(); return CHAN_DENIED;
        }

        let ep = &ENDPOINTS[ep_name as usize - 1];

        if ep.pending_valid {
            let copy_words = if ep.pending_words < *msg_words { ep.pending_words } else { *msg_words };
            for i in 0..copy_words as usize {
                *msg.add(i) = ep.pending_msg[i];
            }
            *msg_words = ep.pending_words;
        }

        if !ep.pending_valid {
            LOCK.release();
            return CHAN_TIMEOUT;
        }
    }

    LOCK.release();
    0
}

// ── Notification operations ─────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_chan_notification_create(
    name: *const c_char, notif_name: *mut u32,
) -> c_int {
    if notif_name.is_null() || !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    let nid = unsafe { alloc_notification() };
    if nid == 0 { LOCK.release(); return CHAN_NO_MEM; }

    unsafe {
        let n = &mut NOTIFICATIONS[nid as usize - 1];
        name_from_c(&mut n.name, name);
        n.owner_pid = 0;

        let om_id = sentraos_om_create_object(name, 10, CAP_SEND | CAP_RECEIVE, ptr::null_mut(), 0);
        if om_id != 0 {
            n.om_obj_id = om_id;
            if n.cap_count < 64 {
                n.caps[n.cap_count as usize] = CapEntry { rights: CAP_SEND | CAP_RECEIVE, pid: 0 };
                n.cap_count += 1;
            }
        }

        *notif_name = nid;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_notification_delete(notif_name: u32) -> c_int {
    if notif_name == 0 || !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    unsafe {
        if notif_ref(notif_name).is_null() { LOCK.release(); return CHAN_DESTROYED; }

        let n = &mut NOTIFICATIONS[notif_name as usize - 1];
        if n.om_obj_id != 0 {
            sentraos_om_delete_object(n.om_obj_id);
        }

        n.in_use.store(false, Ordering::Release);
        n.state.store(NOTIF_CLEAR, Ordering::Release);
        NOTIF_COUNT -= 1;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_notification_signal(notif_name: u32) -> c_int {
    if !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    unsafe {
        if notif_ref(notif_name).is_null() { LOCK.release(); return CHAN_DESTROYED; }

        if !check_notif_cap(notif_name, CAP_SEND, 0) {
            LOCK.release(); return CHAN_DENIED;
        }

        NOTIFICATIONS[notif_name as usize - 1].state.store(NOTIF_SIGNALED, Ordering::Release);
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_notification_wait(
    notif_name: u32, timeout_ms: u64,
) -> c_int {
    if !INIT_DONE.load(Ordering::Acquire) { return CHAN_INVALID; }

    LOCK.acquire();

    unsafe {
        if notif_ref(notif_name).is_null() { LOCK.release(); return CHAN_DESTROYED; }

        if !check_notif_cap(notif_name, CAP_RECEIVE, 0) {
            LOCK.release(); return CHAN_DENIED;
        }

        let n = &NOTIFICATIONS[notif_name as usize - 1];
        if n.state.load(Ordering::Acquire) == NOTIF_SIGNALED {
            // Clear and return success
            NOTIFICATIONS[notif_name as usize - 1].state.store(NOTIF_CLEAR, Ordering::Release);
            LOCK.release();
            return 0;
        }
    }

    LOCK.release();
    CHAN_TIMEOUT
}

#[no_mangle]
pub extern "C" fn sentraos_chan_notification_poll(notif_name: u32) -> c_int {
    if !INIT_DONE.load(Ordering::Acquire) { return 0; }

    unsafe {
        if notif_ref(notif_name).is_null() { return 0; }

        if NOTIFICATIONS[notif_name as usize - 1].state.load(Ordering::Acquire) == NOTIF_SIGNALED {
            return 1;
        }
    }
    0
}

// ── Capability management ───────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_chan_grant_ep_cap(
    ep_name: u32, target_pid: u32, rights: u32,
) -> c_int {
    LOCK.acquire();

    unsafe {
        let ep = ep_ref(ep_name);
        if ep.is_null() { LOCK.release(); return CHAN_DESTROYED; }

        if ENDPOINTS[ep_name as usize - 1].cap_count >= 64 {
            LOCK.release(); return CHAN_NO_MEM;
        }

        let idx = ENDPOINTS[ep_name as usize - 1].cap_count as usize;
        ENDPOINTS[ep_name as usize - 1].caps[idx] = CapEntry { rights, pid: target_pid };
        ENDPOINTS[ep_name as usize - 1].cap_count += 1;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_revoke_ep_cap(ep_name: u32, target_pid: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        if ep_ref(ep_name).is_null() { LOCK.release(); return CHAN_DESTROYED; }

        let ep = &mut ENDPOINTS[ep_name as usize - 1];
        let mut i = 0;
        while i < ep.cap_count as usize {
            if ep.caps[i].pid == target_pid {
                for j in i..ep.cap_count as usize - 1 {
                    ep.caps[j] = ep.caps[j + 1];
                }
                ep.cap_count -= 1;
            } else {
                i += 1;
            }
        }
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_grant_notif_cap(
    notif_name: u32, target_pid: u32, rights: u32,
) -> c_int {
    LOCK.acquire();

    unsafe {
        if notif_ref(notif_name).is_null() { LOCK.release(); return CHAN_DESTROYED; }

        if NOTIFICATIONS[notif_name as usize - 1].cap_count >= 64 {
            LOCK.release(); return CHAN_NO_MEM;
        }

        let idx = NOTIFICATIONS[notif_name as usize - 1].cap_count as usize;
        NOTIFICATIONS[notif_name as usize - 1].caps[idx] = CapEntry { rights, pid: target_pid };
        NOTIFICATIONS[notif_name as usize - 1].cap_count += 1;
    }

    LOCK.release();
    0
}

#[no_mangle]
pub extern "C" fn sentraos_chan_revoke_notif_cap(notif_name: u32, target_pid: u32) -> c_int {
    LOCK.acquire();

    unsafe {
        if notif_ref(notif_name).is_null() { LOCK.release(); return CHAN_DESTROYED; }

        let n = &mut NOTIFICATIONS[notif_name as usize - 1];
        let mut i = 0;
        while i < n.cap_count as usize {
            if n.caps[i].pid == target_pid {
                for j in i..n.cap_count as usize - 1 {
                    n.caps[j] = n.caps[j + 1];
                }
                n.cap_count -= 1;
            } else {
                i += 1;
            }
        }
    }

    LOCK.release();
    0
}

// ── Status queries ──────────────────────────────────────

#[no_mangle]
pub extern "C" fn sentraos_chan_ep_status(ep_name: u32) -> u32 {
    unsafe {
        let ep = ep_ref(ep_name);
        if ep.is_null() { return EP_STATUS_DESTROYED; }
        (*ep).status.load(Ordering::Acquire)
    }
}

#[no_mangle]
pub extern "C" fn sentraos_chan_ep_caller_count(ep_name: u32) -> u32 {
    unsafe {
        let ep = ep_ref(ep_name);
        if ep.is_null() { return 0; }
        (*ep).caller_count
    }
}

#[no_mangle]
pub extern "C" fn sentraos_chan_notif_state(notif_name: u32) -> u32 {
    unsafe {
        let n = notif_ref(notif_name);
        if n.is_null() { return 0; }
        (*n).state.load(Ordering::Acquire)
    }
}

#[no_mangle]
pub extern "C" fn sentraos_chan_stats_endpoints() -> u32 {
    unsafe { EP_COUNT }
}

#[no_mangle]
pub extern "C" fn sentraos_chan_stats_notifications() -> u32 {
    unsafe { NOTIF_COUNT }
}

#[no_mangle]
pub extern "C" fn sentraos_chan_is_init() -> c_int {
    if INIT_DONE.load(Ordering::Acquire) { 1 } else { 0 }
}
