// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage15SpriteBank26Images[];
extern u16 g_Stage15SpriteBank26Palette[];

SaturnSpriteResource g_Stage15SpriteBank26 = {
    g_Stage15SpriteBank26Images,
    g_Stage15SpriteBank26Palette,
    -1,
    0xFFFF,
};
