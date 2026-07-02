// SPDX-License-Identifier: GPL-2.0-only
/*
 * sched_policy_domain — Per-topology-class scheduling policy domains.
 *
 * Each CPU type (P-core, E-core, etc.) gets its own policy domain
 * defining which scheduling classes it runs. This enables:
 *   - P-cores:  latency-optimized fair class
 *   - E-cores:  throughput-optimized fair class
 *   - Mixed:    per-CPU-type class selection without special cases
 *
 * Architecture:
 *   policy_domain         per-CPU assignment
 *   +--------------+      +-----------+
 *   | classes[0]   |<---->| CPU 0 (P) |
 *   | classes[1]   |      +-----------+
 *   | ...          |      +-----------+
 *   | classes[n]   |<---->| CPU 1 (P) |
 *   +--------------+      +-----------+
 *                         +-----------+
 *                         | CPU 2 (E) |
 *                         +-----------+
 */

#include <linux/sched.h>
#include <linux/cpumask.h>
#include <linux/slab.h>
#include "sched.h"
#include "sched_policy_domain.h"

DEFINE_PER_CPU(struct sched_policy_domain *, __cpu_policy_domain);

/* Default policy domain: the classic 5-class hierarchy */
static const struct sched_class *default_classes[] = {
	&stop_sched_class,
	&dl_sched_class,
	&rt_sched_class,
	&fair_sched_class,
	&idle_sched_class,
};

static struct sched_policy_domain default_pd = {
	.classes	= { NULL },
	.nr_classes	= ARRAY_SIZE(default_classes),
	.flags		= SCHED_POLICY_CAPACITY_AWARE | SCHED_POLICY_ENERGY_AWARE,
};

/* Throughput-optimized domain (for E-cores): uses the same classes
 * but the fair class runs a throughput-optimized variant */
static struct sched_policy_domain throughput_pd = {
	.classes	= { NULL },
	.nr_classes	= ARRAY_SIZE(default_classes),
	.flags		= SCHED_POLICY_THROUGHPUT_OPT | SCHED_POLICY_ENERGY_AWARE,
};

/* Latency-optimized domain (for P-cores) */
static struct sched_policy_domain latency_pd = {
	.classes	= { NULL },
	.nr_classes	= ARRAY_SIZE(default_classes),
	.flags		= SCHED_POLICY_LATENCY_OPT | SCHED_POLICY_CAPACITY_AWARE,
};

static bool policy_domains_initialized;

int __init sched_policy_domain_init(void)
{
	int i;

	/* Initialize class pointers */
	for (i = 0; i < default_pd.nr_classes; i++) {
		default_pd.classes[i] = default_classes[i];
		throughput_pd.classes[i] = default_classes[i];
		latency_pd.classes[i] = default_classes[i];
	}

	policy_domains_initialized = true;
	return 0;
}

int sched_policy_domain_register(struct sched_policy_domain *pd)
{
	if (!policy_domains_initialized)
		return -EAGAIN;
	return 0;
}

void sched_policy_domain_unregister(struct sched_policy_domain *pd)
{
}

int sched_policy_domain_assign_cpu(int cpu, struct sched_policy_domain *pd)
{
	if (!pd)
		pd = &default_pd;

	per_cpu(__cpu_policy_domain, cpu) = pd;
	return 0;
}

/*
 * Called from topology detection code to assign domains based
 * on CPU capacity groups.
 */
void __init sched_init_policy_domains(void)
{
	int cpu;

	if (!policy_domains_initialized)
		sched_policy_domain_init();

	for_each_possible_cpu(cpu) {
		/*
		 * In a heterogeneous system, assign domains based on
		 * capacity groups. For homogeneous systems, use default.
		 *
		 * The actual assignment is deferred to topology init,
		 * which calls sched_policy_domain_assign_cpu().
		 */
		per_cpu(__cpu_policy_domain, cpu) = &default_pd;
	}
}

/*
 * Hook for topology init to classify CPUs by capacity:
 *
 * P-cores (high capacity, typically 1.0)  -> latency_pd
 * E-cores (low capacity, typically <0.5)  -> throughput_pd
 */
void sched_policy_domain_classify(int cpu, unsigned long capacity)
{
	struct sched_policy_domain *pd;

	if (!policy_domains_initialized)
		sched_policy_domain_init();

	pd = &default_pd;

	if (static_branch_unlikely(&sched_asym_cpucapacity)) {
		unsigned long max_cap = arch_scale_cpu_capacity(cpumask_first(cpu_coregroup_mask(cpu)));

		if (capacity >= max_cap)
			pd = &latency_pd;
		else
			pd = &throughput_pd;
	}

	sched_policy_domain_assign_cpu(cpu, pd);
}
EXPORT_SYMBOL_GPL(sched_policy_domain_classify);
