// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

static u8 entityLockCameraHitbox[] = {
    0x20,
    0x20,
    0x20,
    0x20,
};

static u8 entityLockCameraData[4] = {
    0,
    1,
    0,
    0,
};

static u16 entityLockCameraTilemapProps[] = {
    0x000, 0x000, 0x300, 0x200, 0x000, 0x000, 0x300, 0x100,
    0x000, 0x000, 0x300, 0x100, 0x000, 0x000, 0x300, 0x200,
};

#ifndef VERSION_PSP

#include "../e_lock_camera.h"

#else

#include "../player_is_within_hitbox.h"

// n.b.! this is not shared at the moment due to register swaps.
//       it should be possible to share the implementation.
INCLUDE_ASM("st/nz1_psp/nonmatchings/nz1/e_lock_camera", NZ1_EntityLockCamera);

#endif
