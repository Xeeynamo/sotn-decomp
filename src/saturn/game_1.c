// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"
#include "lib/spr/spr.h"
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

extern char* DAT_0607C0F0[];
extern char* DAT_0607C114[];
extern char* DAT_0607C118[];
extern char* DAT_0607C11C[];
extern char* DAT_0607C120[];
extern char* DAT_0607C124[];
extern char* DAT_0607C128[];
extern char* DAT_0607C12C[];
extern char* DAT_0607C130[];

void PlaySfx(s32 sfxId);
void func_06067958(void);
void func_0606797C(char*, s16*, s32);
void func_06067A04(void);

s32 func_06066CE0(Entity* self) {
    Primitive* prim0;
    Primitive* prim1;
    Primitive* prim2;
    s16 sp[2];

    s32 temp;
    s32 temp2;
    s32 temp3;

    prim0 = self->ext.save.unk10;
    prim1 = self->ext.save.unk14;
    prim2 = self->ext.save.unk18;
    temp = prim0->x3;
    if (temp == 0) {
        if (self->ext.save.unk4 == 0x28) {
            PlaySfx(SFX_START_SLAM_B);
        } else {
            PlaySfx(SFX_UI_ALERT_TINK);
        }
        func_06067958();
        sp[0] = 0;
        sp[1] = 0;
        func_06066B74(prim0, prim1, prim2);
        prim0->x0 = 0x40;
        prim1->x0 = prim1->x3 = 0x3A;
        prim1->x1 = prim1->x2 = 0x106;
        prim2->x0 = prim2->x3 = 0x3A;
        prim2->x1 = prim2->x2 = 0x106;
        switch (self->ext.save.unk4) {
        case 0x28:
            func_0606797C(DAT_0607C114[0], sp, 0);
            prim0->x0 = 0x70;
            prim2->x0 = prim2->x3 = prim1->x0 = prim1->x3 = 0x6A;
            prim2->x1 = prim2->x2 = prim1->x1 = prim1->x2 = 0xD6;
            prim0->x3 += 2;
            break;
        case 0x29:
            func_0606797C(DAT_0607C118[0], sp, 0);
            prim0->x3 += 2;
            break;
        case 0x2A:
            func_0606797C(DAT_0607C0F0[1], sp, 0);
            func_0606797C(DAT_0607C11C[0], sp, 0);
            sp[0] = 0;
            sp[1] += 0x10;
            func_0606797C(DAT_0607C120[0], sp, 0);
            prim0->x3 += 2;
            break;
        case 0x2B:
            func_0606797C(DAT_0607C0F0[1], sp, 0);
            func_0606797C(DAT_0607C124[0], sp, 0);
            sp[0] = 0;
            sp[1] += 0x10;
            func_0606797C(DAT_0607C128[0], sp, 0);
            prim0->x3 += 2;
            break;
        case 0x2C:
            func_0606797C(DAT_0607C12C[0], sp, 0);
            prim0->x3 += 2;
            break;
        default:
        case 0x2D:
            func_0606797C(DAT_0607C130[0], sp, 0);
            prim0->x3 += 2;
            break;
        }

        func_06067A04();
        temp3 = sp[1] + 0x10;
        self->ext.save.unk1E = temp3;
        prim0->y0 = temp3 + 0x40;
        prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = temp3 + 0x3D;
        prim2->y2 = prim2->y3 = prim1->y2 = prim1->y3 = temp3 + 0x43;
    } else {
        temp2 = self->ext.save.unk1E;
        if (temp <= temp2) {
            temp2 += 0x40;
            prim0->y0 = temp2 - temp;
            prim0->unkA = temp | 0x1800;
            prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = prim0->y0 - 3;
            prim2->drawMode = prim1->drawMode = prim0->drawMode = DRAW_DEFAULT;
            prim0->x3 += 2;
        } else {
            prim0->y0 = 0x40;
            prim0->unkA = temp2 | 0x1800;
            prim2->y0 = prim2->y1 = prim1->y0 = prim1->y1 = 0x3D;
            if (self->ext.save.unk4 == 0x28) {
                prim0->x3 += 2;
            }
            if ((temp >= 0xE0) || (g_pads[0].pressed & 0x700)) {
                prim2->drawMode = prim1->drawMode = prim0->drawMode = DRAW_HIDE;
                return 1;
            }
        }
    }
    return 0;
}

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

extern u8 DAT_0604E5E0[];

extern void* memset(void* dest, int value, unsigned long size);

void func_06067958(void) { memset(DAT_0604E5E0, 0, 0x1800); }

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

void func_06067A04(void) {
    s32 temp = 1;
    s32 temp2 = (DAT_0605aec0[temp][0] * 8) + VRAM_ADDR;

    QueueVramTransfer(temp2, DAT_0604E5E0, 0x1800);
}
