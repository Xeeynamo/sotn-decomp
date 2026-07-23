// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

u16 g_RichterUnusedDaggerConstants[14] = {
    0x0000, 0x0F80, 0x0000, 0x0100, 0x0000, 0x0700, 0x0000,
    0x0880, 0x0400, 0x06AB, 0x0955, 0x0C00, 0x0EAB, 0x1155,
};

s16 g_RichterThrownDaggerYOffsets[8] = {
    -5, -9, -3, -13, -5, 1, -7, -1,
};

u8 g_RichterAxeEffectParams[10][4] = {
    {10, 10, 10, 0}, {10, 10, 10, 0}, {10, 10, 10, 0}, {8, 8, 12, 0},
    {8, 8, 12, 0},   {8, 8, 12, 0},   {5, 5, 14, 0},   {5, 5, 14, 0},
    {2, 2, 16, 0},   {2, 2, 18, 0},
};

AnimationFrame g_RichterSubweaponCrossAnim[] = {
    POSE(36, 1, 0), POSE(1, 2, 0), POSE(1, 3, 0), POSE(1, 4, 0), POSE(1, 5, 0),
    POSE(1, 6, 0),  POSE(1, 7, 0), POSE(1, 8, 0), POSE_LOOP(0),
};
