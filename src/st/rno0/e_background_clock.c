// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

extern EInit g_EInitCommon;
extern EInit g_EInitSpawner;

void EntityPendulum(Entity* self) {
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 33;
        self->zPriority = 0x50;
        self->unk5A = 0;
        self->palette = 0;
        self->drawFlags = ENTITY_ROTATE | ENTITY_OPACITY;
        self->opacity = 0x60;
    }
    angle = rsin((((g_Timer % 120) << 0xC) + 60) / 120);
    if (!angle) {
        g_api.PlaySfx(SFX_LOW_CLOCK_TICK);
    }
    self->rotate = (angle >> 6) + (angle >> 7);
}

void EntityClockTickSound(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    u8 volume;
    s16 distance;

    if (!self->step) {
        InitializeEntity(g_EInitSpawner);
    }
    if ((g_Timer % 60) == 0) {
        switch (self->params) {
        case 0:
            g_api.PlaySfx(SFX_LOW_CLOCK_TICK);
            break;

        case 1:
            distance =
                ((0x140 - (tilemap->scrollX.i.hi + player->posX.i.hi)) * 2) / 5;
            if (distance < 0) {
                volume = 0;
            } else if (distance >= 0x80) {
                volume = 0x7F;
            } else {
                volume = distance;
            }
            g_api.PlaySfxVolPan(SFX_LOW_CLOCK_TICK, volume, -8);
            break;

        case 2:
            distance = ((0x40 + player->posX.i.hi) * 2) / 5;
            if (distance < 0) {
                volume = 0;
            } else if (distance >= 0x80) {
                volume = 0x7F;
            } else {
                volume = distance;
            }
            g_api.PlaySfxVolPan(SFX_LOW_CLOCK_TICK, volume, 8);
            break;
        }
    }
}
