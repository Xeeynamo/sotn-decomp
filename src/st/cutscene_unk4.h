// SPDX-License-Identifier: AGPL-3.0-or-later

// st0 uses a union for g_Dialogue
#ifdef STAGE_IS_ST0
#define G_DIALOGUE g_Dialogue.std
#else
#define G_DIALOGUE g_Dialogue
#endif

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
    void
    CutsceneUnk4(void) {
    Primitive* prim;

    CutsceneUnk3(G_DIALOGUE.nextCharY);
    prim = G_DIALOGUE.prim[G_DIALOGUE.nextCharY];
    prim->tpage = CUTSCENE_UNK4_TPAGE;
    prim->clut = G_DIALOGUE.clutIndex;
#ifdef VERSION_HD
    prim->x0 = G_DIALOGUE.startX;
#endif
    prim->y0 = G_DIALOGUE.nextLineY;
    prim->u0 = 0;
#ifndef VERSION_HD
    prim->x0 = G_DIALOGUE.startX + 4;
#endif
    prim->v0 = G_DIALOGUE.nextCharY * CUTSCENE_UNK4_V + 0x80;
    prim->u1 = 0xC0;
    prim->v1 = CUTSCENE_UNK4_V;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}
