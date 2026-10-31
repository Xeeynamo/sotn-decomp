// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

void func_us_8019D260_from_rcen(void) {
    s16 temp_s3;
    s32 i;
    s8 temp_s4;
    Entity* entity;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(
                E_ID(UNK_16), g_CurrentEntity, entity);
            entity->ext.et_801A518C.unk89 = 6 - i;
            entity->ext.et_801A518C.unk88 = temp_s4;
            entity->params = 2;
            entity->ext.et_801A518C.unk84 = temp_s3;
            entity->zPriority = g_CurrentEntity->zPriority + 1;
        }
    }
}
