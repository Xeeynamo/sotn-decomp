// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D63A0();
void func_060D63B8();
void func_060D63D0();
void func_060D6768();
void func_060D6780();
void func_060D6798();
void func_060D67A4();
void func_060D67BC();
void func_060D6890();
void func_060D68A8();
void func_060D68C0();
void func_060D68D8();
void func_060D68F0();
void func_060D6908();
void func_060D6920();
extern SaturnSpriteResource* DAT_060D71A8[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D63A0,
        func_060D63B8,
        func_060D63D0,
        func_060D6768,
        func_060D6780,
        func_060D6798,
        func_060D6920,
        func_060D67A4,
        func_060D67BC,
        func_060D6890,
        func_060D68A8,
        func_060D68C0,
        func_060D68D8,
        func_060D68F0,
        func_060D6908,
    },
    DAT_060D71A8,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D63A0, func_060D63A0);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D63B8, func_060D63B8);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D63D0, func_060D63D0);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D6768, func_060D6768);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D6780, func_060D6780);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D6798, func_060D6798);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D67A4, func_060D67A4);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D67BC, func_060D67BC);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D6890, func_060D6890);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D68A8, func_060D68A8);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D68C0, func_060D68C0);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D68D8, func_060D68D8);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D68F0, func_060D68F0);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D6908, func_060D6908);
INCLUDE_ASM("asm/saturn/weapon/w_62/f_nonmat", f60D6920, func_060D6920);

u16 DAT_060D6930[9] = {
    0x0201, 0x0402, 0x0603, 0x0605, 0x0603, 0x0402, 0x3A04, 0x0806, 0xFFFF};

u16 DAT_060D6942[8] = {
    0x0A07, 0x0C09, 0x0E0A, 0x0E0B, 0x0E0A, 0x0C09, 0x3C08, 0xFFFF};

u16 DAT_060D6952[6] = {0x040C, 0x100D, 0x100E, 0x100D, 0x040C, 0xFFFF};

u16 DAT_060D695E[4] = {0x120F, 0x1410, 0x120F, 0xFFFF};

u16 DAT_060D6966[10] = {0x1611, 0x1812, 0x1813, 0x1A14, 0x0815,
                        0x0816, 0x0817, 0x0818, 0x0819, 0xFFFF};

u16 DAT_060D697A[10] = {0x1C1A, 0x1E1B, 0x1E1C, 0x201D, 0x081E,
                        0x0823, 0x0824, 0x0825, 0x0826, 0xFFFF};

u16 DAT_060D698E[10] = {0x1C1A, 0x221F, 0x2420, 0x2621, 0x0822,
                        0x0823, 0x0824, 0x0825, 0x0826, 0xFFFF};

u16 DAT_060D69A2[7] = {0x2827, 0x2A28, 0x2A29, 0x2C2A, 0x082B, 0x082C, 0xFFFF};

u16 DAT_060D69B0[14] = {0x2E2D, 0x302E, 0x302F, 0x3230, 0x0831, 0x0836, 0xFFFF,
                        0x2E2D, 0x3432, 0x3633, 0x3834, 0x0835, 0x0836, 0xFFFF};

s8 DAT_060D69CC[31][4] = {
    {0, 0, 0, 0},     {15, -16, 10, 9}, {23, -15, 16, 5}, {26, -13, 28, 5},
    {-40, -31, 0, 0}, {9, 1, 11, 9},    {16, 3, 15, 6},   {18, 4, 28, 5},
    {29, -12, 29, 8}, {9, -9, 14, 9},   {38, 14, 7, 6},   {-6, -16, 6, 4},
    {24, -14, 30, 5}, {30, -12, 16, 3}, {-19, 1, 8, 4},   {16, 3, 30, 5},
    {20, 5, 16, 3},   {11, 13, 20, 9},  {25, 21, 23, 8},  {15, 19, 16, 3},
    {-14, -17, 8, 4}, {24, -16, 28, 8}, {28, -14, 18, 3}, {-25, -19, 6, 4},
    {20, -14, 29, 8}, {23, -12, 18, 3}, {20, -1, 24, 13}, {24, -1, 24, 13},
    {15, 1, 19, 4},   {20, -12, 6, 4},  {12, 4, 6, 4}};

