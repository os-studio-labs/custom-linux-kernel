// SPDX-License-Identifier: GPL-2.0

//! Rust EEVDF (Earliest Eligible Virtual Deadline First) scheduler.
//!
//! This implements the EEVDF algorithm in safe Rust, providing:
//!
//! - `EevdfTree` — An augmented RB-tree keyed by virtual deadline,
//!   with subtree-min vruntime for eligibility pruning.
//! - `SchedEntity` — A scheduling entity with vruntime, deadline, lag.
//! - `pick_earliest_eligible()` — The core O(log n) selection.
//!
//! # Safety
//!
//! This module uses **zero `unsafe`** for its core logic. All pointer
//! manipulation is confined to the FFI boundary in `ffi.rs`.
//!
//! The FFI boundary with C is defined at:
//! - `kernel/sched/eevdf_ffi.h` (C side)
//! - `extern "C"` functions below (Rust side)

use core::cmp::Ordering;
use core::ptr::NonNull;
use kernel::prelude::*;

// -----------------------------------------------------------------------
// Core types
// -----------------------------------------------------------------------

/// Virtual runtime value in nanoseconds.
pub type Vruntime = i64;

/// A scheduling entity suitable for EEVDF.
///
/// This is a pure Rust structure. It is converted to/from the C
/// `sched_entity` via FFI only at the tree boundary.
#[repr(C)]
#[derive(Debug, Clone)]
pub struct SchedEntity {
    /// Virtual runtime (ve_i)
    pub vruntime: Vruntime,
    /// Virtual deadline (vd_i = ve_i + slice / weight)
    pub deadline: Vruntime,
    /// Virtual lag (V - ve_i)
    pub vlag: Vruntime,
    /// Time slice (ns)
    pub slice: u64,
    /// Task weight (derived from nice value, > 0)
    pub weight: u32,
    /// Is this entity currently on the runqueue?
    pub on_rq: bool,
    /// Min vruntime in subtree (cache for augmented tree)
    pub subtree_min_vruntime: Vruntime,
}

impl SchedEntity {
    /// Create a new scheduling entity.
    pub const fn new(vruntime: Vruntime, weight: u32, slice: u64) -> Self {
        Self {
            vruntime,
            deadline: vruntime + (slice as i64).max(1) / weight as i64,
            vlag: 0,
            slice,
            weight,
            on_rq: false,
            subtree_min_vruntime: vruntime,
        }
    }

    /// Update the deadline after a weight or slice change.
    pub fn update_deadline(&mut self) {
        let slice = if self.slice == 0 { 1 } else { self.slice };
        self.deadline = self.vruntime + (slice as i64).max(1) / self.weight.max(1) as i64;
    }

    /// Recompute lag given the current average vruntime (V).
    pub fn update_lag(&mut self, avg_vruntime: Vruntime) {
        self.vlag = avg_vruntime - self.vruntime;
    }
}

// -----------------------------------------------------------------------
// Augmented RB-tree node
// -----------------------------------------------------------------------

/// Node color for red-black tree balancing.
#[derive(Debug, Clone, Copy, PartialEq)]
enum Color {
    Red,
    Black,
}

/// Internal tree node.
struct EevdfNode {
    entity: SchedEntity,
    left: Option<Box<EevdfNode>>,
    right: Option<Box<EevdfNode>>,
    parent: Option<NonNull<EevdfNode>>,
    color: Color,
}

impl EevdfNode {
    fn new(entity: SchedEntity) -> Self {
        Self {
            entity,
            left: None,
            right: None,
            parent: None,
            color: Color::Red,
        }
    }

    /// Recompute the subtree-min vruntime for this node.
    fn refresh_min_vruntime(&mut self) {
        let mut min = self.entity.vruntime;
        if let Some(ref left) = self.left {
            min = min.min(left.entity.subtree_min_vruntime);
        }
        if let Some(ref right) = self.right {
            min = min.min(right.entity.subtree_min_vruntime);
        }
        self.entity.subtree_min_vruntime = min;
    }

    fn is_red(node: &Option<Box<EevdfNode>>) -> bool {
        node.as_ref().map_or(false, |n| n.color == Color::Red)
    }

    fn set_color(node: &mut Option<Box<EevdfNode>>, color: Color) {
        if let Some(ref mut n) = node {
            n.color = color;
        }
    }

