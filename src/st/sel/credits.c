// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;

// BSS
static u16 D_801BB0F8[0x30][0x30];

#if REGION == REGION_EU
// PAL credits use taller lines and scroll one pixel every 3 frames instead of 4
#define CREDITS_LINE_H 20
#define CREDITS_ENTRY_GAP 7
#define CREDITS_SECTION_GAP 15
#define CREDITS_SCROLL_FRAMES 3
#else
#define CREDITS_LINE_H 19
#define CREDITS_ENTRY_GAP 6
#define CREDITS_SECTION_GAP 12
#define CREDITS_SCROLL_FRAMES 4
#endif

u8 func_801B76F0(u8* msg) {
    // aliases g_Dialogue.prim[1]; TODO must split like src/st/st0/3101C_psx.c
    const int PRIM = -LEN(g_Dialogue.prim);
    Primitive* prim;
    s16 i;
    s16 temp_v0;

    g_Dialogue.primIndex[PRIM] = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (g_Dialogue.primIndex[PRIM] != -1) {
        g_Dialogue.scriptCur = msg;
        g_Dialogue.startY = g_Dialogue.nextCharX = 0x200;
#if VERSION >= VER_JP12
        g_Dialogue.startY += 36;
#else
        g_Dialogue.startY += 11;
#endif
        g_Dialogue.nextLineX = 0;
        g_Dialogue.nextCharY = 0;
        g_Dialogue.portraitAnimTimer = 0;
        g_Dialogue.unk12 = 0;
        g_Dialogue.clutIndex = 0;
        g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[PRIM]];
        prim = &g_PrimBuf[g_Dialogue.primIndex[PRIM]];
        for (i = 0; i < 0x20; i++) {
            temp_v0 = i & 1;
            if (temp_v0) {
                prim->tpage = 9;
                prim->x0 = 0xF8;
            } else {
                prim->tpage = 8;
                prim->x0 = 0x18;
            }
            temp_v0 = i >> 1;
            prim->u0 = 0;
            prim->v0 = temp_v0 * 0x10;
            prim->u1 = 0xF0;
            prim->v1 = 0x10;
            prim->y0 = temp_v0 * CREDITS_LINE_H + 0xF0;
            prim->clut = PAL_UNK_1A1;
            prim->x1 = 0;
            prim->priority = 3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }

        return 1;
    }
    g_Dialogue.primIndex[PRIM] = 0;
    return 0;
}

void func_801B786C(s16 nextCharY) {
    RECT rect;

    rect.x = 0x200;
    rect.y = nextCharY * 0x10;
    rect.w = 0x80;
    rect.h = 0x10;
    ClearImage(&rect, 0, 0, 0);
}

