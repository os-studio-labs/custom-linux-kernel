/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SENTRAOS_OOM_H_
#define _LINUX_SENTRAOS_OOM_H_

/*
 * SentraOS OOM Killer — context-aware, ML-like evaluation.
 *
 * Replaces the legacy heuristic in select_bad_process() with a
 * 15-factor weighted scoring model that considers sandbox priority,
 * cgroup context, interactivity, memory growth rate, and more.
 */

#include <linux/types.h>
#include <linux/oom.h>

struct sentraos_oom_victim {
	u32	pid;
	s64	score;
	u32	sandbox_id;
	s64	importance_score;
	u64	memory_used_bytes;
	char	reason[128];
};

#ifdef CONFIG_SENTRAOS_OOM_RUST

struct sentraos_oom_victim sentraos_oom_evaluate(unsigned long totalpages,
						 unsigned int constraint,
						 u32 prefer_pid);

/* Log a kill decision with explanation */
void sentraos_oom_log_kill(const struct sentraos_oom_victim *victim);

/* Set sandbox OOM priority (0=Critical, 4=Sacrificial) */
int sentraos_oom_set_sandbox_priority(u32 sandbox_id, u32 priority);

/* Grant/query OOM immunity for a process */
int sentraos_oom_grant_immunity(u32 pid, u64 duration_ms);

/* Statistics */
u64 sentraos_oom_stats_invocations(void);
u64 sentraos_oom_stats_kills(void);

#else /* CONFIG_SENTRAOS_OOM_RUST */

static inline struct sentraos_oom_victim sentraos_oom_evaluate(
	unsigned long totalpages, unsigned int constraint, u32 prefer_pid)
{
	return (struct sentraos_oom_victim) { .pid = 0 };
}
static inline void sentraos_oom_log_kill(const struct sentraos_oom_victim *v) { }
static inline int sentraos_oom_set_sandbox_priority(u32 s, u32 p) { return 0; }
static inline int sentraos_oom_grant_immunity(u32 p, u64 d) { return 0; }

#endif /* CONFIG_SENTRAOS_OOM_RUST */

#endif /* _LINUX_SENTRAOS_OOM_H_ */
