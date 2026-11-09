// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6548();
void func_060D6690();
void func_060D66A8();
void func_060D66C0();
void func_060D66D8();
void func_060D66F0();
void func_060D66FC();
void func_060D6714();
void func_060D672C();
void func_060D6744();
void func_060D675C();
void func_060D6774();
void func_060D678C();
void func_060D67A4();
void func_060D67BC();
extern SaturnSpriteResource* DAT_060D7318[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6548,
        func_060D6690,
        func_060D66A8,
        func_060D66C0,
        func_060D66D8,
        func_060D66F0,
        func_060D67BC,
        func_060D66FC,
        func_060D6714,
        func_060D672C,
        func_060D6744,
        func_060D675C,
        func_060D6774,
        func_060D678C,
        func_060D67A4,
    },
    DAT_060D7318,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x30303030, 0x30383661, 0x20322A2A, 0x20326420,
    0x2E746578, 0x740D0A30, 0x30303030};

INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D6548, func_060D6548);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D6690, func_060D6690);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D66A8, func_060D66A8);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D66C0, func_060D66C0);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D66D8, func_060D66D8);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D66F0, func_060D66F0);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D66FC, func_060D66FC);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D6714, func_060D6714);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D672C, func_060D672C);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D6744, func_060D6744);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D675C, func_060D675C);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D6774, func_060D6774);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D678C, func_060D678C);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D67A4, func_060D67A4);
INCLUDE_ASM("asm/saturn/weapon/w_56/f_nonmat", f60D67BC, func_060D67BC);

u16 DAT_060D67D0[15] = {
    0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607, 0x0608,
    0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0x080D, 0xFFFF};

u16 DAT_060D67EE[15] = {
    0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14, 0x0E15,
    0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0x0822, 0xFFFF};

u16 DAT_060D680C[15] = {
    0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C, 0x141D,
    0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0x0822, 0xFFFF};

u16 DAT_060D682A[12] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0x082C, 0xFFFF};

u16 DAT_060D6842[12] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0x083E, 0xFFFF};

u16 DAT_060D685A[12] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0x083E, 0xFFFF};

u16 DAT_060D6872[14] = {0x0201, 0x263F, 0x2640, 0x2641, 0x0606, 0x0607, 0x0608,
                        0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0x080D, 0xFFFF};

u16 DAT_060D688E[14] = {0x0A0E, 0x2842, 0x2843, 0x2844, 0x0E13, 0x0E14, 0x0E15,
                        0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0x0822, 0xFFFF};

u16 DAT_060D68AA[14] = {0x0A0E, 0x2A45, 0x2A46, 0x2A47, 0x141B, 0x141C, 0x141D,
                        0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0x0822, 0xFFFF};

u16 DAT_060D68C6[11] = {0x1623, 0x2C48, 0x2C49, 0x2C4A, 0x1A28, 0x1A29,
                        0x1A2A, 0x1A2B, 0x082C, 0x082C, 0xFFFF};

u16 DAT_060D68DC[11] = {0x1C2D, 0x2E4B, 0x2E4C, 0x2E4D, 0x2032, 0x2033,
                        0x2034, 0x2035, 0x083E, 0x083E, 0xFFFF};

u16 DAT_060D68F2[11] = {0x1C2D, 0x304E, 0x304F, 0x3050, 0x243A, 0x243B,
                        0x243C, 0x243D, 0x083E, 0x083E, 0xFFFF};

