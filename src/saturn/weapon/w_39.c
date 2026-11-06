// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62F0();
void func_060D66F0();
void func_060D6708();
void func_060D6720();
void func_060D6738();
void func_060D6750();
void func_060D675C();
void func_060D6774();
void func_060D678C();
void func_060D67A4();
void func_060D67BC();
void func_060D67D4();
void func_060D67EC();
void func_060D6804();
void func_060D681C();
extern SaturnSpriteResource* DAT_060D6F98[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62F0,
        func_060D66F0,
        func_060D6708,
        func_060D6720,
        func_060D6738,
        func_060D6750,
        func_060D681C,
        func_060D675C,
        func_060D6774,
        func_060D678C,
        func_060D67A4,
        func_060D67BC,
        func_060D67D4,
        func_060D67EC,
        func_060D6804,
    },
    DAT_060D6F98,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D62F0, func_060D62F0);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D66F0, func_060D66F0);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D6708, func_060D6708);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D6720, func_060D6720);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D6738, func_060D6738);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D6750, func_060D6750);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D675C, func_060D675C);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D6774, func_060D6774);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D678C, func_060D678C);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D67A4, func_060D67A4);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D67BC, func_060D67BC);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D67D4, func_060D67D4);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D67EC, func_060D67EC);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D6804, func_060D6804);
INCLUDE_ASM("asm/saturn/weapon/w_39/f_nonmat", f60D681C, func_060D681C);

u16 DAT_060D6830[16] = {
    0x0201, 0x0402, 0x0403, 0x0404, 0x0605, 0x0806, 0x0807, 0x0808,
    0x0809, 0x020A, 0x020B, 0x020C, 0x020D, 0x020E, 0x020F, 0xFFFF};

u16 DAT_060D6850[16] = {
    0x0210, 0x0A11, 0x0A12, 0x0A13, 0x0C14, 0x0E15, 0x0E16, 0x0E17,
    0x0E18, 0x0219, 0x021A, 0x0225, 0x0226, 0x0227, 0x0228, 0xFFFF};

u16 DAT_060D6870[16] = {
    0x0210, 0x0A1B, 0x0A1C, 0x0A1D, 0x101E, 0x121F, 0x1220, 0x1221,
    0x1222, 0x0223, 0x0224, 0x0225, 0x0226, 0x0227, 0x0228, 0xFFFF};

u16 DAT_060D6890[13] = {0x0229, 0x142A, 0x142B, 0x142C, 0x162D, 0x182E, 0x182F,
                        0x1830, 0x1831, 0x0232, 0x0233, 0x0234, 0xFFFF};

u16 DAT_060D68AA[13] = {0x0235, 0x1A36, 0x1A37, 0x1A38, 0x1C39, 0x1E3A, 0x1E3B,
                        0x1E3C, 0x1E3D, 0x023E, 0x023F, 0x0247, 0xFFFF};

u16 DAT_060D68C4[14] = {0x0235, 0x1A36, 0x1A37, 0x1A38, 0x2040, 0x2241, 0x2242,
                        0x2243, 0x2244, 0x0245, 0x0246, 0x0247, 0xFFFF, 0x0000};

s8 DAT_060D68E0[18][4] = {
    {0, 0, 0, 0},     {-40, -31, 0, 0}, {4, -24, 6, 4},   {20, -14, 40, 3},
    {33, -14, 29, 2}, {-6, -5, 6, 4},   {11, 3, 41, 3},   {25, 3, 28, 2},
    {6, 9, 16, 10},   {20, 19, 23, 8},  {-4, -21, 8, 7},  {18, -16, 40, 3},
    {31, -16, 28, 3}, {-11, -23, 6, 8}, {20, -15, 34, 4}, {29, -14, 25, 3},
    {23, 1, 29, 10},  {30, 4, 23, 10}};

