// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62B4();
void func_060D6424();
void func_060D643C();
void func_060D6454();
void func_060D646C();
void func_060D6484();
void func_060D6490();
void func_060D64A8();
void func_060D64C0();
void func_060D64D8();
void func_060D64F0();
void func_060D6508();
void func_060D6520();
void func_060D6538();
void func_060D6550();
extern SaturnSpriteResource* DAT_060D6964[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62B4,
        func_060D6424,
        func_060D643C,
        func_060D6454,
        func_060D646C,
        func_060D6484,
        func_060D6550,
        func_060D6490,
        func_060D64A8,
        func_060D64C0,
        func_060D64D8,
        func_060D64F0,
        func_060D6508,
        func_060D6520,
        func_060D6538,
    },
    DAT_060D6964,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x000000F8, 0x00000000, 0x00000000, 0x00000000,
    0x00000020, 0x2E746578, 0x74000000};

INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D62B4, func_060D62B4);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6424, func_060D6424);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D643C, func_060D643C);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6454, func_060D6454);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D646C, func_060D646C);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6484, func_060D6484);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6490, func_060D6490);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D64A8, func_060D64A8);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D64C0, func_060D64C0);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D64D8, func_060D64D8);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D64F0, func_060D64F0);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6508, func_060D6508);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6520, func_060D6520);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6538, func_060D6538);
INCLUDE_ASM("asm/saturn/weapon/w_22/f_nonmat", f60D6550, func_060D6550);

u32 DAT_060D6560[42] = {
    0x00020001, 0x00020002, 0x00020003, 0x00020004, 0x00020005, 0x00020006,
    0xFFFF0000, 0x00010007, 0x00010008, 0x00010009, 0x0003000A, 0x00010008,
    0x0001000B, 0x0002000C, 0x0002000D, 0x0002000E, 0x0002000F, 0x00020010,
    0x00020011, 0x00020012, 0x00020013, 0x00020014, 0x00020015, 0x00020016,
    0x00030017, 0x00040018, 0x0002001D, 0x000F0019, 0x0001001A, 0x0001001B,
    0x0001001A, 0x0001001B, 0x0002001A, 0x0002001B, 0x0002001A, 0x0003001B,
    0x0003001A, 0x0004001B, 0x0005001A, 0xFFFF0000, 0x0002001C, 0x00000000,
};

SaturnSpriteImage DAT_060D6608[29] = {
    {20, 12, 0x0000}, {16, 14, 0x003C}, {16, 18, 0x0074}, {20, 23, 0x00BC},
    {20, 28, 0x0130}, {20, 29, 0x01BC}, {12, 8, 0x0250},  {24, 17, 0x0268},
    {36, 26, 0x02D0}, {40, 31, 0x03BC}, {4, 3, 0x04F4},   {8, 10, 0x04F8},
    {4, 12, 0x050C},  {8, 14, 0x0518},  {8, 21, 0x0534},  {8, 28, 0x0560},
    {8, 29, 0x0598},  {8, 30, 0x05D4},  {8, 31, 0x0610},  {8, 15, 0x0650},
    {12, 2, 0x0670},  {8, 15, 0x0678},  {16, 2, 0x0698},  {12, 15, 0x06A0},
    {12, 14, 0x06D0}, {16, 14, 0x06FC}, {16, 13, 0x0734}, {8, 15, 0x0768},
    {0, 0, 0x0788},
};

struct {
    u16 countAndFlags;
    u16 colors[4][16];
    u16 padding[1];
} DAT_060D667C = {
    0x0004,
    {
        {0x8541, 0x8537, 0x8557, 0x8998, 0x8DB9, 0x91F9, 0x961A, 0x9A5B, 0x9E9C,
         0xA6FD, 0xAF3D, 0xBB7E, 0xCB9E, 0xDBDE, 0xEFDE, 0xFFFF},
        {0xA901, 0x8515, 0x8537, 0x8559, 0x897B, 0x899D, 0x8DDF, 0x963F, 0x9E9F,
         0xA6BF, 0xAEFF, 0xB73F, 0xBF5F, 0xC79F, 0xCFDF, 0xD7FF},
        {0xA00A, 0x8842, 0xA94A, 0xE2D6, 0xF318, 0x9171, 0xFC00, 0x855A, 0x8DDF,
         0x963F, 0x9E9F, 0xAB1F, 0xB77F, 0xC3FF, 0xE3FF, 0xFFFF},
        {0x9800, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xC3FF, 0xCBFF,
         0xD3FF, 0xDBFF, 0xE3FF, 0xE7FF, 0xEFFF, 0xF7FF, 0xFFFF},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6700 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6704 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6710 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, 0, 1},
    },
};

