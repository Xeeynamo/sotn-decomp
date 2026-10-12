// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include "../../st/sel/sel.h"
#include "../pc.h"
#include <string.h>
#include <cutscene.h>
#include "overlay.h"

extern const char* D_801803A8[10];

// stubs
RECT D_80182584 = {0};
RECT D_8018258C = {0};
RECT D_801825A4 = {0};
u8* D_8018C404[100] = {NULL};

// SEL owns a copy as on PSX, so banks.c can point to it from a static table
u16 g_saveIconPal[] = {
#include "../../st/sel/gen/g_saveIconPal.h"
};

extern Overlay g_Overlay;

s32 LoadFileSim(s32 fileId, s32 type);

void Psyz_ModuleStart(void* param) {
    Overlay* o = param;
    memcpy(o, &g_Overlay, sizeof(Overlay));
}

void Psyz_ModuleStop(void) {}

void func_801B9C80(void) {
    // handles the video playback
    // reset D_8003C728 to signal the end of video playback
    D_8003C728 = 0;
}
