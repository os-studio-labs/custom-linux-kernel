# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the firmware health monitoring framework
#
# fw_health.ko is compiled from:
#   fw_health.c     — C bridge (always)
#   fw_health_jiffies.c — jiffies/time helpers (always)
# plus one of:
#   fw_health_core.rs   — lockless Rust state machine (CONFIG_RUST)
#   fw_health_simple.c  — C fallback state machine (!CONFIG_RUST)

obj-$(CONFIG_FW_HEALTH)		+= fw_health.o

fw_health-y			:= fw_health_jiffies.o
fw_health-$(CONFIG_RUST)	+= fw_health_core.o

ifeq ($(CONFIG_RUST),)
fw_health-y			+= fw_health_simple.o
endif
