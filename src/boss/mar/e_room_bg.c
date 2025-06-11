// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"

extern u16 g_EInitCommon[];

static u8 D_us_801804B0[] = {0x40, 0x2F, 0xFF, 0x00};
ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {0x8001, 0x007F, 0, 0, 0x0000, 0x00, 0x30, 0x00000000, D_us_801804B0},
};

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = LOH(objInit->facingLeft);
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
