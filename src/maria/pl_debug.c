// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

void MarDebugOff() { g_IsMarDebugEnter = false; }

static void MarDebugEnter(void) {
    g_IsMarDebugEnter = true;
    g_MarDebugCurFrame = PLAYER.animCurFrame;
    g_MarDebugDrawFlags = PLAYER.drawFlags;
    g_MarDebugPalette = PLAYER.palette;
}

static void MarDebugExit(void) {
    g_IsMarDebugEnter = false;
    PLAYER.animCurFrame = g_MarDebugCurFrame;
    PLAYER.drawFlags = g_MarDebugDrawFlags;
    PLAYER.palette = g_MarDebugPalette;
    PLAYER.hitParams = 0;
}

bool MarDebug(void) {
    if (!g_IsMarDebugEnter) {
        if (g_Player.padTapped & PAD_L2) {
            if (g_Player.demo_timer == 0) {
                MarDebugEnter();
                return true;
            }
        }
        return false;
    }
    if (g_Player.demo_timer) {
        MarDebugExit();
        return false;
    }
    if (g_Player.padTapped & PAD_L2) {
        MarDebugExit();
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
