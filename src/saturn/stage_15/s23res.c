// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage15SpriteBank23Images[];
extern u16 g_Stage15SpriteBank23Palette[];

SaturnSpriteResource g_Stage15SpriteBank23 = {
    g_Stage15SpriteBank23Images,
    g_Stage15SpriteBank23Palette,
    -1,
    0xFFFF,
};
