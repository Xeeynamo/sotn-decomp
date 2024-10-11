// SPDX-License-Identifier: AGPL-3.0-or-later
#include "servant.h"

// sprite data
Sprite g_BatSpriteData[] = {
    {-4, -4, 8, 8, 0x144, 0x78, 8, 0, 16, 8},
    {-4, -4, 8, 8, 0x144, 0x78, 120, 8, 128, 16},
    {-4, -4, 8, 8, 0x144, 0x78, 228, 135, 236, 143},
    {-4, -4, 8, 8, 0x144, 0x78, 80, 0, 88, 8},
};

// ability by level table
// 0 - attack delay (frames?)
// 1 - max angle of attack
// 2 - additional bat count
// 3 - min enemy HP
// 4 - make bad attacks (attack invincible?)
s32 g_BatAbilityStats[][5] = {
    {90, 64, 0, 128, 1}, //
    {90, 96, 0, 128, 1}, //
    {60, 128, 1, 96, 1}, //
    {60, 160, 1, 96, 0}, //
    {60, 192, 2, 64, 0}, //
    {60, 224, 2, 64, 0}, //
    {45, 256, 2, 32, 0}, //
    {45, 288, 3, 32, 0}, //
    {30, 320, 3, 16, 0}, //
    {30, 352, 3, 16, 0}, //
};

// Bat specific clut
u16 g_BatClut[] = {
    0x0000, 0xFC00, 0xF400, 0xEC00, 0xE400, 0xDC00, 0xD400, 0xCC00,
    0xC400, 0xBC00, 0xB400, 0xAC00, 0xA400, 0x9C00, 0x9400, 0x8C00,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7FFF, 0x0000,
    0x0000, 0x000C, 0x0C76, 0x14BF, 0x295F, 0x39FF, 0x463F, 0x7BDE,
};
