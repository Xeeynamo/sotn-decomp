// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_RStage15SpriteBank27Images[];
extern u16 g_RStage15SpriteBank27Palette[];

SaturnSpriteResource g_RStage15SpriteBank27 = {
    g_RStage15SpriteBank27Images,
    g_RStage15SpriteBank27Palette,
    -1,
    0xFFFF,
};
