// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

// func_80158B04
void func_060A6428(u16 arg0) {
    s32 xOffset;

    xOffset = 3;
    if (PLAYER.facingLeft) {
        xOffset = -3;
    }
    PLAYER.posY.i.hi = PLAYER.posY.i.hi;
    PLAYER.posX.i.hi += xOffset;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, 0x10004U, 0);
    PLAYER.posY.i.hi = PLAYER.posY.i.hi;
    PLAYER.posX.i.hi -= xOffset;
    if (arg0 & 1) {
        func_0600FB0C(3);
        PlaySfx(0x644);
    }
    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}

void RicStepStand(void) {
    s16 xMod;
    s32 facing;

    if (PLAYER.step < 64) {
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if (g_unkGraphicsStruct.D_80097448 > 48) {
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
        RicDecelerateX(FIX(0.15625));
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
            if (PLAYER.pose < 3) {
                facing = RicCheckFacing();
                if (g_Player.padPressed & PAD_DOWN) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_801555A8;
                    break;
                }
            }

            if (PLAYER.poseTimer < 0) {
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
            if (PLAYER.pose < 3) {
                RicCheckFacing();
            }
            if (PLAYER.poseTimer < 0) {
                g_Player.unk46 = 0;
                RicSetStand(0);
            }
            break;
        }
    }
}

// func_060A6738
void RicStepWalk(void) {
    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH)) {
        RicDecelerateX(FIX(0.15625)); // altered
        if (RicCheckFacing() == 0) {
            RicSetStand(0);
            return;
        }
        if (PLAYER.step_s != 0) {
            if (PLAYER.step_s) {
            }
        } else {
            RicSetSpeedX(FIX(1.5625)); // altered
        }
    }
}

// RicStepRun
void RicStepRun(void) {
    if (g_Player.runDisable != 0) {
        RicSetWalk(0);
        return;
    }
    g_Player.timers[PL_T_8] = 8;
    g_Player.timers[PL_T_CURSE] = 8;
    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH)) {
        RicDecelerateX(FIX(0.15625));
        if (RicCheckFacing() == 0) {
            RicSetStand(0);
            if (g_Player.timers[PL_T_RUN] == 0) {
                if (!(g_Player.vram_flag &
                      (TOUCHING_L_WALL | TOUCHING_R_WALL))) {
                    RicSetAnimation(ric_anim_stop_run);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }
            } else {
                PLAYER.velocityX = 0;
            }
            return;
        }
        if (PLAYER.step_s == 0) {
            RicSetSpeedX(FIX(2.8125));
        }
    }
}