SaturnSpriteFrame1 DAT_060D671C = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 1, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6728 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6734 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6740 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D674C = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 1, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6758 = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 1, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6764 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6770 = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 1, 9},
    },
};

SaturnSpriteFrame1 DAT_060D677C = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 0, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6788 = {
    {0x0100, 0x0000},
    {
        {0x0200, 3, -6, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6794 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, -6, 12},
    },
};

SaturnSpriteFrame1 DAT_060D67A0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -4, 13},
    },
};

SaturnSpriteFrame1 DAT_060D67AC = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -9, 14},
    },
};

SaturnSpriteFrame1 DAT_060D67B8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -15, 15},
    },
};

SaturnSpriteFrame1 DAT_060D67C4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -11, 16},
    },
};

SaturnSpriteFrame1 DAT_060D67D0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, -9, 17},
    },
};

SaturnSpriteFrame1 DAT_060D67DC = {
    {0x0100, 0x0000},
    {
        {0x0200, 5, -7, 18},
    },
};

SaturnSpriteFrame3 DAT_060D67E8 = {
    {0x0300, 0x0000},
    {
        {0x0200, 3, -21, 19},
        {0x0220, 3, 9, 19},
        {0x0220, 9, -7, 20},
    },
};

SaturnSpriteFrame3 DAT_060D6804 = {
    {0x0300, 0x0000},
    {
        {0x0200, 1, -17, 21},
        {0x0220, 1, 10, 21},
        {0x0220, 10, -4, 22},
    },
};

SaturnSpriteFrame3 DAT_060D6820 = {
    {0x0300, 0x0000},
    {
        {0x0220, 2, 11, 23},
        {0x0200, 2, -17, 23},
        {0x0220, 7, -4, 22},
    },
};

SaturnSpriteFrame3 DAT_060D683C = {
    {0x0300, 0x0000},
    {
        {0x0200, 1, -15, 24},
        {0x0220, 1, 13, 24},
        {0x0220, 6, -2, 22},
    },
};

SaturnSpriteFrame3 DAT_060D6858 = {
    {0x0300, 0x0000},
    {
        {0x0200, 3, -12, 25},
        {0x0220, 3, 14, 25},
        {0x0220, 4, 0, 22},
    },
};

SaturnSpriteFrame3 DAT_060D6874 = {
    {0x0300, 0x0000},
    {
        {0x0200, 0, -12, 26},
        {0x0220, 0, 14, 26},
        {0x0220, 1, 0, 22},
    },
};

SaturnSpriteFrame2 DAT_060D6890 = {
    {0x0200, 0x0000},
    {
        {0x0200, 9, -15, 19},
        {0x0220, 9, 15, 19},
    },
};

SaturnSpriteFrame2 DAT_060D68A4 = {
    {0x0200, 0x0000},
    {
        {0x0200, 10, -15, 27},
        {0x0220, 10, 15, 27},
    },
};

SaturnSpriteFrame1 DAT_060D68B8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 2, 1, 22},
    },
};

SaturnSpriteFrame3 DAT_060D68C4 = {
    {0x0300, 0x0000},
    {
        {0x0300, 0, -12, 26},
        {0x0320, 0, 14, 26},
        {0x0320, 1, 0, 22},
    },
};

SaturnSpriteFrameHeader* DAT_060D68E0[30] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6700,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6804,
    (SaturnSpriteFrameHeader*)&DAT_060D6820,
    (SaturnSpriteFrameHeader*)&DAT_060D683C,
    (SaturnSpriteFrameHeader*)&DAT_060D6858,
    (SaturnSpriteFrameHeader*)&DAT_060D6874,
    (SaturnSpriteFrameHeader*)&DAT_060D6890,
    (SaturnSpriteFrameHeader*)&DAT_060D68A4,
    (SaturnSpriteFrameHeader*)&DAT_060D68B8,
    (SaturnSpriteFrameHeader*)&DAT_060D68C4,
};

SaturnSpriteResource DAT_060D6958 = {
    DAT_060D6608, (u16*)&DAT_060D667C, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6964[1] = {&DAT_060D6958};
