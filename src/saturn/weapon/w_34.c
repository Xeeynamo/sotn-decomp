// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62C8();
void func_060D668C();
void func_060D66A4();
void func_060D66BC();
void func_060D66D4();
void func_060D66EC();
void func_060D66F8();
void func_060D6710();
void func_060D6728();
void func_060D6740();
void func_060D6758();
void func_060D6770();
void func_060D6788();
void func_060D67A0();
void func_060D67B8();
extern SaturnSpriteResource* DAT_060D6D0C[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62C8,
        func_060D668C,
        func_060D66A4,
        func_060D66BC,
        func_060D66D4,
        func_060D66EC,
        func_060D67B8,
        func_060D66F8,
        func_060D6710,
        func_060D6728,
        func_060D6740,
        func_060D6758,
        func_060D6770,
        func_060D6788,
        func_060D67A0,
    },
    DAT_060D6D0C,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D62C8, func_060D62C8);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D668C, func_060D668C);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D66A4, func_060D66A4);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D66BC, func_060D66BC);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D66D4, func_060D66D4);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D66EC, func_060D66EC);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D66F8, func_060D66F8);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D6710, func_060D6710);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D6728, func_060D6728);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D6740, func_060D6740);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D6758, func_060D6758);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D6770, func_060D6770);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D6788, func_060D6788);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D67A0, func_060D67A0);
INCLUDE_ASM("asm/saturn/weapon/w_34/f_nonmat", f60D67B8, func_060D67B8);

u16 DAT_060D67D0[13] = {0x0201, 0x0402, 0x0604, 0x0605, 0x0606, 0x0607, 0x0808,
                        0x0A09, 0x0A0A, 0x0A0B, 0x0A0C, 0x0A0D, 0xFFFF};

u16 DAT_060D67EA[13] = {0x0C0E, 0x0E0F, 0x1010, 0x1011, 0x1012, 0x1013, 0x1214,
                        0x0A15, 0x0A1D, 0x0A1E, 0x0A1F, 0x0A20, 0xFFFF};

u16 DAT_060D6804[13] = {0x0C0E, 0x1416, 0x1617, 0x1618, 0x1619, 0x161A, 0x181B,
                        0x0A1C, 0x0A1D, 0x0A1E, 0x0A1F, 0x0A20, 0xFFFF};

u16 DAT_060D681E[10] = {0x1A21, 0x1C22, 0x1E23, 0x1E24, 0x1E25,
                        0x1E26, 0x2027, 0x0A28, 0x0A29, 0xFFFF};

u16 DAT_060D6832[10] = {0x222A, 0x242B, 0x262C, 0x262D, 0x262E,
                        0x262F, 0x2830, 0x0A31, 0x0A39, 0xFFFF};

u16 DAT_060D6846[11] = {0x222A, 0x2A32, 0x2C33, 0x2C34, 0x2C35, 0x2C36,
                        0x2E37, 0x0A38, 0x0A39, 0xFFFF, 0x0000};

s8 DAT_060D685C[25][4] = {
    {0, 0, 0, 0},     {9, -24, 9, 4},   {34, -21, 33, 8}, {38, -14, 26, 6},
    {30, -9, 19, 4},  {-40, -31, 0, 0}, {-2, -8, 9, 4},   {22, -5, 33, 8},
    {28, 3, 27, 6},   {23, 5, 19, 4},   {9, 3, 20, 16},   {26, 20, 19, 11},
    {15, 17, 19, 5},  {4, -27, 11, 5},  {28, -24, 33, 8}, {31, -16, 29, 6},
    {29, -13, 24, 4}, {-5, -28, 10, 4}, {21, -22, 33, 8}, {30, -14, 26, 6},
    {21, -11, 21, 4}, {23, -3, 29, 21}, {25, 8, 29, 10},  {16, 5, 21, 7},
    {1, 1, 20, 16}};

u16* DAT_060D68C0[7] = {DAT_060D67D0, DAT_060D67D0, DAT_060D67EA, DAT_060D6804,
                        DAT_060D681E, DAT_060D6832, DAT_060D6846};

