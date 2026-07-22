// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

// Opaque extension between the player callback header and SH-2 text.
const u16 g_MariaOverlayHeaderStub[] = {
    0xF84B, 0x4100, 0xEC4B, 0x4100, 0xE04B, 0x4100, 0xD44B,
    0x4100, 0xCC4B, 0x4100, 0xC44B, 0x4100, 0xBC4B, 0x4100,
};
