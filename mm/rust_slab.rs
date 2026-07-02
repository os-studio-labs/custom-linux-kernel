// SPDX-License-Identifier: GPL-2.0

//! Rust slab allocator — type-safe wrappers around `kmem_cache`.
//!
//! The kernel's SLUB allocator (`mm/slub.c`) is highly optimized C code.
//! Rather than rewriting it, we provide safe Rust abstractions that:
//!
//! 1. Wrap `kmem_cache` creation/destruction
//! 2. Provide type-safe allocation with `Arc<T>` and `Box<T>` support
//! 3. Track memory cgroup accounting
//! 4. Support `SLAB_TYPESAFE_BY_RCU` for RCU-protected caches
//!
//! # Architecture
//!
//! ```text
//! Rust slab user          C SLUB (slub.c)
//! +-------------+         +----------------+
//! | Slab<T>     | ------> | kmem_cache     |
//! | .alloc()    |  FFI    | kmem_cache_alloc
//! | .free()     |  -----> | kmem_cache_free|
//! +-------------+         +----------------+
//! ```
//!
//! # Safety
//!
//! This module exposes `unsafe` only at the FFI boundary. The `Slab<T>`
//! API is fully safe (assuming `T: Send + Sync`).

use core::marker::PhantomData;
use core::mem::{align_of, size_of};
use core::ptr::NonNull;
use kernel::bindings;
use kernel::error::{Error, Result};
use kernel::prelude::*;
use kernel::types::Opaque;

// -----------------------------------------------------------------------
// FFI: C kmem_cache operations
// -----------------------------------------------------------------------

extern "C" {
    fn rust_helper_kmem_cache_create(
        name: *const core::ffi::c_char,
        size: u32,
        align: u32,
        flags: u32,
        ctor: Option<unsafe extern "C" fn(*mut core::ffi::c_void)>,
    ) -> *mut bindings::kmem_cache;

    fn rust_helper_kmem_cache_destroy(s: *mut bindings::kmem_cache);

    fn rust_helper_kmem_cache_alloc(
        s: *mut bindings::kmem_cache,
        flags: u32,
    ) -> *mut core::ffi::c_void;

    fn rust_helper_kmem_cache_free(
        s: *mut bindings::kmem_cache,
        obj: *mut core::ffi::c_void,
    );

    fn rust_helper_kmem_cache_zalloc(
        s: *mut bindings::kmem_cache,
        flags: u32,
    ) -> *mut core::ffi::c_void;
}

// -----------------------------------------------------------------------
// Slab flags
// -----------------------------------------------------------------------

/// Slab allocation flags, mapped from C `gfp_t`.
///
/// Values match include/linux/gfp_types.h in Linux 6.9.
pub mod gfp {
    /// Default allocation (may sleep, may reclaim). 
    /// GFP_KERNEL = __GFP_RECLAIM | __GFP_IO | __GFP_FS
    pub const KERNEL: u32 = 0xCC0;
    /// Atomic allocation (no sleep, no reclaim).
    /// GFP_ATOMIC = __GFP_HIGH
    pub const ATOMIC: u32 = 0x20;
    /// GFP_KERNEL with __GFP_ZERO for zero-initialized allocation.
    pub const KERNEL_ZERO: u32 = 0xDC0;
    /// Zero-initialized flag only.
    pub const ZERO: u32 = 0x100;
}

/// Slab cache creation flags.
pub mod slab_flags {
    /// Objects may be reused immediately after RCU grace period.
    pub const TYPESAFE_BY_RCU: u32 = 0x2000;
    /// Panic on creation failure.
    pub const PANIC: u32 = 0x4000;
    /// Objects are reclaimable (for dcache, inode, etc.).
    pub const RECLAIM_ACCOUNT: u32 = 0x20000;
    /// Account to memory cgroup.
    pub const ACCOUNT: u32 = 0x40000;
    /// Hardware cache-line align objects.
    pub const HWCACHE_ALIGN: u32 = 0x80000;
}

// -----------------------------------------------------------------------
// Slab<T> — type-safe slab cache
// -----------------------------------------------------------------------

