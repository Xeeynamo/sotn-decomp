// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9144);

void func_us_801B9338(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9340);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B94CC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B96F4);

void BO6_RicSetStep(s16 step) {
    RIC.step = step;
    RIC.step_s = 0;
}

void BO6_RicSetAnimation(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

void DecelerateX(s32 speed) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += speed;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= speed;
        if (g_CurrentEntity->velocityX < 0)
            g_CurrentEntity->velocityX = 0;
    }
}

void DecelerateY(s32 speed) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += speed;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= speed;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

s32 BO6_RicCheckFacing(void) {
    if (g_Ric.unk44 & 2) {
        return 0;
    }

    if (RIC.facingLeft == 1) {
        if (g_Ric.padPressed & PAD_RIGHT) {
            RIC.facingLeft = 0;
            g_Ric.unk4C = 1;
            return -1;
        } else if (g_Ric.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Ric.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Ric.padPressed & PAD_LEFT) {
            RIC.facingLeft = 1;
            g_Ric.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

void BO6_RicSetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1)
        speed = -speed;
    g_CurrentEntity->velocityX = speed;
}

void func_us_801B9ACC(s32 speed) {
    if (RIC.entityRoomIndex == 1)
        speed = -speed;
    RIC.velocityX = speed;
}

void BO6_RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames) {
    if (!kind) {
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_CRASH_DAGGER, 0x15), 0);
        if (g_Ric.timers[PL_T_INVINCIBLE_SCENE] <= invincibilityFrames) {
            g_Ric.timers[PL_T_INVINCIBLE_SCENE] = invincibilityFrames;
        }
    } else if (g_Ric.timers[PL_T_INVINCIBLE] <= invincibilityFrames) {
        g_Ric.timers[PL_T_INVINCIBLE] = invincibilityFrames;
    }
}

void BO6_DisableAfterImage(s32 resetAnims, s32 arg1) {
    Primitive* prim;

    if (resetAnims) {
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
            .ext.disableAfterImage.resetFlag = 1;
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].animCurFrame =
            g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_2].animCurFrame =
                g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_3].animCurFrame =
                    0;
        prim = &g_PrimBuf[g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                              .primIndex];
        while (prim) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
        .ext.disableAfterImage.disableFlag = 1;
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
        .ext.disableAfterImage.index = MaxAfterImageIndex;
    if (arg1) {
        g_Ric.timers[PL_T_AFTERIMAGE_DISABLE] = 4;
    }
}

void func_us_801B9C14(void) {
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
            .ext.afterImage.resetFlag =
            g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                .ext.afterImage.index =
                g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
                    .ext.afterImage.timer = 0;
}

void func_us_801B9C3C(void) { BO6_RicSetStep(PL_S_DEBUG); }

extern AnimationFrame D_us_80182048[];
extern AnimationFrame D_us_80182038[];
extern AnimationFrame D_us_80182058[];
extern AnimationFrame D_us_80182050[];
void BO6_RicSetCrouch(s32 kind, s32 velocityX) {
    BO6_RicSetStep(PL_S_CROUCH);
    BO6_RicSetAnimation(D_us_80182048);
    RIC.velocityX = velocityX;
    RIC.velocityY = 0;
    if (kind == 1) {
        RIC.anim = D_us_80182038;
        RIC.step_s = 4;
    }
    if (kind == 2) {
        RIC.anim = D_us_80182058;
        RIC.step_s = 1;
    }
    if (kind == 3) {
        RIC.anim = D_us_80182050;
        RIC.step_s = 4;
    }
}

extern AnimationFrame ric_anim_stand[];
void BO6_RicSetStand(s32 velocityX) {
    RIC.velocityX = velocityX;
    RIC.velocityY = 0;
    g_Ric.unk44 = 0;
    BO6_RicSetStep(PL_S_STAND);
    BO6_RicSetAnimation(ric_anim_stand);
}

