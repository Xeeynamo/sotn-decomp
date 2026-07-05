// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <cutscene.h>

// This file uses OVL_EXPORT(Dialogue) with a different struct than cutscene.c
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

// n.b. OVL_EXPORT(Dialogue) is defined as the Dialogue struct, but is used in
// this file as the different type. It appears that either:
// - The devs recognized this as a bad practice and fixed it for pspeu or
// - The pspeu toolchain (probably optimization level) handled them differently
// Either way, us shares a single memory address for 3101C.c and cutscene.c
// while pspeu uses two independent memory addresses.
extern DialoguePrologue OVL_EXPORT(Dialogue);

static u16 D_801BEE90[48][48]; // bss

static u8 unused[] = {0x00, 0x81, 0x17, 0x08, 0x80, 0x08,
                      0x80, 0xFF, 0xFF, 0x00, 0x00, 0x00};

u8 func_801B101C(u8* script) {
    Primitive* prim;
    s16 i;
    s16 shift;

    OVL_EXPORT(Dialogue).primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (OVL_EXPORT(Dialogue).primIndex != -1) {
        OVL_EXPORT(Dialogue).scriptCur = script;
        OVL_EXPORT(Dialogue).nextCharX = 0x200;
        OVL_EXPORT(Dialogue).startY = 0x216;
        OVL_EXPORT(Dialogue).nextLineX = 0;
        OVL_EXPORT(Dialogue).nextCharY = 0;
        OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
        OVL_EXPORT(Dialogue).unk12 = 0;
        OVL_EXPORT(Dialogue).clutIndex = 0;
        prim = OVL_EXPORT(Dialogue).prim =
            &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex];
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
    OVL_EXPORT(Dialogue).primIndex = 0;
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
            self->primIndex = OVL_EXPORT(Dialogue).primIndex;
            ++self->step;
            func_801B1198(0);
            glyphIndex = 0;
            while (1) {
                nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
                if (nextChar == 1) {
                    // Gets weirdly relocated in the asm.
                    OVL_EXPORT(Dialogue).startY =
                        OVL_EXPORT(Dialogue).nextCharX +
                        *OVL_EXPORT(Dialogue).scriptCur++;
                    ++OVL_EXPORT(Dialogue).nextLineX;
                    break;
                }
                glyph = func_801B11E8(nextChar);
                if (glyph) {
                    glyphPtr = D_801BEE90[glyphIndex];
                    for (i = 0; i < 0x30; ++i) {
                        glyphPtr++[0] = glyph++[0];
                    }
                    glyph = D_801BEE90[glyphIndex];
                    y = OVL_EXPORT(Dialogue).nextLineX * 16;
                    LoadTPage((u_long*)glyph, 0, 0, OVL_EXPORT(Dialogue).startY,
                              y, 12, 16);
                    OVL_EXPORT(Dialogue).startY += 3;
                    nextChar = OVL_EXPORT(Dialogue).startY -
                               OVL_EXPORT(Dialogue).nextCharX;
                    if (0x38 <= nextChar && nextChar < 0x40) {
                        OVL_EXPORT(Dialogue).startY += 8;
                    }
                    glyphIndex++;
                } else {
                    OVL_EXPORT(Dialogue).startY += 2;
                    nextChar = OVL_EXPORT(Dialogue).startY -
                               OVL_EXPORT(Dialogue).nextCharX;
                    if (0x38 <= nextChar && nextChar < 0x40) {
                        OVL_EXPORT(Dialogue).startY += 8;
                    }
                }
            }
        }
        break;
    case 1:
        if (!OVL_EXPORT(Dialogue).nextCharY) {
            break;
        }
        nextChar = 0;
        glyphIndex = 0;
        do {
            nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;
            case 1:
                OVL_EXPORT(Dialogue).startY = OVL_EXPORT(Dialogue).nextCharX +
                                              *OVL_EXPORT(Dialogue).scriptCur++;
                OVL_EXPORT(Dialogue).nextLineX++;
                if (OVL_EXPORT(Dialogue).nextLineX > 15) {
                    OVL_EXPORT(Dialogue).nextLineX = 0;
                }
                OVL_EXPORT(Dialogue).nextCharY = 0;
                return;
            case 2:
                OVL_EXPORT(Dialogue).startY = OVL_EXPORT(Dialogue).nextCharX +
                                              *OVL_EXPORT(Dialogue).scriptCur++;
                OVL_EXPORT(Dialogue).nextLineX++;
                if (OVL_EXPORT(Dialogue).nextLineX > 15) {
                    OVL_EXPORT(Dialogue).nextLineX = 0;
                }

                prim = OVL_EXPORT(Dialogue).prim;
                for (i = 0; i < OVL_EXPORT(Dialogue).nextLineX; ++i) {
                    prim = prim->next;
                    prim = prim->next;
                }

                y0 = prim->y0;
                for (prim = OVL_EXPORT(Dialogue).prim; prim != NULL;
                     prim = prim->next) {
                    if (y0 <= prim->y0) {
                        prim->y0 += 0x16;
                        prim->p1 += 0x16;
                    }
                }
                OVL_EXPORT(Dialogue).unk12 += 0x58;
                OVL_EXPORT(Dialogue).portraitAnimTimer += 0x16;
                OVL_EXPORT(Dialogue).nextCharY = 0;
                return;
            }
        } while (0);
        glyph = func_801B11E8(nextChar);

        if (glyph) {
            y = OVL_EXPORT(Dialogue).nextLineX * 16;
            LoadTPage((u_long*)glyph, 0, 0, OVL_EXPORT(Dialogue).startY, y, 0xC,
                      0x10);
            OVL_EXPORT(Dialogue).startY += 3;
        } else {
            OVL_EXPORT(Dialogue).startY += 2;
        }
        nextChar = OVL_EXPORT(Dialogue).startY - OVL_EXPORT(Dialogue).nextCharX;
        if (0x38 <= nextChar && nextChar < 0x40) {
            OVL_EXPORT(Dialogue).startY += 8;
        }
        break;
    case 2:
        break;
    case 7:
        if (OVL_EXPORT(Dialogue).nextCharY) {
            OVL_EXPORT(Dialogue).nextLineX++;
            if (OVL_EXPORT(Dialogue).nextLineX > 15) {
                OVL_EXPORT(Dialogue).nextLineX = 0;
            }
            OVL_EXPORT(Dialogue).nextCharY = 0;
        }
    }

    if (!OVL_EXPORT(Dialogue).unk12) {
        func_801B1198(OVL_EXPORT(Dialogue).nextLineX);
        OVL_EXPORT(Dialogue).nextCharY = 1;
        OVL_EXPORT(Dialogue).unk12 = 88;
    }
    --OVL_EXPORT(Dialogue).unk12;
    if (!OVL_EXPORT(Dialogue).clutIndex) {
        for (prim = OVL_EXPORT(Dialogue).prim, i = 0; i < 32; ++i) {
            prim->y0--;
            if (prim->y0 == -22) {
                prim->y0 =
                    OVL_EXPORT(Dialogue).portraitAnimTimer - prim->p1 + 330;
                prim->p1 = OVL_EXPORT(Dialogue).portraitAnimTimer;
            }
            prim = prim->next;
        }
        OVL_EXPORT(Dialogue).clutIndex = 4;
    }
    --OVL_EXPORT(Dialogue).clutIndex;
}
