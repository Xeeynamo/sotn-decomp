 // SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

enum {
    PAL_TORCH_A = 0x5A,
    PAL_TORCH_B = 0x5B,
};

extern EInit D_us_80180524;
extern AnimateEntityFrame D_us_80180B60[];
extern s16 D_us_80180B6C[];

void EntityBossTorch(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180524);

        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = D_us_80180B6C[self->params];

        // fallthrough
    case 1:
        AnimateEntity(D_us_80180B60, self);

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
