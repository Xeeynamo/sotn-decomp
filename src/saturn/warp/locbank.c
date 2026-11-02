// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "warp.h"

SaturnSpriteResource g_WarpSpriteBank16 = {
    g_WarpSpriteBank16Images,
    (u16*)&g_WarpSpriteBank16Palettes,
    -1,
    0xFFFF,
};
