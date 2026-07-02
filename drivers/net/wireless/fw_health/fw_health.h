/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _FW_HEALTH_H_
#define _FW_HEALTH_H_

#include <linux/types.h>
#include <linux/device.h>

/*
 * fw_health — firmware health monitoring and recovery framework.
 *
 * Any wireless driver can embed a struct fw_health to automatically
 * detect firmware hangs/crashes, log diagnostics, and trigger
 * recovery.  The core bookkeeping runs in Rust for memory safety.
 */

enum fw_health_state {
	FW_HEALTH_OK,
	FW_HEALTH_HUNG,
	FW_HEALTH_CRASHED,
	FW_HEALTH_RECOVERING,
	FW_HEALTH_DEAD,
};

struct fw_health;

struct fw_health_ops {
	int (*recover)(struct fw_health *h, void *priv);
};

struct fw_health *fw_health_alloc(struct device *dev, unsigned long timeout_ms,
				  const struct fw_health_ops *ops, void *priv);
void fw_health_free(struct fw_health *h);

void fw_health_report_ok(struct fw_health *h);
void fw_health_report_hung(struct fw_health *h);
void fw_health_report_crash(struct fw_health *h);

enum fw_health_state fw_health_get_state(struct fw_health *h);
unsigned int fw_health_get_crash_count(struct fw_health *h);
unsigned int fw_health_get_recovery_count(struct fw_health *h);

#endif /* _FW_HEALTH_H_ */
