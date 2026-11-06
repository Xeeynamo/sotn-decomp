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
void func_060D6528();
void func_060D70C8();
void func_060D7614();
void func_060D762C();
void func_060D7644();
void func_060D765C();
void func_060D7674();
void func_060D768C();
void func_060D76A4();
extern SaturnSpriteResource* DAT_060D7F04[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D64B0,
        func_060D64C8,
        func_060D64E0,
        func_060D64F8,
        func_060D6510,
        func_060D76A4,
        func_060D6528,
        func_060D70C8,
        func_060D7614,
        func_060D762C,
        func_060D7644,
        func_060D765C,
        func_060D7674,
        func_060D768C,
    },
    DAT_060D7F04,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D64B0, func_060D64B0);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D64C8, func_060D64C8);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D64E0, func_060D64E0);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D64F8, func_060D64F8);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D6510, func_060D6510);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D651C, func_060D651C);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D6528, func_060D6528);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D70C8, func_060D70C8);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D7614, func_060D7614);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D762C, func_060D762C);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D7644, func_060D7644);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D765C, func_060D765C);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D7674, func_060D7674);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D768C, func_060D768C);
INCLUDE_ASM("asm/saturn/weapon/w_26/f_nonmat", f60D76A4, func_060D76A4);

u32 DAT_060D76B0[208] = {
    0x2F862F96, 0x2FA62FE6, 0x4F226EF3, 0x6A436853, 0xD923D124, 0x410B6493,
    0x52916182, 0x12135291, 0x51811217, 0x52915182, 0x121B65A2, 0x91362519,
    0x2558890A, 0x91330517, 0x051AD11B, 0x35178B01, 0xD11A351C, 0xD11A410B,
    0x649355A1, 0x91262519, 0x2558890B, 0x91230517, 0x051AD113, 0x35178B01,
    0xD112351C, 0xD40ED113, 0x410B0009, 0x55A29115, 0x25192558, 0x890B9112,
    0x0517051A, 0xD10A3517, 0x8B01D10A, 0x351CD406, 0xD10B410B, 0x00096FE3,
    0x4F266EF6, 0x6AF669F6, 0x000B68F6, 0x0FFF1680, 0x06061DF0, 0x0602F600,
    0x00B3FFFF, 0xFE980000, 0x0602F692, 0x0602F76C, 0x0602F83C, 0x00000000,
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
    0x08FF040C, 0x060D7770, 0x060D7778, 0x060D78D8, 0x060D78E4, 0x060D78CC,
    0x060D7848, 0x060D7828, 0x060D77F0, 0x060D77AC, 0x060D7780, 0x060D788C,
    0x060D789C, 0x060D78AC, 0x060D78BC, 0x00000000, 0x00000000, 0x00000200,
    0x00000400, 0x00000600, 0x00000800, 0x00000A00, 0x00000C00, 0x00000E00,
    0x00001000, 0x00001200, 0x00001400, 0x00001600, 0x00001800, 0x00001A00,
    0x00001C00, 0x00001E00, 0x50007F00, 0x50377F37,
};

