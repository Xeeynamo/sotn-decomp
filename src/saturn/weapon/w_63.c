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
extern SaturnSpriteResource* DAT_060D6A50[];

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
    DAT_060D6A50,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x64A04100, 0xE4A04100, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000};

INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D62C8, func_060D62C8);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D62E0, func_060D62E0);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D62F8, func_060D62F8);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D6310, func_060D6310);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D6328, func_060D6328);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D6340, func_060D6340);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D634C, func_060D634C);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D6364, func_060D6364);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D637C, func_060D637C);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D6394, func_060D6394);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D63AC, func_060D63AC);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D63C4, func_060D63C4);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D63DC, func_060D63DC);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D63F4, func_060D63F4);
INCLUDE_ASM("asm/saturn/weapon/w_63/f_nonmat", f60D640C, func_060D640C);

u16 DAT_060D6420[14] = {0x0201, 0x0402, 0x0603, 0x0804, 0x0A05, 0x0C06, 0x0E07,
                        0x1008, 0x1209, 0x140A, 0x140B, 0x140C, 0x140D, 0xFFFF};

u16 DAT_060D643C[14] = {0x160E, 0x180F, 0x1A10, 0x1C11, 0x1C12, 0x1C13, 0x1E14,
                        0x2015, 0x2216, 0x141D, 0x141E, 0x141F, 0x1420, 0xFFFF};

u16 DAT_060D6458[13] = {0x160E, 0x180F, 0x2417, 0x1418, 0x1419, 0x261A, 0x281B,
                        0x281C, 0x141D, 0x141E, 0x141F, 0x1420, 0xFFFF};

u16 DAT_060D6472[14] = {0x2A21, 0x2C22, 0x1423, 0x2E24, 0x2E25, 0x3026, 0x3227,
                        0x3428, 0x3629, 0x142A, 0x142B, 0x142C, 0x142D, 0xFFFF};

u16 DAT_060D648E[14] = {0x382E, 0x3A2F, 0x3C30, 0x3E31, 0x3E32, 0x3E33, 0x4034,
                        0x4235, 0x4436, 0x143D, 0x143E, 0x143F, 0x1440, 0xFFFF};

u16 DAT_060D64AA[13] = {0x382E, 0x3A2F, 0x4637, 0x4838, 0x4838, 0x4A3A, 0x4C3B,
                        0x4E3C, 0x143D, 0x143E, 0x143F, 0x1440, 0xFFFF};

u16* DAT_060D64C4[7] = {DAT_060D6420, DAT_060D6420, DAT_060D643C, DAT_060D6458,
                        DAT_060D6472, DAT_060D648E, DAT_060D64AA};

s8 DAT_060D64E0[40][4] = {
    {0, 0, 0, 0},     {27, -28, 17, 7}, {-15, -28, 17, 7}, {44, -3, 30, 11},
    {68, -14, 34, 6}, {68, -13, 35, 7}, {64, -14, 36, 6},  {45, -18, 27, 7},
    {36, -19, 15, 8}, {25, -18, 15, 8}, {-32, -31, 0, 0},  {18, -13, 17, 7},
    {-25, -5, 12, 7}, {44, 16, 34, 12}, {56, 5, 36, 7},    {33, 1, 21, 7},
    {23, -2, 16, 7},  {18, 0, 15, 7},   {38, 29, 34, 12},  {41, 8, 29, 6},
    {20, 5, 21, 6},   {23, -31, 17, 7}, {-17, -29, 18, 7}, {63, -14, 35, 6},
    {49, -17, 42, 6}, {41, -18, 23, 7}, {32, -21, 16, 8},  {24, -17, 14, 8},
    {6, -31, 12, 7},  {-8, -22, 18, 7}, {39, -4, 45, 14},  {51, -17, 44, 6},
    {42, -18, 24, 7}, {29, -18, 17, 8}, {21, -15, 16, 8},  {42, 11, 40, 19},
    {49, 10, 34, 16}, {47, -10, 26, 5}, {31, -10, 20, 5},  {17, -10, 13, 8}};

WeaponAnimation DAT_060D6580[1] = {
    {(u16**)DAT_060D64C4, (s8*)DAT_060D64E0, 0x0000, 0x062C, 0x60, 0x04, 0},
};

