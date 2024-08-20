#include "no3.h"

s32 func_801C52EC(s32*);
s32 UnkCollisionFunc(u16* hitSensors, s16 sensorCount);

void func_801D59D0(void) {
    s32 temp = func_801C52EC(&D_80183C30);
    s32 temp2 = UnkCollisionFunc(&D_80183C38, 3);

    if ((temp == 128) || (temp2 & 2)) {
        SetStep(5);
        return;
    }

    if (g_CurrentEntity->ext.generic.unk7C.U8.unk0 == 0) {
        if (GetDistanceToPlayerX() < 64) {
            if (g_CurrentEntity->facingLeft != (GetSideToPlayer() & 1)) {
                SetStep(4);
            }
        }
    } else {
        g_CurrentEntity->ext.generic.unk7C.U8.unk0--;
    }
}

INCLUDE_ASM("st/no3/nonmatchings/e_bone_scimitar", EntityBoneScimitar);

// debris that rotates and falls down
void EntityBoneScimitarParts(Entity* entity) {
    if (entity->step) {
        entity->ext.generic.unk88.S8.unk0--;
        if (entity->ext.generic.unk88.S8.unk0 & 0xFF) {
            entity->rotZ += D_80183BA8[entity->params];
            FallEntity();
            MoveEntity();
            return;
        }
        entity->entityId = E_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->params = 0;
        entity->step = 0;
        return;
    }
    InitializeEntity(D_80180B84);
    entity->drawFlags = FLAG_DRAW_ROTZ;
    entity->animCurFrame = *(u8*)&entity->params + 16;

    if (entity->facingLeft != 0) {
        entity->velocityX = -entity->velocityX;
    }

    if (entity->params & 0xF00) {
        entity->palette += entity->params / 256;
    }
}
