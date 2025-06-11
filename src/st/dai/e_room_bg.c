// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

extern u16 g_EInitCommon[];

static u8 AnimFrames_80180AC4[] = {0x40, 0x01, 0xFF, 0x00};
ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {{
    .animSet = ANIMSET_DRA(6),
    .zPriority = 0x1FA,
    .facingLeft = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_DEFAULT,
    .drawMode = DRAW_TPAGE,
    .animFrames = AnimFrames_80180AC4,
}};

void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
#ifdef VERSION_PSP
        self->unk5A = LOHU(objInit->facingLeft);
#else
        self->unk5A = LOH(objInit->facingLeft);
#endif
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
