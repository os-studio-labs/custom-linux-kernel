# SPDX-License-Identifier: GPL-2.0
#
# Makefile for Rust Driver Core — safe wrappers for any driver subsystem

obj-$(CONFIG_RUST_CORE) += rust_core.o

# Core always needs the Rust state machine
rust_core-y := dma_safe.o

# Optional per-subsystem wrappers
rust_core-$(CONFIG_RUST_CORE_PCI)	+= pci_safe.o
rust_core-y				+= net_dma_safe.o
rust_core-y				+= usb_dma_safe.o
