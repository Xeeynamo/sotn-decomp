// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void EntityTableWithGlobe(Entity* self);
void func_060DDF64(Entity* self);
void func_060DE178(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank18[];
extern struct SpriteParts* g_Stage02SpriteBank20[];

u8 g_Stage02TableWithGlobeIdleAnim[8] = {2, 1, 2, 2, 0, 0, 0, 0};

u8 g_Stage02TableWithGlobeBreakAnim[24] = {
    3, 3, 3, 4,  3, 5,  3, 6,  3,    7,  3,    8,
    2, 9, 2, 10, 2, 11, 3, 12, 0x21, 13, 0xFF, 0,
};

u16 g_Stage02TableWithGlobeDropParams[6] = {0, 1, 2, 6, 10, 0};

EntityEntry g_Stage02EntityEntry51 = {
    g_Stage02SpriteBank18, EntityTableWithGlobe};

u16 g_Stage02Entity51Parameters[4] = {7, 8, 18, 6};

EntityEntry g_Stage02EntityEntry54 = {g_Stage02SpriteBank20, func_060DDF64};
EntityEntry g_Stage02EntityEntry53 = {g_Stage02SpriteBank20, func_060DE178};
