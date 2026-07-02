.. SPDX-License-Identifier: GPL-2.0

=================================
AI Subsystem — Kernel AI Management
=================================

Overview
========
The AI subsystem (``CONFIG_AI_SUBSYSTEM``) provides a kernel-level layer for
managing, monitoring, and accelerating AI workloads. It bridges userspace AI
tools (ollama, opencode) and cloud endpoints with kernel resource management.

Architecture
============
::

  ┌──────────────────────────────────────────────────────┐
  │                  Userspace                            │
  │  ┌──────────┐  ┌──────────┐  ┌────────────────────┐  │
  │  │  ollama  │  │ opencode │  │   ai-mgr daemon    │  │
  │  └────┬─────┘  └────┬─────┘  └─────────┬──────────┘  │
  │       │             │                  │              │
  └───────┼─────────────┼──────────────────┼──────────────┘
          │             │                  │
  ┌───────┼─────────────┼──────────────────┼──────────────┐
  │       │             │     ioctl/sysfs  │   Kernel     │
  │  ┌────▼─────────────▼──────────────────▼──────────┐   │
  │  │           AI Subsystem Module                   │   │
  │  │  ┌──────────┐ ┌───────────┐ ┌──────────────┐   │   │
  │  │  │Scheduler │ │Memory Mgr │ │  Monitor     │   │   │
  │  │  │ (nice/   │ │ (hugepag, │ │ (tracking,   │   │   │
  │  │  │  priority)│ │  mlock)  │ │  stats)      │   │   │
  │  │  └──────────┘ └───────────┘ └──────────────┘   │   │
  │  │  ┌──────────┐ ┌───────────┐                    │   │
  │  │  │  Model   │ │  Cloud    │                    │   │
  │  │  │ Registry │ │ Endpoints │                    │   │
  │  │  └──────────┘ └───────────┘                    │   │
  │  └────────────────────────────────────────────────┘   │
  └──────────────────────────────────────────────────────┘

Components
==========

Kernel Module (ai_subsystem)
----------------------------
- ``src/lib.rs`` — module entry point, wires sub-components
- ``src/core/scheduler.rs`` — AI-aware nice value adjustment
- ``src/core/memory.rs`` — huge-page, mlock, and compression hints
- ``src/core/monitor.rs`` — process lifecycle tracking
- ``src/models/mod.rs`` — model registry (local + cloud)
- ``src/models/local.rs`` — local model management
- ``src/models/cloud.rs`` — cloud endpoint registry
- ``src/ioctl.rs`` — ``/dev/ai-control`` ioctl dispatch
- ``src/sysfs.rs`` — ``/sys/kernel/ai/`` interface
- ``src/helpers.c`` — C wrappers for kernel APIs (madvise, mlock, set_user_nice)

Userspace Daemon (ai-mgr)
--------------------------
- ``daemon/src/main.rs`` — daemon entry point, forking
- ``daemon/src/ai_mgr.rs`` — process scanning, classification, stats
- ``daemon/src/tools/ollama.rs`` — Ollama detection and memory tracking
- ``daemon/src/tools/opencode.rs`` — Opencode detection and inference heuristics

Configuration
=============
The subsystem is enabled via ``CONFIG_AI_SUBSYSTEM`` (depends on ``RUST``).
Sub-features:

- ``CONFIG_AI_DEBUG`` — verbose debug output
- ``CONFIG_AI_MEMORY_PRIORITY`` — memory allocation priority for AI
- ``CONFIG_AI_LOCAL_PRIORITY`` — boost local model scheduling
- ``CONFIG_AI_CLOUD_ROUTING`` — cloud endpoint support
- ``CONFIG_AI_MANAGER_DAEMON`` — build the userspace ai-mgr
- ``CONFIG_AI_OLLAMA_INTEGRATION`` — Ollama-specific optimisations
- ``CONFIG_AI_OPENCODE_INTEGRATION`` — Opencode-specific optimisations
- ``CONFIG_AI_SYSFS`` — ``/sys/kernel/ai/`` interface

Sysfs Interface
===============
``/sys/kernel/ai/`` provides runtime control:

- ``stats`` — read subsystem statistics
- ``classify`` — write ``<pid>`` to classify a process as AI workload
- ``priority`` — write ``<pid> <priority>`` to set AI priority (0–7)

IOCTL Interface
===============
The daemon communicates with the kernel module via ``/dev/ai-control``:

.. code-block:: c

  #include <linux/ai.h>

  struct ai_classify_param param = { .pid = 1234, .workload_type = 1 };
  ioctl(fd, AI_IOCTL_CLASSIFY, &param);

See ``include/uapi/linux/ai.h`` for full definitions.

Building
========
The kernel module is built as part of the kernel tree:

.. code-block:: sh

  make menuconfig  # enable CONFIG_AI_SUBSYSTEM
  make             # builds ai_subsystem.ko

The userspace daemon is built separately:

.. code-block:: sh

  cd usr/ai/daemon
  cargo build --release

Initialisation
==============
At boot, the AI subsystem can be initialised via the provided script:

.. code-block:: sh

  /usr/ai/scripts/ai-init.sh

This loads the kernel module, creates the device node, and starts
the ai-mgr daemon.
