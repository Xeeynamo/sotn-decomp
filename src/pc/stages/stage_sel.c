// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../../st/sel/sel.h"
#include "../pc.h"
#include "sfx.h"
#include <string.h>
#include <cutscene.h>

extern const char* D_801803A8[10];

// stubs
RECT D_80182584 = {0};
RECT D_8018258C = {0};
RECT D_801825A4 = {0};
u8* D_8018C404[100] = {NULL};

extern Overlay OVL_EXPORT(Overlay);

s32 LoadFileSim(s32 fileId, s32 type);

static bool g_WereStringsInitialised = false;
void InitStageSEL(Overlay* o) {
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    if (!g_WereStringsInitialised) {
        g_WereStringsInitialised = true;
        for (int i = 0; i < LEN(D_80180128); i++) {
            D_80180128[i].line1 = AnsiToSotnMenuString(D_80180128[i].line1);
            D_80180128[i].line2 = AnsiToSotnMenuString(D_80180128[i].line2);
        }
        for (int i = 0; i < LEN(D_801803A8); i++) {
            D_801803A8[i] = AnsiToSotnMenuString(D_801803A8[i]);
        }
    }
}

void func_801B9C80(void) {
    // handles the video playback
    // reset D_8003C728 to signal the end of video playback
    D_8003C728 = 0;
}
