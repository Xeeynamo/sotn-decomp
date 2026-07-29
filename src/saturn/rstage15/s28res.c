// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_RStage15SpriteBank28Images[];
extern u16 g_RStage15SpriteBank28Palette[];

SaturnSpriteResource g_RStage15SpriteBank28 = {
    g_RStage15SpriteBank28Images,
    g_RStage15SpriteBank28Palette,
    -1,
    0xFFFF,
};
