// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"

extern EInit g_EInitCommon;

void func_us_801B1C34(Entity* self) {
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
    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(g_EInitCommon);
        self->animSet = 0;
        self->animCurFrame = 1;
        self->zPriority = 0xB0;
        break;
    case 1:
        yRaw = self->posY.i.hi - PLAYER.posY.i.hi;
        yAbs = abs(yRaw);
        if (yAbs < 0x20) {
            switch (params) {                /* switch 2 */
            case 0:                                 /* switch 2 */
                if ((xVar < 0x180) && (g_PlayerX < 0x180)) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 1:                                 /* switch 2 */
                if ((xVar > 0x280) && (g_PlayerX > 0x280)) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right -= 1;
                    self->step += 1;
                }
                break;
            case 2:                                 /* switch 2 */
                if ((xVar < 0x100) && (g_PlayerX < 0x100)) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 3:                                 /* switch 2 */
                if ((xVar > 0x300) && (g_PlayerX > 0x300)) {
                    g_Tilemap.width = 0x300;
                    g_Tilemap.right -= 1;
                    self->step += 1;
                }
                break;
            case 4:                                 /* switch 2 */
                if ((xVar < 0x100) && (g_PlayerX < 0x100)) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 5:                                 /* switch 2 */
                if ((xVar > 0x480) && (g_PlayerX > 0x480)) {
                    g_Tilemap.width = 0x480;
                    self->step += 1;
                }
                break;
            case 6:                                 /* switch 2 */
                if ((xVar < 0x80) && (g_PlayerX < 0x80)) {
                    g_Tilemap.x = 0x80;
                    self->step += 1;
                }
                break;
            case 7:                                 /* switch 2 */
                if ((xVar < 0x80) && (g_PlayerX < 0x80)) {
                    g_Tilemap.x = 0x80;
                    self->step += 1;
                }
                break;
            case 8:                                 /* switch 2 */
                if ((xVar > 0x280) && (g_PlayerX > 0x280)) {
                    g_Tilemap.width = 0x280;
                    self->step += 1;
                }
                break;
            case 9:                                 /* switch 2 */
                if ((xVar < 0x80) && (g_PlayerX < 0x80)) {
                    g_Tilemap.x = 0x80;
                    self->step += 1;
                }
                break;
            case 10:                                /* switch 2 */
                if ((xVar > 0x280) && (g_PlayerX > 0x280)) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right -= 1;
                    self->step += 1;
                }
                break;
            case 11:                                /* switch 2 */
                if ((xVar < 0x180) && (g_PlayerX < 0x180)) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 12:                                /* switch 2 */
                if ((xVar > 0x280) && (g_PlayerX > 0x280)) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right -= 1;
                    self->step += 1;
                }
                break;
            case 13:                                /* switch 2 */
                if ((xVar < 0x100) && (g_PlayerX < 0x100)) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left += 1;
                    self->step += 1;
                }
                break;
            case 14:                                /* switch 2 */
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
