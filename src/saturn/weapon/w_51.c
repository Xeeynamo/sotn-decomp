// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D62A0();
void func_060D6520();
void func_060D6778();
void func_060D6D90();
void func_060D6DA8();
void func_060D6DC0();
void func_060D6DD8();
void func_060D6DE4();
void func_060D6DFC();
void func_060D6E14();
void func_060D6E2C();
void func_060D6E44();
void func_060D6E5C();
void func_060D6E74();
void func_060D6E8C();
void func_060D6EA4();
extern SaturnSpriteResource* DAT_060D7A94[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D62A0,
        func_060D6520,
        func_060D6778,
        func_060D6D90,
        func_060D6DA8,
        func_060D6DC0,
        func_060D6DD8,
        func_060D6EA4,
        func_060D6DE4,
        func_060D6DFC,
        func_060D6E14,
        func_060D6E2C,
        func_060D6E44,
        func_060D6E5C,
        func_060D6E74,
        func_060D6E8C,
    },
    DAT_060D7A94,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D62A0, func_060D62A0);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6520, func_060D6520);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6778, func_060D6778);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6D90, func_060D6D90);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6DA8, func_060D6DA8);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6DC0, func_060D6DC0);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6DD8, func_060D6DD8);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6DE4, func_060D6DE4);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6DFC, func_060D6DFC);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6E14, func_060D6E14);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6E2C, func_060D6E2C);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6E44, func_060D6E44);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6E5C, func_060D6E5C);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6E74, func_060D6E74);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6E8C, func_060D6E8C);
INCLUDE_ASM("asm/saturn/weapon/w_51/f_nonmat", f60D6EA4, func_060D6EA4);

u16 DAT_060D6EB0[14] = {0x0201, 0x0402, 0x3203, 0x3204, 0x3205, 0x3206, 0x3407,
                        0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF};

u16 DAT_060D6ECC[14] = {0x0E0E, 0x120F, 0x3610, 0x3611, 0x3612, 0x3613, 0x1814,
                        0x1A15, 0x1A16, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF};

u16 DAT_060D6EE8[13] = {0x0E0E, 0x120F, 0x3817, 0x3818, 0x3A19, 0x3C1A, 0x241B,
                        0x241C, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF};

u16 DAT_060D6F02[14] = {0x0221, 0x0422, 0x3223, 0x3224, 0x3225, 0x3E26, 0x3427,
                        0x0C28, 0x0E29, 0x102A, 0x102B, 0x102C, 0x102D, 0xFFFF};

u16 DAT_060D6F1E[14] = {0x2A2E, 0x042F, 0x3E30, 0x3E31, 0x3E32, 0x3E33, 0x3434,
                        0x0C35, 0x0E36, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF};

u16 DAT_060D6F3A[13] = {0x2A2E, 0x042F, 0x4037, 0x4038, 0x4039, 0x423A, 0x423B,
                        0x0E3C, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF};

u16 DAT_060D6F54[14] = {0x0201, 0x0402, 0x0603, 0x0804, 0x0805, 0x0806, 0x0A07,
                        0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF};

u16 DAT_060D6F70[14] = {0x0E0E, 0x120F, 0x1410, 0x1611, 0x1612, 0x1613, 0x1814,
                        0x1A15, 0x1A16, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF};

u16 DAT_060D6F8C[13] = {0x0E0E, 0x120F, 0x1C17, 0x1E18, 0x2019, 0x221A, 0x241B,
                        0x241C, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF};

u16 DAT_060D6FA6[14] = {0x0221, 0x0422, 0x2623, 0x0824, 0x0825, 0x2826, 0x0A27,
                        0x0C28, 0x0E29, 0x102A, 0x102B, 0x102C, 0x102D, 0xFFFF};

u16 DAT_060D6FC2[14] = {0x2A2E, 0x042F, 0x2630, 0x2831, 0x2832, 0x2833, 0x0A34,
                        0x0C35, 0x0E36, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF};

u16 DAT_060D6FDE[13] = {0x2A2E, 0x042F, 0x2C37, 0x2E38, 0x2E39, 0x303A, 0x303B,
                        0x0E3C, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF};

u16 DAT_060D6FF8[15] = {
    0x0221, 0x0422, 0x2623, 0x0824, 0x0825, 0x0805, 0x0806, 0x0A07,
    0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF};

u16 DAT_060D7016[15] = {
    0x0221, 0x0422, 0x2623, 0x3224, 0x3225, 0x3205, 0x3206, 0x3407,
    0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF};

