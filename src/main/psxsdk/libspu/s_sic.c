// SPDX-License-Identifier: MIT
#include "common.h"
#include "psxsdk/libspu.h"
#include "libspu_internal.h"

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc func) {
    void (*temp_s0)();

    temp_s0 = _spu_IRQCallback;
    if (func != temp_s0) {
        _spu_IRQCallback = func;
        _SpuCallback(func);
    }
    return temp_s0;
}
