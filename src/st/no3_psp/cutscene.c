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

static void func_pspeu_09243108(void) {
    g_Dialogue.nextLineY = g_Dialogue.startY + 0x14;
    g_Dialogue.nextCharX = g_Dialogue.nextLineX = 0x180;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.unk12 = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk17 = 2;
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_09243168);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_09243378);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_092433B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", func_pspeu_09243748);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/cutscene", NO3_EntityCutscene);
