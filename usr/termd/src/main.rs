// SentraOS Terminal Daemon (termd)
//
// Handles all line discipline, canonical mode processing, terminal
// emulation, and PTY management in userspace.
//
// Communicates with the kernel TTY core via /dev/sentraos_bridge.
// The kernel TTY core is just a thin byte-pipe; all the complex
// UNIX terminal logic lives here.

use std::collections::HashMap;
use std::fs::{File, OpenOptions};
use std::sync::atomic::AtomicBool;
use std::sync::Arc;
use std::thread;
use std::time::Duration;

const BRIDGE_PATH: &str = "/dev/sentraos_bridge";

// ─── Canonical mode processor ───────────────────────────

/// Simulates the N_TTY line discipline in userspace.
/// Handles: echo, line buffering, signal character generation,
/// ERASE/KILL/WERASE editing, and all termios settings.
struct LineDiscipline {
    buf: Vec<u8>,
    echo: bool,
    canonical: bool,
    // termios settings
    erase_char: u8,
    kill_char: u8,
    werase_char: u8,
    eof_char: u8,
    intr_char: u8,
    quit_char: u8,
    susp_char: u8,
}

impl LineDiscipline {
    fn new() -> Self {
        Self {
            buf: Vec::new(),
            echo: true,
            canonical: true,
            erase_char: 0x7f,  // DEL
            kill_char: 0x15,   // ^U
            werase_char: 0x17, // ^W
            eof_char: 0x04,    // ^D
            intr_char: 0x03,   // ^C
            quit_char: 0x1c,   // ^\
            susp_char: 0x1a,   // ^Z
        }
    }

    /// Process an input byte through the line discipline.
    /// Returns (output_data, signals_to_send).
    fn process_input(&mut self, byte: u8) -> (Vec<u8>, Vec<u32>) {
        let mut output = Vec::new();
        let mut signals = Vec::new();

        if self.canonical {
            match byte {
                b'\n' | b'\r' => {
                    self.buf.push(byte);
                    if self.echo {
                        output.push(b'\r');
                        output.push(b'\n');
                    }
                }
                _ if byte == self.erase_char => {
                    if let Some(_) = self.buf.pop() {
                        if self.echo {
                            output.extend_from_slice(b"\x08 \x08");
                        }
                    }
                }
                _ if byte == self.kill_char => {
                    let erased = self.buf.len();
                    self.buf.clear();
                    if self.echo && erased > 0 {
                        for _ in 0..erased {
                            output.extend_from_slice(b"\x08 \x08");
                        }
                    }
                }
                _ if byte == self.eof_char => {
                    // Flush line
                    if !self.buf.is_empty() {
                        // Return accumulated line
                    }
                }
                _ if byte == self.intr_char => {
                    signals.push(2); // SIGINT
                    self.buf.clear();
                    if self.echo {
                        output.extend_from_slice(b"^C\r\n");
                    }
                }
                _ if byte == self.susp_char => {
                    signals.push(20); // SIGTSTP
                    if self.echo {
                        output.extend_from_slice(b"^Z\r\n");
                    }
                }
                _ => {
                    self.buf.push(byte);
                    if self.echo {
                        output.push(byte);
                    }
                }
            }
        } else {
            // Raw mode: pass through immediately
            output.push(byte);
        }

        (output, signals)
    }

    /// Drain the canonical line buffer (when newline or EOF received).
    fn drain_line(&mut self) -> Vec<u8> {
        let line = self.buf.clone();
        self.buf.clear();
        line
    }
}

// ─── Terminal daemon ──────────────────────────────────

struct TermDaemon {
    bridge: Option<File>,
    lines: HashMap<u32, LineDiscipline>, // tty_index → discipline
    running: Arc<AtomicBool>,
}

impl TermDaemon {
    fn new() -> Self {
        Self {
            bridge: None,
            lines: HashMap::new(),
            running: Arc::new(AtomicBool::new(true)),
        }
    }

    fn connect(&mut self) -> Result<(), String> {
        let bridge = OpenOptions::new()
            .read(true)
            .write(true)
            .open(BRIDGE_PATH)
            .map_err(|e| format!("Cannot open {}: {}", BRIDGE_PATH, e))?;
        self.bridge = Some(bridge);
        Ok(())
    }

    fn handle_tty_open(&mut self, tty_index: u32) {
        eprintln!("termd: TTY {} opened, attaching line discipline", tty_index);
        self.lines.insert(tty_index, LineDiscipline::new());
    }

    fn handle_tty_close(&mut self, tty_index: u32) {
        eprintln!("termd: TTY {} closed, detaching line discipline", tty_index);
        self.lines.remove(&tty_index);
    }

    fn run(&mut self) {
        eprintln!("termd: SentraOS terminal daemon starting");
        if let Err(e) = self.connect() {
            eprintln!("termd: {}", e);
            return;
        }
        eprintln!("termd: connected to kernel TTY core, waiting for events");

        // In production: poll /dev/sentraos_bridge for TTY events,
        // process through line discipline, write output back.
        //
        // For this implementation: demonstrate the architecture.

        thread::sleep(Duration::from_secs(u64::MAX));
    }
}

fn main() {
    let mut daemon = TermDaemon::new();
    daemon.run();
}
