// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

u16 D_060F018C[2] = {0x6C21, 0x0000};

struct {
    u16 countAndFlags;
    u16 colors[23][16];
} g_Stage15SpriteBank16Palette = {
    0x0017,
    {
        {0x9C5C, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E},
        {0x9C5C, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950},
        {0x9C5C, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192},
        {0x9C5C, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC},
        {0x9C5C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C},
        {0x9C5C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C},
        {0x9C5C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C},
        {0x9C5C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C},
        {0x9C5C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C},
        {0x9C5C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C},
        {0x9C5C, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E, 0xA8CC},
        {0x9C5C, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950, 0xB10E},
        {0x9C5C, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192, 0xB950},
        {0x9C5C, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216, 0xC192},
        {0x9C5C, 0xC192, 0xB950, 0xB10E, 0xA8CC, 0xA08C, 0x984C, 0x904C, 0x904C, 0x984C, 0xA08C, 0xA8CC, 0xB10E, 0xB950, 0xC192, 0xD216},
        {0x9802, 0x8006, 0x800F, 0x8016, 0xCE92, 0xB1AB, 0x98E7, 0x8CC4, 0x9005, 0xB8B3, 0xB42F, 0xA40A, 0x8844, 0x8C22, 0x954D, 0x88EB},
        {0x8000, 0x81D8, 0x8154, 0x80D0, 0x804C, 0x8008, 0x8006, 0x8004, 0x82DA, 0x8256, 0x81D4, 0x810E, 0x8088, 0x8046, 0x8004, 0x8001},
        {0x8000, 0xA98D, 0xA14B, 0x9909, 0x90C7, 0x8885, 0x8443, 0x8000, 0x9EC6, 0x9604, 0x8942, 0x80A0, 0xCA95, 0xC253, 0xBA11, 0xB1CF},
        {0x8000, 0xA193, 0x9951, 0x910F, 0x88CD, 0x848B, 0x8049, 0x8026, 0x96EB, 0x8E4A, 0x8588, 0x80C6, 0xBE9B, 0xBA59, 0xB217, 0xA9D5},
        {0x80A0, 0xEF5A, 0xE718, 0xDED6, 0xD694, 0xCE52, 0xC610, 0xBDCE, 0xB58C, 0xAD4A, 0xA508, 0x9CC6, 0x98A5, 0x9484, 0x9063, 0x8842},
        {0x8880, 0x8882, 0xE318, 0xDAD6, 0xD6B5, 0xCE73, 0xCA52, 0xC210, 0xBDEF, 0xB5AD, 0xAD6B, 0xA94A, 0xA108, 0x9CE7, 0x94A5, 0x9084},
        {0x8000, 0xC294, 0xBA31, 0xB1CE, 0xA96B, 0xA129, 0x98E7, 0x90A5, 0x8000, 0x8863, 0x8002, 0x8024, 0x8046, 0x8088, 0x80CA, 0xDB18},
        {0x80A0, 0xE6D6, 0xDE94, 0xD652, 0xCE10, 0xC5EF, 0xBDAD, 0xB56B, 0xAD29, 0xA4E7, 0x9CC6, 0x9484, 0x9063, 0x8C42, 0x8821, 0x8000},
    },
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
} g_Stage15SpriteBank17Palette = {
    0x4001,
    {
        {0x8000, 0xC294, 0xBA31, 0xB1CE, 0xA96B, 0xA129, 0x98E7, 0x90A5, 0x8000, 0x8863, 0x8002, 0x8024, 0x8046, 0x8088, 0x80CA, 0xDB18},
    },
};

