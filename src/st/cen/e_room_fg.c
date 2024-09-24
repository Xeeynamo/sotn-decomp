// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"

#if !defined(VERSION_HD)

#include "../e_room_fg.h"

#else

static u8 foregroundAnim1[] = {0x40, 0x07, 0xFF, 0x00};
static ObjInit eRoomForegroundInit[] = {
    {0x8002, 0x0081, 0x0000, 0x0000, 0x00, 0, 0, foregroundAnim1},
};

extern u16 g_eInitGeneric2[];
void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &eRoomForegroundInit[entity->params];

    if (!entity->step) {
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
        if (entity->params == 1) {
            entity->rotX = entity->rotY = 0x200;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}

#endif
