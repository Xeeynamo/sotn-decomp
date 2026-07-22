// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

Point16 g_RichterWhipStandingPoseOffsets[7] = {
    {7, -2}, {16, -2}, {5, -18}, {-14, -18},
    {-23, -6}, {-24, -6}, {-25, -5},
};

Point16 g_RichterWhipCrouchingPoseOffsets[7] = {
    {7, 11}, {16, 11}, {5, -5}, {-14, -5},
    {-23, 11}, {-24, 11}, {-25, 11},
};

Point16 g_RichterWhipStandingAimOffsetsLeft[9] = {
    {-15, -3}, {-14, -14}, {-11, -5}, {-16, -5}, {-10, 1},
    {-11, -9}, {-16, -10}, {-13, 0}, {-14, 0},
};

s16 g_RichterWhipStandingAimXOffsetsRight[9] = {
    15, 14, 16, 11, 10, 16, 11, 14, 13,
};

Point16 g_RichterWhipCrouchingAimOffsetsLeft[9] = {
    {-15, 9}, {-14, -1}, {-9, 7}, {-18, 9}, {-9, 15},
    {-11, 4}, {-16, 3}, {-7, 13}, {-14, 13},
};

s16 g_RichterWhipCrouchingAimXOffsetsRight[9] = {
    15, 14, 18, 9, 9, 16, 11, 14, 7,
};

Point16 g_RichterWhipAirborneAimOffsetsLeft[9] = {
    {-15, -6}, {-14, -16}, {-9, -8}, {-18, -6}, {-9, 0},
    {-11, -11}, {-16, -12}, {-7, -2}, {-14, -2},
};

s16 g_RichterWhipAirborneAimXOffsetsRight[9] = {
    15, 14, 18, 9, 9, 16, 11, 14, 7,
};

s32 g_RichterUnusedWhipAimIndices[8] = {1, 5, 2, 7, 4, 8, 3, 6};

Point32 g_RichterWhipPoseVelocities[7] = {
    {0x00040000, 0x00020000},
    {0x00040000, -0x00028000},
    {0x00100000, 0},
    {0x00100000, 0},
    {-0x00140000, 0},
    {-0x00200000, 0},
    {-0x00340000, 0},
};

Point32 g_RichterWhipAimVelocities[9] = {
    {0, 0},
    {-0x00028000, 0},
    {-0x00002000, 0x00020000},
    {-0x00002000, -0x00020000},
    {0x00008000, 0},
    {-0x00020000, 0x00018000},
    {-0x00020000, -0x00018000},
    {0x00008000, 0x00018000},
    {0x00008000, -0x00018000},
};

s32 g_RichterWhipAimPaths[9][9] = {
    {1, 1, 5, 6, 0, 1, 1, 0, 0},
    {2, 5, 2, 0, 7, 2, 0, 2, 0},
    {3, 6, 0, 3, 8, 0, 3, 0, 3},
    {4, 0, 7, 8, 4, 0, 0, 4, 4},
    {5, 5, 5, 0, 0, 5, 1, 2, 0},
    {6, 6, 0, 6, 0, 1, 6, 0, 3},
    {7, 0, 7, 0, 7, 1, 0, 7, 4},
    {8, 0, 0, 8, 8, 4, 3, 7, 8},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

u16 g_RichterWhipPaletteCycle[3] = {16, 17, 18};

s16 g_RichterWhipSegmentDelays[16] = {
    16, 14, 12, 10, 8, 6, 4, 2, 15, 13, 11, 9, 7, 5, 3, 255,
};

u16 g_RichterWhipSegmentPhaseOffsets[16] = {
    0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15,
};

u16 g_RichterWhipCrouchingFramesRight[9] = {
    10, 11, 13, 17, 15, 12, 18, 14, 16,
};

u16 g_RichterWhipCrouchingFramesLeft[9] = {
    10, 11, 17, 13, 15, 18, 12, 16, 14,
};

u16 g_RichterWhipStandingFramesRight[9] = {1, 2, 4, 8, 6, 3, 9, 5, 7};

u16 g_RichterWhipStandingFramesLeft[9] = {1, 2, 8, 4, 6, 9, 3, 7, 5};

u16 g_RichterWhipAirborneFramesRight[9] = {
    19, 20, 22, 26, 24, 21, 27, 23, 25,
};

u16 g_RichterWhipAirborneFramesLeft[9] = {
    19, 20, 26, 22, 24, 27, 21, 25, 23,
};
