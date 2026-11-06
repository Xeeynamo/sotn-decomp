// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6134();
void func_060D637C();
void func_060D65B0();
void func_060D6718();
void func_060D67E0();
void func_060D67F8();
void func_060D6810();
void func_060D681C();
void func_060D6834();
void func_060D684C();
void func_060D6864();
void func_060D687C();
void func_060D6894();
void func_060D68AC();
void func_060D68C4();
void func_060D68DC();
extern SaturnSpriteResource* DAT_060D6D88[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6134,
        func_060D637C,
        func_060D65B0,
        func_060D6718,
        func_060D67E0,
        func_060D67F8,
        func_060D6810,
        func_060D68DC,
        func_060D681C,
        func_060D6834,
        func_060D684C,
        func_060D6864,
        func_060D687C,
        func_060D6894,
        func_060D68AC,
        func_060D68C4,
    },
    DAT_060D6D88,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D6134, func_060D6134);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D637C, func_060D637C);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D65B0, func_060D65B0);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D6718, func_060D6718);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D67E0, func_060D67E0);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D67F8, func_060D67F8);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D6810, func_060D6810);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D681C, func_060D681C);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D6834, func_060D6834);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D684C, func_060D684C);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D6864, func_060D6864);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D687C, func_060D687C);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D6894, func_060D6894);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D68AC, func_060D68AC);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D68C4, func_060D68C4);
INCLUDE_ASM("asm/saturn/weapon/w_40/f_nonmat", f60D68DC, func_060D68DC);

u32 DAT_060D68F0[82] = {
    0x00020206, 0x00020207, 0x00020208, 0x00020209, 0x0002020A, 0x0002020B,
    0x0002020C, 0x0002020D, 0x00000000, 0x00110201, 0x00040202, 0x00010211,
    0x0001040F, 0x000A040E, 0x0004040F, 0x00030410, 0x00030211, 0x00030202,
    0x00020203, 0x00080204, 0x000F0205, 0x00030202, 0x00020203, 0x00080204,
    0x000F0205, 0x00030202, 0x00020203, 0x00080204, 0x000F0205, 0x00080202,
    0x00100201, 0x00030202, 0x00020211, 0x0002040F, 0x0002040E, 0x0008040F,
    0xFFFF0000, 0x00010612, 0x00010613, 0x00010614, 0x00010615, 0x00010616,
    0x00010617, 0x00010618, 0x00010619, 0x00000000, 0x00020A1B, 0x00010A21,
    0x00020A1C, 0x00010A1D, 0x00010A1E, 0x00010A1F, 0x00010A20, 0x00010A1C,
    0x00010A21, 0xFFFF0000, 0x0080001A, 0xFFFF0000, 0x000A040E, 0x0001040F,
    0x00010211, 0x00040202, 0x00040201, 0x0002020D, 0x0002020C, 0x0002020B,
    0x0002020A, 0x00020209, 0x00020208, 0x00020207, 0x00020206, 0x00000005,
    0x00000000, 0x00010611, 0xFD070D0B, 0x05010D04, 0x00000403, 0xB1C10000,
    0x00011800, 0x00014000, 0x0000F000, 0x00016800,
};

SaturnSpriteImage DAT_060D6A38[26] = {
    {20, 22, 0x0000}, {20, 15, 0x0070}, {16, 10, 0x00BC}, {16, 10, 0x00E4},
    {16, 10, 0x010C}, {20, 23, 0x0134}, {16, 23, 0x01A8}, {20, 23, 0x0204},
    {20, 23, 0x0278}, {20, 23, 0x02EC}, {16, 10, 0x0360}, {20, 11, 0x0388},
    {16, 5, 0x03C0},  {20, 5, 0x03D4},  {16, 5, 0x03F0},  {20, 5, 0x0404},
    {20, 6, 0x0420},  {16, 6, 0x0440},  {20, 5, 0x0458},  {20, 5, 0x0474},
    {4, 4, 0x0490},   {8, 7, 0x0494},   {20, 15, 0x04A4}, {40, 30, 0x04F0},
    {12, 10, 0x061C}, {0, 0, 0x063C},
};

struct {
    u16 countAndFlags;
    u16 colors[4][16];
    u16 padding[1];
} DAT_060D6AA0 = {
    0x0004,
    {
        {0xC400, 0xEB5D, 0x9ABD, 0x85BA, 0x8091, 0x8008, 0x8004, 0x8400, 0x9084,
         0xA120, 0x9FFF, 0x81A1, 0x8E64, 0xB06B, 0xAD6B, 0xF7BD},
        {0x81A0, 0xFC00, 0xFC00, 0x8017, 0x8013, 0x8010, 0x800C, 0xFC00, 0xFC00,
         0x80BF, 0x815F, 0x81FF, 0x931F, 0xAFFF, 0xCFFF, 0xFFFF},
        {0x80E0, 0x9C65, 0xA065, 0xA886, 0xB0A7, 0xB4C8, 0xBCE9, 0xC50A, 0xCD2B,
         0xD58C, 0xDE0E, 0xE670, 0xEEF1, 0xF753, 0xFFD5, 0xFFFF},
        {0x8080, 0xA4C6, 0xA8E7, 0xAD29, 0xB16B, 0xB5AD, 0xB9CE, 0xBDEF, 0xC210,
         0xC631, 0xCA52, 0xCE73, 0xD294, 0xD6B5, 0xDAD6, 0xE2F6},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6B24 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6B28 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -21, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6B34 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -14, 1},
        {0x0000, -4, -31, 2},
    },
};

