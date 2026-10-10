// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"

void func_us_80191438(Entity* self) {
    s16 params;
    s16 y;
    s16 absY;

    params = self->params;
    FntPrint("set:%04x\n", params);
    FntPrint("sx:%04x\n", g_Tilemap.left);
    FntPrint("ex:%04x\n", g_Tilemap.right);

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->zPriority = 176;
        break;

    case 1:
        y = self->posY.i.hi - PLAYER.posY.i.hi;
        absY = abs(y);
        if (absY >= 32) {
            break;
        }

        switch (params) {
        case 0:
            if (g_PlayerX < 384) {
                g_Tilemap.x = 384;
                g_Tilemap.left++;
                self->step++;
            }
            break;

        case 1:
            if (g_PlayerX > 640) {
                g_Tilemap.width = 640;
                g_Tilemap.right--;
                self->step++;
            }
            break;

        case 2:
            if (g_PlayerX < 256) {
                g_Tilemap.x = 256;
                g_Tilemap.left++;
                self->step++;
            }
            break;

        case 3:
            if (g_PlayerX > 768) {
                g_Tilemap.width = 768;
                g_Tilemap.right--;
                self->step++;
            }
            break;

        case 4:
            if (g_PlayerX < 256) {
                g_Tilemap.x = 256;
                g_Tilemap.left++;
                self->step++;
            }
            break;

        case 5:
            if (g_PlayerX > 1152) {
                g_Tilemap.width = 1152;
                self->step++;
            }
            break;

        case 6:
            if (g_PlayerX < 128) {
                g_Tilemap.x = 128;
                self->step++;
            }
            break;

        case 7:
            if (g_PlayerX < 128) {
                g_Tilemap.x = 128;
                self->step++;
            }
            break;

        case 8:
            if (g_PlayerX > 640) {
                g_Tilemap.width = 640;
                self->step++;
            }
            break;

        case 9:
            if (g_PlayerX < 128) {
                g_Tilemap.x = 128;
                self->step++;
            }
            break;

        case 10:
            if (g_PlayerX > 640) {
                g_Tilemap.width = 640;
                g_Tilemap.right--;
                self->step++;
            }
            break;

        case 11:
            if (g_PlayerX < 384) {
                g_Tilemap.x = 384;
                g_Tilemap.left++;
                self->step++;
            }
            break;

        case 12:
            if (g_PlayerX > 640) {
                g_Tilemap.width = 640;
                g_Tilemap.right--;
                self->step++;
            }
            break;

        case 13:
            if (g_PlayerX < 256) {
                g_Tilemap.x = 256;
                g_Tilemap.left++;
                self->step++;
            }
            break;

        case 14:
            if (g_PlayerX < 256) {
                g_Tilemap.x = 256;
                g_Tilemap.left++;
                self->step++;
            }
            break;
        }
        break;
    }
}
