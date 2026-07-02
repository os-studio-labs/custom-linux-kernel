#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0
"""
gen_api_keys.py — scan kernel headers for driver-facing functions
and generate DAC API key registration stubs.

Usage:
  python3 gen_api_keys.py <linux-srctree> <output-dir>
"""

import os
import sys
import re
import hashlib

SRCDIR = sys.argv[1]
OUTDIR = sys.argv[2]

# Subsystem headers that define driver-facing APIs
HEADERS = [
    "include/linux/pci.h",
    "include/linux/dma-mapping.h",
    "include/linux/device.h",
    "include/linux/slab.h",
    "include/linux/interrupt.h",
    "include/linux/delay.h",
    "include/linux/io.h",
    "include/linux/mm.h",
    "include/linux/netdevice.h",
    "include/linux/usb.h",
    "include/linux/i2c.h",
    "include/linux/platform_device.h",
    "include/linux/skbuff.h",
    "include/linux/etherdevice.h",
    "include/linux/firmware.h",
    "include/linux/completion.h",
    "include/linux/wait.h",
    "include/linux/timer.h",
    "include/linux/workqueue.h",
    "include/linux/mutex.h",
    "include/linux/spinlock.h",
    "include/linux/printk.h",
    "include/linux/regmap.h",
    "include/linux/clk.h",
    "include/linux/gpio/driver.h",
    "include/linux/pm_runtime.h",
    "include/linux/of.h",
    "include/linux/irq.h",
    "include/linux/dmaengine.h",
    "include/linux/scatterlist.h",
]

# Pattern to match function declarations in C headers
FUNC_PAT = re.compile(
    r'\b(pci_|dma_|dev_|k[z]?alloc|kfree|kcalloc|krealloc|'
    r'request_|free_irq|ioremap|iounmap|read[bwlq]|write[bwlq]|'
    r'usb_|i2c_|spi_|regmap_|clk_|gpio_|platform_|'
    r'net_|skb_|eth_|firmware_|complete_|wait_|schedule_|'
    r'mutex_|spin_|raw_spin_|print_|pr_|dev_err|dev_warn|dev_info|dev_dbg|__)'
    r'[a-z_0-9]+(?=\s*\()'
)

def main():
    os.makedirs(OUTDIR, exist_ok=True)

    functions = set()

    for header_rel in HEADERS:
        path = os.path.join(SRCDIR, header_rel)
        if not os.path.isfile(path):
            print(f"Skipping {header_rel}: not found", file=sys.stderr)
            continue

        with open(path, "r", errors="ignore") as f:
            content = f.read()

        for match in FUNC_PAT.finditer(content):
            name = match.group(0)
            if len(name) > 60 or not name[0].isalpha() or name.startswith("_"):
                continue
            functions.add(name)

    functions = sorted(functions)

    # === Generate dac_keys.c ===
    keys_c_path = os.path.join(OUTDIR, "dac_keys.c")
    with open(keys_c_path, "w") as f:
        f.write("""// SPDX-License-Identifier: GPL-2.0
// dac_keys.c — Auto-generated DAC API key definitions.
// Each function drivers call gets a unique 64-bit key registered at boot.

#include <linux/init.h>
#include <linux/dac_api.h>

extern u64 dac_register_api_key(const char *name, const char *module,
                                unsigned int access, unsigned int rate_limit_ms);

""")
        for func in functions:
            # Use a stable hash
            h = hashlib.sha256(func.encode()).hexdigest()[:16]
            f.write(f'static u64 __dac_key_{func};\n')
            f.write(f'static int __init dac_reg_key_{func}(void)\n')
            f.write('{\n')
            f.write(f'    __dac_key_{func} = dac_register_api_key(\n')
            f.write(f'        "{func}", "kernel", 0, 0);\n')
            f.write('    return 0;\n')
            f.write('}\n')
            f.write(f'pure_initcall(dac_reg_key_{func});\n\n')

    # === Generate dac_keys.h ===
    keys_h_path = os.path.join(OUTDIR, "dac_keys.h")
    with open(keys_h_path, "w") as f:
        f.write("""/* SPDX-License-Identifier: GPL-2.0 */
/* dac_keys.h — Auto-generated DAC API key declarations. */

#ifndef _DAC_KEYS_H_
#define _DAC_KEYS_H_

""")
        for func in functions:
            f.write(f'extern u64 __dac_key_{func};\n')
        f.write('#endif /* _DAC_KEYS_H_ */\n')

    print(f"Generated {keys_c_path} ({len(functions)} keys)")
    print(f"Generated {keys_h_path}")

if __name__ == "__main__":
    main()
