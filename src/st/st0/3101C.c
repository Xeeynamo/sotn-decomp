// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "dialogue2.h"
#include "disk.h"

// This file uses g_Dialogue with a different struct than the usual.
// It is based on struct Dialogue, which is used in cutscene.c
extern Dialogue2 g_Dialogue;
u8 func_801B101C(u8* script) {
    Primitive* prim;
    s16 i;

    g_Dialogue.primIndex[0] = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (g_Dialogue.primIndex[0] != -1) {
        g_Dialogue.nextCharX = 0x200;
        g_Dialogue.scriptCur = script;
        g_Dialogue.startY = 0x216;
        g_Dialogue.nextLineX = 0;
        g_Dialogue.nextCharY = 0;
        g_Dialogue.portraitAnimTimer = 0;
        g_Dialogue.unk12 = 0;
        g_Dialogue.clutIndex = 0;
        g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[0]];
        prim = &g_PrimBuf[g_Dialogue.primIndex[0]];
        for (i = 0; i < 0x20; i++) {
            if (i & 1) {
                prim->tpage = 9;
                prim->x0 = 0x100;
            } else {
                prim->tpage = 8;
                prim->x0 = 0x20;
            }
            prim->v0 = (i >> 1) * 0x10;
            prim->u0 = 0;
            prim->u1 = 0xF0;
            prim->v1 = 0x10;
            prim->y0 = (i >> 1) * 0x16 + 0xF0;
            prim->clut = 0x221;
            prim->priority = 3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }

        return true;
    }
    g_Dialogue.primIndex[0] = 0;
    return false;
}

void func_801B1198(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

u16* func_801B11E8(unsigned char ch) {
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

extern u8 D_80182C58[];
extern u16 D_801BEE90[][0x30];
// Resembles SEL func_801B79D4
void func_801B1298(Entity* self) {
    s32 i;
    Primitive* prim;
    u16 y;
    u16 glyphIndex;
    u16* var_v1;
    u16 nextChar;
    u16* glyph;
    s16 y0;

    switch (self->step) {
    case 0:
        if (func_801B101C(D_80182C58)) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = g_Dialogue.primIndex[0];
            ++self->step;
            func_801B1198(0);
            glyphIndex = 0;
            while (1) {
                nextChar = *g_Dialogue.scriptCur++;
                if (nextChar == 1) {
                    // Gets weirdly relocated in the asm.
                    g_Dialogue.startY =
                        g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
                    ++g_Dialogue.nextLineX;
                    break;
                }
                glyph = func_801B11E8(nextChar);
                if (glyph) {
                    var_v1 = &D_801BEE90[glyphIndex][0];
                    for (i = 0; i < 0x30; ++i) {
                        var_v1++[0] = glyph++[0];
                    }
                    glyph = D_801BEE90[glyphIndex];
                    y = g_Dialogue.nextLineX * 16;
                    LoadTPage(
                        (u_long*)glyph, 0, 0, g_Dialogue.startY, y, 12, 16);
                    g_Dialogue.startY += 3;
                    y = g_Dialogue.startY - g_Dialogue.nextCharX;
                    if (0x38 <= y && y < 0x40) {
                        g_Dialogue.startY += 8;
                    }
                    ++glyphIndex;
                } else {
                    g_Dialogue.startY += 2;
                    y = g_Dialogue.startY - g_Dialogue.nextCharX;
                    if (0x38 <= y && y < 0x40) {
                        g_Dialogue.startY += 8;
                    }
                }
            }
        }
        break;
    case 1:
        if (!g_Dialogue.nextCharY) {
            break;
        }
        nextChar = 0;
        glyphIndex = 0;
        do {
            nextChar = *g_Dialogue.scriptCur++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;
            case 1:
                g_Dialogue.startY =
                    g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
                g_Dialogue.nextLineX++;
                if (g_Dialogue.nextLineX > 15) {
                    g_Dialogue.nextLineX = 0;
                }
                g_Dialogue.nextCharY = 0;
                return;
            case 2:
                g_Dialogue.startY =
                    g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
                g_Dialogue.nextLineX++;
                if (g_Dialogue.nextLineX > 15) {
                    g_Dialogue.nextLineX = 0;
                }

                prim = g_Dialogue.prim[0];
                for (i = 0; i < g_Dialogue.nextLineX; ++i) {
                    prim = prim->next;
                    prim = prim->next;
                }

                y0 = prim->y0;
                for (prim = g_Dialogue.prim[0]; prim != NULL;
                     prim = prim->next) {
                    if (y0 <= prim->y0) {
                        prim->y0 += 0x16;
                        prim->p1 += 0x16;
                    }
                }
                g_Dialogue.unk12 += 0x58;
                g_Dialogue.portraitAnimTimer += 0x16;
                g_Dialogue.nextCharY = 0;
                return;
            }
        } while (0);
        glyph = func_801B11E8(nextChar);

        if (glyph) {
            y = g_Dialogue.nextLineX * 16;
            LoadTPage((u_long*)glyph, 0, 0, g_Dialogue.startY, y, 0xC, 0x10);
            g_Dialogue.startY += 3;
        } else {
            g_Dialogue.startY += 2;
        }
        y = g_Dialogue.startY - g_Dialogue.nextCharX;
        if (0x38 <= y && y < 0x40) {
            g_Dialogue.startY += 8;
        }
        break;
    case 2:
        break;
    case 7:
        if (g_Dialogue.nextCharY) {
            g_Dialogue.nextLineX++;
            if (g_Dialogue.nextLineX > 15) {
                g_Dialogue.nextLineX = 0;
            }
            g_Dialogue.nextCharY = 0;
        }
    }

    if (!g_Dialogue.unk12) {
        func_801B1198(g_Dialogue.nextLineX);
        g_Dialogue.nextCharY = 1;
        g_Dialogue.unk12 = 88;
    }
    --g_Dialogue.unk12;
    if (!g_Dialogue.clutIndex) {
        for (prim = g_Dialogue.prim[0], i = 0; i < 32; ++i) {
            prim->y0--;
            if (prim->y0 == -22) {
                prim->y0 = g_Dialogue.portraitAnimTimer - prim->p1 + 330;
                prim->p1 = g_Dialogue.portraitAnimTimer;
            }
            prim = prim->next;
        }
        g_Dialogue.clutIndex = 4;
    }
    --g_Dialogue.clutIndex;
}
