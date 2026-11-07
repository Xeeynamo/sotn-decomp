// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D612C();
void func_060D6B70();
void func_060D6B8C();
void func_060D6D64();
void func_060D6D7C();
void func_060D6D94();
void func_060D6DAC();
void func_060D6DB8();
void func_060D6DD0();
void func_060D6DE8();
void func_060D6E00();
void func_060D6E18();
void func_060D6E30();
void func_060D6E48();
void func_060D6E60();
void func_060D6E78();
extern SaturnSpriteResource* DAT_060D7648[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D612C,
        func_060D6B70,
        func_060D6B8C,
        func_060D6D64,
        func_060D6D7C,
        func_060D6D94,
        func_060D6DAC,
        func_060D6E78,
        func_060D6DB8,
        func_060D6DD0,
        func_060D6DE8,
        func_060D6E00,
        func_060D6E18,
        func_060D6E30,
        func_060D6E48,
        func_060D6E60,
    },
    DAT_060D7648,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D612C, func_060D612C);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6B70, func_060D6B70);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6B8C, func_060D6B8C);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6D64, func_060D6D64);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6D7C, func_060D6D7C);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6D94, func_060D6D94);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6DAC, func_060D6DAC);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6DB8, func_060D6DB8);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6DD0, func_060D6DD0);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6DE8, func_060D6DE8);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6E00, func_060D6E00);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6E18, func_060D6E18);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6E30, func_060D6E30);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6E48, func_060D6E48);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6E60, func_060D6E60);
INCLUDE_ASM("asm/saturn/weapon/w_21/f_nonmat", f60D6E78, func_060D6E78);

