// SPDX-License-Identifier: GPL-2.0-only
/*
 * driver_bus_ops — Simplified driver registration.
 *
 * Wraps the existing driver model so that:
 *   - Drivers declare a `struct driver_desc` instead of
 *     `struct device_driver` directly.
 *   - The bus operations are clearly separated into
 *     mandatory (`bus_ops`) and optional (`bus_ext_ops`).
 *   - Rust drivers can use this interface without
 *     touching C macros like `module_driver()`.
 */

#include <linux/device/driver.h>
#include <linux/platform_device.h>
#include <linux/export.h>
#include <linux/slab.h>
#include <linux/driver_bus_ops.h>

/*
 * Wraps a driver_desc into the kernel's device_driver.
 * The bus_ops callbacks dispatch to the generic wrappers below.
 */
struct desc_wrapper {
	struct device_driver	driver;
	struct driver_desc	*desc;
};

static int desc_probe(struct device *dev)
{
	struct desc_wrapper *wrap = container_of(dev->driver,
						 struct desc_wrapper, driver);

	if (wrap->desc->bus->probe) {
		int ret = wrap->desc->bus->probe(dev);
		if (ret)
			return ret;
	}

	if (wrap->desc->probe)
		return wrap->desc->probe(dev);

	return 0;
}

static int desc_remove(struct device *dev)
{
	struct desc_wrapper *wrap = container_of(dev->driver,
						 struct desc_wrapper, driver);

	if (wrap->desc->remove)
		return wrap->desc->remove(dev);

	if (wrap->desc->bus->remove)
		wrap->desc->bus->remove(dev);

	return 0;
}

int driver_register_simple(struct driver_desc *desc)
{
	struct desc_wrapper *wrap;
	int ret;

	if (!desc || !desc->name || !desc->bus)
		return -EINVAL;

	wrap = kzalloc(sizeof(*wrap), GFP_KERNEL);
	if (!wrap)
		return -ENOMEM;

	wrap->desc = desc;
	wrap->driver.name	= desc->name;
	wrap->driver.owner	= desc->owner ? THIS_MODULE : NULL;
	wrap->driver.bus	= NULL; /* Set by bus-specific register */
	wrap->driver.probe	= desc_probe;
	wrap->driver.remove	= desc_remove;

	/* Register with the driver core */
	ret = driver_register(&wrap->driver);
	if (ret) {
		kfree(wrap);
		return ret;
	}

	desc->driver_data = wrap;
	return 0;
}
EXPORT_SYMBOL_GPL(driver_register_simple);

struct device_driver *desc_to_driver(struct driver_desc *desc)
{
	struct desc_wrapper *wrap = desc->driver_data;
	return wrap ? &wrap->driver : NULL;
}
EXPORT_SYMBOL_GPL(desc_to_driver);

void driver_unregister_simple(struct driver_desc *desc)
{
	struct desc_wrapper *wrap;

	if (!desc || !desc->driver_data)
		return;

	wrap = desc->driver_data;
	driver_unregister(&wrap->driver);
	kfree(wrap);
	desc->driver_data = NULL;
}
EXPORT_SYMBOL_GPL(driver_unregister_simple);

/*
 * Platform driver variant.
 */
int platform_driver_register_simple(struct driver_desc *desc)
{
	struct platform_driver *pdrv;
	struct desc_wrapper *wrap;
	int ret;

	if (!desc || !desc->name || !desc->bus)
		return -EINVAL;

	wrap = kzalloc(sizeof(*wrap), GFP_KERNEL);
	if (!wrap)
		return -ENOMEM;

	pdrv = kzalloc(sizeof(*pdrv), GFP_KERNEL);
	if (!pdrv) {
		kfree(wrap);
		return -ENOMEM;
	}

	wrap->desc = desc;
	pdrv->driver.name	= desc->name;
	pdrv->driver.owner	= THIS_MODULE;
	pdrv->driver.bus	= &platform_bus_type;
	pdrv->driver.probe	= desc_probe;
	pdrv->driver.remove	= desc_remove;
	pdrv->driver.of_match_table = desc->of_match_table;

	ret = platform_driver_register(pdrv);
	if (ret) {
		kfree(pdrv);
		kfree(wrap);
		return ret;
	}

	desc->driver_data = wrap;
	return 0;
}
EXPORT_SYMBOL_GPL(platform_driver_register_simple);

/*
 * Built-in bus_ops for Rust platform drivers.
 * The bus name is set at registration time; match/probe/remove
 * are handled by the generic desc_probe/desc_remove wrappers.
 */
static int rust_bus_match(struct device *dev, struct device_driver *drv)
{
	return 1; /* Match everything — device-tree matching is handled separately */
}

static const struct bus_ops rust_platform_bus_ops_instance = {
	.name		= "rust_platform",
	.match		= rust_bus_match,
	.probe		= NULL,		/* Use desc->probe (Rust callback) */
	.remove		= NULL,		/* Use desc->remove (Rust callback) */
	.suspend	= NULL,
	.resume		= NULL,
};

const struct bus_ops *rust_platform_bus_ops(void)
{
	return &rust_platform_bus_ops_instance;
}
EXPORT_SYMBOL_GPL(rust_platform_bus_ops);

/*
 * Recover struct driver_desc * from a struct device *.
 * Used by Rust callbacks to find their dispatch table.
 */
struct driver_desc *rust_desc_from_dev(struct device *dev)
{
	struct desc_wrapper *wrap;

	if (!dev || !dev->driver)
		return NULL;

	wrap = container_of(dev->driver, struct desc_wrapper, driver);
	return wrap->desc;
}
EXPORT_SYMBOL_GPL(rust_desc_from_dev);
