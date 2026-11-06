// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D64E4();
void func_060D65DC();
void func_060D65F4();
void func_060D660C();
void func_060D6624();
void func_060D663C();
void func_060D6648();
void func_060D6CD4();
void func_060D7180();
void func_060D7198();
void func_060D71B0();
void func_060D71C8();
void func_060D71E0();
void func_060D71F8();
void func_060D7210();
extern SaturnSpriteResource* DAT_060D79B4[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D64E4,
        func_060D65DC,
        func_060D65F4,
        func_060D660C,
        func_060D6624,
        func_060D663C,
        func_060D7210,
        func_060D6648,
        func_060D6CD4,
        func_060D7180,
        func_060D7198,
        func_060D71B0,
        func_060D71C8,
        func_060D71E0,
        func_060D71F8,
    },
    DAT_060D79B4,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D64E4, func_060D64E4);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D65DC, func_060D65DC);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D65F4, func_060D65F4);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D660C, func_060D660C);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D6624, func_060D6624);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D663C, func_060D663C);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D6648, func_060D6648);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D6CD4, func_060D6CD4);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D7180, func_060D7180);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D7198, func_060D7198);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D71B0, func_060D71B0);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D71C8, func_060D71C8);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D71E0, func_060D71E0);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D71F8, func_060D71F8);
INCLUDE_ASM("asm/saturn/weapon/w_10/f_nonmat", f60D7210, func_060D7210);

u32 DAT_060D7220[156] = {
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
    0x08FF040C, 0x060D7220, 0x060D7228, 0x060D7388, 0x060D7394, 0x060D737C,
    0x060D72F8, 0x060D72D8, 0x060D72A0, 0x060D725C, 0x060D7230, 0x060D733C,
    0x060D734C, 0x060D735C, 0x060D736C, 0x00020C3F, 0x00020C40, 0x00020C41,
    0x00020C42, 0x00020C43, 0x00020C44, 0xFFFF0000, 0x00000200, 0x04000600,
    0x08000A00, 0x0C000E00, 0x10001200, 0x14001600, 0x18001A00, 0x1C001E00,
};

