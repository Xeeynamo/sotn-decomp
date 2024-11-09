// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

extern u32 D_8013799C;
extern s32 D_801379A0;
extern s32 D_801379A4;
extern s32 D_801379A8;

void func_801024DC(void) {
    Primitive* prim;
    s32 x;

    D_8013799C = AllocPrimitives(PRIM_TILE, 4);
    prim = &g_PrimBuf[D_8013799C];
    for (x = 0; prim != NULL; x++) {
        prim->x0 = (x & 1) * 128;
        prim->u0 = 0x80;
        prim->v0 = 0xF0;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    D_801379A8 = 0;
    D_801379A4 = 0;

    D_801379A0 = AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_801379A0];
    prim->u0 = 0;
    prim->v0 = 0;
    prim->u1 = 0xFF;
    prim->v1 = 0;
    prim->u2 = 0;
    prim->v2 = 0xFF;
    prim->u3 = 0xFF;
    prim->v3 = 0xFF;
    prim->tpage = 0x1D;
    prim->clut = 0x1C0;
    prim->priority = 0x1FE;

    prim->drawMode = DRAW_HIDE;
}

s32 func_801025F4(void) {
    Primitive* prim = &g_PrimBuf[D_8013799C];
    return prim->clut;
}

void func_80102628(s32 arg0) {
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[D_8013799C];
    for (i = 0; prim != NULL; i++) {
        prim->x0 = arg0 / 2 * (i & 1);
        prim->y0 = 0;
        prim->u0 = arg0 / 2;
        prim->v0 = 0xF0;
        prim->b0 = 0;
        prim->g0 = 0;
        prim->r0 = 0;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_801026BC(s32 arg0) {
    Primitive* prim = &g_PrimBuf[D_801379A0];

    if (arg0 == 0) {
        prim->drawMode = DRAW_HIDE;
        return;
    } else if (!(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
        SetPrimRect(prim, 0, 1, 255, 255);
    } else {
        prim->x0 = prim->x2 = 255;
        prim->x1 = prim->x3 = 0;
        prim->y0 = prim->y1 = 240;
        prim->y2 = prim->y3 = -15;
    }

    func_80107250(prim, arg0 * 2);

    if (arg0 == 0x40) {
        prim->drawMode = DRAW_DEFAULT;
    } else {
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_psp_090E29A8);

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_801027C4);
