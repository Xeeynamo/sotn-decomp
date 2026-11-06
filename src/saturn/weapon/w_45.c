// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D61E4();
void func_060D6390();
void func_060D64D0();
void func_060D6650();
void func_060D683C();
void func_060D6854();
void func_060D6860();
void func_060D6894();
void func_060D6A38();
void func_060D6B18();
void func_060D6B30();
void func_060D6B48();
void func_060D6B60();
void func_060D6B78();
void func_060D6B90();
extern SaturnSpriteResource* DAT_060D711C[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D61E4,
        func_060D6390,
        func_060D64D0,
        func_060D6650,
        func_060D683C,
        func_060D6854,
        func_060D6B90,
        func_060D6860,
        func_060D6894,
        func_060D6A38,
        func_060D6B18,
        func_060D6B30,
        func_060D6B48,
        func_060D6B60,
        func_060D6B78,
    },
    DAT_060D711C,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D61E4, func_060D61E4);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6390, func_060D6390);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D64D0, func_060D64D0);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6650, func_060D6650);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D683C, func_060D683C);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6854, func_060D6854);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6860, func_060D6860);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6894, func_060D6894);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6A38, func_060D6A38);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6B18, func_060D6B18);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6B30, func_060D6B30);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6B48, func_060D6B48);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6B60, func_060D6B60);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6B78, func_060D6B78);
INCLUDE_ASM("asm/saturn/weapon/w_45/f_nonmat", f60D6B90, func_060D6B90);

u32 DAT_060D6BA0[2] = {
    0x00000000,
    0x00000000,
};

