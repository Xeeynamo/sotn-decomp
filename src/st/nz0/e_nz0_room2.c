// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

// First floor button encountered
void EntityFloorButton(Entity* self) {
    s32 temp = GetPlayerCollisionWith(self, 8, 8, 4);
    Primitive* prim;
    Entity* player;
    s16 primIndex;
    s32 posX, posY;
    s32 camY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.nz0311c0.unk80 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
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
        prim->u0 = 72;
        prim->v0 = 200;
        prim->v1 = prim->u1 = 0x10;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;

        posX = self->posX.i.hi;
        posX += g_Tilemap.scrollX.i.hi;
        posX >>= 4;

        // TODO: !FAKE
        camY = self->posY.i.hi;
        posY = camY += 4;
        posY = camY += g_Tilemap.scrollY.i.hi;

        camY = (camY >> 4) * g_Tilemap.hSize * 16;
        g_Tilemap.fg[posX + camY] = 0x5AF;

    case 1:
        if (temp != 0) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += FIX(1.0);
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((self->ext.nz0311c0.unk80 + 4) < posY) {
                self->posY.i.hi =
                    (self->ext.nz0311c0.unk80 + 4) - g_Tilemap.scrollY.i.hi;
                (self + 1)->ext.nz0311c0.unk88 = 1;
                self->step++;
                (self + 1)->ext.nz0311c0.unk84 ^= 1;
            }
        }

    default:
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = self->posY.i.hi - 8;
        break;

    case 2:
        if (temp == 0) {
            self->posY.val -= FIX(1);
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (posY < self->ext.nz0311c0.unk80) {
                self->posY.i.hi =
                    self->ext.nz0311c0.unk80 - g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
        }
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = self->posY.i.hi - 8;
        break;
    }
}

void EntityFloorSpikes(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 var_v1;
    s32 tilePos;
    s32 new_var;
    u8 temp; // !FAKE
    volatile int pad[3];

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->attackElement = 1;
        self->attack = 7;
        self->hitboxState = 1;
        self->ext.nz0311c0.unk80 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

        temp = 4;
        new_var = self->posY.i.hi - 4;
        new_var += g_Tilemap.scrollY.i.hi;
        tilePos = ((self->posX.i.hi - temp + g_Tilemap.scrollX.i.hi) >> 4) +
                  (((new_var >> 4) * g_Tilemap.hSize) * 16);

        g_Tilemap.fg[tilePos] = 0x102;
        g_Tilemap.fg[tilePos + 1] = 0x103;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
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
        prim->u0 = 0x28;
        prim->v0 = 0xC8;
        prim->v1 = prim->u1 = 0x20;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;
        self->posY.i.hi -= 28;

    case 1:
        self->hitboxState = 1;
        if (self->ext.nz0311c0.unk84 != 0) {
            self->posY.val += FIX(1.0);
            new_var = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            var_v1 = g_Tilemap.scrollY.i.hi;
            if (new_var > self->ext.nz0311c0.unk80) {
                self->hitboxState = 0;
                self->posY.i.hi = self->ext.nz0311c0.unk80 - var_v1;
            }
        } else {
            self->posY.val -= FIX(1);
            new_var = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            var_v1 = g_Tilemap.scrollY.i.hi;
            if (new_var < (self->ext.nz0311c0.unk80 - 28)) {
                self->posY.i.hi = self->ext.nz0311c0.unk80 - 28 - var_v1;
            }
        }
    }
    if (self->ext.nz0311c0.unk88 != 0) {
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
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTableWithGlobe);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;

    case 1:
        AnimateEntity(D_80180EF0, self);
        if (self->hitFlags != 0) {
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            self->hitboxState = 0;
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
            self[1].params = D_80180F10[self->params];
            SetStep(2);
        }
        break;

    case 2:
        AnimateEntity(D_80180EF8, self);
        break;
    }
}
