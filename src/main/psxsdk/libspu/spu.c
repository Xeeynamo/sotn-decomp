#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_reset);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_init);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_writeByIO);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_FiDMA);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_r_);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_t);

s32 _spu_t(s32, ...);
s32 _spu_writeByIO(s32, s32);
extern s32 _spu_mem_mode_plus;
extern s32 _spu_transMode;
extern u16 _spu_tsa;

s32 _spu_write(s32 arg0, s32 arg1) {

    if (_spu_transMode != 0) {
        _spu_writeByIO(arg0, arg1);
        return arg1;
    }
    _spu_t(2, _spu_tsa << _spu_mem_mode_plus);
    _spu_t(1);
    _spu_t(3, arg0, arg1);
    return arg1;
}

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
