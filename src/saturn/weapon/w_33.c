// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62E4();
void func_060D62FC();
void func_060D6314();
void func_060D632C();
void func_060D6344();
void func_060D635C();
void func_060D6368();
void func_060D6380();
void func_060D6398();
void func_060D63B0();
void func_060D63C8();
void func_060D63E0();
void func_060D63F8();
void func_060D6410();
void func_060D6428();
extern SaturnSpriteResource* DAT_060D6AA0[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62E4,
        func_060D62FC,
        func_060D6314,
        func_060D632C,
        func_060D6344,
        func_060D635C,
        func_060D6428,
        func_060D6368,
        func_060D6380,
        func_060D6398,
        func_060D63B0,
        func_060D63C8,
        func_060D63E0,
        func_060D63F8,
        func_060D6410,
    },
    DAT_060D6AA0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D62E4, func_060D62E4);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D62FC, func_060D62FC);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6314, func_060D6314);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D632C, func_060D632C);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6344, func_060D6344);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D635C, func_060D635C);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6368, func_060D6368);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6380, func_060D6380);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6398, func_060D6398);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D63B0, func_060D63B0);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D63C8, func_060D63C8);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D63E0, func_060D63E0);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D63F8, func_060D63F8);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6410, func_060D6410);
INCLUDE_ASM("asm/saturn/weapon/w_33/f_nonmat", f60D6428, func_060D6428);

u16 DAT_060D6440[19] = {0x0201, 0x0402, 0x0403, 0x0604, 0x0805, 0x0A06, 0x0407,
                        0x0408, 0x1411, 0x1412, 0x1613, 0x1614, 0x1615, 0x1816,
                        0x1817, 0x1818, 0x1819, 0x181A, 0xFFFF};

u16 DAT_060D6466[19] = {0x0C09, 0x0E0A, 0x0E0B, 0x100C, 0x120D, 0x0E0E, 0x0E0F,
                        0x0E10, 0x1A1B, 0x1A1C, 0x1C1D, 0x1E1E, 0x201F, 0x1820,
                        0x1821, 0x1822, 0x1823, 0x1824, 0xFFFF};

u16 DAT_060D648C[8] = {
    0x2225, 0x2226, 0x2427, 0x2428, 0x2429, 0x182A, 0x182B, 0xFFFF};

u16 DAT_060D649C[8] = {
    0x262C, 0x262D, 0x282E, 0x282F, 0x2A30, 0x1831, 0x1836, 0xFFFF};

u16 DAT_060D64AC[8] = {
    0x262C, 0x2C32, 0x2E33, 0x3034, 0x1835, 0x1836, 0xFFFF, 0x0000};

s8 DAT_060D64BC[25][4] = {
    {0, 0, 0, 0},     {16, -13, 13, 7}, {20, -12, 16, 8}, {36, -17, 14, 7},
    {28, -11, 25, 5}, {21, -11, 19, 5}, {10, 6, 10, 8},   {13, 5, 16, 8},
    {26, 1, 15, 8},   {19, 7, 25, 5},   {-6, -20, 5, 4},  {26, -13, 28, 4},
    {-40, -31, 0, 0}, {-15, -1, 5, 4},  {10, 11, 19, 7},  {19, 19, 13, 7},
    {14, 17, 19, 4},  {-9, -22, 5, 4},  {26, -15, 26, 6}, {-23, -24, 5, 4},
    {16, -15, 30, 7}, {18, -12, 24, 3}, {19, -2, 23, 12}, {30, 4, 19, 11},
    {15, 1, 19, 4}};

u16* DAT_060D6520[7] = {DAT_060D6440, DAT_060D6440, DAT_060D6466, DAT_060D6466,
                        DAT_060D648C, DAT_060D649C, DAT_060D64AC};

WeaponAnimation DAT_060D653C[1] = {
    {(u16**)DAT_060D6520, (s8*)DAT_060D64BC, 0x0000, 0x0640, 0x85, 0x04, 0},
};

