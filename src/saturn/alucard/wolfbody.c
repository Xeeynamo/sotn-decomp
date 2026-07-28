// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

s16 g_AlucardWolfBodyYOffsets0[8] = {0, 1, 0, -1, 0, 1, 0, -1};
s16 g_AlucardWolfBodyYOffsets1[8] = {0, 1, 2, 3, 4, 3, 2, 1};
s16 g_AlucardWolfBodyYOffsets2[8] = {0, 0, 1, 1, 2, 2, 3, 3};
s16 g_AlucardWolfHeadYOffsets0[8] = {0, 1, 0, -1, 0, 1, 0, -1};
s16 g_AlucardWolfHeadYOffsets1[8] = {0, 1, 1, 0, 0, 1, 1, 0};
s16 g_AlucardWolfHeadYOffsets2[8] = {0, 0, 0, 1, 1, 1, 2, 2};

AnimationFrame g_AlucardWolfHeadAnim[6] = {
    POSE(2, 0x48, 0), POSE(4, 0x4B, 0), POSE(16, 0x4C, 0),
    POSE(4, 0x4B, 0), POSE(8, 0x48, 0), POSE(-1, 0x48, 0),
};

s32 g_AlucardWolfHeadPoseOrder[6] = {0, 1, 2, 1, 0, 0};
s32 g_AlucardWolfHeadPoseOffsets[8] = {0, 1, 1, 2, 2, 1, 1, 0};
