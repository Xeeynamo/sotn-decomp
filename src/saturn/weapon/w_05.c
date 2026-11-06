// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62F4();
void func_060D630C();
void func_060D6324();
void func_060D633C();
void func_060D6354();
void func_060D636C();
void func_060D6378();
void func_060D6390();
void func_060D63A8();
void func_060D63C0();
void func_060D63D8();
void func_060D63F0();
void func_060D6408();
void func_060D6420();
void func_060D6438();
extern SaturnSpriteResource* DAT_060D6D54[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62F4,
        func_060D630C,
        func_060D6324,
        func_060D633C,
        func_060D6354,
        func_060D636C,
        func_060D6438,
        func_060D6378,
        func_060D6390,
        func_060D63A8,
        func_060D63C0,
        func_060D63D8,
        func_060D63F0,
        func_060D6408,
        func_060D6420,
    },
    DAT_060D6D54,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D62F4, func_060D62F4);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D630C, func_060D630C);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6324, func_060D6324);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D633C, func_060D633C);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6354, func_060D6354);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D636C, func_060D636C);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6378, func_060D6378);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6390, func_060D6390);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D63A8, func_060D63A8);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D63C0, func_060D63C0);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D63D8, func_060D63D8);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D63F0, func_060D63F0);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6408, func_060D6408);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6420, func_060D6420);
INCLUDE_ASM("asm/saturn/weapon/w_05/f_nonmat", f60D6438, func_060D6438);

u16 DAT_060D6450[18] = {
    0x0201, 0x0202, 0x0403, 0x0604, 0x0606, 0x0607, 0x0608, 0x0609, 0x060A,
    0x060B, 0x0A0C, 0x0A0D, 0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0xFFFF};

u16 DAT_060D6474[18] = {
    0x0C13, 0x0E14, 0x1015, 0x1216, 0x1218, 0x1219, 0x121A, 0x121B, 0x121C,
    0x161D, 0x161E, 0x181F, 0x1620, 0x222D, 0x222E, 0x222F, 0x2230, 0xFFFF};

u16 DAT_060D6498[18] = {
    0x0C13, 0x0E14, 0x1A21, 0x1C22, 0x1C24, 0x1C25, 0x1C26, 0x1C27, 0x1C28,
    0x2029, 0x202A, 0x202B, 0x202C, 0x222D, 0x222E, 0x222F, 0x2230, 0xFFFF};

u16 DAT_060D64BC[16] = {
    0x0231, 0x0232, 0x0433, 0x0634, 0x0636, 0x0637, 0x0638, 0x0639,
    0x063A, 0x063B, 0x0A3C, 0x0A3D, 0x0A3E, 0x0C3F, 0xFFFF, 0x0000};

u16 DAT_060D64DC[16] = {
    0x2440, 0x2441, 0x0442, 0x0643, 0x0645, 0x0646, 0x0647, 0x0648,
    0x0649, 0x0A4A, 0x0A4B, 0x0A4C, 0x0A4D, 0x0C5A, 0xFFFF, 0x0000};

u16 DAT_060D64FC[16] = {
    0x2440, 0x2441, 0x264E, 0x264F, 0x2651, 0x2652, 0x2653, 0x2654,
    0x2655, 0x2A56, 0x2A57, 0x2A58, 0x2A59, 0x0C5A, 0xFFFF, 0x0000};

u16 DAT_060D651C[18] = {
    0x0201, 0x0202, 0x0403, 0x0604, 0x0805, 0x0607, 0x0608, 0x0609, 0x060A,
    0x060B, 0x0A0C, 0x0A0D, 0x0A0E, 0x0C0F, 0x0C10, 0x0C11, 0x0C12, 0xFFFF};

u16 DAT_060D6540[18] = {
    0x0C13, 0x0E14, 0x1015, 0x1216, 0x1417, 0x1219, 0x121A, 0x121B, 0x121C,
    0x161D, 0x161E, 0x181F, 0x1620, 0x222D, 0x222E, 0x222F, 0x2230, 0xFFFF};

u16 DAT_060D6564[18] = {
    0x0C13, 0x0E14, 0x1A21, 0x1C22, 0x1E23, 0x1C25, 0x1C26, 0x1C27, 0x1C28,
    0x2029, 0x202A, 0x202B, 0x202C, 0x222D, 0x222E, 0x222F, 0x2230, 0xFFFF};

