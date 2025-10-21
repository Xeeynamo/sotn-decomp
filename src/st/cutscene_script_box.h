// SPDX-License-Identifier: AGPL-3.0-or-later
// The CUTSCENE_UNK3_RECT_X and CUTSCENE_UNK4_TPAGE macros must be defined in
// the overlay

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

#ifdef CUTSCENE_UNK4_HAS_ARGS
static void CutsceneUnk4(s32 nextLineY) {
#else
static void CutsceneUnk4(void) {
#endif
    Primitive* prim;

    CutsceneUnk3(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = CUTSCENE_UNK4_TPAGE;
#ifdef CUTSCENE_UNK4_HAS_ARGS
    prim->clut = 0x1A1;
    prim->x0 = 56;
    prim->u0 = 0;
    prim->y0 = nextLineY + 44;
    prim->v0 = nextLineY - 128;
#else
    prim->clut = g_Dialogue.clutIndex;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.startX + 4;
    prim->v0 = g_Dialogue.nextCharY * 12 + 128;
#endif
    prim->u1 = 192;
    prim->v1 = 12;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}
