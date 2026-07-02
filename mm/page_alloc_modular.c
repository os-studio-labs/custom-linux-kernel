// SPDX-License-Identifier: GPL-2.0-only
/*
 * page_alloc_modular — Pluggable page allocation policy interface.
 *
 * PROBLEM: mm/page_alloc.c and mm/oom_kill.c are deeply coupled
 * monoliths.  Policy decisions (which node, when to compact, who to
 * OOM-kill) are hard-coded.
 *
 * SOLUTION: struct page_alloc_ops defines a clean policy vector.
 * Default implementations forward to the standard kernel functions.
 * Backends (including Rust modules) can override individual hooks.
 */

#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/export.h>
#include <linux/topology.h>
#include <linux/oom.h>
#include <linux/compaction.h>
#include <linux/mmzone.h>
#include <linux/page_alloc_modular.h>
#include "internal.h"

/* ── Default implementations ─────────────────────────────── */

static struct page *default_alloc_pages_nodemask(gfp_t gfp_mask,
	unsigned int order, int preferred_nid, nodemask_t *nodemask)
{
	return __alloc_pages(gfp_mask, order, preferred_nid, nodemask);
}

static void default_free_pages(struct page *page, unsigned int order)
{
	__free_pages(page, order);
}

static long default_oom_badness(struct task_struct *p,
				unsigned long totalpages)
{
	return oom_badness(p, totalpages);
}

static bool default_oom_scan_abort(struct task_struct *task,
				   struct oom_control *oc)
{
	return false;
}

static int default_fragmentation_index(int nid, int order)
{
#ifdef CONFIG_COMPACTION
	struct zone *zone;

	if (nid < 0 || nid >= nr_node_ids)
		return 0;

	zone = NODE_DATA(nid)->node_zones + ZONE_NORMAL;
	if (!managed_zone(zone))
		zone = NODE_DATA(nid)->node_zones + ZONE_MOVABLE;
	if (!managed_zone(zone))
		return 0;

	return fragmentation_index(zone, order);
#else
	return 0;
#endif
}

static bool default_should_compact_retry(struct alloc_context *ac,
		int order, int alloc_flags, int compact_result,
		int *compact_priority, int *compaction_retries)
{
	/* Conservative: always allow one retry */
	if (!order)
		return false;
	return true;
}

static int default_preferred_node(gfp_t gfp_mask, unsigned int order,
				  int preferred_nid, nodemask_t *nodemask)
{
	return preferred_nid;
}

static int default_reclaim_priority_adjust(gfp_t gfp_mask,
					   unsigned int order)
{
	return 0;
}

/* ── Ops vector with defaults ─────────────────────────────── */

static struct page_alloc_ops default_alloc_ops = {
	.alloc_pages_nodemask	= default_alloc_pages_nodemask,
	.free_pages		= default_free_pages,
	.oom_badness		= default_oom_badness,
	.oom_scan_abort		= default_oom_scan_abort,
	.fragmentation_index	= default_fragmentation_index,
	.should_compact_retry	= default_should_compact_retry,
	.preferred_node		= default_preferred_node,
	.reclaim_priority_adjust = default_reclaim_priority_adjust,
};

/*
 * The current ops vector.  A NULL entry means "use the default
 * for that slot", which simplifies backend registration.
 *
 * Access is synchronized via READ_ONCE/WRITE_ONCE to ensure
 * atomic pointer visibility.  The ops struct itself must not
 * be modified after installation (it is read-only at runtime).
 */
static struct page_alloc_ops *alloc_ops = &default_alloc_ops;

/* ── Registration ─────────────────────────────────────────── */

struct page_alloc_ops *page_alloc_register_ops(struct page_alloc_ops *new_ops)
{
	struct page_alloc_ops *old;

	old = READ_ONCE(alloc_ops);

	if (new_ops)
		WRITE_ONCE(alloc_ops, new_ops);
	else
		WRITE_ONCE(alloc_ops, &default_alloc_ops);

	return old;
}
EXPORT_SYMBOL_GPL(page_alloc_register_ops);

/* ── Helpers (call through ops with default fallback) ─────── */

static __always_inline struct page_alloc_ops *ops(void)
{
	struct page_alloc_ops *o = READ_ONCE(alloc_ops);
	return o ?: &default_alloc_ops;
}

#define OPS_CALL(ret_type, name, args...)			\
	({							\
		struct page_alloc_ops *__o = ops();		\
		__o->name ? __o->name(args) : default_##name(args);	\
	})

struct page *alloc_pages_modular(gfp_t gfp_mask, unsigned int order)
{
	if (order > MAX_PAGE_ORDER)
		return NULL;
	return OPS_CALL(struct page *, alloc_pages_nodemask,
			gfp_mask, order, numa_node_id(), NULL);
}
EXPORT_SYMBOL_GPL(alloc_pages_modular);

void free_pages_modular(struct page *page, unsigned int order)
{
	if (page)
		OPS_CALL(void, free_pages, page, order);
}
EXPORT_SYMBOL_GPL(free_pages_modular);

long page_alloc_oom_badness(struct task_struct *p, unsigned long totalpages)
{
	return OPS_CALL(long, oom_badness, p, totalpages);
}
EXPORT_SYMBOL_GPL(page_alloc_oom_badness);

bool page_alloc_oom_scan_abort(struct task_struct *task,
			       struct oom_control *oc)
{
	return OPS_CALL(bool, oom_scan_abort, task, oc);
}
EXPORT_SYMBOL_GPL(page_alloc_oom_scan_abort);

int page_alloc_fragmentation_index(int nid, int order)
{
	return OPS_CALL(int, fragmentation_index, nid, order);
}
EXPORT_SYMBOL_GPL(page_alloc_fragmentation_index);

bool page_alloc_should_compact_retry(struct alloc_context *ac,
		int order, int alloc_flags, int compact_result,
		int *compact_priority, int *compaction_retries)
{
	return OPS_CALL(bool, should_compact_retry, ac, order,
			alloc_flags, compact_result,
			compact_priority, compaction_retries);
}
EXPORT_SYMBOL_GPL(page_alloc_should_compact_retry);

int page_alloc_preferred_node(gfp_t gfp_mask, unsigned int order,
			      int preferred_nid, nodemask_t *nodemask)
{
	return OPS_CALL(int, preferred_node, gfp_mask, order,
			preferred_nid, nodemask);
}
EXPORT_SYMBOL_GPL(page_alloc_preferred_node);

int page_alloc_reclaim_priority_adjust(gfp_t gfp_mask, unsigned int order)
{
	return OPS_CALL(int, reclaim_priority_adjust, gfp_mask, order);
}
EXPORT_SYMBOL_GPL(page_alloc_reclaim_priority_adjust);

/* ── Benchmark ────────────────────────────────────────────── */

void page_alloc_benchmark(unsigned int order, unsigned long iterations)
{
	unsigned long i;
	for (i = 0; i < iterations; i++) {
		struct page *page = alloc_pages_modular(GFP_KERNEL, order);
		if (page)
			free_pages_modular(page, order);
	}
}
EXPORT_SYMBOL_GPL(page_alloc_benchmark);
