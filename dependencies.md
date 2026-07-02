# Complete Linux Kernel Dependency Map

## 1. Subsystem Classification & Dependency Graph

```
Legend:
  [CORE]      = Must stay in Ring 0 (hardware isolation, page tables, interrupts)
  [ISOLABLE]  = Can run in isolated Ring 0 sandbox (separate address space)
  [USER]      = Can be moved to user space with IPC bridge
  [HYBRID]    = Split: core part stays, rest moves
  ─────────►  = "depends on"
  ~~~►        = "calls via syscall/IPC"
```

### 1.1 Core Kernel ([CORE] — Ring 0, untouchable)

```
INIT (init/)
  ─► MM (mm/) ─► arch/*
  ─► SCHED (kernel/sched/) ─► MM
  ─► IRQ (kernel/irq/) ─► arch/*
  ─► TIME (kernel/time/) ─► arch/*

SCHEDULER (kernel/sched/)
  ─► MM (mm/memory.c, mm/slab.c) -> page allocation
  ─► IRQ (kernel/irq/) -> rescheduling from irq
  ─► TIME (kernel/time/) -> timeslice tracking
  ─► arch/*/kernel/smp.c -> IPI for reschedule

MEMORY MANAGER (mm/)
  ─► arch/*/mm/ -> page tables, TLB
  ─► kernel/fork.c -> COW, dup_mmap
  ─► drivers/char/mem.c -> /dev/mem access

IPC (ipc/)
  ─► MM -> shared memory segments
  ─► kernel/signal.c -> semaphore undo
  ─► fs/pipe.c -> pipe buffers

LOCKING (kernel/locking/)
  ─► arch/*/include/asm/spinlock.h
  ─► kernel/sched/core.c -> rt_mutex, pi_futex
```

### 1.2 Hardware Abstraction Layer ([CORE] — Ring 0)

```
IRQ subsystem (kernel/irq/)
  ─► drivers/irqchip/ -> irq domain mapping
  ─► arch/*/kernel/irq.c -> arch irq entry/exit

DMA API (kernel/dma/)
  ─► drivers/iommu/ -> iommu mapping
  ─► arch/*/include/asm/dma-mapping.h

PCI CORE (drivers/pci/)
  ─► kernel/dma/ -> dma mapping
  ─► kernel/irq/ -> msi, irq allocation
  ─► drivers/acpi/ -> acpi table parsing
  ─► arch/*/kernel/setup.c -> mmio ranges
```

### 1.3 VFS & Filesystems ([HYBRID])

```
VFS LAYER (fs/) — CORE part stays in Ring 0
  ~~~
  FS DRIVERS (fs/ext4, fs/btrfs, fs/xfs, ...) — ISOLABLE
  ~~~
  FUSE (fs/fuse/) — USER (already supports user space)

Dependencies:
  fs/*.c -> MM (page cache, readahead)
  fs/*.c -> block/ (submit_bio)
  fs/ext4 -> crypto/ (encryption)
  fs/btrfs -> lib/ (crc32c, lzo, zstd)
  fs/xfs -> kernel/locking/ (rwsem)
```

### 1.4 Networking Stack ([HYBRID])

```
NET CORE (net/core/) — must stay in Ring 0
  ─► net/sched/ (qdisc)
  ─► net/ipv4/, net/ipv6/ (TCP/UDP/IP) — ISOLABLE
  ─► net/packet/ (AF_PACKET) — ISOLABLE
  ─► net/wireless/ (cfg80211) — ISOLABLE
  ~~~
  NET DEVICE DRIVERS (drivers/net/) — USER (via IPC bridge)

Dependencies:
  net/core/skbuff.c -> MM (alloc_skb, pskb_copy)
  net/ipv4/tcp_ipv4.c -> crypto/ (checksum)
  net/core/dev.c -> kernel/irq/ (NAPI poll)
```

### 1.5 Block Layer ([HYBRID])

```
BLOCK LAYER (block/) — CORE
  ─► MM (bio allocation, page cache)
  ─► kernel/locking/ (queue lock)
  ~~~
  BLOCK DEVICE DRIVERS (drivers/block/, drivers/nvme/) — USER
  ~~~
  I/O SCHEDULERS (block/mq-deadline, kyber, bfq) — ISOLABLE
```

### 1.6 Device Drivers ([USER] via DAC sandbox)

```
PCI DRIVERS (drivers/pci/...) ─► PCI CORE
USB DRIVERS (drivers/usb/...) ─► USB CORE
PLATFORM DRIVERS (drivers/platform/...) ─► platform bus
I2C DRIVERS (drivers/i2c/...) ─► I2C CORE
SPI DRIVERS (drivers/spi/...) ─► SPI CORE
DRM/GPU (drivers/gpu/drm/...) ─► DRM CORE
SOUND (sound/pci, sound/usb, sound/soc) ─► ALSA CORE
NETWORK (drivers/net/ethernet/, wireless/) ─► NET CORE

Each driver depends on:
  PCI CORE ─► DMA API ─► IOMMU/MM
  MMIO access (ioremap, readl/writel)
  IRQ (request_irq, free_irq)
  DMA (dma_map_single, dma_unmap_single)
  Kernel services (printk, slab, workqueue, timer)
```

