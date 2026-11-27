# XVROS Wi-Fi subsystem

This directory is reserved for Wi-Fi service design, configuration and network protocol documentation.

The current compiled Wi-Fi status implementation is in `source/wifi/`, with its public interface in `include/wifi/`.

Planned responsibilities:
- Wi-Fi radio and connection status
- Saved network metadata (without storing credentials in source control)
- IP configuration and socket lifecycle
- Local network discovery and multiplayer rooms
- XVROS Link transport integration

Current implementation only reads the system Wi-Fi signal indicator. Connection management and network communication are not implemented yet.
