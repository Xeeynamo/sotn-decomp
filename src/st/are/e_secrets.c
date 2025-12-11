// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit D_us_80180AF8;
static s16 breakableCeilingTilesCollision[] = {
    0x0476,
    0x0477,
    0x0478,
    0x0479,
    // No collision
    0x0037,
    0x0038,
    0x0039,
    0x003A,
};

void EntityBreakableCeilingSecret(Entity* self) {
    Entity* newEntity;
    s32 j;
    s16* pSrcTile;
    s32 tileIdx;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AF8);
        self->animCurFrame = 0xA;
        self->zPriority = 0x69;

        // Determine tile indices to use
        pSrcTile = breakableCeilingTilesCollision;
        if (g_CastleFlags[ARE_SECRET_CEILING_OPEN]) {
            pSrcTile += 4; // No collision
        }

        // Update tilemap with appropriate collision
        tileIdx = 0x69;
        for (i = 0; i < 2; tileIdx += 0x40, i++) {
            for (j = 0; j < 2; pSrcTile++, j++) {
                (&g_Tilemap.fg[tileIdx])[j] = *pSrcTile;
            }
        }

        if (g_CastleFlags[ARE_SECRET_CEILING_OPEN]) {
            DestroyEntity(self);
            return;
        }

        self->hitboxState = 2;
        self->hitboxWidth = 0xD;
        self->hitboxHeight = 0x13;
        // fallthrough
    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;
    case 2:
        self->ext.breakable.breakCount++;
        self->animCurFrame++;

        newEntity =
            AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = EXPLOSION_UNK_19;
        }

        self->ext.breakable.resetTimer = 16;
        self->step++;

        if (self->ext.breakable.breakCount == 3) {
            g_CastleFlags[ARE_SECRET_CEILING_OPEN] = true;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(
                ARE_SECRET_CEILING_OPEN);

            pSrcTile = breakableCeilingTilesCollision;
            pSrcTile += 4;
            tileIdx = 0x69;
            for (i = 0; i < 2; tileIdx += 0x40, i++) {
                for (j = 0; j < 2; pSrcTile++, j++) {
                    (&g_Tilemap.fg[tileIdx])[j] = *pSrcTile;
                }
            }
            DestroyEntity(self);
        }
        break;
    case 3:
        if (!--self->ext.breakable.resetTimer) {
            self->step = 1;
        }
        break;
    }
}
