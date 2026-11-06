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
void func_060D659C();
void func_060D6CCC();
void func_060D728C();
void func_060D72A4();
void func_060D72BC();
void func_060D72D4();
void func_060D72EC();
void func_060D7304();
void func_060D731C();
extern SaturnSpriteResource* DAT_060D7A64[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D64B0,
        func_060D64C8,
        func_060D64E0,
        func_060D64F8,
        func_060D6510,
        func_060D731C,
        func_060D659C,
        func_060D6CCC,
        func_060D728C,
        func_060D72A4,
        func_060D72BC,
        func_060D72D4,
        func_060D72EC,
        func_060D7304,
    },
    DAT_060D7A64,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D64B0, func_060D64B0);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D64C8, func_060D64C8);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D64E0, func_060D64E0);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D64F8, func_060D64F8);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D6510, func_060D6510);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D651C, func_060D651C);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D659C, func_060D659C);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D6CCC, func_060D6CCC);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D728C, func_060D728C);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D72A4, func_060D72A4);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D72BC, func_060D72BC);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D72D4, func_060D72D4);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D72EC, func_060D72EC);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D7304, func_060D7304);
INCLUDE_ASM("asm/saturn/weapon/w_28/f_nonmat", f60D731C, func_060D731C);

u32 DAT_060D7330[166] = {
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
    0x08FF040C, 0x060D7330, 0x060D7338, 0x060D7498, 0x060D74A4, 0x060D748C,
    0x060D7408, 0x060D73E8, 0x060D73B0, 0x060D736C, 0x060D7340, 0x060D744C,
    0x060D745C, 0x060D746C, 0x060D747C, 0x00000000, 0x81A0D717, 0xC272B5EE,
    0x9D4B98C8, 0x8C858842, 0x90E2A546, 0xDAD68CA9, 0x995399B6, 0xA659F39C,
    0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000A00,
    0x00000C00, 0x00000E00, 0x00001000, 0x00001200, 0x00001400, 0x00001600,
    0x00001800, 0x00001A00, 0x00001C00, 0x00001E00,
};

SaturnSpriteImage DAT_060D75C8[7] = {
    {12, 13, 0x0000}, {12, 13, 0x0028}, {12, 13, 0x0050}, {12, 16, 0x0078},
    {40, 32, 0x00A8}, {40, 39, 0x01E8}, {0, 0, 0x0370},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D75E4 = {
    0x0003,
    {
        {0x81E0, 0xD717, 0xC272, 0xB5EE, 0x9D69, 0x9907, 0x8C85, 0x8842, 0x98C3,
         0xBDEF, 0xDAD6, 0x845F, 0x9973, 0x9A3D, 0xA71F, 0xEF9B},
        {0x8000, 0x8020, 0x9081, 0x94A1, 0x98C1, 0x8020, 0x8020, 0x9081, 0x94A1,
         0x98C1, 0x9CE1, 0xA101, 0xA941, 0xB9A0, 0xCE60, 0xB5A0},
        {0x81A0, 0xD717, 0xC272, 0xB5EE, 0x9D4B, 0x98C8, 0x8C85, 0x8842, 0x90E2,
         0xA546, 0xDAD6, 0x8CA9, 0x9953, 0x99B6, 0xA659, 0xF39C},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D7648 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D764C = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7658 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 13, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7664 = {
    {0x0100, 0x0000},
    {
        {0x0014, -16, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7670 = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D767C = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7688 = {
    {0x0100, 0x0000},
    {
        {0x0014, -12, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7694 = {
    {0x0100, 0x0000},
    {
        {0x0014, -10, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, -5, -5, 1},
    },
};

SaturnSpriteFrame1 DAT_060D76AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 0, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D76B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 9, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D76C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76DC = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76E8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76F4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7700 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D770C = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7718 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7724 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7730 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D773C = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7748 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7754 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7760 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D776C = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7778 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7784 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7790 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D779C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77A8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77B4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77C0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77CC = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77D8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77E4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77F0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77FC = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7808 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7814 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7820 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D782C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7838 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7844 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7850 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D785C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7868 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7874 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7880 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D788C = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7898 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D78A4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D78B0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 11, 2},
    },
};

SaturnSpriteFrame1 DAT_060D78BC = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D78C8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D78D4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78F8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7904 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7910 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D791C = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7928 = {
    {0x0100, 0x0000},
    {
        {0x0004, 2, 1, 0},
    },
};

SaturnSpriteFrame2 DAT_060D7934 = {
    {0x0200, 0x0000},
    {
        {0x0100, 52, -7, 3},
        {0x0100, 0, -7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7948 = {
    {0x0100, 0x0000},
    {
        {0x0200, 4, -14, 5},
    },
};

SaturnSpriteFrameHeader* DAT_060D7954[65] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7648,
    (SaturnSpriteFrameHeader*)&DAT_060D764C,
    (SaturnSpriteFrameHeader*)&DAT_060D7658,
    (SaturnSpriteFrameHeader*)&DAT_060D7664,
    (SaturnSpriteFrameHeader*)&DAT_060D7670,
    (SaturnSpriteFrameHeader*)&DAT_060D767C,
    (SaturnSpriteFrameHeader*)&DAT_060D7688,
    (SaturnSpriteFrameHeader*)&DAT_060D7694,
    (SaturnSpriteFrameHeader*)&DAT_060D76A0,
    (SaturnSpriteFrameHeader*)&DAT_060D76AC,
    (SaturnSpriteFrameHeader*)&DAT_060D76B8,
    (SaturnSpriteFrameHeader*)&DAT_060D76C4,
    (SaturnSpriteFrameHeader*)&DAT_060D76D0,
    (SaturnSpriteFrameHeader*)&DAT_060D76DC,
    (SaturnSpriteFrameHeader*)&DAT_060D76E8,
    (SaturnSpriteFrameHeader*)&DAT_060D76F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7700,
    (SaturnSpriteFrameHeader*)&DAT_060D770C,
    (SaturnSpriteFrameHeader*)&DAT_060D7718,
    (SaturnSpriteFrameHeader*)&DAT_060D7724,
    (SaturnSpriteFrameHeader*)&DAT_060D7730,
    (SaturnSpriteFrameHeader*)&DAT_060D773C,
    (SaturnSpriteFrameHeader*)&DAT_060D7748,
    (SaturnSpriteFrameHeader*)&DAT_060D7754,
    (SaturnSpriteFrameHeader*)&DAT_060D7760,
    (SaturnSpriteFrameHeader*)&DAT_060D776C,
    (SaturnSpriteFrameHeader*)&DAT_060D7778,
    (SaturnSpriteFrameHeader*)&DAT_060D7784,
    (SaturnSpriteFrameHeader*)&DAT_060D7790,
    (SaturnSpriteFrameHeader*)&DAT_060D779C,
    (SaturnSpriteFrameHeader*)&DAT_060D77A8,
    (SaturnSpriteFrameHeader*)&DAT_060D77B4,
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
    (SaturnSpriteFrameHeader*)&DAT_060D7948,
};

SaturnSpriteResource DAT_060D7A58 = {
    DAT_060D75C8, (u16*)&DAT_060D75E4, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7A64[1] = {&DAT_060D7A58};
