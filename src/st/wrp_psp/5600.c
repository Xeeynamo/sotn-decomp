#include "common.h"
#include "game.h"
#include "sfx.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/5600", CollectGold);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/5600", CollectSubweapon);

void CollectHeartVessel(void) {
    if (g_PlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_Status.hearts += HEART_VESSEL_RICHTER;

        if (g_Status.hearts > g_Status.heartsMax) {
            g_Status.hearts = g_Status.heartsMax;
        }
    } else {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}
