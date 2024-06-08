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

void func_8018CB34(u16 arg0) {
    Collider collider;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &collider, 0);

    if (arg0) {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (collider.effects & EFFECT_QUICKSAND) {
            g_CurrentEntity->posY.val += FIX(0.125);
            return;
        }

        g_CurrentEntity->posY.i.hi += collider.unk18;
        return;
    }

    if (!(collider.effects & EFFECT_NOTHROUGH)) {
        MoveEntity();
        func_8018CAB0();
    }
}

extern s8 c_HeartPrizes[];

#include "../collect_heart.h"

#include "../collect_gold.h"

extern u16 D_80180DC4[];
extern u16 D_80180DF4[];
extern u32 D_091CF6DC;
extern u32 D_091CF698;
extern u16 D_psp_09246370[];
extern u16 D_psp_092462E0[];
extern u16 D_psp_09246388[];
extern u16 D_psp_092462F8[];
void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);

    if (g_PlayableCharacter == PLAYER_MARIA) {
        subWeapon = D_091CF6DC;
    } else {
        subWeapon = D_091CF698;
    }

    if (g_PlayableCharacter == PLAYER_MARIA) {
        D_091CF6DC = D_psp_09246370[subWeaponIdx - 0xe];
        func_90E4C90();
    } else {
        D_091CF698 = D_psp_092462E0[subWeaponIdx - 0xe];
    }

    if (g_PlayableCharacter != PLAYER_MARIA && subWeapon == D_091CF698 ||
        g_PlayableCharacter == PLAYER_MARIA && subWeapon == D_091CF6DC) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        if (g_PlayableCharacter == PLAYER_MARIA) {
            subWeapon = D_psp_09246388[subWeapon];
        } else {
            subWeapon = D_psp_092462F8[subWeapon];
        }
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.generic.unk88.S16.unk2 = 5;
        if (player->facingLeft ^ 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

#include "../collect_heart_vessel.h"

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", DestroyCurrentEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityPrizeDrop);

#include "../entity_explosion.h"

#include "../blink_item.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityEquipItemDrop);
