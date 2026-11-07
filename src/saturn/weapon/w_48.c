// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D648C();
void func_060D693C();
void func_060D6B98();
void func_060D6BB0();
void func_060D6BC8();
void func_060D6BE0();
void func_060D6BEC();
void func_060D6C04();
void func_060D6C1C();
void func_060D6C34();
void func_060D6C4C();
void func_060D6C64();
void func_060D6C7C();
void func_060D6C94();
void func_060D6CAC();
extern SaturnSpriteResource* DAT_060D7484[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D648C,
        func_060D693C,
        func_060D6B98,
        func_060D6BB0,
        func_060D6BC8,
        func_060D6BE0,
        func_060D6CAC,
        func_060D6BEC,
        func_060D6C04,
        func_060D6C1C,
        func_060D6C34,
        func_060D6C4C,
        func_060D6C64,
        func_060D6C7C,
        func_060D6C94,
    },
    DAT_060D7484,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D639C, func_060D639C);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D648C, func_060D648C);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D693C, func_060D693C);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6B98, func_060D6B98);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6BB0, func_060D6BB0);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6BC8, func_060D6BC8);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6BE0, func_060D6BE0);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6BEC, func_060D6BEC);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6C04, func_060D6C04);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6C1C, func_060D6C1C);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6C34, func_060D6C34);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6C4C, func_060D6C4C);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6C64, func_060D6C64);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6C7C, func_060D6C7C);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6C94, func_060D6C94);
INCLUDE_ASM("asm/saturn/weapon/w_48/f_nonmat", f60D6CAC, func_060D6CAC);

