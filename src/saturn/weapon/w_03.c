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
extern SaturnSpriteResource* DAT_060D69C0[];

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
    DAT_060D69C0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D62C8, func_060D62C8);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D62E0, func_060D62E0);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D62F8, func_060D62F8);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D6310, func_060D6310);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D6328, func_060D6328);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D6340, func_060D6340);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D634C, func_060D634C);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D6364, func_060D6364);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D637C, func_060D637C);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D6394, func_060D6394);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D63AC, func_060D63AC);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D63C4, func_060D63C4);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D63DC, func_060D63DC);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D63F4, func_060D63F4);
INCLUDE_ASM("asm/saturn/weapon/w_03/f_nonmat", f60D640C, func_060D640C);

u16 DAT_060D6420[14] = {0x2A01, 0x2C02, 0x0403, 0x2E04, 0x3005, 0x3206, 0x0807,
                        0x0808, 0x0809, 0x340A, 0x340B, 0x340C, 0x340D, 0xFFFF};

u16 DAT_060D643C[14] = {0x360E, 0x380F, 0x0E10, 0x3A11, 0x3C12, 0x3E13, 0x1214,
                        0x1215, 0x1216, 0x401E, 0x401F, 0x4020, 0x4021, 0xFFFF};

u16 DAT_060D6458[14] = {0x360E, 0x380F, 0x4217, 0x4418, 0x4419, 0x461A, 0x1A1B,
                        0x1A1C, 0x1A1D, 0x401E, 0x401F, 0x4020, 0x4021, 0xFFFF};

u16 DAT_060D6474[14] = {0x2A01, 0x2C02, 0x0424, 0x2E25, 0x3026, 0x3206, 0x0807,
                        0x0808, 0x0809, 0x340A, 0x340B, 0x340C, 0x340D, 0xFFFF};

u16 DAT_060D6490[11] = {0x482C, 0x4A2D, 0x042E, 0x4C2F, 0x4E30, 0x5031,
                        0x0832, 0x0833, 0x0834, 0x523C, 0xFFFF};

u16 DAT_060D64A6[21] = {0x482C, 0x4A2D, 0x5435, 0x5636, 0x5637, 0x5838, 0x2239,
                        0x223A, 0x223B, 0x523C, 0xFFFF, 0x0004, 0x243D, 0x0004,
                        0x243E, 0x0004, 0x243F, 0x0004, 0x2440, 0x0000, 0x0000};

s8 DAT_060D64D0[45][4] = {
    {0, 0, 0, 0},      {-4, -26, 15, 4},  {33, -27, 20, 6},  {50, -18, 10, 8},
    {22, -9, 15, 8},   {-19, -4, 5, 4},   {-13, -8, 15, 4},  {24, -11, 20, 8},
    {40, -1, 10, 8},   {19, 8, 15, 8},    {28, 3, 23, 4},    {21, 2, 15, 12},
    {36, 19, 10, 8},   {14, 18, 15, 8},   {-29, 14, 5, 4},   {-18, -28, 15, 4},
    {30, 4, 25, 12},   {8, -3, 20, 8},    {1, 0, 10, 8},     {0, 0, 19, 15},
    {1, 2, 35, 28},    {-14, -26, 10, 8}, {11, -32, 13, 10}, {50, -21, 10, 8},
    {50, -15, 19, 6},  {36, -9, 15, 8},   {-23, -4, 8, 4},   {-23, -7, 10, 8},
    {0, -14, 10, 8},   {40, -5, 10, 8},   {40, 2, 19, 6},    {29, 8, 15, 8},
    {-33, 14, 8, 4},   {26, 2, 20, 12},   {36, 19, 16, 8},   {14, 18, 19, 8},
    {-24, -28, 10, 8}, {-5, -34, 10, 8},  {38, -18, 13, 10}, {41, -15, 19, 6},
    {26, -9, 15, 8},   {-26, -4, 8, 4},   {33, -4, 25, 22},  {41, 8, 19, 8},
    {13, -3, 20, 8}};

u16* DAT_060D6584[7] = {DAT_060D6420, DAT_060D6420, DAT_060D643C, DAT_060D6458,
                        DAT_060D6474, DAT_060D6490, DAT_060D64A6};

