#include "st0.h"

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", EntitySecretButton);

void EntitySecretStairsEmitter(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180628);
        entity->animCurFrame = 3;
        entity->zPriority += 2;
        if (g_isSecretStairsButtonPressed) {
            entity->animCurFrame = 0;
            entity->step = 3;
        }
        break;
    case 1:
        if (g_isSecretStairsButtonPressed) {
            g_api.PlaySfx(NA_SE_SECRET_STAIRS);
            entity->step++;
        }
        break;
    case 2:
        entity->posY.val -= 0x4000;
        if (entity->posY.i.hi < -16) {
            entity->step++;
        }
        break;
    case 3:
        entity->animCurFrame = 0;
        break;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", EntitySecretStairsChunk);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", EntityStageTitleFadeout);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", EntityStageTitleCard);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", func_801ABBBC);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", func_801AC458);
