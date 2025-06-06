// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

extern ObjInit D_801820F0[];
void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &D_801820F0[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_EInitCommon);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk5A;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->flags != 0) {
            entity->flags = objInit->flags;
        }
        if (entity->params >= 5) {
            entity->rotate = 0x800;
            entity->drawFlags |= FLAG_DRAW_ROTATE;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}
