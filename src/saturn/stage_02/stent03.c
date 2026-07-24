// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

void func_060E22FC(Entity* self);
void func_060E2420(Entity* self);

extern SaturnSpriteResource g_Stage02MariaNpcResource;

EntityEntry g_Stage02EntityEntry76 = {
    &g_Stage02MariaNpcResource, func_060E22FC};
EntityEntry g_Stage02EntityEntry75 = {
    &g_Stage02MariaNpcResource, func_060E2420};