void RicStepJump(void) {
    s32 facing;

    if (!g_IsPrologueStage && (PLAYER.velocityY < FIX(-1)) &&
        !(g_Player.unk44 & 0x40) && !(g_Player.padPressed & PAD_CROSS)) {
        PLAYER.velocityY = FIX(-1);
    }
    if ((g_Player.vram_flag & TOUCHING_CEILING) &&
        (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-0.25);
        g_Player.unk44 |= 0x20;
    }
    if (RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_JUMP)) {
        return;
    }
    switch (PLAYER.step_s) {
    case 0:
        RicDecelerateX(FIX(0.078125));
        facing = RicCheckFacing();
        if (facing) {
            if (g_Player.unk44 & 0x10) {
                RicSetSpeedX(FIX(2.8125));
            } else {
                RicSetSpeedX(FIX(1.5625));
            }
            g_Player.unk44 &= ~4;
        } else {
            g_Player.unk44 &= ~0x10;
            if ((PLAYER.pose < 2) && !(g_Player.unk44 & 8) &&
                (g_Player.unk44 & 4) && (g_Player.padTapped & PAD_CROSS)) {
                RicSetAnimation(D_8015555C);
                RicSetSpeedX(FIX(-1.875));
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
        if (PLAYER.pose < 3) {
            facing = RicCheckFacing();
            if (facing) {
                if (g_Player.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.8125));
                } else {
                    RicSetSpeedX(FIX(1.5625));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && PLAYER.facingLeft == 0) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.8125));
                } else {
                    RicSetSpeedX(FIX(1.5625));
                }
                RicSetSpeedX(FIX(1.5625));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.poseTimer < 0) {
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
        if (PLAYER.pose < 3) {
            facing = RicCheckFacing();
            if (facing) {
                if (g_Player.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.8125));
                } else {
                    RicSetSpeedX(FIX(1.5625));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && PLAYER.facingLeft == 0) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    RicSetSpeedX(FIX(2.8125));
                } else {
                    RicSetSpeedX(FIX(1.5625));
                }
                RicSetSpeedX(FIX(1.5625));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.poseTimer < 0) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            RicSetAnimation(D_80155528);
        }
        break;
    }
}
// func_060A6D64
void RicStepFall(void) {
    if (RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_FALL)) {
        return;
    }
    RicDecelerateX(FIX(0.078125));
    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.timers[PL_T_5] && (g_Player.padTapped & PAD_CROSS)) {
            RicSetJump();
        } else if (RicCheckFacing()) {
            RicSetSpeedX(FIX(0.9375));
        }
        break;
    }
}
void RicStepCrouch(void) {
    s32 i;
    s16 xShift;
    s32 facing;

    if ((g_Player.padTapped & PAD_CROSS) && !g_Player.unk46 &&
        (g_Player.padPressed & PAD_DOWN)) {
        for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
            if (g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE) {
                g_Player.timers[PL_T_7] = 8;
                return;
            }
        }
    }
    if (RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_ATTACK | CHECK_SLIDE)) {
        return;
    }
    if ((g_Player.padTapped & PAD_CROSS) && !g_Player.unk46 &&
        (!g_Player.unk72)) {
        RicSetJump(1);
        return;
    } else if (!g_Player.unk72 && !g_Player.unk46 &&
               (g_Player.padTapped & PAD_TRIANGLE) && RicDoCrash()) {
        return;
    }
    RicDecelerateX(FIX(0.15625));
    switch (PLAYER.step_s) {
    case 0x0:
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if (g_unkGraphicsStruct.D_80097448 > 0x18 && !g_Player.unk48) {
            xShift = 9;
            if (PLAYER.facingLeft) {
                xShift = -xShift;
            }
            PLAYER.posX.i.hi += xShift;
            PLAYER.posY.i.hi += 2;
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_EMBERS, 8), 0);
            PLAYER.posY.i.hi -= 2;
            PLAYER.posX.i.hi -= xShift;
            D_8015459C = 0x60;
        }
        if (!(g_Player.padPressed & PAD_DOWN) &&
            ((!g_Player.unk72) || !(g_Player.vram_flag & VRAM_FLAG_UNK40))) {
            RicSetAnimation(D_801554E0);
            PLAYER.step_s = 2;
            return;
        }
        break;
    case 0x1:
        if (!(g_Player.padPressed & PAD_DOWN) &&
            ((!g_Player.unk72) || !(g_Player.vram_flag & VRAM_FLAG_UNK40))) {
            if (RicCheckFacing()) {
                RicSetWalk(0);
                return;
            }
            PLAYER.anim = D_801554E0;
            PLAYER.step_s = 2;
            PLAYER.pose = 2 - PLAYER.pose;
            PLAYER.poseTimer = 1;
            break;
        }
    case 0x4:
        if (PLAYER.poseTimer != -1) {
            return;
        }
        RicSetAnimation(ric_anim_crouch);
        PLAYER.step_s = 0;
        break;
    case 0x2:
        if (!g_Player.unk72 || !(g_Player.vram_flag & VRAM_FLAG_UNK40)) {
            if (RicCheckFacing()) {
                RicSetWalk(0);
                return;
            }
            if (PLAYER.poseTimer == -1) {
                RicSetStand(0);
                return;
            }
        }
        break;
    case 0x3:
        if (PLAYER.poseTimer < 0) {
            RicSetAnimation(ric_anim_crouch);
            PLAYER.step_s = 0;
            return;
        }
        break;
    case 0x40:
        DisableAfterImage(1, 1);
        if (PLAYER.pose < 3) {
            facing = RicCheckFacing();
            if (!(g_Player.padPressed & PAD_DOWN) && !g_Player.unk72) {
                PLAYER.step = PL_S_STAND;
                PLAYER.anim = D_80155588;
                return;
            }
        }
        if (PLAYER.poseTimer < 0) {
            if (g_Player.padPressed & PAD_SQUARE) {
                PLAYER.step_s++;
                g_Player.unk46 = 2;
                RicSetAnimation(D_80155738);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
                return;
            }
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            RicSetAnimation(ric_anim_crouch);
        }
        break;
    case 0x41:
        DisableAfterImage(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            RicSetAnimation(ric_anim_crouch);
        }
        break;
    }
}
static void func_80159C04(void) {
    Entity* entity;
    s16 attackerOffX;
    s16 playerOffX;
    s16 distance;

    entity = PLAYER.unkB4;
    if (entity->facingLeft) {
        attackerOffX = -entity->hitboxOffX;
    } else {
        attackerOffX = entity->hitboxOffX;
    }
    if (PLAYER.facingLeft) {
        playerOffX = -PLAYER.hitboxOffX;
    } else {
        playerOffX = PLAYER.hitboxOffX;
    }

    distance = PLAYER.posX.i.hi + playerOffX - entity->posX.i.hi - attackerOffX;
    if (ABS(distance) < 16 && entity->velocityX != 0) {
        if (entity->velocityX < 0) {
            PLAYER.entityRoomIndex = 0;
            return;
        } else {
            PLAYER.entityRoomIndex = 1;
            return;
        }
    }
    if (distance < 0) {
        PLAYER.entityRoomIndex = 0;
    } else {
        PLAYER.entityRoomIndex = 1;
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A7310, func_060A7310);
static void RicResetPose(void) {
    PLAYER.pose = PLAYER.poseTimer = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.drawFlags &= ~ENTITY_ROTATE;
}

void RicStepBossGrab(void) {
    DamageParam damage;
    s32 damageResult;

    switch (g_CurrentEntity->step_s) {
    case 0:
        RicResetPose();
        if (g_Player.grabReactionEffect == GRAB_REACTION_NORMAL) {
            PLAYER.anim = ric_anim_stun;
            g_Player.timers[PL_T_2] = 8;
            g_Player.damagePalette = 0x46;
            PlaySfx(0x716);
        }
        PLAYER.velocityX = PLAYER.velocityY = 0;
        PLAYER.step_s = 1;
        g_Player.grabState = GRAB_HELD;
        break;
    case 1:
        // Effectively a switch on g_Player.grabState
        if (g_Player.grabState == GRAB_DAMAGE) {
            damage.effects = EFFECT_NONE;
            damage.damageKind = DAMAGEKIND_1;
            damage.damageTaken = g_Player.grabDamage;
            damageResult = CalcPlayerDamage(&damage);
            if (damageResult) {
                RicSetStep(PL_S_DEAD);
                RicStepDead(0, 2, PL_S_BOSS_GRAB, 1);
                return;
            }
            if (g_Player.grabReactionEffect == GRAB_REACTION_NORMAL) {
                g_Player.timers[PL_T_2] = 4;
                g_Player.damagePalette = 0x46;
                PlaySfx(0x717);
            }
            if (g_Player.grabReactionEffect == GRAB_REACTION_STONE) {
            }
            g_Player.grabState = GRAB_HELD;
        } else if (g_Player.grabState == GRAB_RELEASE) {
            PLAYER.step = PL_S_HIT;
            PLAYER.step_s = 2;
            g_Player.grabState = GRAB_NONE;
            g_Player.damageTaken = g_Player.grabDamage;
            PlaySfx(0x5C7);
        } else if (g_Player.grabState == GRAB_NONE) {
            PLAYER.step = PL_S_HIT;
            PLAYER.step_s = 1;
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A7CF0, RicStepDead);
void RicStepStandInAir(void) {
    s16 palettes[] = {0, 20, 21, 22};

    if (PLAYER.step_s == 0) {
        PLAYER.velocityY += FIX(0.21875);
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = 0;
            PLAYER.step_s = 1;
        }
    } else {
        PLAYER.palette = palettes[PLAYER.poseTimer & 3];
        if (g_Player.unk4E == 0) {
            g_SubwpnCrashTimer++;
            if (g_SubwpnCrashTimer <= 300) {
                goto checkVelocity;
            }
        }
        g_SubwpnCrashTimer = 0;
        g_Player.unk46 = 0;
        RicSetStep(PL_S_JUMP);
        RicSetAnimation(D_80155528);
        g_Player.unk44 = 0;
        PLAYER.palette = 0;
    }
checkVelocity:
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

// RicStepEnableFlameWhip
void RicStepEnableFlameWhip(void) {
    if (PLAYER.animCurFrame == 181 && PLAYER.poseTimer == 1) {
        RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_35, 0);
        PlaySfx(SFX_WEAPON_APPEAR);
    }

    if (PLAYER.poseTimer < 0) {
        RicSetStand(0);
        g_Player.unk46 = 0;
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x45), 0);
        g_Player.timers[PL_T_POISON] = 0x800;
    }

    if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        RicSetFall();
        g_Player.unk46 = 0;
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x45), 0);
        g_Player.timers[PL_T_POISON] = 0x800;
    }
}

