// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef CUTSCENE_UNK3_RECT_X
#define CUTSCENE_UNK3_RECT_X 0
#endif

#if defined(VERSION_PSP)
extern s32 cutsceneUnk3Unknown[0x380]; // bss
#endif

static void CutsceneUnk3(s16 nextCharY) {
    RECT rect;
    rect.x = CUTSCENE_UNK3_RECT_X;
    rect.y = (nextCharY * 12) + 384;
    rect.w = 64;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
#if defined(VERSION_PSP)
    func_890A3C0(cutsceneUnk3Unknown, 0, LEN(cutsceneUnk3Unknown));
#endif
}
