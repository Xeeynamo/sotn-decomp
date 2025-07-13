// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

static u8 AnimFrames_80180A30[] = {0x10, 0x0B, 0x00, 0x00};
static u8 AnimFrames_80180A34[] = {
    0x08, 0x0C, 0x08, 0x0D, 0x08, 0x0E, 0x08, 0x0F, 0x08, 0x10, 0x00, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x0069,
     .unk5A = 0x0000,
     .palette = PAL_DRA(0),
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_DEFAULT,
     .flags = 0,
     .animFrames = AnimFrames_80180A30},
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0x0069,
     .unk5A = 0x0000,
     .palette = PAL_DRA(0),
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
     .flags = 0,
     .animFrames = AnimFrames_80180A34},
};

extern ObjInit2 OVL_EXPORT(BackgroundBlockInit)[];
extern u16 g_EInitCommon[];

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
