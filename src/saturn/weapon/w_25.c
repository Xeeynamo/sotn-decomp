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
void func_060D6E94();
void func_060D73E8();
void func_060D7400();
void func_060D7418();
void func_060D7430();
void func_060D7448();
void func_060D7460();
void func_060D7478();
extern SaturnSpriteResource* DAT_060D7C48[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D64B0,
        func_060D64C8,
        func_060D64E0,
        func_060D64F8,
        func_060D6510,
        func_060D7478,
        func_060D651C,
        func_060D6E94,
        func_060D73E8,
        func_060D7400,
        func_060D7418,
        func_060D7430,
        func_060D7448,
        func_060D7460,
    },
    DAT_060D7C48,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D64B0, func_060D64B0);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D64C8, func_060D64C8);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D64E0, func_060D64E0);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D64F8, func_060D64F8);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D6510, func_060D6510);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D651C, func_060D651C);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D6E94, func_060D6E94);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D73E8, func_060D73E8);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D7400, func_060D7400);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D7418, func_060D7418);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D7430, func_060D7430);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D7448, func_060D7448);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D7460, func_060D7460);
INCLUDE_ASM("asm/saturn/weapon/w_25/f_nonmat", f60D7478, func_060D7478);

u32 DAT_060D7490[157] = {
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
    0x08FF040C, 0x060D7490, 0x060D7498, 0x060D75F8, 0x060D7604, 0x060D75EC,
    0x060D7568, 0x060D7548, 0x060D7510, 0x060D74CC, 0x060D74A0, 0x060D75AC,
    0x060D75BC, 0x060D75CC, 0x060D75DC, 0x00000000, 0x00000200, 0x00000400,
    0x00000600, 0x00000800, 0x00000A00, 0x00000C00, 0x00000E00, 0x00001000,
    0x00001200, 0x00001400, 0x00001600, 0x00001800, 0x00001A00, 0x00001C00,
    0x00001E00,
};

