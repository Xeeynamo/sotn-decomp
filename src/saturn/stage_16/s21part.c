// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

u16 g_Stage16BoneScimitarPartRotations[7] = {
    0x100, 0x80, 0x48, 0x20, 0x40, 0x10, 0x30,
};
u16 g_Stage16BoneScimitarPartRotationsPadding = 0;

u8 g_Stage16BoneScimitarDeadPartTimers[7] = {
    0x30, 0x20, 0x14, 0xC, 0x18, 0x10, 0x20,
};
u8 g_Stage16BoneScimitarDeadPartTimersPadding = 0;

s32 g_Stage16BoneScimitarDeadPartVelocityX[7] = {
    FIX(0.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75), 0,
};
s32 g_Stage16BoneScimitarDeadPartVelocityY[7] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-0.875), FIX(-4),
};

s16 g_Stage16BoneScimitarDeadPartPosX[7] = {-4, 0, 4, -4, -4, 4, 0};
s16 g_Stage16BoneScimitarDeadPartPosY[7] = {-16, -8, -4, -4, 9, 9, 0};

u8 g_Stage16BoneScimitarAttackTimerCycles[2][4] = {
    {0x80, 0x08, 0x08, 0x40},
    {0xF0, 0xC0, 0xA0, 0x80},
};

s16 g_Stage16BoneScimitarSensors[14] = {
    0, 19, 8, 0, 0, 3, 8, 0, -12, 16, 0, -16, 0, -16};
