#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_reset);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_init);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_writeByIO);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_FiDMA);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_r_);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_t);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_write);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_read);

extern volatile u16* _spu_RXX[];
extern s32 _spu_mem_mode_plus;

void _spu_FsetRXX(s32 arg0, u32 arg1, s32 arg2) {
    if (arg2 == 0) {
        (*_spu_RXX)[arg0] = arg1;
        return;
    }
    (*_spu_RXX)[arg0] = (arg1 >> _spu_mem_mode_plus);
}

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_FsetRXXa);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_FgetRXXa);
