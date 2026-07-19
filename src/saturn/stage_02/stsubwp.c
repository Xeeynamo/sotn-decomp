// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    s16 offsetX;
    s16 offsetY;
    s16 params;
    s16 facingLeft;
} Stage02SubweaponGlassDebris;

s32 g_Stage02SubweaponContainerPrizeIds[9] = {
    22, 20, 16, 14, 19, 21, 15, 17, 18,
};

u16 g_Stage02SubweaponContainerAngles[10] = {
    0xB199, 0xA952, 0xD218, 0xD1D2, 0xDE73,
    0xC2D0, 0xB250, 0xCB16, 0xC297, 0x90EC,
};

Stage02SubweaponGlassDebris g_Stage02SubweaponGlassDebris[9] = {
    {0, -87, 3, 0},  {-12, -70, 7, 1}, {-13, -55, 6, 0},
    {8, -74, 7, 1},  {12, -60, 6, 1},  {-11, -39, 5, 0},
    {10, -41, 4, 0}, {2, -49, 5, 1},   {0, -66, 7, 1},
};

u8 g_Stage02FallingLiquidAnim[16] = {
    1, 1, 4, 1, 2, 1, 5, 1, 2, 1, 3, 1, 0, 0, 0, 0,
};

s32 g_Stage02FallingLiquidVelocities[4] = {
    -0x10000,
    -0x10000,
    -0x8000,
    -0x4000,
};
