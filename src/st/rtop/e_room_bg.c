// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

static u8 AnimFrames_80180608[] = {0x40, 0x01, 0xFF, 0x00};
static u8 AnimFrames_8018060C[] = {
    0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00, 0x00,
};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {.animSet = ANIMSET_DRA(6),
     .zPriority = 0x1FA,
     .unk5A = 0,
     .palette = PAL_DRA(0),
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_TPAGE,
     .flags = 0,
     .animFrames = AnimFrames_80180608},
    {.animSet = ANIMSET_OVL(1),
     .zPriority = 0xC0,
     .unk5A = 0x0000,
     .palette = PAL_DRA(0),
     .drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX,
     .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
     .flags = 0,
     .animFrames = AnimFrames_8018060C},
};

extern u16 g_EInitCommon[];

// n.b.! same as rwrp
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

        if (self->params == 1) {
            self->scaleX = self->scaleY = 0x0200;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
