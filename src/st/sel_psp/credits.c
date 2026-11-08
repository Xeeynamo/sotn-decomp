// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sel/sel.h"
#include <cutscene.h>

// BSS
static Dialogue4 D_psp_09287E60;
static u16 D_801BB0F8[0x30][0x30];

extern u8* D_psp_09285B98;

static u32 D_psp_09285928[] = {6, 5, 6, 5};

u8 func_801B76F0(u8* msg) {
    Primitive* prim;
    s16 i;
    s16 temp_v0;

    D_psp_09287E60.primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    D_psp_09287E60.nextCharTimer = 0;
    if (D_psp_09287E60.primIndex != -1) {
        D_psp_09287E60.scriptCur = msg;
        D_psp_09287E60.startY = D_psp_09287E60.nextCharX = 0x200;
        D_psp_09287E60.startY += 0xB;
        D_psp_09287E60.nextLineX = 0;
        D_psp_09287E60.nextCharY = 0;
        D_psp_09287E60.portraitAnimTimer = 0;
        D_psp_09287E60.unk12 = 0;
        D_psp_09287E60.clutIndex = 0;
        prim = &g_PrimBuf[D_psp_09287E60.primIndex];
        D_psp_09287E60.prim = prim;
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
            prim->y0 = temp_v0 * 0x13 + 0xF0;
            prim->clut = PAL_UNK_1A1;
            prim->x1 = 0;
            prim->priority = 3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }

        return 1;
    }
    D_psp_09287E60.primIndex = 0;
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

    return g_api.func_80106A28(jCh, 0);
}

