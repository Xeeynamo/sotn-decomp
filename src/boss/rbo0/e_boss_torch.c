// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

// n.b.! this is identical to e_boss_torch for
// rare, but the symbol used here is the same
// address for RBO0_PrizeDrops. It seems like
// e_collect may have been linked against a
// different definition, but is unused for
// this boss.

extern EInit g_EInitEnvironment;
#ifdef VERSION_PSP
static AnimateEntityFrame frames[] = {
#else
// this may be a bug, not sure how this can also be used for PrizeDrops
AnimateEntityFrame RBO0_PrizeDrops[] = {
#endif
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
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = scale[self->params];
        // fallthrough
    case 1:
#ifdef VERSION_PSP
        AnimateEntity(frames, self);
#else
        AnimateEntity(RBO0_PrizeDrops, self);
#endif
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
