#include "ric.h"
#include "player.h"
#include "sfx.h"

void func_80158B04(s32 arg0) {
    s32 var_s0;

    if (PLAYER.facingLeft) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 4), 0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }

    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}

void RicHandleStand(void) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        } else if (D_80097448[0] >= 49) {
            if (PLAYER.facingLeft) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x800, 4), 0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH | CHECK_SLIDE)) {
        RicDecelerateX(0x2000);
        switch (PLAYER.step_s) {
        case 0:
            if (RicCheckFacing() == 0) {
                if (g_Player.padPressed & PAD_UP) {
                    RicSetAnimation(ric_anim_press_up);
                    PLAYER.step_s = 1;
                    break;
                }
            } else {
                RicSetWalk(0);
            }
            break;

        case 1:
            if (RicCheckFacing() != 0) {
                RicSetWalk(0);
REDACTED
            } else if (g_Player.padPressed & PAD_UP) {
REDACTED
REDACTED
                RicSetStand(0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (PLAYER.animFrameIdx < 3) {
                RicCheckFacing();
                if (g_Player.padPressed & PAD_DOWN) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_801555A8;
REDACTED
REDACTED
REDACTED
REDACTED
            if (PLAYER.animFrameDuration < 0) {
                if (g_Player.padPressed & PAD_SQUARE) {
                    g_Player.unk46 = 2;
REDACTED
                    RicSetAnimation(D_80155730);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 17), 0);
REDACTED
REDACTED
                g_Player.unk46 = 0;
                RicSetStand(0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (g_Player.padPressed & PAD_SQUARE) {
REDACTED
REDACTED
            g_Player.unk46 = 0;
            RicSetStand(0);
REDACTED
REDACTED
REDACTED
REDACTED
            if (PLAYER.animFrameIdx < 3) {
                RicCheckFacing();
            }
            if (PLAYER.animFrameDuration < 0) {
                g_Player.unk46 = 0;
                RicSetStand(0);
            }
        }
    }
}

void RicHandleWalk(void) {
    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH)) {
        RicDecelerateX(0x2000);
        if (RicCheckFacing() == 0) {
            RicSetStand(0);
            return;
        }

        if (PLAYER.step_s == 0) {
            RicSetSpeedX(0x14000);
        }
    }
}

void RicHandleRun(void) {
    if (g_Player.unk7A != 0) {
        RicSetWalk(0);
        return;
    }
    g_Player.D_80072F00[PL_T_8] = 8;
    g_Player.D_80072F00[PL_T_CURSE] = 8;

    if (!RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
                       CHECK_ATTACK | CHECK_CROUCH)) {
        RicDecelerateX(0x2000);
        if (RicCheckFacing() == 0) {
            RicSetStand(0);
            if (g_Player.D_80072F00[PL_T_RUN] == 0) {
                if (!(g_Player.pl_vram_flag & 0xC)) {
                    RicSetAnimation(ric_anim_stop_run);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
REDACTED
REDACTED
                PLAYER.velocityX = 0;
REDACTED
REDACTED
            RicSetSpeedX(0x24000);
        }
    }
}

void RicHandleJump(void) {
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
    // Need at least one fake case to make the switch match
    case 1:
        return;
    case 0:
        RicDecelerateX(0x1000);
        if (RicCheckFacing()) {
            if (g_Player.unk44 & 0x10) {
                RicSetSpeedX(FIX(2.25));
            } else {
                RicSetSpeedX(FIX(1.25));
            }
            g_Player.unk44 &= ~4;
        } else {
            g_Player.unk44 &= ~0x10;
            if ((PLAYER.animFrameIdx < 2) &&
                ((LOW(g_Player.unk44) & 0xC) == 4) &&
                (g_Player.padTapped & PAD_CROSS)) {
                RicSetAnimation(D_8015555C);
                RicSetSpeedX(FIX(-1.5));
                PLAYER.velocityY = FIX(-2.625);
                if (g_Player.unk72) {
                    PLAYER.velocityY = 0;
                }
                PLAYER.step_s = 2;
                g_Player.unk44 |= 0xA;
                g_Player.unk44 &= ~4;
            }
        }
        return;
    case 0x40:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            if (RicCheckFacing() != 0) {
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
            if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
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
                g_Player.unk46 = 2;
                PLAYER.step_s += 1;
                RicSetAnimation(D_80155740);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0, 17), 0);
            } else {
                g_Player.unk46 = 0;
                PLAYER.step_s = 0;
                RicSetAnimation(D_80155528);
            }
        }
        return;
    case 0x41:
        func_8015CB58(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            RicSetAnimation(D_80155528);
        }
        return;
    case 0x42:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            if (RicCheckFacing() != 0) {
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
            if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
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
    }
}