SaturnSpriteImage DAT_060D79F0[17] = {
    {12, 14, 0x0000}, {16, 14, 0x002C}, {12, 14, 0x0064}, {16, 15, 0x0090},
    {48, 4, 0x00CC},  {48, 4, 0x00FC},  {48, 4, 0x012C},  {48, 4, 0x015C},
    {48, 4, 0x018C},  {48, 4, 0x01BC},  {48, 4, 0x01EC},  {48, 4, 0x021C},
    {48, 4, 0x024C},  {48, 4, 0x027C},  {48, 4, 0x02AC},  {48, 4, 0x02DC},
    {0, 0, 0x030C},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D7A34 = {
    0x0003,
    {
        {0x89E2, 0x8421, 0x9007, 0x9869, 0x94A7, 0x990B, 0x8D2F, 0x91D6, 0x929B,
         0x9084, 0x9D08, 0xA96C, 0xB9F0, 0xC654, 0xD2D8, 0xE35C},
        {0x8140, 0x8421, 0x8842, 0x8C63, 0x9084, 0x94A5, 0x98C6, 0x9CE7, 0xA108,
         0xA529, 0xA94A, 0xAD6B, 0xB18C, 0xAE45, 0xA5C2, 0x9941},
        {0xB04F, 0x84EA, 0x898E, 0x91F4, 0x9E77, 0xC33C, 0xA8F5, 0x8C63, 0x9CE7,
         0xA94A, 0xB9CE, 0xC631, 0xD6B5, 0xE318, 0xF39C, 0x801F},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D7A98 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7A9C = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AA8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 15, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AB4 = {
    {0x0100, 0x0000},
    {
        {0x0014, -16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AC0 = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7ACC = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AD8 = {
    {0x0100, 0x0000},
    {
        {0x0014, -12, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AE4 = {
    {0x0100, 0x0000},
    {
        {0x0014, -10, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7AF0 = {
    {0x0100, 0x0000},
    {
        {0x0004, -3, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7AFC = {
    {0x0100, 0x0000},
    {
        {0x0004, 2, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7B08 = {
    {0x0100, 0x0000},
    {
        {0x0004, 11, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D7B14 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B20 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B2C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B38 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B44 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B50 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B5C = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B68 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B74 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B80 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B8C = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7B98 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BA4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BB0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BBC = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BC8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BD4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BE0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BEC = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7BF8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C04 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C10 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C1C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C28 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C34 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C40 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C4C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C58 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C64 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C70 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C7C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C88 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7C94 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CA0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CAC = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CB8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CC4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CD0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7CDC = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -1, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7CE8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7CF4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7D00 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7D0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7D18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7D24 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D30 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D3C = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D48 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D54 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D60 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D6C = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D78 = {
    {0x0100, 0x0000},
    {
        {0x0004, 2, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7D84 = {
    {0x0100, 0x0000},
    {
        {0x0100, 4, 25, 3},
    },
};

SaturnSpriteFrame12 DAT_060D7D90 = {
    {0x0C00, 0x0000},
    {
        {0x0200, 16, -27, 4},
        {0x0200, 16, -19, 5},
        {0x0200, 16, -11, 6},
        {0x0200, 16, -3, 7},
        {0x0200, 16, 5, 8},
        {0x0200, 16, 13, 9},
        {0x0200, 16, 21, 10},
        {0x0200, 16, 29, 11},
        {0x0200, 16, 37, 12},
        {0x0200, 16, 45, 13},
        {0x0200, 16, 53, 14},
        {0x0200, 16, 61, 15},
    },
};

SaturnSpriteFrameHeader* DAT_060D7DF4[65] = {
    (SaturnSpriteFrameHeader*)&DAT_060D7A98,
    (SaturnSpriteFrameHeader*)&DAT_060D7A9C,
    (SaturnSpriteFrameHeader*)&DAT_060D7AA8,
    (SaturnSpriteFrameHeader*)&DAT_060D7AB4,
    (SaturnSpriteFrameHeader*)&DAT_060D7AC0,
    (SaturnSpriteFrameHeader*)&DAT_060D7ACC,
    (SaturnSpriteFrameHeader*)&DAT_060D7AD8,
    (SaturnSpriteFrameHeader*)&DAT_060D7AE4,
    (SaturnSpriteFrameHeader*)&DAT_060D7AF0,
    (SaturnSpriteFrameHeader*)&DAT_060D7AFC,
    (SaturnSpriteFrameHeader*)&DAT_060D7B08,
    (SaturnSpriteFrameHeader*)&DAT_060D7B14,
    (SaturnSpriteFrameHeader*)&DAT_060D7B20,
    (SaturnSpriteFrameHeader*)&DAT_060D7B2C,
    (SaturnSpriteFrameHeader*)&DAT_060D7B38,
    (SaturnSpriteFrameHeader*)&DAT_060D7B44,
    (SaturnSpriteFrameHeader*)&DAT_060D7B50,
    (SaturnSpriteFrameHeader*)&DAT_060D7B5C,
    (SaturnSpriteFrameHeader*)&DAT_060D7B68,
    (SaturnSpriteFrameHeader*)&DAT_060D7B74,
    (SaturnSpriteFrameHeader*)&DAT_060D7B80,
    (SaturnSpriteFrameHeader*)&DAT_060D7B8C,
    (SaturnSpriteFrameHeader*)&DAT_060D7B98,
    (SaturnSpriteFrameHeader*)&DAT_060D7BA4,
    (SaturnSpriteFrameHeader*)&DAT_060D7BB0,
    (SaturnSpriteFrameHeader*)&DAT_060D7BBC,
    (SaturnSpriteFrameHeader*)&DAT_060D7BC8,
    (SaturnSpriteFrameHeader*)&DAT_060D7BD4,
    (SaturnSpriteFrameHeader*)&DAT_060D7BE0,
    (SaturnSpriteFrameHeader*)&DAT_060D7BEC,
    (SaturnSpriteFrameHeader*)&DAT_060D7BF8,
    (SaturnSpriteFrameHeader*)&DAT_060D7C04,
    (SaturnSpriteFrameHeader*)&DAT_060D7C10,
    (SaturnSpriteFrameHeader*)&DAT_060D7C1C,
    (SaturnSpriteFrameHeader*)&DAT_060D7C28,
    (SaturnSpriteFrameHeader*)&DAT_060D7C34,
    (SaturnSpriteFrameHeader*)&DAT_060D7C40,
    (SaturnSpriteFrameHeader*)&DAT_060D7C4C,
    (SaturnSpriteFrameHeader*)&DAT_060D7C58,
    (SaturnSpriteFrameHeader*)&DAT_060D7C64,
    (SaturnSpriteFrameHeader*)&DAT_060D7C70,
    (SaturnSpriteFrameHeader*)&DAT_060D7C7C,
    (SaturnSpriteFrameHeader*)&DAT_060D7C88,
    (SaturnSpriteFrameHeader*)&DAT_060D7C94,
    (SaturnSpriteFrameHeader*)&DAT_060D7CA0,
    (SaturnSpriteFrameHeader*)&DAT_060D7CAC,
    (SaturnSpriteFrameHeader*)&DAT_060D7CB8,
    (SaturnSpriteFrameHeader*)&DAT_060D7CC4,
    (SaturnSpriteFrameHeader*)&DAT_060D7CD0,
    (SaturnSpriteFrameHeader*)&DAT_060D7CDC,
    (SaturnSpriteFrameHeader*)&DAT_060D7CE8,
    (SaturnSpriteFrameHeader*)&DAT_060D7CF4,
    (SaturnSpriteFrameHeader*)&DAT_060D7D00,
    (SaturnSpriteFrameHeader*)&DAT_060D7D0C,
    (SaturnSpriteFrameHeader*)&DAT_060D7D18,
    (SaturnSpriteFrameHeader*)&DAT_060D7D24,
    (SaturnSpriteFrameHeader*)&DAT_060D7D30,
    (SaturnSpriteFrameHeader*)&DAT_060D7D3C,
    (SaturnSpriteFrameHeader*)&DAT_060D7D48,
    (SaturnSpriteFrameHeader*)&DAT_060D7D54,
    (SaturnSpriteFrameHeader*)&DAT_060D7D60,
    (SaturnSpriteFrameHeader*)&DAT_060D7D6C,
    (SaturnSpriteFrameHeader*)&DAT_060D7D78,
    (SaturnSpriteFrameHeader*)&DAT_060D7D84,
    (SaturnSpriteFrameHeader*)&DAT_060D7D90,
};

SaturnSpriteResource DAT_060D7EF8 = {
    DAT_060D79F0, (u16*)&DAT_060D7A34, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7F04[1] = {&DAT_060D7EF8};
