#include "cen.h"

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

void EntityUnkId08(Entity* entity) {
    ObjInit* objInit = &D_8018125C[entity->params];

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
REDACTED
            entity->rotZ = 0x800;
            entity->drawFlags = (u8)(entity->drawFlags | FLAG_DRAW_ROTZ);
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

#include "../popup.h"
