// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage16SpriteBank20Images[];
extern u16 g_Stage16SpriteBank20Palette[];

SaturnSpriteResource g_Stage16SpriteBank20 = {
    g_Stage16SpriteBank20Images,
    g_Stage16SpriteBank20Palette,
    -1,
    0xFFFF,
};
