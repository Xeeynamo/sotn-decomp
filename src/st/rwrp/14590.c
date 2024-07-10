#include "rwrp.h"

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

void func_80194DD4(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags = (u8)(entity->drawFlags | FLAG_DRAW_ROTZ);
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

#include "../popup.h"
