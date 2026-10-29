// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

void MarSetInit(s32 step_s) {
    MARIA.step = PL_S_INIT;
    MARIA.step_s = step_s;
    MARIA.pose = MARIA.poseTimer = 0;
    if (step_s & 1) {
        MARIA.anim = mar_80155950;
    } else {
        MARIA.anim = mar_8015591C;
    }
}

void MarSetCrouch(s32 kind, s32 velocityX) {
    MarSetStep(PL_S_CROUCH);
    MarSetAnimation(mar_anim_crouch);
    MARIA.velocityX = velocityX;
    MARIA.velocityY = 0;

    if (kind == 1) {
        MARIA.anim = mar_anim_crouch_from_stand;
        MARIA.step_s = 4;
    }

    if (kind == 2) {
        MARIA.anim = mar_anim_crouch_from_stand;
        MARIA.step_s = 1;
    }

    if (kind == 3) {
        MARIA.anim = mar_anim_crouch_from_stand;
        MARIA.step_s = 4;
    }
}

void MarSetStand(s32 velocityX) {
    MARIA.velocityX = velocityX;
    MARIA.velocityY = 0;
    g_Maria.unk44 = 0;
    MarSetStep(PL_S_STAND);

    switch (g_Maria.prev_step) {
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

void MarSetWalk(s32 unused) {
    g_Maria.unk44 = 0;
    MarSetStep(PL_S_WALK);
    if (g_Maria.unk4C) {
        MarSetAnimation(D_pspeu_092C04A8);
    } else {
        MarSetAnimation(D_pspeu_092C0498);
    }
    MarSetSpeedX(FIX(2.25));
    MARIA.velocityY = 0;
}

void MarSetFall(void) {
    if (g_Maria.prev_step != PL_S_SLIDE && g_Maria.prev_step != PL_S_RUN) {
        MARIA.velocityX = 0;
    }

    if (g_Maria.prev_step != PL_S_WALK) {
        MarSetAnimation(mar_80155534);
    }

    MarSetStep(PL_S_FALL);
    MARIA.velocityY = FIX(2);
    g_Maria.timers[PL_T_5] = 8;
    g_Maria.timers[PL_T_6] = 8;

    if (g_Maria.prev_step == PL_S_SLIDE) {
        g_Maria.timers[PL_T_5] = g_Maria.timers[PL_T_6] = 0;
        MARIA.pose = 2;
        MARIA.poseTimer = 0x10;
        MARIA.velocityX /= 2;
    }
}

void MarSetJump(s32 setunk44Flag) {
    if (g_Maria.unk72) {
        MarSetFall();
        return;
    }

    if (MarCheckFacing() || MARIA.step == Player_Slide) {
        MarSetAnimation(D_pspeu_092C0528);
        MarSetSpeedX(FIX(2.25));
        g_Maria.unk44 = 0;
    } else {
        MarSetAnimation(D_pspeu_092C0620);
        MARIA.velocityX = 0;
        g_Maria.unk44 = 4;
    }

    MarSetStep(PL_S_JUMP);
    MARIA.velocityY = FIX(-5.4375);
    if (setunk44Flag) {
        g_Maria.unk44 &= ~1;
    } else {
        g_Maria.unk44 |= 1;
    }
}

void MarSetDoubleJump(void) {
    g_Maria.unk44 |= 0x21;
    MarSetAnimation(D_pspeu_092C05A0);
    MarSetStep(PL_S_JUMP);
    MARIA.step_s = 0;
    MARIA.velocityY = FIX(-4.25);
    if (g_Maria.unk72) {
        MARIA.velocityY = 0;
    }
}

void MarSetRun(s32 arg0) {
    AnimationFrame* anim;

    g_Maria.unk44 = 1;
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

void func_maria_8015CC28(void);

void MarSetHighJump(void) {
    MarSetStep(PL_S_HIGHJUMP);
    MARIA.velocityX = 0;
    MARIA.velocityY = FIX(-5.0);
    g_Maria.high_jump_timer = 0;
    MarSetAnimation(mar_anim_high_jump);
    func_maria_8015CC28();
    if (g_Maria.unk72) {
        MARIA.velocityY = 0;
    }
}

static s32 MarCheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    s32 nFound;
    s32 nEmpty;

    // Iterate through entities 96-112 (which hold subweapons)
    // Any that match the proposed ID increments the count.
    // If at any point the count reaches the limit, return -1.
    for (entity = &g_Entities[96], i = 0, nFound = 0, nEmpty = 0; i < 16; i++,
        entity++) {
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

// sfx
static s16 sfx_arr[] = {0x8FB, 0x8FC, 0x8FD, 0x8FF};
static void PlayGruntAttackSoundEffect(s32 max) {
    s16 sfxIndex;

    if (max) {
        sfxIndex = rand() % max;
        if (sfxIndex < (max / 2)) {
            PlaySfx(sfx_arr[sfxIndex]);
        }
    }
}

static void func_pspeu_09241BD0(s32 max) {
    s16 sfxIndex;

    if (max) {
        sfxIndex = rand() % 2;
        if (sfxIndex < (max / 2)) {
            PlaySfx(sfx_arr[sfxIndex + 2]);
        }
    }
}

bool MarDoAttack(void) {
    s32 unused = 0;
    if (MarDoSubweapon() == 0) {
        return 1;
    }

    if (MARIA.step != PL_S_STAND && MARIA.step != PL_S_WALK &&
        MARIA.step != PL_S_FALL && MARIA.step != PL_S_JUMP &&
        MARIA.step != PL_S_CROUCH && MARIA.step != PL_S_18) {
        return 0;
    }

    if (g_Maria.timers[PL_T_8] > 0) {
        return 0;
    }

    if (MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_OWL, 0)) {
        switch (MARIA.step) {
        case PL_S_18:
        case PL_S_STAND:
            MARIA.step = 0;
            MarSetAnimation(mar_80155588);
            g_CurrentEntity->velocityX = 0;
            break;
        case PL_S_WALK:
            unused = 1;
            break;
        case PL_S_CROUCH:
            MarSetAnimation(mar_801555A8);
            g_CurrentEntity->velocityX = 0;
            break;
        case PL_S_FALL:
        case PL_S_JUMP:
            MARIA.step = 4;
            MarSetAnimation(mar_801555C8);
            break;
        default:
            return false;
        }

        g_Maria.timers[PL_T_ATTACK] = 4;
        g_Maria.timers[PL_T_8] = 13;
        g_api.PlaySfx(SFX_BONE_SWORD_SWISH_C);
        PlayGruntAttackSoundEffect(4);
        return true;
    }

    return false;
}

static s32 MarDoSubweapon(void) {
    SubweaponDef subweapon;
    s16 subweaponId;
    s32 sfxId;
    s16 chainLimit;
    s16 unused = 0;

    if (!g_Maria.unk68 && g_Maria.unk7A) {
        return 1;
    }

    if (MARIA.step != PL_S_STAND && MARIA.step != PL_S_WALK &&
        MARIA.step != PL_S_FALL && MARIA.step != PL_S_JUMP &&
        MARIA.step != PL_S_CROUCH) {
        return 0;
    }

    if (!(g_Maria.padPressed & PAD_UP)) {
        return 1;
    }

    subweaponId = MarCheckSubweapon(&subweapon, false, false);
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

    subweaponId = MarCheckSubweapon(&subweapon, false, true);
    if (subweaponId <= 0) {
        return 3;
    }

    if (g_Maria.unk72) {
        return 5;
    }

    if (subweaponId == PL_W_CARDINAL &&
        (MARIA.step == PL_S_FALL || MARIA.step == PL_S_JUMP ||
         MARIA.velocityX != 0 || MARIA.velocityY != 0)) {
        return 0;
    }

    MarCreateEntFactoryFromEntity(g_CurrentEntity, subweapon.blueprintNum, 0);
    g_Maria.timers[PL_T_10] = 4;

    switch (MARIA.step) {
    case PL_S_STAND:
    case PL_S_WALK:
    case PL_S_CROUCH:
        if (subweaponId == PL_W_CARDINAL) {
            g_Maria.unk7A = 2;
            g_Maria.unk66 = 2;
            MarSetAnimation(D_pspeu_092C0878);
            MARIA.step = PL_S_CARDINAL_ATTACK;
        } else {
            g_Maria.unk7A = 2;
            MarSetAnimation(mar_80155588);
            MARIA.step = PL_S_STAND;
        }
        break;
    }

    g_Maria.unk46 = 3;
    MARIA.step_s = 0x42;
    g_Maria.timers[PL_T_10] = 4;
    sfxId = MarGetSfx();
    if (sfxId == -1) {
        func_pspeu_09241BD0(4);
    } else if (sfxId > 0) {
        PlaySfx(sfxId);
    }
    return 0;
}

bool MarDoCrash(void) {
    SubweaponDef subWpn;
    Entity* subWpnEnt;
    s16 subWpnID;

    subWpnEnt = NULL;
    if (g_Maria.unk5C) {
        return 0;
    }
    subWpnID = MarCheckSubweapon(&subWpn, true, false);
    if (subWpnID < 0) {
        return 0;
    }
    if (subWpn.blueprintNum) {
        subWpnEnt = MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(subWpn.blueprintNum, 0), 0);
    }
    if (subWpnEnt == NULL) {
        return 0;
    }
    subWpnID = MarCheckSubweapon(&subWpn, true, true);
    g_Maria.unk46 = 4;
    g_Maria.unk4E = 0;
    MARIA.velocityX = MARIA.velocityY = 0;
    switch (subWpnID) {
    case PL_W_NONE:
        if (MARIA.step == PL_S_STAND) {
            MarSetAnimation(mar_80155588);
        } else {
            MarSetAnimation(mar_anim_stand_relax);
        }
        g_Maria.unk46 = 0;
        break;
    case PL_W_CARDINAL:
        g_Maria.unk5C = 2;
        MarSetStep(PL_S_CARDINAL_CRASH);
        MarSetAnimation(anim_maria_use_crash);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_VO_MAR_8EF + MAR_SFX_OFFSET);
        break;
    case PL_W_CAT:
        g_Maria.unk5C = 2;
        MarSetStep(PL_S_CAT_CRASH);
        MarSetAnimation(anim_maria_use_crash);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_VO_MAR_8EE + MAR_SFX_OFFSET);
        break;
    case PL_W_TURTLE:
        g_Maria.unk5C = 2;
        MarSetStep(PL_S_TURTLE_CRASH);
        MarSetAnimation(anim_maria_use_crash);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_VO_MAR_8ED + MAR_SFX_OFFSET);
        break;
    case PL_W_DRAGON:
        g_Maria.unk5C = 2;
        MarSetStep(PL_S_DRAGON_CRASH);
        MarSetAnimation(anim_maria_use_crash);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
        g_api.PlaySfx(SFX_VO_MAR_8F0 + MAR_SFX_OFFSET);
        break;
    }
    g_Maria.timers[PL_T_12] = 4;
    return 1;
}

void MarSetSlide(void) {
    MarCheckFacing();
    MarSetStep(PL_S_SLIDE);
    MarSetAnimation(mar_80155750);
    g_CurrentEntity->velocityY = 0;
    MarSetSpeedX(FIX(4.5));
    func_maria_8015CC28();
    MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_SLIDE_KICK, 0);
    g_api.PlaySfx(SFX_SCRAPE_C);
    g_Maria.timers[PL_T_12] = 4;
}

void MarSetBladeDash(void) {
    MarSetStep(PL_S_BLADEDASH);
    MarSetAnimation(D_pspeu_092C05A0);
    g_CurrentEntity->velocityY = 0;
    MarSetSpeedX(FIX(5.5));
    g_Maria.unk46 = 5;
    g_Maria.timers[PL_T_12] = 4;
    MarCreateEntFactoryFromEntity(g_CurrentEntity, 0x1A, 0);
    func_maria_8015CC28();
    g_api.PlaySfx(SFX_VO_MAR_ATTACK_C + MAR_SFX_OFFSET);
}
