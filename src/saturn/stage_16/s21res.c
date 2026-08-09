// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage16SpriteBank21Images[];
extern u16 g_Stage16SpriteBank21Palette[];

SaturnSpriteResource g_Stage16SpriteBank21 = {
    g_Stage16SpriteBank21Images,
    g_Stage16SpriteBank21Palette,
    -1,
    0xFFFF,
};
