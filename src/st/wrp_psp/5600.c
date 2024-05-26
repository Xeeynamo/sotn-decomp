#include "common.h"
#include "game.h"
#include "sfx.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/5600", CollectGold);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/5600", CollectSubweapon);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/5600", CollectHeartVessel);

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}
