// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

extern s32 g_CutsceneFlags;
extern AnimationFrame D_pspeu_09285860[];

// bss
static s32 mar_hit_stun_timer;
DebugInfo g_MarDebug;
static u8 dead_dissolve_bmp[0x1400];
static s16 D_80174F68;
static s16 D_80174F6C;
static s32 mar_8015459C;

static void func_80158B04(u16 arg0) {
    s16 xMod = 3;
    if (MARIA.facingLeft) {
        xMod = -xMod;
    }

    MARIA.posY.i.hi -= 16;
    MARIA.posX.i.hi += xMod;
    MarCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_EMBERS, 1), 0);
    MARIA.posY.i.hi += 16;
    MARIA.posX.i.hi -= xMod;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }

    if (arg0 & 2) {
        MARIA.velocityX = 0;
        MARIA.velocityY = 0;
    }
}

void MarStepStand(void) {
    s16 xMod;

    if (MARIA.step < 64) {
        if (mar_8015459C != 0) {
            mar_8015459C--;
        } else if (g_unkGraphicsStruct.D_80097448 > 48) {
            xMod = 4;
            if (MARIA.facingLeft) {
                xMod = -xMod;
            }

            MARIA.posX.i.hi += xMod;
            MARIA.posY.i.hi -= 16;
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_EMBERS, 8), 0);
            MARIA.posY.i.hi += 16;
            MARIA.posX.i.hi -= xMod;
            mar_8015459C = 0x60;
        }
    }

    if (!MarCheckInput(
            CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH | CHECK_400 |
            CHECK_800 | CHECK_ATTACK | CHECK_CROUCH | CHECK_SLIDE)) {
        MarDecelerateX(FIX(0.125));
        switch (MARIA.step_s) {
        case 0:
            if (MarCheckFacing()) {
                MarSetWalk(0);
            } else if (g_Maria.padPressed & PAD_UP) {
                MarSetAnimation(mar_anim_press_up);
                MARIA.step_s = 1;
            }
            break;
        case 1:
            if (MarCheckFacing()) {
                MarSetWalk(0);
            } else if (g_Maria.padPressed & PAD_UP) {
            } else {
                MarSetStand(0);
            }
            break;
        case 64:
            MarDisableAfterImage(1, 1);
            if (MarCheckFacing()) {
                MarSetWalk(0);
            } else if (MARIA.poseTimer < 0) {
                g_Maria.unk46 = 0;
                MarSetStand(0);
            }
            break;
        case 66:
            MarDisableAfterImage(1, 1);
            if (MarCheckFacing()) {
                MarSetWalk(0);
            } else if (MARIA.poseTimer < 0) {
                g_Maria.unk46 = 0;
                MarSetStand(0);
            }
            break;
        }
    }
}

void MarStepWalk(void) {
    if (!MarCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_400 | CHECK_800 | CHECK_ATTACK | CHECK_CROUCH)) {
        MarDecelerateX(FIX(0.125));
        if (MarCheckFacing() == 0) {
            MarSetStand(0);
            MarSetAnimation(D_pspeu_092C04B8);
            MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
            return;
        }

        switch (MARIA.step_s) {
        case 0:
            MarSetSpeedX(FIX(2.25));
            break;
        }
    }
}

