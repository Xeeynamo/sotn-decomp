#include "wrp.h"

#if !defined(VERSION_PSP)
u8 D_80181120[] = {0x40, 0x01, 0xFF, 0x00};
u8 D_80181124[] = {0x40, 0x02, 0xFF, 0x00};
u8 D_80181128[] = {0x40, 0x02, 0xFF, 0x00};
u8 D_8018112C[] = {0x40, 0x01, 0xFF, 0x00};
u8 D_80181130[] = {0x40, 0x03, 0xFF, 0x00};
ObjInit2 D_80181134[] = {
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_80181120},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_80181128},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, D_8018112C},
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_80181124},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_80181130},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, D_8018112C},
};

#else
extern ObjInit2 D_80181134[];

#endif

void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->params];

    if (!entity->step) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.u;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params > 4) {
            entity->drawFlags |= DRAW_COLORS;
            entity->rotZ = 0x800;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}
