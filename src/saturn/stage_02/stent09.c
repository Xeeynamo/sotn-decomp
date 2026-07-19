// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060E4908(Entity* self);
void func_060E5410(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank03[];
extern struct SpriteParts* g_Stage02SpriteBank04[];

EntityEntry g_Stage02EntityEntry04 = {
    g_Stage02SpriteBank03, func_060E4908};

u16 g_Stage02Entity04Parameters[8] = {1, 5, 3, 4, 4, 4, 2, 4};

EntityEntry g_Stage02EntityEntry03 = {
    g_Stage02SpriteBank04, func_060E5410};
