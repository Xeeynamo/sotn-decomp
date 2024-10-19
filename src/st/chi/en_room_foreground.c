/*
 * File: en_room_foreground.c
 * Overlay: CHI
 * Description: ENTITY - Room foreground
 */

#include "chi.h"

#if !defined(VERSION_PSP)
// D_801814AC
static u8 D_801814AC[] = {0x40, 0x01, 0xFF, 0x00};
// D_801814B0
static u8 D_801814B0[] = {0x40, 0x02, 0xFF, 0x00};
// D_801814B4
static u8 D_801814B4[] = {0x40, 0x02, 0xFF, 0x00};
// D_801814B8
static u8 D_801814B8[] = {0x40, 0x01, 0xFF, 0x00};
// D_801814BC
static u8 D_801814BC[] = {0x40, 0x03, 0xFF, 0x00};
// D_801814C0
static ObjInit2 D_801814C0[] = {
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814AC},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B4},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B8},
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B0},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814BC},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B8},
};

#else
extern ObjInit2 D_801814C0[];

#endif

extern u16 g_eInitGeneric2[];

// [Duplicate]
// [Need to remove D_######## symbol names before using common include]
// E_ROOM_FOREGROUND
// func_801A7C8C
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_801814C0[entity->params];

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
//TODO: Can't use this include yet, as it still contains D_######## symbol names
//#include "../e_room_fg.h"