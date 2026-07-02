// SPDX-License-Identifier: GPL-2.0
/*
 * dac_sandbox — per-driver fault isolation and recovery.
 *
 * Provides lightweight helpers called from drivers/base/dd.c to set
 * up the DAC sandbox context for every driver probe/remove.
 *
 * The sandbox tracks driver state (alive/faulted/dead), provides
 * fw_health heartbeats, and logs all API calls through the DAC gateway.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/driver.h>
#include <linux/slab.h>
#include <linux/export.h>
#include <linux/fw_health.h>
#include <linux/dac_api.h>
#include <linux/dac_log.h>

extern int dac_sysfs_register(u32 driver_id, const char *name);
extern void dac_sysfs_unregister(const char *name);

/* Rust-implemented DAC core functions */
extern u32 dac_register_driver(const char *name, unsigned long timeout_ms);
extern void dac_deregister_driver(u32 driver_id);
extern void dac_driver_heartbeat(u32 driver_id);
extern void dac_driver_faulted(u32 driver_id);

/* Gateway context management */
extern void dac_set_current_driver(u32 id);

/* ── Fast driver-ID lookup by driver pointer ──────────── */

#define DAC_HT_SIZE	256
static struct hlist_head dac_driver_ht[DAC_HT_SIZE];
static DEFINE_SPINLOCK(dac_ht_lock);

struct dac_driver_map {
	struct device_driver	*drv;
	u32			dac_id;
	struct hlist_node	hash;
	struct rcu_head		rcu;
};

static u32 dac_ht_hash(struct device_driver *drv)
{
	return hash_ptr(drv, 8) % DAC_HT_SIZE;
}

u32 dac_lookup_driver_id(struct device_driver *drv)
{
	struct dac_driver_map *map;
	u32 h = dac_ht_hash(drv);

	rcu_read_lock();
	hlist_for_each_entry_rcu(map, &dac_driver_ht[h], hash) {
		if (map->drv == drv) {
			rcu_read_unlock();
			return map->dac_id;
		}
	}
	rcu_read_unlock();
	return 0;
}
EXPORT_SYMBOL_GPL(dac_lookup_driver_id);

static int dac_add_driver_map(struct device_driver *drv, u32 dac_id)
{
	struct dac_driver_map *map;
	u32 h = dac_ht_hash(drv);

	map = kzalloc(sizeof(*map), GFP_KERNEL);
	if (!map)
		return -ENOMEM;
	map->drv = drv;
	map->dac_id = dac_id;
	spin_lock(&dac_ht_lock);
	hlist_add_head_rcu(&map->hash, &dac_driver_ht[h]);
	spin_unlock(&dac_ht_lock);
	return 0;
}

static void dac_remove_driver_map(struct device_driver *drv)
{
	struct dac_driver_map *map;
	u32 h = dac_ht_hash(drv);

	spin_lock(&dac_ht_lock);
	hlist_for_each_entry(map, &dac_driver_ht[h], hash) {
		if (map->drv == drv) {
			hlist_del_rcu(&map->hash);
			spin_unlock(&dac_ht_lock);
			kfree_rcu(map, rcu);
			return;
		}
	}
	spin_unlock(&dac_ht_lock);
}

/* ── Lazy sandbox setup (called from dd.c) ────────────── */

/*
 * dac_setup_for_driver — ensure a sandbox exists for this driver.
 *
 * Called at the start of every probe and remove.  Lazily registers
 * the driver with the DAC core on first use.  Returns the DAC driver_id
 * (0 = no sandboxing, which is a valid fallback).
 */
u32 dac_setup_for_driver(struct device_driver *drv)
{
	u32 dac_id;

	if (!drv)
		return 0;

	/* Fast path: already registered */
	dac_id = dac_lookup_driver_id(drv);
	if (dac_id)
		goto out_heartbeat;

	/* Slow path: lazy registration */
	dac_id = dac_register_driver(drv->name ?: "unnamed", 5000);
	if (dac_id == 0) {
		pr_debug("dac: lazy-register failed for %s\n", drv->name);
		return 0;
	}

	if (dac_add_driver_map(drv, dac_id)) {
		dac_deregister_driver(dac_id);
		return 0;
	}

	/* Create sysfs node under /sys/kernel/dac/<name>/ */
	dac_sysfs_register(dac_id, drv->name);

	pr_debug("dac: lazily registered driver %s (id=%u)\n",
		 drv->name, dac_id);

out_heartbeat:
	dac_driver_heartbeat(dac_id);
	return dac_id;
}
EXPORT_SYMBOL_GPL(dac_setup_for_driver);

/*
 * dac_teardown_for_driver — called when a driver is unregistered.
 */
void dac_teardown_for_driver(struct device_driver *drv)
{
	u32 dac_id;

	if (!drv)
		return;

	dac_id = dac_lookup_driver_id(drv);
	if (dac_id == 0)
		return;

	dac_sysfs_unregister(drv->name);
	dac_remove_driver_map(drv);
	dac_deregister_driver(dac_id);
	pr_debug("dac: torn down driver %s (id=%u)\n", drv->name, dac_id);
}
EXPORT_SYMBOL_GPL(dac_teardown_for_driver);
