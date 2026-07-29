// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"

void func_060E49FC(Entity* self);

EntityEntry g_Stage15EntityEntry15 = {
    &g_SaturnSharedSpriteBank14Resource, func_060E49FC};

u16 g_Stage15BoneScimitarPartRotations[7] = {
    0x100, 0x80, 0x48, 0x20, 0x40, 0x10, 0x30,
};
u16 g_Stage15BoneScimitarPartRotationsPadding = 0;

u8 g_Stage15BoneScimitarDeadPartTimers[7] = {
    0x30, 0x20, 0x14, 0xC, 0x18, 0x10, 0x20,
};
u8 g_Stage15BoneScimitarDeadPartTimersPadding = 0;

s32 g_Stage15BoneScimitarDeadPartVelocityX[7] = {
    FIX(0.75), FIX(1.75), FIX(1.5), FIX(1), FIX(2), FIX(1.75), 0,
};
s32 g_Stage15BoneScimitarDeadPartVelocityY[7] = {
    FIX(-5), FIX(-3), FIX(-2), FIX(-3), FIX(-4), FIX(-0.875), FIX(-4),
};

s16 g_Stage15BoneScimitarDeadPartPosX[7] = {-4, 0, 4, -4, -4, 4, 0};
s16 g_Stage15BoneScimitarDeadPartPosY[7] = {-16, -8, -4, -4, 9, 9, 0};

u8 g_Stage15BoneScimitarAttackTimerCycles[2][4] = {
    {0x80, 0x08, 0x08, 0x40},
    {0xF0, 0xC0, 0xA0, 0x80},
};

s16 g_Stage15BoneScimitarGroundSensors[4] = {0, 19, 8, 0};
s16 g_Stage15BoneScimitarSpecialSensors[4] = {0, 3, 8, 0};
s16 g_Stage15BoneScimitarMoveSensors[6] = {-12, 16, 0, -16, 0, -16};
