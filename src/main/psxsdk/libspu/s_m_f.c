// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

extern s32 D_8003355C;

void SpuFree(unsigned long arg0) {
    s32 i;

    for (i = 0; i < D_8003355C; i++) {
        if (_spu_memList[i].addr & 0x40000000) {
            break;
        }
        if (_spu_memList[i].addr == arg0) {
            _spu_memList[i].addr |= 0x80000000;
            break;
        }
    }
    func_800286E0();
}
