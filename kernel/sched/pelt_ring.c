// SPDX-License-Identifier: GPL-2.0-only
/*
 * pelt_ring — Lockless ring buffer for PELT utilization signals.
 *
 * PROBLEM:
 *   The scheduler tick calls update_cfs_rq() -> PELT update ->
 *   cpufreq_update_util() IN THE TICK PATH. This couples
 *   frequency scaling latency to scheduler tick jitter.
 *
 * SOLUTION:
 *   Decouple PELT production (scheduler tick) from PELT consumption
 *   (cpufreq governor) using a lockless single-producer single-consumer
 *   ring buffer per CPU.
 *
 *   Producer (scheduler tick, hardirq context):
 *     pelt_ring_sample(cpu, util_avg, util_est, load_avg)
 *
 *   Consumer (cpufreq governor, softirq or workqueue):
 *     pelt_ring_read(cpu, &sample)  // non-blocking
 *
 *   When no sample is available, the governor can use the last known
 *   value, which is cached in the per-CPU pelt_state.
 *
 * Architecture:
 *
 *   +-----------+     spsc ring      +--------------+
 *   | scheduler | ----- samples ---->| cpufreq gov  |
 *   | tick (S)  |                    | (workqueue)  |
 *   +-----------+                    +--------------+
 *         |                                |
 *         v                                v
 *   update_cfs_rq()                  schedutil callback
 *   writes {util, load}              reads latest sample
 *
 * BENCHMARKING:
 *   Measure tick duration reduction with:
 *     perf stat -e cycles:k -C $CPU -- taskset -c $CPU hackbench
 */

#include <linux/percpu.h>
#include <linux/cpufreq.h>
#include <linux/sched/cpufreq.h>
#include <linux/sched/clock.h>
#include <linux/atomic.h>
#include <linux/pelt_ring.h>
#include "sched.h"

/*
 * Ring buffer size (must be power of 2)
 */
#define PELT_RING_SIZE	16
#define PELT_RING_MASK	(PELT_RING_SIZE - 1)

/*
 * Per-CPU PELT state.
 *
 * The ring buffer is single-producer (scheduler tick on this CPU)
 * single-consumer (cpufreq workqueue, potentially on any CPU).
 *
 * Synchronization protocol:
 *   Producer: write slot[head], smp_wmb(), WRITE_ONCE(head, next)
 *   Consumer: READ_ONCE(head), read slot[tail], smp_mb(), WRITE_ONCE(tail, next)
 *
 * last_sample is protected by a sequence counter to prevent torn reads.
 */
struct pelt_ring {
	struct pelt_sample	slots[PELT_RING_SIZE];
	u32			head;		/* written by producer (use WRITE/READ_ONCE) */
	u32			tail;		/* read/written by consumer (use WRITE/READ_ONCE) */

	/* Cached last known values (for consumer when ring is empty) */
	struct pelt_sample	last_sample;
	u32			last_seq;	/* incremented by producer, checked by consumer */
};

static DEFINE_PER_CPU(struct pelt_ring, pelt_rings) = { .head = 0, .tail = 0, .last_seq = 0 };

/*
 * Called from scheduler tick (update_cfs_rq path).
 * Must be called with preemption disabled on the local CPU.
 * This is wait-free for the producer (no locks).
 */
void pelt_ring_sample(int cpu, unsigned long util_avg, unsigned long util_est,
		      unsigned long load_avg, unsigned long runnable_avg)
{
	struct pelt_ring *ring = per_cpu_ptr(&pelt_rings, cpu);
	struct pelt_sample *slot;
	u32 head, next;

	head = READ_ONCE(ring->head);
	next = (head + 1) & PELT_RING_MASK;

	/* If the ring is full, overwrite the oldest entry */
	if (next == READ_ONCE(ring->tail))
		head = (head + 1) & PELT_RING_MASK;

	slot = &ring->slots[head];

	slot->time		= sched_clock();
	slot->util_avg		= util_avg;
	slot->util_est		= util_est;
	slot->load_avg		= load_avg;
	slot->runnable_avg	= runnable_avg;

	/* Update the cached last sample with seqcount to prevent torn reads */
	ring->last_seq++;
	smp_wmb();
	ring->last_sample = *slot;
	smp_wmb();
	ring->last_seq++;

	/* Commit: update head so consumer can see it */
	smp_wmb();
	WRITE_ONCE(ring->head, (head + 1) & PELT_RING_MASK);
}

