// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

s32 _SpuIsInAllocateArea(u32 arg0) {
    SPU_MALLOC* var_a1;
    u32 temp_v1;
    u32 bits1;
    u32 bits2;
    u32 mask;

    bits1 = 0x80000000;
    bits2 = 0x40000000;
    mask = 0x0FFFFFFF;

    var_a1 = _spu_memList;
    while (true) {
        temp_v1 = var_a1->addr;
        if (temp_v1 & bits1) {
            var_a1 += 1;
            continue;
        }
        if (!(temp_v1 & bits2)) {
            if ((temp_v1 & mask) < arg0) {
                if (arg0 >= (u32)((temp_v1 & mask) + var_a1->size)) {
                    var_a1 += 1;
                    continue;
                }
                return 1;
            } else {
                return 1;
            }
        }
        break;
    }
    return 0;
}

s32 _SpuIsInAllocateArea_(u32 arg0) {
    SPU_MALLOC* var_a1;
    u32 temp_v1;
    u32 bits1;
    u32 bits2;
    u32 mask;

    bits1 = 0x80000000;
    bits2 = 0x40000000;
    mask = 0x0FFFFFFF;

    var_a1 = _spu_memList;
    arg0 <<= _spu_mem_mode_plus;
    while (true) {
        temp_v1 = var_a1->addr;
        if (temp_v1 & bits1) {
            var_a1 += 1;
            continue;
        }
        if (!(temp_v1 & bits2)) {
            if ((temp_v1 & mask) < arg0) {
                if (arg0 >= (u32)((temp_v1 & mask) + var_a1->size)) {
                    var_a1 += 1;
                    continue;
                }
                return 1;
            } else {
                return 1;
            }
        }
        break;
    }
    return 0;
}
