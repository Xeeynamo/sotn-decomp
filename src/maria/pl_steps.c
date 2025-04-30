// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"
#include "sfx.h"

static void func_80158B04(u16 arg0) {
    s16 xMod = 3;
    if (PLAYER.facingLeft) {
        xMod = -xMod;
    }

    PLAYER.posY.i.hi -= 16;
    PLAYER.posX.i.hi += xMod;
    MarCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_EMBERS, 1), 0);
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

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepStand);

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
        if (PLAYER.step_s != 0) {
            if (PLAYER.step_s) {
            }
        } else {
            MarSetSpeedX(FIX(2.25));
        }
    }
}

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepJump);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepFall);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepCrouch);

static void func_80159BC8(void) {
    PLAYER.pose = PLAYER.poseTimer = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.drawFlags &= ~FLAG_DRAW_ROTZ;
}

static void func_80159C04(void) {
    Entity* entity;
    s16 var_s3;
    s16 var_s2;
    s16 var_s1;

    entity = PLAYER.unkB8;
#if defined(VERSION_PSP)
    if (!entity) {
        return;
    }
#endif
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
    if (abs(var_s1) < 16 && entity->velocityX != 0) {
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

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepHit);

void MarStepBossGrab(void) {
    DamageParam damage;
    s32 damageResult;

    switch (g_CurrentEntity->step_s) {
    case 0:
        func_80159BC8();
        if (g_Player.unk62 == 0) {
            PLAYER.anim = mar_anim_stun;
            g_Player.timers[PL_T_2] = 8;
            g_Player.unk40 = 0x8166;
            g_api.PlaySfx(SFX_VO_MAR_PAIN_B);
        }
        PLAYER.velocityX = PLAYER.velocityY = 0;
        PLAYER.step_s = 1;
        g_Player.unk60 = 2;
        break;
    case 1:
        // Effectively a switch on g_Player.unk60
        if (g_Player.unk60 == 3) {
            damage.effects = EFFECT_NONE;
            damage.damageKind = DAMAGEKIND_1;
            damage.damageTaken = g_Player.damageTaken;
            damageResult = g_api.CalcPlayerDamageMaria(&damage);
            if (damageResult) {
                MarSetStep(PL_S_DEAD);
                MarStepDead(0, 2, PL_S_BOSS_GRAB, 1);
                return;
            }
            if (g_Player.unk62 == 0) {
                g_Player.timers[PL_T_2] = 4;
                g_Player.unk40 = 0x8166;
                g_api.PlaySfx(SFX_VO_MAR_PAIN_C);
            }
            if (g_Player.unk62 == 2) {
            }
            g_Player.unk60 = 2;
        } else if (g_Player.unk60 == 4) {
            PLAYER.step = PL_S_HIT;
            PLAYER.step_s = 2;
            g_Player.unk60 = 0;
            g_Player.damageTaken = g_Player.unk64;
            g_api.PlaySfx(SFX_VO_MAR_PAIN_D);
        } else if (g_Player.unk60 == 0) {
            PLAYER.step = PL_S_HIT;
            PLAYER.step_s = 1;
        }
        break;
    }
}

enum DeathKind {
    DEATH_GENERIC,
    DEATH_BY_FIRE,
    DEATH_BY_THUNDER,
    DEATH_BY_ICE,
};
#if defined(VERSION_PSP)
extern u8 dead_dissolve_bmp[0x1400];
extern s16 D_80174F68;
extern s16 D_80174F6C;
extern enum DeathKind death_kind;
// RECT D_801545A0 = {512, 256, 32, 80};
extern RECT D_801545A0;
#else
static u8 dead_dissolve_bmp[0x1400];
static s16 D_80174F68;
STATIC_PAD_BSS(2);
static s16 D_80174F6C;
STATIC_PAD_BSS(2);
static enum DeathKind death_kind;
#endif
void MarStepDead(
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
        MarSetAnimation(mar_80155544);
        PLAYER.velocityY = FIX(-1.625);
        g_api.PlaySfx(SFX_VO_MAR_DEATH);
        if (damageEffects & ELEMENT_FIRE) {
            func_8015FA5C(0);
            // RIC blueprint 33 has child 31, EntityPlayerBlinkWhite
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x48), 0);
            // RIC blueprint 53 has child 9, func_80161C2C
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_DEATH_BY_FIRE, 2), 0);
            death_kind = DEATH_BY_FIRE;
        } else if (damageEffects & ELEMENT_THUNDER) {
            func_8015FA5C(2);
            // RIC blueprint 33 has child 31, EntityPlayerBlinkWhite
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x4C), 0);
            // RIC blueprint 48 has child 41, EntityHitByLightning
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_THUNDER, 1), 0);
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_THUNDER, 2), 0);
            death_kind = DEATH_BY_THUNDER;
        } else if (damageEffects & ELEMENT_ICE) {
            func_8015FA5C(3);
            // RIC blueprint 33 has child 31, EntityPlayerBlinkWhite
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x4D), 0);
            // RIC blueprint 47 has child 40, EntityHitByIce
            MarCreateEntFactoryFromEntity(g_CurrentEntity, 47, 0);
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_ICE, 1), 0);
            death_kind = DEATH_BY_ICE;
            PLAYER.drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            func_8015FA5C(1);
            // RIC blueprint 33 has child 31, EntityPlayerBlinkWhite
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_MAR_BLINK, 0x4A), 0);
            // RIC blueprint 11 has child 5, MarEntityHitByCutBlood
            MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_MULTIPLE_EMBERS, 5), 0);
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
        if (PLAYER.pose != 3) {
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
            StoreImage(&D_801545A0, (u_long*)dead_dissolve_bmp);
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
        LoadImage(&D_801545A0, (u_long*)imgPtr);
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

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", func_pspeu_092B0C70);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", func_pspeu_092B0CD0);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", func_pspeu_092B0D20);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", func_pspeu_092B0D70);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", func_pspeu_092B0DC0);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", func_pspeu_092B0E10);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepSlide);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepRun);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", func_8015BB80);

