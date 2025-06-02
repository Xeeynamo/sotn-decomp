// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: st_debug.c
 * Overlay: CHI
 * Description: STAGE - Background Block and Camera Lock
 */

#include "chi.h"

// D_80180798: entityLockCameraHitbox
// D_801807A0: entityLockCameraData
// D_801807A8: entityLockCameraTilemapProps
// func_8019B3FC: [E_BACKGROUND_BLOCK] EntityBackgroundBlock
// func_8019B4DC: [E_CAMERA_LOCK] EntityLockCamera
extern ObjInit2 OVL_EXPORT(BackgroundBlockInit)[];
extern u16 g_EInitCommon[];

// params: Index of ObjInit to use
//         (== 1) Use a different hardcoded scaleY and scaleX value
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit2* objInit = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
#ifdef VERSION_PSP
        self->unk5A = LOHU(objInit->facingLeft);
#else
        self->unk5A = LOH(objInit->facingLeft);
#endif
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->flags) {
            self->flags = objInit->flags;
        }

        if (self->params == 1) {
            self->scaleX = self->scaleY = 0x0200;
        }
    }
    AnimateEntity(objInit->animFrames, self);
}

#include "../entity_lock_camera.h"
