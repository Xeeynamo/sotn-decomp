// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static u8 AnimFrames_80180AC4[] = {0x40, 0x01, 0xFF, 0x00};

ObjInit2 OVL_EXPORT(BackgroundBlockInit)[] = {{
    .animSet = ANIMSET_DRA(6),
    .zPriority = 0x1FA,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_DEFAULT,
    .drawMode = DRAW_TPAGE,
    .animFrames = &AnimFrames_80180AC4,
}};

u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x04B3, 0x04B3, 0x04B3, 0x04B3, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x000D, 0x000E, 0x000F, 0x000E, 0x01F0, 0x01F6, 0x020E, 0x01F6},
    {0x000A, 0x000B, 0x000C, 0x000B, 0x0086, 0x0088, 0x00A1, 0x0088},
};

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

#include "../entity_lock_camera.h"
