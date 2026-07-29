// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage16SpriteBank22Images[];
extern u16 g_Stage16SpriteBank22Palette[];

SaturnSpriteResource g_Stage16SpriteBank22 = {
    g_Stage16SpriteBank22Images,
    g_Stage16SpriteBank22Palette,
    -1,
    0xFFFF,
};
