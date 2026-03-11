// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz0.h"

extern EInit g_EInitInteractable;

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

void EntityCannon(Entity* self) {
    s32 primIndex;
    Entity* newEntity;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        prim->type = PRIM_GT4;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = prim->u2 = 0x28;
        prim->v0 = prim->v1 = 0xA8;
        prim->u1 = prim->u3 = prim->u0 + 0x38;
        prim->v2 = prim->v3 = prim->v0 + 0x20;
        prim->x0 = prim->x2 = self->posX.i.hi + 0x18;
        prim->x1 = prim->x3 = prim->x0 - 0x38;
        prim->y0 = prim->y1 = self->posY.i.hi + 0x10;
        prim->y2 = prim->y3 = prim->y0 - 0x20;

        prim->priority = 0x70;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;

        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = prim->u2 = 0x28;
        prim->v0 = prim->v1 = 0x80;
        prim->u1 = prim->u3 = prim->u0 + 0x40;
        prim->v2 = prim->v3 = prim->v0 + 0x28;
        prim->x0 = prim->x2 = self->posX.i.hi + 0x8;
        prim->x1 = prim->x3 = prim->x0 - 0x40;
        prim->y0 = prim->y1 = 0x88 - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = prim->y0 - 0x28;

        prim->priority = 0x78;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
        break;
    case 1:
        break;
    case 2:
        prim = self->ext.prim;
        prim = prim->next;
        self->posX.i.hi = prim->x0 + 8;
        self->posX.i.lo = 0;
        MoveEntity();
        self->velocityX -= self->velocityX / 8;
        if (abs(self->velocityX < FIX(0.125))) {
            self->step++;
        }
        break;
    case 3:
        break;
    }
}

// projectile shot by cannon
void EntityCannonShot(Entity* self) {
    Entity* newEntity;
    s32 distance;

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
        distance = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (distance < 112) {
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

static s16 tiles_wall[] = {
    // intact
    0x0740, 0x0748, 0x0750, 0x0758, 0x0741, 0x0749,
    // destroyed
    0x0751, 0x0181, 0x0185, 0x0188, 0x020A, 0x0759};
void EntityCannonWall(Entity* self) {
    s32 i;
    s16* tileLayoutPtr;
    s32 tilePos;
    s32 cond;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        i = 6;
        tileLayoutPtr = tiles_wall + i;
        tilePos = 0xB9;
        for (i = 0; i < 6; i++, tileLayoutPtr++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            tilePos -= 0x10;
        }
        DestroyEntity(self);
        break;
    case 1:
        if (g_CastleFlags[NZ0_CANNON_WALL_SHORTCUT]) {
            self->step++;
        }
        break;
    case 2:
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        tileLayoutPtr = &tiles_wall[6];
        for (tilePos = 0x46, i = 0; i < 6; i++, tileLayoutPtr++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            tilePos += 0x10;
        }
        DestroyEntity(self);
        break;
    }
}