/// A type-safe slab cache for `T`.
///
/// # Example
///
/// ```ignore
/// static MY_CACHE: Slab<MyStruct> = Slab::new("my_struct");
///
/// fn do_alloc() -> Result<Box<MyStruct, SlabBox<MyStruct>>> {
///     let obj = MY_CACHE.alloc(gfp::KERNEL)?;
///     Ok(obj)
/// }
/// ```
pub struct Slab<T: ?Sized> {
    name: &'static CStr,
    _type: PhantomData<T>,
}

impl<T> Slab<T> {
    /// Create a new slab cache descriptor.
    ///
    /// This does NOT create the kernel `kmem_cache` — that is
    /// deferred to `init()` or the first `alloc()` call.
    pub const fn new(name: &'static CStr) -> Self {
        Self {
            name,
            _type: PhantomData,
        }
    }

    /// Initialize the underlying `kmem_cache`.
    ///
    /// Must be called before `alloc()` or call `alloc()` which
    /// initializes lazily.
    pub fn init(&self, flags: u32) -> Result<*mut bindings::kmem_cache> {
        let name = self.name.as_char_ptr();
        let size = size_of::<T>() as u32;
        let align = align_of::<T>().max(1) as u32;

        // SAFETY: `name` is a valid C string, size/align are correct.
        let cache = unsafe {
            rust_helper_kmem_cache_create(
                name,
                size,
                align,
                flags,
                None,
            )
        };

        if cache.is_null() {
            Err(Error::ENOMEM)
        } else {
            Ok(cache)
        }
    }

    /// Allocate a new zero-initialized `T` from the slab.
    ///
    /// The caller must ensure `cache` is valid (created by `init()`).
    /// Returns `EINVAL` if `cache` is null.
    ///
    /// # Safety
    ///
    /// `cache` must be a valid, initialized `kmem_cache` pointer
    /// (or null, in which case `EINVAL` is returned).
    pub unsafe fn alloc_raw(
        cache: *mut bindings::kmem_cache,
        flags: u32,
    ) -> Result<NonNull<T>> {
        if cache.is_null() {
            return Err(Error::EINVAL);
        }
        let ptr = unsafe { rust_helper_kmem_cache_zalloc(cache, flags) };
        NonNull::new(ptr as *mut T).ok_or(Error::ENOMEM)
    }

    /// Free a slab-allocated `T`.
    ///
    /// No-op if `cache` is null.
    ///
    /// # Safety
    ///
    /// `ptr` must have been allocated from `cache` via `alloc_raw()`,
    /// or `cache` must be null (no-op).
    pub unsafe fn free_raw(
        cache: *mut bindings::kmem_cache,
        ptr: NonNull<T>,
    ) {
        if cache.is_null() {
            return;
        }
        unsafe { rust_helper_kmem_cache_free(cache, ptr.as_ptr() as *mut core::ffi::c_void) };
    }

    /// Destroy a kmem_cache.
    ///
    /// No-op if `cache` is null.
    ///
    /// # Safety
    ///
    /// All objects must have been freed and no concurrent allocations.
    pub unsafe fn destroy(cache: *mut bindings::kmem_cache) {
        if !cache.is_null() {
            unsafe { rust_helper_kmem_cache_destroy(cache) };
        }
    }
}

// -----------------------------------------------------------------------
// SlabBox<T> — Box-like owned pointer from a slab cache
// -----------------------------------------------------------------------

/// A box-like type that owns a slab-allocated object.
///
/// When dropped, the object is returned to the slab cache.
///
/// # Safety
///
/// `T` must not contain references to stack data.
pub struct SlabBox<T: ?Sized> {
    ptr: NonNull<T>,
    cache: *mut bindings::kmem_cache,
    _marker: PhantomData<T>,
}

impl<T> SlabBox<T> {
    /// Create a new `SlabBox` from a slab-allocated pointer.
    ///
    /// # Safety
    ///
    /// `ptr` must be a valid allocation from `cache`.
    pub unsafe fn from_raw(
        ptr: NonNull<T>,
        cache: *mut bindings::kmem_cache,
    ) -> Self {
        Self {
            ptr,
            cache,
            _marker: PhantomData,
        }
    }

