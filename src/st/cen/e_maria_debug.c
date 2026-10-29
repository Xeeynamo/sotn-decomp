// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

// This file mirrors pl_debug in the Maria overlay
void MarDebugOff() { g_MarDebug.enabled = false; }

void MarDebugEnter(void) {
    g_MarDebug.enabled = true;
    g_MarDebug.curFrame = MARIA.animCurFrame;
    g_MarDebug.drawFlags = MARIA.drawFlags;
    g_MarDebug.palette = MARIA.palette;
}

void MarDebugExit(void) {
    g_MarDebug.enabled = false;
    MARIA.animCurFrame = g_MarDebug.curFrame;
    MARIA.drawFlags = g_MarDebug.drawFlags;
    MARIA.palette = g_MarDebug.palette;
    MARIA.hitParams = 0;
}

bool MarDebug(void) {
    if (!g_MarDebug.enabled) {
        if (g_Maria.padTapped & PAD_L2 && g_Maria.demo_timer == 0) {
            MarDebugEnter();
            return true;
        }
        return false;
    }

    if (g_Maria.demo_timer != 0) {
        MarDebugExit();
        return false;
    }

    if (g_Maria.padTapped & PAD_L2) {
        MarDebugExit();
        return false;
    }
    if (g_Maria.padPressed & PAD_CROSS) {
        if (g_Maria.padPressed & PAD_RIGHT) {
            MARIA.posX.val += FIX(16.0);
        }
        if (g_Maria.padPressed & PAD_LEFT) {
            MARIA.posX.val -= FIX(16.0);
        }
        if (g_Maria.padPressed & PAD_UP) {
            MARIA.posY.val -= FIX(16.0);
        }
        if (g_Maria.padPressed & PAD_DOWN) {
            MARIA.posY.val += FIX(16.0);
        }

    } else {
        if (g_Maria.padTapped & PAD_RIGHT) {
            MARIA.posX.val += FIX(16.0);
        }
        if (g_Maria.padTapped & PAD_LEFT) {
            MARIA.posX.val -= FIX(16.0);
        }
        if (g_Maria.padTapped & PAD_UP) {
            MARIA.posY.val -= FIX(16.0);
        }
        if (g_Maria.padTapped & PAD_DOWN) {
            MARIA.posY.val += FIX(16.0);
        }
    }

    if (g_Maria.padTapped & PAD_CIRCLE) {
        MARIA.animCurFrame--;
    }
    if (g_Maria.padTapped & PAD_SQUARE) {
        MARIA.animCurFrame++;
    }

    if (MARIA.animCurFrame <= 0) {
        MARIA.animCurFrame = 1;
    }
    if (MARIA.animCurFrame > 211) {
        MARIA.animCurFrame = 211;
    }
    FntPrint("charal:%02x\n", MARIA.animCurFrame);
    return true;
}
