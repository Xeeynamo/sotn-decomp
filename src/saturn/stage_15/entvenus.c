// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource g_Stage15SpriteBank28;

void func_060ECE0C(Entity* self);
void func_060ED1C0(Entity* self);
void func_060ED848(Entity* self);
void func_060EDA88(Entity* self);
void func_060EDD10(Entity* self);

EntityEntry g_Stage15EntityVenusManTrap = {
    &g_Stage15SpriteBank28, func_060ECE0C};
s16 g_Stage15VenusManTrapInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry54 = {&g_Stage15SpriteBank28, func_060ED1C0};
s16 g_Stage15VenusManTrapFlowerInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry56 = {&g_Stage15SpriteBank28, func_060ED848};
s16 g_Stage15VenusManTrapTendrilInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry57 = {&g_Stage15SpriteBank28, func_060EDA88};
s16 g_Stage15VenusManTrapDartInitOffset[2] = {0, 0};
EntityEntry g_Stage15EntityEntry55 = {&g_Stage15SpriteBank28, func_060EDD10};

u8 g_Stage15VenusManTrapAnimationData[] = {
    /* Animation 0 */
    2,
    1,
    6,
    2,
    6,
    3,
    6,
    4,
    0xFF,
    0xFF,
    /* Animation 1 */
    6,
    5,
    6,
    6,
    6,
    7,
    6,
    8,
    0xFF,
    0xFF,
    /* Animation 2 */
    2,
    9,
    6,
    0xA,
    6,
    0xB,
    6,
    0xC,
    0xFF,
    0xFF,
    /* Animation 3 */
    6,
    0xD,
    6,
    0xE,
    6,
    0xF,
    6,
    0x10,
    0xFF,
    0xFF,
    /* Animation 4 */
    2,
    0x13,
    2,
    0x14,
    0xFF,
    0xFF,
    /* Animation 5 */
    2,
    0x16,
    2,
    0x17,
    0xFF,
    0xFF,
    /* Animation 6 */
    4,
    0x18,
    3,
    0x19,
    2,
    0x1A,
    2,
    0x1B,
    0xFF,
    0xFF,
};
u16 g_Stage15VenusManTrapAnimationsPadding = 0;
u8* g_Stage15VenusManTrapAnimations[] = {
    &g_Stage15VenusManTrapAnimationData[0],
    &g_Stage15VenusManTrapAnimationData[10],
    &g_Stage15VenusManTrapAnimationData[20],
    &g_Stage15VenusManTrapAnimationData[30],
    &g_Stage15VenusManTrapAnimationData[40],
    &g_Stage15VenusManTrapAnimationData[46],
    &g_Stage15VenusManTrapAnimationData[52],
};