u16* func_801B78BC(char ch) {
    u16 jCh;
#ifndef PLATFORM_PSYZ

    if (ch >= 'a') {
        jCh = ('ａ' - 'a') + ch;
    } else if (ch >= 'A') {
        jCh = ('Ａ' - 'A') + ch;
    } else if (ch == ',') {
        jCh = '，';
    } else if (ch == '/') {
        jCh = '／';
    } else if (ch == '.') {
        jCh = '．';
    } else if (ch == '-') {
        jCh = '−';
    } else if (ch == '(') {
        jCh = '（';
    } else if (ch == ')') {
        jCh = '）';
    } else if (ch == '\'') {
        jCh = '’';
    } else if (ch == '&') {
        jCh = '＆';
    } else if (ch == '"') {
        jCh = '”';
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

s32 EntityCutsceneCredits(Entity* entity) {
    Primitive* prim;
    int bitDepth;
    u16 nextChar;
    u16 glyphIndex;
    u16* glyph;
    u16 y;
    s16 y0;
    s32 i;
    u16* var_s4;

    switch (entity->step) {
    case 0:
        if (func_801B76F0(cutscene_credits)) {
            entity->flags |= FLAG_HAS_PRIMS;
            entity->primIndex = (s32)g_Dialogue.prim[1];
            entity->step++;
            func_801B786C(0);
            glyphIndex = 0;
            while (true) {
                nextChar = *g_Dialogue.scriptCur++;
                if (nextChar == 1) {
                    g_Dialogue.startY =
                        g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
                    g_Dialogue.nextLineX++;
                    break;
                }
                glyph = func_801B78BC(nextChar);
                if (glyph != NULL) {
                    var_s4 = D_801BB0F8[glyphIndex];
                    for (i = 0; i < 0x30; i++) {
                        *var_s4++ = *glyph++;
                    }
                    glyph = D_801BB0F8[glyphIndex];
                    y = g_Dialogue.nextLineX * 0x10;
                    LoadTPage(
                        (u_long*)glyph, 0, 0, g_Dialogue.startY, y, 12, 16);
                    g_Dialogue.startY += 3;
                    nextChar = g_Dialogue.startY - g_Dialogue.nextCharX;
                    if (nextChar >= 0x38 && nextChar < 0x40) {
                        g_Dialogue.startY += 8;
                    }
                    glyphIndex++;
                } else {
                    g_Dialogue.startY += 2;
                    nextChar = g_Dialogue.startY - g_Dialogue.nextCharX;
                    if (nextChar >= 0x38 && nextChar < 0x40) {
                        g_Dialogue.startY += 8;
                    }
                }
            }
        }
        break;
    case 1:
        if (!LOHU(g_Dialogue.nextCharY)) {
            break;
        }
        nextChar = 0;
        glyphIndex = 0;
        nextChar = *g_Dialogue.scriptCur++;
        bitDepth = 0;

        switch (nextChar) {
        case CSOP_END_CREDITS:
            entity->step = 7;
#if VERSION >= VER_US
            g_Dialogue.unk12 = 0x400;
#else
            g_Dialogue.unk12 = 0x600;
#endif
            return 0;
        case CSOP_SUBTEXT:
            g_Dialogue.startY = g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
            g_Dialogue.nextLineX++;
            if (g_Dialogue.nextLineX > 0xF) {
                g_Dialogue.nextLineX = 0;
            }
            g_Dialogue.nextCharY = 0;
            return 0;
        case CSOP_ENTRY:
            g_Dialogue.startY = g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
            g_Dialogue.nextLineX++;
            if (g_Dialogue.nextLineX > 0xF) {
                g_Dialogue.nextLineX = 0;
            }

            prim = g_Dialogue.prim[0];
            for (i = 0; i < g_Dialogue.nextLineX; i++) {
                prim = prim->next;
                prim = prim->next;
            }

            y0 = prim->y0;
            prim = g_Dialogue.prim[0];
            while (prim != NULL) {
                if (y0 <= prim->y0) {
                    prim->y0 += CREDITS_ENTRY_GAP;
                    prim->x1 += CREDITS_ENTRY_GAP;
                }
                prim = prim->next;
            }
            g_Dialogue.unk12 += CREDITS_SCROLL_FRAMES * CREDITS_ENTRY_GAP;
            g_Dialogue.portraitAnimTimer += CREDITS_ENTRY_GAP;
            g_Dialogue.nextCharY = 0;
            return 0;
        case CSOP_SECTION:
            g_Dialogue.startY = g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
            g_Dialogue.nextLineX++;
            if (g_Dialogue.nextLineX > 0xF) {
                g_Dialogue.nextLineX = 0;
            }
            prim = g_Dialogue.prim[0];
            for (i = 0; i < g_Dialogue.nextLineX; i++) {
                prim = prim->next;
                prim = prim->next;
            }

            y0 = prim->y0;
            prim = g_Dialogue.prim[0];
            while (prim != NULL) {
                if (y0 <= prim->y0) {
                    prim->y0 += CREDITS_SECTION_GAP;
                    prim->x1 += CREDITS_SECTION_GAP;
                }
                prim = prim->next;
            }
            g_Dialogue.unk12 += CREDITS_SCROLL_FRAMES * CREDITS_SECTION_GAP;
            g_Dialogue.portraitAnimTimer += CREDITS_SECTION_GAP;
            g_Dialogue.nextCharY = 0;
            return 0;
        default:
            if (nextChar & 0x80) {
                nextChar <<= 8;
                nextChar += *g_Dialogue.scriptCur++;
                glyph = g_api.func_80106A28(nextChar, 0);
            } else {
                glyph = func_801B78BC(nextChar);
            }
            if (glyph != NULL) {
                y = g_Dialogue.nextLineX * 0x10;
                LoadTPage(
                    (u_long*)glyph, bitDepth, 0, g_Dialogue.startY, y, 12, 16);
                g_Dialogue.startY += 3;
                nextChar = g_Dialogue.startY - g_Dialogue.nextCharX;
                if (nextChar >= 0x38 && nextChar < 0x40) {
                    g_Dialogue.startY += 8;
                }
            } else {
                g_Dialogue.startY += 3;
                nextChar = g_Dialogue.startY - g_Dialogue.nextCharX;
                if (nextChar >= 0x38 && nextChar < 0x40) {
                    do {
                        g_Dialogue.startY += 8;
                    } while (0);
                }
            }
            break;
        }
        break;
    case 2:
        break;
    case 7:
        if (!--g_Dialogue.unk12) {
            return 1;
        } else {
            return 0;
        }
    }

    if (!g_Dialogue.unk12) {
        func_801B786C(g_Dialogue.nextLineX);
        g_Dialogue.nextCharY = 1;
        g_Dialogue.unk12 = CREDITS_SCROLL_FRAMES * CREDITS_LINE_H;
    }
    g_Dialogue.unk12--;
    if (!g_Dialogue.clutIndex) {
        prim = g_Dialogue.prim[0];
        for (i = 0; i < 0x20; i++) {
            prim->y0--;
            if (prim->y0 == -CREDITS_LINE_H) {
                prim->y0 = g_Dialogue.portraitAnimTimer - prim->x1 +
                           CREDITS_LINE_H * 15;
                prim->x1 = g_Dialogue.portraitAnimTimer;
            }
            prim = prim->next;
        }
        g_Dialogue.clutIndex = CREDITS_SCROLL_FRAMES;
    }
    g_Dialogue.clutIndex--;
    return 0;
}
