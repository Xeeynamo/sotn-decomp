// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060DFAE4(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank23[];

u16 g_Stage02ElevatorMessage[12] = {
    0x780E, 0x9682, 0x9640, 0x82C5, 0x8E7B, 0x8FF9,
    0x82B3, 0x82EA, 0x82C4, 0x82A2, 0x82E9, 0,
};

EntityEntry g_Stage02EntityEntry73 = {
    g_Stage02SpriteBank23, func_060DFAE4};
