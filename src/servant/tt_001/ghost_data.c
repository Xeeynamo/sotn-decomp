// SPDX-License-Identifier: AGPL-3.0-or-later
#include "servant.h"

// ability stats for level / 10
// 0 - delay counter
// 1 - spell Id
// 2 - make bad attacks (skips enemy hitbox & 8)
s32 g_GhostAbilityStats[][3] = {
    {120, FAM_ABILITY_GHOST_ATTACK, 1},
    {120, FAM_ABILITY_GHOST_ATTACK, 1},
    {100, FAM_ABILITY_GHOST_ATTACK, 1},
    {100, FAM_ABILITY_GHOST_ATTACK, 1},
    {90, FAM_ABILITY_GHOST_ATTACK, 0},
    {90, FAM_ABILITY_GHOST_ATTACK, 0},
    {75, FAM_ABILITY_GHOST_ATTACK, 0},
    {75, FAM_ABILITY_GHOST_ATTACK_SOULSTEAL, 0},
    {60, FAM_ABILITY_GHOST_ATTACK_SOULSTEAL, 0},
    {60, FAM_ABILITY_GHOST_ATTACK_SOULSTEAL, 0},
};

// Ghost specific clut
u16 g_GhostClut[] = {
    0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x7FFF, 0x8000,
    0x8000, 0x8000, 0xFCE7, 0xFDEF, 0xFEF7, 0xFFFF, 0x8000, 0x8000,
};

// x offsets for positioning question marks for confused ghost
// 4th value is never used
u16 g_ConfusedOffsetsX[4] = {6, 3, 8, 0};

// y offsets for positioning question marks for confused ghost
// 4th value is never used
u16 g_ConfusedOffsetsY[4] = {-20, -18, -15, 0};
