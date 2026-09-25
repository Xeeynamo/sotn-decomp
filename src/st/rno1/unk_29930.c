// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

extern EInit D_us_8018076C;

static u16 zPris[] = {0x68,0x68,0x68,
                      0x6C,0x6A,0x68,
                      0x68,0x68,0x68};
static u16 opacs[] = {0x80,0x80,0x60,
                      0x80,0x80,0x40,
                      0x80,0x80,0x80};

void func_us_801B9028_from_no1(Entity* self) {
    switch (self->step) {
    case 0: {
        InitializeEntity(D_us_8018076C);
        self->animCurFrame = self->params + 1;
        self->zPriority = zPris[self->params];
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = opacs[self->params];
        break;
    }

    case 1:
        break;

    case 2:
#include "../pad2_anim_debug.h"
    }
}
