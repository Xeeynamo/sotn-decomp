// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

static u8 anim0[] = {4, 1, 4, 2, 4, 3, 4,  4, 4,  5, 5,  6, 4,
                     7, 4, 8, 4, 9, 4, 10, 4, 11, 5, 12, 0, 0};
static u8 anim1[] = {7, 13, 7, 14, 7, 15, 7, 16, 7, 17, 7, 18, 16, 19, -1, 0};
static u8 anim2[] = {1,  19, 3, 20, 3, 21, 3, 22, 3, 23, 6, 32, 16, 31,
                     32, 32, 3, 23, 3, 22, 3, 21, 3, 20, 8, 19, -1, 0};
static u8 anim3[] = {16, 19, 16, 33, 6, 18, 8, 19, -1, 0};
static u8 anim4[] = {3,  19, 5,  20, 5,  21, 5,  22, 24, 25, 3,  24, 3,  28, 3,
                     29, 88, 30, 6,  29, 5,  22, 5,  21, 5,  20, 5,  19, -1, 0};
static u8 anim5[] = {17, 19, 8, 34, 23, 35, 23, 36, 23, 37, 17, 19, -1, 0};
static u8 anim6[] = {32, 19, 25, 34, 48, 19, 25, 37, 111, 19, 6,  18,
                     8,  38, 8,  39, 8,  40, 8,  41, 32,  42, -1, 0};
static u8 anim7[] = {1, 42, 9, 43, 9, 44, 16, 45, 48, 44, -1, 0};
static u8 anim8[] = {32, 44, 7,  46, 7,  47, 48, 48, 11,
                     49, 14, 48, 11, 49, 64, 48, -1, 0};
static u8 anim9[] = {6, 47, 6, 46, 6, 44, -1, 0};
static u8 anim10[] = {2, 50, 4, 51, 4, 52, 5, 53, 4, 54, 4, 55, 4, 56,
                      4, 57, 4, 58, 5, 59, 4, 60, 4, 61, 2, 50, 0, 0};

extern u32 g_SkipCutscene;
extern u32 g_CutsceneFlags;

void func_801B8E0C(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = 1;
        g_Player.padSim = PAD_LEFT;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        }
        g_Player.demo_timer = 1;
        break;

    case 1:
        if (player->posX.i.hi < 0xB0) {
            g_Player.padSim = 0;
            self->step++;
        } else {
            g_Player.padSim = 0;
            if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                if (g_Timer & 1) {
                    g_Player.padSim = PAD_WOLF;
                }
            } else {
                g_Player.padSim = PAD_LEFT;
            }
        }
        g_Player.demo_timer = 1;
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
        g_Player.demo_timer = 1;
        break;
    }
}

// Maria appearing in the cutscene. Walks in from the door on the left, talks
// to Alucard, and departs to the right.
void EntityMariaNZ0(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* redDoor;
    Primitive* prim;
    s32 i;

    if (g_SkipCutscene && self->step < 12) {
        if (!(g_CutsceneFlags & 1)) {
            g_CutsceneFlags |= 1;
        }
        SetStep(12);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->animSet = ANIMSET_OVL(0xF);
        self->animCurFrame = 1;
        self->unk5A = 0x48;
        self->palette = PAL_UNK_237;
        self->posX.i.hi = -0x10;
        break;
    case 1:
        if (g_CutsceneFlags & 4) {
            // Maria comes through the door on the left, the door is in entity
            // slot 192.
            redDoor = &g_Entities[192];
            g_api.PlaySfxVolPan(SFX_DOOR_OPEN, 0x60, -6);
            prim = &g_PrimBuf[redDoor->primIndex];
            for (i = 0; prim != NULL; i++, prim = prim->next) {
                if (i == 1 && !(self->params & FLAG_DEAD)) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                if (i == 2 && (self->params & FLAG_DEAD)) {
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
        redDoor = &g_Entities[192];
        AnimateEntity(anim0, self);
        MoveEntity();
        if (self->posX.i.hi > 0x18) {
            g_CutsceneFlags |= 2;
            redDoor->step = 5;
            self->step++;
        }
        break;
    case 4:
        AnimateEntity(anim0, self);
        MoveEntity();
        if (self->posX.i.hi > 0x50) {
            g_CutsceneFlags |= 1;
            SetStep(5);
            self->velocityX = 0;
        }
        break;
    case 5:
        AnimateEntity(anim1, self);
        if (g_CutsceneFlags & 8) {
            SetStep(6);
            AnimateEntity(anim2, self);
        }
        break;
    case 6:
        AnimateEntity(anim2, self);
        if (g_CutsceneFlags & 0x10) {
            SetStep(7);
        }
        break;
    case 7:
        AnimateEntity(anim3, self);
        if (g_CutsceneFlags & 0x20) {
            SetStep(8);
        }
        break;
    case 8:
        AnimateEntity(anim4, self);
        if (g_CutsceneFlags & 0x40) {
            SetStep(9);
        }
        break;
    case 9:
        AnimateEntity(anim5, self);
        if (g_CutsceneFlags & 0x80) {
            SetStep(10);
        }
        break;
    case 10:
        AnimateEntity(anim6, self);
        if (g_CutsceneFlags & 0x100) {
            SetStep(11);
        }
        break;
    case 11:
        AnimateEntity(anim7, self);
        if (g_CutsceneFlags & 0x200) {
            SetStep(12);
        }
        break;
    case 12:
        AnimateEntity(anim8, self);
        if (g_CutsceneFlags & 0x400) {
            SetStep(13);
        }
        break;
    case 13:
        AnimateEntity(anim9, self);
        if (g_CutsceneFlags & 0x800) {
            SetStep(14);
            self->velocityX = FIX(0.75);
        }
        break;
    case 14:
        AnimateEntity(anim10, self);
        MoveEntity();
        if (self->posX.i.hi > 0xE0) {
            g_CutsceneFlags |= 0x1000;
            self->step++;
        }
        break;
    case 15:
        AnimateEntity(anim10, self);
        MoveEntity();
        if (self->posX.i.hi > 0x110) {
            DestroyEntity(self);
        }
        break;
    }
}
