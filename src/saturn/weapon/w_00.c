// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62F0();
void func_060D6308();
void func_060D6320();
void func_060D6338();
void func_060D6350();
void func_060D6368();
void func_060D6374();
void func_060D638C();
void func_060D63A4();
void func_060D63BC();
void func_060D63D4();
void func_060D63EC();
void func_060D6404();
void func_060D641C();
void func_060D6434();
extern SaturnSpriteResource* DAT_060D73C0[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62F0,
        func_060D6308,
        func_060D6320,
        func_060D6338,
        func_060D6350,
        func_060D6368,
        func_060D6434,
        func_060D6374,
        func_060D638C,
        func_060D63A4,
        func_060D63BC,
        func_060D63D4,
        func_060D63EC,
        func_060D6404,
        func_060D641C,
    },
    DAT_060D73C0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D62F0, func_060D62F0);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6308, func_060D6308);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6320, func_060D6320);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6338, func_060D6338);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6350, func_060D6350);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6368, func_060D6368);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6374, func_060D6374);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D638C, func_060D638C);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D63A4, func_060D63A4);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D63BC, func_060D63BC);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D63D4, func_060D63D4);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D63EC, func_060D63EC);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6404, func_060D6404);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D641C, func_060D641C);
INCLUDE_ASM("asm/saturn/weapon/w_00/f_nonmat", f60D6434, func_060D6434);

