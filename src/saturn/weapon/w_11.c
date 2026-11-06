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
void func_060D6D90();
void func_060D730C();
void func_060D7324();
void func_060D733C();
void func_060D7354();
void func_060D736C();
void func_060D7384();
void func_060D739C();
extern SaturnSpriteResource* DAT_060D7B64[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D64B0,
        func_060D64C8,
        func_060D64E0,
        func_060D64F8,
        func_060D6510,
        func_060D739C,
        func_060D651C,
        func_060D6D90,
        func_060D730C,
        func_060D7324,
        func_060D733C,
        func_060D7354,
        func_060D736C,
        func_060D7384,
    },
    DAT_060D7B64,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D64B0, func_060D64B0);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D64C8, func_060D64C8);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D64E0, func_060D64E0);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D64F8, func_060D64F8);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D6510, func_060D6510);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D651C, func_060D651C);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D6D90, func_060D6D90);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D730C, func_060D730C);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D7324, func_060D7324);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D733C, func_060D733C);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D7354, func_060D7354);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D736C, func_060D736C);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D7384, func_060D7384);
INCLUDE_ASM("asm/saturn/weapon/w_11/f_nonmat", f60D739C, func_060D739C);

u32 DAT_060D73B0[167] = {
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
    0x08FF040C, 0x060D73B0, 0x060D73B8, 0x060D7518, 0x060D7524, 0x060D750C,
    0x060D7488, 0x060D7468, 0x060D7430, 0x060D73EC, 0x060D73C0, 0x060D74CC,
    0x060D74DC, 0x060D74EC, 0x060D74FC, 0x00030C3F, 0x00020C40, 0x00020C41,
    0x00030C42, 0x00020C41, 0x00020C40, 0x00000000, 0x00010E43, 0x000C1044,
    0xFFFF0000, 0x00000000, 0x00000200, 0x00000400, 0x00000600, 0x00000800,
    0x00000A00, 0x00000C00, 0x00000E00, 0x00001000, 0x00001200, 0x00001400,
    0x00001600, 0x00001800, 0x00001A00, 0x00001C00, 0x00001E00,
};

