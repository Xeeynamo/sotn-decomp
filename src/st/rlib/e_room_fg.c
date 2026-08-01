// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

extern EInit g_EInitCommon;
extern ObjInit D_us_801816D8[];

void EntityRoomForeground(Entity* self) {
    ObjInit* objInit = &D_us_801816D8[self->params];

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->blendMode = objInit->blendMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
        if (self->params >= 5) {
            self->drawFlags |= 4;
            self->rotate = 0x800;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
