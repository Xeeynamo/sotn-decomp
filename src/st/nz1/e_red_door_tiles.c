// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x56A, 0x56B, 0x570, 0x571, 0x135, 0x138, 0x142, 0x138},
    {0x578, 0x579, 0x57A, 0x57B, 0x0F0, 0x0F1, 0x141, 0x10C},
};
