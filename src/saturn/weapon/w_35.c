// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62C8();
void func_060D62E0();
void func_060D62F8();
void func_060D6310();
void func_060D6328();
void func_060D6340();
void func_060D634C();
void func_060D6364();
void func_060D637C();
void func_060D6394();
void func_060D63AC();
void func_060D63C4();
void func_060D63DC();
void func_060D63F4();
void func_060D640C();
extern SaturnSpriteResource* DAT_060D66EC[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62C8,
        func_060D62E0,
        func_060D62F8,
        func_060D6310,
        func_060D6328,
        func_060D6340,
        func_060D640C,
        func_060D634C,
        func_060D6364,
        func_060D637C,
        func_060D6394,
        func_060D63AC,
        func_060D63C4,
        func_060D63DC,
        func_060D63F4,
    },
    DAT_060D66EC,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D62C8, func_060D62C8);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D62E0, func_060D62E0);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D62F8, func_060D62F8);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D6310, func_060D6310);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D6328, func_060D6328);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D6340, func_060D6340);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D634C, func_060D634C);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D6364, func_060D6364);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D637C, func_060D637C);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D6394, func_060D6394);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D63AC, func_060D63AC);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D63C4, func_060D63C4);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D63DC, func_060D63DC);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D63F4, func_060D63F4);
INCLUDE_ASM("asm/saturn/weapon/w_35/f_nonmat", f60D640C, func_060D640C);

u16 DAT_060D6420[10] = {0x0201, 0x0402, 0x0403, 0x0604, 0x0605,
                        0x0606, 0x0607, 0x0608, 0x0609, 0xFFFF};

u16 DAT_060D6434[10] = {0x080A, 0x0A0B, 0x0A0C, 0x060D, 0x060E,
                        0x060F, 0x0610, 0x0611, 0x0612, 0xFFFF};

u16 DAT_060D6448[7] = {0x0C13, 0x0E14, 0x0E15, 0x0616, 0x0617, 0x0618, 0xFFFF};

u16 DAT_060D6456[7] = {0x1019, 0x121A, 0x121B, 0x061C, 0x061D, 0x061E, 0xFFFF};

s8 DAT_060D6464[10][4] = {
    {0, 0, 0, 0},      {5, -23, 10, 5}, {35, -14, 30, 4}, {-40, -31, 0, 0},
    {-5, -6, 10, 5},   {25, 3, 30, 4},  {1, -25, 10, 5},  {31, -16, 30, 4},
    {-10, -26, 10, 5}, {26, -14, 30, 4}};

u16* DAT_060D648C[7] = {DAT_060D6420, DAT_060D6420, DAT_060D6434, DAT_060D6434,
                        DAT_060D6448, DAT_060D6456, DAT_060D6456};

WeaponAnimation DAT_060D64A8[1] = {
    {(u16**)DAT_060D648C, (s8*)DAT_060D6464, 0x0000, 0x060B, 0x93, 0x04, 0},
};

SaturnSpriteImage DAT_060D64B8[7] = {
    {12, 5, 0x0000}, {36, 8, 0x0010}, {12, 2, 0x0058}, {20, 4, 0x0060},
    {4, 2, 0x0074},  {8, 2, 0x0078},  {0, 0, 0x007C},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D64D4 = {
    0x0001,
    {
        {0x81A0, 0x9084, 0x848B, 0x90B2, 0xA0F9, 0x8D5B, 0x8340, 0xAD6B, 0xCE73,
         0xEB5A, 0x90EB, 0x8173, 0x9218, 0x9EDF, 0x83E0, 0x8014},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D64F8 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D64FC = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6508 = {
    {0x0100, 0x0000},
    {
        {0x0004, 35, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6514 = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6520 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D652C = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -4, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6538 = {
    {0x0100, 0x0000},
    {
        {0x0000, -13, -5, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6544 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6550 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D655C = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6568 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6574 = {
    {0x0100, 0x0000},
    {
        {0x0004, 30, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6580 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D658C = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6598 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, 11, 4},
    },
};

SaturnSpriteFrame1 DAT_060D65A4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -21, 12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65B0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -22, 12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65BC = {
    {0x0100, 0x0000},
    {
        {0x0000, -23, 12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65C8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -23, 12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65D4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D65E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 28, -23, 1},
    },
};

SaturnSpriteFrame1 DAT_060D65EC = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D65F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6604 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6610 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D661C = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6628 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6634 = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6640 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D664C = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6658 = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 5},
    },
};

SaturnSpriteFrameHeader* DAT_060D6664[31] = {
    (SaturnSpriteFrameHeader*)&DAT_060D64F8,
    (SaturnSpriteFrameHeader*)&DAT_060D64FC,
    (SaturnSpriteFrameHeader*)&DAT_060D6508,
    (SaturnSpriteFrameHeader*)&DAT_060D6514,
    (SaturnSpriteFrameHeader*)&DAT_060D6520,
    (SaturnSpriteFrameHeader*)&DAT_060D652C,
    (SaturnSpriteFrameHeader*)&DAT_060D6538,
    (SaturnSpriteFrameHeader*)&DAT_060D6544,
    (SaturnSpriteFrameHeader*)&DAT_060D6550,
    (SaturnSpriteFrameHeader*)&DAT_060D655C,
    (SaturnSpriteFrameHeader*)&DAT_060D6568,
    (SaturnSpriteFrameHeader*)&DAT_060D6574,
    (SaturnSpriteFrameHeader*)&DAT_060D6580,
    (SaturnSpriteFrameHeader*)&DAT_060D658C,
    (SaturnSpriteFrameHeader*)&DAT_060D6598,
    (SaturnSpriteFrameHeader*)&DAT_060D65A4,
    (SaturnSpriteFrameHeader*)&DAT_060D65B0,
    (SaturnSpriteFrameHeader*)&DAT_060D65BC,
    (SaturnSpriteFrameHeader*)&DAT_060D65C8,
    (SaturnSpriteFrameHeader*)&DAT_060D65D4,
    (SaturnSpriteFrameHeader*)&DAT_060D65E0,
    (SaturnSpriteFrameHeader*)&DAT_060D65EC,
    (SaturnSpriteFrameHeader*)&DAT_060D65F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6604,
    (SaturnSpriteFrameHeader*)&DAT_060D6610,
    (SaturnSpriteFrameHeader*)&DAT_060D661C,
    (SaturnSpriteFrameHeader*)&DAT_060D6628,
    (SaturnSpriteFrameHeader*)&DAT_060D6634,
    (SaturnSpriteFrameHeader*)&DAT_060D6640,
    (SaturnSpriteFrameHeader*)&DAT_060D664C,
    (SaturnSpriteFrameHeader*)&DAT_060D6658,
};

SaturnSpriteResource DAT_060D66E0 = {
    DAT_060D64B8, (u16*)&DAT_060D64D4, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D66EC[1] = {&DAT_060D66E0};
