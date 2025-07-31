// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

void MarDebugOff() { g_MarDebug.enabled = false; }

static void MarDebugEnter(void) {
    g_MarDebug.enabled = true;
    g_MarDebug.curFrame = PLAYER.animCurFrame;
    g_MarDebug.drawFlags = PLAYER.drawFlags;
    g_MarDebug.palette = PLAYER.palette;
}

static void MarDebugExit(void) {
    g_MarDebug.enabled = false;
    PLAYER.animCurFrame = g_MarDebug.curFrame;
    PLAYER.drawFlags = g_MarDebug.drawFlags;
    PLAYER.palette = g_MarDebug.palette;
    PLAYER.hitParams = 0;
}

bool MarDebug(void) {
    if (!g_MarDebug.enabled) {
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
            PLAYER.posX.val += FIX(16.0);
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.posX.val -= FIX(16.0);
        }
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0);
        }
        if (g_Player.padPressed & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0);
        }

    } else {
        if (g_Player.padTapped & PAD_RIGHT) {
            PLAYER.posX.val += FIX(16.0);
        }
        if (g_Player.padTapped & PAD_LEFT) {
            PLAYER.posX.val -= FIX(16.0);
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
