// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern EInit g_EInitCommon;

extern u16 g_WaterSounds[];
extern s16 g_WaterXTbl[];

static s16 g_splashAspects[] = {0, 1, 2, 4, -1, -2, -4, 0};

static u16 func_pspeu_0924B480(s16 arg0, s16 arg1, s16 arg2, s16* arg3) {
    s16 temp_s2;
    s16 temp;
    s16* ptr;

    ptr = &g_WaterXTbl[arg0 * 8];
    arg1 -= (g_Tilemap.width - *ptr++);
    temp_s2 = *ptr++;
    arg1 += temp_s2;
    if (arg1 < 0) {
        return 0;
    }
    *arg3++ = arg1;

    temp = temp_s2 - arg1;
    if (temp <= 0) {
        return 0;
    }
    temp_s2 = temp;
    *arg3 = temp;

    temp = g_splashAspects[*ptr++];
    if (temp) {
        temp = temp_s2 / temp;
    } else {
        temp = 0;
    }

    temp = temp + (g_Tilemap.height - *ptr++);
    if (temp < arg2) {
        return 0;
    }
    if (arg2 <= (g_Tilemap.height - *ptr++)) {
        return 0;
    }
    return ((temp + 0x7FFF) + 1) - arg2;
}

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntityAlucardWaterEffect);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntitySplashWater);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntitySurfacingWater);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntitySideWaterSplash);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntitySmallWaterDrop);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntityWaterDrop);
