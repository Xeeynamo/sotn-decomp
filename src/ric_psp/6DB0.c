// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

static TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (PLAYER.step != PL_S_STAND || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }

    // Check for X/Y boundaries in TOP
    if (g_StageId == STAGE_TOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX - 8000) < 4 &&
            abs((g_Tilemap.top << 8) + g_PlayerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX - 8384) < 4 &&
#if defined(VERSION_PSP)
            abs((g_Tilemap.top << 8) + g_PlayerY - 14407) < 4) {
#else
            abs((g_Tilemap.top << 8) + g_PlayerY) - 14407 < 4) {
#endif
            return TELEPORT_CHECK_TO_TOP;
        }
    }

    return TELEPORT_CHECK_NONE;
}

static s16 func_80156DE4(void) {
    // Variables that change during execution
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    s32 xCenter;
    s32 xRight;
    s32 xLeft;
    s32 filter;

    // Values that are set once and never again (but not const for some reason)
    filter = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
    xCenter = PLAYER.posX.i.hi;
    xRight = PLAYER.posX.i.hi + 4;
    xLeft = PLAYER.posX.i.hi - 4;

    for (i = 0; i < 3; i++) {
        yvar = PLAYER.posY.i.hi + D_80154568[i];
        collisions = 0;
        g_api.CheckCollision(xCenter, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xRight, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xLeft, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}

extern s32 D_pspeu_092D7A68;
extern s32 D_pspeu_092CFA58;
extern s32 D_pspeu_092D33BC;
extern u8 D_pspeu_092D2548[]; // FR
extern u8 D_pspeu_092CFA70[]; // SP
extern u8 D_pspeu_092D16F8[]; // GE
extern u8 D_pspeu_092D08B8[]; // IT
extern s32 D_pspeu_092D33B0;
// Similar to of DRA func_80109594
void RicInit(s16 initParam) {
    Entity* e;
    s16 radius;
    s16 intensity;
    Primitive* prim;
    s32 i;
    SpriteParts** spriteptr;
    s32* memset_ptr;
    s32 memset_len;
#ifndef VERSION_PSP
    Entity* g_CurrentEntity;
#endif

    g_CurrentEntity = &PLAYER;
    DestroyEntity(g_CurrentEntity);
    PLAYER.posX.val = FIX(32);
    PLAYER.posY.val = FIX(32);
    PLAYER.animSet = ANIMSET_OVL(0x10);
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
    PLAYER.facingLeft = 0;
    PLAYER.palette = 0x8120;
    PLAYER.rotY = 0x100;
    PLAYER.rotX = 0x100;
    PLAYER.rotPivotY = 0x18;
    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = (s32*)&g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }
    g_Player.vram_flag = g_Player.unk04 = 1;
    RicSetStand(0);
    PLAYER.anim = ric_anim_stand_relax;
    g_Player.unk5C = initParam;
    if (g_StageId == STAGE_ST0) {
        g_IsPrologueStage = true;
    } else {
        g_IsPrologueStage = false;
    }
    g_PlayerDraw->enableColorBlend = 0;
    RicDebugOff();
    for (i = 0; i < LEN(D_80175958); i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        D_80175958[i] = +(((rcos(radius) << 4) * intensity) >> 8);
        D_801759D8[i] = -(((rsin(radius) << 4) * intensity) >> 7);
    }
    spriteptr = g_api.o.spriteBanks;
    spriteptr += 0x10;
    *spriteptr = (SpriteParts*)D_801530AC;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_80153AA0;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_80153D24;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_801541A8;
    for (e = &g_Entities[1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_OVL(0x10);
        e->unk5A = i + 1;
        e->palette = PAL_OVL(0x120);
        e->flags = FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
    }
    g_Entities[1].primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    g_Entities[1].flags |= FLAG_HAS_PRIMS;
    for (prim = &g_PrimBuf[g_Entities[1].primIndex], i = 0; prim != NULL; i++,
        prim = prim->next) {
        prim->drawMode = DRAW_UNK_100 | DRAW_UNK02 | DRAW_HIDE;
    }
    if (D_80097C98 == 6) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 1), 0);
        func_8015CC70(1);
    }
    if (D_80097C98 == 4) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 3), 0);
        func_8015CC70(3);
    }
    if (D_80097C98 == 5) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 5), 0);
        func_8015CC70(5);
    }
#ifdef VERSION_PSP
    D_pspeu_092D7A68 = 0x1E;
    func_91040A0(&D_pspeu_092CFA58);
    D_pspeu_092D33BC = func_pspeu_092ACE78(
        0, D_pspeu_092D2548, D_pspeu_092CFA70, D_pspeu_092D16F8,
        D_pspeu_092D08B8);
    if (D_pspeu_092D33BC != 0) {
        func_91040A0(&D_pspeu_092D33B0);
    }
#endif
}

