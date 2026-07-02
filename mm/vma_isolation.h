/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_VMA_ISOLATION_H
#define _LINUX_VMA_ISOLATION_H

/*
 * VMA Isolation Layer — clean interface for VMA operations.
 *
 * PROBLEM:
 *   `struct vm_area_struct` is directly manipulated by ~350 filesystems,
 *   drivers, and core kernel code. Every field is visible to every
 *   consumer. This makes VMA layout changes extremely risky (each field
 *   addition requires auditing all 350+ users).
 *
 * SOLUTION:
 *   Define accessor functions for all VMA field accesses. Drivers
 *   that today access vma->vm_start, vma->vm_end, vma->vm_flags, etc.
 *   should use the accessor API instead.
 *
 *   Phase 1: Add accessors alongside direct field access (opt-in).
 *   Phase 2: Deprecate direct access for out-of-tree drivers.
 *   Phase 3: Make fields opaque via CONFIG_VMA_ISOLATION.
 *
 * This is NOT a rewrite — it's a mechanical transformation that
 * allows the VMA layout to evolve independently.
 */

#include <linux/mm_types.h>
#include <linux/mm.h>

#ifdef CONFIG_VMA_ISOLATION

/* ---------- Read accessors ---------- */

static inline unsigned long vma_start(const struct vm_area_struct *vma)
{ return vma->vm_start; }

static inline unsigned long vma_end(const struct vm_area_struct *vma)
{ return vma->vm_end; }

static inline unsigned long vma_size(const struct vm_area_struct *vma)
{ return vma->vm_end - vma->vm_start; }

static inline unsigned long vma_pgoff(const struct vm_area_struct *vma)
{ return vma->vm_pgoff; }

static inline unsigned long vma_file_offset(const struct vm_area_struct *vma)
{ return (unsigned long)vma->vm_pgoff << PAGE_SHIFT; }

static inline unsigned long vma_flags(const struct vm_area_struct *vma)
{ return vma->vm_flags; }

static inline pgprot_t vma_page_prot(const struct vm_area_struct *vma)
{ return vma->vm_page_prot; }

static inline bool vma_is_readable(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_READ; }

static inline bool vma_is_writable(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_WRITE; }

static inline bool vma_is_executable(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_EXEC; }

static inline bool vma_is_shared(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_SHARED; }

static inline bool vma_is_anonymous(const struct vm_area_struct *vma)
{ return vma->vm_file == NULL; }

static inline bool vma_is_mergeable(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_MERGEABLE; }

static inline bool vma_is_pfnmap(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_PFNMAP; }

static inline bool vma_is_io(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_IO; }

static inline bool vma_is_dax(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_DAX; }

static inline bool vma_is_maywrite(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_MAYWRITE; }

static inline bool vma_is_mayread(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_MAYREAD; }

static inline bool vma_is_mayexec(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_MAYEXEC; }

static inline bool vma_is_growsdown(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_GROWSDOWN; }

static inline bool vma_is_growsup(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_GROWSUP; }

static inline bool vma_is_special(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_SPECIAL; }

static inline struct file *vma_file(const struct vm_area_struct *vma)
{ return vma->vm_file; }

static inline struct anon_vma *vma_anon_vma(const struct vm_area_struct *vma)
{ return vma->anon_vma; }

static inline const struct vm_operations_struct *vma_ops(
	const struct vm_area_struct *vma)
{ return vma->vm_ops; }

static inline struct mm_struct *vma_mm(const struct vm_area_struct *vma)
{ return vma->vm_mm; }

static inline struct vm_userfaultfd_ctx vma_userfaultfd_ctx(
	const struct vm_area_struct *vma)
{ return vma->vm_userfaultfd_ctx; }

#ifdef CONFIG_NUMA
static inline struct mempolicy *vma_policy(const struct vm_area_struct *vma)
{ return vma->vm_policy; }
#endif

static inline struct vma_numab_state *vma_numab_state(
	const struct vm_area_struct *vma)
{ return vma->vm_numab_state; }

static inline const char *vma_name(const struct vm_area_struct *vma)
{ return vma->vm_file ? vma->vm_file->f_path.dentry->d_name.name : NULL; }

/* ---------- VM ops convenience accessors ---------- */

static inline int vma_has_fault(const struct vm_area_struct *vma)
{ return vma->vm_ops && vma->vm_ops->fault; }

static inline int vma_has_map_pages(const struct vm_area_struct *vma)
{ return vma->vm_ops && vma->vm_ops->map_pages; }

static inline int vma_has_pfn_mkwrite(const struct vm_area_struct *vma)
{ return vma->vm_ops && vma->vm_ops->pfn_mkwrite; }

/* ---------- Mutators ---------- */

static inline void vma_set_start(struct vm_area_struct *vma,
				 unsigned long start)
{ vma->vm_start = start; }

static inline void vma_set_end(struct vm_area_struct *vma,
			       unsigned long end)
{ vma->vm_end = end; }

static inline void vma_set_pgoff(struct vm_area_struct *vma,
				 unsigned long pgoff)
{ vma->vm_pgoff = pgoff; }

static inline void vma_set_flags(struct vm_area_struct *vma,
				 unsigned long flags)
{ vma->vm_flags = flags; }

