/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SENTRAOS_CHANNELS_H_
#define _LINUX_SENTRAOS_CHANNELS_H_

/*
 * SentraOS Microkit Channels — seL4-inspired microkernel IPC.
 *
 * Provides lightweight, capability-controlled communication:
 *   - Endpoints for synchronous IPC (call/wait/reply)
 *   - Notifications for asynchronous signaling
 *   - Capability-based access control
 */

#include <linux/types.h>

#ifdef CONFIG_SENTRAOS_CHANNELS

/* Capability rights for endpoints / notifications */
#define SENTRAOS_CAP_SEND      0x0001
#define SENTRAOS_CAP_RECEIVE   0x0002
#define SENTRAOS_CAP_CALL      0x0004
#define SENTRAOS_CAP_REPLY     0x0008
#define SENTRAOS_CAP_ALL       0x000F

/* Initialize the channel subsystem */
int  sentraos_chan_init(void);

/* Endpoint lifecycle */
int  sentraos_chan_endpoint_create(const char *name, u32 *ep_name);
int  sentraos_chan_endpoint_delete(u32 ep_name);

/* Synchronous IPC: call / wait / reply */
int  sentraos_chan_call(u32 ep_name, const u64 *msg, u64 msg_words,
			u64 *reply, u64 *reply_words);
int  sentraos_chan_reply(u32 ep_name, const u64 *reply, u64 reply_words);
int  sentraos_chan_wait(u32 ep_name, u64 *msg, u64 *msg_words, u64 timeout_ms);

/* Notification operations */
int  sentraos_chan_notification_create(const char *name, u32 *notif_name);
int  sentraos_chan_notification_delete(u32 notif_name);
int  sentraos_chan_notification_signal(u32 notif_name);
int  sentraos_chan_notification_wait(u32 notif_name, u64 timeout_ms);
int  sentraos_chan_notification_poll(u32 notif_name);

/* Capability management for endpoints */
int  sentraos_chan_grant_ep_cap(u32 ep_name, u32 target_pid, u32 rights);
int  sentraos_chan_revoke_ep_cap(u32 ep_name, u32 target_pid);

/* Capability management for notifications */
int  sentraos_chan_grant_notif_cap(u32 notif_name, u32 target_pid, u32 rights);
int  sentraos_chan_revoke_notif_cap(u32 notif_name, u32 target_pid);

/* Status queries */
u32  sentraos_chan_ep_status(u32 ep_name);
u32  sentraos_chan_ep_caller_count(u32 ep_name);
u32  sentraos_chan_notif_state(u32 notif_name);
u32  sentraos_chan_stats_endpoints(void);
u32  sentraos_chan_stats_notifications(void);
int  sentraos_chan_is_init(void);

#else /* CONFIG_SENTRAOS_CHANNELS */

static inline int  sentraos_chan_init(void) { return 0; }
static inline int  sentraos_chan_endpoint_create(const char *n, u32 *e) { return 0; }
static inline int  sentraos_chan_endpoint_delete(u32 e) { return 0; }
static inline int  sentraos_chan_call(u32 e, const u64 *m, u64 mw, u64 *r, u64 *rw) { return 0; }
static inline int  sentraos_chan_reply(u32 e, const u64 *r, u64 rw) { return 0; }
static inline int  sentraos_chan_wait(u32 e, u64 *m, u64 *mw, u64 t) { return 0; }
static inline int  sentraos_chan_notification_create(const char *n, u32 *nn) { return 0; }
static inline int  sentraos_chan_notification_delete(u32 n) { return 0; }
static inline int  sentraos_chan_notification_signal(u32 n) { return 0; }
static inline int  sentraos_chan_notification_wait(u32 n, u64 t) { return 0; }
static inline int  sentraos_chan_notification_poll(u32 n) { return 0; }
static inline int  sentraos_chan_grant_ep_cap(u32 e, u32 t, u32 r) { return 0; }
static inline int  sentraos_chan_revoke_ep_cap(u32 e, u32 t) { return 0; }
static inline int  sentraos_chan_grant_notif_cap(u32 n, u32 t, u32 r) { return 0; }
static inline int  sentraos_chan_revoke_notif_cap(u32 n, u32 t) { return 0; }

#endif /* CONFIG_SENTRAOS_CHANNELS */
#endif /* _LINUX_SENTRAOS_CHANNELS_H_ */
