/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SENTRAOS_IPC_H_
#define _LINUX_SENTRAOS_IPC_H_

/*
 * SentraOS Mach IPC — port-based message passing.
 *
 * Inspired by the Mach microkernel, provides:
 *   - Port-based IPC
 *   - Port rights (send, receive, send-once)
 *   - Port sets for multiplexed receive
 *   - Message queues with timeout
 */

#include <linux/types.h>

#ifdef CONFIG_SENTRAOS_IPC

/* Message flags */
#define SENTRAOS_IPC_FLAG_NONE        0x0000
#define SENTRAOS_IPC_FLAG_URGENT      0x0001
#define SENTRAOS_IPC_FLAG_NONBLOCKING 0x0002
#define SENTRAOS_IPC_FLAG_NOTIFY      0x0004

/* Initialize the IPC subsystem (requires Object Manager) */
int  sentraos_ipc_init(void);

/* Port lifecycle */
int  sentraos_ipc_port_allocate(const char *name, u32 *port_name);
int  sentraos_ipc_port_deallocate(u32 port_name);

/* Message passing */
int  sentraos_ipc_msg_send(u32 port_name, const void *msg, u64 size, u32 flags);
int  sentraos_ipc_msg_receive(u32 port_name, void *buf, u64 *size, u64 timeout_ms);
int  sentraos_ipc_msg_send_receive(u32 reply_port, u32 port_name,
				   const void *msg, u64 size,
				   void *reply_buf, u64 *reply_size);

/* Port rights */
int  sentraos_ipc_give_send_right(u32 port_name, u32 target_pid);
int  sentraos_ipc_give_receive_right(u32 port_name, u32 target_pid);
int  sentraos_ipc_revoke_right(u32 port_name, u32 target_pid);

/* Port sets */
int  sentraos_ipc_port_set_create(const char *name, u32 *set_id);
int  sentraos_ipc_port_set_add(u32 set_id, u32 port_name);
int  sentraos_ipc_port_set_remove(u32 set_id, u32 port_name);
int  sentraos_ipc_port_set_poll(u32 set_id, u32 *port_name, u64 timeout_ms);
int  sentraos_ipc_port_set_destroy(u32 set_id);

/* Status queries */
u32  sentraos_ipc_port_status(u32 port_name);
u32  sentraos_ipc_port_msg_count(u32 port_name);
u32  sentraos_ipc_stats_ports(void);
u32  sentraos_ipc_stats_port_sets(void);
int  sentraos_ipc_is_init(void);

#else /* CONFIG_SENTRAOS_IPC */

static inline int  sentraos_ipc_init(void) { return 0; }
static inline int  sentraos_ipc_port_allocate(const char *n, u32 *p) { return 0; }
static inline int  sentraos_ipc_port_deallocate(u32 p) { return 0; }
static inline int  sentraos_ipc_msg_send(u32 p, const void *m, u64 s, u32 f) { return 0; }
static inline int  sentraos_ipc_msg_receive(u32 p, void *b, u64 *s, u64 t) { return 0; }
static inline int  sentraos_ipc_msg_send_receive(u32 rp, u32 p, const void *m,
						 u64 s, void *rb, u64 *rs) { return 0; }
static inline int  sentraos_ipc_give_send_right(u32 p, u32 t) { return 0; }
static inline int  sentraos_ipc_give_receive_right(u32 p, u32 t) { return 0; }
static inline int  sentraos_ipc_revoke_right(u32 p, u32 t) { return 0; }
static inline int  sentraos_ipc_port_set_create(const char *n, u32 *s) { return 0; }
static inline int  sentraos_ipc_port_set_add(u32 s, u32 p) { return 0; }
static inline int  sentraos_ipc_port_set_remove(u32 s, u32 p) { return 0; }
static inline int  sentraos_ipc_port_set_poll(u32 s, u32 *p, u64 t) { return 0; }
static inline int  sentraos_ipc_port_set_destroy(u32 s) { return 0; }

#endif /* CONFIG_SENTRAOS_IPC */
#endif /* _LINUX_SENTRAOS_IPC_H_ */
