// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// This is the row of blue "land" tiles at the bottom of the sky background
void EntityBackgroundSkyLand(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 x;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        for (x = 0; prim != NULL; prim = prim->next) {
            prim->tpage = 15;
            prim->clut = PAL_BACKGROUND_SKY_LAND;
            prim->u0 = prim->u2 = 65;
            prim->u1 = prim->u3 = 127;
            prim->v0 = prim->v1 = 169;
            prim->v2 = prim->v3 = 198;
            prim->x0 = prim->x2 = x;
            x += 62;
            prim->x1 = prim->x3 = x;
            prim->y0 = prim->y1 = 192;
            prim->y2 = prim->y3 = 228;
            prim->priority = 16;
            prim->drawMode = DRAW_DEFAULT;
        }
    }
}
