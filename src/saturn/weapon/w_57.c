// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62C8();
void func_060D62E0();
void func_060D62F8();
void func_060D6310();
void func_060D6328();
void func_060D6340();
void func_060D634C();
void func_060D6364();
void func_060D637C();
void func_060D6394();
void func_060D63AC();
void func_060D63C4();
void func_060D63DC();
void func_060D63F4();
void func_060D640C();
extern SaturnSpriteResource* DAT_060D6C50[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62C8,
        func_060D62E0,
        func_060D62F8,
        func_060D6310,
        func_060D6328,
        func_060D6340,
        func_060D640C,
        func_060D634C,
        func_060D6364,
        func_060D637C,
        func_060D6394,
        func_060D63AC,
        func_060D63C4,
        func_060D63DC,
        func_060D63F4,
    },
    DAT_060D6C50,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D62C8, func_060D62C8);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D62E0, func_060D62E0);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D62F8, func_060D62F8);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D6310, func_060D6310);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D6328, func_060D6328);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D6340, func_060D6340);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D634C, func_060D634C);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D6364, func_060D6364);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D637C, func_060D637C);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D6394, func_060D6394);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D63AC, func_060D63AC);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D63C4, func_060D63C4);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D63DC, func_060D63DC);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D63F4, func_060D63F4);
INCLUDE_ASM("asm/saturn/weapon/w_57/f_nonmat", f60D640C, func_060D640C);

