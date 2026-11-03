// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

struct {
    u16 countAndFlags;
    u16 colors[5][16];
    u16 padding;
} g_Stage14SpriteBank21Palette = {
    0x0005,
    {
        {0xB800, 0x84C9, 0x8D53, 0xA1F9, 0xB6FC, 0x8180, 0x8280, 0xAB2A, 0x9218,
         0x931F, 0x9463, 0x9CE7, 0xB148, 0xCA2E, 0xE2F6, 0xEF7B},
        {0x8420, 0xFFAE, 0xF7A6, 0xF6A0, 0xF5A0, 0xF4C0, 0xF400, 0xB400, 0xFFFF,
         0x845F, 0x845B, 0x8036, 0x8032, 0x800E, 0x8009, 0x8005},
        {0x8000, 0xADF7, 0xAA3A, 0xBA9C, 0xCB5E, 0x9A48, 0x9B47, 0xBF90, 0xB29C,
         0xBB7F, 0xC58B, 0xBE2F, 0xDA4F, 0xE6D2, 0xF379, 0xFBDE},
        {0x8140, 0xFB74, 0xF2F1, 0xE66E, 0xDA0B, 0xCD88, 0xC104, 0xB881, 0xFFFF,
         0xF37B, 0xE6D6, 0xD652, 0xC9AD, 0xBD29, 0xAC84, 0xA000},
        {0x8000, 0x9400, 0xAC20, 0xC440, 0xCC60, 0x9800, 0xA820, 0x9400, 0xA820,
         0xBC40, 0xD460, 0xE880, 0xFCA0, 0xFD60, 0xFF20, 0xFF98},
    },
    0x0000,
};

