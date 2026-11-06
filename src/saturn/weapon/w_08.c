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
void func_060D6B30();
void func_060D6B48();
void func_060D6B60();
void func_060D6B78();
void func_060D6B90();
void func_060D6BA8();
void func_060D6BC0();
void func_060D6BD8();
extern SaturnSpriteResource* DAT_060D72C0[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D64B0,
        func_060D64C8,
        func_060D64E0,
        func_060D64F8,
        func_060D6510,
        func_060D6BD8,
        func_060D651C,
        func_060D6B30,
        func_060D6B48,
        func_060D6B60,
        func_060D6B78,
        func_060D6B90,
        func_060D6BA8,
        func_060D6BC0,
    },
    DAT_060D72C0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D64B0, func_060D64B0);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D64C8, func_060D64C8);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D64E0, func_060D64E0);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D64F8, func_060D64F8);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6510, func_060D6510);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D651C, func_060D651C);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6B30, func_060D6B30);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6B48, func_060D6B48);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6B60, func_060D6B60);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6B78, func_060D6B78);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6B90, func_060D6B90);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6BA8, func_060D6BA8);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6BC0, func_060D6BC0);
INCLUDE_ASM("asm/saturn/weapon/w_08/f_nonmat", f60D6BD8, func_060D6BD8);

u32 DAT_060D6BF0[157] = {
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
    0x08FF040C, 0x060D6BF0, 0x060D6BF8, 0x060D6D58, 0x060D6D64, 0x060D6D4C,
    0x060D6CC8, 0x060D6CA8, 0x060D6C70, 0x060D6C2C, 0x060D6C00, 0x060D6D0C,
    0x060D6D1C, 0x060D6D2C, 0x060D6D3C, 0x00000000, 0x00000200, 0x00000400,
    0x00000600, 0x00000800, 0x00000A00, 0x00000C00, 0x00000E00, 0x00001000,
    0x00001200, 0x00001400, 0x00001600, 0x00001800, 0x00001A00, 0x00001C00,
    0x00001E00,
};