// func_060A8170
void RicStepHydrostorm(void) {
    if (PLAYER.poseTimer < 0) {
        RicSetStand(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.vram_flag & TOUCHING_GROUND) == 0) {
        RicSetFall();
        g_Player.unk46 = 0;
    }
}

// RicStepGenericSubwpnCrash
void RicStepGenericSubwpnCrash(void) {
    if (g_Player.unk4E || ++g_SubwpnCrashTimer > 300) {
        g_SubwpnCrashTimer = 0;
        RicSetStand(0);
        g_Player.unk46 = 0;
    }

    if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        RicSetFall();
        g_Player.unk46 = 0;
    }
}

// RicStepThrowDaggers
void RicStepThrowDaggers(void) {
    if (PLAYER.step_s == 0) {
        throw_dagger_timer = 0x200;
        PLAYER.step_s++;
    } else {
        RicCheckFacing();
        if (!--throw_dagger_timer) {
            g_Player.unk46 = 0;
            RicSetStand(0);
            g_Player.unk4E = 1;
        }
    }
    if (g_Player.padTapped & PAD_CROSS) {
        RicSetJump();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        throw_dagger_timer = 0;
    }
    if (!(g_Player.vram_flag & TOUCHING_GROUND)) {
        RicSetFall();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        throw_dagger_timer = 0;
    }
}

