// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"
/*
This file contains the function(s) needed to "set the stage" for the cutscene.
This will be very overlay specific, which is likely why it is in a separate file
from EntityCutscene.
This file contains a function or functions that bring Alucard back to human form
and adjust the camera to center the view, among other things.
*/

extern u32 g_CutsceneFlags;

// This appears to be unused and deadstripped on PSP
static u8 unused[] = {
    0x01, 0x01, 0xFF, 0x00, 0x01, 0x02, 0xFF, 0x00, 0x01, 0x02, 0x07, 0x03,
    0x07, 0x04, 0x07, 0x05, 0x07, 0x06, 0x07, 0x07, 0x07, 0x08, 0x07, 0x09,
    0x10, 0x0A, 0xFF, 0x00, 0x01, 0x0A, 0x06, 0x0B, 0x06, 0x0C, 0x06, 0x0D,
    0x10, 0x0E, 0x0A, 0x0F, 0x0A, 0x0E, 0x0A, 0x0F, 0x20, 0x0E, 0xFF, 0x00,
    0x01, 0x0E, 0x04, 0x10, 0x04, 0x11, 0x0B, 0x12, 0xFF, 0x00, 0x00, 0x00,
    0x01, 0x13, 0xFF, 0x00, 0x01, 0x12, 0xFF, 0x00, 0x20, 0x12, 0x03, 0x11,
    0x03, 0x10, 0x03, 0x14, 0x03, 0x15, 0x40, 0x16, 0x06, 0x15, 0x05, 0x0D,
    0x05, 0x0C, 0x05, 0x0B, 0x20, 0x0A, 0xFF, 0x00, 0x10, 0x0A, 0x10, 0x17,
    0x08, 0x0A, 0xFF, 0x00, 0x01, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x06, 0x18,
    0x06, 0x19, 0x50, 0x18, 0x03, 0x0C, 0x03, 0x0B, 0x08, 0x0A, 0xFF, 0x00,
    0x01, 0x0A, 0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0x03, 0x0E, 0x06, 0x1B,
    0x10, 0x1A, 0x20, 0x1B, 0x03, 0x0E, 0x03, 0x0D, 0x03, 0x0C, 0xFF, 0x00};

static u8 D_us_80181024[] = {
    0x04, 0x1C, 0x04, 0x1D, 0x04, 0x1E, 0x04, 0x1F, 0xFF, 0x00};
static u8 D_us_80181030[] = {
    0x02, 0x20, 0x04, 0x21, 0x04, 0x22, 0x04, 0x23, 0x04,
    0x24, 0x04, 0x25, 0x04, 0x26, 0x04, 0x27, 0x02, 0x20};
static u8 D_us_80181044[] = {0x08, 0x28, 0x08, 0x29, 0x60, 0x2A, 0xFF, 0x00};
// This appears to be unused and deadstripped on PSP
static u8 unused_too[] = {0x01, 0x0C, 0xFF, 0x00};

void func_801961DC(s16 arg0) {
    s16 temp_v0 = arg0 - g_unkGraphicsStruct.unkC;

    if (temp_v0 > 1) {
        g_unkGraphicsStruct.unkC++;
    } else if (temp_v0 < -1) {
        g_unkGraphicsStruct.unkC--;
    } else {
        g_unkGraphicsStruct.unkC = arg0;
    }
}

void func_us_801C5920(Entity* self) {
    Tilemap* gTilemap;
    Entity* gEntities;
    s16 posScrollX;

    gTilemap = &g_Tilemap;
    gEntities = g_Entities;

    posScrollX = gEntities->posX.i.hi + g_Tilemap.scrollX.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            g_Player.padSim = PAD_BAT;
        } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#ifdef VERSION_PSP
            g_Player.padSim = PAD_NONE;
#else
            g_Player.padSim = PAD_MIST;
