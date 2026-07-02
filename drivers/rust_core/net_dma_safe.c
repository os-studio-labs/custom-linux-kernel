// SPDX-License-Identifier: GPL-2.0
/*
 * net_dma_safe — safe NIC RX/TX DMA buffer management.
 *
 * Integration point for rust_core dma_safe maps in networking drivers.
 * Provides ring-buffer tracking so every RX buffer is automatically
 * unmapped on ring cleanup.
 */

#include <linux/slab.h>
#include <linux/export.h>
#include <linux/device.h>
#include <linux/skbuff.h>
#include "dma_safe.h"

struct net_rx_safe_ring *
net_rx_safe_alloc(struct device *dev, int count, size_t buf_size)
{
	struct net_rx_safe_ring *ring;
	int i;

	ring = kzalloc(sizeof(*ring), GFP_KERNEL);
	if (!ring)
		return NULL;

	ring->maps = kcalloc(count, sizeof(struct dma_safe_map *), GFP_KERNEL);
	if (!ring->maps) {
		kfree(ring);
		return NULL;
	}

	ring->count = count;
	ring->next = 0;

	/* Pre-allocate RX buffers with DMA maps */
	for (i = 0; i < count; i++) {
		void *buf = kzalloc(buf_size, GFP_KERNEL);
		if (!buf)
			goto fail;

		ring->maps[i] = dma_safe_map_area(dev, buf, buf_size,
						  DMA_SAFE_FROM_DEVICE);
		if (!ring->maps[i]) {
			kfree(buf);
			goto fail;
		}
	}

	return ring;

fail:
	while (i-- > 0) {
		if (ring->maps[i]) {
			void *cpu = NULL; /* retrieve from map if possible */
			dma_safe_unmap(ring->maps[i]);
		}
	}
	kfree(ring->maps);
	kfree(ring);
	return NULL;
}
EXPORT_SYMBOL_GPL(net_rx_safe_alloc);

void net_rx_safe_free(struct net_rx_safe_ring *ring)
{
	int i;

	if (!ring)
		return;

	for (i = 0; i < ring->count; i++) {
		if (ring->maps[i])
			dma_safe_unmap(ring->maps[i]);
	}
	kfree(ring->maps);
	kfree(ring);
}
EXPORT_SYMBOL_GPL(net_rx_safe_free);

struct dma_safe_map *net_tx_safe_map_skb(struct device *dev,
					 struct sk_buff *skb)
{
	return dma_safe_map_skb(dev, skb, DMA_SAFE_TO_DEVICE);
}
EXPORT_SYMBOL_GPL(net_tx_safe_map_skb);
