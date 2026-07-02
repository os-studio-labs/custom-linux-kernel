# SPDX-License-Identifier: GPL-2.0
# SentraOS terminal daemon build

sentraos-termd: src/main.rs
	cargo build --release 2>/dev/null || \
		rustc -O src/main.rs -o sentraos-termd

.PHONY: clean
clean:
	rm -f sentraos-termd
