// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

// export table
INCLUDE_ASM("asm/saturn/richter/data", d60A5000, d_060A5000);

// ===== pl_main.c

// GetTeleportToOtherCastle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5060, func_060A5060);

// func_80156DE4
extern s32 D_80154568[];
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

// CheckBladeDashInput
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5864, func_060A5864);

// CheckHighJumpInput
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5988, func_060A5988);

INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60A6272, func_060A6272);

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

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A67B0, func_060A67B0);
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
        if (g_Player.timers[PL_T_5] && (g_Player.padTapped & 0x100)) {
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
    s16 var_s3;
    s16 var_s2;
    s16 var_s1;

    entity = (Entity*)PLAYER.unkB4;
    if (entity->facingLeft) {
        var_s3 = -entity->hitboxOffX;
    } else {
        var_s3 = entity->hitboxOffX;
    }
    if (PLAYER.facingLeft) {
        var_s2 = -PLAYER.hitboxOffX;
    } else {
        var_s2 = PLAYER.hitboxOffX;
    }

    var_s1 = PLAYER.posX.i.hi + var_s2 - entity->posX.i.hi - var_s3;
    if (ABS(var_s1) < 16 && entity->velocityX != 0) {
        if (entity->velocityX < 0) {
            PLAYER.entityRoomIndex = 0;
            return;
        } else {
            PLAYER.entityRoomIndex = 1;
            return;
        }
    }
    if (var_s1 < 0) {
        PLAYER.entityRoomIndex = 0;
    } else {
        PLAYER.entityRoomIndex = 1;
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A7310, func_060A7310);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A7B78, func_060A7B78);
INCLUDE_ASM("asm/saturn/richter/data", d60A7CF0, d_060A7CF0);
extern u16 D_80155528[];
extern u32 g_SubwpnCrashTimer;
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
        func_06011278(0x62F);
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
extern u32 g_SubwpnCrashTimer;
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
extern s32 throw_dagger_timer;
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
extern s32 g_PlayerX;
static void func_8015BB80(void) {
    if (DAT_0605d750.stageID == STAGE_TOP) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8079 > 0) {
            PLAYER.posX.i.hi--;
        }
        if (ABS((g_Tilemap.left << 8) + g_PlayerX) - 8079 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
    if (DAT_0605d750.stageID == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A8D64, func_060A8D64);

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
extern AnimationFrame ric_anim_crouch_from_stand2[];
extern AnimationFrame ric_anim_crouch_from_stand[];
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

void RicSetRun(void);

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
extern AnimationFrame ric_anim_high_jump[];
void RicSetHighJump(void) {
    RicSetStep(PL_S_HIGHJUMP);
    PLAYER.velocityX = 0;
    RicSetSpeedX(FIX(1.5625));
    PLAYER.velocityY = FIX(-7.5);
    g_Player.high_jump_timer = 0;
    RicSetAnimation(ric_anim_high_jump);
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_HIGH_JUMP, 0);
    func_06011278(0x712);
    g_Player.timers[PL_T_12] = 4;
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
    }
}

// func_060A938C
static s32 RicCheckSubwpnChainLimit(s16 subwpnId, s16 limit) {
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
extern AnimationFrame D_80155750[];
void RicSetSlide(void) {
    RicCheckFacing();
    RicSetStep(PL_S_SLIDE);
    RicSetAnimation(D_80155750);
    g_CurrentEntity->velocityY = 0;
    RicSetSpeedX(FIX(6.625));
    func_8015CC28();
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    func_06011278(0x71A);
    g_Player.timers[PL_T_12] = 4;
}

extern AnimationFrame D_8015577C[1];
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
extern AnimationFrame ric_anim_blade_dash[];
void RicSetBladeDash(void) {
    RicSetStep(PL_S_BLADEDASH);
    RicSetAnimation(ric_anim_blade_dash);
    g_CurrentEntity->velocityY = 0;
    RicSetSpeedX(FIX(6.625));
    g_Player.unk46 = 5;
    g_Player.timers[PL_T_12] = 4;
    RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_BLADE_DASH, 0);
    func_8015CC28();
    func_06011278(0x712);
    func_06011278(0x71A);
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
            entity->unk0->unk0 = 0;
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

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA4F4, func_060AA4F4);

// RicCheckInput
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA5C0, func_060AA5C0);

// func_8015E484
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AAB80, func_060AAB80);

extern Point32 g_RicSensorsCeiling[NUM_HORIZONTAL_SENSORS];
extern Point32 g_RicSensorsFloor[NUM_HORIZONTAL_SENSORS];
extern Point32 g_RicSensorsWall[NUM_VERTICAL_SENSORS * 2];

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
static Entity* RicGetFreeEntity(s16 start, s16 end) {
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
static Entity* RicGetFreeEntityReverse(s16 start, s16 end) {
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

extern u8 D_80154674[][4];
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;

void func_8015FA5C(s32 arg0) {
    D_80174FAC = D_80154674[arg0][0];
    D_80174FB0 = D_80154674[arg0][1];
    D_80174FB4 = D_80154674[arg0][2];
    D_80174FB8 = D_80154674[arg0][3];
}

// RicSetSubweaponParams
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ABA98, func_060ABA98);

// func_8015FB84
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ABB78, func_060ABB78);

// func_8015FDB0
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

typedef struct {
    u16 uv0;
    u16 uv1;
} RicUvPair;

