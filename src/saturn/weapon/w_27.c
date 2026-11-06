// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6498();
void func_060D64B0();
void func_060D64C8();
void func_060D64E0();
void func_060D64F8();
void func_060D6510();
void func_060D651C();
void func_060D6940();
void func_060D7210();
void func_060D72CC();
void func_060D72E4();
void func_060D72FC();
void func_060D7314();
void func_060D732C();
void func_060D7344();
extern SaturnSpriteResource* DAT_060D7C2C[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D64B0,
        func_060D64C8,
        func_060D64E0,
        func_060D64F8,
        func_060D6510,
        func_060D7344,
        func_060D651C,
        func_060D6940,
        func_060D7210,
        func_060D72CC,
        func_060D72E4,
        func_060D72FC,
        func_060D7314,
        func_060D732C,
    },
    DAT_060D7C2C,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x00000000, 0x28720000, 0x0022FFFF, 0x000B1000,
    0x00000000, 0x00002882, 0x00000023};

INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D64B0, func_060D64B0);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D64C8, func_060D64C8);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D64E0, func_060D64E0);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D64F8, func_060D64F8);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D6510, func_060D6510);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D651C, func_060D651C);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D6940, func_060D6940);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D7210, func_060D7210);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D72CC, func_060D72CC);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D72E4, func_060D72E4);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D72FC, func_060D72FC);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D7314, func_060D7314);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D732C, func_060D732C);
INCLUDE_ASM("asm/saturn/weapon/w_27/f_nonmat", f60D7344, func_060D7344);

u32 DAT_060D7350[159] = {
    0x00020201, 0x00000000, 0x00020402, 0x00000000, 0x00020603, 0x00020604,
    0x00020605, 0x00020606, 0x00020607, 0x00020608, 0x00020809, 0x0002020A,
    0x0002020B, 0x0002020C, 0x00000000, 0x0003020D, 0x00030E0E, 0x0003100F,
    0x00031210, 0x00031411, 0x00031612, 0x00031813, 0x00031A14, 0x00031C15,
    0x00031A16, 0x00031817, 0x00031618, 0x00031419, 0x0003121A, 0x0003101B,
    0x00030E1C, 0x00000000, 0x00010224, 0x00010225, 0x00010226, 0x00010227,
    0x00010228, 0x00010229, 0x0001022A, 0x0001022B, 0x0001022C, 0x0001022D,
    0x0001022E, 0x0001022F, 0x00010230, 0x00000000, 0x0001022A, 0x0001022B,
    0x0001022C, 0x0001022D, 0x0001022E, 0x0001022F, 0x00010230, 0x00000000,
    0x00020221, 0x00020222, 0x00020223, 0x00020224, 0x00020225, 0x00020226,
    0x00020227, 0x00020228, 0x00020229, 0x0002022A, 0x0002022B, 0x0002022C,
    0x0002022D, 0x0002022E, 0x0002022F, 0x00020230, 0x00000000, 0x00020231,
    0x00020232, 0x00020233, 0xFFFF0000, 0x00020434, 0x00020435, 0x00020436,
    0xFFFF0000, 0x00020233, 0x00020232, 0x00020231, 0xFFFF0000, 0x00020436,
    0x00020435, 0x00020434, 0xFFFF0000, 0x0004021D, 0x0004021E, 0x00000000,
    0x00020C1F, 0x00020C20, 0x00000000, 0x00032237, 0x00032238, 0x00032238,
    0x00032038, 0x00031E38, 0x00030239, 0x0003023A, 0x0003023B, 0x0003023C,
    0x0003023D, 0x00030201, 0x00030201, 0x00030201, 0x00030201, 0x00030201,
    0x00000000, 0x00000000, 0x0EF9040C, 0x0E0D040C, 0xF5F9040C, 0x01FB040C,
    0xE0E10000, 0x16FA040C, 0x0FFA040C, 0x10FB040C, 0x11FC040C, 0x12FD040C,
    0x13FE040C, 0x14FF040C, 0x1500040C, 0x1601040C, 0x0CFB040C, 0x0AFD040C,
    0x08FF040C, 0x060D7350, 0x060D7358, 0x060D74B8, 0x060D74C4, 0x060D74AC,
    0x060D7428, 0x060D7408, 0x060D73D0, 0x060D738C, 0x060D7360, 0x060D746C,
    0x060D747C, 0x060D748C, 0x060D749C, 0x00040C40, 0x00030C41, 0x00030C42,
    0x00030C43, 0x00030C44, 0x00030C45, 0x00030C46, 0x00030C47, 0x00030C48,
    0x00000000, 0x00010C3F, 0x00020A3E, 0x00000000, 0x16151413, 0x13131212,
    0x12111111, 0x1010100F, 0x0E0D0000,
};

