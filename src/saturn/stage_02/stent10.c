// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060EC278(Entity* self);
void func_060EC730(Entity* self);
void func_060EC888(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank33[];

EntityEntry g_Stage02EntityEntry48 = {
    g_Stage02SpriteBank33, func_060EC278};
u32 g_Stage02EntityEntry48Padding = 0;

EntityEntry g_Stage02EntityEntry49 = {
    g_Stage02SpriteBank33, func_060EC730};
u32 g_Stage02EntityEntry49Padding = 0;

EntityEntry g_Stage02EntityEntry50 = {
    g_Stage02SpriteBank33, func_060EC888};
u32 g_Stage02EntityEntry50Padding = 0;
