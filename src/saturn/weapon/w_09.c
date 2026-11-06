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
void func_060D6C4C();
void func_060D6C64();
void func_060D6C7C();
void func_060D6C94();
void func_060D6CAC();
void func_060D6CC4();
void func_060D6CDC();
void func_060D6CF4();
extern SaturnSpriteResource* DAT_060D73FC[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D64B0,
        func_060D64C8,
        func_060D64E0,
        func_060D64F8,
        func_060D6510,
        func_060D6CF4,
        func_060D651C,
        func_060D6C4C,
        func_060D6C64,
        func_060D6C7C,
        func_060D6C94,
        func_060D6CAC,
        func_060D6CC4,
        func_060D6CDC,
    },
    DAT_060D73FC,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D64B0, func_060D64B0);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D64C8, func_060D64C8);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D64E0, func_060D64E0);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D64F8, func_060D64F8);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6510, func_060D6510);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D651C, func_060D651C);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6C4C, func_060D6C4C);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6C64, func_060D6C64);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6C7C, func_060D6C7C);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6C94, func_060D6C94);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6CAC, func_060D6CAC);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6CC4, func_060D6CC4);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6CDC, func_060D6CDC);
INCLUDE_ASM("asm/saturn/weapon/w_09/f_nonmat", f60D6CF4, func_060D6CF4);

u32 DAT_060D6D00[157] = {
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
    0x08FF040C, 0x060D6D00, 0x060D6D08, 0x060D6E68, 0x060D6E74, 0x060D6E5C,
    0x060D6DD8, 0x060D6DB8, 0x060D6D80, 0x060D6D3C, 0x060D6D10, 0x060D6E1C,
    0x060D6E2C, 0x060D6E3C, 0x060D6E4C, 0x00000000, 0x00000200, 0x00000400,
    0x00000600, 0x00000800, 0x00000A00, 0x00000C00, 0x00000E00, 0x00001000,
    0xFFFFEE00, 0x00001400, 0x00001600, 0x00001800, 0x00001A00, 0x00001C00,
    0x00001E00,
};

SaturnSpriteImage DAT_060D6F74[6] = {
    {16, 20, 0x0000}, {20, 20, 0x0050}, {16, 20, 0x00B4},
    {32, 40, 0x0104}, {32, 40, 0x0244}, {0, 0, 0x0384},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D6F8C = {
    0x0003,
    {
        {0x8902, 0x8421, 0xA86A, 0xB8CD, 0xCD6F, 0xE24F, 0x8D2F, 0x91D6, 0x929B,
         0x9084, 0x9D08, 0xA96C, 0xB9F0, 0xC654, 0xD2D8, 0xE35C},
        {0x81C0, 0xD71D, 0xAD6F, 0x9D6D, 0x9972, 0xAA98, 0x9063, 0x9CC6, 0xA508,
         0xB16B, 0xB9CE, 0xC210, 0xCE73, 0xD6B5, 0xE318, 0xEF7B},
        {0xC8E0, 0x8421, 0xAC6A, 0xB515, 0x8322, 0x8CC9, 0x8D51, 0xA9F6, 0xC6BA,
         0x9084, 0x9CE7, 0xA949, 0xB5AC, 0xC630, 0xD6B4, 0xE758},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6FF0 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6FF4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7000 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 17, 0},
    },
};