SaturnSpriteImage g_Stage15SpriteBank16Images[31] = {
    {0x04, 0x06, 0x0000},
    {0x04, 0x05, 0x0008},
    {0x04, 0x04, 0x0010},
    {0x04, 0x30, 0x0014},
    {0x0C, 0x04, 0x0044},
    {0x08, 0x04, 0x0050},
    {0x08, 0x04, 0x0058},
    {0x08, 0x03, 0x0060},
    {0x08, 0x01, 0x0068},
    {0x08, 0x08, 0x006C},
    {0x08, 0x07, 0x007C},
    {0x04, 0x03, 0x008C},
    {0x04, 0x02, 0x0090},
    {0x04, 0x03, 0x0094},
    {0x04, 0x03, 0x0098},
    {0x04, 0x03, 0x009C},
    {0x08, 0x08, 0x00A0},
    {0x10, 0x1A, 0x00B0},
    {0x0C, 0x08, 0x0118},
    {0x10, 0x0A, 0x0130},
    {0x08, 0x08, 0x0158},
    {0x08, 0x07, 0x0168},
    {0x0C, 0x12, 0x0178},
    {0x14, 0x27, 0x01B0},
    {0x10, 0x10, 0x0274},
    {0x10, 0x10, 0x02B4},
    {0x14, 0x0E, 0x02F4},
    {0x10, 0x0D, 0x033C},
    {0x10, 0x0C, 0x0370},
    {0x08, 0x20, 0x03A0},
    {0x00, 0x00, 0x03E0},
};

