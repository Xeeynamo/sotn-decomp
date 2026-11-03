// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "rstage16.h"

u16 g_RStage16SpriteBank23Palette[66] = {
    0x0004, 0x8C4C, 0x8C42, 0x88E1, 0x8581, 0x8620, 0x82C0, 0x8380, 0xA125,
    0xA48C, 0xC400, 0xFC6B, 0xFDCD, 0xFF14, 0xFF9F, 0x801F, 0x8421, 0x8C4C,
    0x8D62, 0xA5E5, 0xC289, 0xDB0D, 0xF7B1, 0xFFFA, 0xA125, 0xA48C, 0xC400,
    0xFC6B, 0xFDCD, 0xFF14, 0xFF9F, 0x801F, 0x8421, 0x8160, 0x8000, 0xA000,
    0xA800, 0xB001, 0xB802, 0xC003, 0xC804, 0xE025, 0xFC6B, 0xFD0C, 0xFDCD,
    0xFE70, 0xFF14, 0xFF5A, 0xFF9F, 0x8160, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0xA000, 0xC400, 0xE025, 0xFC6B, 0xFD0C, 0xFDCD, 0xFE70, 0xFF14,
    0xFF5A, 0xFF9F, 0x0000,
};

SaturnSpriteFrameHeader g_RStage16SpriteBank23Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame1 = {
    {0x0400, 0x0000},
    {
        {0x0000, 5, 9, 0x0000},
        {0x0000, -8, -2, 0x0001},
        {0x0000, 0, -10, 0x0002},
        {0x0000, 5, -6, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame2 = {
    {0x0400, 0x0000},
    {
        {0x0000, 6, 10, 0x0004},
        {0x0000, -9, -3, 0x0001},
        {0x0000, 0, -11, 0x0002},
        {0x0000, 6, -7, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame3 = {
    {0x0400, 0x0000},
    {
        {0x0000, 3, 11, 0x0005},
        {0x0000, -10, -4, 0x0001},
        {0x0000, 0, -12, 0x0002},
        {0x0000, 6, -8, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame4 = {
    {0x0400, 0x0000},
    {
        {0x0000, 4, 10, 0x0006},
        {0x0000, -11, -2, 0x0001},
        {0x0000, 0, -10, 0x0002},
        {0x0000, 7, -6, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame5 = {
    {0x0400, 0x0000},
    {
        {0x0000, 4, 10, 0x0007},
        {0x0000, -10, -3, 0x0001},
        {0x0000, 0, -11, 0x0002},
        {0x0000, 6, -7, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame6 = {
    {0x0400, 0x0000},
    {
        {0x0000, 4, 9, 0x0008},
        {0x0000, -9, -4, 0x0001},
        {0x0000, 0, -12, 0x0002},
        {0x0000, 6, -8, 0x0003},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBank23Frame7 = {
    {0x0300, 0x0000},
    {
        {0x0000, 3, 10, 0x0005},
        {0x0000, 0, -12, 0x0002},
        {0x0000, 1, -8, 0x0003},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBank23Frame8 = {
    {0x0300, 0x0000},
    {
        {0x0000, 3, 10, 0x0006},
        {0x0000, 0, -10, 0x0002},
        {0x0000, -4, -6, 0x0003},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame9 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 2, 0x0009},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBank23Frame10 = {
    {0x0200, 0x0000},
    {
        {0x0000, -3, -13, 0x000A},
        {0x0000, -1, 2, 0x0009},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBank23Frame11 = {
    {0x0200, 0x0000},
    {
        {0x0000, -3, -14, 0x000B},
        {0x0000, -1, 2, 0x0009},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBank23Frame12 = {
    {0x0200, 0x0000},
    {
        {0x0000, -1, -13, 0x000C},
        {0x0000, -1, 2, 0x0009},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBank23Frame13 = {
    {0x0200, 0x0000},
    {
        {0x0000, -1, -13, 0x000D},
        {0x0000, -1, 2, 0x0009},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBank23Frame14 = {
    {0x0200, 0x0000},
    {
        {0x0000, -5, -14, 0x000E},
        {0x0000, -1, 2, 0x0009},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame15 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -2, 0x000F},
    },
};

SaturnSpriteFrame2 g_RStage16SpriteBank23Frame16 = {
    {0x0200, 0x0000},
    {
        {0x0000, -9, 10, 0x0010},
        {0x0000, -9, -11, 0x0011},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame17 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -2, 0x0012},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame18 = {
    {0x0400, 0x0000},
    {
        {0x0000, -5, -2, 0x0013},
        {0x0000, -1, 12, 0x0014},
        {0x0000, 6, -12, 0x0015},
        {0x0000, -17, -19, 0x0016},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame19 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -2, 0x0017},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame20 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -2, 0x0013},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame21 = {
    {0x0400, 0x0000},
    {
        {0x0100, 2, 10, 0x0006},
        {0x0100, -10, -19, 0x0018},
        {0x0100, 8, -14, 0x0019},
        {0x0100, 17, -19, 0x001A},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame22 = {
    {0x0400, 0x0000},
    {
        {0x0000, 2, 10, 0x0006},
        {0x0000, -10, -19, 0x0018},
        {0x0000, 8, -14, 0x0019},
        {0x0000, 17, -19, 0x001A},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame23 = {
    {0x0400, 0x0000},
    {
        {0x0000, 2, 10, 0x0006},
        {0x0000, -9, -19, 0x0018},
        {0x0000, 8, -14, 0x0019},
        {0x0000, 16, -19, 0x001A},
    },
};

SaturnSpriteFrame5 g_RStage16SpriteBank23Frame24 = {
    {0x0500, 0x0000},
    {
        {0x0000, -6, -13, 0x0018},
        {0x0000, 2, 10, 0x0006},
        {0x0000, 10, -10, 0x0003},
        {0x0000, 3, -10, 0x001B},
        {0x0000, 1, -17, 0x001C},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame25 = {
    {0x0400, 0x0000},
    {
        {0x0000, -11, -6, 0x0001},
        {0x0000, 2, 10, 0x0006},
        {0x0000, 2, -12, 0x0002},
        {0x0000, 9, -10, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame26 = {
    {0x0400, 0x0000},
    {
        {0x0000, -12, -3, 0x0001},
        {0x0000, 2, 10, 0x0006},
        {0x0000, 1, -11, 0x0002},
        {0x0000, 8, -7, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame27 = {
    {0x0400, 0x0000},
    {
        {0x0000, 6, 10, 0x001D},
        {0x0000, -13, -2, 0x0001},
        {0x0000, 0, -8, 0x0002},
        {0x0000, 5, -4, 0x0003},
    },
};

SaturnSpriteFrame4 g_RStage16SpriteBank23Frame28 = {
    {0x0400, 0x0000},
    {
        {0x0000, 6, 10, 0x001E},
        {0x0000, -15, -6, 0x0001},
        {0x0000, 1, -6, 0x0002},
        {0x0000, 5, -5, 0x0003},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame29 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 0, 0x001C},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 0, 0x001B},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame31 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 1, 0x0003},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame32 = {
    {0x0100, 0x0000},
    {
        {0x0010, 0, 0, 0x0003},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame33 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 0, 0x001F},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame34 = {
    {0x0100, 0x0000},
    {
        {0x0010, 0, 0, 0x001F},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame35 = {
    {0x0100, 0x0000},
    {
        {0x0200, 0, 1, 0x0020},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame36 = {
    {0x0100, 0x0000},
    {
        {0x0300, 4, 1, 0x0021},
    },
};

SaturnSpriteFrame3 g_RStage16SpriteBank23Frame37 = {
    {0x0300, 0x0000},
    {
        {0x0300, -72, 0, 0x0022},
        {0x0300, -24, 0, 0x0023},
        {0x0300, 24, 0, 0x0024},
    },
};

SaturnSpriteFrame1 g_RStage16SpriteBank23Frame38 = {
    {0x0100, 0x0000},
    {
        {0x0300, 0, 1, 0x0025},
    },
};

SaturnSpriteFrameHeader* g_RStage16SpriteBank23Frames[39] = {
    &g_RStage16SpriteBank23Frame0,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame1,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame2,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame3,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame4,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame5,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame6,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame7,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame8,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame9,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame10,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame11,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame12,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame13,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame14,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame15,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame16,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame17,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame18,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame19,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame20,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame21,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame22,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame23,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame24,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame25,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame26,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame27,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame28,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame29,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame30,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame31,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame32,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame33,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame34,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame35,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame36,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame37,
    (SaturnSpriteFrameHeader*)&g_RStage16SpriteBank23Frame38,
};

SaturnSpriteImage g_RStage16SpriteBank23Images[39] = {
    {0x10, 0x10, 0x0000}, {0x08, 0x04, 0x0040}, {0x0C, 0x0C, 0x0048},
    {0x0C, 0x08, 0x006C}, {0x0C, 0x10, 0x0084}, {0x08, 0x10, 0x00B4},
    {0x08, 0x10, 0x00D4}, {0x0C, 0x10, 0x00F4}, {0x10, 0x10, 0x0124},
    {0x14, 0x18, 0x0164}, {0x10, 0x08, 0x01DC}, {0x14, 0x08, 0x01FC},
    {0x14, 0x08, 0x0224}, {0x14, 0x08, 0x024C}, {0x14, 0x0C, 0x0274},
    {0x14, 0x18, 0x02B0}, {0x14, 0x0C, 0x0328}, {0x14, 0x0C, 0x0364},
    {0x14, 0x18, 0x03A0}, {0x14, 0x18, 0x0418}, {0x0C, 0x08, 0x0490},
    {0x04, 0x08, 0x04A8}, {0x0C, 0x04, 0x04B0}, {0x10, 0x18, 0x04BC},
    {0x08, 0x08, 0x051C}, {0x0C, 0x0C, 0x052C}, {0x04, 0x08, 0x0550},
    {0x08, 0x08, 0x0558}, {0x08, 0x08, 0x0568}, {0x0C, 0x10, 0x0578},
    {0x10, 0x0C, 0x05A8}, {0x04, 0x0C, 0x05D8}, {0x28, 0x20, 0x05E4},
    {0x10, 0x08, 0x0724}, {0x10, 0x10, 0x0744}, {0x20, 0x10, 0x0784},
    {0x10, 0x10, 0x0804}, {0x28, 0x20, 0x0844}, {0x00, 0x00, 0x0984},
};
