// SPDX-License-Identifier: AGPL-3.0-or-later
// Decoded with tools/saturn_sprite_decoder.py.
#include "sattypes.h"
#include <saturn_sprite.h>

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} g_Stage02MariaNpcPalette = {
    0x0001,
    {
        {
            0xB021,
            0x84C9,
            0x8D53,
            0xA1F9,
            0xB6FC,
            0x8180,
            0x8280,
            0xAB2A,
            0x9218,
            0x931F,
            0x9463,
            0x9CE7,
            0xB148,
            0xCA2E,
            0xE2F6,
            0xEF7B,
        },
    },
    {0x0000},
};

SaturnSpriteImage g_Stage02MariaNpcImages[49] = {
    {12, 22, 0x0000}, {12, 23, 0x0044}, {12, 23, 0x008C}, {12, 23, 0x00D4},
    {12, 22, 0x011C}, {12, 22, 0x0160}, {12, 22, 0x01A4}, {12, 23, 0x01E8},
    {8, 23, 0x0230},  {8, 23, 0x0260},  {12, 22, 0x0290}, {12, 22, 0x02D4},
    {12, 23, 0x0318}, {12, 23, 0x0360}, {12, 23, 0x03A8}, {12, 23, 0x03F0},
    {12, 23, 0x0438}, {12, 23, 0x0480}, {4, 8, 0x04C8},   {12, 23, 0x04D0},
    {4, 6, 0x0518},   {4, 4, 0x0520},   {4, 4, 0x0524},   {4, 4, 0x0528},
    {4, 4, 0x052C},   {4, 4, 0x0530},   {4, 3, 0x0534},   {4, 3, 0x0538},
    {4, 3, 0x053C},   {8, 3, 0x0540},   {4, 4, 0x0548},   {4, 5, 0x054C},
    {4, 3, 0x0554},   {12, 23, 0x0558}, {8, 12, 0x05A0},  {8, 15, 0x05B8},
    {8, 15, 0x05D8},  {8, 15, 0x05F8},  {12, 15, 0x0618}, {8, 23, 0x0648},
    {8, 23, 0x0678},  {12, 23, 0x06A8}, {12, 23, 0x06F0}, {8, 8, 0x0738},
    {8, 15, 0x0748},  {4, 3, 0x0768},   {4, 6, 0x076C},   {4, 1, 0x0774},
    {0, 0, 0x0778},
};