void RicStepDeadPrologue(void) {
    switch (PLAYER.step_s) {
    case 0:
        g_CurrentEntity->flags |= FLAG_UNK_10000;
        g_unkGraphicsStruct.unk28 = 4;
        RicDecelerateX(FIX(0.15625));
        if (PLAYER.velocityX == 0) {
            RicSetAnimation(D_80155748);
            g_Player.timers[PL_T_INVINCIBLE_SCENE] = 4;
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_MARIA, 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 9), 0);
            D_801545AC = 0;
            PLAYER.step_s++;
        }
        break;
    case 1:
        D_801545AA += 64;
        PLAYER.drawFlags = ENTITY_SCALEY;
        PLAYER.scaleY = (rsin(D_801545AA) >> 0xA) + 256;
        if (D_801545AC) {
            if (--D_801545AC == 0) {
                PLAYER.drawFlags = ENTITY_DEFAULT;
                PLAYER.scaleY = 0x100;
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_MARIA_POWERS_APPLIED, 0);
                g_DeadPrologueTimer = 0x90;
                PLAYER.step_s++;
            }
        }
        break;
    case 2:
        // In this step, Richter rises into the air, similar to when he uses the
        // Cross subweapon crash.
        if (--g_DeadPrologueTimer == 0) {
            RicSetAnimation(D_801558B4);
            g_CurrentEntity->velocityY = FIX(-1);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_REVIVAL_COLUMN, 0);
            g_DeadPrologueTimer = 0x30;
            PlaySfx(SFX_RIC_SUC_REVIVE);
            dead_prologue_timer = 0xA0;
            PLAYER.step_s++;
        }
        break;
    case 3:
        if (--g_DeadPrologueTimer == 0) {
            PLAYER.velocityY = 0;
            g_DeadPrologueTimer = 0xC0;
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_36, 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_37, 2), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_38, 3), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_39, 4), 0);
            g_Player.timers[PL_T_INVINCIBLE_SCENE] = 0;
            PLAYER.step_s++;
        }
        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }
        dead_prologue_timer--;
        if ((dead_prologue_timer >= 0) && (dead_prologue_timer % 20 == 0)) {
            PlaySfx(SFX_RIC_SUC_REVIVE);
        }
        break;
    case 4:
        if (--g_DeadPrologueTimer == 0) {
            g_DeadPrologueTimer = 0x10;
            PLAYER.step_s++;
        }
        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }
        dead_prologue_timer--;
        if ((dead_prologue_timer >= 0) && (dead_prologue_timer % 20 == 0)) {
            PlaySfx(SFX_RIC_SUC_REVIVE);
        }
        break;
    case 5:
        if (g_DeadPrologueTimer == 5) {
            PLAYER.pose = 6;
            PLAYER.palette = 0;
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_BLUE_SPHERE, 0);
        }
        if (--g_DeadPrologueTimer == 0) {
            RicSetAnimation(D_801558D4);
            PlaySfx(SFX_WEAPON_APPEAR);
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_BLUE_CIRCLE, 0);
            PLAYER.step_s++;
            break;
        }
        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }
        break;
    case 6:
        if (PLAYER.poseTimer < 0) {
            RicSetAnimation(D_801558DC);
            PLAYER.step_s++;
        }
        break;
    case 7:
        if (PLAYER.poseTimer < 0) {
            g_CurrentEntity->flags &= ~FLAG_UNK_10000;
            g_unkGraphicsStruct.unk28 = 0;
            RicSetFall();
            RicSetAnimation(D_801558DC);
            g_Player.timers[PL_T_INVINCIBLE_SCENE] = 4;
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 9), 0);
        }
        break;
    }
}

