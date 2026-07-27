// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitInteractable;

void EntityCastleWall1(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 posX;
    s32 count;

    if (self->step != 0) {
        (void)1;
        return;
    }

    InitializeEntity(g_EInitInteractable);
#if defined(STAGE_IS_RDAI) && !defined(VERSION_PSP)
    self->posY.i.hi += 32;
#endif
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }
    self->flags |= FLAG_HAS_PRIMS;
    self->primIndex = primIndex;
    prim = &g_PrimBuf[primIndex];
    self->ext.prim = prim;
    posX = self->posX.i.hi;
    for (count = 0; count < 2; count++) {
        prim->tpage = 15;
        prim->clut = PAL_CASTLE_WALL_1;
        prim->u0 = prim->u2 = 115 - (count * 16) - self->params;
        prim->u1 = prim->u3 = prim->u0 - (80 - (count * 16));
        prim->v0 = prim->v1 = 67;
        prim->v2 = prim->v3 = 163;
        prim->x0 = prim->x2 = posX;
        if (self->params) {
            posX += 80 - (count * 16);
        } else {
            posX -= 80 - (count * 16);
        }
        prim->x1 = prim->x3 = posX;
        prim->y0 = prim->y1 = self->posY.i.hi;
#if defined(STAGE_IS_RDAI)
        prim->y2 = prim->y3 = prim->y0 - 96;
#else
        prim->y2 = prim->y3 = prim->y0 + 96;
#endif
        prim->priority = 160;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
    }
}

void EntityCastleWall2(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 posX, posY;
    s32 rows;
    s32 countX, countY;

    if (self->step != 0) {
        (void)1;
        return;
    }

    InitializeEntity(g_EInitInteractable);
#if defined(STAGE_IS_RDAI) && !defined(VERSION_PSP)
    self->posY.i.hi += 32;
#endif
    rows = self->params & 0xF;
    primIndex = g_api.AllocPrimitives(PRIM_GT4, rows * 3);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }
    self->flags |= FLAG_HAS_PRIMS;
    self->primIndex = primIndex;
    prim = &g_PrimBuf[primIndex];
    self->ext.prim = prim;
    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    for (countY = 0; countY < rows; countY++) {
        for (countX = 0; countX < 3; countX++) {
            prim->tpage = 15;
            prim->clut = PAL_CASTLE_WALL_2;
            prim->u0 = prim->u2 = 193;
            prim->u1 = prim->u3 = 254;
            prim->v0 = prim->v1 = 193;
            prim->v2 = prim->v3 = 254;
            if (self->params & 0x100) {
#if defined(STAGE_IS_RDAI)
                prim->x0 = prim->x2 = posX + countX * 61;
                prim->x1 = prim->x3 = prim->x0 + 61;
#else
                prim->x0 = prim->x2 = posX - countX * 61;
                prim->x1 = prim->x3 = prim->x0 - 61;
#endif
            } else {
#if defined(STAGE_IS_RDAI)
                prim->x0 = prim->x2 = posX - countX * 61;
                prim->x1 = prim->x3 = prim->x0 - 61;
#else
                prim->x0 = prim->x2 = posX + countX * 61;
                prim->x1 = prim->x3 = prim->x0 + 61;
#endif
            }
#if defined(STAGE_IS_RDAI)
            prim->y0 = prim->y1 = posY - countY * 61;
            prim->y2 = prim->y3 = prim->y0 - 61;
#else
            prim->y0 = prim->y1 = posY + countY * 61;
            prim->y2 = prim->y3 = prim->y0 + 61;
#endif
            prim->priority = 160;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
    }
}
