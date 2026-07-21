// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

void func_060E0304(Entity* self);
void func_060E0684(Entity* self);
void func_060E093C(Entity* self);
void func_060E0B7C(Entity* self);

extern SaturnSpriteResource g_Stage02SharedBreakableResource;

EntityEntry g_Stage02EntityEntry17 = {NULL, func_060E0304};
EntityEntry g_Stage02EntityEntry22 = {NULL, func_060E0684};
EntityEntry g_Stage02EntityEntry23 = {NULL, func_060E093C};
EntityEntry g_Stage02EntityEntry33 = {
    &g_Stage02SharedBreakableResource, func_060E0B7C};
