// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6134();
void func_060D636C();
void func_060D6594();
void func_060D67F8();
void func_060D68C0();
void func_060D68D8();
void func_060D68F0();
void func_060D68FC();
void func_060D6914();
void func_060D692C();
void func_060D6944();
void func_060D695C();
void func_060D6974();
void func_060D698C();
void func_060D69A4();
void func_060D69BC();
extern SaturnSpriteResource* DAT_060D6DD0[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6134,
        func_060D636C,
        func_060D6594,
        func_060D67F8,
        func_060D68C0,
        func_060D68D8,
        func_060D68F0,
        func_060D69BC,
        func_060D68FC,
        func_060D6914,
        func_060D692C,
        func_060D6944,
        func_060D695C,
        func_060D6974,
        func_060D698C,
        func_060D69A4,
    },
    DAT_060D6DD0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D6134, func_060D6134);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D636C, func_060D636C);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D6594, func_060D6594);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D67F8, func_060D67F8);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D68C0, func_060D68C0);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D68D8, func_060D68D8);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D68F0, func_060D68F0);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D68FC, func_060D68FC);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D6914, func_060D6914);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D692C, func_060D692C);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D6944, func_060D6944);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D695C, func_060D695C);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D6974, func_060D6974);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D698C, func_060D698C);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D69A4, func_060D69A4);
INCLUDE_ASM("asm/saturn/weapon/w_42/f_nonmat", f60D69BC, func_060D69BC);

u32 DAT_060D69D0[85] = {
    0x00060201, 0x00040202, 0x00040203, 0x00060204, 0x00050205, 0x00060206,
    0x00000000, 0x00050201, 0x00050202, 0x00050207, 0x00060208, 0x00050209,
    0x0005020A, 0x0005020B, 0x0010020C, 0x0005020D, 0x0005020E, 0x00050209,
    0x0005020A, 0x0005020B, 0x0010020C, 0x0005020D, 0x0005020E, 0x00050209,
    0x0005020A, 0x0005020B, 0x001F020C, 0x00040204, 0x00040205, 0x00040206,
    0x00400201, 0xFFFF0000, 0x00020017, 0x00010018, 0x00020019, 0x0001001A,
    0x0001001B, 0x0001001C, 0x0001001D, 0x00010019, 0x00010018, 0xFFFF0000,
    0x00800A15, 0xFFFF0000, 0x00800016, 0xFFFF0000, 0x00080201, 0x00060006,
    0x00050005, 0x00060004, 0x00040003, 0x00040002, 0x00060001, 0x00000001,
    0x00000000, 0xFF000512, 0xB0D80000, 0xB0C00000, 0x00000907, 0x00000403,
    0x00011800, 0x00014000, 0x0000F000, 0x00016800, 0x00020001, 0x00020002,
    0x00020003, 0x00020004, 0x00020005, 0x00020004, 0x00020003, 0x00020004,
    0x00020003, 0x00020004, 0x00020005, 0x00010006, 0x00010007, 0x00010008,
    0xFFFF0000, 0xFFFEC000, 0xFFFE2000, 0xFFFD8000, 0xFFFC0000, 0xFFFB8000,
    0xFFFB0000,
};