u16* DAT_060D6A48[7] = {DAT_060D6930, DAT_060D6930, DAT_060D6942, DAT_060D6942,
                        DAT_060D6952, DAT_060D695E, DAT_060D695E};

u16* DAT_060D6A64[7] = {DAT_060D6966, DAT_060D6966, DAT_060D697A, DAT_060D698E,
                        DAT_060D69A2, DAT_060D69B0, DAT_060D69B0};

WeaponAnimation DAT_060D6A80[2] = {
    {(u16**)DAT_060D6A48, (s8*)DAT_060D69CC, 0x0000, 0x060C, 0x77, 0x01, 0},
    {(u16**)DAT_060D6A64, (s8*)DAT_060D69CC, 0x0000, 0x060B, 0x7E, 0x02, 0},
};

AnimationFrame DAT_060D6AA0[16] = {
    {0x0003, 0x0037}, {0x0003, 0x0038}, {0x0003, 0x0039}, {0x0003, 0x003A},
    {0x0003, 0x003B}, {0x0004, 0x003C}, {0x0004, 0x003D}, {0x0004, 0x003E},
    {0x0005, 0x003F}, {0x0005, 0x0040}, {0x0005, 0x0041}, {0x0007, 0x0042},
    {0x0007, 0x0043}, {0x0008, 0x0044}, {0x0009, 0x0037}, {0xFFFF, 0x0000}};

SaturnSpriteImage DAT_060D6AE0[20] = {
    {8, 4, 0x0000},  {8, 3, 0x0008},  {8, 3, 0x0010},  {16, 4, 0x0018},
    {8, 4, 0x0028},  {24, 1, 0x0030}, {20, 3, 0x0038}, {4, 2, 0x0048},
    {20, 8, 0x004C}, {20, 5, 0x0074}, {4, 8, 0x0090},  {4, 5, 0x0098},
    {8, 8, 0x00A0},  {4, 4, 0x00B0},  {8, 7, 0x00B4},  {4, 3, 0x00C4},
    {16, 4, 0x00C8}, {4, 2, 0x00D8},  {4, 4, 0x00DC},  {0, 0, 0x00E0},
};

