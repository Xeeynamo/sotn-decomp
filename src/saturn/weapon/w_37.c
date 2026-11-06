// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6554();
void func_060D6A5C();
void func_060D6CD4();
void func_060D6CEC();
void func_060D6D04();
void func_060D6D1C();
void func_060D6D28();
void func_060D6D40();
void func_060D6D58();
void func_060D6D70();
void func_060D6D88();
void func_060D6DA0();
void func_060D6DB8();
void func_060D6DD0();
void func_060D6DE8();
extern SaturnSpriteResource* DAT_060D738C[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6554,
        func_060D6A5C,
        func_060D6CD4,
        func_060D6CEC,
        func_060D6D04,
        func_060D6D1C,
        func_060D6DE8,
        func_060D6D28,
        func_060D6D40,
        func_060D6D58,
        func_060D6D70,
        func_060D6D88,
        func_060D6DA0,
        func_060D6DB8,
        func_060D6DD0,
    },
    DAT_060D738C,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6304, func_060D6304);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6434, func_060D6434);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6554, func_060D6554);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6A5C, func_060D6A5C);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6CD4, func_060D6CD4);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6CEC, func_060D6CEC);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6D04, func_060D6D04);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6D1C, func_060D6D1C);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6D28, func_060D6D28);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6D40, func_060D6D40);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6D58, func_060D6D58);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6D70, func_060D6D70);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6D88, func_060D6D88);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6DA0, func_060D6DA0);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6DB8, func_060D6DB8);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6DD0, func_060D6DD0);
INCLUDE_ASM("asm/saturn/weapon/w_37/f_nonmat", f60D6DE8, func_060D6DE8);

u16 DAT_060D6E00[10] = {0x0201, 0x0402, 0x0403, 0x0604, 0x0605,
                        0x0606, 0x0607, 0x0608, 0x0609, 0xFFFF};

u16 DAT_060D6E14[10] = {0x080A, 0x0A0B, 0x0A0C, 0x060D, 0x060E,
                        0x0613, 0x0614, 0x0615, 0x0616, 0xFFFF};

u16 DAT_060D6E28[10] = {0x080A, 0x0C0F, 0x0E10, 0x1011, 0x0612,
                        0x0613, 0x0614, 0x0615, 0x0616, 0xFFFF};

u16 DAT_060D6E3C[7] = {0x1217, 0x1418, 0x1419, 0x061A, 0x061B, 0x061C, 0xFFFF};

u16 DAT_060D6E4A[7] = {0x161D, 0x181E, 0x181F, 0x0620, 0x0621, 0x0626, 0xFFFF};

u16 DAT_060D6E58[8] = {
    0x161D, 0x1A22, 0x1C23, 0x0624, 0x0625, 0x0626, 0xFFFF, 0x0000};

s8 DAT_060D6E68[15][4] = {
    {0, 0, 0, 0},     {4, -24, 6, 4},  {31, -13, 30, 3}, {-40, -31, 0, 0},
    {-6, -5, 6, 4},   {21, 4, 30, 3},  {9, 15, 18, 8},   {24, 21, 19, 7},
    {16, 18, 21, 5},  {-1, -25, 6, 4}, {29, -15, 30, 7}, {-11, -27, 6, 4},
    {24, -14, 30, 7}, {19, 2, 24, 10}, {36, 8, 14, 8}};

s8 DAT_060D6EA4[15][4] = {
    {0, 0, 0, 0},     {3, -24, 6, 6},   {31, -13, 35, 5}, {-40, -31, 0, 0},
    {-6, -5, 11, 6},  {21, 4, 35, 5},   {9, 15, 23, 10},  {24, 21, 24, 9},
    {16, 18, 26, 7},  {-1, -25, 11, 6}, {29, -15, 35, 9}, {-11, -27, 11, 6},
    {24, -14, 35, 9}, {19, 2, 29, 12},  {36, 8, 19, 10}};

u16* DAT_060D6EE0[7] = {DAT_060D6E00, DAT_060D6E00, DAT_060D6E14, DAT_060D6E28,
                        DAT_060D6E3C, DAT_060D6E4A, DAT_060D6E58};