SaturnSpriteImage DAT_060D6B24[25] = {
    {16, 21, 0x0000}, {16, 22, 0x0054}, {16, 21, 0x00AC}, {16, 21, 0x0100},
    {16, 22, 0x0154}, {16, 22, 0x01AC}, {12, 21, 0x0204}, {12, 21, 0x0244},
    {16, 21, 0x0284}, {20, 23, 0x02D8}, {16, 23, 0x034C}, {20, 21, 0x03A8},
    {16, 22, 0x0414}, {16, 21, 0x046C}, {4, 4, 0x04C0},   {8, 6, 0x04C4},
    {12, 6, 0x04D0},  {4, 11, 0x04E4},  {8, 7, 0x04F0},   {4, 4, 0x0500},
    {8, 7, 0x0504},   {12, 10, 0x0514}, {20, 15, 0x0534}, {40, 30, 0x0580},
    {0, 0, 0x06AC},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D6B88 = {
    0x0003,
    {
        {0xC400, 0x8C63, 0xA507, 0xB5AD, 0xC631, 0xD6B5, 0xEB5A, 0xB5A6, 0x81FD,
         0x83E1, 0x83E1, 0x87E1, 0x8011, 0x801B, 0x83E0, 0x8421},
        {0x80E0, 0x9C65, 0xA065, 0xA886, 0xB0A7, 0xB4C8, 0xBCE9, 0xC50A, 0xCD2B,
         0xD58C, 0xDE0E, 0xE670, 0xEEF1, 0xF753, 0xFFD5, 0xFFFF},
        {0x8080, 0xA4C6, 0xA8E7, 0xAD29, 0xB16B, 0xB5AD, 0xB9CE, 0xBDEF, 0xC210,
         0xC631, 0xCA52, 0xCE73, 0xD294, 0xD6B5, 0xDAD6, 0xE2F6},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6BEC = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6BF0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, -20, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BFC = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C08 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, -22, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C14 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -20, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C20 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, -20, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6C2C = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -21, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6C38 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -22, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6C44 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -20, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6C50 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -20, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C5C = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -21, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6C68 = {
    {0x0100, 0x0000},
    {
        {0x0000, -4, -21, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6C74 = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, -20, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6C80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -20, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6C8C = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -20, 13},
    },
};

SaturnSpriteFrame1 DAT_060D6C98 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -19, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6CA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -18, 15},
    },
};

SaturnSpriteFrame1 DAT_060D6CB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, -17, 16},
    },
};

SaturnSpriteFrame1 DAT_060D6CBC = {
    {0x0100, 0x0000},
    {
        {0x0010, 0, -18, 16},
    },
};

SaturnSpriteFrame1 DAT_060D6CC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -18, 17},
    },
};

SaturnSpriteFrame1 DAT_060D6CD4 = {
    {0x0100, 0x0000},
    {
        {0x0010, 1, -18, 17},
    },
};

SaturnSpriteFrame1 DAT_060D6CE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, 0, 18},
    },
};

SaturnSpriteFrame1 DAT_060D6CEC = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 1, 19},
    },
};

SaturnSpriteFrame1 DAT_060D6CF8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 1, 0, 20},
    },
};

SaturnSpriteFrame1 DAT_060D6D04 = {
    {0x0100, 0x0000},
    {
        {0x0100, 1, 0, 21},
    },
};

SaturnSpriteFrame1 DAT_060D6D10 = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 0, 22},
    },
};

SaturnSpriteFrame1 DAT_060D6D1C = {
    {0x0100, 0x0000},
    {
        {0x0200, 3, -1, 23},
    },
};

SaturnSpriteFrame1 DAT_060D6D28 = {
    {0x0100, 0x0000},
    {
        {0x0210, -2, -1, 23},
    },
};

SaturnSpriteFrame1 DAT_060D6D34 = {
    {0x0100, 0x0000},
    {
        {0x0230, -2, 0, 23},
    },
};

SaturnSpriteFrame1 DAT_060D6D40 = {
    {0x0100, 0x0000},
    {
        {0x0220, 3, 0, 23},
    },
};

SaturnSpriteFrameHeader* DAT_060D6D4C[30] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6BEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6C08,
    (SaturnSpriteFrameHeader*)&DAT_060D6C14,
    (SaturnSpriteFrameHeader*)&DAT_060D6C20,
    (SaturnSpriteFrameHeader*)&DAT_060D6C2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C38,
    (SaturnSpriteFrameHeader*)&DAT_060D6C44,
    (SaturnSpriteFrameHeader*)&DAT_060D6C50,
    (SaturnSpriteFrameHeader*)&DAT_060D6C5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C68,
    (SaturnSpriteFrameHeader*)&DAT_060D6C74,
    (SaturnSpriteFrameHeader*)&DAT_060D6C80,
    (SaturnSpriteFrameHeader*)&DAT_060D6C8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C98,
    (SaturnSpriteFrameHeader*)&DAT_060D6CA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6CD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6D04,
    (SaturnSpriteFrameHeader*)&DAT_060D6D10,
    (SaturnSpriteFrameHeader*)&DAT_060D6D1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D28,
    (SaturnSpriteFrameHeader*)&DAT_060D6D34,
    (SaturnSpriteFrameHeader*)&DAT_060D6D40,
};

SaturnSpriteResource DAT_060D6DC4 = {
    DAT_060D6B24, (u16*)&DAT_060D6B88, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6DD0[1] = {&DAT_060D6DC4};
