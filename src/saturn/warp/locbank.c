// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>
#include "warp.h"

struct SpriteParts* g_WarpSpriteBank16[] = {
    (struct SpriteParts*)g_WarpSpriteBank16Images,
    (struct SpriteParts*)&g_WarpSpriteBank16Palettes,
    (struct SpriteParts*)-1,
};