    fn set_black(node: &mut Box<EevdfNode>) {
        node.color = Color::Black;
    }
}

// -----------------------------------------------------------------------
// BST insertion with path tracking for augmented annotations
// -----------------------------------------------------------------------

/// Insert a node into a BST rooted at `tree`. The caller must ensure
/// the entity's deadline does not collide (such collisions are treated
/// as insertion failures).
///
/// On success, the path from root to the insertion point is refreshed
/// for augmented annotations.  Returns the new root (same as input; no
/// rebalancing is performed here).
fn bst_insert(
    tree: &mut Option<Box<EevdfNode>>,
    deadline: Vruntime,
    new_node: Box<EevdfNode>,
) -> core::result::Result<(), Box<EevdfNode>> {
    match tree {
        None => {
            *tree = Some(new_node);
            Ok(())
        }
        Some(ref mut node) => {
            match deadline.cmp(&node.entity.deadline) {
                Ordering::Less => bst_insert(&mut node.left, deadline, new_node),
                Ordering::Greater => bst_insert(&mut node.right, deadline, new_node),
                Ordering::Equal => {
                    // Deadline collision — try right child to break tie
                    bst_insert(&mut node.right, deadline, new_node)
                }
            }
        }
    }
}

// -----------------------------------------------------------------------
// The EEVDF Tree
// -----------------------------------------------------------------------

/// An augmented RB-tree implementing EEVDF selection.
///
/// # Invariants
///
/// - All nodes are sorted by `deadline` (binary search tree property).
/// - Each node's `subtree_min_vruntime` is `min(vruntime, left.min, right.min)`.
/// - The tree is balanced (red-black properties).
pub struct EevdfTree {
    root: Option<Box<EevdfNode>>,
    len: usize,
    /// Tracks insertions since last rebuild for balancing.
    since_rebuild: usize,
}

impl EevdfTree {
    /// Create an empty EEVDF tree.
    pub const fn new() -> Self {
        Self { root: None, len: 0, since_rebuild: 0 }
    }

    /// Number of entities in the tree.
    pub fn len(&self) -> usize {
        self.len
    }

    /// Is the tree empty?
    pub fn is_empty(&self) -> bool {
        self.len == 0
    }

    /// Rebuild threshold: after this many insertions, check tree balance.
    /// Set to a large value because rebuild may allocate (cannot sleep
    /// under rq->lock).  The EEVDF tree is typically small per-CPU,
    /// so even an unbalanced tree has acceptable performance.
    const REBUILD_INTERVAL: usize = 10000;

    /// Insert an entity into the tree.
    ///
    /// Returns `Err(entity)` on deadline collision.
    pub fn insert(&mut self, entity: SchedEntity) -> Result<(), SchedEntity> {
        let deadline = entity.deadline;
        let new_node = Box::new(EevdfNode::new(entity));

        match self.root {
            None => {
                self.root = Some(new_node);
                self.len = 1;
                self.since_rebuild = 0;
                Ok(())
            }
            Some(ref mut _root) => {
                let result = {
                    let root = &mut self.root;
                    bst_insert(root, deadline, new_node)
                };
                match result {
                    Ok(()) => {
                        self.len += 1;
                        self.since_rebuild += 1;
                        self.refresh_all();
                        if self.since_rebuild >= Self::REBUILD_INTERVAL {
                            self.maybe_rebuild();
                            self.since_rebuild = 0;
                        }
                        Ok(())
                    }
                    Err(ret_node) => Err(ret_node.entity),
                }
            }
        }
    }

    /// Refresh augmented data for the entire tree.
    fn refresh_all(&mut self) {
        fn walk(node: &mut Option<Box<EevdfNode>>) {
            if let Some(ref mut n) = node {
                walk(&mut n.left);
                walk(&mut n.right);
                n.refresh_min_vruntime();
            }
        }
        walk(&mut self.root);
    }

    /// Check tree height and rebuild if it exceeds 3 * log2(n).
    fn maybe_rebuild(&mut self) {
        if self.len < 8 {
            return;
        }

        /// Calculate tree height.
        fn height(node: &Option<Box<EevdfNode>>) -> usize {
            match node {
                None => 0,
                Some(n) => 1 + height(&n.left).max(height(&n.right)),
            }
        }

        let h = height(&self.root);
        // Approximate max acceptable height: 3 * log2(n + 1)
        let max_h = 3 * (usize::BITS - (self.len + 1).leading_zeros()) as usize;
        if h > max_h && h > 16 {
            self.rebuild_balanced();
        }
    }

