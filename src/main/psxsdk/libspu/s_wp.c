#include "common.h"

u16 _spu_FsetRXXa(s32, s32);
s32 _spu_write(u32, u32);
extern s32 _spu_inTransfer;
extern s32 _spu_mem_mode_plus;
extern s32 _spu_transferCallback;
extern u16 _spu_tsa;
u32 SpuWritePartly(u8* addr, u32 size) {
    s32 temp_s0;
    u32 var_s1;

    var_s1 = size;
    if (var_s1 > 0x7F000U) {
        var_s1 = 0x7F000;
    }
    size = var_s1;
    temp_s0 = _spu_tsa << _spu_mem_mode_plus;
    _spu_write(addr, size);
    _spu_tsa = _spu_FsetRXXa(-1, temp_s0 + var_s1);
    if (_spu_transferCallback == 0) {
        _spu_inTransfer = 0;
    }
    return var_s1;
}
