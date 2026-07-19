// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

extern struct SpriteParts g_Stage02SkeletonSpriteParts0;
extern struct SpriteParts g_Stage02SkeletonSpriteParts1;

struct SpriteParts* g_Stage02SpriteBank32[] = {
    &g_Stage02SkeletonSpriteParts0,
    &g_Stage02SkeletonSpriteParts1,
    (struct SpriteParts*)-1,
};