u16 DAT_060D6588[15] = {
    0x0231, 0x0232, 0x0433, 0x0634, 0x0835, 0x0637, 0x0638, 0x0639,
    0x063A, 0x063B, 0x0A3C, 0x0A3D, 0x0A3E, 0x0C3F, 0xFFFF};

u16 DAT_060D65A6[15] = {
    0x2440, 0x2441, 0x0442, 0x0643, 0x0844, 0x0646, 0x0647, 0x0648,
    0x0649, 0x0A4A, 0x0A4B, 0x0A4C, 0x0A4D, 0x0C5A, 0xFFFF};

u16 DAT_060D65C4[16] = {
    0x2440, 0x2441, 0x264E, 0x264F, 0x2850, 0x2652, 0x2653, 0x2654,
    0x2655, 0x2A56, 0x2A57, 0x2A58, 0x2A59, 0x0C5A, 0xFFFF, 0x0000};

s8 DAT_060D65E4[22][4] = {
    {0, 0, 0, 0},      {-4, -26, 15, 4}, {33, -27, 17, 6},  {46, -14, 15, 4},
    {56, -15, 23, 18}, {21, -9, 15, 8},  {-19, -4, 5, 4},   {-13, -8, 15, 4},
    {24, -11, 20, 8},  {40, -1, 10, 8},  {49, 4, 24, 17},   {19, 8, 15, 8},
    {28, 3, 23, 4},    {21, 2, 15, 12},  {36, 19, 10, 8},   {45, 24, 20, 22},
    {14, 18, 15, 8},   {-29, 14, 5, 4},  {-18, -28, 15, 4}, {30, 4, 25, 12},
    {51, 12, 26, 19},  {8, -3, 20, 8}};

u16* DAT_060D663C[7] = {DAT_060D6450, DAT_060D6450, DAT_060D6474, DAT_060D6498,
                        DAT_060D64BC, DAT_060D64DC, DAT_060D64FC};

u16* DAT_060D6658[7] = {DAT_060D651C, DAT_060D651C, DAT_060D6540, DAT_060D6564,
                        DAT_060D6588, DAT_060D65A6, DAT_060D65C4};

WeaponAnimation DAT_060D6674[2] = {
    {(u16**)DAT_060D663C, (s8*)DAT_060D65E4, 0x0003, 0x0689, 0x47, 0x03, 0},
    {(u16**)DAT_060D6658, (s8*)DAT_060D65E4, 0x0003, 0x0689, 0x4E, 0x03, 0},
};

SaturnSpriteImage DAT_060D6694[10] = {
    {12, 9, 0x0000},  {24, 7, 0x001C}, {20, 14, 0x0048}, {12, 3, 0x0090},
    {8, 8, 0x009C},   {12, 4, 0x00AC}, {12, 5, 0x00B8},  {16, 5, 0x00C8},
    {24, 17, 0x00DC}, {0, 0, 0x0144},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
} DAT_060D66BC = {
    0x0001,
    {
        {0x90CB, 0xAE40, 0xB340, 0xCBF0, 0xBBFB, 0xB969, 0xD9B0, 0xAD22, 0xBDE5,
         0xD3D7, 0x8842, 0x98C6, 0xA94A, 0xC1EF, 0xD694, 0xEF99},
    },
};

