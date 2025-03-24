// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"

void RicSetDebug() { RicSetStep(PL_S_DEBUG); }

void func_8015CC70(s32 step_s) {
    PLAYER.step = PL_S_INIT;
    PLAYER.step_s = step_s;
    PLAYER.animFrameIdx = PLAYER.animFrameDuration = 0;
    if (step_s & 1) {
        PLAYER.anim = D_80155950;
    } else {
        PLAYER.anim = D_8015591C;
    }
}

void RicSetCrouch(s32 kind, s32 velocityX) {
    RicSetStep(PL_S_CROUCH);
    RicSetAnimation(ric_anim_crouch);
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    if (kind == 1) {
        PLAYER.anim = ric_anim_crouch_from_stand2;
        PLAYER.step_s = 4;
    }
    if (kind == 2) {
        PLAYER.anim = ric_anim_crouch_from_stand;
        PLAYER.step_s = 1;
    }
    if (kind == 3) {
        PLAYER.anim = ric_anim_land_from_air_run;
        PLAYER.step_s = 4;
    }
}

// Corresponding DRA function is func_8010E570 (much more complex)
void RicSetStand(s32 velocityX) {
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    g_Player.unk44 = 0;
    RicSetStep(PL_S_STAND);
    RicSetAnimation(ric_anim_stand);
}

#if defined(VERSION_HD) || defined(VERSION_PSP) || defined(VERSION_PC)
void RicSetRun(void) {
    g_Player.unk44 = 0;
    RicSetStep(PL_S_RUN);
    RicSetAnimation(ric_anim_run);
    RicSetSpeedX(FIX(2.25));
    g_Player.timers[PL_T_RUN] = 40;
    PLAYER.velocityY = 0;
    RicCreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(BP_SMOKE_PUFF, 5), 0);
}
#endif

void RicSetWalk(s32 arg0) {
    if (g_Player.timers[PL_T_8] && !g_Player.unk7A) {
        RicSetRun();
        return;
    }
    g_Player.timers[PL_T_CURSE] = 8;
    if (g_Player.timers[PL_T_CURSE]) {
        g_Player.timers[PL_T_8] = 12;
    }
    g_Player.timers[PL_T_CURSE] = 12;
    g_Player.unk44 = 0;
    RicSetStep(PL_S_WALK);
    RicSetAnimation(ric_anim_walk);
    RicSetSpeedX(FIX(1.25));
    PLAYER.velocityY = 0;
}

#ifdef VERSION_US
void RicSetRun(void) {
    if (g_Player.unk7A) {
        RicSetWalk(0);
    } else {
        g_Player.unk44 = 0;
        RicSetStep(PL_S_RUN);
        RicSetAnimation(ric_anim_run);
        RicSetSpeedX(FIX(2.25));
        g_Player.timers[PL_T_RUN] = 40;
        PLAYER.velocityY = 0;
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_SMOKE_PUFF, 5), 0);
    }
}
#endif

void RicSetFall(void) {
    if (g_Player.prev_step != PL_S_RUN && g_Player.prev_step != PL_S_SLIDE) {
        PLAYER.velocityX = 0;
    }
    if (g_Player.prev_step != PL_S_WALK && g_Player.prev_step != PL_S_RUN) {
        RicSetAnimation(D_80155534);
    }
    if (g_Player.prev_step == PL_S_RUN) {
        g_Player.unk44 = 0x10;
    }
    RicSetStep(PL_S_FALL);
    PLAYER.velocityY = FIX(2);
    g_Player.timers[PL_T_5] = 8;
    g_Player.timers[PL_T_6] = 8;
    g_Player.timers[PL_T_CURSE] = 0;
    g_Player.timers[PL_T_8] = 0;
    if (g_Player.prev_step == PL_S_SLIDE) {
        g_Player.timers[PL_T_5] = g_Player.timers[PL_T_6] = 0;
        PLAYER.animFrameIdx = 2;
        PLAYER.animFrameDuration = 0x10;
        PLAYER.velocityX /= 2;
    }
}

void RicSetJump(void) {
    if (g_Player.unk72) {
        RicSetFall();
        return;
    }
    if (RicCheckFacing() != 0 || PLAYER.step == Player_Slide) {
        RicSetAnimation(D_8015550C);
        if (PLAYER.step == PL_S_RUN) {
            RicSetSpeedX(FIX(2.25));
            g_Player.unk44 = 0x10;
        } else {
            RicSetSpeedX(FIX(1.25));
            g_Player.unk44 = 0;
        }
    } else {
        RicSetAnimation(D_801554F0);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
    }
    RicSetStep(PL_S_JUMP);
    if (g_IsPrologueStage) {
        PLAYER.velocityY = -FIX(4.6875);
    } else {
        PLAYER.velocityY = -FIX(5.4375);
    }
}

