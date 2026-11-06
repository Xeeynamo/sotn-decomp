// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>
#include "weapon/weapon.h"

void func_060D6128();
void func_060D68AC();
void func_060D68C4();
void func_060D68DC();
void func_060D68F4();
void func_060D690C();
void func_060D6924();
void func_060D6930();
void func_060D6948();
void func_060D6960();
void func_060D6978();
void func_060D6990();
void func_060D69A8();
void func_060D69C0();
void func_060D69D8();
void func_060D69F0();
extern SaturnSpriteResource* DAT_060D6B88[];

SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {
    {
        func_060D6128,
        func_060D68AC,
        func_060D68C4,
        func_060D68DC,
        func_060D68F4,
        func_060D690C,
        func_060D6924,
        func_060D69F0,
        func_060D6930,
        func_060D6948,
        func_060D6960,
        func_060D6978,
        func_060D6990,
        func_060D69A8,
        func_060D69C0,
        func_060D69D8,
    },
    DAT_060D6B88,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D68AC, func_060D68AC);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D68C4, func_060D68C4);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D68DC, func_060D68DC);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D68F4, func_060D68F4);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D690C, func_060D690C);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D6924, func_060D6924);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D6930, func_060D6930);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D6948, func_060D6948);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D6960, func_060D6960);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D6978, func_060D6978);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D6990, func_060D6990);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D69A8, func_060D69A8);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D69C0, func_060D69C0);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D69D8, func_060D69D8);
INCLUDE_ASM("asm/saturn/weapon/w_17/f_nonmat", f60D69F0, func_060D69F0);

u32 DAT_060D6A00[78] = {
    0x00500040, 0x00640020, 0x00780040, 0x00640020, 0x00780009, 0x00950020,
    0x00640020, 0x00950020, 0x00780040, 0x00780040, 0x00950020, 0x009F0040,
    0x00500040, 0x003C0020, 0x00640020, 0x003C0020, 0x00280009, 0x00500000,
    0x003C0020, 0x00500000, 0x00640020, 0x00640020, 0x00500000, 0x00780009,
    0x00500040, 0x00280040, 0x003C0020, 0x00280040, 0x00000040, 0x000B0020,
    0x00280040, 0x000B0020, 0x003C0020, 0x003C0020, 0x000B0020, 0x00280009,
    0x00500040, 0x003C0060, 0x00280040, 0x003C0060, 0x00280077, 0x000B0060,
    0x003C0060, 0x000B0060, 0x00280040, 0x00280040, 0x000B0060, 0x00000040,
    0x00500040, 0x00640060, 0x003C0060, 0x00640060, 0x00780077, 0x0050007F,
    0x00640060, 0x0050007F, 0x003C0060, 0x003C0060, 0x0050007F, 0x00280077,
    0x00500040, 0x00780040, 0x00640060, 0x00780040, 0x009F0040, 0x00950060,
    0x00780040, 0x00950060, 0x00640060, 0x00640060, 0x00950060, 0x00640077,
    0x00000000, 0x00010000, 0x00000000, 0xFFFF0000, 0x801FFC00, 0x83E0FFFF,
};

SaturnSpriteImage DAT_060D6B38[2] = {
    {64, 63, 0x0000},
    {0, 0, 0x03F0},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D6B40 = {
    0x0001,
    {
        {0x8140, 0x815B, 0x899B, 0x95FC, 0xA25C, 0xAE9D, 0xBAFD, 0xC75E, 0x8442,
         0x8485, 0x88E9, 0x894E, 0x8DB2, 0x8E16, 0x929B, 0xB423},
    },
    {0x0000},
};

u32 DAT_060D6B64[6] = {
    0x00000000, 0x01000000, 0x00000001, 0x00000000, 0x060D6B64, 0x060D6B68,
};

SaturnSpriteResource DAT_060D6B7C = {
    DAT_060D6B38, (u16*)&DAT_060D6B40, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6B88[1] = {&DAT_060D6B7C};
