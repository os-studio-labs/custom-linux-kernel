// SPDX-License-Identifier: GPL-2.0

//! Opencode integration helpers.
//!
//! Detects running opencode processes, monitors resource
//! usage, and coordinates with the kernel AI subsystem for
//! priority scheduling.

use std::fs;
use std::path::Path;

/// Detect a running opencode process.
pub fn detect_opencode() -> Option<u32> {
    if let Ok(entries) = fs::read_dir("/proc") {
        for entry in entries.flatten() {
            let pid_str = entry.file_name();
            let pid: u32 = pid_str.to_str()?.parse().ok()?;

            let comm_path = Path::new("/proc").join(&pid_str).join("comm");
            if let Ok(comm) = fs::read_to_string(&comm_path) {
                if comm.trim() == "opencode" {
                    return Some(pid);
                }
            }

            let cmdline_path = Path::new("/proc").join(&pid_str).join("cmdline");
            if let Ok(cmdline) = fs::read_to_string(&cmdline_path) {
                if cmdline.contains("opencode") {
                    return Some(pid);
                }
            }
        }
    }
    None
}

/// Get the memory usage of an opencode process.
pub fn opencode_memory(pid: u32) -> Option<u64> {
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

/// Check whether opencode is currently doing inference (heuristic:
/// high CPU usage in recent samples).
pub fn is_inferring(pid: u32) -> bool {
    let stat_path = format!("/proc/{}/stat", pid);
    let content = match fs::read_to_string(&stat_path) {
        Ok(c) => c,
        Err(_) => return false,
    };

    // Field 14 (0-indexed: 13) is utime, field 15 is stime
    let fields: Vec<&str> = content.split_whitespace().collect();
    if fields.len() < 17 {
        return false;
    }

    let utime: u64 = fields[13].parse().unwrap_or(0);
    let stime: u64 = fields[14].parse().unwrap_or(0);
    let total = utime + stime;

    total > 100
}
