// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060EB9EC(Entity* self);
void func_060EBEB0(Entity* self);
void func_060EC030(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank32[];

EntityEntry g_Stage02EntityEntry45 = {
    g_Stage02SpriteBank32, func_060EB9EC};
EntityEntry g_Stage02EntityEntry47 = {NULL, func_060EBEB0};

u32 g_Stage02SkeletonThrownBoneState[4] = {0};

EntityEntry g_Stage02EntityEntry46 = {NULL, func_060EC030};

u32 g_Stage02SkeletonPiecesState[4] = {0};
