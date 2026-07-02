// SPDX-License-Identifier: GPL-2.0

//! AI manager daemon — main loop and orchestration.
//!
//! The daemon opens `/dev/ai-control`, classifies running
//! processes, sends ioctls to register them with the kernel,
//! monitors resource use, and manages the lifecycle of local
//! and cloud AI models.

use std::collections::HashMap;
use std::fs;
use std::io;
use std::os::fd::{IntoRawFd, RawFd};
use std::path::Path;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::Arc;
use std::time::Duration;

// ── IOCTL helpers matching include/uapi/linux/ai.h ────────────

/// Build an ioctl request number:  _IOWR(type, nr, size) / _IOW / _IOR / _IO
const fn ioctl_cmd(dir: u32, typ: u8, nr: u8, size: u32) -> u64 {
    ((dir as u64) << 30) | ((size as u64) << 16) | ((typ as u64) << 8) | (nr as u64)
}

const AI_IOCTL_CLASSIFY: u64       = ioctl_cmd(3, b'A', 1, 16);  // _IOWR, 4 x i32 -> 16
const AI_IOCTL_SCHED_PRIORITY: u64 = ioctl_cmd(1, b'A', 3, 12); // _IOW, i32+i32+u32 -> 12
const AI_IOCTL_GET_STATS: u64      = ioctl_cmd(2, b'A', 6, 40); // _IOR, 2 u64+2 u32+4 u32 -> 40
const AI_IOCTL_PING: u64           = ioctl_cmd(0, b'A', 7, 0);  // _IO

#[repr(C)]
struct ai_classify_param {
    pid: i32,
    workload_type: u32,
    priority: u32,
    flags: u32,
}

#[repr(C)]
struct ai_sched_param {
    pid: i32,
    nice_offset: i32,
    sched_flags: u32,
}

#[repr(C)]
struct ai_stats {
    local_inferences: u64,
    cloud_inferences: u64,
    total_memory_used: u64,
    active_models: u32,
    active_processes: u32,
    reserved: [u32; 4],
}

/// The IOCTL device node.
const AI_DEVICE: &str = "/dev/ai-control";

/// Interval between monitoring ticks.
const MONITOR_INTERVAL: Duration = Duration::from_secs(5);

/// A classified AI process.
#[derive(Debug, Clone)]
struct AiProcess {
    pid: u32,
    name: String,
    workload_type: u32, // 0=unknown, 1=inference, 2=training, 3=embedding
    memory_bytes: u64,
    is_local: bool,
}

/// The AI manager daemon.
pub struct AiManager {
    running: Arc<AtomicBool>,
    processes: HashMap<u32, AiProcess>,
    fd: Option<RawFd>,
}

impl AiManager {
    pub fn new() -> Self {
        let fd = fs::OpenOptions::new()
            .read(true)
            .write(true)
            .open(AI_DEVICE)
            .ok()
            .map(|f| f.into_raw_fd());

        if fd.is_some() {
            eprintln!("ai-mgr: connected to {}", AI_DEVICE);
        } else {
            eprintln!("ai-mgr: WARNING could not open {}: {}", AI_DEVICE,
                      io::Error::last_os_error());
            eprintln!("ai-mgr: running in degraded mode (no kernel interaction)");
        }

        Self {
            running: Arc::new(AtomicBool::new(true)),
            processes: HashMap::new(),
            fd,
        }
    }

    /// Run the main daemon loop.
    pub fn run(&mut self) -> io::Result<()> {
        // Test kernel connection with a ping
        self.ioctl_ping();

        eprintln!("ai-mgr: starting monitoring loop");

        while self.running.load(Ordering::Relaxed) {
            self.detect_processes();
            self.report_stats();
            std::thread::sleep(MONITOR_INTERVAL);
        }

        Ok(())
    }

    // ── Kernel IOCTL helpers ─────────────────────────────────

    fn ioctl_classify(&self, pid: u32, workload_type: u32, priority: u32) {
        let Some(fd) = self.fd else { return };
        let mut param = ai_classify_param {
            pid: pid as i32,
            workload_type,
            priority,
            flags: 0,
        };
        unsafe {
            libc::ioctl(fd, AI_IOCTL_CLASSIFY as _, &mut param as *mut _ as *mut libc::c_void);
        }
    }

