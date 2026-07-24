// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_sprite.h>

void EntityTableWithGlobe(Entity* self);
void func_060DDF64(Entity* self);
void func_060DE178(Entity* self);

extern SaturnSpriteResource g_Stage02TableWithGlobeResource;
extern SaturnSpriteResource g_Stage02BlueFlameTableResource;

u8 g_Stage02TableWithGlobeIdleAnim[8] = {2, 1, 2, 2, 0, 0, 0, 0};

u8 g_Stage02TableWithGlobeBreakAnim[24] = {
    3, 3, 3, 4,  3, 5,  3, 6,  3,    7,  3,    8,
    2, 9, 2, 10, 2, 11, 3, 12, 0x21, 13, 0xFF, 0,
};

u16 g_Stage02TableWithGlobeDropParams[6] = {0, 1, 2, 6, 10, 0};

EntityEntry g_Stage02EntityEntry51 = {
    &g_Stage02TableWithGlobeResource, EntityTableWithGlobe};

u16 g_Stage02Entity51Parameters[4] = {7, 8, 18, 6};

EntityEntry g_Stage02EntityEntry54 = {
    &g_Stage02BlueFlameTableResource, func_060DDF64};
EntityEntry g_Stage02EntityEntry53 = {
    &g_Stage02BlueFlameTableResource, func_060DE178};
