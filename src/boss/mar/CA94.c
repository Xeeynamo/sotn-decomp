// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"

extern EInit OVL_EXPORT(EInitSpawner);
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
extern u32 OVL_EXPORT(CutsceneFlags);
extern s32 OVL_EXPORT(SkipCutscene);

void func_us_8018CA94(Entity* self) {
    Entity* player;
    Tilemap* tilemap;
    s32 pan;

    // n.b.! unused, required for PSP
    tilemap = &g_Tilemap;
    player = &PLAYER;

    if (OVL_EXPORT(SkipCutscene) && self->step < 12) {
        OVL_EXPORT(SetStep)(12);
    }

    switch (self->step) {
    case 0:
        OVL_EXPORT(InitializeEntity)(OVL_EXPORT(EInitSpawner));
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->unk5A = 0x48;
        self->palette = 0x210;
        break;

    case 1:
        if (OVL_EXPORT(CutsceneFlags) & 0x4) {
            self->animCurFrame = 2;
            self->step++;
        }
        break;

    case 2:
        if (OVL_EXPORT(CutsceneFlags) & 0x8) {
            OVL_EXPORT(SetStep)(3);
        }
        break;

    case 3:
        OVL_EXPORT(AnimateEntity)(D_us_80180690, self);
        if (OVL_EXPORT(CutsceneFlags) & 0x10) {
            OVL_EXPORT(SetStep)(4);
        }
        break;

    case 4:
        OVL_EXPORT(AnimateEntity)(D_us_801806A4, self);
        if (OVL_EXPORT(CutsceneFlags) & 0x20) {
            OVL_EXPORT(SetStep)(5);
        }
        break;

    case 5:
        OVL_EXPORT(AnimateEntity)(D_us_801806B8, self);
        if (OVL_EXPORT(CutsceneFlags) & 0x40) {
            OVL_EXPORT(SetStep)(6);
        }
        break;

    case 6:
        self->animCurFrame = 19;
        if (OVL_EXPORT(CutsceneFlags) & 0x80) {
            self->step++;
        }
        break;

    case 7:
        self->animCurFrame = 0x12;
        if (OVL_EXPORT(CutsceneFlags) & 0x100) {
            self->step++;
        }
        break;

    case 8:
        OVL_EXPORT(AnimateEntity)(D_us_801806CC, self);
        if (OVL_EXPORT(CutsceneFlags) & 0x200) {
            OVL_EXPORT(SetStep)(9);
        }
        break;

    case 9:
        OVL_EXPORT(AnimateEntity)(D_us_801806E4, self);
        if (OVL_EXPORT(CutsceneFlags) & 0x400) {
            OVL_EXPORT(SetStep)(10);
        }
        break;

    case 10:
        OVL_EXPORT(AnimateEntity)(D_us_801806EC, self);
        if (OVL_EXPORT(CutsceneFlags) & 0x800) {
            OVL_EXPORT(SetStep)(11);
        }
        break;

    case 11:
        OVL_EXPORT(AnimateEntity)(D_us_80180700, self);
        if (OVL_EXPORT(CutsceneFlags) & 0x1000) {
            OVL_EXPORT(SetStep)(12);
        }
        break;

    case 12:
        if (!OVL_EXPORT(AnimateEntity)(D_us_80180718, self)) {
            OVL_EXPORT(SetStep)(13);
            self->velocityX = FIX(1.5);
        }
        break;

    case 13:
        pan = OVL_EXPORT(AnimateEntity)(D_us_80180724, self);
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

        OVL_EXPORT(MoveEntity)();

        if (self->posX.i.hi > 184) {
            OVL_EXPORT(SetStep)(14);
            self->velocityY = FIX(-4.0);
        }

        break;

    case 14:
        OVL_EXPORT(AnimateEntity)(D_us_80180738, self);
        self->velocityY += FIX(0.1875);
        OVL_EXPORT(MoveEntity)();

        if (self->velocityY > 0 && self->posY.i.hi > 0x83) {
            self->velocityY = 0;
            OVL_EXPORT(SetStep)(15);
        }

        break;

    case 15:
        pan = OVL_EXPORT(AnimateEntity)(D_us_80180724, self);
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

        OVL_EXPORT(MoveEntity)();

        if (self->posX.i.hi > 256) {
            OVL_EXPORT(CutsceneFlags) |= 0x2000;
        }

        if (self->posX.i.hi > 272) {
            DestroyEntity(self);
        }

        break;
    }
}
