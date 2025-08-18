// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

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
