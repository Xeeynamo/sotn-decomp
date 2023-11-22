#include "common.h"
#include "psxsdk/libspu.h"

s32 _SpuCallback();
extern void (*_spu_IRQCallback)();

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc func) {
    void (*temp_s0)();

    temp_s0 = _spu_IRQCallback;
    if (func != temp_s0) {
        _spu_IRQCallback = func;
        _SpuCallback();
    }
    return temp_s0;
}