void RicStepSlide(void) {
    s32 isTouchingGround = 0;

    if (PLAYER.facingLeft == 0 && g_Player.vram_flag & TOUCHING_R_WALL) {
        isTouchingGround = 1;
    }
    if (PLAYER.facingLeft && g_Player.vram_flag & TOUCHING_L_WALL) {
        isTouchingGround = 1;
    }
    if (PLAYER.posX.i.hi >= 312 && PLAYER.facingLeft == 0) {
        isTouchingGround = 1;
    }
    if (PLAYER.posX.i.hi <= 8 && PLAYER.facingLeft) {
        isTouchingGround = 1;
    }
    if ((PLAYER.facingLeft == 0 &&
         g_Player.colFloor[2].effects & EFFECT_UNK_8000) ||
        (PLAYER.facingLeft && g_Player.colFloor[3].effects & EFFECT_UNK_8000)) {
        isTouchingGround = 1;
    }
    if (isTouchingGround && PLAYER.pose < 6) {
        PLAYER.pose = 6;
        if (PLAYER.velocityX > FIX(1)) {
            PLAYER.velocityX = FIX(2);
        }
        if (PLAYER.velocityX < FIX(-1)) {
            PLAYER.velocityX = FIX(-2);
        }
        RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
    }
    if (PLAYER.pose < 5) {
        if (RicCheckInput(CHECK_FALL | CHECK_CRASH)) {
            return;
        }
        if ((!g_Player.unk72) && (g_Player.padTapped & PAD_CROSS)) {
            PLAYER.posY.i.hi -= 4;
            RicSetSlideKick();
            return;
        }
    } else if (PLAYER.pose < 7) {
        if (RicCheckInput(CHECK_FALL | CHECK_CRASH | CHECK_SLIDE)) {
            return;
        }
    } else if (
        RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_CRASH | CHECK_SLIDE)) {
        return;
    }

    RicDecelerateX(FIX(0.15625));
    switch (PLAYER.step_s) {
    case 0:
        if (!(g_GameTimer & 3) && PLAYER.pose < 6 && PLAYER.pose > 2) {
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SLIDE, 2), 0);
        }
        if (PLAYER.pose == 6 && PLAYER.poseTimer == 1) {
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        }
        if (PLAYER.poseTimer < 0) {
            RicSetCrouch(0, PLAYER.velocityX);
        }
        break;
    }
}
static void func_8015BB80(void) {
    if (g_CurrentRoom.stageID == STAGE_TOP) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8079 > 0) {
            PLAYER.posX.i.hi--;
        }
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8079 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
    if (g_CurrentRoom.stageID == STAGE_RTOP) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8430 > 0) {
            PLAYER.posX.i.hi--;
        }
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8430 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
s32 func_8015BB80NoInline(void) __asm__("_func_8015BB80");

