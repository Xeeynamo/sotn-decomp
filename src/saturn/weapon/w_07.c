// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62FC();
void func_060D6678();
void func_060D67E0();
void func_060D67F8();
void func_060D6810();
void func_060D6828();
void func_060D6834();
void func_060D684C();
void func_060D6864();
void func_060D687C();
void func_060D6894();
void func_060D68AC();
void func_060D68C4();
void func_060D68DC();
void func_060D68F4();
extern SaturnSpriteResource* DAT_060D6FA8[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62FC,
        func_060D6678,
        func_060D67E0,
        func_060D67F8,
        func_060D6810,
        func_060D6828,
        func_060D68F4,
        func_060D6834,
        func_060D684C,
        func_060D6864,
        func_060D687C,
        func_060D6894,
        func_060D68AC,
        func_060D68C4,
        func_060D68DC,
    },
    DAT_060D6FA8,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D62FC, func_060D62FC);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D65E0, func_060D65E0);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D6678, func_060D6678);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D67E0, func_060D67E0);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D67F8, func_060D67F8);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D6810, func_060D6810);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D6828, func_060D6828);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D6834, func_060D6834);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D684C, func_060D684C);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D6864, func_060D6864);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D687C, func_060D687C);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D6894, func_060D6894);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D68AC, func_060D68AC);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D68C4, func_060D68C4);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D68DC, func_060D68DC);
INCLUDE_ASM("asm/saturn/weapon/w_07/f_nonmat", f60D68F4, func_060D68F4);

u16 DAT_060D6900[14] = {0x2A01, 0x2C02, 0x0403, 0x2E04, 0x3005, 0x3206, 0x0807,
                        0x0808, 0x0809, 0x340A, 0x340B, 0x340C, 0x340D, 0xFFFF};

u16 DAT_060D691C[14] = {0x360E, 0x380F, 0x0E10, 0x3A11, 0x3C12, 0x3E13, 0x1214,
                        0x1215, 0x1216, 0x401E, 0x401F, 0x4020, 0x4021, 0xFFFF};

u16 DAT_060D6938[14] = {0x360E, 0x380F, 0x4217, 0x4418, 0x4419, 0x461A, 0x1A1B,
                        0x1A1C, 0x1A1D, 0x401E, 0x401F, 0x4020, 0x4021, 0xFFFF};

u16 DAT_060D6954[14] = {0x2A01, 0x2C02, 0x0403, 0x2E04, 0x3005, 0x3206, 0x0807,
                        0x0808, 0x0809, 0x340A, 0x340B, 0x340C, 0x340D, 0xFFFF};

u16 DAT_060D6970[11] = {0x482C, 0x4A2D, 0x042E, 0x4C2F, 0x4E30, 0x5031,
                        0x0832, 0x0833, 0x0834, 0x523C, 0xFFFF};

u16 DAT_060D6986[11] = {0x482C, 0x4A2D, 0x5435, 0x5636, 0x5637, 0x5838,
                        0x2239, 0x223A, 0x223B, 0x523C, 0xFFFF};

u32 DAT_060D699C[5] = {
    0x0004243D, 0x0004243E, 0x0004243F, 0x00042440, 0x00000000,
};

s8 DAT_060D69B0[45][4] = {
    {0, 0, 0, 0},      {-4, -26, 15, 4},  {33, -27, 20, 6},  {50, -18, 10, 8},
    {21, -9, 15, 8},   {-19, -4, 5, 4},   {-13, -8, 15, 4},  {24, -11, 20, 8},
    {40, -1, 10, 8},   {19, 8, 15, 8},    {28, 3, 23, 4},    {21, 2, 15, 12},
    {36, 19, 10, 8},   {14, 18, 15, 8},   {-29, 14, 5, 4},   {-18, -28, 15, 4},
    {30, 4, 25, 12},   {8, -3, 20, 8},    {1, 0, 10, 8},     {0, 0, 19, 15},
    {1, 2, 35, 28},    {-14, -26, 10, 8}, {11, -32, 13, 10}, {50, -21, 10, 8},
    {50, -15, 19, 6},  {36, -9, 15, 8},   {-23, -4, 8, 4},   {-23, -7, 10, 8},
    {0, -14, 10, 8},   {40, -5, 10, 8},   {40, 2, 19, 6},    {29, 8, 15, 8},
    {-33, 14, 8, 4},   {26, 2, 20, 12},   {36, 19, 16, 8},   {14, 18, 19, 8},
    {-24, -28, 10, 8}, {-5, -34, 10, 8},  {38, -18, 10, 10}, {41, -15, 19, 6},
    {26, -9, 15, 8},   {-26, -4, 8, 4},   {33, -4, 25, 22},  {48, 8, 13, 8},
    {13, -3, 20, 8}};

u16* DAT_060D6A64[7] = {DAT_060D6900, DAT_060D6900, DAT_060D691C, DAT_060D6938,
                        DAT_060D6954, DAT_060D6970, DAT_060D6986};

