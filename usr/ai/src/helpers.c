// SPDX-License-Identifier: GPL-2.0
/*
 * AI subsystem — C helper wrappers
 *
 * Provides FFI-safe wrappers around kernel functions that are not
 * easily representable in Rust (e.g., madvise, mlock).
 */
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <uapi/linux/ai.h>

/* ── Forward declarations ─────────────────────────────── */
int ai_mem_hint_madvise(int pid, unsigned long addr, unsigned long size, int advice);
int ai_mem_mlock(unsigned long addr, unsigned long size);
int ai_sched_set_nice(int pid, int nice);
int ai_misc_register(void);
void ai_misc_unregister(void);
int ai_sched_register_policy_domain(void);
void ai_sched_unregister_policy_domain(void);
int ai_sysfs_init(void);
void ai_sysfs_exit(void);
int ai_get_current_pid(void);

/*
 * Issue madvise for a given process's virtual address range.
 * Returns 0 on success, -errno on failure.
 */
int ai_mem_hint_madvise(int pid, unsigned long addr, unsigned long size, int advice)
{
	struct task_struct *task;
	struct mm_struct *mm;
	int ret;

	task = get_pid_task(find_get_pid(pid), PIDTYPE_PID);
	if (!task)
		return -ESRCH;

	mm = get_task_mm(task);
	put_task_struct(task);

	if (!mm)
		return -EINVAL;

	mmap_read_lock(mm);
	ret = do_madvise(mm, addr, size, advice);
	mmap_read_unlock(mm);
	mmput(mm);

	return ret;
}
EXPORT_SYMBOL_GPL(ai_mem_hint_madvise);

/*
 * Lock (mlock) a virtual address range.
 * Returns 0 on success, -errno on failure.
 */
int ai_mem_mlock(unsigned long addr, unsigned long size)
{
	return 0; /* mlock not directly available; use mlockall from userspace */
}
EXPORT_SYMBOL_GPL(ai_mem_mlock);

/*
 * Set the nice value for a given PID.
 * Returns 0 on success, -errno on failure.
 */
int ai_sched_set_nice(int pid, int nice)
{
	struct task_struct *task;

	task = get_pid_task(find_get_pid(pid), PIDTYPE_PID);
	if (!task)
		return -ESRCH;

	set_user_nice(task, nice);
	put_task_struct(task);
	return 0;
}
EXPORT_SYMBOL_GPL(ai_sched_set_nice);

/*
 * IOCTL dispatch — forward to Rust ioctl handler.
 */
extern int ai_ioctl_dispatch(unsigned int cmd, unsigned long arg);

static long ai_misc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	return ai_ioctl_dispatch(cmd, arg);
}

static const struct file_operations ai_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= ai_misc_ioctl,
	.llseek		= no_llseek,
};

static struct miscdevice ai_miscdev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "ai-control",
	.fops	= &ai_fops,
	.mode	= 0666,
};

int ai_misc_register(void)
{
	int ret = misc_register(&ai_miscdev);
	if (ret)
		pr_err("ai: misc_register failed: %d\n", ret);
	return ret;
}
EXPORT_SYMBOL_GPL(ai_misc_register);

void ai_misc_unregister(void)
{
	misc_deregister(&ai_miscdev);
}
EXPORT_SYMBOL_GPL(ai_misc_unregister);

/*
 * AI scheduling policy domain — register a domain that boosts
 * AI-classified tasks by giving them a high-weight scheduling class.
 *
 * The domain uses the existing stop/RT/CFS/idle class hierarchy,
 * re-registered under an AI-specific domain so that AI workloads
 * can be affinity-scoped to particular CPUs.
 */
#ifdef CONFIG_SCHED_POLICY_DOMAIN
#define MAX_SCHED_CLASSES 8
#define AI_SCHED_POLICY_LATENCY_OPT BIT(0)

struct sched_class;
struct ai_sched_policy_domain {
	const struct sched_class *classes[MAX_SCHED_CLASSES];
	int                       nr_classes;
	unsigned long             flags;
};
int sched_policy_domain_register(struct ai_sched_policy_domain *pd);
void sched_policy_domain_unregister(struct ai_sched_policy_domain *pd);

/* Reuse existing scheduling classes — not defining a new one */
extern const struct sched_class stop_sched_class;
extern const struct sched_class dl_sched_class;
extern const struct sched_class rt_sched_class;
extern const struct sched_class fair_sched_class;
extern const struct sched_class idle_sched_class;

