// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

static bool g_CallElevator = 0;

void EntityBloodSkeleElevButton(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    s32 primIndex;
    s32 hitFlags;
    s32 buttonY;
    s32 distance;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 6;
        self->hitboxHeight = 8;
        self->hitboxOffY = -22;
        self->hitboxState = 1;
        newEntity = &self[-1];
        CreateEntityFromEntity(E_ID(BLOOD_SKELETON), self, newEntity);
        newEntity->posY.i.hi = 344 - g_Tilemap.scrollY.i.hi;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 72;
        prim->v0 = 200;
        prim->u1 = 16;
        prim->v1 = 16;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;
    case 1:
        hitFlags = self->hitFlags;
        newEntity = &self[-1];
        distance = self->posX.i.hi - newEntity->posX.i.hi;
        if (abs(distance) < 8) {
            hitFlags |= 0x8000;
        }
        if (hitFlags) {
            self->posY.val += FIX(1.0);
            buttonY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (buttonY > 376) {
                self->posY.i.hi = 376 - g_Tilemap.scrollY.i.hi;
            }
            g_CallElevator = 1;
        } else {
            self->posY.val -= FIX(1);
            buttonY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (buttonY < 372) {
                self->posY.i.hi = 372 - g_Tilemap.scrollY.i.hi;
            }
            g_CallElevator = 0;
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 8;
    prim->y0 = self->posY.i.hi - 8;
}

void EntityElevator2(Entity* self) {
    s32 isPlayerColliding;
    s32 primIndex;
    s32 camY;
    Entity* player;
    s32 i;
    Primitive* prim;

    isPlayerColliding = GetPlayerCollisionWith(self, 16, 5, 4);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxOffX = 0;
        self->hitboxOffY = 68;
        g_CallElevator = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
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
        if (g_CallElevator) {
            self->posY.i.hi--;
            camY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (camY < 96) {
                self->posY.i.hi = 96 - g_Tilemap.scrollY.i.hi;
            } else if (isPlayerColliding) {
                player = &PLAYER;
                player->posY.i.hi--;
                D_80097488.y.i.hi--;
            }
        } else {
            self->posY.i.hi++;
            camY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (camY > 216) {
                self->posY.i.hi = 216 - g_Tilemap.scrollY.i.hi;
            } else if (isPlayerColliding) {
                player = &PLAYER;
                player->posY.i.hi++;
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
