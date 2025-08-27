// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

s32 SpuInitMalloc(s32 num, s8* top) {
    if (num > 0) {
        _spu_memList = top;
        _spu_memList[0].addr = 0x40001010;
        _spu_memList[0].size = (0x10000 << _spu_mem_mode_plus) - 0x1010;
        D_80033560 = 0;
        D_8003355C = num;
        return num;
    }
    return 0;
}
