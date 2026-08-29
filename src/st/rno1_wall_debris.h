// SPDX-License-Identifier: AGPL-3.0-or-later

static s16 g_Rno1DebrisCollisionSensors[] = {
    0, 0, 0, 4, 0, -4, 0, 0,
};

static s32 g_Rno1DebrisVelocities[][2] = {
    {FIX(1), FIX(-3)}, {FIX(1.5), FIX(-1.5)},  {FIX(0.75), FIX(-2.25)},
    {FIX(2), FIX(-1)}, {FIX(0.5), FIX(-0.25)}, {FIX(1), FIX(-2)},
};

static s32 g_Rno1WallDebrisVelocities[][2] = {
    {0, 0x6000},      {0x2000, 0x4000}, {0x4000, 0x8000},
    {0x8000, 0x6000}, {0xC000, 0x4000},
};

static s16 g_Rno1WallDebrisSizes[] = {8, 12, 4, 14, 6, 0};
static s16 g_Rno1WallDebrisRotations[] = {
    0x180, 0x100, 0x200, 0xC0, 0x1C0, 0,
};

static AnimateEntityFrame g_Rno1DebrisAnim[] = {
    {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {-1, 0},
};
