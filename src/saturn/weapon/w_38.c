// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62F0();
void func_060D65F0();
void func_060D6608();
void func_060D6620();
void func_060D6638();
void func_060D6650();
void func_060D665C();
void func_060D6674();
void func_060D668C();
void func_060D66A4();
void func_060D66BC();
void func_060D66D4();
void func_060D66EC();
void func_060D6704();
void func_060D671C();
extern SaturnSpriteResource* DAT_060D6E98[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62F0,
        func_060D65F0,
        func_060D6608,
        func_060D6620,
        func_060D6638,
        func_060D6650,
        func_060D671C,
        func_060D665C,
        func_060D6674,
        func_060D668C,
        func_060D66A4,
        func_060D66BC,
        func_060D66D4,
        func_060D66EC,
        func_060D6704,
    },
    DAT_060D6E98,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D62F0, func_060D62F0);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D65F0, func_060D65F0);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D6608, func_060D6608);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D6620, func_060D6620);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D6638, func_060D6638);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D6650, func_060D6650);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D665C, func_060D665C);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D6674, func_060D6674);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D668C, func_060D668C);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D66A4, func_060D66A4);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D66BC, func_060D66BC);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D66D4, func_060D66D4);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D66EC, func_060D66EC);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D6704, func_060D6704);
INCLUDE_ASM("asm/saturn/weapon/w_38/f_nonmat", f60D671C, func_060D671C);

u16 DAT_060D6730[16] = {
    0x0201, 0x0402, 0x0403, 0x0404, 0x0605, 0x0806, 0x0807, 0x0808,
    0x0809, 0x020A, 0x020B, 0x020C, 0x020D, 0x020E, 0x020F, 0xFFFF};

u16 DAT_060D6750[16] = {
    0x0210, 0x0A11, 0x0A12, 0x0A13, 0x0C14, 0x0E15, 0x0E16, 0x0E17,
    0x0E18, 0x0219, 0x021A, 0x0225, 0x0226, 0x0227, 0x0228, 0xFFFF};

u16 DAT_060D6770[16] = {
    0x0210, 0x0A1B, 0x0A1C, 0x0A1D, 0x101E, 0x121F, 0x1220, 0x1221,
    0x1222, 0x0223, 0x0224, 0x0225, 0x0226, 0x0227, 0x0228, 0xFFFF};

u16 DAT_060D6790[13] = {0x0229, 0x142A, 0x142B, 0x142C, 0x162D, 0x182E, 0x182F,
                        0x1830, 0x1831, 0x0232, 0x0233, 0x0234, 0xFFFF};

u16 DAT_060D67AA[13] = {0x0235, 0x1A36, 0x1A37, 0x1A38, 0x1C39, 0x1E3A, 0x1E3B,
                        0x1E3C, 0x1E3D, 0x023E, 0x023F, 0x0247, 0xFFFF};

u16 DAT_060D67C4[14] = {0x0235, 0x1A36, 0x1A37, 0x1A38, 0x2040, 0x2241, 0x2242,
                        0x2243, 0x2244, 0x0245, 0x0246, 0x0247, 0xFFFF, 0x0000};

s8 DAT_060D67E0[18][4] = {
    {0, 0, 0, 0},     {-40, -31, 0, 0}, {4, -24, 6, 4},   {20, -14, 40, 3},
    {33, -14, 29, 2}, {-6, -5, 6, 4},   {11, 3, 41, 3},   {25, 3, 28, 2},
    {6, 9, 16, 10},   {20, 19, 23, 8},  {-4, -21, 8, 7},  {18, -16, 40, 3},
    {31, -16, 28, 3}, {-11, -23, 6, 8}, {20, -15, 34, 4}, {29, -14, 25, 3},
    {23, 1, 29, 10},  {30, 4, 23, 10}};

u16* DAT_060D6828[7] = {DAT_060D6730, DAT_060D6730, DAT_060D6750, DAT_060D6770,
                        DAT_060D6790, DAT_060D67AA, DAT_060D67C4};

