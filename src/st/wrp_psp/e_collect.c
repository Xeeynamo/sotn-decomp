#include "../wrp/wrp.h"
#include <sfx.h>

void func_8018CAB0(void) {
    if (g_CurrentEntity->velocityY >= 0) {
        g_CurrentEntity->ext.generic.unk84.unk +=
            g_CurrentEntity->ext.generic.unk88.S16.unk0;
        g_CurrentEntity->velocityX = g_CurrentEntity->ext.generic.unk84.unk;
        if (g_CurrentEntity->velocityX == FIX(1) ||
            g_CurrentEntity->velocityX == FIX(-1)) {
            g_CurrentEntity->ext.generic.unk88.S16.unk0 =
                -g_CurrentEntity->ext.generic.unk88.S16.unk0;
        }
    }

    if (g_CurrentEntity->velocityY < FIX(0.25)) {
        g_CurrentEntity->velocityY += FIX(0.125);
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", func_8018CB34);

extern s8 c_HeartPrizes[];
void CollectHeart(u16 arg0) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_Status.hearts += c_HeartPrizes[arg0];

    if (g_Status.hearts > g_Status.heartsMax) {
        g_Status.hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", CollectGold);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", CollectSubweapon);

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

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", DestroyCurrentEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityPrizeDrop);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityExplosion);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", BlinkItem);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityEquipItemDrop);