u16 DAT_060D6440[14] = {0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607,
                        0x0608, 0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D645C[14] = {0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14,
                        0x0E15, 0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6478[14] = {0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C,
                        0x141D, 0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6494[11] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D64AA[11] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D64C0[11] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF};

u16 DAT_060D64D6[13] = {0x0201, 0x263F, 0x2640, 0x2641, 0x0606, 0x0607, 0x0608,
                        0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D64F0[13] = {0x0A0E, 0x2842, 0x2843, 0x2844, 0x0E13, 0x0E14, 0x0E15,
                        0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D650A[13] = {0x0A0E, 0x2A45, 0x2A46, 0x2A47, 0x141B, 0x141C, 0x141D,
                        0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6524[10] = {0x1623, 0x2C48, 0x2C49, 0x2C4A, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D6538[10] = {0x1C2D, 0x2E4B, 0x2E4C, 0x2E4D, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D654C[10] = {0x1C2D, 0x304E, 0x304F, 0x3050, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF};

s8 DAT_060D6560[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D65C4[7] = {DAT_060D6440, DAT_060D6440, DAT_060D645C, DAT_060D6478,
                        DAT_060D6494, DAT_060D64AA, DAT_060D64C0};

u16* DAT_060D65E0[7] = {DAT_060D64D6, DAT_060D64D6, DAT_060D64F0, DAT_060D650A,
                        DAT_060D6524, DAT_060D6538, DAT_060D654C};

WeaponAnimation DAT_060D65FC[7] = {
    {(u16**)DAT_060D65E0, (s8*)DAT_060D6560, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D65C4, (s8*)DAT_060D6560, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D65C4, (s8*)DAT_060D6560, 0x0000, 0x060C, 0x39, 0x04, 0},
    {(u16**)DAT_060D65C4, (s8*)DAT_060D6560, 0x0000, 0x06A8, 0x39, 0x04, 0},
    {(u16**)DAT_060D65C4, (s8*)DAT_060D6560, 0x0000, 0x060C, 0x39, 0x04, 0},
    {(u16**)DAT_060D65C4, (s8*)DAT_060D6560, 0x0002, 0x060C, 0x39, 0x04, 0},
    {(u16**)DAT_060D65C4, (s8*)DAT_060D6560, 0x0001, 0x060B, 0x39, 0x04, 0},
};

SaturnSpriteImage DAT_060D666C[13] = {
    {12, 5, 0x0000},  {36, 4, 0x0010},  {24, 4, 0x0034},  {8, 1, 0x004C},
    {24, 18, 0x0050}, {24, 12, 0x00BC}, {12, 5, 0x0104},  {48, 10, 0x0114},
    {24, 4, 0x018C},  {8, 1, 0x01A4},   {36, 21, 0x01A8}, {24, 12, 0x0268},
    {0, 0, 0x02B0},
};

SaturnSpriteFrameHeader DAT_060D66A0 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D66A4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66B0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 51, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D66BC = {
    {0x0100, 0x0000},
    {
        {0x0100, 51, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D66C8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 51, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D66D4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 51, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D66E0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66EC = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66F8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6704 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6710 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D671C = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6728 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6734 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6740 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D674C = {
    {0x0100, 0x0000},
    {
        {0x0000, 43, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6758 = {
    {0x0100, 0x0000},
    {
        {0x0100, 43, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6764 = {
    {0x0100, 0x0000},
    {
        {0x0200, 43, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6770 = {
    {0x0100, 0x0000},
    {
        {0x0300, 43, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D677C = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6788 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6794 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D67A0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D67AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D67B8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 29, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D67C4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 29, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D67D0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 29, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D67DC = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D67E8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D67F4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6800 = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D680C = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6818 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6824 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6830 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D683C = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6848 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6854 = {
    {0x0100, 0x0000},
    {
        {0x0100, 45, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6860 = {
    {0x0100, 0x0000},
    {
        {0x0200, 45, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D686C = {
    {0x0100, 0x0000},
    {
        {0x0300, 45, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6878 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6884 = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6890 = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D689C = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D68A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D68B4 = {
    {0x0100, 0x0000},
    {
        {0x0400, -5, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D68C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 43, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D68CC = {
    {0x0100, 0x0000},
    {
        {0x0100, 43, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D68D8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 43, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D68E4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 43, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D68F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D68FC = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6908 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6914 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6920 = {
    {0x0100, 0x0000},
    {
        {0x0100, 37, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D692C = {
    {0x0100, 0x0000},
    {
        {0x0100, 37, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6938 = {
    {0x0100, 0x0000},
    {
        {0x0200, 37, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6944 = {
    {0x0100, 0x0000},
    {
        {0x0300, 37, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6950 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D695C = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6968 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6974 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6980 = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D698C = {
    {0x0100, 0x0000},
    {
        {0x0500, 51, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6998 = {
    {0x0100, 0x0000},
    {
        {0x0600, 51, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69A4 = {
    {0x0100, 0x0000},
    {
        {0x0700, 51, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69B0 = {
    {0x0100, 0x0000},
    {
        {0x0500, 41, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69BC = {
    {0x0100, 0x0000},
    {
        {0x0600, 41, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69C8 = {
    {0x0100, 0x0000},
    {
        {0x0700, 41, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69D4 = {
    {0x0100, 0x0000},
    {
        {0x0500, 31, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D69E0 = {
    {0x0100, 0x0000},
    {
        {0x0600, 31, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D69EC = {
    {0x0100, 0x0000},
    {
        {0x0700, 31, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D69F8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 47, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A04 = {
    {0x0100, 0x0000},
    {
        {0x0600, 47, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A10 = {
    {0x0100, 0x0000},
    {
        {0x0700, 47, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A1C = {
    {0x0100, 0x0000},
    {
        {0x0500, 45, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A28 = {
    {0x0100, 0x0000},
    {
        {0x0600, 45, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A34 = {
    {0x0100, 0x0000},
    {
        {0x0700, 45, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A40 = {
    {0x0100, 0x0000},
    {
        {0x0500, 41, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A4C = {
    {0x0100, 0x0000},
    {
        {0x0600, 41, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A58 = {
    {0x0100, 0x0000},
    {
        {0x0700, 41, 3, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D6A64[81] = {
    (SaturnSpriteFrameHeader*)&DAT_060D66A0,
    (SaturnSpriteFrameHeader*)&DAT_060D66A4,
    (SaturnSpriteFrameHeader*)&DAT_060D66B0,
    (SaturnSpriteFrameHeader*)&DAT_060D66BC,
    (SaturnSpriteFrameHeader*)&DAT_060D66C8,
    (SaturnSpriteFrameHeader*)&DAT_060D66D4,
    (SaturnSpriteFrameHeader*)&DAT_060D66E0,
    (SaturnSpriteFrameHeader*)&DAT_060D66EC,
    (SaturnSpriteFrameHeader*)&DAT_060D66F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6704,
    (SaturnSpriteFrameHeader*)&DAT_060D6710,
    (SaturnSpriteFrameHeader*)&DAT_060D671C,
    (SaturnSpriteFrameHeader*)&DAT_060D6728,
    (SaturnSpriteFrameHeader*)&DAT_060D6734,
    (SaturnSpriteFrameHeader*)&DAT_060D6740,
    (SaturnSpriteFrameHeader*)&DAT_060D674C,
    (SaturnSpriteFrameHeader*)&DAT_060D6758,
    (SaturnSpriteFrameHeader*)&DAT_060D6764,
    (SaturnSpriteFrameHeader*)&DAT_060D6770,
    (SaturnSpriteFrameHeader*)&DAT_060D677C,
    (SaturnSpriteFrameHeader*)&DAT_060D6788,
    (SaturnSpriteFrameHeader*)&DAT_060D6794,
    (SaturnSpriteFrameHeader*)&DAT_060D67A0,
    (SaturnSpriteFrameHeader*)&DAT_060D67AC,
    (SaturnSpriteFrameHeader*)&DAT_060D67B8,
    (SaturnSpriteFrameHeader*)&DAT_060D67C4,
    (SaturnSpriteFrameHeader*)&DAT_060D67D0,
    (SaturnSpriteFrameHeader*)&DAT_060D67DC,
    (SaturnSpriteFrameHeader*)&DAT_060D67E8,
    (SaturnSpriteFrameHeader*)&DAT_060D67F4,
    (SaturnSpriteFrameHeader*)&DAT_060D6800,
    (SaturnSpriteFrameHeader*)&DAT_060D680C,
    (SaturnSpriteFrameHeader*)&DAT_060D6818,
    (SaturnSpriteFrameHeader*)&DAT_060D6824,
    (SaturnSpriteFrameHeader*)&DAT_060D6830,
    (SaturnSpriteFrameHeader*)&DAT_060D683C,
    (SaturnSpriteFrameHeader*)&DAT_060D6848,
    (SaturnSpriteFrameHeader*)&DAT_060D6854,
    (SaturnSpriteFrameHeader*)&DAT_060D6860,
    (SaturnSpriteFrameHeader*)&DAT_060D686C,
    (SaturnSpriteFrameHeader*)&DAT_060D6878,
    (SaturnSpriteFrameHeader*)&DAT_060D6884,
    (SaturnSpriteFrameHeader*)&DAT_060D6890,
    (SaturnSpriteFrameHeader*)&DAT_060D689C,
    (SaturnSpriteFrameHeader*)&DAT_060D68A8,
    (SaturnSpriteFrameHeader*)&DAT_060D68B4,
    (SaturnSpriteFrameHeader*)&DAT_060D68C0,
    (SaturnSpriteFrameHeader*)&DAT_060D68CC,
    (SaturnSpriteFrameHeader*)&DAT_060D68D8,
    (SaturnSpriteFrameHeader*)&DAT_060D68E4,
    (SaturnSpriteFrameHeader*)&DAT_060D68F0,
    (SaturnSpriteFrameHeader*)&DAT_060D68FC,
    (SaturnSpriteFrameHeader*)&DAT_060D6908,
    (SaturnSpriteFrameHeader*)&DAT_060D6914,
    (SaturnSpriteFrameHeader*)&DAT_060D6920,
    (SaturnSpriteFrameHeader*)&DAT_060D692C,
    (SaturnSpriteFrameHeader*)&DAT_060D6938,
    (SaturnSpriteFrameHeader*)&DAT_060D6944,
    (SaturnSpriteFrameHeader*)&DAT_060D6950,
    (SaturnSpriteFrameHeader*)&DAT_060D695C,
    (SaturnSpriteFrameHeader*)&DAT_060D6968,
    (SaturnSpriteFrameHeader*)&DAT_060D6974,
    (SaturnSpriteFrameHeader*)&DAT_060D6980,
    (SaturnSpriteFrameHeader*)&DAT_060D698C,
    (SaturnSpriteFrameHeader*)&DAT_060D6998,
    (SaturnSpriteFrameHeader*)&DAT_060D69A4,
    (SaturnSpriteFrameHeader*)&DAT_060D69B0,
    (SaturnSpriteFrameHeader*)&DAT_060D69BC,
    (SaturnSpriteFrameHeader*)&DAT_060D69C8,
    (SaturnSpriteFrameHeader*)&DAT_060D69D4,
    (SaturnSpriteFrameHeader*)&DAT_060D69E0,
    (SaturnSpriteFrameHeader*)&DAT_060D69EC,
    (SaturnSpriteFrameHeader*)&DAT_060D69F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6A04,
    (SaturnSpriteFrameHeader*)&DAT_060D6A10,
    (SaturnSpriteFrameHeader*)&DAT_060D6A1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A28,
    (SaturnSpriteFrameHeader*)&DAT_060D6A34,
    (SaturnSpriteFrameHeader*)&DAT_060D6A40,
    (SaturnSpriteFrameHeader*)&DAT_060D6A4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A58,
};

SaturnSpriteFrameHeader DAT_060D6BA8 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6BAC = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BB8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6BC4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6BD0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6BDC = {
    {0x0100, 0x0000},
    {
        {0x0300, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6BE8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6BF4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C00 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C0C = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C18 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C24 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C30 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C3C = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C48 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C60 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C6C = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C78 = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C84 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C90 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C9C = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CA8 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CB4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6CC0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6CCC = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6CD8 = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6CE4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6CF0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6CFC = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D08 = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D14 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D20 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D2C = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D38 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D44 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D50 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D5C = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D68 = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D74 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D8C = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D98 = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DA4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DBC = {
    {0x0100, 0x0000},
    {
        {0x0400, -5, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DD4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DE0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DEC = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DF8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E04 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E10 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E1C = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E28 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6E34 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6E40 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6E4C = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6E58 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E64 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E70 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E7C = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E88 = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E94 = {
    {0x0100, 0x0000},
    {
        {0x0500, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EA0 = {
    {0x0100, 0x0000},
    {
        {0x0600, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EAC = {
    {0x0100, 0x0000},
    {
        {0x0700, 38, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EB8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EC4 = {
    {0x0100, 0x0000},
    {
        {0x0600, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6ED0 = {
    {0x0100, 0x0000},
    {
        {0x0700, 28, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EDC = {
    {0x0100, 0x0000},
    {
        {0x0500, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6EE8 = {
    {0x0100, 0x0000},
    {
        {0x0600, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6EF4 = {
    {0x0100, 0x0000},
    {
        {0x0700, 19, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F00 = {
    {0x0100, 0x0000},
    {
        {0x0500, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F0C = {
    {0x0100, 0x0000},
    {
        {0x0600, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F18 = {
    {0x0100, 0x0000},
    {
        {0x0700, 34, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F24 = {
    {0x0100, 0x0000},
    {
        {0x0500, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F30 = {
    {0x0100, 0x0000},
    {
        {0x0600, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F3C = {
    {0x0100, 0x0000},
    {
        {0x0700, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F48 = {
    {0x0100, 0x0000},
    {
        {0x0500, 29, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F54 = {
    {0x0100, 0x0000},
    {
        {0x0600, 29, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F60 = {
    {0x0100, 0x0000},
    {
        {0x0700, 29, 1, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D6F6C[81] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6BA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6C00,
    (SaturnSpriteFrameHeader*)&DAT_060D6C0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C18,
    (SaturnSpriteFrameHeader*)&DAT_060D6C24,
    (SaturnSpriteFrameHeader*)&DAT_060D6C30,
    (SaturnSpriteFrameHeader*)&DAT_060D6C3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C48,
    (SaturnSpriteFrameHeader*)&DAT_060D6C54,
    (SaturnSpriteFrameHeader*)&DAT_060D6C60,
    (SaturnSpriteFrameHeader*)&DAT_060D6C6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C78,
    (SaturnSpriteFrameHeader*)&DAT_060D6C84,
    (SaturnSpriteFrameHeader*)&DAT_060D6C90,
    (SaturnSpriteFrameHeader*)&DAT_060D6C9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6CA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6CB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CCC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CD8,
    (SaturnSpriteFrameHeader*)&DAT_060D6CE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6D08,
    (SaturnSpriteFrameHeader*)&DAT_060D6D14,
    (SaturnSpriteFrameHeader*)&DAT_060D6D20,
    (SaturnSpriteFrameHeader*)&DAT_060D6D2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D38,
    (SaturnSpriteFrameHeader*)&DAT_060D6D44,
    (SaturnSpriteFrameHeader*)&DAT_060D6D50,
    (SaturnSpriteFrameHeader*)&DAT_060D6D5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D68,
    (SaturnSpriteFrameHeader*)&DAT_060D6D74,
    (SaturnSpriteFrameHeader*)&DAT_060D6D80,
    (SaturnSpriteFrameHeader*)&DAT_060D6D8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D98,
    (SaturnSpriteFrameHeader*)&DAT_060D6DA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6E04,
    (SaturnSpriteFrameHeader*)&DAT_060D6E10,
    (SaturnSpriteFrameHeader*)&DAT_060D6E1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E28,
    (SaturnSpriteFrameHeader*)&DAT_060D6E34,
    (SaturnSpriteFrameHeader*)&DAT_060D6E40,
    (SaturnSpriteFrameHeader*)&DAT_060D6E4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E58,
    (SaturnSpriteFrameHeader*)&DAT_060D6E64,
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
};

struct {
    u16 countAndFlags;
    u16 colors[24][16];
    u16 padding[1];
} DAT_060D70B0 = {
    0x0018,
    {
        {0x98C6, 0x8000, 0xFF5A, 0xFFF9, 0xFF5A, 0xFF5A, 0xFF5A, 0xFF5A, 0x843F,
         0xFFFD, 0xDA70, 0xE2D6, 0xDEF6, 0xCDCE, 0xD294, 0xF2F3},
        {0x98C6, 0x8000, 0xD2D4, 0x8000, 0xDAD4, 0xFFFF, 0xFFFF, 0xFFFF, 0x843F,
         0xFF39, 0xFF39, 0xFFFF, 0xFFFF, 0xEF5B, 0xD294, 0xEF5A},
        {0x98C6, 0x8000, 0xCA50, 0xFFF9, 0xD230, 0xCDEF, 0xFF5A, 0xFF5A, 0x801F,
         0xFB39, 0xFF39, 0xFF5A, 0xCE14, 0xBDEF, 0xD294, 0xEAD3},
        {0x98C6, 0x8000, 0xD275, 0xFFF9, 0xDA52, 0xD20D, 0xFFD9, 0xDED2, 0x843F,
         0xEEB5, 0xFF39, 0xD273, 0xFFFF, 0xE694, 0xD294, 0xE24C},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0xFB39, 0xFFF9, 0xFB39, 0xFB39, 0xFB39, 0xFB39, 0x843F,
         0xFFF9, 0x801F, 0xE6F5, 0xE6D5, 0xDA50, 0xD294, 0xF2D1},
        {0x98C6, 0x8000, 0xCA51, 0xFFF9, 0xFF39, 0xFF39, 0xFF39, 0xFF39, 0x843F,
         0xFFF9, 0x801F, 0xEF15, 0xFBBD, 0xDAD0, 0xD294, 0xF39C},
        {0x98C6, 0x8000, 0xE2D7, 0xFFF9, 0xEF14, 0xDE94, 0xFFB9, 0xE2D4, 0x843F,
         0xFFF9, 0x801F, 0xEF18, 0xF779, 0xDAB2, 0xD294, 0xEA90},
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
        {0x98C6, 0x8000, 0x801E, 0x815D, 0x801E, 0x801E, 0x801E, 0x801E, 0x843F,
         0x807F, 0x8493, 0x809A, 0x808F, 0x800D, 0xD294, 0xF2F3},
        {0x98C6, 0x8000, 0x844F, 0x8000, 0x8016, 0x991F, 0x991F, 0x991F, 0x843F,
         0x801D, 0x801D, 0x991F, 0x991F, 0x991F, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x8009, 0x815D, 0x800F, 0x8009, 0x8C1E, 0x8C1E, 0x801F,
         0x801D, 0x801D, 0x8C1E, 0x8094, 0x880F, 0xD294, 0xEAD3},
        {0x98C6, 0x8000, 0x8006, 0x815D, 0x8010, 0x800A, 0x805D, 0x800D, 0x843F,
         0x8013, 0x801D, 0x801A, 0xA19F, 0x8810, 0xD294, 0xE24C},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x801D, 0x815D, 0x801D, 0x801D, 0x801D, 0x801D, 0x843F,
         0x815D, 0x801F, 0x840A, 0x840A, 0x840A, 0xD294, 0xF2D1},
        {0x98C6, 0x8000, 0x8006, 0x815D, 0x801D, 0x801D, 0x801D, 0x801D, 0x843F,
         0x815D, 0x801F, 0x840A, 0x840A, 0x840A, 0xD294, 0xF39C},
        {0x98C6, 0x8000, 0x8806, 0x815D, 0x800A, 0x8005, 0x803D, 0x8008, 0x843F,
         0x815D, 0x801F, 0x880A, 0x880A, 0x8007, 0xD294, 0xEA90},
    },
    {0x0000},
};

SaturnSpriteResource DAT_060D73B4 = {
    DAT_060D666C, (u16*)&DAT_060D70B0, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D73C0[1] = {&DAT_060D73B4};