SaturnSpriteImage DAT_060D654C[19] = {
    {8, 6, 0x0000},   {8, 5, 0x000C},  {16, 7, 0x0018}, {12, 3, 0x0034},
    {12, 3, 0x0040},  {12, 2, 0x004C}, {12, 7, 0x0054}, {8, 4, 0x006C},
    {24, 3, 0x0074},  {20, 3, 0x0088}, {8, 4, 0x0098},  {8, 3, 0x00A0},
    {4, 2, 0x00A8},   {20, 8, 0x00AC}, {12, 5, 0x00D4}, {16, 3, 0x00E4},
    {20, 10, 0x00F0}, {20, 5, 0x0124}, {0, 0, 0x0140},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D6598 = {
    0x0001,
    {
        {0x81A0, 0x8421, 0x98C6, 0xAD6B, 0xC210, 0xD6B5, 0xEB5A, 0xFFFF, 0xFC42,
         0x9084, 0x90EB, 0x8173, 0x9218, 0x9EDF, 0x98DF, 0x93A4},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D65BC = {0x0000, 0x0000};

SaturnSpriteFrame2 DAT_060D65C0 = {
    {0x0200, 0x0000},
    {
        {0x0010, 18, -12, 0},
        {0x0000, -2, -9, 1},
    },
};

SaturnSpriteFrame2 DAT_060D65D4 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -9, 1},
        {0x0000, 21, -12, 0},
    },
};

SaturnSpriteFrame2 DAT_060D65E8 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -9, 1},
        {0x0010, 27, -16, 0},
    },
};

SaturnSpriteFrame2 DAT_060D65FC = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -9, 1},
        {0x0000, 37, -17, 2},
    },
};

SaturnSpriteFrame2 DAT_060D6610 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -9, 1},
        {0x0000, 41, -12, 3},
    },
};

SaturnSpriteFrame2 DAT_060D6624 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -9, 1},
        {0x0000, 33, -12, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6638 = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -9, 1},
        {0x0010, 26, -11, 0},
    },
};

SaturnSpriteFrame2 DAT_060D664C = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -9, 1},
        {0x0000, 26, -16, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6660 = {
    {0x0200, 0x0000},
    {
        {0x0000, -9, 7, 1},
        {0x0010, 12, 6, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6674 = {
    {0x0200, 0x0000},
    {
        {0x0000, -9, 6, 1},
        {0x0000, 13, 6, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6688 = {
    {0x0200, 0x0000},
    {
        {0x0010, 20, 1, 0},
        {0x0000, -9, 6, 1},
    },
};

SaturnSpriteFrame2 DAT_060D669C = {
    {0x0200, 0x0000},
    {
        {0x0000, 29, 0, 2},
        {0x0000, -9, 6, 1},
    },
};

SaturnSpriteFrame2 DAT_060D66B0 = {
    {0x0200, 0x0000},
    {
        {0x0000, -9, 6, 1},
        {0x0000, 30, 6, 3},
    },
};

SaturnSpriteFrame2 DAT_060D66C4 = {
    {0x0200, 0x0000},
    {
        {0x0000, -9, 6, 1},
        {0x0000, 23, 6, 4},
    },
};

SaturnSpriteFrame2 DAT_060D66D8 = {
    {0x0200, 0x0000},
    {
        {0x0000, -9, 6, 1},
        {0x0010, 20, 6, 0},
    },
};

SaturnSpriteFrame2 DAT_060D66EC = {
    {0x0200, 0x0000},
    {
        {0x0000, -9, 7, 1},
        {0x0000, 20, 2, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6700 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -23, 6},
    },
};

SaturnSpriteFrame1 DAT_060D670C = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -21, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6718 = {
    {0x0200, 0x0000},
    {
        {0x0020, 3, -15, 4},
        {0x0004, 22, -13, 8},
    },
};

SaturnSpriteFrame2 DAT_060D672C = {
    {0x0200, 0x0000},
    {
        {0x0000, 38, -13, 3},
        {0x0020, 3, -15, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6740 = {
    {0x0200, 0x0000},
    {
        {0x0000, 27, -12, 9},
        {0x0000, 16, -4, 10},
    },
};

SaturnSpriteFrame2 DAT_060D6754 = {
    {0x0200, 0x0000},
    {
        {0x0000, 14, -3, 10},
        {0x0000, 3, -7, 11},
    },
};

SaturnSpriteFrame2 DAT_060D6768 = {
    {0x0200, 0x0000},
    {
        {0x0000, -1, -7, 11},
        {0x0000, 16, -1, 10},
    },
};

SaturnSpriteFrame2 DAT_060D677C = {
    {0x0200, 0x0000},
    {
        {0x0000, -2, -6, 11},
        {0x0000, 16, -1, 10},
    },
};

SaturnSpriteFrame2 DAT_060D6790 = {
    {0x0200, 0x0000},
    {
        {0x0000, -3, -5, 11},
        {0x0000, 16, 0, 10},
    },
};

SaturnSpriteFrame2 DAT_060D67A4 = {
    {0x0200, 0x0000},
    {
        {0x0000, -3, -5, 11},
        {0x0000, 16, 0, 10},
    },
};

SaturnSpriteFrame1 DAT_060D67B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -5, 6},
    },
};

SaturnSpriteFrame1 DAT_060D67C4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -4, 7},
    },
};

SaturnSpriteFrame2 DAT_060D67D0 = {
    {0x0200, 0x0000},
    {
        {0x0000, -12, 4, 12},
        {0x0004, 10, 10, 13},
    },
};

SaturnSpriteFrame2 DAT_060D67E4 = {
    {0x0200, 0x0000},
    {
        {0x0000, -11, 4, 12},
        {0x0000, 29, 21, 14},
    },
};

SaturnSpriteFrame2 DAT_060D67F8 = {
    {0x0200, 0x0000},
    {
        {0x0010, 18, 18, 15},
        {0x0000, 5, 13, 10},
    },
};

SaturnSpriteFrame2 DAT_060D680C = {
    {0x0200, 0x0000},
    {
        {0x0000, -7, 14, 11},
        {0x0000, 9, 15, 10},
    },
};

SaturnSpriteFrame2 DAT_060D6820 = {
    {0x0200, 0x0000},
    {
        {0x0000, -10, 11, 11},
        {0x0000, 11, 16, 10},
    },
};

SaturnSpriteFrame2 DAT_060D6834 = {
    {0x0200, 0x0000},
    {
        {0x0000, -10, 11, 11},
        {0x0000, 11, 16, 10},
    },
};

SaturnSpriteFrame2 DAT_060D6848 = {
    {0x0200, 0x0000},
    {
        {0x0000, -11, 11, 11},
        {0x0000, 11, 17, 10},
    },
};

SaturnSpriteFrame2 DAT_060D685C = {
    {0x0200, 0x0000},
    {
        {0x0000, -11, 11, 11},
        {0x0000, 11, 17, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6870 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, -26, 6},
    },
};

SaturnSpriteFrame1 DAT_060D687C = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -23, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6888 = {
    {0x0200, 0x0000},
    {
        {0x0020, 0, -18, 4},
        {0x0004, 18, -17, 8},
    },
};

SaturnSpriteFrame2 DAT_060D689C = {
    {0x0200, 0x0000},
    {
        {0x0000, 37, -15, 3},
        {0x0020, 0, -18, 4},
    },
};

SaturnSpriteFrame2 DAT_060D68B0 = {
    {0x0200, 0x0000},
    {
        {0x0000, 24, -13, 9},
        {0x0000, 12, -7, 10},
    },
};

SaturnSpriteFrame2 DAT_060D68C4 = {
    {0x0200, 0x0000},
    {
        {0x0000, 15, -5, 10},
        {0x0000, 0, -9, 11},
    },
};

SaturnSpriteFrame2 DAT_060D68D8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 17, -4, 10},
        {0x0000, -2, -9, 11},
    },
};

SaturnSpriteFrame1 DAT_060D68EC = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, -26, 6},
    },
};

