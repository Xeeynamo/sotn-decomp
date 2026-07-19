// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    s32 x;
    s32 y;
} SpittleBoneParticleVelocity;

SpittleBoneParticleVelocity g_Stage02SpittleBoneSpitParticleVelocities[9] = {
    {-0x26000, 0x04000},
    {-0x25000, 0x06000},
    {-0x24000, 0x08000},
    {-0x22000, 0x0A000},
    {-0x1E000, -0x04000},
    {-0x25000, -0x06000},
    {-0x24000, -0x08000},
    {-0x22000, -0x0A000},
    {-0x1E000, 0},
};

s16 g_Stage02SpittleBoneCollisionOffsets[2] = {0xFF, 0};

s16 g_Stage02SpittleBoneGroundSensors[4][2] = {
    {0, 0},
    {4, 8},
    {-4, -16},
    {0, 0},
};
