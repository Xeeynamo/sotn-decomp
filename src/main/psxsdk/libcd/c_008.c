// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

extern StHEADER* D_800987C8;

int init_ring_status(s32 arg0, u32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        *((s32*)&D_800987C8[i + arg0]) = 0;
    }
}
