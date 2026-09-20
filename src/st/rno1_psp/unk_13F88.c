// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno1/rno1.h"

void func_us_801B9028_from_no1(Entity* self) {
    extern u16 D_us_8018076C[];
    extern u16 D_us_80180D44[];
    extern u16 D_us_80180D58[];

    switch (self->step) {
    case 0: {
        InitializeEntity(D_us_8018076C);
        self->animCurFrame = self->params + 1;
        self->zPriority = D_us_80180D44[self->params];
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = D_us_80180D58[self->params];
        break;
    }

    case 1:
        break;

    case 2:
#include "../pad2_anim_debug.h"
    }
}
