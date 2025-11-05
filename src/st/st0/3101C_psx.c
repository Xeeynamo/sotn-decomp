// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <cutscene.h>

// This file uses g_Dialogue with a different struct than the usual.
// It is based on struct Dialogue, which is used in cutscene.c
// pspeu uses two independent memory addresses for 3101C.c and cutscene.c with
// us sharing a single memory address via union
extern DialogueST0 g_Dialogue;

static u16 D_801BEE90[48][48]; // bss

static u8 unused[] = {0x00, 0x81, 0x17, 0x08, 0x80, 0x08,
                      0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00};

u8 func_801B101C(u8* script) {
    Primitive* prim;
    s16 i;
    s16 shift;

    g_Dialogue.alt.primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (g_Dialogue.alt.primIndex != -1) {
        g_Dialogue.alt.scriptCur = script;
        g_Dialogue.alt.nextCharX = 0x200;
        g_Dialogue.alt.startY = 0x216;
        g_Dialogue.alt.nextLineX = 0;
        g_Dialogue.alt.nextCharY = 0;
        g_Dialogue.alt.portraitAnimTimer = 0;
        g_Dialogue.alt.unk12 = 0;
        g_Dialogue.alt.clutIndex = 0;
        prim = g_Dialogue.alt.prim = &g_PrimBuf[g_Dialogue.alt.primIndex];
        for (i = 0; i < 0x20; i++) {
            shift = i & 1;
            if (shift) {
                prim->tpage = 9;
                prim->x0 = 0x100;
            } else {
                prim->tpage = 8;
                prim->x0 = 0x20;
            }
            shift = i >> 1;
            prim->u0 = 0;
            prim->v0 = shift * 0x10;
            prim->u1 = 0xF0;
            prim->v1 = 0x10;
            prim->y0 = shift * 0x16 + 0xF0;
            prim->clut = 0x221;
            prim->priority = 3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }

        return true;
    }
    g_Dialogue.alt.primIndex = 0;
    return false;
}

