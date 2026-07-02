// SPDX-License-Identifier: GPL-2.0

//! Safe DMA mapping wrappers for any driver subsystem.
//!
//! Every `struct dma_safe_map` records the owning device, direction,
//! and length so that unmapping is always correct.  The `devm_`
//! variant registers a devres callback so unmap happens automatically
//! on driver unbind.

#![no_std]

use core::ffi::{c_int, c_uint, c_ulong, c_void};
use core::ptr;

extern "C" {
    fn dma_map_single(dev: *mut c_void, cpu_addr: *mut c_void,
                      size: c_ulong, dir: c_int) -> c_ulong;
    fn dma_mapping_error(dev: *mut c_void, dma_addr: c_ulong) -> c_int;
    fn dma_unmap_single(dev: *mut c_void, dma_addr: c_ulong,
                        size: c_ulong, dir: c_int);
    fn devm_add_action(dev: *mut c_void,
                       action: extern "C" fn(*mut c_void),
                       data: *mut c_void) -> c_int;
    fn kzalloc(size: c_ulong, flags: c_uint) -> *mut c_void;
    fn kfree(ptr: *mut c_void);
}

const GFP_KERNEL: c_uint = 0xCC0u32;

#[repr(C)]
pub struct DmaSafeMap {
    dev: *mut c_void,
    dma_addr: c_ulong,
    len: c_ulong,
    dir: c_int,
    mapped: c_int,
}

extern "C" fn dma_safe_devres_release(data: *mut c_void) {
    if data.is_null() {
        return;
    }
    let map = data as *mut DmaSafeMap;
    unsafe {
        if (*map).mapped != 0 {
            dma_unmap_single((*map).dev, (*map).dma_addr,
                             (*map).len, (*map).dir);
        }
        kfree(data);
    }
}

#[no_mangle]
pub extern "C" fn rust_dma_map_area(
    dev: *mut c_void,
    cpu_addr: *mut c_void,
    len: c_ulong,
    dir: c_int,
) -> *mut DmaSafeMap {
    if dev.is_null() || cpu_addr.is_null() || len == 0 {
        return ptr::null_mut();
    }

    let map = unsafe { kzalloc(core::mem::size_of::<DmaSafeMap>() as c_ulong, GFP_KERNEL) };
    if map.is_null() {
        return ptr::null_mut();
    }

    let dma_addr = unsafe { dma_map_single(dev, cpu_addr, len, dir) };
    if unsafe { dma_mapping_error(dev, dma_addr) } != 0 {
        unsafe { kfree(map) };
        return ptr::null_mut();
    }

    let h = map as *mut DmaSafeMap;
    unsafe {
        (*h).dev = dev;
        (*h).dma_addr = dma_addr;
        (*h).len = len;
        (*h).dir = dir;
        (*h).mapped = 1;
    }
    h
}

#[no_mangle]
pub extern "C" fn rust_dma_unmap(map: *mut DmaSafeMap) {
    if map.is_null() {
        return;
    }
    unsafe {
        if (*map).mapped != 0 {
            dma_unmap_single((*map).dev, (*map).dma_addr,
                             (*map).len, (*map).dir);
            (*map).mapped = 0;
        }
        kfree(map);
    }
}

#[no_mangle]
pub extern "C" fn rust_devm_dma_map_area(
    dev: *mut c_void,
    cpu_addr: *mut c_void,
    len: c_ulong,
    dir: c_int,
) -> *mut DmaSafeMap {
    let map = rust_dma_map_area(dev, cpu_addr, len, dir);
    if map.is_null() {
        return ptr::null_mut();
    }

    let ret = unsafe {
        devm_add_action(dev, dma_safe_devres_release, map as *mut c_void)
    };
    if ret < 0 {
        rust_dma_unmap(map);
        return ptr::null_mut();
    }
    map
}

// ── Accessors for C callers ──────────────────────────────────

#[no_mangle]
pub extern "C" fn dma_safe_map_addr(map: *mut DmaSafeMap) -> c_ulong {
    if map.is_null() { 0 } else { unsafe { (*map).dma_addr } }
}

#[no_mangle]
pub extern "C" fn dma_safe_map_len(map: *mut DmaSafeMap) -> c_ulong {
    if map.is_null() { 0 } else { unsafe { (*map).len } }
}
