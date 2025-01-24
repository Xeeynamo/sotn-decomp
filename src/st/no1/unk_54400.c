// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

void func_us_801D4400(Entity* self) {
    Entity* tempEntity;

    tempEntity = self->ext.et_801D4400.unk7C;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B0C);
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->rotZ = 0;
        break;

    case 1:
        if (tempEntity->flags & FLAG_DEAD) {
            DestroyEntity(self);
        }
        self->step++;
        break;

    case 2:
        self->posX.i.hi = tempEntity->posX.i.hi;
        self->posY.i.hi = tempEntity->posY.i.hi - 0x10;
        if (self->facingLeft) {
            self->posX.i.hi += 0x28;
            self->velocityX = FIX(6.0);
        } else {
            self->posX.i.hi -= 0x28;
            self->velocityX = FIX(-6.0);
        }
        self->animCurFrame = 0x36;
        self->hitboxState = 1;
        self->step++;
        break;

    case 3:
        self->velocityY += 0x400;
        self->rotZ = ratan2(-self->velocityY, self->velocityX) & 0xFFFF;
        if (!self->facingLeft) {
            self->rotZ = 0x800 - self->rotZ;
        }
        MoveEntity();
        break;
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_54400", func_us_801D4558);

INCLUDE_ASM("st/no1/nonmatchings/unk_54400", func_us_801D4950);