void func_801B1198(s16 yVal) {
    RECT rect;
    rect.x = 0x200;
    rect.y = yVal * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

u16* func_801B11E8(u8 ch) {
    u16 jCh;
#ifndef VERSION_PC
    if (ch >= 'a') {
        jCh = ('ａ' - 'a') + ch;
    } else if (ch >= 'A') {
        jCh = ('Ａ' - 'A') + ch;
    } else if (ch == ',') {
        jCh = '，';
    } else if (ch == '.') {
        jCh = '．';
    } else if (ch == '\'') {
        jCh = '’';
    } else if (ch == ' ') {
        return NULL;
    } else {
        jCh = ('Ａ' - 'A') + ch;
        if (ch >= 'a') {
            ++jCh;
        }
    }
#else
    jCh = 'A';
#endif

    return g_api.func_80106A28(jCh, 0);
}

#include "prologue_cutscene_script.h"

void func_801B1298(Entity* self) {
    s16 y0;
    Primitive* prim;
    s32 i;
    u16* glyph;
    u16 nextChar;
    u16* glyphPtr;
    u16 glyphIndex;
    u16 y;

    switch (self->step) {
    case 0:
        if (func_801B101C((u8*)prologue_script_en)) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = g_Dialogue.alt.primIndex;
            ++self->step;
            func_801B1198(0);
            glyphIndex = 0;
            while (1) {
                nextChar = *g_Dialogue.alt.scriptCur++;
                if (nextChar == 1) {
                    // Gets weirdly relocated in the asm.
                    g_Dialogue.alt.startY =
                        g_Dialogue.alt.nextCharX + *g_Dialogue.alt.scriptCur++;
                    ++g_Dialogue.alt.nextLineX;
                    break;
                }
                glyph = func_801B11E8(nextChar);
                if (glyph) {
                    glyphPtr = D_801BEE90[glyphIndex];
                    for (i = 0; i < 0x30; ++i) {
                        glyphPtr++[0] = glyph++[0];
                    }
                    glyph = D_801BEE90[glyphIndex];
                    y = g_Dialogue.alt.nextLineX * 16;
                    LoadTPage(
                        (u_long*)glyph, 0, 0, g_Dialogue.alt.startY, y, 12, 16);
                    g_Dialogue.alt.startY += 3;
                    nextChar = g_Dialogue.alt.startY - g_Dialogue.alt.nextCharX;
                    if (0x38 <= nextChar && nextChar < 0x40) {
                        g_Dialogue.alt.startY += 8;
                    }
                    glyphIndex++;
                } else {
                    g_Dialogue.alt.startY += 2;
                    nextChar = g_Dialogue.alt.startY - g_Dialogue.alt.nextCharX;
                    if (0x38 <= nextChar && nextChar < 0x40) {
                        g_Dialogue.alt.startY += 8;
                    }
                }
            }
        }
        break;
    case 1:
        if (!g_Dialogue.alt.nextCharY) {
            break;
        }
        nextChar = 0;
        glyphIndex = 0;
        do {
            nextChar = *g_Dialogue.alt.scriptCur++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;
            case 1:
                g_Dialogue.alt.startY =
                    g_Dialogue.alt.nextCharX + *g_Dialogue.alt.scriptCur++;
                g_Dialogue.alt.nextLineX++;
                if (g_Dialogue.alt.nextLineX > 15) {
                    g_Dialogue.alt.nextLineX = 0;
                }
                g_Dialogue.alt.nextCharY = 0;
                return;
            case 2:
                g_Dialogue.alt.startY =
                    g_Dialogue.alt.nextCharX + *g_Dialogue.alt.scriptCur++;
                g_Dialogue.alt.nextLineX++;
                if (g_Dialogue.alt.nextLineX > 15) {
                    g_Dialogue.alt.nextLineX = 0;
                }

                prim = g_Dialogue.alt.prim;
                for (i = 0; i < g_Dialogue.alt.nextLineX; ++i) {
                    prim = prim->next;
                    prim = prim->next;
                }

                y0 = prim->y0;
                for (prim = g_Dialogue.alt.prim; prim != NULL;
                     prim = prim->next) {
                    if (y0 <= prim->y0) {
                        prim->y0 += 0x16;
                        prim->p1 += 0x16;
                    }
                }
                g_Dialogue.alt.unk12 += 0x58;
                g_Dialogue.alt.portraitAnimTimer += 0x16;
                g_Dialogue.alt.nextCharY = 0;
                return;
            }
        } while (0);
        glyph = func_801B11E8(nextChar);

        if (glyph) {
            y = g_Dialogue.alt.nextLineX * 16;
            LoadTPage(
                (u_long*)glyph, 0, 0, g_Dialogue.alt.startY, y, 0xC, 0x10);
            g_Dialogue.alt.startY += 3;
        } else {
            g_Dialogue.alt.startY += 2;
        }
        nextChar = g_Dialogue.alt.startY - g_Dialogue.alt.nextCharX;
        if (0x38 <= nextChar && nextChar < 0x40) {
            g_Dialogue.alt.startY += 8;
        }
        break;
    case 2:
        break;
    case 7:
        if (g_Dialogue.alt.nextCharY) {
            g_Dialogue.alt.nextLineX++;
            if (g_Dialogue.alt.nextLineX > 15) {
                g_Dialogue.alt.nextLineX = 0;
            }
            g_Dialogue.alt.nextCharY = 0;
        }
    }

    if (!g_Dialogue.alt.unk12) {
        func_801B1198(g_Dialogue.alt.nextLineX);
        g_Dialogue.alt.nextCharY = 1;
        g_Dialogue.alt.unk12 = 88;
    }
    --g_Dialogue.alt.unk12;
    if (!g_Dialogue.alt.clutIndex) {
        for (prim = g_Dialogue.alt.prim, i = 0; i < 32; ++i) {
            prim->y0--;
            if (prim->y0 == -22) {
                prim->y0 = g_Dialogue.alt.portraitAnimTimer - prim->p1 + 330;
                prim->p1 = g_Dialogue.alt.portraitAnimTimer;
            }
            prim = prim->next;
        }
        g_Dialogue.alt.clutIndex = 4;
    }
    --g_Dialogue.alt.clutIndex;
}
