// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

static u8 D_80181474[] = {
    0x04, 0x01, 0x04, 0x02, 0x04, 0x03, 0x04, 0x04, 0x04, 0x05,
    0x05, 0x06, 0x04, 0x07, 0x04, 0x08, 0x04, 0x09, 0x04, 0x0A,
    0x04, 0x0B, 0x05, 0x0C, 0x00, 0x00, 0x00, 0x00};
static u8 D_80181490[] = {0x07, 0x0D, 0x07, 0x0E, 0x07, 0x0F, 0x07, 0x10,
                          0x07, 0x11, 0x07, 0x12, 0x10, 0x13, 0xFF, 0x00};
static u8 D_801814A0[] = {
    0x01, 0x13, 0x03, 0x14, 0x03, 0x15, 0x03, 0x16, 0x03, 0x17,
    0x06, 0x20, 0x10, 0x1F, 0x20, 0x20, 0x03, 0x17, 0x03, 0x16,
    0x03, 0x15, 0x03, 0x14, 0x08, 0x13, 0xFF, 0x00};
static u8 D_801814BC[] = {
    0x10, 0x13, 0x10, 0x21, 0x06, 0x12, 0x08, 0x13, 0xFF, 0x00};
static u8 D_801814C8[] = {
    0x03, 0x13, 0x05, 0x14, 0x05, 0x15, 0x05, 0x16, 0x18, 0x19,
    0x03, 0x18, 0x03, 0x1C, 0x03, 0x1D, 0x58, 0x1E, 0x06, 0x1D,
    0x05, 0x16, 0x05, 0x15, 0x05, 0x14, 0x05, 0x13, 0xFF, 0x00};
static u8 D_801814E8[] = {0x11, 0x13, 0x08, 0x22, 0x17, 0x23, 0x17,
                          0x24, 0x17, 0x25, 0x11, 0x13, 0xFF, 0x00};
static u8 D_801814F8[] = {
    0x20, 0x13, 0x19, 0x22, 0x30, 0x13, 0x19, 0x25, 0x6F, 0x13, 0x06, 0x12,
    0x08, 0x26, 0x08, 0x27, 0x08, 0x28, 0x08, 0x29, 0x20, 0x2A, 0xFF, 0x00};
static u8 D_80181510[] = {
    0x01, 0x2A, 0x09, 0x2B, 0x09, 0x2C, 0x10, 0x2D, 0x30, 0x2C, 0xFF, 0x00};
static u8 D_8018151C[] = {0x20, 0x2C, 0x07, 0x2E, 0x07, 0x2F, 0x30, 0x30, 0x0B,
                          0x31, 0x0E, 0x30, 0x0B, 0x31, 0x40, 0x30, 0xFF, 0x00};
static u8 D_80181530[] = {0x06, 0x2F, 0x06, 0x2E, 0x06, 0x2C, 0xFF, 0x00};
static u8 D_80181538[] = {
    0x02, 0x32, 0x04, 0x33, 0x04, 0x34, 0x05, 0x35, 0x04, 0x36, 0x04, 0x37,
    0x04, 0x38, 0x04, 0x39, 0x04, 0x3A, 0x05, 0x3B, 0x04, 0x3C, 0x04, 0x3D,
    0x02, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00,
    0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01};

void func_801B8E0C(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMaria);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = 1;
        g_Player.padSim = PAD_LEFT;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_R2;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 1:
        if (PLAYER.posX.i.hi < 176) {
            g_Player.padSim = 0;
            self->step++;
        } else {
            g_Player.padSim = 0;
            if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                if (g_Timer & 1) {
                    g_Player.padSim = PAD_R2;
                }
            } else {
                g_Player.padSim = PAD_LEFT;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2:
        if (g_CutsceneFlags & 0x2000) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies != 0) {
                g_unkGraphicsStruct.pauseEnemies = 0;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}