extern AnimationFrame D_us_801821F8[];
void func_us_801B9D74(void) {
    g_Ric.unk44 = 0;
    BO6_RicSetStep(PL_S_RUN);
    BO6_RicSetAnimation(D_us_801821F8);
    BO6_RicSetSpeedX(FIX(2.25));
    g_Ric.timers[PL_T_RUN] = 40;
    RIC.velocityY = 0;
    BO6_RicCreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(BP_SMOKE_PUFF, 5), 0);
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9DE4);

extern AnimationFrame D_us_80182094[];
extern AnimationFrame D_us_80182078[];
void func_us_801B9E70(void) {
    if (BO6_RicCheckFacing() != 0 || RIC.step == PL_S_SLIDE) {
        BO6_RicSetAnimation(D_us_80182094);
        if (RIC.step == PL_S_RUN) {
            BO6_RicSetSpeedX(FIX(2.25));
            g_Ric.unk44 = 0x10;
        } else {
            BO6_RicSetSpeedX(FIX(1.25));
            g_Ric.unk44 = 0;
        }
    } else {
        BO6_RicSetAnimation(D_us_80182078);
        RIC.velocityX = 0;
        g_Ric.unk44 = 4;
    }
    BO6_RicSetStep(PL_S_JUMP);
    RIC.velocityY = FIX(-4.6875);
}

extern AnimationFrame D_us_801820BC[];
void BO6_RicSetFall(void) {
    if (g_Ric.prev_step != PL_S_RUN && g_Ric.prev_step != PL_S_SLIDE) {
        RIC.velocityX = 0;
    }
    if (g_Ric.prev_step != PL_S_WALK && g_Ric.prev_step != PL_S_RUN) {
        BO6_RicSetAnimation(D_us_801820BC);
    }
    if (g_Ric.prev_step == PL_S_RUN) {
        g_Ric.unk44 = 0x10;
    }
    BO6_RicSetStep(PL_S_FALL);
    RIC.velocityY = FIX(2);
    g_Ric.timers[PL_T_5] = 8;
    g_Ric.timers[PL_T_6] = 8;
    g_Ric.timers[PL_T_CURSE] = 0;
    g_Ric.timers[PL_T_8] = 0;
    if (g_Ric.prev_step == PL_S_SLIDE) {
        g_Ric.timers[PL_T_5] = g_Ric.timers[PL_T_6] = 0;
        RIC.pose = 2;
        RIC.poseTimer = 0x10;
        RIC.velocityX /= 2;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA050);

s32 BO6_RicCheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    s32 nFound;
    s32 nEmpty;

    entity = &g_Entities[96];
    for (i = 0, nFound = 0, nEmpty = 0; i < 32; i++, entity++) {
        if (!entity->entityId) {
            nEmpty++;
        }
        if (entity->ext.subweapon.subweaponId &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }
        if (nFound >= limit) {
            return -1;
        }
    }
    if (nEmpty) {
        return 0;
    }
    return -1;
}

