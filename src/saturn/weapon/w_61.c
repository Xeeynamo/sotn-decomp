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
void func_060D6740();
void func_060D6758();
void func_060D6764();
void func_060D6B74();
void func_060D6FEC();
void func_060D7004();
void func_060D701C();
void func_060D7034();
void func_060D704C();
void func_060D7064();
void func_060D707C();
extern SaturnSpriteResource* DAT_060D77D0[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6498,
        func_060D64B0,
        func_060D64C8,
        func_060D64E0,
        func_060D6740,
        func_060D6758,
        func_060D707C,
        func_060D6764,
        func_060D6B74,
        func_060D6FEC,
        func_060D7004,
        func_060D701C,
        func_060D7034,
        func_060D704C,
        func_060D7064,
    },
    DAT_060D77D0,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D6498, func_060D6498);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D64B0, func_060D64B0);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D64C8, func_060D64C8);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D64E0, func_060D64E0);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D6740, func_060D6740);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D6758, func_060D6758);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D6764, func_060D6764);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D6B74, func_060D6B74);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D6FEC, func_060D6FEC);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D7004, func_060D7004);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D701C, func_060D701C);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D7034, func_060D7034);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D704C, func_060D704C);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D7064, func_060D7064);
INCLUDE_ASM("asm/saturn/weapon/w_61/f_nonmat", f60D707C, func_060D707C);

AnimationFrame DAT_060D7090[2] = {{0x0002, 0x0201}, {0x0000, 0x0000}};

AnimationFrame DAT_060D7098[2] = {{0x0002, 0x0402}, {0x0000, 0x0000}};

AnimationFrame DAT_060D70A0[11] = {
    {0x0002, 0x0603}, {0x0002, 0x0604}, {0x0002, 0x0605}, {0x0002, 0x0606},
    {0x0002, 0x0607}, {0x0002, 0x0608}, {0x0002, 0x0809}, {0x0002, 0x020A},
    {0x0002, 0x020B}, {0x0002, 0x020C}, {0x0000, 0x0000}};

AnimationFrame DAT_060D70CC[17] = {
    {0x0003, 0x020D}, {0x0003, 0x0E0E}, {0x0003, 0x100F}, {0x0003, 0x1210},
    {0x0003, 0x1411}, {0x0003, 0x1612}, {0x0003, 0x1813}, {0x0003, 0x1A14},
    {0x0003, 0x1C15}, {0x0003, 0x1A16}, {0x0003, 0x1817}, {0x0003, 0x1618},
    {0x0003, 0x1419}, {0x0003, 0x121A}, {0x0003, 0x101B}, {0x0003, 0x0E1C},
    {0x0000, 0x0000}};

AnimationFrame DAT_060D7110[14] = {
    {0x0001, 0x0224}, {0x0001, 0x0225}, {0x0001, 0x0226}, {0x0001, 0x0227},
    {0x0001, 0x0228}, {0x0001, 0x0229}, {0x0001, 0x022A}, {0x0001, 0x022B},
    {0x0001, 0x022C}, {0x0001, 0x022D}, {0x0001, 0x022E}, {0x0001, 0x022F},
    {0x0001, 0x0230}, {0x0000, 0x0000}};

AnimationFrame DAT_060D7148[8] = {
    {0x0001, 0x022A}, {0x0001, 0x022B}, {0x0001, 0x022C}, {0x0001, 0x022D},
    {0x0001, 0x022E}, {0x0001, 0x022F}, {0x0001, 0x0230}, {0x0000, 0x0000}};

AnimationFrame DAT_060D7168[17] = {
    {0x0002, 0x0221}, {0x0002, 0x0222}, {0x0002, 0x0223}, {0x0002, 0x0224},
    {0x0002, 0x0225}, {0x0002, 0x0226}, {0x0002, 0x0227}, {0x0002, 0x0228},
    {0x0002, 0x0229}, {0x0002, 0x022A}, {0x0002, 0x022B}, {0x0002, 0x022C},
    {0x0002, 0x022D}, {0x0002, 0x022E}, {0x0002, 0x022F}, {0x0002, 0x0230},
    {0x0000, 0x0000}};

AnimationFrame DAT_060D71AC[4] = {
    {0x0002, 0x0231}, {0x0002, 0x0232}, {0x0002, 0x0233}, {0xFFFF, 0x0000}};

