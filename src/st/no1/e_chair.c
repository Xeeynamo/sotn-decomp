// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// check if "sit" has been triggered
static s32 func_us_801B8008(Entity* self) {
    s16 offsetX;
    s16 offsetY;

    if (g_pads[0].pressed != PAD_UP) {
        return 0;
    }

    offsetX = self->posX.i.hi - PLAYER.posX.i.hi;
    offsetY = self->posY.i.hi - PLAYER.posY.i.hi;

    if ((offsetY > 4) || (offsetY < -4)) {
        return 0;
    }

    if ((offsetX > 4) || (offsetX < -4)) {
        return 0;
    }

    return 1;
}

void EntityChair(Entity* self) {
    s16 offsetX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        break;

    case 1:
        if (func_us_801B8008(self) != 0) {
            g_Player.D_80072EFC = 0xA;
            g_Player.padSim = PAD_UP;
            g_Player.unk14 = self->params;

            self->step++;
        }
        break;

    case 2:
        g_Player.unk14 = self->params;
        offsetX = self->posX.i.hi - PLAYER.posX.i.hi;
        if (offsetX > 0) {
            PLAYER.posX.i.hi++;
        }
        if (offsetX < 0) {
            PLAYER.posX.i.hi--;
        }
        if (offsetX == 0) {
            self->step++;
        }
        break;

    case 3:
        g_Player.unk14 = self->params;
        if (PLAYER.animFrameDuration < 0) {
            self->ext.chair.unk0 = 0xA00;
            self->step++;
        }

        if (PLAYER.step != 0 || PLAYER.step_s != 4) {
            self->step = 1;
        }
        break;

    case 4:
        g_Player.unk14 = self->params;
        if (PLAYER.step != 0 || PLAYER.step_s != 4) {
            self->step = 1;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
}