/*
 * Read the latest sample from the ring buffer.
 * Non-blocking: returns 0 on success, -EAGAIN if empty.
 *
 * If the ring is empty, `out` will contain the last known sample.
 * Caller should check `out->time` for staleness.
 */
int pelt_ring_read(int cpu, struct pelt_sample *out)
{
	struct pelt_ring *ring = per_cpu_ptr(&pelt_rings, cpu);
	u32 tail, head, seq;

	head = READ_ONCE(ring->head);
	tail = READ_ONCE(ring->tail);

	if (head == tail) {
		/*
		 * Ring is empty — return the last known sample.
		 * Use seqcount to avoid torn struct reads.
		 */
		do {
			seq = READ_ONCE(ring->last_seq);
			smp_rmb();
			out->time		= ring->last_sample.time;
			out->util_avg		= ring->last_sample.util_avg;
			out->util_est		= ring->last_sample.util_est;
			out->load_avg		= ring->last_sample.load_avg;
			out->runnable_avg	= ring->last_sample.runnable_avg;
			smp_rmb();
		} while (seq != READ_ONCE(ring->last_seq) || (seq & 1));
		return -EAGAIN;
	}

	*out = ring->slots[tail];

	/* Advance tail */
	smp_mb();
	WRITE_ONCE(ring->tail, (tail + 1) & PELT_RING_MASK);

	return 0;
}

/*
 * Read a batch of samples, returning the most recent.
 * The consumer should drain all available samples and
 * only use the latest (oldest samples are stale).
 */
int pelt_ring_read_latest(int cpu, struct pelt_sample *out)
{
	struct pelt_ring *ring = per_cpu_ptr(&pelt_rings, cpu);
	u32 tail, head;
	int found = -EAGAIN;

	head = READ_ONCE(ring->head);
	tail = READ_ONCE(ring->tail);

	while (head != tail) {
		*out = ring->slots[tail];
		smp_mb();
		WRITE_ONCE(ring->tail, (tail + 1) & PELT_RING_MASK);
		tail = READ_ONCE(ring->tail);
		head = READ_ONCE(ring->head);
		found = 0;
	}

	if (found == -EAGAIN) {
		u32 seq;
		do {
			seq = READ_ONCE(ring->last_seq);
			smp_rmb();
			out->time		= ring->last_sample.time;
			out->util_avg		= ring->last_sample.util_avg;
			out->util_est		= ring->last_sample.util_est;
			out->load_avg		= ring->last_sample.load_avg;
			out->runnable_avg	= ring->last_sample.runnable_avg;
			smp_rmb();
		} while (seq != READ_ONCE(ring->last_seq) || (seq & 1));
	}

	return found;
}

/*
 * Convert PELT utilization to a cpufreq request.
 *
 * Decoupled from the tick: this can be called from a workqueue,
 * softirq, or on demand.
 */
unsigned long pelt_ring_cpufreq_request(int cpu)
{
	struct pelt_sample sample;
	unsigned long freq;
	int ret;

	ret = pelt_ring_read_latest(cpu, &sample);
	if (ret == -EAGAIN)
		return 0; /* caller should use last known frequency */

	/*
	 * Simple frequency selection: scale frequency proportionally
	 * to utilization.
	 *
	 * util_avg is in [0..SCHED_CAPACITY_SCALE=1024].
	 * max_freq = policy->cpuinfo.max_freq
	 *
	 * The actual freq calculation is done by the cpufreq governor,
	 * which reads the ring instead of calling update_util() directly.
	 */
	freq = sample.util_est ?: sample.util_avg;

	return freq;
}
EXPORT_SYMBOL_GPL(pelt_ring_cpufreq_request);

/*
 * Initialize PELT rings at scheduler init.
 */
int __init pelt_ring_init(void)
{
	int cpu;

	for_each_possible_cpu(cpu) {
		struct pelt_ring *ring = per_cpu_ptr(&pelt_rings, cpu);
		memset(ring, 0, sizeof(*ring));
	}

	return 0;
}

/*
 * Hook into the scheduler tick to capture PELT signals.
 *
 * This is called from update_cfs_rq() in fair.c after
 * load/util averages are computed.
 *
 * Usage:
 *   In fair.c::update_cfs_rq(), after computing util_avg:
 *
 *     if (sched_feat(PELT_RING))
 *         pelt_ring_sample(cpu_of(rq_of(cfs_rq)),
 *                          cfs_rq->avg.util_avg,
 *                          cfs_rq->avg.util_est,
 *                          cfs_rq->avg.load_avg,
 *                          cfs_rq->avg.runnable_avg);
 */
