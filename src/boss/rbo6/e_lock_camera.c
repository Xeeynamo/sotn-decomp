// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo6.h"

static u8 entityLockCameraHitbox[] = {32, 32, 32, 32};

static u8 entityLockCameraData[] = {1, 0, 0, 0};

static u16 entityLockCameraTilemapProps[] = {
    0x100, 0x0FB, 0x200, 0x1FB, 0x000, 0x000, 0x300, 0x300,
};

#include "../../st/e_lock_camera.h"

