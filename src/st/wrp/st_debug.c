#include "wrp.h"

static u8 g_EntityUnkId12Hitbox[] = {
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x50, 0x20};

#ifndef VERSION_PSP // moved to BSS
static u8 g_EntityUnkId12Data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#else
extern u8 g_EntityUnkId12Data[];
#endif

static u16 g_EntityUnkId12TilemapProps[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};

extern ObjInit D_801804E0[];
extern u16 g_eInitGeneric2[];
extern u16 g_EntityUnkId12Init[];

void func_80186FD0(Entity* self) {
    ObjInit* objInit = &D_801804E0[self->params];
    if (!self->step) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;

        if (objInit->unkC) {
            self->flags = objInit->unkC;
        }

        if (self->params == 1) {
            self->rotX = self->rotY = 0x0200;
        }
    }

    AnimateEntity(objInit->unk10, self);
}

#include "../entity_unk_id12.h"
