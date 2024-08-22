// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return (g_randomNext >> 0x18) & 0xFF;
}
