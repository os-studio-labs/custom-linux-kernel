/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_PAGE_ALLOC_MODULAR_H
#define _LINUX_PAGE_ALLOC_MODULAR_H

#include <linux/types.h>
#include <linux/gfp.h>
#include <linux/oom.h>

struct page;
struct alloc_context;

/*
 * page_alloc_ops — Pluggable page allocation policy vector.
 *
 * Each hook maps to a policy decision point in the page allocator
 * or OOM killer.  Default implementations forward to the existing
 * kernel functions so behaviour is identical when no custom ops
 * are installed.
 *
 * A backend may install a partial ops vector; NULL entries fall
 * through to the default.
 */
struct page_alloc_ops {

	/* ── Core allocation ────────────────────────────────── */

	struct page *(*alloc_pages_nodemask)(gfp_t gfp_mask,
		unsigned int order, int preferred_nid,
		nodemask_t *nodemask);

	void (*free_pages)(struct page *page, unsigned int order);

	/* ── OOM victim selection ───────────────────────────── */

	/*
	 * oom_badness — score a task for OOM killing.
	 * Return value: higher = more likely to be killed.
	 * Return LONG_MIN to mark the task as unkillable.
	 * If set, this replaces the default oom_badness().
	 */
	long (*oom_badness)(struct task_struct *p,
			    unsigned long totalpages);

	/*
	 * oom_scan_abort — called during OOM task scan.
	 * Return true to abort the scan and keep the current
	 * best candidate (or nobody if none found yet).
	 * Called from oom_evaluate_task context.
	 */
	bool (*oom_scan_abort)(struct task_struct *task,
			       struct oom_control *oc);

	/* ── Compaction / fragmentation ─────────────────────── */

	/*
	 * fragmentation_index — return [0, 1000] indicating
	 * how fragmented a node is.  0 = no fragmentation,
	 * 1000 = completely fragmented.  Used by proactive
	 * compaction.
	 */
	int (*fragmentation_index)(int nid, int order);

	/*
	 * should_compact_retry — decide whether to retry
	 * compaction after a failure.  Return true to retry.
	 */
	bool (*should_compact_retry)(struct alloc_context *ac,
				     int order, int alloc_flags,
				     int compact_result,
				     int *compact_priority,
				     int *compaction_retries);

	/* ── NUMA node preference ───────────────────────────── */

	/*
	 * preferred_node — override the preferred node for an
	 * allocation.  Return a node id, or NUMA_NO_NODE to
	 * use the default.
	 */
	int (*preferred_node)(gfp_t gfp_mask, unsigned int order,
			      int preferred_nid,
			      nodemask_t *nodemask);

	/* ── Reclaim hint ────────────────────────────────────── */

	/*
	 * reclaim_priority — adjust reclaim aggressiveness.
	 * 0 = normal, >0 = more aggressive, <0 = less aggressive.
	 * Return value is added to the reclaim priority.
	 */
	int (*reclaim_priority_adjust)(gfp_t gfp_mask,
				       unsigned int order);
};

#ifdef CONFIG_PAGE_ALLOC_MODULAR

/*
 * Register a new ops vector.  Returns the previous ops so the
 * caller can restore it later.  Pass NULL to restore the default.
 */
struct page_alloc_ops *page_alloc_register_ops(struct page_alloc_ops *new_ops);

/*
 * Core allocation wrappers — these forward to the current ops.
 */
struct page *alloc_pages_modular(gfp_t gfp_mask, unsigned int order);
void free_pages_modular(struct page *page, unsigned int order);

/*
 * Policy query helpers — call into the current ops with
 * default fallback if the op is NULL.
 */
long page_alloc_oom_badness(struct task_struct *p,
			    unsigned long totalpages);
bool page_alloc_oom_scan_abort(struct task_struct *task,
			       struct oom_control *oc);
int page_alloc_fragmentation_index(int nid, int order);

bool page_alloc_should_compact_retry(struct alloc_context *ac,
				     int order, int alloc_flags,
				     int compact_result,
				     int *compact_priority,
				     int *compaction_retries);

int page_alloc_preferred_node(gfp_t gfp_mask, unsigned int order,
			      int preferred_nid,
			      nodemask_t *nodemask);
int page_alloc_reclaim_priority_adjust(gfp_t gfp_mask,
				       unsigned int order);

/* Benchmark / debug */
void page_alloc_benchmark(unsigned int order, unsigned long iterations);

#else /* !CONFIG_PAGE_ALLOC_MODULAR */

static inline struct page *alloc_pages_modular(gfp_t gfp, unsigned int o)
{ return alloc_pages(gfp, o); }
static inline void free_pages_modular(struct page *p, unsigned int o)
{ __free_pages(p, o); }

static inline long page_alloc_oom_badness(struct task_struct *p,
					  unsigned long totalpages)
{ return oom_badness(p, totalpages); }
static inline bool page_alloc_oom_scan_abort(struct task_struct *task,
					     struct oom_control *oc)
{ return false; }

static inline int page_alloc_fragmentation_index(int nid, int order)
{ return 0; }
static inline int page_alloc_preferred_node(gfp_t gfp_mask,
					    unsigned int order,
					    int preferred_nid,
					    nodemask_t *nodemask)
{ return preferred_nid; }
static inline int page_alloc_reclaim_priority_adjust(gfp_t gfp_mask,
						     unsigned int order)
{ return 0; }

#endif /* CONFIG_PAGE_ALLOC_MODULAR */

#endif /* _LINUX_PAGE_ALLOC_MODULAR_H */
