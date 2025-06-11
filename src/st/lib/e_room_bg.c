// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

extern u16 g_EInitCommon[];

static u8 AnimFrames_09298898[] = {0x40, 0x01, 0xFF, 0x00};
static u8 AnimFrames_092988A0[] = {0x40, 0x01, 0xFF, 0x00};
static u8 AnimFrames_092988A8[] = {0x40, 0x19, 0xFF, 0x00};
static u8 AnimFrames_092988B0[] = {
    0x04, 0x1A, 0x04, 0x1B, 0x04, 0x1C, 0x04, 0x1D, 0x04, 0x1E, 0x00, 0x00,
};
static u8 AnimFrames_092988C0[] = {
    0x03, 0x1F, 0x03, 0x20, 0x03, 0x21, 0x03, 0x20, 0x00, 0x00, 0x00, 0x00,
};
static u8 AnimFrames_092988D0[] = {0x40, 0x22, 0xFF, 0x00};
static u8 AnimFrames_092988D8[] = {0x40, 0x13, 0xFF, 0x00};
static u8 AnimFrames_092988E0[] = {0x40, 0x14, 0xFF, 0x00};
ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x1FA,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_DRA(0),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_09298898,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x81,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_DRA(0x210),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_092988A0,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x81,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_DRA(0x210),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_092988A8,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x81,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_DRA(0x210),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_092988B0,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x81,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_DRA(0x210),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_092988C0,
    },
    {
        .animSet = ANIMSET_OVL(11),
        .zPriority = 0x80,
        .facingLeft = 0x48,
        .unk5A = 0,
        .palette = PAL_DRA(0x210),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .flags = 0,
        .animFrames = AnimFrames_092988D0,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0x6C,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_DRA(0),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_092988D8,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0x6C,
        .facingLeft = 0,
        .unk5A = 0,
        .palette = PAL_DRA(0),
        .drawFlags = FLAG_DRAW_DEFAULT,
        .drawMode = DRAW_DEFAULT,
        .flags = 0,
        .animFrames = AnimFrames_092988E0,
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