void RicHandleFall(void) {
    if (RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_FALL)) {
        return;
    }
    RicDecelerateX(0x1000);
    if (PLAYER.step_s != 0) {
        return;
    }
    if (g_Player.D_80072F00[PL_T_5] != 0 && g_Player.padTapped & PAD_CROSS) {
        RicSetJump();
    } else if (RicCheckFacing() != 0) {
        RicSetSpeedX(0xC000);
    }
}

void RicHandleCrouch(void) {
    s32 i;
    s16 xShift;

    if ((g_Player.padTapped & PAD_CROSS) && (g_Player.unk46 == 0) &&
        (g_Player.padPressed & PAD_DOWN)) {
        for (i = 0; i < 4; i++) {
            if (g_Player.colliders[i].effects & EFFECT_SOLID_FROM_ABOVE) {
                g_Player.D_80072F00[PL_T_7] = 8;
                return;
            }
        }
    }
    if (RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_ATTACK | CHECK_SLIDE)) {
        return;
    }
    if ((g_Player.padTapped & PAD_CROSS) && (g_Player.unk46 == 0) &&
        (!g_Player.unk72)) {
        RicSetJump(1);
        return;
    } else if ((!g_Player.unk72) && (g_Player.unk46 == 0) &&
               (g_Player.padTapped & PAD_TRIANGLE) && RicDoCrash()) {
        return;
    }
    RicDecelerateX(0x2000);
    switch (PLAYER.step_s) {
    case 0x0:
REDACTED
REDACTED
        } else if ((*D_80097448 >= 0x19) && (g_Player.unk48 == 0)) {
            if (PLAYER.facingLeft) {
                xShift = -9;
            } else {
                xShift = 9;
            }
            PLAYER.posX.i.hi += xShift;
            PLAYER.posY.i.hi += 2;
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x800, 4), 0);
            D_8015459C = 0x60;
            PLAYER.posY.i.hi -= 2;
            PLAYER.posX.i.hi -= xShift;
        }
        if (!(g_Player.padPressed & PAD_DOWN) &&
            ((!g_Player.unk72) || !(g_Player.pl_vram_flag & 0x40))) {
            RicSetAnimation(D_801554E0);
            PLAYER.step_s = 2;
            return;
        }
        break;
    case 0x1:
        if (!(g_Player.padPressed & PAD_DOWN) &&
            ((!g_Player.unk72) || !(g_Player.pl_vram_flag & 0x40))) {
            if (RicCheckFacing() == 0) {
                PLAYER.anim = D_801554E0;
                PLAYER.step_s = 2;
                PLAYER.animFrameDuration = 1;
                PLAYER.animFrameIdx = 2 - PLAYER.animFrameIdx;
                return;
            }
            RicSetWalk(0);
            return;
        }
    case 0x4:
        if (PLAYER.animFrameDuration != -1) {
            return;
        }
        RicSetAnimation(ric_anim_crouch);
        PLAYER.step_s = 0;
        return;
    case 0x2:
        if ((!g_Player.unk72) || !(g_Player.pl_vram_flag & 0x40)) {
            if (RicCheckFacing() != 0) {
                RicSetWalk(0);
                return;
            }
            if (PLAYER.animFrameDuration == -1) {
                RicSetStand(0);
                return;
            }
        }
        break;
    case 0x3:
        if (PLAYER.animFrameDuration < 0) {
            RicSetAnimation(ric_anim_crouch);
            PLAYER.step_s = 0;
            return;
        }
        break;
    case 0x40:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            RicCheckFacing();
            if (!(g_Player.padPressed & PAD_DOWN) && (!g_Player.unk72)) {
                PLAYER.step = PL_S_STAND;
                PLAYER.anim = D_80155588;
                return;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            if (g_Player.padPressed & PAD_SQUARE) {
                g_Player.unk46 = 2;
                PLAYER.step_s++;
                RicSetAnimation(D_80155738);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0, 17), 0);
                return;
            }
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            RicSetAnimation(ric_anim_crouch);
        }
        break;
    case 0x41:
        func_8015CB58(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            RicSetAnimation(ric_anim_crouch);
        }
        break;
    }
}

void func_80159BC8(void) {
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.drawFlags &= ~FLAG_DRAW_ROTZ;
}