SaturnSpriteImage DAT_060D764C[14] = {
    {16, 24, 0x0000}, {16, 24, 0x0060}, {16, 24, 0x00C0}, {20, 12, 0x0120},
    {20, 16, 0x015C}, {20, 16, 0x01AC}, {12, 12, 0x01FC}, {12, 12, 0x0220},
    {24, 20, 0x0244}, {20, 12, 0x02BC}, {32, 32, 0x02F8}, {32, 24, 0x03F8},
    {20, 32, 0x04B8}, {0, 0, 0x0558},
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding[1];
} DAT_060D7684 = {
    0x0002,
    {
        {0x85C0, 0x8822, 0x83E0, 0xECE5, 0xF68A, 0x8048, 0x884C, 0x88B5, 0x8D39,
         0x821C, 0x9CA4, 0xAD29, 0xBDAD, 0xD231, 0xE6B5, 0xEB7A},
        {0x8161, 0xEB5A, 0xEAB1, 0xDE29, 0xE4E4, 0xA884, 0x8C00, 0x83E0, 0x802D,
         0x80DD, 0xAA5F, 0x84D1, 0x98C6, 0xB5AD, 0xC631, 0x8421},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D76C8 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D76CC = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76D8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, 13, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76E4 = {
    {0x0100, 0x0000},
    {
        {0x0014, -16, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76F0 = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76FC = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7708 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7714 = {
    {0x0100, 0x0000},
    {
        {0x0014, -11, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7720 = {
    {0x0100, 0x0000},
    {
        {0x0004, -7, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D772C = {
    {0x0100, 0x0000},
    {
        {0x0004, -3, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7738 = {
    {0x0100, 0x0000},
    {
        {0x0004, 4, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7744 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7750 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D775C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7768 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7774 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7780 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D778C = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7798 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77A4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77B0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77BC = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77C8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77D4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77F8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7804 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7810 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D781C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7828 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7834 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7840 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D784C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7858 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7864 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7870 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D787C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7888 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7894 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78DC = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78E8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D78F4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7900 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D790C = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7918 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7924 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7930 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 11, 2},
    },
};

SaturnSpriteFrame1 DAT_060D793C = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7948 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7954 = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7960 = {
    {0x0100, 0x0000},
    {
        {0x0004, 11, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D796C = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7978 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7984 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7990 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D799C = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79A8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 1, 1, 0},
    },
};

SaturnSpriteFrame3 DAT_060D79B4 = {
    {0x0300, 0x0000},
    {
        {0x0100, 1, 15, 3},
        {0x0100, -2, -25, 4},
        {0x0100, 5, -9, 5},
    },
};

SaturnSpriteFrame3 DAT_060D79D0 = {
    {0x0300, 0x0000},
    {
        {0x0100, 1, 14, 6},
        {0x0100, -4, -24, 4},
        {0x0100, 5, -10, 5},
    },
};

SaturnSpriteFrame2 DAT_060D79EC = {
    {0x0200, 0x0000},
    {
        {0x0100, 0, 14, 7},
        {0x0100, 0, -13, 8},
    },
};

SaturnSpriteFrame2 DAT_060D7A00 = {
    {0x0200, 0x0000},
    {
        {0x0100, 0, -12, 8},
        {0x0100, 2, 15, 9},
    },
};

SaturnSpriteFrame2 DAT_060D7A14 = {
    {0x0200, 0x0000},
    {
        {0x0100, 38, -13, 10},
        {0x0100, 20, 3, 11},
    },
};

SaturnSpriteFrame1 DAT_060D7A28 = {
    {0x0100, 0x0000},
    {
        {0x0100, 20, 3, 11},
    },
};

SaturnSpriteFrame1 DAT_060D7A34 = {
    {0x0100, 0x0000},
    {
        {0x0100, 0, -5, 12},
    },
};

SaturnSpriteFrameHeader* DAT_060D7A40[70] = {
    (SaturnSpriteFrameHeader*)&DAT_060D76C8,
    (SaturnSpriteFrameHeader*)&DAT_060D76CC,
    (SaturnSpriteFrameHeader*)&DAT_060D76D8,
    (SaturnSpriteFrameHeader*)&DAT_060D76E4,
    (SaturnSpriteFrameHeader*)&DAT_060D76F0,
    (SaturnSpriteFrameHeader*)&DAT_060D76FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7708,
    (SaturnSpriteFrameHeader*)&DAT_060D7714,
    (SaturnSpriteFrameHeader*)&DAT_060D7720,
    (SaturnSpriteFrameHeader*)&DAT_060D772C,
    (SaturnSpriteFrameHeader*)&DAT_060D7738,
    (SaturnSpriteFrameHeader*)&DAT_060D7744,
    (SaturnSpriteFrameHeader*)&DAT_060D7750,
    (SaturnSpriteFrameHeader*)&DAT_060D775C,
    (SaturnSpriteFrameHeader*)&DAT_060D7768,
    (SaturnSpriteFrameHeader*)&DAT_060D7774,
    (SaturnSpriteFrameHeader*)&DAT_060D7780,
    (SaturnSpriteFrameHeader*)&DAT_060D778C,
    (SaturnSpriteFrameHeader*)&DAT_060D7798,
    (SaturnSpriteFrameHeader*)&DAT_060D77A4,
    (SaturnSpriteFrameHeader*)&DAT_060D77B0,
    (SaturnSpriteFrameHeader*)&DAT_060D77BC,
    (SaturnSpriteFrameHeader*)&DAT_060D77C8,
    (SaturnSpriteFrameHeader*)&DAT_060D77D4,
    (SaturnSpriteFrameHeader*)&DAT_060D77E0,
    (SaturnSpriteFrameHeader*)&DAT_060D77EC,
    (SaturnSpriteFrameHeader*)&DAT_060D77F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7804,
    (SaturnSpriteFrameHeader*)&DAT_060D7810,
    (SaturnSpriteFrameHeader*)&DAT_060D781C,
    (SaturnSpriteFrameHeader*)&DAT_060D7828,
    (SaturnSpriteFrameHeader*)&DAT_060D7834,
    (SaturnSpriteFrameHeader*)&DAT_060D7840,
    (SaturnSpriteFrameHeader*)&DAT_060D784C,
    (SaturnSpriteFrameHeader*)&DAT_060D7858,
    (SaturnSpriteFrameHeader*)&DAT_060D7864,
    (SaturnSpriteFrameHeader*)&DAT_060D7870,
    (SaturnSpriteFrameHeader*)&DAT_060D787C,
    (SaturnSpriteFrameHeader*)&DAT_060D7888,
    (SaturnSpriteFrameHeader*)&DAT_060D7894,
    (SaturnSpriteFrameHeader*)&DAT_060D78A0,
    (SaturnSpriteFrameHeader*)&DAT_060D78AC,
    (SaturnSpriteFrameHeader*)&DAT_060D78B8,
    (SaturnSpriteFrameHeader*)&DAT_060D78C4,
    (SaturnSpriteFrameHeader*)&DAT_060D78D0,
    (SaturnSpriteFrameHeader*)&DAT_060D78DC,
    (SaturnSpriteFrameHeader*)&DAT_060D78E8,
    (SaturnSpriteFrameHeader*)&DAT_060D78F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7900,
    (SaturnSpriteFrameHeader*)&DAT_060D790C,
    (SaturnSpriteFrameHeader*)&DAT_060D7918,
    (SaturnSpriteFrameHeader*)&DAT_060D7924,
    (SaturnSpriteFrameHeader*)&DAT_060D7930,
    (SaturnSpriteFrameHeader*)&DAT_060D793C,
    (SaturnSpriteFrameHeader*)&DAT_060D7948,
    (SaturnSpriteFrameHeader*)&DAT_060D7954,
    (SaturnSpriteFrameHeader*)&DAT_060D7960,
    (SaturnSpriteFrameHeader*)&DAT_060D796C,
    (SaturnSpriteFrameHeader*)&DAT_060D7978,
    (SaturnSpriteFrameHeader*)&DAT_060D7984,
    (SaturnSpriteFrameHeader*)&DAT_060D7990,
    (SaturnSpriteFrameHeader*)&DAT_060D799C,
    (SaturnSpriteFrameHeader*)&DAT_060D79A8,
    (SaturnSpriteFrameHeader*)&DAT_060D79B4,
    (SaturnSpriteFrameHeader*)&DAT_060D79D0,
    (SaturnSpriteFrameHeader*)&DAT_060D79EC,
    (SaturnSpriteFrameHeader*)&DAT_060D7A00,
    (SaturnSpriteFrameHeader*)&DAT_060D7A14,
    (SaturnSpriteFrameHeader*)&DAT_060D7A28,
    (SaturnSpriteFrameHeader*)&DAT_060D7A34,
};

SaturnSpriteResource DAT_060D7B58 = {
    DAT_060D764C, (u16*)&DAT_060D7684, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7B64[1] = {&DAT_060D7B58};