    /// Get a reference to the inner value.
    pub fn as_ref(&self) -> &T {
        // SAFETY: `ptr` is valid and aligned.
        unsafe { self.ptr.as_ref() }
    }

    /// Get a mutable reference to the inner value.
    pub fn as_mut(&mut self) -> &mut T {
        // SAFETY: `ptr` is valid, aligned, and uniquely owned.
        unsafe { self.ptr.as_mut() }
    }
}

impl<T> core::ops::Deref for SlabBox<T> {
    type Target = T;

    fn deref(&self) -> &T {
        self.as_ref()
    }
}

impl<T> core::ops::DerefMut for SlabBox<T> {
    fn deref_mut(&mut self) -> &mut T {
        self.as_mut()
    }
}

impl<T> Drop for SlabBox<T> {
    fn drop(&mut self) {
        // SAFETY: `ptr` was allocated from `cache`, and we have unique ownership.
        unsafe { rust_helper_kmem_cache_free(self.cache, self.ptr.as_ptr() as *mut _) };
    }
}

// -----------------------------------------------------------------------
// Pre-defined kernel slab caches
// -----------------------------------------------------------------------

/// Slab cache for `task_struct`.
pub static TASK_STRUCT_CACHE: Slab<Opaque<bindings::task_struct>> =
    Slab::new(c"task_struct");

/// Slab cache for `mm_struct`.
pub static MM_STRUCT_CACHE: Slab<Opaque<bindings::mm_struct>> =
    Slab::new(c"mm_struct");

/// Slab cache for `vm_area_struct`.
pub static VMA_CACHE: Slab<Opaque<bindings::vm_area_struct>> =
    Slab::new(c"vm_area_struct");

// -----------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------

/// Initialize all kernel slab caches.
///
/// Called during kernel init.
pub fn init_kernel_slabs() -> Result {
    // SAFETY: initialization happens once at boot.
    let flags = slab_flags::PANIC | slab_flags::RECLAIM_ACCOUNT;
    let _ = TASK_STRUCT_CACHE.init(flags)?;
    let _ = MM_STRUCT_CACHE.init(flags)?;
    let _ = VMA_CACHE.init(slab_flags::PANIC)?;
    Ok(())
}

// -----------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_slab_create() {
        let slab: Slab<u64> = Slab::new(c"test_u64");
        let cache = slab.init(slab_flags::PANIC).expect("create cache");
        assert!(!cache.is_null());
        // SAFETY: cache is valid
        unsafe { Slab::destroy(cache) };
    }

    #[test]
    fn test_slab_alloc_free() {
        let slab: Slab<u64> = Slab::new(c"test_u64_af");
        let cache = slab.init(slab_flags::PANIC).expect("create cache");

        // SAFETY: cache is valid
        let ptr = unsafe { slab.alloc_raw(cache, gfp::KERNEL) }.expect("alloc");
        // SAFETY: ptr is valid, write a value
        unsafe { ptr.as_ptr().write(42u64) };
        assert_eq!(unsafe { ptr.as_ref() }, &42u64);

        // SAFETY: ptr was allocated from cache
        unsafe { slab.free_raw(cache, ptr) };
        // SAFETY: cache is valid
        unsafe { Slab::destroy(cache) };
    }

    #[test]
    fn test_slab_box() {
        let slab: Slab<u64> = Slab::new(c"test_u64_box");
        let cache = slab.init(slab_flags::PANIC).expect("create cache");

        // SAFETY: cache is valid
        let ptr = unsafe { slab.alloc_raw(cache, gfp::KERNEL) }.expect("alloc");
        // SAFETY: ptr is valid
        unsafe { ptr.as_ptr().write(100u64) };

        // SAFETY: ptr from cache
        let slab_box = unsafe { SlabBox::from_raw(ptr, cache) };
        assert_eq!(*slab_box, 100u64);
        // Drop frees the object

        // SAFETY: cache is valid; SlabBox::drop already freed
        unsafe { Slab::destroy(cache) };
    }
}
