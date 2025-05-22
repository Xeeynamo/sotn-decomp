// SPDX-License-Identifier: AGPL-3.0-or-later
extern Point16 g_DopSensorsFloor[];
extern Point16 g_DopSensorsCeiling[];
extern Point16 g_DopSensorsWall[];
extern s16 g_DopSensorsCeilingDefault[];
extern s16 g_DopSensorsFloorDefault[];
extern s16 g_DopSensorsCeilingCrouch[];
extern s16 g_DopSensorsFloorCrouch[];
extern s16 g_DopSensorsWallCrouch[];
extern s16 g_DopSensorsWallDefault[];

static void OVL_EXPORT(CheckStageCollision)(bool checkSensors) {
    s16 argX;
    s16 argY;
    s32 xVel;
    s32 i;
    s32 j;
    s32* vram_ptr;
    s32* unk04_ptr;
    s32 status;
    s32 unk04;

    vram_ptr = &g_Dop.vram_flag;
    unk04_ptr = &g_Dop.unk04;
    *unk04_ptr = *vram_ptr;
    *vram_ptr = NULL;
    status = g_Dop.status;

    if (checkSensors) {
        for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
            if (status & Dop_Crouch) {
                g_DopSensorsFloor[i].y = g_DopSensorsFloorCrouch[i];
                g_DopSensorsCeiling[i].y = g_DopSensorsCeilingCrouch[i];
            } else {
                g_DopSensorsFloor[i].y = g_DopSensorsFloorDefault[i];
                g_DopSensorsCeiling[i].y = g_DopSensorsCeilingDefault[i];
            }
        }
        for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
            if (status & Dop_Crouch) {
                g_DopSensorsWall[i].y = g_DopSensorsWallCrouch[i];
                g_DopSensorsWall[i + NUM_VERTICAL_SENSORS].y =
                    g_DopSensorsWallCrouch[i];
            } else {
                g_DopSensorsWall[i].y = g_DopSensorsWallDefault[i];
                g_DopSensorsWall[i + NUM_VERTICAL_SENSORS].y =
                    g_DopSensorsWallDefault[i];
            }
        }
    }
    xVel = DOPPLEGANGER.velocityX;
    unk04 = (*unk04_ptr & 0xF000);
    if (DOPPLEGANGER.velocityX < 0 && !(*unk04_ptr & 8)) {
        if (unk04 == 0xC000) {
            xVel = xVel * 10 / 16;
        }
        if (unk04 == 0xD000) {
            xVel = xVel * 13 / 16;
        }
        DOPPLEGANGER.posX.val += xVel;
    }
    if (DOPPLEGANGER.velocityX > 0 && !(*unk04_ptr & 4)) {
        if (unk04 == 0x8000) {
            xVel = xVel * 10 / 16;
        }
        if (unk04 == 0x9000) {
            xVel = xVel * 13 / 16;
        }
        DOPPLEGANGER.posX.val += xVel;
    }
    if ((DOPPLEGANGER.velocityY < 0) && !(*unk04_ptr & 2)) {
        DOPPLEGANGER.posY.val += DOPPLEGANGER.velocityY;
    }
    if ((DOPPLEGANGER.velocityY > 0) && !(*unk04_ptr & 1)) {
        DOPPLEGANGER.posY.val += DOPPLEGANGER.velocityY;
    }
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        argX = DOPPLEGANGER.posX.i.hi + g_DopSensorsFloor[i].x;
        argY = DOPPLEGANGER.posY.i.hi + g_DopSensorsFloor[i].y;
        g_api.CheckCollision(argX, argY, &g_Dop.colFloor[i], 0);
    }
    OVL_EXPORT(CheckFloor)();
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        argX = DOPPLEGANGER.posX.i.hi + g_DopSensorsCeiling[i].x;
        argY = DOPPLEGANGER.posY.i.hi + g_DopSensorsCeiling[i].y;
        g_api.CheckCollision(argX, argY, &g_Dop.colCeiling[i], 0);
    }
    OVL_EXPORT(CheckCeiling)();
    if ((*vram_ptr & 1) && (DOPPLEGANGER.velocityY >= 0)) {
        DOPPLEGANGER.posY.i.lo = 0;
    }
    if ((*vram_ptr & 2) && (DOPPLEGANGER.velocityY <= 0)) {
        DOPPLEGANGER.posY.i.lo = 0;
    }
    for (i = 0; i < NUM_VERTICAL_SENSORS * 2; i++) {
        argX = DOPPLEGANGER.posX.i.hi + g_DopSensorsWall[i].x;
        argY = DOPPLEGANGER.posY.i.hi + g_DopSensorsWall[i].y;
        g_api.CheckCollision(argX, argY, &g_Dop.colWall[i], 0);
    }
    OVL_EXPORT(CheckWallRight)();
    OVL_EXPORT(CheckWallLeft());
    if ((*vram_ptr & 4) && (DOPPLEGANGER.velocityX > 0)) {
        DOPPLEGANGER.posX.i.lo = 0;
    }
    if ((*vram_ptr & 8) && (DOPPLEGANGER.velocityX < 0)) {
        DOPPLEGANGER.posX.i.lo = 0;
    }
    if (*vram_ptr & 0x8000) {
        *vram_ptr |= 0x20;
    }
    if (!(g_Dop.colFloor[1].effects & EFFECT_SOLID) ||
        !(g_Dop.colFloor[2].effects & EFFECT_SOLID) ||
        !(g_Dop.colFloor[3].effects & EFFECT_SOLID)) {
        *vram_ptr |= 0x20;
    }
}