void MarStepJump(void) {
    s32 facing;

    if (MARIA.velocityY < FIX(-1) && !(g_Maria.unk44 & 0x40) &&
        !(g_Maria.padPressed & PAD_CROSS)) {
        MARIA.velocityY = FIX(-1);
    }

    if (g_Maria.vram_flag & TOUCHING_CEILING && MARIA.velocityY < FIX(-1)) {
        MARIA.velocityY = FIX(-0.25);
        g_Maria.unk44 |= 0x20;
    }
    if (MarCheckInput(CHECK_GROUND | CHECK_FACING | CHECK_DOUBLEJUMP |
                      CHECK_400 | CHECK_ATTACK | CHECK_GRAVITY_JUMP)) {
        return;
    }
    switch (MARIA.step_s) {
    case 0:
        facing = MarCheckFacing();
        if (facing) {
            MarSetSpeedX(FIX(2.25));
            g_Maria.unk44 &= ~4;
        } else {
            MarDecelerateX(abs(g_CurrentEntity->velocityX) / 20);
        }

        if (facing <= 0) {
            g_Maria.unk44 &= ~0x10;
        }

        if (MARIA.velocityY > 0) {
            if (!(g_Maria.unk44 & 1)) {
                MarSetAnimation(mar_80155534);
            }
            MARIA.step_s = 1;
        }

        break;
    case 1:
        facing = MarCheckFacing();
        if (facing) {
            MarSetSpeedX(FIX(2.25));
            g_Maria.unk44 &= ~4;
        } else {
            MarDecelerateX(abs(g_CurrentEntity->velocityX) / 20);
        }

        if (facing <= 0) {
            g_Maria.unk44 &= ~0x10;
        }

        break;
    case 64:
        MarDisableAfterImage(1, 1);
        if (MARIA.pose < 3) {
            facing = MarCheckFacing();
            if (facing) {
                MarSetSpeedX(FIX(2.25));
                g_Maria.unk44 &= ~4;
            } else {
                g_Maria.unk44 &= ~0x10;
            }
        } else if ((g_Maria.padPressed & PAD_RIGHT && MARIA.facingLeft == 0) ||
                   (g_Maria.padPressed & PAD_LEFT && MARIA.facingLeft)) {
            MarSetSpeedX(FIX(2.25));
            g_Maria.unk44 &= ~4;
        } else {
            g_Maria.unk44 &= ~0x10;
        }

        if (MARIA.poseTimer < 0) {
            g_Maria.unk46 = 0;
            MARIA.step_s = 0;
            MarSetAnimation(mar_80155534);
        }

        break;
    case 66:
        MarDisableAfterImage(1, 1);

        if (MARIA.pose < 3) {
            facing = MarCheckFacing();
            if (facing) {
                MarSetSpeedX(FIX(2.25));
                g_Maria.unk44 &= ~4;
            } else {
                g_Maria.unk44 &= ~0x10;
            }
        } else if (
            ((g_Maria.padPressed & PAD_RIGHT) && MARIA.facingLeft == 0) ||
            ((g_Maria.padPressed & PAD_LEFT) && MARIA.facingLeft)) {
            MarSetSpeedX(FIX(2.25));
            g_Maria.unk44 &= ~4;
        } else {
            g_Maria.unk44 &= ~0x10;
        }

        if (MARIA.poseTimer < 0) {
            g_Maria.unk46 = 0;
            MARIA.step_s = 0;
            MarSetAnimation(mar_80155534);
        }

        break;
    case 112:
        if (g_Maria.unk44 & 0x80) {
            MarSetJump(1);
            if (!(g_Maria.padPressed & PAD_CROSS)) {
                MARIA.velocityY = FIX(-4.25);
            }
            g_Maria.unk44 |= 0x40;
        }
        break;
    }

    if ((MARIA.step_s == 0 || MARIA.step_s == 1) && (g_Maria.unk44 & 1) &&
        (g_Maria.padPressed & PAD_DOWN) && (g_Maria.padTapped & PAD_CROSS)) {
        MarSetAnimation(D_pspeu_092C0858);
        MARIA.step_s = 0x70;
        MarCreateEntFactoryFromEntity(g_CurrentEntity, _BP_5, 0);
        g_Maria.unk44 &= ~0x80;
        MARIA.velocityY = FIX(6);
        if (facing) {
            MarSetSpeedX(FIX(4.5));
        }
        PlaySfx(SFX_VO_MAR_8EA + MAR_SFX_OFFSET);
    }
}

void MarStepFall(void) {
    if (MarCheckInput(CHECK_GROUND | CHECK_FACING | CHECK_DOUBLEJUMP |
                      CHECK_400 | CHECK_ATTACK | CHECK_GRAVITY_FALL)) {
        return;
    }

    MarDecelerateX(FIX(1.0 / 16));

    switch (MARIA.step_s) {
    case 0:
        if (g_Maria.timers[PL_T_5] && g_Maria.padTapped & PAD_CROSS) {
            MarSetJump(1);
            return;
        }

        if (MarCheckFacing()) {
            MarSetSpeedX(FIX(0.75));
        }
        break;
    }
}

