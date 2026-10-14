// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

u16 D_us_80180C64 = 0;
u16 D_us_80180C66 = 0;
s16 D_us_80180C68[] = {0x0000, 0x04D0, 0x00D8, 0x00E8, 0x0068, 0x00B0,
                       0x00F0, 0x00F0, 0x0340, 0x0074, 0x00F0, 0x00F0};

#ifdef VERSION_PSP
char D_pspeu_09265D48[] = "mizu %x\n";
#endif

s32 g_SplashYMovement[] = {FIX(-6.5), FIX(9.0 / 32), FIX(-5.5), FIX(17.0 / 64),
                           FIX(-4.5), FIX(0.25),     FIX(-3.5), FIX(15.0 / 64)};
s16 g_SurfacingYTbl[] = {0, 2, 4, 6, 8, 10};
static s16 water_slow_zones[] = {
    0x260, 0x020, 0x0D0, 0x080, 0x470, 0x020,
    0x0D0, 0x080, 0x0C0, 0x02C, 0x0E0, 0x500,
};
s16 D_us_80180CC4[] = {0x01E0, 0x0060, 0x0061, 0x006E, 0x01FF, 0x01E0};
u8 D_us_80180CD0[] = {0, 0, 0, 1, 1, 0, 0, 0};
u16 D_us_80180CD8[] = {
    0x0373, 0x0000, 0x0000, 0x0000, 0x075E, 0x0001, 0x0001, 0x0001,
    0x0375, 0x0000, 0x0000, 0x0000, 0x0765, 0x0001, 0x0001, 0x0001,
    0x03F2, 0x0000, 0x0000, 0x0000, 0x075C, 0x0001, 0x0001, 0x0001,
    0x072D, 0x0000, 0x0000, 0x0000, 0x075D, 0x0001, 0x0001, 0x0001,
    0x0375, 0x0000, 0x0000, 0x0969, 0x0762, 0x0001, 0x0001, 0x0764,
    0x0933, 0x0000, 0x0000, 0x0951, 0x0761, 0x0001, 0x0001, 0x0763};
static s16 g_splashAspects[] = {0, 1, 2, 4, -1, -2, -4, 0};

s32 D_us_801B2870;
s32 D_us_801B2874;

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A071C);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A07CC);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A09DC);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A0A80);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A1120);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A16E4);

extern EInit g_EInitInteractable;

#include "../../st/water_slow_zone.h"

void func_us_801B5004(Tilemap* map, s32 arg1) {
    Tilemap* tmap;
    s16 tilePos;
    u16* tileData;
    s32 i;

    tmap = &g_Tilemap;
    tilePos = D_us_80180CC4[arg1 >> 1];
    tileData = &D_us_80180CD8[arg1 << 2];

    for (i = 0; i < 4; i++) {
        tmap->fg[tilePos] = *tileData++;
        tilePos += tmap->hSize << 4;
    }
}

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A1BE8);

#include "../../st/entity_splash_water.h"

#include "../../st/entity_water_drop.h"
