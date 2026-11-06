// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D63A0();
void func_060D63B8();
void func_060D63D0();
void func_060D63E8();
void func_060D6400();
void func_060D6418();
void func_060D6424();
void func_060D643C();
void func_060D6454();
void func_060D646C();
void func_060D6484();
void func_060D649C();
void func_060D64B4();
void func_060D64CC();
void func_060D64E4();
extern SaturnSpriteResource* DAT_060D6A24[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D63A0,
        func_060D63B8,
        func_060D63D0,
        func_060D63E8,
        func_060D6400,
        func_060D6418,
        func_060D64E4,
        func_060D6424,
        func_060D643C,
        func_060D6454,
        func_060D646C,
        func_060D6484,
        func_060D649C,
        func_060D64B4,
        func_060D64CC,
    },
    DAT_060D6A24,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D63A0, func_060D63A0);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D63B8, func_060D63B8);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D63D0, func_060D63D0);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D63E8, func_060D63E8);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D6400, func_060D6400);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D6418, func_060D6418);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D6424, func_060D6424);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D643C, func_060D643C);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D6454, func_060D6454);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D646C, func_060D646C);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D6484, func_060D6484);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D649C, func_060D649C);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D64B4, func_060D64B4);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D64CC, func_060D64CC);
INCLUDE_ASM("asm/saturn/weapon/w_32/f_nonmat", f60D64E4, func_060D64E4);

u16 DAT_060D64F0[9] = {
    0x0201, 0x0402, 0x0603, 0x0605, 0x0603, 0x0402, 0x3A04, 0x0806, 0xFFFF};

u16 DAT_060D6502[8] = {
    0x0A07, 0x0C09, 0x0E0A, 0x0E0B, 0x0E0A, 0x0C09, 0x3A08, 0xFFFF};

u16 DAT_060D6512[6] = {0x040C, 0x100D, 0x100E, 0x100D, 0x040C, 0xFFFF};

u16 DAT_060D651E[4] = {0x120F, 0x1410, 0x120F, 0xFFFF};

u16 DAT_060D6526[10] = {0x1611, 0x1812, 0x1813, 0x1A14, 0x0815,
                        0x0816, 0x0817, 0x0818, 0x0819, 0xFFFF};

u16 DAT_060D653A[10] = {0x1C1A, 0x1E1B, 0x1E1C, 0x201D, 0x081E,
                        0x0823, 0x0824, 0x0825, 0x0826, 0xFFFF};

u16 DAT_060D654E[10] = {0x1C1A, 0x221F, 0x2420, 0x2621, 0x0822,
                        0x0823, 0x0824, 0x0825, 0x0826, 0xFFFF};

u16 DAT_060D6562[7] = {0x2827, 0x2A28, 0x2A29, 0x2C2A, 0x082B, 0x082C, 0xFFFF};

u16 DAT_060D6570[14] = {0x2E2D, 0x302E, 0x302F, 0x3230, 0x0831, 0x0836, 0xFFFF,
                        0x2E2D, 0x3432, 0x3633, 0x3834, 0x0835, 0x0836, 0xFFFF};

s8 DAT_060D658C[30][4] = {
    {0, 0, 0, 0},     {15, -16, 10, 9}, {23, -15, 16, 5}, {26, -13, 28, 5},
    {-40, -31, 0, 0}, {9, 1, 11, 9},    {16, 3, 15, 6},   {18, 4, 28, 5},
    {29, -12, 29, 8}, {9, -9, 14, 9},   {25, 3, 18, 13},  {-6, -16, 6, 4},
    {24, -14, 30, 5}, {30, -12, 16, 3}, {-19, 1, 8, 4},   {16, 3, 30, 5},
    {20, 5, 16, 3},   {11, 13, 20, 9},  {25, 21, 23, 8},  {15, 19, 16, 3},
    {-14, -17, 8, 4}, {24, -16, 28, 8}, {28, -14, 18, 3}, {-25, -19, 6, 4},
    {20, -14, 29, 8}, {23, -12, 18, 3}, {20, -1, 24, 13}, {24, -1, 24, 13},
    {15, 1, 19, 4},   {20, -12, 6, 4}};

