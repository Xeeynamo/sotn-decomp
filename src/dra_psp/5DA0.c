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
INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_psp_090E2820);

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_psp_090E2848);

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_psp_090E28D0);

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_psp_090E29A8);

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_801027C4);

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_psp_090E2A78);

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_80102CD8);

INCLUDE_ASM("dra_psp/psp/dra_psp/5DA0", func_psp_090E2EF8);
