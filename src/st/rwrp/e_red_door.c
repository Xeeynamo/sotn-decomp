// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rwrp.h"

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x7D, 0x75, 0x25, 0x1D, 0xC9, 0xC8, 0xC7, 0xC6},
    {0x7F, 0x77, 0x27, 0x1F, 0xCD, 0xCC, 0xCB, 0xCA},
};

#include "../e_red_door.h"
