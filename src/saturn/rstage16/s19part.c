// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

s16 g_RStage16WightSensors[4][2] = {
    {0, 23},
    {0, 4},
    {8, -4},
    {-16, 0},
};

s16 g_RStage16Entity28Sensors[4][2] = {
    {0, 12},
    {0, 4},
    {8, -4},
    {-16, 0},
};

u16 g_RStage16WightHitbox0[3] = {
    0x10,
    8,
    0xFF,
};

u16 g_RStage16WightHitbox1[5] = {
    0, 0x17, 8, 0, 0,
};

u8 g_RStage16WightAnim0[12] = {
    0x14, 1, 0x14, 2, 0x14, 3, 0x14, 2, 0, 0, 0, 0,
};

u8 g_RStage16Entity28Anim0[12] = {
    0x18, 4, 0x18, 5, 0x18, 6, 0x18, 5, 0, 0, 0, 0,
};

u8 g_RStage16WightAnim1[20] = {
    0x18, 7, 0x18, 8, 0x18, 9, 0x18, 8, 0, 0,
    0,    0, 0x12, 8, 0x12, 9, 0xFF, 0, 0, 0,
};

u8 g_RStage16WightAnim2[12] = {
    8, 7, 8, 0xA, 4, 7, 0x20, 0xA, 0, 0, 0, 0,
};

u8 g_RStage16WightAnim3[16] = {
    8, 1, 8, 0xB, 8, 0xC, 8, 0xD, 4, 0xE, 2, 0xF, 0xFF, 0, 0, 0,
};

u8 g_RStage16Entity28Anim1[8] = {
    2, 4, 2, 4, 0, 0, 0, 0,
};

u8 g_RStage16WightAnim4[10] = {
    2, 0x12, 2, 0x13, 2, 0x12, 2, 0x13, 0, 0,
};

u16 g_RStage16WightParams[4] = {
    0x40,
    0xE0,
    0x200,
    0x180,
};

s16 g_RStage16Entity28VelocityTable[24] = {
    4,  3,  2,  2,  2,  1,  0,  0,  -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -2, -2, -2, -2,
};

s16 g_RStage16WightInitOffset[3] = {
    0,
    23,
    0,
};