### 1.7 Standalone Subsystems

```
SECURITY (security/)
  ─► kernel/ (LSM hooks)
  ─► fs/ (inode/permission xattrs)   ISOLABLE

CRYPTO (crypto/)
  ─► MM (alloc, sg)
  ─► arch/*/crypto/ (accelerators)   HYBRID

POWER MANAGEMENT (kernel/power/)
  ─► drivers/cpufreq/
  ─► drivers/cpuidle/                HYBRID

TRACING (kernel/trace/)
  ─► Almost everything (hooks)
  ─► kernel/events/                  CORE

VIRTUALIZATION (virt/kvm/)
  ─► arch/*/kvm/
  ─► mm/                            CORE (in Ring -1/0)
```

## 2. Module Dependency Matrix

| Subsystem | Lines of Code | Dependencies | User-Space Potential | Isolation Feasibility |
|-----------|--------------|--------------|---------------------|----------------------|
| kernel/   | ~250K        | arch, mm     | None (must stay)    | N/A (Ring 0 core)    |
| mm/       | ~140K        | arch         | None (must stay)    | N/A (Ring 0 core)    |
| drivers/  | ~12M         | kernel, mm, dma, irq | HIGH | HIGH (DAC sandbox) |
| fs/       | ~850K        | mm, block, crypto | MEDIUM | MEDIUM |
| net/      | ~550K        | mm, crypto   | MEDIUM | MEDIUM |
| sound/    | ~400K        | drivers, mm  | HIGH | HIGH |
| block/    | ~120K        | mm, drivers  | MEDIUM | MEDIUM |
| ipc/      | ~15K         | mm, fs       | N/A | LOW |
| security/ | ~60K         | fs, kernel   | MEDIUM | MEDIUM |
| crypto/   | ~90K         | mm, arch     | HIGH | HIGH |

## 3. Critical Dependency Paths (Cycle Analysis)

### 3.1 No cycles allowed — ordering is strict:

```
arch ─► kernel ─► mm ─► drivers ─► fs ─► net
  │       │        │        │          │      │
  └───────┴────────┴────────┴──────────┴──────┘
                  (nothing depends upward)
```

### 3.2 Exception: Key cycle mitigation

```
drivers/pci/ ←→ kernel/dma/ (both need each other)
  Solution: DMA API becomes pure function table (no callbacks into PCI)

fs/ ←→ mm/ (page reclaim calls into shrinkers in fs)
  Solution: Shrinker API becomes flat callback list, not bidirectional
```

## 4. Lock Contention & Race Analysis

### 4.1 Known Heavy Locks (contention bottlenecks)

```
1. mmap_lock (mm_struct) — every page fault, mmap, munmap
2. dcache_lock (fs/dcache.c) — every path lookup
3. inode_hash_lock — every inode creation/deletion
4. zone->lock (page allocator) — every page alloc/free
5. qdisc lock (net/sched) — every packet enqueue/dequeue
6. tasklist_lock — every process listing
7. files_lock — every fd open/close
8. sighand->siglock — every signal delivery
9. page_table_lock — every page table walk
```

### 4.2 Race Conditions (historic + class)

```
1. MMap vs. truncate: page mapped while file truncated → SIGBUS
2. write vs. close: fd closed during concurrent write → use-after-free
3. RCU callback vs. module unload: callback fires after module removed
4. Timer softirq vs. driver remove: timer fires during/after pci_unregister
5. OOM killer vs. memory allocator: lock ordering violation
```

## 5. Attack Surface (Entry Points from User Space)

```
1. syscalls (~450 entry points)
2. ioctl on /dev/ files (~thousands of driver-specific ioctls)
3. netlink (socket(AF_NETLINK)) — routing, firewall, auditing
4. /sys/ and /proc/ filesystem interfaces
5. BPF program loading
6. Kernel module loading
7. ptrace
8. perf_event_open
```

## 6. Architecture Isolation Plan

```
┌─────────────────────────────────────────────────────────┐
│                    Ring -1 (Hypervisor)                  │
│  SENTRAOS ORCHESTRATOR — monitors all, crash recovery   │
├─────────────────────────────────────────────────────────┤
│                    Ring 0 (Core Kernel)                  │
│  Scheduler | MM | IRQ | Time | Locking | IPC (core)     │
│  VFS vnode layer | NET skbuff/core | Block core         │
│  DMA API | PCI core (config only)                       │
├─────────────────────────────────────────────────────────┤
│                 Ring 0 Isolated Sandboxes                 │
│  (DAC containers — separate pagetables, no direct MMIO) │
│  Driver A  │  Driver B  │  Driver C  │  ...              │
├─────────────────────────────────────────────────────────┤
│                    Ring 3 (User Space)                   │
│  System daemons │ FS deamons (ext4d) │ Net daemons       │
│  FUSE │ WireGuard │ User drivers (UIO/VFIO)              │
└─────────────────────────────────────────────────────────┘
```