WeaponAnimation DAT_060D6EFC[4] = {
    {(u16**)DAT_060D6EE0, (s8*)DAT_060D6E68, 0x0000, 0x060B, 0xA1, 0x04, 0},
    {(u16**)DAT_060D6EE0, (s8*)DAT_060D6EA4, 0x0000, 0x060B, 0xA1, 0x04, 0},
    {(u16**)DAT_060D6EE0, (s8*)DAT_060D6EA4, 0x0000, 0x060B, 0xA1, 0x04, 0},
    {(u16**)DAT_060D6EE0, (s8*)DAT_060D6E68, 0x0000, 0x060B, 0xA1, 0x04, 0},
};
u32 DAT_060D6EFC_tail[12] = {
    0x00501050, 0x00601060, 0x10502050, 0x10602060, 0x70408040, 0x70508050,
    0x70307830, 0x70387838, 0x78308030, 0x78388038, 0x70387838, 0x77407840,
};

u32 DAT_060D6F6C[41] = {
    0x0018FFF2, 0x00400000, 0x0018FFF2, 0x00400000, 0x00140002, 0x00400000,
    0x0012000E, 0x00300022, 0x0018FFF0, 0x00400000, 0x0018FFF2, 0x00400000,
    0x00180004, 0x00300022, 0x01B001B2, 0x01B401B6, 0x01B801BA, 0x00000000,
    0x00000001, 0x00000000, 0x00000001, 0x00000000, 0x00000001, 0x00000000,
    0x00000001, 0x00000000, 0x00000001, 0x00000000, 0x00000001, 0x00000000,
    0x00000001, 0x00000000, 0x00000001, 0x00040014, 0x00070015, 0x00060016,
    0x00030017, 0x00030018, 0x00060019, 0x00020015, 0x00000000,
};

SaturnSpriteImage DAT_060D7010[9] = {
    {8, 4, 0x0000},  {36, 1, 0x0008}, {12, 2, 0x0014},
    {20, 3, 0x001C}, {8, 2, 0x002C},  {32, 12, 0x0030},
    {12, 6, 0x0090}, {20, 5, 0x00A4}, {0, 0, 0x00C0},
};

struct {
    u16 countAndFlags;
    u16 colors[7][16];
    u16 padding[1];
} DAT_060D7034 = {
    0x0007,
    {
        {0x81A0, 0x8421, 0x98C6, 0xAD6B, 0xC210, 0xDEB4, 0xEF37, 0xFFFF, 0xFC42,
         0x9084, 0x90EB, 0xA173, 0xAE18, 0xC33C, 0x98DF, 0x87E1},
        {0x0000, 0xFC21, 0x8421, 0xFC21, 0xCE73, 0xF39C, 0x87FF, 0x87E1, 0x8220,
         0x8421, 0xD421, 0xFC21, 0xFD42, 0xFE48, 0xF6D1, 0xFFBD},
        {0x0000, 0x87FF, 0x8421, 0x87FF, 0xA53F, 0xBDFF, 0x87E1, 0x87E1, 0x87E1,
         0x87E1, 0x8601, 0x86A1, 0x8741, 0x87E1, 0xBBEE, 0xEFFB},
        {0x0000, 0xF39C, 0x8421, 0xF39C, 0xD281, 0xEF61, 0x87E1, 0x87E1, 0x87E1,
         0x87E1, 0x85B5, 0x867F, 0x873F, 0x87FF, 0xB7FF, 0xE7FF},
        {0x0000, 0xCB92, 0x8421, 0xCB92, 0xCE73, 0xF39C, 0x87E1, 0x87E1, 0x87E1,
         0x87E1, 0x842F, 0x8437, 0x843F, 0xA53F, 0xC63F, 0xE73F},
        {0x0000, 0xDADC, 0x8421, 0xDADC, 0x87E1, 0x87E1, 0x87E1, 0x87E1, 0x87E1,
         0x87E1, 0xBC2F, 0xD034, 0xE83A, 0xF13C, 0xF63D, 0xFF5F},
        {0x0000, 0xA108, 0x8421, 0xA108, 0x87E1, 0x87E1, 0x87E1, 0x87E1, 0x87E1,
         0x87E1, 0xA94A, 0xB9CE, 0xCA52, 0xDEF7, 0xEF7B, 0xFFFF},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D7118 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D711C = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7128 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, -13, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7134 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7140 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D714C = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -8, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7158 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7164 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7170 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D717C = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7188 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7194 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 4, 1},
    },
};

