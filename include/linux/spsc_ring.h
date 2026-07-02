/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SPSC_RING_H
#define _LINUX_SPSC_RING_H

/*
 * SPSC Ring Buffer — Lockless single-producer single-consumer ring.
 *
 * This generalizes the PELT ring buffer pattern (kernel/sched/pelt_ring.c)
 * for use by any kernel subsystem that needs zero-cost production telemetry.
 *
 * USAGE:
 *
 *   struct my_event { u64 ts; u32 val; };
 *   DEFINE_SPSC_RING(my_events, struct my_event, 64);
 *
 *   // Producer (hardirq/softirq context, preemption disabled):
 *   struct my_event evt = { .ts = sched_clock(), .val = 42 };
 *   spsc_ring_push(&my_events, &evt);
 *
 *   // Consumer (workqueue/thread context):
 *   struct my_event evt;
 *   while (spsc_ring_pop(&my_events, &evt) == 0)
 *       process(&evt);
 *
 * Architecture:
 *
 *   +-----------+     SPSC (lockless)     +--------------+
 *   | producer  | ----> ring[head] ---->  | consumer     |
 *   | (any ctx) |      ring[tail]         | (any ctx)    |
 *   +-----------+                         +--------------+
 *
 * Synchronization:
 *   - Producer: write slot[head], smp_wmb(), WRITE_ONCE(head, next)
 *   - Consumer: READ_ONCE(head), read slot[tail], smp_mb(), WRITE_ONCE(tail, next)
 */

#include <linux/percpu.h>
#include <linux/atomic.h>

/* ── Ring buffer structure ────────────────────────────────── */

struct spsc_ring {
	void		*slots;		/* array of ring elements */
	u32		slot_size;	/* size of each element */
	u32		mask;		/* ring size - 1 (must be power of 2) */
	u32		head;		/* producer index (use READ/WRITE_ONCE) */
	u32		tail;		/* consumer index (use READ/WRITE_ONCE) */
};

/* ── Static initialization macro ──────────────────────────── */

/**
 * DEFINE_SPSC_RING - Define a statically-allocated SPSC ring buffer
 * @name:   variable name
 * @type:   element type
 * @size:   number of elements (must be power of 2, max 65536)
 */
#define DEFINE_SPSC_RING(name, type, size)				\
	static type __spsc_##name##_slots[size];			\
	static struct spsc_ring name = {				\
		.slots		= __spsc_##name##_slots,		\
		.slot_size	= sizeof(type),				\
		.mask		= (size) - 1,				\
		.head		= 0,					\
		.tail		= 0,					\
	}

/* ── Core operations ─────────────────────────────────────── */

/**
 * spsc_ring_push - Push an element into the ring (producer side).
 * @ring: the ring buffer
 * @elem: pointer to the element to copy in
 *
 * Context: Any context.  For a given ring, must be called by at most
 * one producer at a time (single-producer contract).
 *
 * If the ring is full, the oldest entry is silently overwritten.
 */
static inline void spsc_ring_push(struct spsc_ring *ring, const void *elem)
{
	u32 head, next;

	head = READ_ONCE(ring->head);
	next = (head + 1) & ring->mask;

	/* If full, overwrite the oldest */
	if (next == READ_ONCE(ring->tail))
		head = (head + 1) & ring->mask;

	memcpy(ring->slots + head * ring->slot_size, elem, ring->slot_size);

	smp_wmb();
	WRITE_ONCE(ring->head, next);
}

/**
 * spsc_ring_pop - Pop the oldest element from the ring (consumer side).
 * @ring: the ring buffer
 * @elem: pointer to memory where the element is copied out
 *
 * Return: 0 on success, -EAGAIN if the ring is empty.
 *
 * Context: Any context.  For a given ring, must be called by at most
 * one consumer at a time (single-consumer contract).
 */
static inline int spsc_ring_pop(struct spsc_ring *ring, void *elem)
{
	u32 tail, head;

	head = READ_ONCE(ring->head);
	tail = READ_ONCE(ring->tail);

	if (head == tail)
		return -EAGAIN;

	memcpy(elem, ring->slots + tail * ring->slot_size, ring->slot_size);

	smp_mb();
	WRITE_ONCE(ring->tail, (tail + 1) & ring->mask);

	return 0;
}

/**
 * spsc_ring_drain - Drain all available elements (consumer side).
 * @ring:  the ring buffer
 * @elem:  pointer to temporary storage
 * @cb:    callback invoked for each drained element
 *
 * Return: number of elements drained.
 *
 * This is more efficient than calling spsc_ring_pop() in a loop
 * because it minimizes the number of memory barriers.
 */
static inline unsigned int spsc_ring_drain(struct spsc_ring *ring,
					   void *elem,
					   void (*cb)(void *ctx, const void *elem),
					   void *ctx)
{
	u32 tail, head;
	unsigned int count = 0;

	head = READ_ONCE(ring->head);
	tail = READ_ONCE(ring->tail);

	while (head != tail) {
		memcpy(elem, ring->slots + tail * ring->slot_size,
		       ring->slot_size);
		smp_mb();
		WRITE_ONCE(ring->tail, (tail + 1) & ring->mask);
		tail = READ_ONCE(ring->tail);
		head = READ_ONCE(ring->head);
		if (cb)
			cb(ctx, elem);
		count++;
	}

	return count;
}

/**
 * spsc_ring_available - Return number of elements available to consume.
 */
static inline u32 spsc_ring_available(const struct spsc_ring *ring)
{
	u32 head = READ_ONCE(ring->head);
	u32 tail = READ_ONCE(ring->tail);

	return (head - tail) & ring->mask;
}

/**
 * spsc_ring_space - Return number of free slots for the producer.
 */
static inline u32 spsc_ring_space(const struct spsc_ring *ring)
{
	u32 head = READ_ONCE(ring->head);
	u32 tail = READ_ONCE(ring->tail);

	return (tail - head - 1) & ring->mask;
}

/* ── Per-CPU variant ─────────────────────────────────────── */

/**
 * DEFINE_PER_CPU_SPSC_RING - Define a per-CPU SPSC ring buffer
 * @name:  variable name
 * @type:  element type
 * @size:  number of elements per ring (power of 2)
 */
#define DEFINE_PER_CPU_SPSC_RING(name, type, size)			\
	static DEFINE_PER_CPU(type, __spsc_##name##_slots[size]);	\
	static DEFINE_PER_CPU(struct spsc_ring, name) = {		\
		.slots		= NULL,	/* set at init */		\
		.slot_size	= sizeof(type),				\
		.mask		= (size) - 1,				\
		.head		= 0,					\
		.tail		= 0,					\
	}

#endif /* _LINUX_SPSC_RING_H */
