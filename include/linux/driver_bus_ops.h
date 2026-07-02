/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_DRIVER_BUS_OPS_H
#define _LINUX_DRIVER_BUS_OPS_H

/*
 * Clean bus/driver interface — a minimal, type-safe abstraction
 * for the driver model.
 *
 * PROBLEM:
 *   struct device_driver has ~20 field/vtable combinations.
 *   struct bus_type has ~30 methods. Adding a new bus type
 *   requires implementing ALL of them, many of which are
 *   optional but have no compile-time enforcement.
 *
 * SOLUTION:
 *   Define a minimal MUST_HAVE interface (struct bus_ops)
 *   and an OPTIONAL interface (struct bus_ext_ops).
 *   Drivers implement only what they need.
 *
 *   This is the foundation for Rust driver types.
 */

#include <linux/types.h>
#include <linux/device.h>
#include <linux/module.h>

struct device;
struct device_driver;

/*
 * Core bus operations — every bus must implement these.
 */
struct bus_ops {
	const char	*name;		/* Bus name (matches bus_type->name) */

	/* Match a device to a driver */
	int (*match)(struct device *dev, struct device_driver *drv);

	/* Bind a driver to a device */
	int (*probe)(struct device *dev);

	/* Unbind a driver from a device */
	void (*remove)(struct device *dev);

	/* Suspend/resume (optional: set to NULL if not supported) */
	int (*suspend)(struct device *dev, pm_message_t state);
	int (*resume)(struct device *dev);
};

/*
 * Extended (optional) bus operations.
 */
struct bus_ext_ops {
	int (*shutdown)(struct device *dev);
	int (*online)(struct device *dev);
	int (*offline)(struct device *dev);

	int (*uevent)(struct device *dev, struct kobj_uevent_env *env);
	int (*dma_configure)(struct device *dev);
};

/*
 * Minimal driver descriptor — drivers declare this instead of
 * the full struct device_driver.
 */
struct driver_desc {
	const char		*name;
	const char		*owner;		/* THIS_MODULE */
	const struct bus_ops	*bus;

	/* Subsystem-specific data */
	const void		*of_match_table; /* struct of_device_id * */
	const void		*acpi_match_table;

	/* Driver-specific probe/remove (called after bus probe/remove) */
	int (*probe)(struct device *dev);
	int (*remove)(struct device *dev);

	void	*driver_data;	/* Private data for the driver core */
};

/*
 * Register a driver with the bus.
 *
 * This wraps the existing __driver_register() but with a
 * simplified interface.
 */
int __must_check driver_register_simple(struct driver_desc *desc);

/*
 * Unregister a driver.
 */
void driver_unregister_simple(struct driver_desc *desc);

/*
 * Map from driver_desc to the kernel's struct device_driver.
 * Uses the wrapper embedded in desc->driver_data.
 */
struct device_driver *desc_to_driver(struct driver_desc *desc);

/*
 * Helper: create a platform driver from a driver_desc.
 */
int __must_check platform_driver_register_simple(struct driver_desc *desc);

/*
 * Recover struct driver_desc * from a struct device *.
 * Used by Rust callbacks to find their dispatch table.
 */
struct driver_desc *rust_desc_from_dev(struct device *dev);

/*
 * Return the bus_ops for the Rust platform bus.
 */
const struct bus_ops *rust_platform_bus_ops(void);

#endif /* _LINUX_DRIVER_BUS_OPS_H */
