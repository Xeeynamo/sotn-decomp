// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D64F0();
void func_060D6508();
void func_060D6520();
void func_060D6538();
void func_060D6550();
void func_060D6568();
void func_060D6574();
void func_060D6C28();
void func_060D6C44();
void func_060D6E50();
void func_060D6E68();
void func_060D6E80();
void func_060D6E98();
void func_060D6EB0();
void func_060D6EC8();
extern SaturnSpriteResource* DAT_060D76B8[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D64F0,
        func_060D6508,
        func_060D6520,
        func_060D6538,
        func_060D6550,
        func_060D6568,
        func_060D6EC8,
        func_060D6574,
        func_060D6C28,
        func_060D6C44,
        func_060D6E50,
        func_060D6E68,
        func_060D6E80,
        func_060D6E98,
        func_060D6EB0,
    },
    DAT_060D76B8,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D64F0, func_060D64F0);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6508, func_060D6508);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6520, func_060D6520);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6538, func_060D6538);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6550, func_060D6550);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6568, func_060D6568);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6574, func_060D6574);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6C28, func_060D6C28);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6C44, func_060D6C44);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6E50, func_060D6E50);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6E68, func_060D6E68);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6E80, func_060D6E80);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6E98, func_060D6E98);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6EB0, func_060D6EB0);
INCLUDE_ASM("asm/saturn/weapon/w_23/f_nonmat", f60D6EC8, func_060D6EC8);

u32 DAT_060D6EE0[171] = {
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
    0x08FF040C, 0x060D6EE0, 0x060D6EE8, 0x060D7048, 0x060D7054, 0x060D703C,
    0x060D6FB8, 0x060D6F98, 0x060D6F60, 0x060D6F1C, 0x060D6EF0, 0x060D6FFC,
    0x060D700C, 0x060D701C, 0x060D702C, 0x00020C3F, 0x00020C40, 0x00020C41,
    0x00020C42, 0x00030C43, 0x00000000, 0x00000000, 0x00000200, 0x00000400,
    0x00000600, 0x00000800, 0x00000A00, 0x00000C00, 0x00000E00, 0x00001000,
    0x00001200, 0x00001400, 0x00001600, 0x00001800, 0x00001A00, 0x00001C00,
    0x00001E00, 0x8000BF00, 0x803FBF3F, 0xBF008000, 0xBF3F803F, 0x803FBF3F,
    0x8000BF00, 0xBF3F803F, 0xBF008000,
};

SaturnSpriteImage DAT_060D718C[11] = {
    {12, 16, 0x0000}, {16, 16, 0x0030}, {12, 16, 0x0070}, {20, 15, 0x00A0},
    {12, 8, 0x00EC},  {12, 8, 0x0104},  {8, 6, 0x011C},   {8, 7, 0x0128},
    {60, 43, 0x0138}, {44, 36, 0x03C0}, {0, 0, 0x054C},
};

