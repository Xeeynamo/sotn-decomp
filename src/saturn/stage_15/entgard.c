// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank30;

void func_060EE6C4(Entity* self);
void func_060EEE20(Entity* self);
void func_060EEEE4(Entity* self);

EntityEntry g_Stage15EntityGardener = {&g_Stage15SpriteBank30, func_060EE6C4};
EntityEntry g_Stage15EntityEntry62 = {&g_Stage15SpriteBank30, func_060EEE20};
s16 g_Stage15GardenerProjectileInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry61 = {&g_Stage15SpriteBank30, func_060EEEE4};
