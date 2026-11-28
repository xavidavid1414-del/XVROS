# XVROS BIN container — draft format v1

Status: **draft, not a bootable firmware format**.

This specification defines the project's own `.bin` container for carrying one XVROS core payload. It does not make the file executable by the Nintendo 3DS boot chain, and it is not interchangeable with a Nintendo 3DS `.firm` image. A future loader must explicitly implement and validate this format before any payload can run.

## Byte order and alignment

- All integer fields are unsigned and little-endian.
- Header size is exactly 32 bytes.
- Payload begins at byte offset 32; no implicit padding is permitted in v1.
- The file must end exactly at the end of the payload. Trailing bytes are rejected.
- v1 payload alignment is 4 bytes. Since the header is 32 bytes, the payload offset satisfies this requirement.

## Header layout

| Offset | Size | Field | Required value / meaning |
|---:|---:|---|---|
| 0 | 4 | magic | ASCII `XVBN` |
| 4 | 2 | version | `1` |
| 6 | 2 | header_size | `32` |
| 8 | 4 | flags | `0` in v1; unknown flags rejected |
| 12 | 4 | payload_offset | `32` |
| 16 | 4 | payload_size | Payload length in bytes; must be nonzero |
| 20 | 4 | entry_offset | Offset from payload start; must be less than payload_size |
| 24 | 4 | payload_crc32 | IEEE CRC-32 of payload bytes only |
| 28 | 4 | reserved | `0`; nonzero values rejected |

## Validation rules

A conforming v1 validator must reject:

1. Files shorter than 32 bytes.
2. Incorrect magic, version, header size, flags, payload offset or reserved field.
3. A zero-length payload.
4. An entry offset outside the payload.
5. A declared payload range that exceeds the file.
6. Trailing bytes after the declared payload.
7. A payload whose CRC-32 does not match the header.

The CRC detects accidental corruption; it is **not** a cryptographic signature and does not establish trust or safety.

## Execution boundary

The v1 container is a packaging contract only. It does not define CPU mode, memory mapping, privilege level, hardware initialization, relocation, cache maintenance or a 3DS entry ABI. A loader specification and a separate security review are required before execution is implemented.

## Reference tooling

`tools/validate_xvbin.py` performs structural validation only. Run it with:

```sh
python3 tools/validate_xvbin.py path/to/file.bin
```

A successful validation means only that the file matches this container layout. It does not mean the payload is executable or suitable for installation on a console.
