// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include "rstage15.h"

void func_060E2A78(Entity* self);

EntityEntry g_RStage15EntityEntry14 = {
    &g_SaturnSharedSpriteBank8Resource, InitSolidProp};
EntityEntry g_RStage15EntityEntry08 = {NULL, func_060E2A78};