u16* DAT_060D6604[7] = {DAT_060D64F0, DAT_060D64F0, DAT_060D6502, DAT_060D6502,
                        DAT_060D6512, DAT_060D651E, DAT_060D651E};

u16* DAT_060D6620[7] = {DAT_060D6526, DAT_060D6526, DAT_060D653A, DAT_060D654E,
                        DAT_060D6562, DAT_060D6570, DAT_060D6570};

WeaponAnimation DAT_060D663C[2] = {
    {(u16**)DAT_060D6604, (s8*)DAT_060D658C, 0x0000, 0x060C, 0x77, 0x01, 0},
    {(u16**)DAT_060D6620, (s8*)DAT_060D658C, 0x0000, 0x060B, 0x7E, 0x02, 0},
};

SaturnSpriteImage DAT_060D665C[12] = {
    {8, 5, 0x0000},  {8, 3, 0x000C},  {12, 2, 0x0014}, {16, 2, 0x001C},
    {8, 3, 0x0024},  {24, 1, 0x002C}, {20, 3, 0x0034}, {4, 2, 0x0044},
    {20, 8, 0x0048}, {16, 3, 0x0070}, {20, 5, 0x007C}, {0, 0, 0x0098},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D668C = {
    0x0001,
    {
        {0x8160, 0x8421, 0x9084, 0x98C6, 0xA108, 0xA94A, 0xB18C, 0xB9CD, 0xFC42,
         0x9084, 0x90EB, 0x9D73, 0x9198, 0x9E1F, 0x98DF, 0x93A4},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D66B0 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D66B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -20, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D66CC = {
    {0x0100, 0x0000},
    {
        {0x0000, 41, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66D8 = {
    {0x0100, 0x0000},
    {
        {0x0020, 19, -11, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66F0 = {
    {0x0100, 0x0000},
    {
        {0x0010, 9, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66FC = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6708 = {
    {0x0100, 0x0000},
    {
        {0x0020, 12, 7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6714 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, 0, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6720 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, 6, 2},
    },
};

SaturnSpriteFrame1 DAT_060D672C = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, 6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6738 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -18, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6744 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -11, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6750 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D675C = {
    {0x0100, 0x0000},
    {
        {0x0010, 8, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6768 = {
    {0x0100, 0x0000},
    {
        {0x0010, 39, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6774 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -16, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6780 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -14, 5},
    },
};

SaturnSpriteFrame1 DAT_060D678C = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6798 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, -11, 6},
    },
};

SaturnSpriteFrame1 DAT_060D67A4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67B0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67BC = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67C8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67D4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67E0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D67EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, 4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D67F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6804 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 6, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6810 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, 10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D681C = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, 12, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6828 = {
    {0x0100, 0x0000},
    {
        {0x0010, 25, 18, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6834 = {
    {0x0100, 0x0000},
    {
        {0x0010, 14, 17, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6840 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, 12, 7},
    },
};

SaturnSpriteFrame1 DAT_060D684C = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, 10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6858 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6864 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6870 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D687C = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -18, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6888 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -15, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6894 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D68A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -13, 6},
    },
};

SaturnSpriteFrame1 DAT_060D68AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D68B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D68C4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -21, -19, 4},
    },
};

SaturnSpriteFrame1 DAT_060D68D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -14, 5},
    },
};

SaturnSpriteFrame1 DAT_060D68DC = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D68E8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -11, 6},
    },
};

SaturnSpriteFrame1 DAT_060D68F4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, -10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6900 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, 2, 8},
    },
};

SaturnSpriteFrame1 DAT_060D690C = {
    {0x0100, 0x0000},
    {
        {0x0010, 32, 8, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6918 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 1, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6924 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -7, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6930 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -9, 7},
    },
};