SaturnSpriteFrame1 DAT_060D71A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D71AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D71B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, 9, 4},
    },
};

SaturnSpriteFrame1 DAT_060D71C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, 12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D71D0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 21, 6},
    },
};

SaturnSpriteFrame1 DAT_060D71DC = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 15, 7},
    },
};

SaturnSpriteFrame1 DAT_060D71E8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, 10, 4},
    },
};

SaturnSpriteFrame1 DAT_060D71F4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, 10, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7200 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, 10, 4},
    },
};

SaturnSpriteFrame1 DAT_060D720C = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 10, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7218 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, 10, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7224 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7230 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D723C = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7248 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7254 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -9, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7260 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -6, 4},
    },
};

SaturnSpriteFrame1 DAT_060D726C = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7278 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -13, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7284 = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7290 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D729C = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D72A8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D72B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, 10, 6},
    },
};

SaturnSpriteFrame1 DAT_060D72C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, 4, 7},
    },
};

SaturnSpriteFrame1 DAT_060D72CC = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -5, 4},
    },
};

SaturnSpriteFrame1 DAT_060D72D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D72E4[39] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7118,
    (SaturnSpriteFrameHeader*)&DAT_060D711C,
    (SaturnSpriteFrameHeader*)&DAT_060D7128,
    (SaturnSpriteFrameHeader*)&DAT_060D7134,
    (SaturnSpriteFrameHeader*)&DAT_060D7140,
    (SaturnSpriteFrameHeader*)&DAT_060D714C,
    (SaturnSpriteFrameHeader*)&DAT_060D7158,
    (SaturnSpriteFrameHeader*)&DAT_060D7164,
    (SaturnSpriteFrameHeader*)&DAT_060D7170,
    (SaturnSpriteFrameHeader*)&DAT_060D717C,
    (SaturnSpriteFrameHeader*)&DAT_060D7188,
    (SaturnSpriteFrameHeader*)&DAT_060D7194,
    (SaturnSpriteFrameHeader*)&DAT_060D71A0,
    (SaturnSpriteFrameHeader*)&DAT_060D71AC,
    (SaturnSpriteFrameHeader*)&DAT_060D71B8,
    (SaturnSpriteFrameHeader*)&DAT_060D71C4,
    (SaturnSpriteFrameHeader*)&DAT_060D71D0,
    (SaturnSpriteFrameHeader*)&DAT_060D71DC,
    (SaturnSpriteFrameHeader*)&DAT_060D71E8,
    (SaturnSpriteFrameHeader*)&DAT_060D71F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7200,
    (SaturnSpriteFrameHeader*)&DAT_060D720C,
    (SaturnSpriteFrameHeader*)&DAT_060D7218,
    (SaturnSpriteFrameHeader*)&DAT_060D7224,
    (SaturnSpriteFrameHeader*)&DAT_060D7230,
    (SaturnSpriteFrameHeader*)&DAT_060D723C,
    (SaturnSpriteFrameHeader*)&DAT_060D7248,
    (SaturnSpriteFrameHeader*)&DAT_060D7254,
    (SaturnSpriteFrameHeader*)&DAT_060D7260,
    (SaturnSpriteFrameHeader*)&DAT_060D726C,
    (SaturnSpriteFrameHeader*)&DAT_060D7278,
    (SaturnSpriteFrameHeader*)&DAT_060D7284,
    (SaturnSpriteFrameHeader*)&DAT_060D7290,
    (SaturnSpriteFrameHeader*)&DAT_060D729C,
    (SaturnSpriteFrameHeader*)&DAT_060D72A8,
    (SaturnSpriteFrameHeader*)&DAT_060D72B4,
    (SaturnSpriteFrameHeader*)&DAT_060D72C0,
    (SaturnSpriteFrameHeader*)&DAT_060D72CC,
    (SaturnSpriteFrameHeader*)&DAT_060D72D8,
};

SaturnSpriteResource DAT_060D7380 = {
    DAT_060D7010, (u16*)&DAT_060D7034, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D738C[1] = {&DAT_060D7380};
