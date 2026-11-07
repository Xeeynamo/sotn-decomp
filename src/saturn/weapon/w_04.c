// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62D8();
void func_060D62F0();
void func_060D6308();
void func_060D6320();
void func_060D6338();
void func_060D6350();
void func_060D635C();
void func_060D6374();
void func_060D638C();
void func_060D63A4();
void func_060D63BC();
void func_060D63D4();
void func_060D63EC();
void func_060D6404();
void func_060D641C();
extern SaturnSpriteResource* DAT_060D6DCC[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62D8,
        func_060D62F0,
        func_060D6308,
        func_060D6320,
        func_060D6338,
        func_060D6350,
        func_060D641C,
        func_060D635C,
        func_060D6374,
        func_060D638C,
        func_060D63A4,
        func_060D63BC,
        func_060D63D4,
        func_060D63EC,
        func_060D6404,
    },
    DAT_060D6DCC,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D62D8, func_060D62D8);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D62F0, func_060D62F0);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D6308, func_060D6308);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D6320, func_060D6320);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D6338, func_060D6338);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D6350, func_060D6350);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D635C, func_060D635C);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D6374, func_060D6374);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D638C, func_060D638C);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D63A4, func_060D63A4);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D63BC, func_060D63BC);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D63D4, func_060D63D4);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D63EC, func_060D63EC);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D6404, func_060D6404);
INCLUDE_ASM("asm/saturn/weapon/w_04/f_nonmat", f60D641C, func_060D641C);

u16 DAT_060D6430[18] = {
    0x0201, 0x0202, 0x0403, 0x0604, 0x0606, 0x0607, 0x0608, 0x0609, 0x060A,
    0x060B, 0x0A0C, 0x0A0D, 0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0xFFFF};

u16 DAT_060D6454[18] = {
    0x0C13, 0x0E14, 0x1015, 0x1216, 0x1218, 0x1219, 0x121A, 0x121B, 0x121C,
    0x161D, 0x161E, 0x181F, 0x1620, 0x222D, 0x222E, 0x222F, 0x2230, 0xFFFF};

u16 DAT_060D6478[18] = {
    0x0C13, 0x0E14, 0x1A21, 0x1C22, 0x1C24, 0x1C25, 0x1C26, 0x1C27, 0x1C28,
    0x2029, 0x202A, 0x202B, 0x202C, 0x222D, 0x222E, 0x222F, 0x2230, 0xFFFF};

u16 DAT_060D649C[16] = {
    0x0231, 0x0232, 0x0433, 0x0634, 0x0636, 0x0637, 0x0638, 0x0639,
    0x063A, 0x063B, 0x0A3C, 0x0A3D, 0x0A3E, 0x0C3F, 0xFFFF, 0x0000};

u16 DAT_060D64BC[16] = {
    0x2440, 0x2441, 0x0442, 0x0643, 0x0645, 0x0646, 0x0647, 0x0648,
    0x0649, 0x0A4A, 0x0A4B, 0x0A4C, 0x0A4D, 0x0C5A, 0xFFFF, 0x0000};

u16 DAT_060D64DC[16] = {
    0x2440, 0x2441, 0x264E, 0x264F, 0x2651, 0x2652, 0x2653, 0x2654,
    0x2655, 0x2A56, 0x2A57, 0x2A58, 0x2A59, 0x0C5A, 0xFFFF, 0x0000};

u16 DAT_060D64FC[18] = {
    0x0201, 0x0202, 0x0403, 0x0604, 0x0805, 0x0607, 0x0608, 0x0609, 0x060A,
    0x060B, 0x0A0C, 0x0A0D, 0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0xFFFF};

u16 DAT_060D6520[18] = {
    0x0C13, 0x0E14, 0x1015, 0x1216, 0x1417, 0x1219, 0x121A, 0x121B, 0x121C,
    0x161D, 0x161E, 0x181F, 0x1620, 0x222D, 0x222E, 0x222F, 0x2230, 0xFFFF};

u16 DAT_060D6544[18] = {
    0x0C13, 0x0E14, 0x1A21, 0x1C22, 0x1E23, 0x1C25, 0x1C26, 0x1C27, 0x1C28,
    0x2029, 0x202A, 0x202B, 0x202C, 0x222D, 0x222E, 0x222F, 0x2230, 0xFFFF};

u16 DAT_060D6568[15] = {
    0x0231, 0x0232, 0x0433, 0x0634, 0x0835, 0x0637, 0x0638, 0x0639,
    0x063A, 0x063B, 0x0A3C, 0x0A3D, 0x0A3E, 0x0C3F, 0xFFFF};

