# XVROS firmware target

This directory reserves the firmware engineering area.

## Requested output

The long-term target is a genuine, validated XVROS FIRM-format boot payload (sometimes informally referred to as a `firm.bin`). It is **not available yet**.

A valid Nintendo 3DS FIRM image is not an ordinary application binary. It has a specific container/header and section layout, platform-specific execution requirements and boot-chain constraints. Renaming an ELF, `.3dsx` or arbitrary binary to `.firm` would not make it bootable and could cause a failed boot if installed.

## Development order

1. Build and test XVROS as a normal `.3dsx` homebrew shell.
2. Define the supported hardware and boot environment.
3. Design and review the FIRM container and entry-point requirements.
4. Implement a minimal non-destructive boot test in a controlled development setup.
5. Validate image structure, section addresses, checksums and compatibility before any release.

Until these requirements are met, CI must not create a fake `firm.bin`, and users must not install an experimental image over their console firmware.

The existing console firmware and Luma3DS remain untouched by the current homebrew build.
