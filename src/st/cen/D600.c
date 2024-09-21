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

extern u16 g_EntityUnkId12TilemapProps[];
extern u16 g_EntityUnkId12Init[];
extern u8 g_EntityUnkId12Data[];
extern u8 g_EntityUnkId12Hitbox[];

#include "../entity_unk_id12.h"
