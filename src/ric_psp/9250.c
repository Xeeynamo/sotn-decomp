// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

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

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", RicSetFall);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", RicSetJump);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", RicSetHighJump);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", func_pspeu_092AFA90);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", func_pspeu_092AFB68);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", func_pspeu_092AFDA8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", RicDoCrash);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", RicSetDeadPrologue);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", func_pspeu_092B05A8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", RicSetSlideKick);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/9250", RicSetBladeDash);
