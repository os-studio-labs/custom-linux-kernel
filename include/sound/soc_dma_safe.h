/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _SOUND_SOC_DMA_SAFE_H_
#define _SOUND_SOC_DMA_SAFE_H_

/*
 * soc_dma_safe — safe ALSA/ASoC DMA buffer management.
 *
 * Wraps snd_pcm_lib_* DMA allocation with dma_safe_map tracking
 * so that audio DMA buffers are correctly unmapped on PCM close
 * or driver unbind.
 */

#include <linux/types.h>
#include <sound/soc.h>

struct dma_safe_map;
struct snd_pcm_substream;

struct snd_dma_safe_buf {
	struct dma_safe_map	*map;
	void			*cpu_addr;
	dma_addr_t		dma_addr;
	size_t			size;
};

int snd_dma_safe_alloc_pages(struct snd_pcm_substream *substream,
			     size_t size);
void snd_dma_safe_free_pages(struct snd_pcm_substream *substream);

#endif /* _SOUND_SOC_DMA_SAFE_H_ */