u16 DAT_060D6CC0[14] = {0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607,
                        0x0608, 0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D6CDC[14] = {0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14,
                        0x0E15, 0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6CF8[14] = {0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C,
                        0x141D, 0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6D14[11] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D6D2A[11] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D6D40[12] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF, 0x0000};

s8 DAT_060D6D58[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D6DBC[7] = {DAT_060D6CC0, DAT_060D6CC0, DAT_060D6CDC, DAT_060D6CF8,
                        DAT_060D6D14, DAT_060D6D2A, DAT_060D6D40};

WeaponAnimation DAT_060D6DD8[2] = {
    {(u16**)DAT_060D6DBC, (s8*)DAT_060D6D58, 0x0000, 0x060C, 0x39, 0x04, 0},
    {(u16**)DAT_060D6DBC, (s8*)DAT_060D6D58, 0x0000, 0x060C, 0x39, 0x02, 0},
};

u32 DAT_060D6DF8[22] = {
    0x001A001A, 0x001A0000, 0x0008001A, 0x00100000, 0x0004001F, 0x00100000,
    0x001F001F, 0x001F0000, 0x001EFFF2, 0x00500000, 0x001EFFF2, 0x00500000,
    0x00190002, 0x00500000, 0x0017000E, 0x003C0022, 0x001EFFF0, 0x00500000,
    0x001EFFF2, 0x00500000, 0x001E0004, 0x003C0022,
};

SaturnSpriteImage DAT_060D6E50[7] = {
    {12, 5, 0x0000},  {48, 10, 0x0010}, {24, 4, 0x0088}, {8, 1, 0x00A0},
    {36, 21, 0x00A4}, {24, 12, 0x0164}, {0, 0, 0x01AC},
};

SaturnSpriteFrameHeader DAT_060D6E6C = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6E70 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E7C = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E88 = {
    {0x0100, 0x0000},
    {
        {0x0100, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E94 = {
    {0x0100, 0x0000},
    {
        {0x0200, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EA0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EAC = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EB8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EC4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6ED0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EDC = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6EE8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6EF4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F00 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F24 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F30 = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F3C = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F48 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6F54 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6F60 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6F6C = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6F78 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F84 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F90 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F9C = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FA8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6FB4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6FC0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6FCC = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6FD8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6FE4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6FF0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6FFC = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7008 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7014 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7020 = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D702C = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7038 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7044 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7050 = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D705C = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7068 = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7074 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7080 = {
    {0x0100, 0x0000},
    {
        {0x0400, -5, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D708C = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7098 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D70A4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D70B0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D70BC = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D70C8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D70D4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D70E0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D70EC = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D70F8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7104 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7110 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D711C = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7128 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7134 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7140 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D714C = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7158 = {
    {0x0100, 0x0000},
    {
        {0x0500, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7164 = {
    {0x0100, 0x0000},
    {
        {0x0600, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7170 = {
    {0x0100, 0x0000},
    {
        {0x0700, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D717C = {
    {0x0100, 0x0000},
    {
        {0x0500, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7188 = {
    {0x0100, 0x0000},
    {
        {0x0600, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7194 = {
    {0x0100, 0x0000},
    {
        {0x0700, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D71A0 = {
    {0x0100, 0x0000},
    {
        {0x0500, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D71AC = {
    {0x0100, 0x0000},
    {
        {0x0600, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D71B8 = {
    {0x0100, 0x0000},
    {
        {0x0700, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D71C4 = {
    {0x0100, 0x0000},
    {
        {0x0500, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D71D0 = {
    {0x0100, 0x0000},
    {
        {0x0600, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D71DC = {
    {0x0100, 0x0000},
    {
        {0x0700, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D71E8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D71F4 = {
    {0x0100, 0x0000},
    {
        {0x0600, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7200 = {
    {0x0100, 0x0000},
    {
        {0x0700, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D720C = {
    {0x0100, 0x0000},
    {
        {0x0500, 29, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7218 = {
    {0x0100, 0x0000},
    {
        {0x0600, 29, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7224 = {
    {0x0100, 0x0000},
    {
        {0x0700, 29, 1, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D7230[81] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6E6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E70,
    (SaturnSpriteFrameHeader*)&DAT_060D6E7C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E88,
    (SaturnSpriteFrameHeader*)&DAT_060D6E94,
    (SaturnSpriteFrameHeader*)&DAT_060D6EA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6EB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6EC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6ED0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6EE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6EF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6F00,
    (SaturnSpriteFrameHeader*)&DAT_060D6F0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F18,
    (SaturnSpriteFrameHeader*)&DAT_060D6F24,
    (SaturnSpriteFrameHeader*)&DAT_060D6F30,
    (SaturnSpriteFrameHeader*)&DAT_060D6F3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F48,
    (SaturnSpriteFrameHeader*)&DAT_060D6F54,
    (SaturnSpriteFrameHeader*)&DAT_060D6F60,
    (SaturnSpriteFrameHeader*)&DAT_060D6F6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F78,
    (SaturnSpriteFrameHeader*)&DAT_060D6F84,
    (SaturnSpriteFrameHeader*)&DAT_060D6F90,
    (SaturnSpriteFrameHeader*)&DAT_060D6F9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6FA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6FB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6FC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FCC,
    (SaturnSpriteFrameHeader*)&DAT_060D6FD8,
    (SaturnSpriteFrameHeader*)&DAT_060D6FE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6FF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FFC,
    (SaturnSpriteFrameHeader*)&DAT_060D7008,
    (SaturnSpriteFrameHeader*)&DAT_060D7014,
    (SaturnSpriteFrameHeader*)&DAT_060D7020,
    (SaturnSpriteFrameHeader*)&DAT_060D702C,
    (SaturnSpriteFrameHeader*)&DAT_060D7038,
    (SaturnSpriteFrameHeader*)&DAT_060D7044,
    (SaturnSpriteFrameHeader*)&DAT_060D7050,
    (SaturnSpriteFrameHeader*)&DAT_060D705C,
    (SaturnSpriteFrameHeader*)&DAT_060D7068,
    (SaturnSpriteFrameHeader*)&DAT_060D7074,
    (SaturnSpriteFrameHeader*)&DAT_060D7080,
    (SaturnSpriteFrameHeader*)&DAT_060D708C,
    (SaturnSpriteFrameHeader*)&DAT_060D7098,
    (SaturnSpriteFrameHeader*)&DAT_060D70A4,
    (SaturnSpriteFrameHeader*)&DAT_060D70B0,
    (SaturnSpriteFrameHeader*)&DAT_060D70BC,
    (SaturnSpriteFrameHeader*)&DAT_060D70C8,
    (SaturnSpriteFrameHeader*)&DAT_060D70D4,
    (SaturnSpriteFrameHeader*)&DAT_060D70E0,
    (SaturnSpriteFrameHeader*)&DAT_060D70EC,
    (SaturnSpriteFrameHeader*)&DAT_060D70F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7104,
    (SaturnSpriteFrameHeader*)&DAT_060D7110,
    (SaturnSpriteFrameHeader*)&DAT_060D711C,
    (SaturnSpriteFrameHeader*)&DAT_060D7128,
    (SaturnSpriteFrameHeader*)&DAT_060D7134,
    (SaturnSpriteFrameHeader*)&DAT_060D7140,
    (SaturnSpriteFrameHeader*)&DAT_060D714C,
    (SaturnSpriteFrameHeader*)&DAT_060D7158,
    (SaturnSpriteFrameHeader*)&DAT_060D7164,
    (SaturnSpriteFrameHeader*)&DAT_060D7170,
    (SaturnSpriteFrameHeader*)&DAT_060D717C,
    (SaturnSpriteFrameHeader*)&DAT_060D7188,
    (SaturnSpriteFrameHeader*)&DAT_060D7194,
    (SaturnSpriteFrameHeader*)&DAT_060D71A0,
    (SaturnSpriteFrameHeader*)&DAT_060D71AC,
    (SaturnSpriteFrameHeader*)&DAT_060D71B8,
    (SaturnSpriteFrameHeader*)&DAT_060D71C4,
    (SaturnSpriteFrameHeader*)&DAT_060D71D0,
    (SaturnSpriteFrameHeader*)&DAT_060D71DC,
    (SaturnSpriteFrameHeader*)&DAT_060D71E8,
    (SaturnSpriteFrameHeader*)&DAT_060D71F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7200,
    (SaturnSpriteFrameHeader*)&DAT_060D720C,
    (SaturnSpriteFrameHeader*)&DAT_060D7218,
    (SaturnSpriteFrameHeader*)&DAT_060D7224,
};

struct {
    u16 countAndFlags;
    u16 colors[8][16];
    u16 padding[1];
} DAT_060D7374 = {
    0x0008,
    {
        {0x98C6, 0x8000, 0xFD61, 0xA5C0, 0xFD61, 0xFD61, 0xFD61, 0xFD61, 0x843F,
         0xE9A4, 0xC481, 0xD0A0, 0xD0E0, 0xD000, 0xD294, 0xF2F3},
        {0x98C6, 0x8000, 0xC0E0, 0x8000, 0xDD65, 0xFE0C, 0xFE0C, 0xFE0C, 0x843F,
         0xFD20, 0xFD20, 0xFE0C, 0xFE0C, 0xFE0C, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x9C00, 0xA5C0, 0xC860, 0xA800, 0xFD00, 0xFD00, 0x801F,
         0xFD40, 0xFD20, 0xFD00, 0xDDC0, 0xBC00, 0xD294, 0xEAD3},
        {0x98C6, 0x8000, 0x9800, 0xA5C0, 0xA880, 0xAC00, 0xBD40, 0xBC80, 0x843F,
         0xD4C0, 0xFD20, 0xB4E0, 0xFE88, 0xA060, 0xD294, 0xFECC},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0xFD40, 0xA5C0, 0xFD40, 0xFD40, 0xFD40, 0xFD40, 0x843F,
         0xC1C0, 0x801F, 0xBC00, 0xBC00, 0xBC00, 0xD294, 0xFF51},
        {0x98C6, 0x8000, 0xA000, 0xA5C0, 0xFD00, 0xFD00, 0xFD00, 0xFD00, 0x843F,
         0xC1C0, 0x801F, 0xB400, 0xB400, 0xB400, 0xD294, 0xF39C},
        {0x98C6, 0x8000, 0x9C00, 0xA5C0, 0xD400, 0x9C20, 0xFDC0, 0xA840, 0x843F,
         0xC1C0, 0x801F, 0xB800, 0xB800, 0xB800, 0xD294, 0xEA90},
    },
    {0x0000},
};

SaturnSpriteResource DAT_060D7478 = {
    DAT_060D6E50, (u16*)&DAT_060D7374, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7484[1] = {&DAT_060D7478};
