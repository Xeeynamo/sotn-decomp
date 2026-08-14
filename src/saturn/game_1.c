// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include <saturn_sprite.h>

s32 func_06066B30(Entity* self, s32 arg1) {
    s32 ret;

    if (arg1 == 0) {
        ret = func_06066CE0(self);
    } else if (arg1 == 1) {
        ret = func_06067090(self);
    } else {
        ret = func_060674B8(self, arg1);
    }
    return ret;
}

static u16 LookupTblNoToVram(u16 arg0) {
    if (arg0 & 0x4000) {
        return LocalLookupTblNoToVram(arg0 & 0xFFF);
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
    prim0->unk6 =
        LookupTblNoToVram(g_SaturnSharedSpriteBank12Resource.flags + 1);
    prim0->unk4 = prim0->unk4 & 0xFFC7;
    prim0->unk6 = prim0->unk6 & 0x8FFF | 0x4000;
    prim0->priority = 0x1C0;
    prim0->drawMode = DRAW_HIDE;

    prim1->type = 0x1004;
    prim1->unk4 = 0x4C0;
    prim1->unk6 =
        1 + LookupTblNoToVram(g_SaturnSharedSpriteBank13Resource.flags + 3);
    prim1->unk6 = prim1->unk6 & 0x8FFF | 0x4000;
    prim1->priority = 0x1BE;
    prim1->drawMode = DRAW_HIDE;

    prim2->type = 0x1005;
    prim2->unk4 = 0x4C0;
    prim2->unk6 =
        LookupTblNoToVram(g_SaturnSharedSpriteBank13Resource.flags + 3);
    prim2->unk6 = prim2->unk6 & 0x8FFF | 0x4000;
    prim2->priority = 0x1BF;
    prim2->drawMode = DRAW_HIDE;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6066CE0, func_06066CE0);

void func_06066FE0(Primitive* prim0, Primitive* prim1, Primitive* prim2) {
    if (prim0 == prim2) {
        u32 temp = (g_Timer >> 3 & 7);
        prim1->unk6 =
            temp + 2 +
            LookupTblNoToVram(g_SaturnSharedSpriteBank13Resource.flags + 3);
        prim1->unk6 = prim1->unk6 & 0x8FFF | 0x4000;
    } else {
        prim1->unk6 =
            1 + LookupTblNoToVram(g_SaturnSharedSpriteBank13Resource.flags + 3);
        prim1->unk6 = prim1->unk6 & 0x8FFF | 0x4000;
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067090, func_06067090);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f60674B8, func_060674B8);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067958, func_06067958);

extern u8 DAT_0604E5E0[];

void func_0601960C(char*, u8*, s16*, s16*, s32);

void func_0606797C(char* str, s16* arg1, s32 arg2) {
    s32 temp_r0;
    u32 temp_r2;
    u8* dst;
    s16 sp[2];

    dst = &DAT_0604E5E0[0];
    sp[0] = 0xC0;
    sp[1] = 0x40;
    temp_r2 = arg2 & 0xF;
    temp_r0 = arg2 >> 4;
    if (temp_r0 == 1) {
        if (temp_r2 == 0) {
            sp[1] = 0x20;
        } else {
            sp[1] = 0x10;
            dst = &DAT_0604E5E0[(temp_r2 + 1) * 0x600];
        }
    } else if (temp_r0 == 2) {
        if (temp_r2 == 0) {
            sp[1] = 0x30;
        } else {
            sp[0] = 0x60;
            sp[1] = 0x10;
            dst = &DAT_0604E5E0[(temp_r2 + 5) * 0x300];
        }
    }
    func_0601960C(str, dst, sp, arg1, 1);
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f6067A04, func_06067A04);
