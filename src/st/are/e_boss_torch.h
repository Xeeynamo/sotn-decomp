// SPDX-License-Identifier: AGPL-3.0-or-later
extern EInit g_EInitEnvironment;
static AnimateEntityFrame anim_boss_torch[] = {
    {.duration = 5, .pose = 0x04}, {.duration = 5, .pose = 0x05},
    {.duration = 5, .pose = 0x06}, {.duration = 5, .pose = 0x07},
    {.duration = 5, .pose = 0x08}, POSE_LOOP(0),
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
        self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleX = self->scaleY = scale[self->params];
        // fallthrough
    case 1:
        AnimateEntity(anim_boss_torch, self);
        if (g_Timer & 4) {
            self->palette = (self->params * 2) + PAL_FLAG(PAL_TORCH_A);
        } else {
            self->palette = (self->params * 2) + PAL_FLAG(PAL_TORCH_B);
        }
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
}
