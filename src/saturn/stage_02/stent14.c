// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060EA264(Entity* self);
void func_060EACC0(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank30[];

EntityEntry g_Stage02EntityEntry40 = {
    g_Stage02SpriteBank30, func_060EA264};

s16 g_Stage02AxeKnightParameters[18] = {
    0x405, 0x405, 0x405, 0x405, 2, 0, 2, 0, 1,
    0,     0,     0,     0,     0,  -4, 0, 0, 0,
};

EntityEntry g_Stage02EntityEntry41 = {
    g_Stage02SpriteBank30, func_060EACC0};
