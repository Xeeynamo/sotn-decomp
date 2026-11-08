// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

s32 RicCheckInput(s32 checks) {
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
    if (g_unkGraphicsStruct.D_80097448 > 0x28) {
        velYChange /= 4;
    }
    PLAYER.velocityY += velYChange;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
    if ((checks & CHECK_80) && (g_Player.vram_flag & TOUCHING_CEILING) &&
        (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-1);
    }
    if (PLAYER.velocityY >= 0) {
        if ((checks & CHECK_GROUND) && (g_Player.vram_flag & TOUCHING_GROUND)) {
            switch (g_Player.unk46) {
            case 0:
            default:
                if (g_Player.unk44 & 8) {
                    RicSetCrouch(3, PLAYER.velocityX);
                    PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    return true;
                }
                if (PLAYER.velocityY > FIX(6.875)) {
                    RicSetCrouch(1, 0);
                    PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
                    if (g_Player.unk44 & 0x10) {
                        // bugfix from jp11: running can be disabled
                        if (!g_Player.runDisable) {
                            RicSetRun();
                        } else {
                            RicSetWalk(0);
                        }
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
                    PlaySfx(0x647);
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
                        PlaySfx(0x647);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 2:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    RicSetAnimation(D_80155738);
                    PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    RicSetAnimation(ric_anim_brandish_whip);
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        RicCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        PlaySfx(SFX_STOMP_SOFT_A);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 3:
                if ((PLAYER.velocityY > FIX(6.875)) || (g_Player.unk44 & 8)) {
                    PlaySfx(SFX_STOMP_SOFT_A);
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
        } else if (checks & CHECK_GROUND_AFTER_HIT &&
                   (g_Player.vram_flag & TOUCHING_GROUND)) {
            RicSetCrouch(1, PLAYER.velocityX);
            PlaySfx(SFX_STOMP_SOFT_A);
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
    if (checks & CHECK_FALL && !(g_Player.vram_flag & TOUCHING_GROUND)) {
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
        (PLAYER.posX.i.hi < 312 || PLAYER.facingLeft != 0) &&
        (PLAYER.posX.i.hi > 8 || !PLAYER.facingLeft) &&
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

// func_8015E484
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AAB80, func_060AAB80);

void RicGetPlayerSensor(Collider* col) {
    col->unk14 = g_RicSensorsWall[0].x;
    col->unk1C = g_RicSensorsWall[0].y;
    col->unk18 = g_RicSensorsFloor[1].y - FIX(1);
    col->unk20 = g_RicSensorsCeiling[1].y + FIX(1);
}

// RicCheckFloor
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AAD8C, func_060AAD8C);

// RicCheckCeiling
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AB1F4, func_060AB1F4);

void RicCheckWallRight(void) {
    s32 i;
    s32 effects;
    s32 xCheck;
    s32 yCheck;
    s32* y;
    s32* x;
    s32* vramFlag;

    y = &PLAYER.posY.val;
    x = &PLAYER.posX.val;
    vramFlag = &g_Player.vram_flag;

    if (g_unkGraphicsStruct.unk20) {
        return;
    }
    effects =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_BLOCK);
    if ((effects == (EFFECT_UNK_8000 | EFFECT_BLOCK)) ||
        (effects == (EFFECT_UNK_0800 | EFFECT_BLOCK)) ||
        (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_BLOCK))) {
        *vramFlag |= 4;
        return;
    }

    for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
        effects = g_Player.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_BLOCK);
        if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SIDE |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SIDE |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_BLOCK) ||
            effects == (EFFECT_UNK_0800 | EFFECT_BLOCK) ||
            effects == EFFECT_BLOCK) {
            xCheck =
                *x + g_RicSensorsWall[i].x + g_Player.colWall[i].unk4 - FIX(1);
            yCheck = *y + g_RicSensorsWall[i].y;
            CheckCollision(xCheck, yCheck, &g_RicCollider, 0);
            if ((g_RicCollider.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vramFlag |= 4;
                *x += g_Player.colWall[i].unk4;
                return;
            }
        }
        if (*vramFlag & 1) {
            continue;
        }
        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_8000 &&
            (i != 0) &&
            ((g_Player.colWall[0].effects & EFFECT_UNK_0800) ||
             !(g_Player.colWall[0].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SIDE)))) {
            *vramFlag |= 4;
            *x += g_Player.colWall[i].unk4;
            return;
        }
        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_0800 &&
            (i != 6) &&
            ((g_Player.colWall[6].effects & EFFECT_UNK_8000) ||
             !(g_Player.colWall[6].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SIDE)))) {
            *vramFlag |= 4;
            *x += g_Player.colWall[i].unk4;
            return;
        }
    }
}

void RicCheckWallLeft(void) {
    s32 i;
    s32 effects;
    s32 xCheck;
    s32 yCheck;
    s32* y;
    s32* x;
    s32* vramFlag;

    y = &PLAYER.posY.val;
    x = &PLAYER.posX.val;
    vramFlag = &g_Player.vram_flag;

    if (g_unkGraphicsStruct.unk20) {
        return;
    }
    effects =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_BLOCK);
    if ((effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_BLOCK)) ||
        (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_BLOCK)) ||
        (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                     EFFECT_UNK_0400 | EFFECT_BLOCK))) {
        *vramFlag |= 8;
        return;
    }
    for (i = NUM_VERTICAL_SENSORS; i < NUM_VERTICAL_SENSORS * 2; i++) {
        effects = g_Player.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_BLOCK);
        if ((effects == (EFFECT_UNK_8000 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_BLOCK)) ||
            (effects == (EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0800 | EFFECT_BLOCK)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SIDE |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SIDE |
                         EFFECT_SOLID)) ||
            (effects == EFFECT_BLOCK)) {
            xCheck =
                *x + g_RicSensorsWall[i].x + g_Player.colWall[i].unkC + FIX(1);
            yCheck = *y + g_RicSensorsWall[i].y;
            CheckCollision(xCheck, yCheck, &g_RicCollider, 0);
            if ((g_RicCollider.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vramFlag |= 8;
                *x += g_Player.colWall[i].unkC;
                return;
            }
        }
        if (!(*vramFlag & 1)) {
            if (((effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_8000 | EFFECT_UNK_4000)) &&
                (i != 7) &&
                ((g_Player.colWall[7].effects & EFFECT_UNK_0800) ||
                 !(g_Player.colWall[7].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SIDE)))) {
                *vramFlag |= 8;
                *x += g_Player.colWall[i].unkC;
                return;
            }
            if (((effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
                (i != 13) &&
                ((g_Player.colWall[13].effects & EFFECT_UNK_8000) ||
                 !(g_Player.colWall[13].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SIDE)))) {
                *vramFlag |= 8;
                *x += g_Player.colWall[i].unkC;
                return;
            }
        }
    }
}