WeaponAnimation DAT_060D6844[2] = {
    {(u16**)DAT_060D6828, (s8*)DAT_060D67E0, 0x0000, 0x060B, 0xA8, 0x04, 0},
    {(u16**)DAT_060D6828, (s8*)DAT_060D67E0, 0x0000, 0x060B, 0xA8, 0x04, 0},
};

SaturnSpriteImage DAT_060D6864[27] = {
    {8, 4, 0x0000},   {8, 3, 0x0008},   {16, 6, 0x0010}, {16, 7, 0x0028},
    {44, 7, 0x0044},  {44, 1, 0x0094},  {12, 3, 0x00A0}, {32, 1, 0x00AC},
    {8, 1, 0x00B4},   {4, 1, 0x00B8},   {20, 2, 0x00BC}, {4, 1, 0x00C8},
    {8, 2, 0x00CC},   {8, 4, 0x00D0},   {8, 4, 0x00D8},  {8, 7, 0x00E0},
    {32, 18, 0x00F0}, {28, 14, 0x0180}, {20, 9, 0x01E4}, {12, 6, 0x0214},
    {12, 6, 0x0228},  {20, 5, 0x023C},  {16, 6, 0x0258}, {28, 1, 0x0270},
    {12, 9, 0x0278},  {24, 13, 0x0294}, {0, 0, 0x02E4},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D68D0 = {
    0x0001,
    {
        {0x80C0, 0x8421, 0x98C6, 0xAD6B, 0xC210, 0xDEB4, 0xEF37, 0xFFFF, 0xA173,
         0xAE18, 0xC33C, 0xA5A0, 0x9A20, 0x8EA0, 0x8340, 0x83E0},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D68F4 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D68F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -22, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6904 = {
    {0x0200, 0x0000},
    {
        {0x0000, 7, -22, 0},
        {0x0004, 7, -23, 1},
    },
};

SaturnSpriteFrame2 DAT_060D6918 = {
    {0x0200, 0x0000},
    {
        {0x0000, 7, -22, 0},
        {0x0004, 0, -20, 2},
    },
};

SaturnSpriteFrame2 DAT_060D692C = {
    {0x0200, 0x0000},
    {
        {0x0000, 7, -22, 0},
        {0x0004, -2, -19, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6940 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -19, 4},
    },
};

SaturnSpriteFrame1 DAT_060D694C = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -13, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6958 = {
    {0x0200, 0x0000},
    {
        {0x0000, 50, -13, 6},
        {0x0004, 35, -13, 7},
    },
};

SaturnSpriteFrame2 DAT_060D696C = {
    {0x0200, 0x0000},
    {
        {0x0000, 50, -13, 6},
        {0x0004, 58, -13, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6980 = {
    {0x0200, 0x0000},
    {
        {0x0000, 50, -13, 6},
        {0x0000, 58, -13, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6994 = {
    {0x0200, 0x0000},
    {
        {0x0000, 21, -12, 10},
        {0x0000, 58, -13, 11},
    },
};

SaturnSpriteFrame1 DAT_060D69A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -8, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -7, 12},
    },
};

SaturnSpriteFrame1 DAT_060D69CC = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -7, 12},
    },
};

SaturnSpriteFrame1 DAT_060D69D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -7, 12},
    },
};

SaturnSpriteFrame1 DAT_060D69E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -5, 0},
    },
};

SaturnSpriteFrame2 DAT_060D69F0 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -5, 0},
        {0x0004, -2, -6, 1},
    },
};

SaturnSpriteFrame2 DAT_060D6A04 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -5, 0},
        {0x0004, -11, -2, 2},
    },
};