static void CheckStageCollision(bool arg0) {
    Collider collider;
    s16 argX;
    s16 argY;
    s32 xVel;
    s32 i;
    s32 j;
    s32* vram_ptr;
    s32* unk04_ptr;
    s32 status;

    vram_ptr = &g_Player.vram_flag;
    unk04_ptr = &g_Player.unk04;
    *unk04_ptr = *vram_ptr;
    *vram_ptr = 0;
    status = g_Player.status;

    if (arg0) {
        for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
            if (status & PLAYER_STATUS_CROUCH) {
                g_RicSensorsFloor[i].y = g_RicSensorsFloorDefault[i];
                g_RicSensorsCeiling[i].y = g_RicSensorsCeilingCrouch[i];
            } else {
                g_RicSensorsFloor[i].y = g_RicSensorsFloorDefault[i];
                g_RicSensorsCeiling[i].y = g_RicSensorsCeilingDefault[i];
            }
        }
        for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
            if (status & PLAYER_STATUS_CROUCH) {
                g_RicSensorsWall[i].y = g_RicSensorsWallCrouch[i];
                g_RicSensorsWall[i + NUM_VERTICAL_SENSORS].y =
                    g_RicSensorsWallCrouch[i];
            } else {
                g_RicSensorsWall[i].y = g_RicSensorsWallDefault[i];
                g_RicSensorsWall[i + NUM_VERTICAL_SENSORS].y =
                    g_RicSensorsWallDefault[i];
            }
        }
    }
    xVel = PLAYER.velocityX;
    if (PLAYER.velocityX < 0) {
        if (!(*unk04_ptr & 8)) {
            if ((*unk04_ptr & 0xF000) == 0xC000) {
                xVel = xVel * 10 / 16;
            }
            if ((*unk04_ptr & 0xF000) == 0xD000) {
                xVel = xVel * 13 / 16;
            }
            PLAYER.posX.val += xVel;
        }
    }
    if (PLAYER.velocityX > 0) {
        if (!(*unk04_ptr & 4)) {
            if ((*unk04_ptr & 0xF000) == 0x8000) {
                xVel = xVel * 10 / 16;
            }
            if ((*unk04_ptr & 0xF000) == 0x9000) {
                xVel = xVel * 13 / 16;
            }
            PLAYER.posX.val += xVel;
        }
    }
    if ((PLAYER.velocityY < 0) && !(*unk04_ptr & 2)) {
        PLAYER.posY.val += PLAYER.velocityY;
    }
    if ((PLAYER.velocityY > 0) && !(*unk04_ptr & 1)) {
        PLAYER.posY.val += PLAYER.velocityY;
    }
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        argX = PLAYER.posX.i.hi + g_RicSensorsFloor[i].x;
        argY = PLAYER.posY.i.hi + g_RicSensorsFloor[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colFloor[i], 0);
        if (g_Player.timers[PL_T_7] &&
            (g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
            g_api.CheckCollision(argX, argY + 0xC, &collider, 0);
            if (!(collider.effects & EFFECT_SOLID)) {
                g_Player.colFloor[i].effects = EFFECT_NONE;
            }
        }
    }
    RicCheckFloor();
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        argX = PLAYER.posX.i.hi + g_RicSensorsCeiling[i].x;
        argY = PLAYER.posY.i.hi + g_RicSensorsCeiling[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colCeiling[i], 0);
    }
    RicCheckCeiling();
    if ((*vram_ptr & 1) && (PLAYER.velocityY >= 0)) {
        PLAYER.posY.i.lo = 0;
    }
    if ((*vram_ptr & 2) && (PLAYER.velocityY <= 0)) {
        PLAYER.posY.i.lo = 0;
    }
    for (i = 0; i < NUM_VERTICAL_SENSORS * 2; i++) {
        argX = PLAYER.posX.i.hi + g_RicSensorsWall[i].x;
        argY = PLAYER.posY.i.hi + g_RicSensorsWall[i].y;
        g_api.CheckCollision(argX, argY, &g_Player.colWall[i], 0);
    }
    RicCheckWallRight();
    RicCheckWallLeft();
    if ((*vram_ptr & 4) && (PLAYER.velocityX > 0)) {
        PLAYER.posX.i.lo = 0;
    }
    if ((*vram_ptr & 8) && (PLAYER.velocityX < 0)) {
        PLAYER.posX.i.lo = 0;
    }
}

