// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

extern ObjInit2 D_80180C10[];
extern u16 g_EInitCommon[];
void func_us_8018AC0C(Entity* self) {
    ObjInit2* objInit = &D_80180C10[self->params];

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = LOH(objInit->facingLeft); // bug?
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            self->flags = objInit->unkC;
        }
    }

    AnimateEntity(objInit->animFrames, self);
}

#include "../../st/entity_unk_id12.h"
