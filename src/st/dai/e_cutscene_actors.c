// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum StageSteps {
    CUTSCENE_INIT = 0,
    CUTSCENE_POSITION_ALUCARD = 1,
    CUTSCENE_PAN_LEFT = 2,
    CUTSCENE_PAN_RIGHT = 3,
};

enum MariaSteps {
    MARIA_INIT = 0,
    MARIA_WAIT = 1,
    MARIA_DEPART = 2,
    MARIA_RUN_1 = 3,
    MARIA_JUMP_ALUCARD = 4,
    MARIA_RUN_2 = 5,
    MARIA_JUMP_EXIT = 6,
    MARIA_DEPARTED = 7,
};

enum OVL_EXPORT(CutsceneFlags) {
    DAI_CUTSCENE_ALUCARD_READY = 1 << 0,
    DAI_CUTSCENE_MARIA_DEPARTING = 1 << 1,
    DAI_CUTSCENE_DIALOGUE_CONCLUDED = 1 << 2,
    DAI_CUTSCENE_CUTSCENE_CONCLUDED = 1 << 3,
};

extern EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern u32 g_CutsceneFlags; // defined by e_cutscene_dialogue

static AnimateEntityFrame unused_anims[] = {
    1,  1,  -1, 0,  1,  2,  -1, 0,  1,  2,  7,  3,  7,  4,  7,  5,  7,  6,
    7,  7,  7,  8,  7,  9,  16, 10, -1, 0,  1,  10, 6,  11, 6,  12, 6,  13,
    16, 14, 10, 15, 10, 14, 10, 15, 32, 14, -1, 0,  1,  14, 4,  16, 4,  17,
    11, 18, -1, 0,  0,  0,  1,  19, -1, 0,  1,  18, -1, 0,  32, 18, 3,  17,
    3,  16, 3,  20, 3,  21, 64, 22, 6,  21, 5,  13, 5,  12, 5,  11, 32, 10,
    -1, 0,  16, 10, 16, 23, 8,  10, -1, 0,  1,  10, 2,  11, 2,  12, 6,  24,
    6,  25, 80, 24, 3,  12, 3,  11, 8,  10, -1, 0,  1,  10, 3,  11, 3,  12,
    3,  13, 3,  14, 6,  27, 16, 26, 32, 27, 3,  14, 3,  13, 3,  12, -1, 0};

static AnimateEntityFrame anim_maria_step[] = {
    {4, 28}, {4, 29}, {4, 30}, {4, 31}, POSE_END};
static AnimateEntityFrame anim_maria_run[] = {
    {2, 32}, {4, 33}, {4, 34}, {4, 35}, {4, 36},
    {4, 37}, {4, 38}, {4, 39}, {2, 32}};
static AnimateEntityFrame anim_maria_jump[] = {
    {8, 40}, {8, 41}, {96, 42}, POSE_END};
static AnimateEntityFrame unused_anim[] = {1, 12, POSE_END};

// Pans the camera until Alucard's screen X coordinate matches the target value
static void CutsceneCameraPan(s16 target) {
    s16 delta = target - g_unkGraphicsStruct.unkC;

    if (delta > 1) { // pan left
        // Appears to be Alucard's X coordinates in screen space
        g_unkGraphicsStruct.unkC++;
    } else if (delta < -1) { // pan right
        g_unkGraphicsStruct.unkC--;
    } else {
        g_unkGraphicsStruct.unkC = target;
    }
}

void OVL_EXPORT(EntityCutsceneStage)(Entity* self) {
    Tilemap* gTilemapPtr;
    Entity* player;
    s16 posScrollX;

    gTilemapPtr = &g_Tilemap;
    player = &PLAYER;

    posScrollX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;

    switch (self->step) {
    case CUTSCENE_INIT:
        InitializeEntity(g_EInitSpawner);
        g_PauseAllowed = false;
        // This seems to pause Alucard, rather than enemies
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
    case CUTSCENE_POSITION_ALUCARD:
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
            g_Player.padSim = PAD_NONE;
            g_CutsceneFlags |= DAI_CUTSCENE_ALUCARD_READY;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;
    case CUTSCENE_PAN_LEFT:
        // Pans camera left to center actors
        CutsceneCameraPan(176);
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & DAI_CUTSCENE_MARIA_DEPARTING) {
            self->step++;
            return;
        }
        break;
    case CUTSCENE_PAN_RIGHT:
        // Pans camera right to recenter on Alucard
        CutsceneCameraPan(128);
        if ((g_unkGraphicsStruct.unkC == 128) &&
            (g_CutsceneFlags & DAI_CUTSCENE_CUTSCENE_CONCLUDED)) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
    }
}

void OVL_EXPORT(EntityCutsceneMaria)(Entity* self) {
    Tilemap* gTilemapPtr;
    Entity* player;
    s16 posScrollX, posScrollY;
    s32 pan;

    gTilemapPtr = &g_Tilemap;
    player = &PLAYER;

    posScrollX = self->posX.i.hi + gTilemapPtr->scrollX.i.hi;
    posScrollY = self->posY.i.hi + gTilemapPtr->scrollY.i.hi;

    switch (self->step) {
    case MARIA_INIT:
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(15);
        self->animCurFrame = 10;
        self->unk5A = 72;
        self->palette = PAL_CUTSCENE;
        break;
    case MARIA_WAIT:
        if (g_CutsceneFlags & DAI_CUTSCENE_DIALOGUE_CONCLUDED) {
            self->step++;
        }
        break;
    case MARIA_DEPART:
        if (!AnimateEntity(anim_maria_step, self)) {
            SetStep(MARIA_RUN_1);
            self->velocityX = FIX(1.5);
        }
        break;
    case MARIA_RUN_1:
        pan = AnimateEntity(anim_maria_run, self);
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
            SetStep(MARIA_JUMP_ALUCARD);
            self->velocityY = FIX(-4);
        }
        break;
    case MARIA_JUMP_ALUCARD: // maria at alucard, jumps up stairs
        AnimateEntity(anim_maria_jump, self);
        self->velocityY += FIX(0.1875);
        MoveEntity();
        if (self->velocityY > 0 && posScrollY > 151) {
            self->posY.i.hi = 151 - gTilemapPtr->scrollY.i.hi;
            self->velocityY = 0;
            SetStep(MARIA_RUN_2);
        }
        break;
    case MARIA_RUN_2: // maria land and run more
        pan = AnimateEntity(anim_maria_run, self);
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
            SetStep(MARIA_JUMP_EXIT);
            self->velocityY = FIX(-4);
            g_CutsceneFlags |= DAI_CUTSCENE_CUTSCENE_CONCLUDED;
        }
        break;
    case MARIA_JUMP_EXIT:
        AnimateEntity(anim_maria_jump, self);
        self->velocityY += FIX(0.1875);
        MoveEntity();
        if (self->velocityY > 0 && posScrollY > 135) {
            self->posY.i.hi = 135 - gTilemapPtr->scrollY.i.hi;
            self->velocityY = 0;
            SetStep(MARIA_DEPARTED);
        }
        break;
    case MARIA_DEPARTED:
        pan = AnimateEntity(anim_maria_run, self);
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
