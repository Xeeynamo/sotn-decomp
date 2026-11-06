// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6498();
void func_060D6778();
void func_060D68C0();
void func_060D6B48();
void func_060D6D90();
void func_060D6EE0();
void func_060D6EEC();
void func_060D6F04();
void func_060D6F1C();
void func_060D6F34();
void func_060D6F4C();
void func_060D6F64();
void func_060D6F7C();
void func_060D6F94();
void func_060D6FAC();
extern SaturnSpriteResource* DAT_060D7854[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D6778,
        func_060D68C0,
        func_060D6B48,
        func_060D6D90,
        func_060D6EE0,
        func_060D6FAC,
        func_060D6EEC,
        func_060D6F04,
        func_060D6F1C,
        func_060D6F34,
        func_060D6F4C,
        func_060D6F64,
        func_060D6F7C,
        func_060D6F94,
    },
    DAT_060D7854,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D636C, func_060D636C);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6778, func_060D6778);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D68C0, func_060D68C0);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6B48, func_060D6B48);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6D90, func_060D6D90);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6EE0, func_060D6EE0);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6EEC, func_060D6EEC);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6F04, func_060D6F04);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6F1C, func_060D6F1C);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6F34, func_060D6F34);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6F4C, func_060D6F4C);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6F64, func_060D6F64);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6F7C, func_060D6F7C);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6F94, func_060D6F94);
INCLUDE_ASM("asm/saturn/weapon/w_49/f_nonmat", f60D6FAC, func_060D6FAC);