SaturnSpriteImage DAT_060D7490[13] = {
    {12, 14, 0x0000}, {16, 14, 0x002C}, {12, 14, 0x0064}, {16, 8, 0x0090},
    {16, 13, 0x00B0}, {16, 17, 0x00E4}, {20, 15, 0x0128}, {16, 11, 0x0174},
    {20, 17, 0x01A0}, {60, 55, 0x01F8}, {16, 51, 0x0534}, {16, 28, 0x0600},
    {0, 0, 0x0670},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D74C4 = {
    0x0003,
    {
        {0x9092, 0x8421, 0x98A3, 0xAD2A, 0xCA52, 0xAC61, 0xC503, 0xD9A7, 0xE2AF,
         0x9084, 0x9D08, 0xA96C, 0xB9F0, 0x801F, 0xD2D8, 0xE35C},
        {0x8220, 0x8CA8, 0x992C, 0xA1D2, 0xB679, 0xA4AF, 0xB0F7, 0xADDA, 0xBA7C,
         0x9C41, 0xACE6, 0xBD8B, 0xC631, 0xD6B5, 0xEB5A, 0xFFDE},
        {0xA62A, 0xA0E6, 0x9D2D, 0xB5D2, 0xD677, 0xAC68, 0xACED, 0xAD72, 0xB1F8,
         0x9C41, 0xC125, 0xD5C9, 0xDE6E, 0xEEF5, 0xFFDB, 0xE33A},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D7528 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D752C = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7538 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, 13, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7544 = {
    {0x0100, 0x0000},
    {
        {0x0014, -16, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7550 = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D755C = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7568 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7574 = {
    {0x0100, 0x0000},
    {
        {0x0014, -11, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7580 = {
    {0x0100, 0x0000},
    {
        {0x0004, -2, -4, 1},
    },
};

SaturnSpriteFrame1 DAT_060D758C = {
    {0x0100, 0x0000},
    {
        {0x0004, 3, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7598 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D75A4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75B0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75BC = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75C8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75D4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75F8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7604 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7610 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D761C = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7628 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7634 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7640 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D764C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7658 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7664 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7670 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D767C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7688 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7694 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76DC = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76E8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D76F4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7700 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D770C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7718 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7724 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7730 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D773C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7748 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7754 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7760 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D776C = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7778 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7784 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7790 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D779C = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D77A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D77B4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77C0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 11, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77CC = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77D8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77E4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77F0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D77FC = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7808 = {
    {0x0100, 0x0000},
    {
        {0x0004, 2, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7814 = {
    {0x0100, 0x0000},
    {
        {0x0100, 7, 7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7820 = {
    {0x0100, 0x0000},
    {
        {0x0100, 7, 2, 4},
    },
};

SaturnSpriteFrame1 DAT_060D782C = {
    {0x0100, 0x0000},
    {
        {0x0100, 6, -2, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7838 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 1, 6},
    },
};

SaturnSpriteFrame2 DAT_060D7844 = {
    {0x0200, 0x0000},
    {
        {0x0100, 16, -11, 7},
        {0x0130, -12, 9, 7},
    },
};

SaturnSpriteFrame2 DAT_060D7858 = {
    {0x0200, 0x0000},
    {
        {0x0100, 24, -20, 8},
        {0x0130, -20, 16, 8},
    },
};

SaturnSpriteFrame1 DAT_060D786C = {
    {0x0100, 0x0000},
    {
        {0x0200, -8, -30, 9},
    },
};

SaturnSpriteFrame2 DAT_060D7878 = {
    {0x0200, 0x0000},
    {
        {0x0100, 2, 22, 10},
        {0x0100, 2, 101, 11},
    },
};

SaturnSpriteFrameHeader* DAT_060D788C[71] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7528,
    (SaturnSpriteFrameHeader*)&DAT_060D752C,
    (SaturnSpriteFrameHeader*)&DAT_060D7538,
    (SaturnSpriteFrameHeader*)&DAT_060D7544,
    (SaturnSpriteFrameHeader*)&DAT_060D7550,
    (SaturnSpriteFrameHeader*)&DAT_060D755C,
    (SaturnSpriteFrameHeader*)&DAT_060D7568,
    (SaturnSpriteFrameHeader*)&DAT_060D7574,
    (SaturnSpriteFrameHeader*)&DAT_060D7580,
    (SaturnSpriteFrameHeader*)&DAT_060D758C,
    (SaturnSpriteFrameHeader*)&DAT_060D7598,
    (SaturnSpriteFrameHeader*)&DAT_060D75A4,
    (SaturnSpriteFrameHeader*)&DAT_060D75B0,
    (SaturnSpriteFrameHeader*)&DAT_060D75BC,
    (SaturnSpriteFrameHeader*)&DAT_060D75C8,
    (SaturnSpriteFrameHeader*)&DAT_060D75D4,
    (SaturnSpriteFrameHeader*)&DAT_060D75E0,
    (SaturnSpriteFrameHeader*)&DAT_060D75EC,
    (SaturnSpriteFrameHeader*)&DAT_060D75F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7604,
    (SaturnSpriteFrameHeader*)&DAT_060D7610,
    (SaturnSpriteFrameHeader*)&DAT_060D761C,
    (SaturnSpriteFrameHeader*)&DAT_060D7628,
    (SaturnSpriteFrameHeader*)&DAT_060D7634,
    (SaturnSpriteFrameHeader*)&DAT_060D7640,
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
    (SaturnSpriteFrameHeader*)&DAT_060D7858,
    (SaturnSpriteFrameHeader*)&DAT_060D786C,
    (SaturnSpriteFrameHeader*)&DAT_060D7878,
};

SaturnSpriteResource DAT_060D79A8 = {
    DAT_060D7490, (u16*)&DAT_060D74C4, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D79B4[1] = {&DAT_060D79A8};
