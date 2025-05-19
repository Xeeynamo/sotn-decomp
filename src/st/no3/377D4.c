// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

void EntityBackgroundBlock(Entity* self) {
    ObjInit2* objInit = &D_80180BFC[self->params];

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->facingLeft = objInit->facingLeft;
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

#include "../entity_lock_camera.h"
