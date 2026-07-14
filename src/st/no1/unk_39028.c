// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

static u16 D_us_8018142C[] = {
    0x68, 0x68, 0x68, 0x6C, 0x6A, 0x68, 0x68, 0x68, 0x68, 0x00,
};

static u16 D_us_80181440[] = {
    0x80, 0x80, 0x60, 0x80, 0x80, 0x40, 0x80, 0x80, 0x80, 0x00,
};

// Seems to be some kind of helper for the chair next to the save room
// It spawns the table and chair sprite
void func_us_801B9028(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A4C);
        self->animCurFrame = self->params + 1;
        self->zPriority = D_us_8018142C[self->params];
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = D_us_80181440[self->params];
        break;

    case 1:
        break;

    case 2:
#include "../pad2_anim_debug.h"
    }
}