SaturnSpriteFrame1 DAT_060D700C = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7018 = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7024 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7030 = {
    {0x0100, 0x0000},
    {
        {0x0014, -11, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D703C = {
    {0x0100, 0x0000},
    {
        {0x0014, -9, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7048 = {
    {0x0100, 0x0000},
    {
        {0x0004, -4, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7054 = {
    {0x0100, 0x0000},
    {
        {0x0004, 1, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7060 = {
    {0x0100, 0x0000},
    {
        {0x0004, 10, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D706C = {
    {0x0100, 0x0000},
    {
        {0x0104, 13, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7078 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7084 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7090 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D709C = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70A8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70B4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70C0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70CC = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70D8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70E4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70F0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70FC = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7108 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7114 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7120 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D712C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7138 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7144 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7150 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D715C = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7168 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7174 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7180 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D718C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7198 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71A4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71B0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71BC = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71C8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71D4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71F8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7204 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7210 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D721C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7228 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7234 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 1, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7240 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -1, 2},
    },
};

SaturnSpriteFrame1 DAT_060D724C = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7258 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7264 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 16, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7270 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, 17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D727C = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7288 = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7294 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 1, 5, 0},
    },
};

SaturnSpriteFrame2 DAT_060D72DC = {
    {0x0200, 0x0000},
    {
        {0x0200, -32, -13, 3},
        {0x0200, 32, -13, 4},
    },
};

SaturnSpriteFrameHeader* DAT_060D72F0[64] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6FF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FF4,
    (SaturnSpriteFrameHeader*)&DAT_060D7000,
    (SaturnSpriteFrameHeader*)&DAT_060D700C,
    (SaturnSpriteFrameHeader*)&DAT_060D7018,
    (SaturnSpriteFrameHeader*)&DAT_060D7024,
    (SaturnSpriteFrameHeader*)&DAT_060D7030,
    (SaturnSpriteFrameHeader*)&DAT_060D703C,
    (SaturnSpriteFrameHeader*)&DAT_060D7048,
    (SaturnSpriteFrameHeader*)&DAT_060D7054,
    (SaturnSpriteFrameHeader*)&DAT_060D7060,
    (SaturnSpriteFrameHeader*)&DAT_060D706C,
    (SaturnSpriteFrameHeader*)&DAT_060D7078,
    (SaturnSpriteFrameHeader*)&DAT_060D7084,
    (SaturnSpriteFrameHeader*)&DAT_060D7090,
    (SaturnSpriteFrameHeader*)&DAT_060D709C,
    (SaturnSpriteFrameHeader*)&DAT_060D70A8,
    (SaturnSpriteFrameHeader*)&DAT_060D70B4,
    (SaturnSpriteFrameHeader*)&DAT_060D70C0,
    (SaturnSpriteFrameHeader*)&DAT_060D70CC,
    (SaturnSpriteFrameHeader*)&DAT_060D70D8,
    (SaturnSpriteFrameHeader*)&DAT_060D70E4,
    (SaturnSpriteFrameHeader*)&DAT_060D70F0,
    (SaturnSpriteFrameHeader*)&DAT_060D70FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7108,
    (SaturnSpriteFrameHeader*)&DAT_060D7114,
    (SaturnSpriteFrameHeader*)&DAT_060D7120,
    (SaturnSpriteFrameHeader*)&DAT_060D712C,
    (SaturnSpriteFrameHeader*)&DAT_060D7138,
    (SaturnSpriteFrameHeader*)&DAT_060D7144,
    (SaturnSpriteFrameHeader*)&DAT_060D7150,
    (SaturnSpriteFrameHeader*)&DAT_060D715C,
    (SaturnSpriteFrameHeader*)&DAT_060D7168,
    (SaturnSpriteFrameHeader*)&DAT_060D7174,
    (SaturnSpriteFrameHeader*)&DAT_060D7180,
    (SaturnSpriteFrameHeader*)&DAT_060D718C,
    (SaturnSpriteFrameHeader*)&DAT_060D7198,
    (SaturnSpriteFrameHeader*)&DAT_060D71A4,
    (SaturnSpriteFrameHeader*)&DAT_060D71B0,
    (SaturnSpriteFrameHeader*)&DAT_060D71BC,
    (SaturnSpriteFrameHeader*)&DAT_060D71C8,
    (SaturnSpriteFrameHeader*)&DAT_060D71D4,
    (SaturnSpriteFrameHeader*)&DAT_060D71E0,
    (SaturnSpriteFrameHeader*)&DAT_060D71EC,
    (SaturnSpriteFrameHeader*)&DAT_060D71F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7204,
    (SaturnSpriteFrameHeader*)&DAT_060D7210,
    (SaturnSpriteFrameHeader*)&DAT_060D721C,
    (SaturnSpriteFrameHeader*)&DAT_060D7228,
    (SaturnSpriteFrameHeader*)&DAT_060D7234,
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
};

SaturnSpriteResource DAT_060D73F0 = {
    DAT_060D6F74, (u16*)&DAT_060D6F8C, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D73FC[1] = {&DAT_060D73F0};
