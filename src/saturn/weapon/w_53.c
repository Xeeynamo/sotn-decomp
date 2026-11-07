// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6328();
void func_060D65B8();
void func_060D6874();
void func_060D69F0();
void func_060D6A08();
void func_060D6A20();
void func_060D6A2C();
void func_060D6A44();
void func_060D6A5C();
void func_060D6A74();
void func_060D6A8C();
void func_060D6AA4();
void func_060D6ABC();
void func_060D6AD4();
void func_060D6AEC();
extern SaturnSpriteResource* DAT_060D78C8[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6328,
        func_060D65B8,
        func_060D6874,
        func_060D69F0,
        func_060D6A08,
        func_060D6A20,
        func_060D6AEC,
        func_060D6A2C,
        func_060D6A44,
        func_060D6A5C,
        func_060D6A74,
        func_060D6A8C,
        func_060D6AA4,
        func_060D6ABC,
        func_060D6AD4,
    },
    DAT_060D78C8,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6328, func_060D6328);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D65B8, func_060D65B8);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6874, func_060D6874);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D69F0, func_060D69F0);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6A08, func_060D6A08);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6A20, func_060D6A20);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6A2C, func_060D6A2C);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6A44, func_060D6A44);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6A5C, func_060D6A5C);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6A74, func_060D6A74);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6A8C, func_060D6A8C);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6AA4, func_060D6AA4);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6ABC, func_060D6ABC);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6AD4, func_060D6AD4);
INCLUDE_ASM("asm/saturn/weapon/w_53/f_nonmat", f60D6AEC, func_060D6AEC);

