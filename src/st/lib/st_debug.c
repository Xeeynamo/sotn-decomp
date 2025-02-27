// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

extern ObjInit OVL_EXPORT(BackgroundBlockInit)[];
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit* obj = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk5A;
        self->palette = obj->palette;
        self->drawFlags = obj->drawFlags;
        self->drawMode = obj->drawMode;
        if (obj->flags != 0) {
            self->flags = obj->flags;
        }
    }
    AnimateEntity(obj->animFrames, self);
}
