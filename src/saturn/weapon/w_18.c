// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6384();
void func_060D6574();
void func_060D658C();
void func_060D65A4();
void func_060D65BC();
void func_060D65D4();
void func_060D65E0();
void func_060D65F8();
void func_060D6610();
void func_060D6628();
void func_060D6640();
void func_060D6658();
void func_060D6670();
void func_060D6688();
void func_060D66A0();
extern SaturnSpriteResource* DAT_060D6AD8[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6384,
        func_060D6574,
        func_060D658C,
        func_060D65A4,
        func_060D65BC,
        func_060D65D4,
        func_060D66A0,
        func_060D65E0,
        func_060D65F8,
        func_060D6610,
        func_060D6628,
        func_060D6640,
        func_060D6658,
        func_060D6670,
        func_060D6688,
    },
    DAT_060D6AD8,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6384, func_060D6384);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6574, func_060D6574);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D658C, func_060D658C);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D65A4, func_060D65A4);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D65BC, func_060D65BC);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D65D4, func_060D65D4);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D65E0, func_060D65E0);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D65F8, func_060D65F8);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6610, func_060D6610);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6628, func_060D6628);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6640, func_060D6640);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6658, func_060D6658);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6670, func_060D6670);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D6688, func_060D6688);
INCLUDE_ASM("asm/saturn/weapon/w_18/f_nonmat", f60D66A0, func_060D66A0);

u32 DAT_060D66B0[34] = {
    0x00010001, 0x00010002, 0x00020003, 0x00020004, 0x00020005, 0x00020006,
    0x00020007, 0x00020008, 0x00020009, 0x0002000A, 0x0002000B, 0x0004000A,
    0x0002000C, 0x0002000D, 0xFFFF0000, 0x00010000, 0x00010011, 0x00010000,
    0x00010012, 0x00010000, 0x00010016, 0x00010013, 0x00010000, 0x00010014,
    0x00010000, 0x00010015, 0x00010000, 0x00010016, 0x00000000, 0x00010017,
    0x00000000, 0x0001000E, 0x0001000F, 0x00000000,
};

SaturnSpriteImage DAT_060D6738[16] = {
    {4, 23, 0x0000},  {4, 10, 0x0018},  {4, 8, 0x0024},   {12, 9, 0x002C},
    {12, 10, 0x0048}, {16, 6, 0x0068},  {20, 8, 0x0080},  {20, 10, 0x00A8},
    {16, 11, 0x00DC}, {12, 12, 0x0108}, {12, 7, 0x012C},  {12, 7, 0x0144},
    {32, 47, 0x015C}, {36, 48, 0x02D4}, {44, 59, 0x0484}, {0, 0, 0x0710},
};

struct {
    u16 countAndFlags;
    u16 colors[10][16];
    u16 padding[1];
} DAT_060D6778 = {
    0x000A,
    {
        {0x8140, 0xFD29, 0xFD29, 0xFD08, 0xF508, 0xECE7, 0xE0C6, 0xD8C6, 0xD0A5,
         0xC884, 0xBCA5, 0xB463, 0xAC00, 0xA529, 0xAC00, 0xFE10},
        {0x8180, 0xFFCB, 0xF78A, 0xEF49, 0xE709, 0xDEE8, 0xD6A7, 0xD247, 0xCA06,
         0xC204, 0xB9C5, 0xB184, 0xA940, 0xA529, 0xA940, 0xFFF0},
        {0x8180, 0xAFEB, 0xABAA, 0xA769, 0xA729, 0xA2E8, 0x9EA7, 0x9E87, 0x9A46,
         0x9204, 0x95C5, 0x9184, 0x8140, 0xA529, 0x8160, 0xC3F0},
        {0x8180, 0xAFFE, 0xABDD, 0xA79B, 0xA759, 0xA317, 0x9AD4, 0x9E94, 0x9A52,
         0x9210, 0x95CE, 0x918C, 0x814A, 0xA529, 0x814A, 0xC3FF},
        {0x8180, 0xAABF, 0xAA9F, 0xA27D, 0xA65B, 0xA219, 0x99F7, 0x9DD5, 0x9573,
         0x9171, 0x954F, 0x8CCD, 0x80AB, 0xA529, 0x80AB, 0xC31F},
        {0x8000, 0xA95F, 0xA95F, 0xA11D, 0xA53B, 0xA119, 0x98D7, 0x9CF5, 0x94B3,
         0x9091, 0x94AF, 0x8C6D, 0x800B, 0xA529, 0x80AB, 0xC21F},
        {0x8180, 0xFD5D, 0xFD5C, 0xF51A, 0xED38, 0xE516, 0xDCD4, 0xD4F3, 0xCCB1,
         0xC48F, 0xBCAD, 0xB46A, 0xAC05, 0xA529, 0xA80A, 0xFE5F},
        {0x8180, 0x8400, 0x8401, 0x8421, 0x8441, 0x8841, 0x8842, 0x8862, 0x8C62,
         0x8C63, 0x8C83, 0x9084, 0x90A4, 0x94A5, 0x8420, 0xBDEF},
        {0xF800, 0xB190, 0xB190, 0xB5B1, 0xB9D1, 0xBDF2, 0xC213, 0xC633, 0xCA54,
         0xCE74, 0xD295, 0xD296, 0xD6B6, 0xDAD7, 0xDEF7, 0xE318},
        {0xF800, 0xC632, 0xCA53, 0xCE74, 0xD295, 0xD6B6, 0xDAD7, 0xDEF8, 0xE319,
         0xE739, 0xEB5A, 0xEF7B, 0xF39C, 0xF7BD, 0xFBDE, 0xFFFF},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D68BC = {0x0000, 0x0000};

SaturnSpriteFrame2 DAT_060D68C0 = {
    {0x0200, 0x0000},
    {
        {0x0000, 3, 59, 0},
        {0x0000, 3, 15, 0},
    },
};

SaturnSpriteFrame1 DAT_060D68D4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 12, 0},
    },
};

