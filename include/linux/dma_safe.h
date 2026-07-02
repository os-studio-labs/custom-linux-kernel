/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_DMA_SAFE_H_
#define _LINUX_DMA_SAFE_H_

/*
 * dma_safe — RAII-style DMA mappings for any driver subsystem.
 *
 * Usage:
 *   struct dma_safe_map *map = dma_safe_map_skb(dev, skb, dir);
 *   if (IS_ERR(map)) return PTR_ERR(map);
 *   // ... use map->dma_addr ...
 *   dma_safe_unmap(map);  // or let devres auto-clean
 *
 * Every mapping carries its owning device, direction, and length so
 * that unmapping is always correct — eliminating the most common
 * class of DMA bugs (wrong direction, incomplete unmapping, double
 * free).
 */

#include <linux/types.h>
#include <linux/dma-mapping.h>
#include <linux/skbuff.h>
#include <linux/scatterlist.h>

enum dma_safe_dir {
	DMA_SAFE_TO_DEVICE	= DMA_TO_DEVICE,
	DMA_SAFE_FROM_DEVICE	= DMA_FROM_DEVICE,
	DMA_SAFE_BIDIRECTIONAL	= DMA_BIDIRECTIONAL,
};

struct dma_safe_map {
	struct device		*dev;
	dma_addr_t		dma_addr;
	size_t			len;
	enum dma_safe_dir	dir;
	bool			mapped;
};

/* ── Allocation & destruction ────────────────────────── */

struct dma_safe_map *dma_safe_map_area(struct device *dev,
				       void *cpu_addr, size_t len,
				       enum dma_safe_dir dir);
struct dma_safe_map *dma_safe_map_skb(struct device *dev,
				      struct sk_buff *skb,
				      enum dma_safe_dir dir);
struct dma_safe_map *dma_safe_map_sg(struct device *dev,
				     struct scatterlist *sg, int nents,
				     enum dma_safe_dir dir);
void dma_safe_unmap(struct dma_safe_map *map);

/* ── Devres-automated variant (no explicit free needed) ── */
struct dma_safe_map *devm_dma_safe_map_area(struct device *dev,
					    void *cpu_addr, size_t len,
					    enum dma_safe_dir dir);

#endif /* _LINUX_DMA_SAFE_H_ */
