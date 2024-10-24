// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"
#include "sfx.h"

// clouds in the background ID 0x18
void EntityBackgroundClouds(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 camX, camY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x100;
        prim->y0 = prim->y1 = 0x6E - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = 0xF0;
        setRGB0(prim, 16, 16, 16);
        prim->priority = 0x20;
        prim->drawMode = DRAW_DEFAULT;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim = prim->next;
        camX = -g_Tilemap.scrollX.i.hi;
        camY = 32 - g_Tilemap.scrollY.i.hi;
        while (prim != 0) {
            prim->x0 = prim->x2 = camX;
            camX += 95;
            prim->x1 = prim->x3 = camX;
            prim->tpage = 0xF;
            prim->clut = 5;
            prim->u0 = prim->u2 = 0x84;
            prim->u1 = prim->u3 = 0xE3;
            prim->v0 = prim->v1 = 1;
            prim->v2 = prim->v3 = 0x4F;
            prim->y0 = prim->y1 = camY;
            prim->y2 = prim->y3 = camY + 0x4E;
            prim->priority = 0x20;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        break;

    case 255:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         */
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params == 0) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    g_GpuBuffers[0].draw.r0 = 40;
    g_GpuBuffers[0].draw.g0 = 24;
    g_GpuBuffers[0].draw.b0 = 24;
    g_GpuBuffers[1].draw.r0 = 40;
    g_GpuBuffers[1].draw.g0 = 24;
    g_GpuBuffers[1].draw.b0 = 24;
}
