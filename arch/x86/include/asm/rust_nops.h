/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_RUST_NOPS_H
#define _ASM_X86_RUST_NOPS_H

#include <linux/types.h>

#ifdef CONFIG_X86_RUST_NOPS

void rust_add_nop(u8 *instr, u32 len);
const u8 *rust_get_nop(u32 len);
u32 rust_nop_len(u32 len);

#else /* !CONFIG_X86_RUST_NOPS */

/* Fallback: nop stubs; real add_nop() stays in alternative.c */

static inline const u8 *rust_get_nop(u32 len)
{
	return NULL;
}

static inline u32 rust_nop_len(u32 len)
{
	return len;
}

#endif /* CONFIG_X86_RUST_NOPS */

#endif /* _ASM_X86_RUST_NOPS_H */
