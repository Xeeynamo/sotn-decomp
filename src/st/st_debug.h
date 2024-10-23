// SPDX-License-Identifier: AGPL-3.0-or-later

extern ObjInit g_eBackgroundBlockInit[];
extern u16 g_eInitGeneric2[];

// params: Index of ObjInit to use
//         (== 1) Use a different hardcoded rotY and rotX value
void EntityBackgroundBlock(Entity* self) {
    ObjInit* objInit = &g_eBackgroundBlockInit[self->params];
    if (!self->step) {
        InitializeEntity(g_eInitGeneric2);
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
