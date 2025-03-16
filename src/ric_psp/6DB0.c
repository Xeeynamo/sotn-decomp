// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

static TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (PLAYER.step != PL_S_STAND || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }

    // Check for X/Y boundaries in TOP
    if (g_StageId == STAGE_TOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX - 8000) < 4 &&
            abs((g_Tilemap.top << 8) + g_PlayerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX - 8384) < 4 &&
#if defined(VERSION_PSP)
            abs((g_Tilemap.top << 8) + g_PlayerY - 14407) < 4) {
#else
            abs((g_Tilemap.top << 8) + g_PlayerY) - 14407 < 4) {
#endif
            return TELEPORT_CHECK_TO_TOP;
        }
    }

    return TELEPORT_CHECK_NONE;
}

static s16 func_80156DE4(void) {
    // Variables that change during execution
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    s32 xCenter;
    s32 xRight;
    s32 xLeft;
    s32 filter;

    // Values that are set once and never again (but not const for some reason)
    filter = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
    xCenter = PLAYER.posX.i.hi;
    xRight = PLAYER.posX.i.hi + 4;
    xLeft = PLAYER.posX.i.hi - 4;

    for (i = 0; i < 3; i++) {
        yvar = PLAYER.posY.i.hi + D_80154568[i];
        collisions = 0;
        g_api.CheckCollision(xCenter, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xRight, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xLeft, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicInit);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", CheckStageCollision);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092ADEA0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AE150);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicMain);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015CC70);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetCrouch);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetStand);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AF600);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetWalk);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetFall);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetJump);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AF9D0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AFA90);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AFB68);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AFDA8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicDoCrash);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetDeadPrologue);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B05A8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetSlideKick);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B06F8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015C4AC);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B0A10);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetStep);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetAnimation);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicDecelerateX);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCheckFacing);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetSpeedX);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015CAAC);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetInvincibilityFrames);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", DisableAfterImage);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015CC28);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCheckInput);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicGetPlayerSensor);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B1CD0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B2590);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B2DD8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B3118);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", ReboundStoneBounce1);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", ReboundStoneBounce2);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnReboundStone);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnThrownVibhuti);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B4688);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnAgunea);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityAguneaHitEnemy);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityVibhutiCrashCloud);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashVibhuti);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashReboundStoneParticles);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8016D9C4);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashReboundStoneExplosion);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashReboundStone);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashBibleBeam);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashBible);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8016F198);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashStopwatchDoneSparkle);
// clang-format on

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityStopwatchCrashLightning);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashStopwatch);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BA338);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BA540);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityAguneaLightning);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityAguneaCircle);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnStopwatchCircle);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnStopwatch);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnBibleTrail);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnBible);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BE4C8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BE570);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BE628);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015FA5C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetSubweaponParams);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BE888);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BEA38);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByHoly);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByDark);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityDummy);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicUpdatePlayerEntities);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCreateEntFactoryFromEntity);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityFactory);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySlideKick);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80160D2C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityBladeDash);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80160F0C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySmokePuff);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByCutBlood);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80161C2C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80161EF8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityApplyMariaPowerAnim);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_801623E0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80162604);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityMariaPowers);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityNotImplemented4);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityMaria);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C2E98);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityPlayerBlinkWhite);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_801641A0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityShrinkingPowerUpRing);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByIce);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByLightning);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C73B0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C77B8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityTeleport);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashCrossBeam);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C8D48);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityNotImplemented3);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80167A70);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashHydroStorm);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C9988);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C9B88);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnHolyWater);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnHolyWaterFlame);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityWhip);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityArmBrandishWhip);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80167964);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityNotImplemented1);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityNotImplemented2);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnCrashCross);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityRevivalColumn);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnCross);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80169C10);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnCrossTrail);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnCrashCrossParticles);
// clang-format on
