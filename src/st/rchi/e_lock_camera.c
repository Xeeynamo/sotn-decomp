// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

#ifdef VERSION_PSP
extern u8 D_pspeu_092642F8[];
extern u16 D_pspeu_09264300[];
extern u8 D_pspeu_092646B8[];
#define entityLockCameraHitbox D_pspeu_092642F8
#define entityLockCameraTilemapProps D_pspeu_09264300
#define entityLockCameraData D_pspeu_092646B8
#define ENTITY_LOCK_CAMERA_DATA_DEFINED
#endif

#include "../entity_lock_camera.h"
