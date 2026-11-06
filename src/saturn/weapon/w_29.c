// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D612C();
void func_060D6514();
void func_060D6690();
void func_060D66A8();
void func_060D66C0();
void func_060D66D8();
void func_060D66F0();
void func_060D6700();
void func_060D6BC8();
void func_060D74D8();
void func_060D7560();
void func_060D7578();
void func_060D7590();
void func_060D75A8();
void func_060D75C0();
void func_060D75D8();
extern SaturnSpriteResource* DAT_060D7FE4[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D612C,
        func_060D6514,
        func_060D6690,
        func_060D66A8,
        func_060D66C0,
        func_060D66D8,
        func_060D66F0,
        func_060D75D8,
        func_060D6700,
        func_060D6BC8,
        func_060D74D8,
        func_060D7560,
        func_060D7578,
        func_060D7590,
        func_060D75A8,
        func_060D75C0,
    },
    DAT_060D7FE4,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D612C, func_060D612C);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D6514, func_060D6514);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D6690, func_060D6690);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D66A8, func_060D66A8);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D66C0, func_060D66C0);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D66D8, func_060D66D8);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D66F0, func_060D66F0);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D6700, func_060D6700);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D6BC8, func_060D6BC8);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D74D8, func_060D74D8);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D7560, func_060D7560);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D7578, func_060D7578);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D7590, func_060D7590);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D75A8, func_060D75A8);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D75C0, func_060D75C0);
INCLUDE_ASM("asm/saturn/weapon/w_29/f_nonmat", f60D75D8, func_060D75D8);

u32 DAT_060D75F0[161] = {
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
    0x060D771C, 0x060D772C, 0x060D773C, 0x00000001, 0x00020003, 0x00040005,
    0x00060007, 0x00080009, 0x000A000F, 0x000B000F, 0x000C000F, 0x000D000F,
    0x000E000F, 0x00030C3F, 0x00030C40, 0x00030C3F, 0x00030C40, 0x00030C41,
    0x00030C42, 0x00030C41, 0x00030C42, 0x00000000, 0x06070800,
};

SaturnSpriteImage DAT_060D7874[10] = {
    {16, 24, 0x0000}, {20, 24, 0x0060}, {16, 24, 0x00D8}, {24, 19, 0x0138},
    {24, 21, 0x01AC}, {56, 27, 0x022C}, {16, 24, 0x03A8}, {20, 24, 0x0408},
    {16, 24, 0x0480}, {0, 0, 0x04E0},
};

