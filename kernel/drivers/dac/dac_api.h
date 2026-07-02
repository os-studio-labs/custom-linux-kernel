/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_DAC_API_H_
#define _LINUX_DAC_API_H_

/*
 * DAC (Driver API Centre) — central API key registry and call validation.
 *
 * Every kernel function callable by a driver is assigned an API key at
 * boot.  Drivers use DAC_CALL() to invoke kernel APIs; the gateway
 * validates the key, checks the driver's sandbox state, and forwards
 * the call.  If the driver has crashed, DAC_CALL returns -EIO instead
 * of executing the function (preventing further damage).
 *
 * Example:
 *   #include <linux/dac_api.h>
 *   DAC_DECLARE_KEY(pci_read_config_byte);
 *
 *   u8 val;
 *   int ret = DAC_CALL(pci_read_config_byte, pdev, 0x50, &val);
 *
 * The DAC_CALL macro expands to:
 *   1. Locate the API key for the function at compile time
 *   2. Call dac_gateway() which validates + forwards
 */

#include <linux/types.h>
#include <linux/errno.h>
#include <linux/string.h>

/* ── Opaque handle for an API key ──────────────────────── */

struct dac_api_key {
	u64 key;
	const char *name;
};

/* ── Macro to declare an API key reference ─────────────── */
#define DAC_DECLARE_KEY(name)					\
	extern struct dac_api_key __dac_key_##name

/* ── Gateway function ─────────────────────────────────── */
long dac_gateway(u64 key, const char *func_name,
		 long (*real_fn)(unsigned long, unsigned long),
		 unsigned long arg1, unsigned long arg2);

/* ── DAC_CALL macro — transparent API validation ──────── */

/*
 * DAC_CALL(func, args...) — call a kernel API through the DAC gateway.
 *
 * Expands to:
 *   dac_gateway(key_of_func, "func", (long (*)(...))real_func, arg1, arg2)
 *
 * For 0-arg:  DAC_CALL0(func)
 * For 1-arg:  DAC_CALL1(func, a1)
 * For 2-arg:  DAC_CALL2(func, a1, a2)
 */

#define DAC_CALL0(fn) ({						\
	extern long __dac_real_##fn(void);				\
	DAC_CALL_GATEWAY(0, 0, fn, dac_call_ ## fn);			\
})

#define DAC_CALL1(fn, a1) ({						\
	DECLARE_ARGS(a1);						\
	DAC_CALL_GATEWAY((unsigned long)_a1, 0, fn, dac_call_ ## fn);	\
})

#define DAC_CALL2(fn, a1, a2) ({					\
	DECLARE_ARGS(a1); DECLARE_ARGS2(a2);				\
	DAC_CALL_GATEWAY((unsigned long)_a1, (unsigned long)_a2,	\
			 fn, dac_call_ ## fn);				\
})

/* Internal helpers */
#define DECLARE_ARGS(x)		unsigned long _a1 = (unsigned long)(x)
#define DECLARE_ARGS2(x)	unsigned long _a2 = (unsigned long)(x)

#define DAC_CALL_GATEWAY(a1, a2, fn, call_id) ({			\
	DAC_DECLARE_KEY(fn);						\
	long _dac_ret;							\
	if (__dac_key_##fn.key == 0) {					\
		/* Key not registered — fall through (degraded mode) */	\
		extern long __dac_real_##fn(void);			\
		_dac_ret = (long)(__dac_real_##fn)((void *)(a1), (void *)(a2)); \
	} else {							\
		_dac_ret = dac_gateway(__dac_key_##fn.key, #fn,	\
			(long (*)(unsigned long, unsigned long))	\
				__dac_real_##fn, a1, a2);		\
	}								\
	_dac_ret;							\
})

#endif /* _LINUX_DAC_API_H_ */