SaturnSpriteFrameHeader* DAT_060D693C[55] = {
    (SaturnSpriteFrameHeader*)&DAT_060D66B0,
    (SaturnSpriteFrameHeader*)&DAT_060D66B4,
    (SaturnSpriteFrameHeader*)&DAT_060D66C0,
    (SaturnSpriteFrameHeader*)&DAT_060D66CC,
    (SaturnSpriteFrameHeader*)&DAT_060D66D8,
    (SaturnSpriteFrameHeader*)&DAT_060D66E4,
    (SaturnSpriteFrameHeader*)&DAT_060D66F0,
    (SaturnSpriteFrameHeader*)&DAT_060D66FC,
    (SaturnSpriteFrameHeader*)&DAT_060D6708,
    (SaturnSpriteFrameHeader*)&DAT_060D6714,
    (SaturnSpriteFrameHeader*)&DAT_060D6720,
    (SaturnSpriteFrameHeader*)&DAT_060D672C,
    (SaturnSpriteFrameHeader*)&DAT_060D6738,
    (SaturnSpriteFrameHeader*)&DAT_060D6744,
    (SaturnSpriteFrameHeader*)&DAT_060D6750,
    (SaturnSpriteFrameHeader*)&DAT_060D675C,
    (SaturnSpriteFrameHeader*)&DAT_060D6768,
    (SaturnSpriteFrameHeader*)&DAT_060D6774,
    (SaturnSpriteFrameHeader*)&DAT_060D6780,
    (SaturnSpriteFrameHeader*)&DAT_060D678C,
    (SaturnSpriteFrameHeader*)&DAT_060D6798,
    (SaturnSpriteFrameHeader*)&DAT_060D67A4,
    (SaturnSpriteFrameHeader*)&DAT_060D67B0,
    (SaturnSpriteFrameHeader*)&DAT_060D67BC,
    (SaturnSpriteFrameHeader*)&DAT_060D67C8,
    (SaturnSpriteFrameHeader*)&DAT_060D67D4,
    (SaturnSpriteFrameHeader*)&DAT_060D67E0,
    (SaturnSpriteFrameHeader*)&DAT_060D67EC,
    (SaturnSpriteFrameHeader*)&DAT_060D67F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6804,
    (SaturnSpriteFrameHeader*)&DAT_060D6810,
    (SaturnSpriteFrameHeader*)&DAT_060D681C,
    (SaturnSpriteFrameHeader*)&DAT_060D6828,
    (SaturnSpriteFrameHeader*)&DAT_060D6834,
    (SaturnSpriteFrameHeader*)&DAT_060D6840,
    (SaturnSpriteFrameHeader*)&DAT_060D684C,
    (SaturnSpriteFrameHeader*)&DAT_060D6858,
    (SaturnSpriteFrameHeader*)&DAT_060D6864,
    (SaturnSpriteFrameHeader*)&DAT_060D6870,
    (SaturnSpriteFrameHeader*)&DAT_060D687C,
    (SaturnSpriteFrameHeader*)&DAT_060D6888,
    (SaturnSpriteFrameHeader*)&DAT_060D6894,
    (SaturnSpriteFrameHeader*)&DAT_060D68A0,
    (SaturnSpriteFrameHeader*)&DAT_060D68AC,
    (SaturnSpriteFrameHeader*)&DAT_060D68B8,
    (SaturnSpriteFrameHeader*)&DAT_060D68C4,
    (SaturnSpriteFrameHeader*)&DAT_060D68D0,
    (SaturnSpriteFrameHeader*)&DAT_060D68DC,
    (SaturnSpriteFrameHeader*)&DAT_060D68E8,
    (SaturnSpriteFrameHeader*)&DAT_060D68F4,
    (SaturnSpriteFrameHeader*)&DAT_060D6900,
    (SaturnSpriteFrameHeader*)&DAT_060D690C,
    (SaturnSpriteFrameHeader*)&DAT_060D6918,
    (SaturnSpriteFrameHeader*)&DAT_060D6924,
    (SaturnSpriteFrameHeader*)&DAT_060D6930,
};

SaturnSpriteResource DAT_060D6A18 = {
    DAT_060D665C, (u16*)&DAT_060D668C, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6A24[1] = {&DAT_060D6A18};
