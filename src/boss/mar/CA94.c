// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"

extern EInit g_EInitSpawner;

AnimateEntityFrame D_us_80180688[] = {
    POSE(1, 1, 0), POSE_END, POSE(1, 2, 0), POSE_END};
static AnimateEntityFrame D_us_80180690[] = {
    POSE(1, 2, 0), POSE(7, 3, 0), POSE(7, 4, 0), POSE(7, 5, 0),   POSE(7, 6, 0),
    POSE(7, 7, 0), POSE(7, 8, 0), POSE(7, 9, 0), POSE(16, 10, 0), POSE_END};
static AnimateEntityFrame D_us_801806A4[] = {
    POSE(1, 10, 0),  POSE(6, 11, 0),  POSE(6, 12, 0),  POSE(6, 13, 0),
    POSE(16, 14, 0), POSE(10, 15, 0), POSE(10, 14, 0), POSE(10, 15, 0),
    POSE(32, 14, 0), POSE_END};
static AnimateEntityFrame D_us_801806B8[] = {
    POSE(1, 14, 0), POSE(4, 16, 0), POSE(4, 17, 0), POSE(11, 18, 0), POSE_END,
    POSE_LOOP(0),   POSE(1, 19, 0), POSE_END,       POSE(1, 18, 0),  POSE_END};
static AnimateEntityFrame D_us_801806CC[] = {
    POSE(32, 18, 0), POSE(3, 17, 0),  POSE(3, 16, 0),  POSE(3, 20, 0),
    POSE(3, 21, 0),  POSE(64, 22, 0), POSE(6, 21, 0),  POSE(5, 13, 0),
    POSE(5, 12, 0),  POSE(5, 11, 0),  POSE(32, 10, 0), POSE_END};
static AnimateEntityFrame D_us_801806E4[] = {
    POSE(16, 10, 0), POSE(16, 23, 0), POSE(8, 10, 0), POSE_END};
static AnimateEntityFrame D_us_801806EC[] = {
    POSE(1, 10, 0), POSE(2, 11, 0),  POSE(2, 12, 0), POSE(6, 24, 0),
    POSE(6, 25, 0), POSE(80, 24, 0), POSE(3, 12, 0), POSE(3, 11, 0),
    POSE(8, 10, 0), POSE_END};
static AnimateEntityFrame D_us_80180700[] = {
    POSE(1, 10, 0), POSE(3, 11, 0), POSE(3, 12, 0),  POSE(3, 13, 0),
    POSE(3, 14, 0), POSE(6, 27, 0), POSE(16, 26, 0), POSE(32, 27, 0),
    POSE(3, 14, 0), POSE(3, 13, 0), POSE(3, 12, 0),  POSE_END};
static AnimateEntityFrame D_us_80180718[] = {
    POSE(4, 28, 0), POSE(4, 29, 0), POSE(4, 30, 0),
    POSE(4, 31, 0), POSE_END,       POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180724[] = {
    POSE(2, 32, 0), POSE(4, 33, 0), POSE(4, 34, 0), POSE(4, 35, 0),
    POSE(4, 36, 0), POSE(4, 37, 0), POSE(4, 38, 0), POSE(4, 39, 0),
    POSE(2, 32, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180738[] = {
    POSE(8, 40, 0), POSE(8, 41, 0), POSE(96, 42, 0),
    POSE_END,       POSE(1, 12, 0), POSE_END};

extern u32 g_CutsceneFlags;
extern s32 g_SkipCutscene;

void func_us_8018CA94(Entity* self) {
    Entity* player;
    Tilemap* tilemap;
    s32 pan;

    // n.b.! unused, required for PSP
    tilemap = &g_Tilemap;
    player = &PLAYER;

    if (g_SkipCutscene && self->step < 12) {
        SetStep(12);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->unk5A = 0x48;
        self->palette = PAL_MARIA;
        break;

    case 1:
        if (g_CutsceneFlags & 0x4) {
            self->animCurFrame = 2;
            self->step++;
        }
        break;

    case 2:
        if (g_CutsceneFlags & 0x8) {
            SetStep(3);
        }
        break;

    case 3:
        AnimateEntity(D_us_80180690, self);
        if (g_CutsceneFlags & 0x10) {
            SetStep(4);
        }
        break;

    case 4:
        AnimateEntity(D_us_801806A4, self);
        if (g_CutsceneFlags & 0x20) {
            SetStep(5);
        }
        break;

    case 5:
        AnimateEntity(D_us_801806B8, self);
        if (g_CutsceneFlags & 0x40) {
            SetStep(6);
        }
        break;

    case 6:
        self->animCurFrame = 19;
        if (g_CutsceneFlags & 0x80) {
            self->step++;
        }
        break;

    case 7:
        self->animCurFrame = 0x12;
        if (g_CutsceneFlags & 0x100) {
            self->step++;
        }
        break;

    case 8:
        AnimateEntity(D_us_801806CC, self);
        if (g_CutsceneFlags & 0x200) {
            SetStep(9);
        }
        break;

    case 9:
        AnimateEntity(D_us_801806E4, self);
        if (g_CutsceneFlags & 0x400) {
            SetStep(10);
        }
        break;

    case 10:
        AnimateEntity(D_us_801806EC, self);
        if (g_CutsceneFlags & 0x800) {
            SetStep(11);
        }
        break;

    case 11:
        AnimateEntity(D_us_80180700, self);
        if (g_CutsceneFlags & 0x1000) {
            SetStep(12);
        }
        break;

    case 12:
        if (!AnimateEntity(D_us_80180718, self)) {
            SetStep(13);
            self->velocityX = FIX(1.5);
        }
        break;

    case 13:
        pan = AnimateEntity(D_us_80180724, self);
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

        if (self->posX.i.hi > 184) {
            SetStep(14);
            self->velocityY = FIX(-4.0);
        }

        break;

    case 14:
        AnimateEntity(D_us_80180738, self);
        self->velocityY += FIX(0.1875);
        MoveEntity();

        if (self->velocityY > 0 && self->posY.i.hi > 0x83) {
            self->velocityY = 0;
            SetStep(15);
        }

        break;

    case 15:
        pan = AnimateEntity(D_us_80180724, self);
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

        if (self->posX.i.hi > 256) {
            g_CutsceneFlags |= 0x2000;
        }

        if (self->posX.i.hi > 272) {
            DestroyEntity(self);
        }

        break;
    }
}
