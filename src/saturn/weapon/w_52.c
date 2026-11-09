// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D65E0();
void func_060D65F8();
void func_060D6610();
void func_060D6628();
void func_060D6640();
void func_060D664C();
void func_060D7124();
void func_060D7534();
void func_060D754C();
void func_060D7564();
void func_060D757C();
void func_060D7594();
void func_060D75AC();
void func_060D75C4();
void func_060D75DC();
extern SaturnSpriteResource* DAT_060D7F14[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D7124,
        func_060D65E0,
        func_060D65F8,
        func_060D6610,
        func_060D6628,
        func_060D6640,
        func_060D75DC,
        func_060D664C,
        func_060D7534,
        func_060D754C,
        func_060D7564,
        func_060D757C,
        func_060D7594,
        func_060D75AC,
        func_060D75C4,
    },
    DAT_060D7F14,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D65E0, func_060D65E0);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D65F8, func_060D65F8);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D6610, func_060D6610);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D6628, func_060D6628);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D6640, func_060D6640);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D664C, func_060D664C);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D7124, func_060D7124);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D7534, func_060D7534);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D754C, func_060D754C);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D7564, func_060D7564);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D757C, func_060D757C);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D7594, func_060D7594);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D75AC, func_060D75AC);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D75C4, func_060D75C4);
INCLUDE_ASM("asm/saturn/weapon/w_52/f_nonmat", f60D75DC, func_060D75DC);

u32 DAT_060D75F0[166] = {
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
    0x08FF040C, 0x060D75F0, 0x060D75F8, 0x060D7758, 0x060D7764, 0x060D774C,
    0x060D76C8, 0x060D76A8, 0x060D7670, 0x060D762C, 0x060D7600, 0x060D770C,
    0x060D771C, 0x060D772C, 0x060D773C, 0x00000000, 0x00000000, 0x0030174F,
    0x18302F4F, 0x3030474F, 0x48305F4F, 0x6030774F, 0x0050176F, 0x5018672F,
    0x18502F6F, 0x3050476F, 0x48505F6F, 0x6050776F, 0x10000000, 0x10080000,
    0x10100000, 0x10100800, 0x10101000, 0x08101000, 0x00101000, 0x00081000,
    0x00001000, 0x08001000, 0x10001000, 0x10000000,
};

SaturnSpriteImage DAT_060D7888[17] = {
    {8, 15, 0x0000},  {12, 15, 0x0020}, {8, 15, 0x0050},  {12, 10, 0x0070},
    {12, 14, 0x0090}, {8, 15, 0x00BC},  {12, 14, 0x00DC}, {12, 15, 0x0108},
    {12, 15, 0x0138}, {16, 14, 0x0168}, {12, 14, 0x01A0}, {16, 12, 0x01CC},
    {12, 13, 0x01FC}, {12, 14, 0x0224}, {4, 4, 0x0250},   {4, 4, 0x0254},
    {0, 0, 0x0258},
};

