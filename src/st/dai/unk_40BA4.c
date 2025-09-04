// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// I believe this adjusts player position when entering the tower rooms above
// ground floor, but I couldn't validate that with enough confidence to properly
// document the function.
void func_us_801C0BA4(Entity* self) {
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
    case 1:
    case 2:
    case 3:
    case 4:
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
            case 0:
                if ((g_PlayerX > 640) && (unkX > 640)) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 1:
                if ((g_PlayerX < 384) && (unkX < 384)) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    g_PlayerX -= 256;
                    self->step++;
                }
                break;
            case 2:
                if ((g_PlayerX > 768) && (unkX > 768)) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 3:
                if ((g_PlayerX < 256) && (unkX < 256)) {
                    g_Tilemap.x = 256;
                    g_Tilemap.left++;
                    g_PlayerX -= 256;
                    self->step++;
                }
                break;
            case 4:
                if ((g_PlayerX > 768) && (unkX > 768)) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 5:
                if ((g_PlayerX < 128) && (unkX < 128)) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case 6:
                if ((g_PlayerX > 1152) && (unkX > 1152)) {
                    g_Tilemap.width = 1152;
                    self->step++;
                }
                break;
            case 7:
                if ((g_PlayerX > 1152) && (unkX > 1152)) {
                    g_Tilemap.width = 1152;
                    self->step++;
                }
                break;
            case 8:
                if ((g_PlayerX < 128) && (unkX < 128)) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;
            case 9:
                if ((g_PlayerX > 640) && (unkX > 640)) {
                    g_Tilemap.width = 640;
                    self->step++;
                }
                break;
            case 10:
                if ((g_PlayerX < 384) && (unkX < 384)) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    g_PlayerX -= 256;
                    self->step++;
                }
                break;
            case 11:
                if ((g_PlayerX > 640) && (unkX > 640)) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 12:
                if ((g_PlayerX < 384) && (unkX < 384)) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    g_PlayerX -= 256;
                    self->step++;
                }
                break;
            case 13:
                if ((g_PlayerX > 768) && (unkX > 768)) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;
            case 14:
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