static void CheckBladeDashInput(void) {
    s32 pressed;
    s32 up;
    s32 down;
    s32 forward;
    s32 down_forward;

    pressed = g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (PLAYER.facingLeft == 0) {
        down_forward = PAD_DOWN | PAD_RIGHT;
        forward = PAD_RIGHT;
    } else {
        down_forward = PAD_DOWN | PAD_LEFT;
        forward = PAD_LEFT;
    }
    up = PAD_UP;
    down = PAD_DOWN;

    switch (g_bladeDashButtons.buttonsCorrect) {
    case 0:
        if (g_Player.padTapped == up) {
            g_bladeDashButtons.timer = 20;
            g_bladeDashButtons.buttonsCorrect++;
        }
        break;
    case 1:
        if (pressed == down) {
            g_bladeDashButtons.timer = 20;
            g_bladeDashButtons.buttonsCorrect++;
            break;
        }
        if (--g_bladeDashButtons.timer == 0) {
            g_bladeDashButtons.buttonsCorrect = 0;
        }
        break;
    case 2:
        if (pressed == down_forward) {
            g_bladeDashButtons.timer = 20;
            g_bladeDashButtons.buttonsCorrect++;
            break;
        }
        if (--g_bladeDashButtons.timer == 0) {
            g_bladeDashButtons.buttonsCorrect = 0;
        }
        break;
    case 3:
        if (--g_bladeDashButtons.timer == 0) {
            g_bladeDashButtons.buttonsCorrect = 0;
        }
        if (PLAYER.step == PL_S_STAND || PLAYER.step == PL_S_WALK ||
            PLAYER.step == PL_S_CROUCH || PLAYER.step == PL_S_JUMP ||
            PLAYER.step == PL_S_FALL) {
            if (g_Player.unk72) {
                g_bladeDashButtons.buttonsCorrect = 0;
            } else if (!g_Player.unk46 && (g_Player.padTapped & PAD_SQUARE)) {
                RicSetBladeDash();
            }
        }
        break;
    }
}

static void CheckHighJumpInput(void) {
    switch (D_801758E4.buttonsCorrect) {
    case 0:
        if (g_Player.padTapped & PAD_DOWN) {
            if (g_Player.padHeld == 0) {
                D_801758E4.timer = 16;
                D_801758E4.buttonsCorrect++;
                return;
            }
        }
        break;
    case 1:
        if (g_Player.padTapped & PAD_UP) {
            D_801758E4.timer = 16;
            D_801758E4.buttonsCorrect++;
            return;
        }
        if (--D_801758E4.timer == 0) {
            D_801758E4.buttonsCorrect = 0;
        }
        break;
    case 2:
        if (D_801758E4.timer && --D_801758E4.timer == 0) {
            D_801758E4.buttonsCorrect = 0;
            return;
        }
        if (g_Player.padTapped & PAD_CROSS && !g_Player.unk46) {
            if (PLAYER.step == PL_S_CROUCH || PLAYER.step == PL_S_STAND ||
                (PLAYER.step == PL_S_JUMP && PLAYER.velocityY > FIX(1)) ||
                PLAYER.step == PL_S_FALL) {
                if (g_Player.unk72) {
                    D_801758E4.buttonsCorrect = 0;
                } else {
                    RicSetHighJump();
                    D_801758E4.buttonsCorrect = 0;
                }
            }
        }
        break;
    }
}

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicMain);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015CC70);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetCrouch);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetStand);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AF600);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetWalk);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetFall);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetJump);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetHighJump);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AFA90);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AFB68);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092AFDA8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicDoCrash);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetDeadPrologue);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B05A8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetSlideKick);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetBladeDash);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015C4AC);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B0A10);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetStep);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetAnimation);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicDecelerateX);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCheckFacing);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetSpeedX);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015CAAC);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetInvincibilityFrames);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", DisableAfterImage);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015CC28);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCheckInput);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicGetPlayerSensor);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCheckFloor);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCheckCeiling);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCheckWallRight);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCheckWallLeft);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", ReboundStoneBounce1);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", ReboundStoneBounce2);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnReboundStone);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnThrownVibhuti);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092B4688);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnAgunea);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityAguneaHitEnemy);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityVibhutiCrashCloud);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashVibhuti);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashReboundStoneParticles);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8016D9C4);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashReboundStoneExplosion);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashReboundStone);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashBibleBeam);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashBible);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8016F198);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashStopwatchDoneSparkle);
// clang-format on

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityStopwatchCrashLightning);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashStopwatch);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BA338);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BA540);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityAguneaLightning);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityAguneaCircle);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnStopwatchCircle);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnStopwatch);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnBibleTrail);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnBible);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BE4C8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BE570);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BE628);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_8015FA5C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicSetSubweaponParams);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BE888);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092BEA38);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByHoly);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByDark);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityDummy);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicUpdatePlayerEntities);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicCreateEntFactoryFromEntity);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityFactory);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySlideKick);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80160D2C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityBladeDash);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80160F0C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySmokePuff);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByCutBlood);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80161C2C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80161EF8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityApplyMariaPowerAnim);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_801623E0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80162604);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityMariaPowers);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityNotImplemented4);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityMaria);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C2E98);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityPlayerBlinkWhite);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_801641A0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityShrinkingPowerUpRing);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByIce);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityHitByLightning);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C73B0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C77B8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityTeleport);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashCrossBeam);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C8D48);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityNotImplemented3);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80167A70);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityCrashHydroStorm);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C9988);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_pspeu_092C9B88);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnHolyWater);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnHolyWaterFlame);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityWhip);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityArmBrandishWhip);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80167964);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityNotImplemented1);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityNotImplemented2);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnCrashCross);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntityRevivalColumn);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnCross);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", func_80169C10);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnCrossTrail);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/6DB0", RicEntitySubwpnCrashCrossParticles);
// clang-format on
