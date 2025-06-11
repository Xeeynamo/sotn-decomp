// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

extern u16 g_EInitCommon[];

static u8 D_80180488[] = {0x40, 0x01, 0xFF, 0x00};
static u8 D_8018048C[] = {0x40, 0x07, 0xFF, 0x00};
ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {.animSet = ANIMSET_OVL(2),
     .zPriority = 129,
     .unk5A = 0,
     .palette = PAL_DRA(0),
     .drawFlags = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = D_8018048C},
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

        if (self->params == 1) {
            self->scaleX = self->scaleY = 0x0200;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
