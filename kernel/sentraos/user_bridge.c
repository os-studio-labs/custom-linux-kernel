// SPDX-License-Identifier: GPL-2.0
/*
 * sentraos_user_bridge — IPC bridge for user-space kernel subsystems.
 *
 * Allows filesystem daemons, network protocol handlers, and eventually
 * drivers to run in Ring 3 and communicate with the kernel via a
 * structured capability-based IPC channel.
 *
 * Architecture:
 *   Ring 3 (daemon) <──> /dev/sentraos/bridge <──> Ring 0 (kernel core)
 *                                      │
 *                                      └──> Orchestrator (monitoring)
 *
 * Each message is capability-checked: a daemon can only perform
 * operations that the orchestrator has explicitly granted.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/export.h>
#include <linux/poll.h>

#define SENTRAOS_BRIDGE_MAX_MSG	4096
#define SENTRAOS_BRIDGE_QUEUE	64

/* ── Message types ─────────────────────────────────────── */

enum sentraos_msg_type {
	SENTRAOS_MSG_NONE		= 0,
	SENTRAOS_MSG_FS_READ		= 1,
	SENTRAOS_MSG_FS_WRITE		= 2,
	SENTRAOS_MSG_FS_OPEN		= 3,
	SENTRAOS_MSG_FS_RELEASE		= 4,
	SENTRAOS_MSG_NET_SEND		= 10,
	SENTRAOS_MSG_NET_RECV		= 11,
	SENTRAOS_MSG_DRIVER_IOCTL	= 20,
	SENTRAOS_MSG_DRIVER_MMIO	= 21,
	SENTRAOS_MSG_ORCHESTRATOR	= 100,
};

/* ── Bridge message ────────────────────────────────────── */

struct sentraos_msg {
	u32			type;
	u32			flags;
	u64			capability; /* capability token */
	u64			arg1;
	u64			arg2;
	u64			arg3;
	u64			result;
	char			data[SENTRAOS_BRIDGE_MAX_MSG];
};

/* ── Per-open context ───────────────────────────────────- */

struct bridge_client {
	struct sentraos_msg	queue[SENTRAOS_BRIDGE_QUEUE];
	int			head;
	int			tail;
	wait_queue_head_t	wq;
	struct mutex		lock;
	u64			capabilities; /* bitmask of granted caps */
	pid_t			pid;
};

/* ── Device management ─────────────────────────────────── */

static int bridge_open(struct inode *inode, struct file *filp)
{
	struct bridge_client *client;

	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (!client)
		return -ENOMEM;

	mutex_init(&client->lock);
	init_waitqueue_head(&client->wq);
	client->head = 0;
	client->tail = 0;
	client->pid = current->pid;

	/* Grant basic capabilities */
	client->capabilities = 0;

	filp->private_data = client;
	return 0;
}

static int bridge_release(struct inode *inode, struct file *filp)
{
	struct bridge_client *client = filp->private_data;

	if (client)
		kfree(client);
	return 0;
}

static ssize_t bridge_write(struct file *filp, const char __user *buf,
			    size_t len, loff_t *off)
{
	struct bridge_client *client = filp->private_data;
	struct sentraos_msg msg;
	int next;

	if (len > sizeof(msg))
		return -E2BIG;

	if (copy_from_user(&msg, buf, len))
		return -EFAULT;

	mutex_lock(&client->lock);
	next = (client->head + 1) % SENTRAOS_BRIDGE_QUEUE;
	if (next == client->tail) {
		mutex_unlock(&client->lock);
		return -EAGAIN; /* queue full */
	}

	memcpy(&client->queue[client->head], &msg, sizeof(msg));
	client->head = next;
	mutex_unlock(&client->lock);

	wake_up_interruptible(&client->wq);
	return len;
}

static ssize_t bridge_read(struct file *filp, char __user *buf,
			   size_t len, loff_t *off)
{
	struct bridge_client *client = filp->private_data;
	struct sentraos_msg msg;
	int ret;

	if (len < sizeof(msg))
		return -EINVAL;

	ret = wait_event_interruptible(client->wq,
		client->head != client->tail);
	if (ret)
		return ret;

	mutex_lock(&client->lock);
	if (client->tail == client->head) {
		mutex_unlock(&client->lock);
		return 0;
	}

	memcpy(&msg, &client->queue[client->tail], sizeof(msg));
	client->tail = (client->tail + 1) % SENTRAOS_BRIDGE_QUEUE;
	mutex_unlock(&client->lock);

	if (copy_to_user(buf, &msg, sizeof(msg)))
		return -EFAULT;

	return sizeof(msg);
}

static __poll_t bridge_poll(struct file *filp, poll_table *wait)
{
	struct bridge_client *client = filp->private_data;
	__poll_t mask = 0;

	poll_wait(filp, &client->wq, wait);

	if (client->head != client->tail)
		mask |= EPOLLIN | EPOLLRDNORM;

	return mask;
}

/* ── IOCTL: capability management ──────────────────────── */

enum {
	BRIDGE_IOCTL_GET_CAPS	= _IOR('S', 1, u64),
	BRIDGE_IOCTL_REQ_CAP	= _IOWR('S', 2, u64),
};

static long bridge_ioctl(struct file *filp, unsigned int cmd,
			 unsigned long arg)
{
	struct bridge_client *client = filp->private_data;
	u64 cap;

	switch (cmd) {
	case BRIDGE_IOCTL_GET_CAPS:
		if (copy_to_user((void __user *)arg, &client->capabilities,
				 sizeof(client->capabilities)))
			return -EFAULT;
		return 0;

	case BRIDGE_IOCTL_REQ_CAP:
		if (copy_from_user(&cap, (void __user *)arg, sizeof(cap)))
			return -EFAULT;

		/*
		 * Capability request — orchestrator would validate.
		 * For now, grant all (simplified).
		 */
		client->capabilities |= cap;
		return 0;

	default:
		return -ENOTTY;
	}
}

static const struct file_operations bridge_fops = {
	.owner		= THIS_MODULE,
	.open		= bridge_open,
	.release	= bridge_release,
	.read		= bridge_read,
	.write		= bridge_write,
	.poll		= bridge_poll,
	.unlocked_ioctl	= bridge_ioctl,
};

static struct miscdevice bridge_dev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "sentraos_bridge",
	.fops	= &bridge_fops,
};

/* ── Init ───────────────────────────────────────────────- */

static int __init sentraos_bridge_init(void)
{
	int ret;

	ret = misc_register(&bridge_dev);
	if (ret) {
		pr_err("sentraos: failed to register bridge device\n");
		return ret;
	}

	pr_info("sentraos: user-space bridge at /dev/sentraos_bridge\n");
	return 0;
}
device_initcall(sentraos_bridge_init);

static void __exit sentraos_bridge_exit(void)
{
	misc_deregister(&bridge_dev);
}
__exitcall(sentraos_bridge_exit);
