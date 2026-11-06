// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6140();
void func_060D6580();
void func_060D6800();
void func_060D6974();
void func_060D698C();
void func_060D69A4();
void func_060D69BC();
void func_060D69C8();
void func_060D69E0();
void func_060D69F8();
void func_060D6A10();
void func_060D6A28();
void func_060D6A40();
void func_060D6A58();
void func_060D6A70();
void func_060D6A88();
extern SaturnSpriteResource* DAT_060D7378[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6140,
        func_060D6580,
        func_060D6800,
        func_060D6974,
        func_060D698C,
        func_060D69A4,
        func_060D69BC,
        func_060D6A88,
        func_060D69C8,
        func_060D69E0,
        func_060D69F8,
        func_060D6A10,
        func_060D6A28,
        func_060D6A40,
        func_060D6A58,
        func_060D6A70,
    },
    DAT_060D7378,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6140, func_060D6140);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6580, func_060D6580);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6800, func_060D6800);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6974, func_060D6974);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D698C, func_060D698C);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D69A4, func_060D69A4);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D69BC, func_060D69BC);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D69C8, func_060D69C8);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D69E0, func_060D69E0);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D69F8, func_060D69F8);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6A10, func_060D6A10);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6A28, func_060D6A28);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6A40, func_060D6A40);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6A58, func_060D6A58);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6A70, func_060D6A70);
INCLUDE_ASM("asm/saturn/weapon/w_43/f_nonmat", f60D6A88, func_060D6A88);