static inline void vma_add_flags(struct vm_area_struct *vma,
				 unsigned long flags)
{ vma->vm_flags |= flags; }

static inline void vma_clear_flags(struct vm_area_struct *vma,
				   unsigned long flags)
{ vma->vm_flags &= ~flags; }

static inline void vma_set_page_prot(struct vm_area_struct *vma,
				     pgprot_t prot)
{ vma->vm_page_prot = prot; }

static inline void vma_set_file(struct vm_area_struct *vma, struct file *file)
{ vma->vm_file = file; }

static inline void vma_set_anon_vma(struct vm_area_struct *vma,
				    struct anon_vma *anon_vma)
{ vma->anon_vma = anon_vma; }

static inline void vma_set_ops(struct vm_area_struct *vma,
			       const struct vm_operations_struct *ops)
{ vma->vm_ops = ops; }

static inline void vma_set_mm(struct vm_area_struct *vma,
			      struct mm_struct *mm)
{ vma->vm_mm = mm; }

/* ---------- VMA iteration helpers (maple-tree aware) ---------- */

/**
 * for_each_vma - iterate over VMAs in an mm_struct
 * @mm: the mm_struct
 * @vma: the iterator (struct vm_area_struct *)
 *
 * Safe against VMA removal during iteration (hold mmap_lock).
 */
#define for_each_vma(mm, vma)						\
	for (vma = vma_first(mm); vma; vma = vma_next(mm, vma))

static inline struct vm_area_struct *vma_first(struct mm_struct *mm)
{
	return vma_next(mm, NULL);
}

static inline struct vm_area_struct *vma_next(struct mm_struct *mm,
					      struct vm_area_struct *vma)
{
	if (vma)
		return vma->vm_next;
	return mm->mmap;
}

/* vma_lookup is provided by <linux/mm.h> via the maple tree. */

#else /* !CONFIG_VMA_ISOLATION */

/* When isolation is disabled, accessors map directly to fields.
 * These provide a consistent API regardless of config.
 */

static inline unsigned long vma_start(const struct vm_area_struct *vma)
{ return vma->vm_start; }

static inline unsigned long vma_end(const struct vm_area_struct *vma)
{ return vma->vm_end; }

static inline unsigned long vma_size(const struct vm_area_struct *vma)
{ return vma->vm_end - vma->vm_start; }

static inline unsigned long vma_pgoff(const struct vm_area_struct *vma)
{ return vma->vm_pgoff; }

static inline unsigned long vma_file_offset(const struct vm_area_struct *vma)
{ return (unsigned long)vma->vm_pgoff << PAGE_SHIFT; }

static inline unsigned long vma_flags(const struct vm_area_struct *vma)
{ return vma->vm_flags; }

static inline pgprot_t vma_page_prot(const struct vm_area_struct *vma)
{ return vma->vm_page_prot; }

static inline bool vma_is_readable(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_READ; }

static inline bool vma_is_writable(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_WRITE; }

static inline bool vma_is_executable(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_EXEC; }

static inline bool vma_is_shared(const struct vm_area_struct *vma)
{ return vma->vm_flags & VM_SHARED; }

static inline bool vma_is_anonymous(const struct vm_area_struct *vma)
{ return vma->vm_file == NULL; }

static inline struct file *vma_file(const struct vm_area_struct *vma)
{ return vma->vm_file; }

static inline struct anon_vma *vma_anon_vma(const struct vm_area_struct *vma)
{ return vma->anon_vma; }

static inline const struct vm_operations_struct *vma_ops(
	const struct vm_area_struct *vma)
{ return vma->vm_ops; }

static inline struct mm_struct *vma_mm(const struct vm_area_struct *vma)
{ return vma->vm_mm; }

static inline struct vm_userfaultfd_ctx vma_userfaultfd_ctx(
	const struct vm_area_struct *vma)
{ return vma->vm_userfaultfd_ctx; }

#ifdef CONFIG_NUMA
static inline struct mempolicy *vma_policy(const struct vm_area_struct *vma)
{ return vma->vm_policy; }
#endif

static inline struct vma_numab_state *vma_numab_state(
	const struct vm_area_struct *vma)
{ return vma->vm_numab_state; }

/* Mutators (always available) */

static inline void vma_set_start(struct vm_area_struct *vma,
				 unsigned long start)
{ vma->vm_start = start; }

static inline void vma_set_end(struct vm_area_struct *vma,
			       unsigned long end)
{ vma->vm_end = end; }

static inline void vma_set_flags(struct vm_area_struct *vma,
				 unsigned long flags)
{ vma->vm_flags = flags; }

static inline void vma_add_flags(struct vm_area_struct *vma,
				 unsigned long flags)
{ vma->vm_flags |= flags; }

static inline void vma_clear_flags(struct vm_area_struct *vma,
				   unsigned long flags)
{ vma->vm_flags &= ~flags; }

static inline void vma_set_file(struct vm_area_struct *vma, struct file *file)
{ vma->vm_file = file; }

static inline void vma_set_ops(struct vm_area_struct *vma,
			       const struct vm_operations_struct *ops)
{ vma->vm_ops = ops; }

#endif /* CONFIG_VMA_ISOLATION */

#endif /* _LINUX_VMA_ISOLATION_H */
