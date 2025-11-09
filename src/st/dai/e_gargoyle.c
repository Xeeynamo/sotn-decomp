// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 E_ID(GARGOYLE_TONGUE);
#endif

enum GargoyleSteps {
    GARGOYLE_INIT,
    GARGOYLE_NOP,
    GARGOYLE_ADJUST_DOWN,
    GARGOYLE_ADJUST_UP,
    GARGOYLE_POSITIONED = 16,
};

enum GargoyleParams {
    FACING_LEFT,
    FACING_RIGHT,
    BLOCK_ONLY,
};

extern EInit g_EInitEnvironment;

// This is the tongue and block in front of the statue and does not
// include the statue itself.
void EntityGargoyleTongue(Entity* self) {
    Entity* block;
    s32 count;
    s32 tileIdx;

    switch (self->step) {
    case GARGOYLE_INIT:
        InitializeEntity(g_EInitEnvironment);
        self->zPriority = 92;
        self->animCurFrame = 12;
        if (self->params & FACING_RIGHT) {
            self->animCurFrame = 13;
        }
        if (self->params & BLOCK_ONLY) {
            self->animCurFrame = 14;
            return;
        }
        block = self + 1;
        CreateEntityFromEntity(E_ID(GARGOYLE_TONGUE), self, block);
        block->params = BLOCK_ONLY;
        block->posY.i.hi = 160;
        if (self->params) {
            block->posX.i.hi += 16;
        }
        break;
    case GARGOYLE_NOP:
        break;
    case GARGOYLE_ADJUST_DOWN:
        self->posY.val += FIX(1.125);
        if (self->posY.val > FIX(70.0)) {
            self->posY.val = FIX(70.0);
            self->step = GARGOYLE_POSITIONED;
            if (self->params) {
                tileIdx = 222;
            } else {
                tileIdx = 193;
            }

            for (count = 0; count < 4; tileIdx += 32, count++) {
                g_Tilemap.fg[tileIdx] = 0x4B3;
            }
        }
        break;
    case GARGOYLE_ADJUST_UP:
        self->posY.val -= FIX(1.125);
        if (self->posY.val < FIX(129.0)) {
            self->posY.val = FIX(129.0);
            self->step = GARGOYLE_POSITIONED;
        }
        break;
    }
}
