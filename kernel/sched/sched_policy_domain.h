/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _KERNEL_SCHED_POLICY_DOMAIN_H
#define _KERNEL_SCHED_POLICY_DOMAIN_H

#include <linux/types.h>
#include <linux/bitmap.h>

/*
 * sched_policy_domain — per-topology-class scheduling domain.
 *
 * Each CPU type (P-core, E-core, etc.) gets its own policy domain
 * which defines the scheduling class hierarchy for that CPU type.
 *
 * This replaces the flat for_each_class() dispatch with a
 * per-CPU-type dispatch, enabling:
 *   - P-cores run latency-optimized policies
 *   - E-cores run throughput-optimized policies
 *   - Heterogeneous systems get per-CPU-type class selection
 */

#define MAX_SCHED_CLASSES	8

struct sched_class;

struct sched_policy_domain {
	/* Ordered class table for this domain (highest priority first) */
	const struct sched_class *classes[MAX_SCHED_CLASSES];
	int			nr_classes;

	/* Domain flags */
	unsigned long		flags;
#define SCHED_POLICY_LATENCY_OPT	BIT(0)	/* P-core style */
#define SCHED_POLICY_THROUGHPUT_OPT	BIT(1)	/* E-core style */
#define SCHED_POLICY_ENERGY_AWARE	BIT(2)
#define SCHED_POLICY_CAPACITY_AWARE	BIT(3)

	/* Per-domain runqueue offset for cfs/rt/dl */
	/* (class-specific data accessible via container_of) */
};

/*
 * Per-CPU pointer to the current policy domain.
 * Set during CPU bring-up based on topology.
 */
DECLARE_PER_CPU(struct sched_policy_domain *, __cpu_policy_domain);

static inline struct sched_policy_domain *cpu_policy_domain(int cpu)
{
	return per_cpu(__cpu_policy_domain, cpu);
}

/*
 * Iterate scheduling classes for a given CPU's policy domain.
 * If the domain is not initialized, falls back to an empty iteration
 * (protected by the NULL check).
 */
#define for_each_class_in_domain(class, cpu)				\
	for (class = cpu_policy_domain(cpu) ?				\
	     cpu_policy_domain(cpu)->classes : NULL;			\
	     class && cpu_policy_domain(cpu) &&				\
	     class < cpu_policy_domain(cpu)->classes +			\
	     cpu_policy_domain(cpu)->nr_classes; class++)

/*
 * Policy domain management
 */
#ifdef CONFIG_SCHED_POLICY_DOMAIN
int sched_policy_domain_init(void);
int sched_policy_domain_register(struct sched_policy_domain *pd);
void sched_policy_domain_unregister(struct sched_policy_domain *pd);
int sched_policy_domain_assign_cpu(int cpu, struct sched_policy_domain *pd);
void __init sched_init_policy_domains(void);
void sched_policy_domain_classify(int cpu, unsigned long capacity);
#else
static inline int sched_policy_domain_init(void) { return 0; }
static inline void sched_init_policy_domains(void) { }
static inline void sched_policy_domain_classify(int cpu, unsigned long capacity) { }
#endif /* CONFIG_SCHED_POLICY_DOMAIN */

#endif /* _KERNEL_SCHED_POLICY_DOMAIN_H */
