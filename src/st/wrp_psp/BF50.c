#include "common.h"
#include "game.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", PreventEntityFromRespawning);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", AnimateEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", GetSideToPlayer);

void MoveEntity() {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (!current->entityId) {
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", UnkEntityFunc0);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", func_8018C160);
