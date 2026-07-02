#!/bin/sh
# SPDX-License-Identifier: GPL-2.0
#
# AI subsystem initialisation script.
# Called at boot to load the AI kernel module and start the
# AI manager daemon.

AI_MODULE="ai_subsystem"
AI_DEVICE="/dev/ai-control"
AI_MGR="/usr/sbin/ai-mgr"

echo "AI: initialising subsystem"

# 1. Load the kernel module (built-in or modprobe)
if [ -d /sys/module/"$AI_MODULE" ]; then
    echo "AI: kernel module already loaded (built-in)"
elif modprobe "$AI_MODULE" 2>/dev/null; then
    echo "AI: kernel module loaded"
else
    echo "AI: WARNING could not load kernel module" >&2
fi

# 2. Create device node if it doesn't exist
if [ ! -c "$AI_DEVICE" ]; then
    mknod "$AI_DEVICE" c 10 127 2>/dev/null || true
fi

# 3. Mount sysfs AI interface (if not already)
if [ -d /sys/kernel/ai ]; then
    echo "AI: sysfs interface at /sys/kernel/ai/"
fi

# 4. Start the AI manager daemon
if [ -x "$AI_MGR" ]; then
    echo "AI: starting ai-mgr daemon"
    "$AI_MGR" --foreground &
    echo "$!" > /var/run/ai-mgr.pid
    echo "AI: ai-mgr started (pid $!)"
else
    echo "AI: ai-mgr not found, install with 'make ai-mgr'"
fi

echo "AI: subsystem initialisation complete"
