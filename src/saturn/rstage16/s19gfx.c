// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

u16 g_RStage16SpriteBankWraithPalette[34] = {
    0x0002, 0xA145, 0xEB7B, 0xDAB5, 0xCA10, 0xB96B, 0xA8C6, 0xA0A5, 0x9884,
    0x9463, 0x8C42, 0x8421, 0x8000, 0x805F, 0x8016, 0x840C, 0x8803, 0xA123,
    0xFFFF, 0xF79C, 0xEB18, 0xE2B5, 0xD631, 0xCDCE, 0xBD6B, 0xB108, 0xA4A5,
    0x9863, 0x8C21, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000,
};

SaturnSpriteFrameHeader g_RStage16SpriteBankWraithFrame0 = {0x0000, 0x0000};

SaturnSpriteFrame2 g_RStage16SpriteBankWraithFrame1 = {
    {0x0200, 0x0000},
    {
        {0x0000, 1, -26, 0x0000},
        {0x0000, 7, -21, 0x0001},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBankWraithFrame2 = {
    {0x0200, 0x0000},
    {
        {0x0000, 1, -26, 0x0000},
        {0x0000, 8, -22, 0x0001},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame3 = {
    {0x0500, 0x0000},
    {
        {0x0000, -6, -26, 0x0002},
        {0x0000, 2, -26, 0x0003},
        {0x0000, 12, -22, 0x0004},
        {0x0000, 14, -18, 0x0005},
        {0x0000, -13, -21, 0x0006},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame4 = {
    {0x0500, 0x0000},
    {
        {0x0000, -8, -28, 0x0002},
        {0x0000, 2, -26, 0x0003},
        {0x0000, 12, -24, 0x0004},
        {0x0000, 14, -21, 0x0005},
        {0x0000, -16, -23, 0x0006},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame5 = {
    {0x0500, 0x0000},
    {
        {0x0000, -15, -36, 0x0007},
        {0x0000, 1, -26, 0x0008},
        {0x0000, 12, -35, 0x0009},
        {0x0000, -22, -46, 0x000A},
        {0x0000, 16, -45, 0x000B},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame6 = {
    {0x0500, 0x0000},
    {
        {0x0000, -15, -38, 0x0007},
        {0x0000, 1, -26, 0x0008},
        {0x0000, 13, -36, 0x0009},
        {0x0000, -21, -50, 0x000A},
        {0x0000, 17, -49, 0x000B},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame7 = {
    {0x0500, 0x0000},
    {
        {0x0000, -26, -64, 0x000C},
        {0x0000, -19, -41, 0x000D},
        {0x0000, -3, -26, 0x000E},
        {0x0000, 15, -42, 0x000F},
        {0x0000, 19, -62, 0x0010},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame8 = {
    {0x0500, 0x0000},
    {
        {0x0000, -24, -62, 0x000C},
        {0x0000, -19, -41, 0x000D},
        {0x0000, -3, -26, 0x000E},
        {0x0000, 15, -42, 0x000F},
        {0x0000, 17, -60, 0x0010},
    },
};

SaturnSpriteFrame6 g_RStage16SpriteBankWraithFrame9 = {
    {0x0600, 0x0000},
    {
        {0x0000, -14, -39, 0x0011},
        {0x0000, -14, -39, 0x0011},
        {0x0000, 1, -26, 0x0008},
        {0x0000, 15, -40, 0x0012},
        {0x0000, -24, -62, 0x000C},
        {0x0000, 17, -60, 0x0010},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame10 = {
    {0x0500, 0x0000},
    {
        {0x0000, -14, -39, 0x0011},
        {0x0000, -1, -25, 0x0013},
        {0x0000, 15, -40, 0x0012},
        {0x0000, -24, -62, 0x000C},
        {0x0000, 17, -60, 0x0010},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame11 = {
    {0x0500, 0x0000},
    {
        {0x0000, -14, -39, 0x0011},
        {0x0000, 6, -26, 0x0014},
        {0x0000, 15, -40, 0x0012},
        {0x0000, -24, -62, 0x000C},
        {0x0000, 17, -60, 0x0010},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame12 = {
    {0x0500, 0x0000},
    {
        {0x0000, -13, -38, 0x0011},
        {0x0000, 6, -26, 0x0014},
        {0x0000, 14, -39, 0x0012},
        {0x0000, -24, -60, 0x000C},
        {0x0000, 16, -58, 0x0010},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame13 = {
    {0x0500, 0x0000},
    {
        {0x0000, -28, -56, 0x0015},
        {0x0000, -9, -38, 0x0016},
        {0x0000, 10, -25, 0x0017},
        {0x0000, 16, -40, 0x0018},
        {0x0000, 1, -57, 0x0019},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame14 = {
    {0x0500, 0x0000},
    {
        {0x0000, -30, -53, 0x0015},
        {0x0000, -10, -37, 0x0016},
        {0x0000, 10, -25, 0x0017},
        {0x0000, 9, -37, 0x0018},
        {0x0000, -6, -54, 0x0019},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame15 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -33, 0x001A},
        {0x0000, 11, -24, 0x001B},
        {0x0000, 0, -32, 0x001C},
        {0x0000, -31, -44, 0x001D},
        {0x0000, -20, -43, 0x001E},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame16 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -30, 0x001A},
        {0x0000, 11, -24, 0x001B},
        {0x0000, -2, -31, 0x001C},
        {0x0000, -31, -41, 0x001D},
        {0x0000, -22, -40, 0x001E},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame17 = {
    {0x0500, 0x0000},
    {
        {0x0000, -10, -30, 0x001F},
        {0x0000, 15, -25, 0x0020},
        {0x0000, -3, -27, 0x0021},
        {0x0000, -32, -38, 0x001D},
        {0x0000, -24, -37, 0x0022},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame18 = {
    {0x0500, 0x0000},
    {
        {0x0000, -10, -29, 0x001F},
        {0x0000, 15, -25, 0x0020},
        {0x0000, -3, -26, 0x0021},
        {0x0000, -32, -37, 0x001D},
        {0x0000, -24, -35, 0x0022},
    },
};

SaturnSpriteFrame6 g_RStage16SpriteBankWraithFrame19 = {
    {0x0600, 0x0000},
    {
        {0x0000, 16, -18, 0x0023},
        {0x0000, 2, -42, 0x0024},
        {0x0000, -5, -24, 0x0025},
        {0x0000, -32, -37, 0x001D},
        {0x0000, -24, -35, 0x0022},
        {0x0000, 15, -44, 0x0026},
    },
};

SaturnSpriteFrame6 g_RStage16SpriteBankWraithFrame20 = {
    {0x0600, 0x0000},
    {
        {0x0000, 16, -18, 0x0027},
        {0x0000, 2, -42, 0x0024},
        {0x0000, -5, -24, 0x0028},
        {0x0000, -32, -36, 0x001D},
        {0x0000, -25, -34, 0x0022},
        {0x0000, 15, -43, 0x0026},
    },
};

SaturnSpriteFrame6 g_RStage16SpriteBankWraithFrame21 = {
    {0x0600, 0x0000},
    {
        {0x0000, 11, -18, 0x0029},
        {0x0000, 2, -42, 0x0024},
        {0x0000, -5, -24, 0x002A},
        {0x0000, -32, -35, 0x001D},
        {0x0000, -24, -33, 0x0022},
        {0x0000, 16, -43, 0x0026},
    },
};

SaturnSpriteFrame6 g_RStage16SpriteBankWraithFrame22 = {
    {0x0600, 0x0000},
    {
        {0x0000, 16, -18, 0x002B},
        {0x0000, 2, -42, 0x0024},
        {0x0000, -5, -23, 0x002C},
        {0x0000, -33, -36, 0x001D},
        {0x0000, -24, -34, 0x0022},
        {0x0000, 16, -44, 0x0026},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame23 = {
    {0x0500, 0x0000},
    {
        {0x0000, -31, -56, 0x002D},
        {0x0000, -9, -38, 0x0016},
        {0x0000, 10, -25, 0x0017},
        {0x0000, 16, -40, 0x0018},
        {0x0000, 0, -57, 0x002E},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame24 = {
    {0x0500, 0x0000},
    {
        {0x0000, -33, -54, 0x002D},
        {0x0000, -10, -37, 0x0016},
        {0x0000, 10, -25, 0x0017},
        {0x0000, 9, -37, 0x0018},
        {0x0000, -8, -55, 0x002E},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame25 = {
    {0x0500, 0x0000},
    {
        {0x0100, -45, -45, 0x002F},
        {0x0000, -11, -33, 0x001A},
        {0x0000, 11, -24, 0x001B},
        {0x0000, 0, -32, 0x001C},
        {0x0100, -30, -46, 0x0030},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame26 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -30, 0x001A},
        {0x0000, 11, -24, 0x001B},
        {0x0000, -2, -31, 0x001C},
        {0x0100, -48, -41, 0x002F},
        {0x0100, -32, -43, 0x0030},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame27 = {
    {0x0500, 0x0000},
    {
        {0x0100, -53, -27, 0x0031},
        {0x0000, -10, -30, 0x001F},
        {0x0000, 15, -25, 0x0020},
        {0x0000, -1, -27, 0x0021},
        {0x0100, -44, -24, 0x0032},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame28 = {
    {0x0500, 0x0000},
    {
        {0x0100, -49, -22, 0x0031},
        {0x0000, -10, -29, 0x001F},
        {0x0000, 15, -25, 0x0020},
        {0x0000, -3, -26, 0x0021},
        {0x0100, -46, -20, 0x0032},
    },
};

SaturnSpriteFrame7 g_RStage16SpriteBankWraithFrame29 = {
    {0x0700, 0x0000},
    {
        {0x0000, -10, -28, 0x001F},
        {0x0000, 2, -42, 0x0024},
        {0x0000, 15, -18, 0x0023},
        {0x0100, -49, -21, 0x0031},
        {0x0000, -2, -26, 0x0021},
        {0x0100, -45, -20, 0x0032},
        {0x0000, 15, -43, 0x0026},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame30 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -27, 0x0033},
        {0x0000, 11, -24, 0x001B},
        {0x0000, -5, -26, 0x0033},
        {0x0000, -32, -37, 0x001D},
        {0x0000, -24, -35, 0x0022},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame31 = {
    {0x0500, 0x0000},
    {
        {0x0000, -12, -28, 0x0033},
        {0x0000, 10, -25, 0x0017},
        {0x0000, -6, -27, 0x0033},
        {0x0000, -31, -36, 0x001D},
        {0x0000, -25, -34, 0x0022},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame32 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -29, 0x0033},
        {0x0000, 6, -26, 0x0014},
        {0x0000, -5, -28, 0x0033},
        {0x0000, -29, -37, 0x0034},
        {0x0000, -23, -35, 0x0035},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame33 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -29, 0x0036},
        {0x0000, -2, -25, 0x0037},
        {0x0000, -5, -28, 0x0036},
        {0x0000, -26, -34, 0x0038},
        {0x0000, -21, -33, 0x0039},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBankWraithFrame34 = {
    {0x0300, 0x0000},
    {
        {0x0000, -11, -29, 0x0036},
        {0x0000, -5, -24, 0x003A},
        {0x0000, -5, -28, 0x0036},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBankWraithFrame35 = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, -21, 0x003B},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBankWraithFrame36 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -24, 0x003C},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBankWraithFrame37 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -6, 0x003C},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame38 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -29, 0x0033},
        {0x0000, 6, -26, 0x0014},
        {0x0000, -5, -28, 0x0033},
        {0x0000, -30, -36, 0x001D},
        {0x0000, -24, -34, 0x0022},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame39 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -29, 0x0036},
        {0x0000, -2, -25, 0x0037},
        {0x0000, -5, -28, 0x0036},
        {0x0000, -31, -36, 0x001D},
        {0x0000, -25, -34, 0x0022},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBankWraithFrame40 = {
    {0x0500, 0x0000},
    {
        {0x0000, -11, -29, 0x0036},
        {0x0000, -5, -24, 0x003A},
        {0x0000, -5, -28, 0x0036},
        {0x0000, -31, -36, 0x001D},
        {0x0000, -25, -34, 0x0022},
    },
};

SaturnSpriteFrame7 g_RStage16SpriteBankWraithFrame41 = {
    {0x0700, 0x0000},
    {
        {0x0000, -12, -29, 0x001A},
        {0x0100, -49, -40, 0x002F},
        {0x0000, 2, -42, 0x0024},
        {0x0000, 15, -44, 0x0026},
        {0x0000, 16, -18, 0x0023},
        {0x0000, -1, -32, 0x001C},
        {0x0100, -31, -44, 0x0030},
    },
};

SaturnSpriteFrame7 g_RStage16SpriteBankWraithFrame42 = {
    {0x0700, 0x0000},
    {
        {0x0100, -49, -41, 0x002F},
        {0x0000, -12, -30, 0x001A},
        {0x0000, 2, -42, 0x0024},
        {0x0000, 15, -43, 0x0026},
        {0x0000, 16, -18, 0x0027},
        {0x0000, 0, -31, 0x001C},
        {0x0100, -30, -43, 0x0030},
    },
};

SaturnSpriteFrame7 g_RStage16SpriteBankWraithFrame43 = {
    {0x0700, 0x0000},
    {
        {0x0100, -49, -42, 0x002F},
        {0x0000, -12, -31, 0x001A},
        {0x0000, 2, -42, 0x0024},
        {0x0000, 16, -43, 0x0026},
        {0x0000, 11, -18, 0x0029},
        {0x0000, -1, -31, 0x001C},
        {0x0100, -31, -42, 0x0030},
    },
};

SaturnSpriteFrame7 g_RStage16SpriteBankWraithFrame44 = {
    {0x0700, 0x0000},
    {
        {0x0100, -48, -41, 0x002F},
        {0x0000, -11, -30, 0x001A},
        {0x0000, 2, -42, 0x0024},
        {0x0000, 16, -44, 0x0026},
        {0x0000, 16, -18, 0x002B},
        {0x0000, -2, -33, 0x001C},
        {0x0100, -32, -43, 0x0030},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBankWraithFrame45 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -6, 0x003C},
    },
};

SaturnSpriteFrameHeader* g_RStage16SpriteBankWraithFrames[46] = {
    &g_RStage16SpriteBankWraithFrame0,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame1,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame2,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame3,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame4,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame5,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame6,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame7,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame8,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame9,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame10,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame11,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame12,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame13,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame14,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame15,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame16,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame17,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame18,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame19,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame20,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame21,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame22,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame23,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame24,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame25,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame26,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame27,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame28,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame29,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame30,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame31,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame32,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame33,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame34,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame35,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame36,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame37,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame38,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame39,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame40,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame41,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame42,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame43,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame44,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBankWraithFrame45,
};

SaturnSpriteImage g_RStage16SpriteBankWraithImages[62] = {
    {0x0C, 0x1D, 0x0000}, {0x08, 0x13, 0x0058}, {0x0C, 0x10, 0x0080},
    {0x10, 0x1D, 0x00B0}, {0x0C, 0x11, 0x0124}, {0x04, 0x04, 0x0158},
    {0x04, 0x03, 0x015C}, {0x10, 0x0D, 0x0160}, {0x14, 0x1D, 0x0194},
    {0x0C, 0x11, 0x0228}, {0x08, 0x05, 0x025C}, {0x04, 0x06, 0x0268},
    {0x08, 0x0B, 0x0270}, {0x10, 0x0E, 0x0288}, {0x18, 0x1D, 0x02C0},
    {0x0C, 0x10, 0x0370}, {0x0C, 0x0E, 0x03A0}, {0x10, 0x0E, 0x03CC},
    {0x0C, 0x10, 0x0404}, {0x14, 0x1D, 0x0434}, {0x14, 0x1D, 0x04C8},
    {0x0C, 0x0A, 0x055C}, {0x10, 0x0C, 0x057C}, {0x14, 0x1D, 0x05AC},
    {0x10, 0x0D, 0x0640}, {0x08, 0x09, 0x0674}, {0x10, 0x0B, 0x0688},
    {0x14, 0x1E, 0x06B4}, {0x10, 0x0C, 0x074C}, {0x0C, 0x0A, 0x077C},
    {0x08, 0x0A, 0x079C}, {0x10, 0x0E, 0x07B0}, {0x18, 0x1D, 0x07E8},
    {0x10, 0x0D, 0x0898}, {0x0C, 0x0A, 0x08CC}, {0x18, 0x15, 0x08EC},
    {0x0C, 0x0C, 0x096C}, {0x14, 0x0B, 0x0990}, {0x04, 0x04, 0x09C8},
    {0x18, 0x15, 0x09CC}, {0x14, 0x0B, 0x0A4C}, {0x14, 0x15, 0x0A84},
    {0x14, 0x0B, 0x0AF0}, {0x18, 0x15, 0x0B28}, {0x14, 0x0C, 0x0BA8},
    {0x0C, 0x0C, 0x0BE4}, {0x0C, 0x0C, 0x0C08}, {0x18, 0x11, 0x0C2C},
    {0x14, 0x11, 0x0C94}, {0x20, 0x14, 0x0CEC}, {0x20, 0x13, 0x0D8C},
    {0x10, 0x0D, 0x0E24}, {0x0C, 0x06, 0x0E58}, {0x0C, 0x06, 0x0E6C},
    {0x14, 0x0D, 0x0E80}, {0x14, 0x1D, 0x0EC4}, {0x08, 0x03, 0x0F58},
    {0x08, 0x03, 0x0F60}, {0x18, 0x1C, 0x0F68}, {0x18, 0x1A, 0x1010},
    {0x18, 0x14, 0x10AC}, {0x00, 0x00, 0x1124},
};
