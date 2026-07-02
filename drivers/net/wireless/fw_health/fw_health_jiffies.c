// SPDX-License-Identifier: GPL-2.0
/*
 * fw_health — jiffies/time helpers for Rust firmware health monitor.
 */
#include <linux/jiffies.h>
#include <linux/export.h>

unsigned long rust_helper_get_jiffies(void)
{
	return jiffies;
}
EXPORT_SYMBOL_GPL(rust_helper_get_jiffies);

int rust_helper_time_after(unsigned long a, unsigned long b)
{
	return time_after(a, b);
}
EXPORT_SYMBOL_GPL(rust_helper_time_after);
