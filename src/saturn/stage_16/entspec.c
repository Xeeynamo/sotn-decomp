// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage16SpriteBank23;

void func_060E55B0(Entity* self);

EntityEntry g_Stage16EntitySpecter = {&g_Stage16SpriteBank23, func_060E55B0};
