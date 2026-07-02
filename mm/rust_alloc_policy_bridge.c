// SPDX-License-Identifier: GPL-2.0-only
/*
 * rust_alloc_policy_bridge.c — C ↔ Rust FFI bridge for the Rust
 * allocation policy module.
 *
 * Registers a struct page_alloc_ops that forwards the policy hooks
 * (OOM badness, NUMA preference, reclaim priority, fragmentation
 * index) to the Rust implementations.
 *
 * Hooks that are NULL fall through to the default implementations
 * in page_alloc_modular.c.
 */

#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/export.h>
#include <linux/init.h>
#include <linux/page_alloc_modular.h>

/* ── Rust FFI declarations ─────────────────────────────────── */

extern long rust_alloc_oom_badness(struct task_struct *p,
				   unsigned long totalpages);

extern int rust_alloc_preferred_node(gfp_t gfp_mask, unsigned int order,
				     int preferred_nid,
				     nodemask_t *nodemask);

extern int rust_alloc_reclaim_priority_adjust(gfp_t gfp_mask,
					      unsigned int order);

extern int rust_alloc_fragmentation_index(int nid, int order);

/* Called from the page allocator on failure/success to update stats */
extern void rust_alloc_note_failure(int node);
extern void rust_alloc_note_success(int node);
extern void rust_alloc_note_oom_kill(void);

/* Rust module lifecycle */
extern int rust_alloc_policy_init(void);
extern void rust_alloc_policy_exit(void);

/* ── Wrapped alloc/free with congestion tracking ──────────── */

static struct page *
rust_alloc_pages_nodemask(gfp_t gfp_mask, unsigned int order,
			  int preferred_nid, nodemask_t *nodemask)
{
	struct page *page;

	/* Fall through to the kernel's __alloc_pages */
	page = __alloc_pages(gfp_mask, order, preferred_nid, nodemask);

	if (page) {
		int nid = page_to_nid(page);
		rust_alloc_note_success(nid);
	} else {
		rust_alloc_note_failure(preferred_nid);
	}

	return page;
}

static void rust_free_pages(struct page *page, unsigned int order)
{
	if (page)
		__free_pages(page, order);
}

/* ── Ops vector ────────────────────────────────────────────── */

static struct page_alloc_ops rust_alloc_ops = {
	.alloc_pages_nodemask	  = rust_alloc_pages_nodemask,
	.free_pages		  = rust_free_pages,
	.oom_badness		  = rust_alloc_oom_badness,
	.preferred_node		  = rust_alloc_preferred_node,
	.reclaim_priority_adjust  = rust_alloc_reclaim_priority_adjust,
	.fragmentation_index	  = rust_alloc_fragmentation_index,
};

/* ── Module init / exit ────────────────────────────────────── */

static int __init rust_alloc_policy_bridge_init(void)
{
	struct page_alloc_ops *old;

	rust_alloc_policy_init();
	old = page_alloc_register_ops(&rust_alloc_ops);
	pr_info("rust_alloc_policy: registered (previous ops: %ps)\n", old);
	return 0;
}

static void __exit rust_alloc_policy_bridge_exit(void)
{
	page_alloc_register_ops(NULL);
	rust_alloc_policy_exit();
	pr_info("rust_alloc_policy: unregistered, default ops restored\n");
}

module_init(rust_alloc_policy_bridge_init);
module_exit(rust_alloc_policy_bridge_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Rust page allocation policy — stable OOM, NUMA, reclaim");
MODULE_AUTHOR("SentraOS");
