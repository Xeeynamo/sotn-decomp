// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

// ===== pl_main.c

typedef enum {
    TELEPORT_CHECK_NONE = 0,
    TELEPORT_CHECK_TO_RTOP = 2,
    TELEPORT_CHECK_TO_TOP = 4
} TeleportCheck;

// GetTeleportToOtherCastle
static TeleportCheck func_060A5060(void) {
    if (PLAYER.step != PL_S_STAND || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }
    if (g_CurrentRoom.stageID == STAGE_TOP) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX - 8079) < 4 &&
            ABS((g_Tilemap.top << 8) + g_PlayerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }
    if (g_CurrentRoom.stageID == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX - 8430) < 4 &&
            ABS((g_Tilemap.top << 8) + g_PlayerY - 14407) < 4) {
            return TELEPORT_CHECK_TO_TOP;
        }
    }
    return TELEPORT_CHECK_NONE;
}

// func_80156DE4
static s16 func_80156DE4(void) {
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    s32 xCenter;
    s32 xRight;
    s32 xLeft;
    s32 filter;

    filter = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
    xCenter = PLAYER.posX.val;
    xRight = PLAYER.posX.val + FIX(4);
    xLeft = PLAYER.posX.val - FIX(4);

    for (i = 0; i < 3; i++) {
        yvar = PLAYER.posY.val + D_80154568[i];
        collisions = 0;
        CheckCollision(xCenter, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions++;
        }
        CheckCollision(xRight, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions++;
        }
        CheckCollision(xLeft, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions++;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}

// RicInit
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5208, func_060A5208);

// CheckStageCollision
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5518, func_060A5518);

typedef struct {
    s16 buttonsCorrect;
    s16 timer;
} ButtonComboState;
extern ButtonComboState g_RicComboButtons[2];

// CheckBladeDashInput
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5864, func_060A5864);

// CheckHighJumpInput
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5988, func_060A5988);

INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60A5AA0, func_060A5AA0);

// ===== pl_steps.c

// func_80158B04
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A6428, func_060A6428);

// RicStepStand
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A64CC, func_060A64CC);

#define RicSetSpeedX(speed)                                                    \
    do {                                                                       \
        s32 _tmp_speed = (speed);                                              \
        if (g_CurrentEntity->facingLeft == 1)                                  \
            _tmp_speed = -_tmp_speed;                                          \
        g_CurrentEntity->velocityX = _tmp_speed;                               \
    } while (0)

enum RicInputChecks {
    CHECK_GROUND = 1,
    CHECK_FALL = 4,
    CHECK_FACING = 8,
    CHECK_JUMP = 0x10,
    CHECK_CRASH = 0x40,
    CHECK_80 = 0x80,
    CHECK_GRAVITY_HIT = 0x200,
    CHECK_ATTACK = 0x1000,
    CHECK_CROUCH = 0x2000,
    CHECK_GRAVITY_FALL = 0x8000,
    CHECK_GRAVITY_JUMP = 0x10000,
    CHECK_GROUND_AFTER_HIT = 0x20000,
    CHECK_SLIDE = 0x40000,
};

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
    if (g_Player.unk7A != 0) {
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

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A68A0, func_060A68A0);
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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A6DFC, func_060A6DFC);
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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A7B78, func_060A7B78);
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

