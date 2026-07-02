// SPDX-License-Identifier: GPL-2.0
/*
 * dac_gateway — API call validation and forwarding.
 *
 * Every driver API call passes through this gateway, which:
 *   1. Validates the API key against the registry
 *   2. Checks the driver's sandbox state (alive, faulted, dead)
 *   3. Logs the call if debugging is enabled
 *   4. Forwards to the real function
 *   5. Catches faults (via exception table) and marks driver as faulted
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/kdebug.h>
#include <linux/sched.h>
#include <linux/dac_api.h>
#include <linux/dac_log.h>

/* Rust-implemented validation and driver context management */
extern int dac_validate_call(u64 key, u32 driver_id, void *caller_addr);

/* Current driver ID (set by sandbox before each driver entry point) */
static DEFINE_PER_CPU(u32, dac_current_driver_id);

u32 dac_get_current_driver(void)
{
	return __this_cpu_read(dac_current_driver_id);
}
EXPORT_SYMBOL_GPL(dac_get_current_driver);

void dac_set_current_driver(u32 id)
{
	__this_cpu_write(dac_current_driver_id, id);
}
EXPORT_SYMBOL_GPL(dac_set_current_driver);

/* Rust driver fault marker */
extern void dac_driver_faulted(u32 driver_id);

/*
 * dac_current_fn_name — name of the function currently being called
 * through the gateway (per-CPU, for diagnostics).
 */
static DEFINE_PER_CPU(const char *, dac_current_fn_name);

/*
 * dac_gateway — validate and forward an API call.
 *
 * Returns the real function's return value, or -errno if the
 * driver is not in a valid state.
 *
 * If the driver faults inside the call, the die notifier below
 * catches the oops and marks the driver as faulted.
 */
long dac_gateway(u64 key, const char *func_name,
		 long (*real_fn)(unsigned long, unsigned long),
		 unsigned long arg1, unsigned long arg2)
{
	u32 driver_id = dac_get_current_driver();
	int ret;

	if (driver_id == 0)
		goto forward; /* kernel-initiated call, skip validation */

	ret = dac_validate_call(key, driver_id, __builtin_return_address(0));
	if (ret < 0) {
		pr_debug("dac: driver %u blocked from %s (err=%d)\n",
			 driver_id, func_name, ret);
		return ret;
	}

forward:
	if (!real_fn)
		return -ENOSYS;

	/* Set function name for crash diagnostics */
	__this_cpu_write(dac_current_fn_name, func_name);

	/* Forward the call — if the driver faults, the die notifier fires */
	ret = real_fn(arg1, arg2);

	__this_cpu_write(dac_current_fn_name, NULL);

	return ret;
}
EXPORT_SYMBOL_GPL(dac_gateway);

/* ── Crash detection via die notifier ─────────────────── */

/*
 * On x86, when a kernel oops occurs (e.g., NULL pointer deref in a driver),
 * the die_chain notifier fires.  We check whether the faulting context
 * is inside a driver DAC call and mark the driver as faulted.
 */
static int dac_die_notifier(struct notifier_block *nb,
			    unsigned long val, void *data)
{
	const char *fn_name;
	u32 driver_id;

	/* Only care about oops (not panic) */
	if (val != DIE_OOPS && val != DIE_INT3)
		return NOTIFY_DONE;

	driver_id = dac_get_current_driver();
	if (driver_id == 0)
		return NOTIFY_DONE; /* not inside a driver call */

	fn_name = __this_cpu_read(dac_current_fn_name);

	pr_warn("dac: driver %u faulted in %s (oops caught)\n",
		driver_id, fn_name ?: "?");

	dac_driver_log(driver_id, 2,
		       "CRASH detected in %s — marking driver faulted",
		       fn_name ?: "unknown");

	dac_driver_faulted(driver_id);
	dac_set_current_driver(0);

	return NOTIFY_OK;
}

static struct notifier_block dac_die_nb = {
	.notifier_call = dac_die_notifier,
	.priority = 0, /* run after arch-specific handlers */
};

static int __init dac_gateway_init(void)
{
	register_die_notifier(&dac_die_nb);
	pr_info("dac: crash detection active (die notifier)\n");
	return 0;
}
pure_initcall(dac_gateway_init);

static void __exit dac_gateway_exit(void)
{
	unregister_die_notifier(&dac_die_nb);
}
__exitcall(dac_gateway_exit);

/*
 * API key linker set — all DAC_DECLARE_KEY entries end up here.
 */
extern struct dac_api_key __start___dac_keys[];
extern struct dac_api_key __stop___dac_keys[];

static int __init dac_init_keys(void)
{
	struct dac_api_key *k;
	int count = 0;

	for (k = __start___dac_keys; k < __stop___dac_keys; k++) {
		if (k->key && k->name)
			count++;
	}

	pr_info("dac: registered %d API keys\n", count);
	return 0;
}
pure_initcall(dac_init_keys);
