# SentraOS Kernel

The SentraOS Kernel is a Linux-based kernel designed for the SentraOS
educational operating system project. It extends and modernizes the Linux
kernel with a focus on stability, security, and future-ready architecture.

This kernel introduces significant internal changes, including partial
rewrites of core subsystems in Rust, improved driver management, and a
transition toward a hybrid kernel model.

The goal of the SentraOS Kernel is to provide a robust foundation for
developers, students, and daily users while laying groundwork for a
microkernel-inspired architecture within the Linux ecosystem.

--

Curruntly, the kernel has not been tested and build fails midway. Error resolving underway
--
## Quick Start

* Get the source: <https://github.com/os-studio-labs/custom-linux-kernel>
* Build the kernel: standard linux kernel build command
* Report issues: CREATE AN ISSUE AND IMMEDIATLY REPORT IT TO A CONTRIBUTOR
* Contribute: See "Contribution Guidelines" below

## Key Features

* Modernized core subsystems with Rust integration
* Enhanced memory management for improved stability
* Updated and maintained legacy drivers
* Driver sandboxing and extended APIs
* Removal of obsolete and unused drivers
* Support for local AI subsystems (/usr/ai)
* Improved compatibility with IDE agents and agentic AI systems
* Secure OTA kernel update framework
* Improved watchdog handling and kernel panic management
* Migration of non-critical components to userspace
* Improved daemon and service management
* Hybrid kernel architecture foundation

## Architecture Overview

The SentraOS Kernel is based on the Linux monolithic kernel but introduces
structural changes aimed at evolving toward a hybrid architecture.

Key architectural directions include:

* Partial subsystem isolation
* Movement of non-essential components to userspace
* Enhanced modularity for future microkernel transition
* Integration of modern languages (Rust) for safety-critical components

This approach allows incremental innovation while maintaining compatibility
with existing Linux infrastructure.

## Current Development Changes

The following major changes have been implemented:

* Rewriting of critical kernel components such as the memory manager using Rust
* Investigation, updating, and maintenance of previously unmaintained drivers
* Introduction of driver sandboxing mechanisms
* Expansion of kernel APIs for improved extensibility
* Removal of irrelevant or deprecated drivers
* Addition of /usr/ai subsystem for local AI support
* Support for IDE-integrated and agentic AI workflows
* Implementation of a secure OTA update mechanism
* Improvements to kernel stability and debugging systems
* Migration of non-critical systems to userspace daemons
* Ongoing transition toward a hybrid kernel model

# Who Are You?

Find your role below:

* New Developer - Exploring kernel development and systems programming
* Student - Learning OS internals and kernel architecture
* Researcher - Studying hybrid and microkernel transitions
* Security Engineer - Auditing and hardening kernel components
* Driver Developer - Maintaining and building hardware support
* Maintainer - Reviewing and managing contributions
* AI Coding Assistant - Assisting with kernel development using AI tools

# Contribution Guidelines

## Individuals

Individuals may contribute by submitting pull requests. Before merging:

* Submit your changes via pull request
* Contact the maintainers using the provided email
* Provide a detailed explanation of your changes
* Wait for approval before merging

Direct commits without approval are discouraged.

## Institutions and Organizations

* Submit proposed changes through the official contact email
* Wait for confirmation before submitting a pull request
* After approval, proceed with contribution submission

## AI Agents and AI-Assisted Contributions

AI-assisted development is encouraged.

However, contributors must:

* Contact maintainers before submitting changes
* Provide both human-written and AI-generated summaries
* Ensure full transparency of AI usage

For every AI-generated file or modification, append the following at the
end of the file:

// created by AI AGENT (<provider>, <GitHub username>)

## Others

For all other contribution types, contact the maintainers directly.

# Submission Format

All contributions must include:

* A detailed introduction of the contributor
  (experience, GitHub profile, tools used, AI usage)

* A complete explanation of all changes made
  (purpose, implementation details, problems addressed)

* Build logs and test results

* A justification for why the changes should be accepted

* Modified files and full source code (via cloud/drive link)

* Documentation including:

  * Change summaries
  * Submodule updates
  * AI-generated and human-written reports

# Important Notes

* All modified files must include:

  * GitHub username
  * Date of modification
  * AI usage disclosure (if applicable)

* Follow kernel-style contribution discipline

* Ensure stability and compatibility are not compromised

# Communication and Support

* Email: <error40404.github@gmail.com>
* Issue Tracker: SEE ISSUES
* Documentation: EXPLORE SOURCE CODE