SaturnSpriteFrameHeader g_Stage02MariaNpcFrame0 = {
    0x0000,
    0x0000,
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame1 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 3, 0},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 3, 1},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame3 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 3, 2},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 3, 3},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame5 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 3, 4},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame6 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 3, 5},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame7 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 3, 6},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 3, 7},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame9 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, 3, 8},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame10 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 3, 9},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame11 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 10},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame12 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 3, 11},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame13 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 12},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame14 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 13},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame15 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 14},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame16 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 3, 15},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame17 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, 3, 16},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 3, 17},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame19 = {
    {0x0200, 0x0000},
    {
        {0x0000, 15, -1, 18},
        {0x0000, 12, 3, 19},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame20 = {
    {0x0200, 0x0000},
    {
        {0x0000, 17, -3, 20},
        {0x0000, 12, 3, 19},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame21 = {
    {0x0200, 0x0000},
    {
        {0x0000, 17, -5, 21},
        {0x0000, 12, 3, 19},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame22 = {
    {0x0200, 0x0000},
    {
        {0x0000, 17, -5, 22},
        {0x0000, 12, 3, 19},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame23 = {
    {0x0200, 0x0000},
    {
        {0x0000, 17, -10, 23},
        {0x0000, 12, 3, 19},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame24 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, 3, 19},
        {0x0000, 17, -9, 24},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame25 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, 3, 19},
        {0x0000, 17, -8, 25},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame26 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, 3, 19},
        {0x0000, 17, -8, 26},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame27 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, 3, 19},
        {0x0000, 15, -8, 27},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame28 = {
    {0x0200, 0x0000},
    {
        {0x0000, 17, -8, 28},
        {0x0000, 12, 3, 19},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame29 = {
    {0x0200, 0x0000},
    {
        {0x0000, 19, -7, 29},
        {0x0000, 12, 3, 19},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame30 = {
    {0x0200, 0x0000},
    {
        {0x0000, 20, -7, 29},
        {0x0000, 12, 3, 19},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame31 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, 3, 19},
        {0x0000, 16, -11, 30},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame32 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, 3, 19},
        {0x0000, 17, -11, 31},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame33 = {
    {0x0200, 0x0000},
    {
        {0x0000, 15, 1, 32},
        {0x0000, 12, 3, 33},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame34 = {
    {0x0200, 0x0000},
    {
        {0x0000, 9, 14, 34},
        {0x0000, 9, -5, 35},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame35 = {
    {0x0200, 0x0000},
    {
        {0x0000, 9, 14, 34},
        {0x0000, 9, -5, 36},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame36 = {
    {0x0200, 0x0000},
    {
        {0x0000, 9, 14, 34},
        {0x0000, 9, -4, 37},
    },
};

SaturnSpriteFrame2 g_Stage02MariaNpcFrame37 = {
    {0x0200, 0x0000},
    {
        {0x0000, 9, 14, 34},
        {0x0000, 12, -5, 38},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame38 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 3, 16},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame39 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 3, 15},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame40 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 3, 14},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame41 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 3, 13},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame42 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 3, 39},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame43 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 3, 40},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame44 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 3, 41},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame45 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 3, 42},
    },
};

SaturnSpriteFrame3 g_Stage02MariaNpcFrame46 = {
    {0x0300, 0x0000},
    {
        {0x0000, 17, 18, 43},
        {0x0000, 15, -5, 44},
        {0x0000, 25, -7, 45},
    },
};

SaturnSpriteFrame3 g_Stage02MariaNpcFrame47 = {
    {0x0300, 0x0000},
    {
        {0x0000, 15, -5, 44},
        {0x0000, 17, 18, 43},
        {0x0020, 25, -11, 45},
    },
};

SaturnSpriteFrame4 g_Stage02MariaNpcFrame48 = {
    {0x0400, 0x0000},
    {
        {0x0000, 15, -5, 44},
        {0x0000, 17, 18, 43},
        {0x0000, 23, -12, 46},
        {0x0000, 24, -15, 47},
    },
};

SaturnSpriteFrame4 g_Stage02MariaNpcFrame49 = {
    {0x0400, 0x0000},
    {
        {0x0000, 15, -5, 44},
        {0x0000, 17, 18, 43},
        {0x0000, 23, -12, 46},
        {0x0000, 24, -16, 47},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame50 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 3, 2},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame51 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 3, 3},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame52 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 3, 4},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame53 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 3, 5},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 3, 6},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame55 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 3, 7},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame56 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 3, 8},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame57 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 3, 9},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame58 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 3, 10},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame59 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 3, 11},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame60 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 3, 0},
    },
};

SaturnSpriteFrame1 g_Stage02MariaNpcFrame61 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 3, 1},
    },
};

SaturnSpriteFrameHeader* g_Stage02MariaNpcFrames[62] = {
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame0,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame1,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame2,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame3,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame4,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame5,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame6,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame7,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame8,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame9,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame10,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame11,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame12,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame13,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame14,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame15,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame16,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame17,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame18,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame19,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame20,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame21,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame22,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame23,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame24,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame25,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame26,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame27,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame28,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame29,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame30,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame31,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame32,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame33,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame34,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame35,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame36,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame37,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame38,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame39,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame40,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame41,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame42,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame43,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame44,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame45,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame46,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame47,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame48,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame49,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame50,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame51,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame52,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame53,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame54,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame55,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame56,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame57,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame58,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame59,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame60,
    (SaturnSpriteFrameHeader*)&g_Stage02MariaNpcFrame61,
};

SaturnSpriteResource g_Stage02MariaNpcResource = {
    g_Stage02MariaNpcImages,
    (u16*)&g_Stage02MariaNpcPalette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} g_Stage02SpriteBank17Palette = {
    0x4001,
    {
        {
            0x8000,
            0xCDCA,
            0xD62D,
            0xDE90,
            0xE6D2,
            0xEF14,
            0xF756,
            0xFF98,
            0xFFFF,
            0xFFFF,
            0xFFFF,
            0xFFFF,
            0xFFFF,
            0xFFFF,
            0xFFFF,
            0xFFFF,
        },
    },
    {0x0000},
};

SaturnSpriteImage g_Stage02SpriteBank17Images[3] = {
    {64, 24, 0x0000},
    {64, 24, 0x0180},
    {0, 0, 0x0300},
};

SaturnSpriteResource g_Stage02SpriteBank17Resource = {
    g_Stage02SpriteBank17Images,
    (u16*)&g_Stage02SpriteBank17Palette,
    -1,
    0xFFFF,
};
