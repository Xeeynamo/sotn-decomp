// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

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
    if (g_CurrentRoom.stageID == STAGE_RTOP) {
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

typedef struct {
    s16 buttonsCorrect;
    s16 timer;
} ButtonComboState;
extern ButtonComboState g_RicComboButtons[2];
extern s32 D_80175958[32];
extern s32 D_801759D8[32];
extern const u16 g_RichterProloguePalette[16];
extern s32 D_060BEDA0;

void RicInit(s32 initParam) {
    Entity* e;
    s16 radius;
    s16 intensity;
    Primitive* prim;
    s32 i;

    g_CurrentEntity = &PLAYER;
    DestroyEntity(g_CurrentEntity);
    PLAYER.posX.val = FIX(32);
    PLAYER.posY.val = FIX(32);
    PLAYER.animSet = 0x8010;
    PLAYER.zPriority = 0x90;
    PLAYER.facingLeft = 0;
    PLAYER.palette = 0;
    PLAYER.scaleY = 0x100;
    PLAYER.scaleX = 0x100;
    PLAYER.unk26 = 0x18;
    memset(&g_Player, 0, sizeof(PlayerState));
    memset(g_RicComboButtons, 0, sizeof(g_RicComboButtons));
    g_Player.vram_flag = g_Player.unk04 = 1;
    RicSetStand(0);
    PLAYER.anim = ric_anim_stand_relax;
    g_Player.unk5C = initParam;
    if (g_CurrentRoom.stageID == STAGE_ST0) {
        g_IsPrologueStage = true;
    } else {
        g_IsPrologueStage = false;
    }
    for (i = 0; i < 32; i++) {
        radius = (MTH_GetRand() & 0x3FF) + 0x100;
        intensity = (MTH_GetRand() & 0xFF) + 0x100;
        D_80175958[i] = +(((rcos(radius) << 4) * intensity) >> 8);
        D_801759D8[i] = -(((rsin(radius) << 4) * intensity) >> 7);
    }
    g_CurrentEntity->unk0 = CreateSpriteObject(
        g_RichterSpriteResources[0].allocationIndex,
        g_RichterSpriteResources[0].flags, g_RichterSpritePackage1Images, 1);
    g_CurrentEntity->ext.spriteEntity.frames = g_RichterSpritePackage1Frames;
    g_CurrentEntity->unk0->zPriority = 0x90;
    D_060BEDA0 = 1;
    g_Player.padSim = 0;
    g_Player.demo_timer = 16;
    for (e = &g_Entities[E_AFTERIMAGE_1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->unk0 = CreateSpriteObject(
            g_RichterSpriteResources[0].allocationIndex,
            g_RichterSpriteResources[0].flags, g_RichterSpritePackage1Images,
            1);
        e->unk0->zPriority = 0x8F;
        e->ext.spriteEntity.frames = g_RichterSpritePackage1Frames;
        e->animSet = 0x8010;
        e->unk56 = i + 1;
        e->palette = 0;
        e->flags = FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
    }
    g_Entities[E_AFTERIMAGE_1].primIndex = AllocPrimitives(0, 6);
    g_Entities[E_AFTERIMAGE_1].flags |= FLAG_HAS_PRIMS;
    for (prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex], i = 0;
         prim != NULL; i++, prim = prim->next) {
        prim->drawMode = DRAW_UNK_100 | DRAW_UNK02 | DRAW_HIDE;
    }
    if (D_80097C98 == 6) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 1), 0);
        RicSetInit(1);
    }
    if (D_80097C98 == 4) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 3), 0);
        RicSetInit(3);
    }
    if (D_80097C98 == 5) {
        RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 5), 0);
        RicSetInit(5);
    }
    func_06008524(0x25F00680, g_RichterProloguePalette, 32);
}

