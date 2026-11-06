// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6570();
void func_060D6588();
void func_060D65A0();
void func_060D65B8();
void func_060D65D0();
void func_060D65E8();
void func_060D65F4();
void func_060D660C();
void func_060D6624();
void func_060D663C();
void func_060D6654();
void func_060D666C();
void func_060D6684();
void func_060D669C();
void func_060D66B4();
extern SaturnSpriteResource* DAT_060D6F08[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6570,
        func_060D6588,
        func_060D65A0,
        func_060D65B8,
        func_060D65D0,
        func_060D65E8,
        func_060D66B4,
        func_060D65F4,
        func_060D660C,
        func_060D6624,
        func_060D663C,
        func_060D6654,
        func_060D666C,
        func_060D6684,
        func_060D669C,
    },
    DAT_060D6F08,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D6570, func_060D6570);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D6588, func_060D6588);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D65A0, func_060D65A0);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D65B8, func_060D65B8);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D65D0, func_060D65D0);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D65E8, func_060D65E8);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D65F4, func_060D65F4);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D660C, func_060D660C);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D6624, func_060D6624);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D663C, func_060D663C);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D6654, func_060D6654);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D666C, func_060D666C);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D6684, func_060D6684);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D669C, func_060D669C);
INCLUDE_ASM("asm/saturn/weapon/w_54/f_nonmat", f60D66B4, func_060D66B4);

u16 DAT_060D66C0[15] = {
    0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607, 0x0608,
    0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0x080D, 0xFFFF};

u16 DAT_060D66DE[15] = {
    0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14, 0x0E15,
    0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0x0822, 0xFFFF};

u16 DAT_060D66FC[15] = {
    0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C, 0x141D,
    0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0x0822, 0xFFFF};

u16 DAT_060D671A[12] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0x082C, 0xFFFF};

u16 DAT_060D6732[12] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0x083E, 0xFFFF};

u16 DAT_060D674A[12] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0x083E, 0xFFFF};

u16 DAT_060D6762[14] = {0x0201, 0x263F, 0x2640, 0x2641, 0x0606, 0x0607, 0x0608,
                        0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0x080D, 0xFFFF};

u16 DAT_060D677E[14] = {0x0A0E, 0x2842, 0x2843, 0x2844, 0x0E13, 0x0E14, 0x0E15,
                        0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0x0822, 0xFFFF};

u16 DAT_060D679A[14] = {0x0A0E, 0x2A45, 0x2A46, 0x2A47, 0x141B, 0x141C, 0x141D,
                        0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0x0822, 0xFFFF};

u16 DAT_060D67B6[11] = {0x1623, 0x2C48, 0x2C49, 0x2C4A, 0x1A28, 0x1A29,
                        0x1A2A, 0x1A2B, 0x082C, 0x082C, 0xFFFF};

u16 DAT_060D67CC[11] = {0x1C2D, 0x2E4B, 0x2E4C, 0x2E4D, 0x2032, 0x2033,
                        0x2034, 0x2035, 0x083E, 0x083E, 0xFFFF};

u16 DAT_060D67E2[11] = {0x1C2D, 0x304E, 0x304F, 0x3050, 0x243A, 0x243B,
                        0x243C, 0x243D, 0x083E, 0x083E, 0xFFFF};