struct {
    u16 countAndFlags;
    u16 colors[3][16];
    u16 padding[1];
} DAT_060D6B30 = {
    0x0003,
    {
        {0x81A0, 0x8421, 0x800D, 0x8010, 0x8014, 0x8018, 0x801C, 0x801F, 0xFC42,
         0x9084, 0x90EB, 0x8173, 0x9218, 0x9EDF, 0x98DF, 0x93A4},
        {0x9E00, 0xB033, 0xB053, 0xB473, 0xB893, 0xBCD3, 0xC0F4, 0xC514, 0xC954,
         0xCD74, 0xD195, 0xD5D5, 0xD9F5, 0xDE15, 0xE256, 0xCED9},
        {0x8000, 0x9400, 0xAC20, 0xC440, 0xCC60, 0x9800, 0xA820, 0x9400, 0xA820,
         0xBC40, 0xD460, 0xE880, 0xFCA0, 0xFD60, 0xFF20, 0xFF98},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D6B94 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D6B98 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -19, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BA4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 30, -17, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6BB0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 40, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6BBC = {
    {0x0100, 0x0000},
    {
        {0x0020, 21, -11, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BC8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 35, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6BD4 = {
    {0x0100, 0x0000},
    {
        {0x0010, 8, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BE0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, -1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BEC = {
    {0x0100, 0x0000},
    {
        {0x0020, 12, 5, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6BF8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 1, 1},
    },
};

SaturnSpriteFrame1 DAT_060D6C04 = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C10 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, 5, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C1C = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -16, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C28 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C34 = {
    {0x0100, 0x0000},
    {
        {0x0000, 39, -12, 3},
    },
};

SaturnSpriteFrame1 DAT_060D6C40 = {
    {0x0100, 0x0000},
    {
        {0x0010, 9, -8, 0},
    },
};

SaturnSpriteFrame1 DAT_060D6C4C = {
    {0x0100, 0x0000},
    {
        {0x0010, 34, 12, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6C58 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -16, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6C64 = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6C70 = {
    {0x0100, 0x0000},
    {
        {0x0000, 48, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6C7C = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, -11, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6C88 = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6C94 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6CA0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6CAC = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6CB8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6CC4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, 0, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6CD0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 14, 4, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6CDC = {
    {0x0100, 0x0000},
    {
        {0x0000, 32, 3, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6CE8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 18, 6, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6CF4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6D00 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 12, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6D0C = {
    {0x0100, 0x0000},
    {
        {0x0010, 24, 19, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D18 = {
    {0x0100, 0x0000},
    {
        {0x0010, 17, 18, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6D24 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, 14, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6D30 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, 10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6D3C = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, 10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6D48 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6D54 = {
    {0x0100, 0x0000},
    {
        {0x0000, -19, 9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6D60 = {
    {0x0100, 0x0000},
    {
        {0x0000, -12, -18, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6D6C = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, -15, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6D78 = {
    {0x0100, 0x0000},
    {
        {0x0000, 37, -16, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6D84 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -13, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6D90 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, -10, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6D9C = {
    {0x0100, 0x0000},
    {
        {0x0000, -2, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6DA8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -20, -19, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DB4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -13, 5},
    },
};

SaturnSpriteFrame1 DAT_060D6DC0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 33, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D6DCC = {
    {0x0100, 0x0000},
    {
        {0x0000, 20, -11, 6},
    },
};

SaturnSpriteFrame1 DAT_060D6DD8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, -9, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6DE4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 21, 1, 8},
    },
};

SaturnSpriteFrame1 DAT_060D6DF0 = {
    {0x0100, 0x0000},
    {
        {0x0010, 31, 7, 4},
    },
};

SaturnSpriteFrame1 DAT_060D6DFC = {
    {0x0100, 0x0000},
    {
        {0x0000, 19, 1, 9},
    },
};

SaturnSpriteFrame1 DAT_060D6E08 = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -5, 7},
    },
};

SaturnSpriteFrame1 DAT_060D6E14 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -9, 7},
    },
};

SaturnSpriteFrame2 DAT_060D6E20 = {
    {0x0200, 0x0000},
    {
        {0x0000, 0, -39, 10},
        {0x0000, 3, -51, 11},
    },
};

SaturnSpriteFrame4 DAT_060D6E34 = {
    {0x0400, 0x0000},
    {
        {0x0100, 0, -39, 10},
        {0x0100, 3, -51, 11},
        {0x0000, 3, -39, 12},
        {0x0000, 5, -51, 13},
    },
};

SaturnSpriteFrame6 DAT_060D6E58 = {
    {0x0600, 0x0000},
    {
        {0x0200, 0, -39, 10},
        {0x0200, 3, -51, 11},
        {0x0100, 3, -39, 12},
        {0x0100, 5, -51, 13},
        {0x0000, 0, -40, 14},
        {0x0000, 8, -49, 15},
    },
};

SaturnSpriteFrame5 DAT_060D6E8C = {
    {0x0500, 0x0000},
    {
        {0x0200, 3, -39, 12},
        {0x0200, 5, -51, 13},
        {0x0100, 8, -49, 15},
        {0x0100, 0, -40, 14},
        {0x0000, 4, -43, 16},
    },
};

SaturnSpriteFrame5 DAT_060D6EB8 = {
    {0x0500, 0x0000},
    {
        {0x0200, 8, -49, 15},
        {0x0200, 0, -40, 14},
        {0x0100, 4, -43, 16},
        {0x0020, -1, -45, 14},
        {0x0020, 7, -36, 17},
    },
};

SaturnSpriteFrame5 DAT_060D6EE4 = {
    {0x0500, 0x0000},
    {
        {0x0200, 4, -43, 16},
        {0x0120, -1, -45, 14},
        {0x0120, 7, -36, 17},
        {0x0020, 2, -46, 12},
        {0x0020, 4, -34, 18},
    },
};

SaturnSpriteFrame6 DAT_060D6F10 = {
    {0x0600, 0x0000},
    {
        {0x0220, -1, -45, 14},
        {0x0220, 7, -36, 17},
        {0x0120, 2, -46, 12},
        {0x0120, 4, -34, 18},
        {0x0020, -1, -47, 10},
        {0x0030, -3, -35, 11},
    },
};

SaturnSpriteFrame6 DAT_060D6F44 = {
    {0x0600, 0x0000},
    {
        {0x0220, 2, -46, 12},
        {0x0220, 4, -34, 18},
        {0x0120, -1, -47, 10},
        {0x0130, -3, -35, 11},
        {0x0030, -3, -46, 12},
        {0x0030, -5, -34, 18},
    },
};

SaturnSpriteFrame6 DAT_060D6F78 = {
    {0x0600, 0x0000},
    {
        {0x0220, -1, -47, 10},
        {0x0230, -3, -35, 11},
        {0x0130, -3, -46, 12},
        {0x0130, -5, -34, 18},
        {0x0030, -1, -44, 14},
        {0x0030, -9, -35, 15},
    },
};

SaturnSpriteFrame5 DAT_060D6FAC = {
    {0x0500, 0x0000},
    {
        {0x0230, -3, -46, 12},
        {0x0230, -5, -34, 18},
        {0x0130, -1, -44, 14},
        {0x0130, -9, -35, 15},
        {0x0030, -4, -43, 16},
    },
};

SaturnSpriteFrame5 DAT_060D6FD8 = {
    {0x0500, 0x0000},
    {
        {0x0230, -1, -44, 14},
        {0x0230, -9, -35, 15},
        {0x0130, -4, -43, 16},
        {0x0010, 0, -40, 14},
        {0x0010, -8, -49, 17},
    },
};

SaturnSpriteFrame5 DAT_060D7004 = {
    {0x0500, 0x0000},
    {
        {0x0230, -4, -43, 16},
        {0x0110, 0, -40, 14},
        {0x0110, -8, -49, 17},
        {0x0010, -3, -40, 12},
        {0x0010, -5, -52, 18},
    },
};

SaturnSpriteFrame6 DAT_060D7030 = {
    {0x0600, 0x0000},
    {
        {0x0210, 0, -40, 14},
        {0x0210, -8, -49, 17},
        {0x0110, -3, -40, 12},
        {0x0110, -5, -52, 18},
        {0x0000, 3, -51, 11},
        {0x0000, 0, -39, 10},
    },
};

SaturnSpriteFrame4 DAT_060D7064 = {
    {0x0400, 0x0000},
    {
        {0x0110, -3, -40, 12},
        {0x0110, -5, -52, 18},
        {0x0000, 3, -51, 11},
        {0x0000, 0, -39, 10},
    },
};

SaturnSpriteFrameHeader* DAT_060D7088[69] = {
    (SaturnSpriteFrameHeader*)&DAT_060D6B94,
    (SaturnSpriteFrameHeader*)&DAT_060D6B98,
    (SaturnSpriteFrameHeader*)&DAT_060D6BA4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BB0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BBC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BC8,
    (SaturnSpriteFrameHeader*)&DAT_060D6BD4,
    (SaturnSpriteFrameHeader*)&DAT_060D6BE0,
    (SaturnSpriteFrameHeader*)&DAT_060D6BEC,
    (SaturnSpriteFrameHeader*)&DAT_060D6BF8,
    (SaturnSpriteFrameHeader*)&DAT_060D6C04,
    (SaturnSpriteFrameHeader*)&DAT_060D6C10,
    (SaturnSpriteFrameHeader*)&DAT_060D6C1C,
    (SaturnSpriteFrameHeader*)&DAT_060D6C28,
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
    (SaturnSpriteFrameHeader*)&DAT_060D6E34,
    (SaturnSpriteFrameHeader*)&DAT_060D6E58,
    (SaturnSpriteFrameHeader*)&DAT_060D6E8C,
    (SaturnSpriteFrameHeader*)&DAT_060D6EB8,
    (SaturnSpriteFrameHeader*)&DAT_060D6EE4,
    (SaturnSpriteFrameHeader*)&DAT_060D6F10,
    (SaturnSpriteFrameHeader*)&DAT_060D6F44,
    (SaturnSpriteFrameHeader*)&DAT_060D6F78,
    (SaturnSpriteFrameHeader*)&DAT_060D6FAC,
    (SaturnSpriteFrameHeader*)&DAT_060D6FD8,
    (SaturnSpriteFrameHeader*)&DAT_060D7004,
    (SaturnSpriteFrameHeader*)&DAT_060D7030,
    (SaturnSpriteFrameHeader*)&DAT_060D7064,
};

SaturnSpriteResource DAT_060D719C = {
    DAT_060D6AE0, (u16*)&DAT_060D6B30, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D71A8[1] = {&DAT_060D719C};