void CheckStageCollision(s32 arg0) {
    Collider collider;
    s32 argX;
    s32 argY;
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
    PLAYER.posY.val += PLAYER.velocityY;
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        argX = PLAYER.posX.val + g_RicSensorsFloor[i].x;
        argY = PLAYER.posY.val + g_RicSensorsFloor[i].y;
        CheckCollision(argX, argY, &g_Player.colFloor[i], 0);
        if (g_Player.timers[PL_T_7] &&
            (g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE)) {
            CheckCollision(argX, argY + FIX(12), &collider, 0);
            if (!(collider.effects & EFFECT_SOLID)) {
                g_Player.colFloor[i].effects = EFFECT_NONE;
            }
        }
    }
    RicCheckFloor();
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        argX = PLAYER.posX.val + g_RicSensorsCeiling[i].x;
        argY = PLAYER.posY.val + g_RicSensorsCeiling[i].y;
        CheckCollision(argX, argY, &g_Player.colCeiling[i], 0);
    }
    RicCheckCeiling();
    if ((*vram_ptr & 1) && (PLAYER.velocityY >= 0)) {
        PLAYER.posY.i.lo = 0;
    }
    if ((*vram_ptr & 2) && (PLAYER.velocityY <= 0)) {
        PLAYER.posY.i.lo = 0;
    }
    for (i = 0; i < NUM_VERTICAL_SENSORS * 2; i++) {
        argX = PLAYER.posX.val + g_RicSensorsWall[i].x;
        argY = PLAYER.posY.val + g_RicSensorsWall[i].y;
        CheckCollision(argX, argY, &g_Player.colWall[i], 0);
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

void CheckBladeDashInput(void) {
    u16 pressed;
    s32 up;
    s32 down;
    s32 down_forward;

    pressed = g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (PLAYER.facingLeft == 0) {
        down_forward = PAD_DOWN | PAD_RIGHT;
    } else {
        down_forward = PAD_DOWN | PAD_LEFT;
    }
    up = PAD_UP;
    down = PAD_DOWN;

    switch (g_RicComboButtons[0].buttonsCorrect) {
    case 0:
        if ((g_Player.padTapped & up) == up) {
            g_RicComboButtons[0].timer = 20;
            g_RicComboButtons[0].buttonsCorrect++;
        }
        break;
    case 1:
        if (pressed == down) {
            g_RicComboButtons[0].timer = 20;
            g_RicComboButtons[0].buttonsCorrect++;
            break;
        }
        if (--g_RicComboButtons[0].timer == 0) {
            g_RicComboButtons[0].buttonsCorrect = 0;
        }
        break;
    case 2:
        if ((pressed & down_forward) == down_forward) {
            g_RicComboButtons[0].timer = 20;
            g_RicComboButtons[0].buttonsCorrect++;
            break;
        }
        if (--g_RicComboButtons[0].timer == 0) {
            g_RicComboButtons[0].buttonsCorrect = 0;
        }
        break;
    case 3:
        if (--g_RicComboButtons[0].timer == 0) {
            g_RicComboButtons[0].buttonsCorrect = 0;
        }
        if (PLAYER.step == PL_S_STAND || PLAYER.step == PL_S_WALK ||
            PLAYER.step == PL_S_CROUCH || PLAYER.step == PL_S_JUMP ||
            PLAYER.step == PL_S_FALL) {
            if (g_Player.unk72) {
                g_RicComboButtons[0].buttonsCorrect = 0;
            } else if (!g_Player.unk46 && (g_Player.padTapped & PAD_SQUARE)) {
                RicSetBladeDash();
            }
        }
        break;
    default:
        g_RicComboButtons[0].buttonsCorrect = 0;
        break;
    }
}

void CheckHighJumpInput(void) {
    switch (g_RicComboButtons[1].buttonsCorrect) {
    case 0:
        if (g_Player.padTapped & PAD_DOWN) {
            if (g_Player.padHeld == 0) {
                g_RicComboButtons[1].timer = 16;
                g_RicComboButtons[1].buttonsCorrect++;
                return;
            }
        }
        break;
    case 1:
        if (g_Player.padTapped & PAD_UP) {
            g_RicComboButtons[1].timer = 16;
            g_RicComboButtons[1].buttonsCorrect++;
            return;
        }
        if (--g_RicComboButtons[1].timer == 0) {
            g_RicComboButtons[1].buttonsCorrect = 0;
        }
        break;
    case 2:
        if (g_RicComboButtons[1].timer && --g_RicComboButtons[1].timer == 0) {
            g_RicComboButtons[1].buttonsCorrect = 0;
            return;
        }
        if (g_Player.padTapped & PAD_CROSS && !g_Player.unk46) {
            if (PLAYER.step == PL_S_CROUCH || PLAYER.step == PL_S_STAND ||
                (PLAYER.step == PL_S_JUMP && PLAYER.velocityY > FIX(1)) ||
                PLAYER.step == PL_S_FALL) {
                if (!g_Player.unk72) {
                    RicSetHighJump();
                }
                g_RicComboButtons[1].buttonsCorrect = 0;
            }
        }
        break;
    default:
        g_RicComboButtons[1].buttonsCorrect = 0;
        break;
    }
}

INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60A5AA0, func_060A5AA0);
