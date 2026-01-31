// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

static s16 tiles_wall[] = {
    // wall closed
    0x05C0, 0x05C1, 0x05C8, 0x05C9, 0x05D0, 0x05D1, 0x05D8, 0x05D9,
    // wall opening #1
    0x05C2, 0x05C3, 0x05CA, 0x05CB, 0x05D2, 0x05D3, 0x05DA, 0x05DB,
    // wall opening #2
    0x05C4, 0x05C5, 0x05CC, 0x05CD, 0x05D4, 0x05D5, 0x05DC, 0x05DD,
    // wall open
    0x05C6, 0x05C7, 0x05CE, 0x05CF, 0x05D6, 0x05D7, 0x05DE, 0x05DF};

void EntityLeftSecretRoomWall(Entity* self) {
    s32 i;
    s16* tileLayoutPtr;
    s32 tilePos;
    Entity* newEntity;

    switch (self->step) {
    case LEFT_SECRET_ROOM_WALL_INIT:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->hitboxState = 2;

        if (g_CastleFlags[NZ0_SECRET_WALL_OPEN]) {
            i = 8 * 3;
        } else {
            i = 0;
        }
        tileLayoutPtr = tiles_wall + i;
        tilePos = 0x260;
        for (i = 0; i < 4; i++, tileLayoutPtr += 2) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[1] = tileLayoutPtr[1];
            tilePos += 0x10;
        }

        if (g_CastleFlags[NZ0_SECRET_WALL_OPEN]) {
            DestroyEntity(self);
            break;
        }

    case LEFT_SECRET_ROOM_WALL_IDLE:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case LEFT_SECRET_ROOM_WALL_BREAK:
        self->ext.breakable.breakCount++;
        tileLayoutPtr = tiles_wall + (self->ext.breakable.breakCount * 8);
        tilePos = 0x260;
        for (i = 0; i < 4; i++, tileLayoutPtr += 2) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[1] = tileLayoutPtr[1];
            tilePos += 0x10;
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x13;
        }
        self->ext.breakable.resetTimer = 32;
        self->step++;

        if (self->ext.breakable.breakCount == 3) {
            g_CastleFlags[NZ0_SECRET_WALL_OPEN] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(
                NZ0_SECRET_WALL_OPEN);
            for (i = 0; i < 8; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID(WALL_DEBRIS), self, newEntity);
                    newEntity->posX.i.hi += (Random() & 0xF);
                    newEntity->posY.i.hi += (Random() & 0x3F) - 0x20;
                }
            }
            DestroyEntity(self);
        }
        break;

    case LEFT_SECRET_ROOM_WALL_CHECK:
        if (!--self->ext.breakable.resetTimer) {
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
        flag = (g_CastleFlags[NZ0_SECRET_FLOOR_OPEN] != 0);
        tileLayoutPtr = D_80180E94 + (-flag & 12);

        tilePos = 0x2E7;
        for (i = 0; i < 2; i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tileLayoutPtr += 2;
            tilePos += 0x10;
        }

        if (g_CastleFlags[NZ0_SECRET_FLOOR_OPEN] != 0) {
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
        self->ext.breakable.breakCount++;
        tileLayoutPtr = D_80180E94 + (self->ext.breakable.breakCount * 4);

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
        self->ext.breakable.resetTimer = 32;
        self->step++;

        if (self->ext.breakable.breakCount == 3) {
            g_CastleFlags[NZ0_SECRET_FLOOR_OPEN] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(
                NZ0_SECRET_FLOOR_OPEN);
            DestroyEntity(self);
        }
        break;

    case BOTTOM_SECRET_ROOM_FLOOR_CHECK:
        if (--self->ext.breakable.resetTimer == 0) {
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
        InitializeEntity(g_EInitEnemy3);
        self->drawFlags = FLAG_DRAW_ROTATE;

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
        self->rotate += 0x20;
        if (self->params != 0) {
            self->rotate += 0x20;
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
