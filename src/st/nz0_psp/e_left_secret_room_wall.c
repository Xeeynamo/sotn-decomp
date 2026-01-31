// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../nz0/nz0.h"

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
