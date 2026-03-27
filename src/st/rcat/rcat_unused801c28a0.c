// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

extern EInit g_EInitSkeleton;

void RCAT_Unused801C28A0(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitSkeleton);
        self->scaleX = 0x120;
        self->scaleY = 0x200;
        self->opacity = 0;
        self->hitboxState = 0;
        self->drawFlags |=
            ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        return;
    }

    self->facingLeft = self[-1].facingLeft;
    self->zPriority = self[-1].zPriority - 1;
    self->animCurFrame = self[-1].animCurFrame;
    self->posX.i.hi = self[-1].posX.i.hi;
    self->posY.i.hi = self[-1].posY.i.hi - 20;

    if (self[-1].entityId != E_SKELETON) {
        DestroyEntity(self);
    }
}
