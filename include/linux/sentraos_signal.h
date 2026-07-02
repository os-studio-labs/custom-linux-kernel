/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SENTRAOS_SIGNAL_H
#define _LINUX_SENTRAOS_SIGNAL_H

#include <linux/types.h>

/*
 * SentraOS Signal Manager — C/Rust FFI interface.
 *
 * When CONFIG_SENTRAOS_SIGNAL_RUST=y, the core signal delivery
 * functions in kernel/signal.c are redirected to the Rust
 * signal manager (kernel/signal.rs) which provides:
 *   - Lockless pending queues (atomic bitmask per thread)
 *   - Thread-aware delivery (target specific thread or group)
 *   - Async-safe exit handling
 *   - No raw sigset_t manipulation races
 *
 * When disabled, the legacy C signal path is used unchanged.
 */

struct signal_info {
	u32 signo;
	s32 errno;
	s32 code;
	u32 pid;
	u32 uid;
	u64 value;
	u64 timestamp;
};

#ifdef CONFIG_SENTRAOS_SIGNAL_RUST

/* Allocate/free per-thread signal state */
extern void *signal_state_alloc(u32 pid);
extern void  signal_state_free(u32 pid);

/* Core send — replaces __send_signal_locked + complete_signal */
extern int  signal_send(u32 pid, u32 signo,
			const struct signal_info *info, u32 force);

/* Send to thread group */
extern int  signal_send_group(u32 tgid, u32 signo,
			      const struct signal_info *info);

/* Dequeue next pending signal */
extern u32  signal_dequeue(u32 pid, struct signal_info *info);

/* Block/unblock signal masks (bitmask = 1 << signo) */
extern u64  signal_block(u32 pid, u64 mask);
extern u64  signal_unblock(u32 pid, u64 mask);
extern u64  signal_get_blocked(u32 pid);

/* Check pending signals */
extern u32  signal_has_pending(u32 pid);
extern u32  signal_has_kill(u32 pid);

/* Clear all pending signals (execve) */
extern void signal_clear_all(u32 pid);

/* Copy state from src_pid to dst_pid (fork) */
extern int  signal_copy(u32 src_pid, u32 dst_pid);

/* Statistics */
extern u64  signal_count(void);

/* Init */
extern int  signal_manager_init(void);

#else /* !CONFIG_SENTRAOS_SIGNAL_RUST */

/* Stubs — legacy C path handles everything */
static inline void *signal_state_alloc(u32 pid) { return NULL; }
static inline void  signal_state_free(u32 pid) { }

static inline int signal_send(u32 pid, u32 signo,
			      const struct signal_info *info, u32 force)
{ return -ENOSYS; }

static inline int signal_send_group(u32 tgid, u32 signo,
				    const struct signal_info *info)
{ return -ENOSYS; }

static inline u32  signal_dequeue(u32 pid, struct signal_info *info) { return 0; }
static inline u64  signal_block(u32 pid, u64 mask) { return 0; }
static inline u64  signal_unblock(u32 pid, u64 mask) { return 0; }
static inline u64  signal_get_blocked(u32 pid) { return 0; }
static inline u32  signal_has_pending(u32 pid) { return 0; }
static inline u32  signal_has_kill(u32 pid) { return 0; }
static inline void signal_clear_all(u32 pid) { }
static inline int  signal_copy(u32 src_pid, u32 dst_pid) { return -ENOSYS; }
static inline u64  signal_count(void) { return 0; }
static inline int  signal_manager_init(void) { return 0; }

#endif /* CONFIG_SENTRAOS_SIGNAL_RUST */
#endif /* _LINUX_SENTRAOS_SIGNAL_H */
