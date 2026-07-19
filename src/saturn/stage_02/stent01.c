// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

void func_060DE348(Entity* self);
void func_060DE6CC(Entity* self);
void func_060DE970(Entity* self);
void func_060DEE20(Entity* self);
void func_060DF264(Entity* self);
void func_060DF3B8(Entity* self);
void func_060DF52C(Entity* self);
void func_060DF664(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank00[];
extern struct SpriteParts* g_Stage02SpriteBank01[];
extern SaturnSpriteResource g_Stage02SharedBreakableResource;
extern struct SpriteParts* g_Stage02SpriteBank21[];

EntityEntry g_Stage02EntityEntry55 = {NULL, func_060DE348};
u32 g_Stage02EntityEntryPadding2 = 0;
EntityEntry g_Stage02EntityEntry71 = {
    &g_Stage02SharedBreakableResource, func_060DE6CC};
EntityEntry g_Stage02EntityEntry70 = {
    &g_Stage02SharedBreakableResource, func_060DE970};

u32 g_Stage02EntityParameters1[2] = {0x60, 0x03600660};

EntityEntry g_Stage02EntityEntry56 = {g_Stage02SpriteBank21, func_060DEE20};
EntityEntry g_Stage02EntityEntry57 = {g_Stage02SpriteBank21, func_060DF264};
EntityEntry g_Stage02EntityEntry58 = {g_Stage02SpriteBank01, func_060DF3B8};
EntityEntry g_Stage02EntityEntry59 = {g_Stage02SpriteBank21, func_060DF52C};
EntityEntry g_Stage02EntityEntry60 = {g_Stage02SpriteBank00, func_060DF664};
