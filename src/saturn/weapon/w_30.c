// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D62AC();
void func_060D6B60();
void func_060D6B78();
void func_060D6B90();
void func_060D6BA8();
void func_060D6BC0();
void func_060D6BCC();
void func_060D6BE4();
void func_060D6BFC();
void func_060D6C14();
void func_060D6C2C();
void func_060D6C44();
void func_060D6C5C();
void func_060D6C74();
void func_060D6C8C();
extern SaturnSpriteResource* DAT_060D7E44[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D62AC,
        func_060D6B60,
        func_060D6B78,
        func_060D6B90,
        func_060D6BA8,
        func_060D6BC0,
        func_060D6C8C,
        func_060D6BCC,
        func_060D6BE4,
        func_060D6BFC,
        func_060D6C14,
        func_060D6C2C,
        func_060D6C44,
        func_060D6C5C,
        func_060D6C74,
    },
    DAT_060D7E44,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D62AC, func_060D62AC);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6B60, func_060D6B60);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6B78, func_060D6B78);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6B90, func_060D6B90);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6BA8, func_060D6BA8);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6BC0, func_060D6BC0);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6BCC, func_060D6BCC);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6BE4, func_060D6BE4);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6BFC, func_060D6BFC);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6C14, func_060D6C14);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6C2C, func_060D6C2C);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6C44, func_060D6C44);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6C5C, func_060D6C5C);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6C74, func_060D6C74);
INCLUDE_ASM("asm/saturn/weapon/w_30/f_nonmat", f60D6C8C, func_060D6C8C);

s8 DAT_060D6CA0[29][4] = {
    {0, 0, 0, 0},     {9, -26, 14, 6},   {-16, -23, 14, 6}, {24, -3, 30, 11},
    {59, -14, 36, 6}, {35, -18, 25, 7},  {23, -16, 14, 8},  {6, -10, 14, 8},
    {-40, -31, 0, 0}, {-23, -4, 13, 4},  {18, 16, 39, 12},  {49, 5, 36, 7},
    {23, -1, 18, 4},  {5, 2, 15, 7},     {19, 22, 38, 12},  {46, 29, 23, 13},
    {44, 23, 23, 13}, {30, 8, 28, 6},    {9, 5, 23, 6},     {28, -4, 48, 14},
    {41, -17, 45, 6}, {-10, -26, 10, 5}, {33, 11, 43, 19},  {41, 10, 35, 16},
    {26, -10, 25, 5}, {1, 0, 10, 23},    {-2, 6, 14, 15},   {-2, 0, 9, 11},
    {0, 0, 14, 4}};

u16 DAT_060D6D14[14] = {0x0201, 0x0402, 0x0603, 0x0804, 0x0805, 0x0806, 0x0A07,
                        0x0C08, 0x0E09, 0x100A, 0x100B, 0x100C, 0x100D, 0xFFFF};

u16 DAT_060D6D30[14] = {0x0E0E, 0x120F, 0x1410, 0x1611, 0x1612, 0x1613, 0x1814,
                        0x1A15, 0x1A16, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF};

u16 DAT_060D6D4C[13] = {0x0E0E, 0x120F, 0x1C17, 0x1E18, 0x2019, 0x221A, 0x241B,
                        0x241C, 0x101D, 0x101E, 0x101F, 0x1020, 0xFFFF};

u16 DAT_060D6D66[14] = {0x0221, 0x0422, 0x2623, 0x0824, 0x0825, 0x2826, 0x0A27,
                        0x0C28, 0x0E29, 0x102A, 0x102B, 0x102C, 0x102D, 0xFFFF};

u16 DAT_060D6D82[14] = {0x2A2E, 0x042F, 0x2630, 0x2831, 0x2832, 0x2833, 0x0A34,
                        0x0C35, 0x0E36, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF};

u16 DAT_060D6D9E[13] = {0x2A2E, 0x042F, 0x2C37, 0x2E38, 0x2E39, 0x303A, 0x303B,
                        0x0E3C, 0x103D, 0x103E, 0x103F, 0x1040, 0xFFFF};

u16* DAT_060D6DB8[7] = {DAT_060D6D14, DAT_060D6D14, DAT_060D6D30, DAT_060D6D4C,
                        DAT_060D6D66, DAT_060D6D82, DAT_060D6D9E};

WeaponAnimation DAT_060D6DD4[1] = {
    {(u16**)DAT_060D6DB8, (s8*)DAT_060D6CA0, 0x0000, 0x062C, 0x60, 0x04, 0},
};

u32 DAT_060D6DE4[16] = {
    0x05040603, 0x0702010B, 0x0C0A0D09, 0x0E080000, 0x00000000, 0x00010101,
    0x01020203, 0x03040405, 0xFFFEE800, 0xFFFF1000, 0x02020202, 0x02020000,
    0x03030202, 0x0506FFF4, 0x000C0000, 0x00000000,
};

