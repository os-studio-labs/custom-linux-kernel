/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_RUST_TOPOLOGY_H
#define _ASM_X86_RUST_TOPOLOGY_H

#include <linux/types.h>

/* Topology domain levels (must match Rust's TopoDomain) */
enum rust_topo_domain {
	RUST_TOPO_SMT		= 0,
	RUST_TOPO_CORE		= 1,
	RUST_TOPO_MODULE	= 2,
	RUST_TOPO_TILE		= 3,
	RUST_TOPO_DIE		= 4,
	RUST_TOPO_PKG		= 5,
	RUST_TOPO_MAX		= 6,
};

/* Callback for setting per-CPU APIC data */
typedef void (*rust_set_cpu_data_fn)(unsigned int cpu, u32 apic_id, u32 acpi_id);

/* Callback for marking primary thread */
typedef void (*rust_mark_primary_fn)(unsigned int cpu, u32 apic_id, u32 max_threads);

#ifdef CONFIG_X86_RUST_TOPOLOGY

int  rust_topology_register_apic(u32 apic_id, u32 acpi_id, bool present,
				 const u8 *dom_shifts, u32 nr_cpu_ids,
				 rust_set_cpu_data_fn set_cpu_data,
				 rust_mark_primary_fn mark_primary,
				 u32 max_threads);
int  rust_topology_register_boot_apic(u32 apic_id, const u8 *dom_shifts,
				      rust_set_cpu_data_fn set_cpu_data);
int  rust_topology_get_logical_id(u32 apic_id, int at_level,
				  const u8 *dom_shifts);
u32  rust_topology_unit_count(u32 apic_id, int which_units, int at_level,
			      const u8 *dom_shifts);
void rust_topology_info(u32 *assigned, u32 *disabled, u32 *rejected);
u32  rust_topology_cpuid_to_apicid(u32 cpu);

#else /* !CONFIG_X86_RUST_TOPOLOGY */

/* Not using Rust topology — original C functions remain in use */
static inline void rust_topology_info(u32 *assigned, u32 *disabled, u32 *rejected)
{
	(void)assigned; (void)disabled; (void)rejected;
}

#endif /* CONFIG_X86_RUST_TOPOLOGY */

#endif /* _ASM_X86_RUST_TOPOLOGY_H */