SaturnSpriteFrame2 DAT_060D6B48 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -14, 1},
        {0x0000, -3, -31, 3},
    },
};

SaturnSpriteFrame2 DAT_060D6B5C = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -14, 1},
        {0x0000, -1, -31, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6B70 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, -14, 1},
        {0x0000, -5, -31, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B84 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -20, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6B90 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -20, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6B9C = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, -20, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6BA8 = {
    {0x0100, 0x0000},
    {
        {0x0010, -4, -20, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6BB4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -20, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6BC0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -20, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6BCC = {
    {0x0100, 0x0000},
    {
        {0x0010, -2, -20, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6BD8 = {
    {0x0100, 0x0000},
    {
        {0x0010, 2, -20, 6},
    },
};

SaturnSpriteFrame2 DAT_060D6BE4 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, -10, 10},
        {0x0000, -2, -21, 11},
    },
};

SaturnSpriteFrame2 DAT_060D6BF8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, -10, 10},
        {0x0000, -2, -22, 11},
    },
};

SaturnSpriteFrame2 DAT_060D6C0C = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, -10, 10},
        {0x0000, -2, -23, 11},
    },
};

SaturnSpriteFrame2 DAT_060D6C20 = {
    {0x0200, 0x0000},
    {
        {0x0000, 4, -10, 10},
        {0x0000, -1, -25, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6C34 = {
    {0x0100, 0x0000},
    {
        {0x0100, 9, 0, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6C40 = {
    {0x0100, 0x0000},
    {
        {0x0100, 13, 0, 13},
    },
};

SaturnSpriteFrame1 DAT_060D6C4C = {
    {0x0100, 0x0000},
    {
        {0x0100, 9, 1, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6C58 = {
    {0x0100, 0x0000},
    {
        {0x0100, 13, 0, 15},
    },
};

SaturnSpriteFrame1 DAT_060D6C64 = {
    {0x0100, 0x0000},
    {
        {0x0100, 13, 0, 16},
    },
};

SaturnSpriteFrame1 DAT_060D6C70 = {
    {0x0100, 0x0000},
    {
        {0x0100, 9, 0, 17},
    },
};

SaturnSpriteFrame1 DAT_060D6C7C = {
    {0x0100, 0x0000},
    {
        {0x0100, 13, 0, 18},
    },
};

SaturnSpriteFrame1 DAT_060D6C88 = {
    {0x0100, 0x0000},
    {
        {0x0100, 13, 0, 19},
    },
};

SaturnSpriteFrame1 DAT_060D6C94 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 1, 20},
    },
};

SaturnSpriteFrame1 DAT_060D6CA0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, 1, 21},
    },
};

SaturnSpriteFrame1 DAT_060D6CAC = {
    {0x0100, 0x0000},
    {
        {0x0200, 4, 1, 22},
    },
};

SaturnSpriteFrame1 DAT_060D6CB8 = {
    {0x0100, 0x0000},
    {
        {0x0300, 4, 0, 23},
    },
};

SaturnSpriteFrame1 DAT_060D6CC4 = {
    {0x0100, 0x0000},
    {
        {0x0310, -1, 0, 23},
    },
};

SaturnSpriteFrame1 DAT_060D6CD0 = {
    {0x0100, 0x0000},
    {
        {0x0330, -1, 1, 23},
    },
};

SaturnSpriteFrame1 DAT_060D6CDC = {
    {0x0100, 0x0000},
    {
        {0x0320, 4, 1, 23},
    },
};

SaturnSpriteFrame1 DAT_060D6CE8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, 1, 24},
    },
};

SaturnSpriteFrameHeader* DAT_060D6CF4[34] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6B24,
    (SaturnSpriteFrameHeader*)&DAT_060D6B28,
    (SaturnSpriteFrameHeader*)&DAT_060D6B34,
    (SaturnSpriteFrameHeader*)&DAT_060D6B48,
    (SaturnSpriteFrameHeader*)&DAT_060D6B5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B70,
    (SaturnSpriteFrameHeader*)&DAT_060D6B84,
    (SaturnSpriteFrameHeader*)&DAT_060D6B90,
    (SaturnSpriteFrameHeader*)&DAT_060D6B9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6BA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BCC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BD8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6C0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C20,
    (SaturnSpriteFrameHeader*)&DAT_060D6C34,
    (SaturnSpriteFrameHeader*)&DAT_060D6C40,
    (SaturnSpriteFrameHeader*)&DAT_060D6C4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C58,
    (SaturnSpriteFrameHeader*)&DAT_060D6C64,
    (SaturnSpriteFrameHeader*)&DAT_060D6C70,
    (SaturnSpriteFrameHeader*)&DAT_060D6C7C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C88,
    (SaturnSpriteFrameHeader*)&DAT_060D6C94,
    (SaturnSpriteFrameHeader*)&DAT_060D6CA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6CC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CE8,
};

SaturnSpriteResource DAT_060D6D7C = {
    DAT_060D6A38, (u16*)&DAT_060D6AA0, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6D88[1] = {&DAT_060D6D7C};
