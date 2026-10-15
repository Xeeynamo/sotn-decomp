// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

#include "../e_castle_walls.h"

// This entity renders the triangle shadow area underneath the staircase
void EntityStaircase(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
#if !defined(VERSION_PSP)
        self->posY.i.hi += 32;
#endif
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->r0 = 0x30;
        prim->g0 = 0x20;
        prim->b0 = 0x50;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->x0 = 0;
        prim->y0 = 0;
        prim->x1 = 0x90;
        prim->y1 = 0;
        prim->x2 = prim->x3 = 0;
        prim->y2 = prim->y3 = 0x90;
        prim->priority = 0x5E;
        prim->drawMode = DRAW_DEFAULT;
        /* fallthrough */
    case 1:
        g_GpuBuffers[0].draw.r0 = 0x10;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 0x38;
        g_GpuBuffers[1].draw.r0 = 0x10;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 0x38;
        break;
    }
}