extern AnimationFrame D_us_80182170[];
extern AnimationFrame D_us_801821C0[];
s32 BO6_RicDoSubweapon(void) {
    SubweaponDef subweapon;
    s16 subweaponId;

    if (!(g_Ric.padPressed & PAD_UP)) {
        return 1;
    }

    subweaponId = BO6_RicCheckSubweapon(&subweapon, false, false);
    if (BO6_RicCheckSubwpnChainLimit(subweaponId, subweapon.chainLimit) < 0) {
        return 2;
    }
    BO6_RicCreateEntFactoryFromEntity(
        g_CurrentEntity, subweapon.blueprintNum, 0);
    g_Ric.timers[PL_T_10] = 4;
    switch (RIC.step) {
    case PL_S_RUN:
        RIC.step = PL_S_STAND;
        BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
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
    g_Ric.timers[PL_T_10] = 4;
    return 0;
}

extern AnimationFrame D_us_80182110[];
extern AnimationFrame D_us_80182130[];
extern AnimationFrame D_us_80182150[];
bool BO6_RicDoAttack(void) {
    s32 i;
    s16 poisoned;
    s16 sfxGrunt;

    sfxGrunt = rand() % 6;
    if (BO6_RicDoSubweapon() == 0) {
        if (sfxGrunt == 0) {
            g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_A);
        }
        if (sfxGrunt == 1) {
            g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_B);
        }
        if (sfxGrunt == 2) {
            g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_C);
        }
        if (sfxGrunt == 3) {
            g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_D);
        }
        return true;
    }
    if (g_Ric.timers[PL_T_POISON]) {
        poisoned = true;
    } else {
        poisoned = false;
    }
    for (i = 80; i < 95; i++) {
        DestroyEntity(&g_Entities[i]);
    }
    if (BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_WHIP, poisoned), 0)) {
        if (poisoned) {
            g_api.PlaySfx(SFX_RIC_FLAME_WHIP);
        } else {
            g_api.PlaySfx(SFX_BOSS_RIC_WHIP_ATTACK);
        }
        if (sfxGrunt == 0) {
            g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_A);
        }
        if (sfxGrunt == 1) {
            g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_B);
        }
        if (sfxGrunt == 2) {
            g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_C);
        }
        if (sfxGrunt == 3) {
            g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_D);
        }
        switch (RIC.step) {
        case PL_S_STAND:
        case PL_S_WALK:
            RIC.step = PL_S_STAND;
            BO6_RicSetAnimation(D_us_80182110);
            g_CurrentEntity->velocityX = 0;
            break;
        case PL_S_CROUCH:
            BO6_RicSetAnimation(D_us_80182130);
            g_CurrentEntity->velocityX = 0;
            break;
        case PL_S_FALL:
        case PL_S_JUMP:
            RIC.step = PL_S_JUMP;
            BO6_RicSetAnimation(D_us_80182150);
            break;
        case PL_S_RUN:
            RIC.step = PL_S_STAND;
            BO6_RicSetAnimation(D_us_80182110);
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_SKID_SMOKE, 0);
            break;
        default:
            return false;
        }
        g_Ric.unk46 = 1;
        RIC.step_s = 0x40;
        g_Ric.timers[PL_T_ATTACK] = 4;
        return true;
    }
    return false;
}

extern AnimationFrame D_us_801823C8[];
extern AnimationFrame D_us_80182190[];
extern AnimationFrame D_us_801821E0[];
extern AnimationFrame D_us_80182334[];
extern AnimationFrame D_us_8018246C[];
bool BO6_RicDoCrash(void) {
    SubweaponDef subWpn;
    Entity* subWpnEnt;
    s16 subWpnID;

    subWpnID = BO6_RicCheckSubweapon(&subWpn, true, false);
    if (subWpnID == PL_W_HOLYWATER && g_Ric.timers[PL_T_3]) {
        return 0;
    }
    if (subWpn.blueprintNum) {
        if (subWpnID == 1) {
            subWpnEnt = BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(subWpn.blueprintNum, 1), 0);
        } else {
            subWpnEnt = BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(subWpn.blueprintNum, 0), 0);
        }
    }
    if (subWpnEnt == NULL) {
        return 0;
    }
    g_Ric.unk46 = 4;
    g_Ric.unk4E = 0;
    RIC.velocityX = RIC.velocityY = 0;
    switch (subWpnID) {
    case SUBWPN_NONE:
        BO6_RicSetStep(PL_S_FLAME_WHIP);
        BO6_RicSetAnimation(D_us_801823C8);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_36, 1), 0);
        break;
    case SUBWPN_DAGGER:
        BO6_RicSetStep(PL_S_THROW_DAGGERS);
        BO6_RicSetAnimation(D_us_80182190);
        g_api.PlaySfx(SFX_BOSS_RIC_ITEM_CRASH_ATTACK);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    case SUBWPN_AXE:
        BO6_RicSetStep(PL_S_STAND_IN_AIR);
        BO6_RicSetAnimation(D_us_801821E0);
        RIC.velocityY = FIX(-4.6875);
        func_us_801B9C14();
        g_api.PlaySfx(SFX_BOSS_RIC_ITEM_CRASH_ATTACK);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    case SUBWPN_HOLYWATER:
        BO6_RicSetStep(PL_S_HYDROSTORM);
        BO6_RicSetAnimation(D_us_80182334);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_BOSS_RIC_HYDRO_STORM);
        break;
    case SUBWPN_CROSS:
        BO6_RicSetStep(PL_S_STAND_IN_AIR);
        BO6_RicSetAnimation(D_us_801821E0);
        RIC.velocityY = FIX(-4.6875);
        func_us_801B9C14();
        g_api.PlaySfx(SFX_BOSS_RIC_HOLY_CROSS);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    case SUBWPN_BIBLE:
    case SUBWPN_STOPWATCH:
        BO6_RicSetStep(PL_S_SUBWPN_CRASH);
        BO6_RicSetAnimation(D_us_8018246C);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_BOSS_RIC_ITEM_CRASH_ATTACK);
        break;
    case SUBWPN_REBNDSTONE:
    case SUBWPN_VIBHUTI:
    case SUBWPN_AGUNEA:
        BO6_RicSetStep(PL_S_SUBWPN_CRASH);
        BO6_RicSetAnimation(D_us_80182334);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_BOSS_RIC_ITEM_CRASH_ATTACK);
        break;
    }
    g_Ric.timers[PL_T_12] = 4;
    return 1;
}

