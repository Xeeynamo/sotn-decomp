// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 E_ID(GARGOYLE_STATUE);
#endif

// Gargoyle statues at top of Hippogryph room
void EntityGargoyleStatue(Entity* self) {
    Entity* entity;
    s32 count;
    s32 tileIdx;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStatueBlock);
        self->zPriority = 92;
        self->animCurFrame = 12;
        if (self->params & 1) {
            self->animCurFrame = 13;
        }
        if (self->params & 2) {
            self->animCurFrame = 14;
            return;
        }
        entity = self + 1;
        CreateEntityFromEntity(E_ID(GARGOYLE_STATUE), self, entity);
        entity->params = 2;
        entity->posY.i.hi = 160;
        if (self->params) {
            entity->posX.i.hi += 16;
        }
        break;
    case 1:
        break;
    case 2:
        self->posY.val += FIX(1.125);
        if (self->posY.val > FIX(70.0)) {
            self->posY.val = FIX(70.0);
            self->step = 16;
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
    case 3:
        self->posY.val -= FIX(1.125);
        if (self->posY.val < FIX(129.0)) {
            self->posY.val = FIX(129.0);
            self->step = 16;
        }
        break;
    }
}
