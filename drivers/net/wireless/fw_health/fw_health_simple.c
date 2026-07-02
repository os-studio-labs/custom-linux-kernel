// SPDX-License-Identifier: GPL-2.0
/*
 * fw_health — C-only fallback (used when CONFIG_RUST is not set).
 *
 * Provides the same API as the Rust implementation with a simple
 * state machine.  No fancy atomics; plain integer state.
 */

#include <linux/slab.h>
#include <linux/export.h>
#include <linux/jiffies.h>
#include <linux/atomic.h>
#include "fw_health.h"

struct fw_health {
	enum fw_health_state	state;
	unsigned int		crash_count;
	unsigned int		recovery_count;
	unsigned long		timeout_jiffies;
	unsigned long		last_heartbeat;
	const struct fw_health_ops *ops;
	void			*priv;
	struct device		*dev;
};

struct fw_health *rust_fw_health_alloc(struct device *dev,
				       unsigned long timeout_ms,
				       void *ops, void *priv)
{
	struct fw_health *h = kzalloc(sizeof(*h), GFP_KERNEL);
	if (!h)
		return NULL;

	h->state = FW_HEALTH_OK;
	h->timeout_jiffies = msecs_to_jiffies(timeout_ms);
	h->last_heartbeat = jiffies;
	h->ops = ops;
	h->priv = priv;
	h->dev = dev;
	return h;
}
EXPORT_SYMBOL_GPL(rust_fw_health_alloc);

void rust_fw_health_free(struct fw_health *h)
{
	kfree(h);
}
EXPORT_SYMBOL_GPL(rust_fw_health_free);

void rust_fw_health_report_ok(struct fw_health *h)
{
	if (!h)
		return;
	h->last_heartbeat = jiffies;
	if (h->state == FW_HEALTH_RECOVERING)
		h->state = FW_HEALTH_OK;
	if (h->state == FW_HEALTH_HUNG)
		h->state = FW_HEALTH_OK;
}
EXPORT_SYMBOL_GPL(rust_fw_health_report_ok);

void rust_fw_health_report_hung(struct fw_health *h)
{
	if (h)
		h->state = FW_HEALTH_HUNG;
}
EXPORT_SYMBOL_GPL(rust_fw_health_report_hung);

void rust_fw_health_report_crash(struct fw_health *h)
{
	if (h) {
		h->state = FW_HEALTH_CRASHED;
		h->crash_count++;
	}
}
EXPORT_SYMBOL_GPL(rust_fw_health_report_crash);

int rust_fw_health_get_state(struct fw_health *h)
{
	return h ? h->state : FW_HEALTH_DEAD;
}
EXPORT_SYMBOL_GPL(rust_fw_health_get_state);

unsigned int rust_fw_health_get_crash_count(struct fw_health *h)
{
	return h ? h->crash_count : 0;
}
EXPORT_SYMBOL_GPL(rust_fw_health_get_crash_count);

unsigned int rust_fw_health_get_recovery_count(struct fw_health *h)
{
	return h ? h->recovery_count : 0;
}
EXPORT_SYMBOL_GPL(rust_fw_health_get_recovery_count);

int rust_fw_health_check(struct fw_health *h)
{
	if (!h)
		return -1;
	if (h->state == FW_HEALTH_DEAD)
		return -1;
	if (h->state != FW_HEALTH_OK && h->state != FW_HEALTH_RECOVERING)
		return 0;

	if (time_after(jiffies, h->last_heartbeat + h->timeout_jiffies)) {
		h->state = FW_HEALTH_HUNG;
		return 0;
	}
	return 1;
}
EXPORT_SYMBOL_GPL(rust_fw_health_check);

void rust_fw_health_recovery_succeeded(struct fw_health *h)
{
	if (h) {
		h->state = FW_HEALTH_OK;
		h->recovery_count++;
		h->last_heartbeat = jiffies;
	}
}
EXPORT_SYMBOL_GPL(rust_fw_health_recovery_succeeded);

void rust_fw_health_recovery_failed(struct fw_health *h)
{
	if (h)
		h->state = FW_HEALTH_DEAD;
}
EXPORT_SYMBOL_GPL(rust_fw_health_recovery_failed);
