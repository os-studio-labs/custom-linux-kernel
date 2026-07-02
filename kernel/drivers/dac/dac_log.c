// SPDX-License-Identifier: GPL-2.0
/*
 * dac_log — per-driver ring-buffer logger exposed via sysfs.
 *
 * Every driver sandbox gets a ring buffer (512 entries).  Logs are
 * written via dac_driver_log() and read via /sys/kernel/drivers/<name>/log.
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/export.h>
#include <linux/dac_log.h>

/* ── Driver context ─────────────────────────────────────── */
/* Layout must match dac_core.rs */
#define LOG_RING_SIZE		512

struct dac_log_state {
	unsigned long	tail;
	unsigned long	head;
	struct dac_log_entry	buf[LOG_RING_SIZE];
};

/* Per-driver log state indexed by driver_id (1..4096). */
#define MAX_DAC_DRIVERS		4096
static struct dac_log_state *dac_logs[MAX_DAC_DRIVERS];
static DEFINE_SPINLOCK(dac_log_lock);

/*
 * dac_driver_log — write a log entry for a driver.
 */
void dac_driver_log(u32 driver_id, u32 severity, const char *fmt, ...)
{
	struct dac_log_state *ls;
	unsigned long head, tail, idx;
	va_list args;

	if (driver_id == 0 || driver_id >= MAX_DAC_DRIVERS)
		return;

	spin_lock(&dac_log_lock);
	ls = dac_logs[driver_id];
	if (!ls) {
		ls = kzalloc(sizeof(*ls), GFP_ATOMIC);
		if (!ls) {
			spin_unlock(&dac_log_lock);
			return;
		}
		dac_logs[driver_id] = ls;
	}
	head = ls->head;
	idx = head % LOG_RING_SIZE;
	ls->buf[idx].timestamp = ktime_get_real_fast_ns();
	ls->buf[idx].severity = severity;
	va_start(args, fmt);
	vsnprintf(ls->buf[idx].msg, sizeof(ls->buf[idx].msg), fmt, args);
	va_end(args);
	ls->head = head + 1;
	if (ls->head - ls->tail > LOG_RING_SIZE)
		ls->tail = ls->head - LOG_RING_SIZE;
	spin_unlock(&dac_log_lock);
}
EXPORT_SYMBOL_GPL(dac_driver_log);

/*
 * dac_driver_log_read — read log entries (one sysfs page at a time).
 */
ssize_t dac_driver_log_read(u32 driver_id, char __user *buf,
			    size_t len, loff_t *off)
{
	struct dac_log_state *ls;
	ssize_t total = 0;
	char line[320];
	int n;

	if (driver_id == 0 || driver_id >= MAX_DAC_DRIVERS)
		return 0;

	spin_lock(&dac_log_lock);
	ls = dac_logs[driver_id];
	if (!ls) {
		spin_unlock(&dac_log_lock);
		return 0;
	}

	while (total < len - sizeof(line) && ls->tail < ls->head) {
		unsigned long idx = ls->tail % LOG_RING_SIZE;

		n = snprintf(line, sizeof(line), "[%llu] sev=%u %s\n",
			     ls->buf[idx].timestamp,
			     ls->buf[idx].severity,
			     ls->buf[idx].msg);
		ls->tail++;

		spin_unlock(&dac_log_lock);
		if (copy_to_user(buf + total, line, min((size_t)n, len - total)))
			return -EFAULT;
		total += min((size_t)n, len - total);
		if (total >= len)
			break;
		spin_lock(&dac_log_lock);
	}
	spin_unlock(&dac_log_lock);

	return total;
}
EXPORT_SYMBOL_GPL(dac_driver_log_read);

/*
 * dac_driver_log_read_kernel — read log entries into kernel buffer (sysfs).
 */
ssize_t dac_driver_log_read_kernel(u32 driver_id, char *buf,
				   size_t len, loff_t *off)
{
	struct dac_log_state *ls;
	ssize_t total = 0;
	char line[320];
	int n;

	if (driver_id == 0 || driver_id >= MAX_DAC_DRIVERS)
		return 0;

	spin_lock(&dac_log_lock);
	ls = dac_logs[driver_id];
	if (!ls) {
		spin_unlock(&dac_log_lock);
		return 0;
	}

	while (total < len - sizeof(line) && ls->tail < ls->head) {
		unsigned long idx = ls->tail % LOG_RING_SIZE;

		n = snprintf(line, sizeof(line), "[%llu] sev=%u %s\n",
			     ls->buf[idx].timestamp,
			     ls->buf[idx].severity,
			     ls->buf[idx].msg);
		ls->tail++;

		spin_unlock(&dac_log_lock);
		n = min((size_t)n, len - total);
		memcpy(buf + total, line, n);
		total += n;
		if (total >= len)
			break;
		spin_lock(&dac_log_lock);
	}
	spin_unlock(&dac_log_lock);

	return total;
}
EXPORT_SYMBOL_GPL(dac_driver_log_read_kernel);

static void __exit dac_log_cleanup(void)
{
	int i;

	for (i = 0; i < MAX_DAC_DRIVERS; i++) {
		kfree(dac_logs[i]);
		dac_logs[i] = NULL;
	}
}
__exitcall(dac_log_cleanup);
