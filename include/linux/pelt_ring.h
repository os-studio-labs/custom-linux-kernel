/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_PELT_RING_H
#define _LINUX_PELT_RING_H

#include <linux/types.h>

#ifdef CONFIG_PELT_RING

struct pelt_sample {
	u64			time;
	unsigned long		util_avg;
	unsigned long		util_est;
	unsigned long		load_avg;
	unsigned long		runnable_avg;
};

void pelt_ring_sample(int cpu, unsigned long util_avg,
		      unsigned long util_est,
		      unsigned long load_avg,
		      unsigned long runnable_avg);
int  pelt_ring_read(int cpu, struct pelt_sample *out);
int  pelt_ring_read_latest(int cpu, struct pelt_sample *out);
unsigned long pelt_ring_cpufreq_request(int cpu);
int __init pelt_ring_init(void);

#else /* !CONFIG_PELT_RING */

static inline void pelt_ring_sample(int cpu, unsigned long ua,
				    unsigned long ue,
				    unsigned long la,
				    unsigned long ra) { }
static inline int pelt_ring_read(int cpu, void *out) { return -EAGAIN; }
static inline unsigned long pelt_ring_cpufreq_request(int cpu) { return 0; }
static inline int pelt_ring_init(void) { return 0; }

#endif /* CONFIG_PELT_RING */

#endif /* _LINUX_PELT_RING_H */
