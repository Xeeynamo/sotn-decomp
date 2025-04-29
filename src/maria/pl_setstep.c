// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

void MarSetDebug() { MarSetStep(PL_S_DEBUG); }

void MarSetInit(s32 step_s) {
    PLAYER.step = PL_S_INIT;
    PLAYER.step_s = step_s;
    PLAYER.pose = PLAYER.poseTimer = 0;
    if (step_s & 1) {
        PLAYER.anim = mar_80155950;
    } else {
        PLAYER.anim = mar_8015591C;
    }
}

void MarSetCrouch(s32 kind, s32 velocityX) {
    MarSetStep(PL_S_CROUCH);
    MarSetAnimation(mar_anim_crouch);
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    if (kind == 1) {
        PLAYER.anim = mar_anim_crouch_from_stand;
        PLAYER.step_s = 4;
    }
    if (kind == 2) {
        PLAYER.anim = mar_anim_crouch_from_stand;
        PLAYER.step_s = 1;
    }
    if (kind == 3) {
        PLAYER.anim = mar_anim_crouch_from_stand;
        PLAYER.step_s = 4;
    }
}

void MarSetStand(s32 velocityX) {
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    g_Player.unk44 = 0;
    MarSetStep(PL_S_STAND);
    switch (g_Player.prev_step) {
    case PL_S_JUMP:
        MarSetAnimation(D_pspeu_092C0630);
        break;
    case PL_S_RUN:
        MarSetAnimation(D_pspeu_092C04B8);
        break;
    default:
        MarSetAnimation(mar_anim_stand_relax);
        break;
    }
}

void MarSetWalk(s32 arg0) {
    g_Player.unk44 = 0;
    MarSetStep(PL_S_WALK);
    if (g_Player.unk4C) {
        MarSetAnimation(D_pspeu_092C04A8);
    } else {
        MarSetAnimation(D_pspeu_092C0498);
    }
    MarSetSpeedX(FIX(2.25));
    PLAYER.velocityY = 0;
}

void MarSetFall(void) {
    if (g_Player.prev_step != PL_S_SLIDE && g_Player.prev_step != PL_S_RUN) {
        PLAYER.velocityX = 0;
    }
    if (g_Player.prev_step != PL_S_WALK) {
        MarSetAnimation(mar_80155534);
    }
    MarSetStep(PL_S_FALL);
    PLAYER.velocityY = FIX(2);
    g_Player.timers[PL_T_5] = 8;
    g_Player.timers[PL_T_6] = 8;
    if (g_Player.prev_step == PL_S_SLIDE) {
        g_Player.timers[PL_T_5] = g_Player.timers[PL_T_6] = 0;
        PLAYER.pose = 2;
        PLAYER.poseTimer = 0x10;
        PLAYER.velocityX /= 2;
    }
}

void MarSetJump(s32 setunk44Flag) {
    if (g_Player.unk72) {
        MarSetFall();
        return;
    }
    if (MarCheckFacing() != 0 || PLAYER.step == Player_Slide) {
        MarSetAnimation(D_pspeu_092C0528);
        MarSetSpeedX(FIX(2.25));
        g_Player.unk44 = 0;
    } else {
        MarSetAnimation(D_pspeu_092C0620);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
    }
    MarSetStep(PL_S_JUMP);
    PLAYER.velocityY = FIX(-5.4375);
    if (setunk44Flag) {
        g_Player.unk44 &= ~1;
    } else {
        g_Player.unk44 |= 1;
    }
}

