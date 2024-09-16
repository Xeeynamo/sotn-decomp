// SPDX-License-Identifier: AGPL-3.0-or-later
// Purpose is not 100% clear. Creates a falling blue droplet that sizzles after
// hitting the ground. In existing overlays, this entity is not used. But looks
// like Olrox's drool, so using that until we find any other uses.

extern u32 g_olroxDroolCollOffsets[];

extern u16 g_InitializeEntityData0[];
void EntityOlroxDrool(Entity* self) {
    s16 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex == -1) {
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->hitboxState = 0;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->r0 = 64;
            prim->r1 = 0;
            prim->g0 = 64;
            prim->g1 = 0;
            prim->b0 = 255;
            prim->b1 = 16;
            prim->priority = self->zPriority + 1;
            prim->drawMode |= (DRAW_TPAGE2 + DRAW_TPAGE + DRAW_COLORS +
                               DRAW_UNK02 + DRAW_TRANSP);
            prim = prim->next;
        }
        break;

    case 1:
        prim = self->ext.prim;
        if (CheckColliderOffsets(g_olroxDroolCollOffsets, 0)) {
            prim->y1 += 2;
            if (self->step_s == 0) {
                // When hitting the ground, a sizzling effect is made
                EntityUnkId14Spawner(self, 1, 2, 0, 0, 3, 0);
                self->step_s = 1;
            }
        } else {
            self->velocityY += FIX(0.015625);
            self->posY.val += self->velocityY;
            if ((prim->y0 - prim->y1) > 8) {
                prim->y1 = prim->y0 - 8;
            }
        }

        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;

        if (prim->y0 < prim->y1) {
            g_api.FreePrimitives(self->primIndex);
            DestroyEntity(self);
        }
        break;
    }
}
