// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_RStage15SpriteBank25Images[];
extern u16 g_RStage15SpriteBank25Palette[];

SaturnSpriteResource g_RStage15SpriteBank25 = {
    g_RStage15SpriteBank25Images,
    g_RStage15SpriteBank25Palette,
    -1,
    0xFFFF,
};
