// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"
#include "stage.h"

INCLUDE_ASM("boss/rbo3/nonmatchings/rbo3", func_us_80191438);

INCLUDE_ASM("boss/rbo3/nonmatchings/rbo3", func_us_8019179C);

INCLUDE_ASM("boss/rbo3/nonmatchings/rbo3", func_us_80192020);

extern u16 D_us_8018048C;
extern s8 D_us_80180684[];
extern u8 D_us_801806B0[];

void func_us_801922EC(Entity* self) {
    Entity* prev;
    s32 animCurFrame;
    u8* indexes;
    s8* rect;

    if (!self->step) {
        InitializeEntity(&D_us_8018048C);
    }

    prev = self - 1;
    animCurFrame = prev->animCurFrame;
    self->posX.i.hi = prev->posX.i.hi;
    self->posY.i.hi = prev->posY.i.hi;
    self->facingLeft = prev->facingLeft;

    if (prev->ext.GS_Props.flag) {
        self->hitboxState = 1;
    } else {
        self->hitboxState = 2;
    }

    animCurFrame = prev->animCurFrame;
    indexes = D_us_801806B0;
    rect = D_us_80180684;
    rect += indexes[animCurFrame] * 4;

    self->hitboxOffX = *rect++;
    self->hitboxOffY = *rect++;
    self->hitboxWidth = *rect++;
    self->hitboxHeight = *rect++;

    if (prev->entityId != 0x17) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/rbo3/nonmatchings/rbo3", func_us_801923DC);

INCLUDE_ASM("boss/rbo3/nonmatchings/rbo3", func_us_80192998);

INCLUDE_ASM("boss/rbo3/nonmatchings/rbo3", func_us_80192B38);

INCLUDE_ASM("boss/rbo3/nonmatchings/rbo3", func_us_80192D64);

extern u16 D_us_80180444;

void func_us_80193050(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;

    if (self->step != 0) {
        return;
    }

    InitializeEntity(&D_us_80180444);
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);

    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    prim = &g_PrimBuf[primIndex];
    x = 0;
    self->primIndex = primIndex;
    self->flags |= FLAG_HAS_PRIMS;

    while (prim != NULL) {
        prim->x0 = prim->x2 = x;
        x += 0x3E;
        prim->x1 = prim->x3 = x;
        prim->tpage = 0xF;
        prim->clut = 0xC5;
        prim->u0 = prim->u2 = 0x41;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = 0xA9;
        prim->v2 = prim->v3 = 0xC6;
        prim->y0 = prim->y1 = 0x40;
        prim->y2 = prim->y3 = 0x12;
        prim->priority = 0x10;
        prim->drawMode = DRAW_DEFAULT;

        prim = prim->next;
    }
}
