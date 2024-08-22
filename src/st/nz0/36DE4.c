// SPDX-License-Identifier: AGPL-3.0-only
#include "nz0.h"
#include "sfx.h"

void func_801B6DE4(Entity* self) {
    s32 temp_s1;
    s16 primIndex;
    Primitive* prim;
    s32 y;

    temp_s1 = self->hitFlags;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        self->ext.generic.unk80.modeS32 =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        self->hitboxHeight = 8;
        self->hitboxOffY = -22;
        self->hitboxWidth = 6;
        self->hitboxState = 1;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 72;
        prim->v0 = 200;
        prim->u1 = 16;
        prim->v1 = 16;
        prim->priority = 0x5F;
        prim->type = PRIM_SPRT;
        prim->drawMode = DRAW_UNK02;
    case 1:
        if (temp_s1) {
            self->posY.val += FIX(1.0);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((self->ext.generic.unk80.modeS32 + 4) < y) {
                self->posY.i.hi = (u16)(self->ext.generic.unk80.modeS16.unk0 -
                                        (g_Tilemap.scrollY.i.hi - 4));
                self->step++;
                PlaySfxPositional(SFX_SWITCH_CLICK);
                g_ElevatorTarget = self->params;
            }
        }
        break;
    case 2:
        if (!temp_s1) {
            self->posY.val += 0xFFFF0000;
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (y < self->ext.generic.unk80.modeS32) {
                self->posY.i.hi = (u16)(self->ext.generic.unk80.modeS16.unk0) -
                                  g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 8;
    prim->y0 = self->posY.i.hi;
    prim->y0 = prim->y0 - 8;
}