WeaponAnimation DAT_060D6A80[2] = {
    {(u16**)DAT_060D6A64, (s8*)DAT_060D69B0, 0x000F, 0x0689, 0x40, 0x03, 0},
    {(u16**)DAT_060D6A64, (s8*)DAT_060D69B0, 0x000F, 0x0689, 0x40, 0x03, 0},
};

u32 DAT_060D6AA0[7] = {
    0x0028FFF2, 0x0028FFF2, 0x00280004, 0x00240014,
    0x0028FFF2, 0x0028FFF3, 0x00280010,
};

SaturnSpriteImage DAT_060D6ABC[13] = {
    {12, 9, 0x0000},  {24, 7, 0x001C}, {16, 4, 0x0048},  {16, 5, 0x0058},
    {24, 16, 0x006C}, {16, 4, 0x00CC}, {12, 8, 0x00DC},  {12, 8, 0x00F4},
    {12, 8, 0x010C},  {12, 8, 0x0124}, {48, 39, 0x013C}, {0, 0, 0x0310},
    {0, 0, 0x0310},
};

struct {
    u16 countAndFlags;
    u16 colors[4][16];
} DAT_060D6AF0 = {
    0x0004,
    {
        {0x9132, 0x8C41, 0x9BE3, 0xBD8A, 0xACA1, 0xC503, 0xD9A7, 0xDE2B, 0xE2AF,
         0x9084, 0x9D08, 0xA96C, 0xB9F0, 0xC654, 0xD2D8, 0xE35C},
        {0x8120, 0xBC00, 0xC800, 0xD923, 0xEDC8, 0xFED1, 0xFF73, 0xFFFF, 0x8400,
         0xBDAD, 0xCE10, 0xE6D6, 0xF35A, 0x8000, 0xFFB5, 0x8400},
        {0xC006, 0xC046, 0xC086, 0xC0C6, 0xC106, 0xC146, 0xC186, 0xC1C6, 0xC206,
         0xC246, 0xC286, 0xC2C6, 0xC306, 0xC346, 0xC386, 0xC3C6},
        {0xC008, 0xC048, 0xC088, 0xC0C8, 0xC108, 0xC148, 0xC188, 0xC1C8, 0xC208,
         0xC248, 0xC288, 0xC2C8, 0xC308, 0xC348, 0xC388, 0xC3C8},
    },
};