// RicStepDeadPrologue
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A82F8, func_060A82F8);

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A8664, func_060A8664);
static void func_8015BB80(void) {
    if (g_CurrentRoom.stageID == STAGE_TOP) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8079 > 0) {
            PLAYER.posX.i.hi--;
        }
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8079 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
    if (g_CurrentRoom.stageID == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8430 > 0) {
            PLAYER.posX.i.hi--;
        }
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8430 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A892C, func_060A892C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A8A58, func_060A8A58);
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
            PLAYER.velocityY = -0x60000;
        }
        break;
    case 1:
        if (g_Player.vram_flag & TOUCHING_CEILING) {
            PLAYER.step_s = 2;
            func_060A6428(3);
            g_Player.high_jump_timer = 0;
        } else {
            PLAYER.velocityY += 0x6000;
            if (PLAYER.velocityY > 0x8000) {
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

// ===== pl_setstep.c

AnimationFrame D_80155950[];
AnimationFrame D_8015591C[];
// func_060A8EB8
void RicSetInit(s32 step_s) {
    PLAYER.step = PL_S_INIT;
    PLAYER.step_s = step_s;
    PLAYER.pose = PLAYER.poseTimer = 0;
    if (step_s & 1) {
        PLAYER.anim = D_80155950;
    } else {
        PLAYER.anim = D_8015591C;
    }
}

// RicSetCrouch
extern AnimationFrame ric_anim_crouch[];
extern AnimationFrame ric_anim_land_from_air_run[];
void RicSetCrouch(s32 kind, s32 velocityX) {
    RicSetStep(PL_S_CROUCH);
    RicSetAnimation(ric_anim_crouch);
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    if (kind == 1) {
        PLAYER.anim = ric_anim_crouch_from_stand2;
        PLAYER.step_s = 4;
    }
    if (kind == 2) {
        PLAYER.anim = ric_anim_crouch_from_stand;
        PLAYER.step_s = 1;
    }
    if (kind == 3) {
        PLAYER.anim = ric_anim_land_from_air_run;
        PLAYER.step_s = 4;
    }
}

// RicSetStand
extern AnimationFrame ric_anim_stand[];
void RicSetStand(s32 velocityX) {
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    g_Player.unk44 = 0;
    RicSetStep(PL_S_STAND);
    RicSetAnimation(ric_anim_stand);
}

extern AnimationFrame ric_anim_walk[];
// func_060A8FD0
void RicSetWalk(s32 arg0) {
    if (g_Player.timers[PL_T_8] && !g_Player.unk7A) {
        RicSetRun();
        return;
    }
    g_Player.timers[PL_T_CURSE] = 8;
    if (g_Player.timers[PL_T_CURSE]) {
        g_Player.timers[PL_T_8] = 12;
    }
    g_Player.timers[PL_T_CURSE] = 12;
    g_Player.unk44 = 0;
    RicSetStep(PL_S_WALK);
    RicSetAnimation(ric_anim_walk);
    RicSetSpeedX(FIX(1.5625));
    PLAYER.velocityY = 0;
}

// RicSetRun
extern AnimationFrame ric_anim_run[];
void RicSetRun(void) {
    if (g_Player.unk7A) {
        RicSetWalk(0);
        return;
    }
    g_Player.unk44 = 0;
    RicSetStep(PL_S_RUN);
    RicSetAnimation(ric_anim_run);
    RicSetSpeedX(FIX(2.8125));
    g_Player.timers[PL_T_RUN] = 40;
    PLAYER.velocityY = 0;
    RicCreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(BP_SMOKE_PUFF, 5), 0);
}

void RicSetFall(void) {
    if (g_Player.prev_step != PL_S_RUN && g_Player.prev_step != PL_S_SLIDE) {
        PLAYER.velocityX = 0;
    }
    if (g_Player.prev_step != PL_S_WALK && g_Player.prev_step != PL_S_RUN) {
        RicSetAnimation(D_80155534);
    }
    if (g_Player.prev_step == PL_S_RUN) {
        g_Player.unk44 = 0x10;
    }
    RicSetStep(PL_S_FALL);
    PLAYER.velocityY = FIX(2);
    g_Player.timers[PL_T_5] = 8;
    g_Player.timers[PL_T_6] = 8;
    g_Player.timers[PL_T_CURSE] = 0;
    g_Player.timers[PL_T_8] = 0;
    if (g_Player.prev_step == PL_S_SLIDE) {
        g_Player.timers[PL_T_5] = g_Player.timers[PL_T_6] = 0;
        PLAYER.pose = 2;
        PLAYER.poseTimer = 0x10;
        PLAYER.velocityX /= 2;
    }
}

void RicSetJump(void) {
    if (g_Player.unk72) {
        RicSetFall();
        return;
    }
    if (RicCheckFacing() != 0 || PLAYER.step == Player_Slide) {
        RicSetAnimation(D_8015550C);
        if (PLAYER.step == PL_S_RUN) {
            RicSetSpeedX(FIX(2.8125));
            g_Player.unk44 = 0x10;
        } else {
            RicSetSpeedX(FIX(1.5625));
            g_Player.unk44 = 0;
        }
    } else {
        RicSetAnimation(D_801554F0);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
    }
    RicSetStep(PL_S_JUMP);
    if (g_IsPrologueStage) {
        PLAYER.velocityY = FIX(-4.6875);
    } else {
        PLAYER.velocityY = FIX(-5.4375);
    }
}

// RicSetHighJump
void RicSetHighJump(void) {
    RicSetStep(PL_S_HIGHJUMP);
    PLAYER.velocityX = 0;
    RicSetSpeedX(FIX(1.5625));
    PLAYER.velocityY = FIX(-7.5);
    g_Player.high_jump_timer = 0;
    RicSetAnimation(ric_anim_high_jump);
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_HIGH_JUMP, 0);
    PlaySfx(SFX_UNUSED_712);
    g_Player.timers[PL_T_12] = 4;
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

// func_060A938C
s32 RicCheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    s32 nFound;
    s32 nEmpty;

    // Iterate through entities 32-48 (which hold subweapons)
    // Any that match the proposed ID increments the count.
    // If at any point the count reaches the limit, return -1.
    entity = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0; i < 16; i++, entity++) {
        if (!entity->entityId) {
            nEmpty++;
        }
        if (entity->ext.subweapon.subweaponId &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }
        if (nFound >= limit) {
            return -1;
        }
    }
    // This will indicate that there is an available entity slot
    // to hold the subweapon we're trying to spawn.
    // At the end, if this is zero, there are none available so return
    // -1 to indicate there is no room for the proposed subweapon.
    if (nEmpty) {
        return 0;
    }
    return -1;
}

// RicDoSubweapon
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A93F4, func_060A93F4);

// RicDoAttack
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A95AC, func_060A95AC);

// RicDoCrash
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A97B0, func_060A97B0);

void RicSetDeadPrologue() { RicSetStep(PL_S_DEAD_PROLOGUE); }

// RicSetSlide
void RicSetSlide(void) {
    RicCheckFacing();
    RicSetStep(PL_S_SLIDE);
    RicSetAnimation(D_80155750);
    g_CurrentEntity->velocityY = 0;
    RicSetSpeedX(FIX(6.625));
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    PlaySfx(SFX_TOAD_CROAK);
    g_Player.timers[PL_T_12] = 4;
}

#define SFX_VO_RIC_ATTACK_B 0x711

// PlaySfx needs to be undefined here to match
// func_060A9AFC
void RicSetSlideKick(void) {
    g_Player.unk44 = 0x100; // changed
    RicSetStep(PL_S_SLIDE_KICK);
    RicSetAnimation(D_8015577C);
    g_CurrentEntity->velocityY = FIX(-2);
    RicSetSpeedX(FIX(6.625)); // changed
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    PlaySfx(SFX_VO_RIC_ATTACK_B);
    g_Player.timers[PL_T_12] = 4;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_31, 0);
}

