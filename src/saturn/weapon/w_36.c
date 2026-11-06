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
extern SaturnSpriteResource* DAT_060D66FC[];

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
    DAT_060D66FC,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D62C8, func_060D62C8);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D62E0, func_060D62E0);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D62F8, func_060D62F8);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D6310, func_060D6310);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D6328, func_060D6328);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D6340, func_060D6340);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D634C, func_060D634C);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D6364, func_060D6364);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D637C, func_060D637C);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D6394, func_060D6394);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D63AC, func_060D63AC);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D63C4, func_060D63C4);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D63DC, func_060D63DC);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D63F4, func_060D63F4);
INCLUDE_ASM("asm/saturn/weapon/w_36/f_nonmat", f60D640C, func_060D640C);

u16 DAT_060D6420[10] = {0x0201, 0x0402, 0x0603, 0x0804, 0x0805,
                        0x0806, 0x0807, 0x0808, 0x0809, 0xFFFF};

u16 DAT_060D6434[10] = {0x0A0A, 0x0C0B, 0x0E0C, 0x080D, 0x080E,
                        0x080F, 0x0810, 0x0811, 0x0812, 0xFFFF};

u16 DAT_060D6448[7] = {0x1013, 0x1214, 0x1415, 0x0816, 0x0817, 0x0818, 0xFFFF};

u16 DAT_060D6456[7] = {0x1619, 0x181A, 0x1A1B, 0x081C, 0x081D, 0x081E, 0xFFFF};

s8 DAT_060D6464[14][4] = {
    {0, 0, 0, 0},      {6, -23, 9, 4},    {31, -20, 28, 10}, {34, -13, 28, 3},
    {-40, -31, 0, 0},  {-4, -7, 8, 4},    {21, -5, 28, 10},  {25, 3, 28, 3},
    {1, -25, 8, 4},    {29, -23, 28, 10}, {31, -15, 28, 3},  {-9, -27, 8, 4},
    {24, -22, 28, 10}, {28, -14, 28, 3}};

u16* DAT_060D649C[7] = {DAT_060D6420, DAT_060D6420, DAT_060D6434, DAT_060D6434,
                        DAT_060D6448, DAT_060D6456, DAT_060D6456};

WeaponAnimation DAT_060D64B8[1] = {
    {(u16**)DAT_060D649C, (s8*)DAT_060D6464, 0x0000, 0x060B, 0x9A, 0x04, 0},
};

SaturnSpriteImage DAT_060D64C8[7] = {
    {12, 5, 0x0000}, {32, 9, 0x0010}, {12, 2, 0x0058}, {20, 4, 0x0060},
    {4, 2, 0x0074},  {8, 2, 0x0078},  {0, 0, 0x007C},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D64E4 = {
    0x0001,
    {
        {0x81A0, 0x9084, 0x848B, 0x90B2, 0xA0F9, 0x8DB6, 0x9573, 0xAD6B, 0xCE73,
         0xEB5A, 0x90EB, 0x8173, 0x9218, 0x9E9F, 0xCB5F, 0x812E},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6508 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D650C = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6518 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6524 = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6530 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D653C = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6548 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6554 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6560 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D656C = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6578 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6584 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, -4, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6590 = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, 3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D659C = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, 7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D65A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, 11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -22, 11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65CC = {
    {0x0100, 0x0000},
    {
        {0x0000, -23, 11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -23, 11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D65E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D65F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, -22, 1},
    },
};

SaturnSpriteFrame1 DAT_060D65FC = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6608 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6614 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6620 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -5, 5},
    },
};

SaturnSpriteFrame1 DAT_060D662C = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6638 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6644 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6650 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, -10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D665C = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -5, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6668 = {
    {0x0100, 0x0000},
    {
        {0x0000, -21, -6, 5},
    },
};

SaturnSpriteFrameHeader* DAT_060D6674[31] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6508,
    (SaturnSpriteFrameHeader*)&DAT_060D650C,
    (SaturnSpriteFrameHeader*)&DAT_060D6518,
    (SaturnSpriteFrameHeader*)&DAT_060D6524,
    (SaturnSpriteFrameHeader*)&DAT_060D6530,
    (SaturnSpriteFrameHeader*)&DAT_060D653C,
    (SaturnSpriteFrameHeader*)&DAT_060D6548,
    (SaturnSpriteFrameHeader*)&DAT_060D6554,
    (SaturnSpriteFrameHeader*)&DAT_060D6560,
    (SaturnSpriteFrameHeader*)&DAT_060D656C,
    (SaturnSpriteFrameHeader*)&DAT_060D6578,
    (SaturnSpriteFrameHeader*)&DAT_060D6584,
    (SaturnSpriteFrameHeader*)&DAT_060D6590,
    (SaturnSpriteFrameHeader*)&DAT_060D659C,
    (SaturnSpriteFrameHeader*)&DAT_060D65A8,
    (SaturnSpriteFrameHeader*)&DAT_060D65B4,
    (SaturnSpriteFrameHeader*)&DAT_060D65C0,
    (SaturnSpriteFrameHeader*)&DAT_060D65CC,
    (SaturnSpriteFrameHeader*)&DAT_060D65D8,
    (SaturnSpriteFrameHeader*)&DAT_060D65E4,
    (SaturnSpriteFrameHeader*)&DAT_060D65F0,
    (SaturnSpriteFrameHeader*)&DAT_060D65FC,
    (SaturnSpriteFrameHeader*)&DAT_060D6608,
    (SaturnSpriteFrameHeader*)&DAT_060D6614,
    (SaturnSpriteFrameHeader*)&DAT_060D6620,
    (SaturnSpriteFrameHeader*)&DAT_060D662C,
    (SaturnSpriteFrameHeader*)&DAT_060D6638,
    (SaturnSpriteFrameHeader*)&DAT_060D6644,
    (SaturnSpriteFrameHeader*)&DAT_060D6650,
    (SaturnSpriteFrameHeader*)&DAT_060D665C,
    (SaturnSpriteFrameHeader*)&DAT_060D6668,
};

SaturnSpriteResource DAT_060D66F0 = {
    DAT_060D64C8, (u16*)&DAT_060D64E4, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D66FC[1] = {&DAT_060D66F0};
