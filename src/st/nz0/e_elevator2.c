// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

static bool g_CallElevator = false;

void EntityBloodSkeleElevButton(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 var_a0;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxHeight = 8;
        self->hitboxOffY = -22;
        self->hitboxWidth = 6;
        self->hitboxState = 1;
        CreateEntityFromEntity(E_BLOOD_SKELETON, self, &self[-1]);
        self[-1].posY.i.hi = 344 - g_Tilemap.scrollY.i.hi;

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
        var_a0 = self->hitFlags;

        if (abs(self->posX.i.hi - self[-1].posX.i.hi) < 8) {
            var_a0 |= 0x8000;
        }

        if (var_a0) {
            self->posY.val += FIX(1.0);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (temp > 376) {
                self->posY.i.hi = 376 - g_Tilemap.scrollY.i.hi;
            }
            g_CallElevator = true;
        } else {
            self->posY.val -= FIX(1);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (temp < 372) {
                self->posY.i.hi = 372 - g_Tilemap.scrollY.i.hi;
            }
            g_CallElevator = false;
        }

    default:
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = self->posY.i.hi - 8;
    }
}

void EntityElevator2(Entity* self) {
    s32 temp = GetPlayerCollisionWith(self, 16, 5, 4);
    volatile int pad[3];
    Primitive* prim;
    s16 primIndex;
    s32 player;
    s32 camY;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxOffX = 0;
        self->hitboxOffY = 68;
        g_CallElevator = false;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 8;
        prim->v0 = 0x80;
        prim->u1 = 0x20;
        prim->v1 = 0x48;
        prim->priority = 0x72;
        prim->drawMode = DRAW_UNK02;

        prim = prim->next;
        for (i = 0; i < 2; i++) {
            prim->type = PRIM_SPRT;
            prim->tpage = 0xF;
            prim->clut = 9;
            prim->u0 = 0;
            prim->v0 = 0x80;
            prim->u1 = 8;
            prim->v1 = 0x40;
            prim->priority = 0x5F;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }

    case 1:
        //! FAKE:
        player = PLAYER_CHARACTER;
        if (g_CallElevator) {
            self->posY.i.hi--;
            camY = g_Tilemap.scrollY.i.hi;
            if ((self->posY.i.hi + camY) < 96) {
                self->posY.i.hi = 96 - camY;
            } else if (temp != 0) {
                g_Entities[player].posY.i.hi--;
                D_80097488.y.i.hi--;
            }
        } else {
            self->posY.i.hi++;
            camY = g_Tilemap.scrollY.i.hi;
            if ((self->posY.i.hi + camY) > 216) {
                self->posY.i.hi = 216 - camY;
            } else if (temp != 0) {
                g_Entities[player].posY.i.hi++;
                D_80097488.y.i.hi++;
            }
        }
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi;

    prim = prim->next;
    prim->x0 = self->posX.i.hi - 3;
    prim->y0 = self->posY.i.hi - 56;

    prim = prim->next;
    prim->x0 = self->posX.i.hi - 3;
    prim->y0 = self->posY.i.hi - 120;
}
