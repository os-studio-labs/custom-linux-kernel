/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _KERNEL_SCHED_EEVDF_FFI_H
#define _KERNEL_SCHED_EEVDF_FFI_H

#include <linux/types.h>

/*
 * FFI boundary between C scheduler (fair.c) and Rust EEVDF
 * (rust_eevdf.rs).
 *
 * The Rust side owns the augmented RB-tree; the C side calls
 * through these functions for all EEVDF operations.
 *
 * All functions are safe to call under rq->lock.
 */

struct rust_eevdf_tree;
struct sched_entity;

/*
 * Rust-side EEVDF tree operations.
 *
 * Return values:
 *   0            = success
 *   -EEXIST      = entity already in tree (deadline collision)
 *   -EINVAL      = invalid argument
 *   -ENOMEM      = allocation failure
 */

extern int  rust_eevdf_tree_insert(struct rust_eevdf_tree *tree,
				   u64 vruntime, u64 deadline,
				   s64 vlag, u64 slice, u32 weight,
				   bool on_rq);

extern int  rust_eevdf_tree_remove(struct rust_eevdf_tree *tree,
				   u64 deadline);

/*
 * Pick the earliest eligible entity.
 * On success, populates @out and returns 0.
 * Returns -ENOENT if no eligible entity found.
 */
struct eevdf_pick_result {
	u64 vruntime;
	u64 deadline;
	s64 vlag;
	u64 slice;
	u32 weight;
	bool on_rq;
	s64 subtree_min_vruntime;
};

extern int  rust_eevdf_tree_pick(struct rust_eevdf_tree *tree,
				 s64 avg_vruntime,
				 struct eevdf_pick_result *out);

extern int  rust_eevdf_tree_len(struct rust_eevdf_tree *tree);

/*
 * Lifecycle: the tree is allocated/deallocated by Rust.
 */
extern struct rust_eevdf_tree *rust_eevdf_tree_new(void);
extern void  rust_eevdf_tree_free(struct rust_eevdf_tree *tree);

/*
 * Optional: enable Rust-based fair scheduling class.
 * Controlled by CONFIG_SCHED_RUST_EEVDF.
 */
#ifdef CONFIG_SCHED_RUST_EEVDF
extern const struct sched_class rust_fair_sched_class;
#endif

#endif /* _KERNEL_SCHED_EEVDF_FFI_H */