// RicSetBladeDash
void RicSetBladeDash(void) {
    RicSetStep(PL_S_BLADEDASH);
    RicSetAnimation(ric_anim_blade_dash);
    g_CurrentEntity->velocityY = 0;
    RicSetSpeedX(FIX(6.625));
    g_Player.unk46 = 5;
    g_Player.timers[PL_T_12] = 4;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_BLADE_DASH, 0);
    func_8015CC28();
    PlaySfx(SFX_UNUSED_712);
    PlaySfx(SFX_TOAD_CROAK);
}

// ===== pl_utils.c
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9C2C, func_060A9C2C);

// DrawRicAfterImage
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9DEC, func_060A9DEC);

void RicSetStep(s16 step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

void RicSetAnimation(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA088, func_060AA088);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA194, func_060AA194);

void RicDecelerateX(s32 speed) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += speed;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= speed;
        if (g_CurrentEntity->velocityX < 0)
            g_CurrentEntity->velocityX = 0;
    }
}

void RicDecelerateY(s32 speed) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += speed;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= speed;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

s32 RicCheckFacing(void) {
    if (g_Player.unk44 & 2) {
        return 0;
    }

    if (PLAYER.facingLeft == 1) {
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.facingLeft = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Player.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.facingLeft = 1;
            g_Player.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

int func_8015CAAC(s32 speed) {
    if (PLAYER.entityRoomIndex == 1)
        speed = -speed;
    PLAYER.velocityX = speed;
    return speed;
}

void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames) {
    if (!kind) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x15), 0);
        if (g_Player.timers[PL_T_INVINCIBLE_SCENE] <= invincibilityFrames) {
            g_Player.timers[PL_T_INVINCIBLE_SCENE] = invincibilityFrames;
        }
    } else if (g_Player.timers[PL_T_INVINCIBLE] <= invincibilityFrames) {
        g_Player.timers[PL_T_INVINCIBLE] = invincibilityFrames;
    }
}

// DisableAfterImage
void DisableAfterImage(s32 resetAnims, s32 arg1) {
    Primitive* prim;
    Entity* entity;
    s32 i;

    if (resetAnims) {
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag = 1;
        entity = &g_Entities[E_AFTERIMAGE_1];
        for (i = 0; i < 3; i++, entity++) {
            entity->animCurFrame = 0;
            entity->unk0->flags = 0;
        }
        prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex];
        while (prim) {
            prim->x1 = 0;
            prim = *(Primitive**)((u8*)prim + 0x20);
        }
    }
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.index = 10;
    if (arg1) {
        g_Player.timers[PL_T_AFTERIMAGE_DISABLE] = 4;
    }
}

void func_8015CC28(void) {
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag =
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.index =
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.timer = 0;
}

void func_060AA4F4(s32 spawnParticles) {
    Entity* source;
    Entity* factory;

    if (spawnParticles == 1) {
        source = &PLAYER;
        factory = RicCreateEntFactoryFromEntity(
            source, FACTORY(BP_CRASH_DAGGER, 0x47), 0);
        if (factory != NULL) {
            factory->flags |= FLAG_UNK_10000;
        }
        factory = RicCreateEntFactoryFromEntity(
            source, FACTORY(BP_CRASH_DAGGER, 0x40), 0);
        if (factory != NULL) {
            factory->flags |= FLAG_UNK_10000;
        }
    }

    DisableAfterImage(1, 1);
}

// RicCheckInput
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA5C0, func_060AA5C0);

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

// RicCheckWallRight
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AB5F0, func_060AB5F0);

// RicCheckWallLeft
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AB7B4, func_060AB7B4);

// ===== pl_blueprints.c

#define E_NONE 0
// func_060AB980
Entity* RicGetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

// func_060AB9C0
Entity* RicGetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

#define LEN(x) ((s32)(sizeof(x) / sizeof(*(x))))
s32 D_80174F80[11];
// func_060ABA08
void func_8015F9F0(Entity* entity) {
    s32 i;
    s32 enemyId;

    if (entity < &g_Entities[32]) {
        entity->enemyId = 1;
        return;
    }

    for (i = 0;; i++) {
        for (enemyId = 2; enemyId < LEN(D_80174F80); ++enemyId) {
            if (D_80174F80[enemyId] == i) {
                ++D_80174F80[enemyId];
                entity->enemyId = enemyId;
                return;
            }
        }
    }
}

void func_8015FA5C(s32 arg0) {
    D_80174FAC = D_80154674[arg0][0];
    D_80174FB0 = D_80154674[arg0][1];
    D_80174FB4 = D_80154674[arg0][2];
    D_80174FB8 = D_80154674[arg0][3];
}

// RicSetSubweaponParams
void func_060ABA98(Entity* entity) {
    SubweaponDef* subwpn =
        &ric_subweapons_def[entity->ext.subweapon.subweaponId];
    if (g_Player.timers[PL_T_INVINCIBLE_SCENE]) {
        entity->attack = subwpn->attack * 2;
    } else {
        entity->attack = subwpn->attack;
    }
    entity->attackElement = subwpn->attackElement;
    entity->hitboxState = subwpn->hitboxState;
    entity->nFramesInvincibility = subwpn->nFramesInvincibility;
    entity->stunFrames = subwpn->stunFrames;
    entity->hitEffect = subwpn->hitEffect;
    entity->entityRoomIndex = subwpn->entityRoomIndex;
    entity->attack = func_0606F328(entity->attack);
    func_8015F9F0(entity);
}

// func_8015FB84
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ABB78, func_060ABB78);

typedef struct {
    u8 pad[8];
    u16 uv0;
    u16 uv1;
    s16 x0;
    s16 y0;
    u16 frame;
    u16 timer;
    s16 x1;
    s16 y1;
} RicPrimitive;

