// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage15SpriteBank31Images[];
extern u16 g_Stage15SpriteBank31Palette[];

SaturnSpriteResource g_Stage15SpriteBank31 = {
    g_Stage15SpriteBank31Images,
    g_Stage15SpriteBank31Palette,
    -1,
    0xFFFF,
};
