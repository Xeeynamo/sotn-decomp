// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

struct {
    u16 countAndFlags;
    u16 colors[9][16];
} g_Stage16SpriteBank16Palette = {
    0x0009,
    {
        {0x8000, 0x81D8, 0x8154, 0x80D0, 0x804C, 0x8008, 0x8006, 0x8004, 0x82DA,
         0x8256, 0x81D4, 0x810E, 0x8088, 0x8046, 0x8004, 0x8001},
        {0x8000, 0xA98D, 0xA14B, 0x9909, 0x90C7, 0x8885, 0x8443, 0x8000, 0x9EC6,
         0x9604, 0x8942, 0x80A0, 0xCA95, 0xC253, 0xBA11, 0xB1CF},
        {0x8000, 0xA193, 0x9951, 0x910F, 0x88CD, 0x848B, 0x8049, 0x8026, 0x96EB,
         0x8E4A, 0x8588, 0x80C6, 0xBE9B, 0xBA59, 0xB217, 0xA9D5},
        {0x80A0, 0xEF5A, 0xE718, 0xDED6, 0xD694, 0xCE52, 0xC610, 0xBDCE, 0xB58C,
         0xAD4A, 0xA508, 0x9CC6, 0x98A5, 0x9484, 0x9063, 0x8842},
        {0x8880, 0x8882, 0xE318, 0xDAD6, 0xD6B5, 0xCE73, 0xCA52, 0xC210, 0xBDEF,
         0xB5AD, 0xAD6B, 0xA94A, 0xA108, 0x9CE7, 0x94A5, 0x9084},
        {0x80A0, 0x890D, 0x99B3, 0xA215, 0xAA99, 0x8154, 0x8216, 0x86B9, 0x8421,
         0x8089, 0xFBBD, 0xCA95, 0xBD0C, 0xA4E4, 0xCD89, 0xF24F},
        {0x8000, 0xC294, 0xBA31, 0xB1CE, 0xA96B, 0xA129, 0x98E7, 0x90A5, 0x8000,
         0x8863, 0x8002, 0x8024, 0x8046, 0x8088, 0x80CA, 0xDB18},
        {0xA870, 0x8000, 0x8865, 0x990C, 0xADB2, 0xBE57, 0xCABA, 0xA54F, 0xA54B,
         0x8444, 0x94C8, 0x8C87, 0x8886, 0x8884, 0x8906, 0xDF7D},
        {0x80A0, 0xA5D3, 0x9D90, 0x952D, 0x90CA, 0x8888, 0x90E9, 0x8024, 0x80E9,
         0x80E9, 0x8084, 0x8024, 0x8006, 0x800E, 0x8017, 0x801F},
    },
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
} g_Stage16SpriteBank17Palette = {
    0x4001,
    {
        {0x8000, 0xC294, 0xBA31, 0xB1CE, 0xA96B, 0xA129, 0x98E7, 0x90A5, 0x8000,
         0x8863, 0x8002, 0x8024, 0x8046, 0x8088, 0x80CA, 0xDB18},
    },
};

SaturnSpriteImage g_Stage16SpriteBank16Images[21] = {
    {0x08, 0x08, 0x0000}, {0x10, 0x1A, 0x0010}, {0x0C, 0x08, 0x0078},
    {0x10, 0x0A, 0x0090}, {0x08, 0x08, 0x00B8}, {0x08, 0x07, 0x00C8},
    {0x0C, 0x12, 0x00D8}, {0x10, 0x10, 0x0110}, {0x10, 0x10, 0x0150},
    {0x14, 0x0A, 0x0190}, {0x0C, 0x10, 0x01C4}, {0x14, 0x0E, 0x01F4},
    {0x10, 0x0D, 0x023C}, {0x10, 0x0C, 0x0270}, {0x30, 0x10, 0x02A0},
    {0x20, 0x14, 0x0360}, {0x30, 0x10, 0x0400}, {0x2C, 0x11, 0x04C0},
    {0x1C, 0x1F, 0x057C}, {0x14, 0x1F, 0x0658}, {0x00, 0x00, 0x06F4},
};

SaturnSpriteFrameHeader g_Stage16SpriteBank16Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame2 g_Stage16SpriteBank16Frame1 = {
    {0x0200, 0x0000},
    {
        {0x0000, 0, -40, 0x0000},
        {0x0100, 0, -25, 0x0001},
    },
};

SaturnSpriteFrame3 g_Stage16SpriteBank16Frame2 = {
    {0x0300, 0x0000},
    {
        {0x0000, 3, -40, 0x0002},
        {0x0100, 0, -25, 0x0001},
        {0x0200, 1, -38, 0x0003},
    },
};

SaturnSpriteFrame2 g_Stage16SpriteBank16Frame3 = {
    {0x0200, 0x0000},
    {
        {0x0000, 0, -40, 0x0004},
        {0x0100, 0, -25, 0x0001},
    },
};