SaturnSpriteFrame2 DAT_060D6A18 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -5, 0},
        {0x0004, -11, -2, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A2C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -2, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6A38 = {
    {0x0200, 0x0000},
    {
        {0x0000, 43, 4, 6},
        {0x0004, 18, 4, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6A4C = {
    {0x0200, 0x0000},
    {
        {0x0000, 43, 4, 6},
        {0x0004, 28, 4, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6A60 = {
    {0x0200, 0x0000},
    {
        {0x0000, 43, 4, 6},
        {0x0000, 51, 4, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6A74 = {
    {0x0200, 0x0000},
    {
        {0x0000, 43, 4, 6},
        {0x0000, 51, 4, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6A88 = {
    {0x0200, 0x0000},
    {
        {0x0000, 17, 6, 10},
        {0x0000, 56, 4, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6A9C = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, 9, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6AA8 = {
    {0x0200, 0x0000},
    {
        {0x0000, -4, -5, 0},
        {0x0000, -4, -5, 13},
    },
};

SaturnSpriteFrame2 DAT_060D6ABC = {
    {0x0200, 0x0000},
    {
        {0x0000, -4, -5, 0},
        {0x0000, -5, -5, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6AD0 = {
    {0x0100, 0x0000},
    {
        {0x0004, -5, -2, 15},
    },
};

SaturnSpriteFrame1 DAT_060D6ADC = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 9, 16},
    },
};

SaturnSpriteFrame1 DAT_060D6AE8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, 14, 17},
    },
};

SaturnSpriteFrame1 DAT_060D6AF4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 30, 18, 18},
    },
};

SaturnSpriteFrame1 DAT_060D6B00 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, 21, 19},
    },
};

SaturnSpriteFrame1 DAT_060D6B0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, 21, 20},
    },
};

SaturnSpriteFrame2 DAT_060D6B18 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, 18, 21},
        {0x0000, 46, 27, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6B2C = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, 10, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6B38 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, 10, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6B44 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, 10, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6B50 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, 10, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6B5C = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 10, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6B68 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -23, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6B74 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -23, 0},
        {0x0000, 4, -24, 1},
    },
};

SaturnSpriteFrame2 DAT_060D6B88 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -23, 0},
        {0x0004, -3, -21, 2},
    },
};