s32 func_8015FDB0(RicPrimitive* prim, s16 posX, s16 posY) {
    s16 offset;
    s16 xOffset;
    u16* ptr;
    u16* frameWord = &prim->frame;
    u8 frame = ((u8*)frameWord)[1];

    if (frame >= 3) {
        offset = 4;
    } else {
        offset = 6;
    }

    if (frame == 6) {
        return -1;
    }

    xOffset = offset | 1;
    prim->x0 = posX - xOffset;
    prim->y0 = posY - offset;
    prim->x1 = posX + xOffset;
    prim->y1 = posY + offset;

    ptr = DAT_0605aec0[g_RichterSpritePackage3AllocationIndex +
                       D_060BF1A4[frame]];
    prim->uv0 = ptr[0];
    prim->uv1 = ptr[1];

    prim->timer++;
    if (!(prim->timer & 1)) {
        (*frameWord)++;
    }
    return 0;
}

const u16 pad_60ABCD4[] = {0xAAAA, 0xAAAB};

// RicEntityHitByHoly
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ABCD8, func_060ABCD8);

// RicEntityHitByDark
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ABF34, func_060ABF34);

// RicUpdatePlayerEntities
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AC0E0, func_060AC0E0);

// Runs the update function of every non-player entity slot.
void func_060AC2DC(void) {
    Entity* entity;
    s32 i;

    if (PLAYER.unk0 != NULL) {
        g_CurrentEntity = entity = &g_Entities[UNK_ENTITY_4];
        i = UNK_ENTITY_4;
        do {
            if (!(entity->flags & FLAG_UNK_20000)) {
                DestroyEntity(entity);
            }
            if ((entity->flags & FLAG_UNK_02000000) && (entity->step != 0)) {
                entity->flags |= FLAG_UNK_00200000;
                entity->pfnUpdate(entity);
                entity->flags &= ~FLAG_UNK_00200000;
            }
            i++;
            g_CurrentEntity++;
            entity++;
        } while (i <= 0x3F);
        // prevent inline
        ((s32(*)(s32, s32))DisableAfterImage)(1, 3);
    }
}

Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2) {
    Entity* entity;
    Entity* current;
    s16 i;
    s16 end = 16;

    current = &g_Entities[8];
    for (i = 8; i < end; i++, current++) {
        if (current->entityId == E_NONE) {
            entity = current;
            goto found;
        }
    }
    entity = NULL;
found:
    if (!entity) {
        return NULL;
    }
    DestroyEntity(entity);
    entity->entityId = 1;
    entity->ext.factory.parent = source;
    entity->posX.val = source->posX.val;
    entity->posY.val = source->posY.val;
    entity->facingLeft = source->facingLeft;
    entity->zPriority = source->zPriority;
    entity->params = factoryParams & 0xFFF;
    entity->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    if (source->flags & FLAG_POS_CAMERA_LOCKED) {
        entity->flags |= FLAG_POS_CAMERA_LOCKED;
    }
    if (source->flags & FLAG_UNK_10000) {
        entity->flags |= FLAG_UNK_10000;
    }
    return entity;
}

// RicEntityFactory
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AC46C, func_060AC46C);

void RicEntitySlideKick(Entity* entity) {
    void RicSetSubweaponParams(Entity * entity);

    if (PLAYER.step != PL_S_SLIDE) {
        DestroyEntity(entity);
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->facingLeft = PLAYER.facingLeft;
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                            FLAG_KEEP_ALIVE_OFFCAMERA;
            entity->hitboxOffX = 25;
            entity->hitboxOffY = 12;
            entity->hitboxWidth = 11;
            entity->hitboxHeight = 9;
            entity->ext.subweapon.subweaponId = PL_W_KICK;
            RicSetSubweaponParams(entity);
            entity->ext.subweapon.timer = entity->hitboxState;
            entity->step++;
        }
        entity->hitboxState = entity->ext.subweapon.timer;
        if (PLAYER.pose < 2) {
            entity->hitboxState = 0;
        }
        if (PLAYER.pose > 7) {
            DestroyEntity(entity);
        }
    }
}

// func_80160D2C
void func_060AC908(Entity* entity) {
    if (PLAYER.step != PL_S_SLIDE_KICK) {
        DestroyEntity(entity);
        return;
    }
    entity->posX.i.hi = PLAYER.posX.i.hi;
    entity->posY.i.hi = PLAYER.posY.i.hi;
    entity->facingLeft = PLAYER.facingLeft;
    if (entity->step == 0) {
        entity->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->hitboxOffX = 25;
        entity->hitboxWidth = 11;
        entity->hitboxHeight = 9;
        entity->ext.subweapon.subweaponId = 23;
        func_060ABA98(entity);
        entity->step++;
    }

    if (PLAYER.animCurFrame == 140) {
        entity->hitboxOffY = 0;
    }

    if (PLAYER.animCurFrame == 141) {
        entity->hitboxOffY = 12;
    }

    if (entity->hitFlags) {
        g_Player.unk44 |= 0x80;
    } else {
        g_Player.unk44 &= ~0x80;
    }
    entity->hitFlags = 0;
}

void RicEntityBladeDash(Entity* self) {
    void RicSetSubweaponParams(Entity * entity);

    if (PLAYER.step != PL_S_BLADEDASH) {
        DestroyEntity(self);
    } else {
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->facingLeft = PLAYER.facingLeft;
        if (self->step == 0) {
            self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                          FLAG_KEEP_ALIVE_OFFCAMERA;
            self->hitboxOffX = self->hitboxOffY = 0;
            self->hitboxWidth = 25;
            self->hitboxHeight = 20;
            self->ext.subweapon.subweaponId = 17;
            RicSetSubweaponParams(self);
            self->step++;
        }
        if (PLAYER.pose > 18) {
            DestroyEntity(self);
        }
    }
}

