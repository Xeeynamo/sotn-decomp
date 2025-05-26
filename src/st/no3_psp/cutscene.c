// SPDX-License-Identifier: AGPL-3.0-or-later

#include "../no3/no3.h"

// this is getlang
INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_09242C00);

// this is DrawCutsceneActorName
INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_09242CA0);


extern s32 D_pspeu_09299478[];
static void CutsceneUnk3(s16 yOffset) {
    RECT rect;

    rect.x = 384;
    rect.y = (yOffset * 12) + 256;
    rect.w = 64;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
    func_890A3C0(&D_pspeu_09299478, 0, 0x380);
}
static void func_pspeu_09243040(void) {
    Primitive* prim;

    CutsceneUnk3(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = 0x16;
    prim->clut = g_Dialogue.clutIndex;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.startX + 4;
    prim->v0 = g_Dialogue.nextCharY * 0xC;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}

// CutsceneUnk1
static void func_pspeu_09243108(void) {
    g_Dialogue.nextLineY = g_Dialogue.startY + 0x14;
    g_Dialogue.nextCharX = g_Dialogue.nextLineX = 0x180;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.unk12 = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk17 = 2;
}

// SetCutsceneScript
static u8 func_pspeu_09243168(u8* script) {
    Primitive* prim;

    g_Dialogue.primIndex[2] = g_api.AllocPrimitives(PRIM_SPRT,
#if defined(VERSION_PC)
                                                    8
#else
                                                    7
#endif
    );

    if (g_Dialogue.primIndex[2] != -1) {
        g_Dialogue.scriptCur = script;
        g_Dialogue.unk3C = 0;
        g_Dialogue.primIndex[1] = -1;
        g_Dialogue.primIndex[0] = -1;
        func_pspeu_09243108();

        prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[1] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[2] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[3] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[4] = prim->next;

#ifndef VERSION_PSP
        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[5] = prim->next;
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

    g_Dialogue.primIndex[2] = 0;
    return 0;
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_09243378);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_092433B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_09243748);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", NO3_EntityCutscene);