void func_80159C04(void) {
    Entity* entity = PLAYER.ext.player.unkB8;
    s16 temp_v0;
    s32 var_a0;
    s32 var_a2;

    if (entity->facingLeft) {
        var_a2 = -entity->hitboxOffX;
REDACTED
        var_a2 = entity->hitboxOffX;
REDACTED
REDACTED
    if (PLAYER.facingLeft) {
        var_a0 = -PLAYER.hitboxOffX;
REDACTED
        var_a0 = PLAYER.hitboxOffX;
REDACTED
REDACTED
REDACTED
REDACTED
    if (abs(temp_v0) < 16) {
        if (entity->velocityX != 0) {
            if (entity->velocityX < 0) {
                PLAYER.entityRoomIndex = 0;
REDACTED
REDACTED
                PLAYER.entityRoomIndex = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        PLAYER.entityRoomIndex = 0;
REDACTED
        PLAYER.entityRoomIndex = 1;
REDACTED
REDACTED

void RicHandleDead(
    s32 damageEffects, s32 damageKind, s32 prevStep, s32 prevStepS);

static s32 ric_hit_stun_timer;
void RicHandleHit(s32 damageEffect, u32 damageKind, s16 prevStep) {
    DamageParam damage;
    s32 xShift;
    s32 i;
    bool step_s_zero = false;

    if (ric_hit_stun_timer) {
        ric_hit_stun_timer--;
    }
    switch (PLAYER.step_s) {
    case 0:
        step_s_zero = true;
        func_80159BC8();
        if (damageKind < 16) {
            func_80159C04();
        } else {
            PLAYER.entityRoomIndex = PLAYER.facingLeft;
        }
        if (damageEffect & ELEMENT_THUNDER) {
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 48), 0);
            PLAYER.velocityY = FIX(-4);
            func_8015CAAC(FIX(-1.25));
            PLAYER.step_s = 1;
            PLAYER.anim = D_801556C4;
            g_Player.unk40 = 0x8120;
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 48), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x4600, 33), 0);
            g_Player.D_80072F00[PL_T_2] = 6;
            g_api.PlaySfx(0x703);
            break;
        } else {
            if (damageEffect & ELEMENT_ICE) {
                damageKind = 3;
            }
            switch (damageKind - 2) {
            case 0:
                switch (prevStep) {
                case PL_S_STAND:
                case PL_S_WALK:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 6;
                    PLAYER.anim = D_8015569C;
                    g_api.PlaySfx(0x702);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    break;
                case PL_S_CROUCH:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 7;
                    PLAYER.anim = D_80155704;
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    g_api.PlaySfx(0x703);
                    break;
                case PL_S_FALL:
                case PL_S_JUMP:
                    PLAYER.velocityY = FIX(-3);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.anim = ric_anim_stun;
                    g_api.PlaySfx(0x702);
                    break;
                }
                break;
            case 2:
            case 3:
                PLAYER.velocityY = FIX(-0.5);
                g_Player.damageTaken = PLAYER.hitPoints;
                PLAYER.posY.val -= 1;
                func_8015CAAC(FIX(-8));
                PLAYER.step_s = 2;
                PLAYER.anim = ric_anim_stun;
                g_Player.D_80072F00[PL_T_2] = 0x200;
                PLAYER.facingLeft = PLAYER.entityRoomIndex;
                break;
            default:
            case 1:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
                switch (prevStep) {
                default:
                case PL_S_STAND:
                case PL_S_WALK:
                    PLAYER.velocityY = FIX(-4);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.anim = ric_anim_stun;
                    g_api.PlaySfx(0x702);
                    break;
                case PL_S_CROUCH:
                    PLAYER.velocityY = 0;
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 7;
                    PLAYER.anim = D_80155704;
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                    g_api.PlaySfx(0x703);
                    break;
                case PL_S_FALL:
                case PL_S_JUMP:
                    PLAYER.velocityY = FIX(-3);
                    func_8015CAAC(FIX(-1.25));
                    PLAYER.step_s = 1;
                    PLAYER.anim = ric_anim_stun;
                    g_api.PlaySfx(0x702);
                    break;
                }
                break;
            }
            g_Player.unk40 = 0x8166;
            g_Player.D_80072F00[PL_T_2] = 6;
            if (damageEffect & ELEMENT_FIRE) {
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x100, 8), 0);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0, 9), 0);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x4300, 33), 0);
                g_Player.unk40 = 0x8160;
                g_Player.D_80072F00[PL_T_2] = 0x10;
                break;
            } else if (damageEffect & ELEMENT_CUT) {
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x500, 46), 0);
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x4400, 33), 0);
                g_Player.unk40 = 0x8166;
                g_Player.D_80072F00[PL_T_2] = 0x10;
                break;
            } else if (damageEffect & ELEMENT_ICE) {
                // Creates EntityHitByIce
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0, 47), 0);
                g_Player.D_80072F00[PL_T_2] = 0xC;
                g_Player.unk40 = 0x8169;
                break;
            } else {
                if (damageEffect & ELEMENT_DARK) {
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 70), 0);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5600, 33), 0);
                    g_Player.D_80072F00[PL_T_2] = 0x10;
                    g_Player.unk40 = 0x8164;
                }
                if (damageEffect & ELEMENT_HOLY) {
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 71), 0);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5700, 33), 0);
                    g_Player.D_80072F00[PL_T_2] = 8;
                    g_Player.unk40 = 0x8168;
                }
                if (!(damageEffect & 0xF840)) {
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x5300, 33), 0);
                }
            }
        }
        break;
    case 1:
        if ((g_Player.pl_vram_flag & 2) && (PLAYER.velocityY < FIX(-1))) {
            PLAYER.velocityY = FIX(-1);
        }
        if (RicCheckInput(
                CHECK_80 | CHECK_GRAVITY_HIT | CHECK_GROUND_AFTER_HIT)) {
            return;
        }
        break;
    case 2:
        if ((g_Player.unk04 & 0x8000) && !(g_Player.pl_vram_flag & 0x8000)) {
            goto block_6dc;
        }
        if ((g_Player.pl_vram_flag & 0x8000) && !(g_GameTimer & 1)) {
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0xA00, 74), 0);
        }
        if (!(g_Player.pl_vram_flag & 0xE)) {
            break;
        }
        if (g_Player.pl_vram_flag & 2) {
            func_80158B04(1);
            ric_hit_stun_timer = 0x18;
            PLAYER.velocityX /= 2;
            PLAYER.velocityY = 0;
            PLAYER.step_s = 5;
            damage.effects = 0;
            damage.damageKind = 1;
            damage.damageTaken = g_Player.damageTaken;
            if (g_api.CalcPlayerDamage(&damage)) {
                RicSetStep(PL_S_DEAD);
                RicHandleDead(0, 2, PL_S_HIT, 2);
                return;
            }
            break;
        } else {
            if ((g_StageId != STAGE_BO6) && (g_StageId != STAGE_RBO6) &&
                (g_StageId != STAGE_DRE)) {
                for (i = 2; i < 7; i++) {
                    if (g_Player.colliders3[i].effects & 2) {
                        break;
                    }
                }
                if (i == 7) {
                    for (i = 9; i < 0xE; i++) {
                        if (g_Player.colliders3[i].effects & 2) {
                            break;
                        }
                    }
                }
                if (i == 14) {
                block_6dc:
                    PLAYER.velocityY = FIX(-4);
                    func_8015CAAC(FIX(-1.25));
                    xShift = -3;
                    if (PLAYER.velocityX != 0) {
                        xShift = 3;
                    }
                    PLAYER.posY.i.hi += 20;
                    PLAYER.posX.i.hi = xShift + PLAYER.posX.i.hi;
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x900, 4), 0);
                    PLAYER.posY.i.hi -= 20;
                    PLAYER.posX.i.hi -= xShift;
                    g_api.PlaySfx(SFX_WALL_DEBRIS_B);
                    g_api.func_80102CD8(2);
                    PLAYER.step_s = 1;
                    damage.effects = 0;
                    damage.damageKind = 1;
                    damage.damageTaken = g_Player.damageTaken;
                    if (g_api.CalcPlayerDamage(&damage)) {
                        RicSetStep(PL_S_DEAD);
                        RicHandleDead(0, 2, PL_S_HIT, 2);
                        return;
                    }
                    break;
                }
            }
            ric_hit_stun_timer = 8;
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            PLAYER.velocityY = FIX(-2.5);
            g_api.func_80102CD8(2);
            PLAYER.step_s = 3;
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x800, 75), 0);
        }
        damage.effects = 0;
        damage.damageKind = 1;
        damage.damageTaken = g_Player.damageTaken;
        if (g_api.CalcPlayerDamage(&damage)) {
            RicSetStep(PL_S_DEAD);
            RicHandleDead(0, 2, PL_S_HIT, 2);
            return;
        }
        break;
    case 3:
        if (!ric_hit_stun_timer) {
            RicSetSpeedX(FIX(0.75));
            if (RicCheckInput(
                    CHECK_80 | CHECK_GRAVITY_HIT | CHECK_GROUND_AFTER_HIT)) {
                return;
            }
        }
        break;
    case 5:
        RicDecelerateX(0x2000);
        if (ric_hit_stun_timer) {
            if ((g_Player.pl_vram_flag & 2) && !(g_GameTimer & 3)) {
                func_80158B04(0);
            }
            break;
        } else if (g_Player.pl_vram_flag & 0xC) {
            if (!(g_Player.pl_vram_flag & 0xFF03)) {
                PLAYER.velocityY += FIX(12.0 / 128);
                if (PLAYER.velocityY > FIX(7)) {
                    PLAYER.velocityY = FIX(7);
                }
                if (!(g_GameTimer & 3)) {
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x400, 76), 0);
                }
                break;
            }
        }
        PLAYER.step_s = 1;
        PLAYER.animFrameIdx = 0;
        PLAYER.animFrameDuration = 0;
        break;
    case 6:
        RicDecelerateX(0x2000);
        if (!(g_Player.pl_vram_flag & 1)) {
            RicSetFall();
        }
        if (PLAYER.animFrameDuration < 0) {
            if (!g_Player.unk5C || g_Status.hp > 0) {
                RicSetStand(PLAYER.velocityX);
                break;
            }
            RicSetDeadPrologue();
            return;
        }
        break;
    case 7:
        RicDecelerateX(0x2000);
        if (!(g_Player.pl_vram_flag & 1)) {
            RicSetFall();
        }
        if (PLAYER.animFrameDuration < 0) {
            if (g_Player.unk5C && g_Status.hp <= 0) {
                RicSetDeadPrologue();
                return;
            }
            RicSetCrouch(0, PLAYER.velocityX);
        }
        break;
    }
    if (step_s_zero && (g_Player.unk72)) {
        PLAYER.velocityY = 0;
    }
}