void RicSetHighJump(void) {
    RicSetStep(PL_S_HIGHJUMP);
    PLAYER.velocityX = 0;
    RicSetSpeedX(FIX(1.25));
    PLAYER.velocityY = FIX(-7.5);
    g_Player.high_jump_timer = 0;
    RicSetAnimation(ric_anim_high_jump);
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_HIGH_JUMP, 0);
    g_api.PlaySfx(SFX_VO_RIC_ATTACK_C);
    g_Player.timers[PL_T_12] = 4;
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

static s32 RicCheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    s32 nFound;
    s32 nEmpty;

    // Iterate through entities 32-48 (which hold subweapons)
    // Any that match the proposed ID increments the count.
    // If at any point the count reaches the limit, return -1.
    entity = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0; i < 16; i++, entity++) {
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
    // This will indicate that there is an available entity slot
    // to hold the subweapon we're trying to spawn.
    // At the end, if this is zero, there are none available so return
    // -1 to indicate there is no room for the proposed subweapon.
    if (nEmpty) {
        return 0;
    }
    return -1;
}

s32 func_8015D250() {
    SubweaponDef subweapon;
    s16 subweaponId;
    s16 chainLimit;
    s16 unused;

    unused = 0;
    if (!(g_Player.padPressed & PAD_UP)) {
        return 1;
    }

    subweaponId = func_8015FB84(&subweapon, false, false);
    if (subweaponId <= 0) {
        return 1;
    }
    if (subweapon.blueprintNum == 0) {
        return 4;
    }
    chainLimit = subweapon.chainLimit;
    if (RicCheckSubwpnChainLimit(subweaponId, chainLimit) < 0) {
        return 2;
    }
    subweaponId = func_8015FB84(&subweapon, false, true);
    if (subweaponId <= 0) {
        return 3;
    }
    if (g_Player.unk72) {
        return 5;
    }

    RicCreateEntFactoryFromEntity(g_CurrentEntity, subweapon.blueprintNum, 0);
    g_Player.timers[PL_T_10] = 4;

    switch (PLAYER.step) {
    case PL_S_RUN:
        PLAYER.step = PL_S_STAND;
        RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        RicSetAnimation(D_801555E8);
        break;
    case PL_S_STAND:
    case PL_S_WALK:
    case PL_S_CROUCH:
        PLAYER.step = PL_S_STAND;
        RicSetAnimation(D_801555E8);
        break;
    case PL_S_FALL:
    case PL_S_JUMP:
        PLAYER.step = PL_S_JUMP;
        RicSetAnimation(D_80155638);
        break;
    }
    g_Player.unk46 = 3;
    PLAYER.step_s = 0x42;
    g_Player.timers[PL_T_10] = 4;
    return 0;
}

bool RicDoAttack(void) {
    s32 i;
    s16 poisoned;
    s16 sfxGrunt;

    sfxGrunt = rand() % 6;
    if (func_8015D250() == 0) {
        if (sfxGrunt == 0) {
            g_api.PlaySfx(SFX_VO_RIC_ATTACK_A);
        }
        if (sfxGrunt == 1) {
            g_api.PlaySfx(SFX_VO_RIC_ATTACK_B);
        }
        if (sfxGrunt == 2) {
            g_api.PlaySfx(SFX_VO_RIC_ATTACK_C);
        }
        return true;
    }
    if (g_Player.timers[PL_T_POISON]) {
        poisoned = true;
    } else {
        poisoned = false;
    }
    for (i = 16; i < 31; i++) {
        DestroyEntity(&g_Entities[i]);
    }
    if (RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_WHIP, poisoned), 0)) {
        if (poisoned) {
            g_api.PlaySfx(SFX_RIC_FLAME_WHIP);
        } else {
            g_api.PlaySfx(SFX_RIC_WHIP_ATTACK);
        }
        if (sfxGrunt == 0) {
            g_api.PlaySfx(SFX_VO_RIC_ATTACK_A);
        }
        if (sfxGrunt == 1) {
            g_api.PlaySfx(SFX_VO_RIC_ATTACK_B);
        }
        if (sfxGrunt == 2) {
            g_api.PlaySfx(SFX_VO_RIC_ATTACK_C);
        }
        switch (PLAYER.step) {
        case Player_Stand:
        case Player_Walk:
            PLAYER.step = PL_S_STAND;
            RicSetAnimation(D_80155588);
            g_CurrentEntity->velocityX = 0;
            break;
        case PL_S_RUN:
            PLAYER.step = PL_S_STAND;
            RicSetAnimation(D_80155588);
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
            break;
        case Player_Crouch:
            RicSetAnimation(D_801555A8);
            g_CurrentEntity->velocityX = 0;
            break;
        case Player_Fall:
        case Player_Jump:
            PLAYER.step = PL_S_JUMP;
            RicSetAnimation(D_801555C8);
            break;
        default:
            return false;
        }
        g_Player.unk46 = 1;
        PLAYER.step_s = 0x40;
        g_Player.timers[PL_T_ATTACK] = 4;
        return true;
    }
    return false;
}

