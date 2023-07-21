#include "np3.h"

void EntityBat(Entity* entity) {
    Entity* newEntity;
    s16 xDistance;
    s16 yDistance;

    if (entity->flags & 0x100) {
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
            newEntity->params = 1;
        }
        func_801C2598(0x69C);
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180AFC);
        entity->animCurFrame = 31;
        break;

    case 1:
        xDistance = GetDistanceToPlayerX();
        yDistance = GetDistanceToPlayerY();
        if ((xDistance < 96) && (yDistance < 96) && !(GetSideToPlayer() & 2)) {
            entity->step++;
        }
        break;

    case 2:
        if (AnimateEntity(D_80182570, entity) == 0) {
            entity->facing = (GetSideToPlayer() & 1) ^ 1;
            entity->velocityY = 0xE000;
            if (entity->facing != 0) {
                entity->velocityX = 0x4000;
            } else {
                entity->velocityX = -0x4000;
            }
            entity->animFrameIdx = (Random() & 3) * 3;
            entity->animFrameDuration = 0;
            entity->step++;
        }
        break;

    case 3:
        AnimateEntity(D_80182554, entity);
        MoveEntity();
        if (GetDistanceToPlayerY() < 0x20) {
            if (entity->facing == 0) {
                entity->velocityX = -0x10000;
            } else {
                entity->velocityX = 0x10000;
            }
            *(s32*)&entity->ext.generic.unk7C.s = 0x800;
            entity->step++;
        }
        break;

    case 4:
        AnimateEntity(D_80182554, entity);
        MoveEntity();
        if ((u32)(entity->velocityY + 0x10000) > 0x20000U) {
            *(s32*)&entity->ext.generic.unk7C.s =
                (s32) - *(s32*)&entity->ext.generic.unk7C.s;
        }
        entity->velocityY += *(s32*)&entity->ext.generic.unk7C.u;
        break;
    }
}
