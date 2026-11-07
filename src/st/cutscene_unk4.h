// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef CUTSCENE_UNK4_TPAGE
#define CUTSCENE_UNK4_TPAGE 0x10
#endif

#ifndef CUTSCENE_UNK4_V_OFFSET
#define CUTSCENE_UNK4_V_OFFSET 128
#endif

void CutsceneUnk4(void) {
    Primitive* prim;

    CutsceneUnk3(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = CUTSCENE_UNK4_TPAGE;
    prim->clut = g_Dialogue.clutIndex;
#if CUTSCENE_EARLY_VER
    prim->x0 = g_Dialogue.startX;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->v0 = g_Dialogue.nextCharY * 16 + CUTSCENE_UNK4_V_OFFSET;
    prim->u1 = 0xC0;
    prim->v1 = 16;
#else
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.startX + 4;
    prim->v0 = g_Dialogue.nextCharY * 12 + CUTSCENE_UNK4_V_OFFSET;
    prim->u1 = 0xC0;
    prim->v1 = 12;
#endif
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}
