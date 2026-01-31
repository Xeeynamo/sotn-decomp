// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

// lever to operate cannon
static s32 D_80180ED0[] = {0};

void EntityCannonLever(Entity* self) {
    Primitive* prim;
    Entity* player;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 4;
        self->hitboxHeight = 20;
        self->hitboxState = 2;

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
        prim->u0 = 0x68;
        prim->v0 = 0x80;
        prim->u1 = 8;
        prim->v1 = 0x28;
        prim->priority = 0x70;
        prim->drawMode = DRAW_UNK02;

        player = &PLAYER;
        if (player->posX.i.hi < 128) {
            self->hitboxState = 0;
        }
        break;

    case 1:
        if (self->hitFlags) {
            self->velocityX = FIX(-4);
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->velocityX -= self->velocityX / 16;
        if (abs(self->velocityX < FIX(0.125))) {
            self->step++;
        }
        break;

    case 3:
        D_80180ED0[0] = 1;
        break;
    }

    if (g_CastleFlags[NZ0_CANNON_WALL_SHORTCUT]) {
        self->hitboxState = 0;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 4;
    prim->y0 = self->posY.i.hi - 20;
}

// cannon for shortcut
void EntityCannon(Entity* self) {
    s16 primIndex;
    Entity* newEntity;
    Primitive* prim;
    s32 var_v0;
    s32 temp;
    s32 temp2;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x28;
        prim->v0 = 0xA8;
        prim->u1 = 0x38;
        prim->v1 = 0x20;
        prim->priority = 0x70;
        prim->drawMode = DRAW_UNK02;

        prim = prim->next;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x28;
        prim->v0 = 0x80;
        prim->u1 = 0x40;
        prim->v1 = 0x28;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = 120 - g_Tilemap.scrollY.i.hi;
        prim->priority = 0x78;
        prim->drawMode = DRAW_UNK02;

        if (g_CastleFlags[NZ0_CANNON_WALL_SHORTCUT] != 0) {
            self->step = 3;
        }
        break;

    case 1:
        if (D_80180ED0[0] != 0) {
            g_api.func_80102CD8(1);
            g_api.PlaySfx(SFX_CANNON_EXPLODE);
            self->velocityX = FIX(8);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
            }
            CreateEntityFromEntity(E_CANNON_SHOT, self, &self[1]);
            self->step++;
        }
        break;

    case 2:
        prim = self->ext.prim;
        prim = prim->next;
        self->posX.i.hi = prim->x0 + 8;
        self->posX.i.lo = 0;
        MoveEntity();

        temp = self->velocityX;
        if (temp < 0) {
            var_v0 = temp + 7;
        } else {
            var_v0 = temp;
        }

        temp2 = temp - (var_v0 >> 3);
        self->velocityX = temp - (var_v0 >> 3);

        if (temp2 < 0x2000) {
            self->step++;
        }
        break;
    }

    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 24;
    prim->y0 = self->posY.i.hi - 16;
}

// projectile shot by cannon
void EntityCannonShot(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = 1;
        self->palette = PAL_FLAG(PAL_UNK_1AF);
        self->zPriority = 0x6F;
        self->velocityX = FIX(-8);

    case 1:
        MoveEntity();
        if ((self->posX.i.hi + g_Tilemap.scrollX.i.hi) < 112) {
            g_api.func_80102CD8(1);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 3;
            }
            g_CastleFlags[NZ0_CANNON_WALL_SHORTCUT] = 1;
            DestroyEntity(self);
        }
        break;
    }
}

static u16 D_80180ED4[] = {0x0740, 0x0748, 0x0750, 0x0758, 0x0741, 0x0749};

static u16 D_80180EE0[] = {0x0751, 0x0181, 0x0185, 0x0188, 0x020A, 0x0759};

void EntityCannonWall(Entity* self) {
    u16* tileLayoutPtr;
    s32 tilePos;
    s32 cond;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);

        cond = g_CastleFlags[NZ0_CANNON_WALL_SHORTCUT] != 0;
        tileLayoutPtr = (-cond & 6) + D_80180ED4;
        for (tilePos = 0x46, i = 0; i < 6; i++, tileLayoutPtr++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            tilePos += 0x10;
        }

        if (g_CastleFlags[NZ0_CANNON_WALL_SHORTCUT] != 0) {
            DestroyEntity(self);
        }
        break;

    case 1:
        i = g_CastleFlags[NZ0_CANNON_WALL_SHORTCUT] != 0; // TODO: !FAKE:
        if (i) {
            self->step++;
        }
        break;

    case 2:
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);

        tileLayoutPtr = D_80180EE0;
        for (tilePos = 0x46, i = 0; i < 6; i++, tileLayoutPtr++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            tilePos += 0x10;
        }
        DestroyEntity(self);
    }
}
