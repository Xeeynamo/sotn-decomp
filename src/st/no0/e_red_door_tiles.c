// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    0x0597, 0x0597, 0x0597, 0x0597, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0597, 0x0597, 0x06F3, 0x06F4, 0x0000, 0x0000, 0x031B, 0x031C,
    0x06F5, 0x06F6, 0x06F7, 0x06F8, 0x06F2, 0x045E, 0x047B, 0x047E,
};
