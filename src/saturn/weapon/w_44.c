// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D6950();
void func_060D6968();
void func_060D6980();
void func_060D6998();
void func_060D69B0();
void func_060D69C8();
void func_060D69D4();
void func_060D69EC();
void func_060D6A04();
void func_060D6A1C();
void func_060D6A34();
void func_060D6A4C();
void func_060D6A64();
void func_060D6A7C();
void func_060D6A94();
extern SaturnSpriteResource* DAT_060D6CDC[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D6950,
        func_060D6968,
        func_060D6980,
        func_060D6998,
        func_060D69B0,
        func_060D69C8,
        func_060D6A94,
        func_060D69D4,
        func_060D69EC,
        func_060D6A04,
        func_060D6A1C,
        func_060D6A34,
        func_060D6A4C,
        func_060D6A64,
        func_060D6A7C,
    },
    DAT_060D6CDC,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6950, func_060D6950);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6968, func_060D6968);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6980, func_060D6980);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6998, func_060D6998);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D69B0, func_060D69B0);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D69C8, func_060D69C8);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D69D4, func_060D69D4);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D69EC, func_060D69EC);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6A04, func_060D6A04);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6A1C, func_060D6A1C);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6A34, func_060D6A34);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6A4C, func_060D6A4C);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6A64, func_060D6A64);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6A7C, func_060D6A7C);
INCLUDE_ASM("asm/saturn/weapon/w_44/f_nonmat", f60D6A94, func_060D6A94);

u32 DAT_060D6AA0[16] = {
    0x00000000, 0x00000100, 0x00000200, 0x00000300, 0x00000400, 0x00000500,
    0x00000600, 0x00000700, 0x00000800, 0x00000900, 0x00000A00, 0x00000B00,
    0x00000C00, 0x00000D00, 0x00000E00, 0x00000F00,
};

SaturnSpriteImage DAT_060D6AE0[33] = {
    {4, 36, 0x0000}, {4, 36, 0x0024}, {4, 36, 0x0048}, {4, 36, 0x006C},
    {4, 36, 0x0090}, {4, 36, 0x00B4}, {4, 36, 0x00D8}, {4, 36, 0x00FC},
    {4, 36, 0x0120}, {4, 36, 0x0144}, {4, 36, 0x0168}, {4, 36, 0x018C},
    {4, 36, 0x01B0}, {4, 36, 0x01D4}, {4, 36, 0x01F8}, {4, 36, 0x021C},
    {4, 24, 0x0240}, {4, 24, 0x0258}, {4, 24, 0x0270}, {4, 24, 0x0288},
    {4, 24, 0x02A0}, {4, 24, 0x02B8}, {4, 24, 0x02D0}, {4, 24, 0x02E8},
    {4, 24, 0x0300}, {4, 24, 0x0318}, {4, 24, 0x0330}, {4, 24, 0x0348},
    {4, 24, 0x0360}, {4, 24, 0x0378}, {4, 24, 0x0390}, {36, 28, 0x03A8},
    {0, 0, 0x04A4},
};

struct {
    u16 countAndFlags;
    u16 colors[2][16];
    u16 padding[1];
} DAT_060D6B64 = {
    0x0002,
    {
        {0x81A0, 0x801F, 0x9218, 0x931F, 0x8D2D, 0x9DB4, 0xB258, 0xD2F9, 0xD4A4,
         0xFD27, 0x90C4, 0xA128, 0xB1AD, 0xCA50, 0xDAD5, 0xFB78},
        {0x81E0, 0x8002, 0x8003, 0x8005, 0x8027, 0x8028, 0x842A, 0x844C, 0x844E,
         0x844F, 0x8471, 0x8873, 0x8874, 0x8896, 0x8898, 0x8CBA},
    },
    {0x0000},
};

u32 DAT_060D6BA8[74] = {
    0x00000000, 0x10000000, 0x0000FFC4, 0xFFE40000, 0x0000FFCC, 0xFFE40001,
    0x0000FFD4, 0xFFE40002, 0x0000FFDC, 0xFFE40003, 0x0000FFE4, 0xFFE40004,
    0x0000FFEC, 0xFFE40005, 0x0000FFF4, 0xFFE40006, 0x0000FFFC, 0xFFE40007,
    0x00000004, 0xFFE40008, 0x0000000C, 0xFFE40009, 0x00000014, 0xFFE4000A,
    0x0000001C, 0xFFE4000B, 0x00000024, 0xFFE4000C, 0x0000002C, 0xFFE4000D,
    0x00000034, 0xFFE4000E, 0x0000003C, 0xFFE4000F, 0x10000000, 0x0000FFC4,
    0xFFE80010, 0x0000FFCC, 0xFFE80011, 0x0000FFD4, 0xFFE80012, 0x0000FFDC,
    0xFFE80013, 0x0000FFE4, 0xFFE80014, 0x0000FFEC, 0xFFE80015, 0x0000FFF4,
    0xFFE80016, 0x0000FFFC, 0xFFE80017, 0x00000004, 0xFFE80018, 0x0000000C,
    0xFFE80019, 0x00000014, 0xFFE8001A, 0x0000001C, 0xFFE8001B, 0x00000024,
    0xFFE8001C, 0x0000002C, 0xFFE8001D, 0x00000034, 0xFFE8001E, 0x0000003C,
    0xFFE80010, 0x01000000, 0x01000002, 0xFFE6001F, 0x060D6BA8, 0x060D6BAC,
    0x060D6C30, 0x060D6CB4,
};

SaturnSpriteResource DAT_060D6CD0 = {
    DAT_060D6AE0, (u16*)&DAT_060D6B64, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6CDC[1] = {&DAT_060D6CD0};