s8 DAT_060D7034[34][4] = {
    {0, 0, 0, 0},     {9, -26, 14, 6},   {-16, -23, 14, 6}, {24, -3, 30, 11},
    {59, -14, 36, 6}, {35, -18, 25, 7},  {23, -16, 14, 8},  {6, -10, 14, 8},
    {-40, -31, 0, 0}, {-23, -4, 13, 4},  {18, 16, 39, 12},  {49, 5, 36, 7},
    {23, -1, 18, 4},  {5, 2, 15, 7},     {19, 22, 38, 12},  {46, 29, 23, 13},
    {44, 23, 23, 13}, {30, 8, 28, 6},    {9, 5, 23, 6},     {28, -4, 48, 14},
    {41, -17, 45, 6}, {-10, -26, 10, 5}, {33, 11, 43, 19},  {41, 10, 35, 16},
    {26, -10, 25, 5}, {54, -14, 31, 6},  {33, -18, 23, 7},  {44, 5, 31, 7},
    {44, 29, 20, 13}, {41, 23, 20, 13},  {25, 8, 23, 6},    {36, -17, 40, 6},
    {36, 10, 30, 16}, {21, -10, 20, 5}};

u16* DAT_060D70BC[7] = {DAT_060D6EB0, DAT_060D6EB0, DAT_060D6ECC, DAT_060D6EE8,
                        DAT_060D6F02, DAT_060D6F1E, DAT_060D6F3A};

u16* DAT_060D70D8[7] = {DAT_060D6F54, DAT_060D6F54, DAT_060D6F70, DAT_060D6F8C,
                        DAT_060D6FA6, DAT_060D6FC2, DAT_060D6FDE};

u16* DAT_060D70F4[7] = {DAT_060D6FF8, DAT_060D6FF8, DAT_060D6FF8, DAT_060D6FF8,
                        DAT_060D6FF8, DAT_060D6FF8, DAT_060D6FF8};

u16* DAT_060D7110[7] = {DAT_060D7016, DAT_060D7016, DAT_060D7016, DAT_060D7016,
                        DAT_060D7016, DAT_060D7016, DAT_060D7016};

WeaponAnimation DAT_060D712C[8] = {
    {(u16**)DAT_060D70BC, (s8*)DAT_060D7034, 0x0000, 0x062C, 0x60, 0x04, 0},
    {(u16**)DAT_060D70D8, (s8*)DAT_060D7034, 0x0002, 0x062C, 0x60, 0x04, 0},
    {(u16**)DAT_060D70D8, (s8*)DAT_060D7034, 0x0004, 0x062C, 0x60, 0x04, 0},
    {(u16**)DAT_060D70D8, (s8*)DAT_060D7034, 0x0006, 0x062C, 0x60, 0x04, 0},
    {(u16**)DAT_060D7110, (s8*)DAT_060D7034, 0x0000, 0x060C, 0x67, 0x04, 0},
    {(u16**)DAT_060D70F4, (s8*)DAT_060D7034, 0x0000, 0x060C, 0x67, 0x04, 0},
    {(u16**)DAT_060D70F4, (s8*)DAT_060D7034, 0x0000, 0x060C, 0x67, 0x04, 0},
    {(u16**)DAT_060D70F4, (s8*)DAT_060D7034, 0x0000, 0x060C, 0x67, 0x04, 0},
};
u32 DAT_060D712C_tail[4] = {
    0x060D70BC,
    0x060D7034,
    0x000006A2,
    0x67000000,
};

u32 DAT_060D71BC[87] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000010, 0x0000000F, 0x00000000, 0x00000001, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000010, 0x00000010,
    0x00000001, 0x00000008, 0x00000008, 0x00000008, 0x00000000, 0x00000008,
    0x00000010, 0x00000008, 0x00000001, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000010, 0x0000000F, 0x00000000,
    0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000010, 0x00000010, 0x00000001, 0x00000008, 0x00000008, 0x00000008,
    0x00000000, 0x00000008, 0x00000010, 0x00000008, 0x00000001, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000025, 0x01000001, 0x00200F00, 0x00000030, 0x00000001,
    0x00180080, 0x00000025, 0x0F400001, 0x002000C0, 0x00000030, 0x00000001,
    0x00180140, 0x00800080, 0x00900000, 0x00C00060, 0x00000000, 0x00000060,
    0x00A00000, 0x00400048, 0x00400000,
};

