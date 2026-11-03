// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include "stage_14.h"

typedef struct {
    s8 values[2];
    u8 padding[2];
} Stage14HeartPrizeValues;

EntityEntry g_Stage14EntityEntry02 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DEDF8};
EntityEntry g_Stage14EntityEntry09 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DF654};
EntityEntry g_Stage14EntityEntry10 = {
    &g_SaturnSharedSpriteBank0Resource, func_060DFB40};
EntityEntry g_Stage14EntityEntry11 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E0674};
EntityEntry g_Stage14EntityEntry13 = {NULL, func_060E0774};

Stage14HeartPrizeValues g_Stage14HeartPrizes = {{1, 5}, {0, 0}};

u32 g_Stage14GoldPrizes[10] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

Stage14SubweaponIndices g_Stage14AlucardSubweaponIndices = {
    {1, 2, 4, 3, 6, 5, 7, 8, 9},
    0,
};

char* g_Stage14RelicOrbTexts[] = {g_Stage14ObtainedText};

s16 g_Stage14RelicOrbTextBg1EndY[8] = {
    16, 12, 8, 4, 0, -4, -8, -12,
};

s16 g_Stage14RelicOrbTextBg1StartY[8] = {
    -32, -26, -20, -13, -7, -1, 5, 12,
};

s16 g_Stage14RelicOrbTextBg2StartY[8] = {
    -16, -12, -8, -4, 0, 4, 8, 12,
};

s16 g_Stage14RelicOrbTextBg2EndY[8] = {
    32, 26, 20, 13, 7, 1, -5, -12,
};

s16 g_Stage14RelicOrbSparkleX[8] = {
    -8, 4, -2, 8, 0, 4, -4, 2,
};

s16 g_Stage14RelicOrbSparkleY[8] = {
    -2, 2, 4, -3, 0, 2, -4, 3,
};
