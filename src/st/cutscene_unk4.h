// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CUTSCENE_UNK4_TPAGE
#define CUTSCENE_UNK4_TPAGE 0x10
#endif

#ifdef VERSION_HD
#define CUTSCENE_UNK4_V 16
#else
#define CUTSCENE_UNK4_V 12
#endif

#ifndef VERSION_HD
static
#endif
    void CutsceneUnk4(void) {
    Primitive* prim;

    CutsceneUnk3(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = CUTSCENE_UNK4_TPAGE;
    prim->clut = g_Dialogue.clutIndex;
#ifdef VERSION_HD
    prim->x0 = g_Dialogue.startX;
#endif
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
#ifndef VERSION_HD
    prim->x0 = g_Dialogue.startX + 4;
#endif
    prim->v0 = g_Dialogue.nextCharY * CUTSCENE_UNK4_V + 0x80;
    prim->u1 = 0xC0;
    prim->v1 = CUTSCENE_UNK4_V;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}
