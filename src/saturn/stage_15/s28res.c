// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage15SpriteBank28Images[];
extern u16 g_Stage15SpriteBank28Palette[];

SaturnSpriteResource g_Stage15SpriteBank28 = {
    g_Stage15SpriteBank28Images,
    g_Stage15SpriteBank28Palette,
    -1,
    0xFFFF,
};
