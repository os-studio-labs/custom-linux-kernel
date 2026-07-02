/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_ENERGY_MODEL_RUST_H
#define _LINUX_ENERGY_MODEL_RUST_H

#include <linux/types.h>

/*
 * FFI declarations for the Rust Energy Model (kernel/sched/energy_model_rust.rs).
 *
 * When CONFIG_ENERGY_MODEL_RUST=y, these functions call into the Rust
 * EnergyModel trait implementation.  When disabled, they return defaults
 * (is_available = false, estimate = 0).
 */

#ifdef CONFIG_ENERGY_MODEL_RUST

/**
 * rust_em_estimate - Estimate energy cost for placing a task on a CPU.
 * @cpu:      Target CPU.
 * @util_avg: Task/utilization average (0..1024).
 * @util_est: Estimated utilization (0..1024).
 *
 * Return: Estimated energy in millijoules, or 0 if no model registered.
 */
extern u64 rust_em_estimate(u32 cpu, u32 util_avg, u32 util_est);

/**
 * rust_em_is_available - Check if an energy model is registered.
 *
 * Return: true if a Rust EnergyModel is registered and ready.
 */
extern bool rust_em_is_available(void);

#else /* !CONFIG_ENERGY_MODEL_RUST */

static inline u64 rust_em_estimate(u32 cpu, u32 util_avg, u32 util_est)
{
	return 0;
}

static inline bool rust_em_is_available(void)
{
	return false;
}

#endif /* CONFIG_ENERGY_MODEL_RUST */

#endif /* _LINUX_ENERGY_MODEL_RUST_H */
