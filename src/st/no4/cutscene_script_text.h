// SPDX-License-Identifier: AGPL-3.0-or-later
// This is likely close enough to be shared, but is not shared currently since
// we don't know yet if any other overlays use these specific changes

// The CUTSCENE_UNK1_NEXT_X, CUTSCENE_UNK1_UNK17, and NUM_CUTSCENE_PRIM macros
// must be defined in the overlay

// pspeu needs this to not be static
#ifdef VERSION_US
static
#endif
    void
    CutsceneUnk1(void) {
    g_Dialogue.nextCharX = CUTSCENE_UNK1_NEXT_X;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk17 = CUTSCENE_UNK1_UNK17;
#ifdef VERSION_PSP
    g_Dialogue.startX = 52;
    g_Dialogue.nextLineY = 44;
    g_Dialogue.clutIndex = 417;
    g_Dialogue.unk12 = 0;
    g_Dialogue.nextLineX = 0;
    g_Dialogue.startY = 24;
#endif
}

static u8 SetCutsceneScript(u8* script) {
    Primitive* prim;

    g_Dialogue.primIndex[2] =
        g_api.AllocPrimitives(PRIM_SPRT, NUM_CUTSCENE_PRIM);

    if (g_Dialogue.primIndex[2] != -1) {
        g_Dialogue.scriptCur = script;
        g_Dialogue.primIndex[1] = -1;
        g_Dialogue.primIndex[0] = -1;
        CutsceneUnk1();

        prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[1] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[2] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[3] = prim->next;

#ifdef VERSION_PSP
        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[4] = prim->next;
#endif

        prim->type = PRIM_GT4;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_G4;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
        prim->b0 = prim->b1 = 127;
        prim->x0 = prim->x2 = 4;
        prim->x1 = prim->x3 = 248;
        prim->priority = 509;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->r0 = prim->g0 = prim->b0 = 16;
        prim->x0 = 3;
        prim->y0 = 47;
        prim->v0 = 74;
        prim->priority = 508;
        prim->drawMode = DRAW_HIDE;
        return 1;
    }

    g_Dialogue.primIndex[2] = 0;
    return 0;
}
