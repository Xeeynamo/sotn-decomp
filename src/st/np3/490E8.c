#include "np3.h"

void func_801C90E8(void) {
    s32 temp = func_801BCB5C(&D_80182540);
    s16 temp2 = func_801BD308(&D_80182548, 3);

    if ((temp == 128) || (temp2 & 2)) {
        func_801BD114(5);
        return;
    }
    if ((g_CurrentEntity->ext.generic.unk7C.U8.unk0) == 0) {
        if (GetPlayerDistanceX() < 64) {
            if (g_CurrentEntity->facing != (GetPlayerSide() & 1)) {
                func_801BD114(4);
            }
        }
    } else {
        g_CurrentEntity->ext.generic.unk7C.S8.unk0--;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/490E8", EntityBoneScimitar);

// debris that rotates and falls down
void EntityBoneScimitarParts(Entity* entity) {
    if (entity->step) {
        entity->ext.generic.unk88.S8.unk0--;
        if (entity->ext.generic.unk88.S8.unk0 & 0xFF) {
            entity->unk1E += D_801824B8[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }
        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->subId = 0;
        entity->step = 0;
        return;
    }
    InitializeEntity(&D_80180AF0);
    entity->unk19 = 4;
    entity->animCurFrame = *(u8*)&entity->subId + 16;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }

    if (entity->subId & 0xF00) {
        entity->palette += entity->subId / 256;
    }
}