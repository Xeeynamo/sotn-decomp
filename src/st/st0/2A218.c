// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

static void func_801AA218(s16 arg0) {
    s16 temp_a1 = ((0xE0 - arg0) / 2) + 0x80;
    s16 temp_v1 = temp_a1 - g_unkGraphicsStruct.unkC;

    if (temp_v1 > 2) {
        g_unkGraphicsStruct.unkC += 2;
    } else if (temp_v1 < -2) {
        g_unkGraphicsStruct.unkC -= 2;
    } else {
        g_unkGraphicsStruct.unkC = temp_a1;
    }
}

extern s32 g_SkipCutscene;
extern u32 g_CutsceneFlags;
extern s32 g_IsCutsceneDone;
static u8 D_80180830[] = {0x08, 0x05, 0x08, 0x06, 0x08, 0x07, 0xFF, 0x00};

#ifndef VERSION_PSP
// This appears to be an unused animation and deadstripped on PSP
static u8 unused[] = {0x20, 0x01, 0xFF, 0x00};
#endif

static u8 D_8018083C[] = {0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05,
                          0x02, 0x06, 0x02, 0x05, 0xFF, 0x00, 0x00, 0x00};
static u8 D_8018084C[] = {0x02, 0x04, 0x02, 0x03, 0x20, 0x02, 0x03, 0x0D,
                          0x03, 0x09, 0x02, 0x08, 0x02, 0x07, 0xFF, 0x00};
static u8 D_8018085C[] = {0x02, 0x08, 0x02, 0x09, 0xFF, 0x00, 0x00, 0x00};
static u8 D_80180864[] = {0x06, 0x0D, 0x06, 0x0A, 0x02, 0x01, 0xFF, 0x00};
static u8 D_8018086C[] = {0x06, 0x0A, 0x06, 0x01, 0x08, 0x0A, 0x08, 0x01,
                          0x08, 0x0A, 0x08, 0x01, 0x08, 0x0A, 0xFF, 0x00};
static u8 D_8018087C[] = {0x06, 0x0D, 0x06, 0x09, 0xFF, 0x00, 0x00, 0x00};
static u8 D_80180884[] = {0x02, 0x08, 0x02, 0x07, 0xFF, 0x00, 0x00, 0x00};
static u8 D_8018088C[] = {0x06, 0x0C, 0x06, 0x0B, 0xFF, 0x00, 0x00, 0x00};
static u8 D_80180894[] = {0x06, 0x0C, 0x30, 0x0A, 0x10, 0x01, 0xFF, 0x00};

void EntityCutscene(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    u16 posX;

    self->posX.i.hi = player->posX.i.hi;
    self->posY.i.hi = player->posY.i.hi - 1;

    if ((self->step != 14) && g_SkipCutscene && g_IsCutsceneDone &&
        (self->step > 4)) {
        self->step = 15;
        self->animSet = ANIMSET_DRA(0);
        self->animCurFrame = 0;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCutscene);
        self->unk5A = 0x46;
        self->palette = 0x120;
        break;

    case 1:
        if (self->step_s) {
            if ((player->step <= 2) || (player->step == 25)) {
                posX = player->posX.i.hi + tilemap->scrollX.i.hi;
                if (posX > 0x8000) {
                    posX = 0;
                }
                if (posX > 0xA0) {
                    g_Player.padSim = PAD_LEFT;
                } else {
                    g_Player.padSim = PAD_RIGHT;
                }
                g_Entities[1].ext.entSlot1.unk0 = 1;
                g_Player.D_80072EFC = 0xFF;
                func_801AA218(posX);
                SetStep(2);
            }
        } else {
            if ((player->posX.i.hi + tilemap->scrollX.i.hi) < 0xE1) {
                g_PauseAllowed = false;
                self->step_s++;
            }
        }
        break;

    case 2:
        posX = player->posX.i.hi + tilemap->scrollX.i.hi;
        if (posX > 0x8000) {
            posX = 0;
        }

        if ((g_Player.padSim == PAD_LEFT) && (posX <= 0xA0) ||
            (g_Player.padSim == PAD_RIGHT) && (posX >= 0x9F)) {
            g_Player.D_80072EFC = 1;
            g_Player.padSim = PAD_LEFT;
            self->ext.utimer.t = 0x18;
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
        if (!--self->ext.utimer.t) {
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
            g_PauseAllowed = true;
        }
        break;
    }
}
