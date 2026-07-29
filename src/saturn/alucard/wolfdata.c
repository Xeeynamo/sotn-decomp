// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

s32 g_AlucardWolfInitialVelocity = FIX(16);
s32 g_AlucardWolfPoseRadii[6] = {18, 6, 4, 4, 6, 18};

u16 g_AlucardWolfFrames0[] = {69, 0};
u16 g_AlucardWolfFrames1[] = {49, 0};
u16 g_AlucardWolfFrames2[] = {48, 0};
u16 g_AlucardWolfFrames3[] = {36, 37, 38, 39, 40, 41, 42, 43, 0};
u16 g_AlucardWolfFrames4[] = {44, 45, 46, 47, 48, 49, 50, 51, 0};
u16 g_AlucardWolfFrames5[] = {69, 67, 68, 68, 67, 69, 0};
u16 g_AlucardWolfFrames6[] = {52, 53, 0};
u16 g_AlucardWolfFrames7[] = {53, 52, 0};
u16 g_AlucardWolfFrames8[] = {
    55, 56, 57, 58, 58, 58, 58, 61, 62, 63, 64, 0,
};
u16 g_AlucardWolfFrames9[] = {59, 60, 61, 62, 63, 64, 64, 0};
u16 g_AlucardWolfFrames10[] = {55, 56, 57, 61, 62, 63, 64, 0};
u16 g_AlucardWolfFrames11[] = {59, 60, 61, 62, 63, 64, 0};
u16 g_AlucardWolfFrames12[] = {52, 54, 52, 0};
u16 g_AlucardWolfFrames13[] = {53, 0};
u16 g_AlucardWolfFrames14[] = {60, 61, 62, 63, 60, 61, 62, 63, 0};

u16* g_AlucardWolfFrameSequences[17] = {
    g_AlucardWolfFrames0, g_AlucardWolfFrames1,  g_AlucardWolfFrames4,
    g_AlucardWolfFrames5, g_AlucardWolfFrames3,  g_AlucardWolfFrames6,
    g_AlucardWolfFrames7, g_AlucardWolfFrames12, g_AlucardWolfFrames11,
    g_AlucardWolfFrames8, g_AlucardWolfFrames10, g_AlucardWolfFrames13,
    g_AlucardWolfFrames9, g_AlucardWolfFrames8,  g_AlucardWolfFrames14,
    g_AlucardWolfFrames8, g_AlucardWolfFrames2,
};

s16 g_AlucardWolfPoseAdjustA[8] = {1, 2, 1, 0, 1, 2, 1, 0};
s16 g_AlucardWolfPoseAdjustB[8] = {0, 1, 2, 3, 4, 3, 2, 1};