void RicHandleBossGrab(void) {
    DamageParam damage;
    switch (g_CurrentEntity->step_s) {
    case 0:
        func_80159BC8();
        if (g_Player.unk62 == 0) {
            PLAYER.anim = ric_anim_stun;
            g_Player.D_80072F00[PL_T_2] = 8;
            g_Player.unk40 = 0x8166;
            g_api.PlaySfx(0x702);
        }
        PLAYER.step_s = 1;
        PLAYER.velocityX = PLAYER.velocityY = 0;
        g_Player.unk60 = 2;
        return;
    case 1:
        // Effectively a switch on g_Player.unk60
        if (g_Player.unk60 == 3) {
            damage.effects = 0;
            damage.damageKind = 1;
            damage.damageTaken = g_Player.damageTaken;
            if (g_api.CalcPlayerDamage(&damage)) {
                RicSetStep(PL_S_DEAD);
                RicHandleDead(0, 2, PL_S_BOSS_GRAB, 1);
                return;
            }
            if (g_Player.unk62 == 0) {
                g_Player.D_80072F00[PL_T_2] = 4;
                g_Player.unk40 = 0x8166;
                g_api.PlaySfx(0x703);
            }
            g_Player.unk60 = 2;
        } else if (g_Player.unk60 == 4) {
            PLAYER.step = PL_S_HIT;
            PLAYER.step_s = 2;
            g_Player.unk60 = 0;
            g_Player.damageTaken = g_Player.unk64;
            g_api.PlaySfx(0x704);
        } else if (g_Player.unk60 == 0) {
            PLAYER.step = PL_S_HIT;
            PLAYER.step_s = 1;
        }
    }
}

