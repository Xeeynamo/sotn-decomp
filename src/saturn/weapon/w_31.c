// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6308();
void func_060D6320();
void func_060D6338();
void func_060D6350();
void func_060D6368();
void func_060D6380();
void func_060D638C();
void func_060D63A4();
void func_060D63BC();
void func_060D63D4();
void func_060D63EC();
void func_060D6404();
void func_060D641C();
void func_060D6434();
void func_060D644C();
extern SaturnSpriteResource* DAT_060D6984[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6308,
        func_060D6320,
        func_060D6338,
        func_060D6350,
        func_060D6368,
        func_060D6380,
        func_060D644C,
        func_060D638C,
        func_060D63A4,
        func_060D63BC,
        func_060D63D4,
        func_060D63EC,
        func_060D6404,
        func_060D641C,
        func_060D6434,
    },
    DAT_060D6984,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x000000F8, 0x00000000, 0x00000000, 0x00000000,
    0x00000020, 0x2E746578, 0x74000000};

INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6308, func_060D6308);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6320, func_060D6320);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6338, func_060D6338);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6350, func_060D6350);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6368, func_060D6368);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6380, func_060D6380);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D638C, func_060D638C);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D63A4, func_060D63A4);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D63BC, func_060D63BC);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D63D4, func_060D63D4);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D63EC, func_060D63EC);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6404, func_060D6404);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D641C, func_060D641C);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D6434, func_060D6434);
INCLUDE_ASM("asm/saturn/weapon/w_31/f_nonmat", f60D644C, func_060D644C);

u16 DAT_060D6460[9] = {
    0x0201, 0x0402, 0x0603, 0x0605, 0x0603, 0x0402, 0x0804, 0x0A06, 0xFFFF};

u16 DAT_060D6472[8] = {
    0x0C07, 0x1009, 0x120A, 0x120B, 0x120A, 0x1009, 0x0E08, 0xFFFF};

u16 DAT_060D6482[6] = {0x140C, 0x160D, 0x160E, 0x160D, 0x140C, 0xFFFF};

u16 DAT_060D648E[4] = {0x180F, 0x1A10, 0x180F, 0xFFFF};

u16 DAT_060D6496[10] = {0x1C11, 0x1E12, 0x1E13, 0x0A14, 0x0A15,
                        0x0A16, 0x0A17, 0x0A18, 0x0A19, 0xFFFF};

u16 DAT_060D64AA[10] = {0x201A, 0x221B, 0x221C, 0x221D, 0x0A1E,
                        0x0A23, 0x0A24, 0x0A25, 0x0A26, 0xFFFF};

u16 DAT_060D64BE[10] = {0x201A, 0x241F, 0x2620, 0x2621, 0x0A22,
                        0x0A23, 0x0A24, 0x0A25, 0x0A26, 0xFFFF};

u16 DAT_060D64D2[7] = {0x2827, 0x2A28, 0x2A29, 0x2A2A, 0x0A2B, 0x0A2C, 0xFFFF};

u16 DAT_060D64E0[7] = {0x2C2D, 0x2E2E, 0x2E2F, 0x2E30, 0x0A31, 0x0A36, 0xFFFF};

u16 DAT_060D64EE[7] = {0x2C2D, 0x3032, 0x3233, 0x3434, 0x0A35, 0x0A36, 0xFFFF};

s8 DAT_060D64FC[27][4] = {
    {0, 0, 0, 0},     {15, -15, 10, 8}, {21, -15, 15, 5}, {25, -13, 26, 4},
    {20, -12, 6, 4},  {-40, -31, 0, 0}, {8, 3, 10, 8},    {10, 6, 6, 4},
    {14, 3, 14, 5},   {16, 4, 26, 4},   {18, -15, 18, 5}, {26, -12, 26, 8},
    {9, -9, 14, 9},   {24, 1, 15, 13},  {-11, -15, 5, 4}, {27, -14, 28, 4},
    {-19, 1, 8, 4},   {14, 3, 28, 4},   {10, 11, 19, 7},  {16, 18, 21, 5},
    {-14, -17, 8, 4}, {23, -16, 26, 7}, {-25, -19, 6, 4}, {18, -14, 26, 7},
    {19, -2, 23, 12}, {26, 0, 19, 11},  {15, 1, 19, 4}};

