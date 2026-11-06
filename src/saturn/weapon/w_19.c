// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6814();
void func_060D682C();
void func_060D6844();
void func_060D685C();
void func_060D6874();
void func_060D688C();
void func_060D6898();
void func_060D68B0();
void func_060D68C8();
void func_060D68E0();
void func_060D68F8();
void func_060D6910();
void func_060D6928();
void func_060D6940();
void func_060D6958();
extern SaturnSpriteResource* DAT_060D6B44[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6814,
        func_060D682C,
        func_060D6844,
        func_060D685C,
        func_060D6874,
        func_060D688C,
        func_060D6958,
        func_060D6898,
        func_060D68B0,
        func_060D68C8,
        func_060D68E0,
        func_060D68F8,
        func_060D6910,
        func_060D6928,
        func_060D6940,
    },
    DAT_060D6B44,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6814, func_060D6814);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D682C, func_060D682C);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6844, func_060D6844);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D685C, func_060D685C);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6874, func_060D6874);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D688C, func_060D688C);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6898, func_060D6898);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D68B0, func_060D68B0);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D68C8, func_060D68C8);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D68E0, func_060D68E0);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D68F8, func_060D68F8);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6910, func_060D6910);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6928, func_060D6928);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6940, func_060D6940);
INCLUDE_ASM("asm/saturn/weapon/w_19/f_nonmat", f60D6958, func_060D6958);

u32 DAT_060D6970[7] = {
    0x00010000, 0x00010001, 0x00010002, 0x00010003,
    0x00020004, 0x00400000, 0xFFFF0000,
};

SaturnSpriteImage DAT_060D698C[8] = {
    {16, 11, 0x0000}, {20, 15, 0x002C}, {12, 8, 0x0078},  {20, 15, 0x0090},
    {40, 52, 0x00DC}, {28, 21, 0x02E4}, {40, 64, 0x0378}, {0, 0, 0x05F8},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D69AC = {
    0x0003,
    {
        {0x8581, 0x9463, 0xB527, 0xCDAC, 0xDA52, 0xEB18, 0x83E0, 0x8443, 0x8486,
         0x84EA, 0x898E, 0x9A12, 0xAE97, 0xBF1B, 0xD3BF, 0xFFFF},
        {0x8280, 0x8420, 0x8421, 0x8441, 0x8842, 0x8C63, 0x9084, 0x98C6, 0xA0E6,
         0xA907, 0xB128, 0xB969, 0xC18A, 0xD60C, 0xEA8E, 0xFF11},
        {0x9585, 0x8400, 0x8820, 0x8C21, 0x9041, 0x9442, 0x9863, 0x9C84, 0xD460,
         0xECC0, 0xF180, 0xF604, 0xFA85, 0xFF4B, 0xFFD5, 0xFFFF},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6A10 = {0x0000, 0x0000};

SaturnSpriteFrame4 DAT_060D6A14 = {
    {0x0400, 0x0000},
    {
        {0x0000, -6, -7, 0},
        {0x0010, 8, -7, 0},
        {0x0030, 8, 5, 0},
        {0x0020, -6, 5, 0},
    },
};

SaturnSpriteFrame7 DAT_060D6A38 = {
    {0x0700, 0x0000},
    {
        {0x0000, -9, -14, 1},
        {0x0000, 11, -14, 1},
        {0x0000, 19, 2, 1},
        {0x0000, 11, 16, 1},
        {0x0000, -9, 16, 1},
        {0x0000, -17, 2, 1},
        {0x0000, -17, -7, 2},
    },
};

SaturnSpriteFrame10 DAT_060D6A74 = {
    {0x0A00, 0x0000},
    {
        {0x0000, -13, -11, 3},
        {0x0010, 14, -11, 3},
        {0x0030, 14, 13, 3},
        {0x0020, -13, 13, 3},
        {0x0000, -21, -31, 1},
        {0x0000, 23, -31, 1},
        {0x0000, 47, 1, 1},
        {0x0000, 27, 33, 1},
        {0x0000, -21, 33, 1},
        {0x0000, -41, 1, 1},
    },
};

SaturnSpriteFrame8 DAT_060D6AC8 = {
    {0x0800, 0x0000},
    {
        {0x0100, -39, -51, 4},
        {0x0110, 37, -51, 4},
        {0x0130, 37, 51, 4},
        {0x0120, -39, 51, 4},
        {0x0100, -102, -22, 5},
        {0x0120, -102, 25, 5},
        {0x0110, 99, -22, 5},
        {0x0130, 99, 24, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6B0C = {
    {0x0200, 0x0000},
    {
        {0x0200, -39, 1, 6},
        {0x0210, 41, 1, 6},
    },
};

SaturnSpriteFrameHeader* DAT_060D6B20[6] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6A10,
    (SaturnSpriteFrameHeader*)&DAT_060D6A14,
    (SaturnSpriteFrameHeader*)&DAT_060D6A38,
    (SaturnSpriteFrameHeader*)&DAT_060D6A74,
    (SaturnSpriteFrameHeader*)&DAT_060D6AC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6B0C,
};

SaturnSpriteResource DAT_060D6B38 = {
    DAT_060D698C, (u16*)&DAT_060D69AC, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6B44[1] = {&DAT_060D6B38};
