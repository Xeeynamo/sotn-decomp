// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

s32 g_AlucardSensorsCeilingBat[4] = {
    FIX(-8),
    FIX(-8),
    FIX(-8),
    FIX(-8),
};

s32 g_AlucardSensorsFloorBat[4] = {
    FIX(8),
    FIX(8),
    FIX(8),
    FIX(8),
};

s32 g_AlucardSensorsWallBat[7] = {
    FIX(7), FIX(0), FIX(0), FIX(0), FIX(0), FIX(0), FIX(-7),
};

s32 g_AlucardSensorsCeilingDefault[4] = {
    FIX(-22),
    FIX(-22),
    FIX(-22),
    FIX(-22),
};

s32 g_AlucardSensorsFloorDefault[4] = {
    FIX(29),
    FIX(25),
    FIX(25),
    FIX(25),
};

s32 g_AlucardSensorsWallDefault[7] = {
    FIX(24), FIX(17), FIX(9), FIX(1), FIX(-7), FIX(-14), FIX(-21),
};

s32 g_AlucardSensorsCeilingCrouch[4] = {
    FIX(0),
    FIX(0),
    FIX(0),
    FIX(0),
};

s32 g_AlucardSensorsWallCrouch[7] = {
    FIX(24), FIX(17), FIX(9), FIX(5), FIX(5), FIX(1), FIX(1),
};

Point32 g_AlucardSensorsCeiling[4] = {
    {FIX(0), FIX(-22)},
    {FIX(0), FIX(-22)},
    {FIX(4), FIX(-22)},
    {FIX(-4), FIX(-22)},
};

Point32 g_AlucardSensorsFloor[4] = {
    {FIX(0), FIX(29)},
    {FIX(0), FIX(25)},
    {FIX(4), FIX(25)},
    {FIX(-4), FIX(25)},
};

Point32 g_AlucardSensorsWall[14] = {
    {FIX(7), FIX(24)},   {FIX(7), FIX(17)},   {FIX(7), FIX(9)},
    {FIX(7), FIX(1)},    {FIX(7), FIX(-7)},   {FIX(7), FIX(-14)},
    {FIX(7), FIX(-21)},  {FIX(-7), FIX(24)},  {FIX(-7), FIX(17)},
    {FIX(-7), FIX(9)},   {FIX(-7), FIX(1)},   {FIX(-7), FIX(-7)},
    {FIX(-7), FIX(-14)}, {FIX(-7), FIX(-21)},
};
