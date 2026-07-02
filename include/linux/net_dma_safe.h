/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_NET_DMA_SAFE_H_
#define _LINUX_NET_DMA_SAFE_H_

/*
 * net_dma_safe — safe RX/TX DMA buffer management for NIC drivers.
 *
 * Every RX buffer and TX skb gets a dma_safe_map so that unmapping
 * is guaranteed on free/error.  Eliminates the most common class
 * of NIC driver crashes: DMA mapping leaks on ring overflow.
 */

#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>

struct dma_safe_map;

/* ── RX ring buffer management ────────────────────────── */

struct net_rx_safe_ring {
	struct dma_safe_map	**maps;
	int			count;
	int			next;
};

struct net_rx_safe_ring *
net_rx_safe_alloc(struct device *dev, int count, size_t buf_size);
void net_rx_safe_free(struct net_rx_safe_ring *ring);

struct dma_safe_map *net_rx_safe_get(struct net_rx_safe_ring *ring);
int net_rx_safe_refill(struct net_rx_safe_ring *ring);

/* ── TX buffer tracking ──────────────────────────────── */

struct dma_safe_map *net_tx_safe_map_skb(struct device *dev,
					struct sk_buff *skb);

#endif /* _LINUX_NET_DMA_SAFE_H_ */
