// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

struct {
    u16 countAndFlags;
    u16 colors[7][16];
    u16 padding;
} g_Stage14SpriteBank22Palette = {
    0x0007,
    {
        {0x8140, 0xFB74, 0xF2F1, 0xE66E, 0xDA0B, 0xCD88, 0xC104, 0xB881, 0xFFFF,
         0xF37B, 0xE6D6, 0xD652, 0xC9AD, 0xBD29, 0xAC84, 0xA000},
        {0xB88F, 0xC104, 0xCD88, 0xDA0B, 0xE66E, 0xFB74, 0xB881, 0xC104, 0xDA0B,
         0xE66E, 0xFB74, 0xB881, 0xC104, 0xCD88, 0xE66E, 0xFB74},
        {0x8000, 0xFFFF, 0xF7A6, 0xF6A0, 0xF5A0, 0xF4C0, 0xF400, 0xB400, 0x8000,
         0xFB74, 0xF2F1, 0xE66E, 0xDA0B, 0xCD88, 0xC104, 0xB881},
        {0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
         0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
        {0x8000, 0x9400, 0xAC20, 0xC440, 0xCC60, 0x9800, 0xA820, 0x9400, 0xA820,
         0xBC40, 0xD460, 0xE880, 0xFCA0, 0xFD60, 0xFF20, 0xFF98},
        {0x8112, 0x8912, 0x9112, 0x9912, 0xA112, 0xA912, 0xB112, 0xB912, 0xC112,
         0xC912, 0xD112, 0xD912, 0xE112, 0xE912, 0xF112, 0xF912},
        {0x8190, 0x8990, 0x9190, 0x9990, 0xA190, 0xA990, 0xB190, 0xB990, 0xC190,
         0xC990, 0xD190, 0xD990, 0xE190, 0xE990, 0xF190, 0xF990},
    },
    0x0000,
};

SaturnSpriteFrameHeader g_Stage14SpriteBank22Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame1 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, 1, 0x0000},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -1, 0x0001},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame3 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 0, 0x0002},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 1, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame5 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -4, 0x0004},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x0005},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame7 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 2, 0x0006},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 4, 0x0007},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame9 = {
    {0x0100, 0x0000},
    {
        {0x0100, 9, 0, 0x0008},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame10 = {
    {0x0100, 0x0000},
    {
        {0x0100, 10, 0, 0x0009},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame11 = {
    {0x0100, 0x0000},
    {
        {0x0100, 10, 0, 0x000A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame12 = {
    {0x0100, 0x0000},
    {
        {0x0100, 10, 0, 0x000B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame13 = {
    {0x0100, 0x0000},
    {
        {0x0100, 10, 0, 0x000C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame14 = {
    {0x0100, 0x0000},
    {
        {0x0100, 10, 0, 0x000D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame15 = {
    {0x0100, 0x0000},
    {
        {0x0100, 10, 0, 0x000E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame16 = {
    {0x0100, 0x0000},
    {
        {0x0100, 10, 0, 0x000F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame17 = {
    {0x0100, 0x0000},
    {
        {0x0200, 0, 0, 0x0010},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame18 = {
    {0x0100, 0x0000},
    {
        {0x0210, 1, 0, 0x0010},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame19 = {
    {0x0100, 0x0000},
    {
        {0x0230, 1, 0, 0x0010},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame20 = {
    {0x0100, 0x0000},
    {
        {0x0220, 0, 0, 0x0010},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame21 = {
    {0x0100, 0x0000},
    {
        {0x0300, 0, 0, 0x0010},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame22 = {
    {0x0100, 0x0000},
    {
        {0x0400, -1, -8, 0x0011},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame23 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x0012},
        {0x0400, 24, -8, 0x0013},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame24 = {
    {0x0100, 0x0000},
    {
        {0x0400, 18, 8, 0x0014},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame25 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x0012},
        {0x0400, 1, 8, 0x0015},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame26 = {
    {0x0100, 0x0000},
    {
        {0x0400, -12, 8, 0x0016},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame27 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x0012},
        {0x0400, -14, -8, 0x0017},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame28 = {
    {0x0100, 0x0000},
    {
        {0x0420, -9, 16, 0x0011},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame29 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x0012},
        {0x0520, 13, 16, 0x0013},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame30 = {
    {0x0100, 0x0000},
    {
        {0x0420, 10, 0, 0x0014},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame31 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x0012},
        {0x0420, 11, -17, 0x0015},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame32 = {
    {0x0100, 0x0000},
    {
        {0x0420, -6, -16, 0x0016},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame33 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x0012},
        {0x0420, -8, 0, 0x0017},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame34 = {
    {0x0100, 0x0000},
    {
        {0x0600, 3, 4, 0x0018},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame35 = {
    {0x0100, 0x0000},
    {
        {0x0200, 0, 0, 0x0019},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame36 = {
    {0x0100, 0x0000},
    {
        {0x0210, 0, 0, 0x0019},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame37 = {
    {0x0100, 0x0000},
    {
        {0x0230, 0, 0, 0x0019},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank22Frame38 = {
    {0x0100, 0x0000},
    {
        {0x0220, 0, 0, 0x0019},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame39 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x001A},
        {0x0400, 19, -8, 0x0013},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame40 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x001A},
        {0x0400, 1, 8, 0x0015},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame41 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x001A},
        {0x0400, -13, -8, 0x0017},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame42 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x001A},
        {0x0420, 13, 16, 0x0013},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame43 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x001A},
        {0x0420, 10, -16, 0x0015},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank22Frame44 = {
    {0x0200, 0x0000},
    {
        {0x0300, 0, 0, 0x001A},
        {0x0420, -9, 0, 0x0017},
    },
};

SaturnSpriteFrameHeader* g_Stage14SpriteBank22Frames[45] = {
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame0,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame1,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame2,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame3,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame4,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame5,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame6,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame7,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame8,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame9,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame10,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame11,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame12,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame13,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame14,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame15,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame16,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame17,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame18,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame19,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame20,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame21,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame22,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame23,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame24,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame25,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame26,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame27,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame28,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame29,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame30,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame31,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame32,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame33,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame34,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame35,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame36,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame37,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame38,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame39,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame40,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame41,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame42,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame43,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank22Frame44,
};

SaturnSpriteImage g_Stage14SpriteBank22Images[28] = {
    {0x10, 0x08, 0x0000}, {0x0C, 0x08, 0x0020}, {0x0C, 0x08, 0x0038},
    {0x0C, 0x08, 0x0050}, {0x0C, 0x0C, 0x0068}, {0x0C, 0x0C, 0x008C},
    {0x10, 0x0C, 0x00B0}, {0x0C, 0x0C, 0x00E0}, {0x14, 0x08, 0x0104},
    {0x14, 0x08, 0x012C}, {0x14, 0x08, 0x0154}, {0x14, 0x08, 0x017C},
    {0x14, 0x08, 0x01A4}, {0x14, 0x08, 0x01CC}, {0x14, 0x08, 0x01F4},
    {0x14, 0x08, 0x021C}, {0x14, 0x10, 0x0244}, {0x0C, 0x08, 0x0294},
    {0x14, 0x10, 0x02AC}, {0x0C, 0x08, 0x02FC}, {0x08, 0x08, 0x0314},
    {0x0C, 0x08, 0x0324}, {0x0C, 0x08, 0x033C}, {0x0C, 0x08, 0x0354},
    {0x08, 0x08, 0x036C}, {0x10, 0x10, 0x037C}, {0x10, 0x10, 0x03BC},
    {0x00, 0x00, 0x03FC},
};
