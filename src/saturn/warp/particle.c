// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} WarpSoulStealOrbSpriteRect;

void EntityWarpDummy(Entity* self);
void EntityWarpStageNamePopup(Entity* self);

extern struct SpriteParts* g_EntitySpriteBank08[];

u8 g_WarpSoulStealOrbAnim[] = {
    4, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 3, 0, 0,
};

WarpSoulStealOrbSpriteRect g_WarpSoulStealOrbSpriteRects[6] = {
    {-3, -3, 8, 8},     {-3, -3, 8, 8},     {-7, -7, 16, 15},
    {-11, -11, 24, 23}, {-11, -11, 24, 23}, {-11, -11, 24, 23},
};

u16 g_WarpSoulStealOrbAngles[8] = {
    0x820, 0x840, 0x860, 0x880, 0x8C0, 0x900, 0x940, 0xA00,
};

EntityEntry g_WarpDummyEntry = {
    g_EntitySpriteBank08,
    EntityWarpDummy,
};

EntityEntry g_WarpStageNamePopupEntry = {
    NULL,
    EntityWarpStageNamePopup,
};
