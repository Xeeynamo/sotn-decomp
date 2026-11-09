// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6584();
void func_060D659C();
void func_060D65B4();
void func_060D65CC();
void func_060D65E4();
void func_060D65FC();
void func_060D6608();
void func_060D6E00();
void func_060D72F0();
void func_060D7308();
void func_060D7320();
void func_060D7338();
void func_060D7350();
void func_060D7368();
void func_060D7380();
extern SaturnSpriteResource* DAT_060D7DA0[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6584,
        func_060D659C,
        func_060D65B4,
        func_060D65CC,
        func_060D65E4,
        func_060D65FC,
        func_060D7380,
        func_060D6608,
        func_060D6E00,
        func_060D72F0,
        func_060D7308,
        func_060D7320,
        func_060D7338,
        func_060D7350,
        func_060D7368,
    },
    DAT_060D7DA0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x000000F8, 0x00000000, 0x00000000, 0x00000000,
    0x00000020, 0x2E746578, 0x74000000};

INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D6584, func_060D6584);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D659C, func_060D659C);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D65B4, func_060D65B4);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D65CC, func_060D65CC);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D65E4, func_060D65E4);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D65FC, func_060D65FC);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D6608, func_060D6608);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D6E00, func_060D6E00);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D72F0, func_060D72F0);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D7308, func_060D7308);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D7320, func_060D7320);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D7338, func_060D7338);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D7350, func_060D7350);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D7368, func_060D7368);
INCLUDE_ASM("asm/saturn/weapon/w_24/f_nonmat", f60D7380, func_060D7380);

u32 DAT_060D7390[201] = {
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
    0x08FF040C, 0x060D7390, 0x060D7398, 0x060D74F8, 0x060D7504, 0x060D74EC,
    0x060D7468, 0x060D7448, 0x060D7410, 0x060D73CC, 0x060D73A0, 0x060D74AC,
    0x060D74BC, 0x060D74CC, 0x060D74DC, 0x00200000, 0x00010001, 0x00200000,
    0x00010001, 0x00080000, 0x00010001, 0x00080000, 0xFFFF0000, 0x00020002,
    0x00020003, 0x00020004, 0x00020005, 0x00020006, 0x00020007, 0x00010001,
    0x00020008, 0x00020009, 0x0002000A, 0x0002000B, 0x0002000C, 0x0002000D,
    0x0002000E, 0xFFFF0000, 0x0002000E, 0x0002000D, 0x0002000C, 0x0002000B,
    0x0002000A, 0x00020009, 0x00020009, 0x00010001, 0x00020007, 0x00020006,
    0x00020005, 0x00020004, 0x00020003, 0x00020002, 0xFFFF0000, 0x00300000,
    0xFFFF0000, 0x060D75C4, 0x060D75E4, 0x060D7620, 0x060D765C, 0x00000000,
    0x00000200, 0x00000400, 0x00000600, 0x00000800, 0x00000A00, 0x00000C00,
    0x00000E00, 0x00001000, 0x00001200, 0x00001400, 0x00001600, 0x00001800,
    0x00001A00, 0x00001C00, 0x00001E00,
};

SaturnSpriteImage DAT_060D76B4[9] = {
    {16, 14, 0x0000}, {16, 14, 0x0038}, {16, 14, 0x0070},
    {4, 3, 0x00A8},   {8, 7, 0x00AC},   {20, 20, 0x00BC},
    {28, 20, 0x0120}, {64, 40, 0x01AC}, {0, 0, 0x042C},
};