WeaponAnimation DAT_060D68DC[1] = {
    {(u16**)DAT_060D68C0, (s8*)DAT_060D685C, 0x0000, 0x060B, 0x8C, 0x04, 0},
};

SaturnSpriteImage DAT_060D68EC[18] = {
    {12, 6, 0x0000},  {36, 8, 0x0014},  {16, 6, 0x005C}, {16, 6, 0x0074},
    {16, 6, 0x008C},  {16, 6, 0x00A4},  {16, 6, 0x00BC}, {24, 4, 0x00D4},
    {8, 7, 0x00EC},   {28, 22, 0x00FC}, {12, 7, 0x0198}, {12, 7, 0x01B0},
    {12, 7, 0x01C8},  {12, 7, 0x01E0},  {20, 7, 0x01F8}, {8, 6, 0x021C},
    {20, 11, 0x0228}, {0, 0, 0x0260},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D6934 = {
    0x0001,
    {
        {0x8160, 0xFFFF, 0x98C6, 0xAD6B, 0xC210, 0xD6B5, 0xEB5A, 0xFFFF, 0xD1CE,
         0x9084, 0x90EB, 0x8173, 0x9218, 0x9EDF, 0xB9D4, 0xBA6E},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6958 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D695C = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6968 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6974 = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6980 = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D698C = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6998 = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D69A4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -13, 6},
    },
};

SaturnSpriteFrame1 DAT_060D69B0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D69BC = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -5, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69C8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, -3, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69D4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -3, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69E0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -3, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69EC = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, -3, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6A04 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, -4, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A10 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, 4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A1C = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, 4, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A28 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, 4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6A34 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6A40 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6A4C = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 12, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6A58 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 9, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6A64 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 23, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6A70 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 23, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6A7C = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 23, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6A88 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 23, 13},
    },
};

SaturnSpriteFrame1 DAT_060D6A94 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, 16, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6AA0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 15, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6AAC = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, 14, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6AB8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, 14, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6AC4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, 14, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6AD0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, 14, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6ADC = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -26, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6AE8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -23, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6AF4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6B00 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -15, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6B0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -15, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6B18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -15, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6B24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -13, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6B30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -4, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6B3C = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -2, 15},
    },
};

SaturnSpriteFrame1 DAT_060D6B48 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6B54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6B60 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6B6C = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6B78 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6B84 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B90 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, -10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6B9C = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, -5, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6BA8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -3, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6BB4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 11, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6BC0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 11, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6BCC = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 11, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6BD8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 11, 13},
    },
};

SaturnSpriteFrame1 DAT_060D6BE4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, 5, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6BF0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, -4, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6BFC = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, -3, 15},
    },
};

SaturnSpriteFrame1 DAT_060D6C08 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, -3, 16},
    },
};

SaturnSpriteFrameHeader* DAT_060D6C14[59] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6958,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6A64,
    (SaturnSpriteFrameHeader*)&DAT_060D6A70,
    (SaturnSpriteFrameHeader*)&DAT_060D6A7C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A88,
    (SaturnSpriteFrameHeader*)&DAT_060D6A94,
    (SaturnSpriteFrameHeader*)&DAT_060D6AA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6AAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6AD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6ADC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6B00,
    (SaturnSpriteFrameHeader*)&DAT_060D6B0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B18,
    (SaturnSpriteFrameHeader*)&DAT_060D6B24,
    (SaturnSpriteFrameHeader*)&DAT_060D6B30,
    (SaturnSpriteFrameHeader*)&DAT_060D6B3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B48,
    (SaturnSpriteFrameHeader*)&DAT_060D6B54,
    (SaturnSpriteFrameHeader*)&DAT_060D6B60,
    (SaturnSpriteFrameHeader*)&DAT_060D6B6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B78,
    (SaturnSpriteFrameHeader*)&DAT_060D6B84,
    (SaturnSpriteFrameHeader*)&DAT_060D6B90,
    (SaturnSpriteFrameHeader*)&DAT_060D6B9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6BA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BCC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BD8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6C08,
};

SaturnSpriteResource DAT_060D6D00 = {
    DAT_060D68EC, (u16*)&DAT_060D6934, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6D0C[1] = {&DAT_060D6D00};
