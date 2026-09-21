// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

// Likely copied out of DRA, unused in RNO1
static void DebugShowWaitInfo(const char* msg) {
    static s32 g_DebugWaitInfoTimer;

    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (g_DebugWaitInfoTimer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

static void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}