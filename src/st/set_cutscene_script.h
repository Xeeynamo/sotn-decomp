// SPDX-License-Identifier: AGPL-3.0-or-later

#if defined(VERSION_PC)
#define NUM_CUTSCENE_PRIM 8
#else
#define NUM_CUTSCENE_PRIM 7
#endif

static u8 SetCutsceneScript(u8* script) {
    Primitive* prim;

    OVL_EXPORT(Dialogue).primIndex[2] =
        g_api.AllocPrimitives(PRIM_SPRT, NUM_CUTSCENE_PRIM);

    if (OVL_EXPORT(Dialogue).primIndex[2] != -1) {
        OVL_EXPORT(Dialogue).scriptCur = script;
        OVL_EXPORT(Dialogue).unk3C = 0;
        OVL_EXPORT(Dialogue).primIndex[1] = -1;
        OVL_EXPORT(Dialogue).primIndex[0] = -1;
        CutsceneUnk1();

        prim = OVL_EXPORT(Dialogue).prim[0] =
            &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[2]];

        prim->drawMode = DRAW_HIDE;
        prim = OVL_EXPORT(Dialogue).prim[1] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = OVL_EXPORT(Dialogue).prim[2] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = OVL_EXPORT(Dialogue).prim[3] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = OVL_EXPORT(Dialogue).prim[4] = prim->next;

#if !defined(VERSION_PSP) && !defined(VERSION_HD)
        prim->drawMode = DRAW_HIDE;
        prim = OVL_EXPORT(Dialogue).prim[5] = prim->next;
#endif

        prim->type = PRIM_GT4;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_G4;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
        prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
        prim->x0 = prim->x2 = 4;
        prim->x1 = prim->x3 = 0xF8;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->r0 = prim->g0 = prim->b0 = 0xFF;
        prim->x0 = 3;
        prim->y0 = 0x2F;
        prim->v0 = 0x4A;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_HIDE;
        return 1;
    }

    OVL_EXPORT(Dialogue).primIndex[2] = 0;
    return 0;
}
