/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_RUST_FEATURES_H
#define _ASM_X86_RUST_FEATURES_H

#include <linux/types.h>

struct cpuinfo_x86;

#ifdef CONFIG_X86_RUST_FEATURES

void rust_init_scattered_features_raw(void *cpu_data,
				      void (*set_cap)(void *cpu, u16 feat),
				      u32 (*cpuid_eax_fn)(u32 leaf),
				      void (*cpuid_count_fn)(u32 leaf, u32 sub,
							     u32 *eax, u32 *ebx,
							     u32 *ecx, u32 *edx));

void init_scattered_cpuid_features(struct cpuinfo_x86 *c);

#else /* !CONFIG_X86_RUST_FEATURES */

extern void init_scattered_cpuid_features(struct cpuinfo_x86 *c);

#endif /* CONFIG_X86_RUST_FEATURES */

#endif /* _ASM_X86_RUST_FEATURES_H */