// Compare to DRA func_80115394
enum DeathKind {
    DEATH_GENERIC,
    DEATH_BY_FIRE,
    DEATH_BY_THUNDER,
    DEATH_BY_ICE,
};
static u8 dead_dissolve_bmp[0x1400];
static s16 D_80174F68;
STATIC_PAD_BSS(2);
static s16 D_80174F6C;
STATIC_PAD_BSS(2);
static enum DeathKind death_kind;
void RicHandleDead(
    s32 damageEffects, s32 damageKind, s32 prevStep, s32 prevStepS) {
    s32 j;
    s32 i;
    u8* s2;
    u8* imgPtr;
    s32 disableColorChange = 0;
    PlayerDraw* playerDraw = &g_PlayerDraw[0];

    switch (PLAYER.step_s) {
    case 0:
        func_80159BC8();
        func_80159C04();
        func_8015CAAC(FIX(-0.75));
        RicSetAnimation(D_80155544);
        PLAYER.velocityY = FIX(-1.625);
        g_api.PlaySfx(SFX_UNK_6FF);
        if (damageEffects & ELEMENT_FIRE) {
            func_8015FA5C(0);
            // RIC blueprint 33 has child 31, EntityPlayerBlinkWhite
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x4800, 33), 0);
            // RIC blueprint 53 has child 9, func_80161C2C
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x200, 53), 0);
            death_kind = DEATH_BY_FIRE;
        } else if (damageEffects & ELEMENT_THUNDER) {
            func_8015FA5C(2);
            // RIC blueprint 33 has child 31, EntityPlayerBlinkWhite
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x4C00, 33), 0);
            // RIC blueprint 48 has child 41, EntityHitByLightning
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x100, 48), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x200, 48), 0);
            death_kind = DEATH_BY_THUNDER;
        } else if (damageEffects & ELEMENT_ICE) {
            func_8015FA5C(3);
            // RIC blueprint 33 has child 31, EntityPlayerBlinkWhite
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x4D00, 33), 0);
            // RIC blueprint 47 has child 40, EntityHitByIce
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 47), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x100, 47), 0);
            death_kind = DEATH_BY_ICE;
            PLAYER.drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            func_8015FA5C(1);
            // RIC blueprint 33 has child 31, EntityPlayerBlinkWhite
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x4A00, 33), 0);
            // RIC blueprint 11 has child 5, func_8016147C
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x500, 11), 0);
            death_kind = DEATH_GENERIC;
        }
        playerDraw->r0 = playerDraw->b0 = playerDraw->g0 = playerDraw->r1 =
            playerDraw->b1 = playerDraw->g1 = playerDraw->r2 = playerDraw->b2 =
                playerDraw->g2 = playerDraw->r3 = playerDraw->b3 =
                    playerDraw->g3 = 0x80;
        playerDraw->enableColorBlend = 1;
        PLAYER.step_s++;
        break;
    case 1:
        if (PLAYER.animFrameIdx != 4) {
            break;
        }
        PLAYER.step_s++;
        break;
    case 2:
        // Unusual, FIX usually has denominator of 128
        PLAYER.velocityY += FIX(11.0 / 256);
        if (PLAYER.velocityY > FIX(1.0 / 16)) {
            PLAYER.velocityY >>= 2;
            PLAYER.velocityX >>= 3;
            StoreImage(&D_801545A0, dead_dissolve_bmp);
            D_80174F6C = 0;
            D_80174F68 = 0x40;
            PLAYER.step_s++;
        }
        break;
    case 3:
        if (g_Timer & 1) {
            break;
        }
        if (D_80174F68 > 16) {
            // Another really weird velocityY value.
            // It's 0x233.
            PLAYER.velocityY += FIX(0.0086);
        } else {
            PLAYER.velocityX = 0;
            PLAYER.velocityY = 0;
        }
        for (i = 0; i < 4; i++) {
            s2 = imgPtr = dead_dissolve_bmp;
            s2 += ((D_80174F6C >> 1) & 7);
            s2 += ((D_80174F6C & 0xFF) >> 4) << 6;
            for (j = 0; j < 0x28; j++) {
                if (D_80174F6C & 1) {
                    *(s2 + ((j & 7) * 8) + ((j >> 3) * 0x400)) &= 0xF0;
                } else {
                    *(s2 + ((j & 7) * 8) + ((j >> 3) * 0x400)) &= 0x0F;
                }
            }
            D_80174F6C += 0x23;
            D_80174F6C &= 0xFF;
        }
        LoadImage(&D_801545A0, imgPtr);
        if (--D_80174F68 == 0) {
            PLAYER.velocityY = 0;
            playerDraw->enableColorBlend = 0;
            PLAYER.step_s = 0x80;
        }
        break;
    case 0x80:
        break;
    }
    // Always happens, kind of weird
    if (!disableColorChange) {
        if (death_kind == DEATH_GENERIC) {
            if (playerDraw->r0 < 0xF8) {
                playerDraw->r0 += 2;
            }
            if (playerDraw->g0 > 8) {
                playerDraw->g0 -= 2;
            }

            playerDraw->r3 = playerDraw->r2 = playerDraw->r1 = playerDraw->r0;
            playerDraw->b0 = playerDraw->b1 = playerDraw->g1 = playerDraw->b2 =
                playerDraw->g2 = playerDraw->b3 = playerDraw->g3 =
                    playerDraw->g0;
        }
        if (death_kind == DEATH_BY_FIRE || death_kind == DEATH_BY_THUNDER) {
            if (playerDraw->g0 > 8) {
                playerDraw->g0 -= 2;
            }
            playerDraw->r3 = playerDraw->r2 = playerDraw->r1 = playerDraw->r0 =
                playerDraw->b0 = playerDraw->b1 = playerDraw->g1 =
                    playerDraw->b2 = playerDraw->g2 = playerDraw->b3 =
                        playerDraw->g3 = playerDraw->g0;
        }
        if (death_kind == DEATH_BY_ICE) {
            if ((playerDraw->r0 > 8) && (g_Timer & 1)) {
                playerDraw->r0 -= 1;
            }
            playerDraw->r3 = playerDraw->r2 = playerDraw->r1 = playerDraw->b3 =
                playerDraw->b2 = playerDraw->b1 = playerDraw->b0 =
                    playerDraw->r0;
        }
    }
}

