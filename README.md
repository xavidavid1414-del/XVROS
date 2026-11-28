# XVROS

XVROS is an independent homebrew system environment for the **New Nintendo 2DS XL**.

The first development target is a safe, installable Nintendo 3DS homebrew application. The project is structured so its desktop, system services, applications, emulator frontends, connectivity layer and future boot components can be developed as separate modules.

## Community

Join the XVROS Discord community to follow development, share feedback and connect with other members:

**[Join the XVROS Discord server](https://discord.gg/YDkRCPHw5R)**

## Current status

- [x] Dual-screen homebrew shell foundation
- [x] Dedicated Wi-Fi status module
- [x] Build configuration for a `.3dsx` homebrew application
- [x] Firmware engineering notes and separate firmware target directory
- [ ] Desktop interface and navigation
- [ ] Settings and control center
- [ ] File manager and application manager
- [ ] Theme and resource packages
- [ ] Emulator center and game library
- [ ] XVROS Link companion and multiplayer SDK
- [ ] Full Wi-Fi networking, local rooms and network services
- [ ] Verified bootable `.firm` image

Unchecked items are planned work, not implemented features.

## Build

Install the devkitPro 3DS development toolchain, including devkitARM and libctru, then run:

```sh
make
```

The intended build output is `XVROS.3dsx`. A `.3dsx` is a homebrew application; it is **not** a firmware image.

## Project layout

- `source/` — application entry point and core shell
- `include/` — public project headers
- `source/wifi/` — Wi-Fi status and future network service implementation
- `firmware/` — firmware format research, design and build notes
- `System/` — system service modules
- `Apps/` — built-in applications
- `Assets/` — interface resources
- `Emulators/` — emulator integration layer
- `Tools/` — developer and packaging utilities
- `docs/` — architecture and roadmap

## Firmware and safety

XVROS will not publish a fake or renamed binary as `firm.bin` or `.firm`. A real 3DS FIRM image requires a correctly structured, hardware-compatible boot payload and careful validation. The initial release runs as homebrew under the existing system and Luma3DS environment. A bootable firmware target is a separate engineering milestone and must not overwrite or replace the console's existing firmware.

## Wi-Fi

The initial Wi-Fi module reads the signal indicator exposed by the system. It does not yet connect to access points, manage saved networks, open sockets or host multiplayer rooms. Those capabilities will be implemented in later networking milestones.

## Multiplayer and XVROS Link

XVROS Link is planned as an Android companion and networking layer. Playing the same game on a 2DS and a phone requires a game with compatible multiplayer/network support or a game-specific integration. It cannot automatically make every existing 3DS game cross-platform.

## License

Project source and third-party components must retain their applicable licenses and notices.
