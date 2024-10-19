// SPDX-License-Identifier: AGPL-3.0-or-later

extern ObjInit OVL_EXPORT(BackgroundBlockInit)[];
extern u16 g_EInitCommon[];

void EntityBackgroundBlock(Entity* self) {
    ObjInit* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;

        if (objInit->unkC) {
            self->flags = objInit->unkC;
        }

        if (self->params == 1) {
            self->rotX = self->rotY = 0x0200;
        }
    }

    AnimateEntity(objInit->animFrames, self);
}

#include "entity_unk_id12.h"