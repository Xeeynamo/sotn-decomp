// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

void func_us_801C2A34(Entity* self) {
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = -0x7FFF;
        self->animCurFrame = 0x21;
        self->zPriority = 0x50;
        self->unk5A = 0;
        self->palette = 0;
        self->drawFlags = FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
        self->unk6C = 0x60;
    }
    angle = rsin((((g_Timer % 120) << 0xC) + 0x3C) / 120);
    if (!angle) {
        g_api_PlaySfx(SFX_LOW_CLOCK_TICK);
    }
    self->rotZ = (angle >> 6) + (angle >> 7);
}

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
