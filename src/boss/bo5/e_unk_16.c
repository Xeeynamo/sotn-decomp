// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

extern EInit g_EInitCommon;

void EntityCameraBounds(Entity* self) {
    s16 params = self->params;
    s16 offsetY;
    s16 deltaY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        break;
    case 1:
        offsetY = self->posY.i.hi - PLAYER.posY.i.hi;
        deltaY = abs(offsetY);
        if (deltaY < 32) {
            switch (params) {
            case 0:
                if (g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 1:
                if (g_PlayerX < 384) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;
            case 2:
                if (g_PlayerX > 768) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 3:
                if (g_PlayerX < 256) {
                    g_Tilemap.x = 256;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;
            case 4:
                if (g_PlayerX > 768) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 5:
                if (g_PlayerX < 128) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case 6:
                if (g_PlayerX > 1152) {
                    g_Tilemap.width = 1152;
                    self->step++;
                }
                break;
            case 7:
                if (g_PlayerX > 1152) {
                    g_Tilemap.width = 1152;
                    self->step++;
                }
                break;
            case 8:
                if (g_PlayerX < 128) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case 9:
                if (g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    self->step++;
                }
                break;
            case 10:
                if (g_PlayerX < 384) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;
            case 11:
                if (g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 12:
                if (g_PlayerX < 384) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;
            case 13:
                if (g_PlayerX > 768) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 14:
                if (g_PlayerX > 768) {
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