void BO6_RicSetDeadPrologue(void) { BO6_RicSetStep(PL_S_DEAD_PROLOGUE); }

extern AnimationFrame D_us_801822D8[];
void BO6_RicSetSlide(void) {
    BO6_RicCheckFacing();
    BO6_RicSetStep(PL_S_SLIDE);
    BO6_RicSetAnimation(D_us_801822D8);
    g_CurrentEntity->velocityY = 0;
    BO6_RicSetSpeedX(FIX(5.5));
    func_us_801B9C14();
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(SFX_BOSS_RIC_SLIDE_SKID);
    g_Ric.timers[PL_T_12] = 4;
}

extern AnimationFrame D_us_80182304[];
void BO6_RicSetSlideKick(void) {
    g_Ric.unk44 = 0;
    BO6_RicSetStep(PL_S_SLIDE_KICK);
    BO6_RicSetAnimation(D_us_80182304);
    g_CurrentEntity->velocityY = FIX(-2);
    BO6_RicSetSpeedX(FIX(5.5));
    func_us_801B9C14();
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_A);
    g_Ric.timers[PL_T_12] = 4;
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_31, 0);
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA9D0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckInput);

Entity* BO6_RicGetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

Entity* BO6_RicGetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB314);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB370);

extern SubweaponDef subweapons_def[];
s32 BO6_RicCheckSubweapon(
    SubweaponDef* actualSubwpn, s32 isItemCrash, s32 useHearts) {
    s32 subwpnId;
    s32 dist;

    dist = RIC.posX.i.hi - g_Entities[0].posX.i.hi;
    if (dist < 0) {
        dist = -dist;
    }
    if (!isItemCrash) {
        if (dist < 0x50) {
            subwpnId = 3;
        } else {
            subwpnId = 4;
        }
        dist = RIC.posY.i.hi - g_Entities[0].posY.i.hi;
        if (dist >= 0x19) {
            subwpnId = 2;
        }
        if (dist < -0x18) {
            subwpnId = 3;
        }
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            subwpnId = 2;
        }
    } else {
        subwpnId = 4;
        if (g_Ric.padPressed & PAD_L2) {
            subwpnId = 2;
        } else if (g_Ric.padPressed & PAD_UP) {
            subwpnId = 3;
        } else if (g_Ric.padPressed & PAD_L1) {
            subwpnId = 9;
        } else if (g_Ric.padPressed & PAD_R1) {
            subwpnId = 5;
        }
        subwpnId = subweapons_def[subwpnId].crashId;
    }
    *actualSubwpn = subweapons_def[subwpnId];
    return subwpnId;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB5BC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByHoly);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByDark);

