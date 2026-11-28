#include "xvbin.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void put_le16(uint8_t *p, uint16_t value)
{
    p[0] = (uint8_t)value;
    p[1] = (uint8_t)(value >> 8);
}

static void put_le32(uint8_t *p, uint32_t value)
{
    p[0] = (uint8_t)value;
    p[1] = (uint8_t)(value >> 8);
    p[2] = (uint8_t)(value >> 16);
    p[3] = (uint8_t)(value >> 24);
}

/* CRC-32 fixture for the fixed payload "test". */
static void make_valid(uint8_t file[36])
{
    memset(file, 0, 36);
    memcpy(file, "XVBN", 4);
    put_le16(file + 4, 1);
    put_le16(file + 6, 32);
    put_le32(file + 12, 32);
    put_le32(file + 16, 4);
    put_le32(file + 20, 0);
    put_le32(file + 24, 0xD87F7E0Cu);
    memcpy(file + 32, "test", 4);
}

int main(void)
{
    uint8_t file[36];
    XvbinInfo info;

    make_valid(file);
    assert(xvbin_validate(file, sizeof(file), &info) == XVBIN_OK);
    assert(info.payload_size == 4);
    assert(info.entry_offset == 0);
    puts("PASS: valid container");

    file[0] = 'N';
    assert(xvbin_validate(file, sizeof(file), &info) == XVBIN_ERR_MAGIC);
    puts("PASS: bad magic rejected");

    make_valid(file);
    assert(xvbin_validate(file, 31, &info) == XVBIN_ERR_TRUNCATED);
    puts("PASS: short header rejected");

    make_valid(file);
    assert(xvbin_validate(file, sizeof(file) - 1, &info) == XVBIN_ERR_LENGTH);
    puts("PASS: truncated payload rejected");

    make_valid(file);
    file[35] ^= 1u;
    assert(xvbin_validate(file, sizeof(file), &info) == XVBIN_ERR_CRC);
    puts("PASS: corrupted payload rejected");

    make_valid(file);
    assert(xvbin_validate(file, sizeof(file) + 1, &info) == XVBIN_ERR_LENGTH);
    puts("PASS: trailing data rejected");

    puts("All XVROS BIN C tests passed.");
    return 0;
}
