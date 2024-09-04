#include "np3.h"

extern ObjInit D_801820F0[];
void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &D_801820F0[entity->params];

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
            entity->drawFlags |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}
