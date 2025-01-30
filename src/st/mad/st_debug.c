// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"
#include "sfx.h"

void func_8018E5AC(Entity* self) {
    s32 temp_v0;
    ObjInit* objInit = &D_8018056C[self->params];

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        temp_v0 = objInit->flags;
        if (temp_v0 != 0) {
            self->flags = temp_v0;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}

#include "../entity_unk_id12.h"
