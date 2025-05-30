// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

u8 mar_801545B0[] = {10, 8, 8, 6, 6, 4, 4,  4,  4, 4,
                     4,  4, 4, 4, 4, 4, -1, -1, 0, 0};
u8 mar_801545C4[] = {4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16};
u8 mar_801545D4[] = {8,  12, 16, 20, 24, 28, 32, 32,
                     32, 32, 32, 32, 32, 32, 32, 32};
Point16 g_MarSensorsCeiling[NUM_HORIZONTAL_SENSORS] = {
    {0, -16},
    {0, -16},
    {4, -16},
    {-4, -16},
};
Point16 g_MarSensorsFloor[NUM_HORIZONTAL_SENSORS] = {
    {0, 28},
    {0, 24},
    {4, 24},
    {-4, 24},
};
Point16 g_MarSensorsWall[NUM_VERTICAL_SENSORS * 2] = {
    {7, 23},  {7, 16},  {7, 8},  {7, 0},  {7, -8},  {7, -8},  {7, -15},
    {-7, 23}, {-7, 16}, {-7, 8}, {-7, 0}, {-7, -8}, {-7, -8}, {-7, -15},
};
s16 g_MarSensorsCeilingDefault[NUM_HORIZONTAL_SENSORS] = {-16, -16, -16, -16};
s16 g_MarSensorsFloorDefault[NUM_HORIZONTAL_SENSORS] = {28, 24, 24, 24};
s16 g_MarSensorsWallDefault[] = {23, 16, 8, 0, -8, -8, -15};
s16 D_pspeu_092C5198[NUM_HORIZONTAL_SENSORS] = {-4, -4, -4, -4};
s16 D_pspeu_092C51A0[NUM_HORIZONTAL_SENSORS] = {28, 24, 24, 24};
s16 D_pspeu_092C51A8[NUM_VERTICAL_SENSORS] = {15, 13, 11, 9, 7, -1, -3};
s16 g_MarSensorsCeilingCrouch[NUM_HORIZONTAL_SENSORS] = {0, 0, 0, 0};
s16 g_MarSensorsWallCrouch[NUM_VERTICAL_SENSORS] = {23, 16, 8, 4, 4, 1, 1};
