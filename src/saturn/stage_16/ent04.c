// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060DCE98(Entity* self);
void func_060DD6F4(Entity* self);
void func_060DDBE0(Entity* self);
void func_060DE714(Entity* self);
void func_060DE814(Entity* self);

extern char g_Stage16ObtainedText[];

typedef struct {
    s8 values[2];
    u8 padding[2];
} Stage16HeartPrizeValues;

typedef struct {
    u16 indices[9];
    u16 padding;
} Stage16SubweaponIndices;

EntityEntry g_Stage16EntityEntry02 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DCE98};
EntityEntry g_Stage16EntityEntry09 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DD6F4};
EntityEntry g_Stage16EntityEntry10 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DDBE0};
EntityEntry g_Stage16EntityEntry11 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DE714};
EntityEntry g_Stage16EntityEntry13 = {NULL, func_060DE814};

Stage16HeartPrizeValues g_Stage16HeartPrizes = {{1, 5}, {0, 0}};

u32 g_Stage16GoldPrizes[10] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

Stage16SubweaponIndices g_Stage16AlucardSubweaponIndices = {
    {1, 2, 4, 3, 6, 5, 7, 8, 9},
    0,
};

char* g_Stage16RelicOrbTexts[] = {g_Stage16ObtainedText};

s16 g_Stage16RelicOrbTextBg1EndY[8] = {
    16, 12, 8, 4, 0, -4, -8, -12,
};

s16 g_Stage16RelicOrbTextBg1StartY[8] = {
    -32, -26, -20, -13, -7, -1, 5, 12,
};

s16 g_Stage16RelicOrbTextBg2StartY[8] = {
    -16, -12, -8, -4, 0, 4, 8, 12,
};

s16 g_Stage16RelicOrbTextBg2EndY[8] = {
    32, 26, 20, 13, 7, 1, -5, -12,
};

s16 g_Stage16RelicOrbSparkleX[8] = {
    -8, 4, -2, 8, 0, 4, -4, 2,
};

s16 g_Stage16RelicOrbSparkleY[8] = {
    -2, 2, 4, -3, 0, 2, -4, 3,
};
