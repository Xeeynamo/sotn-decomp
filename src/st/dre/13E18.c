// SPDX-License-Identifier: AGPL-3.0-only
#include "dre.h"
#include "sfx.h"

extern s32 D_80180660;

void EntityUnkId1C(Entity* self) {
    Entity* newEntity;
    s32 velX;
    s8* hitbox;
    s32 i;

    if (D_80180660 == 0) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        if (self->step != 5) {
            if (D_80180660 != 0) {
                D_80180660--;
            }
            self->hitboxState = 0;
            self->flags |= FLAG_DEAD;
            g_api.PlaySfxVolPan(0x6D9, 0x54, 0);
            SetStep(5);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804F4);
        self->hitboxState = 0;
        velX =
            self->ext.generic.unkA0 - (self->posX.i.hi + g_Tilemap.scrollX.i.hi)
            << 0x10;
        if (velX < 0) {
            velX += 0x3F;
        }
        self->velocityX = velX >> 6;
        self->ext.generic.unk80.modeS16.unk0 = 0x40;

    case 1:
        MoveEntity();
        newEntity = self->ext.generic.unk9C;
        self->animCurFrame = newEntity->animCurFrame;
        self->facingLeft = newEntity->facingLeft;
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            self->hitboxState = 3;
            SetStep(2);
        }
        break;

    case 2:
        newEntity = self->ext.generic.unk9C;
        self->animCurFrame = newEntity->animCurFrame;
        self->facingLeft = newEntity->facingLeft;
        if (newEntity->ext.generic.unk84.U8.unk1 != 0) {
            self->ext.generic.unk80.modeS16.unk0 = (self->params * 0x30) + 1;
            SetStep(3);
        }
        break;

    case 3:
        self->animCurFrame = 26;
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            SetStep(4);
        }
        break;

    case 4:
        if (self->step_s == 0) {
            self->ext.generic.unk84.S8.unk1 = 0;
            self->step_s++;
        }

        if (AnimateEntity(D_80180780, self) == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 0x120;
            SetStep(3);
        }

        if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
            PlaySfxPositional(0x6E2);
            for (i = 0; i < 2; i++) {
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x1D, self, newEntity);
                    newEntity->params = i;
                    if (i != 0) {
                        newEntity->posX.i.hi -= 2;
                    } else {
                        newEntity->posX.i.hi += 2;
                    }
                    newEntity->ext.generic.unk9C = self;
                    newEntity->posY.i.hi -= 10;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
        }
        if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
            PlaySfxPositional(0x872);
            PlaySfxPositional(0x87C);
            PlaySfxPositional(SFX_FIRE_SHOT);
            self->ext.generic.unk84.S8.unk1 = 1;
        }
        break;

    case 5:
        if (self->step_s == 0) {
            self->ext.generic.unk80.modeS16.unk0 = 0x20;
            self->step_s++;
        }
        if (self->ext.generic.unk80.modeS16.unk0 & 1) {
            self->animSet = 0;
        } else {
            self->animSet = ANIMSET_OVL(1);
        }
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    hitbox = &D_80180830[self->animCurFrame][D_801807F8];
    hitbox--;
    hitbox++;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
}