SaturnSpriteImage DAT_060D75CC[24] = {
    {16, 20, 0x0000}, {20, 16, 0x0050}, {16, 20, 0x00A0}, {16, 20, 0x00F0},
    {20, 20, 0x0140}, {20, 16, 0x01A4}, {20, 16, 0x01F4}, {20, 16, 0x0244},
    {20, 16, 0x0294}, {20, 16, 0x02E4}, {20, 16, 0x0334}, {20, 16, 0x0384},
    {20, 16, 0x03D4}, {4, 8, 0x0424},   {4, 8, 0x042C},   {4, 8, 0x0434},
    {4, 8, 0x043C},   {4, 8, 0x0444},   {4, 8, 0x044C},   {4, 8, 0x0454},
    {4, 8, 0x045C},   {4, 8, 0x0464},   {4, 8, 0x046C},   {0, 0, 0x0474},
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding[1];
} DAT_060D762C = {
    0x0002,
    {
        {0x8267, 0xB31C, 0x8219, 0x80F6, 0x800E, 0x80A0, 0x9D80, 0xC5A0, 0xCEA0,
         0x8421, 0x806A, 0x8151, 0x8299, 0xB18C, 0xD294, 0x8019},
        {0xB0A5, 0x80F3, 0x819C, 0x921D, 0x969E, 0xAF5F, 0xD7DF, 0xFFFF, 0xE900,
         0xED40, 0xF180, 0xF604, 0xFA85, 0xFF4B, 0xFFD5, 0x84A8},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D7670 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7674 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -11, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7680 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, 9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D768C = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -8, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7698 = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -8, 1},
    },
};

SaturnSpriteFrame1 DAT_060D76A4 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -7, 1},
    },
};

SaturnSpriteFrame1 DAT_060D76B0 = {
    {0x0100, 0x0000},
    {
        {0x0014, -12, -7, 1},
    },
};

SaturnSpriteFrame1 DAT_060D76BC = {
    {0x0100, 0x0000},
    {
        {0x0014, -10, -6, 1},
    },
};

SaturnSpriteFrame1 DAT_060D76C8 = {
    {0x0100, 0x0000},
    {
        {0x0004, -6, -8, 2},
    },
};

SaturnSpriteFrame1 DAT_060D76D4 = {
    {0x0100, 0x0000},
    {
        {0x0004, -3, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D76E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 5, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D76EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76F8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7704 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7710 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D771C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7728 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7734 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7740 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D774C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7758 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7764 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7770 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D777C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7788 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7794 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77DC = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77E8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77F4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7800 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D780C = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7818 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7824 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7830 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D783C = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7848 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7854 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7860 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D786C = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7878 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7884 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7890 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D789C = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78A8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D78C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D78CC = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -11, 3},
    },
};

SaturnSpriteFrame1 DAT_060D78D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D78E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 8, 3},
    },
};

SaturnSpriteFrame1 DAT_060D78F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D78FC = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7908 = {
    {0x0100, 0x0000},
    {
        {0x0004, 11, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7914 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7920 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D792C = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7938 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7944 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7950 = {
    {0x0100, 0x0000},
    {
        {0x0004, 0, -3, 0},
    },
};

SaturnSpriteFrame2 DAT_060D795C = {
    {0x0200, 0x0000},
    {
        {0x0000, 0, -3, 0},
        {0x0100, 1, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7970 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D797C = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7988 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -2, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7994 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -2, 7},
    },
};

SaturnSpriteFrame1 DAT_060D79A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -2, 8},
    },
};

SaturnSpriteFrame1 DAT_060D79AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -2, 9},
    },
};

