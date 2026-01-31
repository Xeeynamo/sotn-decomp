// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

static s32 D_80180EB4 = 0;

void BoxPuzzleFloorButton(Entity* self) {
    s32 temp_s1 = GetPlayerCollisionWith(self, 8, 8, 4);
    s16 primIndex;
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
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
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
void BoxPuzzleSpikes(Entity* self, s16 primIndex) {
    Primitive* prim;
    s8 var_v1;
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
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 40;
        prim->v0 = 200;
        prim->u1 = 32;
        prim->v1 = 32;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;

        if (self->params & D_80180EB4) {
            self->posY.i.hi = 480 - g_Tilemap.scrollY.i.hi;
            self->ext.nz0311c0.unk88 = 1;
        } else {
            self->posY.i.hi = 452 - g_Tilemap.scrollY.i.hi;
            self->ext.nz0311c0.unk88 = 0;
        }

    case 1:
        if (self->params & D_80180EB4) {
            self->posY.val += FIX(1.0);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (temp > 480) {
                self->posY.i.hi = 480 - g_Tilemap.scrollY.i.hi;
            }
            var_v1 = 1;
        } else {
            self->posY.val -= FIX(1);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (temp < 452) {
                self->posY.i.hi = 452 - g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
            var_v1 = 0;
        }

        if (self->ext.nz0311c0.unk88 != var_v1) {
            self->ext.nz0311c0.unk88 = var_v1;
            PlaySfxPositional(SFX_MAGIC_SWITCH);
        }
    }

    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi - 16;
    temp = 480 - (g_Tilemap.scrollY.i.hi + self->posY.i.hi);
    D_801CB736[self->params] = temp;
}

// movable box for spike/switch areas
static s16 D_80180EB8[][2] = {
    {0x0000, 0x0010}, {0x0010, 0x0000}, {0x0000, 0x0010},
    {0x0000, 0x0004}, {0x0002, 0xFFFC}, {0xFFFC, 0x0000}};

void EntityMovableBox(Entity* self) {
    Entity* player;
    Primitive* prim;
    s32 temp_s1 = GetPlayerCollisionWith(self, 0x10, 0x10, 5);
    s32 var_s1 = temp_s1;
    s16 primIndex;
    s32 temp_v0_2;
    s32 new_var;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
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
        prim->u0 = 8;
        prim->v0 = 200;
        prim->u1 = 32;
        prim->v1 = 32;
        prim->priority = 112;
        prim->drawMode = DRAW_UNK02;

    case 1:
        player = &PLAYER;
        self->velocityX = 0;
        self->velocityY = 0;

        if (var_s1 & 1) {
            temp_s1 = GetSideToPlayer();
            if (temp_s1 & 1 && player->velocityX > 0) {
                if (!(g_Timer & 7)) {
                    g_api.PlaySfx(SFX_STONE_MOVE_B);
                }
                self->velocityX = FIX(0.5);
            }
            temp_s1 = GetSideToPlayer();
            if (!(primIndex = (temp_s1 & 1)) && (player->velocityX < 0)) {
                if (!(g_Timer & 7)) {
                    g_api.PlaySfx(SFX_STONE_MOVE_B);
                }
                self->velocityX = FIX(-0.5);
            }
        }

        UnkCollisionFunc2(D_80180EB8);

        if (self->params == 0) {
            temp_v0_2 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (abs(temp_v0_2 - 192) < 24) {
                var_s1 = 1;
            } else {
                var_s1 = 0;
            }
            if (abs(temp_v0_2 - 256) < 24) {
                var_s1 = 2;
            }
            if ((self->ext.nz0311c0.unk84 == 0) &&
                ((s16)D_801CB736[var_s1] != 0)) {
                var_s1 = 0;
                self->posX.val -= self->velocityX;
            }
            self->ext.nz0311c0.unk84 = var_s1;
            if (var_s1 != 0) {
                self->posY.i.hi =
                    (448 - D_801CB736[var_s1]) - g_Tilemap.scrollY.i.hi;
            }
        }
        break;
    }
    prim = self->ext.prim;
    new_var = ((u16)self->posX.i.hi) - 16;
    prim->x0 = new_var;
    prim->y0 = ((u16)self->posY.i.hi) - 16;
}
