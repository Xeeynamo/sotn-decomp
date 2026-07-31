// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage15SpriteBank24Images[];
extern u16 g_Stage15SpriteBank24Palette[];

SaturnSpriteResource g_Stage15SpriteBank24 = {
    g_Stage15SpriteBank24Images,
    g_Stage15SpriteBank24Palette,
    -1,
    0xFFFF,
};
