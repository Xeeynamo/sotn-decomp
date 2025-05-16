// SPDX-License-Identifier: AGPL-3.0-or-later

// This conditional is up here just to keep the code block cleaner
// This define will be moved to the overlay header as they're converted
#if defined(STAGE_IS_NO4) || defined(STAGE_IS_NO3) || defined(STAGE_IS_NP3) || \
    defined(BO4_H) || defined(MAR_H) || defined(RBO3_H) || defined(RBO5_H) ||  \
    defined(STAGE_IS_NZ0) || defined(STAGE_IS_ST0) || defined(STAGE_IS_LIB) || \
    defined(MAD_H)
#define STDEBUG_NOROT
#endif
extern ObjInit2 OVL_EXPORT(BackgroundBlockInit)[];
extern u16 g_EInitCommon[];

// params: Index of ObjInit to use
//         (== 1) Use a different hardcoded rotY and rotX value
void EntityBackgroundBlock(Entity* self) {
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
#if defined(STAGE_IS_NO3) || defined(STAGE_IS_NP3)
        self->facingLeft = objInit->facingLeft;
        self->unk5A = objInit->unk5A;
#else
        self->unk5A = LOH(objInit->facingLeft);
#endif
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }
#ifndef STDEBUG_NOROT
        if (self->params == 1) {
            self->rotX = self->rotY = 0x0200;
        }
#endif
    }
    AnimateEntity(objInit->animFrames, self);
}

#ifndef STDEBUG_NOELOCKCAM
#include "entity_lock_camera.h"
#endif
