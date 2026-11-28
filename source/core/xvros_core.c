#include "core/xvros_core.h"

XvrosCoreResult xvros_core_init(XvrosCore *core)
{
    if (core == 0)
        return XVROS_CORE_RESULT_INVALID_ARGUMENT;

    core->state = XVROS_CORE_READY;
    core->update_count = 0;
    return XVROS_CORE_RESULT_OK;
}

XvrosCoreResult xvros_core_update(XvrosCore *core)
{
    if (core == 0)
        return XVROS_CORE_RESULT_INVALID_ARGUMENT;
    if (core->state != XVROS_CORE_READY)
        return XVROS_CORE_RESULT_INVALID_STATE;

    if (core->update_count != UINT32_MAX)
        ++core->update_count;

    return XVROS_CORE_RESULT_OK;
}

XvrosCoreResult xvros_core_shutdown(XvrosCore *core)
{
    if (core == 0)
        return XVROS_CORE_RESULT_INVALID_ARGUMENT;
    if (core->state != XVROS_CORE_READY)
        return XVROS_CORE_RESULT_INVALID_STATE;

    core->state = XVROS_CORE_STOPPING;
    core->state = XVROS_CORE_STOPPED;
    return XVROS_CORE_RESULT_OK;
}

const char *xvros_core_state_name(XvrosCoreState state)
{
    switch (state) {
    case XVROS_CORE_COLD: return "cold";
    case XVROS_CORE_READY: return "ready";
    case XVROS_CORE_STOPPING: return "stopping";
    case XVROS_CORE_STOPPED: return "stopped";
    case XVROS_CORE_ERROR: return "error";
    default: return "unknown";
    }
}