s8 DAT_060D67F8[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D685C[7] = {DAT_060D66C0, DAT_060D66C0, DAT_060D66DE, DAT_060D66FC,
                        DAT_060D671A, DAT_060D6732, DAT_060D674A};

u16* DAT_060D6878[7] = {DAT_060D6762, DAT_060D6762, DAT_060D677E, DAT_060D679A,
                        DAT_060D67B6, DAT_060D67CC, DAT_060D67E2};

WeaponAnimation DAT_060D6894[3] = {
    {(u16**)DAT_060D6878, (s8*)DAT_060D67F8, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D685C, (s8*)DAT_060D67F8, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D685C, (s8*)DAT_060D67F8, 0x0000, 0x060B, 0x39, 0x04, 0},
};

u32 DAT_060D68C4[4] = {
    0xFFF1FFE5,
    0xFFF1FFEE,
    0xFFFA000A,
    0xFFF7FFF8,
};

SaturnSpriteImage DAT_060D68D4[7] = {
    {16, 8, 0x0000},  {48, 12, 0x0020}, {24, 8, 0x00B0}, {12, 8, 0x00E0},
    {44, 28, 0x00F8}, {28, 16, 0x022C}, {0, 0, 0x029C},
};

SaturnSpriteFrameHeader DAT_060D68F0 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D68F4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6900 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D690C = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6918 = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6924 = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6930 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D693C = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6948 = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6954 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6960 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D696C = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6978 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6984 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6990 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D699C = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69A8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69B4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69C0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69CC = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D69D8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D69E4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D69F0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D69FC = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A08 = {
    {0x0100, 0x0000},
    {
        {0x0100, 22, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A14 = {
    {0x0100, 0x0000},
    {
        {0x0200, 22, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A20 = {
    {0x0100, 0x0000},
    {
        {0x0300, 22, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A2C = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6A38 = {
    {0x0100, 0x0000},
    {
        {0x0100, 20, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6A44 = {
    {0x0100, 0x0000},
    {
        {0x0200, 20, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6A50 = {
    {0x0100, 0x0000},
    {
        {0x0300, 20, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6A5C = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A68 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A74 = {
    {0x0100, 0x0000},
    {
        {0x0000, -26, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A80 = {
    {0x0100, 0x0000},
    {
        {0x0000, -26, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A8C = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6A98 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6AA4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6AB0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6ABC = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6AC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6AD4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 33, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6AE0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 33, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6AEC = {
    {0x0100, 0x0000},
    {
        {0x0300, 33, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6AF8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, -9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6B04 = {
    {0x0100, 0x0000},
    {
        {0x0400, -8, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6B10 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6B1C = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6B28 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6B34 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6B40 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B4C = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B58 = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B64 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B70 = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6B7C = {
    {0x0100, 0x0000},
    {
        {0x0100, 30, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6B88 = {
    {0x0100, 0x0000},
    {
        {0x0200, 30, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6B94 = {
    {0x0100, 0x0000},
    {
        {0x0300, 30, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6BA0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6BAC = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6BB8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6BC4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6BD0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -21, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BDC = {
    {0x0100, 0x0000},
    {
        {0x0500, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6BE8 = {
    {0x0100, 0x0000},
    {
        {0x0600, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6BF4 = {
    {0x0100, 0x0000},
    {
        {0x0700, 36, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C00 = {
    {0x0100, 0x0000},
    {
        {0x0500, 26, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C0C = {
    {0x0100, 0x0000},
    {
        {0x0600, 26, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C18 = {
    {0x0100, 0x0000},
    {
        {0x0700, 26, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C24 = {
    {0x0100, 0x0000},
    {
        {0x0500, 24, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6C30 = {
    {0x0100, 0x0000},
    {
        {0x0600, 24, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6C3C = {
    {0x0100, 0x0000},
    {
        {0x0700, 24, 13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6C48 = {
    {0x0100, 0x0000},
    {
        {0x0500, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C54 = {
    {0x0100, 0x0000},
    {
        {0x0600, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C60 = {
    {0x0100, 0x0000},
    {
        {0x0700, 32, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C6C = {
    {0x0100, 0x0000},
    {
        {0x0500, 30, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C78 = {
    {0x0100, 0x0000},
    {
        {0x0600, 30, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C84 = {
    {0x0100, 0x0000},
    {
        {0x0700, 30, -19, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C90 = {
    {0x0100, 0x0000},
    {
        {0x0500, 34, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6C9C = {
    {0x0100, 0x0000},
    {
        {0x0600, 34, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6CA8 = {
    {0x0100, 0x0000},
    {
        {0x0700, 34, 2, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D6CB4[81] = {
    (SaturnSpriteFrameHeader*)&DAT_060D68F0,
    (SaturnSpriteFrameHeader*)&DAT_060D68F4,
    (SaturnSpriteFrameHeader*)&DAT_060D6900,
    (SaturnSpriteFrameHeader*)&DAT_060D690C,
    (SaturnSpriteFrameHeader*)&DAT_060D6918,
    (SaturnSpriteFrameHeader*)&DAT_060D6924,
    (SaturnSpriteFrameHeader*)&DAT_060D6930,
    (SaturnSpriteFrameHeader*)&DAT_060D693C,
    (SaturnSpriteFrameHeader*)&DAT_060D6948,
    (SaturnSpriteFrameHeader*)&DAT_060D6954,
    (SaturnSpriteFrameHeader*)&DAT_060D6960,
    (SaturnSpriteFrameHeader*)&DAT_060D696C,
    (SaturnSpriteFrameHeader*)&DAT_060D6978,
    (SaturnSpriteFrameHeader*)&DAT_060D6984,
    (SaturnSpriteFrameHeader*)&DAT_060D6990,
    (SaturnSpriteFrameHeader*)&DAT_060D699C,
    (SaturnSpriteFrameHeader*)&DAT_060D69A8,
    (SaturnSpriteFrameHeader*)&DAT_060D69B4,
    (SaturnSpriteFrameHeader*)&DAT_060D69C0,
    (SaturnSpriteFrameHeader*)&DAT_060D69CC,
    (SaturnSpriteFrameHeader*)&DAT_060D69D8,
    (SaturnSpriteFrameHeader*)&DAT_060D69E4,
    (SaturnSpriteFrameHeader*)&DAT_060D69F0,
    (SaturnSpriteFrameHeader*)&DAT_060D69FC,
    (SaturnSpriteFrameHeader*)&DAT_060D6A08,
    (SaturnSpriteFrameHeader*)&DAT_060D6A14,
    (SaturnSpriteFrameHeader*)&DAT_060D6A20,
    (SaturnSpriteFrameHeader*)&DAT_060D6A2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A38,
    (SaturnSpriteFrameHeader*)&DAT_060D6A44,
    (SaturnSpriteFrameHeader*)&DAT_060D6A50,
    (SaturnSpriteFrameHeader*)&DAT_060D6A5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A68,
    (SaturnSpriteFrameHeader*)&DAT_060D6A74,
    (SaturnSpriteFrameHeader*)&DAT_060D6A80,
    (SaturnSpriteFrameHeader*)&DAT_060D6A8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A98,
    (SaturnSpriteFrameHeader*)&DAT_060D6AA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6AB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6ABC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6AE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6AEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6B04,
    (SaturnSpriteFrameHeader*)&DAT_060D6B10,
    (SaturnSpriteFrameHeader*)&DAT_060D6B1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B28,
    (SaturnSpriteFrameHeader*)&DAT_060D6B34,
    (SaturnSpriteFrameHeader*)&DAT_060D6B40,
    (SaturnSpriteFrameHeader*)&DAT_060D6B4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B58,
    (SaturnSpriteFrameHeader*)&DAT_060D6B64,
    (SaturnSpriteFrameHeader*)&DAT_060D6B70,
    (SaturnSpriteFrameHeader*)&DAT_060D6B7C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B88,
    (SaturnSpriteFrameHeader*)&DAT_060D6B94,
    (SaturnSpriteFrameHeader*)&DAT_060D6BA0,
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
};

struct {
    u16 countAndFlags;
    u16 colors[8][16];
    u16 padding[1];
} DAT_060D6DF8 = {
    0x0008,
    {
        {0x0000, 0x8000, 0x800F, 0x800F, 0x800F, 0x800F, 0x800F, 0x800F, 0x83E0,
         0x800F, 0x8CB4, 0x0000, 0x0000, 0x0000, 0xD294, 0xCF1C},
        {0x0000, 0x8000, 0x0000, 0x0000, 0x0000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8014, 0x940C, 0x83E0,
         0x8005, 0x844E, 0x807D, 0x0000, 0x0000, 0xD294, 0xE35C},
        {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA008, 0x0000, 0x83E0,
         0x0000, 0x8008, 0x0000, 0x806C, 0x0000, 0xD294, 0xBEBC},
        {0x0000, 0x8000, 0x800B, 0x9DC0, 0x800B, 0x800B, 0x800B, 0x800B, 0x83E0,
         0xB9C0, 0x800B, 0x0000, 0x0000, 0x0000, 0xD294, 0xAABC},
        {0x0000, 0x8000, 0x0000, 0x9DC0, 0x8011, 0x8011, 0x8011, 0x8011, 0x83E0,
         0xB9C0, 0x8011, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
        {0x0000, 0x8000, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x8008, 0x0000, 0x83E0,
         0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0x9E1C},
        {0x0000, 0x8000, 0x8900, 0x8900, 0x8900, 0x8900, 0x8902, 0x8904, 0x843F,
         0x9541, 0x95E1, 0x0000, 0x0000, 0x0000, 0xD294, 0xF2D1},
    },
    {0x0000},
};

SaturnSpriteResource DAT_060D6EFC = {
    DAT_060D68D4, (u16*)&DAT_060D6DF8, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6F08[1] = {&DAT_060D6EFC};
