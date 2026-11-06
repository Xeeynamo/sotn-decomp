// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62C8();
void func_060D676C();
void func_060D68D4();
void func_060D68EC();
void func_060D6904();
void func_060D691C();
void func_060D6928();
void func_060D6940();
void func_060D6958();
void func_060D6970();
void func_060D6988();
void func_060D69A0();
void func_060D69B8();
void func_060D69D0();
void func_060D69E8();
extern SaturnSpriteResource* DAT_060D70F0[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62C8,
        func_060D676C,
        func_060D68D4,
        func_060D68EC,
        func_060D6904,
        func_060D691C,
        func_060D69E8,
        func_060D6928,
        func_060D6940,
        func_060D6958,
        func_060D6970,
        func_060D6988,
        func_060D69A0,
        func_060D69B8,
        func_060D69D0,
    },
    DAT_060D70F0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D62C8, func_060D62C8);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D66D4, func_060D66D4);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D676C, func_060D676C);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D68D4, func_060D68D4);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D68EC, func_060D68EC);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D6904, func_060D6904);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D691C, func_060D691C);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D6928, func_060D6928);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D6940, func_060D6940);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D6958, func_060D6958);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D6970, func_060D6970);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D6988, func_060D6988);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D69A0, func_060D69A0);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D69B8, func_060D69B8);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D69D0, func_060D69D0);
INCLUDE_ASM("asm/saturn/weapon/w_06/f_nonmat", f60D69E8, func_060D69E8);

u16 DAT_060D6A00[14] = {0x0201, 0x0202, 0x0403, 0x0604, 0x0605, 0x0806, 0x0807,
                        0x0808, 0x0809, 0x0A0A, 0x0A0B, 0x0A0C, 0x0A0D, 0xFFFF};

u16 DAT_060D6A1C[14] = {0x0A0E, 0x0C0F, 0x0E10, 0x1011, 0x1012, 0x1213, 0x1214,
                        0x1415, 0x1216, 0x1C1E, 0x1C1F, 0x1C20, 0x1C21, 0xFFFF};

u16 DAT_060D6A38[14] = {0x0A0E, 0x0C0F, 0x1617, 0x1818, 0x1819, 0x1A1A, 0x1A1B,
                        0x1A1C, 0x1A1D, 0x1C1E, 0x1C1F, 0x1C20, 0x1C21, 0xFFFF};

u16 DAT_060D6A54[11] = {0x0222, 0x0223, 0x0424, 0x0625, 0x0626, 0x0827,
                        0x0828, 0x0829, 0x082A, 0x0A2B, 0xFFFF};

u16 DAT_060D6A6A[11] = {0x1E2C, 0x1E2D, 0x042E, 0x062F, 0x0630, 0x0831,
                        0x0832, 0x0833, 0x0834, 0x0A3C, 0xFFFF};

u16 DAT_060D6A80[22] = {
    0x1E2C, 0x1E2D, 0x2035, 0x2036, 0x2037, 0x2238, 0x2239, 0x223A,
    0x223B, 0x0A3C, 0xFFFF, 0x0004, 0x243D, 0x0004, 0x243E, 0x0004,
    0x243F, 0x0004, 0x2440, 0x0000, 0x0000, 0x0000};

s8 DAT_060D6AAC[21][4] = {
    {0, 0, 0, 0},    {-4, -26, 15, 4}, {33, -27, 20, 6}, {50, -18, 10, 8},
    {21, -9, 15, 8}, {-19, -4, 5, 4},  {-13, -8, 15, 4}, {24, -11, 20, 8},
    {40, -1, 10, 8}, {19, 8, 15, 8},   {28, 3, 23, 4},   {21, 2, 15, 12},
    {36, 19, 10, 8}, {14, 18, 15, 8},  {-29, 14, 5, 4},  {-18, -28, 15, 4},
    {30, 4, 25, 12}, {8, -3, 20, 8},   {1, 0, 10, 8},    {0, 0, 19, 15},
    {1, 2, 35, 28}};

u16* DAT_060D6B00[7] = {DAT_060D6A00, DAT_060D6A00, DAT_060D6A1C, DAT_060D6A38,
                        DAT_060D6A54, DAT_060D6A6A, DAT_060D6A80};

