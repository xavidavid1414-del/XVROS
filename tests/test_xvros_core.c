#include "core/xvros_core.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    XvrosCore core = { XVROS_CORE_COLD, 99 };

    assert(xvros_core_init(0) == XVROS_CORE_RESULT_INVALID_ARGUMENT);
    assert(xvros_core_init(&core) == XVROS_CORE_RESULT_OK);
    assert(core.state == XVROS_CORE_READY);
    assert(core.update_count == 0);
    puts("PASS: initialization resets core state");

    assert(xvros_core_update(&core) == XVROS_CORE_RESULT_OK);
    assert(core.update_count == 1);
    puts("PASS: update advances counter");

    core.update_count = UINT32_MAX;
    assert(xvros_core_update(&core) == XVROS_CORE_RESULT_OK);
    assert(core.update_count == UINT32_MAX);
    puts("PASS: update counter saturates without wrapping");

    assert(xvros_core_shutdown(&core) == XVROS_CORE_RESULT_OK);
    assert(core.state == XVROS_CORE_STOPPED);
    assert(xvros_core_update(&core) == XVROS_CORE_RESULT_INVALID_STATE);
    assert(xvros_core_shutdown(&core) == XVROS_CORE_RESULT_INVALID_STATE);
    puts("PASS: stopped core rejects further operations");

    assert(xvros_core_state_name(XVROS_CORE_READY)[0] == 'r');
    assert(xvros_core_state_name((XvrosCoreState)99)[0] == 'u');
    puts("PASS: state names handle known and unknown values");

    puts("All XVROS core tests passed.");
    return 0;
}