    fn ioctl_set_priority(&self, pid: u32, nice_offset: i32) {
        let Some(fd) = self.fd else { return };
        let param = ai_sched_param {
            pid: pid as i32,
            nice_offset,
            sched_flags: 0,
        };
        unsafe {
            libc::ioctl(fd, AI_IOCTL_SCHED_PRIORITY as _, &param as *const _ as *const libc::c_void);
        }
    }

    #[allow(dead_code)]
    fn ioctl_get_stats(&self) -> Option<ai_stats> {
        let Some(fd) = self.fd else { return None };
        let mut stats = ai_stats {
            local_inferences: 0,
            cloud_inferences: 0,
            total_memory_used: 0,
            active_models: 0,
            active_processes: 0,
            reserved: [0; 4],
        };
        let ret = unsafe {
            libc::ioctl(fd, AI_IOCTL_GET_STATS as _, &mut stats as *mut _ as *mut libc::c_void)
        };
        if ret == 0 { Some(stats) } else { None }
    }

    fn ioctl_ping(&self) {
        let Some(fd) = self.fd else { return };
        unsafe {
            libc::ioctl(fd, AI_IOCTL_PING as _);
        }
    }

    /// Stop the daemon.
    pub fn shutdown(&self) {
        self.running.store(false, Ordering::Relaxed);
    }

    /// Scan /proc for known AI workloads.
    fn detect_processes(&mut self) {
        if let Ok(entries) = fs::read_dir("/proc") {
            for entry in entries.flatten() {
                let pid_str = entry.file_name();
                let pid: u32 = match pid_str.to_str().and_then(|s| s.parse().ok()) {
                    Some(p) => p,
                    None => continue,
                };

                let comm_path = Path::new("/proc").join(&pid_str).join("comm");
                let name = match fs::read_to_string(&comm_path) {
                    Ok(n) => n.trim().to_string(),
                    Err(_) => continue,
                };

                let wtype = self.classify_process(&name);
                if wtype == 0 {
                    continue;
                }

                let is_local = self.is_local_tool(&name);

                let mem = self
                    .get_process_memory(pid)
                    .unwrap_or(0);

                let proc = AiProcess {
                    pid,
                    name: name.clone(),
                    workload_type: wtype,
                    memory_bytes: mem,
                    is_local,
                };

                // Notify the kernel about this AI process
                self.ioctl_classify(pid, wtype, if is_local { 7 } else { 4 });

                self.processes.insert(pid, proc);
            }
        }
    }

    /// Classify a process name into a workload type.
    fn classify_process(&self, name: &str) -> u32 {
        match name {
            n if n.contains("ollama") => 1,    // inference
            n if n.contains("opencode") => 1,  // inference
            n if n.contains("python") => 2,    // training
            n if n.contains("llama") => 1,     // inference
            n if n.contains("transformers") => 2,
            n if n.contains("whisper") => 1,
            _ => 0,
        }
    }

    /// Check if the process is a local AI tool.
    fn is_local_tool(&self, name: &str) -> bool {
        matches!(
            name,
            "ollama" | "ollama_llama_server" | "opencode" | "llama" | "llama-server"
        )
    }

    /// Read RSS from /proc/<pid>/status.
    fn get_process_memory(&self, pid: u32) -> Option<u64> {
        let status_path = format!("/proc/{}/status", pid);
        let content = fs::read_to_string(&status_path).ok()?;
        for line in content.lines() {
            if line.starts_with("VmRSS:") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                if parts.len() >= 2 {
                    let kb: u64 = parts[1].parse().ok()?;
                    return Some(kb * 1024);
                }
            }
        }
        None
    }

    /// Print current statistics to stderr.
    fn report_stats(&self) {
        let local_count = self.processes.values().filter(|p| p.is_local).count();
        let cloud_count = self.processes.values().filter(|p| !p.is_local).count();
        let total_mem: u64 = self.processes.values().map(|p| p.memory_bytes).sum();

        eprintln!(
            "ai-mgr: {} local + {} cloud processes, {} MB AI memory",
            local_count,
            cloud_count,
            total_mem / (1024 * 1024)
        );
    }

    /// Return a reference to tracked processes (for tool integrations).
    pub fn processes(&self) -> &HashMap<u32, AiProcess> {
        &self.processes
    }
}