u16* DAT_060D6568[7] = {DAT_060D6460, DAT_060D6460, DAT_060D6472, DAT_060D6472,
                        DAT_060D6482, DAT_060D648E, DAT_060D648E};

u16* DAT_060D6584[7] = {DAT_060D6496, DAT_060D6496, DAT_060D64AA, DAT_060D64BE,
                        DAT_060D64D2, DAT_060D64E0, DAT_060D64EE};

WeaponAnimation DAT_060D65A0[2] = {
    {(u16**)DAT_060D6568, (s8*)DAT_060D64FC, 0x0000, 0x060B, 0x69, 0x02, 0},
    {(u16**)DAT_060D6584, (s8*)DAT_060D64FC, 0x0000, 0x060B, 0x70, 0x03, 0},
};

SaturnSpriteImage DAT_060D65C0[11] = {
    {8, 4, 0x0000},  {8, 3, 0x0008},  {8, 2, 0x0010},  {16, 2, 0x0014},
    {8, 3, 0x001C},  {24, 1, 0x0024}, {20, 3, 0x002C}, {4, 2, 0x003C},
    {20, 8, 0x0040}, {20, 5, 0x0068}, {0, 0, 0x0084},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D65EC = {
    0x0001,
    {
        {0x81A0, 0x8421, 0x98C6, 0xAD6B, 0xC210, 0xD6B5, 0xEB5A, 0xFFFF, 0xFC42,
         0x9084, 0x90EB, 0x8173, 0x9218, 0x9EDF, 0x98DF, 0x93A4},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6610 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6614 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -19, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6620 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D662C = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6638 = {
    {0x0100, 0x0000},
    {
        {0x0020, 21, -11, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6644 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6650 = {
    {0x0100, 0x0000},
    {
        {0x0010, 8, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D665C = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6668 = {
    {0x0100, 0x0000},
    {
        {0x0020, 12, 5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6674 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6680 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 6, 2},
    },
};

SaturnSpriteFrame1 DAT_060D668C = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, 6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6698 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66A4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, -11, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66B0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, -11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66BC = {
    {0x0100, 0x0000},
    {
        {0x0010, 9, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66C8 = {
    {0x0100, 0x0000},
    {
        {0x0010, 33, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D66D4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -16, 4},
    },
};

SaturnSpriteFrame1 DAT_060D66E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D66EC = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -11, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6704 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6710 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D671C = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6728 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6734 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6740 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D674C = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6758 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6764 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 6, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6770 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D677C = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 12, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6788 = {
    {0x0100, 0x0000},
    {
        {0x0010, 23, 19, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6794 = {
    {0x0100, 0x0000},
    {
        {0x0010, 17, 18, 6},
    },
};

SaturnSpriteFrame1 DAT_060D67A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, 14, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67AC = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, 10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67C4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67D0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67DC = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -18, 4},
    },
};

SaturnSpriteFrame1 DAT_060D67E8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -15, 5},
    },
};

SaturnSpriteFrame1 DAT_060D67F4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6800 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -13, 6},
    },
};

SaturnSpriteFrame1 DAT_060D680C = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6818 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6824 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, -19, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6830 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D683C = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6848 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -11, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6854 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6860 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, 1, 8},
    },
};

SaturnSpriteFrame1 DAT_060D686C = {
    {0x0100, 0x0000},
    {
        {0x0010, 30, 7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6878 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 1, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6884 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6890 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -9, 7},
    },
};

SaturnSpriteFrameHeader* DAT_060D689C[55] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6610,
    (SaturnSpriteFrameHeader*)&DAT_060D6614,
    (SaturnSpriteFrameHeader*)&DAT_060D6620,
    (SaturnSpriteFrameHeader*)&DAT_060D662C,
    (SaturnSpriteFrameHeader*)&DAT_060D6638,
    (SaturnSpriteFrameHeader*)&DAT_060D6644,
    (SaturnSpriteFrameHeader*)&DAT_060D6650,
    (SaturnSpriteFrameHeader*)&DAT_060D665C,
    (SaturnSpriteFrameHeader*)&DAT_060D6668,
    (SaturnSpriteFrameHeader*)&DAT_060D6674,
    (SaturnSpriteFrameHeader*)&DAT_060D6680,
    (SaturnSpriteFrameHeader*)&DAT_060D668C,
    (SaturnSpriteFrameHeader*)&DAT_060D6698,
    (SaturnSpriteFrameHeader*)&DAT_060D66A4,
    (SaturnSpriteFrameHeader*)&DAT_060D66B0,
    (SaturnSpriteFrameHeader*)&DAT_060D66BC,
    (SaturnSpriteFrameHeader*)&DAT_060D66C8,
    (SaturnSpriteFrameHeader*)&DAT_060D66D4,
    (SaturnSpriteFrameHeader*)&DAT_060D66E0,
    (SaturnSpriteFrameHeader*)&DAT_060D66EC,
    (SaturnSpriteFrameHeader*)&DAT_060D66F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6704,
    (SaturnSpriteFrameHeader*)&DAT_060D6710,
    (SaturnSpriteFrameHeader*)&DAT_060D671C,
    (SaturnSpriteFrameHeader*)&DAT_060D6728,
    (SaturnSpriteFrameHeader*)&DAT_060D6734,
    (SaturnSpriteFrameHeader*)&DAT_060D6740,
    (SaturnSpriteFrameHeader*)&DAT_060D674C,
    (SaturnSpriteFrameHeader*)&DAT_060D6758,
    (SaturnSpriteFrameHeader*)&DAT_060D6764,
    (SaturnSpriteFrameHeader*)&DAT_060D6770,
    (SaturnSpriteFrameHeader*)&DAT_060D677C,
    (SaturnSpriteFrameHeader*)&DAT_060D6788,
    (SaturnSpriteFrameHeader*)&DAT_060D6794,
    (SaturnSpriteFrameHeader*)&DAT_060D67A0,
    (SaturnSpriteFrameHeader*)&DAT_060D67AC,
    (SaturnSpriteFrameHeader*)&DAT_060D67B8,
    (SaturnSpriteFrameHeader*)&DAT_060D67C4,
    (SaturnSpriteFrameHeader*)&DAT_060D67D0,
    (SaturnSpriteFrameHeader*)&DAT_060D67DC,
    (SaturnSpriteFrameHeader*)&DAT_060D67E8,
    (SaturnSpriteFrameHeader*)&DAT_060D67F4,
    (SaturnSpriteFrameHeader*)&DAT_060D6800,
    (SaturnSpriteFrameHeader*)&DAT_060D680C,
    (SaturnSpriteFrameHeader*)&DAT_060D6818,
    (SaturnSpriteFrameHeader*)&DAT_060D6824,
    (SaturnSpriteFrameHeader*)&DAT_060D6830,
    (SaturnSpriteFrameHeader*)&DAT_060D683C,
    (SaturnSpriteFrameHeader*)&DAT_060D6848,
    (SaturnSpriteFrameHeader*)&DAT_060D6854,
    (SaturnSpriteFrameHeader*)&DAT_060D6860,
    (SaturnSpriteFrameHeader*)&DAT_060D686C,
    (SaturnSpriteFrameHeader*)&DAT_060D6878,
    (SaturnSpriteFrameHeader*)&DAT_060D6884,
    (SaturnSpriteFrameHeader*)&DAT_060D6890,
};

SaturnSpriteResource DAT_060D6978 = {
    DAT_060D65C0, (u16*)&DAT_060D65EC, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6984[1] = {&DAT_060D6978};
