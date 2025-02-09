// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

extern ObjInit2 BO4_BackgroundBlockInit[];
extern u16 g_EInitCommon[];
void EntityBackgroundBlock(Entity* self) {
    ObjInit2* objInit = &BO4_BackgroundBlockInit[self->params];

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        // this is the same as boss/mar, maybe a boss thing?
        self->unk5A = LOH(objInit->facingLeft); // bug?
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