struct {
    u16 countAndFlags;
    u16 colors[4][16];
    u16 padding[1];
} DAT_060D71B8 = {
    0x0004,
    {
        {0x8E0F, 0x9821, 0x8D2F, 0x9594, 0xA219, 0x92FF, 0x9099, 0x98DF, 0xB4E8,
         0x9084, 0xA109, 0xAD6C, 0xBA11, 0xC654, 0xD2D8, 0xE35C},
        {0x8100, 0x815B, 0x819C, 0x921D, 0x969E, 0xAF5F, 0xD7DF, 0xFFFF, 0xE900,
         0xED40, 0xF180, 0xF604, 0xFA85, 0xFF4B, 0xFFD5, 0xFFDC},
        {0x8581, 0x9463, 0xB527, 0xCDAC, 0xDA52, 0xEB18, 0xBF5C, 0xB555, 0xCE3F,
         0x9CC8, 0x910E, 0x9973, 0xAA1A, 0xAE9E, 0xC6FE, 0xE35D},
        {0x8100, 0x8400, 0x8420, 0x8421, 0x8821, 0x8841, 0x8842, 0x8C42, 0x8C62,
         0x8C63, 0x9063, 0x9083, 0x9084, 0x9484, 0x94A4, 0x94A5},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D723C = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7240 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D724C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, 14, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7258 = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7264 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7270 = {
    {0x0100, 0x0000},
    {
        {0x0014, -12, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D727C = {
    {0x0100, 0x0000},
    {
        {0x0014, -11, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7288 = {
    {0x0100, 0x0000},
    {
        {0x0014, -9, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7294 = {
    {0x0100, 0x0000},
    {
        {0x0004, -1, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D72A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 3, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D72AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 10, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D72B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72DC = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72E8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72F4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7300 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D730C = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7318 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7324 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7330 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D733C = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7348 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7354 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7360 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D736C = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7378 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7384 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7390 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D739C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73A8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73B4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73C0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73CC = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73D8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73E4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73F0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73FC = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7408 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7414 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7420 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D742C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7438 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7444 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7450 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D745C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7468 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7474 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7480 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D748C = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7498 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -6, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74A4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74B0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74BC = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D74C8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74D4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 11, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74F8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7504 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7510 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D751C = {
    {0x0100, 0x0000},
    {
        {0x0004, 0, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7528 = {
    {0x0100, 0x0000},
    {
        {0x0104, 3, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7534 = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 1, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7540 = {
    {0x0100, 0x0000},
    {
        {0x0100, 3, 1, 5},
    },
};

SaturnSpriteFrame1 DAT_060D754C = {
    {0x0100, 0x0000},
    {
        {0x0100, 1, 1, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7558 = {
    {0x0100, 0x0000},
    {
        {0x0100, 0, 1, 7},
    },
};

SaturnSpriteFrame1 DAT_060D7564 = {
    {0x0100, 0x0000},
    {
        {0x0200, 17, 26, 8},
    },
};

SaturnSpriteFrame4 DAT_060D7570 = {
    {0x0400, 0x0000},
    {
        {0x0300, -34, -1, 9},
        {0x0310, 36, -1, 9},
        {0x0330, 36, 52, 9},
        {0x0320, -34, 52, 9},
    },
};

SaturnSpriteFrameHeader* DAT_060D7594[70] = {
    (SaturnSpriteFrameHeader*)&DAT_060D723C,
    (SaturnSpriteFrameHeader*)&DAT_060D7240,
    (SaturnSpriteFrameHeader*)&DAT_060D724C,
    (SaturnSpriteFrameHeader*)&DAT_060D7258,
    (SaturnSpriteFrameHeader*)&DAT_060D7264,
    (SaturnSpriteFrameHeader*)&DAT_060D7270,
    (SaturnSpriteFrameHeader*)&DAT_060D727C,
    (SaturnSpriteFrameHeader*)&DAT_060D7288,
    (SaturnSpriteFrameHeader*)&DAT_060D7294,
    (SaturnSpriteFrameHeader*)&DAT_060D72A0,
    (SaturnSpriteFrameHeader*)&DAT_060D72AC,
    (SaturnSpriteFrameHeader*)&DAT_060D72B8,
    (SaturnSpriteFrameHeader*)&DAT_060D72C4,
    (SaturnSpriteFrameHeader*)&DAT_060D72D0,
    (SaturnSpriteFrameHeader*)&DAT_060D72DC,
    (SaturnSpriteFrameHeader*)&DAT_060D72E8,
    (SaturnSpriteFrameHeader*)&DAT_060D72F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7300,
    (SaturnSpriteFrameHeader*)&DAT_060D730C,
    (SaturnSpriteFrameHeader*)&DAT_060D7318,
    (SaturnSpriteFrameHeader*)&DAT_060D7324,
    (SaturnSpriteFrameHeader*)&DAT_060D7330,
    (SaturnSpriteFrameHeader*)&DAT_060D733C,
    (SaturnSpriteFrameHeader*)&DAT_060D7348,
    (SaturnSpriteFrameHeader*)&DAT_060D7354,
    (SaturnSpriteFrameHeader*)&DAT_060D7360,
    (SaturnSpriteFrameHeader*)&DAT_060D736C,
    (SaturnSpriteFrameHeader*)&DAT_060D7378,
    (SaturnSpriteFrameHeader*)&DAT_060D7384,
    (SaturnSpriteFrameHeader*)&DAT_060D7390,
    (SaturnSpriteFrameHeader*)&DAT_060D739C,
    (SaturnSpriteFrameHeader*)&DAT_060D73A8,
    (SaturnSpriteFrameHeader*)&DAT_060D73B4,
    (SaturnSpriteFrameHeader*)&DAT_060D73C0,
    (SaturnSpriteFrameHeader*)&DAT_060D73CC,
    (SaturnSpriteFrameHeader*)&DAT_060D73D8,
    (SaturnSpriteFrameHeader*)&DAT_060D73E4,
    (SaturnSpriteFrameHeader*)&DAT_060D73F0,
    (SaturnSpriteFrameHeader*)&DAT_060D73FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7408,
    (SaturnSpriteFrameHeader*)&DAT_060D7414,
    (SaturnSpriteFrameHeader*)&DAT_060D7420,
    (SaturnSpriteFrameHeader*)&DAT_060D742C,
    (SaturnSpriteFrameHeader*)&DAT_060D7438,
    (SaturnSpriteFrameHeader*)&DAT_060D7444,
    (SaturnSpriteFrameHeader*)&DAT_060D7450,
    (SaturnSpriteFrameHeader*)&DAT_060D745C,
    (SaturnSpriteFrameHeader*)&DAT_060D7468,
    (SaturnSpriteFrameHeader*)&DAT_060D7474,
    (SaturnSpriteFrameHeader*)&DAT_060D7480,
    (SaturnSpriteFrameHeader*)&DAT_060D748C,
    (SaturnSpriteFrameHeader*)&DAT_060D7498,
    (SaturnSpriteFrameHeader*)&DAT_060D74A4,
    (SaturnSpriteFrameHeader*)&DAT_060D74B0,
    (SaturnSpriteFrameHeader*)&DAT_060D74BC,
    (SaturnSpriteFrameHeader*)&DAT_060D74C8,
    (SaturnSpriteFrameHeader*)&DAT_060D74D4,
    (SaturnSpriteFrameHeader*)&DAT_060D74E0,
    (SaturnSpriteFrameHeader*)&DAT_060D74EC,
    (SaturnSpriteFrameHeader*)&DAT_060D74F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7504,
    (SaturnSpriteFrameHeader*)&DAT_060D7510,
    (SaturnSpriteFrameHeader*)&DAT_060D751C,
    (SaturnSpriteFrameHeader*)&DAT_060D7528,
    (SaturnSpriteFrameHeader*)&DAT_060D7534,
    (SaturnSpriteFrameHeader*)&DAT_060D7540,
    (SaturnSpriteFrameHeader*)&DAT_060D754C,
    (SaturnSpriteFrameHeader*)&DAT_060D7558,
    (SaturnSpriteFrameHeader*)&DAT_060D7564,
    (SaturnSpriteFrameHeader*)&DAT_060D7570,
};

SaturnSpriteResource DAT_060D76AC = {
    DAT_060D718C, (u16*)&DAT_060D71B8, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D76B8[1] = {&DAT_060D76AC};
