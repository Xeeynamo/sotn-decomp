// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include "sfx.h"

extern EInit g_EInitTOPCommon;

// breakable wall behind leap stone or power of mist
extern s16 D_us_80180CBC[];
extern s16 D_us_80180CC2[];

void EntityBreakableWall(Entity* self) {
    s32 wallStatus;
    Entity* entity;
    s32 i;
    s16* wallTiles;
    s32 var_a1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTOPCommon);
        self->zPriority = 0x6A;
        self->animCurFrame = 0xF;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x18;
        self->hitboxOffX = 8;
        self->hitboxOffY = 0;
        self->hitboxState = 2;
        if (!self->params) {
            if (g_CastleFlags[OVL_EXPORT(SECRET_WALL_1_BROKEN)]) {
                wallStatus = 3;
            } else {
                wallStatus = 0;
            }
        } else if (g_CastleFlags[OVL_EXPORT(SECRET_WALL_2_BROKEN])) {
            wallStatus = 3;
        } else {
            wallStatus = 0;
        }

        wallTiles = &D_us_80180CBC[wallStatus];
        if (!self->params) {
            var_a1 = 0x2518;
        } else {
            var_a1 = 0x3518;
        }
        for (i = 0; i < 3; i++, wallTiles++) {
            g_Tilemap.fg[var_a1] = *wallTiles;
            var_a1 += 0x80;
        }
        if (wallStatus != 0) {
            DestroyEntity(self);
            break;
        }
        // fallthrough

    case 1:
        if (self->hitFlags) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        self->ext.breakable.breakCount++;
        self->animCurFrame++;
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0x13;
            entity->zPriority = self->zPriority + 1;
        }
        self->ext.breakable.resetTimer = 0x20;
        self->step++;
        if (self->ext.breakable.breakCount == 3) {
            if (!self->params) {
                g_CastleFlags[OVL_EXPORT(SECRET_WALL_1_BROKEN)] = 1;
            } else {
                g_CastleFlags[OVL_EXPORT(SECRET_WALL_2_BROKEN)] = 1;
            }
            wallTiles = D_us_80180CC2;
            if (!self->params) {
                var_a1 = 0x2518;
            } else {
                var_a1 = 0x3518;
            }

            for (i = 0; i < 3; i++, wallTiles++) {
                g_Tilemap.fg[var_a1] = *wallTiles;
                var_a1 += 0x80;
            }

            self->entityId = 0xC;
            self->pfnUpdate = EntityHeartDrop;
            self->step = 0;
            self->step_s = 0;
            self->pose = 0;
            self->poseTimer = 0;

            if (!self->params) {
                // PrizeDrops[2] = Fire Mail
                self->params = 2;
            } else {
                // PrizeDrops[1] = Turkey
                self->params = 1;
            }
            // n.b.! odd return, but necessary for PSP
            return;
        }
        break;

    case 3:
        if (--self->ext.breakable.resetTimer == 0) {
            self->step = 1;
        }
        break;
    }
}