u16 DAT_060D6586[15] = {
    0x2440, 0x2441, 0x0442, 0x0643, 0x0844, 0x0646, 0x0647, 0x0648,
    0x0649, 0x0A4A, 0x0A4B, 0x0A4C, 0x0A4D, 0x0C5A, 0xFFFF};

u16 DAT_060D65A4[16] = {
    0x2440, 0x2441, 0x264E, 0x264F, 0x2850, 0x2652, 0x2653, 0x2654,
    0x2655, 0x2A56, 0x2A57, 0x2A58, 0x2A59, 0x0C5A, 0xFFFF, 0x0000};

s8 DAT_060D65C4[22][4] = {
    {0, 0, 0, 0},      {-4, -26, 15, 4}, {33, -27, 20, 6},  {46, -14, 15, 4},
    {56, -15, 23, 18}, {21, -9, 15, 8},  {-19, -4, 5, 4},   {-13, -8, 15, 4},
    {24, -11, 20, 8},  {40, -1, 10, 8},  {49, 4, 24, 17},   {28, 8, 15, 8},
    {28, 3, 23, 4},    {21, 2, 15, 12},  {36, 19, 10, 8},   {45, 24, 20, 22},
    {14, 18, 15, 8},   {-29, 14, 5, 4},  {-18, -28, 15, 4}, {30, 4, 25, 12},
    {51, 12, 26, 19},  {8, -3, 20, 8}};

u16* DAT_060D661C[7] = {DAT_060D6430, DAT_060D6430, DAT_060D6454, DAT_060D6478,
                        DAT_060D649C, DAT_060D64BC, DAT_060D64DC};

u16* DAT_060D6638[7] = {DAT_060D64FC, DAT_060D64FC, DAT_060D6520, DAT_060D6544,
                        DAT_060D6568, DAT_060D6586, DAT_060D65A4};

WeaponAnimation DAT_060D6654[2] = {
    {(u16**)DAT_060D661C, (s8*)DAT_060D65C4, 0x0001, 0x0689, 0x47, 0x03, 0},
    {(u16**)DAT_060D6638, (s8*)DAT_060D65C4, 0x0001, 0x0689, 0x4E, 0x00, 0},
};

