// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo1/rbo1.h"

void CreateDeathFlames(void) {
    Entity* entity;
    s32 i;
    s32 style;
    s16 angle;

    style = Random() & 3;
    angle = ((Random() & 0xF) << 8) - ROT(180);
    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(UNK_1D), g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.deathFlames.unk89 = 6 - i;
            entity->ext.deathFlames.angle = angle;
            entity->ext.deathFlames.unk88 = style;
            entity->zPriority = g_CurrentEntity->zPriority + 1;
        }
    }
}
