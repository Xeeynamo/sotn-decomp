// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

void func_80158B04(u16 arg0) {
    s16 xMod = 3;
    if (PLAYER.facingLeft) {
        xMod = -xMod;
    }

    PLAYER.posY.i.hi -= 16;
    PLAYER.posX.i.hi += xMod;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_EMBERS, 1), 0);
    PLAYER.posY.i.hi += 16;
    PLAYER.posX.i.hi -= xMod;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }
    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleStand);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleWalk);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleRun);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleJump);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleFall);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleCrouch);

INCLUDE_ASM("ric_psp/nonmatchings/410", func_80159BC8);

INCLUDE_ASM("ric_psp/nonmatchings/410", func_80159C04);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleHit);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleBossGrab);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleDead);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleStandInAir);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleEnableFlameWhip);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleHydrostorm);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleGenericSubwpnCrash);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleThrowDaggers);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleDeadPrologue);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleSlide);

INCLUDE_ASM("ric_psp/nonmatchings/410", func_8015BB80);

INCLUDE_ASM("ric_psp/nonmatchings/410", func_8015BCD0);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleSlideKick);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleBladeDash);

INCLUDE_ASM("ric_psp/nonmatchings/410", RicHandleHighJump);
