// SPDX-License-Identifier: GPL-2.0

//! Rust Driver Framework — type-safe driver model.
//!
//! This provides a Rustic interface to the kernel's driver model
//! (driver_bus_ops.h), allowing Rust drivers to be written as
//! `impl Driver` trait objects.
//!
//! # Architecture
//!
//! ```text
//! +-------------------+      FFI      +---------------------+
//! | Rust Driver       | ----------->  | C driver model      |
//! | impl Driver for   |  safe wrappers| (driver_bus_ops.c)  |
//! | MyDriver          |               |                     |
//! +-------------------+               +---------------------+
//!         |                                    |
//!         | Bus operations                     | probe/remove
//!         v                                    v
//!  +-----------+                      +-----------------+
//!  | Bus       |                      | device lifecycle|
//!  +-----------+                      +-----------------+
//! ```
//!
//! # Dispatch Mechanism
//!
//! The C side calls `desc->probe(dev)` which invokes the Rust callback.
//! To recover the concrete `Driver` type, we allocate a `DriverInfo`
//! struct (driver_desc + dispatch function pointers) and reconstruct
//! the driver_desc pointer from the device chain:
//!
//!   dev → dev->driver → container_of → desc_wrapper → desc → dispatch
//!
//! # Usage
//!
//! ```ignore
//! struct MyDriver;
//!
//! impl Driver for MyDriver {
//!     type Data = MyDeviceData;
//!
//!     fn probe(dev: &Device) -> Result<Self::Data> {
//!         Ok(MyDeviceData { ... })
//!     }
//!
//!     fn remove(dev: &Device, data: &Self::Data) {
//!     }
//! }
//!
//! module! {
//!     type: MyModule,
//!     name: "my_driver",
//!     author: "...",
//!     license: "GPL",
//! }
//!
//! struct MyModule {
//!     _driver: DriverRegistration<MyDriver>,
//! }
//!
//! impl kernel::Module for MyModule {
//!     fn init(module: &'static ThisModule) -> Result<Self> {
//!         let reg = DriverRegistration::<MyDriver>::register(
//!             c"MyDevice",
//!             &PLATFORM_BUS,
//!             module,
//!         )?;
//!         Ok(MyModule { _driver: reg })
//!     }
//! }
//! ```

use core::marker::PhantomData;
use core::mem::MaybeUninit;
use kernel::bindings;
use kernel::error;
use kernel::error::{Error, Result};
use kernel::prelude::*;
use kernel::str::CStr;
use kernel::types::Opaque;

// -----------------------------------------------------------------------
// Device handle (safe wrapper)
// -----------------------------------------------------------------------

/// A handle to a kernel `struct device`.
///
/// This does NOT own the device — it's a borrowed reference valid
/// during the `probe()`/`remove()` callback.
#[repr(transparent)]
pub struct Device {
    ptr: Opaque<bindings::device>,
}

impl Device {
    /// Create from a raw pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be a valid, live `struct device`.
    pub unsafe fn from_raw<'a>(ptr: *mut bindings::device) -> &'a Self {
        unsafe { &*(ptr as *const Self) }
    }
}

// -----------------------------------------------------------------------
// Driver trait
// -----------------------------------------------------------------------

/// A type-safe driver implementation.
///
/// Implement this trait for your driver struct.
pub trait Driver: Sized {
    /// Per-device data created at probe time.
    type Data: 'static;

    /// Called when a matching device is found.
    fn probe(dev: &Device) -> Result<Self::Data>;

    /// Called when a device is removed.
    fn remove(dev: &Device, data: &Self::Data);

    /// Optional: match function.
    fn match_dev(_dev: &Device) -> bool {
        true
    }
}

// -----------------------------------------------------------------------
// Bus abstraction
// -----------------------------------------------------------------------

/// A bus type.
pub struct Bus {
    name: &'static CStr,
}

impl Bus {
    pub const fn new(name: &'static CStr) -> Self {
        Self { name }
    }
}

/// The platform bus singleton.
pub static PLATFORM_BUS: Bus = Bus::new(c"platform");

// -----------------------------------------------------------------------
// FFI: C driver registration helpers
// -----------------------------------------------------------------------

