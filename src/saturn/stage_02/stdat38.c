// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

u16 g_Stage02BoneScimitarPartRotations[7] = {
    0x100, 0x80, 0x48, 0x20, 0x40, 0x10, 0x18};
u16 g_Stage02BoneScimitarPartRotationsPadding = 0;

u8 g_Stage02BoneScimitarDeadPartTimers[7] = {
    0x30, 0x20, 0x14, 0xC, 0x18, 0x10, 0x14};
u8 g_Stage02BoneScimitarDeadPartTimersPadding = 0;

s32 g_Stage02BoneScimitarDeadPartVelocityX[7] = {
    FIX(0.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75), FIX(0.75)};

s32 g_Stage02BoneScimitarDeadPartVelocityY[7] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-0.875), FIX(-4)};

s16 g_Stage02BoneScimitarDeadPartPosX[7] = {-4, 0, 4, -4, -4, 4, 0};
s16 g_Stage02BoneScimitarDeadPartPosY[7] = {-16, -8, -4, -4, 9, 9, 0};

u8 g_Stage02BoneScimitarAttackTimerCycles[2][4] = {
    {0x80, 0x08, 0x08, 0x40},
    {0xF0, 0xC0, 0xA0, 0x80},
};

s16 g_Stage02BoneScimitarGroundSensors[8] = {
    0, 20, 0, 4, 8, -4, -16, 0};
s16 g_Stage02BoneScimitarSpecialSensors[4] = {0, 20, 12, 0};
s16 g_Stage02BoneScimitarMoveSensors[6] = {-12, 16, 0, -16, 0, -16};

s16 g_Stage02BoneScimitarInitOffset[2] = {0, 20};