SaturnSpriteImage DAT_060D6E24[48] = {
    {20, 8, 0x0000},  {52, 11, 0x0028}, {36, 3, 0x00B8},  {36, 5, 0x00D4},
    {36, 8, 0x0104},  {20, 5, 0x014C},  {28, 8, 0x0168},  {40, 19, 0x01A0},
    {32, 16, 0x0260}, {20, 2, 0x02E0},  {24, 7, 0x02EC},  {24, 2, 0x0318},
    {16, 2, 0x0324},  {12, 15, 0x032C}, {12, 7, 0x035C},  {12, 8, 0x0374},
    {12, 15, 0x038C}, {12, 11, 0x03BC}, {8, 11, 0x03E0},  {12, 11, 0x03F8},
    {8, 15, 0x041C},  {8, 6, 0x043C},   {8, 15, 0x0448},  {16, 2, 0x0468},
    {8, 11, 0x0470},  {16, 18, 0x0488}, {16, 3, 0x04D0},  {16, 14, 0x04DC},
    {8, 4, 0x0514},   {20, 11, 0x051C}, {12, 5, 0x0554},  {16, 15, 0x0564},
    {16, 23, 0x05A0}, {4, 3, 0x05FC},   {4, 3, 0x0600},   {4, 3, 0x0604},
    {4, 3, 0x0608},   {4, 3, 0x060C},   {16, 7, 0x0610},  {4, 3, 0x062C},
    {4, 3, 0x0630},   {16, 11, 0x0634}, {20, 11, 0x0660}, {4, 5, 0x0698},
    {4, 3, 0x06A0},   {8, 33, 0x06A4},  {24, 19, 0x06E8}, {0, 0, 0x075C},
};