SaturnSpriteImage DAT_060D7704[21] = {
    {12, 10, 0x0000}, {12, 10, 0x0020}, {12, 10, 0x0040}, {60, 44, 0x0060},
    {20, 4, 0x02F4},  {20, 4, 0x0308},  {20, 4, 0x031C},  {20, 4, 0x0330},
    {20, 4, 0x0344},  {20, 4, 0x0358},  {20, 4, 0x036C},  {20, 4, 0x0380},
    {20, 4, 0x0394},  {20, 4, 0x03A8},  {20, 4, 0x03BC},  {20, 4, 0x03D0},
    {20, 4, 0x03E4},  {20, 4, 0x03F8},  {20, 4, 0x040C},  {20, 4, 0x0420},
    {0, 0, 0x0434},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D7758 = {
    0x0003,
    {
        {0x8220, 0x9509, 0x8842, 0x98C7, 0xA508, 0xB16B, 0xBDCD, 0xD292, 0xE316,
         0xF379, 0x88C2, 0x98E4, 0xA164, 0x84CA, 0x9191, 0xAA34},
        {0x8D80, 0x83E0, 0x8400, 0x8420, 0x8820, 0x8840, 0x8C40, 0x8C60, 0x9060,
         0x9080, 0x9480, 0x94A0, 0x98A0, 0x98C0, 0x9CC0, 0x9CE0},
        {0xD005, 0x8513, 0x8842, 0x98C7, 0xA508, 0xB16B, 0xBDCD, 0xD292, 0xE316,
         0xF379, 0xA5DF, 0xA104, 0xA164, 0xA9E6, 0xB266, 0xD6EF},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D77BC = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D77C0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77CC = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77D8 = {
    {0x0100, 0x0000},
    {
        {0x0014, -16, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77E4 = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77F0 = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77FC = {
    {0x0100, 0x0000},
    {
        {0x0014, -12, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7808 = {
    {0x0100, 0x0000},
    {
        {0x0014, -10, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7814 = {
    {0x0100, 0x0000},
    {
        {0x0004, -5, -8, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7820 = {
    {0x0100, 0x0000},
    {
        {0x0004, 0, -6, 1},
    },
};

SaturnSpriteFrame1 DAT_060D782C = {
    {0x0100, 0x0000},
    {
        {0x0004, 9, -6, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7838 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7844 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7850 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D785C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7868 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7874 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7880 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D788C = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7898 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78A4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78B0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78BC = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78C8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78D4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78F8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7904 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7910 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D791C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7928 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7934 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7940 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D794C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7958 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7964 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7970 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D797C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7988 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7994 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79DC = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79E8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79F4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A00 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -6, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7A0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -8, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7A18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -10, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7A24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 8, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7A30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 9, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7A3C = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 10, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7A48 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A54 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A60 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A6C = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A78 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A84 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A90 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -9, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A9C = {
    {0x0100, 0x0000},
    {
        {0x0004, 2, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AA8 = {
    {0x0100, 0x0000},
    {
        {0x0100, -4, -19, 3},
    },
};

SaturnSpriteFrame16 DAT_060D7AB4 = {
    {0x1000, 0x0000},
    {
        {0x0200, 4, -87, 4},
        {0x0200, 4, -79, 5},
        {0x0200, 4, -71, 6},
        {0x0200, 4, -63, 7},
        {0x0200, 4, -55, 8},
        {0x0200, 4, -47, 9},
        {0x0200, 4, -39, 10},
        {0x0200, 4, -31, 11},
        {0x0200, 4, -23, 12},
        {0x0200, 4, -15, 13},
        {0x0200, 4, 1, 14},
        {0x0200, 4, 9, 15},
        {0x0200, 4, 17, 16},
        {0x0200, 4, 25, 17},
        {0x0200, 4, 33, 18},
        {0x0200, 4, -7, 19},
    },
};

SaturnSpriteFrameHeader* DAT_060D7B38[65] = {
    (SaturnSpriteFrameHeader*)&DAT_060D77BC,
    (SaturnSpriteFrameHeader*)&DAT_060D77C0,
    (SaturnSpriteFrameHeader*)&DAT_060D77CC,
    (SaturnSpriteFrameHeader*)&DAT_060D77D8,
    (SaturnSpriteFrameHeader*)&DAT_060D77E4,
    (SaturnSpriteFrameHeader*)&DAT_060D77F0,
    (SaturnSpriteFrameHeader*)&DAT_060D77FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7808,
    (SaturnSpriteFrameHeader*)&DAT_060D7814,
    (SaturnSpriteFrameHeader*)&DAT_060D7820,
    (SaturnSpriteFrameHeader*)&DAT_060D782C,
    (SaturnSpriteFrameHeader*)&DAT_060D7838,
    (SaturnSpriteFrameHeader*)&DAT_060D7844,
    (SaturnSpriteFrameHeader*)&DAT_060D7850,
    (SaturnSpriteFrameHeader*)&DAT_060D785C,
    (SaturnSpriteFrameHeader*)&DAT_060D7868,
    (SaturnSpriteFrameHeader*)&DAT_060D7874,
    (SaturnSpriteFrameHeader*)&DAT_060D7880,
    (SaturnSpriteFrameHeader*)&DAT_060D788C,
    (SaturnSpriteFrameHeader*)&DAT_060D7898,
    (SaturnSpriteFrameHeader*)&DAT_060D78A4,
    (SaturnSpriteFrameHeader*)&DAT_060D78B0,
    (SaturnSpriteFrameHeader*)&DAT_060D78BC,
    (SaturnSpriteFrameHeader*)&DAT_060D78C8,
    (SaturnSpriteFrameHeader*)&DAT_060D78D4,
    (SaturnSpriteFrameHeader*)&DAT_060D78E0,
    (SaturnSpriteFrameHeader*)&DAT_060D78EC,
    (SaturnSpriteFrameHeader*)&DAT_060D78F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7904,
    (SaturnSpriteFrameHeader*)&DAT_060D7910,
    (SaturnSpriteFrameHeader*)&DAT_060D791C,
    (SaturnSpriteFrameHeader*)&DAT_060D7928,
    (SaturnSpriteFrameHeader*)&DAT_060D7934,
    (SaturnSpriteFrameHeader*)&DAT_060D7940,
    (SaturnSpriteFrameHeader*)&DAT_060D794C,
    (SaturnSpriteFrameHeader*)&DAT_060D7958,
    (SaturnSpriteFrameHeader*)&DAT_060D7964,
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
    (SaturnSpriteFrameHeader*)&DAT_060D7AB4,
};

SaturnSpriteResource DAT_060D7C3C = {
    DAT_060D7704, (u16*)&DAT_060D7758, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7C48[1] = {&DAT_060D7C3C};
