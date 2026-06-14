// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

void BottomCornerText(u8* str, u8 leftAlign) {
    u8 toPrint[64];
    Primitive* prim;
    s32 i;
    u8 ch;
    u8* chIdx;
    u16 textWidth;
    u16 xPos;
    s16 xPos2;

    chIdx = (u8*)&toPrint;
    xPos = textWidth = 0;

    // Clear out the toPrint array
    for (i = 0; i < 64; i++) {
        *chIdx++ = 0;
    }
    // Reset array pointer
    chIdx = (u8*)&toPrint;

    while (true) {
        // Copy values from the incoming arg0 array to the local array, until we
        // get a 0xFF followed by a 0
        ch = *str++;
        if (ch == 0xFF) {
            ch = *str++;
            if (ch == 0) {
                break;
            }
        }
        *chIdx++ = ch;
#if defined(VERSION_US) && !defined(VERSION_BETA)
        if (ch) {
            xPos++;
        }
        if (ch) {
            textWidth += 8;
        } else {
            textWidth += 4;
        }
#else
        textWidth++;

        if (ch) {
            xPos++;
        }

        ch = *str;

        if (ch == 0xFF) {
            *str++;
            ch = *str++;

            if (ch == 0) {
                break;
            }
            if (ch != 0xFF) {
                *chIdx = ch;
                xPos++;
            } else {
                str -= 2;
            }
        }
        chIdx++;
#endif
    }

    g_unkGraphicsStruct.BottomCornerTextPrims =
        g_api.AllocPrimitives(PRIM_SPRT, xPos + 4);

    if (g_unkGraphicsStruct.BottomCornerTextPrims == -1) {
        return;
    }

    prim = &g_PrimBuf[g_unkGraphicsStruct.BottomCornerTextPrims];
    prim->type = PRIM_G4;
    PRED(prim) = 0;
    PGRN(prim) = 0;
    PBLU(prim) = 0;

    if (leftAlign) {
        prim->b0 = prim->b1 = 0xAF;
    } else {
        prim->g0 = prim->g1 = 0x5F;
    }

#if !defined(VERSION_US) || defined(VERSION_BETA)
    textWidth <<= 3;
#endif

    if (leftAlign) {
        textWidth += 4;
    }
    if (leftAlign) {
        xPos = 7;
    } else {
        xPos = 0xD4 - textWidth;
    }

    prim->x0 = prim->x2 = xPos;
    prim->x1 = prim->x3 = xPos + textWidth + 0x20;
    prim->y0 = prim->y1 = 0xD0;
    prim->y2 = prim->y3 = 0xDF;
    prim->priority = 0x1EE;
    prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = PAL_UNK_197;
    prim->x0 = xPos - 6;
    prim->y0 = 0xCB;
    prim->u0 = 0x80;
    prim->v0 = 0;
    prim->u1 = 0x10;
    prim->v1 = 0x18;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    prim->tpage = 0x1F;
    prim->clut = PAL_UNK_197;
    prim->x0 = xPos + textWidth + 0x16;
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
    prim->clut = PAL_UNK_197;
    prim->x0 = prim->x2 = xPos + 0xA;
    prim->x1 = prim->x3 = xPos + textWidth + 0x18;
    prim->y0 = prim->y1 = 0xCD;
    prim->y2 = prim->y3 = 0xE1;
    prim->u0 = prim->u2 = 0x98;
    prim->u1 = prim->u3 = 0x9C;
    prim->v0 = prim->v1 = 2;
    prim->v2 = prim->v3 = 0x16;
    prim->priority = 0x1EF;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    xPos2 = xPos + 0x10;

    // Reset array pointer
    chIdx = (u8*)&toPrint;

    while (prim != NULL) {
        ch = *chIdx++;
        if (ch) {
            prim->tpage = 0x1E;
            prim->clut = PAL_UNK_196;
            prim->u0 = (s8)((ch & 0x0F) << 3);
            prim->v0 = (s8)((ch & 0xF0) >> 1);
            prim->u1 = prim->v1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = xPos2;
            prim->y0 = 0xD4;
            prim = prim->next;
        }
#if !defined(VERSION_US) || defined(VERSION_BETA)
        ch = *chIdx++;
        if (ch) {
            prim->tpage = 0x1E;
            prim->clut = PAL_UNK_196;
            prim->u0 = (s8)((ch & 0x0F) << 3);
            prim->v0 = (s8)((ch & 0xF0) >> 1);
            prim->u1 = prim->v1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = xPos2;
            prim->y0 = 0xCC;
            prim = prim->next;
        }
        if (ch >= 0xF0 && ch < 0xFD) {
            xPos2 += 12;
        } else {
            xPos2 += 8;
        }
#else
        if (ch) {
            xPos2 += 8;
        } else {
            xPos2 += 4;
        }
#endif
    }
    g_unkGraphicsStruct.BottomCornerTextTimer = 0x130;
}
