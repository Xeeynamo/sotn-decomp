// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060DFED0(Entity* self);
void func_060E072C(Entity* self);
void func_060E0C18(Entity* self);
void func_060E174C(Entity* self);
void func_060E184C(Entity* self);

extern char g_Stage15ObtainedText[];

typedef struct {
    s8 values[2];
    u8 padding[2];
} Stage15HeartPrizeValues;

typedef struct {
    u16 indices[9];
    u16 padding;
} Stage15SubweaponIndices;

EntityEntry g_Stage15EntityEntry02 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DFED0};
EntityEntry g_Stage15EntityEntry09 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E072C};
EntityEntry g_Stage15EntityEntry10 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E0C18};
EntityEntry g_Stage15EntityEntry11 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E174C};
EntityEntry g_Stage15EntityEntry13 = {NULL, func_060E184C};

Stage15HeartPrizeValues g_Stage15HeartPrizes = {{1, 5}, {0, 0}};

u32 g_Stage15GoldPrizes[10] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

Stage15SubweaponIndices g_Stage15AlucardSubweaponIndices = {
    {1, 2, 4, 3, 6, 5, 7, 8, 9},
    0,
};

char* g_Stage15RelicOrbTexts[] = {g_Stage15ObtainedText};

s16 g_Stage15RelicOrbTextBg1EndY[8] = {
    16, 12, 8, 4, 0, -4, -8, -12,
};

s16 g_Stage15RelicOrbTextBg1StartY[8] = {
    -32, -26, -20, -13, -7, -1, 5, 12,
};

s16 g_Stage15RelicOrbTextBg2StartY[8] = {
    -16, -12, -8, -4, 0, 4, 8, 12,
};

s16 g_Stage15RelicOrbTextBg2EndY[8] = {
    32, 26, 20, 13, 7, 1, -5, -12,
};

s16 g_Stage15RelicOrbSparkleX[8] = {
    -8, 4, -2, 8, 0, 4, -4, 2,
};

s16 g_Stage15RelicOrbSparkleY[8] = {
    -2, 2, 4, -3, 0, 2, -4, 3,
};
