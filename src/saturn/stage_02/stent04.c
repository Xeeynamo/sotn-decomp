// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060E2A80(Entity* self);
void func_060E32DC(Entity* self);
void func_060E37C8(Entity* self);
void func_060E42FC(Entity* self);
void func_060E43F4(Entity* self);

extern char g_Stage02ObtainedText[];

typedef struct {
    s8 values[2];
    u8 padding[2];
} Stage02HeartPrizeValues;

typedef struct {
    u16 indices[9];
    u16 padding;
} Stage02SubweaponIndices;

EntityEntry g_Stage02EntityEntry02 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E2A80};
EntityEntry g_Stage02EntityEntry09 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E32DC};
EntityEntry g_Stage02EntityEntry10 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E37C8};
EntityEntry g_Stage02EntityEntry11 = {
    &g_SaturnSharedSpriteBank0Resource, func_060E42FC};
EntityEntry g_Stage02EntityEntry13 = {NULL, func_060E43F4};

Stage02HeartPrizeValues g_Stage02HeartPrizes = {{1, 5}, {0, 0}};

u32 g_Stage02GoldPrizes[10] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

Stage02SubweaponIndices g_Stage02AlucardSubweaponIndices = {
    {1, 2, 4, 3, 6, 5, 7, 8, 9},
    0,
};

char* g_Stage02RelicOrbTexts[] = {g_Stage02ObtainedText};

s16 g_Stage02RelicOrbTextBg1EndY[8] = {
    16, 12, 8, 4, 0, -4, -8, -12,
};

s16 g_Stage02RelicOrbTextBg1StartY[8] = {
    -32, -26, -20, -13, -7, -1, 5, 12,
};

s16 g_Stage02RelicOrbTextBg2StartY[8] = {
    -16, -12, -8, -4, 0, 4, 8, 12,
};

s16 g_Stage02RelicOrbTextBg2EndY[8] = {
    32, 26, 20, 13, 7, 1, -5, -12,
};

s16 g_Stage02RelicOrbSparkleX[8] = {
    -8, 4, -2, 8, 0, 4, -4, 2,
};

s16 g_Stage02RelicOrbSparkleY[8] = {
    -2, 2, 4, -3, 0, 2, -4, 3,
};
