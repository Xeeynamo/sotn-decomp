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
    1, 1,  255, 0,  1,  2,  255, 0,  1,   2,  7,   3,  7,  4,  7,   5,
    7, 6,  7,   7,  7,  8,  7,   9,  16,  10, 255, 0,  1,  10, 6,   11,
    6, 12, 6,   13, 16, 14, 10,  15, 10,  14, 10,  15, 32, 14, 255, 0,
    1, 14, 4,   16, 4,  17, 11,  18, 255, 0,  0,   0,  1,  19, 255, 0,
    1, 18, 255, 0,  32, 18, 3,   17, 3,   16, 3,   20, 3,  21, 64,  22,
    6, 21, 5,   13, 5,  12, 5,   11, 32,  10, 255, 0,  16, 10, 16,  23,
    8, 10, 255, 0,  1,  10, 2,   11, 2,   12, 6,   24, 6,  25, 80,  24,
    3, 12, 3,   11, 8,  10, 255, 0,  1,   10, 3,   11, 3,  12, 3,   13,
    3, 14, 6,   27, 16, 26, 32,  27, 3,   14, 3,   13, 3,  12, 255, 0};

static u8 D_us_80181024[] = {4, 28, 4, 29, 4, 30, 4, 31, 255, 0};
static u8 D_us_80181030[] = {
    2, 32, 4, 33, 4, 34, 4, 35, 4, 36, 4, 37, 4, 38, 4, 39, 2, 32};
static u8 D_us_80181044[] = {8, 40, 8, 41, 96, 42, 255, 0};
// This appears to be unused and deadstripped on PSP
static u8 unused_too[] = {1, 12, 255, 0};

static void func_801961DC(s16 arg0) {
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
    Tilemap* gTilemapPtr;
    Entity* player;
    s16 posScrollX;

    gTilemapPtr = &g_Tilemap;
    player = &PLAYER;

    posScrollX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;

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
        if (posScrollX > 368) {
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
            player->posX.i.hi = 368 - g_Tilemap.scrollX.i.hi;
            g_Player.padSim = 0;
            g_CutsceneFlags |= 1;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;
    case 2:
        func_801961DC(176);
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 2) {
            self->step++;
            return;
        }
        break;
    case 3:
        func_801961DC(128);
        if ((g_unkGraphicsStruct.unkC == 128) && (g_CutsceneFlags & 8)) {
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
    Tilemap* gTilemapPtr;
    Entity* player;
    s16 posScrollX, posScrollY;
    s32 pan;

    gTilemapPtr = &g_Tilemap;
    player = &PLAYER;

    posScrollX = self->posX.i.hi + gTilemapPtr->scrollX.i.hi;
    posScrollY = self->posY.i.hi + gTilemapPtr->scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(15);
        self->animCurFrame = 10;
        self->unk5A = 72;
        self->palette = PAL_CUTSCENE;
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
            self->posY.i.hi = 151 - gTilemapPtr->scrollY.i.hi;
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
            self->posY.i.hi = 135 - gTilemapPtr->scrollY.i.hi;
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
            g_api.PlaySfxVolPan(SFX_STOMP_SOFT_B, 80, pan);
        }
        MoveEntity();
        if (posScrollX > 544) {
            DestroyEntity(self);
        }
        break;
    }
}
