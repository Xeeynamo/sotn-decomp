// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

s16 D_80154568[4] = {0, -8, -16, 0};
s32 g_IsPrologueStage = 0;
s16 D_80154574[] = {0x812F, 0x812F, 0x8120, 0x812F, 0x812F, 0x8120,
                    0x812F, 0x812F, 0x8120, 0x812F, 0x812E, 0x812F,
                    0x812E, 0x812F, 0x8120, 0x0000};
s16 D_80154594[] = {0x8120, 0x812B, 0x812C, 0x812D};
s32 D_8015459C = 0;
RECT D_801545A0 = {512, 256, 32, 80};
s16 g_DeadPrologueTimer = 0;
s16 D_801545AA = 0;
s16 D_801545AC = 0;
u8 D_801545B0[] = {10, 8, 8, 6, 6, 4, 4,   4,   4, 4,
                   4,  4, 4, 4, 4, 4, 255, 255, 0, 0};
u8 D_801545C4[] = {4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16};
u8 D_801545D4[] = {8,  12, 16, 20, 24, 28, 32, 32,
                   32, 32, 32, 32, 32, 32, 32, 32};
Point16 g_RicSensorsCeiling[NUM_HORIZONTAL_SENSORS] = {
    {0, -16},
    {0, -16},
    {4, -16},
    {-4, -16},
};
Point16 g_RicSensorsFloor[NUM_HORIZONTAL_SENSORS] = {
    {0, 28},
    {0, 24},
    {4, 24},
    {-4, 24},
};
Point16 g_RicSensorsWall[NUM_VERTICAL_SENSORS * 2] = {
    {7, 23},  {7, 16},  {7, 8},  {7, 0},  {7, -8},  {7, -8},  {7, -15},
    {-7, 23}, {-7, 16}, {-7, 8}, {-7, 0}, {-7, -8}, {-7, -8}, {-7, -15},
};
u16 g_RicSensorsCeilingDefault[NUM_HORIZONTAL_SENSORS] = {-16, -16, -16, -16};
u16 g_RicSensorsFloorDefault[NUM_HORIZONTAL_SENSORS] = {28, 24, 24, 24};
u16 g_RicSensorsWallDefault[NUM_VERTICAL_SENSORS] = {23, 16, 8, 0, -8, -8, -15};
u16 g_RicSensorsCeilingCrouch[NUM_HORIZONTAL_SENSORS] = {0, 0, 0, 0};
u16 g_RicSensorsWallCrouch[NUM_VERTICAL_SENSORS] = {23, 16, 8, 4, 4, 1, 1};
u8 D_80154674[][4] = {{16, 127, 63, 0},
                      {16, 127, 0, 0},
                      {16, 63, 63, 127},
                      {16, 63, 127, 63},
                      {16, 47, 63, 127}};
