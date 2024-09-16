// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

extern ObjInit2 D_80180C10[];
extern u16 g_eInitGeneric2[];
void func_us_8018AC0C(Entity* self) {
    ObjInit2* objInit = &D_80180C10[self->params];

    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = LOH(objInit->facingLeft); // bug?
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            self->flags = objInit->unkC;
        }
    }

    AnimateEntity(objInit->unk10, self);
}

static u8 g_EntityUnkId12Hitbox[] = {
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x50, 0x20};
static u8 g_EntityUnkId12Data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static u16 g_EntityUnkId12TilemapProps[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};
#include "../../st/entity_unk_id12.h"