void func_80160F0C(Entity* self) {
    void RicSetSubweaponParams(Entity * entity);

    if (PLAYER.step != PL_S_HIGHJUMP) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (self->step == 0) {
        self->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxOffX = 15;
        self->hitboxOffY = -26;
        self->hitboxWidth = 15;
        self->hitboxHeight = 12;
        self->ext.subweapon.subweaponId = PL_W_HIGHJUMP;
        RicSetSubweaponParams(self);
        self->step++;
    }
}

const u16 pad_60ACB6C[] = {0x8888, 0x8889};

// RicEntitySmokePuff
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ACB70, func_060ACB70);

// RicEntityHitByCutBlood
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ACFA0, func_060ACFA0);

// func_80161C2C
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AD780, func_060AD780);

// func_80161EF8
void func_060ADA34(Entity* self) {
    switch (self->step) {
    case 0:
        self->unk0 = CreateSpriteObject(
            g_EntitySpriteBank01.allocationIndex, g_EntitySpriteBank01.flags,
            g_EntitySpriteBank01.images, 5);
        if (self->unk0 != NULL) {
            self->ext.spriteEntity.frames = DAT_06045E14;
            self->unk0->zPriority = g_Entities->zPriority + 4;
            self->animSet = 2;
            self->anim = anim_80154E38;
            self->flags = 0x170000;
            self->velocityY = (MTH_GetRand() & 0x3FFF) - FIX(1);
            self->step++;
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        if (self->pose == 6) {
            if (self->poseTimer == 1 && (MTH_GetRand() & 1)) {
                RicCreateEntFactoryFromEntity(self, 4, 0);
            }
        }
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// RicEntityApplyMariaPowerAnim
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ADB2C, func_060ADB2C);

// func_801623E0
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ADE2C, func_060ADE2C);

// func_80162604
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ADFD4, func_060ADFD4);

// RicEntityMariaPowers
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AE1B4, func_060AE1B4);

s32 DestroyEntity();

void func_060AE538(void) { DestroyEntity(); }

// RicEntityMaria
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AE550, func_060AE550);

#define E_WEAPON 0x10
#define STAGE_ENTITY_START 64

// func_060AE714
bool func_80162E9C(Entity* entity) {
    Entity* e;
    s32 i;
    s16 objId;
    s16 params;

    objId = entity->entityId;
    params = entity->params;
    for (e = &g_Entities[E_WEAPON], i = E_WEAPON; i < STAGE_ENTITY_START; e++,
        i++) {
        if (objId == e->entityId && params == e->params && e != entity) {
            return true;
        }
    }
    return false;
}

// RicEntityPlayerBlinkWhite
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AE768, func_060AE768);

// func_801641A0
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AEC04, func_060AEC04);

// RicEntityShrinkingPowerUpRing
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AEDCC, func_060AEDCC);

// RicEntityHitByIce
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AF094, func_060AF094);

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AF704, func_060AF704);

// RicEntityHitByLightning
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AF7F4, func_060AF7F4);

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AFE70, func_060AFE70);
INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60B00C4, func_060B00C4);

// ===== ???

void RicEntityDummy(void) { DestroyEntity(); }

void func_060B0604() {}

const u16 pad_60B060E = 0; // file split?

s32 func_060B0610() { return 0; }

const u16 pad_60B061A = 0; // file split!

// ===== pl_whip.c

// RicEntityWhip
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B061C, func_060B061C);

// RicEntityArmBrandishWhip
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B12CC, func_060B12CC);

// func_80167964
void func_80167964(Entity* entity) {
    if (g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_10000;
        entity->step++;
    }
    if (!(entity->params & 0xFF00)) {
        g_Entities[D_80155D30[entity->poseTimer]].palette = 5;
    }
    g_Entities[D_80155D30[entity->poseTimer]].ext.whip.unkA0 = 4;
    entity->poseTimer++;
    if (entity->poseTimer == 15) {
        DestroyEntity(entity);
    }
}

// ===== pl_subweapon_dummy.c

void RicEntityNotImplemented1() {}

void RicEntityNotImplemented2() {}

const u16 pad_60B151E = 0; // file split!

// ===== 2F8E8.c

// RicEntitySubwpnReboundStone
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B1520, func_060B1520);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B240C, func_060B240C);

// RicEntitySubwpnAgunea
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B24C8, func_060B24C8);

// RicEntityAguneaHitEnemy
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B28E8, func_060B28E8);

// RicEntityVibhutiCrashCloud
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B2EE4, func_060B2EE4);

// RicEntityCrashVibhuti
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3074, func_060B3074);

// func_060B33DC
void RicEntityCrashReboundStoneParticles(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_CRASH_REBOUND_STONE;
        RicSetSubweaponParams(entity);
        entity->hitboxWidth = 5; // 4 on ps1
        entity->hitboxHeight = 4;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 3) {
            DestroyEntity(entity);
        }
        break;
    }
}

// ===== 319C4.c

// func_8016D9C4, includes part of next function
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3454, func_060B3454);

// RicEntityCrashReboundStoneExplosion, split start at mid function
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B38FC, func_060B38FC);
// RicEntityCrashReboundStone
void RicEntityCrashReboundStone(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->step++;
        entity->ext.subweapon.timer = 0x14;
    case 1:
        if (--entity->ext.subweapon.timer) {
            break;
        }
    case 3:
    case 5:
        RicCreateEntFactoryFromEntity(entity, BP_57, 0);
        entity->step++;
    case 2:
    case 4:
    case 6:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 10) {
            entity->ext.subweapon.timer = 0;
            entity->posX.val = FIX(160.0);
            entity->posY.val = 0;
            RicCreateEntFactoryFromEntity(entity, FACTORY(BP_EMBERS, 1), 0);
            entity->step++;
        }
        break;
    case 7:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 15) {
            DestroyEntity(entity);
            g_Player.unk4E = 1;
            RicCreateEntFactoryFromEntity(
                entity, BP_CRASH_REBOUND_STONE_EXPLOSION, 0);
        }
        break;
    }
}