SaturnSpriteImage DAT_060D6590[14] = {
    {20, 8, 0x0000},  {52, 11, 0x0028}, {36, 3, 0x00B8}, {36, 7, 0x00D4},
    {36, 7, 0x0114},  {20, 8, 0x0154},  {28, 7, 0x017C}, {40, 19, 0x01B0},
    {32, 16, 0x0270}, {20, 3, 0x02F0},  {24, 7, 0x0300}, {24, 3, 0x032C},
    {16, 3, 0x0340},  {0, 0, 0x034C},
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding[1];
} DAT_060D65C8 = {
    0x0002,
    {
        {0x8982, 0x8421, 0x84CA, 0x952F, 0xA173, 0x9218, 0x9EDF, 0xA0A4, 0x9E6A,
         0xE9A3, 0xAD02, 0x801B, 0xC5A7, 0xDA4F, 0xDF37, 0xEF99},
        {0x9E00, 0x8018, 0x8438, 0x8C79, 0x9099, 0x98D9, 0x9CFA, 0xA53A, 0xAD7B,
         0xB19B, 0xB9DB, 0xBDFC, 0xC63C, 0xCE7C, 0xD29D, 0xDADD},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D660C = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6610 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -28, 0},
    },
};

SaturnSpriteFrame1 DAT_060D661C = {
    {0x0100, 0x0000},
    {
        {0x0010, -28, -25, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6628 = {
    {0x0200, 0x0000},
    {
        {0x0100, 59, -2, 1},
        {0x0000, 68, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D663C = {
    {0x0100, 0x0000},
    {
        {0x0000, 68, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6648 = {
    {0x0100, 0x0000},
    {
        {0x0000, 68, -14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6654 = {
    {0x0100, 0x0000},
    {
        {0x0000, 65, -14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6660 = {
    {0x0100, 0x0000},
    {
        {0x0000, 44, -17, 4},
    },
};

SaturnSpriteFrame1 DAT_060D666C = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -20, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6678 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -17, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6684 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6690 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D669C = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D66A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -21, -5, 5},
    },
};

SaturnSpriteFrame1 DAT_060D66B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D66C0 = {
    {0x0100, 0x0000},
    {
        {0x0010, -39, -8, 0},
    },
};

SaturnSpriteFrame2 DAT_060D66CC = {
    {0x0200, 0x0000},
    {
        {0x0100, 49, 15, 1},
        {0x0000, 58, 5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66E0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 59, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D66EC = {
    {0x0100, 0x0000},
    {
        {0x0000, 59, 3, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 55, 3, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6704 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, 0, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6710 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D671C = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 1, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6728 = {
    {0x0200, 0x0000},
    {
        {0x0100, 37, 31, 7},
        {0x0000, 52, 32, 8},
    },
};

SaturnSpriteFrame1 DAT_060D673C = {
    {0x0100, 0x0000},
    {
        {0x0000, 53, 32, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6748 = {
    {0x0100, 0x0000},
    {
        {0x0000, 52, 30, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6754 = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, 8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6760 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, 5, 9},
    },
};

SaturnSpriteFrame1 DAT_060D676C = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 4, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6778 = {
    {0x0100, 0x0000},
    {
        {0x0000, -12, 7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6784 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, 8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6790 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, 9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D679C = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D67A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -28, 0},
    },
};

SaturnSpriteFrame1 DAT_060D67B4 = {
    {0x0100, 0x0000},
    {
        {0x0010, -23, -29, 0},
    },
};

SaturnSpriteFrame2 DAT_060D67C0 = {
    {0x0200, 0x0000},
    {
        {0x0100, 51, -2, 1},
        {0x0000, 65, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D67D4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D67E0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 66, -16, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67EC = {
    {0x0100, 0x0000},
    {
        {0x0000, 59, -16, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, -17, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6804 = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6810 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -19, 0},
    },
};

SaturnSpriteFrame1 DAT_060D681C = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6828 = {
    {0x0100, 0x0000},
    {
        {0x0000, -13, -10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6834 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, -9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6840 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, -8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D684C = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -32, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6858 = {
    {0x0100, 0x0000},
    {
        {0x0010, -26, -30, 0},
    },
};

SaturnSpriteFrame2 DAT_060D6864 = {
    {0x0200, 0x0000},
    {
        {0x0100, 51, -2, 1},
        {0x0000, 60, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6878 = {
    {0x0100, 0x0000},
    {
        {0x0000, 61, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6884 = {
    {0x0100, 0x0000},
    {
        {0x0000, 61, -14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6890 = {
    {0x0100, 0x0000},
    {
        {0x0000, 56, -14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D689C = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -17, 10},
    },
};

SaturnSpriteFrame1 DAT_060D68A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -21, 0},
    },
};

SaturnSpriteFrame1 DAT_060D68B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -20, 0},
    },
};

SaturnSpriteFrame2 DAT_060D68C0 = {
    {0x0200, 0x0000},
    {
        {0x0100, 43, 17, 7},
        {0x0000, 60, 19, 8},
    },
};

SaturnSpriteFrame1 DAT_060D68D4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 61, 18, 8},
    },
};

SaturnSpriteFrame1 DAT_060D68E0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 56, 10, 8},
    },
};

SaturnSpriteFrame1 DAT_060D68EC = {
    {0x0100, 0x0000},
    {
        {0x0000, 41, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D68F8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -10, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6904 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -12, 12},
    },
};

SaturnSpriteFrame1 DAT_060D6910 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D691C = {
    {0x0100, 0x0000},
    {
        {0x0000, -13, -8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6928 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, -7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6934 = {
    {0x0100, 0x0000},
    {
        {0x0000, -17, -6, 5},
    },
};

SaturnSpriteFrameHeader* DAT_060D6940[65] = {
    (SaturnSpriteFrameHeader*)&DAT_060D660C,
    (SaturnSpriteFrameHeader*)&DAT_060D6610,
    (SaturnSpriteFrameHeader*)&DAT_060D661C,
    (SaturnSpriteFrameHeader*)&DAT_060D6628,
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
    (SaturnSpriteFrameHeader*)&DAT_060D66E0,
    (SaturnSpriteFrameHeader*)&DAT_060D66EC,
    (SaturnSpriteFrameHeader*)&DAT_060D66F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6704,
    (SaturnSpriteFrameHeader*)&DAT_060D6710,
    (SaturnSpriteFrameHeader*)&DAT_060D671C,
    (SaturnSpriteFrameHeader*)&DAT_060D6728,
    (SaturnSpriteFrameHeader*)&DAT_060D673C,
    (SaturnSpriteFrameHeader*)&DAT_060D6748,
    (SaturnSpriteFrameHeader*)&DAT_060D6754,
    (SaturnSpriteFrameHeader*)&DAT_060D6760,
    (SaturnSpriteFrameHeader*)&DAT_060D676C,
    (SaturnSpriteFrameHeader*)&DAT_060D6778,
    (SaturnSpriteFrameHeader*)&DAT_060D6784,
    (SaturnSpriteFrameHeader*)&DAT_060D6790,
    (SaturnSpriteFrameHeader*)&DAT_060D679C,
    (SaturnSpriteFrameHeader*)&DAT_060D67A8,
    (SaturnSpriteFrameHeader*)&DAT_060D67B4,
    (SaturnSpriteFrameHeader*)&DAT_060D67C0,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6878,
    (SaturnSpriteFrameHeader*)&DAT_060D6884,
    (SaturnSpriteFrameHeader*)&DAT_060D6890,
    (SaturnSpriteFrameHeader*)&DAT_060D689C,
    (SaturnSpriteFrameHeader*)&DAT_060D68A8,
    (SaturnSpriteFrameHeader*)&DAT_060D68B4,
    (SaturnSpriteFrameHeader*)&DAT_060D68C0,
    (SaturnSpriteFrameHeader*)&DAT_060D68D4,
    (SaturnSpriteFrameHeader*)&DAT_060D68E0,
    (SaturnSpriteFrameHeader*)&DAT_060D68EC,
    (SaturnSpriteFrameHeader*)&DAT_060D68F8,
    (SaturnSpriteFrameHeader*)&DAT_060D6904,
    (SaturnSpriteFrameHeader*)&DAT_060D6910,
    (SaturnSpriteFrameHeader*)&DAT_060D691C,
    (SaturnSpriteFrameHeader*)&DAT_060D6928,
    (SaturnSpriteFrameHeader*)&DAT_060D6934,
};

SaturnSpriteResource DAT_060D6A44 = {
    DAT_060D6590, (u16*)&DAT_060D65C8, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6A50[1] = {&DAT_060D6A44};
