// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

s32 SpearGuardCheckCollision(void) {
    Collider collider;
    s32 x;
    s32 y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.i.hi -= 3;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi - 0x1E;
    g_api.CheckCollision(x, y, &collider, 0);

    if (collider.effects & EFFECT_SOLID) {
        y = (g_CurrentEntity->posY.i.hi += collider.unk20);
    } else {
        return false;
    }

    if (g_CurrentEntity->velocityX == 0) {
        return true;
    }

    if (g_CurrentEntity->velocityX > 0) {
        x += 0x20;
        y -= 0x24;
    } else {
        x -= 0x20;
        y += 0x1C;
    }
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_UNK_8000)) {
        return false;
    }
    return true;
}

#include "../approach_s16.h"

INCLUDE_ASM("st/rdai/nonmatchings/e_archer", func_us_801BF830);

extern EInit g_EInitRdaiUnk1F;

#define RDAI_UNK1F_ANGLE(self) (*(s16*)((u8*)&(self)->ext + 0xC))

void EntityRdaiUnk1F(Entity* self) {
    Entity* entity;
    s32 velocity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRdaiUnk1F);
        self->step = self->params + 1;
        self->hitboxOffX = -2;
        self->hitboxOffY = 6;
        break;

    case 1:
        self->animCurFrame = 2;
        entity = self - 1;
        if (entity->entityId != E_UNK_1E) {
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->zPriority = entity->zPriority + 2;
        break;

    case 2:
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 8;
        entity = self - 2;
        if (entity->entityId != E_UNK_1E) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_21, self, entity);
                entity->params = 8;
            }
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi + 0x1C;
        self->posY.i.hi = entity->posY.i.hi - 0x26;
        self->zPriority = entity->zPriority - 1;
        velocity = entity->velocityX >> 9;
        self->rotate -= velocity;
        RDAI_UNK1F_ANGLE(self) += velocity * 2;
        self->posY.i.hi += abs((rsin(RDAI_UNK1F_ANGLE(self)) << 3) >> 12);
        break;

    case 3:
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 8;
        entity = self - 3;
        if (entity->entityId != E_UNK_1E) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_21, self, entity);
                entity->params = 8;
            }
            DestroyEntity(self);
            break;
        }
        self->posX.i.hi = entity->posX.i.hi - 0x20;
        self->posY.i.hi = entity->posY.i.hi + 0x18;
        self->zPriority = entity->zPriority + 1;
        velocity = entity->velocityX >> 9;
        self->rotate -= velocity;
        RDAI_UNK1F_ANGLE(self) += velocity * 2;
        self->posY.i.hi += abs((rsin(RDAI_UNK1F_ANGLE(self)) << 3) >> 12);
        break;
    }
}

#undef RDAI_UNK1F_ANGLE

extern EInit g_EInitArcher;
extern s16 g_RdaiArcherOffsets[][2];

void func_us_801BFE6C(Entity* self) {
    Entity* entity;
    s32 i;
    s32 animIndex;
    s16 angle;
    s32 deltaX;
    s32 deltaY;

    entity = self - 4;
    self->posX.i.hi = entity->posX.i.hi + 0x28;
    self->posY.i.hi = entity->posY.i.hi + 0x10;
    animIndex = entity->animCurFrame - 0x21;
    if (animIndex >= 0) {
        s16* offsets = (s16*)g_RdaiArcherOffsets;
        offsets += animIndex * 2;
        self->posX.i.hi += offsets[0];
        self->posY.i.hi += offsets[1];
    }

    if ((self->flags & FLAG_DEAD) && self->step != 3) {
        SetStep(3);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitArcher);
        self->animCurFrame = 0x1D;
#if defined(VERSION_PSP)
        entity = self + 1;
        CreateEntityFromEntity(E_UNK_1D, self, entity);
        entity->params = 1;
        entity->nextPart = self;
        self->nextPart = entity;
        entity = self + 2;
        CreateEntityFromEntity(E_UNK_1D, self, entity);
        entity->params = 2;
        entity = self + 3;
        CreateEntityFromEntity(E_UNK_1D, self, entity);
        entity->params = 3;
#else
        CreateEntityFromEntity(E_UNK_1D, self, self + 1);
        (self + 1)->params = 1;
        (self + 1)->nextPart = self;
        self->nextPart = self + 1;
        CreateEntityFromEntity(E_UNK_1D, self, self + 2);
        (self + 2)->params = 2;
        CreateEntityFromEntity(E_UNK_1D, self, self + 3);
        (self + 3)->params = 3;
#endif
        // fallthrough

    case 1:
        if (!self->step_s) {
            self->ext.rdaiArcher.timer = 0x80;
            self->ext.rdaiArcher.mode = 0;
            self->step_s++;
        }
        entity = &PLAYER;
        deltaX = entity->posX.i.hi - self->posX.i.hi;
        deltaY = entity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(deltaY, deltaX);
        if (angle > 0x200) {
            angle = 0x200;
        }
        if (angle < -0x200) {
            angle = -0x200;
        }
        func_801CDC80(&self->rotate, angle, 8);
        if (!--self->ext.rdaiArcher.timer) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->ext.rdaiArcher.timer = 0x60;
            self->ext.rdaiArcher.mode = 1;
            self->step_s++;
            // fallthrough
        case 1:
            entity = &PLAYER;
            deltaX = entity->posX.i.hi - self->posX.i.hi;
            deltaY = entity->posY.i.hi - self->posY.i.hi;
            angle = ratan2(deltaY, deltaX);
            if (angle > 0x200) {
                angle = 0x200;
            }
            if (angle < -0x200) {
                angle = -0x200;
            }
            func_801CDC80(&self->rotate, angle, 8);
            if (!--self->ext.rdaiArcher.timer) {
                PlaySfxPositional(SFX_ARROW_SHOT_D);
                self->ext.rdaiArcher.mode = 2;
                self->ext.rdaiArcher.timer = 0x30;
                self->step_s++;
            }
            break;

        case 2:
            if (!--self->ext.rdaiArcher.timer) {
                self->ext.rdaiArcher.mode = 3;
                self->ext.rdaiArcher.timer = 0x80;
                self->step_s++;
            }
            break;

        case 3:
            if (!--self->ext.rdaiArcher.timer) {
                SetStep(1);
            }
            break;
        }
        break;

    case 3:
        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_UNK_21, self, entity);
                entity->params = i + 0x13;
            }
        }
        DestroyEntity(self);
        break;
    }
}

INCLUDE_ASM("st/rdai/nonmatchings/e_archer", func_us_801C0240);

INCLUDE_ASM("st/rdai/nonmatchings/e_archer", func_us_801C0528);

INCLUDE_ASM("st/rdai/nonmatchings/e_archer", func_us_801C0898);
