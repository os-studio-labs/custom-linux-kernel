// SPDX-License-Identifier: GPL-2.0
/*
 * usb_dma_safe — safe USB URB allocation with automatic DMA tracking.
 */

#include <linux/slab.h>
#include <linux/export.h>
#include <linux/usb.h>
#include "dma_safe.h"

struct usb_safe_urb *usb_safe_alloc_urb(struct usb_device *udev,
					int pipe, size_t len, gfp_t flags)
{
	struct usb_safe_urb *surb;
	void *buf;

	surb = kzalloc(sizeof(*surb), flags);
	if (!surb)
		return NULL;

	buf = kzalloc(len, flags);
	if (!buf) {
		kfree(surb);
		return NULL;
	}

	surb->urb = usb_alloc_urb(0, flags);
	if (!surb->urb) {
		kfree(buf);
		kfree(surb);
		return NULL;
	}

	surb->buf = buf;
	surb->len = len;

	/* Create DMA-safe mapping */
	surb->map = dma_safe_map_area(&udev->dev, buf, len,
				      usb_pipeout(pipe) ?
				      DMA_SAFE_TO_DEVICE :
				      DMA_SAFE_FROM_DEVICE);
	if (!surb->map) {
		usb_free_urb(surb->urb);
		kfree(buf);
		kfree(surb);
		return NULL;
	}

	if (usb_pipein(pipe))
		usb_fill_bulk_urb(surb->urb, udev, pipe, buf, len,
				  NULL, NULL);
	else
		usb_fill_bulk_urb(surb->urb, udev, pipe, buf, len,
				  NULL, NULL);

	return surb;
}
EXPORT_SYMBOL_GPL(usb_safe_alloc_urb);

int usb_safe_submit_urb(struct usb_safe_urb *surb, gfp_t flags)
{
	if (!surb || !surb->urb)
		return -EINVAL;

	return usb_submit_urb(surb->urb, flags);
}
EXPORT_SYMBOL_GPL(usb_safe_submit_urb);

void usb_safe_free_urb(struct usb_safe_urb *surb)
{
	if (!surb)
		return;

	if (surb->urb)
		usb_kill_urb(surb->urb);

	if (surb->map)
		dma_safe_unmap(surb->map);

	usb_free_urb(surb->urb);
	kfree(surb->buf);
	kfree(surb);
}
EXPORT_SYMBOL_GPL(usb_safe_free_urb);
