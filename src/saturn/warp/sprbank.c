// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

extern struct SpriteParts* g_EntitySpriteBank00[];
extern struct SpriteParts* g_EntitySpriteBank01[];
extern struct SpriteParts* g_EntitySpriteBank02[];
extern struct SpriteParts* g_EntitySpriteBank03[];
extern struct SpriteParts* g_EntitySpriteBank04[];
extern struct SpriteParts* g_EntitySpriteBank05[];
extern struct SpriteParts* g_EntitySpriteBank06[];
extern struct SpriteParts* g_EntitySpriteBank07[];
extern struct SpriteParts* g_EntitySpriteBank08[];
extern struct SpriteParts* g_EntitySpriteBank09[];
extern struct SpriteParts* g_EntitySpriteBank10[];
extern struct SpriteParts* g_EntitySpriteBank11[];
extern struct SpriteParts* g_EntitySpriteBank12[];
extern struct SpriteParts* g_EntitySpriteBank13[];
extern struct SpriteParts* g_EntitySpriteBank14[];
extern struct SpriteParts* g_EntitySpriteBank15[];
extern struct SpriteParts* g_WarpSpriteBank16[];

struct SpriteParts** g_WarpSpriteBanks[18] = {
    g_EntitySpriteBank00,
    g_EntitySpriteBank01,
    g_EntitySpriteBank02,
    g_EntitySpriteBank03,
    g_EntitySpriteBank04,
    g_EntitySpriteBank05,
    g_EntitySpriteBank06,
    g_EntitySpriteBank07,
    g_EntitySpriteBank08,
    g_EntitySpriteBank09,
    g_EntitySpriteBank10,
    g_EntitySpriteBank11,
    g_EntitySpriteBank12,
    g_EntitySpriteBank13,
    g_EntitySpriteBank14,
    g_EntitySpriteBank15,
    g_WarpSpriteBank16,
    NULL,
};
