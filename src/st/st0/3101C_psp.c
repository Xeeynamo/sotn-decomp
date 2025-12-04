// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <cutscene.h>

// This file uses g_Dialogue with a different struct than cutscene.c
typedef struct {
    /* 0x00 */ u8* scriptCur;
    /* 0x04 */ s16 startX;
    /* 0x06 */ s16 nextLineY;
    /* 0x08 */ s16 startY;
    /* 0x0A */ s16 nextCharX;
    /* 0x0C */ s16 nextLineX;
    /* 0x0E */ u16 nextCharY;
    /* 0x10 */ u16 portraitAnimTimer;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 clutIndex;
#ifdef VERSION_PSP
    /* 0x14 */ u8 nextCharTimer;
    /* 0x15 */ u8 unk17;
#endif
    /* 0x14 */ Primitive* prim;
    /* 0x18 */ u32 primIndex;
    /* 0x1C */ u16* unk20;
    /* 0x20 */ s32 : 32;
    /* 0x24 */ u16* clutIndexes;
    /* 0x28 */ s32 : 32;
    /* 0x2C */ s32 clutArrLength;
    /* 0x30 */ s32 : 32;
    /* 0x34 */ u8* script;
#ifndef VERSION_PSP
    /* 0x38 */ u16 unk3C; // maybe it is a begin flag?
    /* 0x3A */ u16 timer;
#endif
    /* 0x3C */ u8* scriptEnd;
} DialoguePrologue;

