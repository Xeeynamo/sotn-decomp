#include "common.h"
#include "game.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", PreventEntityFromRespawning);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", AnimateEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", GetSideToPlayer);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", MoveEntity);

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", AllocEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", UnkEntityFunc0);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/BF50", func_8018C160);
