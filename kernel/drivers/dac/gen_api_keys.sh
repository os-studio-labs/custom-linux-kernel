#!/bin/bash
# SPDX-License-Identifier: GPL-2.0
#
# gen_api_keys.sh — generate DAC API key definitions for all exported
# kernel functions that drivers commonly call.
#
# Each key is registered at boot via an initcall, so no linker-script
# support is needed.

set -euo pipefail

SRCDIR="$1"
OUTDIR="$2"
KEYS_C="$OUTDIR/dac_keys.c"
KEYS_H="$OUTDIR/dac_keys.h"

mkdir -p "$OUTDIR"
exec 3>"$KEYS_C"
exec 4>"$KEYS_H"

cat >&3 << 'CEOF'
// SPDX-License-Identifier: GPL-2.0
// dac_keys.c — Auto-generated DAC API key definitions.
// Each function drivers call gets a unique 64-bit key registered at boot.

#include <linux/init.h>
#include <linux/dac_api.h>

/* Rust-implemented registration function */
extern u64 dac_register_api_key(const char *name, const char *module,
				unsigned int access, unsigned int rate_limit_ms);

CEOF

cat >&4 << 'HEOF'
/* SPDX-License-Identifier: GPL-2.0 */
/* dac_keys.h — Auto-generated DAC API key declarations. */

#ifndef _DAC_KEYS_H_
#define _DAC_KEYS_H_

#define DAC_KEY(name) extern u64 __dac_key_##name

HEOF

# Key subsystems to scan for driver-facing API functions
HEADERS=(
	"include/linux/pci.h"
	"include/linux/dma-mapping.h"
	"include/linux/device.h"
	"include/linux/slab.h"
	"include/linux/interrupt.h"
	"include/linux/delay.h"
	"include/linux/io.h"
	"include/linux/mm.h"
	"include/linux/netdevice.h"
	"include/linux/usb.h"
	"include/linux/i2c.h"
	"include/linux/platform_device.h"
	"include/linux/skbuff.h"
	"include/linux/etherdevice.h"
	"include/linux/firmware.h"
	"include/linux/completion.h"
	"include/linux/wait.h"
	"include/linux/timer.h"
	"include/linux/workqueue.h"
	"include/linux/mutex.h"
	"include/linux/spinlock.h"
	"include/linux/printk.h"
	"include/linux/regmap.h"
	"include/linux/clk.h"
	"include/linux/gpio/driver.h"
	"include/linux/pm_runtime.h"
	"include/linux/of.h"
	"include/linux/irq.h"
	"include/linux/dmaengine.h"
	"include/linux/scatterlist.h"
	"include/linux/highmem.h"
)

declare -A SEEN

for header in "${HEADERS[@]}"; do
	fullpath="$SRCDIR/$header"
	[ -f "$fullpath" ] || continue

	# Extract function identifiers: look for patterns like
	#   type func_name(args);
	#   type func_name(args) { ... }
	#   EXPORT_SYMBOL(func_name)
	# within the header.
	#
	# Also look for inline function definitions.
	grep -oP '(?<![a-z_])(pci_|dma_|dev_|k[z]?alloc|kfree|kcalloc|krealloc|request_|free_irq|ioremap|iounmap|read[bwlq]|write[bwlq]|usb_|i2c_|spi_|regmap_|clk_|gpio_|platform_|net_|skb_|eth_|firmware_|complete_|wait_|schedule_|mutex_|spin_|raw_spin_|print_|pr_|dev_err|dev_warn|dev_info|dev_dbg|__)[a-z_0-9]+)(?=\s*\()' "$fullpath" 2>/dev/null || true
done | sort -u | while read -r func; do
	[ -z "$func" ] || [ "${#func}" -gt 60 ] && continue
	[[ "$func" =~ ^[a-z_] ]] || continue
	[ -z "${SEEN[$func]:-}" ] || continue
	SEEN[$func]=1

	# Register via initcall
	cat >&3 << DEF
static u64 __dac_key_${func};
static int __init dac_reg_key_${func}(void)
{
	__dac_key_${func} = dac_register_api_key("${func}", "kernel", 0, 0);
	return 0;
}
pure_initcall(dac_reg_key_${func});

DEF

	# Header declaration
	echo "DAC_KEY(${func});" >&4
done

# End header guard
echo "#endif /* _DAC_KEYS_H_ */" >&4

exec 3>&-
exec 4>&-

count=$(grep -c 'pure_initcall' "$KEYS_C")
echo "Generated $KEYS_C and $KEYS_H ($count keys)"