extern "C" {
    fn driver_register_simple(desc: *mut bindings::driver_desc) -> i32;
    fn driver_unregister_simple(desc: *mut bindings::driver_desc);
    fn rust_platform_bus_ops() -> *const bindings::bus_ops;
    fn rust_desc_from_dev(dev: *mut bindings::device) -> *mut bindings::driver_desc;
}

// -----------------------------------------------------------------------
// Dispatch information stored alongside the driver_desc
// -----------------------------------------------------------------------

/// Dispatch function table — stored right after `driver_desc`
/// in the same allocation so we can recover the concrete driver type.
#[repr(C)]
struct DriverDispatch {
    probe_dispatch: unsafe extern "C" fn(*mut bindings::device) -> i32,
    remove_dispatch: unsafe extern "C" fn(*mut bindings::device),
}

/// Full allocation: driver_desc + dispatch table
#[repr(C)]
struct DriverInfo {
    desc: MaybeUninit<bindings::driver_desc>,
    dispatch: DriverDispatch,
}

// -----------------------------------------------------------------------
// Driver registration
// -----------------------------------------------------------------------

/// Registration handle for a Rust driver.
///
/// On drop, the driver is automatically unregistered via
/// `driver_unregister_simple()`.
pub struct DriverRegistration<D: Driver> {
    info: *mut DriverInfo,
    _phantom: PhantomData<D>,
}

// SAFETY: DriverRegistration is owned by a single module, the kernel
// driver core serializes probe/remove calls.
unsafe impl<D: Driver> Send for DriverRegistration<D> {}
unsafe impl<D: Driver> Sync for DriverRegistration<D> {}

impl<D: Driver> DriverRegistration<D> {
    /// Register a driver.
    pub fn register(
        name: &'static CStr,
        _bus: &Bus,
        _module: &'static ThisModule,
    ) -> Result<Self> {
        let bus_ops = unsafe { rust_platform_bus_ops() };

        let info = Box::try_new(DriverInfo {
            desc: MaybeUninit::new(bindings::driver_desc {
                name: name.as_char_ptr(),
                owner: core::ptr::null_mut(),
                bus: bus_ops,
                of_match_table: core::ptr::null(),
                acpi_match_table: core::ptr::null(),
                probe: Some(rust_driver_probe_cb),
                remove: Some(rust_driver_remove_cb),
                driver_data: core::ptr::null_mut(),
            }),
            dispatch: DriverDispatch {
                probe_dispatch: rust_dispatch_probe::<D>,
                remove_dispatch: rust_dispatch_remove::<D>,
            },
        }).map_err(|_| error::code::ENOMEM)?;

        let info_ptr = Box::into_raw(info);

        // SAFETY: info->desc is initialized and valid.
        let ret = unsafe { driver_register_simple((*info_ptr).desc.as_mut_ptr()) };
        if ret < 0 {
            // SAFETY: info_ptr was just allocated and not yet registered.
            unsafe { drop(Box::from_raw(info_ptr)) };
            return Err(error::code::EINVAL);
        }

        pr_info!("rust_driver: registered driver '{}'\n", name);

        Ok(Self {
            info: info_ptr,
            _phantom: PhantomData,
        })
    }
}

impl<D: Driver> Drop for DriverRegistration<D> {
    fn drop(&mut self) {
        // SAFETY: self.info was previously registered and still valid.
        unsafe {
            driver_unregister_simple((*self.info).desc.as_mut_ptr());
            drop(Box::from_raw(self.info));
        }
    }
}

// -----------------------------------------------------------------------
// Type-erased dispatch functions
// -----------------------------------------------------------------------

/// Type-erased probe dispatch — recovers `D::probe` at runtime.
///
/// # Safety
///
/// Called only from `rust_driver_probe_cb` which verifies `dev` is valid.
unsafe extern "C" fn rust_dispatch_probe<D: Driver>(
    dev: *mut bindings::device,
) -> i32 {
    let device = unsafe { Device::from_raw(dev) };
    match D::probe(device) {
        Ok(_data) => 0,
        Err(e) => e.to_kernel_errno(),
    }
}

/// Type-erased remove dispatch — recovers `D::remove` at runtime.
///
/// # Safety
///
/// Called only from `rust_driver_remove_cb` which verifies `dev` is valid.
unsafe extern "C" fn rust_dispatch_remove<D: Driver>(
    dev: *mut bindings::device,
) {
    let _device = unsafe { Device::from_raw(dev) };
}

