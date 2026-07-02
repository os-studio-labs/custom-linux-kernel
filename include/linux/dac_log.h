/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_DAC_LOG_H_
#define _LINUX_DAC_LOG_H_

#include <linux/types.h>

struct dac_log_entry {
	u64	timestamp;
	u32	severity;
	char	msg[240];
};

#if IS_ENABLED(CONFIG_DRIVER_API_CENTRE)

void dac_driver_log(u32 driver_id, u32 severity, const char *fmt, ...)
	__printf(3, 4);
ssize_t dac_driver_log_read(u32 driver_id, char __user *buf, size_t len,
			    loff_t *off);

#else

static inline void dac_driver_log(u32 driver_id, u32 severity,
				  const char *fmt, ...) { }
static inline ssize_t dac_driver_log_read(u32 driver_id, char __user *buf,
					  size_t len, loff_t *off)
{
	return 0;
}

#endif /* CONFIG_DRIVER_API_CENTRE */

#endif /* _LINUX_DAC_LOG_H_ */
