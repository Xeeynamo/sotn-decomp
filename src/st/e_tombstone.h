// SPDX-License-Identifier: AGPL-3.0-or-later
#include <sfx.h>

extern EInit g_EInitTombstone;
static s16 sensors[] = {
    0x0000, 0x0010, 0x0000, 0x0004, 0x0008, 0xFFFC, 0xFFF0, 0x0000};
static s16 unused[] = {0x1508, 0x1608, 0x1708, 0x1608, 0x1508, 0x00FF};

void EntityTombstone(Entity* self) {
    Entity* entity;

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, self, entity);
            entity->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTombstone);
        self->hitboxOffY = -6;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->animCurFrame = 0x15;
        break;

    case 1:
        if (UnkCollisionFunc3(sensors) & 1) {
            self->step++;
        }
        break;

    case 2:
        if (self->ext.tombstone.timer) {
            self->ext.tombstone.timer--;
        } else if (GetDistanceToPlayerX() < 0x40) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.tombstone.timer = 0x18;
            self->rotate = 0xFC0;
            PlaySfxPositional(SFX_TOMBSTONE_MOVE);
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            if (!--self->ext.tombstone.timer) {
                if (self->facingLeft) {
                    self->velocityX = FIX(2);
                } else {
                    self->velocityX = -FIX(2);
                }
                self->velocityY = -FIX(4);
                self->step_s++;
                return;
            } else if (self->ext.tombstone.timer & 4) {
                self->rotate += 0x20;
                return;
            } else {
                self->rotate -= 0x20;
                return;
            }
            return;
        }

        if (abs(self->velocityY) < FIX(2)) {
            self->animCurFrame = 0x17;
        } else {
            self->animCurFrame = 0x16;
        }
        if (UnkCollisionFunc3(&sensors) & 1) {
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            self->animCurFrame = 0x15;
            self->ext.tombstone.timer = 0x80;
            self->rotate = 0;
            self->step--;
        }
        break;
    }
}