SaturnSpriteFrameHeader DAT_060D6B72 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6B76 = {
    {0x0100, 0x0000},
    {
        {0x0010, -12, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6B82 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6B8E = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -29, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6B9A = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -21, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BA6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 53, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6BB2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -9, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6BBE = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BCA = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BD6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BE2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -15, -3, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BEE = {
    {0x0100, 0x0000},
    {
        {0x0010, -17, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BFA = {
    {0x0100, 0x0000},
    {
        {0x0010, -18, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C06 = {
    {0x0100, 0x0000},
    {
        {0x0010, -19, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C12 = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C1E = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -11, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C2A = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -13, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C36 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C42 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C4E = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 8, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C5A = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C66 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C72 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C7E = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6C8A = {
    {0x0100, 0x0000},
    {
        {0x0000, 41, 16, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C96 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 23, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CA2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 21, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CAE = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 19, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CBA = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 17, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CC6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CD2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -23, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CDE = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, 13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CEA = {
    {0x0100, 0x0000},
    {
        {0x0010, -25, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CF6 = {
    {0x0100, 0x0000},
    {
        {0x0010, -26, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D02 = {
    {0x0100, 0x0000},
    {
        {0x0010, -7, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D0E = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -30, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D1A = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -32, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D26 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D32 = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D3E = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D4A = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D56 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D62 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D6E = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D7A = {
    {0x0100, 0x0000},
    {
        {0x0010, -22, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D86 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -30, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D92 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, -30, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D9E = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DAA = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DB6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -10, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DC2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DCE = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DDA = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DE6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -9, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DF2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 49, 5, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6DFE = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E0A = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E16 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E22 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E2E = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E3A = {
    {0x0100, 0x0000},
    {
        {0x0010, -22, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E46 = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 0, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6E52 = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 0, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6E5E = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 0, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6E6A = {
    {0x0100, 0x0000},
    {
        {0x0100, 2, 0, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6E76 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, 1, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6E82 = {
    {0x0100, 0x0000},
    {
        {0x0300, -49, -39, 11},
    },
};
u16 DAT_060D6E82_tail[1] = {
    0x0000,
};

SaturnSpriteFrameHeader* DAT_060D6E90[67] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6B72,
    (SaturnSpriteFrameHeader*)&DAT_060D6B76,
    (SaturnSpriteFrameHeader*)&DAT_060D6B82,
    (SaturnSpriteFrameHeader*)&DAT_060D6B8E,
    (SaturnSpriteFrameHeader*)&DAT_060D6B9A,
    (SaturnSpriteFrameHeader*)&DAT_060D6BA6,
    (SaturnSpriteFrameHeader*)&DAT_060D6BB2,
    (SaturnSpriteFrameHeader*)&DAT_060D6BBE,
    (SaturnSpriteFrameHeader*)&DAT_060D6BCA,
    (SaturnSpriteFrameHeader*)&DAT_060D6BD6,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE2,
    (SaturnSpriteFrameHeader*)&DAT_060D6BEE,
    (SaturnSpriteFrameHeader*)&DAT_060D6BFA,
    (SaturnSpriteFrameHeader*)&DAT_060D6C06,
    (SaturnSpriteFrameHeader*)&DAT_060D6C12,
    (SaturnSpriteFrameHeader*)&DAT_060D6C1E,
    (SaturnSpriteFrameHeader*)&DAT_060D6C2A,
    (SaturnSpriteFrameHeader*)&DAT_060D6C36,
    (SaturnSpriteFrameHeader*)&DAT_060D6C42,
    (SaturnSpriteFrameHeader*)&DAT_060D6C4E,
    (SaturnSpriteFrameHeader*)&DAT_060D6C5A,
    (SaturnSpriteFrameHeader*)&DAT_060D6C66,
    (SaturnSpriteFrameHeader*)&DAT_060D6C72,
    (SaturnSpriteFrameHeader*)&DAT_060D6C7E,
    (SaturnSpriteFrameHeader*)&DAT_060D6C8A,
    (SaturnSpriteFrameHeader*)&DAT_060D6C96,
    (SaturnSpriteFrameHeader*)&DAT_060D6CA2,
    (SaturnSpriteFrameHeader*)&DAT_060D6CAE,
    (SaturnSpriteFrameHeader*)&DAT_060D6CBA,
    (SaturnSpriteFrameHeader*)&DAT_060D6CC6,
    (SaturnSpriteFrameHeader*)&DAT_060D6CD2,
    (SaturnSpriteFrameHeader*)&DAT_060D6CDE,
    (SaturnSpriteFrameHeader*)&DAT_060D6CEA,
    (SaturnSpriteFrameHeader*)&DAT_060D6CF6,
    (SaturnSpriteFrameHeader*)&DAT_060D6D02,
    (SaturnSpriteFrameHeader*)&DAT_060D6D0E,
    (SaturnSpriteFrameHeader*)&DAT_060D6D1A,
    (SaturnSpriteFrameHeader*)&DAT_060D6D26,
    (SaturnSpriteFrameHeader*)&DAT_060D6D32,
    (SaturnSpriteFrameHeader*)&DAT_060D6D3E,
    (SaturnSpriteFrameHeader*)&DAT_060D6D4A,
    (SaturnSpriteFrameHeader*)&DAT_060D6D56,
    (SaturnSpriteFrameHeader*)&DAT_060D6D62,
    (SaturnSpriteFrameHeader*)&DAT_060D6D6E,
    (SaturnSpriteFrameHeader*)&DAT_060D6D7A,
    (SaturnSpriteFrameHeader*)&DAT_060D6D86,
    (SaturnSpriteFrameHeader*)&DAT_060D6D92,
    (SaturnSpriteFrameHeader*)&DAT_060D6D9E,
    (SaturnSpriteFrameHeader*)&DAT_060D6DAA,
    (SaturnSpriteFrameHeader*)&DAT_060D6DB6,
    (SaturnSpriteFrameHeader*)&DAT_060D6DC2,
    (SaturnSpriteFrameHeader*)&DAT_060D6DCE,
    (SaturnSpriteFrameHeader*)&DAT_060D6DDA,
    (SaturnSpriteFrameHeader*)&DAT_060D6DE6,
    (SaturnSpriteFrameHeader*)&DAT_060D6DF2,
    (SaturnSpriteFrameHeader*)&DAT_060D6DFE,
    (SaturnSpriteFrameHeader*)&DAT_060D6E0A,
    (SaturnSpriteFrameHeader*)&DAT_060D6E16,
    (SaturnSpriteFrameHeader*)&DAT_060D6E22,
    (SaturnSpriteFrameHeader*)&DAT_060D6E2E,
    (SaturnSpriteFrameHeader*)&DAT_060D6E3A,
    (SaturnSpriteFrameHeader*)&DAT_060D6E46,
    (SaturnSpriteFrameHeader*)&DAT_060D6E52,
    (SaturnSpriteFrameHeader*)&DAT_060D6E5E,
    (SaturnSpriteFrameHeader*)&DAT_060D6E6A,
    (SaturnSpriteFrameHeader*)&DAT_060D6E76,
    (SaturnSpriteFrameHeader*)&DAT_060D6E82,
};

SaturnSpriteResource DAT_060D6F9C = {
    DAT_060D6ABC, (u16*)&DAT_060D6AF0, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6FA8[1] = {&DAT_060D6F9C};
