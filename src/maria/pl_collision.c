// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

bool MarCheckInput(s32 checks) {
    s32 velYChange;
    u32 effects;

    if (checks & CHECK_FACING) {
        MarCheckFacing();
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
                    MarSetCrouch(3, PLAYER.velocityX);
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    return true;
                }
                if (PLAYER.velocityY > FIX(6.875)) {
                    MarSetCrouch(1, 0);
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
                    MarSetWalk(0);
                } else {
                    MarSetStand(0);
                }
                return true;
            case 1:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = mar_801555A8;
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    PLAYER.anim = mar_80155588;
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        MarCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_HARD_E);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 3:
                if ((PLAYER.velocityY > FIX(6.875)) || (g_Player.unk44 & 8)) {
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }
                PLAYER.velocityY = 0;
                if (!(g_Player.unk44 & 8)) {
                    PLAYER.velocityX = 0;
                }
                PLAYER.step = PL_S_STAND;
                PLAYER.anim = mar_80155588;
                g_Player.unk44 = 0;
                return true;
            }
        } else if (
            checks & CHECK_GROUND_AFTER_HIT && (g_Player.vram_flag & 1)) {
            MarSetCrouch(1, PLAYER.velocityX);
            g_api.PlaySfx(SFX_STOMP_HARD_E);
            MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
            return true;
        }
    }
    if (checks & CHECK_FALL && !(g_Player.vram_flag & 1)) {
        if (g_Player.unk46) {
            if (g_Player.unk46 == 1) {
                PLAYER.step_s = 0x40;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = mar_801555C8;
                return true;
            }
            if (g_Player.unk46 == 3) {
                PLAYER.step_s = 0x42;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = mar_801555C8;
                return true;
            }
        } else {
            MarSetFall();
            return true;
        }
    }
    if (checks & CHECK_CRASH && (g_Player.padTapped & PAD_TRIANGLE) &&
        MarDoCrash()) {
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
        MarSetSlide();
        return true;
    }
    if (checks & CHECK_JUMP && g_Player.padTapped & PAD_CROSS) {
        MarSetJump(1);
        return true;
    }
    if (checks & CHECK_ATTACK && g_Player.padTapped & PAD_SQUARE &&
        MarDoAttack()) {
        return true;
    }
    if (checks & CHECK_20 && g_Player.padTapped & PAD_CROSS &&
        !(g_Player.unk44 & 1)) {
        func_pspeu_092B2040();
        return 1;
    }
    if (checks & CHECK_CROUCH && (g_Player.padPressed & PAD_DOWN)) {
        MarSetCrouch(2, 0);
        return true;
    }
    if (checks & CHECK_400) {
        if (PLAYER.facingLeft == 0) {
            if (g_Player.padTapped & PAD_R1) {
                MarSetRun(0);
                return 1;
            }
        } else {
            if (g_Player.padTapped & PAD_L1) {
                MarSetRun(0);
                return 1;
            }
        }
    }
    if (checks & CHECK_800) {
        if (PLAYER.facingLeft == 0) {
            if (g_Player.padTapped & PAD_L1) {
                MarSetRun(1);
                return 1;
            }
        } else {
            if (g_Player.padTapped & PAD_R1) {
                MarSetRun(1);
                return 1;
            }
        }
    }
    return false;
}

void MarGetPlayerSensor(Collider* col) {
    col->unk14 = g_MarSensorsWall[0].x;
    col->unk1C = g_MarSensorsWall[0].y;
    col->unk18 = g_MarSensorsFloor[1].y - 1;
    col->unk20 = g_MarSensorsCeiling[1].y + 1;
}

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckFloor);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckCeiling);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckWallRight);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckWallLeft);