u32 DAT_060D6E90[215] = {
    0x00040001, 0x00040002, 0x00040003, 0x00040004, 0x00000000, 0x00040005,
    0x00040006, 0x00040007, 0x00040008, 0x00030005, 0x00030006, 0x00030007,
    0x00030008, 0x00020005, 0x00020006, 0x00020007, 0x00020008, 0x00030009,
    0x0003000A, 0x0003000B, 0x00020009, 0x0002000A, 0x0002000B, 0x00020009,
    0x0002000A, 0x0002000B, 0x00010009, 0x0001000A, 0x0001000B, 0xFFFF0000,
    0x0020000A, 0x0040000C, 0x0018000A, 0xFFFF0000, 0x0020000A, 0x0040000D,
    0x0018000A, 0xFFFF0000, 0x00011019, 0x0001101A, 0x0001101B, 0x0001040E,
    0x0001060F, 0x00010810, 0x00010A11, 0x00010C12, 0x00010C13, 0x00010E14,
    0x00010E15, 0x00010616, 0xFFFF0000, 0x0001001E, 0x0001001F, 0x00010020,
    0x00000000, 0x00050017, 0x00040018, 0x00030019, 0x0003001A, 0x0003001B,
    0x0003001C, 0x00030019, 0x00050018, 0x00070017, 0x00000000, 0x00020022,
    0x00020023, 0x00020024, 0x00020025, 0x00020026, 0x00020027, 0x00020028,
    0x00020029, 0x00030022, 0x00030023, 0x00030024, 0x00030025, 0x00030026,
    0x00030027, 0x00030028, 0x00030029, 0x00040022, 0x00040023, 0x00040024,
    0x00040025, 0x00040026, 0x00050027, 0x00050028, 0x00050029, 0x00050022,
    0x00060023, 0x00060024, 0x00060025, 0x00070026, 0x00080027, 0x00090028,
    0x00190029, 0x00000000, 0x00800021, 0x00000000, 0x00000000, 0xF1F40000,
    0x00F31410, 0xAB330000, 0xFFDF0A24, 0x00DF0F24, 0xFF9B0966, 0x0154091E,
    0xE8ED0000, 0xB0FD0000, 0xC8B40000, 0xEDF10000, 0x81108117, 0x81188110,
    0x00030000, 0x00000006, 0x6F006F06, 0x0006000C, 0x6F066F0C, 0x000C0012,
    0x6F0C6F12, 0x00120018, 0x6F126F18, 0x0018001E, 0x6F186F1E, 0x001E0024,
    0x6F1E6F24, 0x0024002A, 0x6F246F2A, 0x002A0030, 0x6F2A6F30, 0x00300036,
    0x6F306F36, 0x0036003C, 0x6F366F3C, 0x003C0042, 0x6F3C6F42, 0x00420048,
    0x6F426F48, 0x0048004E, 0x6F486F4E, 0x004E0054, 0x6F4E6F54, 0x0054005A,
    0x6F546F5A, 0x005A0060, 0x6F5A6F60, 0x00600066, 0x6F606F66, 0x0066006C,
    0x6F666F6C, 0x006C0072, 0x6F6C6F72, 0x00720078, 0x6F726F78, 0x0078007E,
    0x6F786F7E, 0x007E0084, 0x6F7E6F84, 0x0084008A, 0x6F846F8A, 0x008A0090,
    0x6F8A6F90, 0x00900096, 0x6F906F96, 0x0096009C, 0x6F966F9C, 0x009C00A2,
    0x6F9C6FA2, 0x00000000, 0x00000100, 0x00000200, 0x00000300, 0x00000400,
    0x00000500, 0x00000600, 0x00000700, 0x00000800, 0x00000900, 0x00000A00,
    0x00000B00, 0x00000C00, 0x00000D00, 0x00000E00, 0x00000F00, 0x00001000,
    0x00001100, 0x00001200, 0x00001300, 0x00001400, 0x00001500, 0x00001600,
    0x00001700, 0x00001800, 0x00001900, 0x00000050, 0x00000044, 0x0000003C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

SaturnSpriteImage DAT_060D71EC[38] = {
    {4, 2, 0x0000},   {4, 2, 0x0004},   {4, 1, 0x0008},   {4, 2, 0x000C},
    {4, 2, 0x0010},   {4, 2, 0x0014},   {4, 2, 0x0018},   {4, 2, 0x001C},
    {4, 2, 0x0020},   {4, 1, 0x0024},   {4, 2, 0x0028},   {16, 9, 0x002C},
    {16, 9, 0x0050},  {4, 31, 0x0074},  {20, 7, 0x0094},  {24, 31, 0x00B8},
    {12, 30, 0x0174}, {12, 59, 0x01D0}, {12, 44, 0x0284}, {12, 44, 0x0308},
    {4, 19, 0x038C},  {4, 1, 0x03A0},   {4, 2, 0x03A4},   {8, 6, 0x03A8},
    {12, 9, 0x03B4},  {16, 11, 0x03D0}, {16, 11, 0x03FC}, {48, 51, 0x0428},
    {24, 31, 0x068C}, {4, 4, 0x0748},   {4, 5, 0x074C},   {8, 2, 0x0754},
    {4, 3, 0x0758},   {4, 4, 0x075C},   {4, 3, 0x0760},   {8, 1, 0x0764},
    {8, 2, 0x0768},   {0, 0, 0x076C},
};

struct {
    u16 countAndFlags;
    u16 colors[7][16];
    u16 padding[1];
} DAT_060D7284 = {
    0x0007,
    {
        {0x8581, 0x8426, 0x910E, 0x9973, 0x9DF9, 0xAA7E, 0xBEDE, 0xD73D, 0x8421,
         0x9083, 0xA528, 0xB5AC, 0xCA51, 0xDAD5, 0xEF7A, 0xFFFE},
        {0x9465, 0x8400, 0x8820, 0x8C21, 0x9041, 0x9442, 0x9863, 0x9C84, 0xD460,
         0xECC0, 0xF180, 0xF604, 0xFA85, 0xFF4B, 0xFFD5, 0xFFFF},
        {0x8280, 0x9CA5, 0xA4E7, 0xAD29, 0xB56B, 0xBDAD, 0xC1CF, 0xCA11, 0xD253,
         0xDA95, 0xE2D7, 0xFC00, 0xA938, 0xBDD8, 0x8C63, 0x9884},
        {0x8280, 0xCC84, 0xB4A5, 0xBCE7, 0xC529, 0xCD4B, 0xD58D, 0xD1F0, 0xCE74,
         0xCAD7, 0xCB5B, 0xFC00, 0x8C7F, 0x8C7F, 0xFC63, 0xE463},
        {0x0000, 0x86E1, 0x9D2A, 0x9971, 0xA5F5, 0xB277, 0xC2F8, 0xDB59, 0xB238,
         0x90C4, 0xA128, 0xB1AD, 0xCA50, 0xE96F, 0xDAD5, 0xE77A},
        {0x0000, 0x90E5, 0x8C88, 0x90A8, 0x98C8, 0x9CE8, 0xA508, 0xA52A, 0x98E9,
         0x8421, 0x8842, 0x8C63, 0x94A5, 0x98C6, 0x9CE7, 0xA529},
        {0x0000, 0xA2A9, 0xA0E7, 0xB150, 0xC5B3, 0xCA36, 0xCEB9, 0xD33B, 0xC218,
         0x9083, 0xA528, 0xADAC, 0xBA51, 0xF16B, 0xDAD5, 0xEF7A},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D7368 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D736C = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7378 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7384 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7390 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 3},
    },
};

