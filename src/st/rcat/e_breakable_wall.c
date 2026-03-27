// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

extern EInit g_EInitParticle;
extern u8 D_us_80181408[][2];

void EntityBreakableWallDebris(Entity* self) {
    Collider collider;

    Primitive* prim;
    Primitive* prevPrim;
    Entity* newEntity;
    s32 primIndex;
    s16 posX;
    s16 posY;
    Primitive* nextPrim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.segmentedBreakableWall.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0xB;
            prim->clut = PAL_BREAKABLE_WALL_DEBRIS_MAIN;
            prim->u0 = prim->u2 = D_us_80181408[self->params][0];
            prim->u1 = prim->u3 = prim->u0 + 0xF;
            prim->v2 = prim->v3 = D_us_80181408[self->params][1];
            prim->v0 = prim->v1 = prim->v2 + 0xF;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 0x10;
            LOH(prim->next->b2) = 0x10;
            prim->next->b3 = 0x80;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            prim = prim->next;

            prim->clut = PAL_BREAKABLE_WALL_DEBRIS_HIGHLIGHT;
            prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }

        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.segmentedBreakableWall.prim;
        posX = prim->next->x1 = self->posX.i.hi;
        posY = prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        prevPrim = prim;
        prim = prim->next;
        prim = prim->next;

        nextPrim = prim->next;
        *prim = *prevPrim;
        prim->next = nextPrim;

        prim->clut = PAL_BREAKABLE_WALL_DEBRIS_HIGHLIGHT;
        prim->y0 -= 2;
        prim->y1 -= 2;
        prim->y2 -= 2;
        prim->y3 -= 2;
        prim->priority -= 1;
        prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;

        posY += 2;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects) {
            self->velocityY = FIX(-1.75);
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.segmentedBreakableWall.prim;
        posX = prim->next->x1 = self->posX.i.hi;
        posY = prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (self->params > 1) {
            LOH(prim->next->tpage) += 0x10;
        } else {
            LOH(prim->next->tpage) -= 0x10;
        }
        posY += 2;

        prevPrim = prim;
        prim = prim->next;
        prim = prim->next;

        nextPrim = prim->next;
        *prim = *prevPrim;
        prim->next = nextPrim;

        prim->clut = PAL_BREAKABLE_WALL_DEBRIS_HIGHLIGHT;
        prim->y0 -= 2;
        prim->y1 -= 2;
        prim->y2 -= 2;
        prim->y3 -= 2;
        prim->priority -= 1;
        prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;

        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects) {
            newEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, newEntity);
                newEntity->params = 0x10;
            }
            DestroyEntity(self);
        }
        break;
    }
}