SaturnSpriteImage DAT_060D6E64[5] = {
    {12, 14, 0x0000}, {20, 14, 0x002C}, {12, 14, 0x0074},
    {44, 26, 0x00A0}, {0, 0, 0x01C0},
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding[1];
} DAT_060D6E78 = {
    0x0002,
    {
        {0x89E2, 0x8421, 0x8444, 0x8467, 0x84AB, 0x88ED, 0x8D30, 0x9573, 0x9994,
         0x9DB6, 0xA1F7, 0xA619, 0xE2F4, 0xAE7C, 0xCA52, 0xB6DF},
        {0x81C0, 0xD71D, 0xAD6F, 0x9D6D, 0x9972, 0xAA98, 0x9063, 0x9CC6, 0xA508,
         0xB16B, 0xB9CE, 0xC210, 0xCE73, 0xD6B5, 0xE318, 0xEF7B},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6EBC = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6EC0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -7, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6ECC = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 13, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6ED8 = {
    {0x0100, 0x0000},
    {
        {0x0014, -16, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EE4 = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EF0 = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6EFC = {
    {0x0100, 0x0000},
    {
        {0x0014, -12, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F08 = {
    {0x0100, 0x0000},
    {
        {0x0014, -10, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F14 = {
    {0x0100, 0x0000},
    {
        {0x0004, -2, -5, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F20 = {
    {0x0100, 0x0000},
    {
        {0x0004, 3, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F2C = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, -3, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6F38 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F44 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F50 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F5C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F68 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F74 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F80 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F8C = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6F98 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FA4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FB0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FBC = {
    {0x0100, 0x0000},
    {
        {0x0004, 27, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FC8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FD4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FE0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FEC = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6FF8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7004 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7010 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D701C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7028 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7034 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7040 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D704C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7058 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7064 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7070 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D707C = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7088 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7094 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70DC = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70E8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D70F4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7100 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D710C = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7118 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, -7, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7124 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, 11, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7130 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D713C = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7148 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7154 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7160 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D716C = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7178 = {
    {0x0100, 0x0000},
    {
        {0x0004, 16, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7184 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7190 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -6, 0},
    },
};

SaturnSpriteFrame1 DAT_060D719C = {
    {0x0100, 0x0000},
    {
        {0x0004, 2, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D71A8 = {
    {0x0100, 0x0000},
    {
        {0x0100, 13, 1, 3},
    },
};

SaturnSpriteFrameHeader* DAT_060D71B4[64] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6EBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6EC0,
    (SaturnSpriteFrameHeader*)&DAT_060D6ECC,
    (SaturnSpriteFrameHeader*)&DAT_060D6ED8,
    (SaturnSpriteFrameHeader*)&DAT_060D6EE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6EF0,
    (SaturnSpriteFrameHeader*)&DAT_060D6EFC,
    (SaturnSpriteFrameHeader*)&DAT_060D6F08,
    (SaturnSpriteFrameHeader*)&DAT_060D6F14,
    (SaturnSpriteFrameHeader*)&DAT_060D6F20,
    (SaturnSpriteFrameHeader*)&DAT_060D6F2C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F38,
    (SaturnSpriteFrameHeader*)&DAT_060D6F44,
    (SaturnSpriteFrameHeader*)&DAT_060D6F50,
    (SaturnSpriteFrameHeader*)&DAT_060D6F5C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F68,
    (SaturnSpriteFrameHeader*)&DAT_060D6F74,
    (SaturnSpriteFrameHeader*)&DAT_060D6F80,
    (SaturnSpriteFrameHeader*)&DAT_060D6F8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6F98,
    (SaturnSpriteFrameHeader*)&DAT_060D6FA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6FB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6FC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6FD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6FE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6FEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6FF8,
    (SaturnSpriteFrameHeader*)&DAT_060D7004,
    (SaturnSpriteFrameHeader*)&DAT_060D7010,
    (SaturnSpriteFrameHeader*)&DAT_060D701C,
    (SaturnSpriteFrameHeader*)&DAT_060D7028,
    (SaturnSpriteFrameHeader*)&DAT_060D7034,
    (SaturnSpriteFrameHeader*)&DAT_060D7040,
    (SaturnSpriteFrameHeader*)&DAT_060D704C,
    (SaturnSpriteFrameHeader*)&DAT_060D7058,
    (SaturnSpriteFrameHeader*)&DAT_060D7064,
    (SaturnSpriteFrameHeader*)&DAT_060D7070,
    (SaturnSpriteFrameHeader*)&DAT_060D707C,
    (SaturnSpriteFrameHeader*)&DAT_060D7088,
    (SaturnSpriteFrameHeader*)&DAT_060D7094,
    (SaturnSpriteFrameHeader*)&DAT_060D70A0,
    (SaturnSpriteFrameHeader*)&DAT_060D70AC,
    (SaturnSpriteFrameHeader*)&DAT_060D70B8,
    (SaturnSpriteFrameHeader*)&DAT_060D70C4,
    (SaturnSpriteFrameHeader*)&DAT_060D70D0,
    (SaturnSpriteFrameHeader*)&DAT_060D70DC,
    (SaturnSpriteFrameHeader*)&DAT_060D70E8,
    (SaturnSpriteFrameHeader*)&DAT_060D70F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7100,
    (SaturnSpriteFrameHeader*)&DAT_060D710C,
    (SaturnSpriteFrameHeader*)&DAT_060D7118,
    (SaturnSpriteFrameHeader*)&DAT_060D7124,
    (SaturnSpriteFrameHeader*)&DAT_060D7130,
    (SaturnSpriteFrameHeader*)&DAT_060D713C,
    (SaturnSpriteFrameHeader*)&DAT_060D7148,
    (SaturnSpriteFrameHeader*)&DAT_060D7154,
    (SaturnSpriteFrameHeader*)&DAT_060D7160,
    (SaturnSpriteFrameHeader*)&DAT_060D716C,
    (SaturnSpriteFrameHeader*)&DAT_060D7178,
    (SaturnSpriteFrameHeader*)&DAT_060D7184,
    (SaturnSpriteFrameHeader*)&DAT_060D7190,
    (SaturnSpriteFrameHeader*)&DAT_060D719C,
    (SaturnSpriteFrameHeader*)&DAT_060D71A8,
};

SaturnSpriteResource DAT_060D72B4 = {
    DAT_060D6E64, (u16*)&DAT_060D6E78, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D72C0[1] = {&DAT_060D72B4};