void func_us_801BBBC0(void) {}

void func_us_801BBBC8(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BBBD0);

Entity* BO6_RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2) {
    Entity* entity = BO6_RicGetFreeEntity(0x44, 0x50);
    if (!entity) {
        return NULL;
    }
    DestroyEntity(entity);
    entity->entityId = E_FACTORY;
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

extern u16 D_us_8018043C[];
void func_us_801BC2F0(Entity* self) {
    if (RIC.step != PL_S_SLIDE) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (!self->step) {
        InitializeEntity(D_us_8018043C);
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxOffX = 0x14;
        self->hitboxOffY = 0xC;
        self->hitboxWidth = self->hitboxHeight = 9;
        self->step = 1;
        self->ext.subweapon.subweaponId = self->hitboxState;
    }
    self->hitboxState = self->ext.subweapon.subweaponId;
    if (RIC.pose < 2) {
        self->hitboxState = 0;
    }
    if (RIC.pose >= 8) {
        DestroyEntity(self);
    }
}

extern u16 D_us_80180448[];
void func_us_801BC3E0(Entity* self) {
    if (RIC.step != PL_S_SLIDE_KICK) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (!self->step) {
        InitializeEntity(D_us_80180448);
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxOffX = 0x14;
        self->hitboxWidth = self->hitboxHeight = 9;
        self->step = 1;
    }
    if (RIC.animCurFrame == 140) {
        self->hitboxOffY = 0;
    }
    if (RIC.animCurFrame == 141) {
        self->hitboxOffY = 12;
    }
    if (self->hitFlags) {
        g_Ric.unk44 |= 0x80;
    } else {
        g_Ric.unk44 &= ~0x80;
    }
    self->hitFlags = 0;
}

extern u16 D_us_80180424[];
void func_us_801BC4F8(Entity* self) {
    if (RIC.step != PL_S_BLADEDASH) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (!self->step) {
        InitializeEntity(D_us_80180424);
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxHeight = 20;
        self->hitboxWidth = 20;
        self->hitboxHeight = 12;
        self->hitboxWidth = 12;
        self->hitboxOffY = 0;
        self->hitboxOffX = 0;
        self->ext.subweapon.subweaponId = PL_W_BIBLE_BEAM;
        self->step++;
    }
    if (RIC.pose >= 19) {
        DestroyEntity(self);
    }
}

extern u16 D_us_80180430[];
void func_us_801BC5C8(Entity* self) {
    if (RIC.step != PL_S_HIGHJUMP) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (!self->step) {
        InitializeEntity(D_us_80180430);
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxOffX = 0xC;
        self->hitboxOffY = -0x1A;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->step = 1;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC678);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByCutBlood);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD0B8);

extern AnimationFrame D_us_80181A40[];
void func_us_801BD384(Entity* self) {
    switch (self->step) {
    case 0:
        self->animSet = 2;
        self->anim = D_us_80181A40;
        self->flags = 0x28000000;
        self->zPriority = RIC.zPriority + 4;
        self->velocityY = (rand() & 0x3FFF) + 0xFFFF0000;
        self->step++;
        break;
    case 1:
        if (self->pose == 6 && self->poseTimer == 1) {
            if (rand() & 1) {
                BO6_RicCreateEntFactoryFromEntity(self, 4, 0);
            }
        }
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

s32 func_us_801BD47C(Entity* self) {
    Entity* entity;
    s32 i;

    entity = &g_Entities[80];
    for (i = 80; i < 144; i++, entity++) {
        if (entity->entityId == self->entityId &&
            entity->params == self->params) {
            if (entity != self) {
                return 1;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityPlayerBlinkWhite);