u16 DAT_060D6B00[14] = {0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607,
                        0x0608, 0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D6B1C[14] = {0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14,
                        0x0E15, 0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6B38[14] = {0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C,
                        0x141D, 0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6B54[11] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D6B6A[11] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D6B80[11] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF};

u16 DAT_060D6B96[13] = {0x0201, 0x263F, 0x2640, 0x2641, 0x0606, 0x0607, 0x0608,
                        0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D6BB0[13] = {0x0A0E, 0x2842, 0x2843, 0x2844, 0x0E13, 0x0E14, 0x0E15,
                        0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6BCA[13] = {0x0A0E, 0x2A45, 0x2A46, 0x2A47, 0x141B, 0x141C, 0x141D,
                        0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6BE4[10] = {0x1623, 0x2C48, 0x2C49, 0x2C4A, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D6BF8[10] = {0x1C2D, 0x2E4B, 0x2E4C, 0x2E4D, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D6C0C[10] = {0x1C2D, 0x304E, 0x304F, 0x3050, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF};

s8 DAT_060D6C20[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D6C84[7] = {DAT_060D6B00, DAT_060D6B00, DAT_060D6B1C, DAT_060D6B38,
                        DAT_060D6B54, DAT_060D6B6A, DAT_060D6B80};

u16* DAT_060D6CA0[7] = {DAT_060D6B96, DAT_060D6B96, DAT_060D6BB0, DAT_060D6BCA,
                        DAT_060D6BE4, DAT_060D6BF8, DAT_060D6C0C};

WeaponAnimation DAT_060D6CBC[5] = {
    {(u16**)DAT_060D6CA0, (s8*)DAT_060D6C20, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D6CA0, (s8*)DAT_060D6C20, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D6C84, (s8*)DAT_060D6C20, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D6C84, (s8*)DAT_060D6C20, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D6C84, (s8*)DAT_060D6C20, 0x0000, 0x060B, 0x39, 0x04, 0},
};
u16 DAT_060D6CBC_tail[27] = {
    0x011A, 0x011B, 0x011C, 0x011D, 0x011E, 0x011F, 0x0120, 0x0121, 0x0122,
    0x0122, 0x0121, 0x0120, 0x011F, 0x011E, 0x011D, 0x011C, 0x011B, 0x011A,
    0x0608, 0x0609, 0x070A, 0x070B, 0x080C, 0x080D, 0x090E, 0x090F, 0x0910,
};

u16 DAT_060D6D42[419] = {
    0x0001, 0x0000, 0x0000, 0x0025, 0x08E0, 0x4040, 0x5000, 0x0001, 0x0001,
    0x0001, 0x0020, 0x0480, 0x4040, 0x5000, 0x0000, 0x0000, 0x0000, 0x0030,
    0x00E0, 0x4040, 0x5000, 0x0000, 0x0000, 0x0001, 0x0018, 0x02E0, 0x4040,
    0x5000, 0x0000, 0x0000, 0x0000, 0x0025, 0x08E0, 0x4040, 0x5000, 0x0000,
    0x0001, 0x0001, 0x0020, 0x0C80, 0x4040, 0x5000, 0x0001, 0x0000, 0x0000,
    0x0030, 0x00F0, 0x4040, 0x5000, 0x0001, 0x0000, 0x0000, 0x0018, 0x0600,
    0x4040, 0x5000, 0x0000, 0x0001, 0x0000, 0x0028, 0x0000, 0x4040, 0x5000,
    0x0001, 0x0000, 0x0001, 0x0030, 0x0AF0, 0x4040, 0x5000, 0x0001, 0x0000,
    0x0000, 0x0025, 0x08E0, 0x0060, 0x3000, 0x0001, 0x0001, 0x0001, 0x0020,
    0x0480, 0x0060, 0x3000, 0x0000, 0x0000, 0x0000, 0x0030, 0x00E0, 0x0060,
    0x3000, 0x0000, 0x0000, 0x0001, 0x0018, 0x02E0, 0x0060, 0x3000, 0x0000,
    0x0000, 0x0000, 0x0025, 0x08E0, 0x0060, 0x3000, 0x0000, 0x0001, 0x0001,
    0x0020, 0x0C80, 0x0060, 0x3000, 0x0001, 0x0000, 0x0000, 0x0030, 0x00F0,
    0x0060, 0x3000, 0x0001, 0x0000, 0x0000, 0x0018, 0x0600, 0x0060, 0x3000,
    0x0000, 0x0001, 0x0000, 0x0028, 0x0000, 0x0060, 0x3000, 0x0001, 0x0000,
    0x0001, 0x0030, 0x0AF0, 0x0060, 0x3000, 0x0001, 0x0000, 0x0000, 0x0025,
    0x08E0, 0x4000, 0x8000, 0x0001, 0x0001, 0x0001, 0x0020, 0x0480, 0x4000,
    0x8000, 0x0000, 0x0000, 0x0000, 0x0030, 0x00E0, 0x4000, 0x8000, 0x0000,
    0x0000, 0x0001, 0x0018, 0x02E0, 0x4000, 0x8000, 0x0000, 0x0000, 0x0000,
    0x0025, 0x08E0, 0x4000, 0x8000, 0x0000, 0x0001, 0x0001, 0x0020, 0x0C80,
    0x4000, 0x8000, 0x0001, 0x0000, 0x0000, 0x0030, 0x00F0, 0x4000, 0x8000,
    0x0001, 0x0000, 0x0000, 0x0018, 0x0600, 0x4000, 0x8000, 0x0000, 0x0001,
    0x0000, 0x0028, 0x0000, 0x4000, 0x8000, 0x0001, 0x0000, 0x0001, 0x0030,
    0x0AF0, 0x4000, 0x8000, 0x0001, 0x0000, 0x0000, 0x0025, 0x08E0, 0xC000,
    0x8000, 0x0001, 0x0001, 0x0001, 0x0020, 0x0480, 0x40C0, 0x4000, 0x0000,
    0x0000, 0x0000, 0x0030, 0x00E0, 0x8000, 0xC000, 0x0000, 0x0000, 0x0001,
    0x0018, 0x02E0, 0x8080, 0x4000, 0x0000, 0x0000, 0x0000, 0x0025, 0x08E0,
    0xC000, 0x8000, 0x0000, 0x0001, 0x0001, 0x0020, 0x0C80, 0x40C0, 0xC000,
    0x0001, 0x0000, 0x0000, 0x0030, 0x00F0, 0x8020, 0xC000, 0x0001, 0x0000,
    0x0000, 0x0018, 0x0600, 0x4080, 0x4000, 0x0000, 0x0001, 0x0000, 0x0028,
    0x0000, 0x4080, 0x0000, 0x0001, 0x0000, 0x0001, 0x0030, 0x0AF0, 0x2020,
    0xC000, 0x0000, 0x0001, 0x0000, 0x0025, 0x0E00, 0xC000, 0x8000, 0x0000,
    0x0001, 0x0000, 0x0026, 0x0C00, 0xB010, 0x7000, 0x0000, 0x0001, 0x0000,
    0x0027, 0x0A00, 0xA020, 0x6000, 0x0000, 0x0001, 0x0000, 0x0028, 0x0800,
    0x9030, 0x5000, 0x0000, 0x0001, 0x0000, 0x0029, 0x0600, 0x8040, 0x4000,
    0x0000, 0x0001, 0x0000, 0x0028, 0x0400, 0x9030, 0x5000, 0x0000, 0x0001,
    0x0000, 0x0027, 0x0200, 0xA020, 0x6000, 0x0000, 0x0001, 0x0000, 0x0026,
    0x0000, 0x0080, 0x6000, 0x0000, 0x0001, 0x0000, 0x0027, 0x0300, 0xC0A0,
    0x6000, 0x0000, 0x0001, 0x0000, 0x0028, 0x0600, 0x6BC0, 0xE000, 0x0000,
    0x0001, 0x0000, 0x0027, 0x0900, 0x3070, 0xE000, 0x0002, 0x0051, 0x0002,
    0x0052, 0x0001, 0x0053, 0x0002, 0x0058, 0x0001, 0x0059, 0x0002, 0x005A,
    0x0001, 0x005B, 0x0002, 0x0054, 0x0001, 0x0055, 0x0002, 0x0056, 0x0001,
    0x0057, 0xFFFF, 0x0000, 0x0001, 0x005D, 0x0001, 0x005E, 0x0001, 0x005F,
    0x0001, 0x0060, 0x0001, 0x0061, 0x0001, 0x0062, 0x0001, 0x0063, 0x0001,
    0x0064, 0x0001, 0x0065, 0x0001, 0x005D, 0x0001, 0x005E, 0x0001, 0x005F,
    0x0001, 0x0060, 0x0001, 0x0061, 0x0001, 0x0062, 0x0001, 0x0063, 0x0001,
    0x0064, 0x0001, 0x0065, 0xFFFF, 0x0000,
};

SaturnSpriteImage DAT_060D7088[17] = {
    {12, 5, 0x0000},  {40, 4, 0x0010},  {24, 4, 0x0038},  {8, 1, 0x0050},
    {32, 19, 0x0054}, {24, 12, 0x00EC}, {20, 32, 0x0134}, {16, 32, 0x01D4},
    {40, 31, 0x0254}, {36, 31, 0x038C}, {20, 27, 0x04A4}, {20, 26, 0x052C},
    {20, 21, 0x05B0}, {20, 15, 0x061C}, {8, 18, 0x0668},  {4, 16, 0x068C},
    {0, 0, 0x069C},
};

struct {
    u16 countAndFlags;
    u16 colors[12][16];
    u16 padding[1];
} DAT_060D70CC = {
    0x000C,
    {
        {0x98C6, 0x8000, 0xFF5A, 0xFFF9, 0xFF5A, 0xFF5A, 0xFF5A, 0xFF5A, 0x843F,
         0xFFFD, 0xDA70, 0xE2D6, 0xDEF6, 0xCDCE, 0xD294, 0xF2F3},
        {0x98C6, 0x8000, 0xD2D4, 0x8000, 0xDAD4, 0xFFFF, 0xFFFF, 0xFFFF, 0x843F,
         0xFF39, 0xFF39, 0xFFFF, 0xFFFF, 0xEF5B, 0xD294, 0xEF5A},
        {0x98C6, 0x8000, 0xCA50, 0xFFF9, 0xD230, 0xCDEF, 0xFF5A, 0xFF5A, 0x801F,
         0xFB39, 0xFF39, 0xFF5A, 0xCE14, 0xBDEF, 0xD294, 0xEAD3},
        {0x98C6, 0x8000, 0xD275, 0xFFF9, 0xDA52, 0xD20D, 0xFFD9, 0xDED2, 0x843F,
         0xEEB5, 0xFF39, 0xD273, 0xFFFF, 0xE694, 0xD294, 0xE24C},
        {0x98C6, 0x8000, 0x8000, 0x8000, 0x8000, 0xA818, 0xB0B8, 0xAC38, 0x83E0,
         0x800E, 0x8450, 0x9418, 0x9418, 0x9818, 0xD294, 0xFFFF},
        {0x98C6, 0x8000, 0xFB39, 0xFFF9, 0xFB39, 0xFB39, 0xFB39, 0xFB39, 0x843F,
         0xFFF9, 0x801F, 0xE6F5, 0xE6D5, 0xDA50, 0xD294, 0xF2D1},
        {0x98C6, 0x8000, 0xCA51, 0xFFF9, 0xFF39, 0xFF39, 0xFF39, 0xFF39, 0x843F,
         0xFFF9, 0x801F, 0xEF15, 0xFBBD, 0xDAD0, 0xD294, 0xF39C},
        {0x98C6, 0x8000, 0xE2D7, 0xFFF9, 0xEF14, 0xDE94, 0xFFB9, 0xE2D4, 0x843F,
         0xFFF9, 0x801F, 0xEF18, 0xF779, 0xDAB2, 0xD294, 0xEA90},
        {0x8160, 0x8005, 0x8007, 0x8009, 0x800B, 0x800C, 0x800E, 0x8010, 0x8012,
         0x8033, 0x8435, 0x8437, 0x8438, 0x843A, 0x843C, 0x843E},
        {0x8160, 0x9820, 0xA040, 0xA840, 0xB040, 0xB840, 0xBC60, 0xC460, 0xCC60,
         0xD460, 0xDC80, 0xE080, 0xE880, 0xF080, 0xF8A0, 0xFCA0},
        {0x8160, 0xC0EF, 0xC10E, 0xC54E, 0xC98E, 0xCDCE, 0xD20E, 0xD64E, 0xDA70,
         0xDEB2, 0xE2D4, 0xE716, 0xEB38, 0xEF7A, 0xF39C, 0xFBDE},
        {0x8160, 0x80C0, 0x8100, 0x8520, 0x8560, 0x8980, 0x89A0, 0x8DE0, 0x8E00,
         0x9240, 0x9260, 0x9680, 0x96C0, 0x9AE0, 0x9B20, 0x9F40},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D7250 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7254 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7260 = {
    {0x0100, 0x0000},
    {
        {0x0000, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D726C = {
    {0x0100, 0x0000},
    {
        {0x0100, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7278 = {
    {0x0100, 0x0000},
    {
        {0x0200, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7284 = {
    {0x0100, 0x0000},
    {
        {0x0300, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7290 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D729C = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D72A8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D72B4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D72C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72CC = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72FC = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7308 = {
    {0x0100, 0x0000},
    {
        {0x0100, 33, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7314 = {
    {0x0100, 0x0000},
    {
        {0x0200, 33, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7320 = {
    {0x0100, 0x0000},
    {
        {0x0300, 33, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D732C = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7338 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7344 = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7350 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D735C = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7368 = {
    {0x0100, 0x0000},
    {
        {0x0100, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7374 = {
    {0x0100, 0x0000},
    {
        {0x0200, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7380 = {
    {0x0100, 0x0000},
    {
        {0x0300, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D738C = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7398 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D73A4 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D73B0 = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D73BC = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73C8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73D4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73E0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73EC = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7404 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7410 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D741C = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7428 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7434 = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7440 = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D744C = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7458 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7464 = {
    {0x0100, 0x0000},
    {
        {0x0400, -5, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7470 = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D747C = {
    {0x0100, 0x0000},
    {
        {0x0100, 33, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7488 = {
    {0x0100, 0x0000},
    {
        {0x0200, 33, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7494 = {
    {0x0100, 0x0000},
    {
        {0x0300, 33, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D74A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74AC = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74B8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74C4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74D0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D74DC = {
    {0x0100, 0x0000},
    {
        {0x0100, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D74E8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D74F4 = {
    {0x0100, 0x0000},
    {
        {0x0300, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7500 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D750C = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7518 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7524 = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7530 = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D753C = {
    {0x0100, 0x0000},
    {
        {0x0500, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7548 = {
    {0x0100, 0x0000},
    {
        {0x0600, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7554 = {
    {0x0100, 0x0000},
    {
        {0x0700, 41, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7560 = {
    {0x0100, 0x0000},
    {
        {0x0500, 31, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D756C = {
    {0x0100, 0x0000},
    {
        {0x0600, 31, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7578 = {
    {0x0100, 0x0000},
    {
        {0x0700, 31, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7584 = {
    {0x0100, 0x0000},
    {
        {0x0500, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7590 = {
    {0x0100, 0x0000},
    {
        {0x0600, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D759C = {
    {0x0100, 0x0000},
    {
        {0x0700, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D75A8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 37, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75B4 = {
    {0x0100, 0x0000},
    {
        {0x0600, 37, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75C0 = {
    {0x0100, 0x0000},
    {
        {0x0700, 37, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75CC = {
    {0x0100, 0x0000},
    {
        {0x0500, 35, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75D8 = {
    {0x0100, 0x0000},
    {
        {0x0600, 35, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75E4 = {
    {0x0100, 0x0000},
    {
        {0x0700, 35, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75F0 = {
    {0x0100, 0x0000},
    {
        {0x0500, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D75FC = {
    {0x0100, 0x0000},
    {
        {0x0600, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7608 = {
    {0x0100, 0x0000},
    {
        {0x0700, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7614 = {
    {0x0100, 0x0000},
    {
        {0x0800, 32, -7, 6},
    },
};

SaturnSpriteFrame2 DAT_060D7620 = {
    {0x0200, 0x0000},
    {
        {0x0800, 34, -7, 7},
        {0x0920, 40, -11, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7634 = {
    {0x0100, 0x0000},
    {
        {0x0920, 42, -6, 7},
    },
};

SaturnSpriteFrame1 DAT_060D7640 = {
    {0x0100, 0x0000},
    {
        {0x0A20, 59, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D764C = {
    {0x0100, 0x0000},
    {
        {0x0A20, 61, -7, 9},
    },
};

SaturnSpriteFrame1 DAT_060D7658 = {
    {0x0100, 0x0000},
    {
        {0x0B00, 59, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D7664 = {
    {0x0100, 0x0000},
    {
        {0x0B00, 61, -7, 9},
    },
};

SaturnSpriteFrame1 DAT_060D7670 = {
    {0x0100, 0x0000},
    {
        {0x0820, 51, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D767C = {
    {0x0100, 0x0000},
    {
        {0x0820, 53, -7, 9},
    },
};

SaturnSpriteFrame1 DAT_060D7688 = {
    {0x0100, 0x0000},
    {
        {0x0900, 51, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D7694 = {
    {0x0100, 0x0000},
    {
        {0x0900, 53, -7, 9},
    },
};

SaturnSpriteFrame1 DAT_060D76A0 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 33, -7, 10},
    },
};

SaturnSpriteFrame1 DAT_060D76AC = {
    {0x0100, 0x0000},
    {
        {0x0A00, 37, -6, 11},
    },
};

SaturnSpriteFrame1 DAT_060D76B8 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 50, -1, 12},
    },
};

SaturnSpriteFrame2 DAT_060D76C4 = {
    {0x0200, 0x0000},
    {
        {0x0A00, 52, -7, 13},
        {0x0A20, 41, 1, 10},
    },
};

SaturnSpriteFrame1 DAT_060D76D8 = {
    {0x0100, 0x0000},
    {
        {0x0A20, 46, 0, 11},
    },
};

SaturnSpriteFrame1 DAT_060D76E4 = {
    {0x0100, 0x0000},
    {
        {0x0A20, 57, -3, 12},
    },
};

SaturnSpriteFrame2 DAT_060D76F0 = {
    {0x0200, 0x0000},
    {
        {0x0A20, 59, -9, 13},
        {0x0A00, 50, -23, 14},
    },
};

SaturnSpriteFrame1 DAT_060D7704 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 63, -15, 15},
    },
};

SaturnSpriteFrame2 DAT_060D7710 = {
    {0x0200, 0x0000},
    {
        {0x0A00, 67, -11, 15},
        {0x0A00, 62, 8, 13},
    },
};

SaturnSpriteFrameHeader* DAT_060D7724[102] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7250,
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
    (SaturnSpriteFrameHeader*)&DAT_060D72E4,
    (SaturnSpriteFrameHeader*)&DAT_060D72F0,
    (SaturnSpriteFrameHeader*)&DAT_060D72FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7308,
    (SaturnSpriteFrameHeader*)&DAT_060D7314,
    (SaturnSpriteFrameHeader*)&DAT_060D7320,
    (SaturnSpriteFrameHeader*)&DAT_060D732C,
    (SaturnSpriteFrameHeader*)&DAT_060D7338,
    (SaturnSpriteFrameHeader*)&DAT_060D7344,
    (SaturnSpriteFrameHeader*)&DAT_060D7350,
    (SaturnSpriteFrameHeader*)&DAT_060D735C,
    (SaturnSpriteFrameHeader*)&DAT_060D7368,
    (SaturnSpriteFrameHeader*)&DAT_060D7374,
    (SaturnSpriteFrameHeader*)&DAT_060D7380,
    (SaturnSpriteFrameHeader*)&DAT_060D738C,
    (SaturnSpriteFrameHeader*)&DAT_060D7398,
    (SaturnSpriteFrameHeader*)&DAT_060D73A4,
    (SaturnSpriteFrameHeader*)&DAT_060D73B0,
    (SaturnSpriteFrameHeader*)&DAT_060D73BC,
    (SaturnSpriteFrameHeader*)&DAT_060D73C8,
    (SaturnSpriteFrameHeader*)&DAT_060D73D4,
    (SaturnSpriteFrameHeader*)&DAT_060D73E0,
    (SaturnSpriteFrameHeader*)&DAT_060D73EC,
    (SaturnSpriteFrameHeader*)&DAT_060D73F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7404,
    (SaturnSpriteFrameHeader*)&DAT_060D7410,
    (SaturnSpriteFrameHeader*)&DAT_060D741C,
    (SaturnSpriteFrameHeader*)&DAT_060D7428,
    (SaturnSpriteFrameHeader*)&DAT_060D7434,
    (SaturnSpriteFrameHeader*)&DAT_060D7440,
    (SaturnSpriteFrameHeader*)&DAT_060D744C,
    (SaturnSpriteFrameHeader*)&DAT_060D7458,
    (SaturnSpriteFrameHeader*)&DAT_060D7464,
    (SaturnSpriteFrameHeader*)&DAT_060D7470,
    (SaturnSpriteFrameHeader*)&DAT_060D747C,
    (SaturnSpriteFrameHeader*)&DAT_060D7488,
    (SaturnSpriteFrameHeader*)&DAT_060D7494,
    (SaturnSpriteFrameHeader*)&DAT_060D74A0,
    (SaturnSpriteFrameHeader*)&DAT_060D74AC,
    (SaturnSpriteFrameHeader*)&DAT_060D74B8,
    (SaturnSpriteFrameHeader*)&DAT_060D74C4,
    (SaturnSpriteFrameHeader*)&DAT_060D74D0,
    (SaturnSpriteFrameHeader*)&DAT_060D74DC,
    (SaturnSpriteFrameHeader*)&DAT_060D74E8,
    (SaturnSpriteFrameHeader*)&DAT_060D74F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7500,
    (SaturnSpriteFrameHeader*)&DAT_060D750C,
    (SaturnSpriteFrameHeader*)&DAT_060D7518,
    (SaturnSpriteFrameHeader*)&DAT_060D7524,
    (SaturnSpriteFrameHeader*)&DAT_060D7530,
    (SaturnSpriteFrameHeader*)&DAT_060D753C,
    (SaturnSpriteFrameHeader*)&DAT_060D7548,
    (SaturnSpriteFrameHeader*)&DAT_060D7554,
    (SaturnSpriteFrameHeader*)&DAT_060D7560,
    (SaturnSpriteFrameHeader*)&DAT_060D756C,
    (SaturnSpriteFrameHeader*)&DAT_060D7578,
    (SaturnSpriteFrameHeader*)&DAT_060D7584,
    (SaturnSpriteFrameHeader*)&DAT_060D7590,
    (SaturnSpriteFrameHeader*)&DAT_060D759C,
    (SaturnSpriteFrameHeader*)&DAT_060D75A8,
    (SaturnSpriteFrameHeader*)&DAT_060D75B4,
    (SaturnSpriteFrameHeader*)&DAT_060D75C0,
    (SaturnSpriteFrameHeader*)&DAT_060D75CC,
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
    (SaturnSpriteFrameHeader*)&DAT_060D7250,
    (SaturnSpriteFrameHeader*)&DAT_060D76A0,
    (SaturnSpriteFrameHeader*)&DAT_060D76AC,
    (SaturnSpriteFrameHeader*)&DAT_060D76B8,
    (SaturnSpriteFrameHeader*)&DAT_060D76C4,
    (SaturnSpriteFrameHeader*)&DAT_060D76D8,
    (SaturnSpriteFrameHeader*)&DAT_060D76E4,
    (SaturnSpriteFrameHeader*)&DAT_060D76F0,
    (SaturnSpriteFrameHeader*)&DAT_060D7704,
    (SaturnSpriteFrameHeader*)&DAT_060D7710,
};

SaturnSpriteResource DAT_060D78BC = {
    DAT_060D7088, (u16*)&DAT_060D70CC, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D78C8[1] = {&DAT_060D78BC};