// n.b. g_Dialogue is defined as the Dialogue struct, but is used in this file
// as the different type.
// It appears that either:
// - The devs recognized this as a bad practice and fixed it for pspeu or
// - The pspeu toolchain (probably optimization level) handled them differently
// Either way, us shares a single memory address for 3101C.c and cutscene.c
// while pspeu uses two independent memory addresses.
static DialoguePrologue g_Dialogue;        // bss
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
    g_Dialogue.primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (g_Dialogue.primIndex != -1) {
        g_Dialogue.scriptCur = script;

        g_Dialogue.startY = g_Dialogue.nextCharX = 0x200;

        switch (g_UserLanguage) {
        default:
        case LANG_EN:
            g_Dialogue.startY += func_pspeu_09242F68((u8*)opening_line_en);
            g_Dialogue.clutIndexes = clut_en_es;
            g_Dialogue.unk20 = unk20_en_es;
            g_Dialogue.clutArrLength = 4;
            break;
        case LANG_FR:
            g_Dialogue.startY += func_pspeu_09242F68((u8*)opening_line_fr);
            g_Dialogue.clutIndexes = clut_fr_de_it;
            g_Dialogue.unk20 = unk20_fr_de_it;
            g_Dialogue.clutArrLength = 2;
            break;
        case LANG_SP:
            g_Dialogue.startY += func_pspeu_09242F68((u8*)opening_line_es);
            g_Dialogue.clutIndexes = clut_en_es;
            g_Dialogue.unk20 = unk20_en_es;
            g_Dialogue.clutArrLength = 4;
            break;
        case LANG_GE:
            g_Dialogue.startY += func_pspeu_09242F68((u8*)opening_line_de);
            g_Dialogue.clutIndexes = clut_fr_de_it;
            g_Dialogue.unk20 = unk20_fr_de_it;
            g_Dialogue.clutArrLength = 2;
            break;
        case LANG_IT:
            g_Dialogue.startY += func_pspeu_09242F68((u8*)opening_line_it);
            g_Dialogue.clutIndexes = clut_fr_de_it;
            g_Dialogue.unk20 = unk20_fr_de_it;
            g_Dialogue.clutArrLength = 2;
            break;
        }
        g_Dialogue.nextLineX = 0;
        g_Dialogue.nextCharY = 0;
        g_Dialogue.portraitAnimTimer = 0;
        g_Dialogue.unk12 = 0;
        g_Dialogue.clutIndex = 0;
        prim = g_Dialogue.prim = &g_PrimBuf[g_Dialogue.primIndex];
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
    g_Dialogue.primIndex = 0;
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
        g_Dialogue.script = GetLangAt(
            0, (u8*)prologue_script_en, (u8*)prologue_script_fr,
            (u8*)prologue_script_es, (u8*)prologue_script_de,
            (u8*)prologue_script_it);
        if (func_801B101C(g_Dialogue.script)) {
            func_psp_08925F7C(0x100, 0xF1, 0x10, 1);
            func_psp_08925F7C(0x110, 0xF2, 0x10, 1);
            func_psp_08925F7C(0x100, 0xF0, 0x10, 1);
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = g_Dialogue.primIndex;
            ++self->step;
            func_801B1198(0);
            glyphIndex = 0;
            while (1) {
                nextChar = *g_Dialogue.scriptCur++;
                if (nextChar == 1) {
                    // Gets weirdly relocated in the asm.
                    *g_Dialogue.scriptCur++;
                    g_Dialogue.startY =
                        g_Dialogue.nextCharX +
                        func_pspeu_09242F68(g_Dialogue.scriptCur);
                    ++g_Dialogue.nextLineX;
                    break;
                }
                glyph = func_801B11E8(nextChar);
                if (glyph) {
                    glyphPtr = D_801BEE90[glyphIndex];
                    for (i = 0; i < 0x30; ++i) {
                        glyphPtr++[0] = glyph++[0];
                    }
                    glyph = D_801BEE90[glyphIndex];
                    y = g_Dialogue.nextLineX * 16;
                    LoadTPage(
                        (u_long*)glyph, 0, 0, g_Dialogue.startY, y, 12, 16);
                    g_Dialogue.startY += 3;
                    nextChar = g_Dialogue.startY - g_Dialogue.nextCharX;
                    if (0x38 <= nextChar && nextChar < 0x40) {
                        g_Dialogue.startY += 8;
                    }
                    glyphIndex++;
                } else {
                    g_Dialogue.startY += 2;
                    nextChar = g_Dialogue.startY - g_Dialogue.nextCharX;
                    if (0x38 <= nextChar && nextChar < 0x40) {
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
                prim = g_Dialogue.prim;
                nextLineOne = (g_Dialogue.nextLineX & 0xFFFF & 0xFFFF) * 16;
                nextLineTwo = (g_Dialogue.nextLineX & 0xFFFF & 0xFFFF) * 16;
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
                *g_Dialogue.scriptCur++;
                g_Dialogue.startY = g_Dialogue.nextCharX +
                                    func_pspeu_09242F68(g_Dialogue.scriptCur);
                g_Dialogue.nextLineX++;
                if (g_Dialogue.nextLineX > 15) {
                    g_Dialogue.nextLineX = 0;
                }
                func_801B1198(g_Dialogue.nextLineX);
                g_Dialogue.nextCharY = 0;
                return;
            case 2:
                *g_Dialogue.scriptCur++;
                g_Dialogue.startY = g_Dialogue.nextCharX +
                                    func_pspeu_09242F68(g_Dialogue.scriptCur);
                g_Dialogue.nextLineX++;
                if (g_Dialogue.nextLineX > 15) {
                    g_Dialogue.nextLineX = 0;
                }

                prim = g_Dialogue.prim;
                for (i = 0; i < g_Dialogue.nextLineX; ++i) {
                    prim = prim->next;
                    prim = prim->next;
                }

                y0 = prim->y0;
                for (prim = g_Dialogue.prim; prim != NULL; prim = prim->next) {
                    if (y0 <= prim->y0) {
                        prim->y0 += 0x16;
                        prim->p1 += 0x16;
                    }
                }
                g_Dialogue.unk12 += g_Dialogue.unk20[D_pspeu_0927B0B8++ % 3];
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
            nextChar = g_Dialogue.startY - g_Dialogue.nextCharX;
            if (0x38 <= nextChar && nextChar < 0x40) {
                g_Dialogue.startY += 8;
            }
        } else {
            g_Dialogue.startY += 2;
            nextChar = g_Dialogue.startY - g_Dialogue.nextCharX;
            if (0x38 <= nextChar && nextChar < 0x40) {
                g_Dialogue.startY += 8;
            }
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
        g_Dialogue.unk12 = g_Dialogue.unk20[D_pspeu_0927B0B8++ % 3];
    }
    --g_Dialogue.unk12;
    if (!g_Dialogue.clutIndex) {
        for (prim = g_Dialogue.prim, i = 0; i < 32; ++i) {
            prim->y0--;
            if (prim->y0 == -22) {
                prim->y0 = g_Dialogue.portraitAnimTimer - prim->p1 + 330;
                prim->p1 = g_Dialogue.portraitAnimTimer;
                if (self->step == 7) {
                    prim->drawMode = DRAW_HIDE;
                }
            }
            prim = prim->next;
        }
        arrLen = g_Dialogue.clutArrLength;
        g_Dialogue.clutIndex =
            g_Dialogue.clutIndexes[D_pspeu_0927B0C0++ % arrLen];
    }
    --g_Dialogue.clutIndex;
}
