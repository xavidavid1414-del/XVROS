import struct
import unittest
import zlib

from validate_xvbin import HEADER, HEADER_SIZE, ValidationError, validate


def make_bin(payload=b"XVROS test payload", entry=0):
    header = HEADER.pack(
        b"XVBN", 1, HEADER_SIZE, 0, HEADER_SIZE,
        len(payload), entry, zlib.crc32(payload) & 0xFFFFFFFF, 0
    )
    return header + payload


class ValidateXvbinTests(unittest.TestCase):
    def test_valid_container(self):
        result = validate(make_bin())
        self.assertEqual(result["version"], 1)

    def test_rejects_short_header(self):
        with self.assertRaises(ValidationError):
            validate(b"XVBN")

    def test_rejects_bad_magic(self):
        data = bytearray(make_bin())
        data[0:4] = b"NOPE"
        with self.assertRaises(ValidationError):
            validate(data)

    def test_rejects_out_of_range_entry(self):
        with self.assertRaises(ValidationError):
            validate(make_bin(entry=len(b"XVROS test payload")))

    def test_rejects_corrupt_payload(self):
        data = bytearray(make_bin())
        data[-1] ^= 0xFF
        with self.assertRaises(ValidationError):
            validate(data)

    def test_rejects_trailing_bytes(self):
        with self.assertRaises(ValidationError):
            validate(make_bin() + b"extra")


if __name__ == "__main__":
    unittest.main()
