/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SENTRAOS_TTY_H_
#define _LINUX_SENTRAOS_TTY_H_

/*
 * SentraOS TTY/CONSOLE — minimal kernel TTY core interface.
 *
 * The kernel provides just a thin byte-pipe transport layer.
 * All line discipline, canonical mode, terminal emulation,
 * and PTY management runs in userspace (termd daemon).
 */

#include <linux/types.h>

#ifdef CONFIG_SENTRAOS_TTY_RUST

/* TTY lifecycle */
u32 sentraos_tty_alloc(const char *name, u32 is_console, u32 sandbox_id);
void sentraos_tty_free(u32 index);

/* Open/close */
int sentraos_tty_open(u32 index, u32 pid);
void sentraos_tty_close(u32 index);

/* I/O — raw byte pipe */
u32 sentraos_tty_write(u32 index, const u8 *data, u32 len);
u32 sentraos_tty_read(u32 index, u8 *buf, u32 len);

/* Console emergency path (direct framebuffer/printk when daemon is down) */
int sentraos_console_write(const char *msg);

/* Daemon connection management */
int sentraos_tty_daemon_connected(u32 index);
int sentraos_tty_daemon_disconnected(u32 index);

/* Statistics */
u32 sentraos_tty_count(void);
u32 sentraos_tty_open_count(u32 index);

#else /* CONFIG_SENTRAOS_TTY_RUST */

static inline u32 sentraos_tty_alloc(const char *n, u32 c, u32 s) { return 0; }
static inline void sentraos_tty_free(u32 i) { }
static inline int sentraos_tty_open(u32 i, u32 p) { return -ENODEV; }
static inline void sentraos_tty_close(u32 i) { }
static inline u32 sentraos_tty_write(u32 i, const u8 *d, u32 l) { return 0; }
static inline u32 sentraos_tty_read(u32 i, u8 *b, u32 l) { return 0; }
static inline int sentraos_console_write(const char *m) { return 0; }
static inline int sentraos_tty_daemon_connected(u32 i) { return 0; }
static inline int sentraos_tty_daemon_disconnected(u32 i) { return 0; }
static inline u32 sentraos_tty_count(void) { return 0; }
static inline u32 sentraos_tty_open_count(u32 i) { return 0; }

#endif /* CONFIG_SENTRAOS_TTY_RUST */

#endif /* _LINUX_SENTRAOS_TTY_H_ */
