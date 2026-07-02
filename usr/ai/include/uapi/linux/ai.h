/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * AI subsystem — userspace API definitions
 *
 * Shared between kernel modules and userspace daemons.
 */

#ifndef _UAPI_LINUX_AI_H
#define _UAPI_LINUX_AI_H

#include <linux/ioctl.h>
#include <linux/types.h>

/* ── IOCTL commands ────────────────────────────────────── */

/* Magic number for AI ioctls */
#define AI_IOCTL_MAGIC  'A'

/* AI_IOCTL_CLASSIFY — register / update an AI process */
/* _IOWR(MAGIC, 1, struct ai_classify_param) */
#define AI_IOCTL_CLASSIFY \
	_IOWR(AI_IOCTL_MAGIC, 1, struct ai_classify_param)

/* AI_IOCTL_MEMORY_HINT — apply memory policy for AI region */
#define AI_IOCTL_MEMORY_HINT \
	_IOW(AI_IOCTL_MAGIC, 2, struct ai_memory_hint)

/* AI_IOCTL_SCHED_PRIORITY — adjust scheduling priority */
#define AI_IOCTL_SCHED_PRIORITY \
	_IOW(AI_IOCTL_MAGIC, 3, struct ai_sched_param)

/* AI_IOCTL_ADD_CLOUD — register a cloud AI endpoint */
#define AI_IOCTL_ADD_CLOUD \
	_IOW(AI_IOCTL_MAGIC, 4, __u64)

/* AI_IOCTL_REMOVE_CLOUD — remove a cloud AI endpoint */
#define AI_IOCTL_REMOVE_CLOUD \
	_IOW(AI_IOCTL_MAGIC, 5, __u32)

/* AI_IOCTL_GET_STATS — copy global AI statistics to userspace */
/* _IOR(MAGIC, 6, struct ai_stats) */
#define AI_IOCTL_GET_STATS \
	_IOR(AI_IOCTL_MAGIC, 6, struct ai_stats)

/* AI_IOCTL_PING — health check */
#define AI_IOCTL_PING _IO(AI_IOCTL_MAGIC, 7)

/* ── Shared structs ────────────────────────────────────── */

struct ai_classify_param {
	__s32 pid;
	__u32 workload_type;
	__u32 priority;
	__u32 flags;
};

struct ai_memory_hint {
	__u64 addr;
	__u64 size;
	__u32 policy;
	__u32 _flags;
};

struct ai_sched_param {
	__s32 pid;
	__s32 nice_offset;
	__u32 _sched_flags;
};

struct ai_stats {
	__u64 local_inferences;
	__u64 cloud_inferences;
	__u64 total_memory_used;
	__u32 active_models;
	__u32 active_processes;
	__u32 reserved[4];
};

#endif /* _UAPI_LINUX_AI_H */