struct {
    u16 countAndFlags;
    u16 colors[20][16];
    u16 padding[1];
} DAT_060D76D8 = {
    0x0014,
    {
        {0x8140, 0x8421, 0x9084, 0xA8E5, 0xC146, 0xFF53, 0x9084, 0x9084, 0x9084,
         0x9084, 0x9084, 0x9084, 0x9084, 0x9084, 0x9084, 0x9084},
        {0x8000, 0x9400, 0xAC20, 0xC440, 0xCC60, 0x9800, 0xA820, 0x9400, 0xA820,
         0xBC40, 0xD460, 0xE880, 0xFCA0, 0xFD60, 0xFF20, 0xFF98},
        {0x80A0, 0x8000, 0x8380, 0x81E0, 0xA045, 0xE8E0, 0xD448, 0xBC6B, 0xA48E,
         0x8CD1, 0x9516, 0x9598, 0xA1DB, 0xB29C, 0xC71B, 0xEF5B},
        {0x0000, 0x8421, 0x9084, 0xA8E5, 0xC146, 0xFF53, 0x9084, 0x9084, 0x9084,
         0x9084, 0x9084, 0x9084, 0x9084, 0x9084, 0x9084, 0x9084},
        {0x0000, 0x8421, 0xFC00, 0xFD07, 0xFDA6, 0xFF53, 0xFC00, 0xFC00, 0xFC00,
         0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00, 0xFC00},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x4842, 0x1084, 0x1084,
         0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x7C00, 0x1084, 0x1084,
         0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x7C00, 0x1084,
         0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x1084, 0x7C00,
         0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x1084, 0x1084,
         0x7C00, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084},
        {0x0000, 0x0421, 0x0842, 0x28E5, 0x4146, 0x7F53, 0x0842, 0x0842, 0x0842,
         0x0842, 0x7C00, 0x0842, 0x0842, 0x0842, 0x0842, 0x0842},
        {0x0000, 0x0421, 0x0842, 0x28E5, 0x4146, 0x7F53, 0x0842, 0x0842, 0x0842,
         0x0842, 0x0842, 0x7C00, 0x0842, 0x0842, 0x0842, 0x0842},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x1084, 0x1084,
         0x1084, 0x1084, 0x1084, 0x7C00, 0x1084, 0x1084, 0x1084},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x1084, 0x1084,
         0x1084, 0x1084, 0x1084, 0x1084, 0x7C00, 0x1084, 0x1084},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x1084, 0x1084,
         0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x7C00, 0x1084},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x1084, 0x1084,
         0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x7C00},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x1084, 0x1084,
         0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x5821},
        {0x0000, 0x0421, 0x1084, 0x28E5, 0x4146, 0x7F53, 0x1084, 0x1084, 0x1084,
         0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x3442},
        {0x0000, 0x8000, 0x0380, 0x01E0, 0x2045, 0x68E0, 0x5448, 0x3C6B, 0x248E,
         0x0CD1, 0x1516, 0x1598, 0x21DB, 0x329C, 0x471B, 0x6F5B},
        {0x0000, 0x348C, 0x410C, 0x5151, 0x4D9A, 0x2485, 0x2CA7, 0x30E7, 0x3927,
         0x4168, 0x41AA, 0x49EE, 0x5251, 0x5AB4, 0x6318, 0x77BC},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D795C = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7960 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D796C = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, 14, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7978 = {
    {0x0100, 0x0000},
    {
        {0x0014, -18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7984 = {
    {0x0100, 0x0000},
    {
        {0x0014, -17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7990 = {
    {0x0100, 0x0000},
    {
        {0x0014, -16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D799C = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79A8 = {
    {0x0100, 0x0000},
    {
        {0x0014, -12, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79B4 = {
    {0x0100, 0x0000},
    {
        {0x0004, -2, -4, 1},
    },
};

SaturnSpriteFrame1 DAT_060D79C0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 3, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D79CC = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D79D8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79E4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79F0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D79FC = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A08 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A14 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A20 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A2C = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A38 = {
    {0x0100, 0x0000},
    {
        {0x0004, 28, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A44 = {
    {0x0100, 0x0000},
    {
        {0x0004, 29, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A50 = {
    {0x0100, 0x0000},
    {
        {0x0004, 29, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A5C = {
    {0x0100, 0x0000},
    {
        {0x0004, 29, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A68 = {
    {0x0100, 0x0000},
    {
        {0x0004, 28, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A74 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A80 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A8C = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A98 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AA4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AB0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7ABC = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AC8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AD4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AE0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AEC = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AF8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B04 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B10 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B1C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B28 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B34 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B40 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B4C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B58 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B64 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B70 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B7C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B88 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B94 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BA0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7BAC = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7BB8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -6, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7BC4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7BD0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7BDC = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, 14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7BE8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BF4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C00 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C0C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C18 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C24 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C30 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C3C = {
    {0x0100, 0x0000},
    {
        {0x0004, 4, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C48 = {
    {0x0100, 0x0000},
    {
        {0x0100, 0, 23, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7C54 = {
    {0x0100, 0x0000},
    {
        {0x0100, -1, 18, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7C60 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 5, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7C6C = {
    {0x0100, 0x0000},
    {
        {0x0100, -6, 5, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7C78 = {
    {0x0100, 0x0000},
    {
        {0x0200, 24, -6, 7},
    },
};

SaturnSpriteFrameHeader* DAT_060D7C84[68] = {
    (SaturnSpriteFrameHeader*)&DAT_060D795C,
    (SaturnSpriteFrameHeader*)&DAT_060D7960,
    (SaturnSpriteFrameHeader*)&DAT_060D796C,
    (SaturnSpriteFrameHeader*)&DAT_060D7978,
    (SaturnSpriteFrameHeader*)&DAT_060D7984,
    (SaturnSpriteFrameHeader*)&DAT_060D7990,
    (SaturnSpriteFrameHeader*)&DAT_060D799C,
    (SaturnSpriteFrameHeader*)&DAT_060D79A8,
    (SaturnSpriteFrameHeader*)&DAT_060D79B4,
    (SaturnSpriteFrameHeader*)&DAT_060D79C0,
    (SaturnSpriteFrameHeader*)&DAT_060D79CC,
    (SaturnSpriteFrameHeader*)&DAT_060D79D8,
    (SaturnSpriteFrameHeader*)&DAT_060D79E4,
    (SaturnSpriteFrameHeader*)&DAT_060D79F0,
    (SaturnSpriteFrameHeader*)&DAT_060D79FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7A08,
    (SaturnSpriteFrameHeader*)&DAT_060D7A14,
    (SaturnSpriteFrameHeader*)&DAT_060D7A20,
    (SaturnSpriteFrameHeader*)&DAT_060D7A2C,
    (SaturnSpriteFrameHeader*)&DAT_060D7A38,
    (SaturnSpriteFrameHeader*)&DAT_060D7A44,
    (SaturnSpriteFrameHeader*)&DAT_060D7A50,
    (SaturnSpriteFrameHeader*)&DAT_060D7A5C,
    (SaturnSpriteFrameHeader*)&DAT_060D7A68,
    (SaturnSpriteFrameHeader*)&DAT_060D7A74,
    (SaturnSpriteFrameHeader*)&DAT_060D7A80,
    (SaturnSpriteFrameHeader*)&DAT_060D7A8C,
    (SaturnSpriteFrameHeader*)&DAT_060D7A98,
    (SaturnSpriteFrameHeader*)&DAT_060D7AA4,
    (SaturnSpriteFrameHeader*)&DAT_060D7AB0,
    (SaturnSpriteFrameHeader*)&DAT_060D7ABC,
    (SaturnSpriteFrameHeader*)&DAT_060D7AC8,
    (SaturnSpriteFrameHeader*)&DAT_060D7AD4,
    (SaturnSpriteFrameHeader*)&DAT_060D7AE0,
    (SaturnSpriteFrameHeader*)&DAT_060D7AEC,
    (SaturnSpriteFrameHeader*)&DAT_060D7AF8,
    (SaturnSpriteFrameHeader*)&DAT_060D7B04,
    (SaturnSpriteFrameHeader*)&DAT_060D7B10,
    (SaturnSpriteFrameHeader*)&DAT_060D7B1C,
    (SaturnSpriteFrameHeader*)&DAT_060D7B28,
    (SaturnSpriteFrameHeader*)&DAT_060D7B34,
    (SaturnSpriteFrameHeader*)&DAT_060D7B40,
    (SaturnSpriteFrameHeader*)&DAT_060D7B4C,
    (SaturnSpriteFrameHeader*)&DAT_060D7B58,
    (SaturnSpriteFrameHeader*)&DAT_060D7B64,
    (SaturnSpriteFrameHeader*)&DAT_060D7B70,
    (SaturnSpriteFrameHeader*)&DAT_060D7B7C,
    (SaturnSpriteFrameHeader*)&DAT_060D7B88,
    (SaturnSpriteFrameHeader*)&DAT_060D7B94,
    (SaturnSpriteFrameHeader*)&DAT_060D7BA0,
    (SaturnSpriteFrameHeader*)&DAT_060D7BAC,
    (SaturnSpriteFrameHeader*)&DAT_060D7BB8,
    (SaturnSpriteFrameHeader*)&DAT_060D7BC4,
    (SaturnSpriteFrameHeader*)&DAT_060D7BD0,
    (SaturnSpriteFrameHeader*)&DAT_060D7BDC,
    (SaturnSpriteFrameHeader*)&DAT_060D7BE8,
    (SaturnSpriteFrameHeader*)&DAT_060D7BF4,
    (SaturnSpriteFrameHeader*)&DAT_060D7C00,
    (SaturnSpriteFrameHeader*)&DAT_060D7C0C,
    (SaturnSpriteFrameHeader*)&DAT_060D7C18,
    (SaturnSpriteFrameHeader*)&DAT_060D7C24,
    (SaturnSpriteFrameHeader*)&DAT_060D7C30,
    (SaturnSpriteFrameHeader*)&DAT_060D7C3C,
    (SaturnSpriteFrameHeader*)&DAT_060D7C48,
    (SaturnSpriteFrameHeader*)&DAT_060D7C54,
    (SaturnSpriteFrameHeader*)&DAT_060D7C60,
    (SaturnSpriteFrameHeader*)&DAT_060D7C6C,
    (SaturnSpriteFrameHeader*)&DAT_060D7C78,
};

SaturnSpriteResource DAT_060D7D94 = {
    DAT_060D76B4, (u16*)&DAT_060D76D8, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7DA0[1] = {&DAT_060D7D94};
