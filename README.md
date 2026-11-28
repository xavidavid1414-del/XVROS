# XVROS

XVROS is an independent system-software project targeting the **New Nintendo 2DS XL**.

The requested final deliverables are a genuine Nintendo 3DS-compatible `.firm` image and a separately specified `.bin` artifact. Neither exists yet; the project is in early development. Any current homebrew application build is a temporary development harness, not the final product.

## Community

Join the XVROS Discord community to follow development, share feedback and connect with other members:

**[Join the XVROS Discord server](https://discord.gg/YDkRCPHw5R)**

## Current status

- [x] Initial repository and source layout
- [x] Early dual-screen homebrew development harness
- [x] Initial Wi-Fi signal status module
- [x] Separate firmware engineering directory
- [x] `.firm` and `.bin` targets documented as distinct deliverables
- [ ] Verified FIRM boot-chain and container specification
- [ ] Defined XVROS BIN layout and loader contract
- [x] Portable core lifecycle foundation (host-tested)\n- [ ] Hardware initialization and device service integration
- [ ] FIRM and BIN packaging tools
- [x] Automated BIN and core lifecycle validation
- [ ] Non-destructive hardware testing
- [ ] Qualified `.firm` and `.bin` release artifacts

Unchecked items are planned work, not implemented features.

## Firmware targets

- `.firm` — a real FIRM-format image, with verified structure and a documented compatible boot path.
- `.bin` — a separate raw binary artifact whose contents, memory layout and loading method must be specified by XVROS.

The file extension does not make an image bootable. XVROS will not rename an ELF, `.3dsx` or arbitrary binary and present it as firmware. See [firmware engineering notes](firmware/README.md) for the implementation milestones and release safeguards.

## Development harness

The repository currently contains an early 3DS homebrew build harness used for development and CI experiments. It is not the final requested format and must not be installed or described as a bootable XVROS firmware.

## Project layout

- `source/` — current development harness and early core code
- `include/` — public project headers
- `source/wifi/` — initial Wi-Fi signal status module
- `firmware/` — FIRM/BIN specifications, packaging and validation work
- `System/` — planned system services
- `Apps/` — planned built-in applications
- `Assets/` — planned interface resources
- `Emulators/` — planned emulator integration layer
- `Tools/` — planned developer and packaging utilities
- `docs/` — architecture and roadmap

## Wi-Fi

The initial Wi-Fi module reads the signal indicator exposed by the system. It does not yet connect to access points, manage saved networks, open sockets or host multiplayer rooms.

## Multiplayer and XVROS Link

XVROS Link is a planned Android companion and networking layer. Cross-play requires compatible game protocols or game-specific integration; a launcher cannot automatically make every existing 3DS game cross-platform.

## License

Project source and third-party components must retain their applicable licenses and notices.