void MarStepCrouch(void) {
    s32 i;
    s16 xShift;
    s32 facing;

    if (g_Maria.padTapped & PAD_CROSS && !g_Maria.unk46 &&
        g_Maria.padPressed & PAD_DOWN) {
        for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
            if (g_Maria.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE) {
                g_Maria.timers[PL_T_7] = 8;
                return;
            }
        }
    }
    if (MarCheckInput(CHECK_FALL | CHECK_FACING | CHECK_ATTACK | CHECK_SLIDE)) {
        return;
    }
    if (g_Maria.padTapped & PAD_CROSS && !g_Maria.unk46 && !g_Maria.unk72) {
        MarSetJump(1);
        return;
    } else if (!g_Maria.unk72 && !g_Maria.unk46 &&
               (g_Maria.padTapped & PAD_TRIANGLE) && MarDoCrash()) {
        return;
    }
    MarDecelerateX(FIX(0.125));
    switch (MARIA.step_s) {
    case 0:
        if (mar_8015459C != 0) {
            mar_8015459C--;
        } else if (g_unkGraphicsStruct.D_80097448 > 0x18 && !g_Maria.unk48) {
            xShift = 9;
            if (MARIA.facingLeft) {
                xShift = -xShift;
            }
            MARIA.posX.i.hi += xShift;
            MARIA.posY.i.hi += 2;
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_EMBERS, 8), 0);
            MARIA.posY.i.hi -= 2;
            MARIA.posX.i.hi -= xShift;
            mar_8015459C = 0x60;
        }

        if (!(g_Maria.padPressed & PAD_DOWN) &&
            (!g_Maria.unk72 || !(g_Maria.vram_flag & VRAM_FLAG_UNK40))) {
            MarSetAnimation(mar_801554E0);
            MARIA.step_s = 2;
        }
        break;
    case 1:
        if (!(g_Maria.padPressed & PAD_DOWN) &&
            (!g_Maria.unk72 || !(g_Maria.vram_flag & VRAM_FLAG_UNK40))) {
            if (MarCheckFacing()) {
                MarSetWalk(0);
                break;
            }
            MARIA.anim = mar_801554E0;
            MARIA.step_s = 2;
            MARIA.pose = 0;
            MARIA.poseTimer = 1;
            break;
        }
        // fallthrough
    case 4:
        if (MARIA.poseTimer == -1) {
            MarSetAnimation(mar_anim_crouch);
            MARIA.step_s = 0;
        }
        break;
    case 2:
        if (!g_Maria.unk72 || !(g_Maria.vram_flag & VRAM_FLAG_UNK40)) {
            if (MarCheckFacing()) {
                MarSetWalk(0);
                break;
            }

            if (MARIA.poseTimer == -1) {
                MarSetStand(0);
                break;
            }
        }
        break;
    case 3:
        if (MARIA.poseTimer < 0) {
            MarSetAnimation(mar_anim_crouch);
            MARIA.step_s = 0;
        }
        break;
    case 64:
        MarDisableAfterImage(1, 1);
        if (MARIA.pose < 3) {
            facing = MarCheckFacing();
            if (!(g_Maria.padPressed & PAD_DOWN) && !g_Maria.unk72) {
                MARIA.step = PL_S_STAND;
                MARIA.anim = mar_80155588;
                break;
            }
        }

        if (MARIA.poseTimer < 0) {
            g_Maria.unk46 = 0;
            MARIA.step_s = 0;
            MarSetAnimation(mar_anim_crouch);
        }
        break;
    case 65:
        MarDisableAfterImage(1, 1);
        if (!(g_Maria.padPressed & PAD_SQUARE)) {
            g_Maria.unk46 = 0;
            MARIA.step_s = 0;
            MarSetAnimation(mar_anim_crouch);
        }
        break;
    }
}

static void MarResetPose(void) {
    MARIA.pose = MARIA.poseTimer = 0;
    g_Maria.unk44 = 0;
    g_Maria.unk46 = 0;
    MARIA.drawFlags &= ~ENTITY_ROTATE;
}

static void func_80159C04(void) {
    if (MARIA.posX.i.hi <= PLAYER.posX.i.hi) {
        MARIA.entityRoomIndex = 0;
    } else {
        MARIA.entityRoomIndex = 1;
    }
}