struct {
    u16 countAndFlags;
    u16 colors[13][16];
} DAT_060D78CC = {
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

SaturnSpriteFrameHeader DAT_060D7A6E = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7A72 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A7E = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 14, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A8A = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7A96 = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AA2 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AAE = {
    {0x0100, 0x0000},
    {
        {0x0014, -11, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7ABA = {
    {0x0100, 0x0000},
    {
        {0x0014, -9, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AC6 = {
    {0x0100, 0x0000},
    {
        {0x0004, -2, -4, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7AD2 = {
    {0x0100, 0x0000},
    {
        {0x0004, 3, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7ADE = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7AEA = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AF6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B02 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B0E = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B1A = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B26 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B32 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B3E = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B4A = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B56 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B62 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B6E = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B7A = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B86 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B92 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B9E = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BAA = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BB6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BC2 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BCE = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BDA = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BE6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BF2 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BFE = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C0A = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C16 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C22 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C2E = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C3A = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C46 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C52 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C5E = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C6A = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C76 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C82 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C8E = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C9A = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CA6 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CB2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7CBE = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7CCA = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -6, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7CD6 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7CE2 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7CEE = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7CFA = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D06 = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D12 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D1E = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D2A = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D36 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D42 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D4E = {
    {0x0100, 0x0000},
    {
        {0x0004, 1, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D5A = {
    {0x0100, 0x0000},
    {
        {0x0100, 1, 14, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7D66 = {
    {0x0100, 0x0000},
    {
        {0x0200, 1, 9, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7D72 = {
    {0x0100, 0x0000},
    {
        {0x0300, 0, 10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7D7E = {
    {0x0100, 0x0000},
    {
        {0x0400, -2, 9, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7D8A = {
    {0x0100, 0x0000},
    {
        {0x0500, -1, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D7D96 = {
    {0x0100, 0x0000},
    {
        {0x0600, 1, 9, 8},
    },
};

SaturnSpriteFrame1 DAT_060D7DA2 = {
    {0x0100, 0x0000},
    {
        {0x0700, 2, 10, 9},
    },
};

SaturnSpriteFrame1 DAT_060D7DAE = {
    {0x0100, 0x0000},
    {
        {0x0800, 1, 9, 10},
    },
};

SaturnSpriteFrame1 DAT_060D7DBA = {
    {0x0100, 0x0000},
    {
        {0x0900, 2, 9, 11},
    },
};

SaturnSpriteFrame1 DAT_060D7DC6 = {
    {0x0100, 0x0000},
    {
        {0x0A00, 2, 9, 12},
    },
};

SaturnSpriteFrame1 DAT_060D7DD2 = {
    {0x0100, 0x0000},
    {
        {0x0B00, 0, 9, 13},
    },
};
u16 DAT_060D7DD2_tail[1] = {
    0x0000,
};

SaturnSpriteFrameHeader* DAT_060D7DE0[74] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7A6E,
    (SaturnSpriteFrameHeader*)&DAT_060D7A72,
    (SaturnSpriteFrameHeader*)&DAT_060D7A7E,
    (SaturnSpriteFrameHeader*)&DAT_060D7A8A,
    (SaturnSpriteFrameHeader*)&DAT_060D7A96,
    (SaturnSpriteFrameHeader*)&DAT_060D7AA2,
    (SaturnSpriteFrameHeader*)&DAT_060D7AAE,
    (SaturnSpriteFrameHeader*)&DAT_060D7ABA,
    (SaturnSpriteFrameHeader*)&DAT_060D7AC6,
    (SaturnSpriteFrameHeader*)&DAT_060D7AD2,
    (SaturnSpriteFrameHeader*)&DAT_060D7ADE,
    (SaturnSpriteFrameHeader*)&DAT_060D7AEA,
    (SaturnSpriteFrameHeader*)&DAT_060D7AF6,
    (SaturnSpriteFrameHeader*)&DAT_060D7B02,
    (SaturnSpriteFrameHeader*)&DAT_060D7B0E,
    (SaturnSpriteFrameHeader*)&DAT_060D7B1A,
    (SaturnSpriteFrameHeader*)&DAT_060D7B26,
    (SaturnSpriteFrameHeader*)&DAT_060D7B32,
    (SaturnSpriteFrameHeader*)&DAT_060D7B3E,
    (SaturnSpriteFrameHeader*)&DAT_060D7B4A,
    (SaturnSpriteFrameHeader*)&DAT_060D7B56,
    (SaturnSpriteFrameHeader*)&DAT_060D7B62,
    (SaturnSpriteFrameHeader*)&DAT_060D7B6E,
    (SaturnSpriteFrameHeader*)&DAT_060D7B7A,
    (SaturnSpriteFrameHeader*)&DAT_060D7B86,
    (SaturnSpriteFrameHeader*)&DAT_060D7B92,
    (SaturnSpriteFrameHeader*)&DAT_060D7B9E,
    (SaturnSpriteFrameHeader*)&DAT_060D7BAA,
    (SaturnSpriteFrameHeader*)&DAT_060D7BB6,
    (SaturnSpriteFrameHeader*)&DAT_060D7BC2,
    (SaturnSpriteFrameHeader*)&DAT_060D7BCE,
    (SaturnSpriteFrameHeader*)&DAT_060D7BDA,
    (SaturnSpriteFrameHeader*)&DAT_060D7BE6,
    (SaturnSpriteFrameHeader*)&DAT_060D7BF2,
    (SaturnSpriteFrameHeader*)&DAT_060D7BFE,
    (SaturnSpriteFrameHeader*)&DAT_060D7C0A,
    (SaturnSpriteFrameHeader*)&DAT_060D7C16,
    (SaturnSpriteFrameHeader*)&DAT_060D7C22,
    (SaturnSpriteFrameHeader*)&DAT_060D7C2E,
    (SaturnSpriteFrameHeader*)&DAT_060D7C3A,
    (SaturnSpriteFrameHeader*)&DAT_060D7C46,
    (SaturnSpriteFrameHeader*)&DAT_060D7C52,
    (SaturnSpriteFrameHeader*)&DAT_060D7C5E,
    (SaturnSpriteFrameHeader*)&DAT_060D7C6A,
    (SaturnSpriteFrameHeader*)&DAT_060D7C76,
    (SaturnSpriteFrameHeader*)&DAT_060D7C82,
    (SaturnSpriteFrameHeader*)&DAT_060D7C8E,
    (SaturnSpriteFrameHeader*)&DAT_060D7C9A,
    (SaturnSpriteFrameHeader*)&DAT_060D7CA6,
    (SaturnSpriteFrameHeader*)&DAT_060D7CB2,
    (SaturnSpriteFrameHeader*)&DAT_060D7CBE,
    (SaturnSpriteFrameHeader*)&DAT_060D7CCA,
    (SaturnSpriteFrameHeader*)&DAT_060D7CD6,
    (SaturnSpriteFrameHeader*)&DAT_060D7CE2,
    (SaturnSpriteFrameHeader*)&DAT_060D7CEE,
    (SaturnSpriteFrameHeader*)&DAT_060D7CFA,
    (SaturnSpriteFrameHeader*)&DAT_060D7D06,
    (SaturnSpriteFrameHeader*)&DAT_060D7D12,
    (SaturnSpriteFrameHeader*)&DAT_060D7D1E,
    (SaturnSpriteFrameHeader*)&DAT_060D7D2A,
    (SaturnSpriteFrameHeader*)&DAT_060D7D36,
    (SaturnSpriteFrameHeader*)&DAT_060D7D42,
    (SaturnSpriteFrameHeader*)&DAT_060D7D4E,
    (SaturnSpriteFrameHeader*)&DAT_060D7D5A,
    (SaturnSpriteFrameHeader*)&DAT_060D7D66,
    (SaturnSpriteFrameHeader*)&DAT_060D7D72,
    (SaturnSpriteFrameHeader*)&DAT_060D7D7E,
    (SaturnSpriteFrameHeader*)&DAT_060D7D8A,
    (SaturnSpriteFrameHeader*)&DAT_060D7D96,
    (SaturnSpriteFrameHeader*)&DAT_060D7DA2,
    (SaturnSpriteFrameHeader*)&DAT_060D7DAE,
    (SaturnSpriteFrameHeader*)&DAT_060D7DBA,
    (SaturnSpriteFrameHeader*)&DAT_060D7DC6,
    (SaturnSpriteFrameHeader*)&DAT_060D7DD2,
};

SaturnSpriteResource DAT_060D7F08 = {
    DAT_060D7888, (u16*)&DAT_060D78CC, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7F14[1] = {&DAT_060D7F08};
