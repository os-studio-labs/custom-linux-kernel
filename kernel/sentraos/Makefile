# SPDX-License-Identifier: GPL-2.0
#
# Makefile for SentraOS microkernel architecture layer

obj-$(CONFIG_SENTRAOS_STEALTH)		+= sentraos_monitor.o
obj-$(CONFIG_SENTRAOS_ORCHESTRATOR)	+= orchestrator.o
obj-$(CONFIG_SENTRAOS_ISOLATION)	+= driver_isolation.o
obj-$(CONFIG_SENTRAOS_CONCURRENCY)	+= concurrency_safe.o
obj-$(CONFIG_SENTRAOS_USER_BRIDGE)	+= user_bridge.o

# Rust objects
rust-obj-$(CONFIG_SENTRAOS_STEALTH)	+= sentraos_monitor.o
rust-obj-$(CONFIG_SENTRAOS_ORCHESTRATOR) += orchestrator.o
rust-obj-$(CONFIG_SENTRAOS_OBJECT_MANAGER) += object_manager.o
rust-obj-$(CONFIG_SENTRAOS_IPC) += mach_ipc.o
rust-obj-$(CONFIG_SENTRAOS_CHANNELS) += microkit_channels.o

# Also register with standard obj for linking
obj-$(CONFIG_SENTRAOS_OBJECT_MANAGER) += object_manager.o
obj-$(CONFIG_SENTRAOS_IPC) += mach_ipc.o
obj-$(CONFIG_SENTRAOS_CHANNELS) += microkit_channels.o

# OTA Update Manager
obj-$(CONFIG_SENTRAOS_OTA) += ota_helpers.o
rust-obj-$(CONFIG_SENTRAOS_OTA) += ota_update.o
obj-$(CONFIG_SENTRAOS_OTA) += ota_update.o

# Stealth linker magic: the sentraos hidden memory pool
# must be placed in a section that no /proc/* or /sys/* exposes.
LDFLAGS_sentraos_monitor.o += -Wl,--section-start=.sentraos_pool=0x1000000
