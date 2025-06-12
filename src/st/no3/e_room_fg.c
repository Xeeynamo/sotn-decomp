// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

static u8 anim1[] = {64, 1, 255, 0};
static u8 anim2[] = {64, 2, 255, 0};
static u8 anim3[] = {64, 2, 255, 0};
static u8 anim4[] = {64, 1, 255, 0};
static u8 anim5[] = {64, 3, 255, 0};

static ObjInit objData[] = {
    {0x6, 492, 0, 0x0, 0x0, 16, 0, anim1},
    {0xc, 492, 0, 0x0, 0x0, 16, 0, anim3},
    {0xc, 128, 0, 0x0, 0x0, 16, 0, anim4},
    {0x6, 492, 0, 0x0, 0x0, 16, 0, anim2},
    {0xc, 492, 0, 0x0, 0x0, 16, 0, anim5},
    {0xc, 128, 0, 0x0, 0x0, 16, 0, anim4},
};

void EntityRoomForeground(Entity* self) {
    ObjInit* objInit = &objData[self->params];

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags != 0) {
            self->flags = objInit->flags;
        }
        if (self->params > 4) {
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->rotate = 0x800;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}