SaturnSpriteFrameHeader g_Stage15SpriteBank16Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame1 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -3, 0x0000},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame2 = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, -2, 0x0001},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame3 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -1, 0x0002},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame5 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame7 = {
    {0x0100, 0x0000},
    {
        {0x0300, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame8 = {
    {0x0100, 0x0000},
    {
        {0x0400, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame9 = {
    {0x0100, 0x0000},
    {
        {0x0500, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame10 = {
    {0x0100, 0x0000},
    {
        {0x0600, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame11 = {
    {0x0100, 0x0000},
    {
        {0x0700, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame12 = {
    {0x0100, 0x0000},
    {
        {0x0800, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame13 = {
    {0x0100, 0x0000},
    {
        {0x0900, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame14 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame15 = {
    {0x0100, 0x0000},
    {
        {0x0B00, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame16 = {
    {0x0100, 0x0000},
    {
        {0x0C00, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame17 = {
    {0x0100, 0x0000},
    {
        {0x0D00, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame18 = {
    {0x0100, 0x0000},
    {
        {0x0E00, 4, 48, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame19 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -3, 0x0004},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame20 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, -3, 0x0005},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame21 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, -3, 0x0006},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame22 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -3, 0x0007},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame23 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -1, 0x0008},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame24 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, -8, 0x0009},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame25 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, -7, 0x000A},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame26 = {
    {0x0100, 0x0000},
    {
        {0x0F00, 5, -5, 0x000B},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame27 = {
    {0x0100, 0x0000},
    {
        {0x0F00, 5, -4, 0x000C},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame28 = {
    {0x0100, 0x0000},
    {
        {0x0F00, 5, -3, 0x000D},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame29 = {
    {0x0100, 0x0000},
    {
        {0x0F00, 5, -4, 0x000E},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame30 = {
    {0x0100, 0x0000},
    {
        {0x0F00, 5, -2, 0x000F},
    },
};

SaturnSpriteFrame2 g_Stage15SpriteBank16Frame31 = {
    {0x0200, 0x0000},
    {
        {0x1000, 0, -41, 0x0010},
        {0x1100, 0, -26, 0x0011},
    },
};

SaturnSpriteFrame3 g_Stage15SpriteBank16Frame32 = {
    {0x0300, 0x0000},
    {
        {0x1000, 3, -41, 0x0012},
        {0x1100, 0, -26, 0x0011},
        {0x1200, 1, -39, 0x0013},
    },
};

SaturnSpriteFrame2 g_Stage15SpriteBank16Frame33 = {
    {0x0200, 0x0000},
    {
        {0x1000, 0, -41, 0x0014},
        {0x1100, 0, -26, 0x0011},
    },
};

SaturnSpriteFrame3 g_Stage15SpriteBank16Frame34 = {
    {0x0300, 0x0000},
    {
        {0x1000, 1, -40, 0x0015},
        {0x1100, 0, -26, 0x0011},
        {0x1200, 1, -39, 0x0013},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame35 = {
    {0x0100, 0x0000},
    {
        {0x1100, 1, -18, 0x0016},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame36 = {
    {0x0100, 0x0000},
    {
        {0x1100, 1, -38, 0x0017},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame37 = {
    {0x0100, 0x0000},
    {
        {0x1110, -1, -38, 0x0017},
    },
};

SaturnSpriteFrame2 g_Stage15SpriteBank16Frame38 = {
    {0x0200, 0x0000},
    {
        {0x1300, 2, 0, 0x0018},
        {0x1000, 3, -24, 0x0012},
    },
};

SaturnSpriteFrame3 g_Stage15SpriteBank16Frame39 = {
    {0x0300, 0x0000},
    {
        {0x1300, 2, 0, 0x0018},
        {0x1000, 0, -24, 0x0010},
        {0x1400, 2, 0, 0x0019},
    },
};

SaturnSpriteFrame2 g_Stage15SpriteBank16Frame40 = {
    {0x0200, 0x0000},
    {
        {0x1300, 2, 0, 0x0018},
        {0x1000, 0, -24, 0x0014},
    },
};

SaturnSpriteFrame3 g_Stage15SpriteBank16Frame41 = {
    {0x0300, 0x0000},
    {
        {0x1300, 2, 0, 0x0018},
        {0x1000, 1, -23, 0x0015},
        {0x1400, 2, 0, 0x0019},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame42 = {
    {0x0100, 0x0000},
    {
        {0x1300, 2, 0, 0x0018},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame43 = {
    {0x0100, 0x0000},
    {
        {0x1500, 3, -20, 0x001A},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame44 = {
    {0x0100, 0x0000},
    {
        {0x1500, 0, -20, 0x001B},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame45 = {
    {0x0100, 0x0000},
    {
        {0x1500, 1, -20, 0x001C},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank16Frame46 = {
    {0x0100, 0x0000},
    {
        {0x1600, 0, 0, 0x001D},
    },
};

SaturnSpriteFrameHeader* g_Stage15SpriteBank16Frames[47] = {
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame0,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame1,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame2,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame3,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame4,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame5,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame6,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame7,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame8,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame9,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame10,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame11,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame12,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame13,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame14,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame15,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame16,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame17,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame18,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame19,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame20,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame21,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame22,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame23,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame24,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame25,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame26,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame27,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame28,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame29,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame30,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame31,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame32,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame33,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame34,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame35,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame36,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame37,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame38,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame39,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame40,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame41,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame42,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame43,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame44,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame45,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank16Frame46,
};

SaturnSpriteResource g_Stage15SpriteBank16 = {
    (SaturnSpriteImage*)&g_Stage15SpriteBank16Images,
    (u16*)&g_Stage15SpriteBank16Palette,
    -1,
    0xFFFF,
};

SaturnSpriteResource g_Stage15SpriteBank17 = {
    NULL,
    (u16*)&g_Stage15SpriteBank17Palette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding;
} g_Stage15SpriteBank18Palette = {
    0x4002,
    {
        {0x800C, 0xBDA7, 0xC62A, 0xCE6D, 0xD6AF, 0xDEF1, 0xE753, 0xEF95, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
        {0x8220, 0xFC21, 0x8421, 0xFC21, 0xCE73, 0xF39C, 0x87FF, 0x87E1, 0x8220, 0x8421, 0xD421, 0xFC21, 0xFD42, 0xFE48, 0xF6D1, 0xFFBD},
    },
    0x0000,
};

SaturnSpriteImage g_Stage15SpriteBank18Images[8] = {
    {0x20, 0x18, 0x0000},
    {0x20, 0x18, 0x00C0},
    {0x20, 0x18, 0x0180},
    {0x18, 0x20, 0x0240},
    {0x18, 0x20, 0x0300},
    {0x18, 0x20, 0x03C0},
    {0x08, 0x08, 0x0480},
    {0x00, 0x00, 0x0490},
};

SaturnSpriteResource g_Stage15SpriteBank18 = {
    (SaturnSpriteImage*)&g_Stage15SpriteBank18Images,
    (u16*)&g_Stage15SpriteBank18Palette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding;
} g_Stage15SpriteBank19Palette = {
    0x0001,
    {
        {0xB0A5, 0xD940, 0xE180, 0xBC00, 0xC900, 0xD900, 0xD940, 0xE180, 0xBC00, 0xC900, 0xD900, 0xD940, 0xE180, 0xBC00, 0xC900, 0xD900},
    },
    0x0000,
};

SaturnSpriteImage g_Stage15SpriteBank19Images[3] = {
    {0x10, 0x20, 0x0000},
    {0x14, 0x10, 0x0080},
    {0x00, 0x00, 0x00D0},
};

SaturnSpriteResource g_Stage15SpriteBank19 = {
    (SaturnSpriteImage*)&g_Stage15SpriteBank19Images,
    (u16*)&g_Stage15SpriteBank19Palette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding;
} g_Stage15SpriteBank20Palette = {
    0x0002,
    {
        {0x9C22, 0x9190, 0x8D4E, 0x890C, 0x88EA, 0x84A8, 0x8066, 0x8044, 0xA688, 0x9DC6, 0x9504, 0x8CC2, 0x88A1, 0x8481, 0x8461, 0x8441},
        {0x9C22, 0x9190, 0x810C, 0x80CA, 0x8088, 0x8086, 0x8044, 0xB74C, 0xA688, 0x9DC6, 0x9504, 0x8CC2, 0x88A1, 0x8481, 0x8461, 0x8441},
    },
    0x0000,
};

SaturnSpriteImage g_Stage15SpriteBank20Images[8] = {
    {0x18, 0x18, 0x0000},
    {0x18, 0x18, 0x0090},
    {0x30, 0x20, 0x0120},
    {0x10, 0x13, 0x02A0},
    {0x18, 0x18, 0x02EC},
    {0x30, 0x20, 0x037C},
    {0x18, 0x18, 0x04FC},
    {0x00, 0x00, 0x058C},
};

SaturnSpriteFrameHeader g_Stage15SpriteBank20Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame3 g_Stage15SpriteBank20Frame1 = {
    {0x0300, 0x0000},
    {
        {0x0000, -34, -23, 0x0000},
        {0x0100, 14, -24, 0x0001},
        {0x0100, 1, -79, 0x0002},
    },
};

SaturnSpriteFrame1 g_Stage15SpriteBank20Frame2 = {
    {0x0100, 0x0000},
    {
        {0x0100, 6, -20, 0x0003},
    },
};

SaturnSpriteFrame3 g_Stage15SpriteBank20Frame3 = {
    {0x0300, 0x0000},
    {
        {0x0000, 32, -23, 0x0004},
        {0x0100, -4, -79, 0x0005},
        {0x0100, -10, -24, 0x0006},
    },
};

SaturnSpriteFrameHeader* g_Stage15SpriteBank20Frames[4] = {
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank20Frame0,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank20Frame1,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank20Frame2,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank20Frame3,
};

SaturnSpriteResource g_Stage15SpriteBank20 = {
    (SaturnSpriteImage*)&g_Stage15SpriteBank20Images,
    (u16*)&g_Stage15SpriteBank20Palette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding;
} g_Stage15SpriteBank21Palette = {
    0x0001,
    {
        {0x9C22, 0xBDCA, 0xB989, 0xB168, 0xA927, 0xA507, 0x9CC6, 0x94A5, 0x9484, 0x8822, 0x81A0, 0x8160, 0x8140, 0x8100, 0x80C0, 0x8080},
    },
    0x0000,
};

SaturnSpriteImage g_Stage15SpriteBank21Images[3] = {
    {0x20, 0x28, 0x0000},
    {0x24, 0x28, 0x0140},
    {0x00, 0x00, 0x02A8},
};

SaturnSpriteFrameHeader g_Stage15SpriteBank21Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame2 g_Stage15SpriteBank21Frame1 = {
    {0x0200, 0x0000},
    {
        {0x0000, -27, -40, 0x0000},
        {0x0000, 36, -40, 0x0001},
    },
};

SaturnSpriteFrameHeader* g_Stage15SpriteBank21Frames[2] = {
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank21Frame0,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank21Frame1,
};

SaturnSpriteResource g_Stage15SpriteBank21 = {
    (SaturnSpriteImage*)&g_Stage15SpriteBank21Images,
    (u16*)&g_Stage15SpriteBank21Palette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding;
} g_Stage15SpriteBank22Palette = {
    0x0001,
    {
        {0x87E1, 0xF316, 0xEAD4, 0xE292, 0xDA50, 0xD20E, 0xC9CC, 0xC18A, 0xB948, 0xB106, 0xA8C5, 0xA084, 0x9843, 0x9022, 0x8C21, 0x8821},
    },
    0x0000,
};

SaturnSpriteImage g_Stage15SpriteBank22Images[13] = {
    {0x40, 0x01, 0x0000},
    {0x40, 0x01, 0x0010},
    {0x40, 0x01, 0x0020},
    {0x0C, 0x01, 0x0030},
    {0x40, 0x01, 0x0034},
    {0x40, 0x01, 0x0044},
    {0x40, 0x01, 0x0054},
    {0x0C, 0x01, 0x0064},
    {0x40, 0x01, 0x0068},
    {0x40, 0x01, 0x0078},
    {0x40, 0x01, 0x0088},
    {0x0C, 0x01, 0x0098},
    {0x00, 0x00, 0x009C},
};

SaturnSpriteFrameHeader g_Stage15SpriteBank22Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame5 g_Stage15SpriteBank22Frame1 = {
    {0x0500, 0x0000},
    {
        {0x0000, 64, 2, 0x0000},
        {0x0000, 192, 2, 0x0001},
        {0x0000, 320, 2, 0x0002},
        {0x0000, 448, 2, 0x0000},
        {0x0000, 524, 2, 0x0003},
    },
};

SaturnSpriteFrame5 g_Stage15SpriteBank22Frame2 = {
    {0x0500, 0x0000},
    {
        {0x0000, 64, 2, 0x0004},
        {0x0000, 192, 2, 0x0005},
        {0x0000, 320, 2, 0x0006},
        {0x0000, 448, 2, 0x0004},
        {0x0000, 524, 2, 0x0007},
    },
};

SaturnSpriteFrame5 g_Stage15SpriteBank22Frame3 = {
    {0x0500, 0x0000},
    {
        {0x0000, 64, 2, 0x0008},
        {0x0000, 192, 2, 0x0009},
        {0x0000, 320, 2, 0x000A},
        {0x0000, 448, 2, 0x0008},
        {0x0000, 524, 2, 0x000B},
    },
};

SaturnSpriteFrameHeader* g_Stage15SpriteBank22Frames[4] = {
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank22Frame0,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank22Frame1,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank22Frame2,
    (SaturnSpriteFrameHeader*)&g_Stage15SpriteBank22Frame3,
};

SaturnSpriteResource g_Stage15SpriteBank22 = {
    (SaturnSpriteImage*)&g_Stage15SpriteBank22Images,
    (u16*)&g_Stage15SpriteBank22Palette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding;
} g_Stage15SpriteBank32Palette = {
    0x4001,
    {
        {0xB0A5, 0x815B, 0x819C, 0x921D, 0x969E, 0xAF5F, 0xD7DF, 0xFFFF, 0xE900, 0xED40, 0xF180, 0xF604, 0xFA85, 0xFF4B, 0xFFD5, 0xFFFF},
    },
    0x0000,
};

SaturnSpriteImage g_Stage15SpriteBank32Images[2] = {
    {0x08, 0x08, 0x0000},
    {0x00, 0x00, 0x0010},
};

SaturnSpriteResource g_Stage15SpriteBank32 = {
    (SaturnSpriteImage*)&g_Stage15SpriteBank32Images,
    (u16*)&g_Stage15SpriteBank32Palette,
    -1,
    0xFFFF,
};
