/*
 * File: en_background_block.c
 * Overlay: CHI
 * Description: ENTITY - Background Block
 */

#include "chi.h"

extern ObjInit2 ObjInit2_80180740[];
extern s32 g_eInitGeneric2;

// [Needs shared file changes to be moved to shared file]
// func_8019B3FC: [E_BACKGROUND_BLOCK] EntityBackgroundBlock
void EntityBackgroundBlock(Entity* entity) {
    ObjInit* objInit = &ObjInit2_80180740[entity->params];
    if (entity->step == 0) {
        InitializeEntity(&g_eInitGeneric2);
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
            entity->rotY = 0x200;
            entity->rotX = 0x200;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}