SaturnSpriteFrame3 g_Stage16SpriteBank16Frame4 = {
    {0x0300, 0x0000},
    {
        {0x0000, 1, -39, 0x0005},
        {0x0100, 0, -25, 0x0001},
        {0x0200, 1, -38, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame5 = {
    {0x0100, 0x0000},
    {
        {0x0100, 1, -17, 0x0006},
    },
};

SaturnSpriteFrame2 g_Stage16SpriteBank16Frame6 = {
    {0x0200, 0x0000},
    {
        {0x0300, 2, 0, 0x0007},
        {0x0000, 3, -24, 0x0002},
    },
};

SaturnSpriteFrame3 g_Stage16SpriteBank16Frame7 = {
    {0x0300, 0x0000},
    {
        {0x0300, 2, 0, 0x0007},
        {0x0000, 0, -24, 0x0000},
        {0x0400, 2, 0, 0x0008},
    },
};

SaturnSpriteFrame2 g_Stage16SpriteBank16Frame8 = {
    {0x0200, 0x0000},
    {
        {0x0300, 2, 0, 0x0007},
        {0x0000, 0, -24, 0x0004},
    },
};

SaturnSpriteFrame3 g_Stage16SpriteBank16Frame9 = {
    {0x0300, 0x0000},
    {
        {0x0300, 2, 0, 0x0007},
        {0x0000, 1, -23, 0x0005},
        {0x0400, 2, 0, 0x0008},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame10 = {
    {0x0100, 0x0000},
    {
        {0x0300, 2, 0, 0x0007},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame11 = {
    {0x0100, 0x0000},
    {
        {0x0500, 2, -8, 0x0009},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame12 = {
    {0x0100, 0x0000},
    {
        {0x0200, 3, -16, 0x000A},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame13 = {
    {0x0100, 0x0000},
    {
        {0x0600, 3, -20, 0x000B},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame14 = {
    {0x0100, 0x0000},
    {
        {0x0600, 0, -20, 0x000C},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame15 = {
    {0x0100, 0x0000},
    {
        {0x0600, 1, -20, 0x000D},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame16 = {
    {0x0100, 0x0000},
    {
        {0x0700, -28, -16, 0x000E},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame17 = {
    {0x0100, 0x0000},
    {
        {0x0700, 18, -20, 0x000F},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame18 = {
    {0x0100, 0x0000},
    {
        {0x0700, 32, -16, 0x0010},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame19 = {
    {0x0100, 0x0000},
    {
        {0x0700, 29, -17, 0x0011},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame20 = {
    {0x0100, 0x0000},
    {
        {0x0800, 5, 31, 0x0012},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank16Frame21 = {
    {0x0100, 0x0000},
    {
        {0x0800, 13, 31, 0x0013},
    },
};

SaturnSpriteFrameHeader* g_Stage16SpriteBank16Frames[22] = {
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame0,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame1,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame2,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame3,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame4,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame5,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame6,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame7,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame8,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame9,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame10,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame11,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame12,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame13,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame14,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame15,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame16,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame17,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame18,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame19,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame20,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank16Frame21,
};

SaturnSpriteResource g_Stage16SpriteBank16 = {
    g_Stage16SpriteBank16Images,
    (u16*)&g_Stage16SpriteBank16Palette,
    -1,
    0xFFFF,
};

SaturnSpriteResource g_Stage16SpriteBank17 = {
    NULL,
    (u16*)&g_Stage16SpriteBank17Palette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding;
} g_Stage16SpriteBank18Palette = {
    0x4001,
    {
        {0x800C, 0xBDA7, 0xC62A, 0xCE6D, 0xD6AF, 0xDEF1, 0xE753, 0xEF95, 0xFFFF,
         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    },
    0x0000,
};

SaturnSpriteImage g_Stage16SpriteBank18Images[3] = {
    {0x40, 0x18, 0x0000},
    {0x40, 0x18, 0x0180},
    {0x00, 0x00, 0x0300},
};

SaturnSpriteResource g_Stage16SpriteBank18 = {
    g_Stage16SpriteBank18Images,
    (u16*)&g_Stage16SpriteBank18Palette,
    -1,
    0xFFFF,
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding;
} g_Stage16SpriteBank19Palette = {
    0x4001,
    {
        {0x8180, 0xDF18, 0xCE94, 0xBE10, 0xAD8C, 0x9D08, 0x90C6, 0x8884, 0x8042,
         0x83E0, 0x83E0, 0x83E0, 0x83E0, 0x83E0, 0x83E0, 0x83E0},
    },
    0x0000,
};

SaturnSpriteImage g_Stage16SpriteBank19Images[3] = {
    {0x0C, 0x38, 0x0000},
    {0x0C, 0x05, 0x00A8},
    {0x00, 0x00, 0x00B8},
};

SaturnSpriteFrameHeader g_Stage16SpriteBank19Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame1 g_Stage16SpriteBank19Frame1 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 0, 0x0000},
    },
};

SaturnSpriteFrame1 g_Stage16SpriteBank19Frame2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 0, 0x0001},
    },
};

SaturnSpriteFrameHeader* g_Stage16SpriteBank19Frames[3] = {
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank19Frame0,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank19Frame1,
    (SaturnSpriteFrameHeader*)&g_Stage16SpriteBank19Frame2,
};

SaturnSpriteResource g_Stage16SpriteBank19 = {
    g_Stage16SpriteBank19Images,
    (u16*)&g_Stage16SpriteBank19Palette,
    -1,
    0xFFFF,
};
