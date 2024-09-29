// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

extern u16 D_80180A60[];
extern u8 D_us_80180690[];
extern u8 D_us_801806A4[];
extern u8 D_us_801806B8[];
extern u8 D_us_801806CC[];
extern u8 D_us_801806E4[];
extern u8 D_us_801806EC[];
extern u8 D_us_80180700[];
extern u8 D_us_80180718[];
extern u8 D_us_80180724[];
extern u8 D_us_80180738[];
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
        InitializeEntity(D_80180A60);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->unk5A = 0x48;
        self->palette = PAL_DRA(0x210);
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
        if (pan & 0x80 &&
            (self->animFrameIdx == 3 || self->animFrameIdx == 7)) {

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
        if (pan & 0x80 &&
            (self->animFrameIdx == 3 || self->animFrameIdx == 7)) {

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