SaturnSpriteFrame1 DAT_060D739C = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D73A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 5},
    },
};

SaturnSpriteFrame1 DAT_060D73B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 6},
    },
};

SaturnSpriteFrame1 DAT_060D73C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 7},
    },
};

SaturnSpriteFrame1 DAT_060D73CC = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 8},
    },
};

SaturnSpriteFrame1 DAT_060D73D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 9},
    },
};

SaturnSpriteFrame1 DAT_060D73E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 10},
    },
};

SaturnSpriteFrame2 DAT_060D73F0 = {
    {0x0200, 0x0000},
    {
        {0x0000, 9, -12, 11},
        {0x0000, 2, 0, 2},
    },
};

SaturnSpriteFrame2 DAT_060D7404 = {
    {0x0200, 0x0000},
    {
        {0x0000, 9, -12, 12},
        {0x0000, 2, 0, 2},
    },
};

SaturnSpriteFrame2 DAT_060D7418 = {
    {0x0200, 0x0000},
    {
        {0x0100, 1, -29, 13},
        {0x0100, 1, -5, 14},
    },
};

SaturnSpriteFrame2 DAT_060D742C = {
    {0x0200, 0x0000},
    {
        {0x0200, 1, -45, 15},
        {0x0110, 0, -29, 13},
    },
};

SaturnSpriteFrame1 DAT_060D7440 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, -28, 16},
    },
};

SaturnSpriteFrame2 DAT_060D744C = {
    {0x0200, 0x0000},
    {
        {0x0300, 1, -45, 15},
        {0x0130, -2, -29, 16},
    },
};

SaturnSpriteFrame2 DAT_060D7460 = {
    {0x0200, 0x0000},
    {
        {0x0100, 3, -57, 17},
        {0x0100, 3, -159, 18},
    },
};

SaturnSpriteFrame3 DAT_060D7474 = {
    {0x0300, 0x0000},
    {
        {0x0130, -3, -57, 17},
        {0x0200, 1, -45, 15},
        {0x0130, -3, -160, 19},
    },
};

SaturnSpriteFrame1 DAT_060D7490 = {
    {0x0100, 0x0000},
    {
        {0x0110, -2, -171, 16},
    },
};

SaturnSpriteFrame2 DAT_060D749C = {
    {0x0200, 0x0000},
    {
        {0x0300, 1, -45, 15},
        {0x0120, 3, -173, 16},
    },
};

SaturnSpriteFrame1 DAT_060D74B0 = {
    {0x0100, 0x0000},
    {
        {0x0130, 0, -186, 20},
    },
};

SaturnSpriteFrame1 DAT_060D74BC = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 1, 21},
    },
};

SaturnSpriteFrame1 DAT_060D74C8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 1, 22},
    },
};

SaturnSpriteFrame1 DAT_060D74D4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 1, 23},
    },
};

SaturnSpriteFrame1 DAT_060D74E0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 1, 24},
    },
};

SaturnSpriteFrame1 DAT_060D74EC = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 1, 25},
    },
};

SaturnSpriteFrame1 DAT_060D74F8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 26},
    },
};

SaturnSpriteFrame1 DAT_060D7504 = {
    {0x0100, 0x0000},
    {
        {0x0400, 9, -16, 27},
    },
};

SaturnSpriteFrame1 DAT_060D7510 = {
    {0x0100, 0x0000},
    {
        {0x0500, 9, -16, 27},
    },
};

SaturnSpriteFrame1 DAT_060D751C = {
    {0x0100, 0x0000},
    {
        {0x0600, 9, -16, 27},
    },
};

SaturnSpriteFrame1 DAT_060D7528 = {
    {0x0100, 0x0000},
    {
        {0x0400, 21, -12, 28},
    },
};

SaturnSpriteFrame1 DAT_060D7534 = {
    {0x0100, 0x0000},
    {
        {0x0400, -2, 1, 29},
    },
};