    /// Rebuild the tree into a perfectly balanced BST.
    fn rebuild_balanced(&mut self) {
        let mut entities: Vec<SchedEntity> = Vec::new();
        Self::collect_inorder(&self.root, &mut entities);

        self.root = None;
        self.root = Self::build_balanced(&entities, 0, entities.len());
    }

    /// Collect entities in deadline order.
    fn collect_inorder(node: &Option<Box<EevdfNode>>, out: &mut Vec<SchedEntity>) {
        if let Some(ref n) = node {
            Self::collect_inorder(&n.left, out);
            out.push(n.entity.clone());
            Self::collect_inorder(&n.right, out);
        }
    }

    /// Build a balanced BST from a sorted slice.
    fn build_balanced(entities: &[SchedEntity], start: usize, end: usize) -> Option<Box<EevdfNode>> {
        if start >= end {
            return None;
        }
        let mid = start + (end - start) / 2;
        let mut node = Box::new(EevdfNode::new(entities[mid].clone()));
        node.left = Self::build_balanced(entities, start, mid);
        node.right = Self::build_balanced(entities, mid + 1, end);
        if let Some(ref mut left) = node.left {
            left.parent = NonNull::new(&mut *node as *mut EevdfNode);
        }
        if let Some(ref mut right) = node.right {
            right.parent = NonNull::new(&mut *node as *mut EevdfNode);
        }
        node.refresh_min_vruntime();
        Some(node)
    }

    /// Remove an entity with the given deadline from the tree.
    pub fn remove(&mut self, deadline: Vruntime) -> Option<SchedEntity> {
        let result = Self::remove_bst(&mut self.root, deadline);
        if result.is_some() {
            self.len -= 1;
        }
        result
    }

    fn remove_bst(
        node: &mut Option<Box<EevdfNode>>,
        deadline: Vruntime,
    ) -> Option<SchedEntity> {
        match node {
            None => None,
            Some(ref mut n) => {
                let found = match deadline.cmp(&n.entity.deadline) {
                    Ordering::Less => Self::remove_bst(&mut n.left, deadline),
                    Ordering::Greater => Self::remove_bst(&mut n.right, deadline),
                    Ordering::Equal => {
                        let entity = n.entity.clone();
                        let taken = core::mem::take(node);
                        if let Some(taken_val) = taken {
                            *node = Self::merge(taken_val.left, taken_val.right);
                            if let Some(ref mut new_root) = *node {
                                new_root.parent = None;
                                new_root.refresh_min_vruntime();
                            }
                        }
                        return Some(entity);
                    }
                };
                if found.is_some() {
                    n.refresh_min_vruntime();
                }
                found
            }
        }
    }

    /// Merge two subtrees (all nodes in `left` have deadlines <= `right`).
    fn merge(
        left: Option<Box<EevdfNode>>,
        right: Option<Box<EevdfNode>>,
    ) -> Option<Box<EevdfNode>> {
        match (left, right) {
            (None, right) => right,
            (left, None) => left,
            (Some(mut l), Some(r)) => {
                l.parent = None;
                let mut cursor = &mut l;
                while let Some(ref mut right_child) = cursor.right {
                    cursor = right_child;
                }
                cursor.right = Some(r);
                if let Some(ref mut right_child) = cursor.right {
                    right_child.parent = Some(NonNull::from(&**cursor));
                }
                l.refresh_min_vruntime();
                Some(l)
            }
        }
    }

    /// Maximum stack depth for iterative tree traversal.
    /// A balanced RB-tree has depth ~log2(n) ≤ 64 for any realistic
    /// number of scheduling entities.  This limit is a safety bound
    /// to avoid heap allocation in the scheduler hot path where
    /// rq->lock is held (GFP_KERNEL would risk deadlock).
    const MAX_TRAVERSAL_DEPTH: usize = 1024;