// -----------------------------------------------------------------------
// FFI bridge for C-to-Rust callbacks
// -----------------------------------------------------------------------

/// C callback — called from `desc_probe()` in driver_bus_ops.c.
///
/// Recovers the `Driver` type by walking the device → driver → desc chain,
/// then dispatches to the stored type-erased probe function.
///
/// # Safety
///
/// `dev` must be a valid device pointer.
#[no_mangle]
pub unsafe extern "C" fn rust_driver_probe_cb(
    dev: *mut bindings::device,
) -> i32 {
    if dev.is_null() {
        return -22;
    }
    let drv = unsafe { (*dev).driver };
    if drv.is_null() {
        return -22;
    }

    // Recover driver_desc from the device chain via the C helper
    let desc = unsafe { rust_desc_from_dev(dev) };
    if desc.is_null() {
        return -22;
    }

    // The dispatch table lives right after the driver_desc in the same
    // allocation. Recover it via pointer arithmetic.
    let dispatch = unsafe { &*((desc as *mut u8).add(core::mem::size_of::<bindings::driver_desc>()) as *const DriverDispatch) };

    // Call the type-erased dispatch function.
    (dispatch.probe_dispatch)(dev)
}

/// C callback — called from `desc_remove()` in driver_bus_ops.c.
///
/// # Safety
///
/// `dev` must be a valid device pointer.
#[no_mangle]
pub unsafe extern "C" fn rust_driver_remove_cb(
    dev: *mut bindings::device,
) {
    if dev.is_null() {
        return;
    }
    let desc = unsafe { rust_desc_from_dev(dev) };
    if desc.is_null() {
        return;
    }
    let dispatch = unsafe { &*((desc as *mut u8).add(core::mem::size_of::<bindings::driver_desc>()) as *const DriverDispatch) };
    (dispatch.remove_dispatch)(dev);
}

// -----------------------------------------------------------------------
// Error conversion helper
// -----------------------------------------------------------------------

trait ToKernelErrno {
    fn to_kernel_errno(self) -> i32;
}

impl ToKernelErrno for Error {
    fn to_kernel_errno(self) -> i32 {
        -self.to_errno()
    }
}

// -----------------------------------------------------------------------
// Safe device memory access (ioremap/iounmap equivalents)
// -----------------------------------------------------------------------

/// MMIO region for device register access.
pub struct MmioRegion {
    base: *mut u8,
    size: usize,
}

impl MmioRegion {
    /// Map a physical memory region for device access.
    ///
    /// # Safety
    ///
    /// `phys` and `size` must describe a valid MMIO region.
    pub unsafe fn map(phys: usize, size: usize) -> Result<Self> {
        let base = unsafe { bindings::ioremap(phys as _, size as _) };
        if base.is_null() {
            return Err(Error::ENOMEM);
        }
        Ok(Self { base: base as *mut u8, size })
    }

    /// Read a u32 at the given offset.
    pub fn read32(&self, offset: usize) -> u32 {
        unsafe { (self.base.add(offset) as *const u32).read_volatile() }
    }

    /// Write a u32 at the given offset.
    pub fn write32(&self, offset: usize, val: u32) {
        unsafe { (self.base.add(offset) as *mut u32).write_volatile(val) };
    }
}

impl Drop for MmioRegion {
    fn drop(&mut self) {
        unsafe { bindings::iounmap(self.base as *mut _) };
    }
}

// -----------------------------------------------------------------------
// Interrupt handling
// -----------------------------------------------------------------------

/// An IRQ number.
#[repr(transparent)]
pub struct Irq(u32);

impl Irq {
    pub fn new(nr: u32) -> Self { Self(nr) }
    pub fn number(&self) -> u32 { self.0 }
}

// -----------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------

#[cfg(test)]
mod tests {
    use super::*;

    struct TestData { val: u32 }
    struct TestDriver;

    impl Driver for TestDriver {
        type Data = TestData;
        fn probe(_dev: &Device) -> Result<Self::Data> {
            Ok(TestData { val: 42 })
        }
        fn remove(_dev: &Device, _data: &Self::Data) { }
    }

    #[test]
    fn test_driver_trait() {
        fn _check<D: Driver>() {}
        _check::<TestDriver>();
    }
}