SaturnSpriteFrame1 DAT_060D7540 = {
    {0x0100, 0x0000},
    {
        {0x0400, -2, 2, 30},
    },
};

SaturnSpriteFrame1 DAT_060D754C = {
    {0x0100, 0x0000},
    {
        {0x0400, 3, 6, 31},
    },
};

SaturnSpriteFrame1 DAT_060D7558 = {
    {0x0100, 0x0000},
    {
        {0x0400, 6, 6, 32},
    },
};

SaturnSpriteFrame1 DAT_060D7564 = {
    {0x0100, 0x0000},
    {
        {0x0400, 9, 1, 33},
    },
};

SaturnSpriteFrame1 DAT_060D7570 = {
    {0x0100, 0x0000},
    {
        {0x0400, 6, -2, 34},
    },
};

SaturnSpriteFrame1 DAT_060D757C = {
    {0x0100, 0x0000},
    {
        {0x0400, 5, -4, 35},
    },
};

SaturnSpriteFrame1 DAT_060D7588 = {
    {0x0100, 0x0000},
    {
        {0x0400, 2, -3, 36},
    },
};

SaturnSpriteFrameHeader* DAT_060D7594[42] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7368,
    (SaturnSpriteFrameHeader*)&DAT_060D736C,
    (SaturnSpriteFrameHeader*)&DAT_060D7378,
    (SaturnSpriteFrameHeader*)&DAT_060D7384,
    (SaturnSpriteFrameHeader*)&DAT_060D7390,
    (SaturnSpriteFrameHeader*)&DAT_060D739C,
    (SaturnSpriteFrameHeader*)&DAT_060D73A8,
    (SaturnSpriteFrameHeader*)&DAT_060D73B4,
    (SaturnSpriteFrameHeader*)&DAT_060D73C0,
    (SaturnSpriteFrameHeader*)&DAT_060D73CC,
    (SaturnSpriteFrameHeader*)&DAT_060D73D8,
    (SaturnSpriteFrameHeader*)&DAT_060D73E4,
    (SaturnSpriteFrameHeader*)&DAT_060D73F0,
    (SaturnSpriteFrameHeader*)&DAT_060D7404,
    (SaturnSpriteFrameHeader*)&DAT_060D7418,
    (SaturnSpriteFrameHeader*)&DAT_060D742C,
    (SaturnSpriteFrameHeader*)&DAT_060D7440,
    (SaturnSpriteFrameHeader*)&DAT_060D744C,
    (SaturnSpriteFrameHeader*)&DAT_060D7460,
    (SaturnSpriteFrameHeader*)&DAT_060D7474,
    (SaturnSpriteFrameHeader*)&DAT_060D7490,
    (SaturnSpriteFrameHeader*)&DAT_060D749C,
    (SaturnSpriteFrameHeader*)&DAT_060D74B0,
    (SaturnSpriteFrameHeader*)&DAT_060D74BC,
    (SaturnSpriteFrameHeader*)&DAT_060D74C8,
    (SaturnSpriteFrameHeader*)&DAT_060D74D4,
    (SaturnSpriteFrameHeader*)&DAT_060D74E0,
    (SaturnSpriteFrameHeader*)&DAT_060D74EC,
    (SaturnSpriteFrameHeader*)&DAT_060D74F8,
    (SaturnSpriteFrameHeader*)&DAT_060D74F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7504,
    (SaturnSpriteFrameHeader*)&DAT_060D7510,
    (SaturnSpriteFrameHeader*)&DAT_060D751C,
    (SaturnSpriteFrameHeader*)&DAT_060D7528,
    (SaturnSpriteFrameHeader*)&DAT_060D7534,
    (SaturnSpriteFrameHeader*)&DAT_060D7540,
    (SaturnSpriteFrameHeader*)&DAT_060D754C,
    (SaturnSpriteFrameHeader*)&DAT_060D7558,
    (SaturnSpriteFrameHeader*)&DAT_060D7564,
    (SaturnSpriteFrameHeader*)&DAT_060D7570,
    (SaturnSpriteFrameHeader*)&DAT_060D757C,
    (SaturnSpriteFrameHeader*)&DAT_060D7588,
};

SaturnSpriteResource DAT_060D763C = {
    DAT_060D71EC, (u16*)&DAT_060D7284, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7648[1] = {&DAT_060D763C};
