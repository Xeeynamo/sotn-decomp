// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include <saturn_sprite.h>

s32 func_06066B30(s32 arg0, s32 arg1) {
    s32 ret;

    if (arg1 == 0) {
        ret = func_06066CE0();
    } else if (arg1 == 1) {
        ret = func_06067090();
    } else {
        ret = func_060674B8(arg0, arg1);
    }
    return ret;
}

static inline u16 unkFunc(u16 arg0) {
    if (arg0 & 0x4000) {
        return func_06007CE0(arg0 & 0xFFF);
    } else {
        return SPR_2LookupTblNoToVram(arg0 & 0xFFF);
    }
}

extern u16 DAT_0605aec0[][2];
extern SaturnSpriteResource g_SaturnSharedSpriteBank12Resource;
extern SaturnSpriteResource g_SaturnSharedSpriteBank13Resource;

void func_06066B74(Primitive* prim0, Primitive* prim1, Primitive* prim2) {
    prim0->type = 0x1000;
    prim0->unk4 = 0x488;
    prim0->unk8 = DAT_0605aec0[1][0];
    prim0->unkA = 0x1840;
    prim0->unk6 = unkFunc(g_SaturnSharedSpriteBank12Resource.flags + 1);
    prim0->unk4 = prim0->unk4 & 0xFFC7;
    prim0->unk6 = prim0->unk6 & 0x8FFF | 0x4000;
    prim0->unk2 = 0x1C0;
    prim0->drawMode = DRAW_HIDE;

    prim1->type = 0x1004;
    prim1->unk4 = 0x4C0;
    prim1->unk6 = unkFunc(g_SaturnSharedSpriteBank13Resource.flags + 3) + 1;
    prim1->unk6 = prim1->unk6 & 0x8FFF | 0x4000;
    prim1->unk2 = 0x1BE;
    prim1->drawMode = DRAW_HIDE;

    prim2->type = 0x1005;
    prim2->unk4 = 0x4C0;
    prim2->unk6 = unkFunc(g_SaturnSharedSpriteBank13Resource.flags + 3);
    prim2->unk6 = prim2->unk6 & 0x8FFF | 0x4000;
    prim2->unk2 = 0x1BF;
    prim2->drawMode = DRAW_HIDE;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066CE0, func_06066CE0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066FE0, func_06066FE0);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067090, func_06067090);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60674B8, func_060674B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067958, func_06067958);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606797C, func_0606797C);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067A04, func_06067A04);
