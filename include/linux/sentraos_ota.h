/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SENTRAOS_OTA_H_
#define _LINUX_SENTRAOS_OTA_H_

/*
 * SentraOS OTA Update Manager — local secure update system.
 *
 * Provides staged update lifecycle with cryptographic verification:
 *   1. Stage  — load and verify an update payload
 *   2. Apply  — activate the verified update
 *   3. Rollback — revert an applied update
 *   4. Cancel — remove a staged update
 *
 * Update payloads are signed (PKCS#7) and verified against the
 * kernel's built-in trusted keyring.  Payload integrity is
 * protected by SHA-256.
 */

#include <linux/types.h>

#ifdef CONFIG_SENTRAOS_OTA

/* ── Update types ─────────────────────────────────── */
#define SENTRAOS_OTA_TYPE_HOTPATCH  1  /* Live function patching */
#define SENTRAOS_OTA_TYPE_MODULE    2  /* Kernel module load     */
#define SENTRAOS_OTA_TYPE_KERNEL    3  /* Full kernel (kexec)    */
#define SENTRAOS_OTA_TYPE_CONFIG    4  /* Kernel parameter tune  */
#define SENTRAOS_OTA_TYPE_FIRMWARE  5  /* Firmware blob update   */

/* ── Update status values ─────────────────────────── */
#define SENTRAOS_OTA_STATUS_STAGED       0
#define SENTRAOS_OTA_STATUS_APPLIED      1
#define SENTRAOS_OTA_STATUS_FAILED       2
#define SENTRAOS_OTA_STATUS_ROLLED_BACK  3
#define SENTRAOS_OTA_STATUS_CANCELLED    4

/* ── Lifecycle API ────────────────────────────────── */

/* Initialize the OTA subsystem (validates crypto backend) */
int  sentraos_ota_init(void);

/*
 * Stage an update for later application.
 * @update_data: pointer to complete update payload blob
 * @update_size: total size of the blob in bytes
 * @update_id:   output — assigned update ID
 *
 * The payload is parsed, integrity-checked (SHA-256), and
 * cryptographically verified (PKCS#7) before staging.
 * Returns 0 on success, negative errno on failure.
 */
int  sentraos_ota_stage(const void *update_data, u64 update_size,
			u32 *update_id);

/* Apply a previously staged update. */
int  sentraos_ota_apply(u32 update_id);

/* Rollback an applied update (backend permitting). */
int  sentraos_ota_rollback(u32 update_id);

/* Cancel a staged update (remove without applying). Fails if applied. */
int  sentraos_ota_cancel(u32 update_id);

/* ── Status / query API ───────────────────────────── */

/* Return the current status of an update (SENTRAOS_OTA_STATUS_*). */
u32  sentraos_ota_status(u32 update_id);

/*
 * List update IDs matching an optional status filter.
 * @ids:          output buffer for up to @count IDs
 * @status_filter: pointer to status value, or NULL for all
 * @count:        capacity of @ids buffer
 * Returns the number of IDs written.
 */
int  sentraos_ota_list(u32 *ids, u32 *status_filter, u32 count);

/*
 * Get a human-readable info string for an update.
 * @buf:      output buffer
 * @buf_size: capacity of @buf in bytes
 * Returns 0 on success, negative on error.
 */
int  sentraos_ota_info(u32 update_id, char *buf, u32 buf_size);

/* Count of staged (not yet applied) updates. */
u32  sentraos_ota_total_staged(void);

/* Count of applied (active) updates. */
u32  sentraos_ota_total_applied(void);

/* Returns 1 if initialized, 0 otherwise. */
int  sentraos_ota_is_init(void);

#else /* CONFIG_SENTRAOS_OTA */

static inline int  sentraos_ota_init(void) { return 0; }
static inline int  sentraos_ota_stage(const void *d, u64 s, u32 *id) { return 0; }
static inline int  sentraos_ota_apply(u32 id) { return 0; }
static inline int  sentraos_ota_rollback(u32 id) { return 0; }
static inline int  sentraos_ota_cancel(u32 id) { return 0; }
static inline u32  sentraos_ota_status(u32 id) { return 0; }
static inline int  sentraos_ota_list(u32 *ids, u32 *sf, u32 c) { return 0; }
static inline int  sentraos_ota_info(u32 id, char *b, u32 s) { return 0; }
static inline u32  sentraos_ota_total_staged(void) { return 0; }
static inline u32  sentraos_ota_total_applied(void) { return 0; }

#endif /* CONFIG_SENTRAOS_OTA */
#endif /* _LINUX_SENTRAOS_OTA_H_ */
