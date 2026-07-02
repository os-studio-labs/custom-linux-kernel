/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_RUST_CACHE_H
#define _ASM_X86_RUST_CACHE_H

#include <linux/types.h>

/* Cache type (must match Rust's CacheType) */
enum rust_cache_type {
	RUST_CACHE_L1_INST	= 1,
	RUST_CACHE_L1_DATA	= 2,
	RUST_CACHE_L2		= 3,
	RUST_CACHE_L3		= 4,
	RUST_CACHE_TRACE	= 5,
};

/* Cache descriptor result */
struct rust_cache_desc {
	enum rust_cache_type cache_type;
	u16 size_kb;
};

#ifdef CONFIG_X86_RUST_CACHE

bool rust_fill_cache_descriptor(u8 descriptor, struct rust_cache_desc *out);

#else /* !CONFIG_X86_RUST_CACHE */

/* Fallback: always return false; real fallback is the original while loop in cacheinfo.c */
static inline bool rust_fill_cache_descriptor(u8 descriptor,
					      struct rust_cache_desc *out)
{
	return false;
}

#endif /* CONFIG_X86_RUST_CACHE */

#endif /* _ASM_X86_RUST_CACHE_H */