AnimationFrame DAT_060D71BC[4] = {
    {0x0002, 0x0434}, {0x0002, 0x0435}, {0x0002, 0x0436}, {0xFFFF, 0x0000}};

AnimationFrame DAT_060D71CC[4] = {
    {0x0002, 0x0233}, {0x0002, 0x0232}, {0x0002, 0x0231}, {0xFFFF, 0x0000}};

AnimationFrame DAT_060D71DC[4] = {
    {0x0002, 0x0436}, {0x0002, 0x0435}, {0x0002, 0x0434}, {0xFFFF, 0x0000}};

AnimationFrame DAT_060D71EC[3] = {
    {0x0004, 0x021D}, {0x0004, 0x021E}, {0x0000, 0x0000}};

AnimationFrame DAT_060D71F8[3] = {
    {0x0002, 0x0C1F}, {0x0002, 0x0C20}, {0x0000, 0x0000}};

AnimationFrame DAT_060D7204[16] = {
    {0x0003, 0x2237}, {0x0003, 0x2238}, {0x0003, 0x2238}, {0x0003, 0x2038},
    {0x0003, 0x1E38}, {0x0003, 0x0239}, {0x0003, 0x023A}, {0x0003, 0x023B},
    {0x0003, 0x023C}, {0x0003, 0x023D}, {0x0003, 0x0201}, {0x0003, 0x0201},
    {0x0003, 0x0201}, {0x0003, 0x0201}, {0x0003, 0x0201}, {0x0000, 0x0000}};

s8 DAT_060D7244[18][4] = {
    {0, 0, 0, 0},    {14, -7, 4, 12},  {14, 13, 4, 12}, {-11, -7, 4, 12},
    {1, -5, 4, 12},  {-32, -31, 0, 0}, {22, -6, 4, 12}, {15, -6, 4, 12},
    {16, -5, 4, 12}, {17, -4, 4, 12},  {18, -3, 4, 12}, {19, -2, 4, 12},
    {20, -1, 4, 12}, {21, 0, 4, 12},   {22, 1, 4, 12},  {12, -5, 4, 12},
    {10, -3, 4, 12}, {8, -1, 4, 12}};

AnimationFrame* DAT_060D728C[14] = {
    DAT_060D7090, DAT_060D7098, DAT_060D71F8, DAT_060D7204, DAT_060D71EC,
    DAT_060D7168, DAT_060D7148, DAT_060D7110, DAT_060D70CC, DAT_060D70A0,
    DAT_060D71AC, DAT_060D71BC, DAT_060D71CC, DAT_060D71DC};