SaturnSpriteFrameHeader DAT_060D66DE = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D66E2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -12, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66EE = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -28, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66FA = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -26, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6706 = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, -20, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6712 = {
    {0x0100, 0x0000},
    {
        {0x0000, 70, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D671E = {
    {0x0100, 0x0000},
    {
        {0x0000, 55, -14, 3},
    },
};

SaturnSpriteFrame3 DAT_060D672A = {
    {0x0300, 0x0000},
    {
        {0x0000, 65, -14, 4},
        {0x0010, 68, -14, 4},
        {0x0000, 55, -14, 3},
    },
};

SaturnSpriteFrame2 DAT_060D6746 = {
    {0x0200, 0x0000},
    {
        {0x0000, 79, -15, 5},
        {0x0000, 55, -14, 3},
    },
};

SaturnSpriteFrame2 DAT_060D675A = {
    {0x0200, 0x0000},
    {
        {0x0000, 79, -14, 6},
        {0x0000, 56, -14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D676E = {
    {0x0100, 0x0000},
    {
        {0x0000, 43, -14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D677A = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6786 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, -5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6792 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D679E = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67AA = {
    {0x0100, 0x0000},
    {
        {0x0010, -16, -3, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67B6 = {
    {0x0100, 0x0000},
    {
        {0x0010, -17, -4, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67C2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -18, -5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67CE = {
    {0x0100, 0x0000},
    {
        {0x0010, -19, -6, 7},
    },
};

SaturnSpriteFrame1 DAT_060D67DA = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D67E6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D67F2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -10, 1},
    },
};

SaturnSpriteFrame1 DAT_060D67FE = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D680A = {
    {0x0100, 0x0000},
    {
        {0x0000, 62, 5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6816 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 4, 3},
    },
};

SaturnSpriteFrame3 DAT_060D6822 = {
    {0x0300, 0x0000},
    {
        {0x0000, 52, 4, 4},
        {0x0010, 55, 4, 4},
        {0x0000, 42, 4, 3},
    },
};

SaturnSpriteFrame2 DAT_060D683E = {
    {0x0200, 0x0000},
    {
        {0x0000, 66, 3, 5},
        {0x0000, 42, 4, 3},
    },
};

SaturnSpriteFrame2 DAT_060D6852 = {
    {0x0200, 0x0000},
    {
        {0x0000, 65, 4, 6},
        {0x0000, 42, 4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6866 = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, 4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6872 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, 7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D687E = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D688A = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, 13, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6896 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, 13, 7},
    },
};

SaturnSpriteFrame1 DAT_060D68A2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, 3, 8},
    },
};

SaturnSpriteFrame1 DAT_060D68AE = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, 17, 3},
    },
};

SaturnSpriteFrame1 DAT_060D68BA = {
    {0x0100, 0x0000},
    {
        {0x0000, 58, 25, 2},
    },
};

SaturnSpriteFrame1 DAT_060D68C6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 23, 7},
    },
};

SaturnSpriteFrame3 DAT_060D68D2 = {
    {0x0300, 0x0000},
    {
        {0x0000, 47, 26, 4},
        {0x0010, 50, 26, 4},
        {0x0000, 42, 23, 7},
    },
};

SaturnSpriteFrame2 DAT_060D68EE = {
    {0x0200, 0x0000},
    {
        {0x0000, 61, 27, 5},
        {0x0000, 42, 23, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6902 = {
    {0x0200, 0x0000},
    {
        {0x0000, 60, 27, 6},
        {0x0000, 42, 23, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6916 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 23, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6922 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, 21, 7},
    },
};

SaturnSpriteFrame1 DAT_060D692E = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 19, 7},
    },
};

SaturnSpriteFrame1 DAT_060D693A = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, 17, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6946 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 15, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6952 = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, 15, 7},
    },
};

SaturnSpriteFrame1 DAT_060D695E = {
    {0x0100, 0x0000},
    {
        {0x0010, -25, 14, 7},
    },
};

