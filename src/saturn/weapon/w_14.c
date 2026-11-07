// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D69D4();
void func_060D6BB8();
void func_060D6BD0();
void func_060D6BE8();
void func_060D6C00();
void func_060D6C18();
void func_060D6C24();
void func_060D6C3C();
void func_060D6C54();
void func_060D6C6C();
void func_060D6C84();
void func_060D6C9C();
void func_060D6CB4();
void func_060D6CCC();
void func_060D6CE4();
extern SaturnSpriteResource* DAT_060D6FB8[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D69D4,
        func_060D6BB8,
        func_060D6BD0,
        func_060D6BE8,
        func_060D6C00,
        func_060D6C18,
        func_060D6CE4,
        func_060D6C24,
        func_060D6C3C,
        func_060D6C54,
        func_060D6C6C,
        func_060D6C84,
        func_060D6C9C,
        func_060D6CB4,
        func_060D6CCC,
    },
    DAT_060D6FB8,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D69D4, func_060D69D4);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6BB8, func_060D6BB8);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6BD0, func_060D6BD0);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6BE8, func_060D6BE8);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6C00, func_060D6C00);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6C18, func_060D6C18);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6C24, func_060D6C24);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6C3C, func_060D6C3C);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6C54, func_060D6C54);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6C6C, func_060D6C6C);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6C84, func_060D6C84);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6C9C, func_060D6C9C);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6CB4, func_060D6CB4);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6CCC, func_060D6CCC);
INCLUDE_ASM("asm/saturn/weapon/w_14/f_nonmat", f60D6CE4, func_060D6CE4);

SaturnSpriteImage DAT_060D6CF0[18] = {
    {40, 31, 0x0000}, {12, 7, 0x0138}, {12, 7, 0x0150}, {12, 4, 0x0168},
    {28, 5, 0x0174},  {32, 6, 0x0198}, {4, 3, 0x01C8},  {12, 7, 0x01CC},
    {12, 6, 0x01E4},  {12, 5, 0x01F8}, {8, 8, 0x0208},  {8, 11, 0x0218},
    {40, 2, 0x0230},  {36, 7, 0x0244}, {12, 7, 0x0284}, {32, 43, 0x029C},
    {32, 36, 0x03F4}, {0, 0, 0x0514},
};

struct {
    u16 countAndFlags;
    u16 colors[8][16];
    u16 padding[1];
} DAT_060D6D38 = {
    0x0008,
    {
        {0x8942, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xE670,
         0xDDEE, 0xD58C, 0xC54A, 0xB508, 0xA8C6, 0x9884, 0x8C42},
        {0xB804, 0xB844, 0xB884, 0xB8C4, 0xB904, 0xB944, 0xB984, 0xB9C4, 0xBA04,
         0xBA44, 0xBA84, 0xBAC4, 0xBB04, 0xBB44, 0xBB84, 0xBBC4},
        {0xA582, 0x8821, 0x9484, 0x84C6, 0x814C, 0x9E36, 0x9EDB, 0x8C8D, 0xA174,
         0xAC85, 0xC0CC, 0xC96E, 0xD610, 0xDA93, 0xDF37, 0xEF59},
        {0x8180, 0x8421, 0x8C60, 0x88A7, 0x890B, 0x9DF4, 0xCAF9, 0xD100, 0xE9E6,
         0xA316, 0x9884, 0xAD27, 0xBDAC, 0xD251, 0xDEB4, 0xEF38},
        {0x8125, 0x9444, 0xC255, 0xA94B, 0xA5AD, 0x9189, 0xA316, 0xA087, 0xB509,
         0xBDAC, 0x9CE7, 0xB18C, 0xC631, 0xD6B5, 0xEB5A, 0xFFFF},
        {0x9181, 0x8C25, 0x9C68, 0xA0CD, 0xAD30, 0xAD93, 0xADF6, 0xC699, 0xE800,
         0x8000, 0xA507, 0xB149, 0xBDAC, 0xCA0F, 0xD672, 0xE2D5},
        {0xA5E2, 0x8821, 0xB5AD, 0xD6B5, 0x8148, 0x9E31, 0x801F, 0xA08C, 0xC192,
         0xA4A7, 0xB0C7, 0xBD28, 0xC98A, 0xD1CC, 0xDA4D, 0xE2D0},
        {0x8180, 0x8000, 0x8820, 0x9041, 0x9C81, 0xA4A2, 0xB0E2, 0xB903, 0xC544,
         0xC986, 0xCDC9, 0xD60C, 0xDA4F, 0xE292, 0xE6D5, 0xEF38},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6E3C = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6E40 = {
    {0x0100, 0x0000},
    {
        {0x0000, 52, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E4C = {
    {0x0100, 0x0000},
    {
        {0x0000, 52, 16, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E58 = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 0, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E64 = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 0, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E70 = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E7C = {
    {0x0100, 0x0000},
    {
        {0x0200, 4, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6E88 = {
    {0x0100, 0x0000},
    {
        {0x0200, 4, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6E94 = {
    {0x0100, 0x0000},
    {
        {0x0300, 33, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6EA0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 5, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6EAC = {
    {0x0100, 0x0000},
    {
        {0x0400, 1, 1, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6EB8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 4, 0, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6EC4 = {
    {0x0100, 0x0000},
    {
        {0x0500, 4, 1, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6ED0 = {
    {0x0100, 0x0000},
    {
        {0x0500, 6, 2, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6EDC = {
    {0x0100, 0x0000},
    {
        {0x0500, -2, -1, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6EE8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 5, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6EF4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 1, 2, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6F00 = {
    {0x0100, 0x0000},
    {
        {0x0600, 8, 1, 13},
    },
};

SaturnSpriteFrame1 DAT_060D6F0C = {
    {0x0100, 0x0000},
    {
        {0x0700, 2, 0, 14},
    },
};

SaturnSpriteFrame2 DAT_060D6F18 = {
    {0x0200, 0x0000},
    {
        {0x0700, 0, -89, 15},
        {0x0700, 0, -10, 16},
    },
};

SaturnSpriteFrame1 DAT_060D6F2C = {
    {0x0100, 0x0000},
    {
        {0x0400, 1, 2, 12},
    },
};

SaturnSpriteFrame3 DAT_060D6F38 = {
    {0x0300, 0x0000},
    {
        {0x0500, 6, 2, 9},
        {0x0500, 8, 4, 9},
        {0x0500, 9, 7, 9},
    },
};

SaturnSpriteFrameHeader* DAT_060D6F54[22] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6E3C,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6F2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F38,
};

SaturnSpriteResource DAT_060D6FAC = {
    DAT_060D6CF0, (u16*)&DAT_060D6D38, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6FB8[1] = {&DAT_060D6FAC};
