// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62C8();
void func_060D6464();
void func_060D6630();
void func_060D6740();
void func_060D6758();
void func_060D6770();
void func_060D677C();
void func_060D6794();
void func_060D67AC();
void func_060D67C4();
void func_060D67DC();
void func_060D67F4();
void func_060D680C();
void func_060D6824();
void func_060D683C();
extern SaturnSpriteResource* DAT_060D74AC[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62C8,
        func_060D6464,
        func_060D6630,
        func_060D6740,
        func_060D6758,
        func_060D6770,
        func_060D683C,
        func_060D677C,
        func_060D6794,
        func_060D67AC,
        func_060D67C4,
        func_060D67DC,
        func_060D67F4,
        func_060D680C,
        func_060D6824,
    },
    DAT_060D74AC,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D62C8, func_060D62C8);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6464, func_060D6464);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6630, func_060D6630);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6740, func_060D6740);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6758, func_060D6758);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6770, func_060D6770);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D677C, func_060D677C);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6794, func_060D6794);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D67AC, func_060D67AC);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D67C4, func_060D67C4);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D67DC, func_060D67DC);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D67F4, func_060D67F4);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D680C, func_060D680C);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D6824, func_060D6824);
INCLUDE_ASM("asm/saturn/weapon/w_60/f_nonmat", f60D683C, func_060D683C);

u16 DAT_060D6850[14] = {0x0201, 0x0402, 0x3203, 0x3204, 0x3205, 0x3206, 0x3407,
                        0x0C08, 0x0C09, 0x100A, 0x100B, 0x5A0C, 0x100D, 0xFFFF};

u16 DAT_060D686C[14] = {0x0E0E, 0x120F, 0x3610, 0x3611, 0x3612, 0x3613, 0x1814,
                        0x1A15, 0x1A16, 0x101D, 0x101E, 0x581F, 0x1020, 0xFFFF};

u16 DAT_060D6888[13] = {0x0E0E, 0x120F, 0x3817, 0x3818, 0x3819, 0x3C1A, 0x241B,
                        0x241C, 0x101D, 0x101E, 0x581F, 0x1020, 0xFFFF};

u16 DAT_060D68A2[14] = {0x0221, 0x0422, 0x3223, 0x3224, 0x3225, 0x3E26, 0x3427,
                        0x0C28, 0x0E29, 0x102A, 0x102B, 0x102C, 0x102D, 0xFFFF};

u16 DAT_060D68BE[14] = {0x2A2E, 0x042F, 0x3E30, 0x3E31, 0x3E32, 0x3E33, 0x3434,
                        0x0C35, 0x0E36, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF};

u16 DAT_060D68DA[13] = {0x2A2E, 0x042F, 0x4037, 0x4038, 0x4039, 0x423A, 0x423B,
                        0x103C, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF};

u16 DAT_060D68F4[25] = {
    0x0201, 0x0402, 0x3203, 0x3204, 0x3205, 0x3245, 0x3246, 0x4447, 0x4648,
    0x4849, 0x4A4A, 0x4C4B, 0x4E4C, 0x504D, 0x524E, 0x544F, 0x3206, 0x3407,
    0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF};

u16 DAT_060D6926[15] = {
    0x0201, 0x0402, 0x3203, 0x3204, 0x5605, 0x3206, 0x3407, 0x0C08,
    0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF, 0x0000};

u16* DAT_060D6944[7] = {DAT_060D6850, DAT_060D6850, DAT_060D686C, DAT_060D6888,
                        DAT_060D68A2, DAT_060D68BE, DAT_060D68DA};

u16* DAT_060D6960[7] = {DAT_060D68F4, DAT_060D68F4, DAT_060D68F4, DAT_060D68F4,
                        DAT_060D68F4, DAT_060D68F4, DAT_060D68F4};

u16* DAT_060D697C[7] = {DAT_060D6926, DAT_060D6926, DAT_060D686C, DAT_060D6888,
                        DAT_060D68A2, DAT_060D68BE, DAT_060D68DA};