// RicEntityCrashBibleBeam
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3B3C, func_060B3B3C);

// RicEntityCrashBible
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B40F8, func_060B40F8);

// func_8016F198
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B4644, func_060B4644);

// RicEntityCrashStopwatchDoneSparkle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B47EC, func_060B47EC);

// func_060B5434
void RicEntityStopwatchCrashLightning(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_30;
        RicSetSubweaponParams(entity);
        entity->hitboxWidth = 10;
        entity->hitboxHeight = 8;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 4) {
            DestroyEntity(entity);
        }
        break;
    }
}

// RicEntityCrashStopwatch
void RicEntityCrashStopwatch(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_20000;
        self->ext.subweapon.crashIndex = 0;
        self->step_s++;
        if (self->step_s > 3) {
            self->step++;
        }
        break;
    case 1:
    case 3:
    case 5:
    case 7:
        self->ext.subweapon.crashIndex++;
        RicCreateEntFactoryFromEntity(
            self, FACTORY(BP_SUBWPN_STOPWATCH, self->ext.subweapon.crashIndex),
            0);
        self->ext.subweapon.timer = 0;
        self->step++;
        break;
    case 2:
    case 4:
    case 6:
        self->ext.subweapon.timer++;
        if (self->ext.subweapon.timer > 15) {
            self->step++;
        }
        break;
    case 8:
        DestroyEntity(self);
        break;
    }
}
const u16 pad_60B5560[] = {0xAAAA, 0xAAAB};

// GetAguneaLightningAngle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B5564, func_060B5564);

// RicEntityAguneaLightning
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B5670, func_060B5670);

// RicEntityAguneaCircle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B5AA0, func_060B5AA0);

// RicEntitySubwpnStopwatchCircle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B5F64, func_060B5F64);

// RicEntitySubwpnStopwatch
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B60D8, func_060B60D8);

// RicEntitySubwpnBibleTrail
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B7020, func_060B7020);

// RicEntitySubwpnBible
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B720C, func_060B720C);

// ===== pl_subweapons_dagger.c
// RicEntitySubwpnKnife
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B7650, func_060B7650);

// ===== pl_subweapons_axe.c
// RicEntitySubwpnThrownAxe
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B7A4C, func_060B7A4C);

// RicEntityCrashAxe
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B8044, func_060B8044);

// ===== pl_subweapons_cross.c
INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60B8664, func_060B8664);

// RicEntityRevivalColumn
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B8B1C, func_060B8B1C);

// RicEntitySubwpnCross
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B8DF8, func_060B8DF8);

// func_80169C10
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B91B8, func_060B91B8);

// RicEntitySubwpnCrossTrail
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9300, func_060B9300);

// RicEntitySubwpnCrashCrossParticles
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B940C, func_060B940C);

// ===== pl_subweapon_holywater.c
void RicEntityNotImplemented3() {}

const u16 pad_60B9666 = 0x0009; // nop

// RicEntitySubwpnHolyWaterBreakGlass
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9668, func_060B9668);

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9978, func_060B9978);

// RicEntityCrashHydroStorm
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9A50, func_060B9A50);

// RicCheckHolyWaterCollision
s32 RicCheckHolyWaterCollision(s32 baseY, s32 baseX) {
    Collider res1;
    Collider res2;
    s32 newY;
    s32 x;
    s32 y;
    s32 collEffs;
    const u32 colFullSet = 0xF801;
    const u32 colSetNo800 = 0xF001;
    const u32 colSet1 = 0x8801;
    const u32 colSet2 = 0x8001;

    x = g_CurrentEntity->posX.val + baseX;
    y = g_CurrentEntity->posY.val + baseY;
    CheckCollision(x, y, &res1, 0);
    collEffs = res1.effects & colFullSet;
    y = y - FIX(1) + res1.unk18;
    CheckCollision(x, y, &res2, 0);
    newY = g_CurrentEntity->posY.val + res1.unk18 + baseY;

    if ((collEffs & colSet1) == EFFECT_SOLID ||
        (collEffs & colSet1) == (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        collEffs = res2.effects & colSetNo800;
        if (!(collEffs & EFFECT_SOLID)) {
            g_CurrentEntity->posY.val = newY;
            return 1;
        }
        if ((res2.effects & colSet2) == colSet2) {
            g_CurrentEntity->posY.val = newY - FIX(1) + res2.unk18;
            return collEffs;
        }
        return 0;
    } else if ((collEffs & colSet2) == colSet2) {
        g_CurrentEntity->posY.val = newY;
        return collEffs & colSetNo800;
    }
    return 0;
}

#define EFFECT_UNK_0002 1 << 1

// SAT func_060B9E40
// Equivalent to DRA func_80125B6C
s32 func_8016840C(s32 y, s32 x) {
    Collider collider;
    s32 xShift;
    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }
    CheckCollision(g_CurrentEntity->posX.val + x, g_CurrentEntity->posY.val + y,
                   &collider, 0);
    if (g_CurrentEntity->velocityX > 0) {
        xShift = collider.unk14;
    } else {
        xShift = collider.unk1C;
    }
    if (collider.effects & EFFECT_UNK_0002) {
        g_CurrentEntity->posX.val += xShift;
        return 2;
    }
    return 0;
}

