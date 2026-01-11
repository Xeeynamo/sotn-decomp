// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern s32 D_us_801CF3C8;
extern s32 D_us_801CF3CC;
extern s16 RIC_posX_i_hi;
extern s16 PLAYER_posX_i_hi;

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B4BD0);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B4EAC);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_CheckBladeDashInput);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_CheckHighJumpInput);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicMain);

void func_us_801B5A14(s32 arg0) {
    D_us_801CF3C8 = arg0;
    D_us_801CF3CC = 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", RichterThinking);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B6998);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", EntityRichter);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepStand);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepWalk);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepRun);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepJump);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepFall);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepCrouch);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicResetPose);

void func_us_801B77D8(void) {
    if (RIC_posX_i_hi - PLAYER_posX_i_hi > 0) {
        RIC.entityRoomIndex = 1;
    } else {
        RIC.entityRoomIndex = 0;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHit);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepDead);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepStandInAir);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepEnableFlameWhip);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHydrostorm);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepGenericSubwpnCrash);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepThrowDaggers);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlideKick);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepBladeDash);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B8E80);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHighJump);