s32 func_801B79D4(Entity* entity) {
    Primitive* prim;
    u16 nextChar;
    u16 glyphIndex;
    u16* glyph;
    u16 y;
    s16 y0;
    s32 i;
    u16* var_s4;

    DisableAutoPowerOff();
    switch (entity->step) {
    case 0:
        if (func_801B76F0(D_psp_09285B98)) {
            entity->flags |= FLAG_HAS_PRIMS;
            entity->primIndex = D_psp_09287E60.primIndex;
            entity->step++;
            func_801B786C(0);
            glyphIndex = 0;
            while (true) {
                nextChar = *D_psp_09287E60.scriptCur++;
                if (nextChar == 1) {
                    D_psp_09287E60.startY =
                        D_psp_09287E60.nextCharX + *D_psp_09287E60.scriptCur++;
                    D_psp_09287E60.nextLineX++;
                    break;
                }
                glyph = func_801B78BC(nextChar);
                if (glyph != NULL) {
                    var_s4 = D_801BB0F8[glyphIndex];
                    for (i = 0; i < 0x30; i++) {
                        *var_s4++ = *glyph++;
                    }
                    glyph = D_801BB0F8[glyphIndex];
                    y = D_psp_09287E60.nextLineX * 0x10;
                    LoadTPage(
                        (u_long*)glyph, 0, 0, D_psp_09287E60.startY, y, 12, 16);
                    D_psp_09287E60.startY += 3;
                    nextChar = D_psp_09287E60.startY - D_psp_09287E60.nextCharX;
                    if (nextChar >= 0x38 && nextChar < 0x40) {
                        D_psp_09287E60.startY += 8;
                    }
                    glyphIndex++;
                } else {
                    D_psp_09287E60.startY += 2;
                    nextChar = D_psp_09287E60.startY - D_psp_09287E60.nextCharX;
                    if (nextChar >= 0x38 && nextChar < 0x40) {
                        D_psp_09287E60.startY += 8;
                    }
                }
            }
        }
        break;

    case 1:
        if (!D_psp_09287E60.nextCharY) {
            break;
        }
        nextChar = 0;
        glyphIndex = 0;
        nextChar = *D_psp_09287E60.scriptCur++;
        switch (nextChar) {
        case 0:
            entity->step = 7;
            D_psp_09287E60.unk12 = 0x300;
            return 0;

        case 1:
            D_psp_09287E60.startY =
                D_psp_09287E60.nextCharX + *D_psp_09287E60.scriptCur++;
            D_psp_09287E60.nextLineX++;
            if (D_psp_09287E60.nextLineX > 0xF) {
                D_psp_09287E60.nextLineX = 0;
            }
            D_psp_09287E60.nextCharY = 0;
            return 0;

        case 2:
            D_psp_09287E60.startY =
                D_psp_09287E60.nextCharX + *D_psp_09287E60.scriptCur++;
            D_psp_09287E60.nextLineX++;
            if (D_psp_09287E60.nextLineX > 0xF) {
                D_psp_09287E60.nextLineX = 0;
            }
            prim = D_psp_09287E60.prim;
            for (i = 0; i < D_psp_09287E60.nextLineX; i++) {
                prim = prim->next;
                prim = prim->next;
            }
            y0 = prim->y0;
            prim = D_psp_09287E60.prim;
            while (prim != NULL) {
                if (y0 <= prim->y0) {
                    prim->y0 += 6;
                    prim->x1 += 6;
                }
                prim = prim->next;
            }
            D_psp_09287E60.unk12 += 0x21;
            D_psp_09287E60.portraitAnimTimer += 6;
            D_psp_09287E60.nextCharY = 0;
            return 0;

        case 3:
            D_psp_09287E60.startY =
                D_psp_09287E60.nextCharX + *D_psp_09287E60.scriptCur++;
            D_psp_09287E60.nextLineX++;
            if (D_psp_09287E60.nextLineX > 0xF) {
                D_psp_09287E60.nextLineX = 0;
            }
            prim = D_psp_09287E60.prim;
            for (i = 0; i < D_psp_09287E60.nextLineX; i++) {
                prim = prim->next;
                prim = prim->next;
            }
            y0 = prim->y0;
            prim = D_psp_09287E60.prim;
            while (prim != NULL) {
                if (y0 <= prim->y0) {
                    prim->y0 += 12;
                    prim->x1 += 12;
                }
                prim = prim->next;
            }
            D_psp_09287E60.unk12 += 0x42;
            D_psp_09287E60.portraitAnimTimer += 12;
            D_psp_09287E60.nextCharY = 0;
            return 0;

        default:
            if (nextChar & 0x80) {
                nextChar <<= 8;
                nextChar += *D_psp_09287E60.scriptCur++;
                glyph = g_api.func_80106A28(nextChar, 0);
            } else {
                glyph = func_801B78BC(nextChar);
            }
            if (glyph != NULL) {
                y = D_psp_09287E60.nextLineX * 0x10;
                LoadTPage(
                    (u_long*)glyph, 0, 0, D_psp_09287E60.startY, y, 12, 16);
                D_psp_09287E60.startY += 3;
                nextChar = D_psp_09287E60.startY - D_psp_09287E60.nextCharX;
                if (nextChar >= 0x38 && nextChar < 0x40) {
                    D_psp_09287E60.startY += 8;
                }
            } else {
                D_psp_09287E60.startY += 3;
                nextChar = D_psp_09287E60.startY - D_psp_09287E60.nextCharX;
                if (nextChar >= 0x38 && nextChar < 0x40) {
                    D_psp_09287E60.startY += 8;
                }
            }
            break;
        }
        break;

    case 2:
        break;

    case 7:
        if (!--D_psp_09287E60.unk12) {
            return 1;
        } else {
            return 0;
        }
    }
    if (!D_psp_09287E60.unk12) {
        func_801B786C(D_psp_09287E60.nextLineX);
        D_psp_09287E60.nextCharY = 1;
        D_psp_09287E60.unk12 = 0x69;
    }
    D_psp_09287E60.unk12--;
    if (!D_psp_09287E60.clutIndex) {
        prim = D_psp_09287E60.prim;
        for (i = 0; i < 0x20; i++) {
            prim->y0--;
            if (prim->y0 == -19) {
                prim->y0 =
                    D_psp_09287E60.portraitAnimTimer - (s16)prim->x1 + 0x11D;
                prim->x1 = D_psp_09287E60.portraitAnimTimer;
            }
            prim = prim->next;
        }
        D_psp_09287E60.nextCharTimer++;
        D_psp_09287E60.nextCharTimer %= 4;
        D_psp_09287E60.clutIndex = D_psp_09285928[D_psp_09287E60.nextCharTimer];
    }
    D_psp_09287E60.clutIndex--;
    return 0;
}
