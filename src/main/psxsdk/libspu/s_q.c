#include "common.h"
#include "libspu_internal.h"

s32 CloseEvent(u32);
s32 DisableEvent(u32);
void _SpuDataCallback(void (*arg0)());

void SpuQuit(void) {
    if (_spu_isCalled == 1) {
        _spu_isCalled = 0;
        EnterCriticalSection();
        _spu_transferCallback = NULL;
        _spu_IRQCallback = NULL;
        _SpuDataCallback(0);
        CloseEvent(_spu_EVdma);
        DisableEvent(_spu_EVdma);
        ExitCriticalSection();
    }
}
