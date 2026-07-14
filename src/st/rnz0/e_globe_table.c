// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz0.h"

extern EInit g_EInitTableWithGlobe;

// table with globe on it that can be broken
static u8 D_80180EF0[] = {2, 1, 2, 2, 0, 0};

static u8 D_80180EF8[] = {
    3, 3, 3, 4,  3, 5,  3, 6,  3,  7,  3,  8,
    2, 9, 2, 10, 2, 11, 3, 12, 33, 13, -1, 0,
};

void EntityTableWithGlobe(Entity* self) {
    Entity* child;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTableWithGlobe);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->hitboxOffX = 0;
        self->hitboxOffY = 10;
        self->hitboxState = 2;
    case 1:
        AnimateEntity(D_80180EF0, self);
        if (self->hitFlags) {
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            self->hitboxState = 0;
            child = self + 1;
            CreateEntityFromEntity(E_HEART_DROP, self, child);
            child->params = self->params;
            SetStep(2);
        }
        break;
    case 2:
        AnimateEntity(D_80180EF8, self);
        break;
    }
}
