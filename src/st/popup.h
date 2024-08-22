// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#if defined(VERSION_US)
void BottomCornerText(u8* str, u8 lower_left) {
    u8 toPrint[64];
    Primitive* prim;
    s32 i;
    u32 ch;
    u8* chIdx = &toPrint;

    u16 textWidth = 0;
    // serves two purposes, use #define for dual names
    u16 dualVar = 0;
#define charcount dualVar

    // Clear out the toPrint array
    for (i = 0; i < 64; i++) {
        *chIdx++ = 0;
    }
    // Reset array pointer
    chIdx = &toPrint;

    while (1) {
        i = 0;
        // Copy values from the incoming arg0 array to the local array, until we
        // get a 0xFF followed by a 0
        ch = *str++;
        if (ch == 0xFF) {
            ch = *str++;
            if (ch == 0) {
                break;
            }
        }
        *chIdx = ch;
        chIdx++;
        if (ch != 0) {
            charcount++;
            textWidth += 8;
        } else {
            textWidth += 4;
        }
    }

    g_unkGraphicsStruct.BottomCornerTextPrims =
        g_api.AllocPrimitives(PRIM_SPRT, charcount + 4);
    if (g_unkGraphicsStruct.BottomCornerTextPrims == -1) {
        return;
    }
#undef charcount

    prim = &g_PrimBuf[g_unkGraphicsStruct.BottomCornerTextPrims];
    prim->type = 3;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->g0 = prim->g1 = prim->g2 =
        prim->g3 = prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;

    if (lower_left) {
        prim->b0 = prim->b1 = 0xAF;
    } else {
        prim->g0 = prim->g1 = 0x5F;
    }

#define xpos dualVar
    if (lower_left) {
        xpos = 7;
        textWidth += 4;
    } else {
        xpos = 0xD4 - textWidth;
    }

    prim->x0 = prim->x2 = xpos;
    prim->x1 = prim->x3 = xpos + textWidth + 0x20;
    prim->y0 = prim->y1 = 0xD0;
    prim->y2 = prim->y3 = 0xDF;
    prim->priority = 0x1EE;
    prim->drawMode = 0x11;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = xpos - 6;
    prim->y0 = 0xCB;
    prim->u0 = 0x80;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = xpos + textWidth + 0x16;
    prim->y0 = 0xCB;
    prim->u0 = 0xA8;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->type = 4;
    prim->y0 = prim->y1 = 0xCD;
    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->y2 = prim->y3 = 0xE1;
    prim->u0 = prim->u2 = 0x98;
    prim->u1 = prim->u3 = 0x9C;
    prim->v0 = prim->v1 = 2;
    prim->x0 = prim->x2 = xpos + 0xA;
    prim->x1 = prim->x3 = xpos + textWidth + 0x18;
    prim->v2 = prim->v3 = 0x16;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;

    xpos += 0x10;

    // Reset array pointer
    chIdx = &toPrint;
    for (prim = prim->next; prim != NULL;) {
        ch = *chIdx++;
        if (ch != 0) {
            prim->x0 = xpos;
            prim->u0 = (ch & 0xF) * 8;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->v0 = (ch & 0xF0) >> 1;
            prim->v1 = 8;
            prim->u1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_DEFAULT;
            prim->y0 = 0xD4;
            prim = prim->next;
            xpos += 8;
        } else {
            xpos += 4;
        }
    }
#undef xpos
    g_unkGraphicsStruct.BottomCornerTextTimer = 0x130;
}
#else
void BottomCornerText(u8* str, u8 lower_left) {
    u8 toPrint[64];
    Primitive* prim;
    s32 i;
    u8 ch;
    u8* chIdx;

    u16 textWidth;
    u16 dualVar;
    s16 xpos2;

    chIdx = (u8*)&toPrint;
    dualVar = textWidth = 0;
#define charcount dualVar

    for (i = 0; i < 64; i++) {
        *chIdx++ = 0;
    }
    chIdx = (u8*)&toPrint;

    while (1) {
        ch = *str++;

        if (ch == 0xFF) {
            ch = *str++;

            if (ch == 0) {
                break;
            }
        }

        *chIdx++ = ch;
        textWidth++;

        if (ch) {
            dualVar++;
        }

        ch = *str;

        if (ch == 0xff) {
            *str++;
            ch = *str++;

            if (ch != 0) {
                if (ch != 0xff) {
                    *chIdx = ch;
                    dualVar++;
                } else {
                    str -= 2;
                }

            } else {
                break;
            }
        }

        chIdx++;
    }

    g_unkGraphicsStruct.BottomCornerTextPrims =
        g_api.AllocPrimitives(PRIM_SPRT, charcount + 4);
    if (g_unkGraphicsStruct.BottomCornerTextPrims == -1) {
        return;
    }
#undef charcount

    prim = &g_PrimBuf[g_unkGraphicsStruct.BottomCornerTextPrims];
    prim->type = PRIM_G4;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
    if (lower_left) {
        prim->b0 = prim->b1 = 0xAF;
    } else {
        prim->g0 = prim->g1 = 0x5F;
    }

#if defined(VERSION_HD)
    ch = 8;
    textWidth *= ch;
#else
    textWidth *= 8;
#endif

    if (lower_left) {
        textWidth += 4;
    }
#define xpos dualVar
    if (lower_left) {
        xpos = 7;
    } else {
        xpos = 0xD4 - textWidth;
    }

    prim->x0 = prim->x2 = xpos;
    prim->x1 = prim->x3 = xpos + textWidth + 0x20;
    prim->y0 = prim->y1 = 0xD0;
    prim->y2 = prim->y3 = 0xDF;
    prim->priority = 0x1EE;
    prim->drawMode = 0x11;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = xpos - 6;
    prim->y0 = 0xCB;
    prim->u0 = 0x80;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = xpos + textWidth + 0x16;
    prim->y0 = 0xCB;
    prim->u0 = 0xA8;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->type = PRIM_GT4;
    prim->tpage = 0x1F;
    prim->clut = 0x197;
    prim->x0 = prim->x2 = xpos + 0xA;
    prim->x1 = prim->x3 = xpos + textWidth + 0x18;
    prim->y0 = prim->y1 = 0xCD;
    prim->y2 = prim->y3 = 0xE1;
    prim->u0 = prim->u2 = 0x98;
    prim->u1 = prim->u3 = 0x9C;
    prim->v0 = prim->v1 = 2;
    prim->v2 = prim->v3 = 0x16;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;

    prim = prim->next;

    xpos2 = dualVar + 0x10;

    chIdx = (u8*)&toPrint;

    for (; prim != NULL;) {
        ch = *chIdx++;
        if (ch) {
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->u0 = (s8)((ch & 0xF) * 8);
            prim->v0 = (s8)((ch & 0xF0) >> 1);
            prim->u1 = prim->v1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = xpos2;
            prim->y0 = 0xd4;
            prim = prim->next;
        }
        ch = *chIdx++;
        if (ch) {
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->u0 = (s8)((ch & 0xF) * 8);
            prim->v0 = (s8)((ch & 0xF0) >> 1);
            prim->u1 = prim->v1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = xpos2;
            prim->y0 = 0xcc;
            prim = prim->next;
        }
        if ((ch >= 0xF0) && (ch < 0xFD)) {
            xpos2 += 0xC;
        } else {
            xpos2 += 8;
        }
    }
#undef xpos
    g_unkGraphicsStruct.BottomCornerTextTimer = 0x130;
}
#endif