u16 DAT_060D6420[14] = {0x0201, 0x0402, 0x0403, 0x0404, 0x0405, 0x0606, 0x0607,
                        0x0608, 0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D643C[14] = {0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0x0E13, 0x0E14,
                        0x0E15, 0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6458[14] = {0x0A0E, 0x1017, 0x1218, 0x1019, 0x121A, 0x141B, 0x141C,
                        0x141D, 0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6474[11] = {0x1623, 0x1824, 0x1825, 0x1826, 0x1827, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D648A[11] = {0x1C2D, 0x1E2E, 0x1E2F, 0x1E30, 0x1E31, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D64A0[11] = {0x1C2D, 0x2236, 0x2237, 0x2238, 0x2239, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF};

u16 DAT_060D64B6[13] = {0x0201, 0x263F, 0x2640, 0x2641, 0x0606, 0x0607, 0x0608,
                        0x0609, 0x080A, 0x080B, 0x080C, 0x080D, 0xFFFF};

u16 DAT_060D64D0[13] = {0x0A0E, 0x2842, 0x2843, 0x2844, 0x0E13, 0x0E14, 0x0E15,
                        0x0E16, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D64EA[13] = {0x0A0E, 0x2A45, 0x2A46, 0x2A47, 0x141B, 0x141C, 0x141D,
                        0x141E, 0x081F, 0x0820, 0x0821, 0x0822, 0xFFFF};

u16 DAT_060D6504[10] = {0x1623, 0x2C48, 0x2C49, 0x2C4A, 0x1A28,
                        0x1A29, 0x1A2A, 0x1A2B, 0x082C, 0xFFFF};

u16 DAT_060D6518[10] = {0x1C2D, 0x2E4B, 0x2E4C, 0x2E4D, 0x2032,
                        0x2033, 0x2034, 0x2035, 0x083E, 0xFFFF};

u16 DAT_060D652C[10] = {0x1C2D, 0x304E, 0x304F, 0x3050, 0x243A,
                        0x243B, 0x243C, 0x243D, 0x083E, 0xFFFF};

s8 DAT_060D6540[25][4] = {
    {0, 0, 0, 0},     {5, -23, 10, 5},  {38, -17, 44, 8},  {38, -14, 23, 4},
    {-40, -31, 0, 0}, {-5, -6, 10, 5},  {28, 0, 44, 8},    {28, 3, 23, 4},
    {36, 22, 16, 11}, {15, 7, 24, 12},  {18, 14, 23, 4},   {1, -25, 10, 5},
    {34, -19, 44, 8}, {34, -16, 23, 4}, {-10, -26, 10, 5}, {30, -17, 44, 8},
    {30, -14, 23, 4}, {29, 0, 34, 14},  {23, 2, 26, 11},   {36, -14, 43, 4},
    {26, 3, 43, 4},   {35, 21, 15, 10}, {33, -16, 43, 4},  {29, -14, 43, 4},
    {28, 3, 33, 10}};

u16* DAT_060D65A4[7] = {DAT_060D6420, DAT_060D6420, DAT_060D643C, DAT_060D6458,
                        DAT_060D6474, DAT_060D648A, DAT_060D64A0};

u16* DAT_060D65C0[7] = {DAT_060D64B6, DAT_060D64B6, DAT_060D64D0, DAT_060D64EA,
                        DAT_060D6504, DAT_060D6518, DAT_060D652C};

WeaponAnimation DAT_060D65DC[4] = {
    {(u16**)DAT_060D65C0, (s8*)DAT_060D6540, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D65A4, (s8*)DAT_060D6540, 0x0000, 0x060B, 0x39, 0x04, 0},
    {(u16**)DAT_060D65A4, (s8*)DAT_060D6540, 0x0000, 0x060C, 0x39, 0x04, 0},
    {(u16**)DAT_060D65A4, (s8*)DAT_060D6540, 0x0000, 0x06A8, 0x39, 0x04, 0},
};

SaturnSpriteImage DAT_060D661C[7] = {
    {12, 5, 0x0000},  {44, 10, 0x0010}, {24, 4, 0x0080}, {8, 1, 0x0098},
    {32, 19, 0x009C}, {24, 12, 0x0134}, {0, 0, 0x017C},
};

SaturnSpriteFrameHeader DAT_060D6638 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D663C = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6648 = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6654 = {
    {0x0100, 0x0000},
    {
        {0x0100, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6660 = {
    {0x0100, 0x0000},
    {
        {0x0200, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D666C = {
    {0x0100, 0x0000},
    {
        {0x0300, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6678 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6684 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6690 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D669C = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66CC = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D66F0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D66FC = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6708 = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6714 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6720 = {
    {0x0100, 0x0000},
    {
        {0x0100, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D672C = {
    {0x0100, 0x0000},
    {
        {0x0200, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6738 = {
    {0x0100, 0x0000},
    {
        {0x0300, 28, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6744 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6750 = {
    {0x0100, 0x0000},
    {
        {0x0100, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D675C = {
    {0x0100, 0x0000},
    {
        {0x0200, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6768 = {
    {0x0100, 0x0000},
    {
        {0x0300, 19, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6774 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6780 = {
    {0x0100, 0x0000},
    {
        {0x0100, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D678C = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6798 = {
    {0x0100, 0x0000},
    {
        {0x0300, 17, 13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D67A4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67B0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -24, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67BC = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67C8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -25, 10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67D4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D67E0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D67EC = {
    {0x0100, 0x0000},
    {
        {0x0100, 34, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D67F8 = {
    {0x0100, 0x0000},
    {
        {0x0200, 34, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6804 = {
    {0x0100, 0x0000},
    {
        {0x0300, 34, -21, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6810 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D681C = {
    {0x0100, 0x0000},
    {
        {0x0100, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6828 = {
    {0x0100, 0x0000},
    {
        {0x0200, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6834 = {
    {0x0100, 0x0000},
    {
        {0x0300, 36, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6840 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D684C = {
    {0x0100, 0x0000},
    {
        {0x0400, -5, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6858 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6864 = {
    {0x0100, 0x0000},
    {
        {0x0100, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6870 = {
    {0x0100, 0x0000},
    {
        {0x0200, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D687C = {
    {0x0100, 0x0000},
    {
        {0x0300, 32, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6888 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6894 = {
    {0x0100, 0x0000},
    {
        {0x0100, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D68A0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D68AC = {
    {0x0100, 0x0000},
    {
        {0x0300, 35, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D68B8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D68C4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D68D0 = {
    {0x0100, 0x0000},
    {
        {0x0200, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D68DC = {
    {0x0100, 0x0000},
    {
        {0x0300, 27, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D68E8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D68F4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6900 = {
    {0x0100, 0x0000},
    {
        {0x0200, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D690C = {
    {0x0100, 0x0000},
    {
        {0x0300, 25, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6918 = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6924 = {
    {0x0100, 0x0000},
    {
        {0x0500, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6930 = {
    {0x0100, 0x0000},
    {
        {0x0600, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D693C = {
    {0x0100, 0x0000},
    {
        {0x0700, 40, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6948 = {
    {0x0100, 0x0000},
    {
        {0x0500, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6954 = {
    {0x0100, 0x0000},
    {
        {0x0600, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6960 = {
    {0x0100, 0x0000},
    {
        {0x0700, 30, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D696C = {
    {0x0100, 0x0000},
    {
        {0x0500, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6978 = {
    {0x0100, 0x0000},
    {
        {0x0600, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6984 = {
    {0x0100, 0x0000},
    {
        {0x0700, 21, 14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6990 = {
    {0x0100, 0x0000},
    {
        {0x0500, 36, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D699C = {
    {0x0100, 0x0000},
    {
        {0x0600, 36, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69A8 = {
    {0x0100, 0x0000},
    {
        {0x0700, 36, -20, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69B4 = {
    {0x0100, 0x0000},
    {
        {0x0500, 34, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69C0 = {
    {0x0100, 0x0000},
    {
        {0x0600, 34, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69CC = {
    {0x0100, 0x0000},
    {
        {0x0700, 34, -18, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69D8 = {
    {0x0100, 0x0000},
    {
        {0x0500, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D69E4 = {
    {0x0100, 0x0000},
    {
        {0x0600, 31, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D69F0 = {
    {0x0100, 0x0000},
    {
        {0x0700, 31, 3, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D69FC[81] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6638,
    (SaturnSpriteFrameHeader*)&DAT_060D663C,
    (SaturnSpriteFrameHeader*)&DAT_060D6648,
    (SaturnSpriteFrameHeader*)&DAT_060D6654,
    (SaturnSpriteFrameHeader*)&DAT_060D6660,
    (SaturnSpriteFrameHeader*)&DAT_060D666C,
    (SaturnSpriteFrameHeader*)&DAT_060D6678,
    (SaturnSpriteFrameHeader*)&DAT_060D6684,
    (SaturnSpriteFrameHeader*)&DAT_060D6690,
    (SaturnSpriteFrameHeader*)&DAT_060D669C,
    (SaturnSpriteFrameHeader*)&DAT_060D66A8,
    (SaturnSpriteFrameHeader*)&DAT_060D66B4,
    (SaturnSpriteFrameHeader*)&DAT_060D66C0,
    (SaturnSpriteFrameHeader*)&DAT_060D66CC,
    (SaturnSpriteFrameHeader*)&DAT_060D66D8,
    (SaturnSpriteFrameHeader*)&DAT_060D66E4,
    (SaturnSpriteFrameHeader*)&DAT_060D66F0,
    (SaturnSpriteFrameHeader*)&DAT_060D66FC,
    (SaturnSpriteFrameHeader*)&DAT_060D6708,
    (SaturnSpriteFrameHeader*)&DAT_060D6714,
    (SaturnSpriteFrameHeader*)&DAT_060D6720,
    (SaturnSpriteFrameHeader*)&DAT_060D672C,
    (SaturnSpriteFrameHeader*)&DAT_060D6738,
    (SaturnSpriteFrameHeader*)&DAT_060D6744,
    (SaturnSpriteFrameHeader*)&DAT_060D6750,
    (SaturnSpriteFrameHeader*)&DAT_060D675C,
    (SaturnSpriteFrameHeader*)&DAT_060D6768,
    (SaturnSpriteFrameHeader*)&DAT_060D6774,
    (SaturnSpriteFrameHeader*)&DAT_060D6780,
    (SaturnSpriteFrameHeader*)&DAT_060D678C,
    (SaturnSpriteFrameHeader*)&DAT_060D6798,
    (SaturnSpriteFrameHeader*)&DAT_060D67A4,
    (SaturnSpriteFrameHeader*)&DAT_060D67B0,
    (SaturnSpriteFrameHeader*)&DAT_060D67BC,
    (SaturnSpriteFrameHeader*)&DAT_060D67C8,
    (SaturnSpriteFrameHeader*)&DAT_060D67D4,
    (SaturnSpriteFrameHeader*)&DAT_060D67E0,
    (SaturnSpriteFrameHeader*)&DAT_060D67EC,
    (SaturnSpriteFrameHeader*)&DAT_060D67F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6804,
    (SaturnSpriteFrameHeader*)&DAT_060D6810,
    (SaturnSpriteFrameHeader*)&DAT_060D681C,
    (SaturnSpriteFrameHeader*)&DAT_060D6828,
    (SaturnSpriteFrameHeader*)&DAT_060D6834,
    (SaturnSpriteFrameHeader*)&DAT_060D6840,
    (SaturnSpriteFrameHeader*)&DAT_060D684C,
    (SaturnSpriteFrameHeader*)&DAT_060D6858,
    (SaturnSpriteFrameHeader*)&DAT_060D6864,
    (SaturnSpriteFrameHeader*)&DAT_060D6870,
    (SaturnSpriteFrameHeader*)&DAT_060D687C,
    (SaturnSpriteFrameHeader*)&DAT_060D6888,
    (SaturnSpriteFrameHeader*)&DAT_060D6894,
    (SaturnSpriteFrameHeader*)&DAT_060D68A0,
    (SaturnSpriteFrameHeader*)&DAT_060D68AC,
    (SaturnSpriteFrameHeader*)&DAT_060D68B8,
    (SaturnSpriteFrameHeader*)&DAT_060D68C4,
    (SaturnSpriteFrameHeader*)&DAT_060D68D0,
    (SaturnSpriteFrameHeader*)&DAT_060D68DC,
    (SaturnSpriteFrameHeader*)&DAT_060D68E8,
    (SaturnSpriteFrameHeader*)&DAT_060D68F4,
    (SaturnSpriteFrameHeader*)&DAT_060D6900,
    (SaturnSpriteFrameHeader*)&DAT_060D690C,
    (SaturnSpriteFrameHeader*)&DAT_060D6918,
    (SaturnSpriteFrameHeader*)&DAT_060D6924,
    (SaturnSpriteFrameHeader*)&DAT_060D6930,
    (SaturnSpriteFrameHeader*)&DAT_060D693C,
    (SaturnSpriteFrameHeader*)&DAT_060D6948,
    (SaturnSpriteFrameHeader*)&DAT_060D6954,
    (SaturnSpriteFrameHeader*)&DAT_060D6960,
    (SaturnSpriteFrameHeader*)&DAT_060D696C,
    (SaturnSpriteFrameHeader*)&DAT_060D6978,
    (SaturnSpriteFrameHeader*)&DAT_060D6984,
    (SaturnSpriteFrameHeader*)&DAT_060D6990,
    (SaturnSpriteFrameHeader*)&DAT_060D699C,
    (SaturnSpriteFrameHeader*)&DAT_060D69A8,
    (SaturnSpriteFrameHeader*)&DAT_060D69B4,
    (SaturnSpriteFrameHeader*)&DAT_060D69C0,
    (SaturnSpriteFrameHeader*)&DAT_060D69CC,
    (SaturnSpriteFrameHeader*)&DAT_060D69D8,
    (SaturnSpriteFrameHeader*)&DAT_060D69E4,
    (SaturnSpriteFrameHeader*)&DAT_060D69F0,
};

struct {
    u16 countAndFlags;
    u16 colors[8][16];
    u16 padding[1];
} DAT_060D6B40 = {
    0x0008,
    {
        {0x0000, 0x8007, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0xAD6B, 0x843F,
         0xB148, 0xA928, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
        {0x0000, 0x8007, 0x0000, 0x0000, 0x0000, 0xE717, 0xE717, 0xE717, 0x843F,
         0xA0E6, 0xA0E6, 0xE717, 0xE717, 0xE717, 0xD294, 0xF39C},
        {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xB56A, 0xA927, 0x801F,
         0x9062, 0x98C6, 0xB148, 0x0000, 0x0000, 0xD294, 0xF39C},
        {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0xA4E6, 0x0000, 0x843F,
         0x0000, 0x9483, 0x0000, 0xA0C4, 0x0000, 0xD294, 0xF39C},
        {0x0000, 0x8007, 0x98C6, 0x9DC0, 0x98C6, 0x98C6, 0x98C6, 0x98C6, 0x843F,
         0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
        {0x0000, 0x8007, 0x0000, 0x9DC0, 0xA94A, 0xA94A, 0xA94A, 0xA94A, 0x843F,
         0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xF39C},
        {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x94A5, 0x0000, 0x843F,
         0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xEB5A},
        {0x0000, 0x8007, 0x0000, 0x9DC0, 0x0000, 0x0000, 0x94A5, 0x0000, 0x843F,
         0xB9C0, 0x801F, 0x0000, 0x0000, 0x0000, 0xD294, 0xEB5A},
    },
    {0x0000},
};

SaturnSpriteResource DAT_060D6C44 = {
    DAT_060D661C, (u16*)&DAT_060D6B40, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6C50[1] = {&DAT_060D6C44};
