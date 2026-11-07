// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D64B4();
void func_060D64CC();
void func_060D64E4();
void func_060D64FC();
void func_060D6514();
void func_060D652C();
void func_060D6538();
void func_060D6A7C();
void func_060D6A94();
void func_060D6AAC();
void func_060D6AC4();
void func_060D6ADC();
void func_060D6AF4();
void func_060D6B0C();
void func_060D6B24();
extern SaturnSpriteResource* DAT_060D73F8[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D64B4,
        func_060D64CC,
        func_060D64E4,
        func_060D64FC,
        func_060D6514,
        func_060D652C,
        func_060D6B24,
        func_060D6538,
        func_060D6A7C,
        func_060D6A94,
        func_060D6AAC,
        func_060D6AC4,
        func_060D6ADC,
        func_060D6AF4,
        func_060D6B0C,
    },
    DAT_060D73F8,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D64B4, func_060D64B4);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D64CC, func_060D64CC);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D64E4, func_060D64E4);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D64FC, func_060D64FC);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6514, func_060D6514);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D652C, func_060D652C);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6538, func_060D6538);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6A7C, func_060D6A7C);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6A94, func_060D6A94);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6AAC, func_060D6AAC);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6AC4, func_060D6AC4);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6ADC, func_060D6ADC);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6AF4, func_060D6AF4);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6B0C, func_060D6B0C);
INCLUDE_ASM("asm/saturn/weapon/w_58/f_nonmat", f60D6B24, func_060D6B24);

u32 DAT_060D6B30[143] = {
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
    0x08FF040C, 0x060D6B30, 0x060D6B38, 0x060D6C98, 0x060D6CA4, 0x060D6C8C,
    0x060D6C08, 0x060D6BE8, 0x060D6BB0, 0x060D6B6C, 0x060D6B40, 0x060D6C4C,
    0x060D6C5C, 0x060D6C6C, 0x060D6C7C, 0x00000000, 0x00000000,
};

SaturnSpriteImage DAT_060D6D6C[17] = {
    {8, 15, 0x0000},  {12, 15, 0x0020}, {8, 15, 0x0050},  {12, 10, 0x0070},
    {12, 14, 0x0090}, {8, 15, 0x00BC},  {12, 14, 0x00DC}, {12, 15, 0x0108},
    {12, 15, 0x0138}, {16, 14, 0x0168}, {12, 14, 0x01A0}, {16, 12, 0x01CC},
    {12, 13, 0x01FC}, {12, 14, 0x0224}, {4, 4, 0x0250},   {4, 4, 0x0254},
    {0, 0, 0x0258},
};

struct {
    u16 countAndFlags;
    u16 colors[13][16];
} DAT_060D6DB0 = {
    0x000D,
    {
        {0xE0A8, 0x9063, 0x8297, 0xB33F, 0x800F, 0x8016, 0x843C, 0xA11F, 0x9CC6,
         0xAD29, 0xB98C, 0xC5EF, 0xD252, 0xE2B5, 0xEF18, 0xFB9C},
        {0x8220, 0x9509, 0x8842, 0x98C7, 0xA508, 0xB16B, 0xBDCD, 0xD292, 0xE316,
         0xF379, 0x88C2, 0x98E4, 0xA164, 0x84CA, 0x9191, 0xAA34},
        {0x89E2, 0x8421, 0x8444, 0x8467, 0x84AB, 0x88ED, 0x8D30, 0x9573, 0x9994,
         0x9DB6, 0xA1F7, 0xA619, 0xE2F4, 0xAE7C, 0xCA52, 0xB6DF},
        {0x8902, 0x8421, 0xA86A, 0xB8CD, 0xCD6F, 0xE24F, 0x8D2F, 0x91D6, 0x929B,
         0x9084, 0x9D08, 0xA96C, 0xB9F0, 0xC654, 0xD2D8, 0xE35C},
        {0x9092, 0x8421, 0x98A3, 0xAD2A, 0xCA52, 0xAC61, 0xC503, 0xD9A7, 0xE2AF,
         0x9084, 0x9D08, 0xA96C, 0xB9F0, 0x801F, 0xD2D8, 0xE35C},
        {0x85C0, 0x8822, 0x83E0, 0xECE5, 0xF68A, 0x8048, 0x884C, 0x88B5, 0x8D39,
         0x821C, 0x9CA4, 0xAD29, 0xBDAD, 0xD231, 0xE6B5, 0xEB7A},
        {0x8E0F, 0x9821, 0x8D2F, 0x9594, 0xA219, 0x92FF, 0x9099, 0x98DF, 0xB4E8,
         0x9084, 0xA109, 0xAD6C, 0xBA11, 0xC654, 0xD2D8, 0xE35C},
        {0x8140, 0x8421, 0x9084, 0xA8E5, 0xC146, 0xFF53, 0x9084, 0x9084, 0x9084,
         0x9084, 0x9084, 0x9084, 0x9084, 0x9084, 0x9084, 0x9084},
        {0x89E2, 0x8421, 0x9007, 0x9869, 0x94A7, 0x990B, 0x8D2F, 0x91D6, 0x929B,
         0x9084, 0x9D08, 0xA96C, 0xB9F0, 0xC654, 0xD2D8, 0xE35C},
        {0x8267, 0xB31C, 0x8219, 0x80F6, 0x800E, 0x80A0, 0x9D80, 0xC5A0, 0xCEA0,
         0x8421, 0x806A, 0x8151, 0x8299, 0xB18C, 0xD294, 0x8019},
        {0x81A0, 0xD717, 0xC272, 0xB5EE, 0x9D4B, 0x98C8, 0x8C85, 0x8842, 0x90E2,
         0xA546, 0xDAD6, 0x8CA9, 0x9953, 0x99B6, 0xA659, 0xF39C},
        {0xA1C2, 0x8421, 0x90A5, 0xA12A, 0xB1AE, 0xC233, 0xD2D8, 0x908B, 0x8013,
         0x801F, 0x9D70, 0xA6FE, 0xAF5F, 0x921D, 0x965D, 0x9EBE},
        {0xA1C2, 0x8421, 0x90A5, 0xA12A, 0xB1AE, 0xC233, 0xFFFF, 0x908B, 0x8013,
         0x801F, 0x9D70, 0xA6FE, 0xAF5F, 0x921D, 0x965D, 0x9EBE},
    },
};

