// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

// export table
INCLUDE_ASM("asm/saturn/richter/data", d60A5000, d_060A5000);

// ===== pl_main.c

// GetTeleportToOtherCastle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5060, func_060A5060);

// func_80156DE4
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A5154, func_060A5154);

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

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A6738, func_060A6738);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A67B0, func_060A67B0);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A68A0, func_060A68A0);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A6D64, func_060A6D64);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A6DFC, func_060A6DFC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A726C, func_060A726C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A7310, func_060A7310);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A7B78, func_060A7B78);
INCLUDE_ASM("asm/saturn/richter/data", d60A7CF0, d_060A7CF0);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A7FD4, func_060A7FD4);

// RicStepEnableFlameWhip
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A80B0, func_060A80B0);

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A81C4, func_060A81C4);

// RicStepThrowDaggers
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A8234, func_060A8234);

// RicStepDeadPrologue
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A82F8, func_060A82F8);

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A8664, func_060A8664);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A887C, func_060A887C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A892C, func_060A892C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A8A58, func_060A8A58);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A8C88, func_060A8C88);

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A8F00, func_060A8F00);

// RicSetStand
extern AnimationFrame ric_anim_stand[];
void RicSetStand(s32 velocityX) {
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    g_Player.unk44 = 0;
    RicSetStep(PL_S_STAND);
    RicSetAnimation(ric_anim_stand);
}

#define RicSetSpeedX(speed)                                                    \
    do {                                                                       \
        s32 _tmp_speed = (speed);                                              \
        if (g_CurrentEntity->facingLeft == 1)                                  \
            _tmp_speed = -_tmp_speed;                                          \
        g_CurrentEntity->velocityX = _tmp_speed;                               \
    } while (0)

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
    RicSetSpeedX(0x19000);
    PLAYER.velocityY = 0;
}

// RicSetRun
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9068, func_060A9068);

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
            RicSetSpeedX(0x2D000);
            g_Player.unk44 = 0x10;
        } else {
            RicSetSpeedX(0x19000);
            g_Player.unk44 = 0;
        }
    } else {
        RicSetAnimation(D_801554F0);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
    }
    RicSetStep(PL_S_JUMP);
    if (g_IsPrologueStage) {
        PLAYER.velocityY = -0x4B000;
    } else {
        PLAYER.velocityY = -0x57000;
    }
}

// RicSetHighJump
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A92D8, func_060A92D8);

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9A74, func_060A9A74);

// RicSetSlideKick
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9AFC, func_060A9AFC);

// RicSetBladeDash
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9B9C, func_060A9B9C);

// ===== pl_utils.c
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60A9C2C, func_060A9C2C);

// func_8015C6D4
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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA438, func_060AA438);

void func_8015CC28(void) {
    g_Entities[E_AFTERIMAGE_1].ext.afterimage.disableFlag =
        g_Entities[E_AFTERIMAGE_1].ext.afterimage.resetFlag =
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.unk2 =
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.unk3 = 0;
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA4F4, func_060AA4F4);

// RicCheckInput
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AA5C0, func_060AA5C0);

// func_8015E484
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AAB80, func_060AAB80);

extern Point16 g_RicSensorsCeiling[NUM_HORIZONTAL_SENSORS];
extern Point16 g_RicSensorsFloor[NUM_HORIZONTAL_SENSORS];
extern Point16 g_RicSensorsWall[NUM_VERTICAL_SENSORS * 2];

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ABC24, func_060ABC24);

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AC398, func_060AC398);

// RicEntityFactory
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AC46C, func_060AC46C);

// RicEntitySlideKick
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AC824, func_060AC824);

// func_80160D2C
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60AC908, func_060AC908);

// RicEntityBladeDash
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ACA10, func_060ACA10);

// func_80160F0C
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60ACACC, func_060ACACC);

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B1458, func_060B1458);

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

// RicEntityCrashReboundStoneParticles
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B33DC, func_060B33DC);

// ===== 319C4.c

// func_8016D9C4, includes part of next function
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3454, func_060B3454);

// RicEntityCrashReboundStoneExplosion, split start at mid function
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3A0C, func_060B3A0C);
// RicEntityCrashReboundStone
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3A48, func_060B3A48);

// RicEntityCrashBibleBeam
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3B3C, func_060B3B3C);

// RicEntityCrashBible
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B40F8, func_060B40F8);

// func_8016F198
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B4644, func_060B4644);

// RicEntityCrashStopwatchDoneSparkle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B47EC, func_060B47EC);

// RicEntityStopwatchCrashLightning
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B5434, func_060B5434);

// RicEntityCrashStopwatch
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B54AC, func_060B54AC);

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9D6C, func_060B9D6C);

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

s32 func_06032EA8(s32, s32, s32);
void func_06033024(s32, s32, s32);
void func_060BB330();

s32 DAT_060c4118;
s32 DAT_060c411c;

void func_060BACA4(void) {
    s32 arg0;
    s32 arg2;
    s32 arg1;
    void (*ptr)(s32, s32, s32);
    func_06032EA8(&DAT_060c4118, 0, 4);
    arg0 = 0x002B2000;
    arg1 = &DAT_060c411c;
    ptr = func_06033024;
    arg2 = 0x00009600;
    ptr(arg0, arg1, arg2);

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB90C, func_060BB90C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB9BC, func_060BB9BC);

s32 d_06086390;
s32 d_060476A0;
s32 d_060476A4;
s32 d_060cd748;
s32 d_060cd74c;
void func_060BB9BC(s32*);
s32* func_060784A8();

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
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC7A8, func_060BC7A8);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC834, func_060BC834);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BCA10, func_060BCA10);
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
