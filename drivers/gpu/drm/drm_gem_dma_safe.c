// SPDX-License-Identifier: GPL-2.0
/*
 * drm_gem_dma_safe — safe GEM DMA buffer with automatic cleanup.
 *
 * Integrates the rust_core DMA safety wrappers into the DRM GEM
 * DMA helper framework so that every GEM object gets proper DMA
 * mapping tracking.
 */

#include <linux/slab.h>
#include <linux/export.h>
#include <drm/drm_device.h>
#include <drm/drm_gem.h>
#include <drm/drm_gem_dma_safe.h>
#include <drm/drm_prime.h>
#include <linux/dma-mapping.h>

/* Forward declaration for rust_core dma_safe */
struct dma_safe_map *devm_dma_safe_map_area(struct device *dev,
					    void *cpu_addr, size_t len,
					    enum dma_safe_dir dir);
void dma_safe_unmap(struct dma_safe_map *map);

struct drm_gem_dma_safe_obj *
drm_gem_dma_safe_alloc(struct drm_device *drm, size_t size)
{
	struct drm_gem_dma_safe_obj *obj;
	struct device *dev = drm->dev;
	int ret;

	obj = kzalloc(sizeof(*obj), GFP_KERNEL);
	if (!obj)
		return ERR_PTR(-ENOMEM);

	obj->size = size;

	/* Allocate CPU-accessible buffer */
	obj->cpu_addr = dma_alloc_coherent(dev, size,
					   &obj->base.dma_addr, GFP_KERNEL);
	if (!obj->cpu_addr) {
		kfree(obj);
		return ERR_PTR(-ENOMEM);
	}

	/* Wrap in a dma_safe_map for tracking */
	obj->map = devm_dma_safe_map_area(dev, obj->cpu_addr, size,
					  DMA_SAFE_BIDIRECTIONAL);
	if (!obj->map) {
		dma_free_coherent(dev, size, obj->cpu_addr, obj->base.dma_addr);
		kfree(obj);
		return ERR_PTR(-ENOMEM);
	}

	ret = drm_gem_object_init(drm, &obj->base.base, size);
	if (ret) {
		dma_safe_unmap(obj->map);
		dma_free_coherent(dev, size, obj->cpu_addr, obj->base.dma_addr);
		kfree(obj);
		return ERR_PTR(ret);
	}

	return obj;
}
EXPORT_SYMBOL_GPL(drm_gem_dma_safe_alloc);

void drm_gem_dma_safe_free(struct drm_gem_dma_safe_obj *obj)
{
	struct device *dev;

	if (!obj)
		return;

	dev = obj->base.base.dev->dev;

	drm_gem_object_release(&obj->base.base);

	if (obj->map)
		dma_safe_unmap(obj->map);

	if (obj->cpu_addr && obj->size)
		dma_free_coherent(dev, obj->size,
				  obj->cpu_addr, obj->base.dma_addr);

	kfree(obj);
}
EXPORT_SYMBOL_GPL(drm_gem_dma_safe_free);
