// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

extern s16 D_pspeu_0928F4A0[];
extern s16 D_pspeu_0928F5C0[];
extern Pos D_pspeu_09290580[];

extern u8 D_pspeu_0928F6E0[];
extern u8 D_pspeu_0928F7A0[];

void func_pspeu_09254C28(void) {
    s32 i;
    Primitive* prim;
    s16* var_a1;
    u8* var_a3;
    s16* var_t0;

    u8 u, v;

    prim = g_CurrentEntity->ext.prim;
    var_a1 = D_pspeu_0928F4A0;
    var_a3 = D_pspeu_0928F6E0;

    u = 0x60;
    v = 0x40;

    for (i = 0; i < 26; i++) {
        prim->tpage = 0x13;
        prim->clut = 0x209;
        prim->u0 = u + (var_a1 + *var_a3 * 2)[0];
        prim->v0 = v + (var_a1 + *var_a3++ * 2)[1];
        prim->u1 = u + (var_a1 + *var_a3 * 2)[0];
        prim->v1 = v + (var_a1 + *var_a3++ * 2)[1];
        prim->u2 = u + (var_a1 + *var_a3 * 2)[0];
        prim->v2 = v + (var_a1 + *var_a3++ * 2)[1];
        prim->u3 = u + (var_a1 + *var_a3 * 2)[0];
        prim->v3 = v + (var_a1 + *var_a3++ * 2)[1];

        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xD0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
    }
    g_CurrentEntity->ext.et_801B0930.prim0 = prim;
    var_a1 = D_pspeu_0928F5C0;
    var_a3 = D_pspeu_0928F7A0;
    u = 0;
    v = 0x80;
    for (i = 0; i < 39; i++) {
        prim->tpage = 0x110;
        prim->clut = 0x20B;
        prim->u0 = u + (var_a1 + *var_a3 * 2)[0];
        prim->v0 = v + (var_a1 + *var_a3++ * 2)[1];
        prim->u1 = u + (var_a1 + *var_a3 * 2)[0];
        prim->v1 = v + (var_a1 + *var_a3++ * 2)[1];
        prim->u2 = u + (var_a1 + *var_a3 * 2)[0];
        prim->v2 = v + (var_a1 + *var_a3++ * 2)[1];
        prim->u3 = u + (var_a1 + *var_a3 * 2)[0];
        prim->v3 = v + (var_a1 + *var_a3++ * 2)[1];
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xD0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
    }

    var_a1 = D_pspeu_0928F4A0;
    for (i = 0; i < 66; i++) {
        D_pspeu_09290580[i].x.val = (*var_a1 - 0x10) * FIX(1.0);
        var_a1++;
        D_pspeu_09290580[i].y.val = (*var_a1 - 0x27) * FIX(1.0);
        var_a1++;
    }
}

// same as us/func_us_801B088C
void func_pspeu_09255118(void) {
    s32 i;
    s32 x;
    s32 y;
    s32 t1, t2, t3, t4;
    s16* var_a1;
    s16* var_a0;

    var_a1 = D_pspeu_0928F4A0;
    var_a0 = D_pspeu_0928F5C0;

    t1 = -0x10;
    t2 = -0x27;
    t3 = -0x40;
    t4 = -0x70;

    for (i = 0; i < 66; i++) {
        x = (t3 + *var_a0) - (t1 + *var_a1);
        x = (x * FIX(1.0)) / 128;
        D_pspeu_09290580[i].x.val = D_pspeu_09290580[i].x.val + x;
        var_a1++;
        var_a0++;

        y = (t4 + *var_a0) - (t2 + *var_a1);
        y = (y * FIX(1.0)) / 128;
        D_pspeu_09290580[i].y.val = D_pspeu_09290580[i].y.val + y;
        var_a1++;
        var_a0++;
    }
}

// same as us/func_us_801B0930
INCLUDE_ASM("boss/bo0_psp/nonmatchings/bo0_psp/3053C", func_pspeu_09255288);
