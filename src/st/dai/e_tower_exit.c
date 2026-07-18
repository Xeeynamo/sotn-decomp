// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// Towers (T1, T2, T3) count from left to right
// Skyway is the corridor between T1 and T2
enum ExitLocation {
    T1_TO_SKYWAY,
    TO_SPIKES_HALL,
    TO_NO2,
    TOWARD_STAIRS,
    TO_CONFESSIONAL,
    SKYWAY_TO_T1,
    SPIKES_HALL_TO_T1, // These two could
    SKYWAY_TO_T2,      // be swapped
    BO5_TO_T2,
    BO5_TO_T3,
    T2_TO_SKYWAY,
    T2_TO_BO5,
    T3_TO_BO5,
    TO_TOP,
    TO_SAVE,
};

extern EInit g_EInitCommon;

// Handles when the screen transition is not at the edge of the screen when
// leaving dai towers, but does not seem to handle transition into the towers.
void EntityTowerExit(Entity* self) {
    s32 unkX;
    s16 params = self->params;
    s16 offsetY;
    s16 deltaY;

    unkX = g_PlayerX;
    unkX -= g_Player.unk7C - PLAYER.posX.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        break;
    case 1: // It seems that the specific exit logic will be run 3 times before
    case 2: // the entity goes dormant
    case 3: // Starting at step 1 after initialization, it falls through to step
    case 4: // 4 and the specific params case increments self->step each time
        offsetY = self->posY.i.hi - PLAYER.posY.i.hi;
        deltaY = abs(offsetY);
#ifdef VERSION_PSP
        if (deltaY < 32) {
#else
        if (deltaY < 48) {
            if (g_Player.status & PLAYER_STATUS_DEAD) {
                PLAYER.velocityX = 0;
                return;
            }
#endif
            switch (params) {
            case T1_TO_SKYWAY:
                if ((g_PlayerX > 640) && (unkX > 640)) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case TO_SPIKES_HALL:
                if ((g_PlayerX < 384) && (unkX < 384)) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    g_PlayerX -= 256;
                    self->step++;
                }
                break;
            case TO_NO2:
                if ((g_PlayerX > 768) && (unkX > 768)) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case TOWARD_STAIRS:
                if ((g_PlayerX < 256) && (unkX < 256)) {
                    g_Tilemap.x = 256;
                    g_Tilemap.left++;
                    g_PlayerX -= 256;
                    self->step++;
                }
                break;
            case TO_CONFESSIONAL:
                if ((g_PlayerX > 768) && (unkX > 768)) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case SKYWAY_TO_T1:
                if ((g_PlayerX < 128) && (unkX < 128)) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case SPIKES_HALL_TO_T1:
                if ((g_PlayerX > 1152) && (unkX > 1152)) {
                    g_Tilemap.width = 1152;
                    self->step++;
                }
                break;
            case SKYWAY_TO_T2:
                if ((g_PlayerX > 1152) && (unkX > 1152)) {
                    g_Tilemap.width = 1152;
                    self->step++;
                }
                break;
            case BO5_TO_T2:
                if ((g_PlayerX < 128) && (unkX < 128)) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case BO5_TO_T3:
                if ((g_PlayerX > 640) && (unkX > 640)) {
                    g_Tilemap.width = 640;
                    self->step++;
                }
                break;
            case T2_TO_SKYWAY:
                if ((g_PlayerX < 384) && (unkX < 384)) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    g_PlayerX -= 256;
                    self->step++;
                }
                break;
            case T2_TO_BO5:
                if ((g_PlayerX > 640) && (unkX > 640)) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case T3_TO_BO5:
                if ((g_PlayerX < 384) && (unkX < 384)) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    g_PlayerX -= 256;
                    self->step++;
                }
                break;
            case TO_TOP:
                if ((g_PlayerX > 768) && (unkX > 768)) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case TO_SAVE:
                if ((g_PlayerX > 768) && (unkX > 768)) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            }
        }
        break;
    }
}