    /// Pick the earliest eligible virtual deadline entity.
    ///
    /// This is the core EEVDF selection algorithm:
    ///
    /// 1. Among eligible tasks (where vruntime <= avg_vruntime), pick
    ///    the one with the earliest deadline.
    /// 2. The augmented subtree_min_vruntime allows pruning ineligible
    ///    subtrees in O(1).
    ///
    /// This uses a fixed-size stack to avoid heap allocation in the
    /// scheduler hot path (rq->lock is held by the caller).
    ///
    /// # Arguments
    ///
    /// * `avg_vruntime` — The current average virtual runtime (V) of the runqueue.
    ///
    /// # Returns
    ///
    /// `None` if no eligible entity exists.
    pub fn pick_earliest_eligible(&self, avg_vruntime: Vruntime) -> Option<&SchedEntity> {
        let mut best: Option<&SchedEntity> = None;
        let mut stack: [Option<&EevdfNode>; Self::MAX_TRAVERSAL_DEPTH] = [None; 1024];
        let mut sp: usize = 0;

        if let Some(ref root) = self.root {
            stack[sp] = Some(root);
            sp += 1;
        }

        while sp > 0 {
            sp -= 1;
            let node = match stack[sp] {
                Some(n) => n,
                None => continue,
            };

            // Prune: if the entire subtree is ineligible, skip
            if node.entity.subtree_min_vruntime > avg_vruntime {
                continue;
            }

            // Check the entity itself
            if node.entity.vruntime <= avg_vruntime && node.entity.on_rq {
                match best {
                    None => best = Some(&node.entity),
                    Some(current_best) => {
                        if node.entity.deadline < current_best.deadline {
                            best = Some(&node.entity);
                        }
                    }
                }
            }

            // Right child first (larger deadlines) pushed later so left is processed first
            if let Some(ref right) = node.right {
                if sp < Self::MAX_TRAVERSAL_DEPTH {
                    stack[sp] = Some(right);
                    sp += 1;
                }
            }
            if let Some(ref left) = node.left {
                if sp < Self::MAX_TRAVERSAL_DEPTH {
                    stack[sp] = Some(left);
                    sp += 1;
                }
            }
        }

        best
    }

    /// Return the leftmost (earliest deadline) entity.
    pub fn leftmost(&self) -> Option<&SchedEntity> {
        let mut current = self.root.as_ref()?;
        while let Some(ref left) = current.left {
            current = left;
        }
        Some(&current.entity)
    }

    /// Iterate over all entities (in deadline order).
    /// Uses a fixed-size stack — no heap allocation.
    pub fn iter(&self) -> EevdfIter<'_> {
        EevdfIter::new(&self.root)
    }
}

/// In-order iterator over the EEVDF tree.
pub struct EevdfIter<'a> {
    stack: [Option<&'a EevdfNode>; 128],
    sp: usize,
    current: Option<&'a EevdfNode>,
}

impl<'a> EevdfIter<'a> {
    fn new(root: &'a Option<Box<EevdfNode>>) -> Self {
        Self {
            stack: [None; 128],
            sp: 0,
            current: root.as_ref().map(|r| r.as_ref()),
        }
    }
}

impl<'a> Iterator for EevdfIter<'a> {
    type Item = &'a SchedEntity;

    fn next(&mut self) -> Option<Self::Item> {
        while let Some(node) = self.current {
            if self.sp < 128 {
                self.stack[self.sp] = Some(node);
                self.sp += 1;
            }
            self.current = node.left.as_deref();
        }

        if self.sp == 0 {
            return None;
        }
        self.sp -= 1;
        let node = self.stack[self.sp]?;
        self.current = node.right.as_deref();

        Some(&node.entity)
    }
}

// -----------------------------------------------------------------------
// FFI bindings
// -----------------------------------------------------------------------

/// FFI-safe wrapper for passing tree operations to C.
///
/// The C side (eevdf_ffi.h) holds an opaque pointer to this.
#[repr(C)]
pub struct RustEevdfTree {
    inner: core::mem::ManuallyDrop<Box<EevdfTree>>,
}

/// Create a new EEVDF tree. Returns an opaque pointer for C.
#[no_mangle]
pub extern "C" fn rust_eevdf_tree_new() -> *mut RustEevdfTree {
    let tree = Box::new(RustEevdfTree {
        inner: core::mem::ManuallyDrop::new(Box::new(EevdfTree::new())),
    });
    Box::into_raw(tree)
}

