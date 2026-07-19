// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void func_060E633C(Entity* self);
void func_060E6628(Entity* self);

extern struct SpriteParts* g_Stage02SpriteBank06[];

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Stage02SoulStealOrbSpriteRect;

EntityEntry g_Stage02EntityEntry06 = {
    g_Stage02SpriteBank06, func_060E633C};
EntityEntry g_Stage02EntityEntry12 = {NULL, func_060E6628};

u8 g_Stage02SoulStealOrbAnim[14] = {
    4, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 3, 0, 0,
};

Stage02SoulStealOrbSpriteRect g_Stage02SoulStealOrbSpriteRects[6] = {
    {-3, -3, 8, 8},
    {-3, -3, 8, 8},
    {-7, -7, 16, 15},
    {-11, -11, 24, 23},
    {-11, -11, 24, 23},
    {-11, -11, 24, 23},
};

u16 g_Stage02SoulStealOrbAngles[8] = {
    0x820, 0x840, 0x860, 0x880, 0x8C0, 0x900, 0x940, 0xA00,
};
u16 g_Stage02SoulStealOrbAnglesPadding = 0;
