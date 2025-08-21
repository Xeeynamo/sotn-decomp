// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

extern s32 D_80097960;
extern StHEADER* D_800987C8;
extern s32 D_80098894;

u_long StFreeRing(u_long* base) {
    s32 temp_a1;
    s32 i;
    s16 nSectors;
    StHEADER* temp_v0;

    temp_a1 = (base - (u_long*)&D_800987C8[D_80098894]) / 504;
    temp_v0 = &D_800987C8[temp_a1];
    nSectors = D_800987C8[temp_a1].nSectors;
    if ((s16)temp_v0->id != 4) {
        return 1;
    }
    for (i = 0; i < nSectors; i++) {
        *((s16*)&D_800987C8[i + temp_a1]) = 0;
    }
    D_80097960 = i + temp_a1;
    return 0;
}
