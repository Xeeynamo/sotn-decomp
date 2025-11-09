// SPDX-License-Identifier: AGPL-3.0-or-later
// Animates the portrait size of the actor by enlarging or shrinking it
static void ScaleCutsceneAvatar(const u8 ySteps) {
    const int PrimCount = 5;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    primIndex = g_Dialogue.nextCharY + 1;
    while (primIndex >= PrimCount) {
        primIndex -= PrimCount;
    }
    if (g_CurrentEntity->step_s == 0) {
        prim = g_Dialogue.prim[primIndex];
        prim->v0 += ySteps;
        prim->v1 -= ySteps;
        if (prim->v1 == 0) {
            g_CurrentEntity->step_s++;
            prim->drawMode = DRAW_HIDE;
        }
    }

    for (i = 0; i < PrimCount; i++) {
        if (i != primIndex) {
            prim = g_Dialogue.prim[i];
            prim->y0 -= ySteps;
        }
    }
    g_Dialogue.portraitAnimTimer++;
}