s8 DAT_060D6998[46][4] = {
    {0, 0, 0, 0},     {26, -32, 14, 6},  {-32, -32, 14, 6}, {24, -3, 30, 11},
    {59, -14, 36, 6}, {35, -18, 25, 7},  {32, -24, 14, 8},  {16, -14, 14, 8},
    {-40, -31, 0, 0}, {-38, -12, 13, 6}, {18, 16, 39, 12},  {49, 5, 36, 7},
    {42, -1, 18, 4},  {32, -6, 15, 7},   {19, 22, 38, 12},  {46, 29, 23, 13},
    {44, 23, 23, 13}, {30, 8, 28, 6},    {9, 5, 23, 6},     {28, -4, 48, 14},
    {41, -17, 45, 6}, {-10, -26, 10, 5}, {33, 11, 43, 19},  {41, 10, 35, 16},
    {26, -10, 25, 5}, {64, -14, 37, 6},  {54, -18, 23, 7},  {60, 5, 31, 7},
    {52, 29, 20, 13}, {41, 23, 20, 13},  {40, 8, 23, 6},    {54, -17, 40, 6},
    {66, 24, 16, 8},  {21, -10, 20, 5},  {65, -14, 37, 6},  {66, -14, 37, 6},
    {67, -14, 37, 6}, {71, -14, 37, 6},  {80, -14, 37, 6},  {88, -14, 37, 6},
    {96, -14, 37, 6}, {104, -14, 37, 6}, {112, -14, 37, 6}, {72, -14, 37, 14},
    {-40, 12, 10, 6}, {-24, -3, 10, 5}};

WeaponAnimation DAT_060D6A50[3] = {
    {(u16**)DAT_060D6944, (s8*)DAT_060D6998, 0x0000, 0x062C, 0x60, 0x04, 0},
    {(u16**)DAT_060D6960, (s8*)DAT_060D6998, 0x0000, 0x062C, 0xE0, 0x04, 0},
    {(u16**)DAT_060D697C, (s8*)DAT_060D6998, 0x0000, 0x062C, 0x60, 0x04, 0},
};

AnimationFrame DAT_060D6A80[5] = {
    {0x0003, 0x0041},
    {0x0003, 0x0042},
    {0x0003, 0x0043},
    {0x0003, 0x0044},
    {0x0000, 0x0000}};

