// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

AnimationFrame g_RichterUnusedHolyWaterGlassAnim[] = {
    POSE(128, 0, 0),
    POSE_LOOP(0),
};

s16 g_RichterHolyWaterGlassShardVertices[4][6] = {
    {2, -2, 0, -4, 0, 0},
    {-3, -3, -1, 1, 2, 0},
    {-4, -3, 2, -2, -2, 2},
    {-1, 0, 0, -4, 3, 3},
};

s16 g_RichterUnusedHolyWaterParams[4] = {16, 0, -1, 0};

s32 g_RichterHolyWaterFlameTextureCoords[8][2] = {
    {28, 0}, {28, 16}, {28, 32}, {28, 48},
    {60, 0}, {60, 16}, {60, 32}, {60, 48},
};
