// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

// bust with red eyes that can have a candle on it
void EntityRedEyeBust(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnemy3);
        self->animCurFrame = 7;
        self->zPriority = 0x70;
        break;

    case 1:
        break;

    case 2:
#include "../pad2_anim_debug.h"
    }
}
