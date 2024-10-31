// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

// bust with red eyes that can have a candle on it
void EntityRedEyeBust(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C34);
        self->animCurFrame = 7;
        self->zPriority = 0x70;
        break;

    case 1:
        break;

    case 2:
#include "../pad2_anim_debug.h"
    }
}

// A purplish-red brick background that scrolls behind the foreground layer
void EntityPurpleBrickScrollingBackground(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 tempPosX;
    s32 tempPosY;
    s32 x, y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->posX.i.hi = 0;
        self->posY.i.hi = 0;
        self->unk68 = 0x80;
        // Composed of 15 primitives
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 15);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 4;
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xBF;
            prim->priority = 0x20;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }

    case 1:
        // Add a scrolling effect
        tempPosX = self->posX.i.hi;
        tempPosX = tempPosX & 0x7F;
        tempPosX = tempPosX - 0x80;
        tempPosY = self->posY.i.hi;
        tempPosY = (tempPosY & 0x3F) - 0x40;
        prim = self->ext.prim;
        // Primitives are laid out in a 5-tall by 3-wide grid
        for (y = 0; y < 5; y++) {
            for (x = 0; x < 3; x++) {
                prim->x0 = prim->x2 = tempPosX + (x * 0x80);
                prim->x1 = prim->x3 = prim->x0 + 0x80;
                prim->y0 = prim->y1 = tempPosY + (y * 0x40);
                prim->y2 = prim->y3 = prim->y0 + 0x40;
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
}

static u16 D_80180E54[] = {
    0x05C0, 0x05C1, 0x05C8, 0x05C9, 0x05D0, 0x05D1, 0x05D8, 0x05D9,
    0x05C2, 0x05C3, 0x05CA, 0x05CB, 0x05D2, 0x05D3, 0x05DA, 0x05DB,
    0x05C4, 0x05C5, 0x05CC, 0x05CD, 0x05D4, 0x05D5, 0x05DC, 0x05DD,
    0x05C6, 0x05C7, 0x05CE, 0x05CF, 0x05D6, 0x05D7, 0x05DE, 0x05DF};
void EntityLeftSecretRoomWall(Entity* self, u16* tileLayoutPtr, s32 tilePos) {
    Entity* newEntity;
    s32 cond;
    s32 i;

    switch (self->step) {
    case LEFT_SECRET_ROOM_WALL_INIT:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->hitboxState = 2;

        cond = g_CastleFlags[CASTLE_FLAG_129] != 0;
        tileLayoutPtr = D_80180E54 + (-cond & 24);

        tilePos = 0x260;
        for (i = 0; i < 4; i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tilePos += 0x10;
            tileLayoutPtr += 2;
        }

        if (g_CastleFlags[CASTLE_FLAG_129] != 0) {
            DestroyEntity(self);
            break;
        }

    case LEFT_SECRET_ROOM_WALL_IDLE:
        if (self->hitFlags != 0) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case LEFT_SECRET_ROOM_WALL_BREAK:
        self->ext.nz0311c0.unk84++;
        tileLayoutPtr = D_80180E54 + (self->ext.nz0311c0.unk84 * 8);

        tilePos = 0x260;
        for (i = 0; i < 4; i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tileLayoutPtr += 2;
            tilePos += 0x10;
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x13;
        }
        self->ext.nz0311c0.unk80 = 32;
        self->step++;

        if (self->ext.nz0311c0.unk84 == 3) {
            g_CastleFlags[CASTLE_FLAG_129] = 1;
            g_api.func_800F1FC4(0x81);

            for (i = 0; i < 8; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_WALL_DEBRIS, self, newEntity);
                    newEntity->posX.i.hi += (Random() & 0xF);
                    newEntity->posY.i.hi -= 0x20 - (Random() & 0x3F);
                }
            }
            DestroyEntity(self);
        }
        break;

    case LEFT_SECRET_ROOM_WALL_CHECK:
        if (--self->ext.nz0311c0.unk80 == 0) {
            self->step = LEFT_SECRET_ROOM_WALL_IDLE;
        }
        break;
    }
}

static u16 D_80180E94[] = {
    0x05B8, 0x05B8, 0x05B9, 0x05B9, 0x05B2, 0x05B3, 0x05BA, 0x05BB,
    0x05B4, 0x05B5, 0x05BC, 0x05BD, 0x05B6, 0x05B7, 0x05BE, 0x05BF};
