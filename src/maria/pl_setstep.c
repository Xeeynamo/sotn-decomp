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

INCLUDE_ASM("maria_psp/nonmatchings/pl_setstep", func_pspeu_092B1E18);

INCLUDE_ASM("maria_psp/nonmatchings/pl_setstep", func_pspeu_092B1F30);

INCLUDE_ASM("maria_psp/nonmatchings/pl_setstep", func_pspeu_092B2040);

INCLUDE_ASM("maria_psp/nonmatchings/pl_setstep", func_pspeu_092B20B8);

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

INCLUDE_ASM("maria_psp/nonmatchings/pl_setstep", func_pspeu_092B22B8);

INCLUDE_ASM("maria_psp/nonmatchings/pl_setstep", func_pspeu_092B2348);

INCLUDE_ASM("maria_psp/nonmatchings/pl_setstep", func_pspeu_092B2590);

INCLUDE_ASM("maria_psp/nonmatchings/pl_setstep", func_pspeu_092B28B0);

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
