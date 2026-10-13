// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"

extern EInit g_EInitInteractable;

void func_us_80193050(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 x;

    if (self->step) {
        return;
    }

    InitializeEntity(g_EInitInteractable);
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);

    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    self->flags |= FLAG_HAS_PRIMS;
    self->primIndex = primIndex;
    prim = &g_PrimBuf[primIndex];
    x = 0;

    while (prim != NULL) {
        prim->tpage = 0xF;
        prim->clut = 0xC5;
        prim->u0 = prim->u2 = 65;
        prim->u1 = prim->u3 = 127;
        prim->v0 = prim->v1 = 169;
        prim->v2 = prim->v3 = 198;
        prim->x0 = prim->x2 = x;
        x += 62;
        prim->x1 = prim->x3 = x;
        prim->y0 = prim->y1 = 64;
        prim->y2 = prim->y3 = 18;
        prim->priority = 0x10;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
    }
}