WeaponAnimation DAT_060D65A0[1] = {
    {(u16**)DAT_060D6584, (s8*)DAT_060D64D0, 0x0005, 0x0689, 0x40, 0x03, 0},
};

SaturnSpriteImage DAT_060D65B0[6] = {
    {12, 8, 0x0000}, {20, 7, 0x0018},  {16, 4, 0x003C},
    {12, 6, 0x004C}, {24, 15, 0x0060}, {0, 0, 0x00BC},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
} DAT_060D65C8 = {
    0x0001,
    {
        {0xAD82, 0x9484, 0x8000, 0x8449, 0xA570, 0xBA33, 0x948F, 0xB0D3, 0xA17A,
         0x9EBA, 0x8842, 0x98C6, 0xA94A, 0xC1EF, 0xD694, 0xEF59},
    },
};

SaturnSpriteFrameHeader DAT_060D65EA = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D65EE = {
    {0x0100, 0x0000},
    {
        {0x0010, -12, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D65FA = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -28, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6606 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -28, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6612 = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, -20, 0},
    },
};

SaturnSpriteFrame1 DAT_060D661E = {
    {0x0100, 0x0000},
    {
        {0x0000, 54, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D662A = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, -10, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6636 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6642 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D664E = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D665A = {
    {0x0100, 0x0000},
    {
        {0x0010, -11, -2, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6666 = {
    {0x0100, 0x0000},
    {
        {0x0010, -13, -3, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6672 = {
    {0x0100, 0x0000},
    {
        {0x0010, -14, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D667E = {
    {0x0100, 0x0000},
    {
        {0x0010, -15, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D668A = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6696 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66A2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -12, 1},
    },
};

SaturnSpriteFrame1 DAT_060D66AE = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66BA = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66C6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, 7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66D2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66DE = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66EA = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66F6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6702 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, 15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D670E = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, 22, 3},
    },
};

SaturnSpriteFrame1 DAT_060D671A = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 22, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6726 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 20, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6732 = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 18, 3},
    },
};

SaturnSpriteFrame1 DAT_060D673E = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, 15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D674A = {
    {0x0100, 0x0000},
    {
        {0x0010, -19, 15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6756 = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6762 = {
    {0x0100, 0x0000},
    {
        {0x0010, -21, 13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D676E = {
    {0x0100, 0x0000},
    {
        {0x0010, -22, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D677A = {
    {0x0100, 0x0000},
    {
        {0x0010, -15, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6786 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6792 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, -31, 1},
    },
};

SaturnSpriteFrame1 DAT_060D679E = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D67AA = {
    {0x0100, 0x0000},
    {
        {0x0000, 53, -17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D67B6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D67C2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67CE = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67DA = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67E6 = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67F2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -22, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D67FE = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D680A = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -29, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6816 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, -21, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6822 = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D682E = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -11, 2},
    },
};

SaturnSpriteFrame1 DAT_060D683A = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6846 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6852 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D685E = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -8, 4},
    },
};

SaturnSpriteFrame1 DAT_060D686A = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6876 = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6882 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 2, 3},
    },
};

SaturnSpriteFrame1 DAT_060D688E = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 0, 3},
    },
};

SaturnSpriteFrame1 DAT_060D689A = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D68A6 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D68B2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -18, -4, 3},
    },
};
u16 DAT_060D68B2_tail[1] = {
    0x0000,
};

SaturnSpriteFrameHeader* DAT_060D68C0[61] = {
    (SaturnSpriteFrameHeader*)&DAT_060D65EA,
    (SaturnSpriteFrameHeader*)&DAT_060D65EE,
    (SaturnSpriteFrameHeader*)&DAT_060D65FA,
    (SaturnSpriteFrameHeader*)&DAT_060D6606,
    (SaturnSpriteFrameHeader*)&DAT_060D6612,
    (SaturnSpriteFrameHeader*)&DAT_060D661E,
    (SaturnSpriteFrameHeader*)&DAT_060D662A,
    (SaturnSpriteFrameHeader*)&DAT_060D6636,
    (SaturnSpriteFrameHeader*)&DAT_060D6642,
    (SaturnSpriteFrameHeader*)&DAT_060D664E,
    (SaturnSpriteFrameHeader*)&DAT_060D665A,
    (SaturnSpriteFrameHeader*)&DAT_060D6666,
    (SaturnSpriteFrameHeader*)&DAT_060D6672,
    (SaturnSpriteFrameHeader*)&DAT_060D667E,
    (SaturnSpriteFrameHeader*)&DAT_060D668A,
    (SaturnSpriteFrameHeader*)&DAT_060D6696,
    (SaturnSpriteFrameHeader*)&DAT_060D66A2,
    (SaturnSpriteFrameHeader*)&DAT_060D66AE,
    (SaturnSpriteFrameHeader*)&DAT_060D66BA,
    (SaturnSpriteFrameHeader*)&DAT_060D66C6,
    (SaturnSpriteFrameHeader*)&DAT_060D66D2,
    (SaturnSpriteFrameHeader*)&DAT_060D66DE,
    (SaturnSpriteFrameHeader*)&DAT_060D66EA,
    (SaturnSpriteFrameHeader*)&DAT_060D66F6,
    (SaturnSpriteFrameHeader*)&DAT_060D6702,
    (SaturnSpriteFrameHeader*)&DAT_060D670E,
    (SaturnSpriteFrameHeader*)&DAT_060D671A,
    (SaturnSpriteFrameHeader*)&DAT_060D6726,
    (SaturnSpriteFrameHeader*)&DAT_060D6732,
    (SaturnSpriteFrameHeader*)&DAT_060D673E,
    (SaturnSpriteFrameHeader*)&DAT_060D674A,
    (SaturnSpriteFrameHeader*)&DAT_060D6756,
    (SaturnSpriteFrameHeader*)&DAT_060D6762,
    (SaturnSpriteFrameHeader*)&DAT_060D676E,
    (SaturnSpriteFrameHeader*)&DAT_060D677A,
    (SaturnSpriteFrameHeader*)&DAT_060D6786,
    (SaturnSpriteFrameHeader*)&DAT_060D6792,
    (SaturnSpriteFrameHeader*)&DAT_060D679E,
    (SaturnSpriteFrameHeader*)&DAT_060D67AA,
    (SaturnSpriteFrameHeader*)&DAT_060D67B6,
    (SaturnSpriteFrameHeader*)&DAT_060D67C2,
    (SaturnSpriteFrameHeader*)&DAT_060D67CE,
    (SaturnSpriteFrameHeader*)&DAT_060D67DA,
    (SaturnSpriteFrameHeader*)&DAT_060D67E6,
    (SaturnSpriteFrameHeader*)&DAT_060D67F2,
    (SaturnSpriteFrameHeader*)&DAT_060D67FE,
    (SaturnSpriteFrameHeader*)&DAT_060D680A,
    (SaturnSpriteFrameHeader*)&DAT_060D6816,
    (SaturnSpriteFrameHeader*)&DAT_060D6822,
    (SaturnSpriteFrameHeader*)&DAT_060D682E,
    (SaturnSpriteFrameHeader*)&DAT_060D683A,
    (SaturnSpriteFrameHeader*)&DAT_060D6846,
    (SaturnSpriteFrameHeader*)&DAT_060D6852,
    (SaturnSpriteFrameHeader*)&DAT_060D685E,
    (SaturnSpriteFrameHeader*)&DAT_060D686A,
    (SaturnSpriteFrameHeader*)&DAT_060D6876,
    (SaturnSpriteFrameHeader*)&DAT_060D6882,
    (SaturnSpriteFrameHeader*)&DAT_060D688E,
    (SaturnSpriteFrameHeader*)&DAT_060D689A,
    (SaturnSpriteFrameHeader*)&DAT_060D68A6,
    (SaturnSpriteFrameHeader*)&DAT_060D68B2,
};

SaturnSpriteResource DAT_060D69B4 = {
    DAT_060D65B0, (u16*)&DAT_060D65C8, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D69C0[1] = {&DAT_060D69B4};