SaturnSpriteImage DAT_060D7318[21] = {
    {24, 12, 0x0000}, {52, 16, 0x0048}, {40, 8, 0x0118},  {40, 8, 0x0168},
    {40, 12, 0x01B8}, {20, 12, 0x0230}, {28, 12, 0x026C}, {44, 20, 0x02C0},
    {32, 20, 0x039C}, {24, 8, 0x043C},  {24, 8, 0x046C},  {28, 8, 0x049C},
    {16, 8, 0x04D4},  {20, 20, 0x04F4}, {20, 20, 0x0558}, {20, 20, 0x05BC},
    {20, 20, 0x0620}, {20, 20, 0x0684}, {20, 20, 0x06E8}, {20, 20, 0x074C},
    {0, 0, 0x07B0},
};

SaturnSpriteFrameHeader DAT_060D736C = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7370 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D737C = {
    {0x0100, 0x0000},
    {
        {0x0010, -23, -24, 0},
    },
};

SaturnSpriteFrame2 DAT_060D7388 = {
    {0x0200, 0x0000},
    {
        {0x0100, 32, -3, 1},
        {0x0000, 55, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D739C = {
    {0x0100, 0x0000},
    {
        {0x0000, 55, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D73A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 55, -14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 52, -16, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D73CC = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -17, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -14, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D73F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D73FC = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, -3, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7408 = {
    {0x0100, 0x0000},
    {
        {0x0000, -21, -2, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7414 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7420 = {
    {0x0100, 0x0000},
    {
        {0x0010, -29, -5, 0},
    },
};

SaturnSpriteFrame2 DAT_060D742C = {
    {0x0200, 0x0000},
    {
        {0x0100, 22, 14, 1},
        {0x0000, 45, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7440 = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, 3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D744C = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, 3, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7458 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7464 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, 4, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7470 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D747C = {
    {0x0100, 0x0000},
    {
        {0x0000, -1, 4, 0},
    },
};

SaturnSpriteFrame2 DAT_060D7488 = {
    {0x0200, 0x0000},
    {
        {0x0100, 18, 17, 7},
        {0x0000, 38, 29, 8},
    },
};

SaturnSpriteFrame1 DAT_060D749C = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, 28, 8},
    },
};

SaturnSpriteFrame1 DAT_060D74A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, 22, 8},
    },
};

SaturnSpriteFrame1 DAT_060D74B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, 8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D74C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, 4, 9},
    },
};

SaturnSpriteFrame1 DAT_060D74CC = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 3, 9},
    },
};

SaturnSpriteFrame1 DAT_060D74D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -12, 10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D74E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, 11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D74F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, 12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D74FC = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7508 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7514 = {
    {0x0100, 0x0000},
    {
        {0x0010, -25, -26, 0},
    },
};

SaturnSpriteFrame2 DAT_060D7520 = {
    {0x0200, 0x0000},
    {
        {0x0100, 33, -3, 1},
        {0x0000, 52, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7534 = {
    {0x0100, 0x0000},
    {
        {0x0000, 53, -16, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7540 = {
    {0x0100, 0x0000},
    {
        {0x0000, 53, -16, 3},
    },
};

SaturnSpriteFrame1 DAT_060D754C = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -18, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7558 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, -13, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7564 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -19, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7570 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -16, 0},
    },
};

SaturnSpriteFrame1 DAT_060D757C = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7588 = {
    {0x0100, 0x0000},
    {
        {0x0000, -13, -7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7594 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D75A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, -5, 5},
    },
};

SaturnSpriteFrame1 DAT_060D75AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75B8 = {
    {0x0100, 0x0000},
    {
        {0x0010, -34, -27, 0},
    },
};

SaturnSpriteFrame2 DAT_060D75C4 = {
    {0x0200, 0x0000},
    {
        {0x0100, 26, -3, 1},
        {0x0000, 47, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D75D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D75E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, -14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D75F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 43, -16, 3},
    },
};

SaturnSpriteFrame1 DAT_060D75FC = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -17, 10},
    },
};

SaturnSpriteFrame1 DAT_060D7608 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -18, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7614 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -17, 0},
    },
};

SaturnSpriteFrame2 DAT_060D7620 = {
    {0x0200, 0x0000},
    {
        {0x0100, 26, 7, 7},
        {0x0000, 46, 19, 8},
    },
};

SaturnSpriteFrame1 DAT_060D7634 = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, 18, 8},
    },
};

SaturnSpriteFrame1 DAT_060D7640 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 10, 8},
    },
};