SaturnSpriteImage DAT_060D72C4[17] = {
    {16, 20, 0x0000}, {20, 20, 0x0050}, {16, 20, 0x00B4}, {20, 20, 0x0104},
    {8, 8, 0x0168},   {8, 8, 0x0178},   {8, 8, 0x0188},   {8, 8, 0x0198},
    {8, 8, 0x01A8},   {8, 8, 0x01B8},   {8, 8, 0x01C8},   {8, 8, 0x01D8},
    {8, 8, 0x01E8},   {8, 8, 0x01F8},   {8, 8, 0x0208},   {8, 8, 0x0218},
    {0, 0, 0x0228},
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding[1];
} DAT_060D7308 = {
    0x0002,
    {
        {0xC5E2, 0x8421, 0x8444, 0x8467, 0x84AB, 0x88ED, 0x8D30, 0x9573, 0x9994,
         0x9DB6, 0x8031, 0x807F, 0x80C0, 0x81C0, 0x8281, 0xB69D},
        {0xC001, 0x80E7, 0x8548, 0x8DAA, 0x920B, 0x9A6D, 0xA2CF, 0xA730, 0x80C0,
         0x8521, 0x89A1, 0x8E02, 0x9223, 0x9685, 0x9EE7, 0xA349},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D734C = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D7350 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D735C = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 17, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7368 = {
    {0x0100, 0x0000},
    {
        {0x0014, -15, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7374 = {
    {0x0100, 0x0000},
    {
        {0x0014, -14, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7380 = {
    {0x0100, 0x0000},
    {
        {0x0014, -13, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D738C = {
    {0x0100, 0x0000},
    {
        {0x0014, -11, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7398 = {
    {0x0100, 0x0000},
    {
        {0x0014, -9, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73A4 = {
    {0x0100, 0x0000},
    {
        {0x0004, -4, -1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D73B0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 1, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D73BC = {
    {0x0100, 0x0000},
    {
        {0x0004, 10, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D73C8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73D4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73E0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73EC = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73F8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7404 = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7410 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D741C = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7428 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7434 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7440 = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 4, 0},
    },
};

SaturnSpriteFrame1 DAT_060D744C = {
    {0x0100, 0x0000},
    {
        {0x0004, 26, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7458 = {
    {0x0100, 0x0000},
    {
        {0x0004, 25, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7464 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 3, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7470 = {
    {0x0100, 0x0000},
    {
        {0x0004, 23, 2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D747C = {
    {0x0100, 0x0000},
    {
        {0x0004, 22, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7488 = {
    {0x0100, 0x0000},
    {
        {0x0004, 20, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7494 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74A0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -2, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74AC = {
    {0x0100, 0x0000},
    {
        {0x0004, 21, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74B8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74C4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 24, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74D0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74DC = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74E8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74F4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7500 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D750C = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7518 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7524 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7530 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D753C = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7548 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7554 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7560 = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D756C = {
    {0x0100, 0x0000},
    {
        {0x0004, 19, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7578 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7584 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7590 = {
    {0x0100, 0x0000},
    {
        {0x0000, 15, 1, 2},
    },
};

SaturnSpriteFrame1 DAT_060D759C = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, -1, 2},
    },
};

SaturnSpriteFrame1 DAT_060D75A8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D75B4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, 15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D75C0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 16, 2},
    },
};

SaturnSpriteFrame1 DAT_060D75CC = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, 17, 2},
    },
};

SaturnSpriteFrame1 DAT_060D75D8 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75E4 = {
    {0x0100, 0x0000},
    {
        {0x0004, 12, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75F0 = {
    {0x0100, 0x0000},
    {
        {0x0004, 13, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D75FC = {
    {0x0100, 0x0000},
    {
        {0x0004, 14, 0, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7608 = {
    {0x0100, 0x0000},
    {
        {0x0004, 15, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7614 = {
    {0x0100, 0x0000},
    {
        {0x0004, 17, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7620 = {
    {0x0100, 0x0000},
    {
        {0x0004, 18, -2, 0},
    },
};

SaturnSpriteFrame2 DAT_060D762C = {
    {0x0200, 0x0000},
    {
        {0x0004, 1, 5, 0},
        {0x0100, 1, -3, 3},
    },
};

SaturnSpriteFrame2 DAT_060D7640 = {
    {0x0200, 0x0000},
    {
        {0x0000, 12, -63, 0},
        {0x0100, 12, -71, 3},
    },
};

SaturnSpriteFrame6 DAT_060D7654 = {
    {0x0600, 0x0000},
    {
        {0x0100, 0, -55, 4},
        {0x0100, 0, -39, 5},
        {0x0100, 0, -23, 6},
        {0x0100, 0, -7, 7},
        {0x0100, 0, 9, 8},
        {0x0100, 0, 25, 9},
    },
};

SaturnSpriteFrame6 DAT_060D7688 = {
    {0x0600, 0x0000},
    {
        {0x0100, 0, -55, 10},
        {0x0100, 0, -39, 11},
        {0x0100, 0, -23, 12},
        {0x0100, 0, -7, 13},
        {0x0100, 0, 9, 14},
        {0x0100, 0, 25, 15},
    },
};

SaturnSpriteFrameHeader* DAT_060D76BC[66] = {
    (SaturnSpriteFrameHeader*)&DAT_060D734C,
    (SaturnSpriteFrameHeader*)&DAT_060D7350,
    (SaturnSpriteFrameHeader*)&DAT_060D735C,
    (SaturnSpriteFrameHeader*)&DAT_060D7368,
    (SaturnSpriteFrameHeader*)&DAT_060D7374,
    (SaturnSpriteFrameHeader*)&DAT_060D7380,
    (SaturnSpriteFrameHeader*)&DAT_060D738C,
    (SaturnSpriteFrameHeader*)&DAT_060D7398,
    (SaturnSpriteFrameHeader*)&DAT_060D73A4,
    (SaturnSpriteFrameHeader*)&DAT_060D73B0,
    (SaturnSpriteFrameHeader*)&DAT_060D73BC,
    (SaturnSpriteFrameHeader*)&DAT_060D73C8,
    (SaturnSpriteFrameHeader*)&DAT_060D73D4,
    (SaturnSpriteFrameHeader*)&DAT_060D73E0,
    (SaturnSpriteFrameHeader*)&DAT_060D73EC,
    (SaturnSpriteFrameHeader*)&DAT_060D73F8,
    (SaturnSpriteFrameHeader*)&DAT_060D7404,
    (SaturnSpriteFrameHeader*)&DAT_060D7410,
    (SaturnSpriteFrameHeader*)&DAT_060D741C,
    (SaturnSpriteFrameHeader*)&DAT_060D7428,
    (SaturnSpriteFrameHeader*)&DAT_060D7434,
    (SaturnSpriteFrameHeader*)&DAT_060D7440,
    (SaturnSpriteFrameHeader*)&DAT_060D744C,
    (SaturnSpriteFrameHeader*)&DAT_060D7458,
    (SaturnSpriteFrameHeader*)&DAT_060D7464,
    (SaturnSpriteFrameHeader*)&DAT_060D7470,
    (SaturnSpriteFrameHeader*)&DAT_060D747C,
    (SaturnSpriteFrameHeader*)&DAT_060D7488,
    (SaturnSpriteFrameHeader*)&DAT_060D7494,
    (SaturnSpriteFrameHeader*)&DAT_060D74A0,
    (SaturnSpriteFrameHeader*)&DAT_060D74AC,
    (SaturnSpriteFrameHeader*)&DAT_060D74B8,
    (SaturnSpriteFrameHeader*)&DAT_060D74C4,
    (SaturnSpriteFrameHeader*)&DAT_060D74D0,
    (SaturnSpriteFrameHeader*)&DAT_060D74DC,
    (SaturnSpriteFrameHeader*)&DAT_060D74E8,
    (SaturnSpriteFrameHeader*)&DAT_060D74F4,
    (SaturnSpriteFrameHeader*)&DAT_060D7500,
    (SaturnSpriteFrameHeader*)&DAT_060D750C,
    (SaturnSpriteFrameHeader*)&DAT_060D7518,
    (SaturnSpriteFrameHeader*)&DAT_060D7524,
    (SaturnSpriteFrameHeader*)&DAT_060D7530,
    (SaturnSpriteFrameHeader*)&DAT_060D753C,
    (SaturnSpriteFrameHeader*)&DAT_060D7548,
    (SaturnSpriteFrameHeader*)&DAT_060D7554,
    (SaturnSpriteFrameHeader*)&DAT_060D7560,
    (SaturnSpriteFrameHeader*)&DAT_060D756C,
    (SaturnSpriteFrameHeader*)&DAT_060D7578,
    (SaturnSpriteFrameHeader*)&DAT_060D7584,
    (SaturnSpriteFrameHeader*)&DAT_060D7590,
    (SaturnSpriteFrameHeader*)&DAT_060D759C,
    (SaturnSpriteFrameHeader*)&DAT_060D75A8,
    (SaturnSpriteFrameHeader*)&DAT_060D75B4,
    (SaturnSpriteFrameHeader*)&DAT_060D75C0,
    (SaturnSpriteFrameHeader*)&DAT_060D75CC,
    (SaturnSpriteFrameHeader*)&DAT_060D75D8,
    (SaturnSpriteFrameHeader*)&DAT_060D75E4,
    (SaturnSpriteFrameHeader*)&DAT_060D75F0,
    (SaturnSpriteFrameHeader*)&DAT_060D75FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7608,
    (SaturnSpriteFrameHeader*)&DAT_060D7614,
    (SaturnSpriteFrameHeader*)&DAT_060D7620,
    (SaturnSpriteFrameHeader*)&DAT_060D762C,
    (SaturnSpriteFrameHeader*)&DAT_060D7640,
    (SaturnSpriteFrameHeader*)&DAT_060D7654,
    (SaturnSpriteFrameHeader*)&DAT_060D7688,
};

SaturnSpriteResource DAT_060D77C4 = {
    DAT_060D72C4, (u16*)&DAT_060D7308, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D77D0[1] = {&DAT_060D77C4};