struct {
    u16 countAndFlags;
    u16 colors[22][16];
    u16 padding[1];
} DAT_060D789C = {
    0x0016,
    {
        {0xA1C2, 0x8421, 0x90A5, 0xA12A, 0xB1AE, 0xC233, 0xD2D8, 0x908B, 0x8013,
         0x801F, 0x9D70, 0xA6FE, 0xAF5F, 0x921D, 0x965D, 0x9EBE},
        {0xB400, 0x801F, 0x801A, 0x8015, 0x8011, 0x800F, 0x800D, 0x800B, 0x8009,
         0x80BF, 0x815F, 0x81FF, 0x931F, 0xAFFF, 0xCFFF, 0xFFFF},
        {0x99A0, 0x801A, 0x8018, 0x8016, 0x8015, 0x8013, 0x8012, 0x8010, 0x800F,
         0x8016, 0x811F, 0x857F, 0x89DF, 0x8A3F, 0x8E9F, 0x931F},
        {0xB04B, 0x846A, 0x80F1, 0x817A, 0x923F, 0xAB3F, 0x8C63, 0xB9CE, 0xD6B5,
         0xB04B, 0xB04B, 0xB04B, 0xB04B, 0xB297, 0xCFF3, 0x83C0},
        {0x0000, 0x0421, 0x10A5, 0x212A, 0x31AE, 0x4233, 0x52D8, 0x108B, 0x0013,
         0x001F, 0x1D70, 0x121D, 0x165D, 0x1EBE, 0x26FE, 0x2F5F},
        {0x0000, 0x0421, 0x10A5, 0x212A, 0x31AE, 0x4233, 0x52D8, 0x108B, 0x0013,
         0x001F, 0x1D70, 0x2F5F, 0x121D, 0x165D, 0x1EBE, 0x26FE},
        {0x0000, 0x0421, 0x10A5, 0x212A, 0x31AE, 0x4233, 0x52D8, 0x108B, 0x0013,
         0x001F, 0x1D70, 0x26FE, 0x2F5F, 0x121D, 0x165D, 0x1EBE},
        {0x0000, 0x0421, 0x10A5, 0x212A, 0x31AE, 0x4233, 0x52D8, 0x108B, 0x0013,
         0x001F, 0x1D70, 0x1EBE, 0x26FE, 0x2F5F, 0x121D, 0x165D},
        {0x0000, 0x0421, 0x10A5, 0x212A, 0x31AE, 0x4233, 0x52D8, 0x108B, 0x0013,
         0x001F, 0x1D70, 0x165D, 0x1EBE, 0x26FE, 0x2F5F, 0x121D},
        {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
         0x0000, 0x0000, 0x0000, 0x165D, 0x0000, 0x0000, 0x2F5F},
        {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
         0x0000, 0x0000, 0x2F5F, 0x0000, 0x165D, 0x0000, 0x0000},
        {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
         0x0000, 0x0000, 0x0000, 0x2F5F, 0x0000, 0x165D, 0x0000},
        {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
         0x0000, 0x0000, 0x0000, 0x0000, 0x2F5F, 0x0000, 0x165D},
        {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
         0x0000, 0x0000, 0x165D, 0x0000, 0x0000, 0x2F5F, 0x0000},
        {0x0000, 0x046A, 0x00F1, 0x017A, 0x123F, 0x2B3F, 0x0C63, 0x39CE, 0x56B5,
         0x0000, 0x0000, 0x0000, 0x0000, 0x3297, 0x4FF3, 0x03C0},
        {0x0000, 0x046A, 0x00F1, 0x017A, 0x123F, 0x2B3F, 0x0C63, 0x39CE, 0x56B5,
         0x0000, 0x0000, 0x0000, 0x2E55, 0x0000, 0x03E0, 0x02C0},
        {0x0000, 0x046A, 0x00F1, 0x017A, 0x123F, 0x2B3F, 0x0C63, 0x39CE, 0x56B5,
         0x0000, 0x0000, 0x2E14, 0x0000, 0x0000, 0x03C0, 0x0240},
        {0x0000, 0x046A, 0x00F1, 0x017A, 0x123F, 0x2B3F, 0x0C63, 0x39CE, 0x56B5,
         0x0000, 0x2E14, 0x0000, 0x0000, 0x0000, 0x0280, 0x0180},
        {0x0000, 0x046A, 0x00F1, 0x017A, 0x123F, 0x2B3F, 0x0C63, 0x39CE, 0x56B5,
         0x2E55, 0x0000, 0x0000, 0x0000, 0x0000, 0x0180, 0x0180},
        {0x0000, 0x0017, 0x011B, 0x023F, 0x37FF, 0x67FF, 0x0C63, 0x39CE, 0x56B5,
         0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03C0, 0x0240},
        {0x0000, 0x001F, 0x001A, 0x0015, 0x0011, 0x000F, 0x000D, 0x000B, 0x0009,
         0x00BF, 0x015F, 0x01FF, 0x131F, 0x2FFF, 0x4FFF, 0x7FFF},
        {0x0000, 0x001A, 0x0018, 0x0016, 0x0015, 0x0013, 0x0012, 0x0010, 0x000F,
         0x0016, 0x011F, 0x057F, 0x09DF, 0x0A3F, 0x0E9F, 0x131F},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D7B60 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7B64 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B70 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, 13, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B7C = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B88 = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B94 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BA0 = {
    {0x0100, 0x0000},
    {
        {0x0014, -12, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BAC = {
    {0x0100, 0x0000},
    {
        {0x0014, -10, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BB8 = {
    {0x0100, 0x0000},
    {
        {0x0004, -1, -4, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7BC4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 3, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7BD0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 11, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7BDC = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BE8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BF4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C00 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C0C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C18 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C24 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C30 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C3C = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C48 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C54 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C60 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C6C = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C78 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C84 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C90 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C9C = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CA8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CB4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CC0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CCC = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CD8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CE4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CF0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CFC = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D08 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D14 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D20 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D2C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D38 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D44 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D50 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D5C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D68 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D74 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D80 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D8C = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D98 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7DA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7DB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7DBC = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7DC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 11, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7DD4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7DE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7DEC = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7DF8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7E04 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7E10 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7E1C = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7E28 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7E34 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7E40 = {
    {0x0100, 0x0000},
    {
        {0x0004, 2, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7E4C = {
    {0x0100, 0x0000},
    {
        {0x0100, 0, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7E58 = {
    {0x0100, 0x0000},
    {
        {0x0200, 0, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7E64 = {
    {0x0100, 0x0000},
    {
        {0x0110, -1, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7E70 = {
    {0x0100, 0x0000},
    {
        {0x0210, -1, 1, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7E7C = {
    {0x0100, 0x0000},
    {
        {0x0300, 1, 4, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7E88 = {
    {0x0100, 0x0000},
    {
        {0x0300, 6, -2, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7E94 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -10, 6},
    },
};

SaturnSpriteFrame1 DAT_060D7EA0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D7EAC = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -10, 8},
    },
};

SaturnSpriteFrameHeader* DAT_060D7EB8[72] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7B60,
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
    (SaturnSpriteFrameHeader*)&DAT_060D7C84,
    (SaturnSpriteFrameHeader*)&DAT_060D7C90,
    (SaturnSpriteFrameHeader*)&DAT_060D7C9C,
    (SaturnSpriteFrameHeader*)&DAT_060D7CA8,
    (SaturnSpriteFrameHeader*)&DAT_060D7CB4,
    (SaturnSpriteFrameHeader*)&DAT_060D7CC0,
    (SaturnSpriteFrameHeader*)&DAT_060D7CCC,
    (SaturnSpriteFrameHeader*)&DAT_060D7CD8,
    (SaturnSpriteFrameHeader*)&DAT_060D7CE4,
    (SaturnSpriteFrameHeader*)&DAT_060D7CF0,
    (SaturnSpriteFrameHeader*)&DAT_060D7CFC,
    (SaturnSpriteFrameHeader*)&DAT_060D7D08,
    (SaturnSpriteFrameHeader*)&DAT_060D7D14,
    (SaturnSpriteFrameHeader*)&DAT_060D7D20,
    (SaturnSpriteFrameHeader*)&DAT_060D7D2C,
    (SaturnSpriteFrameHeader*)&DAT_060D7D38,
    (SaturnSpriteFrameHeader*)&DAT_060D7D44,
    (SaturnSpriteFrameHeader*)&DAT_060D7D50,
    (SaturnSpriteFrameHeader*)&DAT_060D7D5C,
    (SaturnSpriteFrameHeader*)&DAT_060D7D68,
    (SaturnSpriteFrameHeader*)&DAT_060D7D74,
    (SaturnSpriteFrameHeader*)&DAT_060D7D80,
    (SaturnSpriteFrameHeader*)&DAT_060D7D8C,
    (SaturnSpriteFrameHeader*)&DAT_060D7D98,
    (SaturnSpriteFrameHeader*)&DAT_060D7DA4,
    (SaturnSpriteFrameHeader*)&DAT_060D7DB0,
    (SaturnSpriteFrameHeader*)&DAT_060D7DBC,
    (SaturnSpriteFrameHeader*)&DAT_060D7DC8,
    (SaturnSpriteFrameHeader*)&DAT_060D7DD4,
    (SaturnSpriteFrameHeader*)&DAT_060D7DE0,
    (SaturnSpriteFrameHeader*)&DAT_060D7DEC,
    (SaturnSpriteFrameHeader*)&DAT_060D7DF8,
    (SaturnSpriteFrameHeader*)&DAT_060D7E04,
    (SaturnSpriteFrameHeader*)&DAT_060D7E10,
    (SaturnSpriteFrameHeader*)&DAT_060D7E1C,
    (SaturnSpriteFrameHeader*)&DAT_060D7E28,
    (SaturnSpriteFrameHeader*)&DAT_060D7E34,
    (SaturnSpriteFrameHeader*)&DAT_060D7E40,
    (SaturnSpriteFrameHeader*)&DAT_060D7E4C,
    (SaturnSpriteFrameHeader*)&DAT_060D7E58,
    (SaturnSpriteFrameHeader*)&DAT_060D7E64,
    (SaturnSpriteFrameHeader*)&DAT_060D7E70,
    (SaturnSpriteFrameHeader*)&DAT_060D7E7C,
    (SaturnSpriteFrameHeader*)&DAT_060D7E88,
    (SaturnSpriteFrameHeader*)&DAT_060D7E94,
    (SaturnSpriteFrameHeader*)&DAT_060D7EA0,
    (SaturnSpriteFrameHeader*)&DAT_060D7EAC,
};

SaturnSpriteResource DAT_060D7FD8 = {
    DAT_060D7874, (u16*)&DAT_060D789C, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7FE4[1] = {&DAT_060D7FD8};
