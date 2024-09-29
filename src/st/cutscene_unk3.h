// SPDX-License-Identifier: AGPL-3.0-or-later
static void CutsceneUnk3(s16 arg0) {
    RECT rect;

    rect.y = (arg0 * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}
