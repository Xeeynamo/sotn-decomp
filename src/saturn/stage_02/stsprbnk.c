// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

#define DECLARE_SPRITE_BANK(index)                                            \
    extern struct SpriteParts* g_Stage02SpriteBank##index[]

DECLARE_SPRITE_BANK(00);
DECLARE_SPRITE_BANK(01);
DECLARE_SPRITE_BANK(02);
DECLARE_SPRITE_BANK(03);
DECLARE_SPRITE_BANK(04);
DECLARE_SPRITE_BANK(05);
DECLARE_SPRITE_BANK(06);
DECLARE_SPRITE_BANK(07);
DECLARE_SPRITE_BANK(08);
DECLARE_SPRITE_BANK(09);
DECLARE_SPRITE_BANK(10);
DECLARE_SPRITE_BANK(11);
DECLARE_SPRITE_BANK(12);
DECLARE_SPRITE_BANK(13);
DECLARE_SPRITE_BANK(14);
DECLARE_SPRITE_BANK(15);
DECLARE_SPRITE_BANK(17);
DECLARE_SPRITE_BANK(18);
DECLARE_SPRITE_BANK(19);
DECLARE_SPRITE_BANK(20);
DECLARE_SPRITE_BANK(21);
DECLARE_SPRITE_BANK(22);
DECLARE_SPRITE_BANK(23);
DECLARE_SPRITE_BANK(24);
DECLARE_SPRITE_BANK(25);
DECLARE_SPRITE_BANK(26);
DECLARE_SPRITE_BANK(27);
DECLARE_SPRITE_BANK(28);
DECLARE_SPRITE_BANK(29);
DECLARE_SPRITE_BANK(30);
DECLARE_SPRITE_BANK(31);
DECLARE_SPRITE_BANK(32);
DECLARE_SPRITE_BANK(33);

extern SaturnSpriteResource g_Stage02SharedBreakableResource;

void* g_Stage02SpriteBanks[35] = {
    g_Stage02SpriteBank00, g_Stage02SpriteBank01, g_Stage02SpriteBank02,
    g_Stage02SpriteBank03, g_Stage02SpriteBank04, g_Stage02SpriteBank05,
    g_Stage02SpriteBank06, g_Stage02SpriteBank07, g_Stage02SpriteBank08,
    g_Stage02SpriteBank09, g_Stage02SpriteBank10, g_Stage02SpriteBank11,
    g_Stage02SpriteBank12, g_Stage02SpriteBank13, g_Stage02SpriteBank14,
    g_Stage02SpriteBank15, &g_Stage02SharedBreakableResource,
    g_Stage02SpriteBank17,
    g_Stage02SpriteBank18, g_Stage02SpriteBank19, g_Stage02SpriteBank20,
    g_Stage02SpriteBank21, g_Stage02SpriteBank22, g_Stage02SpriteBank23,
    g_Stage02SpriteBank24, g_Stage02SpriteBank25, g_Stage02SpriteBank26,
    g_Stage02SpriteBank27, g_Stage02SpriteBank28, g_Stage02SpriteBank29,
    g_Stage02SpriteBank30, g_Stage02SpriteBank31, g_Stage02SpriteBank32,
    g_Stage02SpriteBank33, NULL,
};
