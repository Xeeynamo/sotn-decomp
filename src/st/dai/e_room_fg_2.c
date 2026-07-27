// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"
// Used ext.prim because it didn't seem worthwhile to create an entire ext
// simply for a prim

/*
There are two different entities used for the castle wall foreground tiles.
EntityCastleWall1: Most castle wall foreground tiles
EntityCastleWall2: The castle wall foreground tiles outside the confessional
room
*/

#include "../e_castle_walls.h"

// This entity renders the triangle shadow area underneath the staircase
void EntityStaircase(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 offsetY;
    Entity* playerPtr;

    switch (self->step) {
    case 0: // entity init
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->r0 = 64;
        prim->g0 = 56;
        prim->b0 = 48;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->x0 = 104;
        prim->y0 = 232;
        prim->x1 = 256;
        prim->y1 = 112;
        prim->x2 = prim->x3 = 256;
        prim->y2 = prim->y3 = 240;
        prim->priority = 94;
        prim->drawMode = DRAW_DEFAULT;
    case 1: // render entity
        g_GpuBuffers[0].draw.r0 = 16;
        g_GpuBuffers[0].draw.g0 = 8;
        g_GpuBuffers[0].draw.b0 = 56;
        g_GpuBuffers[1].draw.r0 = 16;
        g_GpuBuffers[1].draw.g0 = 8;
        g_GpuBuffers[1].draw.b0 = 56;
        playerPtr = &PLAYER;
        offsetY = 128 - playerPtr->posY.i.hi;
        if (offsetY < 0) {
            offsetY = 0;
        }
        prim = self->ext.prim;
        prim->y1 = 112 - offsetY;
        break;
    }
}