// Corresponding DRA function is PlayerStepTeleport
void MarStepTeleport(void) {
    Entity* e;

    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    g_Player.padSim = 0;
    g_Player.demo_timer = 4;
    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.pose == 3 && PLAYER.poseTimer == 1) {
            e = MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 0), 0);
            if (!e) {
                PLAYER.poseTimer = 2;
            }
        }
        if (PLAYER.poseTimer < 0) {
            MarSetStand(0);
        }
        break;
    case 1:
        if (PLAYER.poseTimer < 0) {
            MarSetStand(0);
        }
        if (g_Player.warp_flag) {
            MarSetStand(0);
        }
        break;
    case 2:
        func_8015BB80();
        if (PLAYER.pose == 3 && PLAYER.poseTimer == 1) {
            e = MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 2), 0);
            if (!e) {
                PLAYER.poseTimer = 2;
            }
        }
        if (PLAYER.poseTimer < 0) {
            MarSetStand(0);
        }
        break;
    case 3:
        if (PLAYER.poseTimer < 0) {
            MarSetStand(0);
        }
        if (g_Player.warp_flag) {
            MarSetStand(0);
        }
        break;
    case 4:
        func_8015BB80();
        if (PLAYER.pose == 3 && PLAYER.poseTimer == 1) {
            e = MarCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_TELEPORT, 4), 0);
            if (!e) {
                PLAYER.poseTimer = 2;
            }
        }
        if (PLAYER.poseTimer < 0) {
            MarSetStand(0);
        }
        break;
    case 5:
        if (PLAYER.poseTimer < 0) {
            MarSetStand(0);
        }
        if (g_Player.warp_flag) {
            MarSetStand(0);
        }
        break;
    }
}

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepBladeDash);

INCLUDE_ASM("maria_psp/nonmatchings/pl_steps", MarStepHighJump);