extern u16 D_060C2F40;
extern u8 D_060BF1A4[];
extern RicUvPair D_0605AEC0[];

s32 func_8015FDB0(RicPrimitive* prim, s16 posX, s16 posY) {
    s16 offset;
    s16 xOffset;
    RicUvPair* uvAnim;
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

    uvAnim = &D_0605AEC0[D_060C2F40 + D_060BF1A4[frame]];
    prim->uv0 = uvAnim->uv0;
    prim->uv1 = uvAnim->uv1;

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

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AC2DC, func_060AC2DC);

Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2);
// RicCreateEntFactoryFromEntity
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

// RicEntitySlideKick
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
            entity->ext.subweapon.subweaponId = 18;
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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AC908, func_060AC908);

// RicEntityBladeDash
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

// func_80160F0C
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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ADA34, func_060ADA34);

// RicEntityApplyMariaPowerAnim
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ADB2C, func_060ADB2C);

// func_801623E0
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ADE2C, func_060ADE2C);

// func_80162604
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ADFD4, func_060ADFD4);

// RicEntityMariaPowers
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AE1B4, func_060AE1B4);

s32 func_0600FFB8();

void func_060AE538(void) { func_0600FFB8(); }

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
INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60B052A, func_060B052A);

// ===== ???

void RicEntityDummy(void) { func_0600FFB8(); }

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
extern s16 D_80155D30[];
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
INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/data", d60B23B6, d_060B23B6);
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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3A0C, func_060B3A0C);
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
INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60B89CE, func_060B89CE);

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

// bad split, part of previous function
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9A2C, func_060B9A2C);

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

void func_060BB330();

s32 DAT_060c4118;
s32 DAT_060c411c;

void func_060BACA4(void) {
    memset(&DAT_060c4118, 0, 4);
    memcpy(0x002B2000, &DAT_060c411c, 0x9600);

    func_060BB330();
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BACEC, func_060BACEC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BAED0, func_060BAED0);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB09C, func_060BB09C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB184, func_060BB184);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB330, func_060BB330);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB454, func_060BB454);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB58C, func_060BB58C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB718, func_060BB718);
typedef struct {
    u8 pad[0x1800];
    u16 colors0[4];
    u16 colors1[4];
} RicGouraudTable;

extern s32 d_060476A0;
extern s32 d_060476A4;
extern s32 d_060cd748;
extern s32 d_060cd74c;
extern RicGouraudTable* DAT_0606471C;
extern s32 d_0605c6e4;
s32* func_060784A8(void);

void func_060BB90C(void) {
    s32* ptr;
    u16* colors0;
    u16* colors1;

    ptr = func_060784A8();
    func_060BBDE0(ptr);
    d_060cd748 = d_060476A0;
    d_060cd74c = d_060476A4;
    if (g_PlayableCharacter == 0) {
        d_060476A0 = 0x252000;
        d_060476A4 = 1;
    }
    colors0 = DAT_0606471C->colors0;
    colors0[0] = colors0[1] = 0xB18C;
    colors0[2] = colors0[3] = 0xD294;
    colors1 = DAT_0606471C->colors1;
    colors1[0] = colors1[1] = colors1[2] = colors1[3] = 0x9084;
    d_0605c6e4 = 1;
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB9BC, func_060BB9BC);

s32 d_06086390;
s32 d_060476A0;
s32 d_060476A4;
s32 d_060cd748;
s32 d_060cd74c;
void func_060BB9BC(s32*);

void func_060BBA88(void) {
    s32* iVar2;
    iVar2 = func_060784A8();
    func_060BB9BC(iVar2);
    d_060476A0 = d_060cd748;
    d_060476A4 = d_060cd74c;
}

s32 d_06086390;
void func_060BBAC8(void) {
    s32* iVar2;
    d_06086390 = 0;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBAF4, func_060BBAF4);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBC00, func_060BBC00);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBCCC, func_060BBCCC);

void func_060BBD88(void) {
    int* iVar2;
    d_06086390 = 4;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BBDB4(void) {
    int* iVar2;
    d_06086390 = 5;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBDE0, func_060BBDE0);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBF08, func_060BBF08);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC048, func_060BC048);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC108, func_060BC108);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC228, func_060BC228);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC4E4, func_060BC4E4);
extern s16 PTR_DAT_060cd7f0[];

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

    first = PTR_DAT_060cd7f0[arg0];
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
typedef struct {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
} Unk0605cd70;

extern Unk0605cd70 DAT_0605cd70;
extern u8 DAT_06057f68;
extern u32 d_06085534;
s32 func_060732E4(u16 arg0);
void func_060BC834(void);

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
    if ((DAT_06057f68 == 0) && ((g_pads[0].previous & 0x100) != 0)) {
        d_06085534 = 6;
        DAT_06057f68 = 4;
    }
    func_060BC834();
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BCA84, func_060BCA84);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BCDB8, func_060BCDB8);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BCE64, func_060BCE64);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD11C, func_060BD11C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD2AC, func_060BD2AC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD3D8, func_060BD3D8);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD4EC, func_060BD4EC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD580, func_060BD580);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD768, func_060BD768);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BDADC, func_060BDADC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BDFD4, func_060BDFD4);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BE110, func_060BE110);
INCLUDE_ASM("asm/saturn/richter/data", d60BED58, d_060BED58);
