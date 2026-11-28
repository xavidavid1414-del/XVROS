#include "xvbin.h"

#include <stdint.h>

#define XVBIN_HEADER_SIZE 32u
#define XVBIN_VERSION 1u

static uint16_t read_le16(const uint8_t *p)
{
    return (uint16_t)((uint16_t)p[0] | ((uint16_t)p[1] << 8));
}

static uint32_t read_le32(const uint8_t *p)
{
    return (uint32_t)p[0]
        | ((uint32_t)p[1] << 8)
        | ((uint32_t)p[2] << 16)
        | ((uint32_t)p[3] << 24);
}

static uint32_t crc32_ieee(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFFu;
    size_t i;

    for (i = 0; i < length; ++i) {
        unsigned bit;
        crc ^= data[i];
        for (bit = 0; bit < 8; ++bit) {
            const uint32_t mask = (uint32_t)-(int32_t)(crc & 1u);
            crc = (crc >> 1) ^ (0xEDB88320u & mask);
        }
    }

    return crc ^ 0xFFFFFFFFu;
}

XvbinResult xvbin_validate(const uint8_t *data, size_t length, XvbinInfo *info)
{
    uint32_t payload_offset;
    uint32_t payload_size;
    uint32_t entry_offset;
    uint32_t expected_crc;
    size_t expected_length;

    if (data == NULL || info == NULL)
        return XVBIN_ERR_ARGUMENT;
    if (length < XVBIN_HEADER_SIZE)
        return XVBIN_ERR_TRUNCATED;
    if (data[0] != 'X' || data[1] != 'V' || data[2] != 'B' || data[3] != 'N')
        return XVBIN_ERR_MAGIC;
    if (read_le16(data + 4) != XVBIN_VERSION)
        return XVBIN_ERR_VERSION;
    if (read_le16(data + 6) != XVBIN_HEADER_SIZE)
        return XVBIN_ERR_HEADER;
    if (read_le32(data + 8) != 0u)
        return XVBIN_ERR_FLAGS;

    payload_offset = read_le32(data + 12);
    payload_size = read_le32(data + 16);
    entry_offset = read_le32(data + 20);
    expected_crc = read_le32(data + 24);

    if (payload_offset != XVBIN_HEADER_SIZE)
        return XVBIN_ERR_OFFSET;
    if (payload_size == 0u)
        return XVBIN_ERR_EMPTY;
    if (entry_offset >= payload_size)
        return XVBIN_ERR_ENTRY;
    if (read_le32(data + 28) != 0u)
        return XVBIN_ERR_RESERVED;

    /* The explicit subtraction check prevents size_t addition overflow. */
    if ((size_t)payload_size > (size_t)-1 - (size_t)payload_offset)
        return XVBIN_ERR_LENGTH;
    expected_length = (size_t)payload_offset + (size_t)payload_size;
    if (expected_length != length)
        return XVBIN_ERR_LENGTH;
    if (crc32_ieee(data + payload_offset, payload_size) != expected_crc)
        return XVBIN_ERR_CRC;

    info->payload_size = payload_size;
    info->entry_offset = entry_offset;
    info->payload_crc32 = expected_crc;
    return XVBIN_OK;
}

const char *xvbin_result_string(XvbinResult result)
{
    switch (result) {
    case XVBIN_OK: return "valid";
    case XVBIN_ERR_ARGUMENT: return "invalid argument";
    case XVBIN_ERR_TRUNCATED: return "truncated header";
    case XVBIN_ERR_MAGIC: return "invalid magic";
    case XVBIN_ERR_VERSION: return "unsupported version";
    case XVBIN_ERR_HEADER: return "invalid header size";
    case XVBIN_ERR_FLAGS: return "unsupported flags";
    case XVBIN_ERR_OFFSET: return "invalid payload offset";
    case XVBIN_ERR_EMPTY: return "empty payload";
    case XVBIN_ERR_ENTRY: return "entry offset outside payload";
    case XVBIN_ERR_RESERVED: return "reserved field is nonzero";
    case XVBIN_ERR_LENGTH: return "file length does not match payload";
    case XVBIN_ERR_CRC: return "payload CRC-32 mismatch";
    default: return "unknown validation result";
    }
}
