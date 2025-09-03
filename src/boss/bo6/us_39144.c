// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9144);

void func_us_801B9338(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9340);

// split pl_utils

// maybe func_8015C4AC
INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B94CC);

// maybe func_8015C6D4
INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B96F4);

// BO6_RicSetStep
void OVL_EXPORT(RicSetStep)(s16 step) {
    RIC.step = step;
    RIC.step_s = 0;
}

void OVL_EXPORT(RicSetAnimation)(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", DecelerateX);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", DecelerateY);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckFacing);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSpeedX);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9ACC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetInvincibilityFrames);

// similar to func_8010DFF0 in DRA or func_us_801C5354 in BO4
void OVL_EXPORT(DisableAfterImage)(s32 resetAnims, s32 time) {
    Primitive* prim;

    if (resetAnims) {
        g_Entities[E_ID_41].ext.disableAfterImage.unk7D = 1;
        g_Entities[E_ID_41].animCurFrame = g_Entities[E_ID_42].animCurFrame =
            g_Entities[E_ID_43].animCurFrame = 0;
        prim = &g_PrimBuf[g_Entities[E_ID_41].primIndex];
        while (prim != NULL) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[E_ID_41].ext.disableAfterImage.unk7C = 1;
    g_Entities[E_ID_41].ext.disableAfterImage.unk7E = 0xA;
    if (time) {
        g_Ric.timers[ALU_T_15] = 4;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9C14);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9C3C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetCrouch);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetStand);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9D74);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9DE4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9E70);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetFall);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA050);

static s32 OVL_EXPORT(RicCheckSubwpnChainLimit)(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    u32 nEmpty;
    s32 nFound;

    entity = &g_Entities[0x60];
    for (i = 0, nFound = 0, nEmpty = 0; i < 32; i++, entity++) {
        if (!entity->entityId) {
            nEmpty++;
        }

        if (entity->ext.subweapon.subweaponId != 0 &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }

        if (nFound >= limit) {
            return -1;
        }
    }

    if (nEmpty < 1) {
        return -1;
    } else {
        return 0;
    }
}

extern u16 D_us_80182170[][2];
extern u16 D_us_801821C0[][2];

s32 OVL_EXPORT(RicDoSubweapon)(void) {
    SubweaponDef subweapon;
    s16 subweaponId;
    s16 chainLimit;

    if (!(g_Ric.padPressed & PAD_UP)) {
        return 1;
    }

    subweaponId = BO6_RicCheckSubweapon(&subweapon, 0, 0);
    chainLimit = subweapon.chainLimit;
    if (OVL_EXPORT(RicCheckSubwpnChainLimit)(subweaponId, chainLimit) < 0) {
        return 2;
    }

    OVL_EXPORT(RicCreateEntFactoryFromEntity)
    (g_CurrentEntity, subweapon.blueprintNum, 0);
    g_Ric.timers[PL_T_10] = 4;
    switch (RIC.step) {
    case PL_S_RUN:
        RIC.step = PL_S_STAND;
        OVL_EXPORT(RicCreateEntFactoryFromEntity)(g_CurrentEntity, 0U, 0);
        BO6_RicSetAnimation(D_us_80182170);
        break;
    case PL_S_STAND:
    case PL_S_WALK:
    case PL_S_CROUCH:
        RIC.step = PL_S_STAND;
        BO6_RicSetAnimation(D_us_80182170);
        break;
    case PL_S_FALL:
    case PL_S_JUMP:
        RIC.step = PL_S_JUMP;
        BO6_RicSetAnimation(D_us_801821C0);
        break;
    }
    g_Ric.unk46 = 3;
    RIC.step_s = 0x42;
    // n.b.! this was just set before the switch
    g_Ric.timers[PL_T_10] = 4;
    return 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoAttack);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoCrash);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetDeadPrologue);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSlideKick);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA9D0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckInput);

static Entity* OVL_EXPORT(RicGetFreeEntity)(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicGetFreeEntityReverse);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB314);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB370);

extern SubweaponDef subweapons_def[];

s32 BO6_RicCheckSubweapon(
    SubweaponDef* actualSubwpn, s32 isItemCrash, s32 useHearts) {
    SubweaponDef* subwpn;
    SubweaponDef* wpn;
    s32 i;
    s32 subweaponId;
    s32 distanceX;

    distanceX = abs(RIC.posX.i.hi - PLAYER.posX.i.hi);

    if (isItemCrash == 0) {
        if (distanceX < 0x50) {
            subweaponId = 3;
        } else {
            subweaponId = 4;
        }
        if ((RIC.posY.i.hi - PLAYER.posY.i.hi) > 0x18) {
            subweaponId = 2;
        }
        if ((RIC.posY.i.hi - PLAYER.posY.i.hi) < -0x18) {
            subweaponId = 3;
        }
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            subweaponId = 2;
        }

        *actualSubwpn = subweapons_def[subweaponId];
    } else {
        subweaponId = 4;
        if (g_Ric.padPressed & 4) {
            subweaponId = 2;
        } else {
            if (g_Ric.padPressed & 1) {
                subweaponId = 3;
            }
            if (g_Ric.padPressed & 0x800) {
                subweaponId = 9;
            }
            if (g_Ric.padPressed & 0x100) {
                subweaponId = 5;
            }
        }

        subwpn = &subweapons_def[subweaponId];
        *actualSubwpn = subweapons_def[subwpn->crashId];
    }
    return subweaponId;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB5BC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByHoly);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByDark);