WeaponAnimation DAT_060D6B1C[1] = {
    {(u16**)DAT_060D6B00, (s8*)DAT_060D6AAC, 0x0006, 0x0689, 0x40, 0x03, 0},
};

u32 DAT_060D6B2C[12] = {
    0x00010002, 0x00030004, 0x00050006, 0x00070008, 0x00070006, 0x00050004,
    0x00030002, 0x00014000, 0xFFFE4000, 0x00008000, 0xFFFF0000, 0xFFFFC000,
};

SaturnSpriteImage DAT_060D6B5C[7] = {
    {12, 9, 0x0000},  {24, 7, 0x001C},  {16, 3, 0x0048}, {16, 5, 0x0054},
    {24, 16, 0x0068}, {28, 30, 0x00C8}, {0, 0, 0x019C},
};

struct {
    u16 countAndFlags;
    u16 colors[9][16];
} DAT_060D6B78 = {
    0x0009,
    {
        {0xAD82, 0x9484, 0x8000, 0x8449, 0xA570, 0xBA33, 0x948F, 0xB0D3, 0xA17A,
         0x9EBA, 0x8842, 0x98C6, 0xA94A, 0xC1EF, 0xD694, 0xEF59},
        {0x81A0, 0x9041, 0xFCA6, 0xEC26, 0xD986, 0xD846, 0xD8A8, 0xD90A, 0xD98C,
         0xD9EE, 0xDA50, 0xDAD2, 0xEE6B, 0xDF49, 0xC0A7, 0xD98A},
        {0x81A0, 0xA061, 0xF085, 0xDC24, 0xDAD2, 0xD986, 0xD846, 0xD8A8, 0xD90A,
         0xD98C, 0xD9EE, 0xDA50, 0xDF49, 0xF77A, 0xC0A7, 0xD98A},
        {0x81A0, 0x9041, 0xE464, 0xCC23, 0xDA50, 0xDAD2, 0xD986, 0xD846, 0xD8A8,
         0xD90A, 0xD98C, 0xD9EE, 0xEE6B, 0xDF49, 0xC0A7, 0xD98A},
        {0x81A0, 0xA061, 0xD843, 0xBC22, 0xD9EE, 0xDA50, 0xDAD2, 0xD986, 0xD846,
         0xD8A8, 0xD90A, 0xD98C, 0xDF49, 0xF77A, 0xC0A7, 0xD98A},
        {0x81A0, 0x9041, 0xCC23, 0xB041, 0xD98C, 0xD9EE, 0xDA50, 0xDAD2, 0xD986,
         0xD846, 0xD8A8, 0xD90A, 0xEE6B, 0xDF49, 0xC0A7, 0xD98A},
        {0x81A0, 0xA061, 0xD843, 0xBC22, 0xD90A, 0xD98C, 0xD9EE, 0xDA50, 0xDAD2,
         0xD986, 0xD846, 0xD8A8, 0xDF49, 0xF77A, 0xC0A7, 0xD98A},
        {0x81A0, 0x9041, 0xE464, 0xCC23, 0xD8A8, 0xD90A, 0xD98C, 0xD9EE, 0xDA50,
         0xDAD2, 0xD986, 0xD846, 0xEE6B, 0xDF49, 0xC0A7, 0xD98A},
        {0x81A0, 0xA061, 0xF085, 0xDC24, 0xD846, 0xD8A8, 0xD90A, 0xD98C, 0xD9EE,
         0xDA50, 0xDAD2, 0xD986, 0xDF49, 0xF77A, 0xC0A7, 0xD98A},
    },
};

