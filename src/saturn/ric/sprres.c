// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage g_RichterSpritePackage1Images[];
extern u16 g_RichterSpritePackage1Palette[];
extern SaturnSpriteImage g_RichterSpritePackage2Images[];
extern u16 g_RichterSpritePackage2Palette[];
extern SaturnSpriteImage g_RichterSpritePackage3Images[];
extern u16 g_RichterSpritePackage3Palette[];
extern SaturnSpriteImage g_RichterSpritePackage4Images[];
extern u16 g_RichterSpritePackage4Palette[];
extern SaturnSpriteImage g_RichterSpritePackage5Images[];
extern u16 g_RichterSpritePackage5Palette[];
extern SaturnSpriteImage g_RichterSpritePackage6Images[];
extern u16 g_RichterSpritePackage6Palette[];
extern SaturnSpriteImage g_RichterSpritePackage7Images[];
extern u16 g_RichterSpritePackage7Palette[];
extern SaturnSpriteImage g_RichterSpritePackage8Images[];
extern u16 g_RichterSpritePackage8Palette[];
extern SaturnSpriteImage g_RichterSpritePackage9Images[];
extern u16 g_RichterSpritePackage9Palette[];
extern SaturnSpriteImage g_RichterSpritePackage10Images[];
extern u16 g_RichterSpritePackage10Palette[];
extern struct SpriteParts* g_EntitySpriteBank15[];

SaturnSpriteResource g_RichterSpriteResources[10] = {
    {g_RichterSpritePackage1Images, g_RichterSpritePackage1Palette, -1, 0xFFFF},
    {g_RichterSpritePackage3Images, g_RichterSpritePackage3Palette, -1, 0xFFFF},
    {g_RichterSpritePackage4Images, g_RichterSpritePackage4Palette, -1, 0xFFFF},
    {g_RichterSpritePackage5Images, g_RichterSpritePackage5Palette, -1, 0xFFFF},
    {g_RichterSpritePackage6Images, g_RichterSpritePackage6Palette, -1, 0xFFFF},
    {g_RichterSpritePackage2Images, g_RichterSpritePackage2Palette, -1, 0xFFFF},
    {g_RichterSpritePackage7Images, g_RichterSpritePackage7Palette, -1, 0xFFFF},
    {g_RichterSpritePackage8Images, g_RichterSpritePackage8Palette, -1, 0xFFFF},
    {g_RichterSpritePackage9Images, g_RichterSpritePackage9Palette, -1, 0xFFFF},
    {g_RichterSpritePackage10Images, g_RichterSpritePackage10Palette, -1, 0xFFFF},
};

void* g_RichterSpriteBanks[17] = {
    &g_RichterSpriteResources[0], g_EntitySpriteBank15,
    g_EntitySpriteBank15,         g_EntitySpriteBank15,
    g_EntitySpriteBank15,         &g_RichterSpriteResources[1],
    &g_RichterSpriteResources[2], &g_RichterSpriteResources[3],
    &g_RichterSpriteResources[4], &g_RichterSpriteResources[5],
    &g_RichterSpriteResources[6], &g_RichterSpriteResources[7],
    &g_RichterSpriteResources[8], &g_RichterSpriteResources[9],
    g_EntitySpriteBank15,         g_EntitySpriteBank15,
    NULL,
};