void RicHandleStandInAir(void) {
REDACTED
        PLAYER.velocityY += 0x3800;
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = 0;
REDACTED
REDACTED
    } else if (g_Player.unk4E != 0) {
        g_Player.unk46 = 0;
        RicSetStep(PL_S_JUMP);
        RicSetAnimation(D_80155528);
        g_Player.unk44 = 0;
    }
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

void RicHandleEnableFlameWhip(void) {
    if ((PLAYER.animCurFrame == 0xB5) && (PLAYER.animFrameDuration == 1)) {
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 35), 0);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
    }

    if (PLAYER.animFrameDuration < 0) {
        RicSetStand(0);
        g_Player.unk46 = 0;
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4500, 33), 0);
        g_Player.D_80072F00[PL_T_POISON] = 0x800;
    }

    if (!(g_Player.pl_vram_flag & 1)) {
        RicSetFall();
        g_Player.unk46 = 0;
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x4500, 33), 0);
        g_Player.D_80072F00[PL_T_POISON] = 0x800;
    }
}

void RicHandleHydrostorm(void) {
    if (PLAYER.animFrameDuration < 0) {
        RicSetStand(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.pl_vram_flag & 1) == 0) {
        RicSetFall();
        g_Player.unk46 = 0;
    }
}

void RicHandleGenericSubwpnCrash(void) {
    if (g_Player.unk4E) {
        RicSetStand(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.pl_vram_flag & 1) == 0) {
        RicSetFall();
        g_Player.unk46 = 0;
    }
}

