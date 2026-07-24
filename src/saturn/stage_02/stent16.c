// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

void func_060E0DC8(Entity* self);

extern SaturnSpriteResource g_Stage02LifeMaxTankResource;

EntityEntry g_Stage02EntityEntry52 = {
    &g_Stage02LifeMaxTankResource, func_060E0DC8};