struct {
    u16 countAndFlags;
    u16 colors[30][16];
    u16 padding[1];
} DAT_060D6EE4 = {
    0x001E,
    {
        {0x8982, 0x8421, 0x84CA, 0x952F, 0xA173, 0x9218, 0x9EDF, 0xA0A4, 0x83E0,
         0xBBF6, 0x8623, 0x885F, 0xC5A7, 0xDA4F, 0xDF37, 0xEF99},
        {0x9E00, 0xB033, 0xB053, 0xB473, 0xB893, 0xBCD3, 0xC0F4, 0xC514, 0xC954,
         0xCD74, 0xD195, 0xD5D5, 0xD9F5, 0xDE15, 0xE256, 0xCED9},
        {0xDCF0, 0xA4EC, 0xAD71, 0xADF6, 0xA400, 0xC000, 0xE0A8, 0xA219, 0xAED9,
         0x8D73, 0x9084, 0xA128, 0xB1AD, 0xCA50, 0xDAD5, 0xE77A},
        {0xB4CE, 0x88EC, 0x9D72, 0xADF6, 0xA400, 0xC000, 0xE0A8, 0x8E58, 0xAED9,
         0x818F, 0x9084, 0x956B, 0xA5D1, 0xBA55, 0xC2B9, 0xCF3E},
        {0xD4F0, 0x88EC, 0x9D72, 0xADF6, 0xA400, 0xC821, 0xE0E8, 0x91F6, 0xAAD8,
         0x8550, 0x9084, 0xA128, 0xB1AD, 0xCA50, 0xDAD5, 0xE77A},
        {0xDD50, 0x8929, 0x9DB0, 0xAE33, 0x9800, 0xB000, 0xD065, 0xA959, 0xCA59,
         0x9093, 0x9084, 0xA108, 0xB18C, 0xC210, 0xD694, 0xE739},
        {0x8280, 0x88EC, 0x81D2, 0x81F6, 0x9462, 0xA504, 0xB968, 0xD5AC, 0x843E,
         0x8000, 0x9084, 0xA128, 0xB1AD, 0xCA50, 0xDAD5, 0xE77A},
        {0xC5CC, 0x8D2F, 0x91D6, 0xAE9C, 0xC400, 0xD400, 0xFCA8, 0x969B, 0xAF7E,
         0x8CC8, 0x8421, 0xF39C, 0xC210, 0xDEF7, 0xC2F7, 0xD77B},
        {0x8000, 0x8421, 0x84CA, 0x952F, 0xA173, 0x9218, 0x9EDF, 0xA0A4, 0x83E0,
         0xBBF6, 0x8623, 0x885F, 0xC5A7, 0xDA4F, 0xDF37, 0xEF99},
        {0x8000, 0xB033, 0xB053, 0xB473, 0xB893, 0xBCD3, 0xC0F4, 0xC514, 0xC954,
         0xCD74, 0xD195, 0xD5D5, 0xD9F5, 0xDE15, 0xE256, 0xCED9},
        {0x8000, 0x90C7, 0x94E8, 0x9909, 0x9D4B, 0xA16C, 0xA5AE, 0xA9CF, 0xB211,
         0xB632, 0xBA53, 0xBE95, 0xC2B6, 0xC6F8, 0xCB19, 0xD35B},
        {0x8000, 0x88EC, 0x9FFF, 0xAF3F, 0x801F, 0x801F, 0x801F, 0x801F, 0x843E,
         0x88A9, 0x8869, 0x8D0F, 0x899F, 0x92DF, 0xC7BF, 0xE7FF},
        {0x8000, 0xA4EC, 0xAD71, 0xADF6, 0xA400, 0xC000, 0xE0A8, 0xA219, 0xAED9,
         0x8D73, 0x9084, 0xA128, 0xB1AD, 0xCA50, 0xDAD5, 0xE77A},
        {0x8000, 0xA4EC, 0xAD71, 0xADF6, 0x90A4, 0x9CE4, 0xA521, 0x8E58, 0xAED9,
         0x818F, 0x9084, 0x956B, 0xA9CF, 0xBE54, 0xCAB7, 0xDB3C},
        {0x8000, 0x88EC, 0x9D72, 0xADF6, 0xA400, 0xC000, 0xE0A8, 0x8E58, 0xAED9,
         0x818F, 0x9084, 0x956B, 0xA5D1, 0xBA55, 0xC2B9, 0xCF3E},
        {0x8000, 0x88EC, 0x9D72, 0xADF6, 0x88A5, 0x9D04, 0x9961, 0x8EFF, 0xAED9,
         0x8158, 0x9084, 0x956B, 0xA5D1, 0xBA55, 0xC2B9, 0xCF3E},
        {0x8000, 0x88EC, 0x9D72, 0xADF6, 0xA400, 0xC821, 0xE0E8, 0x91F6, 0xAAD8,
         0x8550, 0x9084, 0xA128, 0xB1AD, 0xCA50, 0xDAD5, 0xE77A},
        {0x8000, 0x88EC, 0x9D72, 0xADF6, 0x90A5, 0xA0E6, 0xA125, 0xDD4E, 0xDA2E,
         0xB06A, 0x9084, 0x956B, 0xA5D1, 0xBA55, 0xC2B9, 0xCF3E},
        {0x8000, 0x8929, 0x9DB0, 0xAE33, 0x9800, 0xB000, 0xD065, 0xA959, 0xCA59,
         0x9093, 0x9084, 0xA108, 0xB18C, 0xC210, 0xD694, 0xE739},
        {0x8000, 0x8929, 0x9DB0, 0xAE33, 0x88A5, 0x9904, 0x9941, 0x8E58, 0xAED9,
         0x818F, 0x9084, 0x956B, 0xA5D1, 0xBA55, 0xCEB7, 0xE739},
        {0x8000, 0x88EC, 0x81D2, 0x81F6, 0x9462, 0xA504, 0xB968, 0xD5AC, 0x843E,
         0x8000, 0x9084, 0xA128, 0xB1AD, 0xCA50, 0xDAD5, 0xE77A},
        {0x8000, 0x88EC, 0x9D72, 0xADF6, 0xA400, 0xC000, 0xE0A8, 0xE983, 0x843E,
         0x8000, 0x9084, 0xA128, 0xB1AD, 0xCA50, 0xDAD5, 0xE77A},
        {0x8000, 0x8D2F, 0x91D6, 0xAE9C, 0xC400, 0xD400, 0xFCA8, 0x969B, 0xAF7E,
         0x8CC8, 0x8421, 0xF39C, 0xC210, 0xDEF7, 0xC2F7, 0xD77B},
        {0x8000, 0x88EC, 0x9D72, 0xAE16, 0x94E5, 0xA146, 0xA1A6, 0x969B, 0xAF7E,
         0x8CC8, 0x8000, 0xF39C, 0xC210, 0xDEF7, 0xC2F7, 0xD77B},
        {0x8000, 0x8000, 0xBCE7, 0xEDC5, 0x843E, 0x843E, 0x843E, 0x801F, 0xFFE0,
         0x98B5, 0x8869, 0x8D0F, 0x9DBF, 0xAABF, 0xCFBF, 0xEBDF},
        {0x8000, 0x8000, 0xBCE7, 0xEDC5, 0x801F, 0x801F, 0x801F, 0x801F, 0xFFE0,
         0x98B5, 0x8869, 0x84D4, 0x899F, 0x92DF, 0xC7BF, 0xE7FF},
        {0x8000, 0x88EC, 0x9FFF, 0xAF3F, 0x801F, 0x801F, 0x801F, 0x801F, 0x843E,
         0x88A9, 0x8869, 0x8D0F, 0x899F, 0x92DF, 0xC7BF, 0xE7FF},
        {0x8000, 0x88EC, 0xAF3F, 0x9FFF, 0x801F, 0x801F, 0x801F, 0x801F, 0x803F,
         0x88B3, 0x8869, 0x8D0F, 0x899F, 0x92DF, 0xC7BF, 0xE7FF},
        {0x8000, 0x8915, 0x9E7F, 0xABDF, 0x8014, 0x801F, 0x801F, 0x801F, 0xFFE0,
         0x9866, 0x88CA, 0x8D0F, 0x899F, 0x92DF, 0xC7BF, 0xE7FF},
        {0x8000, 0xA197, 0xA71F, 0xBFFF, 0x801B, 0x801F, 0x801F, 0xB7FF, 0xCE3F,
         0x88A9, 0x8466, 0xFFFF, 0xAB3F, 0xCFFF, 0xC7BF, 0xE7FF},
    },
    {0x0000},
};

SaturnSpriteFrameHeader DAT_060D72A8 = {0x0000, 0x0000};

SaturnSpriteFrame1 DAT_060D72AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -25, 0},
    },
};

SaturnSpriteFrame1 DAT_060D72B8 = {
    {0x0100, 0x0000},
    {
        {0x0010, -24, -24, 0},
    },
};

