// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank27;

void func_060EBC24(Entity* self);
void func_060ECB7C(Entity* self);

EntityEntry g_Stage15EntityWaterLeaper = {
    &g_Stage15SpriteBank27, func_060EBC24};
s16 g_Stage15WaterLeaperInitOffset[2] = {0, 16};
EntityEntry g_Stage15EntityEntry52 = {NULL, func_060ECB7C};
