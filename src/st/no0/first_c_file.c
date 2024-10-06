// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C1854);

bool func_801A7E2C(Entity* self) {
    s16 diffX = PLAYER.posX.i.hi - self->posX.i.hi;

    diffX = abs(diffX);
    if (self->hitboxWidth >= diffX) {
        diffX = PLAYER.posY.i.hi - self->posY.i.hi;
        diffX = abs(diffX);
        return self->hitboxHeight >= diffX;
    } else {
        return false;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_801B0AA4);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C1E48);

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

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2044);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2184);

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

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C27A4);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2A34);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2B24);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2CD8);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", func_us_801C2E7C);

void func_us_801C3308(Entity* self) {
    g_CastleFlags[CASTLE_FLAG_1] = 1;
    DestroyEntity(self);
}

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", MakeExplosions);

INCLUDE_ASM("st/no0/nonmatchings/first_c_file", EntityWargExplosionPuffOpaque);