void MarStepHit(s32 damageEffect, u32 damageKind, s16 step, s16 step_s) {
    DamageParam damageParam;
    s32 i;
    s32 damageResult;
    s16 posX;
    s32 step_s_zero;

    if (g_Maria.unk7A == 2) {
        g_Maria.unk7A = 0;
        g_Maria.unk66 = 0;
    }

    step_s_zero = false;
    if (mar_hit_stun_timer) {
        mar_hit_stun_timer--;
    }

    switch (MARIA.step_s) {
    case 0:
        step_s_zero = true;
        MarResetPose();
        if (damageKind < DAMAGEKIND_16) {
            func_80159C04();
        } else {
            MARIA.entityRoomIndex = MARIA.facingLeft;
        }

        if (damageEffect & ELEMENT_THUNDER) {
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_THUNDER, 0);
            MARIA.velocityY = FIX(-4);
            func_maria_8015CAAC(FIX(-1.25));
            MARIA.step_s = 1;
            MARIA.anim = mar_801556C4;
            g_Maria.damagePalette = PAL_MARIA;
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_THUNDER, 0);
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x46), 0);
            g_Maria.timers[PL_T_2] = 6;
            g_api.PlaySfx(SFX_VO_MAR_PAIN_C + MAR_SFX_OFFSET);
        } else {
            if (damageEffect & ELEMENT_ICE) {
                damageKind = DAMAGEKIND_3;
            }
            // TODO check if this is real, i suspect not. Fix damageKind.
            switch (damageKind) {
            case 2:
                switch (step) {
                case PL_S_STAND:
                case PL_S_WALK:
                    MARIA.velocityY = 0;
                    func_maria_8015CAAC(FIX(-1.25));
                    MARIA.step_s = 6;
                    MARIA.anim = mar_anim_stun;
                    g_api.PlaySfx(SFX_VO_MAR_PAIN_B + MAR_SFX_OFFSET);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    break;
                case PL_S_CROUCH:
                    MARIA.velocityY = 0;
                    func_maria_8015CAAC(FIX(-1.25));
                    MARIA.step_s = 7;
                    MARIA.anim = mar_80155704;
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    g_api.PlaySfx(SFX_VO_MAR_PAIN_C + MAR_SFX_OFFSET);
                    break;
                case PL_S_JUMP:
                case PL_S_FALL:
                    MARIA.velocityY = FIX(-3);
                    func_maria_8015CAAC(FIX(-1.25));
                    MARIA.step_s = 1;
                    MARIA.anim = D_pspeu_092C0790;
                    g_api.PlaySfx(SFX_VO_MAR_PAIN_B + MAR_SFX_OFFSET);
                    break;
                }
                break;
            case 5:
            case 4:
                g_Maria.damageTaken = MARIA.hitPoints;
                MARIA.posY.val -= 1;
                MARIA.velocityY = FIX(-0.5);
                func_maria_8015CAAC(FIX(-8));
                MARIA.step_s = 2;
                MARIA.anim = mar_anim_stun;
                g_Maria.timers[PL_T_2] = 0x200;
                MARIA.facingLeft = MARIA.entityRoomIndex;
                break;
            default:
            case 16:
            case 3:
                switch (step) {
                default:
                case PL_S_STAND:
                case PL_S_WALK:
                    MARIA.velocityY = FIX(-4);
                    func_maria_8015CAAC(FIX(-1.25));
                    MARIA.step_s = 1;
                    MARIA.anim = mar_anim_stun;
                    g_api.PlaySfx(SFX_VO_MAR_PAIN_B + MAR_SFX_OFFSET);
                    break;
                case PL_S_CROUCH:
                    MARIA.velocityY = 0;
                    func_maria_8015CAAC(FIX(-1.25));
                    MARIA.step_s = 7;
                    MARIA.anim = mar_80155704;
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    g_api.PlaySfx(SFX_VO_MAR_PAIN_C + MAR_SFX_OFFSET);
                    break;
                case PL_S_JUMP:
                case PL_S_FALL:
                    MARIA.velocityY = FIX(-3);
                    func_maria_8015CAAC(FIX(-1.25));
                    MARIA.step_s = 1;
                    MARIA.anim = D_pspeu_092C0790;
                    g_api.PlaySfx(SFX_VO_MAR_PAIN_B + MAR_SFX_OFFSET);
                    break;
                }
                break;
            }

            g_Maria.damagePalette = PAL_FLAG(PAL_CC_RED_EFFECT_A);
            g_Maria.timers[PL_T_2] = 6;
            if (damageEffect & ELEMENT_FIRE) {
                MarCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_HIT_BY_FIRE, 1), 0);
                MarCreateEntFactoryFromEntity(
                    g_CurrentEntity, _BP_HOLYWATER_FLAMES, 0);
                MarCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x43), 0);
                g_Maria.damagePalette = PAL_FLAG(PAL_CC_FIRE_EFFECT);
                g_Maria.timers[PL_T_2] = 0x10;
            } else if (damageEffect & ELEMENT_CUT) {
                MarCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_HIT_BY_CUT, 5), 0);
                MarCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x44), 0);
                g_Maria.damagePalette = PAL_FLAG(PAL_CC_RED_EFFECT_A);
                g_Maria.timers[PL_T_2] = 0x10;
            } else if (damageEffect & ELEMENT_ICE) {
                MarCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_HIT_BY_ICE, 0);
                g_Maria.timers[PL_T_2] = 0xC;
                g_Maria.damagePalette = PAL_FLAG(PAL_CC_BLUE_EFFECT_A);
            } else {
                if (damageEffect & ELEMENT_DARK) {
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_HIT_BY_DARK, 0);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x56), 0);
                    g_Maria.timers[PL_T_2] = 0x10;
                    g_Maria.damagePalette = PAL_FLAG(PAL_CC_DARK_EFFECT);
                }
                if (damageEffect & ELEMENT_HOLY) {
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_HIT_BY_HOLY, 0);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x57), 0);
                    g_Maria.timers[PL_T_2] = 8;
                    g_Maria.damagePalette = PAL_FLAG(PAL_CC_GREEN_EFFECT_A);
                }
                if (!(damageEffect & 0xF840)) {
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x53), 0);
                }
            }
        }
        break;
    case 1:
        if ((g_Maria.vram_flag & TOUCHING_CEILING) &&
            MARIA.velocityY < FIX(-1)) {
            MARIA.velocityY = FIX(-1);
        }

        if (MarCheckInput(
                CHECK_80 | CHECK_GRAVITY_HIT | CHECK_GROUND_AFTER_HIT)) {
            return;
        }

        break;
    case 2:
        if ((g_Maria.unk04 & 0x8000) &&
            !(g_Maria.vram_flag & TOUCHING_ANY_SLOPE)) {
            goto block_6dc;
        }

        if ((g_Maria.vram_flag & TOUCHING_ANY_SLOPE) && !(g_GameTimer & 1)) {
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SMOKE_PUFF_2, 10), 0);
        }

        if (!(g_Maria.vram_flag &
              (TOUCHING_L_WALL | TOUCHING_R_WALL | TOUCHING_CEILING))) {
            break;
        }

        if (g_Maria.vram_flag & TOUCHING_CEILING) {
            func_80158B04(1);
            MARIA.velocityX /= 2;
            MARIA.velocityY = 0;
            mar_hit_stun_timer = 0x18;
            MARIA.step_s = 5;
            damageParam.effects = EFFECT_NONE;
            damageParam.damageKind = DAMAGEKIND_1;
            damageParam.damageTaken = g_Maria.damageTaken;
            damageResult = g_api.CalcPlayerDamageMaria(&damageParam);
            if (damageResult) {
                MarSetStep(PL_S_DEAD);
                MarStepDead(0, 2, PL_S_HIT, 2);
                return;
            }
            break;
        }

        if (g_StageId != STAGE_BO6 && g_StageId != STAGE_RBO6 &&
            g_StageId != STAGE_DRE) {
            for (i = 2; i < NUM_VERTICAL_SENSORS; i++) {
                if (g_Maria.colWall[i].effects & EFFECT_UNK_0002) {
                    break;
                }
            }

            if (i == NUM_VERTICAL_SENSORS) {
                for (i = NUM_VERTICAL_SENSORS + 2; i < NUM_VERTICAL_SENSORS * 2;
                     i++) {
                    if (g_Maria.colWall[i].effects & EFFECT_UNK_0002) {
                        break;
                    }
                }
            }

            if (i == NUM_VERTICAL_SENSORS * 2) {
            block_6dc:
                MARIA.velocityY = FIX(-4);
                func_maria_8015CAAC(FIX(-1.25));
                posX = -3;
                if (MARIA.velocityX != 0) {
                    posX = -posX;
                }
                MARIA.posY.i.hi += 20;
                MARIA.posX.i.hi += posX;
                MarCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_EMBERS, 9), 0);
                MARIA.posY.i.hi -= 20;
                MARIA.posX.i.hi -= posX;
                g_api.PlaySfx(SFX_WALL_DEBRIS_B);
                g_api.func_80102CD8(2);
                MARIA.step_s = 1;
                damageParam.effects = EFFECT_NONE;
                damageParam.damageKind = DAMAGEKIND_1;
                damageParam.damageTaken = g_Maria.damageTaken;
                damageResult = g_api.CalcPlayerDamageMaria(&damageParam);
                if (damageResult) {
                    MarSetStep(PL_S_DEAD);
                    MarStepDead(0, 2, PL_S_HIT, 2);
                    return;
                }

                break;
            }
        }

        mar_hit_stun_timer = 8;
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        MARIA.velocityY = FIX(-2.5);
        g_api.func_80102CD8(2);
        MARIA.step_s = 3;
        MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_SKID_SMOKE_2, 8), 0);
        damageParam.effects = EFFECT_NONE;
        damageParam.damageKind = DAMAGEKIND_1;
        damageParam.damageTaken = g_Maria.damageTaken;
        damageResult = g_api.CalcPlayerDamageMaria(&damageParam);
        if (damageResult) {
            MarSetStep(PL_S_DEAD);
            MarStepDead(0, 2, PL_S_HIT, 2);
            return;
        }

        break;
    case 3:
        if (!mar_hit_stun_timer) {
            MarSetSpeedX(FIX(0.75));
            if (MarCheckInput(
                    CHECK_80 | CHECK_GRAVITY_HIT | CHECK_GROUND_AFTER_HIT)) {
                return;
            }
        }
        break;
    case 5:
        MarDecelerateX(FIX(0.125));
        if (mar_hit_stun_timer) {
            if ((g_Maria.vram_flag & TOUCHING_CEILING) && !(g_GameTimer & 3)) {
                func_80158B04(0);
            }
        } else if ((g_Maria.vram_flag & (TOUCHING_L_WALL | TOUCHING_R_WALL)) &&
                   !(g_Maria.vram_flag & (u16)~0xFC)) {
            MARIA.velocityY += FIX(12.0 / 128);
            if (MARIA.velocityY > FIX(7)) {
                MARIA.velocityY = FIX(7);
            }

            if (!(g_GameTimer & 3)) {
                MarCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_SKID_SMOKE_3, 4), 0);
            }
        } else {
            MARIA.step_s = 1;
            MARIA.poseTimer = MARIA.pose = 0;
        }
        break;
    case 6:
        MarDecelerateX(FIX(0.125));
        if (!(g_Maria.vram_flag & TOUCHING_GROUND)) {
            MarSetFall();
        }

        if (MARIA.poseTimer < 0) {
            MarSetStand(MARIA.velocityX);
        }
        break;
    case 7:
        MarDecelerateX(FIX(1.0 / 8.0));
        if (!(g_Maria.vram_flag & TOUCHING_GROUND)) {
            MarSetFall();
        }

        if (MARIA.poseTimer < 0) {
            MarSetCrouch(0, MARIA.velocityX);
        }
        break;
    case 4:
        break;
    }

    if (step_s_zero && g_Maria.unk72) {
        MARIA.velocityY = 0;
    }
}

