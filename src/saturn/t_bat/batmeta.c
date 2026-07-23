// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

extern SaturnSpriteResource* g_BatResourceDescriptors[2];

SaturnSpriteResource** g_BatResourceDescriptorList = g_BatResourceDescriptors;

u16 g_BatOverlayLoadMetadata[14] = {
    0xFFFF, 0xFFFF, 0x0100, 0x0000, 0x64A2, 0x4100, 0x1CA3,
    0x4100, 0xD9F2, 0x0000, 0xFFFF, 0xFFFF, 0x0400, 0x0000,
};