void func_us_801BBBC0(void) {}

void func_us_801BBBC8(void) {}

extern AnimationFrame* D_us_801812B8[];
extern PfnEntityUpdate D_us_8018158C[];
extern u8 D_us_801D0800;
extern u8 D_us_801D0804;
extern u8 D_us_801D0808;
extern u8 D_us_801D07FC;

void func_us_801BBBD0(void) {
    Entity* entity;
    PfnEntityUpdate entityUpdate;
    s32 i;

    entity = g_CurrentEntity = &g_Entities[E_ID_44];

    for (i = E_ID_44; i < E_ID_90; i++, g_CurrentEntity++, entity++) {
        if (entity->entityId) {
            entityUpdate = D_us_8018158C[entity->entityId];
            entityUpdate(entity);
            entity = g_CurrentEntity;

            if (entity->entityId) {
                if (!(entity->flags & FLAG_UNK_10000000) &&
                    (entity->posX.i.hi > 288 || entity->posX.i.hi < -32 ||
                     entity->posY.i.hi > 256 || entity->posY.i.hi < -16)) {
                    DestroyEntity(entity);
                } else {
                    if (entity->flags & FLAG_UNK_20000000) {
                        g_api.UpdateAnim(NULL, D_us_801812B8);
                    }
                    entity->flags |= FLAG_NOT_AN_ENEMY;
                }
            }
        }
    }

    if (D_us_801D07FC) {
        D_us_801D07FC--;
        if (D_us_801D07FC & 1) {
            g_api.func_800EA5AC(1, D_us_801D0800, D_us_801D0804, D_us_801D0808);
        }
    }
    if ((RIC.step == 0x11) || (RIC.step == 0x60) || (RIC.step == 0x70)) {
        FntPrint("dead boss\n");
        entity = &g_Entities[E_ID_44];
        for (i = E_ID_44; i < E_ID_90; i++, entity++) {
            entity->hitboxState = 0;
        };
    }
}

Entity* OVL_EXPORT(RicCreateEntFactoryFromEntity)(
    Entity* source, u32 factoryParams, s32 arg2) {
    Entity* entity = OVL_EXPORT(RicGetFreeEntity)(68, 80);
    if (!entity) {
        return NULL;
    }
    DestroyEntity(entity);
    entity->entityId = E_FACTORY;
    // the parent pointer must align for anything the factory creates
    entity->ext.factory.parent = source;
    entity->posX.val = source->posX.val;
    entity->posY.val = source->posY.val;
    entity->facingLeft = source->facingLeft;
    entity->zPriority = source->zPriority;
    entity->params = factoryParams & 0xFFF;
    entity->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    return entity;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityFactory);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC2F0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC3E0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC4F8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC5C8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC678);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByCutBlood);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD0B8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD384);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD47C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityPlayerBlinkWhite);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BE79C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityShrinkingPowerUpRing);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByIce);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByLightning);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C03E8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", EntityShaft);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C0FE8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C13A8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityWhip);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityArmBrandishWhip);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C2688);

void func_us_801C277C(void) {}

void func_us_801C2784(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnHolyWaterBreakGlass);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashHydroStorm);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_DebugShowWaitInfo);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_DebugInputWait);
INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C310C);

int WarpBackgroundBrightness() {
    return 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C32C4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnHolyWaterFlame);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnCrashCross);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C4200);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C488C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnCrossTrail);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnCrashCrossParticles);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnThrownAxe);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C560C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnKnife);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_ReboundStoneBounce1);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_ReboundStoneBounce2);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnReboundStone);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnThrownVibhuti);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_PrimDecreaseBrightness);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnAgunea);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityAguneaHitEnemy);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityVibhutiCrashCloud);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashVibhuti);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C8590);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C8618);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashReboundStoneExplosion);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashReboundStone);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashBibleBeam);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashBible);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801C9DE8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801CA340);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_GetAguneaLightningAngle);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_AguneaShuffleParams);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityAguneaLightning);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityAguneaCircle);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnStopwatchCircle);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_EntityStopWatch);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnBibleTrail);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntitySubwpnBible);

INCLUDE_RODATA("boss/bo6/nonmatchings/us_39144", D_us_801A7028);

INCLUDE_RODATA("boss/bo6/nonmatchings/us_39144", D_us_801A7030);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityCrashCrossBeam);