u16 DAT_060D6AA0[14] = {0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607,
                        0x0608, 0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D6ABC[14] = {0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14,
                        0x0E15, 0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6AD8[14] = {0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C,
                        0x141D, 0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6AF4[11] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D6B0A[11] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D6B20[11] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF};

u16 DAT_060D6B36[43] = {
    0x0002, 0x0023, 0x0001, 0x0024, 0x0001, 0x0025, 0x0001, 0x0026, 0x0001,
    0x0027, 0x0001, 0x0028, 0x0001, 0x0029, 0x0001, 0x002A, 0x0002, 0x002B,
    0x0004, 0x002C, 0x0002, 0x0023, 0x0001, 0x0024, 0x0001, 0x0025, 0x0001,
    0x0026, 0x0001, 0x0027, 0x0001, 0x0028, 0x0001, 0x0029, 0x0001, 0x002A,
    0x0002, 0x002B, 0x0008, 0x002C, 0xFFFF, 0x0000, 0x0000,
};

s8 DAT_060D6B8C[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D6BF0[7] = {DAT_060D6AA0, DAT_060D6AA0, DAT_060D6ABC, DAT_060D6AD8,
                        DAT_060D6AF4, DAT_060D6B0A, DAT_060D6B20};

WeaponAnimation DAT_060D6C0C[3] = {
    {(u16**)DAT_060D6BF0, (s8*)DAT_060D6B8C, 0x0000, 0x06A8, 0x39, 0x04, 0},
    {(u16**)DAT_060D6BF0, (s8*)DAT_060D6B8C, 0x0000, 0x06A8, 0x39, 0x04, 0},
    {(u16**)DAT_060D6BF0, (s8*)DAT_060D6B8C, 0x0001, 0x06A8, 0x39, 0x04, 0},
};
u32 DAT_060D6C0C_tail[1] = {
    0xC3ECC3E8,
};

u32 DAT_060D6C40[1] = {
    0xFD8CFE10,
};

SaturnSpriteImage DAT_060D6C44[7] = {
    {12, 5, 0x0000},  {44, 10, 0x0010}, {24, 4, 0x0080}, {8, 1, 0x0098},
    {32, 19, 0x009C}, {24, 12, 0x0134}, {0, 0, 0x017C},
};

SaturnSpriteFrameHeader DAT_060D6C60 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6C64 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C70 = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C7C = {
    {0x0100, 0x0000},
    {
        {0x0100, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C88 = {
    {0x0100, 0x0000},
    {
        {0x0200, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C94 = {
    {0x0100, 0x0000},
    {
        {0x0300, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CA0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CAC = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CB8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CC4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CD0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CDC = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CE8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CF4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D00 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D18 = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D24 = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D30 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D3C = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D48 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D54 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D60 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D6C = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D78 = {
    {0x0100, 0x0000},
    {
        {0x0100, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D84 = {
    {0x0100, 0x0000},
    {
        {0x0200, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D90 = {
    {0x0100, 0x0000},
    {
        {0x0300, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D9C = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6DA8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6DB4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6DC0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6DCC = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DD8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DE4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DF0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DFC = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E08 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E14 = {
    {0x0100, 0x0000},
    {
        {0x0100, 34, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E20 = {
    {0x0100, 0x0000},
    {
        {0x0200, 34, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E2C = {
    {0x0100, 0x0000},
    {
        {0x0300, 34, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E38 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E44 = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E50 = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E5C = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E68 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E74 = {
    {0x0100, 0x0000},
    {
        {0x0400, -5, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E8C = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E98 = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EA4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EBC = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EC8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6ED4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EE0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6EEC = {
    {0x0100, 0x0000},
    {
        {0x0100, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6EF8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F04 = {
    {0x0100, 0x0000},
    {
        {0x0300, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F10 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F1C = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F28 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F34 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F40 = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F4C = {
    {0x0100, 0x0000},
    {
        {0x0500, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F58 = {
    {0x0100, 0x0000},
    {
        {0x0600, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F64 = {
    {0x0100, 0x0000},
    {
        {0x0700, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F70 = {
    {0x0100, 0x0000},
    {
        {0x0500, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F7C = {
    {0x0100, 0x0000},
    {
        {0x0600, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F88 = {
    {0x0100, 0x0000},
    {
        {0x0700, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F94 = {
    {0x0100, 0x0000},
    {
        {0x0500, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FA0 = {
    {0x0100, 0x0000},
    {
        {0x0600, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FAC = {
    {0x0100, 0x0000},
    {
        {0x0700, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6FB8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 36, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FC4 = {
    {0x0100, 0x0000},
    {
        {0x0600, 36, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FD0 = {
    {0x0100, 0x0000},
    {
        {0x0700, 36, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FDC = {
    {0x0100, 0x0000},
    {
        {0x0500, 34, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FE8 = {
    {0x0100, 0x0000},
    {
        {0x0600, 34, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FF4 = {
    {0x0100, 0x0000},
    {
        {0x0700, 34, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7000 = {
    {0x0100, 0x0000},
    {
        {0x0500, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D700C = {
    {0x0100, 0x0000},
    {
        {0x0600, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7018 = {
    {0x0100, 0x0000},
    {
        {0x0700, 31, 3, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D7024[81] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6C60,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6CF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6D00,
    (SaturnSpriteFrameHeader*)&DAT_060D6D0C,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6DB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DCC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DD8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6E08,
    (SaturnSpriteFrameHeader*)&DAT_060D6E14,
    (SaturnSpriteFrameHeader*)&DAT_060D6E20,
    (SaturnSpriteFrameHeader*)&DAT_060D6E2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E38,
    (SaturnSpriteFrameHeader*)&DAT_060D6E44,
    (SaturnSpriteFrameHeader*)&DAT_060D6E50,
    (SaturnSpriteFrameHeader*)&DAT_060D6E5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E68,
    (SaturnSpriteFrameHeader*)&DAT_060D6E74,
    (SaturnSpriteFrameHeader*)&DAT_060D6E80,
    (SaturnSpriteFrameHeader*)&DAT_060D6E8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E98,
    (SaturnSpriteFrameHeader*)&DAT_060D6EA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6EB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6EC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6ED4,
    (SaturnSpriteFrameHeader*)&DAT_060D6EE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6EF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6F04,
    (SaturnSpriteFrameHeader*)&DAT_060D6F10,
    (SaturnSpriteFrameHeader*)&DAT_060D6F1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F28,
    (SaturnSpriteFrameHeader*)&DAT_060D6F34,
    (SaturnSpriteFrameHeader*)&DAT_060D6F40,
    (SaturnSpriteFrameHeader*)&DAT_060D6F4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F58,
    (SaturnSpriteFrameHeader*)&DAT_060D6F64,
    (SaturnSpriteFrameHeader*)&DAT_060D6F70,
    (SaturnSpriteFrameHeader*)&DAT_060D6F7C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F88,
    (SaturnSpriteFrameHeader*)&DAT_060D6F94,
    (SaturnSpriteFrameHeader*)&DAT_060D6FA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6FB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6FC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6FD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6FE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6FF4,
    (SaturnSpriteFrameHeader*)&DAT_060D7000,
    (SaturnSpriteFrameHeader*)&DAT_060D700C,
    (SaturnSpriteFrameHeader*)&DAT_060D7018,
};

struct {
    u16 countAndFlags;
    u16 colors[16][16];
    u16 padding[1];
} DAT_060D7168 = {
    0x0010,
    {
        {0x98C6, 0x8000, 0xFD61, 0xA5C0, 0xFD61, 0xFD61, 0xFD61, 0xFD61, 0x843F,
         0xE9A4, 0xC481, 0xD0A0, 0xD0E0, 0xD000, 0xD294, 0xF2F3},
        {0x98C6, 0x8000, 0xC0E0, 0x8000, 0xDD65, 0xFE0C, 0xFE0C, 0xFE0C, 0x843F,
         0xFD20, 0xFD20, 0xFE0C, 0xFE0C, 0xFE0C, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x9C00, 0xA5C0, 0xC860, 0xA800, 0xFD00, 0xFD00, 0x801F,
         0xFD40, 0xFD20, 0xFD00, 0xDDC0, 0xBC00, 0xD294, 0xEAD3},
        {0x98C6, 0x8000, 0x9800, 0xA5C0, 0xA880, 0xAC00, 0xBD40, 0xBC80, 0x843F,
         0xD4C0, 0xFD20, 0xB4E0, 0xFE88, 0xA060, 0xD294, 0xFECC},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0xFD40, 0xA5C0, 0xFD40, 0xFD40, 0xFD40, 0xFD40, 0x843F,
         0xC1C0, 0x801F, 0xBC00, 0xBC00, 0xBC00, 0xD294, 0xFF51},
        {0x98C6, 0x8000, 0xA000, 0xA5C0, 0xFD00, 0xFD00, 0xFD00, 0xFD00, 0x843F,
         0xC1C0, 0x801F, 0xB400, 0xB400, 0xB400, 0xD294, 0xF39C},
        {0x98C6, 0x8000, 0x9C00, 0xA5C0, 0xD400, 0x9C20, 0xFDC0, 0xA840, 0x843F,
         0xC1C0, 0x801F, 0xB800, 0xB800, 0xB800, 0xD294, 0xEA90},
        {0x98C6, 0x8000, 0xA641, 0x93E0, 0xA641, 0xA641, 0xA641, 0xA641, 0x843F,
         0xAB04, 0x96C4, 0x8D60, 0xA980, 0x9100, 0xD294, 0xF2F3},
        {0x98C6, 0x8000, 0x8D00, 0x8000, 0x9D80, 0xC746, 0xC746, 0xC746, 0x843F,
         0xBE20, 0xBE20, 0xC746, 0xC746, 0xC746, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x8860, 0x9380, 0x8CE0, 0x90A0, 0xBE81, 0xBE81, 0x801F,
         0x9620, 0xBA20, 0xCAE1, 0x80C0, 0x94C0, 0xD294, 0xEAD3},
        {0x98C6, 0x8000, 0x8440, 0x93E0, 0x80A0, 0x8120, 0x9AE0, 0x80C0, 0x843F,
         0x81E0, 0xA620, 0x80C0, 0xCFC2, 0x8080, 0xD294, 0xD7EC},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0x80E0, 0x82A0, 0x80E0, 0x80E0, 0x80E0, 0x80E0, 0x843F,
         0x82A0, 0x801F, 0x8060, 0x8040, 0x8840, 0xD294, 0xF2D1},
        {0x98C6, 0x8000, 0x8C60, 0x82A0, 0xA8E0, 0xA8E0, 0xA8E0, 0xA8E0, 0x843F,
         0x82A0, 0x801F, 0x9460, 0x9460, 0x9460, 0xD294, 0xF39C},
        {0x98C6, 0x8000, 0x8840, 0x82A0, 0x80E0, 0x8840, 0x9180, 0x8840, 0x843F,
         0x82A0, 0x801F, 0x8840, 0x8840, 0x8840, 0xD294, 0xEA90},
    },
    {0x0000},
};

SaturnSpriteResource DAT_060D736C = {
    DAT_060D6C44, (u16*)&DAT_060D7168, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7378[1] = {&DAT_060D736C};
