// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitRdaiUnk1F;

#define RDAI_UNK1F_ANGLE(self) (*(s16*)((u8*)&(self)->ext + 0xC))

void EntityRdaiUnk1F(Entity* self) {
    Entity* entity;
    s32 velocity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRdaiUnk1F);
#if defined(VERSION_PSP)
        self->step = self->params + 1;
        self->hitboxOffX = -2;
        self->hitboxOffY = 6;
#else
        self->hitboxOffX = -2;
        self->hitboxOffY = 6;
        self->step = self->params + 1;
#endif
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
        self->posY.i.hi +=
            abs((rsin(RDAI_UNK1F_ANGLE(self)) << 3) >> 12);
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
        self->posY.i.hi +=
            abs((rsin(RDAI_UNK1F_ANGLE(self)) << 3) >> 12);
        break;
    }
}

#undef RDAI_UNK1F_ANGLE
