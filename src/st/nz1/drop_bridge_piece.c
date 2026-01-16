// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

void DropBridgePiece(void) {
    s32 i, j;
    s32 fgIndex, xIndex, yIndex;
    s32 x = g_CurrentEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;
    s32 y = g_CurrentEntity->posY.i.hi + g_Tilemap.scrollY.i.hi;
    xIndex = x - 64;
    yIndex = y - 32;

    for (i = 0; i < 4; i++) {
        y = i * 16 + yIndex;
        for (j = 0; j < 8; j++) {
            x = j * 16 + xIndex;
            fgIndex = (x >> 4) + (((y >> 4) * g_Tilemap.hSize) << 4);
            g_Tilemap.fg[fgIndex] = 0;
        }
    }
}
