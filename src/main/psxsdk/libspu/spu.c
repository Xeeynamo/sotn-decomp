#include "common.h"
#include "libspu_internal.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_reset);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_init);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_writeByIO);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_FiDMA);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_r_);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_t);

s32 _spu_write(u32 arg0, u32 arg1) {

    if (_spu_transMode != 0) {
        _spu_writeByIO(arg0, arg1);
        return arg1;
    }
    _spu_t(2, _spu_tsa << _spu_mem_mode_plus);
    _spu_t(1);
    _spu_t(3, arg0, arg1);
    return arg1;
}

s32 _spu_read(s32 arg0, s32 arg1) {
    s32 temp = _spu_tsa << _spu_mem_mode_plus;
    _spu_t(2, temp);
    _spu_t(0);
    _spu_t(3, arg0, arg1);
    return arg1;
}

void _spu_FsetRXX(s32 arg0, u32 arg1, s32 arg2) {
    if (arg2 == 0) {
        _spu_RXX->raw[arg0] = arg1;
        return;
    }

    _spu_RXX->raw[arg0] = (arg1 >> _spu_mem_mode_plus);
}

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_FsetRXXa);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/spu", _spu_FgetRXXa);