SaturnSpriteFrame1 DAT_060D68E0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 0, -2, 1},
    },
};

SaturnSpriteFrame2 DAT_060D68EC = {
    {0x0200, 0x0000},
    {
        {0x0300, -1, -3, 2},
        {0x0310, 0, -3, 2},
    },
};

SaturnSpriteFrame2 DAT_060D6900 = {
    {0x0200, 0x0000},
    {
        {0x0400, 6, -5, 3},
        {0x0410, -5, -5, 3},
    },
};

SaturnSpriteFrame2 DAT_060D6914 = {
    {0x0200, 0x0000},
    {
        {0x0500, -1, -6, 4},
        {0x0510, 2, -6, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6928 = {
    {0x0200, 0x0000},
    {
        {0x0600, 12, -13, 5},
        {0x0610, -12, -13, 5},
    },
};

SaturnSpriteFrame2 DAT_060D693C = {
    {0x0200, 0x0000},
    {
        {0x0000, 11, -14, 6},
        {0x0010, -10, -14, 6},
    },
};

SaturnSpriteFrame2 DAT_060D6950 = {
    {0x0200, 0x0000},
    {
        {0x0100, 14, -20, 7},
        {0x0110, -13, -20, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6964 = {
    {0x0200, 0x0000},
    {
        {0x0200, 8, -22, 8},
        {0x0210, -7, -22, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6978 = {
    {0x0200, 0x0000},
    {
        {0x0300, 12, -24, 9},
        {0x0310, -11, -24, 9},
    },
};

SaturnSpriteFrame5 DAT_060D698C = {
    {0x0500, 0x0000},
    {
        {0x0700, -1, -27, 10},
        {0x0700, 7, -27, 10},
        {0x0700, 11, -27, 10},
        {0x0700, 3, -23, 10},
        {0x0700, 3, -15, 10},
    },
};

SaturnSpriteFrame5 DAT_060D69B8 = {
    {0x0500, 0x0000},
    {
        {0x0700, -10, -39, 11},
        {0x0700, 18, -31, 11},
        {0x0700, -6, -19, 11},
        {0x0700, 10, -7, 11},
        {0x0700, 1, 9, 11},
    },
};

SaturnSpriteFrame2 DAT_060D69E4 = {
    {0x0200, 0x0000},
    {
        {0x0800, -27, -3, 12},
        {0x0800, 40, -3, 13},
    },
};

SaturnSpriteFrame2 DAT_060D69F8 = {
    {0x0200, 0x0000},
    {
        {0x0900, -27, -3, 12},
        {0x0900, 40, -3, 13},
    },
};

SaturnSpriteFrame1 DAT_060D6A0C = {
    {0x0100, 0x0000},
    {
        {0x0700, -6, 2, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6A18 = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, 2, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6A24 = {
    {0x0100, 0x0000},
    {
        {0x0100, -6, 2, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6A30 = {
    {0x0100, 0x0000},
    {
        {0x0200, -6, 2, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6A3C = {
    {0x0100, 0x0000},
    {
        {0x0300, -6, 2, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6A48 = {
    {0x0100, 0x0000},
    {
        {0x0400, -6, 2, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6A54 = {
    {0x0100, 0x0000},
    {
        {0x0500, -6, 2, 14},
    },
};

SaturnSpriteFrame1 DAT_060D6A60 = {
    {0x0100, 0x0000},
    {
        {0x0600, -6, 2, 14},
    },
};

SaturnSpriteFrameHeader* DAT_060D6A6C[24] = {
    (SaturnSpriteFrameHeader*)&DAT_060D68BC,
    (SaturnSpriteFrameHeader*)&DAT_060D68C0,
    (SaturnSpriteFrameHeader*)&DAT_060D68D4,
    (SaturnSpriteFrameHeader*)&DAT_060D68E0,
    (SaturnSpriteFrameHeader*)&DAT_060D68EC,
    (SaturnSpriteFrameHeader*)&DAT_060D6900,
    (SaturnSpriteFrameHeader*)&DAT_060D6914,
    (SaturnSpriteFrameHeader*)&DAT_060D6928,
    (SaturnSpriteFrameHeader*)&DAT_060D693C,
    (SaturnSpriteFrameHeader*)&DAT_060D6950,
    (SaturnSpriteFrameHeader*)&DAT_060D6964,
    (SaturnSpriteFrameHeader*)&DAT_060D6978,
    (SaturnSpriteFrameHeader*)&DAT_060D698C,
    (SaturnSpriteFrameHeader*)&DAT_060D69B8,
    (SaturnSpriteFrameHeader*)&DAT_060D69E4,
    (SaturnSpriteFrameHeader*)&DAT_060D69F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6A0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A18,
    (SaturnSpriteFrameHeader*)&DAT_060D6A24,
    (SaturnSpriteFrameHeader*)&DAT_060D6A30,
    (SaturnSpriteFrameHeader*)&DAT_060D6A3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A48,
    (SaturnSpriteFrameHeader*)&DAT_060D6A54,
    (SaturnSpriteFrameHeader*)&DAT_060D6A60,
};

SaturnSpriteResource DAT_060D6ACC = {
    DAT_060D6738, (u16*)&DAT_060D6778, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6AD8[1] = {&DAT_060D6ACC};
