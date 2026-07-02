# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the AI subsystem
#
# Rust source files are compiled via the kernel's Rust-for-Linux build
# infrastructure.  C helper files are compiled alongside.

obj-$(CONFIG_AI_SUBSYSTEM) += ai_subsystem.o

ai_subsystem-y := \
	src/helpers.o \
	src/lib.o

ai_subsystem-$(CONFIG_AI_SYSFS) += src/sysfs.o

ccflags-y += -I$(srctree)/$(src)/include

# UAPI headers — exported to userspace
header-test-y += include/uapi/linux/ai.h
always-y += include/uapi/linux/ai.h

# Userspace AI manager daemon (built with host cargo)
# This is a separate build from the kernel module.
PHONY += ai-mgr
ai-mgr:
	$(Q)cd $(src)/daemon && cargo build --release 2>/dev/null || \
	echo "ai-mgr: install Rust toolchain to build userspace daemon"
