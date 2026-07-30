// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060E3794(Entity* self);
void func_060E3A80(Entity* self);

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Stage15SoulStealOrbSpriteRect;

EntityEntry g_Stage15EntityEntry06 = {
    &g_SaturnSharedSpriteBank6Resource, func_060E3794};
EntityEntry g_Stage15EntityEntry12 = {NULL, func_060E3A80};

u8 g_Stage15SoulStealOrbAnim[14] = {
    4, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 3, 0, 0,
};

Stage15SoulStealOrbSpriteRect g_Stage15SoulStealOrbSpriteRects[6] = {
    {-3, -3, 8, 8},     {-3, -3, 8, 8},     {-7, -7, 16, 15},
    {-11, -11, 24, 23}, {-11, -11, 24, 23}, {-11, -11, 24, 23},
};

u16 g_Stage15SoulStealOrbAngles[8] = {
    0x820, 0x840, 0x860, 0x880, 0x8C0, 0x900, 0x940, 0xA00,
};
u16 g_Stage15SoulStealOrbAnglesPadding = 0;