bool RicDoCrash(void) {
    SubweaponDef subWpn;
    Entity* subWpnEnt;
    s16 subWpnID;

    subWpnID = func_8015FB84(&subWpn, true, false);
    if (subWpnID < 0) {
        return 0;
    }
    if (subWpnID == PL_W_HOLYWATER && g_Player.timers[PL_T_3]) {
        return 0;
    }
#if defined(VERSION_US)
    if (subWpnID == PL_W_STOPWATCH && g_unkGraphicsStruct.D_800973FC) {
        return 0;
    }
#endif
    if (subWpn.blueprintNum) {
        if (subWpnID == 1) {
            subWpnEnt = RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(subWpn.blueprintNum, 1), 0);
        } else {
            subWpnEnt = RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(subWpn.blueprintNum, 0), 0);
        }
    }
    if (subWpnEnt == NULL) {
        return 0;
    }
    if (subWpnEnt == NULL) {
        return 0;
    }
    subWpnID = func_8015FB84(&subWpn, true, true);
    g_Player.unk46 = 4;
    g_Player.unk4E = 0;
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    switch (subWpnID) {
    case SUBWPN_NONE:
        RicSetStep(PL_S_FLAME_WHIP);
        RicSetAnimation(ric_anim_flame_whip);
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_36, 1), 0);
        g_api.PlaySfx(SFX_VO_RIC_ATTACK_YELL);
        break;
    case SUBWPN_DAGGER:
        RicSetStep(PL_S_THROW_DAGGERS);
        RicSetAnimation(ric_anim_throw_daggers);
        g_api.PlaySfx(SFX_VO_RIC_ATTACK_YELL);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    case SUBWPN_AXE:
        RicSetStep(PL_S_STAND_IN_AIR);
        RicSetAnimation(ric_anim_stand_in_air);
        PLAYER.velocityY = FIX(-4.6875);
        if (g_Player.unk72) {
            PLAYER.velocityY = 0;
        }
        func_8015CC28();
        g_api.PlaySfx(SFX_VO_RIC_ATTACK_YELL);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    case SUBWPN_HOLYWATER:
        RicSetStep(PL_S_HYDROSTORM);
        RicSetAnimation(ric_anim_point_finger_up);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_VO_RIC_HYDRO_STORM);
        break;
    case SUBWPN_REBNDSTONE:
    case SUBWPN_VIBHUTI:
    case SUBWPN_AGUNEA:
        RicSetStep(PL_S_SUBWPN_CRASH);
        RicSetAnimation(ric_anim_point_finger_up);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_VO_RIC_ATTACK_YELL);
        break;
    case SUBWPN_BIBLE:
    case SUBWPN_STOPWATCH:
        RicSetStep(PL_S_SUBWPN_CRASH);
        RicSetAnimation(D_801558E4);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x40), 0);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x47), 0);
        g_api.PlaySfx(SFX_VO_RIC_ATTACK_YELL);
        break;
    case SUBWPN_CROSS:
        RicSetStep(PL_S_STAND_IN_AIR);
        RicSetAnimation(ric_anim_stand_in_air);
        PLAYER.velocityY = FIX(-4.6875);
        if (g_Player.unk72) {
            PLAYER.velocityY = 0;
        }
        func_8015CC28();
        g_api.PlaySfx(SFX_VO_RIC_PAIN_A);
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 2), 0);
        break;
    }
    g_Player.timers[PL_T_12] = 4;
    return 1;
}

void RicSetDeadPrologue() { RicSetStep(PL_S_DEAD_PROLOGUE); }

void RicSetSlide(void) {
    RicCheckFacing();
    RicSetStep(PL_S_SLIDE);
    RicSetAnimation(D_80155750);
    g_CurrentEntity->velocityY = 0;
    RicSetSpeedX(FIX(5.5));
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(SFX_RIC_SLIDE_SKID);
    g_Player.timers[PL_T_12] = 4;
}

void RicSetSlideKick(void) {
    g_Player.unk44 = 0;
    RicSetStep(PL_S_SLIDE_KICK);
    RicSetAnimation(D_8015577C);
    g_CurrentEntity->velocityY = FIX(-2);
    RicSetSpeedX(FIX(5.5));
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(SFX_VO_RIC_ATTACK_B);
    g_Player.timers[PL_T_12] = 4;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_31, 0);
}

void RicSetBladeDash(void) {
    RicSetStep(PL_S_BLADEDASH);
    RicSetAnimation(ric_anim_blade_dash);
    g_CurrentEntity->velocityY = 0;
    RicSetSpeedX(FIX(5.5));
    g_Player.unk46 = 5;
    g_Player.timers[PL_T_12] = 4;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_BLADE_DASH, 0);
    func_8015CC28();
    g_api.PlaySfx(SFX_VO_RIC_ATTACK_C);
    g_api.PlaySfx(SFX_RIC_SLIDE_SKID);
}
