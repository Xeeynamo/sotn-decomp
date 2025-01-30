// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"
#include "sfx.h"

// puts garbled hp max up text on screen
void EntityUnkId11(Entity* entity) {
    ObjInit* obj = (ObjInit*)&D_80180528[entity->params * 10];

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

        if (entity->params == 1) {
            entity->rotY = 0x200;
            entity->rotX = 0x200;
        }
    }

    AnimateEntity(obj->animFrames, entity);
}

#include "../entity_unk_id12.h"
