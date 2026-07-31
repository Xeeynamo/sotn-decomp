// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060DE8E4(Entity* self);
void func_060DF140(Entity* self);
void func_060DF62C(Entity* self);
void func_060E0160(Entity* self);
void func_060E0260(Entity* self);

extern char g_RStage15ObtainedText[];

typedef struct {
    s8 values[2];
    u8 padding[2];
} RStage15HeartPrizeValues;

typedef struct {
    u16 indices[9];
    u16 padding;
} RStage15SubweaponIndices;

EntityEntry g_RStage15EntityEntry02 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DE8E4};
EntityEntry g_RStage15EntityEntry09 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DF140};
EntityEntry g_RStage15EntityEntry10 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DF62C};
EntityEntry g_RStage15EntityEntry11 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E0160};
EntityEntry g_RStage15EntityEntry13 = {NULL, func_060E0260};

RStage15HeartPrizeValues g_RStage15HeartPrizes = {{1, 5}, {0, 0}};

u32 g_RStage15GoldPrizes[10] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

RStage15SubweaponIndices g_RStage15AlucardSubweaponIndices = {
    {1, 2, 4, 3, 6, 5, 7, 8, 9},
    0,
};

char* g_RStage15RelicOrbTexts[] = {g_RStage15ObtainedText};

s16 g_RStage15RelicOrbTextBg1EndY[8] = {
    16, 12, 8, 4, 0, -4, -8, -12,
};

s16 g_RStage15RelicOrbTextBg1StartY[8] = {
    -32, -26, -20, -13, -7, -1, 5, 12,
};

s16 g_RStage15RelicOrbTextBg2StartY[8] = {
    -16, -12, -8, -4, 0, 4, 8, 12,
};

s16 g_RStage15RelicOrbTextBg2EndY[8] = {
    32, 26, 20, 13, 7, 1, -5, -12,
};

s16 g_RStage15RelicOrbSparkleX[8] = {
    -8, 4, -2, 8, 0, 4, -4, 2,
};

s16 g_RStage15RelicOrbSparkleY[8] = {
    -2, 2, 4, -3, 0, 2, -4, 3,
};