void MarStepBossGrab(void) {
    DamageParam damage;
    s32 damageResult;

    switch (g_CurrentEntity->step_s) {
    case 0:
        MarResetPose();
        if (g_Maria.unk62 == 0) {
            MARIA.anim = mar_anim_stun;
            g_Maria.timers[PL_T_2] = 8;
            g_Maria.damagePalette = PAL_FLAG(PAL_CC_RED_EFFECT_A);
            g_api.PlaySfx(SFX_VO_MAR_PAIN_B + MAR_SFX_OFFSET);
        }
        MARIA.velocityX = MARIA.velocityY = 0;
        MARIA.step_s = 1;
        g_Maria.unk60 = 2;
        break;
    case 1:
        // Effectively a switch on g_Maria.unk60
        if (g_Maria.unk60 == 3) {
            damage.effects = EFFECT_NONE;
            damage.damageKind = DAMAGEKIND_1;
            damage.damageTaken = g_Maria.damageTaken;
            damageResult = g_api.CalcPlayerDamageMaria(&damage);
            if (damageResult) {
                MarSetStep(PL_S_DEAD);
                MarStepDead(0, 2, PL_S_BOSS_GRAB, 1);
                break;
            }

            if (g_Maria.unk62 == 0) {
                g_Maria.timers[PL_T_2] = 4;
                g_Maria.damagePalette = PAL_FLAG(PAL_CC_RED_EFFECT_A);
                g_api.PlaySfx(SFX_VO_MAR_PAIN_C + MAR_SFX_OFFSET);
            }

            if (g_Maria.unk62 == 2) {
                // nb. bug? Empty block here
            }

            g_Maria.unk60 = 2;
        } else if (g_Maria.unk60 == 4) {
            MARIA.step = PL_S_HIT;
            MARIA.step_s = 2;
            g_Maria.unk60 = 0;
            g_Maria.damageTaken = g_Maria.unk64;
            g_api.PlaySfx(SFX_VO_MAR_PAIN_D + MAR_SFX_OFFSET);
        } else if (g_Maria.unk60 == 0) {
            MARIA.step = PL_S_HIT;
            MARIA.step_s = 1;
        }

        break;
    }
}

