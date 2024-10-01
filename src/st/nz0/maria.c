// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

void func_801B8E0C(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_MariaInit);
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.pauseEnemies = 1;
        g_Player.padSim = PAD_LEFT;
        if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
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
            if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
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
            D_8003C8B8 = 1;
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
void EntityMaria(Entity* self) {
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
        InitializeEntity(g_MariaInit);
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
