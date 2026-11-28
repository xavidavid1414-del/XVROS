#ifndef XVROS_XVBIN_H
#define XVROS_XVBIN_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    XVBIN_OK = 0,
    XVBIN_ERR_ARGUMENT,
    XVBIN_ERR_TRUNCATED,
    XVBIN_ERR_MAGIC,
    XVBIN_ERR_VERSION,
    XVBIN_ERR_HEADER,
    XVBIN_ERR_FLAGS,
    XVBIN_ERR_OFFSET,
    XVBIN_ERR_EMPTY,
    XVBIN_ERR_ENTRY,
    XVBIN_ERR_RESERVED,
    XVBIN_ERR_LENGTH,
    XVBIN_ERR_CRC
} XvbinResult;

typedef struct {
    uint32_t payload_size;
    uint32_t entry_offset;
    uint32_t payload_crc32;
} XvbinInfo;

/* Validates an XVROS BIN v1 container only; never executes its payload. */
XvbinResult xvbin_validate(const uint8_t *data, size_t length, XvbinInfo *info);
const char *xvbin_result_string(XvbinResult result);

#endif