SaturnSpriteFrame2 DAT_060D72C4 = {
    {0x0200, 0x0000},
    {
        {0x0100, 34, -2, 1},
        {0x0000, 58, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D72D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 58, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D72E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 58, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 55, -15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D72FC = {
    {0x0100, 0x0000},
    {
        {0x0000, 34, -16, 4},
    },
};

SaturnSpriteFrame1 DAT_060D7308 = {
    {0x0100, 0x0000},
    {
        {0x0000, 24, -17, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7314 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -14, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7320 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D732C = {
    {0x0100, 0x0000},
    {
        {0x0000, -13, -8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7338 = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7344 = {
    {0x0100, 0x0000},
    {
        {0x0000, -18, -6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7350 = {
    {0x0100, 0x0000},
    {
        {0x0000, 8, -10, 0},
    },
};

SaturnSpriteFrame1 DAT_060D735C = {
    {0x0100, 0x0000},
    {
        {0x0010, -30, -5, 0},
    },
};

SaturnSpriteFrame2 DAT_060D7368 = {
    {0x0200, 0x0000},
    {
        {0x0100, 24, 15, 1},
        {0x0000, 48, 5, 2},
    },
};

SaturnSpriteFrame1 DAT_060D737C = {
    {0x0100, 0x0000},
    {
        {0x0000, 49, 4, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7388 = {
    {0x0100, 0x0000},
    {
        {0x0000, 49, 4, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7394 = {
    {0x0100, 0x0000},
    {
        {0x0000, 45, 2, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 23, 1, 6},
    },
};

SaturnSpriteFrame1 DAT_060D73AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, 1, 0},
    },
};

SaturnSpriteFrame1 DAT_060D73B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 0, 4, 0},
    },
};

SaturnSpriteFrame2 DAT_060D73C4 = {
    {0x0200, 0x0000},
    {
        {0x0100, 16, 16, 7},
        {0x0000, 42, 28, 8},
    },
};

SaturnSpriteFrame1 DAT_060D73D8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 43, 27, 8},
    },
};

SaturnSpriteFrame1 DAT_060D73E4 = {
    {0x0100, 0x0000},
    {
        {0x0000, 42, 21, 8},
    },
};

SaturnSpriteFrame1 DAT_060D73F0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 26, 9, 3},
    },
};

SaturnSpriteFrame1 DAT_060D73FC = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, 5, 9},
    },
};

SaturnSpriteFrame1 DAT_060D7408 = {
    {0x0100, 0x0000},
    {
        {0x0000, 9, 4, 9},
    },
};

SaturnSpriteFrame1 DAT_060D7414 = {
    {0x0100, 0x0000},
    {
        {0x0000, -9, 6, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7420 = {
    {0x0100, 0x0000},
    {
        {0x0000, -11, 7, 5},
    },
};

SaturnSpriteFrame1 DAT_060D742C = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, 8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7438 = {
    {0x0100, 0x0000},
    {
        {0x0000, -15, 9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D7444 = {
    {0x0100, 0x0000},
    {
        {0x0000, 13, -27, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7450 = {
    {0x0100, 0x0000},
    {
        {0x0010, -26, -26, 0},
    },
};

SaturnSpriteFrame2 DAT_060D745C = {
    {0x0200, 0x0000},
    {
        {0x0100, 35, -2, 1},
        {0x0000, 55, -14, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7470 = {
    {0x0100, 0x0000},
    {
        {0x0000, 56, -15, 2},
    },
};

SaturnSpriteFrame1 DAT_060D747C = {
    {0x0100, 0x0000},
    {
        {0x0000, 56, -15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7488 = {
    {0x0100, 0x0000},
    {
        {0x0000, 49, -17, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7494 = {
    {0x0100, 0x0000},
    {
        {0x0000, 29, -16, 6},
    },
};

SaturnSpriteFrame1 DAT_060D74A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 22, -19, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74AC = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -16, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -8, -12, 5},
    },
};

SaturnSpriteFrame1 DAT_060D74C4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -11, 5},
    },
};

SaturnSpriteFrame1 DAT_060D74D0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D74DC = {
    {0x0100, 0x0000},
    {
        {0x0000, -16, -9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D74E8 = {
    {0x0100, 0x0000},
    {
        {0x0000, 4, -29, 0},
    },
};

SaturnSpriteFrame1 DAT_060D74F4 = {
    {0x0100, 0x0000},
    {
        {0x0010, -35, -27, 0},
    },
};

SaturnSpriteFrame2 DAT_060D7500 = {
    {0x0200, 0x0000},
    {
        {0x0100, 28, -2, 1},
        {0x0000, 50, -12, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7514 = {
    {0x0100, 0x0000},
    {
        {0x0000, 51, -13, 2},
    },
};

SaturnSpriteFrame1 DAT_060D7520 = {
    {0x0100, 0x0000},
    {
        {0x0000, 51, -13, 3},
    },
};

SaturnSpriteFrame1 DAT_060D752C = {
    {0x0100, 0x0000},
    {
        {0x0000, 46, -15, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7538 = {
    {0x0100, 0x0000},
    {
        {0x0000, 28, -17, 10},
    },
};

SaturnSpriteFrame1 DAT_060D7544 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -18, 0},
    },
};

SaturnSpriteFrame1 DAT_060D7550 = {
    {0x0100, 0x0000},
    {
        {0x0000, 10, -17, 0},
    },
};

SaturnSpriteFrame2 DAT_060D755C = {
    {0x0200, 0x0000},
    {
        {0x0104, 30, 6, 7},
        {0x0000, 59, 17, 8},
    },
};

SaturnSpriteFrame1 DAT_060D7570 = {
    {0x0100, 0x0000},
    {
        {0x0000, 59, 17, 8},
    },
};

SaturnSpriteFrame1 DAT_060D757C = {
    {0x0100, 0x0000},
    {
        {0x0000, 59, 17, 8},
    },
};

SaturnSpriteFrame1 DAT_060D7588 = {
    {0x0100, 0x0000},
    {
        {0x0000, 31, -7, 3},
    },
};

SaturnSpriteFrame1 DAT_060D7594 = {
    {0x0100, 0x0000},
    {
        {0x0000, 17, -10, 11},
    },
};

SaturnSpriteFrame1 DAT_060D75A0 = {
    {0x0100, 0x0000},
    {
        {0x0000, 16, -12, 12},
    },
};

SaturnSpriteFrame1 DAT_060D75AC = {
    {0x0100, 0x0000},
    {
        {0x0000, -7, -10, 5},
    },
};

SaturnSpriteFrame1 DAT_060D75B8 = {
    {0x0100, 0x0000},
    {
        {0x0000, -10, -9, 5},
    },
};

SaturnSpriteFrame1 DAT_060D75C4 = {
    {0x0100, 0x0000},
    {
        {0x0000, -12, -8, 5},
    },
};

SaturnSpriteFrame1 DAT_060D75D0 = {
    {0x0100, 0x0000},
    {
        {0x0000, -14, -7, 5},
    },
};

SaturnSpriteFrame7 DAT_060D75DC = {
    {0x0700, 0x0000},
    {
        {0x0200, -6, -4, 13},
        {0x0200, -17, 12, 14},
        {0x0200, 24, -16, 15},
        {0x0200, 7, 9, 16},
        {0x0200, 1, -13, 17},
        {0x0200, 7, -10, 18},
        {0x0200, 7, -2, 19},
    },
};

SaturnSpriteFrame7 DAT_060D7618 = {
    {0x0700, 0x0000},
    {
        {0x0200, -7, -5, 13},
        {0x0200, -18, 11, 14},
        {0x0200, 23, -17, 15},
        {0x0200, 7, 9, 16},
        {0x0200, 1, -14, 17},
        {0x0200, 8, -11, 18},
        {0x0200, 8, -1, 19},
    },
};

SaturnSpriteFrame7 DAT_060D7654 = {
    {0x0700, 0x0000},
    {
        {0x0200, -8, -5, 13},
        {0x0200, -19, 11, 14},
        {0x0200, 22, -17, 15},
        {0x0200, 5, 9, 20},
        {0x0200, 1, -14, 17},
        {0x0200, 9, -11, 18},
        {0x0200, 9, -2, 19},
    },
};

SaturnSpriteFrame7 DAT_060D7690 = {
    {0x0700, 0x0000},
    {
        {0x0200, -7, -4, 13},
        {0x0200, -18, 12, 14},
        {0x0200, 23, -16, 15},
        {0x0200, 5, 9, 20},
        {0x0200, 1, -13, 17},
        {0x0200, 8, -10, 18},
        {0x0200, 8, -3, 19},
    },
};

SaturnSpriteFrame6 DAT_060D76CC = {
    {0x0600, 0x0000},
    {
        {0x0300, -6, -4, 13},
        {0x0300, -17, 12, 14},
        {0x0300, 24, -16, 15},
        {0x0300, 7, 9, 16},
        {0x0300, 1, -13, 17},
        {0x0300, 7, -10, 18},
    },
};

SaturnSpriteFrame6 DAT_060D7700 = {
    {0x0600, 0x0000},
    {
        {0x0300, -7, -5, 13},
        {0x0300, -18, 11, 14},
        {0x0300, 23, -17, 15},
        {0x0300, 7, 9, 16},
        {0x0300, 1, -14, 17},
        {0x0300, 8, -11, 18},
    },
};

SaturnSpriteFrame6 DAT_060D7734 = {
    {0x0600, 0x0000},
    {
        {0x0300, -8, -5, 13},
        {0x0300, -19, 11, 14},
        {0x0300, 22, -17, 15},
        {0x0300, 5, 9, 20},
        {0x0300, 1, -14, 17},
        {0x0300, 9, -11, 18},
    },
};

SaturnSpriteFrame6 DAT_060D7768 = {
    {0x0600, 0x0000},
    {
        {0x0300, -7, -4, 13},
        {0x0300, -18, 12, 14},
        {0x0300, 23, -16, 15},
        {0x0300, 5, 9, 20},
        {0x0300, 1, -13, 17},
        {0x0300, 8, -10, 18},
    },
};

SaturnSpriteFrame7 DAT_060D779C = {
    {0x0700, 0x0000},
    {
        {0x0400, -3, -13, 21},
        {0x0400, -16, -32, 22},
        {0x0420, -16, -2, 22},
        {0x0400, -11, -16, 23},
        {0x0400, 4, -13, 24},
        {0x0400, 2, 6, 25},
        {0x0400, -10, -17, 26},
    },
};

SaturnSpriteFrame7 DAT_060D77D8 = {
    {0x0700, 0x0000},
    {
        {0x0400, -1, -12, 21},
        {0x0400, -15, -32, 22},
        {0x0420, -15, -2, 22},
        {0x0400, -11, -16, 23},
        {0x0400, 4, -13, 24},
        {0x0400, 2, 6, 25},
        {0x0400, -9, -17, 26},
    },
};

SaturnSpriteFrame7 DAT_060D7814 = {
    {0x0700, 0x0000},
    {
        {0x0400, -4, -11, 21},
        {0x0400, -14, -32, 22},
        {0x0420, -14, -2, 22},
        {0x0400, -11, -16, 23},
        {0x0400, 4, -13, 24},
        {0x0400, 2, 6, 25},
        {0x0400, -8, -17, 26},
    },
};

SaturnSpriteFrame7 DAT_060D7850 = {
    {0x0700, 0x0000},
    {
        {0x0400, 4, -11, 21},
        {0x0400, -6, -29, 27},
        {0x0420, -7, -3, 27},
        {0x0400, -11, -16, 23},
        {0x0400, 4, -13, 24},
        {0x0400, 2, 6, 25},
        {0x0400, -9, -17, 26},
    },
};

SaturnSpriteFrame7 DAT_060D788C = {
    {0x0700, 0x0000},
    {
        {0x0400, 6, -11, 21},
        {0x0400, -4, -29, 27},
        {0x0420, -5, -3, 27},
        {0x0400, -11, -16, 23},
        {0x0400, 4, -13, 24},
        {0x0400, 2, 6, 25},
        {0x0400, -8, -17, 26},
    },
};

SaturnSpriteFrame6 DAT_060D78C8 = {
    {0x0600, 0x0000},
    {
        {0x0400, 5, -11, 21},
        {0x0410, -27, -32, 22},
        {0x0430, -27, -2, 22},
        {0x0400, 3, -13, 24},
        {0x0400, 1, 6, 25},
        {0x0400, -9, -17, 26},
    },
};

SaturnSpriteFrame6 DAT_060D78FC = {
    {0x0600, 0x0000},
    {
        {0x0400, 5, -11, 21},
        {0x0400, -14, -32, 22},
        {0x0420, -14, -2, 22},
        {0x0400, 3, -13, 24},
        {0x0400, 1, 6, 25},
        {0x0400, -9, -17, 26},
    },
};

SaturnSpriteFrame6 DAT_060D7930 = {
    {0x0600, 0x0000},
    {
        {0x0400, -14, -32, 22},
        {0x0420, -14, -2, 22},
        {0x0200, 16, -14, 28},
        {0x0400, 4, -13, 24},
        {0x0400, 1, 6, 25},
        {0x0400, -9, -17, 26},
    },
};

SaturnSpriteFrame7 DAT_060D7964 = {
    {0x0700, 0x0000},
    {
        {0x0500, -1, 1, 21},
        {0x0500, -15, -20, 22},
        {0x0520, -15, 10, 22},
        {0x0500, -1, 13, 29},
        {0x0500, -11, -3, 23},
        {0x0500, 2, -1, 24},
        {0x0500, -10, -4, 26},
    },
};

SaturnSpriteFrame7 DAT_060D79A0 = {
    {0x0700, 0x0000},
    {
        {0x0500, -5, 1, 21},
        {0x0500, -14, -20, 22},
        {0x0520, -14, 10, 22},
        {0x0500, -1, 13, 29},
        {0x0500, -11, -3, 23},
        {0x0500, 2, -1, 24},
        {0x0500, -9, -4, 26},
    },
};

SaturnSpriteFrame7 DAT_060D79DC = {
    {0x0700, 0x0000},
    {
        {0x0500, -6, 2, 21},
        {0x0500, -13, -20, 22},
        {0x0520, -13, 10, 22},
        {0x0500, -1, 13, 29},
        {0x0500, -11, -3, 23},
        {0x0500, 2, -1, 24},
        {0x0500, -8, -4, 26},
    },
};

SaturnSpriteFrame7 DAT_060D7A18 = {
    {0x0700, 0x0000},
    {
        {0x0500, 2, 2, 21},
        {0x0500, -7, -15, 27},
        {0x0520, -7, 9, 27},
        {0x0500, -1, 13, 29},
        {0x0500, -11, -3, 23},
        {0x0500, 2, -1, 24},
        {0x0500, -9, -4, 26},
    },
};

SaturnSpriteFrame7 DAT_060D7A54 = {
    {0x0700, 0x0000},
    {
        {0x0500, 4, 2, 21},
        {0x0500, -6, -15, 27},
        {0x0520, -6, 9, 27},
        {0x0500, -1, 13, 29},
        {0x0500, -12, -3, 23},
        {0x0500, 2, -1, 24},
        {0x0500, -9, -4, 26},
    },
};

SaturnSpriteFrame6 DAT_060D7A90 = {
    {0x0600, 0x0000},
    {
        {0x0500, -1, 3, 21},
        {0x0510, -28, -20, 22},
        {0x0530, -28, 10, 22},
        {0x0500, -2, 13, 29},
        {0x0500, 1, -1, 24},
        {0x0500, -10, -3, 26},
    },
};

SaturnSpriteFrame6 DAT_060D7AC4 = {
    {0x0600, 0x0000},
    {
        {0x0500, -1, 3, 21},
        {0x0500, -17, -20, 22},
        {0x0520, -17, 10, 22},
        {0x0500, -2, 13, 29},
        {0x0500, 1, -1, 24},
        {0x0500, -10, -3, 26},
    },
};

SaturnSpriteFrame6 DAT_060D7AF8 = {
    {0x0600, 0x0000},
    {
        {0x0500, -17, -20, 22},
        {0x0520, -17, 10, 22},
        {0x0500, -1, 13, 29},
        {0x0500, 2, -1, 24},
        {0x0500, -10, -3, 26},
        {0x0500, 15, -3, 28},
    },
};

SaturnSpriteFrame2 DAT_060D7B2C = {
    {0x0200, 0x0000},
    {
        {0x0600, 1, 19, 30},
        {0x0600, -1, 0, 31},
    },
};

SaturnSpriteFrame2 DAT_060D7B40 = {
    {0x0200, 0x0000},
    {
        {0x0600, 1, 19, 30},
        {0x0600, -1, 1, 31},
    },
};

SaturnSpriteFrame2 DAT_060D7B54 = {
    {0x0200, 0x0000},
    {
        {0x0600, 1, 19, 30},
        {0x0600, -1, 2, 31},
    },
};

SaturnSpriteFrame4 DAT_060D7B68 = {
    {0x0400, 0x0000},
    {
        {0x0700, 6, 0, 32},
        {0x0700, 18, -17, 33},
        {0x0700, -12, -17, 34},
        {0x0700, 1, -19, 35},
    },
};

SaturnSpriteFrame4 DAT_060D7B8C = {
    {0x0400, 0x0000},
    {
        {0x0700, 6, 0, 32},
        {0x0700, 18, -17, 33},
        {0x0700, -12, -17, 34},
        {0x0700, 1, -19, 36},
    },
};

SaturnSpriteFrame3 DAT_060D7BB0 = {
    {0x0300, 0x0000},
    {
        {0x0700, 6, 0, 32},
        {0x0700, -12, -17, 34},
        {0x0700, 18, -17, 33},
    },
};

SaturnSpriteFrame5 DAT_060D7BCC = {
    {0x0500, 0x0000},
    {
        {0x0700, 6, 0, 32},
        {0x0700, 18, -17, 37},
        {0x0700, 6, -16, 38},
        {0x0700, -12, -17, 39},
        {0x0200, -1, -4, 40},
    },
};

SaturnSpriteFrame3 DAT_060D7BF8 = {
    {0x0300, 0x0000},
    {
        {0x0700, 7, -9, 41},
        {0x0700, 13, 13, 42},
        {0x0700, -11, -11, 43},
    },
};

SaturnSpriteFrame4 DAT_060D7C14 = {
    {0x0400, 0x0000},
    {
        {0x0700, 13, 13, 42},
        {0x0700, 7, -9, 41},
        {0x0700, -11, -11, 43},
        {0x0700, 4, -16, 44},
    },
};

SaturnSpriteFrame4 DAT_060D7C38 = {
    {0x0400, 0x0000},
    {
        {0x0700, 13, 13, 42},
        {0x0700, 7, -9, 41},
        {0x0700, -11, -11, 43},
        {0x0700, 4, -16, 35},
    },
};

SaturnSpriteFrame3 DAT_060D7C5C = {
    {0x0300, 0x0000},
    {
        {0x0700, 12, 13, 42},
        {0x0700, 6, -9, 41},
        {0x0700, -12, -11, 43},
    },
};

SaturnSpriteFrame1 DAT_060D7C78 = {
    {0x0100, 0x0000},
    {
        {0x0400, 3, 1, 23},
    },
};

SaturnSpriteFrame1 DAT_060D7C84 = {
    {0x0100, 0x0000},
    {
        {0x0000, 2, 38, 45},
    },
};

SaturnSpriteFrame1 DAT_060D7C90 = {
    {0x0100, 0x0000},
    {
        {0x0000, -5, 32, 46},
    },
};

SaturnSpriteFrameHeader* DAT_060D7C9C[103] = {
    (SaturnSpriteFrameHeader*)&DAT_060D72A8,
    (SaturnSpriteFrameHeader*)&DAT_060D72AC,
    (SaturnSpriteFrameHeader*)&DAT_060D72B8,
    (SaturnSpriteFrameHeader*)&DAT_060D72C4,
    (SaturnSpriteFrameHeader*)&DAT_060D72D8,
    (SaturnSpriteFrameHeader*)&DAT_060D72E4,
    (SaturnSpriteFrameHeader*)&DAT_060D72F0,
    (SaturnSpriteFrameHeader*)&DAT_060D72FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7308,
    (SaturnSpriteFrameHeader*)&DAT_060D7314,
    (SaturnSpriteFrameHeader*)&DAT_060D7320,
    (SaturnSpriteFrameHeader*)&DAT_060D732C,
    (SaturnSpriteFrameHeader*)&DAT_060D7338,
    (SaturnSpriteFrameHeader*)&DAT_060D7344,
    (SaturnSpriteFrameHeader*)&DAT_060D7350,
    (SaturnSpriteFrameHeader*)&DAT_060D735C,
    (SaturnSpriteFrameHeader*)&DAT_060D7368,
    (SaturnSpriteFrameHeader*)&DAT_060D737C,
    (SaturnSpriteFrameHeader*)&DAT_060D7388,
    (SaturnSpriteFrameHeader*)&DAT_060D7394,
    (SaturnSpriteFrameHeader*)&DAT_060D73A0,
    (SaturnSpriteFrameHeader*)&DAT_060D73AC,
    (SaturnSpriteFrameHeader*)&DAT_060D73B8,
    (SaturnSpriteFrameHeader*)&DAT_060D73C4,
    (SaturnSpriteFrameHeader*)&DAT_060D73D8,
    (SaturnSpriteFrameHeader*)&DAT_060D73E4,
    (SaturnSpriteFrameHeader*)&DAT_060D73F0,
    (SaturnSpriteFrameHeader*)&DAT_060D73FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7408,
    (SaturnSpriteFrameHeader*)&DAT_060D7414,
    (SaturnSpriteFrameHeader*)&DAT_060D7420,
    (SaturnSpriteFrameHeader*)&DAT_060D742C,
    (SaturnSpriteFrameHeader*)&DAT_060D7438,
    (SaturnSpriteFrameHeader*)&DAT_060D7444,
    (SaturnSpriteFrameHeader*)&DAT_060D7450,
    (SaturnSpriteFrameHeader*)&DAT_060D745C,
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
    (SaturnSpriteFrameHeader*)&DAT_060D7514,
    (SaturnSpriteFrameHeader*)&DAT_060D7520,
    (SaturnSpriteFrameHeader*)&DAT_060D752C,
    (SaturnSpriteFrameHeader*)&DAT_060D7538,
    (SaturnSpriteFrameHeader*)&DAT_060D7544,
    (SaturnSpriteFrameHeader*)&DAT_060D7550,
    (SaturnSpriteFrameHeader*)&DAT_060D755C,
    (SaturnSpriteFrameHeader*)&DAT_060D7570,
    (SaturnSpriteFrameHeader*)&DAT_060D757C,
    (SaturnSpriteFrameHeader*)&DAT_060D7588,
    (SaturnSpriteFrameHeader*)&DAT_060D7594,
    (SaturnSpriteFrameHeader*)&DAT_060D75A0,
    (SaturnSpriteFrameHeader*)&DAT_060D75AC,
    (SaturnSpriteFrameHeader*)&DAT_060D75B8,
    (SaturnSpriteFrameHeader*)&DAT_060D75C4,
    (SaturnSpriteFrameHeader*)&DAT_060D75D0,
    (SaturnSpriteFrameHeader*)&DAT_060D75DC,
    (SaturnSpriteFrameHeader*)&DAT_060D7618,
    (SaturnSpriteFrameHeader*)&DAT_060D7654,
    (SaturnSpriteFrameHeader*)&DAT_060D7690,
    (SaturnSpriteFrameHeader*)&DAT_060D76CC,
    (SaturnSpriteFrameHeader*)&DAT_060D7700,
    (SaturnSpriteFrameHeader*)&DAT_060D7734,
    (SaturnSpriteFrameHeader*)&DAT_060D7768,
    (SaturnSpriteFrameHeader*)&DAT_060D779C,
    (SaturnSpriteFrameHeader*)&DAT_060D77D8,
    (SaturnSpriteFrameHeader*)&DAT_060D7814,
    (SaturnSpriteFrameHeader*)&DAT_060D7850,
    (SaturnSpriteFrameHeader*)&DAT_060D788C,
    (SaturnSpriteFrameHeader*)&DAT_060D78C8,
    (SaturnSpriteFrameHeader*)&DAT_060D78FC,
    (SaturnSpriteFrameHeader*)&DAT_060D7930,
    (SaturnSpriteFrameHeader*)&DAT_060D7964,
    (SaturnSpriteFrameHeader*)&DAT_060D79A0,
    (SaturnSpriteFrameHeader*)&DAT_060D79DC,
    (SaturnSpriteFrameHeader*)&DAT_060D7A18,
    (SaturnSpriteFrameHeader*)&DAT_060D7A54,
    (SaturnSpriteFrameHeader*)&DAT_060D7A90,
    (SaturnSpriteFrameHeader*)&DAT_060D7AC4,
    (SaturnSpriteFrameHeader*)&DAT_060D7AF8,
    (SaturnSpriteFrameHeader*)&DAT_060D7B2C,
    (SaturnSpriteFrameHeader*)&DAT_060D7B40,
    (SaturnSpriteFrameHeader*)&DAT_060D7B54,
    (SaturnSpriteFrameHeader*)&DAT_060D7B68,
    (SaturnSpriteFrameHeader*)&DAT_060D7B8C,
    (SaturnSpriteFrameHeader*)&DAT_060D7BB0,
    (SaturnSpriteFrameHeader*)&DAT_060D7BCC,
    (SaturnSpriteFrameHeader*)&DAT_060D7BF8,
    (SaturnSpriteFrameHeader*)&DAT_060D7C14,
    (SaturnSpriteFrameHeader*)&DAT_060D7C38,
    (SaturnSpriteFrameHeader*)&DAT_060D7C5C,
    (SaturnSpriteFrameHeader*)&DAT_060D7C78,
    (SaturnSpriteFrameHeader*)&DAT_060D7C84,
    (SaturnSpriteFrameHeader*)&DAT_060D7C90,
};

SaturnSpriteResource DAT_060D7E38 = {
    DAT_060D6E24, (u16*)&DAT_060D6EE4, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D7E44[1] = {&DAT_060D7E38};