SaturnSpriteFrameHeader DAT_060D6F52 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6F56 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F62 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 14, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F6E = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F7A = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F86 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F92 = {
    {0x0100, 0x0000},
    {
        {0x0014, -11, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F9E = {
    {0x0100, 0x0000},
    {
        {0x0014, -9, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FAA = {
    {0x0100, 0x0000},
    {
        {0x0004, -2, -4, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FB6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 3, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FC2 = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6FCE = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FDA = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FE6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FF2 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FFE = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D700A = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7016 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7022 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D702E = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D703A = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7046 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7052 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D705E = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D706A = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7076 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7082 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D708E = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D709A = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70A6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70B2 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70BE = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70CA = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70D6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70E2 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70EE = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70FA = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7106 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7112 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D711E = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D712A = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7136 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7142 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D714E = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D715A = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7166 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7172 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D717E = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D718A = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7196 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D71A2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D71AE = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -6, 2},
    },
};

SaturnSpriteFrame1 DAT_060D71BA = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D71C6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D71D2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D71DE = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71EA = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71F6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7202 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D720E = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D721A = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7226 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7232 = {
    {0x0100, 0x0000},
    {
        {0x0004, 1, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D723E = {
    {0x0100, 0x0000},
    {
        {0x0100, 1, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D724A = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, 9, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7256 = {
    {0x0100, 0x0000},
    {
        {0x0300, 0, 10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7262 = {
    {0x0100, 0x0000},
    {
        {0x0400, -2, 9, 6},
    },
};

SaturnSpriteFrame1 DAT_060D726E = {
    {0x0100, 0x0000},
    {
        {0x0500, -1, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D727A = {
    {0x0100, 0x0000},
    {
        {0x0600, 1, 9, 8},
    },
};

SaturnSpriteFrame1 DAT_060D7286 = {
    {0x0100, 0x0000},
    {
        {0x0700, 2, 10, 9},
    },
};

SaturnSpriteFrame1 DAT_060D7292 = {
    {0x0100, 0x0000},
    {
        {0x0800, 1, 9, 10},
    },
};

SaturnSpriteFrame1 DAT_060D729E = {
    {0x0100, 0x0000},
    {
        {0x0900, 2, 9, 11},
    },
};

SaturnSpriteFrame1 DAT_060D72AA = {
    {0x0100, 0x0000},
    {
        {0x0A00, 2, 9, 12},
    },
};

SaturnSpriteFrame1 DAT_060D72B6 = {
    {0x0100, 0x0000},
    {
        {0x0B00, 0, 9, 13},
    },
};
u16 DAT_060D72B6_tail[1] = {
    0x0000,
};

SaturnSpriteFrameHeader* DAT_060D72C4[74] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6F52,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6FCE,
    (SaturnSpriteFrameHeader*)&DAT_060D6FDA,
    (SaturnSpriteFrameHeader*)&DAT_060D6FE6,
    (SaturnSpriteFrameHeader*)&DAT_060D6FF2,
    (SaturnSpriteFrameHeader*)&DAT_060D6FFE,
    (SaturnSpriteFrameHeader*)&DAT_060D700A,
    (SaturnSpriteFrameHeader*)&DAT_060D7016,
    (SaturnSpriteFrameHeader*)&DAT_060D7022,
    (SaturnSpriteFrameHeader*)&DAT_060D702E,
    (SaturnSpriteFrameHeader*)&DAT_060D703A,
    (SaturnSpriteFrameHeader*)&DAT_060D7046,
    (SaturnSpriteFrameHeader*)&DAT_060D7052,
    (SaturnSpriteFrameHeader*)&DAT_060D705E,
    (SaturnSpriteFrameHeader*)&DAT_060D706A,
    (SaturnSpriteFrameHeader*)&DAT_060D7076,
    (SaturnSpriteFrameHeader*)&DAT_060D7082,
    (SaturnSpriteFrameHeader*)&DAT_060D708E,
    (SaturnSpriteFrameHeader*)&DAT_060D709A,
    (SaturnSpriteFrameHeader*)&DAT_060D70A6,
    (SaturnSpriteFrameHeader*)&DAT_060D70B2,
    (SaturnSpriteFrameHeader*)&DAT_060D70BE,
    (SaturnSpriteFrameHeader*)&DAT_060D70CA,
    (SaturnSpriteFrameHeader*)&DAT_060D70D6,
    (SaturnSpriteFrameHeader*)&DAT_060D70E2,
    (SaturnSpriteFrameHeader*)&DAT_060D70EE,
    (SaturnSpriteFrameHeader*)&DAT_060D70FA,
    (SaturnSpriteFrameHeader*)&DAT_060D7106,
    (SaturnSpriteFrameHeader*)&DAT_060D7112,
    (SaturnSpriteFrameHeader*)&DAT_060D711E,
    (SaturnSpriteFrameHeader*)&DAT_060D712A,
    (SaturnSpriteFrameHeader*)&DAT_060D7136,
    (SaturnSpriteFrameHeader*)&DAT_060D7142,
    (SaturnSpriteFrameHeader*)&DAT_060D714E,
    (SaturnSpriteFrameHeader*)&DAT_060D715A,
    (SaturnSpriteFrameHeader*)&DAT_060D7166,
    (SaturnSpriteFrameHeader*)&DAT_060D7172,
    (SaturnSpriteFrameHeader*)&DAT_060D717E,
    (SaturnSpriteFrameHeader*)&DAT_060D718A,
    (SaturnSpriteFrameHeader*)&DAT_060D7196,
    (SaturnSpriteFrameHeader*)&DAT_060D71A2,
    (SaturnSpriteFrameHeader*)&DAT_060D71AE,
    (SaturnSpriteFrameHeader*)&DAT_060D71BA,
    (SaturnSpriteFrameHeader*)&DAT_060D71C6,
    (SaturnSpriteFrameHeader*)&DAT_060D71D2,
    (SaturnSpriteFrameHeader*)&DAT_060D71DE,
    (SaturnSpriteFrameHeader*)&DAT_060D71EA,
    (SaturnSpriteFrameHeader*)&DAT_060D71F6,
    (SaturnSpriteFrameHeader*)&DAT_060D7202,
    (SaturnSpriteFrameHeader*)&DAT_060D720E,
    (SaturnSpriteFrameHeader*)&DAT_060D721A,
    (SaturnSpriteFrameHeader*)&DAT_060D7226,
    (SaturnSpriteFrameHeader*)&DAT_060D7232,
    (SaturnSpriteFrameHeader*)&DAT_060D723E,
    (SaturnSpriteFrameHeader*)&DAT_060D724A,
    (SaturnSpriteFrameHeader*)&DAT_060D7256,
    (SaturnSpriteFrameHeader*)&DAT_060D7262,
    (SaturnSpriteFrameHeader*)&DAT_060D726E,
    (SaturnSpriteFrameHeader*)&DAT_060D727A,
    (SaturnSpriteFrameHeader*)&DAT_060D7286,
    (SaturnSpriteFrameHeader*)&DAT_060D7292,
    (SaturnSpriteFrameHeader*)&DAT_060D729E,
    (SaturnSpriteFrameHeader*)&DAT_060D72AA,
    (SaturnSpriteFrameHeader*)&DAT_060D72B6,
};

SaturnSpriteResource DAT_060D73EC = {
    DAT_060D6D6C, (u16*)&DAT_060D6DB0, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D73F8[1] = {&DAT_060D73EC};
