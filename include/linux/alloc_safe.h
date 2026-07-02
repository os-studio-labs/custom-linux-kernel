/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_ALLOC_SAFE_H_
#define _LINUX_ALLOC_SAFE_H_

/*
 * alloc_safe — allocation wrappers that never return NULL.
 *
 * These helpers panic on OOM instead of returning NULL, eliminating
 * entire classes of NULL-deref bugs.  Use ONLY in non-critical paths
 * where failure is unrecoverable.  Do NOT use in interrupt context
 * or where recovery is possible.
 */

#include <linux/slab.h>
#include <linux/bug.h>

static inline __attribute__((malloc))
void *kzalloc_safe(size_t size)
{
	void *p = kzalloc(size, GFP_KERNEL);
	if (unlikely(!p))
		panic("kzalloc_safe(%zu) failed\n", size);
	return p;
}

static inline __attribute__((malloc))
void *kmalloc_safe(size_t size, gfp_t flags)
{
	void *p = kmalloc(size, flags);
	if (unlikely(!p))
		panic("kmalloc_safe(%zu) failed\n", size);
	return p;
}

#define kzalloc_safe_struct(type) ((type *)kzalloc_safe(sizeof(type)))

#endif /* _LINUX_ALLOC_SAFE_H_ */