u16 DAT_060D6FC0[14] = {0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607,
                        0x0608, 0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D6FDC[14] = {0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14,
                        0x0E15, 0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6FF8[14] = {0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C,
                        0x141D, 0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D7014[11] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D702A[11] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D7040[12] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF, 0x0000};

s8 DAT_060D7058[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D70BC[7] = {DAT_060D6FC0, DAT_060D6FC0, DAT_060D6FDC, DAT_060D6FF8,
                        DAT_060D7014, DAT_060D702A, DAT_060D7040};

WeaponAnimation DAT_060D70D8[4] = {
    {(u16**)DAT_060D70BC, (s8*)DAT_060D7058, 0x0000, 0x060C, 0x39, 0x04, 0},
    {(u16**)DAT_060D70BC, (s8*)DAT_060D7058, 0x0000, 0x060C, 0x39, 0x02, 0},
    {(u16**)DAT_060D70BC, (s8*)DAT_060D7058, 0x0000, 0x062C, 0x39, 0x04, 0},
    {(u16**)DAT_060D70BC, (s8*)DAT_060D7058, 0x0000, 0x062C, 0x39, 0x04, 0},
};

u32 DAT_060D7118[66] = {
    0x001EFFF2, 0x00500000, 0x001EFFF2, 0x00500000, 0x00190002, 0x00500000,
    0x0017000E, 0x003C0022, 0x001EFFF0, 0x00500000, 0x001EFFF2, 0x00500000,
    0x001E0004, 0x003C0022, 0x00010001, 0x00010002, 0x00010003, 0x00010004,
    0x00010005, 0x00010006, 0x00010007, 0x00010008, 0x00000000, 0x00010001,
    0x00010002, 0x00010003, 0x00010004, 0x00010005, 0x00010004, 0x00010003,
    0x00010004, 0x00010003, 0x00010004, 0x00010005, 0x00010006, 0x00010007,
    0x00010008, 0xFFFF0000, 0x00030001, 0x00030002, 0x00030003, 0x00030004,
    0x00030005, 0x00030006, 0x00030007, 0x00030008, 0x00030009, 0x0003000A,
    0x0003000B, 0x0003000C, 0x0003000D, 0xFFFF0000, 0x00020001, 0x00020002,
    0x00020003, 0x00020004, 0x00020005, 0x00020006, 0x00020007, 0x00020008,
    0x00020009, 0x0002000A, 0x0002000B, 0x0002000C, 0x0002000D, 0xFFFF0000,
};

SaturnSpriteImage DAT_060D7220[7] = {
    {12, 5, 0x0000},  {48, 10, 0x0010}, {24, 4, 0x0088}, {8, 1, 0x00A0},
    {36, 21, 0x00A4}, {24, 12, 0x0164}, {0, 0, 0x01AC},
};

SaturnSpriteFrameHeader DAT_060D723C = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7240 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D724C = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7258 = {
    {0x0100, 0x0000},
    {
        {0x0100, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7264 = {
    {0x0100, 0x0000},
    {
        {0x0200, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7270 = {
    {0x0100, 0x0000},
    {
        {0x0300, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D727C = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7288 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7294 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D72A0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D72AC = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72C4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72D0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72DC = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72E8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D72F4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7300 = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D730C = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7318 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7324 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7330 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D733C = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7348 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7354 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7360 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D736C = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7378 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7384 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7390 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D739C = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D73A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73CC = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D73F0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D73FC = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7408 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7414 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7420 = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D742C = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7438 = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7444 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7450 = {
    {0x0100, 0x0000},
    {
        {0x0400, -5, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D745C = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7468 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7474 = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7480 = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D748C = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7498 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74A4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74B0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74BC = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D74C8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D74D4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D74E0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D74EC = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D74F8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7504 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7510 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D751C = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7528 = {
    {0x0100, 0x0000},
    {
        {0x0500, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7534 = {
    {0x0100, 0x0000},
    {
        {0x0600, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7540 = {
    {0x0100, 0x0000},
    {
        {0x0700, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D754C = {
    {0x0100, 0x0000},
    {
        {0x0500, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7558 = {
    {0x0100, 0x0000},
    {
        {0x0600, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7564 = {
    {0x0100, 0x0000},
    {
        {0x0700, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7570 = {
    {0x0100, 0x0000},
    {
        {0x0500, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D757C = {
    {0x0100, 0x0000},
    {
        {0x0600, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7588 = {
    {0x0100, 0x0000},
    {
        {0x0700, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7594 = {
    {0x0100, 0x0000},
    {
        {0x0500, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75A0 = {
    {0x0100, 0x0000},
    {
        {0x0600, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75AC = {
    {0x0100, 0x0000},
    {
        {0x0700, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75B8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75C4 = {
    {0x0100, 0x0000},
    {
        {0x0600, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75D0 = {
    {0x0100, 0x0000},
    {
        {0x0700, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75DC = {
    {0x0100, 0x0000},
    {
        {0x0500, 29, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D75E8 = {
    {0x0100, 0x0000},
    {
        {0x0600, 29, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D75F4 = {
    {0x0100, 0x0000},
    {
        {0x0700, 29, 1, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D7600[81] = {
    (SaturnSpriteFrameHeader*)&DAT_060D723C,
    (SaturnSpriteFrameHeader*)&DAT_060D7240,
    (SaturnSpriteFrameHeader*)&DAT_060D724C,
    (SaturnSpriteFrameHeader*)&DAT_060D7258,
    (SaturnSpriteFrameHeader*)&DAT_060D7264,
    (SaturnSpriteFrameHeader*)&DAT_060D7270,
    (SaturnSpriteFrameHeader*)&DAT_060D727C,
    (SaturnSpriteFrameHeader*)&DAT_060D7288,
    (SaturnSpriteFrameHeader*)&DAT_060D7294,
    (SaturnSpriteFrameHeader*)&DAT_060D72A0,
    (SaturnSpriteFrameHeader*)&DAT_060D72AC,
    (SaturnSpriteFrameHeader*)&DAT_060D72B8,
    (SaturnSpriteFrameHeader*)&DAT_060D72C4,
    (SaturnSpriteFrameHeader*)&DAT_060D72D0,
    (SaturnSpriteFrameHeader*)&DAT_060D72DC,
    (SaturnSpriteFrameHeader*)&DAT_060D72E8,
    (SaturnSpriteFrameHeader*)&DAT_060D72F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7300,
    (SaturnSpriteFrameHeader*)&DAT_060D730C,
    (SaturnSpriteFrameHeader*)&DAT_060D7318,
    (SaturnSpriteFrameHeader*)&DAT_060D7324,
    (SaturnSpriteFrameHeader*)&DAT_060D7330,
    (SaturnSpriteFrameHeader*)&DAT_060D733C,
    (SaturnSpriteFrameHeader*)&DAT_060D7348,
    (SaturnSpriteFrameHeader*)&DAT_060D7354,
    (SaturnSpriteFrameHeader*)&DAT_060D7360,
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
    (SaturnSpriteFrameHeader*)&DAT_060D73FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7408,
    (SaturnSpriteFrameHeader*)&DAT_060D7414,
    (SaturnSpriteFrameHeader*)&DAT_060D7420,
    (SaturnSpriteFrameHeader*)&DAT_060D742C,
    (SaturnSpriteFrameHeader*)&DAT_060D7438,
    (SaturnSpriteFrameHeader*)&DAT_060D7444,
    (SaturnSpriteFrameHeader*)&DAT_060D7450,
    (SaturnSpriteFrameHeader*)&DAT_060D745C,
    (SaturnSpriteFrameHeader*)&DAT_060D7468,
    (SaturnSpriteFrameHeader*)&DAT_060D7474,
    (SaturnSpriteFrameHeader*)&DAT_060D7480,
    (SaturnSpriteFrameHeader*)&DAT_060D748C,
    (SaturnSpriteFrameHeader*)&DAT_060D7498,
    (SaturnSpriteFrameHeader*)&DAT_060D74A4,
    (SaturnSpriteFrameHeader*)&DAT_060D74B0,
    (SaturnSpriteFrameHeader*)&DAT_060D74BC,
    (SaturnSpriteFrameHeader*)&DAT_060D74C8,
    (SaturnSpriteFrameHeader*)&DAT_060D74D4,
    (SaturnSpriteFrameHeader*)&DAT_060D74E0,
    (SaturnSpriteFrameHeader*)&DAT_060D74EC,
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
    (SaturnSpriteFrameHeader*)&DAT_060D7594,
    (SaturnSpriteFrameHeader*)&DAT_060D75A0,
    (SaturnSpriteFrameHeader*)&DAT_060D75AC,
    (SaturnSpriteFrameHeader*)&DAT_060D75B8,
    (SaturnSpriteFrameHeader*)&DAT_060D75C4,
    (SaturnSpriteFrameHeader*)&DAT_060D75D0,
    (SaturnSpriteFrameHeader*)&DAT_060D75DC,
    (SaturnSpriteFrameHeader*)&DAT_060D75E8,
    (SaturnSpriteFrameHeader*)&DAT_060D75F4,
};

struct {
    u16 countAndFlags;
    u16 colors[8][16];
    u16 padding[1];
} DAT_060D7744 = {
    0x0008,
    {
        {0x98C6, 0x8000, 0x823E, 0x83DD, 0x823E, 0x823E, 0x823E, 0x823E, 0x843F,
         0x82FF, 0x82BF, 0x815D, 0x815D, 0x80FD, 0xD294, 0xF2F3},
        {0x98C6, 0x8000, 0x80FD, 0x8000, 0x817D, 0x833F, 0x833F, 0x833F, 0x843F,
         0x821D, 0x821D, 0x833F, 0x833F, 0x833F, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x8093, 0x835D, 0x80DD, 0x809D, 0x825E, 0x825E, 0x801F,
         0x821D, 0x821D, 0x82DE, 0x80BD, 0x80BD, 0xD294, 0xEAD3},
        {0x98C6, 0x8000, 0x8072, 0x837D, 0x807D, 0x80FD, 0x82DD, 0x80BD, 0x843F,
         0x81BD, 0x821D, 0x809D, 0x819C, 0x805D, 0xD294, 0x83DF},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x80DD, 0x829D, 0x80DD, 0x80DD, 0x80DD, 0x80DD, 0x843F,
         0x829D, 0x801F, 0x803D, 0x801D, 0x803D, 0xD294, 0xF2D1},
        {0x98C6, 0x8000, 0x8055, 0x829D, 0x80DD, 0x80DD, 0x80DD, 0x80DD, 0x843F,
         0x829D, 0x801F, 0x803D, 0x803D, 0x803D, 0xD294, 0xF39C},
        {0x98C6, 0x8000, 0x803D, 0x829D, 0x80DD, 0x803D, 0x817D, 0x803D, 0x843F,
         0x829D, 0x801F, 0x803D, 0x803D, 0x803D, 0xD294, 0xEA90},
    },
    {0x0000},
};

SaturnSpriteResource DAT_060D7848 = {
    DAT_060D7220, (u16*)&DAT_060D7744, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7854[1] = {&DAT_060D7848};