SaturnSpriteFrame1 DAT_060D764C = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7658 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -11, 11},
    },
};

SaturnSpriteFrame1 DAT_060D7664 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -13, 12},
    },
};

SaturnSpriteFrame1 DAT_060D7670 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D767C = {
    {0x0100, 0x0000},
    {
        {0x0000, -13, -5, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7688 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7694 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, -3, 5},
    },
};

SaturnSpriteFrame1 DAT_060D76A0 = {
    {0x0100, 0x0000},
    {
        {0x0200, -4, 21, 13},
    },
};

SaturnSpriteFrame1 DAT_060D76AC = {
    {0x0100, 0x0000},
    {
        {0x0300, -4, 21, 14},
    },
};

SaturnSpriteFrame1 DAT_060D76B8 = {
    {0x0100, 0x0000},
    {
        {0x0400, -4, 21, 15},
    },
};

SaturnSpriteFrame1 DAT_060D76C4 = {
    {0x0100, 0x0000},
    {
        {0x0500, -4, 21, 16},
    },
};

SaturnSpriteFrame1 DAT_060D76D0 = {
    {0x0100, 0x0000},
    {
        {0x0600, -4, 21, 17},
    },
};

SaturnSpriteFrame1 DAT_060D76DC = {
    {0x0100, 0x0000},
    {
        {0x0700, -4, 21, 18},
    },
};

SaturnSpriteFrame1 DAT_060D76E8 = {
    {0x0100, 0x0000},
    {
        {0x0800, -4, 21, 19},
    },
};

SaturnSpriteFrame1 DAT_060D76F4 = {
    {0x0100, 0x0000},
    {
        {0x0900, -4, 21, 13},
    },
};

SaturnSpriteFrame1 DAT_060D7700 = {
    {0x0100, 0x0000},
    {
        {0x0A00, -4, 21, 14},
    },
};

SaturnSpriteFrame1 DAT_060D770C = {
    {0x0100, 0x0000},
    {
        {0x0B00, -4, 21, 15},
    },
};

SaturnSpriteFrame1 DAT_060D7718 = {
    {0x0100, 0x0000},
    {
        {0x0C00, -4, 21, 16},
    },
};

SaturnSpriteFrame1 DAT_060D7724 = {
    {0x0100, 0x0000},
    {
        {0x0D00, -4, 21, 17},
    },
};

SaturnSpriteFrame1 DAT_060D7730 = {
    {0x0100, 0x0000},
    {
        {0x0E00, -4, 21, 18},
    },
};

SaturnSpriteFrame1 DAT_060D773C = {
    {0x0100, 0x0000},
    {
        {0x0F00, -4, 21, 19},
    },
};

SaturnSpriteFrame1 DAT_060D7748 = {
    {0x0100, 0x0000},
    {
        {0x1000, -4, 21, 13},
    },
};

SaturnSpriteFrame1 DAT_060D7754 = {
    {0x0100, 0x0000},
    {
        {0x1100, -4, 21, 14},
    },
};

SaturnSpriteFrame1 DAT_060D7760 = {
    {0x0100, 0x0000},
    {
        {0x1200, -4, 21, 15},
    },
};

SaturnSpriteFrame1 DAT_060D776C = {
    {0x0100, 0x0000},
    {
        {0x1300, -4, 21, 16},
    },
};

SaturnSpriteFrame1 DAT_060D7778 = {
    {0x0100, 0x0000},
    {
        {0x1400, -4, 21, 17},
    },
};

SaturnSpriteFrame1 DAT_060D7784 = {
    {0x0100, 0x0000},
    {
        {0x1500, -4, 21, 18},
    },
};

SaturnSpriteFrame1 DAT_060D7790 = {
    {0x0100, 0x0000},
    {
        {0x1600, -4, 21, 19},
    },
};

SaturnSpriteFrame1 DAT_060D779C = {
    {0x0100, 0x0000},
    {
        {0x1700, -4, 21, 13},
    },
};

SaturnSpriteFrame1 DAT_060D77A8 = {
    {0x0100, 0x0000},
    {
        {0x1800, -4, 21, 14},
    },
};

SaturnSpriteFrame1 DAT_060D77B4 = {
    {0x0100, 0x0000},
    {
        {0x1900, -4, 21, 15},
    },
};

SaturnSpriteFrame1 DAT_060D77C0 = {
    {0x0100, 0x0000},
    {
        {0x1A00, -4, 21, 16},
    },
};

