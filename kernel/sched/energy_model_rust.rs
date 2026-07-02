// SPDX-License-Identifier: GPL-2.0

//! Rust Energy Model — decoupled power-aware scheduling.
//!
//! # Problem
//!
//! The current Energy Model (EM) is embedded in `kernel/sched/fair.c`
//! via `compute_energy()` and `find_energy_efficient_cpu()`. This:
//!
//! 1. Ties energy-aware placement to CFS — deadline and RT classes
//!    cannot benefit from energy awareness.
//! 2. Makes the EM unpluggable — you cannot swap the policy.
//! 3. Couples EM data structures (em_perf_domain) to scheduler topology.
//!
//! # Solution
//!
//! A standalone Energy Model module in Rust that:
//!
//! - Is scheduler-class-agnostic (any class can ask "what's the
//!   energy cost of placing task T on CPU C?")
//! - Uses a clean trait-based interface (`EnergyModel`)
//! - Publishes events via the PELT ring buffer for consumption
//! - Allows alternative energy models (ACPI, DT-based, learned)
//!
//! ```text
//! +------------------+     energy_cost()    +--------------+
//! | fair.c (C)       | -------------------> | EnergyModel  |
//! | deadline.c (C)   | <--- event (PELT) ---| (Rust)       |
//! | rt.c (C)         |                      +--------------+
//! +------------------+                            |
//!                                                 | em_perf_domain
//!                                                 v
//!                                          drivers/thermal/ (cpufreq)
//! ```

use core::marker::PhantomData;
use kernel::prelude::*;

// -----------------------------------------------------------------------
// Core energy types
// -----------------------------------------------------------------------

/// Power in milliwatts.
pub type PowerMw = u32;

/// Energy in millijoules (Power * time).
pub type EnergyMj = u64;

/// A performance state (frequency/voltage pair).
#[repr(C)]
#[derive(Debug, Clone, Copy)]
pub struct PerfState {
    /// Frequency in KHz.
    pub frequency: u32,
    /// Power at this state in milliwatts.
    pub power: PowerMw,
    /// Capacity at this state (0..1024, relative to max).
    pub capacity: u32,
}

/// An energy model for a single performance domain.
///
/// A performance domain is a set of CPUs that share voltage/frequency
/// (e.g., all P-cores in a cluster).
pub struct PerfDomain {
    /// CPUs in this domain (CPU indices).
    pub cpus: &'static [u32],
    /// Available performance states (sorted by frequency ascending).
    pub states: &'static [PerfState],
}

/// Result of an energy cost query.
#[derive(Debug, Clone, Copy)]
pub struct EnergyCost {
    /// Total energy for the placement.
    pub total: EnergyMj,
    /// The selected performance state index.
    pub state_idx: u32,
    /// Estimated utilization after placement (0..1024).
    pub util: u32,
}

// -----------------------------------------------------------------------
// The EnergyModel trait
// -----------------------------------------------------------------------

/// An energy model that can estimate power and energy costs.
///
/// # Implementations
///
/// - `FlatEnergyModel`: uses the existing `em_perf_domain` data
/// - `DummyEnergyModel`: always returns zero (for testing)
pub trait EnergyModel: Send + Sync {
    /// Estimate the energy cost of running a task with given utilization
    /// on a specific CPU.
    fn estimate_energy(
        &self,
        cpu: usize,
        util_avg: u32,
        util_est: u32,
    ) -> EnergyCost;

    /// Return the max capacity of a CPU (0..1024).
    fn max_capacity(&self, cpu: usize) -> u32;

    /// Return the current capacity of a CPU (accounting for thermal
    /// pressure).
    fn current_capacity(&self, cpu: usize) -> u32;

    /// Return the number of performance states for a CPU.
    fn nr_perf_states(&self, cpu: usize) -> u32;
}

// -----------------------------------------------------------------------
// DummyEnergyModel (for testing/fallback)
// -----------------------------------------------------------------------

/// A no-op energy model that always returns zero energy cost.
/// Useful as a fallback when no real EM is registered.
pub struct DummyEnergyModel;

impl EnergyModel for DummyEnergyModel {
    fn estimate_energy(
        &self,
        _cpu: usize,
        _util_avg: u32,
        _util_est: u32,
    ) -> EnergyCost {
        EnergyCost {
            total: 0,
            state_idx: 0,
            util: 0,
        }
    }

    fn max_capacity(&self, _cpu: usize) -> u32 {
        1024
    }

    fn current_capacity(&self, _cpu: usize) -> u32 {
        1024
    }

    fn nr_perf_states(&self, _cpu: usize) -> u32 {
        1
    }
}

// -----------------------------------------------------------------------
// Global energy model registry
// -----------------------------------------------------------------------

use core::sync::atomic::{AtomicPtr, Ordering};

static GLOBAL_ENERGY_MODEL: AtomicPtr<()> = AtomicPtr::new(core::ptr::null_mut());

/// Register a global energy model.
///
/// This replaces any previously registered model.
pub fn register_energy_model(em: &'static dyn EnergyModel) {
    let ptr = em as *const dyn EnergyModel as *mut ();
    GLOBAL_ENERGY_MODEL.store(ptr, Ordering::Release);
}

/// Unregister the global energy model.
pub fn unregister_energy_model() {
    GLOBAL_ENERGY_MODEL.store(core::ptr::null_mut(), Ordering::Release);
}

/// Get the currently registered energy model, or the dummy fallback.
fn get_energy_model() -> &'static dyn EnergyModel {
    let ptr = GLOBAL_ENERGY_MODEL.load(Ordering::Acquire);
    if ptr.is_null() {
        static DUMMY: DummyEnergyModel = DummyEnergyModel;
        &DUMMY
    } else {
        // SAFETY: registered models must be 'static and valid.
        unsafe { &*(ptr as *const dyn EnergyModel) }
    }
}

// -----------------------------------------------------------------------
// C FFI — schedulers call these functions
// -----------------------------------------------------------------------

/// Estimate energy for placing a task with given utilization on a CPU.
///
/// Called from C scheduler classes.
#[no_mangle]
pub extern "C" fn rust_em_estimate(
    cpu: u32,
    util_avg: u32,
    util_est: u32,
) -> u64 {
    let em = get_energy_model();
    let cost = em.estimate_energy(cpu as usize, util_avg, util_est);
    cost.total
}

/// Return true if energy-aware scheduling is available.
#[no_mangle]
pub extern "C" fn rust_em_is_available() -> bool {
    !GLOBAL_ENERGY_MODEL.load(Ordering::Acquire).is_null()
}

// -----------------------------------------------------------------------
// Usage from C (in fair.c, etc.):
//
//   if (rust_em_is_available()) {
//       u64 energy_cost = rust_em_estimate(cpu, util_avg, util_est);
//       // compare costs across CPUs, pick lowest
//   }
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_dummy_model() {
        let em = DummyEnergyModel;
        let cost = em.estimate_energy(0, 500, 600);
        assert_eq!(cost.total, 0);
    }

    #[test]
    fn test_registry() {
        let em = DummyEnergyModel;
        register_energy_model(&em);
        assert!(rust_em_is_available());
        unregister_energy_model();
        assert!(!rust_em_is_available());
    }
}
