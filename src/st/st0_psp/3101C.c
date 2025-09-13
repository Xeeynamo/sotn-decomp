// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../st0/st0.h"

// This file uses g_Dialogue with a different struct than the usual.
// It is based on struct Dialogue, which is used in cutscene.c
extern UnkPrimStruct D_pspeu_0927B0C8[]; // bss
extern Dialogue2 g_Dialogue2;            // bss
extern u16 D_pspeu_0927B0B8;             // bss
extern u16 D_pspeu_0927B0C0;             // bss
extern u16 D_pspeu_09279EB8[][0x30];     // bss

#include "../st0/prologue_cutscene_script.h"

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
    g_Dialogue2.primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (g_Dialogue2.primIndex != -1) {
        g_Dialogue2.scriptCur = script;
        g_Dialogue2.startY = g_Dialogue2.nextCharX = 0x200;

        switch (g_UserLanguage) {
        default:
        case LANG_EN:
            g_Dialogue2.startY += func_pspeu_09242F68((u8*)opening_line_en);
            g_Dialogue2.clutIndexes = clut_en_es;
            g_Dialogue2.unk20 = unk20_en_es;
            g_Dialogue2.clutArrLength = 4;
            break;
        case LANG_FR:
            g_Dialogue2.startY += func_pspeu_09242F68((u8*)opening_line_fr);
            g_Dialogue2.clutIndexes = clut_fr_de_it;
            g_Dialogue2.unk20 = unk20_fr_de_it;
            g_Dialogue2.clutArrLength = 2;
            break;
        case LANG_SP:
            g_Dialogue2.startY += func_pspeu_09242F68((u8*)opening_line_es);
            g_Dialogue2.clutIndexes = clut_en_es;
            g_Dialogue2.unk20 = unk20_en_es;
            g_Dialogue2.clutArrLength = 4;
            break;
        case LANG_GE:
            g_Dialogue2.startY += func_pspeu_09242F68((u8*)opening_line_de);
            g_Dialogue2.clutIndexes = clut_fr_de_it;
            g_Dialogue2.unk20 = unk20_fr_de_it;
            g_Dialogue2.clutArrLength = 2;
            break;
        case LANG_IT:
            g_Dialogue2.startY += func_pspeu_09242F68((u8*)opening_line_it);
            g_Dialogue2.clutIndexes = clut_fr_de_it;
            g_Dialogue2.unk20 = unk20_fr_de_it;
            g_Dialogue2.clutArrLength = 2;
            break;
        }
        g_Dialogue2.nextLineX = 0;
        g_Dialogue2.nextCharY = 0;
        g_Dialogue2.portraitAnimTimer = 0;
        g_Dialogue2.unk12 = 0;
        g_Dialogue2.clutIndex = 0;
        prim = g_Dialogue2.prim = &g_PrimBuf[g_Dialogue2.primIndex];
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
    g_Dialogue2.primIndex = 0;
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

u16* func_801B11E8(u8 dialogue) {
    u16 ret;
    u8 sp1F;
    char sp1C[3];

    sp1C[0] = dialogue;
    sp1C[1] = 0;
    sp1C[2] = 0;

    ret = g_api.func_psp_0913F960(sp1C, &sp1F);
    return g_api.func_psp_0913FA28(ret, 0);
}

static s32 func_pspeu_09242F68(u8* text) {
    u32 i;

    i = 0;
    while (1) {
        *text &= 0xFF;

        switch (*text) {
        case 0:
        case 1:
        case 2:
            return 0x3C - ((i * 3) / 2);
        default:
            text++;
            i++;
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
        g_Dialogue2.script = GetLangAt(
            0, (u8*)prologue_script_en, (u8*)prologue_script_fr,
            (u8*)prologue_script_es, (u8*)prologue_script_de,
            (u8*)prologue_script_it);
        if (func_801B101C(g_Dialogue2.script)) {
            func_8925F7C(0x100, 0xF1, 0x10, 1);
            func_8925F7C(0x110, 0xF2, 0x10, 1);
            func_8925F7C(0x100, 0xF0, 0x10, 1);
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = g_Dialogue2.primIndex;
            ++self->step;
            func_801B1198(0);
            glyphIndex = 0;
            while (1) {
                nextChar = *g_Dialogue2.scriptCur++;
                if (nextChar == 1) {
                    // Gets weirdly relocated in the asm.
                    g_Dialogue2.scriptCur++;
                    g_Dialogue2.startY =
                        g_Dialogue2.nextCharX +
                        func_pspeu_09242F68(g_Dialogue2.scriptCur);
                    ++g_Dialogue2.nextLineX;
                    break;
                }
                glyph = func_801B11E8(nextChar);
                if (glyph) {
                    glyphPtr = D_pspeu_09279EB8[glyphIndex];
                    for (i = 0; i < 0x30; ++i) {
                        glyphPtr++[0] = glyph++[0];
                    }
                    glyph = D_pspeu_09279EB8[glyphIndex];
                    y = g_Dialogue2.nextLineX * 16;
                    LoadTPage(
                        (u_long*)glyph, 0, 0, g_Dialogue2.startY, y, 12, 16);
                    g_Dialogue2.startY += 3;
                    nextChar = g_Dialogue2.startY - g_Dialogue2.nextCharX;
                    if (0x38 <= nextChar && nextChar < 0x40) {
                        g_Dialogue2.startY += 8;
                    }
                    glyphIndex++;
                } else {
                    g_Dialogue2.startY += 2;
                    nextChar = g_Dialogue2.startY - g_Dialogue2.nextCharX;
                    if (0x38 <= nextChar && nextChar < 0x40) {
                        g_Dialogue2.startY += 8;
                    }
                }
            }
        }
        break;
    case 1:
        if (!g_Dialogue2.nextCharY) {
            break;
        }
        nextChar = 0;
        glyphIndex = 0;
        do {
            nextChar = *g_Dialogue2.scriptCur++;
            switch (nextChar) {
            case 0:
                self->step = 7;

                prim = g_Dialogue2.prim;
                nextLineOne = (g_Dialogue2.nextLineX & 0xFFFF & 0xFFFF) * 16;
                nextLineTwo = (g_Dialogue2.nextLineX & 0xFFFF & 0xFFFF) * 16;
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
                g_Dialogue2.scriptCur++;
                g_Dialogue2.startY = g_Dialogue2.nextCharX +
                                     func_pspeu_09242F68(g_Dialogue2.scriptCur);
                g_Dialogue2.nextLineX++;
                if (g_Dialogue2.nextLineX > 15) {
                    g_Dialogue2.nextLineX = 0;
                }
                func_801B1198(g_Dialogue2.nextLineX);
                g_Dialogue2.nextCharY = 0;
                return;
            case 2:
                g_Dialogue2.scriptCur++;
                g_Dialogue2.startY = g_Dialogue2.nextCharX +
                                     func_pspeu_09242F68(g_Dialogue2.scriptCur);
                g_Dialogue2.nextLineX++;
                if (g_Dialogue2.nextLineX > 15) {
                    g_Dialogue2.nextLineX = 0;
                }

                prim = g_Dialogue2.prim;
                for (i = 0; i < g_Dialogue2.nextLineX; ++i) {
                    prim = prim->next;
                    prim = prim->next;
                }

                y0 = prim->y0;
                prim = g_Dialogue2.prim;
                while (prim != NULL) {
                    if (y0 <= prim->y0) {
                        prim->y0 += 0x16;
                        prim->p1 += 0x16;
                    }
                    prim = prim->next;
                }

                g_Dialogue2.unk12 += g_Dialogue2.unk20[D_pspeu_0927B0B8++ % 3];
                g_Dialogue2.portraitAnimTimer += 0x16;
                g_Dialogue2.nextCharY = 0;
                return;
            }
        } while (0);
        glyph = func_801B11E8(nextChar);

        if (glyph) {
            y = g_Dialogue2.nextLineX * 16;
            LoadTPage((u_long*)glyph, 0, 0, g_Dialogue2.startY, y, 0xC, 0x10);
            g_Dialogue2.startY += 3;
            nextChar = g_Dialogue2.startY - g_Dialogue2.nextCharX;
            if (0x38 <= nextChar && nextChar < 0x40) {
                g_Dialogue2.startY += 8;
            }
        } else {
            g_Dialogue2.startY += 2;
            nextChar = g_Dialogue2.startY - g_Dialogue2.nextCharX;
            if (0x38 <= nextChar && nextChar < 0x40) {
                g_Dialogue2.startY += 8;
            }
        }

        break;
    case 2:
        break;
    case 7:
        if (g_Dialogue2.nextCharY) {
            g_Dialogue2.nextLineX++;
            if (g_Dialogue2.nextLineX > 15) {
                g_Dialogue2.nextLineX = 0;
            }
            g_Dialogue2.nextCharY = 0;
        }
    }

    if (!g_Dialogue2.unk12) {
        func_801B1198(g_Dialogue2.nextLineX);
        g_Dialogue2.nextCharY = 1;
        g_Dialogue2.unk12 = g_Dialogue2.unk20[D_pspeu_0927B0B8++ % 3];
    }
    --g_Dialogue2.unk12;
    if (!g_Dialogue2.clutIndex) {
        for (prim = g_Dialogue2.prim, i = 0; i < 32; ++i) {
            prim->y0--;
            if (prim->y0 == -22) {
                prim->y0 = g_Dialogue2.portraitAnimTimer - prim->p1 + 330;
                prim->p1 = g_Dialogue2.portraitAnimTimer;
                if (self->step == 7) {
                    prim->drawMode = DRAW_HIDE;
                }
            }
            prim = prim->next;
        }
        arrLen = g_Dialogue2.clutArrLength;
        g_Dialogue2.clutIndex =
            g_Dialogue2.clutIndexes[D_pspeu_0927B0C0++ % arrLen];
    }
    --g_Dialogue2.clutIndex;
}