static RECT D_801545A0 = {512, 256, 32, 80};
void MarStepDead(s32 damageEffect, s32 damageKind, s32 step, s32 step_s) {
    s32 disableColorChange;
    PlayerDraw* draw;
    s32 scrollX;
    s32 scrollY;

    disableColorChange = 0;
    draw = &g_PlayerDraw[5];

    switch (MARIA.step_s) {
    case 0:
        g_CutsceneFlags |= 0x200;
        MarResetPose();
        func_80159C04();
        func_maria_8015CAAC(FIX(-0.75));
        MarSetAnimation(mar_80155544);
        MARIA.velocityY = FIX(-1.625);
        g_api_PlaySfx(SFX_VO_MAR_DEATH + MAR_SFX_OFFSET);
        MARIA.step_s++;
        break;
    case 1:
        if (MARIA.pose == 3) {
            MarSetAnimation(D_pspeu_092C05A0);
            MARIA.step_s++;
        }
        break;
    case 2:
        // Unusual, FIX usually has denominator of 128
        MARIA.velocityY += FIX(11.0 / 256);
        if (MARIA.velocityY > FIX(1.0 / 16)) {
            StoreImage(&D_801545A0, (u_long*)dead_dissolve_bmp);
            D_80174F6C = 0;
            D_80174F68 = 0x40;
            MARIA.step_s++;
        }
        break;
    case 3:
        MARIA.velocityY += FIX(11.0 / 256);
        if (g_Maria.vram_flag & TOUCHING_GROUND) {
            MarSetAnimation(D_pspeu_09285860);
            MARIA.step_s = 4;
            if (PLAYER.posX.i.hi > MARIA.posX.i.hi) {
                MARIA.facingLeft = 0;
                break;
            }
            MARIA.facingLeft = 1;
        }
        break;
    case 4:
        if (MARIA.velocityX > 0) {
            // nb. Weird no-op here
        }
        MARIA.step_s++;
        // fallthrough
    case 5:
        scrollX = g_Tilemap.scrollX.i.hi + MARIA.posX.i.hi;
        scrollY = g_Tilemap.scrollY.i.hi + MARIA.posY.i.hi;
        if (MARIA.velocityX > 0) {
            if (scrollX > 0x1AC) {
                MARIA.step_s = 0x80;
                MARIA.velocityX = 0;
                break;
            }
        } else if (scrollX < 0x153) {
            MARIA.step_s = 0x80;
            MARIA.velocityX = 0;
        }
        break;
    case 128:
        g_CutsceneFlags |= 0x20;
        break;
    }
}

void func_pspeu_092B0C70(void) {
    if (MARIA.poseTimer < 0) {
        g_Maria.unk4E = 1;
        MarSetStand(0);
        g_Maria.unk46 = 0;
    } else {
        MarStepStand();
    }
}