SaturnSpriteFrame1 DAT_060D79B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -2, 10},
    },
};

SaturnSpriteFrame1 DAT_060D79C4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -2, 11},
    },
};

SaturnSpriteFrame1 DAT_060D79D0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -2, 12},
    },
};

SaturnSpriteFrame1 DAT_060D79DC = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 13},
    },
};

SaturnSpriteFrame1 DAT_060D79E8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 14},
    },
};

SaturnSpriteFrame1 DAT_060D79F4 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 15},
    },
};

SaturnSpriteFrame1 DAT_060D7A00 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 16},
    },
};

SaturnSpriteFrame1 DAT_060D7A0C = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 16},
    },
};

SaturnSpriteFrame1 DAT_060D7A18 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 16},
    },
};

SaturnSpriteFrame1 DAT_060D7A24 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 17},
    },
};

SaturnSpriteFrame1 DAT_060D7A30 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 17},
    },
};

SaturnSpriteFrame1 DAT_060D7A3C = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 17},
    },
};

SaturnSpriteFrame1 DAT_060D7A48 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 18},
    },
};

SaturnSpriteFrame1 DAT_060D7A54 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 18},
    },
};

SaturnSpriteFrame1 DAT_060D7A60 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 18},
    },
};

SaturnSpriteFrame1 DAT_060D7A6C = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 19},
    },
};

SaturnSpriteFrame1 DAT_060D7A78 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 19},
    },
};

SaturnSpriteFrame1 DAT_060D7A84 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 19},
    },
};

SaturnSpriteFrame1 DAT_060D7A90 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 20},
    },
};

SaturnSpriteFrame1 DAT_060D7A9C = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 21},
    },
};

SaturnSpriteFrame1 DAT_060D7AA8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 22},
    },
};

