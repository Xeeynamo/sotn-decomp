// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

// First floor button encountered
void EntityFloorButton(Entity* self) {
    s32 collided;
    Primitive* prim;
    Entity* player;
    s32 primIndex;
    s32 x;
    s32 y;
    s32 tileIndex;
    Entity* child;

    collided = GetPlayerCollisionWith(self, 8, 8, 4);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.nz0311c0.unk80 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
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
        prim->u1 = 0x10;
        prim->v1 = 0x10;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;

        x = self->posX.i.hi;
        y = self->posY.i.hi + 4;
        x += g_Tilemap.scrollX.i.hi;
        y += g_Tilemap.scrollY.i.hi;
        tileIndex = (x >> 4) + (y >> 4) * g_Tilemap.hSize * 0x10;
        g_Tilemap.fg[tileIndex] = 0x5AF;
    case 1:
        if (collided) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += FIX(1.0);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((self->ext.nz0311c0.unk80 + 4) < y) {
                self->posY.i.hi =
                    (self->ext.nz0311c0.unk80 + 4) - g_Tilemap.scrollY.i.hi;
                self->step++;
                child = self + 1;
                child->ext.nz0311c0.unk84 ^= 1;
                child->ext.nz0311c0.unk88 = 1;
            }
        }
        break;
    case 2:
        if (collided == 0) {
            self->posY.val -= FIX(1);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (y < self->ext.nz0311c0.unk80) {
                self->posY.i.hi =
                    self->ext.nz0311c0.unk80 - g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 8;
    prim->y0 = self->posY.i.hi - 8;
}

void EntityFloorSpikes(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 x;
    s32 y;
    s32 tileIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->attackElement = 1;
        self->attack = 7;
        self->hitboxState = 1;
        self->ext.nz0311c0.unk80 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

        x = self->posX.i.hi - 4;
        y = self->posY.i.hi - 4;
        x += g_Tilemap.scrollX.i.hi;
        y += g_Tilemap.scrollY.i.hi;
        tileIndex = (x >> 4) + (y >> 4) * g_Tilemap.hSize * 0x10;
        g_Tilemap.fg[tileIndex] = 0x102;
        (&g_Tilemap.fg[tileIndex])[1] = 0x103;

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
        prim->u0 = 0x28;
        prim->v0 = 0xC8;
        prim->u1 = 0x20;
        prim->v1 = 0x20;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;
#ifdef VERSION_US
        self->posY.i.hi -= 28;
#endif
    case 1:
        self->hitboxState = 1;
        if (self->ext.nz0311c0.unk84 != 0) {
            self->posY.val += FIX(1.0);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (self->ext.nz0311c0.unk80 < y) {
                self->posY.i.hi =
                    self->ext.nz0311c0.unk80 - g_Tilemap.scrollY.i.hi;
                self->hitboxState = 0;
            }
        } else {
            self->posY.val -= FIX(1);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (self->ext.nz0311c0.unk80 - 28 > y) {
                self->posY.i.hi =
                    self->ext.nz0311c0.unk80 - 28 - g_Tilemap.scrollY.i.hi;
            }
        }
        break;
    }
    if (self->ext.nz0311c0.unk88) {
        PlaySfxPositional(SFX_MAGIC_SWITCH);
        self->ext.nz0311c0.unk88 = 0;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi - 16;
}

// table with globe on it that can be broken
static u8 D_80180EF0[] = {0x02, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00};

static u8 D_80180EF8[] = {
    0x03, 0x03, 0x03, 0x04, 0x03, 0x05, 0x03, 0x06, 0x03, 0x07, 0x03, 0x08,
    0x02, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x03, 0x0C, 0x21, 0x0D, 0xFF, 0x00};

static u16 D_80180F10[] = {0, 1, 2, 6, 10, 0};

void EntityTableWithGlobe(Entity* self) {
    Entity* child;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTableWithGlobe);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->hitboxOffX = 0;
        self->hitboxOffY = -10;
        self->hitboxState = 2;
    case 1:
        AnimateEntity(D_80180EF0, self);
        if (self->hitFlags) {
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            self->hitboxState = 0;
            child = self + 1;
            CreateEntityFromEntity(E_HEART_DROP, self, child);
            child->params = D_80180F10[self->params];
            SetStep(2);
        }
        break;
    case 2:
        AnimateEntity(D_80180EF8, self);
        break;
    }
}
