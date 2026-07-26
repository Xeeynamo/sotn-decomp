// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitArcher;
extern s16 g_RdaiArcherOffsets[][2];

#define RDAI_ARCHER_TIMER(self) (*(s16*)((u8*)&(self)->ext + 4))
#define RDAI_ARCHER_MODE(self) (*((u8*)&(self)->ext + 9))

void func_us_801BFE6C(Entity* self) {
    Entity* entity;
    s32 i;
    s32 animIndex;
    s32 playerX;
    s32 playerY;
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
            RDAI_ARCHER_TIMER(self) = 0x80;
            RDAI_ARCHER_MODE(self) = 0;
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
        if (!--RDAI_ARCHER_TIMER(self)) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            RDAI_ARCHER_TIMER(self) = 0x60;
            RDAI_ARCHER_MODE(self) = 1;
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
            if (!--RDAI_ARCHER_TIMER(self)) {
                PlaySfxPositional(0x628);
                RDAI_ARCHER_MODE(self) = 2;
                RDAI_ARCHER_TIMER(self) = 0x30;
                self->step_s++;
            }
            break;

        case 2:
            if (!--RDAI_ARCHER_TIMER(self)) {
                RDAI_ARCHER_MODE(self) = 3;
                RDAI_ARCHER_TIMER(self) = 0x80;
                self->step_s++;
            }
            break;

        case 3:
            if (!--RDAI_ARCHER_TIMER(self)) {
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

#undef RDAI_ARCHER_TIMER
#undef RDAI_ARCHER_MODE