SaturnSpriteFrame1 DAT_060D68F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -22, -23, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6904 = {
    {0x0200, 0x0000},
    {
        {0x0020, -3, -16, 4},
        {0x0004, 18, -14, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6918 = {
    {0x0200, 0x0000},
    {
        {0x0000, 34, -13, 3},
        {0x0020, -3, -16, 4},
    },
};

SaturnSpriteFrame2 DAT_060D692C = {
    {0x0200, 0x0000},
    {
        {0x0000, 23, -11, 9},
        {0x0000, 10, -4, 10},
    },
};

SaturnSpriteFrame2 DAT_060D6940 = {
    {0x0200, 0x0000},
    {
        {0x0000, 10, -4, 10},
        {0x0000, -3, -6, 11},
    },
};

SaturnSpriteFrame2 DAT_060D6954 = {
    {0x0200, 0x0000},
    {
        {0x0020, -5, -10, 1},
        {0x0004, 21, -2, 16},
    },
};

SaturnSpriteFrame2 DAT_060D6968 = {
    {0x0200, 0x0000},
    {
        {0x0000, 39, 11, 14},
        {0x0020, -5, -10, 1},
    },
};

SaturnSpriteFrame2 DAT_060D697C = {
    {0x0200, 0x0000},
    {
        {0x0000, 21, 2, 17},
        {0x0000, 7, -4, 10},
    },
};

SaturnSpriteFrame2 DAT_060D6990 = {
    {0x0200, 0x0000},
    {
        {0x0000, 10, -3, 10},
        {0x0000, -7, -6, 11},
    },
};

SaturnSpriteFrame2 DAT_060D69A4 = {
    {0x0200, 0x0000},
    {
        {0x0000, -10, -4, 11},
        {0x0000, 12, -1, 10},
    },
};

SaturnSpriteFrameHeader* DAT_060D69B8[55] = {
    (SaturnSpriteFrameHeader*)&DAT_060D65BC,
    (SaturnSpriteFrameHeader*)&DAT_060D65C0,
    (SaturnSpriteFrameHeader*)&DAT_060D65D4,
    (SaturnSpriteFrameHeader*)&DAT_060D65E8,
    (SaturnSpriteFrameHeader*)&DAT_060D65FC,
    (SaturnSpriteFrameHeader*)&DAT_060D6610,
    (SaturnSpriteFrameHeader*)&DAT_060D6624,
    (SaturnSpriteFrameHeader*)&DAT_060D6638,
    (SaturnSpriteFrameHeader*)&DAT_060D664C,
    (SaturnSpriteFrameHeader*)&DAT_060D6660,
    (SaturnSpriteFrameHeader*)&DAT_060D6674,
    (SaturnSpriteFrameHeader*)&DAT_060D6688,
    (SaturnSpriteFrameHeader*)&DAT_060D669C,
    (SaturnSpriteFrameHeader*)&DAT_060D66B0,
    (SaturnSpriteFrameHeader*)&DAT_060D66C4,
    (SaturnSpriteFrameHeader*)&DAT_060D66D8,
    (SaturnSpriteFrameHeader*)&DAT_060D66EC,
    (SaturnSpriteFrameHeader*)&DAT_060D6700,
    (SaturnSpriteFrameHeader*)&DAT_060D670C,
    (SaturnSpriteFrameHeader*)&DAT_060D6718,
    (SaturnSpriteFrameHeader*)&DAT_060D672C,
    (SaturnSpriteFrameHeader*)&DAT_060D6740,
    (SaturnSpriteFrameHeader*)&DAT_060D6754,
    (SaturnSpriteFrameHeader*)&DAT_060D6768,
    (SaturnSpriteFrameHeader*)&DAT_060D677C,
    (SaturnSpriteFrameHeader*)&DAT_060D6790,
    (SaturnSpriteFrameHeader*)&DAT_060D67A4,
    (SaturnSpriteFrameHeader*)&DAT_060D67B8,
    (SaturnSpriteFrameHeader*)&DAT_060D67C4,
    (SaturnSpriteFrameHeader*)&DAT_060D67D0,
    (SaturnSpriteFrameHeader*)&DAT_060D67E4,
    (SaturnSpriteFrameHeader*)&DAT_060D67F8,
    (SaturnSpriteFrameHeader*)&DAT_060D680C,
    (SaturnSpriteFrameHeader*)&DAT_060D6820,
    (SaturnSpriteFrameHeader*)&DAT_060D6834,
    (SaturnSpriteFrameHeader*)&DAT_060D6848,
    (SaturnSpriteFrameHeader*)&DAT_060D685C,
    (SaturnSpriteFrameHeader*)&DAT_060D6870,
    (SaturnSpriteFrameHeader*)&DAT_060D687C,
    (SaturnSpriteFrameHeader*)&DAT_060D6888,
    (SaturnSpriteFrameHeader*)&DAT_060D689C,
    (SaturnSpriteFrameHeader*)&DAT_060D68B0,
    (SaturnSpriteFrameHeader*)&DAT_060D68C4,
    (SaturnSpriteFrameHeader*)&DAT_060D68D8,
    (SaturnSpriteFrameHeader*)&DAT_060D68EC,
    (SaturnSpriteFrameHeader*)&DAT_060D68F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6904,
    (SaturnSpriteFrameHeader*)&DAT_060D6918,
    (SaturnSpriteFrameHeader*)&DAT_060D692C,
    (SaturnSpriteFrameHeader*)&DAT_060D6940,
    (SaturnSpriteFrameHeader*)&DAT_060D6954,
    (SaturnSpriteFrameHeader*)&DAT_060D6968,
    (SaturnSpriteFrameHeader*)&DAT_060D697C,
    (SaturnSpriteFrameHeader*)&DAT_060D6990,
    (SaturnSpriteFrameHeader*)&DAT_060D69A4,
};

SaturnSpriteResource DAT_060D6A94 = {
    DAT_060D654C, (u16*)&DAT_060D6598, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6AA0[1] = {&DAT_060D6A94};
