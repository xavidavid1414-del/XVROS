#!/usr/bin/env python3
"""Structural validator for the XVROS BIN container v1 (not a code loader)."""
import argparse
import struct
import sys
import zlib
from pathlib import Path

HEADER = struct.Struct("<4sHHIIIIII")
MAGIC = b"XVBN"
VERSION = 1
HEADER_SIZE = 32


class ValidationError(ValueError):
    pass


def validate(data: bytes) -> dict:
    if len(data) < HEADER_SIZE:
        raise ValidationError("file is shorter than the 32-byte header")

    magic, version, header_size, flags, payload_offset, payload_size, entry_offset, checksum, reserved = HEADER.unpack_from(data)

    if magic != MAGIC:
        raise ValidationError("bad magic; expected XVBN")
    if version != VERSION:
        raise ValidationError(f"unsupported version: {version}")
    if header_size != HEADER_SIZE:
        raise ValidationError(f"header_size must be {HEADER_SIZE}")
    if flags != 0:
        raise ValidationError("v1 flags must be zero")
    if payload_offset != HEADER_SIZE:
        raise ValidationError(f"payload_offset must be {HEADER_SIZE}")
    if payload_size == 0:
        raise ValidationError("payload_size must be nonzero")
    if entry_offset >= payload_size:
        raise ValidationError("entry_offset is outside the payload")
    if reserved != 0:
        raise ValidationError("reserved field must be zero")

    expected_size = payload_offset + payload_size
    if expected_size > len(data):
        raise ValidationError("declared payload extends beyond end of file")
    if expected_size < len(data):
        raise ValidationError("trailing bytes after payload are not allowed")

    payload = data[payload_offset:expected_size]
    actual_crc = zlib.crc32(payload) & 0xFFFFFFFF
    if actual_crc != checksum:
        raise ValidationError("payload CRC-32 mismatch")

    return {
        "version": version,
        "payload_size": payload_size,
        "entry_offset": entry_offset,
        "payload_crc32": checksum,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("file", type=Path, help="XVROS .bin file to validate")
    args = parser.parse_args()

    try:
        result = validate(args.file.read_bytes())
    except (OSError, ValidationError) as exc:
        print(f"INVALID: {exc}", file=sys.stderr)
        return 1

    print("STRUCTURALLY VALID XVROS BIN (v1)")
    for key, value in result.items():
        print(f"{key}: {value}")
    print("Note: structural validity does not mean executable or bootable.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