SaturnSpriteFrame1 DAT_060D77CC = {
    {0x0100, 0x0000},
    {
        {0x1B00, -4, 21, 17},
    },
};

SaturnSpriteFrame1 DAT_060D77D8 = {
    {0x0100, 0x0000},
    {
        {0x1C00, -4, 21, 18},
    },
};

SaturnSpriteFrame1 DAT_060D77E4 = {
    {0x0100, 0x0000},
    {
        {0x1D00, -4, 21, 19},
    },
};

SaturnSpriteFrameHeader* DAT_060D77F0[93] = {
    (SaturnSpriteFrameHeader*)&DAT_060D736C,
    (SaturnSpriteFrameHeader*)&DAT_060D7370,
    (SaturnSpriteFrameHeader*)&DAT_060D737C,
    (SaturnSpriteFrameHeader*)&DAT_060D7388,
    (SaturnSpriteFrameHeader*)&DAT_060D739C,
    (SaturnSpriteFrameHeader*)&DAT_060D73A8,
    (SaturnSpriteFrameHeader*)&DAT_060D73B4,
    (SaturnSpriteFrameHeader*)&DAT_060D73C0,
    (SaturnSpriteFrameHeader*)&DAT_060D73CC,
    (SaturnSpriteFrameHeader*)&DAT_060D73D8,
    (SaturnSpriteFrameHeader*)&DAT_060D73E4,
    (SaturnSpriteFrameHeader*)&DAT_060D73F0,
    (SaturnSpriteFrameHeader*)&DAT_060D73FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7408,
    (SaturnSpriteFrameHeader*)&DAT_060D7414,
    (SaturnSpriteFrameHeader*)&DAT_060D7420,
    (SaturnSpriteFrameHeader*)&DAT_060D742C,
    (SaturnSpriteFrameHeader*)&DAT_060D7440,
    (SaturnSpriteFrameHeader*)&DAT_060D744C,
    (SaturnSpriteFrameHeader*)&DAT_060D7458,
    (SaturnSpriteFrameHeader*)&DAT_060D7464,
    (SaturnSpriteFrameHeader*)&DAT_060D7470,
    (SaturnSpriteFrameHeader*)&DAT_060D747C,
    (SaturnSpriteFrameHeader*)&DAT_060D7488,
    (SaturnSpriteFrameHeader*)&DAT_060D749C,
    (SaturnSpriteFrameHeader*)&DAT_060D74A8,
    (SaturnSpriteFrameHeader*)&DAT_060D74B4,
    (SaturnSpriteFrameHeader*)&DAT_060D74C0,
    (SaturnSpriteFrameHeader*)&DAT_060D74CC,
    (SaturnSpriteFrameHeader*)&DAT_060D74D8,
    (SaturnSpriteFrameHeader*)&DAT_060D74E4,
    (SaturnSpriteFrameHeader*)&DAT_060D74F0,
    (SaturnSpriteFrameHeader*)&DAT_060D74FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7508,
    (SaturnSpriteFrameHeader*)&DAT_060D7514,
    (SaturnSpriteFrameHeader*)&DAT_060D7520,
    (SaturnSpriteFrameHeader*)&DAT_060D7534,
    (SaturnSpriteFrameHeader*)&DAT_060D7540,
    (SaturnSpriteFrameHeader*)&DAT_060D754C,
    (SaturnSpriteFrameHeader*)&DAT_060D7558,
    (SaturnSpriteFrameHeader*)&DAT_060D7564,
    (SaturnSpriteFrameHeader*)&DAT_060D7570,
    (SaturnSpriteFrameHeader*)&DAT_060D757C,
    (SaturnSpriteFrameHeader*)&DAT_060D7588,
    (SaturnSpriteFrameHeader*)&DAT_060D7594,
    (SaturnSpriteFrameHeader*)&DAT_060D75A0,
    (SaturnSpriteFrameHeader*)&DAT_060D75AC,
    (SaturnSpriteFrameHeader*)&DAT_060D75B8,
    (SaturnSpriteFrameHeader*)&DAT_060D75C4,
    (SaturnSpriteFrameHeader*)&DAT_060D75D8,
    (SaturnSpriteFrameHeader*)&DAT_060D75E4,
    (SaturnSpriteFrameHeader*)&DAT_060D75F0,
    (SaturnSpriteFrameHeader*)&DAT_060D75FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7608,
    (SaturnSpriteFrameHeader*)&DAT_060D7614,
    (SaturnSpriteFrameHeader*)&DAT_060D7620,
    (SaturnSpriteFrameHeader*)&DAT_060D7634,
    (SaturnSpriteFrameHeader*)&DAT_060D7640,
    (SaturnSpriteFrameHeader*)&DAT_060D764C,
    (SaturnSpriteFrameHeader*)&DAT_060D7658,
    (SaturnSpriteFrameHeader*)&DAT_060D7664,
    (SaturnSpriteFrameHeader*)&DAT_060D7670,
    (SaturnSpriteFrameHeader*)&DAT_060D767C,
    (SaturnSpriteFrameHeader*)&DAT_060D7688,
    (SaturnSpriteFrameHeader*)&DAT_060D7694,
    (SaturnSpriteFrameHeader*)&DAT_060D76A0,
    (SaturnSpriteFrameHeader*)&DAT_060D76AC,
    (SaturnSpriteFrameHeader*)&DAT_060D76B8,
    (SaturnSpriteFrameHeader*)&DAT_060D76C4,
    (SaturnSpriteFrameHeader*)&DAT_060D76D0,
    (SaturnSpriteFrameHeader*)&DAT_060D76DC,
    (SaturnSpriteFrameHeader*)&DAT_060D76E8,
    (SaturnSpriteFrameHeader*)&DAT_060D76F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7700,
    (SaturnSpriteFrameHeader*)&DAT_060D770C,
    (SaturnSpriteFrameHeader*)&DAT_060D7718,
    (SaturnSpriteFrameHeader*)&DAT_060D7724,
    (SaturnSpriteFrameHeader*)&DAT_060D7730,
    (SaturnSpriteFrameHeader*)&DAT_060D773C,
    (SaturnSpriteFrameHeader*)&DAT_060D7748,
    (SaturnSpriteFrameHeader*)&DAT_060D7754,
    (SaturnSpriteFrameHeader*)&DAT_060D7760,
    (SaturnSpriteFrameHeader*)&DAT_060D776C,
    (SaturnSpriteFrameHeader*)&DAT_060D7778,
    (SaturnSpriteFrameHeader*)&DAT_060D7784,
    (SaturnSpriteFrameHeader*)&DAT_060D7790,
    (SaturnSpriteFrameHeader*)&DAT_060D779C,
    (SaturnSpriteFrameHeader*)&DAT_060D77A8,
    (SaturnSpriteFrameHeader*)&DAT_060D77B4,
    (SaturnSpriteFrameHeader*)&DAT_060D77C0,
    (SaturnSpriteFrameHeader*)&DAT_060D77CC,
    (SaturnSpriteFrameHeader*)&DAT_060D77D8,
    (SaturnSpriteFrameHeader*)&DAT_060D77E4,
};

