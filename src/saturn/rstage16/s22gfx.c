// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

u16 g_RStage16SpriteBank22Palette[34] = {
    0x0002, 0xAC60, 0x9084, 0xA508, 0xB9AD, 0xCE51, 0xE2F6, 0xF79B, 0xBDAB,
    0x984E, 0x8857, 0xA59F, 0x80F0, 0x921A, 0x9973, 0x8019, 0x8421, 0xAC60,
    0x8864, 0x8CCA, 0x9572, 0x99B8, 0xA27B, 0xC6FF, 0xAD0F, 0x8502, 0x9DC1,
    0xDA82, 0xB9CA, 0xCE73, 0xE339, 0x8300, 0x8421, 0x0000,
};

SaturnSpriteFrameHeader g_RStage16SpriteBank22Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame4 g_RStage16SpriteBank22Frame1 = {
    {0x0400, 0x0000},
    {
        {0x0000, 5, 9, 0x0000},
        {0x0000, -6, -2, 0x0001},
        {0x0000, -3, -11, 0x0002},
        {0x0000, 0, -5, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank22Frame2 = {
    {0x0400, 0x0000},
    {
        {0x0000, 7, 9, 0x0004},
        {0x0000, -7, -3, 0x0001},
        {0x0000, -3, -12, 0x0002},
        {0x0000, 1, -6, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank22Frame3 = {
    {0x0400, 0x0000},
    {
        {0x0000, 5, 7, 0x0005},
        {0x0000, -8, -4, 0x0001},
        {0x0000, -3, -13, 0x0002},
        {0x0000, 1, -7, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank22Frame4 = {
    {0x0400, 0x0000},
    {
        {0x0000, 5, 9, 0x0006},
        {0x0000, -9, -2, 0x0001},
        {0x0000, -3, -11, 0x0002},
        {0x0000, 2, -5, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank22Frame5 = {
    {0x0400, 0x0000},
    {
        {0x0000, 0, 9, 0x0007},
        {0x0000, -8, -3, 0x0001},
        {0x0000, -3, -12, 0x0002},
        {0x0000, 1, -6, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank22Frame6 = {
    {0x0400, 0x0000},
    {
        {0x0000, 2, 9, 0x0008},
        {0x0000, -7, -4, 0x0001},
        {0x0000, -3, -13, 0x0002},
        {0x0000, 1, -7, 0x0003},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBank22Frame7 = {
    {0x0300, 0x0000},
    {
        {0x0000, 5, 7, 0x0005},
        {0x0000, -3, -13, 0x0002},
        {0x0000, -4, -7, 0x0003},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBank22Frame8 = {
    {0x0300, 0x0000},
    {
        {0x0000, 5, 9, 0x0006},
        {0x0000, -3, -11, 0x0002},
        {0x0000, -8, -5, 0x0003},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame9 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 0, 0x0009},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame10 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -1, 0x000A},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame11 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -2, 0x000B},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame12 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 1, 0x000C},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank22Frame13 = {
    {0x0400, 0x0000},
    {
        {0x0000, 4, 10, 0x000D},
        {0x0000, -9, -2, 0x0001},
        {0x0000, -4, -9, 0x000E},
        {0x0000, -1, -3, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank22Frame14 = {
    {0x0400, 0x0000},
    {
        {0x0000, 3, 11, 0x000F},
        {0x0000, -14, -6, 0x0001},
        {0x0000, -4, -7, 0x000E},
        {0x0000, -3, -4, 0x0003},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame15 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -1, 0x0010},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame16 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 0x0011},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame17 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 2, 0x0003},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame18 = {
    {0x0100, 0x0000},
    {
        {0x0010, 4, 1, 0x0003},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame19 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 1, 0x0012},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame20 = {
    {0x0100, 0x0000},
    {
        {0x0010, -1, 1, 0x0012},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank22Frame21 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 0, 0x0013},
    },
};

SaturnSpriteFrameHeader* g_RStage16SpriteBank22Frames[22] = {
    &g_RStage16SpriteBank22Frame0,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame1,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame2,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame3,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame4,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame5,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame6,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame7,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame8,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame9,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame10,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame11,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame12,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame13,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame14,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame15,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame16,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame17,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame18,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame19,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame20,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank22Frame21,
};

SaturnSpriteImage g_RStage16SpriteBank22Images[21] = {
    {0x0C, 0x0D, 0x0000}, {0x08, 0x02, 0x0028}, {0x08, 0x09, 0x002C},
    {0x08, 0x06, 0x0040}, {0x0C, 0x0D, 0x004C}, {0x08, 0x0D, 0x0074},
    {0x08, 0x0D, 0x0090}, {0x08, 0x0D, 0x00AC}, {0x0C, 0x0D, 0x00C8},
    {0x10, 0x15, 0x00F0}, {0x14, 0x17, 0x0144}, {0x10, 0x17, 0x01B8},
    {0x14, 0x15, 0x0214}, {0x0C, 0x0C, 0x0280}, {0x08, 0x09, 0x02A4},
    {0x0C, 0x0B, 0x02B8}, {0x08, 0x06, 0x02DC}, {0x08, 0x07, 0x02E8},
    {0x04, 0x0B, 0x02F8}, {0x08, 0x07, 0x0304}, {0x00, 0x00, 0x0314},
};
