// SPDX-License-Identifier: AGPL-3.0-only
#include "dre.h"

#include "../check_coll_offsets.h"

#include "../entity_unkId13.h"

#include "../entity_unkId14_spawner.h"

#include "../entity_unkId15_spawner.h"

#include "../entity_unkId14.h"

#include "../entity_unkId15.h"

#include "../entity_olrox_drool.h"

#include "../unk_collision_func5.h"

#include "../unk_collision_func4.h"

#include "../entity_intense_explosion.h"

#include "../initialize_unk_entity.h"

#include "../make_entity_from_id.h"

#include "../make_explosions.h"

#include "../entity_big_red_fireball.h"

#include "../unk_recursive_primfunc_1.h"

#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_positional.h"

#include "../e_stage_name.h"

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

extern ObjInit D_80181420[];
void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &D_80181420[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk5A;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

#include "../popup.h"
