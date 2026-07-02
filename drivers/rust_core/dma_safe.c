// SPDX-License-Identifier: GPL-2.0
/*
 * dma_safe — C bridge to Rust DMA safety tracking.
 *
 * All memory allocation and map tracking is done in Rust for
 * type safety.  This C file provides the public entry points.
 */

#include <linux/slab.h>
#include <linux/export.h>
#include <linux/dma-mapping.h>
#include <linux/device.h>
#include <linux/skbuff.h>
#include "dma_safe.h"

/* Rust implementation */
extern struct dma_safe_map *rust_dma_map_area(struct device *dev,
					      void *cpu_addr, size_t len,
					      enum dma_safe_dir dir);
extern void rust_dma_unmap(struct dma_safe_map *map);
extern struct dma_safe_map *rust_devm_dma_map_area(struct device *dev,
						   void *cpu_addr, size_t len,
						   enum dma_safe_dir dir);

struct dma_safe_map *dma_safe_map_area(struct device *dev,
				       void *cpu_addr, size_t len,
				       enum dma_safe_dir dir)
{
	return rust_dma_map_area(dev, cpu_addr, len, dir);
}
EXPORT_SYMBOL_GPL(dma_safe_map_area);

struct dma_safe_map *dma_safe_map_skb(struct device *dev,
				      struct sk_buff *skb,
				      enum dma_safe_dir dir)
{
	return rust_dma_map_area(dev, skb->data, skb->len, dir);
}
EXPORT_SYMBOL_GPL(dma_safe_map_skb);

struct dma_safe_map *dma_safe_map_sg(struct device *dev,
				     struct scatterlist *sg, int nents,
				     enum dma_safe_dir dir)
{
	return rust_dma_map_area(dev, sg_virt(sg),
				 sg->length * nents, dir);
}
EXPORT_SYMBOL_GPL(dma_safe_map_sg);

void dma_safe_unmap(struct dma_safe_map *map)
{
	rust_dma_unmap(map);
}
EXPORT_SYMBOL_GPL(dma_safe_unmap);

struct dma_safe_map *devm_dma_safe_map_area(struct device *dev,
					    void *cpu_addr, size_t len,
					    enum dma_safe_dir dir)
{
	return rust_devm_dma_map_area(dev, cpu_addr, len, dir);
}
EXPORT_SYMBOL_GPL(devm_dma_safe_map_area);