s8 DAT_060D6908[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D696C[7] = {DAT_060D67D0, DAT_060D67D0, DAT_060D67EE, DAT_060D680C,
                        DAT_060D682A, DAT_060D6842, DAT_060D685A};

u16* DAT_060D6988[7] = {DAT_060D6872, DAT_060D6872, DAT_060D688E, DAT_060D68AA,
                        DAT_060D68C6, DAT_060D68DC, DAT_060D68F2};

WeaponAnimation DAT_060D69A4[3] = {
    {(u16**)DAT_060D6988, (s8*)DAT_060D6908, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D696C, (s8*)DAT_060D6908, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D696C, (s8*)DAT_060D6908, 0x0000, 0x060B, 0x39, 0x04, 0},
};

u32 DAT_060D69D4[65] = {
    0xFFF1FFE5, 0xFFF1FFEE, 0xFFFA000A, 0xFFF7FFF8, 0x011A011B, 0x011C011D,
    0x011E011F, 0x01200121, 0x01220122, 0x01210120, 0x011F011E, 0x011D011C,
    0x011B011A, 0x06080609, 0x070A070B, 0x080C080D, 0x090E090F, 0x09100001,
    0x00000000, 0x002508E0, 0x60000000, 0x00010001, 0x00010020, 0x04806000,
    0x00000000, 0x00000000, 0x003000E0, 0x60000000, 0x00000000, 0x00010018,
    0x02E06000, 0x00000000, 0x00000000, 0x002508E0, 0x60000000, 0x00000001,
    0x00010020, 0x0C806000, 0x00000001, 0x00000000, 0x003000F0, 0x60000000,
    0x00010000, 0x00000018, 0x06006000, 0x00000000, 0x00010000, 0x00280000,
    0x60000000, 0x00010000, 0x00010030, 0x0AF06000, 0x00000002, 0x00510002,
    0x00520001, 0x00530002, 0x00580001, 0x00590002, 0x005A0001, 0x005B0002,
    0x00540001, 0x00550002, 0x00560001, 0x0057FFFF, 0x00000000,
};

SaturnSpriteImage DAT_060D6AD8[17] = {
    {12, 5, 0x0000},  {40, 4, 0x0010},  {24, 4, 0x0038},  {8, 1, 0x0050},
    {32, 19, 0x0054}, {24, 12, 0x00EC}, {20, 32, 0x0134}, {16, 32, 0x01D4},
    {40, 31, 0x0254}, {36, 31, 0x038C}, {20, 27, 0x04A4}, {20, 26, 0x052C},
    {20, 21, 0x05B0}, {20, 15, 0x061C}, {8, 18, 0x0668},  {4, 16, 0x068C},
    {0, 0, 0x069C},
};

struct {
    u16 countAndFlags;
    u16 colors[12][16];
    u16 padding[1];
} DAT_060D6B1C = {
    0x000C,
    {
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
        {0x8160, 0x8005, 0x8007, 0x8009, 0x800B, 0x800C, 0x800E, 0x8010, 0x8012,
         0x8033, 0x8435, 0x8437, 0x8438, 0x843A, 0x843C, 0x843E},
        {0x8160, 0x9820, 0xA040, 0xA840, 0xB040, 0xB840, 0xBC60, 0xC460, 0xCC60,
         0xD460, 0xDC80, 0xE080, 0xE880, 0xF080, 0xF8A0, 0xFCA0},
        {0x8160, 0xC0EF, 0xC10E, 0xC54E, 0xC98E, 0xCDCE, 0xD20E, 0xD64E, 0xDA70,
         0xDEB2, 0xE2D4, 0xE716, 0xEB38, 0xEF7A, 0xF39C, 0xFBDE},
        {0x8160, 0x80C0, 0x8100, 0x8520, 0x8560, 0x8980, 0x89A0, 0x8DE0, 0x8E00,
         0x9240, 0x9260, 0x9680, 0x96C0, 0x9AE0, 0x9B20, 0x9F40},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6CA0 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6CA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CBC = {
    {0x0100, 0x0000},
    {
        {0x0100, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CC8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CD4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CEC = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CF8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D04 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D10 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D1C = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D28 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D34 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D40 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D4C = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D58 = {
    {0x0100, 0x0000},
    {
        {0x0100, 33, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D64 = {
    {0x0100, 0x0000},
    {
        {0x0200, 33, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D70 = {
    {0x0100, 0x0000},
    {
        {0x0300, 33, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D7C = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D88 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D94 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DA0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DAC = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DB8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DC4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DD0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DDC = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6DE8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6DF4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E00 = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E0C = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E18 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E24 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E30 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E3C = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E48 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E54 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E60 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E6C = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E78 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E84 = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E90 = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E9C = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EA8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6EB4 = {
    {0x0100, 0x0000},
    {
        {0x0400, -5, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EC0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6ECC = {
    {0x0100, 0x0000},
    {
        {0x0100, 33, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6ED8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 33, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EE4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 33, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EF0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EFC = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6F08 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6F14 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6F20 = {
    {0x0100, 0x0000},
    {
        {0x0100, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F2C = {
    {0x0100, 0x0000},
    {
        {0x0100, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F38 = {
    {0x0100, 0x0000},
    {
        {0x0200, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F44 = {
    {0x0100, 0x0000},
    {
        {0x0300, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F50 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F5C = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F68 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F74 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F80 = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F8C = {
    {0x0100, 0x0000},
    {
        {0x0500, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F98 = {
    {0x0100, 0x0000},
    {
        {0x0600, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FA4 = {
    {0x0100, 0x0000},
    {
        {0x0700, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FB0 = {
    {0x0100, 0x0000},
    {
        {0x0500, 31, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FBC = {
    {0x0100, 0x0000},
    {
        {0x0600, 31, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FC8 = {
    {0x0100, 0x0000},
    {
        {0x0700, 31, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FD4 = {
    {0x0100, 0x0000},
    {
        {0x0500, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FE0 = {
    {0x0100, 0x0000},
    {
        {0x0600, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FEC = {
    {0x0100, 0x0000},
    {
        {0x0700, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FF8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 37, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7004 = {
    {0x0100, 0x0000},
    {
        {0x0600, 37, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7010 = {
    {0x0100, 0x0000},
    {
        {0x0700, 37, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D701C = {
    {0x0100, 0x0000},
    {
        {0x0500, 35, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7028 = {
    {0x0100, 0x0000},
    {
        {0x0600, 35, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7034 = {
    {0x0100, 0x0000},
    {
        {0x0700, 35, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7040 = {
    {0x0100, 0x0000},
    {
        {0x0500, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D704C = {
    {0x0100, 0x0000},
    {
        {0x0600, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7058 = {
    {0x0100, 0x0000},
    {
        {0x0700, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7064 = {
    {0x0100, 0x0000},
    {
        {0x0800, 32, -7, 6},
    },
};

SaturnSpriteFrame2 DAT_060D7070 = {
    {0x0200, 0x0000},
    {
        {0x0800, 34, -7, 7},
        {0x0820, 40, -11, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7084 = {
    {0x0100, 0x0000},
    {
        {0x0820, 42, -6, 7},
    },
};

SaturnSpriteFrame1 DAT_060D7090 = {
    {0x0100, 0x0000},
    {
        {0x0820, 59, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D709C = {
    {0x0100, 0x0000},
    {
        {0x0820, 61, -7, 9},
    },
};

SaturnSpriteFrame1 DAT_060D70A8 = {
    {0x0100, 0x0000},
    {
        {0x0800, 59, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D70B4 = {
    {0x0100, 0x0000},
    {
        {0x0800, 61, -7, 9},
    },
};

SaturnSpriteFrame1 DAT_060D70C0 = {
    {0x0100, 0x0000},
    {
        {0x0820, 51, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D70CC = {
    {0x0100, 0x0000},
    {
        {0x0820, 53, -7, 9},
    },
};

SaturnSpriteFrame1 DAT_060D70D8 = {
    {0x0100, 0x0000},
    {
        {0x0800, 51, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D70E4 = {
    {0x0100, 0x0000},
    {
        {0x0800, 53, -7, 9},
    },
};

SaturnSpriteFrame1 DAT_060D70F0 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 33, -7, 10},
    },
};

SaturnSpriteFrame1 DAT_060D70FC = {
    {0x0100, 0x0000},
    {
        {0x0A00, 37, -6, 11},
    },
};

SaturnSpriteFrame1 DAT_060D7108 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 50, -1, 12},
    },
};

SaturnSpriteFrame2 DAT_060D7114 = {
    {0x0200, 0x0000},
    {
        {0x0A00, 52, -7, 13},
        {0x0A20, 41, 1, 10},
    },
};

SaturnSpriteFrame1 DAT_060D7128 = {
    {0x0100, 0x0000},
    {
        {0x0A20, 46, 0, 11},
    },
};

SaturnSpriteFrame1 DAT_060D7134 = {
    {0x0100, 0x0000},
    {
        {0x0A20, 57, -3, 12},
    },
};

SaturnSpriteFrame2 DAT_060D7140 = {
    {0x0200, 0x0000},
    {
        {0x0A20, 59, -9, 13},
        {0x0A00, 50, -23, 14},
    },
};

SaturnSpriteFrame1 DAT_060D7154 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 63, -15, 15},
    },
};

SaturnSpriteFrame2 DAT_060D7160 = {
    {0x0200, 0x0000},
    {
        {0x0A00, 67, -11, 15},
        {0x0A00, 62, 8, 13},
    },
};

SaturnSpriteFrameHeader* DAT_060D7174[102] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6CA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6CD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6D04,
    (SaturnSpriteFrameHeader*)&DAT_060D6D10,
    (SaturnSpriteFrameHeader*)&DAT_060D6D1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D28,
    (SaturnSpriteFrameHeader*)&DAT_060D6D34,
    (SaturnSpriteFrameHeader*)&DAT_060D6D40,
    (SaturnSpriteFrameHeader*)&DAT_060D6D4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D58,
    (SaturnSpriteFrameHeader*)&DAT_060D6D64,
    (SaturnSpriteFrameHeader*)&DAT_060D6D70,
    (SaturnSpriteFrameHeader*)&DAT_060D6D7C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D88,
    (SaturnSpriteFrameHeader*)&DAT_060D6D94,
    (SaturnSpriteFrameHeader*)&DAT_060D6DA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6E00,
    (SaturnSpriteFrameHeader*)&DAT_060D6E0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E18,
    (SaturnSpriteFrameHeader*)&DAT_060D6E24,
    (SaturnSpriteFrameHeader*)&DAT_060D6E30,
    (SaturnSpriteFrameHeader*)&DAT_060D6E3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E48,
    (SaturnSpriteFrameHeader*)&DAT_060D6E54,
    (SaturnSpriteFrameHeader*)&DAT_060D6E60,
    (SaturnSpriteFrameHeader*)&DAT_060D6E6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E78,
    (SaturnSpriteFrameHeader*)&DAT_060D6E84,
    (SaturnSpriteFrameHeader*)&DAT_060D6E90,
    (SaturnSpriteFrameHeader*)&DAT_060D6E9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6EA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6EB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6EC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6ECC,
    (SaturnSpriteFrameHeader*)&DAT_060D6ED8,
    (SaturnSpriteFrameHeader*)&DAT_060D6EE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6EF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6F08,
    (SaturnSpriteFrameHeader*)&DAT_060D6F14,
    (SaturnSpriteFrameHeader*)&DAT_060D6F20,
    (SaturnSpriteFrameHeader*)&DAT_060D6F2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F38,
    (SaturnSpriteFrameHeader*)&DAT_060D6F44,
    (SaturnSpriteFrameHeader*)&DAT_060D6F50,
    (SaturnSpriteFrameHeader*)&DAT_060D6F5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F68,
    (SaturnSpriteFrameHeader*)&DAT_060D6F74,
    (SaturnSpriteFrameHeader*)&DAT_060D6F80,
    (SaturnSpriteFrameHeader*)&DAT_060D6F8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F98,
    (SaturnSpriteFrameHeader*)&DAT_060D6FA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6FB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6FC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6FD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6FE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6FF8,
    (SaturnSpriteFrameHeader*)&DAT_060D7004,
    (SaturnSpriteFrameHeader*)&DAT_060D7010,
    (SaturnSpriteFrameHeader*)&DAT_060D701C,
    (SaturnSpriteFrameHeader*)&DAT_060D7028,
    (SaturnSpriteFrameHeader*)&DAT_060D7034,
    (SaturnSpriteFrameHeader*)&DAT_060D7040,
    (SaturnSpriteFrameHeader*)&DAT_060D704C,
    (SaturnSpriteFrameHeader*)&DAT_060D7058,
    (SaturnSpriteFrameHeader*)&DAT_060D7064,
    (SaturnSpriteFrameHeader*)&DAT_060D7070,
    (SaturnSpriteFrameHeader*)&DAT_060D7084,
    (SaturnSpriteFrameHeader*)&DAT_060D7090,
    (SaturnSpriteFrameHeader*)&DAT_060D709C,
    (SaturnSpriteFrameHeader*)&DAT_060D70A8,
    (SaturnSpriteFrameHeader*)&DAT_060D70B4,
    (SaturnSpriteFrameHeader*)&DAT_060D70C0,
    (SaturnSpriteFrameHeader*)&DAT_060D70CC,
    (SaturnSpriteFrameHeader*)&DAT_060D70D8,
    (SaturnSpriteFrameHeader*)&DAT_060D70E4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CA0,
    (SaturnSpriteFrameHeader*)&DAT_060D70F0,
    (SaturnSpriteFrameHeader*)&DAT_060D70FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7108,
    (SaturnSpriteFrameHeader*)&DAT_060D7114,
    (SaturnSpriteFrameHeader*)&DAT_060D7128,
    (SaturnSpriteFrameHeader*)&DAT_060D7134,
    (SaturnSpriteFrameHeader*)&DAT_060D7140,
    (SaturnSpriteFrameHeader*)&DAT_060D7154,
    (SaturnSpriteFrameHeader*)&DAT_060D7160,
};

SaturnSpriteResource DAT_060D730C = {
    DAT_060D6AD8, (u16*)&DAT_060D6B1C, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7318[1] = {&DAT_060D730C};