void MarStepCardinalCrash(void) {
    if (g_Maria.unk5C != 2) {
        g_Maria.unk4E = 1;
        MarSetStand(0);
        g_Maria.unk46 = 0;
    }
}

void MarStepCatCrash(void) {
    if (g_Maria.unk5C != 2) {
        g_Maria.unk4E = 1;
        MarSetStand(0);
        g_Maria.unk46 = 0;
    }
}

void MarStepTurtleCrash(void) {
    if (g_Maria.unk5C != 2) {
        g_Maria.unk4E = 1;
        MarSetStand(0);
        g_Maria.unk46 = 0;
    }
}

void MarStepDragonCrash(void) {
    if (g_Maria.unk5C != 2) {
        g_Maria.unk4E = 1;
        MarSetStand(0);
        g_Maria.unk46 = 0;
    }
}

void MarStepCardinalAttack(void) {
    if (g_Maria.unk66 == 0) {
        MarSetStand(0);
        g_Maria.unk46 = 0;
    }
}

void MarStepSlide(void) {
    s32 isTouchingGround;

    isTouchingGround = 0;
    if (MARIA.facingLeft == 0 && g_Maria.vram_flag & TOUCHING_R_WALL) {
        isTouchingGround = 1;
    }

    if (MARIA.facingLeft && g_Maria.vram_flag & TOUCHING_L_WALL) {
        isTouchingGround = 1;
    }

    if (MARIA.posX.i.hi >= STAGE_WIDTH - 4 && MARIA.facingLeft == 0) {
        isTouchingGround = 1;
    }

    if (MARIA.posX.i.hi < 5 && MARIA.facingLeft) {
        isTouchingGround = 1;
    }

    if ((MARIA.facingLeft == 0 &&
         g_Maria.colFloor[2].effects & EFFECT_UNK_8000) ||
        (MARIA.facingLeft && g_Maria.colFloor[3].effects & EFFECT_UNK_8000)) {
        isTouchingGround = 1;
    }

    if (isTouchingGround != 0 && MARIA.pose < 2) {
        MARIA.pose = 2;

        if (MARIA.velocityX > FIX(1)) {
            MARIA.velocityX = FIX(2);
        }

        if (MARIA.velocityX < FIX(-1)) {
            MARIA.velocityX = FIX(-2);
        }

        MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
    }
    if (MarCheckInput(CHECK_FALL | CHECK_CRASH)) {
        return;
    }
    MarDecelerateX(FIX(0.125));

    switch (MARIA.step_s) {
    case 0:
        if (!(g_GameTimer & 3) && MARIA.pose < 2 && MARIA.pose > 0) {
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SLIDE, 2), 0);
        }

        if (MARIA.pose == 2 && MARIA.poseTimer == 1) {
            MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        }

        if (MARIA.poseTimer < 0) {
            MarSetCrouch(0, MARIA.velocityX);
        }
        break;
    }
}

void MarStepRun(void) {
    s32 halt;
    s32 isTouchingGround;

    halt = 0;
    isTouchingGround = 0;
    MarDecelerateX(FIX(0.375));
    if (MARIA.facingLeft == 0 && g_Maria.vram_flag & TOUCHING_R_WALL) {
        isTouchingGround = 1;
    }

    if (MARIA.facingLeft && g_Maria.vram_flag & TOUCHING_L_WALL) {
        isTouchingGround = 1;
    }

    if (MARIA.posX.i.hi >= STAGE_WIDTH - 4 && MARIA.facingLeft == 0) {
        isTouchingGround = 1;
    }

    if (MARIA.posX.i.hi < 5 && MARIA.facingLeft) {
        isTouchingGround = 1;
    }

    if (isTouchingGround) {
        if (MARIA.velocityX > FIX(1)) {
            MARIA.velocityX = FIX(2);
        }
        if (MARIA.velocityX < FIX(-1)) {
            MARIA.velocityX = FIX(-2);
        }
    }

    if (g_CurrentEntity->anim == D_pspeu_092C0668) {
        if (MARIA.velocityX == 0) {
            halt = 1;
        }
        if (!(g_Maria.vram_flag & TOUCHING_GROUND)) {
            halt = 1;
            MARIA.velocityX = 0;
        }
    } else if (g_Maria.vram_flag & TOUCHING_GROUND) {
        if (MARIA.velocityX == 0) {
            halt = 1;
        }
    } else if (abs(MARIA.velocityX) <= FIX(2)) {
        halt = 1;
    }

    if (g_Maria.vram_flag & (TOUCHING_L_WALL | TOUCHING_R_WALL)) {
        halt = 1;
        MARIA.velocityX = 0;
    }

    if (halt) {
        if (g_Maria.vram_flag & TOUCHING_GROUND) {
            MarSetStand(0);
        } else {
            MarSetFall();
        }
    }
}