SaturnSpriteImage DAT_060D6A94[22] = {
    {24, 10, 0x0000}, {52, 11, 0x003C}, {36, 3, 0x00CC}, {36, 7, 0x00E8},
    {36, 6, 0x0128},  {20, 6, 0x0160},  {28, 8, 0x0180}, {40, 19, 0x01B8},
    {28, 16, 0x0278}, {20, 3, 0x02E8},  {24, 7, 0x02F8}, {20, 3, 0x0324},
    {16, 2, 0x0334},  {28, 5, 0x033C},  {28, 8, 0x0360}, {8, 1, 0x0398},
    {4, 3, 0x039C},   {4, 3, 0x03A0},   {4, 2, 0x03A4},  {4, 1, 0x03A8},
    {8, 1, 0x03AC},   {0, 0, 0x03B0},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D6AEC = {
    0x0003,
    {
        {0x8982, 0x8421, 0x84CA, 0x952F, 0xA173, 0x9218, 0x9EDF, 0xA0A4, 0x83E0,
         0xBBF6, 0x8623, 0xC009, 0xC5A7, 0xDA4F, 0xDF37, 0xEF99},
        {0x9E00, 0xB033, 0xB053, 0xB473, 0xB893, 0xBCD3, 0xC0F4, 0xC514, 0xC954,
         0xCD74, 0xD195, 0xD5D5, 0xD9F5, 0xDE15, 0xE256, 0xCED9},
        {0x8080, 0x8082, 0x8084, 0x8086, 0x8088, 0x808A, 0x808C, 0x808E, 0x8090,
         0x8092, 0x8094, 0x8096, 0x8098, 0x809A, 0x809C, 0x809E},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6B50 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6B54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6B60 = {
    {0x0100, 0x0000},
    {
        {0x0010, -27, -26, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6B6C = {
    {0x0200, 0x0000},
    {
        {0x0100, 55, -2, 1},
        {0x0000, 66, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B8C = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6B98 = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -16, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6BB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -19, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BBC = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -16, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, -10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6BD4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6BE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6BEC = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6BF8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, -12, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C04 = {
    {0x0100, 0x0000},
    {
        {0x0010, -33, -7, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6C10 = {
    {0x0200, 0x0000},
    {
        {0x0100, 47, 15, 1},
        {0x0000, 58, 5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 59, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 59, 4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C3C = {
    {0x0100, 0x0000},
    {
        {0x0000, 59, 4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C48 = {
    {0x0100, 0x0000},
    {
        {0x0000, 41, 1, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6C54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C60 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 2, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6C6C = {
    {0x0200, 0x0000},
    {
        {0x0100, 37, 26, 7},
        {0x0000, 48, 28, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, 28, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C8C = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, 28, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C98 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 5, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6CB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 4, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6CBC = {
    {0x0100, 0x0000},
    {
        {0x0000, -27, 9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6CC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -28, 10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6CD4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -29, 11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6CE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -30, 12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6CEC = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CF8 = {
    {0x0100, 0x0000},
    {
        {0x0010, -19, -28, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6D04 = {
    {0x0200, 0x0000},
    {
        {0x0100, 51, -2, 1},
        {0x0000, 65, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D3C = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, -16, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6D48 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -21, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -18, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D60 = {
    {0x0100, 0x0000},
    {
        {0x0000, -6, -12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D6C = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D78 = {
    {0x0100, 0x0000},
    {
        {0x0000, -12, -10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D84 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D90 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -31, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D9C = {
    {0x0100, 0x0000},
    {
        {0x0010, -38, -29, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6DA8 = {
    {0x0200, 0x0000},
    {
        {0x0100, 49, -2, 1},
        {0x0000, 60, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DBC = {
    {0x0100, 0x0000},
    {
        {0x0000, 61, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 61, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DD4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 61, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -16, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6DEC = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, -20, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DF8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -19, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6E04 = {
    {0x0200, 0x0000},
    {
        {0x0100, 44, 15, 7},
        {0x0000, 57, 18, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6E18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 57, 17, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6E24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 57, 17, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6E30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 41, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E3C = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -10, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6E48 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -12, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6E54 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E60 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E6C = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6E78 = {
    {0x0100, 0x0000},
    {
        {0x0000, -12, -7, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6E84 = {
    {0x0200, 0x0000},
    {
        {0x0200, 72, -20, 13},
        {0x0100, 80, -12, 13},
    },
};

SaturnSpriteFrame3 DAT_060D6E98 = {
    {0x0300, 0x0000},
    {
        {0x0200, 78, -20, 13},
        {0x0100, 72, -10, 13},
        {0x0000, 64, -4, 13},
    },
};

SaturnSpriteFrame3 DAT_060D6EB4 = {
    {0x0300, 0x0000},
    {
        {0x0200, 91, -13, 13},
        {0x0100, 68, -8, 13},
        {0x0000, 84, 4, 13},
    },
};

SaturnSpriteFrame4 DAT_060D6ED0 = {
    {0x0400, 0x0000},
    {
        {0x0200, 80, -16, 13},
        {0x0100, 94, -11, 13},
        {0x0000, 72, -24, 13},
        {0x0200, 71, 0, 13},
    },
};

SaturnSpriteFrame6 DAT_060D6EF4 = {
    {0x0600, 0x0000},
    {
        {0x0100, 61, -13, 14},
        {0x0100, 83, -20, 15},
        {0x0120, 83, -7, 15},
        {0x0100, 86, -13, 16},
        {0x0100, 94, -13, 17},
        {0x0100, 102, -13, 18},
    },
};

SaturnSpriteFrame8 DAT_060D6F28 = {
    {0x0800, 0x0000},
    {
        {0x0200, 61, -13, 14},
        {0x0200, 88, -20, 15},
        {0x0220, 88, -7, 15},
        {0x0200, 81, -13, 16},
        {0x0200, 89, -13, 17},
        {0x0200, 97, -13, 18},
        {0x0200, 78, -20, 19},
        {0x0220, 78, -7, 19},
    },
};

SaturnSpriteFrame10 DAT_060D6F6C = {
    {0x0A00, 0x0000},
    {
        {0x0000, 79, -13, 16},
        {0x0000, 61, -13, 14},
        {0x0000, 95, -20, 15},
        {0x0020, 95, -7, 15},
        {0x0000, 85, -13, 17},
        {0x0000, 92, -13, 18},
        {0x0000, 84, -20, 19},
        {0x0020, 84, -7, 19},
        {0x0020, 78, -7, 19},
        {0x0000, 78, -20, 19},
    },
};

SaturnSpriteFrame10 DAT_060D6FC0 = {
    {0x0A00, 0x0000},
    {
        {0x0000, 77, -13, 16},
        {0x0000, 61, -13, 14},
        {0x0000, 97, -20, 15},
        {0x0020, 97, -7, 15},
        {0x0000, 82, -13, 17},
        {0x0000, 88, -13, 18},
        {0x0000, 86, -20, 19},
        {0x0020, 86, -7, 19},
        {0x0020, 78, -7, 19},
        {0x0000, 78, -20, 19},
    },
};

SaturnSpriteFrame10 DAT_060D7014 = {
    {0x0A00, 0x0000},
    {
        {0x0000, 76, -13, 16},
        {0x0000, 61, -13, 14},
        {0x0000, 99, -20, 15},
        {0x0020, 99, -7, 15},
        {0x0000, 78, -13, 17},
        {0x0000, 83, -13, 18},
        {0x0000, 87, -20, 19},
        {0x0020, 87, -7, 19},
        {0x0020, 79, -7, 19},
        {0x0000, 79, -20, 19},
    },
};

SaturnSpriteFrame12 DAT_060D7068 = {
    {0x0C00, 0x0000},
    {
        {0x0000, 76, -13, 16},
        {0x0000, 61, -13, 14},
        {0x0000, 103, -20, 15},
        {0x0000, 78, -13, 17},
        {0x0020, 103, -7, 15},
        {0x0000, 83, -13, 18},
        {0x0000, 91, -20, 19},
        {0x0020, 91, -7, 19},
        {0x0020, 83, -7, 19},
        {0x0000, 83, -20, 19},
        {0x0000, 80, -20, 19},
        {0x0020, 80, -7, 19},
    },
};

SaturnSpriteFrame14 DAT_060D70CC = {
    {0x0E00, 0x0000},
    {
        {0x0000, 76, -13, 16},
        {0x0000, 61, -13, 14},
        {0x0000, 113, -20, 15},
        {0x0000, 78, -13, 17},
        {0x0020, 113, -7, 15},
        {0x0000, 83, -13, 18},
        {0x0000, 101, -20, 19},
        {0x0020, 101, -7, 19},
        {0x0020, 93, -7, 19},
        {0x0000, 93, -20, 19},
        {0x0000, 90, -20, 19},
        {0x0020, 90, -7, 19},
        {0x0000, 83, -20, 20},
        {0x0020, 84, -7, 20},
    },
};

SaturnSpriteFrame14 DAT_060D7140 = {
    {0x0E00, 0x0000},
    {
        {0x0000, 76, -13, 16},
        {0x0000, 61, -13, 14},
        {0x0000, 120, -20, 15},
        {0x0000, 78, -13, 17},
        {0x0020, 120, -7, 15},
        {0x0000, 83, -13, 18},
        {0x0000, 108, -20, 19},
        {0x0020, 108, -7, 19},
        {0x0020, 100, -7, 19},
        {0x0000, 100, -20, 19},
        {0x0000, 92, -20, 19},
        {0x0020, 92, -7, 19},
        {0x0000, 84, -20, 20},
        {0x0020, 84, -7, 20},
    },
};

SaturnSpriteFrame16 DAT_060D71B4 = {
    {0x1000, 0x0000},
    {
        {0x0000, 76, -13, 16},
        {0x0000, 61, -13, 14},
        {0x0000, 130, -20, 15},
        {0x0000, 78, -13, 17},
        {0x0020, 130, -7, 15},
        {0x0000, 83, -13, 18},
        {0x0000, 118, -20, 19},
        {0x0020, 118, -7, 19},
        {0x0020, 110, -7, 19},
        {0x0000, 110, -20, 19},
        {0x0000, 102, -20, 19},
        {0x0020, 102, -7, 19},
        {0x0000, 84, -20, 20},
        {0x0020, 84, -7, 20},
        {0x0000, 94, -20, 20},
        {0x0020, 94, -7, 20},
    },
};

SaturnSpriteFrame18 DAT_060D7238 = {
    {0x1200, 0x0000},
    {
        {0x0000, 76, -13, 16},
        {0x0000, 61, -13, 14},
        {0x0000, 140, -20, 15},
        {0x0000, 78, -13, 17},
        {0x0020, 140, -7, 15},
        {0x0000, 83, -13, 18},
        {0x0000, 128, -20, 19},
        {0x0020, 128, -7, 19},
        {0x0020, 120, -7, 19},
        {0x0000, 120, -20, 19},
        {0x0000, 112, -20, 19},
        {0x0020, 112, -7, 19},
        {0x0000, 91, -20, 20},
        {0x0020, 91, -7, 20},
        {0x0000, 101, -20, 20},
        {0x0020, 101, -7, 20},
        {0x0000, 84, -20, 20},
        {0x0020, 83, -7, 20},
    },
};

SaturnSpriteFrame18 DAT_060D72CC = {
    {0x1200, 0x0000},
    {
        {0x0200, 76, -13, 16},
        {0x0200, 61, -13, 14},
        {0x0200, 150, -20, 15},
        {0x0200, 78, -13, 17},
        {0x0220, 150, -7, 15},
        {0x0200, 83, -13, 18},
        {0x0200, 138, -20, 19},
        {0x0220, 138, -7, 19},
        {0x0220, 130, -7, 19},
        {0x0200, 130, -20, 19},
        {0x0200, 122, -20, 19},
        {0x0220, 122, -7, 19},
        {0x0200, 95, -20, 20},
        {0x0220, 95, -7, 20},
        {0x0200, 111, -20, 20},
        {0x0220, 111, -7, 20},
        {0x0200, 84, -20, 20},
        {0x0220, 83, -7, 20},
    },
};

SaturnSpriteFrameHeader* DAT_060D7360[80] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6B50,
    (SaturnSpriteFrameHeader*)&DAT_060D6B54,
    (SaturnSpriteFrameHeader*)&DAT_060D6B60,
    (SaturnSpriteFrameHeader*)&DAT_060D6B6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B80,
    (SaturnSpriteFrameHeader*)&DAT_060D6B8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B98,
    (SaturnSpriteFrameHeader*)&DAT_060D6BA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6C04,
    (SaturnSpriteFrameHeader*)&DAT_060D6C10,
    (SaturnSpriteFrameHeader*)&DAT_060D6C24,
    (SaturnSpriteFrameHeader*)&DAT_060D6C30,
    (SaturnSpriteFrameHeader*)&DAT_060D6C3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C48,
    (SaturnSpriteFrameHeader*)&DAT_060D6C54,
    (SaturnSpriteFrameHeader*)&DAT_060D6C60,
    (SaturnSpriteFrameHeader*)&DAT_060D6C6C,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6D18,
    (SaturnSpriteFrameHeader*)&DAT_060D6D24,
    (SaturnSpriteFrameHeader*)&DAT_060D6D30,
    (SaturnSpriteFrameHeader*)&DAT_060D6D3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D48,
    (SaturnSpriteFrameHeader*)&DAT_060D6D54,
    (SaturnSpriteFrameHeader*)&DAT_060D6D60,
    (SaturnSpriteFrameHeader*)&DAT_060D6D6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D78,
    (SaturnSpriteFrameHeader*)&DAT_060D6D84,
    (SaturnSpriteFrameHeader*)&DAT_060D6D90,
    (SaturnSpriteFrameHeader*)&DAT_060D6D9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6DA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6E04,
    (SaturnSpriteFrameHeader*)&DAT_060D6E18,
    (SaturnSpriteFrameHeader*)&DAT_060D6E24,
    (SaturnSpriteFrameHeader*)&DAT_060D6E30,
    (SaturnSpriteFrameHeader*)&DAT_060D6E3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E48,
    (SaturnSpriteFrameHeader*)&DAT_060D6E54,
    (SaturnSpriteFrameHeader*)&DAT_060D6E60,
    (SaturnSpriteFrameHeader*)&DAT_060D6E6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E78,
    (SaturnSpriteFrameHeader*)&DAT_060D6E84,
    (SaturnSpriteFrameHeader*)&DAT_060D6E98,
    (SaturnSpriteFrameHeader*)&DAT_060D6EB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6ED0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6F28,
    (SaturnSpriteFrameHeader*)&DAT_060D6F6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6FC0,
    (SaturnSpriteFrameHeader*)&DAT_060D7014,
    (SaturnSpriteFrameHeader*)&DAT_060D7068,
    (SaturnSpriteFrameHeader*)&DAT_060D70CC,
    (SaturnSpriteFrameHeader*)&DAT_060D7140,
    (SaturnSpriteFrameHeader*)&DAT_060D71B4,
    (SaturnSpriteFrameHeader*)&DAT_060D7238,
    (SaturnSpriteFrameHeader*)&DAT_060D72CC,
};

SaturnSpriteResource DAT_060D74A0 = {
    DAT_060D6A94, (u16*)&DAT_060D6AEC, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D74AC[1] = {&DAT_060D74A0};
