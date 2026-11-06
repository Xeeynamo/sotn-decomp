// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62C0();
void func_060D62D8();
void func_060D62F0();
void func_060D6308();
void func_060D6320();
void func_060D6338();
void func_060D6344();
void func_060D635C();
void func_060D6374();
void func_060D638C();
void func_060D63A4();
void func_060D63BC();
void func_060D63D4();
void func_060D63EC();
void func_060D6404();
extern SaturnSpriteResource* DAT_060D694C[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62C0,
        func_060D62D8,
        func_060D62F0,
        func_060D6308,
        func_060D6320,
        func_060D6338,
        func_060D6404,
        func_060D6344,
        func_060D635C,
        func_060D6374,
        func_060D638C,
        func_060D63A4,
        func_060D63BC,
        func_060D63D4,
        func_060D63EC,
    },
    DAT_060D694C,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x64A04100, 0xE4A04100, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000};

INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D62C0, func_060D62C0);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D62D8, func_060D62D8);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D62F0, func_060D62F0);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D6308, func_060D6308);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D6320, func_060D6320);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D6338, func_060D6338);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D6344, func_060D6344);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D635C, func_060D635C);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D6374, func_060D6374);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D638C, func_060D638C);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D63A4, func_060D63A4);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D63BC, func_060D63BC);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D63D4, func_060D63D4);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D63EC, func_060D63EC);
INCLUDE_ASM("asm/saturn/weapon/w_02/f_nonmat", f60D6404, func_060D6404);

u16 DAT_060D6410[14] = {0x0201, 0x0202, 0x0403, 0x0604, 0x0605, 0x0806, 0x0807,
                        0x0808, 0x0809, 0x0A0A, 0x0A0B, 0x0A0C, 0x0A0D, 0xFFFF};

u16 DAT_060D642C[14] = {0x0A0E, 0x0C0F, 0x0E10, 0x1011, 0x1012, 0x1213, 0x1214,
                        0x1415, 0x1216, 0x1C1E, 0x1C1F, 0x1C20, 0x1C21, 0xFFFF};

u16 DAT_060D6448[14] = {0x0A0E, 0x0C0F, 0x1617, 0x1818, 0x1819, 0x1A1A, 0x1A1B,
                        0x1A1C, 0x1A1D, 0x1C1E, 0x1C1F, 0x1C20, 0x1C21, 0xFFFF};

u16 DAT_060D6464[11] = {0x0222, 0x0223, 0x0424, 0x0625, 0x0626, 0x0827,
                        0x0828, 0x0829, 0x082A, 0x0A2B, 0xFFFF};

u16 DAT_060D647A[11] = {0x1E2C, 0x1E2D, 0x042E, 0x062F, 0x0630, 0x0831,
                        0x0832, 0x0833, 0x0834, 0x0A3C, 0xFFFF};

u16 DAT_060D6490[22] = {
    0x1E2C, 0x1E2D, 0x2035, 0x2036, 0x2037, 0x2238, 0x2239, 0x223A,
    0x223B, 0x0A3C, 0xFFFF, 0x0004, 0x243D, 0x0004, 0x243E, 0x0004,
    0x243F, 0x0004, 0x2440, 0x0000, 0x0000, 0x0000};

s8 DAT_060D64BC[21][4] = {
    {0, 0, 0, 0},    {-3, -26, 15, 4}, {33, -27, 20, 6}, {50, -18, 10, 8},
    {21, -9, 15, 8}, {-19, -4, 5, 4},  {-13, -8, 15, 4}, {24, -11, 20, 8},
    {40, -1, 10, 8}, {19, 8, 15, 8},   {28, 3, 23, 4},   {21, 2, 15, 12},
    {36, 19, 10, 8}, {14, 18, 15, 8},  {-29, 14, 5, 4},  {-18, -28, 15, 4},
    {30, 4, 25, 12}, {8, -3, 20, 8},   {1, 0, 10, 8},    {0, 0, 19, 15},
    {1, 2, 35, 28}};

u16* DAT_060D6510[7] = {DAT_060D6410, DAT_060D6410, DAT_060D642C, DAT_060D6448,
                        DAT_060D6464, DAT_060D647A, DAT_060D6490};

WeaponAnimation DAT_060D652C[1] = {
    {(u16**)DAT_060D6510, (s8*)DAT_060D64BC, 0x0000, 0x0689, 0x40, 0x03, 0},
};

