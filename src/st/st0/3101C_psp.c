// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <cutscene.h>

// This file uses g_Dialogue with a different struct than the usual.
// It is based on struct Dialogue, which is used in cutscene.c
// pspeu uses two independent memory addresses for 3101C.c and cutscene.c with
// us sharing a single memory address via union
static DialogueST0 g_Dialogue;             // bss
static UnkPrimStruct D_pspeu_0927B0C8[32]; // bss
static u16 D_pspeu_0927B0C0;               // bss
static u16 D_pspeu_0927B0B8;               // bss
static u16 D_801BEE90[48][48];             // bss

#include "prologue_cutscene_script.h"

static u16 clut_fr_de_it[] = {3, 3};
static u16 unk20_fr_de_it[] = {64, 65, 65, 0};
static u16 clut_en_es[] = {3, 4, 4, 4};
static u16 unk20_en_es[] = {84, 83, 84, 0};

static char opening_line_en[] = "Count Dracula had risen, with,";
static char opening_line_fr[] = "Le Comte Dracula \330tait";
static char opening_line_es[] = "El Conde Dr\323cula hab\334a";
static char opening_line_de[] = "Graf Dracula war mithilfe";
static char opening_line_it[] = "Il Conte Dracula \xD7 risorto";

extern s32 g_UserLanguage;

static void SetPrim(s32 i, Primitive* prim) { D_pspeu_0927B0C8[i].prim = prim; }

static void SetPrimYZero(s32 i, s16 prim_y0) {
    D_pspeu_0927B0C8[i].y0 = prim_y0;
}

