// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

extern EInit g_EInitEnvironment;
static AnimateEntityFrame frames[] = {
    POSE(5, 0x04, 0), POSE(5, 0x05, 0), POSE(5, 0x06, 0),
    POSE(5, 0x07, 0), POSE(5, 0x08, 0), POSE_LOOP(0),
};
// Torches are scaled slightly smaller based on params
// to appear further in the background.
static s16 scale[] = {256, 200, 164};

void EntityBossTorch(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
#ifdef INVERTED_STAGE
        self->zPriority = 0x6A;
#endif
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = scale[self->params];
        // fallthrough
    case 1:
        AnimateEntity(frames, self);
        if (g_Timer & 4) {
            self->palette = (self->params * 2) + PAL_FLAG(PAL_TORCH_A);
        } else {
            self->palette = (self->params * 2) + PAL_FLAG(PAL_TORCH_B);
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }
}
