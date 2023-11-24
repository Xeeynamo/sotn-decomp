#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_ini", _SpuInit);

void _spu_FiDMA();
extern s32 D_80033098;
extern s32 _spu_EVdma;
extern s32 _spu_isCalled;

void SpuStart(void) {
    s32 temp_v0;

    if (_spu_isCalled == 0) {
        _spu_isCalled = 1;
        EnterCriticalSection();
        D_80033098 = 0;
        _SpuDataCallback(_spu_FiDMA);
        temp_v0 = OpenEvent(0xF0000009U, 0x20, 0x2000, NULL);
        _spu_EVdma = temp_v0;
        EnableEvent(temp_v0);
        ExitCriticalSection();
    }
}
