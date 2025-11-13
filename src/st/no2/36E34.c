// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_28);
#endif

static u8 D_us_80180E44[] = {
    16, 2, 16, 3, 16, 4, 16, 5, 16, 6, 16, 7, 16, 8, 16, 9, 0, 0};
static u8 D_us_80180E58[] = {8, 10, 8, 11, 0, 0};
static u8 D_us_80180E60[] = {8, 12, 8, 13, 0, 0};
static u8 D_us_80180E68[] = {64, 1,  14, 14, 14, 15, 14, 16, 14, 17,
                             14, 18, 14, 19, 14, 20, 64, 21, -1, 0};
static u8 D_us_80180E7C[] = {4, 21, 8, 18, 48, 16, -1, 0};
static u8 D_us_80180E84[] = {14, 18, 4, 21, -1, 0};
static u8 D_us_80180E8C[] = {3, 15, 3, 14, -1, 0};
static u8 D_us_80180E94[] = {
    14, 22, 14, 23, 14, 24, 14, 25, 14, 26, 14, 27, 14, 28, 14, 29, 0, 0};

void func_us_801B6E34(Entity* self) {
    Entity* tempEntity;
    u8 rand;

    tempEntity = self + 1;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801808B0);
        self->animCurFrame = 0;
        self->zPriority = 0x1E;
        if (self->params & 1) {
            self->palette++;
        }
        if ((self->params & 0x10) == 0) {
            tempEntity = self + 1;
            CreateEntityFromEntity(E_ID(ID_28), self, tempEntity);
            tempEntity->params = self->params + 0x10;
            self->step = 1;
            return;
        }
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_OPACITY;
        self->opacity = 0x80;
        self->zPriority += 1;
        self->step = 8;
        break;

    case 1:
        if (GetDistanceToPlayerX() < 0x40) {
            if (self->ext.et_801B6E34.unk80) {
                rand = Random() & 0xF;
            } else {
                rand = Random() & 1;
            }
            if (!rand) {
                self->ext.et_801B6E34.unk80 |= 1;
                self->ext.et_801B6E34.unk84 = (Random() & 3) * 7;
                if (Random() & 1) {
                    self->ext.et_801B6E34.unk84 = -self->ext.et_801B6E34.unk84;
                }
                self->posX.i.hi += self->ext.et_801B6E34.unk84;
                self->step++;
            } else {
                self->step = 6;
            }
        }
        self->animCurFrame = 0;
        tempEntity->animCurFrame = 0;
        break;

    case 2:
        AnimateEntity(D_us_80180E44, self);
        tempEntity->animCurFrame = self->animCurFrame;
        tempEntity->opacity -= 1;
        if (!tempEntity->opacity) {
            SetStep(3);
        }
        break;

    case 3:
        if (!AnimateEntity(D_us_80180E58, self)) {
            PlaySfxPositional(SFX_DUNGEON_PRISONER_RATTLE);
        }
        tempEntity->animCurFrame = self->animCurFrame + 2;
        tempEntity->zPriority = 0x6A;
        tempEntity->drawMode = DRAW_DEFAULT;
        tempEntity->drawFlags = FLAG_DRAW_DEFAULT;
        if (GetDistanceToPlayerX() > 0x40) {
            tempEntity->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
            tempEntity->drawFlags |= FLAG_DRAW_OPACITY;
            tempEntity->zPriority = self->zPriority + 1;
            SetStep(4);
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180E68, self)) {
                if (Random() & 1) {
                    SetStep(5);
                } else {
                    SetSubStep(1);
                }
            }
            break;

        case 1:
            if (!AnimateEntity(D_us_80180E7C, self)) {
                if (GetDistanceToPlayerX() < 0x40) {
                    SetSubStep(2);
                } else {
                    SetSubStep(3);
                }
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80180E8C, self)) {
                SetStep(3);
            }
            break;

        case 3:
            if (!AnimateEntity(D_us_80180E84, self)) {
                SetStep(5);
            }
            break;
        }
        tempEntity->animCurFrame = 0;
        break;

    case 5:
        AnimateEntity(D_us_80180E94, self);
        tempEntity->animCurFrame = self->animCurFrame;
        tempEntity->opacity++;
        if (tempEntity->opacity > 0x80) {
            self->posX.i.hi -= self->ext.et_801B6E34.unk84;
            SetStep(1);
        }
        break;

    case 6:
        self->animCurFrame = 0;
        tempEntity->animCurFrame = 0;
        if (GetDistanceToPlayerX() > 0x40) {
            self->step = 1;
        }
        break;

    case 8:
        tempEntity = self - 1;
        self->posX.i.hi = tempEntity->posX.i.hi;
        self->posY.i.hi = tempEntity->posY.i.hi;
        break;

    case 16:
#include "../pad2_anim_debug.h"
    }
}
