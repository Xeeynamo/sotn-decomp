// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

static s32 D_80180EB4 = 0;

void BoxPuzzleFloorButton(Entity* self) {
    s32 temp_s1 = GetPlayerCollisionWith(self, 8, 8, 4);
    s32 primIndex;
    Primitive* prim;
    Entity* player;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
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
        if (temp_s1 != 0) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += FIX(1.0);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (temp > 468) {
                self->posY.i.hi = 468 - g_Tilemap.scrollY.i.hi;
                D_80180EB4 ^= self->params;
                self->step++;
            }
        }
        break;
    case 2:
        if (temp_s1 == 0) {
            self->step++;
        }
        break;
    case 3:
        self->posY.val -= FIX(1);
        temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        if (temp < 464) {
            self->posY.i.hi = 464 - g_Tilemap.scrollY.i.hi;
            self->step = 1;
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 8;
    prim->y0 = self->posY.i.hi - 8;
}

// Spikes which go up and down when pressing the buttons
void BoxPuzzleSpikes(Entity* self) {
    s32 primIndex;
    Primitive* prim;
    s32 var_s2;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->attackElement = 1;
        self->attack = 7;
        self->hitboxState = 1;

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
        prim->u0 = 40;
        prim->v0 = 200;
        prim->u1 = 32;
        prim->v1 = 32;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;

        if (D_80180EB4 & self->params) {
            self->posY.i.hi = 480 - g_Tilemap.scrollY.i.hi;
            self->ext.nz0311c0.unk88 = 1;
        } else {
            self->posY.i.hi = 452 - g_Tilemap.scrollY.i.hi;
            self->ext.nz0311c0.unk88 = 0;
        }
    case 1:
        if (D_80180EB4 & self->params) {
            self->posY.val += FIX(1.0);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (temp > 480) {
                self->posY.i.hi = 480 - g_Tilemap.scrollY.i.hi;
            }
            var_s2 = 1;
        } else {
            self->posY.val -= FIX(1);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (temp < 452) {
                self->posY.i.hi = 452 - g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
            var_s2 = 0;
        }

        if (self->ext.nz0311c0.unk88 != var_s2) {
            self->ext.nz0311c0.unk88 = var_s2;
            PlaySfxPositional(SFX_MAGIC_SWITCH);
        }
    }

    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi - 16;
    temp = 480 - (g_Tilemap.scrollY.i.hi + self->posY.i.hi);
    D_801CB738[self->params - 1] = temp;
}

// movable box for spike/switch areas
static s16 D_80180EB8[][2] = {{0, 16}, {16, 0}};
static s16 unk_stuff[][2] = {{0, 16}, {0, 4}, {2, -4}, {-4, 0}};
void EntityMovableBox(Entity* self) {
    s32 primIndex;
    Entity* player;
    Primitive* prim;
    s32 var_s1;
    s32 var_s4;

    var_s1 = GetPlayerCollisionWith(self, 0x10, 0x10, 5);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
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
        prim->u0 = 8;
        prim->v0 = 200;
        prim->u1 = 32;
        prim->v1 = 32;
        prim->priority = 112;
        prim->drawMode = DRAW_UNK02;
    case 1:
        self->velocityX = 0;
        self->velocityY = 0;
        player = &PLAYER;
        if (var_s1 & 1) {
            if ((GetSideToPlayer() & 1) && player->velocityX > 0) {
                if (!(g_Timer & 7)) {
                    g_api.PlaySfx(SFX_STONE_MOVE_B);
                }
                self->velocityX = FIX(0.5);
            }
            if ((GetSideToPlayer() & 1) ^ 1 && player->velocityX < 0) {
                if (!(g_Timer & 7)) {
                    g_api.PlaySfx(SFX_STONE_MOVE_B);
                }
                self->velocityX = FIX(-0.5);
            }
        }
        UnkCollisionFunc2(D_80180EB8);
        if (!self->params) {
            var_s1 = 0;
            var_s4 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (abs(var_s4 - 192) < 24) {
                var_s1 = 1;
            }
            if (abs(var_s4 - 256) < 24) {
                var_s1 = 2;
            }
            if (self->ext.nz0311c0.unk84 == 0 && D_801CB738[var_s1 - 1]) {
                self->posX.val -= self->velocityX;
                var_s1 = 0;
            }
            self->ext.nz0311c0.unk84 = var_s1;
            if (self->ext.nz0311c0.unk84 != 0) {
                self->posY.i.hi = (0x1C0 - g_Tilemap.scrollY.i.hi) -
                                  D_801CB738[self->ext.nz0311c0.unk84 - 1];
            }
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi - 16;
}
