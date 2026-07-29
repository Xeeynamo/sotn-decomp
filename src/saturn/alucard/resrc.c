// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteImage AlucardImages[];
extern SaturnSpriteImage AlucardSubImages[];
extern SaturnSpriteImage AlucardFxImages[];
extern SaturnSpriteImage AlucardFx2Images[];
extern SaturnSpriteImage AlucardPkg3Images[];
extern SaturnSpriteImage AlucardPkg4Images[];
extern SaturnSpriteImage AlucardPkg5Images[];
extern SaturnSpriteImage AlucardPkg6Images[];
extern SaturnSpriteImage AlucardPkg7Images[];
extern SaturnSpriteImage AlucardPkg8Images[];
extern SaturnSpriteImage AlucardPkg9Images[];
extern SaturnSpriteImage AlucardPkg10Images[];

extern u16 g_AlucardPalettes[];
extern u16 g_AlucardPaletteShades[];
extern u16 AlucardSubPalette[];
extern u16 AlucardFxPalette[];
extern u16 AlucardFx2Palette[];
extern u16 AlucardPkg3Palette[];
extern u16 AlucardPkg4Palette[];
extern u16 AlucardPkg5Palette[];
extern u16 AlucardPkg6Palette[];
extern u16 AlucardPkg7Palette[];
extern u16 AlucardPkg8Palette[];
extern u16 AlucardPkg9Palette[];
extern u16 AlucardPkg10Palette[];

SaturnSpriteResource AlucardSpriteResources[13] = {
    {AlucardImages, g_AlucardPalettes, -1, 0xFFFF},
    {AlucardImages, g_AlucardPaletteShades, -1, 0xFFFF},
    {AlucardSubImages, AlucardSubPalette, -1, 0xFFFF},
    {AlucardFxImages, AlucardFxPalette, -1, 0xFFFF},
    {AlucardFx2Images, AlucardFx2Palette, -1, 0xFFFF},
    {AlucardPkg3Images, AlucardPkg3Palette, -1, 0xFFFF},
    {AlucardPkg4Images, AlucardPkg4Palette, -1, 0xFFFF},
    {AlucardPkg5Images, AlucardPkg5Palette, -1, 0xFFFF},
    {AlucardPkg6Images, AlucardPkg6Palette, -1, 0xFFFF},
    {AlucardPkg7Images, AlucardPkg7Palette, -1, 0xFFFF},
    {AlucardPkg8Images, AlucardPkg8Palette, -1, 0xFFFF},
    {AlucardPkg9Images, AlucardPkg9Palette, -1, 0xFFFF},
    {AlucardPkg10Images, AlucardPkg10Palette, -1, 0xFFFF},
};