// Maria appearing in the cutscene. Walks in from the door on the left, talks
// to Alucard, and departs to the right.
void EntityMariaNZ0(Entity* self) {
    Entity* redDoor;
    Primitive* prim;
    s32 i;

    if (g_SkipCutscene && (self->step < 12)) {
        if (!(g_CutsceneFlags & 1)) {
            g_CutsceneFlags |= 1;
        }
        SetStep(12);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMaria);
        self->animSet = ANIMSET_OVL(0xF);
        self->animCurFrame = 1;
        self->unk5A = 0x48;
        self->palette = 0x237;
        self->posX.i.hi = -0x10;
        break;
    case 1:
        if (g_CutsceneFlags & 4) {
            // Maria comes through the door on the left, the door is in entity
            // slot 192.
            redDoor = &g_Entities[192];
            g_api.PlaySfxVolPan(SFX_DOOR_OPEN, 0x60, -6);
            for (prim = &g_PrimBuf[redDoor->primIndex], i = 0; prim != NULL;
                 prim = prim->next, i++) {
                if ((i == 1) && !(self->params & FLAG_DEAD)) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                if ((i == 2) && (self->params & FLAG_DEAD)) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                if (i == 0) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
            }
            // This line ends up hiding the rest-state door while the swinging
            // door opens
            redDoor->animCurFrame = 0;
            redDoor->step++;
            self->step++;
        }
        break;
    case 2:
        redDoor = &g_Entities[192];
        if (redDoor->step == 3) {
            self->velocityX = FIX(0.75);
            self->step++;
        }
        break;
    case 3:
        AnimateEntity(D_80181474, self);
        MoveEntity();
        if (self->posX.i.hi >= 25) {
            redDoor = &g_Entities[192];
            redDoor->step = 5;
            g_CutsceneFlags |= 2;
            self->step++;
        }
        break;
    case 4:
        AnimateEntity(D_80181474, self);
        MoveEntity();
        if (self->posX.i.hi > 80) {
            g_CutsceneFlags |= 1;
            SetStep(5);
            self->velocityX = 0;
        }
        break;
    case 5:
        AnimateEntity(D_80181490, self);
        if (g_CutsceneFlags & 8) {
            SetStep(6);
            AnimateEntity(D_801814A0, self);
        }
        break;
    case 6:
        AnimateEntity(D_801814A0, self);
        if (g_CutsceneFlags & 0x10) {
            SetStep(7);
        }
        break;
    case 7:
        AnimateEntity(D_801814BC, self);
        if (g_CutsceneFlags & 0x20) {
            SetStep(8);
        }
        break;
    case 8:
        AnimateEntity(D_801814C8, self);
        if (g_CutsceneFlags & 0x40) {
            SetStep(9);
        }
        break;
    case 9:
        AnimateEntity(D_801814E8, self);
        if (g_CutsceneFlags & 0x80) {
            SetStep(10);
        }
        break;
    case 10:
        AnimateEntity(D_801814F8, self);
        if (g_CutsceneFlags & 0x100) {
            SetStep(11);
        }
        break;
    case 11:
        AnimateEntity(D_80181510, self);
        if (g_CutsceneFlags & 0x200) {
            SetStep(12);
        }
        break;
    case 12:
        AnimateEntity(D_8018151C, self);
        if (g_CutsceneFlags & 0x400) {
            SetStep(13);
        }
        break;
    case 13:
        AnimateEntity(D_80181530, self);
        if (g_CutsceneFlags & 0x800) {
            SetStep(14);
            self->velocityX = FIX(0.75);
        }
        break;
    case 14:
        AnimateEntity(D_80181538, self);
        MoveEntity();
        if (self->posX.i.hi > 224) {
            g_CutsceneFlags |= 0x1000;
            self->step++;
        }
        break;
    case 15:
        AnimateEntity(D_80181538, self);
        MoveEntity();
        if (self->posX.i.hi > 272) {
            DestroyEntity(self);
        }
        break;
    }
}
