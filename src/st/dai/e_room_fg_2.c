// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// Castle wall foreground
void EntityCastleWall1(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 posX;
    s32 count;

    if (self->step != 0) {
        s32 nop; // This does nothing, but
        nop;     // pspeu seems to require it to match
        return;
    }

    InitializeEntity(g_EInitInteractable);
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }
    self->flags |= FLAG_HAS_PRIMS;
    self->primIndex = primIndex;
    prim = &g_PrimBuf[primIndex];
    self->ext.unk41EE4.prim = prim;
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
        prim->y2 = prim->y3 = prim->y0 + 96;
        prim->priority = 160;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
    }
}

// Foreground stone outside confessional room and other places
void EntityCastleWall2(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 posX, posY;
    s32 rows;
    s32 countX, countY;

    if (self->step != 0) {
        s32 nop; // This does nothing, but
        nop;     // pspeu seems to require it to match
        return;
    }

    InitializeEntity(g_EInitInteractable);
    rows = self->params & 0xF;
    primIndex = g_api.AllocPrimitives(PRIM_GT4, rows * 3);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }
    self->flags |= FLAG_HAS_PRIMS;
    self->primIndex = primIndex;
    prim = &g_PrimBuf[primIndex];
    self->ext.unk41EE4.prim = prim;
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
                prim->x0 = prim->x2 = posX - countX * 61;
                prim->x1 = prim->x3 = prim->x0 - 61;
            } else {
                prim->x0 = prim->x2 = posX + countX * 61;
                prim->x1 = prim->x3 = prim->x0 + 61;
            }
            prim->y0 = prim->y1 = posY + countY * 61;
            prim->y2 = prim->y3 = prim->y0 + 61;
            prim->priority = 160;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
    }
}

void EntityStaircase(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 offsetY;
    Entity* playerPtr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.unk41EE4.prim = prim;
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
    case 1:
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
        prim = self->ext.unk41EE4.prim;
        prim->y1 = 112 - offsetY;
        break;
    }
}
