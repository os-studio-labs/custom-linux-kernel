// SPDX-License-Identifier: GPL-2.0

//! AI manager daemon — entry point.
//!
//! Usage: ai-mgr [--foreground]

mod ai_mgr;

use std::env;

fn main() {
    eprintln!("ai-mgr: AI Manager Daemon v0.1");

    let args: Vec<String> = env::args().collect();
    let foreground = args.len() > 1 && args[1] == "--foreground";

    if !foreground {
        // Daemonize by forking
        // SAFETY: fork() is safe in single-threaded context before daemon starts.
        let pid = unsafe { libc::fork() };
        match pid {
            0 => { /* child continues */ }
            n if n > 0 => {
                eprintln!("ai-mgr: daemonized (pid {})", std::process::id());
                std::process::exit(0);
            }
            _ => {
                eprintln!("ai-mgr: fork failed");
                std::process::exit(1);
            }
        }
    }

    let mut manager = ai_mgr::AiManager::new();

    ctrlc::set_handler(move || {
        eprintln!("\nai-mgr: shutting down");
        std::process::exit(0);
    })
    .expect("ai-mgr: failed to set Ctrl-C handler");

    if let Err(e) = manager.run() {
        eprintln!("ai-mgr: fatal error: {}", e);
        std::process::exit(1);
    }
}
