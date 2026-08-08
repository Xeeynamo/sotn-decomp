// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

extern EInit g_EInitCommon;
extern EInit RNO0_EInitSpawner;

void func_us_801CC8F8_from_no0(Entity* self);

void EntityBackgroundPillars(Entity* self){
    Entity* entityPtr;
    s16 i;
    Primitive* prim;
    s32 primIndex;

    if (self->step) {
        return;
    }

    InitializeEntity(RNO0_EInitSpawner);
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 9);
    if (primIndex != -1) {
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->flags |= FLAG_HAS_PRIMS;
        for (i = -0x10; prim != NULL; i += 0x1E) {
            prim->tpage = 0xF;
            prim->clut = 0x2A;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xC0;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xB0;
            prim->x0 = prim->x2 = i;
            prim->x1 = prim->x3 = i + 0x20;
            prim->y0 = prim->y1 = 0x5F;
            prim->y2 = prim->y3 = 0x3F;
            prim->priority = 0;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
    }

    entityPtr = self + 1;

    for (i = -0x10; i < 0x130; i += 0x60) {
        DestroyEntity(entityPtr);
        entityPtr->entityId = E_UNK_16;
        entityPtr->pfnUpdate = func_us_801CC8F8_from_no0;
        entityPtr->posY.i.hi = 0x6A;
        entityPtr->posX.i.hi = i;
        entityPtr++;
    }
}

void func_us_801CC8F8_from_no0(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 3;
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x54;
        self->unk68 = 0xC0;
        self->flags &= ~FLAG_UNK_20000000;
        return;
    }

    if (self->posX.i.hi < -0x40) {
        self->posX.i.hi += 0x180;
    }

    if (self->posX.i.hi > 0x140) {
        self->posX.i.hi -= 0x180;
    }
}

static s16 xBase[] = {0x50, 0x68, 0x70, 0x68, 0x50, 0x38, 0x30, 0x38};
static s16 yBase[] = {0x90, 0x93, 0x9C, 0xA5, 0xA8, 0xA5, 0x9C, 0x93};
                             
// updates entity movement direction
void func_us_801CC9B4_from_no0(Entity* self) {
    u8 angle;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 5;
        self->zPriority = 1;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->ext.et_801CC9B4.currentAngle = 0;
        return;
    }
    if ((g_GameTimer & 0xF) == 0) {
        angle = (Random() & 7);
        self->ext.et_801CC9B4.targetAngle = GetAnglePointToEntityShifted(
            xBase[angle], yBase[angle]);
    }
    angle = AdjustValueWithinThreshold(8, self->ext.et_801CC9B4.currentAngle,
                                       self->ext.et_801CC9B4.targetAngle);
    SetEntityVelocityFromAngle(angle, 4);
    MoveEntity();
    self->ext.et_801CC9B4.currentAngle = angle;
}