// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

bool RicCheckInput(s32 checks) {
    s32 velYChange;
    u32 effects;

    if (checks & CHECK_FACING) {
        if (g_Player.unk46 == 0) {
            RicCheckFacing();
        }
    }
    velYChange = 0;
    if (checks & CHECK_GRAVITY_FALL) {
        velYChange = FIX(28.0 / 128);
    }
    if (checks & CHECK_GRAVITY_JUMP) {
        if (PLAYER.velocityY < FIX(3.0 / 8) &&
            PLAYER.velocityY > FIX(-1.0 / 8) && !(g_Player.unk44 & 0x20) &&
            (g_Player.padPressed & PAD_CROSS)) {
            // Note that 5.6 is precisely 1/5 of 28.
            velYChange = FIX(5.6 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }
    if (checks & CHECK_GRAVITY_HIT) {
        if (PLAYER.velocityY < FIX(3.0 / 8) &&
            PLAYER.velocityY > FIX(-1.0 / 8)) {
            velYChange = FIX(14.0 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }
    if (*D_80097448 > 0x28) {
        velYChange /= 4;
    }
    PLAYER.velocityY += velYChange;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
    if ((checks & CHECK_80) && (g_Player.vram_flag & 2) &&
        (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-1);
    }
    if (PLAYER.velocityY >= 0) {
        if ((checks & CHECK_GROUND) && (g_Player.vram_flag & 1)) {
            switch (g_Player.unk46) {
            case 0:
            default:
                if (g_Player.unk44 & 8) {
                    RicSetCrouch(3, PLAYER.velocityX);
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    return true;
                }
                if (PLAYER.velocityY > FIX(6.875)) {
                    RicSetCrouch(1, 0);
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
                    if (g_Player.unk44 & 0x10
#if defined(VERSION_US)
                        && !g_Player.unk7A
#endif
                    ) {
                        RicSetRun();
                    } else {
                        RicSetWalk(0);
                    }
                } else {
                    RicSetStand(0);
                }
                return true;
            case 1:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_801555A8;
                    g_api.PlaySfx(SFX_STOMP_HARD_B);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    PLAYER.anim = D_80155588;
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        RicCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_HARD_B);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 2:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_80155738;
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    PLAYER.anim = ric_anim_brandish_whip;
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        RicCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 3:
                if ((PLAYER.velocityY > FIX(6.875)) || (g_Player.unk44 & 8)) {
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }
                PLAYER.velocityY = 0;
                if (!(g_Player.unk44 & 8)) {
                    PLAYER.velocityX = 0;
                }
                PLAYER.step = PL_S_STAND;
                PLAYER.anim = D_801555E8;
                g_Player.unk44 = 0;
                return true;
            }
        } else if (
            checks & CHECK_GROUND_AFTER_HIT && (g_Player.vram_flag & 1)) {
            RicSetCrouch(1, PLAYER.velocityX);
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
            if (g_Player.unk5C && (g_Status.hp < 2)) {
                RicSetDeadPrologue();
                return true;
            } else {
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_SKID_SMOKE, 0);
            }
            return true;
        }
    }
    if (checks & CHECK_FALL && !(g_Player.vram_flag & 1)) {
        if (g_Player.unk46) {
            if (g_Player.unk46 == 1) {
                PLAYER.step_s = 0x40;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_801555C8;
                return true;
            }
            if (g_Player.unk46 == 2) {
                PLAYER.step_s = 0x41;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_801555C8;
                return true;
            }
            if (g_Player.unk46 == 3) {
                PLAYER.step_s = 0x42;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_80155638;
                return true;
            }
        } else {
            RicSetFall();
            return true;
        }
    }
    if (g_Player.unk46) {
        return false;
    }
    if (checks & CHECK_CRASH && (g_Player.padTapped & PAD_TRIANGLE) &&
        RicDoCrash()) {
        return true;
    }
    if (checks & CHECK_SLIDE &&
        !(PLAYER.facingLeft == 0 &&
          g_Player.colFloor[2].effects & EFFECT_UNK_8000) &&
        !(PLAYER.facingLeft &&
          g_Player.colFloor[3].effects & EFFECT_UNK_8000) &&
        (PLAYER.posX.i.hi < (u8)-4 || PLAYER.facingLeft != 0) &&
        (PLAYER.posX.i.hi >= 5 || !PLAYER.facingLeft) &&
        g_Player.padPressed & PAD_DOWN && g_Player.padTapped & PAD_CROSS) {
        RicSetSlide();
        return true;
    }
    if (checks & CHECK_JUMP && (g_Player.padTapped & PAD_CROSS)) {
        RicSetJump();
        return true;
    }
    if (checks & CHECK_ATTACK && (g_Player.padTapped & PAD_SQUARE) &&
        RicDoAttack()) {
        return true;
    }
    if (checks & CHECK_CROUCH && (g_Player.padPressed & PAD_DOWN)) {
        RicSetCrouch(2, 0);
        return true;
    }
    return false;
}

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicGetPlayerSensor);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckFloor);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckCeiling);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckWallRight);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/B070", RicCheckWallLeft);