static s32 throw_dagger_timer;
void RicHandleThrowDaggers(void) {
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
    if (!(g_Player.pl_vram_flag & 1)) {
        RicSetFall();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        throw_dagger_timer = 0;
    }
}

// This happens when he dies in prologue and gets saved by Maria.
static s32 dead_prologue_timer;
void RicHandleDeadPrologue(void) {
REDACTED
REDACTED
        g_CurrentEntity->flags |= FLAG_UNK_10000;
        g_unkGraphicsStruct.unk20 = 4;
        RicDecelerateX(0x2000);
        if (PLAYER.velocityX == 0) {
            RicSetAnimation(D_80155748);
            g_Player.D_80072F00[PL_T_INVINCIBLE] = 4;
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 29), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x900, 33), 0);
            D_801545AC = 0;
            PLAYER.step_s++;
        }
        break;
REDACTED
        PLAYER.drawFlags = FLAG_DRAW_ROTY;
REDACTED
        PLAYER.rotY = (rsin(D_801545AA) >> 0xA) + 256;
REDACTED
REDACTED
REDACTED
                PLAYER.drawFlags = 0;
                PLAYER.rotY = 0x100;
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0, 23), 0);
                g_DeadPrologueTimer = 0x90;
                PLAYER.step_s++;
            }
        }
        break;
