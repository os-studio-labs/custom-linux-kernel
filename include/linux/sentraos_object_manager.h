/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_SENTRAOS_OBJECT_MANAGER_H_
#define _LINUX_SENTRAOS_OBJECT_MANAGER_H_

/*
 * SentraOS Object Manager — NT-style unified object management.
 *
 * All kernel entities (processes, threads, ports, endpoints, events,
 * files, devices) are managed as reference-counted objects with:
 *   - Hierarchical namespace (directory tree)
 *   - Per-object access control
 *   - Handle table with duplication and access checks
 *   - Type descriptors with per-type operations
 */

#include <linux/types.h>

#ifdef CONFIG_SENTRAOS_OBJECT_MANAGER

/* Object type IDs */
#define SENTRAOS_OB_TYPE_DIRECTORY      1
#define SENTRAOS_OB_TYPE_PROCESS        2
#define SENTRAOS_OB_TYPE_THREAD         3
#define SENTRAOS_OB_TYPE_EVENT          4
#define SENTRAOS_OB_TYPE_MUTANT         5
#define SENTRAOS_OB_TYPE_SEMAPHORE      6
#define SENTRAOS_OB_TYPE_TIMER          7
#define SENTRAOS_OB_TYPE_PORT           8
#define SENTRAOS_OB_TYPE_ENDPOINT       9
#define SENTRAOS_OB_TYPE_NOTIFICATION  10
#define SENTRAOS_OB_TYPE_FILE          11
#define SENTRAOS_OB_TYPE_DEVICE        12
#define SENTRAOS_OB_TYPE_IO_COMPLETION 13
#define SENTRAOS_OB_TYPE_CUSTOM       255

/* Access mask bits (NT-style) */
#define SENTRAOS_ACCESS_READ          0x0001
#define SENTRAOS_ACCESS_WRITE         0x0002
#define SENTRAOS_ACCESS_EXECUTE       0x0004
#define SENTRAOS_ACCESS_DELETE        0x0008
#define SENTRAOS_ACCESS_READ_CONTROL  0x0010
#define SENTRAOS_ACCESS_WRITE_DAC     0x0020
#define SENTRAOS_ACCESS_WRITE_OWNER   0x0040
#define SENTRAOS_ACCESS_SYNCHRONIZE   0x0080
#define SENTRAOS_ACCESS_ALL           0xFFFF
#define SENTRAOS_ACCESS_GENERIC_READ  0x0100
#define SENTRAOS_ACCESS_GENERIC_WRITE 0x0200
#define SENTRAOS_ACCESS_GENERIC_ALL   0x0800

/* Initialize the object manager. Must be called first. */
int sentraos_om_init(void);

/* Create a new object. Returns object ID or 0 on failure. */
u32  sentraos_om_create_object(const char *name, u32 type_id,
			       u32 default_access, void *data, u64 data_size);

/* Delete an object (unlinks from parent, frees if refcount hits 0). */
int  sentraos_om_delete_object(u32 obj_id);

/* Reference counting */
void sentraos_om_ref(u32 obj_id);
void sentraos_om_deref(u32 obj_id);
u64  sentraos_om_ref_count(u32 obj_id);

/* Handle management */
int  sentraos_om_open_handle(u32 obj_id, u32 desired_access, u32 *handle);
int  sentraos_om_close_handle(u32 handle);
u32  sentraos_om_handle_to_obj(u32 handle);

/* Directory / namespace operations */
u32  sentraos_om_create_directory(const char *name);
int  sentraos_om_link(u32 dir_id, u32 obj_id);
int  sentraos_om_unlink(u32 dir_id, u32 obj_id);
u32  sentraos_om_lookup(const char *name);
int  sentraos_om_enumerate(u32 dir_id, u32 *buf, u32 buf_size);

/* Security / access control */
int  sentraos_om_set_security(u32 obj_id, u64 security_ctx);
int  sentraos_om_check_access(u32 obj_id, u32 desired_access, u64 subject_ctx);
int  sentraos_om_set_default_access(u32 obj_id, u32 access);

/* Query / introspection */
u32  sentraos_om_get_type(u32 obj_id);
void *sentraos_om_get_data(u32 obj_id);
int  sentraos_om_set_data(u32 obj_id, void *data, u64 data_size);
int  sentraos_om_get_name(u32 obj_id, char *buf, u32 buf_size);
u32  sentraos_om_stats(void);
int  sentraos_om_is_init(void);

#else /* CONFIG_SENTRAOS_OBJECT_MANAGER */

static inline int  sentraos_om_init(void) { return 0; }
static inline u32  sentraos_om_create_object(const char *name, u32 type_id,
					     u32 da, void *data, u64 size) { return 0; }
static inline int  sentraos_om_delete_object(u32 id) { return 0; }
static inline void sentraos_om_ref(u32 id) { }
static inline void sentraos_om_deref(u32 id) { }
static inline u64  sentraos_om_ref_count(u32 id) { return 0; }
static inline int  sentraos_om_open_handle(u32 id, u32 a, u32 *h) { return 0; }
static inline int  sentraos_om_close_handle(u32 h) { return 0; }
static inline u32  sentraos_om_handle_to_obj(u32 h) { return 0; }
static inline u32  sentraos_om_create_directory(const char *n) { return 0; }
static inline int  sentraos_om_link(u32 d, u32 o) { return 0; }
static inline int  sentraos_om_unlink(u32 d, u32 o) { return 0; }
static inline u32  sentraos_om_lookup(const char *n) { return 0; }
static inline int  sentraos_om_enumerate(u32 d, u32 *b, u32 s) { return 0; }
static inline int  sentraos_om_set_security(u32 id, u64 ctx) { return 0; }
static inline int  sentraos_om_check_access(u32 id, u32 a, u64 ctx) { return 0; }
static inline int  sentraos_om_set_default_access(u32 id, u32 a) { return 0; }
static inline u32  sentraos_om_get_type(u32 id) { return 0; }
static inline void *sentraos_om_get_data(u32 id) { return NULL; }
static inline int  sentraos_om_set_data(u32 id, void *d, u64 s) { return 0; }

#endif /* CONFIG_SENTRAOS_OBJECT_MANAGER */
#endif /* _LINUX_SENTRAOS_OBJECT_MANAGER_H_ */
