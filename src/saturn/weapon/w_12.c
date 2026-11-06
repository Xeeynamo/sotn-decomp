// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D665C();
void func_060D6ADC();
void func_060D6C50();
void func_060D6C68();
void func_060D6C80();
void func_060D6C98();
void func_060D6CA4();
void func_060D6CBC();
void func_060D6CD4();
void func_060D6CEC();
void func_060D6D04();
void func_060D6D1C();
void func_060D6D34();
void func_060D6D4C();
void func_060D6D64();
extern SaturnSpriteResource* DAT_060D6FB0[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D665C,
        func_060D6ADC,
        func_060D6C50,
        func_060D6C68,
        func_060D6C80,
        func_060D6C98,
        func_060D6D64,
        func_060D6CA4,
        func_060D6CBC,
        func_060D6CD4,
        func_060D6CEC,
        func_060D6D04,
        func_060D6D1C,
        func_060D6D34,
        func_060D6D4C,
    },
    DAT_060D6FB0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D665C, func_060D665C);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6ADC, func_060D6ADC);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6C50, func_060D6C50);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6C68, func_060D6C68);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6C80, func_060D6C80);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6C98, func_060D6C98);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6CA4, func_060D6CA4);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6CBC, func_060D6CBC);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6CD4, func_060D6CD4);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6CEC, func_060D6CEC);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6D04, func_060D6D04);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6D1C, func_060D6D1C);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6D34, func_060D6D34);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6D4C, func_060D6D4C);
INCLUDE_ASM("asm/saturn/weapon/w_12/f_nonmat", f60D6D64, func_060D6D64);

u32 DAT_060D6D70[5] = {
    0x00000001, 0x01020103, 0x02040205, 0x03060307, 0x04080409,
};

SaturnSpriteImage DAT_060D6D84[9] = {
    {40, 32, 0x0000}, {40, 32, 0x0140}, {40, 32, 0x0280},
    {40, 32, 0x03C0}, {40, 32, 0x0500}, {12, 8, 0x0640},
    {12, 8, 0x0658},  {12, 8, 0x0670},  {0, 0, 0x0688},
};

SaturnSpriteFrameHeader DAT_060D6DA8 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6DAC = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, 15, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DB8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 50, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DC4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 50, -7, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6DD0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 50, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DDC = {
    {0x0100, 0x0000},
    {
        {0x0400, 50, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DE8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 50, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DF4 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 1, 0, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E00 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 1, 0, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6E0C = {
    {0x0100, 0x0000},
    {
        {0x0A00, 1, 0, 7},
    },
};

SaturnSpriteFrameHeader* DAT_060D6E18[10] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6DA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6E00,
    (SaturnSpriteFrameHeader*)&DAT_060D6E0C,
};

struct {
    u16 countAndFlags;
    u16 colors[11][16];
    u16 padding[1];
} DAT_060D6E40 = {
    0x000B,
    {
        {0x9164, 0xB117, 0xB599, 0xBA1B, 0xC2BE, 0xC77F, 0xCFFF, 0xFFFD, 0xF24E,
         0xE9AD, 0xE14B, 0xD12A, 0xC0E8, 0xB4C7, 0xA486, 0x9864},
        {0xB606, 0xD5B9, 0xDA1B, 0xDEBD, 0xE75F, 0xEBFF, 0xF3FF, 0xFFFF, 0xFED1,
         0xFE4F, 0xFDED, 0xF5AC, 0xE58B, 0xD969, 0xC928, 0xBD06},
        {0x8942, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xCD2B,
         0xD58C, 0xDE0E, 0xE670, 0xEEF1, 0xF753, 0xFFD5, 0xFFFF},
        {0x9DC6, 0xC1D8, 0xCA5A, 0xD2DC, 0xDB5F, 0xE3DF, 0xEBFF, 0xFFFF, 0x9DC6,
         0xE1AF, 0xEA10, 0xFAF4, 0xFF75, 0xFFD7, 0xFFF9, 0xFFFF},
        {0xA1E7, 0xC5F9, 0xCE7B, 0xD6FD, 0xDF7F, 0xE7FF, 0xEFFF, 0xFFFF, 0xA1E7,
         0xA1E7, 0xE5D0, 0xEE31, 0xFF96, 0xFFF8, 0xFFFA, 0xFFFF},
        {0x9E05, 0xBD9A, 0xBDFC, 0xC69E, 0xCF5F, 0xD7FF, 0xDFFF, 0xFFFF, 0x9E05,
         0x9E05, 0x9E05, 0xE96E, 0xF1AD, 0xFFF4, 0xFFF6, 0xFFFF},
        {0x8942, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0x8942,
         0x8942, 0x8942, 0x8942, 0xCD2B, 0xD58C, 0xFFD5, 0xFFFF},
        {0x9E86, 0xB97E, 0xB9FF, 0xC2FF, 0xCBFF, 0xD3FF, 0xFFFF, 0xFFFF, 0x9E86,
         0x9E86, 0x9E86, 0x9E86, 0x9E86, 0xF94E, 0xFDAD, 0xFFFF},
        {0x9AA4, 0xB11F, 0xB19F, 0xBADF, 0xC3FF, 0xCBFF, 0xFFFF, 0xFFFF, 0x9AA4,
         0x9AA4, 0x9AA4, 0x9AA4, 0x9AA4, 0x9AA4, 0xFCEB, 0xFD4A},
        {0x92E1, 0xAC9F, 0xA13F, 0xAB9F, 0xB7FF, 0xFFFF, 0xFFFF, 0xFFFF, 0x92E1,
         0x92E1, 0x92E1, 0x92E1, 0x92E1, 0x92E1, 0x92E1, 0xFC69},
        {0xB804, 0xB844, 0xB884, 0xB8C4, 0xB904, 0xB944, 0xB984, 0xB9C4, 0xBA04,
         0xBA44, 0xBA84, 0xBAC4, 0xBB04, 0xBB44, 0xBB84, 0xBBC4},
    },
    {0x0000},
};

SaturnSpriteResource DAT_060D6FA4 = {
    DAT_060D6D84, (u16*)&DAT_060D6E40, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6FB0[1] = {&DAT_060D6FA4};
