// SPDX-License-Identifier: GPL-2.0
/*
 * fw_health — C bridge to Rust firmware health monitor.
 *
 * Thin wrappers that forward calls to the Rust implementation
 * in fw_health_core.rs.
 */

#include <linux/slab.h>
#include <linux/export.h>
#include <linux/device.h>
#include "fw_health.h"

/* Rust implementation (no_mangle, extern "C") */
extern struct fw_health *rust_fw_health_alloc(struct device *dev,
					      unsigned long timeout_ms,
					      void *ops, void *priv);
extern void rust_fw_health_free(struct fw_health *h);
extern void rust_fw_health_report_ok(struct fw_health *h);
extern void rust_fw_health_report_hung(struct fw_health *h);
extern void rust_fw_health_report_crash(struct fw_health *h);
extern int rust_fw_health_get_state(struct fw_health *h);
extern unsigned int rust_fw_health_get_crash_count(struct fw_health *h);
extern unsigned int rust_fw_health_get_recovery_count(struct fw_health *h);

struct fw_health *fw_health_alloc(struct device *dev, unsigned long timeout_ms,
				  const struct fw_health_ops *ops, void *priv)
{
	return rust_fw_health_alloc(dev, timeout_ms, (void *)ops, priv);
}
EXPORT_SYMBOL_GPL(fw_health_alloc);

void fw_health_free(struct fw_health *h)
{
	rust_fw_health_free(h);
}
EXPORT_SYMBOL_GPL(fw_health_free);

void fw_health_report_ok(struct fw_health *h)
{
	rust_fw_health_report_ok(h);
}
EXPORT_SYMBOL_GPL(fw_health_report_ok);

void fw_health_report_hung(struct fw_health *h)
{
	rust_fw_health_report_hung(h);
}
EXPORT_SYMBOL_GPL(fw_health_report_hung);

void fw_health_report_crash(struct fw_health *h)
{
	rust_fw_health_report_crash(h);
}
EXPORT_SYMBOL_GPL(fw_health_report_crash);

enum fw_health_state fw_health_get_state(struct fw_health *h)
{
	return rust_fw_health_get_state(h);
}
EXPORT_SYMBOL_GPL(fw_health_get_state);

unsigned int fw_health_get_crash_count(struct fw_health *h)
{
	return rust_fw_health_get_crash_count(h);
}
EXPORT_SYMBOL_GPL(fw_health_get_crash_count);

unsigned int fw_health_get_recovery_count(struct fw_health *h)
{
	return rust_fw_health_get_recovery_count(h);
}
EXPORT_SYMBOL_GPL(fw_health_get_recovery_count);