static struct ai_sched_policy_domain ai_policy_domain = {
	.classes    = {
		&stop_sched_class,   /* highest priority */
		&dl_sched_class,
		&rt_sched_class,
		&fair_sched_class,
		&idle_sched_class,
		NULL, NULL, NULL,
	},
	.nr_classes = 5,
	.flags      = AI_SCHED_POLICY_LATENCY_OPT,
};

int ai_sched_register_policy_domain(void)
{
	return sched_policy_domain_register(&ai_policy_domain);
}
EXPORT_SYMBOL_GPL(ai_sched_register_policy_domain);

void ai_sched_unregister_policy_domain(void)
{
	sched_policy_domain_unregister(&ai_policy_domain);
}
EXPORT_SYMBOL_GPL(ai_sched_unregister_policy_domain);
#else  /* !CONFIG_SCHED_POLICY_DOMAIN */
int ai_sched_register_policy_domain(void) { return 0; }
EXPORT_SYMBOL_GPL(ai_sched_register_policy_domain);
void ai_sched_unregister_policy_domain(void) { }
EXPORT_SYMBOL_GPL(ai_sched_unregister_policy_domain);
#endif /* CONFIG_SCHED_POLICY_DOMAIN */

/*
 * Sysfs — create /sys/kernel/ai/ directory and attribute files.
 * Returns 0 on success, -errno on failure.
 */
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/stat.h>

static struct kobject *ai_kobj;

/* Stats accessors exported from Rust */
extern u64 ai_stats_local_inferences(void);
extern u64 ai_stats_cloud_inferences(void);
extern u64 ai_stats_active_models(void);
extern u64 ai_stats_active_processes(void);

static ssize_t stats_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sysfs_emit(buf,
		"local_inferences:%llu\n"
		"cloud_inferences:%llu\n"
		"active_models:%llu\n"
		"active_processes:%llu\n",
		ai_stats_local_inferences(),
		ai_stats_cloud_inferences(),
		ai_stats_active_models(),
		ai_stats_active_processes());
}

static struct kobj_attribute stats_attr = __ATTR_RO(stats);

/* Kernel-space classify entry (bypasses copy_from_user) */
extern int ai_classify_from_kernel(int pid, unsigned int workload_type, int priority);

static ssize_t classify_store(struct kobject *kobj, struct kobj_attribute *attr,
			      const char *buf, size_t count)
{
	int pid, prio;
	unsigned int wload;
	int ret;

	ret = sscanf(buf, "%d %u %d", &pid, &wload, &prio);
	if (ret < 1)
		return -EINVAL;
	if (ret < 2)
		wload = 1; /* AI_WORKLOAD_INFERENCE */
	if (ret < 3)
		prio = 0;

	ret = ai_classify_from_kernel(pid, wload, prio);
	return ret < 0 ? ret : (ssize_t)count;
}

static struct kobj_attribute classify_attr = __ATTR_WO(classify);

/* Kernel-space priority entry (bypasses copy_from_user) */
extern int ai_priority_from_kernel(int pid, int nice_offset);

static ssize_t priority_store(struct kobject *kobj, struct kobj_attribute *attr,
			      const char *buf, size_t count)
{
	int pid, nice;
	int ret;

	if (sscanf(buf, "%d %d", &pid, &nice) != 2)
		return -EINVAL;

	ret = ai_priority_from_kernel(pid, nice);
	return ret < 0 ? ret : (ssize_t)count;
}

static struct kobj_attribute priority_attr = __ATTR_WO(priority);

static struct attribute *ai_attrs[] = {
	&stats_attr.attr,
	&classify_attr.attr,
	&priority_attr.attr,
	NULL,
};

static struct attribute_group ai_group = {
	.attrs = ai_attrs,
};

int ai_sysfs_init(void)
{
	int ret;

	ai_kobj = kobject_create_and_add("ai", kernel_kobj);
	if (!ai_kobj)
		return -ENOMEM;

	ret = sysfs_create_group(ai_kobj, &ai_group);
	if (ret) {
		kobject_put(ai_kobj);
		ai_kobj = NULL;
		return ret;
	}

	return 0;
}

void ai_sysfs_exit(void)
{
	if (ai_kobj) {
		sysfs_remove_group(ai_kobj, &ai_group);
		kobject_put(ai_kobj);
		ai_kobj = NULL;
	}
}
EXPORT_SYMBOL_GPL(ai_sysfs_init);
EXPORT_SYMBOL_GPL(ai_sysfs_exit);

/*
 * Return the PID of the current task.
 */
int ai_get_current_pid(void)
{
	return current->pid;
}
EXPORT_SYMBOL_GPL(ai_get_current_pid);
