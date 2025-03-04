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

void RicHandleStand(void) {
    s16 xMod;
    s32 facing;

    if (PLAYER.step < 64) {
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if (D_80097448[0] > 48) {
            xMod = 4;
            if (PLAYER.facingLeft) {
                xMod = -xMod;
            }
            PLAYER.posX.i.hi += xMod;
            PLAYER.posY.i.hi -= 16;
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_EMBERS, 8), 0);
            PLAYER.posY.i.hi += 16;
            PLAYER.posX.i.hi -= xMod;
            D_8015459C = 0x60;
        }
    }

    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH | CHECK_SLIDE)) {
        RicDecelerateX(0x2000);
        switch (PLAYER.step_s) {
        case 0:
            if (RicCheckFacing()) {
                RicSetWalk(0);
            } else if (g_Player.padPressed & PAD_UP) {
                RicSetAnimation(ric_anim_press_up);
                PLAYER.step_s = 1;
                break;
            }
            break;
        case 1:
            if (RicCheckFacing()) {
                RicSetWalk(0);
            } else if (g_Player.padPressed & PAD_UP) {
            } else {
                RicSetStand(0);
            }
            break;
        case 64:
            DisableAfterImage(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                facing = RicCheckFacing();
                if (g_Player.padPressed & PAD_DOWN) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_801555A8;
                    break;
                }
            }

            if (PLAYER.animFrameDuration < 0) {
                if (g_Player.padPressed & PAD_SQUARE) {
                    PLAYER.step_s++;
                    g_Player.unk46 = 2;
                    RicSetAnimation(ric_anim_brandish_whip);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
                    break;
                }
                g_Player.unk46 = 0;
                RicSetStand(0);
            }
            break;
        case 65:
            DisableAfterImage(1, 1);
            if (g_Player.padPressed & PAD_SQUARE) {
                break;
            }
            g_Player.unk46 = 0;
            RicSetStand(0);
            break;
        case 66:
            DisableAfterImage(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                RicCheckFacing();
            }
            if (PLAYER.animFrameDuration < 0) {
                g_Player.unk46 = 0;
                RicSetStand(0);
            }
            break;
        }
    }
}

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
