// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

s16 g_Stage15HumanFaceTreeSensors[8] = {0, 32, 0, 4, 16, -4, -32, 0};

s16 g_Stage15HumanFaceTreeWallSensors[4] = {0, 32, 8, 0};

u8 g_Stage15HumanFaceTreeAnim0[16] = {
    0x0E, 0x0C, 0x0E, 0x0D, 0x0E, 0x0E, 0x0E, 0x0F,
    0x0E, 0x0E, 0x0E, 0x0D, 0x0E, 0x0C, 0xFF, 0x00,
};

u8 g_Stage15HumanFaceTreeAnim1[16] = {
    0x0E, 0x10, 0x0E, 0x11, 0x0E, 0x12, 0x0E, 0x13,
    0x0E, 0x12, 0x0E, 0x11, 0x0E, 0x10, 0xFF, 0x00,
};

u8* g_Stage15HumanFaceTreeAnimSet0[2] = {
    g_Stage15HumanFaceTreeAnim0, g_Stage15HumanFaceTreeAnim1};

u8 g_Stage15HumanFaceTreeAnim2[12] = {
    0x12, 0x0C, 0x12, 0x0D, 0x12, 0x0E, 0x62, 0x0F, 0x12, 0x14, 0xFF, 0x00,
};

u8 g_Stage15HumanFaceTreeAnim3[12] = {
    0x12, 0x10, 0x12, 0x11, 0x12, 0x12, 0x62, 0x13, 0x12, 0x17, 0xFF, 0x00,
};

u8* g_Stage15HumanFaceTreeAnimSet1[2] = {
    g_Stage15HumanFaceTreeAnim2, g_Stage15HumanFaceTreeAnim3};

u8 g_Stage15HumanFaceTreeAnim4[8] = {
    0x04, 0x45, 0x04, 0x46, 0x04, 0x47, 0xFF, 0x00,
};

u8 g_Stage15HumanFaceTreeAnim5[8] = {
    0x04, 0x48, 0x04, 0x49, 0xFF, 0x00, 0x00, 0x00,
};

u8* g_Stage15HumanFaceTreeAnimSet2[2] = {
    g_Stage15HumanFaceTreeAnim4, g_Stage15HumanFaceTreeAnim5};

u8 g_Stage15HumanFaceTreeAnim6[8] = {
    0x04, 0x4C, 0x04, 0x4D, 0x04, 0x4E, 0xFF, 0x00,
};

u8 g_Stage15HumanFaceTreeAnim7[8] = {
    0x04, 0x4F, 0x04, 0x50, 0x04, 0x51, 0xFF, 0x00,
};

u8* g_Stage15HumanFaceTreeAnimSet3[2] = {
    g_Stage15HumanFaceTreeAnim6, g_Stage15HumanFaceTreeAnim7};

s16 g_Stage15HumanFaceTreeFramesByDistance[22] = {
    -140, 1,  -100, 2,  -70, 3,   -28, 4,   -10, 5,     10,
    6,    28, 7,    70, 8,   100, 9,   140, 10,  32767, 11};

Point16 g_Stage15HumanFaceTreePartPolar[8] = {
    {83, -368}, {82, -256}, {82, -160}, {81, -80},
    {80, 80},   {77, 176},  {80, 320},  {88, 384},
};

s8 g_Stage15HumanFaceTreeHitboxes[44] = {
    -22, -30, 14,  40,  -22, -30, 14,  40,  -14, -30, 10,  40,  -14, -30, 10,
    40,  -2,  -30, 4,   40,  0,   -30, 4,   40,  2,   -30, 4,   40,  14,  -30,
    10,  40,  14,  -30, 10,  40,  22,  -30, 14,  40,  22,  -30, 14,  40,
};
