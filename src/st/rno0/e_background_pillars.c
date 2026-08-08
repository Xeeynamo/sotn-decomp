// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

extern EInit RNO0_EInitSpawner;

void func_us_801CC8F8_from_no0(self);

void EntityBackgroundPillars(Entity* self){
    Entity* entityPtr;
    s16 i;
    Primitive* prim;
    s32 primIndex;

    if (self->step) {
        return;
    }

    InitializeEntity(RNO0_EInitSpawner);
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 9);
    if (primIndex != -1) {
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->flags |= FLAG_HAS_PRIMS;
        for (i = -0x10; prim != NULL; i += 0x1E) {
            prim->tpage = 0xF;
            prim->clut = 0x2A;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xC0;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xB0;
            prim->x0 = prim->x2 = i;
            prim->x1 = prim->x3 = i + 0x20;
            prim->y0 = prim->y1 = 0x5F;
            prim->y2 = prim->y3 = 0x3F;
            prim->priority = 0;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
    }

    entityPtr = self + 1;

    for (i = -0x10; i < 0x130; i += 0x60) {
        DestroyEntity(entityPtr);
        entityPtr->entityId = E_UNK_16;
        entityPtr->pfnUpdate = func_us_801CC8F8_from_no0;
        entityPtr->posY.i.hi = 0x6A;
        entityPtr->posX.i.hi = i;
        entityPtr++;
    }
}

INCLUDE_ASM("st/rno0/nonmatchings/e_background_pillars", func_us_801CC8F8_from_no0);

INCLUDE_ASM("st/rno0/nonmatchings/e_background_pillars", func_us_801CC9B4_from_no0);