struct {
    u16 countAndFlags;
    u16 colors[9][16];
    u16 padding[1];
} DAT_060D7964 = {
    0x0009,
    {
        {0x8000, 0x8421, 0x84CA, 0x952F, 0xA173, 0x9218, 0x9EDF, 0xA0A4, 0x83E0,
         0xBBF6, 0x8623, 0xA94A, 0xC5A7, 0xDA4F, 0xDF37, 0xEF99},
        {0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
         0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
        {0x8000, 0x8421, 0x84CA, 0x952F, 0xA173, 0x9218, 0x9EDF, 0xA0A4, 0x83E0,
         0xBBF6, 0x8623, 0x871F, 0x8E5F, 0xDA4F, 0x810E, 0xEF99},
        {0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
         0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
        {0x8000, 0x8421, 0x84CA, 0x952F, 0xA173, 0x9218, 0x9EDF, 0xA0A4, 0x83E0,
         0xBBF6, 0x8623, 0xFF4F, 0xC5A7, 0xDA4F, 0xDF37, 0xEF99},
        {0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
         0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
        {0x8000, 0x8421, 0x84CA, 0x952F, 0xA173, 0x9218, 0x9EDF, 0xA0A4, 0x83E0,
         0xBBF6, 0x8623, 0x8DC2, 0x8D01, 0xDA4F, 0x8000, 0xEF99},
        {0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
         0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000},
        {0xC210, 0xC210, 0xC210, 0xC210, 0xC210, 0xC210, 0xC210, 0xC210, 0xC210,
         0xC210, 0xC210, 0xC210, 0xC210, 0xC210, 0xC210, 0xC210},
    },
    {0x0000},
};

SaturnSpriteResource DAT_060D7A88 = {
    DAT_060D7318, (u16*)&DAT_060D7964, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7A94[1] = {&DAT_060D7A88};
