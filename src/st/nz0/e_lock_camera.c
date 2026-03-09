// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

static u8 entityLockCameraHitbox[] = {32, 32, 32, 32};

static u8 entityLockCameraData[] = {0, 0, 0, 0};

static u16 entityLockCameraTilemapProps[] = {
    0x000, 0x0FB, 0x100, 0x1FB, 0x000, 0x0FB, 0x100, 0x1FB,
    0x000, 0x0FB, 0x600, 0x1FB, 0x000, 0x000, 0x600, 0x1FB,
};

#include "../e_lock_camera.h"