SaturnSpriteImage DAT_060D6674[12] = {
    {16, 10, 0x0000}, {24, 13, 0x0028}, {56, 43, 0x0078}, {8, 12, 0x02D4},
    {12, 2, 0x02EC},  {8, 13, 0x02F4},  {20, 14, 0x0310}, {20, 15, 0x0358},
    {12, 4, 0x03A4},  {24, 17, 0x03B0}, {4, 7, 0x0418},   {0, 0, 0x0420},
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding[1];
} DAT_060D66A4 = {
    0x0002,
    {
        {0x9143, 0xF440, 0xFD60, 0xFEA0, 0xFF83, 0xB969, 0xD9B0, 0x9C10, 0x9D7A,
         0x9F5F, 0x8842, 0x98C6, 0xA94A, 0xC1EF, 0xD694, 0xEF99},
        {0x9484, 0xF342, 0xD280, 0x94A9, 0xA14D, 0xA217, 0xB6DC, 0x9CA4, 0xB0E5,
         0xC988, 0xAE75, 0x9DEE, 0xA507, 0xB58A, 0xCA0E, 0xDAD4},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D66E8 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D66EC = {
    {0x0100, 0x0000},
    {
        {0x0010, -16, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -30, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6704 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, -26, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6710 = {
    {0x0100, 0x0000},
    {
        {0x0000, 49, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D671C = {
    {0x0100, 0x0000},
    {
        {0x0100, 63, -18, 2},
    },
};

SaturnSpriteFrame3 DAT_060D6728 = {
    {0x0300, 0x0000},
    {
        {0x0000, 58, -14, 3},
        {0x0010, 69, -14, 3},
        {0x0000, 54, -14, 4},
    },
};

SaturnSpriteFrame3 DAT_060D6744 = {
    {0x0300, 0x0000},
    {
        {0x0000, 56, -14, 5},
        {0x0010, 71, -14, 5},
        {0x0000, 54, -14, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6760 = {
    {0x0200, 0x0000},
    {
        {0x0000, 67, -14, 6},
        {0x0000, 54, -14, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6774 = {
    {0x0200, 0x0000},
    {
        {0x0000, 66, -14, 7},
        {0x0000, 54, -14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6788 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -14, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6794 = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -9, 4},
    },
};

SaturnSpriteFrame1 DAT_060D67A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -6, 8},
    },
};

SaturnSpriteFrame1 DAT_060D67AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -6, 8},
    },
};

SaturnSpriteFrame1 DAT_060D67B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -6, 8},
    },
};

SaturnSpriteFrame1 DAT_060D67C4 = {
    {0x0100, 0x0000},
    {
        {0x0010, -12, -4, 8},
    },
};

SaturnSpriteFrame1 DAT_060D67D0 = {
    {0x0100, 0x0000},
    {
        {0x0010, -13, -5, 8},
    },
};

SaturnSpriteFrame1 DAT_060D67DC = {
    {0x0100, 0x0000},
    {
        {0x0010, -14, -6, 8},
    },
};

SaturnSpriteFrame1 DAT_060D67E8 = {
    {0x0100, 0x0000},
    {
        {0x0010, -15, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D67F4 = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6800 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -12, 0},
    },
};

SaturnSpriteFrame1 DAT_060D680C = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -10, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6818 = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6824 = {
    {0x0100, 0x0000},
    {
        {0x0100, 55, 1, 2},
    },
};

SaturnSpriteFrame3 DAT_060D6830 = {
    {0x0300, 0x0000},
    {
        {0x0000, 45, 4, 3},
        {0x0010, 56, 4, 3},
        {0x0000, 41, 4, 4},
    },
};

SaturnSpriteFrame3 DAT_060D684C = {
    {0x0300, 0x0000},
    {
        {0x0000, 43, 4, 5},
        {0x0010, 58, 4, 5},
        {0x0000, 41, 4, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6868 = {
    {0x0200, 0x0000},
    {
        {0x0000, 54, 4, 6},
        {0x0000, 41, 4, 4},
    },
};

SaturnSpriteFrame2 DAT_060D687C = {
    {0x0200, 0x0000},
    {
        {0x0000, 53, 4, 7},
        {0x0000, 41, 4, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6890 = {
    {0x0100, 0x0000},
    {
        {0x0000, 41, 4, 4},
    },
};

SaturnSpriteFrame1 DAT_060D689C = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D68A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 9, 8},
    },
};

SaturnSpriteFrame1 DAT_060D68B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, 12, 8},
    },
};

SaturnSpriteFrame1 DAT_060D68C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 12, 8},
    },
};

SaturnSpriteFrame1 DAT_060D68CC = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, 3, 9},
    },
};

SaturnSpriteFrame2 DAT_060D68D8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 38, 17, 4},
        {0x0000, 41, 10, 10},
    },
};

SaturnSpriteFrame1 DAT_060D68EC = {
    {0x0100, 0x0000},
    {
        {0x0100, 51, 21, 2},
    },
};

SaturnSpriteFrame3 DAT_060D68F8 = {
    {0x0300, 0x0000},
    {
        {0x0000, 40, 25, 3},
        {0x0010, 51, 25, 3},
        {0x0000, 38, 22, 8},
    },
};

