// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/e_skelerang", func_us_801D191C);

void EntitySkelerangBoomerang(Entity* self) {
    Entity* entity;
    u8 step;
    s16 angle;
    s16 posX;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSkelerangBoomerang);
        self->drawFlags |= FLAG_DRAW_ROTZ;
        self->animCurFrame = 0;
        self->hitboxState = 0;
        break;
    case 1:
        entity = (self - 2) - self->params;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->hitboxState = 0;
        self->animCurFrame = 0;
        self->step_s = 0;
        self->ext.skelerang.unk84 = 48;
        if (self->params) {
            self->ext.skelerang.unk80 = 0;
            return;
        }
        self->ext.skelerang.unk80 = 128;
        break;
    case 2:
        self->hitboxState = 1;
        MoveEntity();
        self->rotZ += 256;
        if (!self->ext.skelerang.unk84) {
            self->step_s = 1;
        } else {
            self->ext.skelerang.unk84 -= 1;
        }
        entity = (self - 1) - self->params - self->step_s;
        angle = GetAngleBetweenEntitiesShifted(self, entity);
        step = self->step_s + 3;
        self->ext.skelerang.unk80 =
            AdjustValueWithinThreshold(step, self->ext.skelerang.unk80, angle);
        SetEntityVelocityFromAngle(self->ext.skelerang.unk80, 48);
        posX = entity->posX.i.hi - self->posX.i.hi;
        posY = entity->posY.i.hi - self->posY.i.hi;
        posX = abs(posX);
        posY = abs(posY);
        if (posX < 6 && posY < 6) {
            PlaySfxPositional(SFX_MULTI_CLOCK_TICK);
            self->step_s++;
        }
        if (self->step_s == 2) {
            self->step++;
        }
        break;
    case 3:
        self->hitboxState = 0;
        self->rotZ = 512;
        break;
    case 4:
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, self, entity);
            entity->params = 1;
        }
        DestroyEntity(self);
        break;
    }
}

void func_us_801D2318(Entity* entity) {
    Entity* parent;
    if (!entity->step) {
        InitializeEntity(g_EInitInteractable);
    }
    parent = entity - 1;
    if (parent->entityId != 0x2E) {
        DestroyEntity(entity);
    }
}