u16* DAT_060D6928[7] = {DAT_060D6830, DAT_060D6830, DAT_060D6850, DAT_060D6870,
                        DAT_060D6890, DAT_060D68AA, DAT_060D68C4};

WeaponAnimation DAT_060D6944[2] = {
    {(u16**)DAT_060D6928, (s8*)DAT_060D68E0, 0x0000, 0x060B, 0xA8, 0x04, 0},
    {(u16**)DAT_060D6928, (s8*)DAT_060D68E0, 0x0000, 0x060B, 0xA8, 0x04, 0},
};

SaturnSpriteImage DAT_060D6964[27] = {
    {8, 4, 0x0000},   {8, 4, 0x0008},   {16, 7, 0x0010},  {16, 7, 0x002C},
    {44, 7, 0x0048},  {44, 2, 0x0098},  {12, 3, 0x00B0},  {32, 2, 0x00BC},
    {8, 1, 0x00CC},   {4, 1, 0x00D0},   {20, 2, 0x00D4},  {4, 1, 0x00E0},
    {8, 2, 0x00E4},   {8, 4, 0x00E8},   {8, 4, 0x00F0},   {8, 8, 0x00F8},
    {32, 19, 0x0108}, {28, 15, 0x01A0}, {20, 10, 0x020C}, {12, 7, 0x0240},
    {12, 7, 0x0258},  {20, 5, 0x0270},  {12, 5, 0x028C},  {28, 2, 0x029C},
    {12, 10, 0x02AC}, {28, 15, 0x02CC}, {0, 0, 0x0338},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D69D0 = {
    0x0001,
    {
        {0x80C0, 0x8421, 0x98C6, 0xAD6B, 0xC210, 0xD6B5, 0xE739, 0xFFFF, 0xA173,
         0xAE18, 0xC33C, 0xF0E5, 0xED0A, 0xED2F, 0xE954, 0xE99A},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D69F4 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D69F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -22, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6A04 = {
    {0x0200, 0x0000},
    {
        {0x0000, 7, -22, 0},
        {0x0004, 7, -22, 1},
    },
};

SaturnSpriteFrame2 DAT_060D6A18 = {
    {0x0200, 0x0000},
    {
        {0x0000, 7, -22, 0},
        {0x0004, 0, -19, 2},
    },
};

SaturnSpriteFrame2 DAT_060D6A2C = {
    {0x0200, 0x0000},
    {
        {0x0000, 7, -22, 0},
        {0x0004, -2, -19, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A40 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -19, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A4C = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -13, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6A58 = {
    {0x0200, 0x0000},
    {
        {0x0000, 50, -13, 6},
        {0x0004, 35, -13, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6A6C = {
    {0x0200, 0x0000},
    {
        {0x0000, 50, -13, 6},
        {0x0004, 58, -13, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6A80 = {
    {0x0200, 0x0000},
    {
        {0x0000, 50, -13, 6},
        {0x0000, 58, -13, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6A94 = {
    {0x0200, 0x0000},
    {
        {0x0000, 21, -12, 10},
        {0x0000, 58, -13, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6AA8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -8, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6AB4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6AC0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -7, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6ACC = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -7, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6AD8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -7, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6AE4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -5, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6AF0 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -5, 0},
        {0x0004, -2, -5, 1},
    },
};

SaturnSpriteFrame2 DAT_060D6B04 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -5, 0},
        {0x0004, -11, -1, 2},
    },
};

SaturnSpriteFrame2 DAT_060D6B18 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -5, 0},
        {0x0004, -11, -2, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6B2C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -2, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6B38 = {
    {0x0200, 0x0000},
    {
        {0x0000, 43, 4, 6},
        {0x0004, 18, 4, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6B4C = {
    {0x0200, 0x0000},
    {
        {0x0000, 43, 4, 6},
        {0x0004, 28, 4, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6B60 = {
    {0x0200, 0x0000},
    {
        {0x0000, 43, 4, 6},
        {0x0000, 51, 4, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6B74 = {
    {0x0200, 0x0000},
    {
        {0x0000, 43, 4, 6},
        {0x0000, 51, 4, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6B88 = {
    {0x0200, 0x0000},
    {
        {0x0000, 17, 6, 10},
        {0x0000, 56, 4, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6B9C = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, 9, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6BA8 = {
    {0x0200, 0x0000},
    {
        {0x0000, -4, -5, 0},
        {0x0000, -4, -5, 13},
    },
};

SaturnSpriteFrame2 DAT_060D6BBC = {
    {0x0200, 0x0000},
    {
        {0x0000, -4, -5, 0},
        {0x0000, -5, -5, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6BD0 = {
    {0x0100, 0x0000},
    {
        {0x0004, -5, -1, 15},
    },
};

SaturnSpriteFrame1 DAT_060D6BDC = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 10, 16},
    },
};

SaturnSpriteFrame1 DAT_060D6BE8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, 13, 17},
    },
};

SaturnSpriteFrame1 DAT_060D6BF4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 30, 19, 18},
    },
};

SaturnSpriteFrame1 DAT_060D6C00 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, 22, 19},
    },
};

SaturnSpriteFrame1 DAT_060D6C0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, 22, 20},
    },
};

SaturnSpriteFrame2 DAT_060D6C18 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, 18, 21},
        {0x0000, 46, 27, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6C2C = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, 10, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C38 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, 10, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C44 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, 10, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6C50 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, 10, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6C5C = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 10, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6C68 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -23, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6C74 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -23, 0},
        {0x0000, 4, -23, 1},
    },
};

SaturnSpriteFrame2 DAT_060D6C88 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -23, 0},
        {0x0004, -3, -20, 2},
    },
};

SaturnSpriteFrame2 DAT_060D6C9C = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -23, 0},
        {0x000B, -3, -21, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CB0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -21, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6CBC = {
    {0x0200, 0x0000},
    {
        {0x0000, 51, -15, 6},
        {0x0004, 25, -15, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6CD0 = {
    {0x0200, 0x0000},
    {
        {0x0000, 51, -15, 6},
        {0x0004, 34, -15, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6CE4 = {
    {0x0200, 0x0000},
    {
        {0x0000, 51, -15, 6},
        {0x0000, 60, -15, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6CF8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 51, -15, 6},
        {0x0000, 59, -15, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6D0C = {
    {0x0200, 0x0000},
    {
        {0x0000, 24, -13, 10},
        {0x0000, 63, -15, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6D20 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -9, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6D2C = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, -6, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6D38 = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, -25, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6D44 = {
    {0x0200, 0x0000},
    {
        {0x0000, -6, -25, 0},
        {0x0000, -6, -25, 13},
    },
};

SaturnSpriteFrame2 DAT_060D6D58 = {
    {0x0200, 0x0000},
    {
        {0x0000, -6, -25, 0},
        {0x0000, -7, -25, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6D6C = {
    {0x0100, 0x0000},
    {
        {0x0004, -7, -21, 15},
    },
};

SaturnSpriteFrame2 DAT_060D6D78 = {
    {0x0200, 0x0000},
    {
        {0x0014, -9, -17, 22},
        {0x0014, 23, -13, 23},
    },
};

SaturnSpriteFrame2 DAT_060D6D8C = {
    {0x0200, 0x0000},
    {
        {0x0000, 41, -13, 6},
        {0x0004, 26, -13, 23},
    },
};

SaturnSpriteFrame2 DAT_060D6DA0 = {
    {0x0200, 0x0000},
    {
        {0x0000, 41, -13, 6},
        {0x0004, 25, -13, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6DB4 = {
    {0x0200, 0x0000},
    {
        {0x0000, 41, -13, 6},
        {0x0000, 49, -13, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6DC8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 41, -13, 6},
        {0x0000, 49, -13, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6DDC = {
    {0x0200, 0x0000},
    {
        {0x0000, 19, -11, 10},
        {0x0000, 53, -13, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6DF0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -7, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6DFC = {
    {0x0200, 0x0000},
    {
        {0x0004, -2, -17, 24},
        {0x0004, 36, 4, 25},
    },
};

SaturnSpriteFrame1 DAT_060D6E10 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 2, 17},
    },
};

SaturnSpriteFrame1 DAT_060D6E1C = {
    {0x0100, 0x0000},
    {
        {0x0004, 40, 8, 18},
    },
};

SaturnSpriteFrame1 DAT_060D6E28 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 11, 19},
    },
};

SaturnSpriteFrame1 DAT_060D6E34 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 11, 20},
    },
};

SaturnSpriteFrame2 DAT_060D6E40 = {
    {0x0200, 0x0000},
    {
        {0x0000, 22, 5, 21},
        {0x0000, 53, 15, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6E54 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -5, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6E60 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 12},
    },
};

SaturnSpriteFrameHeader* DAT_060D6E6C[72] = {
    (SaturnSpriteFrameHeader*)&DAT_060D69F4,
    (SaturnSpriteFrameHeader*)&DAT_060D69F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6A04,
    (SaturnSpriteFrameHeader*)&DAT_060D6A18,
    (SaturnSpriteFrameHeader*)&DAT_060D6A2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A40,
    (SaturnSpriteFrameHeader*)&DAT_060D6A4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A58,
    (SaturnSpriteFrameHeader*)&DAT_060D6A6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A80,
    (SaturnSpriteFrameHeader*)&DAT_060D6A94,
    (SaturnSpriteFrameHeader*)&DAT_060D6AA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6AC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6ACC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AD8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6AF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6B04,
    (SaturnSpriteFrameHeader*)&DAT_060D6B18,
    (SaturnSpriteFrameHeader*)&DAT_060D6B2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B38,
    (SaturnSpriteFrameHeader*)&DAT_060D6B4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B60,
    (SaturnSpriteFrameHeader*)&DAT_060D6B74,
    (SaturnSpriteFrameHeader*)&DAT_060D6B88,
    (SaturnSpriteFrameHeader*)&DAT_060D6B9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6BA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6C00,
    (SaturnSpriteFrameHeader*)&DAT_060D6C0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C18,
    (SaturnSpriteFrameHeader*)&DAT_060D6C2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C38,
    (SaturnSpriteFrameHeader*)&DAT_060D6C44,
    (SaturnSpriteFrameHeader*)&DAT_060D6C50,
    (SaturnSpriteFrameHeader*)&DAT_060D6C5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C68,
    (SaturnSpriteFrameHeader*)&DAT_060D6C74,
    (SaturnSpriteFrameHeader*)&DAT_060D6C88,
    (SaturnSpriteFrameHeader*)&DAT_060D6C9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6CB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6D0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D20,
    (SaturnSpriteFrameHeader*)&DAT_060D6D2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D38,
    (SaturnSpriteFrameHeader*)&DAT_060D6D44,
    (SaturnSpriteFrameHeader*)&DAT_060D6D58,
    (SaturnSpriteFrameHeader*)&DAT_060D6D6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D78,
    (SaturnSpriteFrameHeader*)&DAT_060D6D8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6DA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6E10,
    (SaturnSpriteFrameHeader*)&DAT_060D6E1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E28,
    (SaturnSpriteFrameHeader*)&DAT_060D6E34,
    (SaturnSpriteFrameHeader*)&DAT_060D6E40,
    (SaturnSpriteFrameHeader*)&DAT_060D6E54,
    (SaturnSpriteFrameHeader*)&DAT_060D6E60,
};

SaturnSpriteResource DAT_060D6F8C = {
    DAT_060D6964, (u16*)&DAT_060D69D0, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6F98[1] = {&DAT_060D6F8C};
