// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "shared_sprite_banks.h"
#include "rstage16.h"

EntityEntry g_RStage16EntityEntry06 = {
    &g_SaturnSharedSpriteBank6Resource, func_060E0104};

EntityEntry g_RStage16EntityEntry12 = {NULL, func_060E03F0};

u8 g_RStage16SoulStealOrbAnim[14] = {
    4, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 3, 0, 0,
};

RStage16SoulStealOrbSpriteRect g_RStage16SoulStealOrbSpriteRects[6] = {
    {-3, -3, 8, 8},     {-3, -3, 8, 8},     {-7, -7, 16, 15},
    {-11, -11, 24, 23}, {-11, -11, 24, 23}, {-11, -11, 24, 23},
};

u16 g_RStage16SoulStealOrbAngles[8] = {
    0x820, 0x840, 0x860, 0x880, 0x8C0, 0x900, 0x940, 0xA00,
};

u16 g_RStage16SoulStealOrbAnglesPadding = 0;