SaturnSpriteImage DAT_060D653C[6] = {
    {8, 7, 0x0000},  {24, 7, 0x0010},  {12, 3, 0x003C},
    {12, 5, 0x0048}, {24, 17, 0x0058}, {0, 0, 0x00C0},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
} DAT_060D6554 = {
    0x0001,
    {
        {0xAD82, 0x9484, 0x8000, 0x8449, 0xA570, 0xBA33, 0x948F, 0xB0D3, 0xA17A,
         0x9EBA, 0x8842, 0x98C6, 0xA94A, 0xC1EF, 0xD694, 0xEF59},
    },
};

SaturnSpriteFrameHeader DAT_060D6576 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D657A = {
    {0x0100, 0x0000},
    {
        {0x0010, -8, -21, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6586 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6592 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -30, 1},
    },
};

SaturnSpriteFrame1 DAT_060D659E = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -19, 0},
    },
};

SaturnSpriteFrame1 DAT_060D65AA = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D65B6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -9, 2},
    },
};

SaturnSpriteFrame1 DAT_060D65C2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D65CE = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D65DA = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D65E6 = {
    {0x0100, 0x0000},
    {
        {0x0010, -11, -3, 3},
    },
};

SaturnSpriteFrame1 DAT_060D65F2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -13, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D65FE = {
    {0x0100, 0x0000},
    {
        {0x0010, -14, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D660A = {
    {0x0100, 0x0000},
    {
        {0x0010, -15, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6616 = {
    {0x0100, 0x0000},
    {
        {0x0010, -16, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6622 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D662E = {
    {0x0100, 0x0000},
    {
        {0x0000, 27, -14, 1},
    },
};

SaturnSpriteFrame1 DAT_060D663A = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6646 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6652 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, 8, 2},
    },
};

SaturnSpriteFrame1 DAT_060D665E = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D666A = {
    {0x0100, 0x0000},
    {
        {0x0000, 7, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6676 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6682 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, 3, 4},
    },
};

SaturnSpriteFrame1 DAT_060D668E = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, 16, 2},
    },
};

SaturnSpriteFrame1 DAT_060D669A = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, 21, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66A6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 21, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66B2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, 19, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66BE = {
    {0x0100, 0x0000},
    {
        {0x0000, 5, 17, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66CA = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66D6 = {
    {0x0100, 0x0000},
    {
        {0x0010, -19, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66E2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, 13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66EE = {
    {0x0100, 0x0000},
    {
        {0x0010, -21, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D66FA = {
    {0x0100, 0x0000},
    {
        {0x0010, -22, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6706 = {
    {0x0100, 0x0000},
    {
        {0x0010, -11, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6712 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, -28, 0},
    },
};

SaturnSpriteFrame1 DAT_060D671E = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -33, 1},
    },
};

SaturnSpriteFrame1 DAT_060D672A = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6736 = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6742 = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D674E = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D675A = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6766 = {
    {0x0100, 0x0000},
    {
        {0x0000, 6, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6772 = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D677E = {
    {0x0100, 0x0000},
    {
        {0x0010, -18, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D678A = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -28, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6796 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -31, 1},
    },
};

SaturnSpriteFrame1 DAT_060D67A2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -20, 0},
    },
};

SaturnSpriteFrame1 DAT_060D67AE = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D67BA = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -10, 2},
    },
};

SaturnSpriteFrame1 DAT_060D67C6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67D2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67DE = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D67EA = {
    {0x0100, 0x0000},
    {
        {0x0000, 36, -8, 4},
    },
};

SaturnSpriteFrame1 DAT_060D67F6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, 5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6802 = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D680E = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D681A = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6826 = {
    {0x0100, 0x0000},
    {
        {0x0000, 3, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6832 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D683E = {
    {0x0100, 0x0000},
    {
        {0x0010, -18, -5, 3},
    },
};
u16 DAT_060D683E_tail[1] = {
    0x0000,
};

SaturnSpriteFrameHeader* DAT_060D684C[61] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6576,
    (SaturnSpriteFrameHeader*)&DAT_060D657A,
    (SaturnSpriteFrameHeader*)&DAT_060D6586,
    (SaturnSpriteFrameHeader*)&DAT_060D6592,
    (SaturnSpriteFrameHeader*)&DAT_060D659E,
    (SaturnSpriteFrameHeader*)&DAT_060D65AA,
    (SaturnSpriteFrameHeader*)&DAT_060D65B6,
    (SaturnSpriteFrameHeader*)&DAT_060D65C2,
    (SaturnSpriteFrameHeader*)&DAT_060D65CE,
    (SaturnSpriteFrameHeader*)&DAT_060D65DA,
    (SaturnSpriteFrameHeader*)&DAT_060D65E6,
    (SaturnSpriteFrameHeader*)&DAT_060D65F2,
    (SaturnSpriteFrameHeader*)&DAT_060D65FE,
    (SaturnSpriteFrameHeader*)&DAT_060D660A,
    (SaturnSpriteFrameHeader*)&DAT_060D6616,
    (SaturnSpriteFrameHeader*)&DAT_060D6622,
    (SaturnSpriteFrameHeader*)&DAT_060D662E,
    (SaturnSpriteFrameHeader*)&DAT_060D663A,
    (SaturnSpriteFrameHeader*)&DAT_060D6646,
    (SaturnSpriteFrameHeader*)&DAT_060D6652,
    (SaturnSpriteFrameHeader*)&DAT_060D665E,
    (SaturnSpriteFrameHeader*)&DAT_060D666A,
    (SaturnSpriteFrameHeader*)&DAT_060D6676,
    (SaturnSpriteFrameHeader*)&DAT_060D6682,
    (SaturnSpriteFrameHeader*)&DAT_060D668E,
    (SaturnSpriteFrameHeader*)&DAT_060D669A,
    (SaturnSpriteFrameHeader*)&DAT_060D66A6,
    (SaturnSpriteFrameHeader*)&DAT_060D66B2,
    (SaturnSpriteFrameHeader*)&DAT_060D66BE,
    (SaturnSpriteFrameHeader*)&DAT_060D66CA,
    (SaturnSpriteFrameHeader*)&DAT_060D66D6,
    (SaturnSpriteFrameHeader*)&DAT_060D66E2,
    (SaturnSpriteFrameHeader*)&DAT_060D66EE,
    (SaturnSpriteFrameHeader*)&DAT_060D66FA,
    (SaturnSpriteFrameHeader*)&DAT_060D6706,
    (SaturnSpriteFrameHeader*)&DAT_060D6712,
    (SaturnSpriteFrameHeader*)&DAT_060D671E,
    (SaturnSpriteFrameHeader*)&DAT_060D672A,
    (SaturnSpriteFrameHeader*)&DAT_060D6736,
    (SaturnSpriteFrameHeader*)&DAT_060D6742,
    (SaturnSpriteFrameHeader*)&DAT_060D674E,
    (SaturnSpriteFrameHeader*)&DAT_060D675A,
    (SaturnSpriteFrameHeader*)&DAT_060D6766,
    (SaturnSpriteFrameHeader*)&DAT_060D6772,
    (SaturnSpriteFrameHeader*)&DAT_060D677E,
    (SaturnSpriteFrameHeader*)&DAT_060D678A,
    (SaturnSpriteFrameHeader*)&DAT_060D6796,
    (SaturnSpriteFrameHeader*)&DAT_060D67A2,
    (SaturnSpriteFrameHeader*)&DAT_060D67AE,
    (SaturnSpriteFrameHeader*)&DAT_060D67BA,
    (SaturnSpriteFrameHeader*)&DAT_060D67C6,
    (SaturnSpriteFrameHeader*)&DAT_060D67D2,
    (SaturnSpriteFrameHeader*)&DAT_060D67DE,
    (SaturnSpriteFrameHeader*)&DAT_060D67EA,
    (SaturnSpriteFrameHeader*)&DAT_060D67F6,
    (SaturnSpriteFrameHeader*)&DAT_060D6802,
    (SaturnSpriteFrameHeader*)&DAT_060D680E,
    (SaturnSpriteFrameHeader*)&DAT_060D681A,
    (SaturnSpriteFrameHeader*)&DAT_060D6826,
    (SaturnSpriteFrameHeader*)&DAT_060D6832,
    (SaturnSpriteFrameHeader*)&DAT_060D683E,
};

SaturnSpriteResource DAT_060D6940 = {
    DAT_060D653C, (u16*)&DAT_060D6554, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D694C[1] = {&DAT_060D6940};
