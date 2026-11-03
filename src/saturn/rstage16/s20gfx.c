// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

u16 g_RStage16SpriteBankWightPalette[50] = {
    0x0003, 0x8000, 0x8008, 0x800A, 0x800E, 0x8012, 0x8056, 0x80DA, 0x811F,
    0x815F, 0x819F, 0x81DF, 0x821F, 0x83E0, 0x83E0, 0x83E0, 0xFFFF, 0x8000,
    0x8800, 0x9020, 0x9841, 0xA082, 0xA904, 0xBDE6, 0xCAC8, 0x83E0, 0x8004,
    0x8C08, 0x980A, 0xA40C, 0xA096, 0xB17A, 0xCA5F, 0xA94B, 0x90EA, 0x9DB2,
    0xB255, 0xCAD9, 0x83FF, 0x8428, 0x883A, 0x843A, 0x8428, 0x8421, 0xC58C,
    0xDA10, 0xE294, 0xEF18, 0xFB9B, 0x0000,
};

SaturnSpriteFrameHeader g_RStage16SpriteBankWightFrame0 = {0x0000, 0x0000};

SaturnSpriteFrame3 g_RStage16SpriteBankWightFrame1 = {
    {0x0300, 0x0000},
    {
        {0x0000, 3, -3, 0x0000},
        {0x0100, 4, 11, 0x0001},
        {0x0100, -3, -8, 0x0002},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBankWightFrame2 = {
    {0x0300, 0x0000},
    {
        {0x0000, 5, -2, 0x0000},
        {0x0100, 9, 11, 0x0003},
        {0x0100, 1, -9, 0x0004},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBankWightFrame3 = {
    {0x0300, 0x0000},
    {
        {0x0000, 4, -2, 0x0000},
        {0x0100, 2, -10, 0x0005},
        {0x0100, 6, 10, 0x0006},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame4 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 14, 0x0000},
        {0x0100, 0, 5, 0x0004},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame5 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 15, 0x0000},
        {0x0100, 0, 7, 0x0007},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame6 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 16, 0x0000},
        {0x0100, 1, 8, 0x0008},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame7 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 0, 0x0000},
        {0x0100, 4, 11, 0x0001},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, -1, 0x0000},
        {0x0100, 9, 11, 0x0003},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame9 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, -2, 0x0000},
        {0x0100, 6, 10, 0x0006},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame10 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -1, 0x0009},
        {0x0100, 4, 11, 0x0001},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBankWightFrame11 = {
    {0x0300, 0x0000},
    {
        {0x0000, 4, -4, 0x0000},
        {0x0100, 4, 11, 0x0001},
        {0x0100, 1, -12, 0x0004},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBankWightFrame12 = {
    {0x0300, 0x0000},
    {
        {0x0000, 4, -7, 0x000A},
        {0x0100, 4, 11, 0x0001},
        {0x0100, 0, -18, 0x0007},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBankWightFrame13 = {
    {0x0300, 0x0000},
    {
        {0x0000, 4, -9, 0x000B},
        {0x0100, 4, 11, 0x0001},
        {0x0100, 0, -21, 0x0008},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBankWightFrame14 = {
    {0x0300, 0x0000},
    {
        {0x0000, 4, -11, 0x000C},
        {0x0100, 4, 11, 0x0001},
        {0x0100, 0, -26, 0x0007},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBankWightFrame15 = {
    {0x0300, 0x0000},
    {
        {0x0000, 4, -11, 0x000D},
        {0x0100, 4, 11, 0x0001},
        {0x0100, 1, -27, 0x0004},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame16 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 12, 0x0000},
        {0x0100, 0, 5, 0x0007},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame17 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 11, 0x0000},
        {0x0100, 0, 5, 0x0007},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame18 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 0, 0x0000},
        {0x0100, 4, 11, 0x0001},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWightFrame19 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 1, 0x0000},
        {0x0100, 4, 11, 0x0001},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBankWightFrame20 = {
    {0x0400, 0x0000},
    {
        {0x0200, 14, -10, 0x000E},
        {0x0200, 11, -9, 0x000E},
        {0x0200, 13, -7, 0x000E},
        {0x0200, 11, -7, 0x000E},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBankWightFrame21 = {
    {0x0400, 0x0000},
    {
        {0x0200, 16, -13, 0x000E},
        {0x0200, 7, -11, 0x000E},
        {0x0200, 15, -4, 0x000E},
        {0x0200, 9, -5, 0x000E},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWightFrame22 = {
    {0x0500, 0x0000},
    {
        {0x0210, 14, -15, 0x000E},
        {0x0210, -2, -14, 0x000E},
        {0x0200, 17, -2, 0x000E},
        {0x0200, 5, -2, 0x000E},
        {0x0220, 11, -11, 0x000E},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWightFrame23 = {
    {0x0500, 0x0000},
    {
        {0x0200, 23, -20, 0x000E},
        {0x0200, 0, -18, 0x000E},
        {0x0210, 12, 1, 0x000E},
        {0x0230, -3, -4, 0x000E},
        {0x0220, 11, -14, 0x000E},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWightFrame24 = {
    {0x0500, 0x0000},
    {
        {0x0210, 20, -16, 0x000E},
        {0x0220, -2, -19, 0x000E},
        {0x0200, 24, 1, 0x000E},
        {0x0200, 4, -2, 0x000E},
        {0x0220, 11, -13, 0x000E},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBankWightFrame25 = {
    {0x0400, 0x0000},
    {
        {0x0210, 15, -13, 0x000E},
        {0x0200, 1, -11, 0x000E},
        {0x0220, 24, -1, 0x000E},
        {0x0210, -5, 3, 0x000E},
    },
};

SaturnSpriteFrameHeader* g_RStage16SpriteBankWightFrames[26] = {
    &g_RStage16SpriteBankWightFrame0,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame1,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame2,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame3,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame4,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame5,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame6,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame7,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame8,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame9,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame10,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame11,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame12,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame13,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame14,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame15,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame16,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame17,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame18,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame19,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame20,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame21,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame22,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame23,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame24,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWightFrame25,
};

SaturnSpriteImage g_RStage16SpriteBankWightImages[16] = {
    {0x08, 0x07, 0x0000}, {0x14, 0x0D, 0x0010}, {0x0C, 0x0B, 0x0054},
    {0x10, 0x0E, 0x0078}, {0x10, 0x0B, 0x00B0}, {0x14, 0x0B, 0x00DC},
    {0x0C, 0x0F, 0x0114}, {0x10, 0x0D, 0x0144}, {0x10, 0x0D, 0x0178},
    {0x08, 0x07, 0x01AC}, {0x08, 0x0B, 0x01BC}, {0x08, 0x0D, 0x01D4},
    {0x08, 0x0F, 0x01F0}, {0x08, 0x0F, 0x0210}, {0x0C, 0x05, 0x0230},
    {0x00, 0x00, 0x0240},
};
