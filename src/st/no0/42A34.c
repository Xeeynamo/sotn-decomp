// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/42A34", func_us_801C2A34);

INCLUDE_ASM("st/no0/nonmatchings/42A34", func_us_801C2B24);

INCLUDE_ASM("st/no0/nonmatchings/42A34", func_us_801C2CD8);

INCLUDE_ASM("st/no0/nonmatchings/42A34", func_us_801C2E7C);

void func_us_801C3308(Entity* self) {
    g_CastleFlags[CASTLE_FLAG_1] = 1;
    DestroyEntity(self);
}

void AxeKnightDeath() {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_WARG_EXP_OPAQUE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.wargpuff.unk89 = 6 - i;
            entity->ext.wargpuff.unk84 = temp_s3;
            entity->ext.wargpuff.unk88 = temp_s4;
        }
    }
}

INCLUDE_ASM("st/no0/nonmatchings/42A34", EntityWargExplosionPuffOpaque);
