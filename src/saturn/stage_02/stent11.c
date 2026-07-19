// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060E9828(Entity* self);
void func_060EA058(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank29[];

EntityEntry g_Stage02EntityEntry38 = {
    g_Stage02SpriteBank29, func_060E9828};
EntityEntry g_Stage02EntityEntry39 = {
    g_Stage02SpriteBank29, func_060EA058};

s16 g_Stage02BoneScimitarPartsInitOffset[2] = {0, 0};
