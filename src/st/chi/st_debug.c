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
#include "../st_debug.h"