SaturnSpriteFrame3 DAT_060D6914 = {
    {0x0300, 0x0000},
    {
        {0x0000, 38, 25, 5},
        {0x0010, 53, 25, 5},
        {0x0000, 38, 22, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6930 = {
    {0x0200, 0x0000},
    {
        {0x0000, 49, 25, 6},
        {0x0000, 38, 22, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6944 = {
    {0x0200, 0x0000},
    {
        {0x0000, 48, 25, 7},
        {0x0000, 38, 22, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6958 = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, 22, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6964 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 20, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6970 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 18, 8},
    },
};

SaturnSpriteFrame1 DAT_060D697C = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 16, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6988 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, 14, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6994 = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, 14, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69A0 = {
    {0x0100, 0x0000},
    {
        {0x0010, -21, 13, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69AC = {
    {0x0100, 0x0000},
    {
        {0x0010, -23, 12, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69B8 = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, 11, 8},
    },
};

SaturnSpriteFrame1 DAT_060D69C4 = {
    {0x0100, 0x0000},
    {
        {0x0010, -19, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D69D0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -31, 0},
    },
};

SaturnSpriteFrame1 DAT_060D69DC = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, -29, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69E8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 51, -26, 0},
    },
};

SaturnSpriteFrame1 DAT_060D69F4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 59, -19, 2},
    },
};

SaturnSpriteFrame3 DAT_060D6A00 = {
    {0x0300, 0x0000},
    {
        {0x0000, 50, -15, 3},
        {0x0010, 61, -15, 3},
        {0x0000, 46, -15, 4},
    },
};

SaturnSpriteFrame3 DAT_060D6A1C = {
    {0x0300, 0x0000},
    {
        {0x0000, 48, -15, 5},
        {0x0010, 63, -15, 5},
        {0x0000, 46, -15, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6A38 = {
    {0x0200, 0x0000},
    {
        {0x0000, 46, -15, 4},
        {0x0000, 59, -15, 6},
    },
};

SaturnSpriteFrame2 DAT_060D6A4C = {
    {0x0200, 0x0000},
    {
        {0x0000, 58, -15, 7},
        {0x0000, 46, -15, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A60 = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -15, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A6C = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6A78 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -9, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6A84 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -8, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6A90 = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -8, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6A9C = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6AA8 = {
    {0x0100, 0x0000},
    {
        {0x0010, -28, -26, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6AB4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -31, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6AC0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -27, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6ACC = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6AD8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 56, -17, 2},
    },
};

SaturnSpriteFrame3 DAT_060D6AE4 = {
    {0x0300, 0x0000},
    {
        {0x0000, 48, -13, 3},
        {0x0010, 59, -13, 3},
        {0x0000, 44, -13, 4},
    },
};

SaturnSpriteFrame3 DAT_060D6B00 = {
    {0x0300, 0x0000},
    {
        {0x0000, 46, -13, 5},
        {0x0010, 61, -13, 5},
        {0x0000, 44, -13, 4},
    },
};

SaturnSpriteFrame2 DAT_060D6B1C = {
    {0x0200, 0x0000},
    {
        {0x0000, 44, -13, 4},
        {0x0000, 57, -13, 6},
    },
};

SaturnSpriteFrame2 DAT_060D6B30 = {
    {0x0200, 0x0000},
    {
        {0x0000, 56, -13, 7},
        {0x0000, 44, -13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6B44 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, -13, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6B50 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -10, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6B5C = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -9, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6B68 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -6, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6B74 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -6, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6B80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -8, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6B8C = {
    {0x0200, 0x0000},
    {
        {0x0000, 46, 4, 4},
        {0x0000, 49, -3, 10},
    },
};

SaturnSpriteFrame1 DAT_060D6BA0 = {
    {0x0100, 0x0000},
    {
        {0x0100, 60, 9, 2},
    },
};

SaturnSpriteFrame3 DAT_060D6BAC = {
    {0x0300, 0x0000},
    {
        {0x0000, 48, 13, 3},
        {0x0010, 59, 13, 3},
        {0x0000, 46, 10, 8},
    },
};

SaturnSpriteFrame3 DAT_060D6BC8 = {
    {0x0300, 0x0000},
    {
        {0x0000, 46, 13, 5},
        {0x0010, 61, 13, 5},
        {0x0000, 46, 10, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6BE4 = {
    {0x0200, 0x0000},
    {
        {0x0000, 57, 13, 6},
        {0x0000, 46, 10, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6BF8 = {
    {0x0200, 0x0000},
    {
        {0x0000, 56, 13, 7},
        {0x0000, 46, 10, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, 10, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 0, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, -3, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C3C = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -7, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6C48 = {
    {0x0100, 0x0000},
    {
        {0x0010, -19, -6, 8},
    },
};

SaturnSpriteFrameHeader* DAT_060D6C54[91] = {
    (SaturnSpriteFrameHeader*)&DAT_060D66E8,
    (SaturnSpriteFrameHeader*)&DAT_060D66EC,
    (SaturnSpriteFrameHeader*)&DAT_060D66F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6704,
    (SaturnSpriteFrameHeader*)&DAT_060D6710,
    (SaturnSpriteFrameHeader*)&DAT_060D671C,
    (SaturnSpriteFrameHeader*)&DAT_060D6728,
    (SaturnSpriteFrameHeader*)&DAT_060D6744,
    (SaturnSpriteFrameHeader*)&DAT_060D6760,
    (SaturnSpriteFrameHeader*)&DAT_060D6774,
    (SaturnSpriteFrameHeader*)&DAT_060D6788,
    (SaturnSpriteFrameHeader*)&DAT_060D6794,
    (SaturnSpriteFrameHeader*)&DAT_060D67A0,
    (SaturnSpriteFrameHeader*)&DAT_060D67AC,
    (SaturnSpriteFrameHeader*)&DAT_060D67B8,
    (SaturnSpriteFrameHeader*)&DAT_060D67C4,
    (SaturnSpriteFrameHeader*)&DAT_060D67D0,
    (SaturnSpriteFrameHeader*)&DAT_060D67DC,
    (SaturnSpriteFrameHeader*)&DAT_060D67E8,
    (SaturnSpriteFrameHeader*)&DAT_060D67F4,
    (SaturnSpriteFrameHeader*)&DAT_060D6800,
    (SaturnSpriteFrameHeader*)&DAT_060D680C,
    (SaturnSpriteFrameHeader*)&DAT_060D6818,
    (SaturnSpriteFrameHeader*)&DAT_060D6824,
    (SaturnSpriteFrameHeader*)&DAT_060D6830,
    (SaturnSpriteFrameHeader*)&DAT_060D684C,
    (SaturnSpriteFrameHeader*)&DAT_060D6868,
    (SaturnSpriteFrameHeader*)&DAT_060D687C,
    (SaturnSpriteFrameHeader*)&DAT_060D6890,
    (SaturnSpriteFrameHeader*)&DAT_060D689C,
    (SaturnSpriteFrameHeader*)&DAT_060D68A8,
    (SaturnSpriteFrameHeader*)&DAT_060D68B4,
    (SaturnSpriteFrameHeader*)&DAT_060D68C0,
    (SaturnSpriteFrameHeader*)&DAT_060D68CC,
    (SaturnSpriteFrameHeader*)&DAT_060D68D8,
    (SaturnSpriteFrameHeader*)&DAT_060D68EC,
    (SaturnSpriteFrameHeader*)&DAT_060D68F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6914,
    (SaturnSpriteFrameHeader*)&DAT_060D6930,
    (SaturnSpriteFrameHeader*)&DAT_060D6944,
    (SaturnSpriteFrameHeader*)&DAT_060D6958,
    (SaturnSpriteFrameHeader*)&DAT_060D6964,
    (SaturnSpriteFrameHeader*)&DAT_060D6970,
    (SaturnSpriteFrameHeader*)&DAT_060D697C,
    (SaturnSpriteFrameHeader*)&DAT_060D6988,
    (SaturnSpriteFrameHeader*)&DAT_060D6994,
    (SaturnSpriteFrameHeader*)&DAT_060D69A0,
    (SaturnSpriteFrameHeader*)&DAT_060D69AC,
    (SaturnSpriteFrameHeader*)&DAT_060D69B8,
    (SaturnSpriteFrameHeader*)&DAT_060D69C4,
    (SaturnSpriteFrameHeader*)&DAT_060D69D0,
    (SaturnSpriteFrameHeader*)&DAT_060D69DC,
    (SaturnSpriteFrameHeader*)&DAT_060D69E8,
    (SaturnSpriteFrameHeader*)&DAT_060D69F4,
    (SaturnSpriteFrameHeader*)&DAT_060D6A00,
    (SaturnSpriteFrameHeader*)&DAT_060D6A1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A38,
    (SaturnSpriteFrameHeader*)&DAT_060D6A4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A60,
    (SaturnSpriteFrameHeader*)&DAT_060D6A6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6A78,
    (SaturnSpriteFrameHeader*)&DAT_060D6A84,
    (SaturnSpriteFrameHeader*)&DAT_060D6A90,
    (SaturnSpriteFrameHeader*)&DAT_060D6A9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6AA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6AC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6ACC,
    (SaturnSpriteFrameHeader*)&DAT_060D6AD8,
    (SaturnSpriteFrameHeader*)&DAT_060D6AE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6B00,
    (SaturnSpriteFrameHeader*)&DAT_060D6B1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B30,
    (SaturnSpriteFrameHeader*)&DAT_060D6B44,
    (SaturnSpriteFrameHeader*)&DAT_060D6B50,
    (SaturnSpriteFrameHeader*)&DAT_060D6B5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6B68,
    (SaturnSpriteFrameHeader*)&DAT_060D6B74,
    (SaturnSpriteFrameHeader*)&DAT_060D6B80,
    (SaturnSpriteFrameHeader*)&DAT_060D6B8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6BA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6C0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C18,
    (SaturnSpriteFrameHeader*)&DAT_060D6C24,
    (SaturnSpriteFrameHeader*)&DAT_060D6C30,
    (SaturnSpriteFrameHeader*)&DAT_060D6C3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C48,
};

SaturnSpriteResource DAT_060D6DC0 = {
    DAT_060D6674, (u16*)&DAT_060D66A4, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6DCC[1] = {&DAT_060D6DC0};
