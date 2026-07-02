# SPDX-License-Identifier: GPL-2.0
#
# SentraOS user-space orchestrator daemon build

# User-space program, not kernel module
sentraosd: src/main.rs
	cargo build --release 2>/dev/null || \
		rustc -O src/main.rs -o sentraosd

.PHONY: clean
clean:
	rm -f sentraosd
