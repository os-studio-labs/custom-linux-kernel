// SPDX-License-Identifier: GPL-2.0
/*
 * soc_dma_safe — safe ALSA/ASoC DMA buffer allocation.
 *
 * Wraps the standard ALSA DMA buffer API with dma_safe_map tracking
 * so that every audio buffer is correctly unmapped on PCM close.
 */

#include <linux/slab.h>
#include <linux/export.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/soc_dma_safe.h>
#include <linux/dma-mapping.h>

/* Forward declarations from rust_core */
struct dma_safe_map *dma_safe_map_area(struct device *dev,
				       void *cpu_addr, size_t len,
				       enum dma_safe_dir dir);
void dma_safe_unmap(struct dma_safe_map *map);

int snd_dma_safe_alloc_pages(struct snd_pcm_substream *substream,
			     size_t size)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_dma_buffer *dmab;
	struct dma_safe_map *map;
	int ret;

	ret = snd_pcm_lib_malloc_pages(substream, size);
	if (ret < 0)
		return ret;

	dmab = &runtime->dma_buffer;
	if (!dmab->area)
		return -ENOMEM;

	/* Wrap in a dma_safe_map for tracking */
	map = dma_safe_map_area(dmab->dev.dev, dmab->area, dmab->bytes,
				DMA_SAFE_BIDIRECTIONAL);
	if (!map) {
		snd_pcm_lib_free_pages(substream);
		return -ENOMEM;
	}

	/* Store map pointer in private area of the substream */
	runtime->private_data = map;
	return 0;
}
EXPORT_SYMBOL_GPL(snd_dma_safe_alloc_pages);

void snd_dma_safe_free_pages(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct dma_safe_map *map;

	map = runtime->private_data;
	if (map) {
		dma_safe_unmap(map);
		runtime->private_data = NULL;
	}

	snd_pcm_lib_free_pages(substream);
}
EXPORT_SYMBOL_GPL(snd_dma_safe_free_pages);