// same as DRA/func_80115C50
static s32 func_8015BB80(void) {
    if (g_StageId == STAGE_TOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX) - 8000 > 0) {
            MARIA.posX.i.hi--;
        }

        if (abs((g_Tilemap.left << 8) + g_PlayerX) - 8000 < 0) {
            MARIA.posX.i.hi++;
        }
    }

    if (g_StageId == STAGE_RTOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX) - 8384 > 0) {
            MARIA.posX.i.hi--;
        }

        if (abs((g_Tilemap.left << 8) + g_PlayerX) - 8384 < 0) {
            MARIA.posX.i.hi++;
        }
    }

    return 0;
}

// Corresponding DRA function is PlayerStepTeleport
void MarStepTeleport(void) {
    Entity* entity;

    MARIA.velocityX = MARIA.velocityY = 0;
    g_Maria.padSim = 0;
    g_Maria.demo_timer = 4;

    switch (MARIA.step_s) {
    case 0:
        if (MARIA.pose == 3 && MARIA.poseTimer == 1) {
            entity = MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 0), 0);
            if (entity == NULL) {
                MARIA.poseTimer = 2;
            }
        }

        if (MARIA.poseTimer < 0) {
            MarSetStand(0);
        }

        break;
    case 1:
        if (MARIA.poseTimer < 0) {
            MarSetStand(0);
        }

        if (g_Maria.warp_flag) {
            MarSetStand(0);
        }

        break;
    case 2:
        func_8015BB80();
        if (MARIA.pose == 3 && MARIA.poseTimer == 1) {
            entity = MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 2), 0);
            if (entity == NULL) {
                MARIA.poseTimer = 2;
            }
        }

        if (MARIA.poseTimer < 0) {
            MarSetStand(0);
        }

        break;
    case 3:
        if (MARIA.poseTimer < 0) {
            MarSetStand(0);
        }

        if (g_Maria.warp_flag) {
            MarSetStand(0);
        }

        break;
    case 4:
        func_8015BB80();
        if (MARIA.pose == 3 && MARIA.poseTimer == 1) {
            entity = MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 4), 0);
            if (entity == NULL) {
                MARIA.poseTimer = 2;
            }
        }

        if (MARIA.poseTimer < 0) {
            MarSetStand(0);
        }

        break;
    case 5:
        if (MARIA.poseTimer < 0) {
            MarSetStand(0);
        }

        if (g_Maria.warp_flag) {
            MarSetStand(0);
        }

        break;
    }
}

void MarStepBladeDash(void) {
    MarDecelerateX(FIX(7.0 / 64));
    if (MARIA.poseTimer < 0) {
        g_Maria.unk46 = 0;
        MarSetStand(0);
        return;
    }

    if (MARIA.pose >= 0x12 && !(g_Maria.vram_flag & TOUCHING_GROUND)) {
        g_Maria.unk46 = 0;
        MarSetFall();
        return;
    }

    if (!(g_GameTimer & 3) && MARIA.pose < 0x12 &&
        (g_Maria.vram_flag & TOUCHING_GROUND)) {
        MarCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_SLIDE, 2), 0);
    }

    if (MARIA.pose == 18 && MARIA.poseTimer == 1 &&
        (g_Maria.vram_flag & TOUCHING_GROUND)) {
        MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
    }
}

void MarStepHighJump(void) {
    bool loadAnim;

    loadAnim = false;
    g_Maria.high_jump_timer++;
    switch (MARIA.step_s) {
    case 0:
        if (g_Maria.vram_flag & TOUCHING_CEILING) {
            MARIA.velocityY = FIX(1.5);
            MARIA.step_s = 3;
            g_Maria.high_jump_timer = 0;
        } else if (g_Maria.high_jump_timer > 0x1C) {
            MARIA.step_s = 1;
            MARIA.velocityY = FIX(-6);
        }

        break;
    case 1:
        if (g_Maria.vram_flag & TOUCHING_CEILING) {
            MARIA.velocityY = FIX(1);
            MARIA.step_s = 3;
            g_Maria.high_jump_timer = 0;
        } else {
            MARIA.velocityY += FIX(0.375);
            if (MARIA.velocityY > FIX(0.5)) {
                MARIA.velocityY = FIX(1.5);
                MARIA.step_s = 3;
            }
        }

        break;
    case 3:
        if (g_Maria.padPressed & PAD_RIGHT) {
            MARIA.facingLeft = 0;
            MARIA.velocityX = FIX(1.5);
        } else if (g_Maria.padPressed & PAD_LEFT) {
            MARIA.facingLeft = 1;
            MARIA.velocityX = FIX(-1.5);
        } else {
            MARIA.velocityX = 0;
        }

        if (!(g_Maria.padPressed & PAD_CROSS)) {
            loadAnim = true;
        }

        MarCheckInput(1);
        break;
    }

    if (loadAnim) {
        MarSetAnimation(mar_80155534);
        MarSetStep(PL_S_JUMP);
    } else if (!(VSync(-1) % 15)) {
        PlaySfx(SFX_WING_FLAP_A);
    }
}