u8 func_801B101C(u8* script) {
    Primitive* prim;
    s16 i;
    s16 shift;

    D_pspeu_0927B0C0 = 0;
    D_pspeu_0927B0B8 = 0;
    g_Dialogue.alt.primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (g_Dialogue.alt.primIndex != -1) {
        g_Dialogue.alt.scriptCur = script;

        g_Dialogue.alt.startY = g_Dialogue.alt.nextCharX = 0x200;

        switch (g_UserLanguage) {
        default:
        case LANG_EN:
            g_Dialogue.alt.startY += func_pspeu_09242F68((u8*)opening_line_en);
            g_Dialogue.alt.clutIndexes = clut_en_es;
            g_Dialogue.alt.unk20 = unk20_en_es;
            g_Dialogue.alt.clutArrLength = 4;
            break;
        case LANG_FR:
            g_Dialogue.alt.startY += func_pspeu_09242F68((u8*)opening_line_fr);
            g_Dialogue.alt.clutIndexes = clut_fr_de_it;
            g_Dialogue.alt.unk20 = unk20_fr_de_it;
            g_Dialogue.alt.clutArrLength = 2;
            break;
        case LANG_SP:
            g_Dialogue.alt.startY += func_pspeu_09242F68((u8*)opening_line_es);
            g_Dialogue.alt.clutIndexes = clut_en_es;
            g_Dialogue.alt.unk20 = unk20_en_es;
            g_Dialogue.alt.clutArrLength = 4;
            break;
        case LANG_GE:
            g_Dialogue.alt.startY += func_pspeu_09242F68((u8*)opening_line_de);
            g_Dialogue.alt.clutIndexes = clut_fr_de_it;
            g_Dialogue.alt.unk20 = unk20_fr_de_it;
            g_Dialogue.alt.clutArrLength = 2;
            break;
        case LANG_IT:
            g_Dialogue.alt.startY += func_pspeu_09242F68((u8*)opening_line_it);
            g_Dialogue.alt.clutIndexes = clut_fr_de_it;
            g_Dialogue.alt.unk20 = unk20_fr_de_it;
            g_Dialogue.alt.clutArrLength = 2;
            break;
        }
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
            SetPrim(i, prim);
            SetPrimYZero(i, prim->y0);
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
    u8 sp1F;
    char sp1C[3];

    sp1C[0] = ch;
    sp1C[1] = 0;
    sp1C[2] = 0;

    jCh = g_api.func_psp_0913F960(sp1C, &sp1F);
    return g_api.func_psp_0913FA28(jCh, 0);
}

static s32 func_pspeu_09242F68(u8* text) {
    u32 i;

    for (i = 0;; text++, i++) {
        *text &= 0xFF;

        switch (*text) {
        case 0:
        case 1:
        case 2:
            return 0x3C - ((i * 3) / 2);
        }
    }
}

void func_801B1298(Entity* self) {
    s16 y0;
    u16 nextLineTwo;
    s32 arrLen;
    Primitive* prim;
    s32 i;
    u16* glyph;
    u16 nextChar;
    u16* glyphPtr;
    u16 primV0;
    u16 glyphIndex;
    u16 y;
    u16 nextLineOne;

    switch (self->step) {
    case 0:
        g_Dialogue.alt.script = GetLangAt(
            0, (u8*)prologue_script_en, (u8*)prologue_script_fr,
            (u8*)prologue_script_es, (u8*)prologue_script_de,
            (u8*)prologue_script_it);
        if (func_801B101C(g_Dialogue.alt.script)) {
            func_8925F7C(0x100, 0xF1, 0x10, 1);
            func_8925F7C(0x110, 0xF2, 0x10, 1);
            func_8925F7C(0x100, 0xF0, 0x10, 1);
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = g_Dialogue.alt.primIndex;
            ++self->step;
            func_801B1198(0);
            glyphIndex = 0;
            while (1) {
                nextChar = *g_Dialogue.alt.scriptCur++;
                if (nextChar == 1) {
                    // Gets weirdly relocated in the asm.
                    *g_Dialogue.alt.scriptCur++;
                    g_Dialogue.alt.startY =
                        g_Dialogue.alt.nextCharX +
                        func_pspeu_09242F68(g_Dialogue.alt.scriptCur);
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
                prim = g_Dialogue.alt.prim;
                nextLineOne = (g_Dialogue.alt.nextLineX & 0xFFFF & 0xFFFF) * 16;
                nextLineTwo = (g_Dialogue.alt.nextLineX & 0xFFFF & 0xFFFF) * 16;
                for (i = 0; i < 0x20; i++) {
                    primV0 = prim->v0;

                    if (primV0 < nextLineOne) {
                        primV0 += 0x100;
                    }

                    if (primV0 > nextLineOne && primV0 <= nextLineTwo) {
                        prim->drawMode = DRAW_HIDE;
                    }
                    prim = prim->next;
                }
                return;
            case 1:
                *g_Dialogue.alt.scriptCur++;
                g_Dialogue.alt.startY =
                    g_Dialogue.alt.nextCharX +
                    func_pspeu_09242F68(g_Dialogue.alt.scriptCur);
                g_Dialogue.alt.nextLineX++;
                if (g_Dialogue.alt.nextLineX > 15) {
                    g_Dialogue.alt.nextLineX = 0;
                }
                func_801B1198(g_Dialogue.alt.nextLineX);
                g_Dialogue.alt.nextCharY = 0;
                return;
            case 2:
                *g_Dialogue.alt.scriptCur++;
                g_Dialogue.alt.startY =
                    g_Dialogue.alt.nextCharX +
                    func_pspeu_09242F68(g_Dialogue.alt.scriptCur);
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
                g_Dialogue.alt.unk12 +=
                    g_Dialogue.alt.unk20[D_pspeu_0927B0B8++ % 3];
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
            nextChar = g_Dialogue.alt.startY - g_Dialogue.alt.nextCharX;
            if (0x38 <= nextChar && nextChar < 0x40) {
                g_Dialogue.alt.startY += 8;
            }
        } else {
            g_Dialogue.alt.startY += 2;
            nextChar = g_Dialogue.alt.startY - g_Dialogue.alt.nextCharX;
            if (0x38 <= nextChar && nextChar < 0x40) {
                g_Dialogue.alt.startY += 8;
            }
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
        g_Dialogue.alt.unk12 = g_Dialogue.alt.unk20[D_pspeu_0927B0B8++ % 3];
    }
    --g_Dialogue.alt.unk12;
    if (!g_Dialogue.alt.clutIndex) {
        for (prim = g_Dialogue.alt.prim, i = 0; i < 32; ++i) {
            prim->y0--;
            if (prim->y0 == -22) {
                prim->y0 = g_Dialogue.alt.portraitAnimTimer - prim->p1 + 330;
                prim->p1 = g_Dialogue.alt.portraitAnimTimer;
                if (self->step == 7) {
                    prim->drawMode = DRAW_HIDE;
                }
            }
            prim = prim->next;
        }
        arrLen = g_Dialogue.alt.clutArrLength;
        g_Dialogue.alt.clutIndex =
            g_Dialogue.alt.clutIndexes[D_pspeu_0927B0C0++ % arrLen];
    }
    --g_Dialogue.alt.clutIndex;
}