#endif
        } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        } else {
            g_Player.padSim = PAD_LEFT;
        }
        g_Player.demo_timer = 1;
        break;
    case 1:
        if (posScrollX > 0x170) {
            if (g_Player.status &
                (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_MIST_FORM |
                 PLAYER_STATUS_BAT_FORM)) {
                g_Player.padSim = PAD_NONE;
                if (g_Timer & 1) {
                    if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                        g_Player.padSim = PAD_BAT;
                    } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
                        g_Player.padSim = PAD_MIST;
                    } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                        g_Player.padSim = PAD_WOLF;
                    }
                }
            } else {
                g_Player.padSim = PAD_LEFT;
            }
        } else {
            gEntities->posX.i.hi = 0x170 - g_Tilemap.scrollX.i.hi;
            g_Player.padSim = 0;
            g_CutsceneFlags |= 1;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;
    case 2:
        func_801961DC(0xB0);
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 2) {
            self->step++;
            return;
        }
        break;
    case 3:
        func_801961DC(0x80);
        if ((g_unkGraphicsStruct.unkC == 0x80) && (g_CutsceneFlags & 8)) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
    }
}

void func_us_801C5B88(Entity* self) {
    Tilemap* gTilemap;
    Entity* gEntities;
    s16 posScrollX, posScrollY;
    s32 pan;

    gTilemap = &g_Tilemap;
    gEntities = g_Entities;

    posScrollX = self->posX.i.hi + gTilemap->scrollX.i.hi;
    posScrollY = self->posY.i.hi + gTilemap->scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(15);
        self->animCurFrame = 10;
        self->unk5A = 72;
        self->palette = PAL_UNK251;
        break;
    case 1:
        if (g_CutsceneFlags & 4) {
            self->step++;
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_80181024, self)) {
            SetStep(3);
            self->velocityX = FIX(1.5);
        }
        break;
    case 3:
        pan = AnimateEntity(D_us_80181030, self);
        if (pan & 0x80 && (self->pose == 3 || self->pose == 7)) {
            pan = (self->posX.i.hi - 120) / 16;
            if (pan < -8) {
                pan = -8;
            }
            if (pan > 8) {
                pan = 8;
            }
            g_api.PlaySfxVolPan(SFX_STOMP_SOFT_B, 80, pan);
        }
        MoveEntity();
        if (posScrollX > 368) {
            SetStep(4);
            self->velocityY = FIX(-4);
        }
        break;
    case 4:
        AnimateEntity(D_us_80181044, self);
        self->velocityY += FIX(0.1875);
        MoveEntity();
        if (self->velocityY > 0 && posScrollY > 151) {
            self->posY.i.hi = 151 - gTilemap->scrollY.i.hi;
            self->velocityY = FIX(0);
            SetStep(5);
        }
        break;
    case 5:
        pan = AnimateEntity(D_us_80181030, self);
        if (pan & 0x80 && (self->pose == 3 || self->pose == 7)) {
            pan = (self->posX.i.hi - 120) / 16;
            if (pan < -8) {
                pan = -8;
            }
            if (pan > 8) {
                pan = 8;
            }
            g_api.PlaySfxVolPan(SFX_STOMP_SOFT_B, 80, pan);
        }
        MoveEntity();
        if (posScrollX > 448) {
            SetStep(6);
            self->velocityY = FIX(-4);
            g_CutsceneFlags |= 8;
        }
        break;
    case 6:
        AnimateEntity(D_us_80181044, self);
        self->velocityY += FIX(0.1875);
        MoveEntity();
        if (self->velocityY > 0 && posScrollY > 135) {
            self->posY.i.hi = 0x87 - gTilemap->scrollY.i.hi;
            self->velocityY = FIX(0);
            SetStep(7);
        }
        break;
    case 7:
        pan = AnimateEntity(D_us_80181030, self);
        if (pan & 0x80 && (self->pose == 3 || self->pose == 7)) {
            pan = (self->posX.i.hi - 120) / 16;
            if (pan < -8) {
                pan = -8;
            }
            if (pan > 8) {
                pan = 8;
            }
            g_api.PlaySfxVolPan(SFX_STOMP_SOFT_B, 0x50, pan);
        }
        MoveEntity();
        if (posScrollX > 544) {
            DestroyEntity(self);
        }
        break;
    }
}
