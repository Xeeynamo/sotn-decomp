#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_it", _spu_setInTransfer);

extern s32 _spu_inTransfer;

s32 _spu_getInTransfer(void) { return _spu_inTransfer == 0; }
