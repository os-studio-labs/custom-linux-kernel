/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_USB_DMA_SAFE_H_
#define _LINUX_USB_DMA_SAFE_H_

/*
 * usb_dma_safe — safe USB transfer buffer management.
 *
 * Wraps USB URB allocation and DMA mapping so that buffers are
 * automatically freed and unmapped on URB completion or error.
 * Eliminates the common "URB leak on disconnect" class of bugs.
 */

#include <linux/types.h>
#include <linux/usb.h>

struct dma_safe_map;

struct usb_safe_urb {
	struct urb		*urb;
	struct dma_safe_map	*map;
	void			*buf;
	size_t			len;
};

struct usb_safe_urb *usb_safe_alloc_urb(struct usb_device *udev,
					int pipe, size_t len, gfp_t flags);
int usb_safe_submit_urb(struct usb_safe_urb *surb, gfp_t flags);
void usb_safe_free_urb(struct usb_safe_urb *surb);

#endif /* _LINUX_USB_DMA_SAFE_H_ */