// RicEntitySubwpnHolyWater
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9EA0, func_060B9EA0);

// RicEntitySubwpnHolyWaterFlame
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BA3DC, func_060BA3DC);

// ===== pl_crash_cross.c
// RicEntityCrashCrossBeam
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BA788, func_060BA788);

// ===== all these functions below seems to be exclusive to Saturn

void func_060BACA4(void) {
    memset(&g_RichterCastleMapState, 0, 4);
    memcpy(CASTLE_MAP_BITMAP, g_RichterCastleMapBitmap, CASTLE_MAP_BITMAP_SIZE);

    func_060BB330();
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BACEC, func_060BACEC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BAED0, func_060BAED0);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB09C, func_060BB09C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB184, func_060BB184);
void func_060BB330(void) {
    u8* dst;
    u8* revealDst;
    s32 mapOffset;
    s32 mapIndex;
    s32 row;
    s32 col;
    s32 revealRow;
    u32 revealCol;

    dst = CASTLE_MAP_BITMAP;
    mapOffset = 0;

    if (g_CurrentRoom.stageID & 0x20) {
        mapOffset = 0x0400;
        revealDst = dst + 0x6970;

        for (revealRow = 0; revealRow <= 3; revealRow++) {
            for (revealCol = 0; revealCol <= 10; revealCol++) {
                revealDst[revealCol] = g_RichterMapRevealPattern[revealCol];
            }
            revealDst += CASTLE_MAP_BITMAP_PITCH;
        }
    }

    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BACEC(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }

    func_060BB184();

    dst = CASTLE_MAP_BITMAP;
    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BB09C(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }

    dst = CASTLE_MAP_BITMAP;
    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BAED0(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB454, func_060BB454);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB58C, func_060BB58C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB718, func_060BB718);
typedef struct {
    u8 pad[0x1800];
    u16 colors0[4];
    u16 colors1[4];
} RicGouraudTable;

extern RicGouraudTable* SpGourTbl;
s32* func_060784A8(void);

void func_060BB90C(void) {
    s32* ptr;
    u16* colors0;
    u16* colors1;

    ptr = func_060784A8();
    func_060BBDE0(ptr);
    g_RichterSavedMapVramBase = DAT_060476a0;
    g_RichterSavedMapPlaneConfig = DAT_060476a4;
    if (g_PlayableCharacter == 0) {
        DAT_060476a0 = 0x252000;
        DAT_060476a4 = 1;
    }
    colors0 = SpGourTbl->colors0;
    colors0[0] = colors0[1] = 0xB18C;
    colors0[2] = colors0[3] = 0xD294;
    colors1 = SpGourTbl->colors1;
    colors1[0] = colors1[1] = colors1[2] = colors1[3] = 0x9084;
    DAT_0605c6e4 = 1;
}

