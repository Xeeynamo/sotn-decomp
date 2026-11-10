// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef CUTSCENE_UNK3_RECT_X
#define CUTSCENE_UNK3_RECT_X 0
#endif

#ifndef CUTSCENE_UNK3_RECT_Y
#define CUTSCENE_UNK3_RECT_Y 384
#endif

#if TARGET == TARGET_PSP
extern u8 cutsceneUnk3Unknown[0x380]; // bss
#endif

static void CutsceneUnk3(s16 nextCharY) {
    RECT rect;
    rect.x = CUTSCENE_UNK3_RECT_X;
#if CUTSCENE_EARLY_VER
    rect.y = (nextCharY * 16) + CUTSCENE_UNK3_RECT_Y;
    rect.w = 64;
    rect.h = 16;
#else
    rect.y = (nextCharY * 12) + CUTSCENE_UNK3_RECT_Y;
    rect.w = 64;
    rect.h = 12;
#endif
    ClearImage(&rect, 0, 0, 0);
#if TARGET == TARGET_PSP
    memset(cutsceneUnk3Unknown, 0, LEN(cutsceneUnk3Unknown));
#endif
}
