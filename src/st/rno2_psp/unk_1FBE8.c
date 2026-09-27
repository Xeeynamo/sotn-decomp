// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

void EntityBackgroundBlock(Entity* self) {
    extern ObjInit2 BackgroundBlockInit[];
    ObjInit2* objInit = &BackgroundBlockInit[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = LOHU(objInit->facingLeft);
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->blendMode = objInit->blendMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