void func_060BB9BC(s32* src) {
    s32* dst;
    Unk0605DB60* entry;
    s32 i;

    dst = (s32*)((DAT_0605aec0[0][0] * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, src, 0x8400);
    while (DMA_CpuResult() == 2) {
    }

    entry = d_0605DB60;
    for (i = 0; i <= 0x1F; i++) {
        entry->unkC = entry->unk8;
        entry->unkE = entry->unkA;
        entry++;
    }

    dst = (s32*)((SPR_2LookupTblNoToVram(0x10) * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, src + 0x4200, 0x400);
    while (DMA_CpuResult() == 2) {
    }

    dst = (s32*)0x25F00800;
    DMA_CpuMemCopy2(dst, src + 0x4400, 0x200);
    while (DMA_CpuResult() == 2) {
    }
}

s32 DAT_06086390;
s32 DAT_060476a0;
s32 DAT_060476a4;

void func_060BBA88(void) {
    s32* iVar2;
    iVar2 = func_060784A8();
    func_060BB9BC(iVar2);
    DAT_060476a0 = g_RichterSavedMapVramBase;
    DAT_060476a4 = g_RichterSavedMapPlaneConfig;
}

void func_060BBAC8(void) {
    s32* iVar2;
    DAT_06086390 = 0;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BBAF4(void) {
    s32* work;
    u8* area;
    u8* dst;
    s32 i;
    u32 clear_size;
    u8* dma_base;
    s32 dma_offset;
    u16 dma_value;
    s32* dma_dest;

    DAT_06086390 = 1;
    work = func_060784A8();
    work[0x4500] = -1;

    clear_size = 0xA000U;
    area = (u8*)(work + 0x4501);
    memset(area, 0, clear_size);
    dst = area;

    i = 0;
    do {
        func_06078700(dst, DAT_06085DE8[i], 4);
        dst += 0x180;
        i++;
    } while (i <= 10);

    i = 0;
    do {
        func_06078700(dst, DAT_06085E14[i], 4);
        dst += 0x180;
        i++;
    } while (i <= 7);

    i = 0;
    do {
        func_06078700(dst, DAT_06085DCC[i], 4);
        dst += 0x180;
        i++;
    } while (i <= 1);

    dma_base = (u8*)DAT_0605aec0;
    dma_offset = 8;
    dma_value = *(u16*)(dma_base + dma_offset);
    dma_dest = (s32*)(0x25C00000U + dma_value * 8);
    DMA_CpuMemCopy2(dma_dest, work + 0x4501, 0xFC0U);

    do {
    } while (DMA_CpuResult() == 2);
}
void func_060BBC00(void) {
    s32* base;
    s32* dst;
    u8* text;
    s32 slot;
    s32 i;

    DAT_06086390 = 2;
    base = func_060784A8();
    base[0x4500] = -1;
    memset(base + 0x4501, 0, 0xA000);

    text = (u8*)(base + 0x4501);
    for (i = 0; i <= 7; i++) {
        func_06078700(text, func_06078748(i), 12);
        text += 0x480;
    }
    func_06078700(text, DAT_06085DCC[2], 6);

    // DAT_0605aec0[2][0]; the compiler reads it through an index register.
    slot = 2;
    dst = (s32*)((DAT_0605aec0[slot][0] * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, base + 0x4501, 0x1320);
    while (DMA_CpuResult() == 2) {
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBCCC, func_060BBCCC);

void func_060BBD88(void) {
    int* iVar2;
    DAT_06086390 = 4;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BBDB4(void) {
    int* iVar2;
    DAT_06086390 = 5;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBDE0, func_060BBDE0);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBF08, func_060BBF08);

// CheckIfAllButtonsAreAssigned
bool func_060BC048(void) {
    s32 buf[9];
    s32 i;
    s32 bitMask_Assigned;
    s32* buttonConfig;

    for (i = 0; i < 9; i++) {
        buf[i] = 0;
    }

    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 8; i++) {
        buf[*buttonConfig++] = 1;
    }

    for (i = 0; i < 9; i++) {
        if (buf[i] == 0) {
            g_Settings.buttonConfig[8] = i;
            break;
        }
    }

    for (i = 0; i < 9; i++) {
        g_Settings.buttonMask[i] = g_ButtonMask[g_Settings.buttonConfig[i]];
    }

    bitMask_Assigned = 0;
    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 9; i++) {
        bitMask_Assigned |= 1 << *buttonConfig++;
    }
    if (bitMask_Assigned == 0xFF) {
        return true;
    } else {
        return false;
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC108, func_060BC108);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC228, func_060BC228);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC4E4, func_060BC4E4);

void func_060BC7A8(u32 arg0) {
    s32 first;
    s32 current;
    s32 offset;
    s32 i;
    u8* ptr;

    if (arg0 == 6) {
        offset = 0x28;
    } else if (arg0 & 1) {
        offset = 0x28;
    } else {
        offset = 0;
    }

    first = g_RichterMapRevealRowIndices[arg0];
    for (current = first; current < first + 4; current++) {
        s32 tile = current << 6;

        ptr = (u8*)tile;
        ptr += 0x25E58000 + offset;
        for (i = 0; i < 0x20; i++) {
            *ptr++ = 0;
        }

        if (offset == 0x28) {
            ptr = (u8*)(0x25E58800 + tile);
            for (i = 0; i < 0x10; i++) {
                *ptr++ = 0;
            }
        }
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC834, func_060BC834);

extern u32 D_06085534;
s32 func_060732E4(u16 arg0);

void func_060BCA10(void) {
    if (DAT_0605cd70.unk8 != 0) {
        if (DAT_0605cd70.unk8 == 1) {
            goto after;
        }
        return;
    } else {
        func_060732E4(DAT_0605cd70.unk0);
        DAT_0605cd70.unk8++;
    }
after:
    if ((DAT_06057f68 == 0) && (g_pads[0].previous & 0x100)) {
        D_06085534 = 6;
        DAT_06057f68 = 4;
    }
    func_060BC834();
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BCA84, func_060BCA84);
void func_060BCDB8(void) {
    switch (DAT_0605cd70.unk8) {
    case 0:
        func_060732E4(DAT_0605cd70.unk0);
        DAT_0605cd70.unk8++;
        /* fall through */
    case 1:
        if (DAT_06057f68 == 0 && (g_pads->previous & PAD_CROSS)) {
            D_06085534 = 6;
            DAT_06057f68 = 4;
        }
        if (DAT_06057f68 == 3) {
            DAT_06057f68 = 0;
        }
        if (DAT_06057f68 == 6) {
            DAT_0605cd70.unk0 = 6;
            DAT_0605cd70.unk8 = 0;
            DAT_06065470 &= ~0x003F;
            SclProcess = 1;
        }
        func_060BCA84();
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BCE64, func_060BCE64);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD11C, func_060BD11C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD2AC, func_060BD2AC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD3D8, func_060BD3D8);

// SortTimeAttackEntries
void func_060BD4EC(void) {
    s32 i;
    s32 isLooping;
    s32 swapTime;
    s32 swapName;

    for (i = 0; i < 28; i++) {
        D_060CEE6C[i] = func_0606F21C(i, 0);
        if (D_060CEE6C[i] == 0) {
            D_060CEE6C[i] = 1000000;
        }
        D_060CEEDC[i] = i;
    }

    do {
        isLooping = false;
        for (i = 0; i < 27; i++) {
            if (D_060CEE6C[i] > D_060CEE6C[i + 1]) {
                swapTime = D_060CEE6C[i];
                D_060CEE6C[i] = D_060CEE6C[i + 1];
                D_060CEE6C[i + 1] = swapTime;
                swapName = D_060CEEDC[i];
                D_060CEEDC[i] = D_060CEEDC[i + 1];
                D_060CEEDC[i + 1] = swapName;
                isLooping++;
            }
        }
    } while (isLooping);
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD580, func_060BD580);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD768, func_060BD768);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BDADC, func_060BDADC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BDFD4, func_060BDFD4);

void func_060BE110(void) {
    if (d_06086234 == 0) {
        memset((void*)0x25E58288, 0, 0xC);
        memset((void*)0x25E582C8, 0, 0xC);
    }

    if (d_06086250 == 0) {
        memset((void*)0x25E58348, 0, 0xC);
        memset((void*)0x25E58388, 0, 0xC);
    }

    if (g_GameClearFlag == 0) {
        memset((void*)0x25E584C8, 0, 0x10);
        memset((void*)0x25E58508, 0, 0x10);
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BE198, func_060BE198);