void func_pspeu_092B2040(void) {
    g_Player.unk44 |= 0x21;
    MarSetAnimation(D_pspeu_092C05A0);
    MarSetStep(PL_S_JUMP);
    PLAYER.step_s = 0;
    PLAYER.velocityY = FIX(-4.25);
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

void MarSetRun(s32 arg0) {
    AnimationFrame* anim;

    g_Player.unk44 = 1;
    MarSetStep(PL_S_RUN);
    if (arg0) {
        anim = D_pspeu_092C0668;
    } else {
        anim = D_pspeu_092C06A0;
    }
    MarSetAnimation(anim);
    g_CurrentEntity->velocityY = 0;
    if (arg0) {
        MarSetSpeedX(FIX(-8));
    } else {
        MarSetSpeedX(FIX(8));
    }
    g_api.PlaySfx(SFX_WEAPON_SCRAPE_ECHO);
}

void MarSetHighJump(void) {
    MarSetStep(PL_S_HIGHJUMP);
    PLAYER.velocityX = 0;
    PLAYER.velocityY = FIX(-5.0);
    g_Player.high_jump_timer = 0;
    MarSetAnimation(mar_anim_high_jump);
    func_8015CC28();
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

static s32 MarCheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
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

extern s16 D_pspeu_092C5040[];
static void PlayGruntAttackSoundEffect(s32 max) {
    s16 sfxIndex;

    if (max) {
        sfxIndex = rand() % max;
        if (sfxIndex < 5) {
            func_9142FC8(D_pspeu_092C5040[sfxIndex]);
        }
    }
}

bool MarDoAttack(void) {
    s32 var_s0;

    var_s0 = 0;
    if (MarDoSubweapon() == 0) {
        return 1;
    }
    if (PLAYER.step != PL_S_STAND && PLAYER.step != PL_S_WALK &&
        PLAYER.step != PL_S_FALL && PLAYER.step != PL_S_JUMP &&
        PLAYER.step != PL_S_CROUCH && PLAYER.step != PL_S_18) {
        return 0;
    }
    if (g_Player.timers[PL_T_8] > 0) {
        return 0;
    }
    if (MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_OWL, 0)) {
        switch (PLAYER.step) {
        case PL_S_18:
        case PL_S_STAND:
            PLAYER.step = 0;
            MarSetAnimation(D_pspeu_092C06C8);
            g_CurrentEntity->velocityX = 0;
            break;
        case PL_S_WALK:
            var_s0 = 1;
            break;
        case PL_S_CROUCH:
            MarSetAnimation(D_pspeu_092C0730);
            g_CurrentEntity->velocityX = 0;
            break;
        case PL_S_FALL:
        case PL_S_JUMP:
            PLAYER.step = 4;
            MarSetAnimation(D_pspeu_092C0720);
            break;
        default:
            return false;
        }
        g_Player.timers[PL_T_ATTACK] = 4;
        g_Player.timers[PL_T_8] = 13;
        g_api_PlaySfx(SFX_BONE_SWORD_SWISH_C);
        PlayGruntAttackSoundEffect(10);
        return true;
    }
    return false;
}

s32 MarDoSubweapon(void) {
    SubweaponDef subweapon;
    s16 subweaponId;
    s16 chainLimit;
    s16 unused;

    unused = 0;
    if (g_Player.unk7A) {
        return 1;
    }
    if (PLAYER.step != PL_S_STAND && PLAYER.step != PL_S_WALK &&
        PLAYER.step != PL_S_FALL && PLAYER.step != PL_S_JUMP &&
        PLAYER.step != PL_S_CROUCH) {
        return 0;
    }
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
    if (MarCheckSubwpnChainLimit(subweaponId, chainLimit) < 0) {
        return 2;
    }
    subweaponId = func_8015FB84(&subweapon, false, true);
    if (subweaponId <= 0) {
        return 3;
    }
    if (g_Player.unk72) {
        return 5;
    }
    if (subweaponId == _PL_W_DAGGER &&
        (PLAYER.step == PL_S_FALL || PLAYER.step == PL_S_JUMP ||
         PLAYER.velocityX || PLAYER.velocityY)) {
        return 0;
    }

    MarCreateEntFactoryFromEntity(g_CurrentEntity, subweapon.blueprintNum, 0);
    g_Player.timers[PL_T_10] = 4;
    switch (PLAYER.step) {
    case PL_S_STAND:
    case PL_S_WALK:
    case PL_S_CROUCH:
        if (subweaponId == _PL_W_DAGGER) {
            g_Player.unk7A = 2;
            MarSetAnimation(D_pspeu_092C0878);
            PLAYER.step = PL_S_SUBWPN_28;
        } else {
            g_Player.unk7A = 3;
            MarSetAnimation(D_pspeu_092C06C8);
            PLAYER.step = PL_S_STAND;
        }
        break;
    }
    g_Player.unk46 = 3;
    PLAYER.step_s = 0x42;
    g_Player.timers[PL_T_10] = 4;
    func_9142FC8(0x8EB);
    return 0;
}

bool MarDoCrash(void) {
    SubweaponDef subWpn;
    Entity* subWpnEnt;
    s16 subWpnID;

    subWpnEnt = NULL;
    if (g_Player.unk5C) {
        return 0;
    }
    subWpnID = func_8015FB84(&subWpn, true, false);
    if (subWpnID < 0) {
        return 0;
    }
    if (subWpnID != PL_W_NONE &&
        (PLAYER.step == PL_S_FALL || PLAYER.step == PL_S_JUMP)) {
        return 0;
    }
    if (subWpn.blueprintNum) {
        subWpnEnt = MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(subWpn.blueprintNum, 0), 0);
    }
    if (subWpnEnt == NULL) {
        return 0;
    }
    subWpnID = func_8015FB84(&subWpn, true, true);
    g_Player.unk4A = subWpnID;
    g_Player.unk46 = 4;
    g_Player.unk4E = 0;
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    switch (subWpnID) {
    case 0:
        if (PLAYER.step == PL_S_FALL || PLAYER.step == PL_S_JUMP) {
            MarSetAnimation(D_pspeu_092C0720);
        } else if (PLAYER.step == PL_S_STAND || PLAYER.step == PL_S_WALK) {
            MarSetAnimation(D_pspeu_092C06C8);
        } else {
            MarSetAnimation(mar_anim_stand_relax);
        }
        g_api.PlaySfx(SFX_VO_MAR_8EC);
        g_Player.unk46 = 0;
        break;
    case 1:
        g_Player.unk5C = 2;
        MarSetStep(PL_S_SUBWPN_19);
        MarSetAnimation(D_pspeu_092C07E8);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_VO_MAR_8EF);
        break;
    case 2:
        g_Player.unk5C = 2;
        MarSetStep(PL_S_SUBWPN_20);
        MarSetAnimation(D_pspeu_092C07E8);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_VO_MAR_8EE);
        break;
    case 3:
        g_Player.unk5C = 2;
        MarSetStep(PL_S_SUBWPN_21);
        MarSetAnimation(D_pspeu_092C07E8);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_VO_MAR_8ED);
        break;
    case 4:
        g_Player.unk5C = 2;
        MarSetStep(PL_S_SUBWPN_27);
        MarSetAnimation(D_pspeu_092C07E8);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_VO_MAR_8F0);
        break;
    }
    g_Player.timers[PL_T_12] = 4;
    return 1;
}

void MarSetSlide(void) {
    MarCheckFacing();
    MarSetStep(PL_S_SLIDE);
    MarSetAnimation(mar_80155750);
    g_CurrentEntity->velocityY = 0;
    MarSetSpeedX(FIX(4.5));
    func_8015CC28();
    MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(SFX_SCRAPE_C);
    g_Player.timers[PL_T_12] = 4;
}

void MarSetBladeDash(void) {
    MarSetStep(PL_S_BLADEDASH);
    MarSetAnimation(mar_anim_blade_dash);
    g_CurrentEntity->velocityY = 0;
    MarSetSpeedX(FIX(5.5));
    g_Player.unk46 = 5;
    g_Player.timers[PL_T_12] = 4;
    MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_BLADE_DASH, 0);
    func_8015CC28();
    g_api.PlaySfx(SFX_VO_MAR_ATTACK_C);
}
