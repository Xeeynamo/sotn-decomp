// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62EC();
void func_060D66BC();
void func_060D66D4();
void func_060D66EC();
void func_060D6704();
void func_060D671C();
void func_060D6728();
void func_060D6740();
void func_060D6758();
void func_060D6770();
void func_060D6788();
void func_060D67A0();
void func_060D67B8();
void func_060D67D0();
void func_060D67E8();
extern SaturnSpriteResource* DAT_060D7160[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62EC,
        func_060D66BC,
        func_060D66D4,
        func_060D66EC,
        func_060D6704,
        func_060D671C,
        func_060D67E8,
        func_060D6728,
        func_060D6740,
        func_060D6758,
        func_060D6770,
        func_060D6788,
        func_060D67A0,
        func_060D67B8,
        func_060D67D0,
    },
    DAT_060D7160,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x000000F8, 0x00000000, 0x00000000, 0x00000000,
    0x00000020, 0x2E746578, 0x74000000};

INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D62EC, func_060D62EC);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D66BC, func_060D66BC);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D66D4, func_060D66D4);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D66EC, func_060D66EC);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D6704, func_060D6704);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D671C, func_060D671C);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D6728, func_060D6728);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D6740, func_060D6740);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D6758, func_060D6758);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D6770, func_060D6770);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D6788, func_060D6788);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D67A0, func_060D67A0);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D67B8, func_060D67B8);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D67D0, func_060D67D0);
INCLUDE_ASM("asm/saturn/weapon/w_55/f_nonmat", f60D67E8, func_060D67E8);