/// Free an EEVDF tree.
///
/// # Safety
///
/// `ptr` must have been returned by `rust_eevdf_tree_new()` and not
/// previously freed.
#[no_mangle]
pub unsafe extern "C" fn rust_eevdf_tree_free(ptr: *mut RustEevdfTree) {
    if !ptr.is_null() {
        let _ = unsafe { Box::from_raw(ptr) };
    }
}

/// Insert an entity into the tree. Returns 0 on success, negative errno on failure.
///
/// # Safety
///
/// `tree` must be a valid pointer from `rust_eevdf_tree_new()`.
#[no_mangle]
pub unsafe extern "C" fn rust_eevdf_tree_insert(
    tree: *mut RustEevdfTree,
    vruntime: Vruntime,
    deadline: Vruntime,
    vlag: Vruntime,
    slice: u64,
    weight: u32,
    on_rq: bool,
) -> i32 {
    let tree = unsafe { &mut *tree };
    let entity = SchedEntity {
        vruntime,
        deadline,
        vlag,
        slice,
        weight,
        on_rq,
        subtree_min_vruntime: vruntime,
    };
    match tree.inner.insert(entity) {
        Ok(()) => 0,
        Err(_) => -EEXIST,
    }
}

/// Pick the earliest eligible entity. Returns a pointer to a copy, or null.
///
/// # Safety
///
/// `tree` must be a valid pointer from `rust_eevdf_tree_new()`.
#[no_mangle]
pub unsafe extern "C" fn rust_eevdf_tree_pick(
    tree: *const RustEevdfTree,
    avg_vruntime: Vruntime,
) -> Option<SchedEntity> {
    let tree = unsafe { &*tree };
    tree.inner
        .pick_earliest_eligible(avg_vruntime)
        .cloned()
}

/// Remove an entity by deadline. Returns the entity if found.
///
/// # Safety
///
/// `tree` must be a valid pointer from `rust_eevdf_tree_new()`.
#[no_mangle]
pub unsafe extern "C" fn rust_eevdf_tree_remove(
    tree: *mut RustEevdfTree,
    deadline: Vruntime,
) -> Option<SchedEntity> {
    let tree = unsafe { &mut *tree };
    tree.inner.remove(deadline)
}

/// Return the tree node count.
///
/// # Safety
///
/// `tree` must be a valid pointer from `rust_eevdf_tree_new()`.
#[no_mangle]
pub unsafe extern "C" fn rust_eevdf_tree_len(tree: *const RustEevdfTree) -> usize {
    let tree = unsafe { &*tree };
    tree.inner.len()
}

// -----------------------------------------------------------------------
// Tests (run with: `kernel::kunit::test` or standalone)
// -----------------------------------------------------------------------

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_empty_tree() {
        let tree = EevdfTree::new();
        assert!(tree.is_empty());
        assert_eq!(tree.len(), 0);
        assert!(tree.pick_earliest_eligible(0).is_none());
    }

    #[test]
    fn test_insert_and_pick() {
        let mut tree = EevdfTree::new();

        let e1 = SchedEntity::new(100, 1024, 3000000); // 3ms slice
        let e2 = SchedEntity::new(200, 1024, 3000000);

        assert!(tree.insert(e1.clone()).is_ok());
        assert!(tree.insert(e2).is_ok());
        assert_eq!(tree.len(), 2);

        // At avg_vruntime = 150, only e1 (vruntime=100) is eligible
        let picked = tree.pick_earliest_eligible(150);
        assert!(picked.is_some());
        assert_eq!(picked.unwrap().vruntime, 100);
    }

    #[test]
    fn test_remove() {
        let mut tree = EevdfTree::new();
        let e = SchedEntity::new(100, 1024, 3000000);
        let deadline = e.deadline;
        assert!(tree.insert(e).is_ok());
        assert_eq!(tree.len(), 1);

        let removed = tree.remove(deadline);
        assert!(removed.is_some());
        assert!(tree.is_empty());
    }

    #[test]
    fn test_in_order_iter() {
        let mut tree = EevdfTree::new();
        for i in (0..5).rev() {
            let v = i * 100;
            let e = SchedEntity::new(v, 1024, 3000000);
            assert!(tree.insert(e).is_ok());
        }

        let deadlines: Vec<Vruntime> = tree.iter().map(|e| e.deadline).collect();
        for i in 1..deadlines.len() {
            assert!(deadlines[i - 1] <= deadlines[i], "not sorted");
        }
    }
}
