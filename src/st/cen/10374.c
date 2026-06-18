// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include "game.h"

void EntityMaria(Entity* self) {
    if (self->step == 0) {
#if !defined(VERSION_HD)
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[MET_MARIA_IN_CEN] != 0) {
            DestroyEntity(self);
            return;
        }
#endif
        InitializeEntity(g_EInitSpawner);
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 10;
        self->unk5A = 0x48;
        self->palette = 0x210;
        self->zPriority = 0x80;
    }
}

s16 func_8019040C(Primitive* prim, s16 arg1) {
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
