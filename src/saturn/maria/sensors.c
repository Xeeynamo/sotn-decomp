// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

Point32 g_RicSensorsCeiling[] = {
    {FIX(0), FIX(-16)},
    {FIX(0), FIX(-16)},
    {FIX(4), FIX(-16)},
    {FIX(-4), FIX(-16)},
};

Point32 g_RicSensorsFloor[] = {
    {FIX(0), FIX(29)},
    {FIX(0), FIX(25)},
    {FIX(4), FIX(25)},
    {FIX(-4), FIX(25)},
};

Point32 g_RicSensorsWall[] = {
    {FIX(7), FIX(24)},  {FIX(7), FIX(17)},   {FIX(7), FIX(9)},
    {FIX(7), FIX(1)},   {FIX(7), FIX(-7)},   {FIX(7), FIX(-8)},
    {FIX(7), FIX(-15)}, {FIX(-7), FIX(24)},  {FIX(-7), FIX(17)},
    {FIX(-7), FIX(9)},  {FIX(-7), FIX(1)},   {FIX(-7), FIX(-7)},
    {FIX(-7), FIX(-8)}, {FIX(-7), FIX(-15)},
};

s32 g_RicSensorsCeilingDefault[] = {
    FIX(-16),
    FIX(-16),
    FIX(-16),
    FIX(-16),
};

s32 g_RicSensorsFloorDefault[] = {FIX(29), FIX(25), FIX(25), FIX(25)};

s32 g_RicSensorsWallDefault[] = {
    FIX(24), FIX(17), FIX(9), FIX(1), FIX(-7), FIX(-8), FIX(-15),
};

s32 g_RicSensorsCeilingCrouch[] = {0, 0, 0, 0};

s32 g_RicSensorsWallCrouch[] = {
    FIX(24), FIX(17), FIX(9), FIX(5), FIX(5), FIX(1), FIX(1),
};