SaturnSpriteFrame2 DAT_060D6B9C = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -23, 0},
        {0x0004, -3, -21, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BB0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -21, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6BBC = {
    {0x0200, 0x0000},
    {
        {0x0000, 51, -15, 6},
        {0x0004, 25, -15, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6BD0 = {
    {0x0200, 0x0000},
    {
        {0x0000, 51, -15, 6},
        {0x0004, 34, -15, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6BE4 = {
    {0x0200, 0x0000},
    {
        {0x0000, 51, -15, 6},
        {0x0000, 60, -15, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6BF8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 51, -15, 6},
        {0x0000, 59, -15, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6C0C = {
    {0x0200, 0x0000},
    {
        {0x0000, 24, -13, 10},
        {0x0000, 63, -15, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6C20 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -9, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C2C = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, -6, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6C38 = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, -25, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6C44 = {
    {0x0200, 0x0000},
    {
        {0x0000, -6, -25, 0},
        {0x0000, -6, -25, 13},
    },
};

SaturnSpriteFrame2 DAT_060D6C58 = {
    {0x0200, 0x0000},
    {
        {0x0000, -6, -25, 0},
        {0x0000, -7, -25, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6C6C = {
    {0x0100, 0x0000},
    {
        {0x0004, -7, -22, 15},
    },
};

SaturnSpriteFrame2 DAT_060D6C78 = {
    {0x0200, 0x0000},
    {
        {0x0014, -13, -17, 22},
        {0x0014, 23, -13, 23},
    },
};

SaturnSpriteFrame2 DAT_060D6C8C = {
    {0x0200, 0x0000},
    {
        {0x0000, 41, -13, 6},
        {0x0004, 26, -13, 23},
    },
};

SaturnSpriteFrame2 DAT_060D6CA0 = {
    {0x0200, 0x0000},
    {
        {0x0000, 41, -13, 6},
        {0x0004, 25, -13, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6CB4 = {
    {0x0200, 0x0000},
    {
        {0x0000, 41, -13, 6},
        {0x0000, 49, -13, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6CC8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 41, -13, 6},
        {0x0000, 49, -13, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6CDC = {
    {0x0200, 0x0000},
    {
        {0x0000, 19, -11, 10},
        {0x0000, 53, -13, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6CF0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -7, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6CFC = {
    {0x0200, 0x0000},
    {
        {0x0004, -2, -18, 24},
        {0x0004, 32, 4, 25},
    },
};

SaturnSpriteFrame1 DAT_060D6D10 = {
    {0x0100, 0x0000},
    {
        {0x0004, 32, 3, 17},
    },
};

SaturnSpriteFrame1 DAT_060D6D1C = {
    {0x0100, 0x0000},
    {
        {0x0004, 40, 7, 18},
    },
};

SaturnSpriteFrame1 DAT_060D6D28 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 10, 19},
    },
};

SaturnSpriteFrame1 DAT_060D6D34 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 10, 20},
    },
};

SaturnSpriteFrame2 DAT_060D6D40 = {
    {0x0200, 0x0000},
    {
        {0x0000, 22, 5, 21},
        {0x0000, 53, 15, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6D54 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -5, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6D60 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 12},
    },
};

SaturnSpriteFrameHeader* DAT_060D6D6C[72] = {
    (SaturnSpriteFrameHeader*)&DAT_060D68F4,
    (SaturnSpriteFrameHeader*)&DAT_060D68F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6904,
    (SaturnSpriteFrameHeader*)&DAT_060D6918,
    (SaturnSpriteFrameHeader*)&DAT_060D692C,
    (SaturnSpriteFrameHeader*)&DAT_060D6940,
    (SaturnSpriteFrameHeader*)&DAT_060D694C,
    (SaturnSpriteFrameHeader*)&DAT_060D6958,
    (SaturnSpriteFrameHeader*)&DAT_060D696C,
    (SaturnSpriteFrameHeader*)&DAT_060D6980,
    (SaturnSpriteFrameHeader*)&DAT_060D6994,
    (SaturnSpriteFrameHeader*)&DAT_060D69A8,
    (SaturnSpriteFrameHeader*)&DAT_060D69B4,
    (SaturnSpriteFrameHeader*)&DAT_060D69C0,
    (SaturnSpriteFrameHeader*)&DAT_060D69CC,
    (SaturnSpriteFrameHeader*)&DAT_060D69D8,
    (SaturnSpriteFrameHeader*)&DAT_060D69E4,
    (SaturnSpriteFrameHeader*)&DAT_060D69F0,
    (SaturnSpriteFrameHeader*)&DAT_060D6A04,
    (SaturnSpriteFrameHeader*)&DAT_060D6A18,
    (SaturnSpriteFrameHeader*)&DAT_060D6A2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A38,
    (SaturnSpriteFrameHeader*)&DAT_060D6A4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A60,
    (SaturnSpriteFrameHeader*)&DAT_060D6A74,
    (SaturnSpriteFrameHeader*)&DAT_060D6A88,
    (SaturnSpriteFrameHeader*)&DAT_060D6A9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6AA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6ABC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6ADC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6B00,
    (SaturnSpriteFrameHeader*)&DAT_060D6B0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B18,
    (SaturnSpriteFrameHeader*)&DAT_060D6B2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B38,
    (SaturnSpriteFrameHeader*)&DAT_060D6B44,
    (SaturnSpriteFrameHeader*)&DAT_060D6B50,
    (SaturnSpriteFrameHeader*)&DAT_060D6B5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B68,
    (SaturnSpriteFrameHeader*)&DAT_060D6B74,
    (SaturnSpriteFrameHeader*)&DAT_060D6B88,
    (SaturnSpriteFrameHeader*)&DAT_060D6B9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6BB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6C0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C20,
    (SaturnSpriteFrameHeader*)&DAT_060D6C2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C38,
    (SaturnSpriteFrameHeader*)&DAT_060D6C44,
    (SaturnSpriteFrameHeader*)&DAT_060D6C58,
    (SaturnSpriteFrameHeader*)&DAT_060D6C6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C78,
    (SaturnSpriteFrameHeader*)&DAT_060D6C8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6CA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6CDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6D10,
    (SaturnSpriteFrameHeader*)&DAT_060D6D1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D28,
    (SaturnSpriteFrameHeader*)&DAT_060D6D34,
    (SaturnSpriteFrameHeader*)&DAT_060D6D40,
    (SaturnSpriteFrameHeader*)&DAT_060D6D54,
    (SaturnSpriteFrameHeader*)&DAT_060D6D60,
};

SaturnSpriteResource DAT_060D6E8C = {
    DAT_060D6864, (u16*)&DAT_060D68D0, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6E98[1] = {&DAT_060D6E8C};