void RicStepTeleport(void) {
    Entity* e;

    PLAYER.velocityX = PLAYER.velocityY = 0;
    g_Player.padSim = 0;
    g_Player.demo_timer = 4;
    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.pose == 5 && PLAYER.poseTimer == 1) {
            e = RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 0), 0);
            if (!e) {
                PLAYER.poseTimer = 2;
            }
        }
        if (PLAYER.poseTimer < 0) {
            RicSetStand(0);
        }
        break;
    case 1:
        if (PLAYER.poseTimer < 0) {
            RicSetStand(0);
        }
        if (g_Player.warp_flag) {
            RicSetStand(0);
        }
        break;
    case 2:
        func_8015BB80NoInline();
        if (PLAYER.pose == 5 && PLAYER.poseTimer == 1) {
            e = RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 2), 0);
            if (!e) {
                PLAYER.poseTimer = 2;
            }
        }
        if (PLAYER.poseTimer < 0) {
            RicSetStand(0);
        }
        break;
    case 3:
        if (PLAYER.poseTimer < 0) {
            RicSetStand(0);
        }
        if (g_Player.warp_flag) {
            RicSetStand(0);
        }
        break;
    case 4:
        func_8015BB80NoInline();
        if (PLAYER.pose == 5 && PLAYER.poseTimer == 1) {
            e = RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 4), 0);
            if (!e) {
                PLAYER.poseTimer = 2;
            }
        }
        if (PLAYER.poseTimer < 0) {
            RicSetStand(0);
        }
        break;
    case 5:
        if (PLAYER.poseTimer < 0) {
            RicSetStand(0);
        }
        if (g_Player.warp_flag) {
            RicSetStand(0);
        }
        break;
    }
}
void RicStepSlideKick(void) {
    if (!(g_Player.padPressed & PAD_CROSS)) {
        g_Player.unk44 &= ~0x100;
    }
    // If we are pressing square while in contact with an enemy
    // (as detected in g_Player.unk44), we will bounce back.
    if (!(g_Player.unk44 & 0x100)) {
        if (g_Player.unk44 & 0x80) {
            PLAYER.step = PL_S_JUMP;
            RicSetAnimation(D_8015555C);
            RicSetSpeedX(FIX(-1.875));
            PLAYER.velocityY = 0;
            if (!g_Player.unk72) {
                PLAYER.velocityY = FIX(-4.5);
            }
            g_Player.unk44 |= (8 + 2);
            g_Player.unk44 &= ~4;
            PLAYER.step_s = 2;
            return;
        }
    }
    RicDecelerateX(FIX(0.078125));
    PLAYER.velocityY += 0x1000;

    if (g_Player.vram_flag & TOUCHING_GROUND) {
        g_CurrentEntity->velocityX /= 2;
        RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        PLAYER.facingLeft++;
        PLAYER.facingLeft &= 1;
        RicSetCrouch(3, PLAYER.velocityX);
        PlaySfx(SFX_STOMP_SOFT_A);
        return;
    }
    if (PLAYER.velocityX > 0) {
        if (g_Player.vram_flag & TOUCHING_R_WALL) {
            PLAYER.velocityX = 0;
        }
    } else if (g_Player.vram_flag & TOUCHING_L_WALL) {
        PLAYER.velocityX = 0;
    }
    if (PLAYER.velocityX < 0) {
        if (g_Player.padPressed & PAD_RIGHT) {
            RicDecelerateX(FIX(0.15625));
        }
        if (PLAYER.velocityX > FIX(-3) ||
            (g_Player.vram_flag & TOUCHING_L_WALL)) {
            PLAYER.facingLeft++;
            PLAYER.facingLeft &= 1;
            PLAYER.velocityX >>= 1;
            RicSetAnimation(D_80155788);
            g_Player.unk44 = 0xA;
            PLAYER.step_s = 2;
            PLAYER.step = PL_S_JUMP;
        }
    }
    if (PLAYER.velocityX > 0) {
        if (g_Player.padPressed & PAD_LEFT) {
            RicDecelerateX(FIX(0.15625));
        }
        if (PLAYER.velocityX < FIX(3) ||
            (g_Player.vram_flag & TOUCHING_R_WALL)) {
            PLAYER.facingLeft++;
            PLAYER.facingLeft &= 1;
            PLAYER.velocityX >>= 1;
            RicSetAnimation(D_80155788);
            g_Player.unk44 = 0xA;
            PLAYER.step_s = 2;
            PLAYER.step = PL_S_JUMP;
        }
    }
}
// RicStepBladeDash
void RicStepBladeDash(void) {
    RicDecelerateX(FIX(0.140625));

    if (PLAYER.poseTimer < 0) {
        g_Player.unk46 = 0;
        RicSetStand(0);
    } else if (PLAYER.pose >= 0x12 && !(g_Player.vram_flag & TOUCHING_GROUND)) {
        g_Player.unk46 = 0;
        RicSetFall();
    } else {
        if (!(g_GameTimer & 3) && PLAYER.pose < 0x12 &&
            g_Player.vram_flag & TOUCHING_GROUND) {
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SLIDE, 2), 0);
        }
        if (PLAYER.pose == 18 && PLAYER.poseTimer == 1 &&
            (g_Player.vram_flag & TOUCHING_GROUND)) {
            RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        }
    }
}