REDACTED
        // In this step, Richter rises into the air, similar to when he uses the
        // Cross subweapon crash.
        if (!--g_DeadPrologueTimer) {
            RicSetAnimation(D_801558B4);
REDACTED
            g_CurrentEntity->velocityY = FIX(-1);
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 22), 0);
            g_DeadPrologueTimer = 0x30;
            g_api.PlaySfx(0x6E2);
            dead_prologue_timer = 0xA0;
            PLAYER.step_s++;
        }
        break;
    case 3:
        if (!--g_DeadPrologueTimer) {
            PLAYER.velocityY = 0;
            g_DeadPrologueTimer = 0xC0;
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 36), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x200, 37), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x300, 38), 0);
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x400, 39), 0);
            PLAYER.palette = 0x813D;
            g_Player.D_80072F00[PL_T_INVINCIBLE] = 0;
            PLAYER.step_s++;
        }
        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }
        dead_prologue_timer--;
        if ((dead_prologue_timer >= 0) && (dead_prologue_timer % 20 == 0)) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;
    case 4:
        if (!--g_DeadPrologueTimer) {
            g_DeadPrologueTimer = 0x10;
            PLAYER.step_s++;
        }
        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }
        dead_prologue_timer--;
        if ((dead_prologue_timer >= 0) && (dead_prologue_timer % 20 == 0)) {
            g_api.PlaySfx(NA_SE_PL_RIC_UNK_6E2);
        }
        break;
    case 5:
        if (g_DeadPrologueTimer == 5) {
            PLAYER.animFrameIdx = 6;
            PLAYER.palette = 0x8120;
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 28), 0);
        }
        if (!--g_DeadPrologueTimer) {
            RicSetAnimation(D_801558D4);
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 27), 0);
            PLAYER.step_s++;
            break;
        }
        if (g_Status.hp < g_Status.hpMax) {
            g_Status.hp++;
        }
        break;
    case 6:
        if (PLAYER.animFrameDuration < 0) {
            RicSetAnimation(D_801558DC);
            PLAYER.step_s++;
        }
        break;
REDACTED
        if (PLAYER.animFrameDuration < 0) {
            g_CurrentEntity->flags &= ~FLAG_UNK_10000;
            g_unkGraphicsStruct.unk20 = 0;
            RicSetFall();
            RicSetAnimation(D_801558DC);
            g_Player.D_80072F00[PL_T_INVINCIBLE] = 4;
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x900, 33), 0);
        }
        break;
    }
}

void RicHandleSlide(void) {
    s32 isTouchingGround = 0;

    if (!PLAYER.facingLeft) {
        isTouchingGround = (g_Player.pl_vram_flag & 4) != isTouchingGround;
    } else if (g_Player.pl_vram_flag & 8) {
        isTouchingGround = 1;
    }
    if ((PLAYER.posX.i.hi > (u8)-5) && (!PLAYER.facingLeft)) {
        isTouchingGround = 1;
    }
    if (PLAYER.posX.i.hi < 5 && (PLAYER.facingLeft)) {
        isTouchingGround = 1;
    }
    if ((!PLAYER.facingLeft &&
         (g_Player.colliders[2].effects & EFFECT_UNK_8000)) ||
        (PLAYER.facingLeft &&
         (g_Player.colliders[3].effects & EFFECT_UNK_8000))) {
        isTouchingGround = 1;
    }
    if (isTouchingGround && (PLAYER.animFrameIdx < 6)) {
        PLAYER.animFrameIdx = 6;
        if (PLAYER.velocityX > FIX(1)) {
            PLAYER.velocityX = FIX(2);
        }
        if (PLAYER.velocityX < FIX(-1)) {
            PLAYER.velocityX = FIX(-2);
        }
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
    }
    if (PLAYER.animFrameIdx < 5) {
        if (RicCheckInput(CHECK_FALL | CHECK_CRASH)) {
            return;
        }
        if ((!g_Player.unk72) && (g_Player.padTapped & PAD_CROSS)) {
            PLAYER.posY.i.hi -= 4;
            RicSetSlideKick();
            return;
        }
    } else if (PLAYER.animFrameIdx < 7) {
        if (RicCheckInput(CHECK_FALL | CHECK_CRASH | CHECK_SLIDE)) {
            return;
        }
    } else if (
        RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_CRASH | CHECK_SLIDE)) {
        return;
    }

    RicDecelerateX(0x2000);
    if (PLAYER.step_s == 0) {
        if (!(g_GameTimer & 3) && (2 < PLAYER.animFrameIdx) &&
            (PLAYER.animFrameIdx < 6)) {
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x200, 24), 0);
        }
        if (PLAYER.animFrameIdx == 6 && PLAYER.animFrameDuration == 1) {
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
        }
        if (PLAYER.animFrameDuration < 0) {
            RicSetCrouch(0, PLAYER.velocityX);
        }
    }
}
REDACTED
// same as DRA/func_80115C50
REDACTED
    if (g_StageId == STAGE_TOP) {
        if (abs(g_Tilemap.left * 256 + g_PlayerX) - 8000 > 0) {
            PLAYER.posX.i.hi--;
        }

        if (abs(g_Tilemap.left * 256 + g_PlayerX) - 8000 < 0) {
REDACTED
REDACTED
REDACTED
REDACTED
    if (g_StageId == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {

        if (abs(g_Tilemap.left * 256 + g_PlayerX) - 8384 > 0) {
            PLAYER.posX.i.hi--;
        }

        if (abs(g_Tilemap.left * 256 + g_PlayerX) - 8384 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
