// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D62F0();
void func_060D64D4();
void func_060D6794();
void func_060D67AC();
void func_060D67C4();
void func_060D67DC();
void func_060D67F4();
void func_060D6800();
void func_060D6818();
void func_060D6830();
void func_060D6848();
void func_060D6860();
void func_060D6878();
void func_060D6890();
void func_060D68A8();
void func_060D68C0();
extern SaturnSpriteResource* DAT_060D6B5C[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D62F0,
        func_060D64D4,
        func_060D6794,
        func_060D67AC,
        func_060D67C4,
        func_060D67DC,
        func_060D67F4,
        func_060D68C0,
        func_060D6800,
        func_060D6818,
        func_060D6830,
        func_060D6848,
        func_060D6860,
        func_060D6878,
        func_060D6890,
        func_060D68A8,
    },
    DAT_060D6B5C,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6134, func_060D6134);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D62F0, func_060D62F0);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D64D4, func_060D64D4);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6794, func_060D6794);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D67AC, func_060D67AC);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D67C4, func_060D67C4);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D67DC, func_060D67DC);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D67F4, func_060D67F4);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6800, func_060D6800);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6818, func_060D6818);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6830, func_060D6830);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6848, func_060D6848);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6860, func_060D6860);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6878, func_060D6878);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D6890, func_060D6890);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D68A8, func_060D68A8);
INCLUDE_ASM("asm/saturn/weapon/w_41/f_nonmat", f60D68C0, func_060D68C0);

u32 DAT_060D68D0[45] = {
    0x00040201, 0x00010402, 0x00010603, 0x0001120A, 0x00010804, 0x00010A05,
    0x00040C06, 0x00020A07, 0x00020E08, 0x00021009, 0x0001120A, 0x00020603,
    0x00020402, 0x00000000, 0x0002160C, 0x0001160D, 0x0002160E, 0x0001160F,
    0x00011610, 0x00011611, 0x00011612, 0x0001160E, 0x0001160D, 0xFFFF0000,
    0x0080000B, 0xFFFF0000, 0x00000000, 0x00FA080D, 0x00FB080A, 0x00FE0807,
    0x00040808, 0x0007080C, 0x0008080E, 0x0006080B, 0x00040809, 0x00020806,
    0x00000403, 0xB1C10000, 0x00011800, 0x00007800, 0x00016800, 0x0000C800,
    0xFFFCC000, 0xFFFD0000, 0xFFFC8000,
};

SaturnSpriteImage DAT_060D6984[16] = {
    {12, 15, 0x0000}, {12, 12, 0x0030}, {12, 8, 0x0054},  {12, 8, 0x006C},
    {12, 11, 0x0084}, {12, 14, 0x00A8}, {12, 13, 0x00D4}, {12, 12, 0x00FC},
    {12, 9, 0x0120},  {12, 4, 0x013C},  {4, 4, 0x0148},   {8, 7, 0x014C},
    {12, 10, 0x015C}, {20, 15, 0x017C}, {40, 30, 0x01C8}, {0, 0, 0x02F4},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D69C4 = {
    0x0003,
    {
        {0x99E0, 0x8C63, 0x94A5, 0x9CE7, 0xA108, 0xAD6B, 0xB9CE, 0xC210, 0x839C,
         0x8428, 0x8431, 0x8436, 0x843D, 0x992D, 0xADD0, 0xC039},
        {0x80E0, 0x9C65, 0xA065, 0xA886, 0xB0A7, 0xB4C8, 0xBCE9, 0xC50A, 0xCD2B,
         0xD58C, 0xDE0E, 0xE670, 0xEEF1, 0xF753, 0xFFD5, 0xFFFF},
        {0x8080, 0xA4C6, 0xA8E7, 0xAD29, 0xB16B, 0xB5AD, 0xB9CE, 0xBDEF, 0xC210,
         0xC631, 0xCA52, 0xCE73, 0xD294, 0xD6B5, 0xDAD6, 0xE2F6},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6A28 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6A2C = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -13, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6A38 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -11, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A44 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6A50 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A5C = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A68 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 3, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6A74 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 2, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6A80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 1, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6A8C = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -2, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6A98 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -5, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6AA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, -5, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6AB0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 1, -5, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6ABC = {
    {0x0100, 0x0000},
    {
        {0x0100, 1, -5, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6AC8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, -5, 13},
    },
};

SaturnSpriteFrame1 DAT_060D6AD4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 3, -6, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6AE0 = {
    {0x0100, 0x0000},
    {
        {0x0210, -2, -6, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6AEC = {
    {0x0100, 0x0000},
    {
        {0x0230, -2, -5, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6AF8 = {
    {0x0100, 0x0000},
    {
        {0x0220, 3, -5, 14},
    },
};

SaturnSpriteFrameHeader* DAT_060D6B04[19] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6A28,
    (SaturnSpriteFrameHeader*)&DAT_060D6A2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A38,
    (SaturnSpriteFrameHeader*)&DAT_060D6A44,
    (SaturnSpriteFrameHeader*)&DAT_060D6A50,
    (SaturnSpriteFrameHeader*)&DAT_060D6A5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A68,
    (SaturnSpriteFrameHeader*)&DAT_060D6A74,
    (SaturnSpriteFrameHeader*)&DAT_060D6A80,
    (SaturnSpriteFrameHeader*)&DAT_060D6A8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A98,
    (SaturnSpriteFrameHeader*)&DAT_060D6AA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6AB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6ABC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6AE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6AEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AF8,
};

SaturnSpriteResource DAT_060D6B50 = {
    DAT_060D6984, (u16*)&DAT_060D69C4, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6B5C[1] = {&DAT_060D6B50};
