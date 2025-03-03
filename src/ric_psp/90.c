// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

static void RicDebugEnter(void) {
    g_IsRicDebugEnter = true;
    g_RicDebugCurFrame = PLAYER.animCurFrame;
    g_RicDebugDrawFlags = PLAYER.drawFlags;
    g_RicDebugPalette = PLAYER.palette;
}

void RicDebugExit(void) {
    g_IsRicDebugEnter = false;
    PLAYER.animCurFrame = g_RicDebugCurFrame;
    PLAYER.drawFlags = g_RicDebugDrawFlags;
    PLAYER.palette = g_RicDebugPalette;
    PLAYER.hitParams = 0;
}

INCLUDE_ASM("ric_psp/nonmatchings/90", RicDebug);
