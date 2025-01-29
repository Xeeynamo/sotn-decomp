// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo3.h"

extern ObjInit D_us_801804CC[];

void func_801A7D64(Entity* self) {
    ObjInit* objInit = &D_us_801804CC[self->params];

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags != 0) {
            self->flags = objInit->flags;
        }
    }

    AnimateEntity(objInit->animFrames, self);
}

#include "../../st/entity_unk_id12.h"
