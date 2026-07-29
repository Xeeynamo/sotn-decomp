// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage15SpriteBank27Images[];
extern u16 g_Stage15SpriteBank27Palette[];

SaturnSpriteResource g_Stage15SpriteBank27 = {
    g_Stage15SpriteBank27Images,
    g_Stage15SpriteBank27Palette,
    -1,
    0xFFFF,
};
