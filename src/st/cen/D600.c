// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: D600.c
 * Overlay: CEN
 * Description: Center Cube Area (Final Boss)
 */

#include "cen.h"
#include "game.h"
#include "sfx.h"

// background block of rock
void EntityBackgroundBlock(Entity* self) {
    ObjInit* obj = &D_80180490[self->params].animSet;

    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk5A;
        self->palette = obj->palette;
        self->drawFlags = obj->drawFlags;
        self->drawMode = obj->drawMode;

        if (obj->unkC != 0) {
            self->flags = obj->unkC;
        }

        if (self->params == 1) {
            self->rotY = 0x200;
            self->rotX = 0x200;
        }
    }
    AnimateEntity(obj->animFrames, self);
}

u8 g_EntityUnkId12Hitbox[] = {32, 32, 32, 32, 32, 32, 80, 32};
u8 g_EntityUnkId12Data[] = {0, 0, 0, 0, 0, 0, 0, 0};

u16 g_EntityUnkId12TilemapProps[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};

static u16 D_80180554[] = {
    0x0E03, 0x0F04, 0x1004, 0x1104, 0x1204, 0x1304, 0x1403, 0x0000,
};

static u16 D_80180564[] = {
    0x1503, 0x1604, 0x1704, 0x1804, 0x1904, 0x1A04, 0x1B03, 0x0000,
};

u16* D_80180574[] = {
    D_80180554, D_80180564, NULL, NULL, NULL, NULL, NULL, NULL,
};

// height
u8 D_80180594[] = {
    12, 20, 0, 0, 0, 0, 0, 0,
};

// params
u8 D_8018059C[] = {
    0x3, 0x3, 0, 0, 0, 0, 0, 0,
};

// animset
u16 D_801805A4[] = {
    ANIMSET_OVL(1), ANIMSET_OVL(1), 0, 0, 0, 0, 0, 0,
};

// draw mode
u8 D_801805B4[] = {
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
};

s16 D_801805BC[] = {
    -4, -4, 3, -6, 2, 9, -4, 12, 0, 2, 0, 15, 0, 31,
};

#include "../entity_unk_id12.h"