SaturnSpriteFrameHeader DAT_060D6C9A = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6C9E = {
    {0x0100, 0x0000},
    {
        {0x0010, -12, -22, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CAA = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -28, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CB6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -31, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CC2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -20, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CCE = {
    {0x0100, 0x0000},
    {
        {0x0000, 57, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CDA = {
    {0x0100, 0x0000},
    {
        {0x0000, 51, -9, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CE6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 38, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CF2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6CFE = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D0A = {
    {0x0100, 0x0000},
    {
        {0x0010, -15, -3, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D16 = {
    {0x0100, 0x0000},
    {
        {0x0010, -17, -4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D22 = {
    {0x0100, 0x0000},
    {
        {0x0010, -18, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D2E = {
    {0x0100, 0x0000},
    {
        {0x0010, -19, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D3A = {
    {0x0100, 0x0000},
    {
        {0x0010, -20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D46 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D52 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -15, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6D5E = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D6A = {
    {0x0100, 0x0000},
    {
        {0x0000, 49, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D76 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, 8, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D82 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D8E = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6D9A = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DA6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DB2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, 16, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DBE = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 23, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DCA = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, 21, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DD6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 19, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DE2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 17, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DEE = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6DFA = {
    {0x0100, 0x0000},
    {
        {0x0010, -23, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E06 = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, 13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E12 = {
    {0x0100, 0x0000},
    {
        {0x0010, -25, 12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E1E = {
    {0x0100, 0x0000},
    {
        {0x0010, -26, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E2A = {
    {0x0100, 0x0000},
    {
        {0x0010, -7, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E36 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E42 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -34, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6E4E = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, -23, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E5A = {
    {0x0100, 0x0000},
    {
        {0x0000, 54, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E66 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E72 = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E7E = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E8A = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6E96 = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6EA2 = {
    {0x0100, 0x0000},
    {
        {0x0010, -22, -24, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EAE = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EBA = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, -32, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6EC6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, -21, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6ED2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EDE = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -10, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EEA = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6EF6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F02 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F0E = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -9, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6F1A = {
    {0x0100, 0x0000},
    {
        {0x0000, 53, 5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6F26 = {
    {0x0100, 0x0000},
    {
        {0x0000, 50, 11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F32 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F3E = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F4A = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F56 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, -6, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F62 = {
    {0x0100, 0x0000},
    {
        {0x0010, -22, -5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6F6E = {
    {0x0100, 0x0000},
    {
        {0x0100, -13, 4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F7A = {
    {0x0100, 0x0000},
    {
        {0x0220, -13, 2, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F86 = {
    {0x0100, 0x0000},
    {
        {0x0330, -20, 2, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F92 = {
    {0x0100, 0x0000},
    {
        {0x0410, -19, 4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6F9E = {
    {0x0100, 0x0000},
    {
        {0x0500, -13, 4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6FAA = {
    {0x0100, 0x0000},
    {
        {0x0620, 0, 0, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6FB6 = {
    {0x0100, 0x0000},
    {
        {0x0730, -19, 2, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6FC2 = {
    {0x0100, 0x0000},
    {
        {0x0810, -19, 4, 5},
    },
};
u16 DAT_060D6FC2_tail[1] = {
    0x0000,
};

SaturnSpriteFrameHeader* DAT_060D6FD0[69] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6C9A,
    (SaturnSpriteFrameHeader*)&DAT_060D6C9E,
    (SaturnSpriteFrameHeader*)&DAT_060D6CAA,
    (SaturnSpriteFrameHeader*)&DAT_060D6CB6,
    (SaturnSpriteFrameHeader*)&DAT_060D6CC2,
    (SaturnSpriteFrameHeader*)&DAT_060D6CCE,
    (SaturnSpriteFrameHeader*)&DAT_060D6CDA,
    (SaturnSpriteFrameHeader*)&DAT_060D6CE6,
    (SaturnSpriteFrameHeader*)&DAT_060D6CF2,
    (SaturnSpriteFrameHeader*)&DAT_060D6CFE,
    (SaturnSpriteFrameHeader*)&DAT_060D6D0A,
    (SaturnSpriteFrameHeader*)&DAT_060D6D16,
    (SaturnSpriteFrameHeader*)&DAT_060D6D22,
    (SaturnSpriteFrameHeader*)&DAT_060D6D2E,
    (SaturnSpriteFrameHeader*)&DAT_060D6D3A,
    (SaturnSpriteFrameHeader*)&DAT_060D6D46,
    (SaturnSpriteFrameHeader*)&DAT_060D6D52,
    (SaturnSpriteFrameHeader*)&DAT_060D6D5E,
    (SaturnSpriteFrameHeader*)&DAT_060D6D6A,
    (SaturnSpriteFrameHeader*)&DAT_060D6D76,
    (SaturnSpriteFrameHeader*)&DAT_060D6D82,
    (SaturnSpriteFrameHeader*)&DAT_060D6D8E,
    (SaturnSpriteFrameHeader*)&DAT_060D6D9A,
    (SaturnSpriteFrameHeader*)&DAT_060D6DA6,
    (SaturnSpriteFrameHeader*)&DAT_060D6DB2,
    (SaturnSpriteFrameHeader*)&DAT_060D6DBE,
    (SaturnSpriteFrameHeader*)&DAT_060D6DCA,
    (SaturnSpriteFrameHeader*)&DAT_060D6DD6,
    (SaturnSpriteFrameHeader*)&DAT_060D6DE2,
    (SaturnSpriteFrameHeader*)&DAT_060D6DEE,
    (SaturnSpriteFrameHeader*)&DAT_060D6DFA,
    (SaturnSpriteFrameHeader*)&DAT_060D6E06,
    (SaturnSpriteFrameHeader*)&DAT_060D6E12,
    (SaturnSpriteFrameHeader*)&DAT_060D6E1E,
    (SaturnSpriteFrameHeader*)&DAT_060D6E2A,
    (SaturnSpriteFrameHeader*)&DAT_060D6E36,
    (SaturnSpriteFrameHeader*)&DAT_060D6E42,
    (SaturnSpriteFrameHeader*)&DAT_060D6E4E,
    (SaturnSpriteFrameHeader*)&DAT_060D6E5A,
    (SaturnSpriteFrameHeader*)&DAT_060D6E66,
    (SaturnSpriteFrameHeader*)&DAT_060D6E72,
    (SaturnSpriteFrameHeader*)&DAT_060D6E7E,
    (SaturnSpriteFrameHeader*)&DAT_060D6E8A,
    (SaturnSpriteFrameHeader*)&DAT_060D6E96,
    (SaturnSpriteFrameHeader*)&DAT_060D6EA2,
    (SaturnSpriteFrameHeader*)&DAT_060D6EAE,
    (SaturnSpriteFrameHeader*)&DAT_060D6EBA,
    (SaturnSpriteFrameHeader*)&DAT_060D6EC6,
    (SaturnSpriteFrameHeader*)&DAT_060D6ED2,
    (SaturnSpriteFrameHeader*)&DAT_060D6EDE,
    (SaturnSpriteFrameHeader*)&DAT_060D6EEA,
    (SaturnSpriteFrameHeader*)&DAT_060D6EF6,
    (SaturnSpriteFrameHeader*)&DAT_060D6F02,
    (SaturnSpriteFrameHeader*)&DAT_060D6F0E,
    (SaturnSpriteFrameHeader*)&DAT_060D6F1A,
    (SaturnSpriteFrameHeader*)&DAT_060D6F26,
    (SaturnSpriteFrameHeader*)&DAT_060D6F32,
    (SaturnSpriteFrameHeader*)&DAT_060D6F3E,
    (SaturnSpriteFrameHeader*)&DAT_060D6F4A,
    (SaturnSpriteFrameHeader*)&DAT_060D6F56,
    (SaturnSpriteFrameHeader*)&DAT_060D6F62,
    (SaturnSpriteFrameHeader*)&DAT_060D6F6E,
    (SaturnSpriteFrameHeader*)&DAT_060D6F7A,
    (SaturnSpriteFrameHeader*)&DAT_060D6F86,
    (SaturnSpriteFrameHeader*)&DAT_060D6F92,
    (SaturnSpriteFrameHeader*)&DAT_060D6F9E,
    (SaturnSpriteFrameHeader*)&DAT_060D6FAA,
    (SaturnSpriteFrameHeader*)&DAT_060D6FB6,
    (SaturnSpriteFrameHeader*)&DAT_060D6FC2,
};

SaturnSpriteResource DAT_060D70E4 = {
    DAT_060D6B5C, (u16*)&DAT_060D6B78, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D70F0[1] = {&DAT_060D70E4};