SaturnSpriteImage DAT_060D6BA8[17] = {
    {12, 16, 0x0000}, {12, 16, 0x0030}, {8, 16, 0x0060},  {16, 11, 0x0080},
    {16, 14, 0x00AC}, {16, 13, 0x00E4}, {12, 11, 0x0118}, {12, 11, 0x013C},
    {20, 16, 0x0160}, {16, 11, 0x01B0}, {28, 30, 0x01DC}, {32, 23, 0x02B0},
    {16, 9, 0x0368},  {20, 14, 0x038C}, {16, 14, 0x03D4}, {16, 14, 0x040C},
    {0, 0, 0x0444},
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding[1];
} DAT_060D6BEC = {
    0x0002,
    {
        {0x85C0, 0x8822, 0x83E0, 0xECE5, 0xF68A, 0x8048, 0x884C, 0x88B5, 0x8D39,
         0x821C, 0x9CA4, 0xAD29, 0xBDAD, 0xD231, 0xE6B5, 0xEB7A},
        {0x8161, 0xEB5A, 0xEAB1, 0xDE29, 0xE4E4, 0xA884, 0x8C00, 0x83E0, 0x802D,
         0x80DD, 0xAA5F, 0x84D1, 0x98C6, 0xB5AD, 0xC631, 0x8421},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6C30 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6C34 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C40 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 14, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C4C = {
    {0x0100, 0x0000},
    {
        {0x0010, -17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C58 = {
    {0x0100, 0x0000},
    {
        {0x0010, -16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C64 = {
    {0x0100, 0x0000},
    {
        {0x0010, -15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C70 = {
    {0x0100, 0x0000},
    {
        {0x0010, -14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C7C = {
    {0x0100, 0x0000},
    {
        {0x0010, -12, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C88 = {
    {0x0100, 0x0000},
    {
        {0x0000, -3, -2, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C94 = {
    {0x0100, 0x0000},
    {
        {0x0000, 1, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CA0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6CAC = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CB8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CC4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CD0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CDC = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CE8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6CF4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D00 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D0C = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D18 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D24 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D30 = {
    {0x0100, 0x0000},
    {
        {0x0000, 25, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D3C = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D48 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D54 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D60 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D6C = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D78 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D84 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D90 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6D9C = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DA8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DB4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DC0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DCC = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DD8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DE4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DF0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6DFC = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E08 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E14 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E20 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E2C = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E38 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E44 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E50 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E5C = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E68 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6E74 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -2, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E80 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E8C = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -6, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6E98 = {
    {0x0100, 0x0000},
    {
        {0x0000, 11, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6EBC = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 12, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6ED4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EEC = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EF8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F04 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F10 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 2, 0},
    },
};

SaturnSpriteFrame3 DAT_060D6F1C = {
    {0x0300, 0x0000},
    {
        {0x0100, 1, 15, 3},
        {0x0100, 1, -25, 4},
        {0x0100, 6, -9, 5},
    },
};

SaturnSpriteFrame3 DAT_060D6F38 = {
    {0x0300, 0x0000},
    {
        {0x0100, 4, 14, 6},
        {0x0100, -1, -24, 4},
        {0x0100, 6, -10, 5},
    },
};

SaturnSpriteFrame2 DAT_060D6F54 = {
    {0x0200, 0x0000},
    {
        {0x0100, 3, 14, 7},
        {0x0100, 1, -12, 8},
    },
};

SaturnSpriteFrame2 DAT_060D6F68 = {
    {0x0200, 0x0000},
    {
        {0x0100, 1, -11, 8},
        {0x0100, 2, 15, 9},
    },
};

SaturnSpriteFrame2 DAT_060D6F7C = {
    {0x0200, 0x0000},
    {
        {0x0100, 40, -14, 10},
        {0x0100, 20, 3, 11},
    },
};

SaturnSpriteFrame1 DAT_060D6F90 = {
    {0x0100, 0x0000},
    {
        {0x0100, 20, 3, 11},
    },
};

SaturnSpriteFrame2 DAT_060D6F9C = {
    {0x0200, 0x0000},
    {
        {0x0100, -11, 18, 12},
        {0x0100, -27, 1, 13},
    },
};

SaturnSpriteFrame2 DAT_060D6FB0 = {
    {0x0200, 0x0000},
    {
        {0x0100, -1, 12, 14},
        {0x0100, -16, -10, 13},
    },
};

SaturnSpriteFrame2 DAT_060D6FC4 = {
    {0x0200, 0x0000},
    {
        {0x0130, 12, 18, 12},
        {0x0100, 29, 6, 13},
    },
};

SaturnSpriteFrame2 DAT_060D6FD8 = {
    {0x0200, 0x0000},
    {
        {0x0100, 6, 13, 15},
        {0x0100, 15, -9, 13},
    },
};

SaturnSpriteFrameHeader* DAT_060D6FEC[73] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6C30,
    (SaturnSpriteFrameHeader*)&DAT_060D6C34,
    (SaturnSpriteFrameHeader*)&DAT_060D6C40,
    (SaturnSpriteFrameHeader*)&DAT_060D6C4C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C58,
    (SaturnSpriteFrameHeader*)&DAT_060D6C64,
    (SaturnSpriteFrameHeader*)&DAT_060D6C70,
    (SaturnSpriteFrameHeader*)&DAT_060D6C7C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C88,
    (SaturnSpriteFrameHeader*)&DAT_060D6C94,
    (SaturnSpriteFrameHeader*)&DAT_060D6CA0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6CC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6CD0,
    (SaturnSpriteFrameHeader*)&DAT_060D6CDC,
    (SaturnSpriteFrameHeader*)&DAT_060D6CE8,
    (SaturnSpriteFrameHeader*)&DAT_060D6CF4,
    (SaturnSpriteFrameHeader*)&DAT_060D6D00,
    (SaturnSpriteFrameHeader*)&DAT_060D6D0C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D18,
    (SaturnSpriteFrameHeader*)&DAT_060D6D24,
    (SaturnSpriteFrameHeader*)&DAT_060D6D30,
    (SaturnSpriteFrameHeader*)&DAT_060D6D3C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D48,
    (SaturnSpriteFrameHeader*)&DAT_060D6D54,
    (SaturnSpriteFrameHeader*)&DAT_060D6D60,
    (SaturnSpriteFrameHeader*)&DAT_060D6D6C,
    (SaturnSpriteFrameHeader*)&DAT_060D6D78,
    (SaturnSpriteFrameHeader*)&DAT_060D6D84,
    (SaturnSpriteFrameHeader*)&DAT_060D6D90,
    (SaturnSpriteFrameHeader*)&DAT_060D6D9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6DA8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DB4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DCC,
    (SaturnSpriteFrameHeader*)&DAT_060D6DD8,
    (SaturnSpriteFrameHeader*)&DAT_060D6DE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6DF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6DFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6E08,
    (SaturnSpriteFrameHeader*)&DAT_060D6E14,
    (SaturnSpriteFrameHeader*)&DAT_060D6E20,
    (SaturnSpriteFrameHeader*)&DAT_060D6E2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E38,
    (SaturnSpriteFrameHeader*)&DAT_060D6E44,
    (SaturnSpriteFrameHeader*)&DAT_060D6E50,
    (SaturnSpriteFrameHeader*)&DAT_060D6E5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E68,
    (SaturnSpriteFrameHeader*)&DAT_060D6E74,
    (SaturnSpriteFrameHeader*)&DAT_060D6E80,
    (SaturnSpriteFrameHeader*)&DAT_060D6E8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6E98,
    (SaturnSpriteFrameHeader*)&DAT_060D6EA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6EB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6EC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6ED4,
    (SaturnSpriteFrameHeader*)&DAT_060D6EE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6EF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6F04,
    (SaturnSpriteFrameHeader*)&DAT_060D6F10,
    (SaturnSpriteFrameHeader*)&DAT_060D6F1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F38,
    (SaturnSpriteFrameHeader*)&DAT_060D6F54,
    (SaturnSpriteFrameHeader*)&DAT_060D6F68,
    (SaturnSpriteFrameHeader*)&DAT_060D6F7C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F90,
    (SaturnSpriteFrameHeader*)&DAT_060D6F9C,
    (SaturnSpriteFrameHeader*)&DAT_060D6FB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FC4,
    (SaturnSpriteFrameHeader*)&DAT_060D6FD8,
};

SaturnSpriteResource DAT_060D7110 = {
    DAT_060D6BA8, (u16*)&DAT_060D6BEC, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D711C[1] = {&DAT_060D7110};
