// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rdai.h"

extern EInit g_EInitCommon;

void EntityTowerExit(Entity* self) {
    s16 yRaw;
    s16 yAbs;
    s16 xVar;
    s16 params;

    params = self->params;
    FntPrint("set:%04x\n", params);
    FntPrint("sx:%04x\n", g_Tilemap.left);
    FntPrint("ex:%04x\n", g_Tilemap.right);
    xVar = g_PlayerX;
    xVar -= (g_Player.unk7C - PLAYER.posX.i.hi);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = 0;
        self->animCurFrame = 1;
        self->zPriority = 0xB0;
        break;
    case 1:
        yRaw = self->posY.i.hi - PLAYER.posY.i.hi;
        yAbs = abs(yRaw);
#ifdef VERSION_PSP
        if (yAbs < 0x20) {
#else
        if (yAbs < 0x30) {
            if (g_Player.status & PLAYER_STATUS_DEAD) {
                PLAYER.velocityX = 0;
                return;
            }
#endif
            switch (params) {
            case 0:
                if ((xVar < 0x180) && (g_PlayerX < 0x180)) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 1:
                if ((xVar > 0x280) && (g_PlayerX > 0x280)) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right -= 1;
                    self->step += 1;
                }
                break;
            case 2:
                if ((xVar < 0x100) && (g_PlayerX < 0x100)) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 3:
                if ((xVar > 0x300) && (g_PlayerX > 0x300)) {
                    g_Tilemap.width = 0x300;
                    g_Tilemap.right -= 1;
                    self->step += 1;
                }
                break;
            case 4:
                if ((xVar < 0x100) && (g_PlayerX < 0x100)) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 5:
                if ((xVar > 0x480) && (g_PlayerX > 0x480)) {
                    g_Tilemap.width = 0x480;
                    self->step += 1;
                }
                break;
            case 6:
                if ((xVar < 0x80) && (g_PlayerX < 0x80)) {
                    g_Tilemap.x = 0x80;
                    self->step += 1;
                }
                break;
            case 7:
                if ((xVar < 0x80) && (g_PlayerX < 0x80)) {
                    g_Tilemap.x = 0x80;
                    self->step += 1;
                }
                break;
            case 8:
                if ((xVar > 0x280) && (g_PlayerX > 0x280)) {
                    g_Tilemap.width = 0x280;
                    self->step += 1;
                }
                break;
            case 9:
                if ((xVar < 0x80) && (g_PlayerX < 0x80)) {
                    g_Tilemap.x = 0x80;
                    self->step += 1;
                }
                break;
            case 10:
                if ((xVar > 0x280) && (g_PlayerX > 0x280)) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right -= 1;
                    self->step += 1;
                }
                break;
            case 11:
                if ((xVar < 0x180) && (g_PlayerX < 0x180)) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 12:
                if ((xVar > 0x280) && (g_PlayerX > 0x280)) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right -= 1;
                    self->step += 1;
                }
                break;
            case 13:
                if ((xVar < 0x100) && (g_PlayerX < 0x100)) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 14:
                if ((xVar < 0x100) && (g_PlayerX < 0x100)) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            }
        }
        break;
    }
}
