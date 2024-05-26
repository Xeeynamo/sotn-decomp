#include "dre.h"

void EntityExplosion(Entity* entity) {
    u32 temp_v0;
    u32 temp;

    if (!entity->step) {
        InitializeEntity(g_InitializeEntityData0);
        entity->animSet = ANIMSET_DRA(2);
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->drawMode = 0x30;

        if (entity->params & 0xF0) {
            entity->palette = 0x8195;
            entity->drawMode = DRAW_TPAGE;
        }

        temp_v0 = entity->params & 0xFF00;

        if (temp_v0 != 0) {
            entity->zPriority = (u16)(temp_v0 >> 8);
        }

        entity->params &= 0xF;
        entity->velocityY = D_801811B0[entity->params];
        return;
    }

    entity->posY.val += entity->velocityY;
    if (!AnimateEntity(D_8018125C[entity->params], entity)) {
        DestroyEntity(entity);
    }
}

#include "../blink_item.h"