// RicStepHighJump
void func_060A8D64(void) {
    bool loadAnim;

    loadAnim = false;
    g_Player.high_jump_timer++;
    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
            if (PLAYER.facingLeft) {
                if (!(g_Player.padPressed & PAD_LEFT)) {
                    RicDecelerateX(FIX(0.078125));
                }
            } else {
                if (!(g_Player.padPressed & PAD_RIGHT)) {
                    RicDecelerateX(FIX(0.078125));
                }
            }
        } else {
            RicDecelerateX(FIX(0.078125));
        }

        if (g_Player.vram_flag & TOUCHING_CEILING) {
            func_060A6428(3);
            g_Player.high_jump_timer = 0;
            PLAYER.step_s = 2;
        } else if (g_Player.high_jump_timer > 0x1C) {
            PLAYER.step_s = 1;
            PLAYER.velocityY = FIX(-6);
        }
        break;
    case 1:
        if (g_Player.vram_flag & TOUCHING_CEILING) {
            PLAYER.step_s = 2;
            func_060A6428(3);
            g_Player.high_jump_timer = 0;
        } else {
            PLAYER.velocityY += FIX(0.375);
            if (PLAYER.velocityY > FIX(0.5)) {
                loadAnim = true;
            }
        }
        break;
    case 2:
        if (g_Player.high_jump_timer > 4) {
            loadAnim = true;
        }
        break;
    }

    if (loadAnim) {
        RicSetAnimation(D_80155534);
        RicSetStep(PL_S_JUMP);
    }
}

void RicSetDebug(void) { RicSetStep(PL_S_DEBUG); }
