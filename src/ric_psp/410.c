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

void RicHandleWalk(void) {
    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH)) {
        RicDecelerateX(FIX(0.125));
        if (RicCheckFacing() == 0) {
            RicSetStand(0);
            return;
        }
        if (g_Entities[0].step_s != 0) {
            if (g_Entities[0].step_s) {
            }
        } else {
            RicSetSpeedX(FIX(1.25));
        }
    }
}

void RicHandleRun(void) {
#ifdef VERSION_US
    if (g_Player.unk7A != 0) {
        RicSetWalk(0);
        return;
    }
#endif
    g_Player.timers[PL_T_8] = 8;
    g_Player.timers[PL_T_CURSE] = 8;
    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH)) {
        RicDecelerateX(0x2000);
        if (RicCheckFacing() == 0) {
            RicSetStand(0);
            if (g_Player.timers[PL_T_RUN] == 0) {
                if (!(g_Player.pl_vram_flag & 0xC)) {
                    RicSetAnimation(ric_anim_stop_run);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }
            } else {
                PLAYER.velocityX = 0;
            }
            return;
        }
        if (g_Entities[0].step_s != 0) {
            if (g_Entities[0].step_s) {
            }
        } else {
            RicSetSpeedX(FIX(2.25));
        }
    }
}

void RicHandleJump(void) {
    s32 facing;
    if (!g_IsPrologueStage && (PLAYER.velocityY < FIX(-1)) &&
        !(g_Player.unk44 & 0x40) && !(g_Player.padPressed & PAD_CROSS)) {
        PLAYER.velocityY = FIX(-1);
    }
    if ((g_Player.pl_vram_flag & 2) && (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-0.25);
        g_Player.unk44 |= 0x20;
    }
    if (RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_JUMP)) {
        return;
    }
    switch (PLAYER.step_s) {
    case 0:
        RicDecelerateX(0x1000);
        facing = RicCheckFacing();
        if (facing) {
            if (g_Player.unk44 & 0x10) {
                RicSetSpeedX(FIX(2.25));
            } else {
                RicSetSpeedX(FIX(1.25));
            }
            g_Player.unk44 &= ~4;
        } else {
            g_Player.unk44 &= ~0x10;
            if ((PLAYER.animFrameIdx < 2) && !(g_Player.unk44 & 8) &&
                (g_Player.unk44 & 4) && (g_Player.padTapped & PAD_CROSS)) {
                RicSetAnimation(D_8015555C);
                RicSetSpeedX(FIX(-1.5));
                PLAYER.velocityY = FIX(-2.625);
                if (g_Player.unk72) {
                    PLAYER.velocityY = 0;
                }
                g_Player.unk44 |= 0xA;
                g_Player.unk44 &= ~4;
                PLAYER.step_s = 2;
            }
        }
        break;
    case 2:
        break;
    case 0x40:
        DisableAfterImage(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            facing = RicCheckFacing();
            if (facing) {
                if (g_Player.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.25));
                } else {
                    RicSetSpeedX(FIX(1.25));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && PLAYER.facingLeft == 0) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.25));
                } else {
                    RicSetSpeedX(FIX(1.25));
                }
                RicSetSpeedX(FIX(1.25));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            if (g_Player.padPressed & PAD_SQUARE) {
                PLAYER.step_s += 1;
                g_Player.unk46 = 2;
                RicSetAnimation(D_80155740);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
            } else {
                g_Player.unk46 = 0;
                PLAYER.step_s = 0;
                RicSetAnimation(D_80155528);
            }
        }
        break;
    case 0x41:
        DisableAfterImage(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            RicSetAnimation(D_80155528);
        }
        break;
    case 0x42:
        DisableAfterImage(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            facing = RicCheckFacing();
            if (facing) {
                if (g_Player.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.25));
                } else {
                    RicSetSpeedX(FIX(1.25));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && PLAYER.facingLeft == 0) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.25));
                } else {
                    RicSetSpeedX(FIX(1.25));
                }
                RicSetSpeedX(FIX(1.25));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            RicSetAnimation(D_80155528);
        }
        break;
    }
}

void RicHandleFall(void) {
    if (RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_FALL)) {
        return;
    }
    RicDecelerateX(0x1000);
    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.timers[PL_T_5] && g_Player.padTapped & PAD_CROSS) {
            RicSetJump();
        } else if (RicCheckFacing()) {
            RicSetSpeedX(0xC000);
        }
        break;
    }
}

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
