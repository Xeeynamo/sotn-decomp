// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

void RicDebugOff() { g_IsRicDebugEnter = false; }

static void RicDebugEnter(void) {
    g_IsRicDebugEnter = true;
    g_RicDebugCurFrame = PLAYER.animCurFrame;
    g_RicDebugDrawFlags = PLAYER.drawFlags;
    g_RicDebugPalette = PLAYER.palette;
}

static void RicDebugExit(void) {
    g_IsRicDebugEnter = false;
    PLAYER.animCurFrame = g_RicDebugCurFrame;
    PLAYER.drawFlags = g_RicDebugDrawFlags;
    PLAYER.palette = g_RicDebugPalette;
    PLAYER.hitParams = 0;
}

bool RicDebug(void) {
    if (!g_IsRicDebugEnter) {
        if (g_Player.padTapped & PAD_L2) {
            if (g_Player.pl_demo_timer == 0) {
                RicDebugEnter();
                return true;
            }
        }
        return false;
    }
    if (g_Player.pl_demo_timer) {
        RicDebugExit();
        return false;
    }
    if (g_Player.padTapped & PAD_L2) {
        RicDebugExit();
        return false;
    }
    if (g_Player.padPressed & PAD_CROSS) {
        if (g_Player.padPressed & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0);
        }
        if (g_Player.padPressed & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0);
        }
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0);
        }
        if (g_Player.padPressed & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0);
        }

    } else {
        if (g_Player.padTapped & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0);
        }
        if (g_Player.padTapped & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0);
        }
        if (g_Player.padTapped & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0);
        }
        if (g_Player.padTapped & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0);
        }
    }

    if (g_Player.padTapped & PAD_CIRCLE) {
        PLAYER.animCurFrame--;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        PLAYER.animCurFrame++;
    }

    if (PLAYER.animCurFrame <= 0) {
        PLAYER.animCurFrame = 1;
    }
    if (PLAYER.animCurFrame > 211) {
        PLAYER.animCurFrame = 211;
    }
    FntPrint("charal:%02x\n", PLAYER.animCurFrame);
    return true;
}
