#ifndef XVROS_CORE_H
#define XVROS_CORE_H

#include <stdint.h>

typedef enum {
    XVROS_CORE_COLD = 0,
    XVROS_CORE_READY,
    XVROS_CORE_STOPPING,
    XVROS_CORE_STOPPED,
    XVROS_CORE_ERROR
} XvrosCoreState;

typedef struct {
    XvrosCoreState state;
    uint32_t update_count;
} XvrosCore;

typedef enum {
    XVROS_CORE_RESULT_OK = 0,
    XVROS_CORE_RESULT_INVALID_ARGUMENT,
    XVROS_CORE_RESULT_INVALID_STATE
} XvrosCoreResult;

/* Initializes the portable lifecycle state. No hardware is touched here. */
XvrosCoreResult xvros_core_init(XvrosCore *core);

/* Advances one logical update while the core is READY. */
XvrosCoreResult xvros_core_update(XvrosCore *core);

/* Requests an orderly transition to STOPPED. */
XvrosCoreResult xvros_core_shutdown(XvrosCore *core);

const char *xvros_core_state_name(XvrosCoreState state);

#endif