void EntityBottomSecretRoomFloor(
    Entity* self, u16* tileLayoutPtr, s32 tilePos) {
    Entity* newEntity;
    s32 flag;
    s32 i;

    switch (self->step) {
    case BOTTOM_SECRET_ROOM_FLOOR_INIT:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 16;
        self->hitboxHeight = 16;
        self->hitboxState = 2;
        flag = (g_CastleFlags[CASTLE_FLAG_130] != 0);
        tileLayoutPtr = D_80180E94 + (-flag & 12);

        tilePos = 0x2E7;
        for (i = 0; i < 2; i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tileLayoutPtr += 2;
            tilePos += 0x10;
        }

        if (g_CastleFlags[CASTLE_FLAG_130] != 0) {
            DestroyEntity(self);
            break;
        }

    case BOTTOM_SECRET_ROOM_FLOOR_IDLE:
        if (self->hitFlags != 0) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        return;

    case BOTTOM_SECRET_ROOM_FLOOR_BREAK:
        self->ext.nz0311c0.unk84++;
        tileLayoutPtr = D_80180E94 + (self->ext.nz0311c0.unk84 * 4);

        tilePos = 0x2E7;
        for (i = 0; i < 2; i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tileLayoutPtr += 2;
            tilePos += 0x10;
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        self->ext.nz0311c0.unk80 = 32;
        self->step++;

        if (self->ext.nz0311c0.unk84 == 3) {
            g_CastleFlags[CASTLE_FLAG_130] = 1;
            g_api.func_800F1FC4(0x82);
            DestroyEntity(self);
        }
        break;

    case BOTTOM_SECRET_ROOM_FLOOR_CHECK:
        if (--self->ext.nz0311c0.unk80 == 0) {
            self->step = BOTTOM_SECRET_ROOM_FLOOR_IDLE;
        }
        break;
    }
}

// Debris produced when left wall is destroyed
void EntitySecretWallDebris(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 rnd;
    s16 rnd2;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C34);
        self->drawFlags = FLAG_DRAW_ROTZ;

        if (Random() & 1) {
            self->animCurFrame = 1;
        } else {
            self->animCurFrame = 2;
        }

        rnd = (Random() & 0x1F) + 16;
        rnd2 = ((Random() & 0x3F) * 16) | 0xC00;
        if (self->params != 0) {
            self->animCurFrame = 3;
            rnd = (Random() & 0x1F) + 16;
            rnd2 = (Random() * 6) + 0x900;
        }

        self->velocityX = rnd * rcos(rnd2);
        self->velocityY = rnd * rsin(rnd2);
        if (self->velocityX < 0) {
            self->facingLeft = 1;
        }

    case 1:
        MoveEntity();
        self->rotZ += 0x20;
        if (self->params != 0) {
            self->rotZ += 0x20;
        }

        self->velocityY += FIX(0.125);
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            if (self->params == 0) {
                PlaySfxPositional(SFX_WALL_DEBRIS_B);
                for (i = 0; i < 2; i++) {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_WALL_DEBRIS, self, newEntity);
                        newEntity->params = 0x1;
                    }
                }
                DestroyEntity(self);
                break;
            }
            if (self->velocityY < FIX(0.5)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->params = 0x10;
                }
                DestroyEntity(self);
                break;
            }
            self->velocityY = -self->velocityY;
            self->velocityY *= 2;
            self->velocityY /= 3;
        }
    }
}

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

// lever to operate cannon
static s32 D_80180ED0[] = {0};
void EntityCannonLever(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_v0;

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
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;

        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x68;
        prim->v0 = 0x80;
        prim->u1 = 8;
        prim->v1 = 0x28;
        prim->priority = 0x70;
        prim->drawMode = DRAW_UNK02;

        if (PLAYER.posX.i.hi < 128) {
            self->hitboxState = 0;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            self->velocityX = FIX(-4);
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        temp_v1_2 = self->velocityX;
        if (temp_v1_2 < 0) {
            var_v0 = temp_v1_2 + 0xF;
        } else {
            var_v0 = temp_v1_2;
        }
        temp_v0_2 = temp_v1_2 - (var_v0 >> 4);
        self->velocityX = temp_v0_2;
        if (temp_v0_2 < 0x2000) {
            self->step++;
        }
        break;

    case 3:
        D_80180ED0[0] = 1;
        break;
    }

    if (g_CastleFlags[CANNON_WALL_SHORTCUT] != 0) {
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

        if (g_CastleFlags[CANNON_WALL_SHORTCUT] != 0) {
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
        self->palette = 0x81AF;
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
            g_CastleFlags[CANNON_WALL_SHORTCUT] = 1;
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

        cond = g_CastleFlags[CANNON_WALL_SHORTCUT] != 0;
        tileLayoutPtr = (-cond & 6) + D_80180ED4;
        for (tilePos = 0x46, i = 0; i < 6; i++, tileLayoutPtr++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            tilePos += 0x10;
        }

        if (g_CastleFlags[CANNON_WALL_SHORTCUT] != 0) {
            DestroyEntity(self);
        }
        break;

    case 1:
        i = g_CastleFlags[CANNON_WALL_SHORTCUT] != 0; // TODO: !FAKE:
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

// Floor button which you kill the blood skeleton to lift the small elevator
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

// Tank (and decoration) at bottom of secret floor room. When broken,
// provides a Life Max Up
static u8 D_80180F1C[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04, 0x01, 0x05,
    0x01, 0x06, 0x01, 0x07, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00};
static u8 D_80180F30[] = {
    0x0F, 0x09, 0x06, 0x0A, 0x05, 0x0B, 0x04, 0x0C, 0x03, 0x0D,
    0x03, 0x0E, 0x03, 0x0F, 0x03, 0x10, 0x03, 0x11, 0x03, 0x12,
    0x30, 0x13, 0x01, 0x14, 0xFF, 0x00, 0x00, 0x00};
static u16 D_80180F4C[] = {0x0003, 0x0000};
void EntityLifeMaxTank(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLifeMaxTank);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;

    case 1:
        AnimateEntity(D_80180F1C, self);
        if (self->hitFlags) {
            PlaySfxPositional(SFX_GLASS_BREAK_A);
            self->hitboxState = 0;
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(D_80180F30, self) == 0) {
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
            self[1].params = D_80180F4C[self->params];
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 2;
                newEntity->posY.i.hi -= 8;
            }
            self->step++;
        }
        break;

    case 3:
        newEntity = self;
        newEntity->animCurFrame = 20;
        break;
    }
}
