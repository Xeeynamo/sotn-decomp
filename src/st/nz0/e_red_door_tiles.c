// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    0x0761, 0x0769, 0x0771, 0x0779, 0x0130, 0x0138, 0x01C0, 0x01C5,
    0x0763, 0x076B, 0x0773, 0x077B, 0x0175, 0x017A, 0x0200, 0x0203,
    0x0762, 0x076A, 0x0772, 0x077A, 0x0000, 0x0000, 0x0000, 0x0000,
};
