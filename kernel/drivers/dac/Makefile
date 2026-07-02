# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the Driver API Centre (DAC)
#
# The DAC is built as part of the kernel image when CONFIG_DRIVER_API_CENTRE=y.
# It lives under kernel/ because it is core infrastructure, not a driver.

obj-$(CONFIG_DRIVER_API_CENTRE) += dac_gateway.o
obj-$(CONFIG_DRIVER_API_CENTRE) += dac_sandbox.o
obj-$(CONFIG_DRIVER_API_CENTRE) += dac_log.o
obj-$(CONFIG_DRIVER_API_CENTRE) += dac_sysfs.o

# Rust core
obj-$(CONFIG_DRIVER_API_CENTRE) += dac_core.o

# Auto-generated API keys (run gen_api_keys.py to (re)generate)
obj-$(CONFIG_DRIVER_API_CENTRE) += dac_keys.o

PHONY: gen_dac_keys
gen_dac_keys:
	$(srctree)/kernel/drivers/dac/gen_api_keys.py $(srctree) $(srctree)/kernel/drivers/dac/

# Rust integration
ifdef CONFIG_DRIVER_API_CENTRE
RUSTFLAGS_dac_core.o := -Zallow-features=concat_idents
endif
