// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage16SpriteBank25Images[];
extern u16 g_Stage16SpriteBank25Palette[];

SaturnSpriteResource g_Stage16SpriteBank25 = {
    g_Stage16SpriteBank25Images,
    g_Stage16SpriteBank25Palette,
    -1,
    0xFFFF,
};
