/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _DRM_GEM_DMA_SAFE_H_
#define _DRM_GEM_DMA_SAFE_H_

/*
 * drm_gem_dma_safe — safe GEM DMA buffer allocation and mapping.
 *
 * Wraps drm_gem_dma_helper with automatic DMA mapping tracking
 * via the rust_core dma_safe framework.  Every GEM object carries
 * a dma_safe_map so that unmapping on destroy is guaranteed.
 *
 * Usage in a driver:
 *   struct drm_gem_dma_safe_obj *obj = drm_gem_dma_safe_alloc(dev, size);
 *   if (IS_ERR(obj)) return PTR_ERR(obj);
 *   // use obj->map->dma_addr for the hardware address
 *   // free happens automatically via devres on DRM file close
 */

#include <linux/types.h>
#include <drm/drm_device.h>
#include <drm/drm_gem.h>

struct dma_safe_map;

struct drm_gem_dma_safe_obj {
	struct drm_gem_base		base;
	struct dma_safe_map		*map;   /* from rust_core */
	void				*cpu_addr;
	size_t				size;
};

struct drm_gem_dma_safe_obj *
drm_gem_dma_safe_alloc(struct drm_device *drm, size_t size);
void drm_gem_dma_safe_free(struct drm_gem_dma_safe_obj *obj);

#endif /* _DRM_GEM_DMA_SAFE_H_ */
