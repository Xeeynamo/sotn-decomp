// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

void func_801AA218(s16 arg0) {
    s16 temp_a1 = ((0xE0 - arg0) / 2) + 0x80;
    s16 temp_v1 = temp_a1 - g_unkGraphicsStruct.unkC;

    if (temp_v1 >= 3) {
        g_unkGraphicsStruct.unkC += 2;
    } else if (temp_v1 < -2) {
        g_unkGraphicsStruct.unkC -= 2;
    } else {
        g_unkGraphicsStruct.unkC = temp_a1;
    }
}

void EntityCutscene(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    u16 posX;

    self->posX.i.hi = player->posX.i.hi;
    self->posY.i.hi = player->posY.i.hi - 1;

    if ((self->step != 14) && g_SkipCutscene && g_IsCutsceneDone &&
        (self->step >= 5)) {
        self->step = 15;
        self->animSet = ANIMSET_DRA(0);
        self->animCurFrame = 0;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180598);
        self->unk5A = 0x46;
        self->palette = 0x120;
        break;

    case 1:
        if (self->step_s != 0) {
            if ((player->step < 3) || (player->step == 25)) {
                posX = player->posX.i.hi + tilemap->scrollX.i.hi;
                if (posX > 0x8000) {
                    posX = 0;
                }
                if (posX > 0xA0) {
                    g_Player.padSim = PAD_LEFT;
                } else {
                    g_Player.padSim = PAD_RIGHT;
                }
                g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
                g_Player.D_80072EFC = 0xFF;
                func_801AA218(posX);
                SetStep(2);
            }
        } else {
            if ((player->posX.i.hi + tilemap->scrollX.i.hi) < 0xE1) {
                D_8003C8B8 = 0;
                self->step_s++;
            }
        }
        break;

    case 2:
        posX = player->posX.i.hi + tilemap->scrollX.i.hi;
        if (posX > 0x8000) {
            posX = 0;
        }

        if ((g_Player.padSim == 0x8000) && (posX <= 0xA0) ||
            (g_Player.padSim == 0x2000) && (posX >= 0x9F)) {
            g_Player.D_80072EFC = 1;
            g_Player.padSim = PAD_LEFT;
            self->ext.generic.unk7C.s = 0x18;
            g_CutsceneFlags |= 1;
            self->step++;
        }
        func_801AA218(posX);
        break;

    case 3:
        posX = player->posX.i.hi + tilemap->scrollX.i.hi;
        if (posX > 0x8000) {
            posX = 0;
        }
        func_801AA218(posX);
        g_Player.D_80072EFC = 1;
        g_Player.padSim = 0;
        if (!--self->ext.generic.unk7C.u) {
            SetStep(4);
        }
        break;

    case 4:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180830, self) == 0) {
            self->step++;
            g_Tilemap.width = 0x100;
        }
        player->animCurFrame = self->animCurFrame;
        break;

    case 5:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = self->animCurFrame;
        if (g_CutsceneFlags & 0x400) {
            player->animCurFrame = 0;
            self->animSet = ANIMSET_OVL(5);
            self->animCurFrame = 1;
            SetStep(6);
        }
        break;

    case 6:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018083C, self) == 0) {
            if (g_CutsceneFlags & 0x800) {
                SetStep(7);
            }
        }
        player->animCurFrame = 0;
        break;

    case 7:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018084C, self) == 0) {
            if (g_CutsceneFlags & 0x1000) {
                SetStep(8);
            }
        }
        player->animCurFrame = 0;
        break;

    case 8:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018085C, self) == 0) {
            if (g_CutsceneFlags & 0x2000) {
                SetStep(9);
            }
        }
        player->animCurFrame = 0;
        break;

    case 9:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180864, self) == 0) {
            if (g_CutsceneFlags & 0x4000) {
                SetStep(10);
            }
        }
        player->animCurFrame = 0;
        break;

    case 10:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018086C, self) == 0) {
            if (g_CutsceneFlags & 0x8000) {
                SetStep(11);
            }
        }
        player->animCurFrame = 0;
        break;

    case 11:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018087C, self) == 0) {
            if (g_CutsceneFlags & 0x10000) {
                SetStep(12);
            }
        }
        player->animCurFrame = 0;
        break;

    case 12:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180884, self) == 0) {
            if (g_CutsceneFlags & 0x20000) {
                SetStep(13);
            }
        }
        player->animCurFrame = 0;
        break;

    case 13:
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_8018088C, self) == 0) {
            if (g_CutsceneFlags & 0x40000) {
                SetStep(14);
            }
        }
        player->animCurFrame = 0;
        break;

    case 14:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = 0;
        if (AnimateEntity(D_80180894, self) == 0) {
            self->animCurFrame = 0;
            player->animCurFrame = 7;
            SetStep(15);
        }
        break;

    case 15:
        g_Player.D_80072EFC = 1;
        player->animCurFrame = 7;
        if (g_CutsceneFlags & 4) {
            g_Player.padSim = PAD_LEFT;
            DestroyEntity(self);
            D_8003C8B8 = 1;
        }
        break;
    }
}
