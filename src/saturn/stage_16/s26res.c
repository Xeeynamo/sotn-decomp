// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_Stage16SpriteBank26Images[];
extern u16 g_Stage16SpriteBank26Palette[];

SaturnSpriteResource g_Stage16SpriteBank26 = {
    g_Stage16SpriteBank26Images,
    g_Stage16SpriteBank26Palette,
    -1,
    0xFFFF,
};
