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
extern SaturnSpriteResource* DAT_060D6B8C[];

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
    DAT_060D6B8C,
};

u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {
    0x484C4100, 0x00000000, 0x1C4C4100, 0x00000000,
    0xF04B4100, 0x00000000, 0xC44B4100};

INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D6060, func_060D6060);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D6128, func_060D6128);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D68AC, func_060D68AC);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D68C4, func_060D68C4);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D68DC, func_060D68DC);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D68F4, func_060D68F4);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D690C, func_060D690C);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D6924, func_060D6924);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D6930, func_060D6930);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D6948, func_060D6948);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D6960, func_060D6960);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D6978, func_060D6978);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D6990, func_060D6990);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D69A8, func_060D69A8);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D69C0, func_060D69C0);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D69D8, func_060D69D8);
INCLUDE_ASM("asm/saturn/weapon/w_59/f_nonmat", f60D69F0, func_060D69F0);

u16 DAT_060D6A00[156] = {
    0x0050, 0x0040, 0x0064, 0x0020, 0x0078, 0x0040, 0x0064, 0x0020, 0x0078,
    0x0009, 0x0095, 0x0020, 0x0064, 0x0020, 0x0095, 0x0020, 0x0078, 0x0040,
    0x0078, 0x0040, 0x0095, 0x0020, 0x009F, 0x0040, 0x0050, 0x0040, 0x003C,
    0x0020, 0x0064, 0x0020, 0x003C, 0x0020, 0x0028, 0x0009, 0x0050, 0x0000,
    0x003C, 0x0020, 0x0050, 0x0000, 0x0064, 0x0020, 0x0064, 0x0020, 0x0050,
    0x0000, 0x0078, 0x0009, 0x0050, 0x0040, 0x0028, 0x0040, 0x003C, 0x0020,
    0x0028, 0x0040, 0x0000, 0x0040, 0x000B, 0x0020, 0x0028, 0x0040, 0x000B,
    0x0020, 0x003C, 0x0020, 0x003C, 0x0020, 0x000B, 0x0020, 0x0028, 0x0009,
    0x0050, 0x0040, 0x003C, 0x0060, 0x0028, 0x0040, 0x003C, 0x0060, 0x0028,
    0x0077, 0x000B, 0x0060, 0x003C, 0x0060, 0x000B, 0x0060, 0x0028, 0x0040,
    0x0028, 0x0040, 0x000B, 0x0060, 0x0000, 0x0040, 0x0050, 0x0040, 0x0064,
    0x0060, 0x003C, 0x0060, 0x0064, 0x0060, 0x0078, 0x0077, 0x0050, 0x007F,
    0x0064, 0x0060, 0x0050, 0x007F, 0x003C, 0x0060, 0x003C, 0x0060, 0x0050,
    0x007F, 0x0028, 0x0077, 0x0050, 0x0040, 0x0078, 0x0040, 0x0064, 0x0060,
    0x0078, 0x0040, 0x009F, 0x0040, 0x0095, 0x0060, 0x0078, 0x0040, 0x0095,
    0x0060, 0x0064, 0x0060, 0x0064, 0x0060, 0x0095, 0x0060, 0x0064, 0x0077,
    0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x801F,
    0xFC00, 0x83E0, 0xFFFF,
};

SaturnSpriteImage DAT_060D6B38[3] = {
    {64, 64, 0x0000},
    {64, 64, 0x0400},
    {0, 0, 0x0800},
};

struct {
    u16 countAndFlags;
    u16 colors[1][16];
    u16 padding[1];
} DAT_060D6B44 = {
    0x0001,
    {
        {0xC800, 0x98C6, 0xA108, 0xA529, 0xA94A, 0xAD6B, 0xB18C, 0xB9CE, 0xBDEF,
         0xC210, 0xC631, 0xCE73, 0xD294, 0xD6B5, 0xDAD6, 0xDEF7},
    },
    {0x0000},
};

u32 DAT_060D6B68[6] = {
    0x00000000, 0x01000000, 0x00000000, 0x00000000, 0x060D6B68, 0x060D6B6C,
};

SaturnSpriteResource DAT_060D6B80 = {
    DAT_060D6B38, (u16*)&DAT_060D6B44, 0xFFFF, 0xFFFF};

SaturnSpriteResource* DAT_060D6B8C[1] = {&DAT_060D6B80};
