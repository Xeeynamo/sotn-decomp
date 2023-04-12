#include "no3.h"

void EntityBat(Entity* entity) {
    Entity* newEntity;
    s16 xDistance;
    s16 yDistance;

    if (entity->flags & 0x100) {
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, entity, newEntity);
            newEntity->subId = 1;
        }
        func_801CAD28(0x69C);
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180B90);
        entity->animCurFrame = 31;
        break;

    case 1:
        xDistance = func_801C4F64();
        yDistance = func_801C4FA0();
        if ((xDistance < 0x60) && (yDistance < 0x60) &&
            !(func_801C4FD4() & 2)) {
            entity->step++;
        }
        break;

    case 2:
        if (AnimateEntity(&D_80183C60, entity) == 0) {
            entity->facing = (func_801C4FD4() & 1) ^ 1;
            entity->accelerationY = 0xE000;
            if (entity->facing != 0) {
                entity->accelerationX = 0x4000;
            } else {
                entity->accelerationX = -0x4000;
            }
            entity->animFrameIdx = (Random() & 3) * 3;
            entity->animFrameDuration = 0;
            entity->step++;
        }
        break;

    case 3:
        AnimateEntity(&D_80183C44, entity);
        MoveEntity();
        if (func_801C4FA0() < 0x20) {
            if (entity->facing == 0) {
                entity->accelerationX = -0x10000;
            } else {
                entity->accelerationX = 0x10000;
            }
            *(s32*)&entity->unk7C.s = 0x800;
            entity->step++;
        }
        break;

    case 4:
        AnimateEntity(&D_80183C44, entity);
        MoveEntity();
        if ((u32)(entity->accelerationY + 0x10000) > 0x20000U) {
            *(s32*)&entity->unk7C.s = (s32) - *(s32*)&entity->unk7C.s;
        }
        entity->accelerationY += *(s32*)&entity->unk7C.u;
        break;
    }
}
