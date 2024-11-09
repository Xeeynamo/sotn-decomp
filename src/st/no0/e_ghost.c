// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"
#include "common.h"

INCLUDE_ASM("st/no0/nonmatchings/e_ghost", func_us_801D5E4C);

extern s16 D_us_80181FE0[];

void EntityGhostEnemySpawner(Entity* self) {
    Entity* entity;
    s32 xPos;
    s32 yPos;
    s16* minMaxPositions;

    if (!self->step) {
        InitializeEntity(D_us_80180A88);
        self->flags &= ~FLAG_UNK_2000;
        self->ext.ghostEnemy.timer = 1;
    }
    if (!--self->ext.ghostEnemy.timer) {
        self->ext.ghostEnemy.timer = (Random() & 47) + 48;
        entity = &PLAYER;
        xPos = g_Tilemap.scrollX.i.hi + entity->posX.i.hi;
        yPos = g_Tilemap.scrollY.i.hi + entity->posY.i.hi;
        if (self->params) {
            minMaxPositions = &D_us_80181FE0[(self->params - 1) * 4];
            if (xPos < minMaxPositions[0] || xPos > minMaxPositions[1] ||
                yPos < minMaxPositions[2] || yPos > minMaxPositions[3]) {
                return;
            }
        }

        entity = AllocEntity(&g_Entities[160], &g_Entities[164]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_GHOST_ENEMY, self, entity);
            entity->zPriority = 170;
            entity->posX.i.hi = xPos - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = yPos - g_Tilemap.scrollY.i.hi;
            xPos = (Random() & 63) + 48;
            if (Random() & 1) {
                entity->posX.i.hi += xPos;
            } else {
                entity->posX.i.hi -= xPos;
            }

            yPos = ((Random() & 127) - 64);
            entity->posY.i.hi += yPos;
        }
    }
}
