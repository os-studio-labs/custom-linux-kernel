# Contributing to SentraOS Kernel

Thank you for your interest in contributing to the SentraOS Kernel project.

This project follows a structured and review-driven development model to ensure
high standards of stability, security, and maintainability. All contributions
must adhere to the guidelines outlined in this document.

---

## 1. Contribution Principles

All contributions must:

- Be clearly justified and well-documented
- Maintain or improve system stability and security
- Align with the architectural direction of the project
- Undergo review prior to merging

Direct, unreviewed commits to protected branches are not permitted.

---

## 2. Contribution Workflow

All contributors are required to follow the standard workflow:

1. Fork the repository
2. Create a new branch using one of the following formats:

   - `feature/<name>`
   - `fix/<name>`
   - `subsystem/<name>`

3. Implement changes
4. Commit with clear and descriptive messages
5. Submit a Pull Request (PR)
6. Await review and approval from maintainers

---

## 3. Pull Request Requirements

Each Pull Request must include the following:

### 3.1 Description
- Summary of changes
- Purpose and motivation
- Affected subsystems or components

### 3.2 Technical Details
- Implementation approach
- Files modified
- Dependencies or side effects

### 3.3 Validation
- Build logs
- Test results (if applicable)
- Known limitations or issues

### 3.4 Justification
A clear explanation of why the contribution should be accepted.

---

## 4. Build and Testing Requirements

Before submission, contributors must:

- Attempt to build the kernel (or clearly document build failures)
- Provide complete build logs, for example:
make bzImage 2>&1 | tee build.log

- Specify:
- Toolchain used
- Target architecture
- Build environment

---

## 5. Code Standards

All contributions must follow these standards:

- Maintain readability and modularity
- Avoid unnecessary complexity
- Follow Linux kernel coding conventions where applicable

### Required Metadata in Modified Files

Each modified file must include:

- Contributor GitHub username
- Date of modification
- AI usage disclosure (if applicable)

---

## 6. AI-Assisted Contributions

AI-assisted development is permitted under the following conditions:

- Full disclosure of AI usage is required
- Contributors must understand and validate all generated code
- Contributors are fully responsible for correctness and safety

### Required Annotation

All AI-generated files or modifications must include the following footer:

```c
// created by AI AGENT (<provider>, <GitHub username>)

Pull Request Requirements

Each PR involving AI must include:

AI-generated summary
Human-written explanation
7. Contributor Roles
Contributor
Submits pull requests
Proposes changes and improvements
Reviewer
Reviews pull requests
Suggests modifications and improvements
Maintainer
Reviews and approves contributions
Has final authority over merging decisions
Ensures alignment with project goals
8. High-Risk Changes

The following areas are considered high-risk and require additional scrutiny:

Memory management
Scheduler modifications
Security subsystems
Core driver infrastructure

Such contributions may:

Require extended review cycles
Be subject to multiple revisions
Be rejected if stability cannot be ensured
9. Communication Guidelines
Use GitHub Issues for bug reports and discussions
Maintain clear, concise, and technical communication
Avoid low-effort or non-constructive submissions
10. Rejection Criteria

Contributions may be rejected if they:

Lack proper documentation or explanation
Do not include build or validation evidence
Contain undisclosed AI-generated code
Introduce instability without sufficient justification
Do not align with project architecture or goals
11. Project Status Notice

The SentraOS Kernel is currently under active development and may not be fully stable.

Contributors are expected to:

Exercise caution when modifying core subsystems
Prioritize correctness over feature expansion
Respect the evolving architecture
12. Contact and Support
Email: error40404.github@gmail.com
Issue Tracker: GitHub Issues
13. Legal and Attribution Notice

This repository includes components derived from the Linux kernel.

All contributions must comply with applicable open-source licenses and
must not violate licensing terms.
