// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include "stage_14.h"

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Stage14SoulStealOrbSpriteRect;

EntityEntry g_Stage14EntityEntry06 = {
    &g_SaturnSharedSpriteBank6Resource, func_060E26BC};
EntityEntry g_Stage14EntityEntry12 = {NULL, func_060E29A8};

u8 g_Stage14SoulStealOrbAnim[14] = {
    4, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 3, 0, 0,
};

Stage14SoulStealOrbSpriteRect g_Stage14SoulStealOrbSpriteRects[6] = {
    {-3, -3, 8, 8},     {-3, -3, 8, 8},     {-7, -7, 16, 15},
    {-11, -11, 24, 23}, {-11, -11, 24, 23}, {-11, -11, 24, 23},
};

u16 g_Stage14SoulStealOrbAngles[8] = {
    0x820, 0x840, 0x860, 0x880, 0x8C0, 0x900, 0x940, 0xA00,
};
u16 g_Stage14SoulStealOrbAnglesPadding = 0;