SaturnSpriteFrame1 DAT_060D696A = {
    {0x0100, 0x0000},
    {
        {0x0010, -27, 13, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6976 = {
    {0x0100, 0x0000},
    {
        {0x0010, -28, 12, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6982 = {
    {0x0100, 0x0000},
    {
        {0x0010, -15, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D698E = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D699A = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -29, 1},
    },
};

SaturnSpriteFrame1 DAT_060D69A6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D69B2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D69BE = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -15, 3},
    },
};

SaturnSpriteFrame3 DAT_060D69CA = {
    {0x0300, 0x0000},
    {
        {0x0000, 57, -15, 4},
        {0x0010, 60, -15, 4},
        {0x0000, 47, -15, 3},
    },
};

SaturnSpriteFrame2 DAT_060D69E6 = {
    {0x0200, 0x0000},
    {
        {0x0000, 47, -15, 3},
        {0x0000, 70, -16, 5},
    },
};

SaturnSpriteFrame2 DAT_060D69FA = {
    {0x0200, 0x0000},
    {
        {0x0000, 70, -15, 6},
        {0x0000, 47, -15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A0E = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, -15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A1A = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6A26 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -8, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6A32 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -7, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6A3E = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, -7, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6A4A = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, -6, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6A56 = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6A62 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6A6E = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -27, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6A7A = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, -21, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6A86 = {
    {0x0100, 0x0000},
    {
        {0x0000, 63, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6A92 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -13, 3},
    },
};

SaturnSpriteFrame3 DAT_060D6A9E = {
    {0x0300, 0x0000},
    {
        {0x0000, 55, -13, 4},
        {0x0010, 58, -13, 4},
        {0x0000, 45, -13, 3},
    },
};

SaturnSpriteFrame2 DAT_060D6ABA = {
    {0x0200, 0x0000},
    {
        {0x0000, 45, -13, 3},
        {0x0000, 68, -14, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6ACE = {
    {0x0200, 0x0000},
    {
        {0x0000, 68, -13, 6},
        {0x0000, 45, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6AE2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6AEE = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -10, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6AFA = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -8, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6B06 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6B12 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6B1E = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -8, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6B2A = {
    {0x0100, 0x0000},
    {
        {0x0000, 47, 4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6B36 = {
    {0x0100, 0x0000},
    {
        {0x0000, 67, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6B42 = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, 11, 7},
    },
};

SaturnSpriteFrame3 DAT_060D6B4E = {
    {0x0300, 0x0000},
    {
        {0x0000, 55, 15, 4},
        {0x0010, 58, 15, 4},
        {0x0000, 50, 11, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6B6A = {
    {0x0200, 0x0000},
    {
        {0x0000, 69, 15, 5},
        {0x0000, 50, 11, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6B7E = {
    {0x0200, 0x0000},
    {
        {0x0000, 69, 16, 6},
        {0x0000, 50, 11, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6B92 = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, 11, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6B9E = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 1, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6BAA = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -2, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6BB6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, -6, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6BC2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -6, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6BCE = {
    {0x0100, 0x0000},
    {
        {0x0010, -23, -5, 7},
    },
};
u16 DAT_060D6BCE_tail[1] = {
    0x0000,
};

SaturnSpriteFrameHeader* DAT_060D6BDC[91] = {
    (SaturnSpriteFrameHeader*)&DAT_060D66DE,
    (SaturnSpriteFrameHeader*)&DAT_060D66E2,
    (SaturnSpriteFrameHeader*)&DAT_060D66EE,
    (SaturnSpriteFrameHeader*)&DAT_060D66FA,
    (SaturnSpriteFrameHeader*)&DAT_060D6706,
    (SaturnSpriteFrameHeader*)&DAT_060D6712,
    (SaturnSpriteFrameHeader*)&DAT_060D671E,
    (SaturnSpriteFrameHeader*)&DAT_060D672A,
    (SaturnSpriteFrameHeader*)&DAT_060D6746,
    (SaturnSpriteFrameHeader*)&DAT_060D675A,
    (SaturnSpriteFrameHeader*)&DAT_060D676E,
    (SaturnSpriteFrameHeader*)&DAT_060D677A,
    (SaturnSpriteFrameHeader*)&DAT_060D6786,
    (SaturnSpriteFrameHeader*)&DAT_060D6792,
    (SaturnSpriteFrameHeader*)&DAT_060D679E,
    (SaturnSpriteFrameHeader*)&DAT_060D67AA,
    (SaturnSpriteFrameHeader*)&DAT_060D67B6,
    (SaturnSpriteFrameHeader*)&DAT_060D67C2,
    (SaturnSpriteFrameHeader*)&DAT_060D67CE,
    (SaturnSpriteFrameHeader*)&DAT_060D67DA,
    (SaturnSpriteFrameHeader*)&DAT_060D67E6,
    (SaturnSpriteFrameHeader*)&DAT_060D67F2,
    (SaturnSpriteFrameHeader*)&DAT_060D67FE,
    (SaturnSpriteFrameHeader*)&DAT_060D680A,
    (SaturnSpriteFrameHeader*)&DAT_060D6816,
    (SaturnSpriteFrameHeader*)&DAT_060D6822,
    (SaturnSpriteFrameHeader*)&DAT_060D683E,
    (SaturnSpriteFrameHeader*)&DAT_060D6852,
    (SaturnSpriteFrameHeader*)&DAT_060D6866,
    (SaturnSpriteFrameHeader*)&DAT_060D6872,
    (SaturnSpriteFrameHeader*)&DAT_060D687E,
    (SaturnSpriteFrameHeader*)&DAT_060D688A,
    (SaturnSpriteFrameHeader*)&DAT_060D6896,
    (SaturnSpriteFrameHeader*)&DAT_060D68A2,
    (SaturnSpriteFrameHeader*)&DAT_060D68AE,
    (SaturnSpriteFrameHeader*)&DAT_060D68BA,
    (SaturnSpriteFrameHeader*)&DAT_060D68C6,
    (SaturnSpriteFrameHeader*)&DAT_060D68D2,
    (SaturnSpriteFrameHeader*)&DAT_060D68EE,
    (SaturnSpriteFrameHeader*)&DAT_060D6902,
    (SaturnSpriteFrameHeader*)&DAT_060D6916,
    (SaturnSpriteFrameHeader*)&DAT_060D6922,
    (SaturnSpriteFrameHeader*)&DAT_060D692E,
    (SaturnSpriteFrameHeader*)&DAT_060D693A,
    (SaturnSpriteFrameHeader*)&DAT_060D6946,
    (SaturnSpriteFrameHeader*)&DAT_060D6952,
    (SaturnSpriteFrameHeader*)&DAT_060D695E,
    (SaturnSpriteFrameHeader*)&DAT_060D696A,
    (SaturnSpriteFrameHeader*)&DAT_060D6976,
    (SaturnSpriteFrameHeader*)&DAT_060D6982,
    (SaturnSpriteFrameHeader*)&DAT_060D698E,
    (SaturnSpriteFrameHeader*)&DAT_060D699A,
    (SaturnSpriteFrameHeader*)&DAT_060D69A6,
    (SaturnSpriteFrameHeader*)&DAT_060D69B2,
    (SaturnSpriteFrameHeader*)&DAT_060D69BE,
    (SaturnSpriteFrameHeader*)&DAT_060D69CA,
    (SaturnSpriteFrameHeader*)&DAT_060D69E6,
    (SaturnSpriteFrameHeader*)&DAT_060D69FA,
    (SaturnSpriteFrameHeader*)&DAT_060D6A0E,
    (SaturnSpriteFrameHeader*)&DAT_060D6A1A,
    (SaturnSpriteFrameHeader*)&DAT_060D6A26,
    (SaturnSpriteFrameHeader*)&DAT_060D6A32,
    (SaturnSpriteFrameHeader*)&DAT_060D6A3E,
    (SaturnSpriteFrameHeader*)&DAT_060D6A4A,
    (SaturnSpriteFrameHeader*)&DAT_060D6A56,
    (SaturnSpriteFrameHeader*)&DAT_060D6A62,
    (SaturnSpriteFrameHeader*)&DAT_060D6A6E,
    (SaturnSpriteFrameHeader*)&DAT_060D6A7A,
    (SaturnSpriteFrameHeader*)&DAT_060D6A86,
    (SaturnSpriteFrameHeader*)&DAT_060D6A92,
    (SaturnSpriteFrameHeader*)&DAT_060D6A9E,
    (SaturnSpriteFrameHeader*)&DAT_060D6ABA,
    (SaturnSpriteFrameHeader*)&DAT_060D6ACE,
    (SaturnSpriteFrameHeader*)&DAT_060D6AE2,
    (SaturnSpriteFrameHeader*)&DAT_060D6AEE,
    (SaturnSpriteFrameHeader*)&DAT_060D6AFA,
    (SaturnSpriteFrameHeader*)&DAT_060D6B06,
    (SaturnSpriteFrameHeader*)&DAT_060D6B12,
    (SaturnSpriteFrameHeader*)&DAT_060D6B1E,
    (SaturnSpriteFrameHeader*)&DAT_060D6B2A,
    (SaturnSpriteFrameHeader*)&DAT_060D6B36,
    (SaturnSpriteFrameHeader*)&DAT_060D6B42,
    (SaturnSpriteFrameHeader*)&DAT_060D6B4E,
    (SaturnSpriteFrameHeader*)&DAT_060D6B6A,
    (SaturnSpriteFrameHeader*)&DAT_060D6B7E,
    (SaturnSpriteFrameHeader*)&DAT_060D6B92,
    (SaturnSpriteFrameHeader*)&DAT_060D6B9E,
    (SaturnSpriteFrameHeader*)&DAT_060D6BAA,
    (SaturnSpriteFrameHeader*)&DAT_060D6BB6,
    (SaturnSpriteFrameHeader*)&DAT_060D6BC2,
    (SaturnSpriteFrameHeader*)&DAT_060D6BCE,
};

SaturnSpriteResource DAT_060D6D48 = {
    DAT_060D6694, (u16*)&DAT_060D66BC, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6D54[1] = {&DAT_060D6D48};
