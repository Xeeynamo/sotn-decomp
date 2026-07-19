// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    u8 slot0[14];
    u8 slot1[26];
    u8 slot2[30];
    u8 slot3[30];
    u8 slot4[14];
    u8 slot5[26];
    u8 slot6[30];
    u8 slot7[30];
    u8 slot8[18];
    u16 padding;
    u8* slots[9];
} AxeKnightSpriteAnimationData;

AxeKnightSpriteAnimationData g_Stage02AxeKnightSpriteAnimations = {
    {26, 1, 10, 2, 10, 3, 26, 4, 10, 3, 10, 2, -1, -1},
    {10, 1, 10, 2, 10, 3, 10, 4, 8, 5, 8, 6, 8,
     7,  8, 8,  10, 9, 4,  10, 4, 11, 4, 12, -1, -1},
    {10, 1, 10, 2, 10, 3, 10, 4, 8, 5, 8, 6, 8,  7,  8,
     13, 8, 14, 1,  15, 1,  16, 1, 17, 32, 18, 8,  19, -1, -1},
    {10, 1, 10, 2, 10, 3, 10, 4, 8, 5, 8, 6, 8,  7,  8,
     13, 8, 14, 2,  15, 2,  20, 2, 21, 32, 22, 8,  23, -1, -1},
    {26, 24, 10, 25, 10, 26, 26, 27, 10, 26, 10, 25, -1, -1},
    {10, 24, 10, 25, 10, 26, 10, 27, 8, 28, 8, 29, 8,
     30, 8,  31, 10, 32, 4,  33, 4, 34, 4, 35, -1, -1},
    {10, 24, 10, 25, 10, 26, 10, 27, 8, 28, 8, 29, 8,  30, 8,
     36, 8,  37, 2,  38, 2,  39, 2, 40, 32, 41, 8,  42, -1, -1},
    {10, 24, 10, 25, 10, 26, 10, 27, 8, 28, 8, 29, 8,  30, 8,
     36, 8,  37, 2,  38, 2,  43, 2, 44, 32, 45, 8,  46, -1, -1},
    {8, 47, 8, 48, 8, 49, 8, 50, 8, 51, 8, 52, 8, 53, 8, 54, -1, -1},
    0,
    {g_Stage02AxeKnightSpriteAnimations.slot0,
     g_Stage02AxeKnightSpriteAnimations.slot1,
     g_Stage02AxeKnightSpriteAnimations.slot2,
     g_Stage02AxeKnightSpriteAnimations.slot3,
     g_Stage02AxeKnightSpriteAnimations.slot4,
     g_Stage02AxeKnightSpriteAnimations.slot5,
     g_Stage02AxeKnightSpriteAnimations.slot6,
     g_Stage02AxeKnightSpriteAnimations.slot7,
     g_Stage02AxeKnightSpriteAnimations.slot8},
};
