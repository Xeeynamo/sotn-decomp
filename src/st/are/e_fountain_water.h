// SPDX-License-Identifier: AGPL-3.0-or-later
extern EInit g_EInitInteractable;

void EntityFountainWater(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        prim->tpage = 0xF;
        prim->clut = PAL_FOUNTAIN_WATER;
        prim->u0 = prim->u2 = 3;
        prim->u1 = prim->u3 = 0x84;
        prim->v0 = prim->v1 = 0xB8;
        prim->v2 = prim->v3 = 0xFD;
#ifdef INVERTED_STAGE
        prim->x0 = prim->x2 = 0x100 - (0x4F - g_Tilemap.scrollX.i.hi);
        prim->x1 = prim->x3 = prim->x0 - 0x81;
#ifdef VERSION_PSP
        prim->y0 = prim->y1 = 0x100 - (0x8C - g_Tilemap.scrollY.i.hi);
#else
        prim->y0 = prim->y1 = 0xF7 - (0x8C - g_Tilemap.scrollY.i.hi);
#endif
        prim->y2 = prim->y3 = prim->y0 - 0x45;
#else
        prim->x0 = prim->x2 = 0x4F - g_Tilemap.scrollX.i.hi;
        prim->x1 = prim->x3 = prim->x0 + 0x81;
        prim->y0 = prim->y1 = 0x8C - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = prim->y0 + 0x45;
#endif
        prim->priority = 0x2A;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;

        prim->type = PRIM_TILE;
        prim->u0 = 0x90;
        prim->v0 = 0x20;
#ifdef INVERTED_STAGE
        prim->x0 = 0x28 - g_Tilemap.scrollX.i.hi;
        prim->y0 = 0xE0 - (0xB9 - g_Tilemap.scrollY.i.hi);
#else
        prim->x0 = 0x48 - g_Tilemap.scrollX.i.hi;
        prim->y0 = 0xB9 - g_Tilemap.scrollY.i.hi;
#endif
        prim->r0 = 8;
        prim->g0 = 0x20;
        prim->b0 = 0x30;
        prim->priority = 0x9F;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        // Fallthrough
    case 1:
        prim = self->ext.prim;
        if (!(g_Timer & 3)) {
            prim->clut++;
            if (prim->clut > PAL_FOUNTAIN_WATER_MAX) {
                prim->clut = PAL_FOUNTAIN_WATER;
            }
        }
        break;
    }
}
