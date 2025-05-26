// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"

void EntityRoomForeground(Entity* entity) {
    ObjInit* obj = &D_801810F4[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_EInitCommon);
        entity->animSet = obj->animSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk5A;
        entity->palette = obj->palette;
        entity->drawFlags = obj->drawFlags;
        entity->drawMode = obj->drawMode;
        if (obj->flags != 0) {
            entity->flags = obj->flags;
        }
    }
    AnimateEntity(obj->animFrames, entity);
}
