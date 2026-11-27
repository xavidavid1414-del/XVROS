# XVROS architecture

## Target device

New Nintendo 2DS XL, initially running as a homebrew application under the existing system environment.

## Planned subsystems

| Area | Responsibility |
|---|---|
| Core | Main loop, lifecycle, shared services |
| System | Device information, storage, settings and process utilities |
| Interface | Top-screen desktop and bottom-screen control center |
| Apps | Built-in tools and application launcher |
| Assets | Icons, fonts, wallpapers and interface resources |
| Emulators | Emulator frontends and game library integration |
| Wi-Fi | Signal state, connection information, sockets and local network services |
| XVROS Link | Android companion protocol and compatible multiplayer sessions |
| Tools | Packaging, asset conversion, diagnostics and updates |
| Firmware | Separate future boot-payload research and implementation |

## Wi-Fi module

The `source/wifi/` module is deliberately separate from the interface. The first implementation reads the system-reported Wi-Fi signal level through libctru. It does not yet manage saved access points, enable/disable the radio, obtain IP configuration, open sockets, or host multiplayer rooms.

Planned Wi-Fi service milestones:

1. Signal and radio-state reporting
2. Connection and IP information
3. Socket/network initialization and cleanup
4. Local network discovery and room service
5. XVROS Link protocol integration

## Interface plan

- Top screen: main desktop, app launcher and active application.
- Bottom screen: quick settings/control center, touch actions and status.
- Settings categories: Controls, Interface, Audio, Display, Performance and Other Settings.

## Package formats under consideration

- `.xvapp` — XVROS application package
- `.xvtheme` — theme/resource package
- `.xvplugin` — optional extension package
- `.cfg` — configuration data
- `Assets.pak` — packed interface resources

These are design proposals and are not implemented package formats yet.

## XVROS Link

The Android companion is intended to let a phone and the 2DS participate in the same multiplayer session. This requires a compatible game protocol or game-specific networking support; generic cross-play for every existing game is outside the scope of a universal launcher.

## Firmware boundary

The homebrew shell and the future FIRM target are separate deliverables. The homebrew shell must remain usable without replacing the device's installed firmware.