SaturnSpriteFrameHeader g_Stage14SpriteBank21Frame0 = {0x0000, 0x0000};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame1 = {
    {0x0200, 0x0000},
    {
        {0x0010, -2, 8, 0x0000},
        {0x0010, -1, -14, 0x0001},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -2, 3, 0x0002},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame3 = {
    {0x0100, 0x0000},
    {
        {0x0010, -2, 3, 0x0003},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame4 = {
    {0x0100, 0x0000},
    {
        {0x0010, -3, 3, 0x0004},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame5 = {
    {0x0100, 0x0000},
    {
        {0x0010, -4, 3, 0x0005},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame6 = {
    {0x0100, 0x0000},
    {
        {0x0010, -8, 3, 0x0006},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame7 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -5, 0x0007},
        {0x0000, 0, 10, 0x0008},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 0, -5, 0x0009},
        {0x0000, -1, 10, 0x000A},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame9 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 10, 0x000B},
        {0x0000, 5, -5, 0x000C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame10 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 4, 0x000D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame11 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 5, 0x000E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame12 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 6, 0x000F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame13 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 2, 0x0010},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame14 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 1, 0x0011},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame15 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 3, 0x0012},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame16 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 2, 0x0013},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame17 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 2, 0x0014},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 0, 0x0015},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame19 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 2, 0x0016},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame20 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, 2, 0x0017},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame21 = {
    {0x0300, 0x0000},
    {
        {0x0000, 2, 9, 0x0018},
        {0x0000, 2, -8, 0x0019},
        {0x0000, 12, -9, 0x001A},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame22 = {
    {0x0200, 0x0000},
    {
        {0x0000, 2, 9, 0x0018},
        {0x0000, 2, -9, 0x001B},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame23 = {
    {0x0200, 0x0000},
    {
        {0x0000, 2, 9, 0x0018},
        {0x0000, 1, -9, 0x001C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 3, 0x001D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame25 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x001E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame26 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x001F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame27 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x0020},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame28 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x0021},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame29 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x0022},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 3, 0x0023},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame31 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 3, 0x0024},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame32 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 3, 0x0025},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame33 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x0026},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame34 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x0027},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame35 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 3, 0x0028},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame36 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -5, 0x0029},
        {0x0000, 0, 14, 0x002A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame37 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 4, 0x002B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame38 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 3, 0x002C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame39 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x002D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame40 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 4, 0x002E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame41 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 4, 0x002F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame42 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 4, 0x0030},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame43 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 4, 0x0031},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame44 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 4, 0x0032},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame45 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 4, 0x0033},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame46 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 4, 0x0034},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame47 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 4, 0x0035},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame48 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 4, 0x0036},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame49 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 4, 0x0037},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame50 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 4, 0x0038},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame51 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 4, 0x0039},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame52 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 4, 0x003A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame53 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 4, 0x003B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 5, 0x003C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame55 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 4, 0x003D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame56 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 6, 0x003E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame57 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 4, 0x003F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame58 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 6, 0x0040},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame59 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 8, 0x0041},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame60 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 11, 0x0042},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame61 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 12, 0x0043},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame62 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 12, 0x0044},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame63 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 12, 0x0045},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame64 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x0046},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame65 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x0047},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame66 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 0, 0x0048},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame67 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -5, 0x0049},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame68 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -12, 0x004A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame69 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -15, 0x004B},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame70 = {
    {0x0200, 0x0000},
    {
        {0x0000, 10, 9, 0x004C},
        {0x0000, 1, -29, 0x004D},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame71 = {
    {0x0200, 0x0000},
    {
        {0x0000, 1, -30, 0x004E},
        {0x0000, 9, 9, 0x004F},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame72 = {
    {0x0200, 0x0000},
    {
        {0x0000, 1, -30, 0x0050},
        {0x0000, 10, 9, 0x004C},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame73 = {
    {0x0200, 0x0000},
    {
        {0x0000, 9, 9, 0x004F},
        {0x0000, 1, -30, 0x0051},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame74 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -6, 0x0052},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame75 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, -2, 0x0053},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame76 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 2, 0x0054},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame77 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 4, 0x0055},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame78 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 4, 0x0056},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame79 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 4, 0x0057},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x0058},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame81 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 4, 0x0059},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame82 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x005A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame83 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, -5, 0x005B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame84 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 4, 0x005C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame85 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 1, 0x005D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame86 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, 1, 0x005E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame87 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, 1, 0x005F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame88 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 10, 0x0060},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame89 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 7, 0x0061},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame90 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, 5, 0x0062},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame91 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 3, 0x0063},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame92 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 3, 0x0064},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame93 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x0065},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame94 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 3, 0x0066},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame95 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 3, 0x0067},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame96 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x0068},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame97 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 11, 0x0069},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame98 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 11, 0x0069},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame99 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 4, 0x006A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame100 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 4, 0x006A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame101 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 2, 0x006B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame102 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, 2, 0x006B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame103 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x006C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame104 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x006C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame105 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 2, 0x006D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame106 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, 2, 0x006D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame107 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 6, 0x006E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame108 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 5, 0x006F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame109 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, 5, 0x0070},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame110 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 5, 0x0071},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame111 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 4, 0x0072},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame112 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 4, 0x0073},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame113 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, 4, 0x0074},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame114 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 4, 0x0075},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame115 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 6, 0x0076},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame116 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 6, 0x0077},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame117 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 10, 0x0078},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame118 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 10, 0x0079},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame119 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, 13, 0x007A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame120 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 13, 0x007B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame121 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 13, 0x007C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame122 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 11, 0x007D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame123 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 7, 0x007E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame124 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, 10, 0x007F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame125 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 13, 0x0080},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame126 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 11, 0x0081},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame127 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 6, 0x0082},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame128 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 4, 0x0083},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame129 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x0084},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame130 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 0, 0x0085},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame131 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 1, 0x0086},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame132 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 3, 0x0087},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame133 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 3, 0x0088},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame134 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 4, 0x0089},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame135 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, -1, 0x008A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame136 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, 3, 0x008B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame137 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -1, 0x008C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame138 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0x008D},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame139 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -1, 0x008E},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame140 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -14, 0x008F},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame141 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -12, 0x0090},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame142 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, -8, 0x0091},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame143 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -3, 0x0092},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame144 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, -7, 0x0093},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame145 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -6, 0x0094},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame146 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x0095},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame147 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 3, 0x0096},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame148 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, 3, 0x0097},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame149 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, 3, 0x0098},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame150 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 3, 0x0099},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame151 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, 2, 0x009A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame152 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 3, 0x009B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame153 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, 2, 0x009C},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame154 = {
    {0x0300, 0x0000},
    {
        {0x0000, 5, 3, 0x009D},
        {0x0000, 29, -2, 0x009E},
        {0x0100, 50, -3, 0x009F},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame155 = {
    {0x0300, 0x0000},
    {
        {0x0000, 5, 3, 0x009D},
        {0x0000, 33, -2, 0x00A0},
        {0x0100, 54, -3, 0x00A1},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame156 = {
    {0x0300, 0x0000},
    {
        {0x0000, 5, 3, 0x009D},
        {0x0000, 33, -2, 0x00A2},
        {0x0100, 57, -3, 0x00A3},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame157 = {
    {0x0300, 0x0000},
    {
        {0x0000, 5, 3, 0x009D},
        {0x0000, 33, -2, 0x00A4},
        {0x0100, 59, -3, 0x00A5},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame158 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 0, 0x00A6},
        {0x0000, 27, -2, 0x00A7},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame159 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -1, 0x00A8},
        {0x0000, 27, -2, 0x00A7},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame160 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 3, 0x00A9},
        {0x0000, 27, -2, 0x00A7},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame161 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, 3, 0x00AA},
        {0x0000, 27, -2, 0x00A7},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame162 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, 3, 0x00AB},
        {0x0000, 27, -2, 0x00A7},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame163 = {
    {0x0400, 0x0000},
    {
        {0x0000, 11, 3, 0x00AC},
        {0x0000, 0, -3, 0x00AD},
        {0x0000, 27, -2, 0x00A7},
        {0x0000, -5, 11, 0x00AE},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame164 = {
    {0x0400, 0x0000},
    {
        {0x0000, 11, 3, 0x00AC},
        {0x0000, 0, -3, 0x00AD},
        {0x0000, 27, -2, 0x00A7},
        {0x0000, -4, 11, 0x00AF},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame165 = {
    {0x0400, 0x0000},
    {
        {0x0000, 11, 3, 0x00AC},
        {0x0000, 0, -3, 0x00AD},
        {0x0000, 27, -2, 0x00A7},
        {0x0000, 1, 13, 0x00B0},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame166 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 11, 0x00B1},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame167 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, 12, 0x00B2},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame168 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 13, 0x00B3},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame169 = {
    {0x0200, 0x0000},
    {
        {0x0000, 0, 13, 0x00B4},
        {0x0000, 23, 15, 0x00B5},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame170 = {
    {0x0200, 0x0000},
    {
        {0x0000, 2, 13, 0x00B6},
        {0x0000, 23, 15, 0x00B5},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame171 = {
    {0x0200, 0x0000},
    {
        {0x0000, 1, 13, 0x00B7},
        {0x0000, 23, 15, 0x00B5},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame172 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 1, 0x00B8},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame173 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 1, 0x00B9},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame174 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x00BA},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame175 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 3, 0x00BB},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame176 = {
    {0x0100, 0x0000},
    {
        {0x0200, -3, -3, 0x00BC},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame177 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -4, 0x00BD},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame178 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -2, 0x00BE},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame179 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 1, 0x00BF},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame180 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 1, 0x00C0},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame181 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, 1, 0x00C1},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame182 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, 1, 0x00C2},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame183 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 1, 0x00C3},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame184 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 3, 0x00C4},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame185 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -19, 0x00C5},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame186 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, -20, 0x00C6},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame187 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, -6, 0x00C7},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame188 = {
    {0x0100, 0x0000},
    {
        {0x0200, 0, -7, 0x00C8},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame189 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -6, 0x00C9},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame190 = {
    {0x0300, 0x0000},
    {
        {0x0200, 5, -28, 0x00CA},
        {0x0200, 6, 5, 0x00CB},
        {0x0200, 3, 21, 0x00CC},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame191 = {
    {0x0300, 0x0000},
    {
        {0x0000, 4, -28, 0x00CE},
        {0x0000, 7, 5, 0x00CF},
        {0x0000, 3, 21, 0x00CC},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame192 = {
    {0x0300, 0x0000},
    {
        {0x0200, 5, -28, 0x00D1},
        {0x0200, 4, 5, 0x00D2},
        {0x0200, 3, 21, 0x00CC},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame193 = {
    {0x0300, 0x0000},
    {
        {0x0000, 1, -27, 0x00D4},
        {0x0000, 7, 5, 0x00CF},
        {0x0000, 3, 21, 0x00CC},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame194 = {
    {0x0400, 0x0000},
    {
        {0x0000, 4, -25, 0x00D6},
        {0x0000, 5, -3, 0x00D7},
        {0x0000, 6, 9, 0x00D8},
        {0x0000, 3, 21, 0x00CC},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame195 = {
    {0x0400, 0x0000},
    {
        {0x0000, 6, -24, 0x00D9},
        {0x0000, 5, -3, 0x00D7},
        {0x0000, 6, 9, 0x00DA},
        {0x0000, 3, 21, 0x00CC},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame196 = {
    {0x0400, 0x0000},
    {
        {0x0000, 4, -21, 0x00DB},
        {0x0000, 5, -3, 0x00D7},
        {0x0000, 7, 9, 0x00DC},
        {0x0000, 3, 21, 0x00CC},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame197 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -1, 0x00DD},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame198 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x00DF},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame199 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 3, 0x00E1},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame200 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 2, 0x00E2},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame201 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x00E3},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame202 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 3, 0x00E4},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame203 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 3, 0x00E5},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame204 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x00E6},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame205 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x00E7},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame206 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x00E8},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame207 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x00E9},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame208 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x00EA},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame209 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 0x00EB},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame210 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 3, 0x00EC},
        {0x0000, 13, -6, 0x00ED},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame211 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 3, 0x00EC},
        {0x0000, 12, -7, 0x00EE},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame212 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 3, 0x00EC},
        {0x0000, 11, -8, 0x00EF},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame213 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 3, 0x00EC},
        {0x0000, 8, -9, 0x00F0},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame214 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 3, 0x00EC},
        {0x0000, 9, -9, 0x00F1},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame215 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 3, 0x00EC},
        {0x0000, 11, -7, 0x00F2},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame216 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 3, 0x00EC},
        {0x0000, 15, -8, 0x00F3},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame217 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, 3, 0x00EC},
        {0x0000, 15, -9, 0x00F4},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame218 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 3, 0x00F5},
        {0x0000, 10, -14, 0x00F6},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame219 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 3, 0x00F5},
        {0x0000, 11, -16, 0x00F7},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame220 = {
    {0x0200, 0x0000},
    {
        {0x0000, 5, 3, 0x00F5},
        {0x0000, 11, -16, 0x00F8},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame221 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 4, 0x00F9},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame222 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 4, 0x00FA},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame223 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 4, 0x00FB},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame224 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame225 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 14, -9, 0x00FE},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame226 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 14, -9, 0x00FF},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame227 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 14, -9, 0x0100},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame228 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 10, -9, 0x0101},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame229 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 10, -10, 0x0102},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame230 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 10, -11, 0x0103},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame231 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 10, -9, 0x0104},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame232 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 10, -8, 0x0105},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame233 = {
    {0x0200, 0x0000},
    {
        {0x0000, 6, 3, 0x00FD},
        {0x0000, 10, -7, 0x0106},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame234 = {
    {0x0300, 0x0000},
    {
        {0x0000, 6, 3, 0x0107},
        {0x0000, 10, -7, 0x0106},
        {0x0000, 1, -6, 0x0108},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame235 = {
    {0x0300, 0x0000},
    {
        {0x0000, 6, 3, 0x0107},
        {0x0000, 10, -7, 0x0106},
        {0x0000, 2, -7, 0x0109},
    },
};

SaturnSpriteFrame3 g_Stage14SpriteBank21Frame236 = {
    {0x0300, 0x0000},
    {
        {0x0000, 6, 3, 0x0107},
        {0x0000, 10, -7, 0x0106},
        {0x0000, 6, -7, 0x010A},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame237 = {
    {0x0200, 0x0000},
    {
        {0x0100, -5, 1, 0x010B},
        {0x0000, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame238 = {
    {0x0200, 0x0000},
    {
        {0x0100, -2, 1, 0x010C},
        {0x0200, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame239 = {
    {0x0200, 0x0000},
    {
        {0x0100, -3, 1, 0x010D},
        {0x0000, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame240 = {
    {0x0200, 0x0000},
    {
        {0x0100, -5, 1, 0x010E},
        {0x0200, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame241 = {
    {0x0200, 0x0000},
    {
        {0x0100, -4, 0, 0x010F},
        {0x0000, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame242 = {
    {0x0200, 0x0000},
    {
        {0x0100, -4, 0, 0x0110},
        {0x0200, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame243 = {
    {0x0200, 0x0000},
    {
        {0x0100, -4, -1, 0x0111},
        {0x0000, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame244 = {
    {0x0200, 0x0000},
    {
        {0x0100, -2, -1, 0x0112},
        {0x0200, 4, 5, 0x00FC},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame245 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 5, 0x0113},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame246 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, 5, 0x0114},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame247 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 6, 0x0115},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame248 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, 7, 0x0116},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame249 = {
    {0x0200, 0x0000},
    {
        {0x0000, 0, 7, 0x0117},
        {0x0000, 23, -4, 0x0118},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame250 = {
    {0x0200, 0x0000},
    {
        {0x0200, 22, -4, 0x0118},
        {0x0200, 5, 1, 0x0119},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame251 = {
    {0x0200, 0x0000},
    {
        {0x0000, 22, -4, 0x0118},
        {0x0000, 5, -1, 0x011A},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame252 = {
    {0x0200, 0x0000},
    {
        {0x0000, 22, -4, 0x0118},
        {0x0000, 5, -1, 0x011B},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame253 = {
    {0x0200, 0x0000},
    {
        {0x0000, 22, -4, 0x0118},
        {0x0000, 5, 3, 0x011C},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame254 = {
    {0x0200, 0x0000},
    {
        {0x0000, 22, -4, 0x0118},
        {0x0000, 5, 7, 0x011D},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame255 = {
    {0x0200, 0x0000},
    {
        {0x0000, 22, -4, 0x0118},
        {0x0000, 5, 7, 0x011E},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame256 = {
    {0x0200, 0x0000},
    {
        {0x0000, 22, -4, 0x0118},
        {0x0000, 5, 7, 0x011F},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame257 = {
    {0x0200, 0x0000},
    {
        {0x0000, 1, 18, 0x0120},
        {0x0000, 1, 9, 0x0121},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame258 = {
    {0x0200, 0x0000},
    {
        {0x0000, 1, 18, 0x0120},
        {0x0000, 1, 10, 0x0121},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame259 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 13, 0x0122},
    },
};

SaturnSpriteFrame2 g_Stage14SpriteBank21Frame260 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, 13, 0x0123},
        {0x0000, 20, 19, 0x0124},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame261 = {
    {0x0400, 0x0000},
    {
        {0x0000, 3, 3, 0x0125},
        {0x0400, -8, -12, 0x0126},
        {0x0400, -19, -17, 0x0127},
        {0x0400, -8, -4, 0x0128},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame262 = {
    {0x0400, 0x0000},
    {
        {0x0200, 3, 3, 0x0125},
        {0x0410, -13, -12, 0x0126},
        {0x0400, -4, -19, 0x0129},
        {0x0400, -15, -6, 0x012A},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame263 = {
    {0x0500, 0x0000},
    {
        {0x0000, 3, 3, 0x0125},
        {0x0420, -8, -12, 0x0126},
        {0x0410, -5, -5, 0x0127},
        {0x0420, -13, -18, 0x0129},
        {0x0430, -3, -16, 0x0127},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame264 = {
    {0x0500, 0x0000},
    {
        {0x0200, 3, 3, 0x0125},
        {0x0430, -13, -12, 0x0126},
        {0x0410, -2, -18, 0x012A},
        {0x0410, -14, -3, 0x0128},
        {0x0420, -17, -17, 0x0127},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame265 = {
    {0x0500, 0x0000},
    {
        {0x0000, 5, 3, 0x012B},
        {0x0420, 9, -7, 0x0126},
        {0x0410, 12, 0, 0x0127},
        {0x0420, 4, -13, 0x0129},
        {0x0430, 14, -11, 0x0127},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame266 = {
    {0x0400, 0x0000},
    {
        {0x0200, 10, 3, 0x012C},
        {0x0410, 16, -8, 0x0126},
        {0x0400, 25, -15, 0x0129},
        {0x0400, 14, -2, 0x012A},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame267 = {
    {0x0500, 0x0000},
    {
        {0x0000, 18, 4, 0x012D},
        {0x0430, 28, -6, 0x0126},
        {0x0410, 39, -12, 0x012A},
        {0x0410, 27, 3, 0x0128},
        {0x0420, 24, -11, 0x0127},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame268 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 3, 0x0125},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame269 = {
    {0x0100, 0x0000},
    {
        {0x0200, 3, 3, 0x0125},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame270 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 3, 0x012E},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame271 = {
    {0x0400, 0x0000},
    {
        {0x0200, 14, 2, 0x012F},
        {0x0400, 44, -8, 0x0130},
        {0x0420, 50, -13, 0x0131},
        {0x0420, 40, 5, 0x0132},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame272 = {
    {0x0500, 0x0000},
    {
        {0x0000, 14, 4, 0x0133},
        {0x0410, 33, -8, 0x0130},
        {0x0430, 31, -17, 0x0134},
        {0x0420, 41, 4, 0x0132},
        {0x0420, 56, -14, 0x0135},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame273 = {
    {0x0400, 0x0000},
    {
        {0x0200, 17, 2, 0x0136},
        {0x0420, 44, -6, 0x0130},
        {0x0430, 40, -22, 0x0134},
        {0x0410, 53, 9, 0x0127},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame274 = {
    {0x0500, 0x0000},
    {
        {0x0000, 14, 2, 0x0137},
        {0x0430, 34, -6, 0x0130},
        {0x0430, 29, 4, 0x0131},
        {0x0400, 42, -11, 0x0134},
        {0x0400, 37, -25, 0x0129},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame275 = {
    {0x0400, 0x0000},
    {
        {0x0200, 14, 2, 0x012F},
        {0x0400, 42, -7, 0x0138},
        {0x0400, 50, -15, 0x0131},
        {0x0400, 32, -18, 0x0135},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame276 = {
    {0x0400, 0x0000},
    {
        {0x0000, 14, 4, 0x0133},
        {0x0420, 41, -6, 0x0139},
        {0x0420, 42, -11, 0x0134},
        {0x0410, 31, -16, 0x0128},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame277 = {
    {0x0400, 0x0000},
    {
        {0x0200, 17, 2, 0x0136},
        {0x0420, 42, -5, 0x0138},
        {0x0410, 36, 4, 0x0134},
        {0x0400, 47, -1, 0x0134},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame278 = {
    {0x0500, 0x0000},
    {
        {0x0000, 14, 2, 0x0137},
        {0x0400, 41, -8, 0x0139},
        {0x0420, 37, -3, 0x0132},
        {0x0410, 49, -3, 0x012A},
        {0x0420, 34, -19, 0x0127},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame279 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 4, 0x013A},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame280 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 4, 0x013B},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame281 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 3, 0x012C},
    },
};

SaturnSpriteFrame1 g_Stage14SpriteBank21Frame282 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 3, 0x012B},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame283 = {
    {0x0400, 0x0000},
    {
        {0x0000, 13, 2, 0x013C},
        {0x0400, 40, -10, 0x0130},
        {0x0420, 46, -15, 0x0131},
        {0x0420, 36, 3, 0x0132},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame284 = {
    {0x0500, 0x0000},
    {
        {0x0200, 13, 2, 0x013C},
        {0x0410, 31, -10, 0x0130},
        {0x0430, 29, -19, 0x0134},
        {0x0420, 39, 2, 0x0132},
        {0x0420, 54, -16, 0x0135},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame285 = {
    {0x0400, 0x0000},
    {
        {0x0000, 13, 2, 0x013C},
        {0x0420, 42, -8, 0x0130},
        {0x0430, 38, -24, 0x0134},
        {0x0410, 51, 7, 0x0127},
    },
};

SaturnSpriteFrame5 g_Stage14SpriteBank21Frame286 = {
    {0x0500, 0x0000},
    {
        {0x0200, 13, 2, 0x013C},
        {0x0430, 31, -9, 0x0130},
        {0x0430, 26, 1, 0x0131},
        {0x0400, 39, -14, 0x0134},
        {0x0400, 34, -28, 0x0129},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame287 = {
    {0x0400, 0x0000},
    {
        {0x0000, 13, 2, 0x013C},
        {0x0400, 39, -10, 0x0138},
        {0x0400, 47, -18, 0x0131},
        {0x0400, 29, -21, 0x0135},
    },
};

SaturnSpriteFrame4 g_Stage14SpriteBank21Frame288 = {
    {0x0400, 0x0000},
    {
        {0x0200, 13, 2, 0x013C},
        {0x0420, 38, -9, 0x0139},
        {0x0420, 39, -14, 0x0134},
        {0x0410, 28, -19, 0x0128},
    },
};

SaturnSpriteFrameHeader* g_Stage14SpriteBank21Frames[289] = {
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame0,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame1,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame2,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame3,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame4,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame5,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame6,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame7,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame8,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame9,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame10,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame11,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame12,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame13,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame14,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame15,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame16,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame17,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame18,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame19,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame20,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame21,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame22,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame23,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame24,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame25,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame26,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame27,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame28,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame29,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame30,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame31,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame32,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame33,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame34,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame35,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame36,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame37,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame38,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame39,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame40,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame41,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame42,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame43,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame44,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame45,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame46,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame47,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame48,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame49,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame50,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame51,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame52,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame53,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame54,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame55,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame56,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame57,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame58,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame59,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame60,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame61,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame62,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame63,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame64,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame65,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame66,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame67,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame68,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame69,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame70,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame71,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame72,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame73,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame74,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame75,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame76,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame77,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame78,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame79,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame80,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame81,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame82,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame83,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame84,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame85,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame86,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame87,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame88,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame89,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame90,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame91,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame92,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame93,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame94,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame95,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame96,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame97,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame98,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame99,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame100,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame101,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame102,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame103,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame104,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame105,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame106,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame107,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame108,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame109,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame110,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame111,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame112,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame113,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame114,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame115,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame116,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame117,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame118,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame119,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame120,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame121,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame122,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame123,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame124,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame125,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame126,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame127,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame128,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame129,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame130,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame131,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame132,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame133,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame134,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame135,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame136,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame137,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame138,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame139,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame140,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame141,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame142,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame143,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame144,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame145,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame146,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame147,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame148,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame149,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame150,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame151,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame152,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame153,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame154,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame155,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame156,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame157,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame158,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame159,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame160,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame161,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame162,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame163,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame164,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame165,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame166,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame167,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame168,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame169,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame170,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame171,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame172,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame173,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame174,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame175,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame176,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame177,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame178,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame179,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame180,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame181,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame182,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame183,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame184,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame185,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame186,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame187,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame188,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame189,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame190,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame191,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame192,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame193,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame194,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame195,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame196,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame197,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame198,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame199,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame200,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame201,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame202,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame203,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame204,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame205,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame206,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame207,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame208,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame209,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame210,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame211,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame212,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame213,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame214,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame215,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame216,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame217,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame218,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame219,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame220,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame221,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame222,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame223,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame224,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame225,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame226,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame227,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame228,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame229,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame230,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame231,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame232,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame233,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame234,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame235,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame236,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame237,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame238,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame239,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame240,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame241,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame242,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame243,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame244,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame245,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame246,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame247,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame248,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame249,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame250,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame251,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame252,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame253,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame254,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame255,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame256,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame257,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame258,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame259,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame260,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame261,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame262,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame263,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame264,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame265,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame266,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame267,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame268,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame269,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame270,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame271,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame272,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame273,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame274,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame275,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame276,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame277,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame278,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame279,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame280,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame281,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame282,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame283,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame284,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame285,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame286,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame287,
    (SaturnSpriteFrameHeader*)&g_Stage14SpriteBank21Frame288,
};

SaturnSpriteImage g_Stage14SpriteBank21Images[318] = {
    {0x08, 0x11, 0x0000}, {0x08, 0x07, 0x0024}, {0x0C, 0x17, 0x0034},
    {0x0C, 0x17, 0x007C}, {0x0C, 0x17, 0x00C4}, {0x0C, 0x17, 0x010C},
    {0x0C, 0x17, 0x0154}, {0x08, 0x0F, 0x019C}, {0x08, 0x0F, 0x01BC},
    {0x08, 0x0F, 0x01DC}, {0x08, 0x0F, 0x01FC}, {0x0C, 0x10, 0x021C},
    {0x0C, 0x0F, 0x024C}, {0x0C, 0x16, 0x027C}, {0x10, 0x14, 0x02C0},
    {0x10, 0x13, 0x0310}, {0x10, 0x16, 0x035C}, {0x14, 0x14, 0x03B4},
    {0x10, 0x16, 0x0418}, {0x14, 0x16, 0x0470}, {0x10, 0x16, 0x04E0},
    {0x14, 0x14, 0x0538}, {0x10, 0x16, 0x059C}, {0x10, 0x16, 0x05F4},
    {0x0C, 0x0F, 0x064C}, {0x0C, 0x0A, 0x067C}, {0x0C, 0x0B, 0x069C},
    {0x10, 0x0B, 0x06C0}, {0x14, 0x0B, 0x06EC}, {0x08, 0x17, 0x0724},
    {0x0C, 0x16, 0x0754}, {0x0C, 0x16, 0x0798}, {0x0C, 0x16, 0x07DC},
    {0x0C, 0x17, 0x0820}, {0x0C, 0x17, 0x0868}, {0x0C, 0x17, 0x08B0},
    {0x0C, 0x16, 0x08F8}, {0x0C, 0x16, 0x093C}, {0x0C, 0x16, 0x0980},
    {0x0C, 0x17, 0x09C4}, {0x08, 0x17, 0x0A0C}, {0x0C, 0x0F, 0x0A3C},
    {0x08, 0x0B, 0x0A6C}, {0x0C, 0x16, 0x0A84}, {0x0C, 0x16, 0x0AC8},
    {0x0C, 0x16, 0x0B0C}, {0x0C, 0x16, 0x0B50}, {0x10, 0x15, 0x0B94},
    {0x10, 0x15, 0x0BE8}, {0x10, 0x15, 0x0C3C}, {0x10, 0x15, 0x0C90},
    {0x10, 0x15, 0x0CE4}, {0x10, 0x15, 0x0D38}, {0x10, 0x15, 0x0D8C},
    {0x0C, 0x15, 0x0DE0}, {0x0C, 0x15, 0x0E20}, {0x0C, 0x15, 0x0E60},
    {0x0C, 0x15, 0x0EA0}, {0x0C, 0x15, 0x0EE0}, {0x10, 0x15, 0x0F20},
    {0x10, 0x14, 0x0F74}, {0x10, 0x15, 0x0FC4}, {0x0C, 0x13, 0x1018},
    {0x0C, 0x15, 0x1054}, {0x0C, 0x14, 0x1094}, {0x0C, 0x12, 0x10D0},
    {0x0C, 0x0E, 0x1108}, {0x0C, 0x0E, 0x1134}, {0x0C, 0x0E, 0x1160},
    {0x08, 0x0E, 0x118C}, {0x08, 0x17, 0x11A8}, {0x08, 0x17, 0x11D8},
    {0x10, 0x16, 0x1208}, {0x10, 0x18, 0x1260}, {0x0C, 0x1F, 0x12C0},
    {0x0C, 0x26, 0x1320}, {0x0C, 0x10, 0x1394}, {0x08, 0x17, 0x13C4},
    {0x08, 0x17, 0x13F4}, {0x0C, 0x10, 0x1424}, {0x08, 0x17, 0x1454},
    {0x08, 0x17, 0x1484}, {0x0C, 0x20, 0x14B4}, {0x10, 0x1B, 0x1514},
    {0x10, 0x17, 0x1580}, {0x0C, 0x16, 0x15DC}, {0x0C, 0x16, 0x1620},
    {0x0C, 0x16, 0x1664}, {0x08, 0x17, 0x16A8}, {0x0C, 0x16, 0x16D8},
    {0x0C, 0x16, 0x171C}, {0x0C, 0x1F, 0x1760}, {0x0C, 0x15, 0x17C0},
    {0x0C, 0x19, 0x1800}, {0x0C, 0x19, 0x184C}, {0x0C, 0x19, 0x1898},
    {0x0C, 0x0F, 0x18E4}, {0x0C, 0x12, 0x1914}, {0x0C, 0x14, 0x194C},
    {0x0C, 0x16, 0x1988}, {0x0C, 0x17, 0x19CC}, {0x0C, 0x17, 0x1A14},
    {0x08, 0x17, 0x1A5C}, {0x0C, 0x17, 0x1A8C}, {0x08, 0x17, 0x1AD4},
    {0x10, 0x0F, 0x1B04}, {0x10, 0x15, 0x1B40}, {0x14, 0x17, 0x1B94},
    {0x0C, 0x16, 0x1C08}, {0x14, 0x17, 0x1C4C}, {0x10, 0x15, 0x1CC0},
    {0x14, 0x14, 0x1D14}, {0x14, 0x13, 0x1D78}, {0x10, 0x14, 0x1DD8},
    {0x18, 0x16, 0x1E28}, {0x18, 0x16, 0x1EAC}, {0x14, 0x16, 0x1F30},
    {0x10, 0x15, 0x1FA0}, {0x10, 0x13, 0x1FF4}, {0x10, 0x13, 0x2040},
    {0x0C, 0x0F, 0x208C}, {0x0C, 0x0F, 0x20BC}, {0x14, 0x0D, 0x20EC},
    {0x18, 0x0C, 0x2130}, {0x18, 0x0C, 0x2178}, {0x14, 0x0E, 0x21C0},
    {0x14, 0x15, 0x2208}, {0x18, 0x11, 0x2274}, {0x14, 0x0D, 0x22DC},
    {0x10, 0x0F, 0x2320}, {0x10, 0x13, 0x235C}, {0x0C, 0x15, 0x23A8},
    {0x0C, 0x17, 0x23E8}, {0x08, 0x19, 0x2430}, {0x0C, 0x19, 0x2464},
    {0x08, 0x17, 0x24B0}, {0x0C, 0x17, 0x24E0}, {0x14, 0x16, 0x2528},
    {0x14, 0x16, 0x2598}, {0x20, 0x12, 0x2608}, {0x20, 0x16, 0x2698},
    {0x18, 0x17, 0x2748}, {0x14, 0x14, 0x27D4}, {0x20, 0x14, 0x2838},
    {0x24, 0x11, 0x28D8}, {0x18, 0x17, 0x2974}, {0x14, 0x15, 0x2A00},
    {0x1C, 0x14, 0x2A6C}, {0x14, 0x17, 0x2AF8}, {0x0C, 0x17, 0x2B6C},
    {0x0C, 0x17, 0x2BB4}, {0x10, 0x17, 0x2BFC}, {0x18, 0x17, 0x2C58},
    {0x1C, 0x17, 0x2CE4}, {0x10, 0x17, 0x2D88}, {0x10, 0x17, 0x2DE4},
    {0x10, 0x17, 0x2E40}, {0x14, 0x17, 0x2E9C}, {0x08, 0x02, 0x2F10},
    {0x04, 0x02, 0x2F14}, {0x0C, 0x02, 0x2F18}, {0x04, 0x02, 0x2F20},
    {0x0C, 0x02, 0x2F24}, {0x04, 0x02, 0x2F2C}, {0x0C, 0x02, 0x2F30},
    {0x04, 0x02, 0x2F38}, {0x14, 0x19, 0x2F3C}, {0x08, 0x02, 0x2FBC},
    {0x14, 0x1A, 0x2FC0}, {0x14, 0x17, 0x3044}, {0x10, 0x17, 0x30B8},
    {0x10, 0x17, 0x3114}, {0x0C, 0x17, 0x3170}, {0x04, 0x0D, 0x31B8},
    {0x04, 0x02, 0x31C8}, {0x04, 0x04, 0x31CC}, {0x04, 0x06, 0x31D0},
    {0x0C, 0x0F, 0x31D8}, {0x10, 0x0E, 0x3208}, {0x14, 0x0D, 0x3240},
    {0x0C, 0x0D, 0x3284}, {0x10, 0x0B, 0x32AC}, {0x0C, 0x0D, 0x32D8},
    {0x08, 0x0D, 0x3300}, {0x08, 0x19, 0x331C}, {0x08, 0x19, 0x3350},
    {0x0C, 0x17, 0x3384}, {0x10, 0x17, 0x33CC}, {0x10, 0x1C, 0x3428},
    {0x14, 0x1D, 0x3498}, {0x10, 0x1B, 0x352C}, {0x10, 0x18, 0x3598},
    {0x10, 0x18, 0x35F8}, {0x0C, 0x18, 0x3658}, {0x0C, 0x18, 0x36A0},
    {0x08, 0x18, 0x36E8}, {0x0C, 0x17, 0x3718}, {0x1C, 0x19, 0x3760},
    {0x1C, 0x19, 0x3810}, {0x10, 0x1E, 0x38C0}, {0x10, 0x1F, 0x3938},
    {0x0C, 0x1E, 0x39B4}, {0x08, 0x16, 0x3A10}, {0x0C, 0x0C, 0x3A3C},
    {0x08, 0x04, 0x3A60}, {0x10, 0x05, 0x3A68}, {0x08, 0x16, 0x3A7C},
    {0x0C, 0x0C, 0x3AA8}, {0x10, 0x05, 0x3ACC}, {0x08, 0x16, 0x3AE0},
    {0x08, 0x0C, 0x3B0C}, {0x10, 0x04, 0x3B24}, {0x08, 0x14, 0x3B34},
    {0x10, 0x05, 0x3B5C}, {0x08, 0x12, 0x3B70}, {0x08, 0x04, 0x3B94},
    {0x0C, 0x08, 0x3B9C}, {0x0C, 0x11, 0x3BB4}, {0x0C, 0x08, 0x3BE8},
    {0x0C, 0x0F, 0x3C00}, {0x0C, 0x08, 0x3C30}, {0x0C, 0x1B, 0x3C48},
    {0x10, 0x02, 0x3C9C}, {0x0C, 0x17, 0x3CA4}, {0x10, 0x02, 0x3CEC},
    {0x0C, 0x17, 0x3CF4}, {0x08, 0x17, 0x3D3C}, {0x0C, 0x17, 0x3D6C},
    {0x0C, 0x17, 0x3DB4}, {0x0C, 0x17, 0x3DFC}, {0x0C, 0x17, 0x3E44},
    {0x0C, 0x17, 0x3E8C}, {0x0C, 0x17, 0x3ED4}, {0x0C, 0x17, 0x3F1C},
    {0x0C, 0x17, 0x3F64}, {0x0C, 0x17, 0x3FAC}, {0x08, 0x17, 0x3FF4},
    {0x08, 0x04, 0x4024}, {0x08, 0x03, 0x402C}, {0x08, 0x02, 0x4034},
    {0x04, 0x02, 0x4038}, {0x04, 0x02, 0x403C}, {0x04, 0x03, 0x4040},
    {0x08, 0x02, 0x4044}, {0x08, 0x02, 0x4048}, {0x08, 0x16, 0x404C},
    {0x04, 0x07, 0x4078}, {0x04, 0x09, 0x4080}, {0x04, 0x0A, 0x408C},
    {0x0C, 0x15, 0x4098}, {0x0C, 0x15, 0x40D8}, {0x0C, 0x15, 0x4118},
    {0x0C, 0x15, 0x4158}, {0x0C, 0x17, 0x4198}, {0x08, 0x03, 0x41E0},
    {0x08, 0x03, 0x41E8}, {0x08, 0x03, 0x41F0}, {0x04, 0x04, 0x41F8},
    {0x04, 0x04, 0x41FC}, {0x04, 0x04, 0x4200}, {0x04, 0x03, 0x4204},
    {0x04, 0x04, 0x4208}, {0x04, 0x05, 0x420C}, {0x0C, 0x17, 0x4214},
    {0x08, 0x04, 0x425C}, {0x08, 0x04, 0x4264}, {0x0C, 0x05, 0x426C},
    {0x04, 0x04, 0x427C}, {0x08, 0x05, 0x4280}, {0x08, 0x06, 0x428C},
    {0x08, 0x08, 0x4298}, {0x0C, 0x0A, 0x42A8}, {0x10, 0x0F, 0x42C8},
    {0x14, 0x14, 0x4304}, {0x1C, 0x19, 0x4368}, {0x0C, 0x15, 0x4418},
    {0x10, 0x14, 0x4458}, {0x10, 0x13, 0x44A8}, {0x18, 0x13, 0x44F4},
    {0x10, 0x12, 0x4568}, {0x08, 0x07, 0x45B0}, {0x0C, 0x18, 0x45C0},
    {0x0C, 0x1A, 0x4608}, {0x0C, 0x1B, 0x4658}, {0x0C, 0x17, 0x46AC},
    {0x0C, 0x12, 0x46F4}, {0x0C, 0x12, 0x472C}, {0x0C, 0x12, 0x4764},
    {0x0C, 0x07, 0x479C}, {0x08, 0x0E, 0x47B4}, {0x14, 0x0D, 0x47D0},
    {0x0C, 0x0C, 0x4814}, {0x10, 0x07, 0x4838}, {0x0C, 0x16, 0x4854},
    {0x0C, 0x09, 0x4898}, {0x04, 0x04, 0x48B4}, {0x04, 0x05, 0x48B8},
    {0x08, 0x04, 0x48C0}, {0x04, 0x07, 0x48C8}, {0x0C, 0x17, 0x48D0},
    {0x0C, 0x17, 0x4918}, {0x14, 0x16, 0x4960}, {0x10, 0x16, 0x49D0},
    {0x18, 0x18, 0x4A28}, {0x10, 0x11, 0x4AB8}, {0x0C, 0x07, 0x4AFC},
    {0x04, 0x0B, 0x4B14}, {0x18, 0x16, 0x4B20}, {0x0C, 0x0A, 0x4BA4},
    {0x08, 0x04, 0x4BC4}, {0x14, 0x17, 0x4BCC}, {0x14, 0x17, 0x4C40},
    {0x10, 0x11, 0x4CB4}, {0x0C, 0x0C, 0x4CF8}, {0x14, 0x16, 0x4D1C},
    {0x14, 0x16, 0x4D8C}, {0x18, 0x16, 0x4DFC}, {0x00, 0x00, 0x4E80},
};