u16 DAT_060D6800[14] = {0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607,
                        0x0608, 0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D681C[14] = {0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14,
                        0x0E15, 0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6838[14] = {0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C,
                        0x141D, 0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6854[11] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D686A[11] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D6880[11] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF};

u16 DAT_060D6896[69] = {
    0x0201, 0x263F, 0x2640, 0x2641, 0x0606, 0x0607, 0x0608, 0x0609, 0x080A,
    0x080B, 0x080C, 0x080D, 0xFFFF, 0x0A0E, 0x2842, 0x2843, 0x2844, 0x0E13,
    0x0E14, 0x0E15, 0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF, 0x0A0E,
    0x2A45, 0x2A46, 0x2A47, 0x141B, 0x141C, 0x141D, 0x141E, 0x081F, 0x0820,
    0x0821, 0x0822, 0xFFFF, 0x1623, 0x2C48, 0x2C49, 0x2C4A, 0x1A28, 0x1A29,
    0x1A2A, 0x1A2B, 0x082C, 0xFFFF, 0x1C2D, 0x2E4B, 0x2E4C, 0x2E4D, 0x2032,
    0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF, 0x1C2D, 0x304E, 0x304F, 0x3050,
    0x243A, 0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF,
};

s8 DAT_060D6920[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D6984[7] = {DAT_060D6800, DAT_060D6800, DAT_060D681C, DAT_060D6838,
                        DAT_060D6854, DAT_060D686A, DAT_060D6880};

u32 DAT_060D69A0[7] = {
    0x060D6896, 0x060D6896, 0x060D68B0, 0x060D68CA,
    0x060D68E4, 0x060D68F8, 0x060D690C,
};

WeaponAnimation DAT_060D69BC[1] = {
    {(u16**)DAT_060D6984, (s8*)DAT_060D6920, 0x0000, 0x060B, 0x39, 0x04, 0},
};
u32 DAT_060D69BC_tail[8] = {
    0x060D6984, 0x060D6920, 0x0000060B, 0x39040000,
    0x060D69A0, 0x060D6920, 0x0000060B, 0x39040000,
};

u32 DAT_060D69EC[42] = {
    0x0001010C, 0xFFDBFFB4, 0x00580058, 0x00010000, 0x00280028, 0x00800080,
    0x00000002, 0x0126000B, 0xFFD50010, 0x00200000, 0x00000070, 0x00000080,
    0x00200124, 0xFFFDFFD5, 0x00100020, 0x00000000, 0x00700000, 0x00800020,
    0x00000001, 0x0110FFFD, 0xFFD50020, 0x00200000, 0x00000000, 0x00400020,
    0x00600000, 0x00010118, 0xFFFEFFD5, 0x00200020, 0x00000000, 0x00000060,
    0x00200080, 0x00000000, 0x00000000, 0x060D69EC, 0x060D6A06, 0x060D6A36,
    0x060D6A50, 0x00020051, 0x00020052, 0x00020053, 0x00020054, 0xFFFF0000,
};

SaturnSpriteImage DAT_060D6A94[11] = {
    {16, 8, 0x0000},  {48, 12, 0x0020}, {24, 8, 0x00B0},  {12, 8, 0x00E0},
    {44, 28, 0x00F8}, {28, 16, 0x022C}, {60, 44, 0x029C}, {12, 16, 0x0530},
    {20, 16, 0x0560}, {20, 16, 0x05B0}, {0, 0, 0x0600},
};

struct {
    u16 countAndFlags;
    u16 colors[10][16];
    u16 padding[1];
} DAT_060D6AC0 = {
    0x000A,
    {
        {0x98C6, 0x8000, 0xA821, 0x9DC0, 0xA821, 0xA821, 0xA821, 0xA821, 0x843F,
         0xB0E4, 0x9CA4, 0x8000, 0x8000, 0x8000, 0xD294, 0xF2F3},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xED8C, 0xED8C, 0xED8C, 0x843F,
         0xBC00, 0xBC00, 0xED8C, 0xED8C, 0xED8C, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x8000, 0x9DC0, 0x8000, 0x8000, 0xE021, 0xE021, 0x801F,
         0x9C00, 0xB800, 0xE021, 0x8000, 0x8000, 0xD294, 0xEAD3},
        {0x98C6, 0x8000, 0x8000, 0x9DC0, 0x8000, 0x8000, 0xA0C0, 0x8000, 0x843F,
         0x8000, 0xA800, 0x8000, 0xF608, 0x8000, 0xD294, 0xE24C},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x9C00, 0x9DC0, 0x9C00, 0x9C00, 0x9C00, 0x9C00, 0x843F,
         0xB9C0, 0x801F, 0x8000, 0x8000, 0x8000, 0xD294, 0xF2D1},
        {0x98C6, 0x8000, 0x8000, 0x9DC0, 0xD400, 0xD400, 0xD400, 0xD400, 0x843F,
         0xB9C0, 0x801F, 0x8000, 0x8000, 0x8000, 0xD294, 0xF39C},
        {0x98C6, 0x8000, 0x8000, 0x9DC0, 0x8000, 0x8000, 0xCCA0, 0x8000, 0x843F,
         0xB9C0, 0x801F, 0x8000, 0x8000, 0x8000, 0xD294, 0xEA90},
        {0x9484, 0xF342, 0xD280, 0x94A9, 0xA14D, 0xA217, 0xB6DC, 0x9CA4, 0xB0E5,
         0xC988, 0xAE75, 0x9DEE, 0xA507, 0xB58A, 0xCA0E, 0xDAD4},
        {0x9143, 0xF840, 0xF961, 0xFEA2, 0xFFE3, 0xB969, 0xD9B0, 0x9C10, 0x9D7A,
         0x9F5F, 0x8842, 0x98C6, 0xA94A, 0xC1EF, 0xD694, 0xEF99},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6C04 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6C08 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C14 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C20 = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C2C = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C38 = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C44 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C50 = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C5C = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C68 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C74 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C80 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C8C = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C98 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CBC = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CC8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CD4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CEC = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CF8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D04 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D10 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D1C = {
    {0x0100, 0x0000},
    {
        {0x0100, 22, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D28 = {
    {0x0100, 0x0000},
    {
        {0x0200, 22, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D34 = {
    {0x0100, 0x0000},
    {
        {0x0300, 22, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D40 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D4C = {
    {0x0100, 0x0000},
    {
        {0x0100, 20, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D58 = {
    {0x0100, 0x0000},
    {
        {0x0200, 20, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D64 = {
    {0x0100, 0x0000},
    {
        {0x0300, 20, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D70 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D7C = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D88 = {
    {0x0100, 0x0000},
    {
        {0x0000, -26, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D94 = {
    {0x0100, 0x0000},
    {
        {0x0000, -26, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DA0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DAC = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DB8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DC4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DD0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DDC = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DE8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 33, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DF4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 33, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E00 = {
    {0x0100, 0x0000},
    {
        {0x0300, 33, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E0C = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, -9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E18 = {
    {0x0100, 0x0000},
    {
        {0x0400, -8, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E30 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E3C = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E48 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E60 = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E6C = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E78 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E84 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6E90 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6E9C = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6EA8 = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6EB4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6EC0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6ECC = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6ED8 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6EE4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -21, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6EF0 = {
    {0x0100, 0x0000},
    {
        {0x0500, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EFC = {
    {0x0100, 0x0000},
    {
        {0x0600, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F08 = {
    {0x0100, 0x0000},
    {
        {0x0700, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F14 = {
    {0x0100, 0x0000},
    {
        {0x0500, 26, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F20 = {
    {0x0100, 0x0000},
    {
        {0x0600, 26, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F2C = {
    {0x0100, 0x0000},
    {
        {0x0700, 26, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F38 = {
    {0x0100, 0x0000},
    {
        {0x0500, 24, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F44 = {
    {0x0100, 0x0000},
    {
        {0x0600, 24, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F50 = {
    {0x0100, 0x0000},
    {
        {0x0700, 24, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F5C = {
    {0x0100, 0x0000},
    {
        {0x0500, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F68 = {
    {0x0100, 0x0000},
    {
        {0x0600, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F74 = {
    {0x0100, 0x0000},
    {
        {0x0700, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F80 = {
    {0x0100, 0x0000},
    {
        {0x0500, 30, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F8C = {
    {0x0100, 0x0000},
    {
        {0x0600, 30, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F98 = {
    {0x0100, 0x0000},
    {
        {0x0700, 30, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FA4 = {
    {0x0100, 0x0000},
    {
        {0x0500, 34, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FB0 = {
    {0x0100, 0x0000},
    {
        {0x0600, 34, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FBC = {
    {0x0100, 0x0000},
    {
        {0x0700, 34, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FC8 = {
    {0x0100, 0x0000},
    {
        {0x0800, -4, -4, 6},
    },
};

SaturnSpriteFrame2 DAT_060D6FD4 = {
    {0x0200, 0x0000},
    {
        {0x0900, -4, 0, 7},
        {0x0910, 4, 25, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6FE8 = {
    {0x0100, 0x0000},
    {
        {0x0900, 0, 0, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6FF4 = {
    {0x0100, 0x0000},
    {
        {0x0900, 0, 0, 9},
    },
};

SaturnSpriteFrameHeader* DAT_060D7000[85] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6C04,
    (SaturnSpriteFrameHeader*)&DAT_060D6C08,
    (SaturnSpriteFrameHeader*)&DAT_060D6C14,
    (SaturnSpriteFrameHeader*)&DAT_060D6C20,
    (SaturnSpriteFrameHeader*)&DAT_060D6C2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C38,
    (SaturnSpriteFrameHeader*)&DAT_060D6C44,
    (SaturnSpriteFrameHeader*)&DAT_060D6C50,
    (SaturnSpriteFrameHeader*)&DAT_060D6C5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C68,
    (SaturnSpriteFrameHeader*)&DAT_060D6C74,
    (SaturnSpriteFrameHeader*)&DAT_060D6C80,
    (SaturnSpriteFrameHeader*)&DAT_060D6C8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C98,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6FE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6FF4,
};

SaturnSpriteResource DAT_060D7154 = {
    DAT_060D6A94, (u16*)&DAT_060D6AC0, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7160[1] = {&DAT_060D7154};
