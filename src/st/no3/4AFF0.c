// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

#include "../e_stage_name.h"

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

#include "sfx.h"

void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &D_80182764[entity->params];

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
            entity->rotZ = 0x800;
            entity->drawFlags |= FLAG_DRAW_ROTZ;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}
