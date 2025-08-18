// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

s32 SpuSetIRQ(s32 arg0) {
    u32 var_v1;

    if ((arg0 == 0) || (arg0 == 3)) {
        _spu_RXX->rxx.spucnt &= ~0x40;
        for (var_v1 = 0; _spu_RXX->rxx.spucnt & 0x40; var_v1++) {
            if (var_v1 + 1 > 0xF00) {
                printf("SPU: time out: wait (IRQ/ON)");
                return -1;
            }
        }
    }
    if ((arg0 == 1) || (arg0 == 3)) {
        _spu_RXX->rxx.spucnt |= 0x40;
        for (var_v1 = 0; !(_spu_RXX->rxx.spucnt & 0x40); var_v1++) {
            if (var_v1 + 1 > 0xF00) {
                printf("SPU: time out: wait (IRQ/OFF)");
                return -1;
            }
        }
    }
    return arg0;
}
