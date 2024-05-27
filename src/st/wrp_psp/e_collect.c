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

extern u8* D_80180E08[];
extern s32 c_GoldPrizes[];

void CollectGold(u16 goldSize) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    goldSize -= 2;
    g_Status.gold += c_GoldPrizes[goldSize];
    if ((s32)g_Status.gold > MAX_GOLD) {
        g_Status.gold = MAX_GOLD;
    }

    if (g_unkGraphicsStruct.BottomCornerTextTimer) {
        g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
        g_unkGraphicsStruct.BottomCornerTextTimer = 0;
    }

    BottomCornerText(D_80180E08[goldSize], 1);
    DestroyEntity(g_CurrentEntity);
}

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

extern u16 D_80180458[];
extern s32 D_80180EC4[];
extern u8* D_80180F70[];
void EntityExplosion(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(D_80180458);
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->animSet = ANIMSET_DRA(2);
        entity->drawMode = 0x30;
        if (entity->params & 0xF0) {
            entity->palette = 0x8195;
            entity->drawMode = DRAW_TPAGE;
        }

        if (entity->params & 0xFF00) {
            entity->zPriority = (entity->params & 0xFF00) >> 8;
        }
        entity->params &= 15;
        entity->velocityY = D_80180EC4[entity->params];
    } else {
        entity->posY.val += entity->velocityY;
        if (!AnimateEntity(D_80180F70[entity->params], entity)) {
            DestroyEntity(entity);
        }
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", BlinkItem);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityEquipItemDrop);