SaturnSpriteFrameHeader* DAT_060D7AB4[91] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7670,
    (SaturnSpriteFrameHeader*)&DAT_060D7674,
    (SaturnSpriteFrameHeader*)&DAT_060D7680,
    (SaturnSpriteFrameHeader*)&DAT_060D768C,
    (SaturnSpriteFrameHeader*)&DAT_060D7698,
    (SaturnSpriteFrameHeader*)&DAT_060D76A4,
    (SaturnSpriteFrameHeader*)&DAT_060D76B0,
    (SaturnSpriteFrameHeader*)&DAT_060D76BC,
    (SaturnSpriteFrameHeader*)&DAT_060D76C8,
    (SaturnSpriteFrameHeader*)&DAT_060D76D4,
    (SaturnSpriteFrameHeader*)&DAT_060D76E0,
    (SaturnSpriteFrameHeader*)&DAT_060D76EC,
    (SaturnSpriteFrameHeader*)&DAT_060D76F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7704,
    (SaturnSpriteFrameHeader*)&DAT_060D7710,
    (SaturnSpriteFrameHeader*)&DAT_060D771C,
    (SaturnSpriteFrameHeader*)&DAT_060D7728,
    (SaturnSpriteFrameHeader*)&DAT_060D7734,
    (SaturnSpriteFrameHeader*)&DAT_060D7740,
    (SaturnSpriteFrameHeader*)&DAT_060D774C,
    (SaturnSpriteFrameHeader*)&DAT_060D7758,
    (SaturnSpriteFrameHeader*)&DAT_060D7764,
    (SaturnSpriteFrameHeader*)&DAT_060D7770,
    (SaturnSpriteFrameHeader*)&DAT_060D777C,
    (SaturnSpriteFrameHeader*)&DAT_060D7788,
    (SaturnSpriteFrameHeader*)&DAT_060D7794,
    (SaturnSpriteFrameHeader*)&DAT_060D77A0,
    (SaturnSpriteFrameHeader*)&DAT_060D77AC,
    (SaturnSpriteFrameHeader*)&DAT_060D77B8,
    (SaturnSpriteFrameHeader*)&DAT_060D77C4,
    (SaturnSpriteFrameHeader*)&DAT_060D77D0,
    (SaturnSpriteFrameHeader*)&DAT_060D77DC,
    (SaturnSpriteFrameHeader*)&DAT_060D77E8,
    (SaturnSpriteFrameHeader*)&DAT_060D77F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7800,
    (SaturnSpriteFrameHeader*)&DAT_060D780C,
    (SaturnSpriteFrameHeader*)&DAT_060D7818,
    (SaturnSpriteFrameHeader*)&DAT_060D7824,
    (SaturnSpriteFrameHeader*)&DAT_060D7830,
    (SaturnSpriteFrameHeader*)&DAT_060D783C,
    (SaturnSpriteFrameHeader*)&DAT_060D7848,
    (SaturnSpriteFrameHeader*)&DAT_060D7854,
    (SaturnSpriteFrameHeader*)&DAT_060D7860,
    (SaturnSpriteFrameHeader*)&DAT_060D786C,
    (SaturnSpriteFrameHeader*)&DAT_060D7878,
    (SaturnSpriteFrameHeader*)&DAT_060D7884,
    (SaturnSpriteFrameHeader*)&DAT_060D7890,
    (SaturnSpriteFrameHeader*)&DAT_060D789C,
    (SaturnSpriteFrameHeader*)&DAT_060D78A8,
    (SaturnSpriteFrameHeader*)&DAT_060D78B4,
    (SaturnSpriteFrameHeader*)&DAT_060D78C0,
    (SaturnSpriteFrameHeader*)&DAT_060D78CC,
    (SaturnSpriteFrameHeader*)&DAT_060D78D8,
    (SaturnSpriteFrameHeader*)&DAT_060D78E4,
    (SaturnSpriteFrameHeader*)&DAT_060D78F0,
    (SaturnSpriteFrameHeader*)&DAT_060D78FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7908,
    (SaturnSpriteFrameHeader*)&DAT_060D7914,
    (SaturnSpriteFrameHeader*)&DAT_060D7920,
    (SaturnSpriteFrameHeader*)&DAT_060D792C,
    (SaturnSpriteFrameHeader*)&DAT_060D7938,
    (SaturnSpriteFrameHeader*)&DAT_060D7944,
    (SaturnSpriteFrameHeader*)&DAT_060D7950,
    (SaturnSpriteFrameHeader*)&DAT_060D795C,
    (SaturnSpriteFrameHeader*)&DAT_060D7970,
    (SaturnSpriteFrameHeader*)&DAT_060D797C,
    (SaturnSpriteFrameHeader*)&DAT_060D7988,
    (SaturnSpriteFrameHeader*)&DAT_060D7994,
    (SaturnSpriteFrameHeader*)&DAT_060D79A0,
    (SaturnSpriteFrameHeader*)&DAT_060D79AC,
    (SaturnSpriteFrameHeader*)&DAT_060D79B8,
    (SaturnSpriteFrameHeader*)&DAT_060D79C4,
    (SaturnSpriteFrameHeader*)&DAT_060D79D0,
    (SaturnSpriteFrameHeader*)&DAT_060D79DC,
    (SaturnSpriteFrameHeader*)&DAT_060D79E8,
    (SaturnSpriteFrameHeader*)&DAT_060D79F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7A00,
    (SaturnSpriteFrameHeader*)&DAT_060D7A0C,
    (SaturnSpriteFrameHeader*)&DAT_060D7A18,
    (SaturnSpriteFrameHeader*)&DAT_060D7A24,
    (SaturnSpriteFrameHeader*)&DAT_060D7A30,
    (SaturnSpriteFrameHeader*)&DAT_060D7A3C,
    (SaturnSpriteFrameHeader*)&DAT_060D7A48,
    (SaturnSpriteFrameHeader*)&DAT_060D7A54,
    (SaturnSpriteFrameHeader*)&DAT_060D7A60,
    (SaturnSpriteFrameHeader*)&DAT_060D7A6C,
    (SaturnSpriteFrameHeader*)&DAT_060D7A78,
    (SaturnSpriteFrameHeader*)&DAT_060D7A84,
    (SaturnSpriteFrameHeader*)&DAT_060D7A90,
    (SaturnSpriteFrameHeader*)&DAT_060D7A9C,
    (SaturnSpriteFrameHeader*)&DAT_060D7AA8,
};

SaturnSpriteResource DAT_060D7C20 = {
    DAT_060D75CC, (u16*)&DAT_060D762C, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7C2C[1] = {&DAT_060D7C20};
