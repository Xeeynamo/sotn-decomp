// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include "game.h"

void EntityMaria(Entity* self) {
    if (self->step == 0) {
#if !defined(VERSION_HD)
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[MET_MARIA_IN_CEN] != 0) {
            DestroyEntity(self);
            return;
        }
#endif
        InitializeEntity(g_EInitSpawner);
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 10;
        self->unk5A = 0x48;
        self->palette = 0x210;
        self->zPriority = 0x80;
    }
}
