// SPDX-License-Identifier: GPL-2.0

//! Ollama integration helpers.
//!
//! Detects running Ollama instances, queries model metadata,
//! and hints the kernel to apply optimisation policies.

use std::collections::HashMap;
use std::fs;
use std::path::Path;

/// Check if an Ollama server process is running.
pub fn detect_ollama() -> Option<u32> {
    if let Ok(entries) = fs::read_dir("/proc") {
        for entry in entries.flatten() {
            let pid_str = entry.file_name();
            let pid: u32 = pid_str.to_str()?.parse().ok()?;

            let comm_path = Path::new("/proc").join(&pid_str).join("comm");
            let cmdline_path = Path::new("/proc").join(&pid_str).join("cmdline");

            if let Ok(comm) = fs::read_to_string(&comm_path) {
                let comm = comm.trim();
                if comm == "ollama" || comm == "ollama_llama_server" {
                    return Some(pid);
                }
            }

            // Also check cmdline for "ollama" (in case comm is truncated)
            if let Ok(cmdline) = fs::read_to_string(&cmdline_path) {
                if cmdline.contains("ollama") {
                    return Some(pid);
                }
            }
        }
    }
    None
}

/// Get the list of loaded models from an Ollama API endpoint.
/// Assumes ollama serve is running on localhost:11434.
#[cfg(feature = "ollama")]
pub fn list_models() -> Result<Vec<String>, String> {
    let url = "http://localhost:11434/api/tags";
    let resp = reqwest::blocking::get(url).map_err(|e| format!("HTTP error: {}", e))?;
    let json: serde_json::Value =
        serde_json::from_slice(&resp.bytes().map_err(|e| format!("read error: {}", e))?)
            .map_err(|e| format!("JSON error: {}", e))?;

    let mut models = Vec::new();
    if let Some(models_arr) = json["models"].as_array() {
        for m in models_arr {
            if let Some(name) = m["name"].as_str() {
                models.push(name.to_string());
            }
        }
    }
    Ok(models)
}

/// Return memory usage for ollama processes.
pub fn ollama_memory_usage() -> HashMap<u32, u64> {
    let mut result = HashMap::new();
    if let Ok(entries) = fs::read_dir("/proc") {
        for entry in entries.flatten() {
            let pid_str = entry.file_name();
            let pid: u32 = match pid_str.to_str().and_then(|s| s.parse().ok()) {
                Some(p) => p,
                None => continue,
            };

            let comm_path = Path::new("/proc").join(&pid_str).join("comm");
            let comm = match fs::read_to_string(&comm_path) {
                Ok(c) => c.trim().to_string(),
                Err(_) => continue,
            };

            if comm == "ollama" || comm == "ollama_llama_server" {
                if let Ok(status) = fs::read_to_string(Path::new("/proc").join(&pid_str).join("status"))
                {
                    for line in status.lines() {
                        if line.starts_with("VmRSS:") {
                            if let Some(kb_str) = line.split_whitespace().nth(1) {
                                if let Ok(kb) = kb_str.parse::<u64>() {
                                    result.insert(pid, kb * 1024);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    result
}
