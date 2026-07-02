// SPDX-License-Identifier: GPL-2.0
/*
 * dac_sysfs — per-driver sysfs interface under /sys/kernel/dac/<name>/
 *
 * Each registered driver gets:
 *   /sys/kernel/dac/<name>/state   — sandbox state (active/faulted/dead)
 *   /sys/kernel/dac/<name>/crashes  — crash counter
 *   /sys/kernel/dac/<name>/log      — ring-buffer log (read-only, drains)
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/export.h>
#include <linux/string.h>
#include <linux/stat.h>
#include <linux/uaccess.h>
#include <linux/dac_api.h>
#include <linux/dac_log.h>

/* ── DAC sysfs top-level kset ─────────────────────────── */

static struct kset *dac_kset;

/* ── Per-driver sysfs attributes ──────────────────────── */

struct dac_sysfs_driver {
	struct kobject		kobj;
	u32			driver_id;
	char			name[48];
};

/* Forward declarations from DAC core / sandbox */
extern u32 dac_lookup_driver_id(struct device_driver *drv);
extern long dac_driver_state_read(u32 driver_id);
extern u32 dac_driver_crash_count(u32 driver_id);

/* ── State attribute ───────────────────────────────────── */

static ssize_t state_show(struct kobject *kobj, struct kobj_attribute *attr,
			  char *buf)
{
	struct dac_sysfs_driver *sd = container_of(kobj, struct dac_sysfs_driver, kobj);
	long state;

	state = dac_driver_state_read(sd->driver_id);
	if (state < 0)
		return sysfs_emit(buf, "unknown\n");

	switch (state) {
	case 0:  return sysfs_emit(buf, "unregistered\n");
	case 1:  return sysfs_emit(buf, "active\n");
	case 2:  return sysfs_emit(buf, "faulted\n");
	case 3:  return sysfs_emit(buf, "recovering\n");
	case 4:  return sysfs_emit(buf, "dead\n");
	default: return sysfs_emit(buf, "unknown\n");
	}
}
static struct kobj_attribute state_attr = __ATTR_RO(state);

/* ── Crashes attribute ──────────────────────────────────── */

static ssize_t crashes_show(struct kobject *kobj, struct kobj_attribute *attr,
			    char *buf)
{
	struct dac_sysfs_driver *sd = container_of(kobj, struct dac_sysfs_driver, kobj);
	u32 cnt = dac_driver_crash_count(sd->driver_id);

	return sysfs_emit(buf, "%u\n", cnt);
}
static struct kobj_attribute crashes_attr = __ATTR_RO(crashes);

/* ── Log attribute ──────────────────────────────────────── */

static ssize_t log_read(struct file *filp, struct kobject *kobj,
			struct bin_attribute *attr,
			char *buf, loff_t off, size_t count)
{
	struct dac_sysfs_driver *sd = container_of(kobj, struct dac_sysfs_driver, kobj);

	return dac_driver_log_read_kernel(sd->driver_id, buf, count, &off);
}
static struct bin_attribute log_attr = __BIN_ATTR(log, 0444, log_read, NULL, 0);

/* ── Driver sysfs release ──────────────────────────────── */

static void dac_sysfs_release(struct kobject *kobj)
{
	struct dac_sysfs_driver *sd = container_of(kobj, struct dac_sysfs_driver, kobj);
	kfree(sd);
}

static struct attribute *dac_drv_attrs[] = {
	&state_attr.attr,
	&crashes_attr.attr,
	NULL,
};
ATTRIBUTE_GROUPS(dac_drv);

static struct bin_attribute *dac_drv_bin_attrs[] = {
	&log_attr,
	NULL,
};

static const struct kobj_type dac_drv_ktype = {
	.release	= dac_sysfs_release,
	.sysfs_ops	= &kobj_sysfs_ops,
	.default_groups	= dac_drv_groups,
	.default_bin_attrs = dac_drv_bin_attrs,
};

/* ── Register a driver's sysfs node ─────────────────────── */

int dac_sysfs_register(u32 driver_id, const char *name)
{
	struct dac_sysfs_driver *sd;
	int ret;

	if (!dac_kset || driver_id == 0 || !name)
		return -EINVAL;

	sd = kzalloc(sizeof(*sd), GFP_KERNEL);
	if (!sd)
		return -ENOMEM;

	sd->driver_id = driver_id;
	strscpy(sd->name, name, sizeof(sd->name));

	ret = kobject_init_and_add(&sd->kobj, &dac_drv_ktype,
				   &dac_kset->kobj, "%s", name);
	if (ret) {
		kobject_put(&sd->kobj);
		return ret;
	}

	/* Make log bin attribute size match the ring buffer */
	log_attr.size = 512 * sizeof(struct dac_log_entry);

	kobject_uevent(&sd->kobj, KOBJ_ADD);
	return 0;
}

/* ── Unregister a driver's sysfs node ───────────────────── */

void dac_sysfs_unregister(const char *name)
{
	struct kobject *kobj;

	if (!dac_kset || !name)
		return;

	kobj = kobject_find_obj(&dac_kset->kobj, name);
	if (kobj) {
		kobject_del(kobj);
		kobject_put(kobj);
	}
}

/* ── Init / cleanup ────────────────────────────────────── */

static int __init dac_sysfs_init(void)
{
	dac_kset = kset_create_and_add("dac", NULL, kernel_kobj);
	if (!dac_kset)
		return -ENOMEM;

	pr_info("dac: created /sys/kernel/dac/ sysfs interface\n");
	return 0;
}
late_initcall(dac_sysfs_init);

static void __exit dac_sysfs_exit(void)
{
	if (dac_kset) {
		kset_unregister(dac_kset);
		dac_kset = NULL;
	}
}
__exitcall(dac_sysfs_exit);

/* Export for use by dac_sandbox */
EXPORT_SYMBOL_GPL(dac_sysfs_register);
EXPORT_SYMBOL_GPL(dac_sysfs_unregister);
