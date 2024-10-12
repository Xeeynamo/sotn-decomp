// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

s16 func_us_801C1F98(Primitive* prim, s16 arg1) {
    s16 ret = arg1;
    s16 temp_v0;

    prim->x2 = arg1;
    prim->x0 = arg1;
    ret += 0x20;
    prim->drawMode = DRAW_UNK02;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x60;
    prim->y0 = prim->y1 = 0x2C;
    prim->y2 = prim->y3 = 0x3C;
    prim->u0 = prim->u2 = 2;

    if (ret > 0xB0) {
        temp_v0 = 0xB2 - arg1;
        prim->u1 = prim->u3 = temp_v0;
        ret = 0;
        prim->x1 = prim->x3 = 0xB0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = ret;
    }
    return ret;
}

s16 func_us_801C2044(Primitive* prim, s16 offset) {
    prim->drawMode = DRAW_UNK02;
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->v2 = prim->v3 = 0x26;
    prim->y2 = prim->y3 = offset;
    offset -= 0x20;

    if (offset < 0x44) {
        offset = 0x44 - offset;
        prim->v0 = prim->v1 = offset + 6;
        prim->y0 = prim->y1 = 0x44;

        prim = prim->next;
        prim->drawMode = DRAW_UNK02;
        prim->v0 = prim->v1 = 0x50;
        prim->v2 = prim->v3 = 0x60;
        prim->y0 = prim->y1 = 0x2C;
        prim->y2 = prim->y3 = 0x3C;
        prim->u0 = prim->u2 = 0x22 - offset;
        prim->u1 = prim->u3 = 0x22;
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi;
        prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + offset;
    } else {
        prim->v0 = prim->v1 = 6;
        prim->y0 = prim->y1 = offset;
    }
    return offset;
}

INCLUDE_ASM("st/no0/nonmatchings/41F98", func_us_801C2184);

extern u16 D_us_80180B60[];
void func_us_801C26B8(Entity* self) {
    Entity* entity = &self[self->params];
    s32 step = self->step;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B60);
        if (self->params & 16) {
            self->animCurFrame = self->params & 15;
            self->zPriority = 0x6A;
            self->step = 2;
            return;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        self->posX.i.hi = entity->posX.i.hi;
        if (self->params == step) {
            self->posY.i.hi = entity->posY.i.hi + 35;
            self->ext.generic.unk80.modeS8.unk0 =
                GetPlayerCollisionWith(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 24;
            self->ext.generic.unk80.modeS8.unk0 =
                GetPlayerCollisionWith(self, 12, 8, 6);
        }
        break;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/41F98", func_us_801C27A4);

INCLUDE_ASM("st/no0/nonmatchings/41F98", func_us_801C2A34);

INCLUDE_ASM("st/no0/nonmatchings/41F98", func_us_801C2B24);

INCLUDE_ASM("st/no0/nonmatchings/41F98", func_us_801C2CD8);

INCLUDE_ASM("st/no0/nonmatchings/41F98", func_us_801C2E7C);

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

INCLUDE_ASM("st/no0/nonmatchings/41F98", EntityWargExplosionPuffOpaque);
