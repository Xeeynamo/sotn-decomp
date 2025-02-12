// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"

INCLUDE_ASM("asm/us/st/mad/nonmatchings/17B94", func_80197B94);

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

void EntityRoomForeground(Entity* entity) {
    ObjInit* obj = &D_801810F4[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_EInitCommon);
        entity->animSet = obj->animSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk5A;
        entity->palette = obj->palette;
        entity->drawFlags = obj->drawFlags;
        entity->drawMode = obj->drawMode;
        if (obj->flags != 0) {
            entity->flags = obj->flags;
        }
    }
    AnimateEntity(obj->animFrames, entity);
}

// Different from other overlays, but identical to the one in Weapon 21.
void BottomCornerText(u8* str, u8 lowerLeft) {
    u8 toPrint[64];
    Primitive* prim;
    s32 i;
    u32 ch;
    u32 ch2;
    u8* chIdx = &toPrint;

    s16 textWidth = 0;
    s32 widthTemp;
    // serves two purposes, use #define for dual names
    u16 dualVar = 0;
#define charcount dualVar
    for (i = 0; i < 64; i++) {
        *chIdx++ = 0;
    }

    chIdx = &toPrint;
    while (1) {
        ch = *str++;
        if (ch == 0xFF) {
            ch = *str++;
            if (ch == 0) {
                break;
            }
        }
        *chIdx = ch;
        chIdx++;
        textWidth += 1;
        if (ch != 0) {
            charcount += 1;
        }
        if (*str == 0xFF) {
            str++;
            ch = *str++;
            ch2 = ch & 0xFF;
            if (ch2 == 0) {
                break;
            }
            if (ch2 != 0xFF) {
                *chIdx = ch;
                charcount += 1;
            } else {
                str -= 2;
            }
        }
        chIdx++;
    }

    g_unkGraphicsStruct.BottomCornerTextPrims =
        g_api.AllocPrimBuffers(PRIM_SPRT, charcount + 4);
    if (g_unkGraphicsStruct.BottomCornerTextPrims == -1) {
        return;
    }
#undef charcount

    prim = &g_PrimBuf[g_unkGraphicsStruct.BottomCornerTextPrims];
    prim->type = PRIM_G4;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->g0 = prim->g1 = prim->g2 =
        prim->g3 = prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
    if (lowerLeft) {
        prim->b0 = prim->b1 = 0xAF;
    } else {
        prim->g0 = prim->g1 = 0x5F;
    }
#define xpos dualVar

    textWidth <<= 3;
    if (lowerLeft) {
        textWidth |= 4;
        xpos = 7;
    } else {
        xpos = 0xD4 - textWidth;
    }
    prim->x0 = prim->x2 = xpos;
    prim->x1 = prim->x3 = xpos + textWidth + 0x20;
    prim->y0 = prim->y1 = 0xD0;
    prim->y2 = prim->y3 = 0xDF;
    prim->priority = 0x1EE;
    prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
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

    chIdx = &toPrint;
    for (prim = prim->next; prim != NULL;) {
        ch = *chIdx++;
        if (ch != 0) {
            prim->u0 = (ch & 0xF) * 8;
            prim->v0 = (ch & 0xF0) >> 1;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->v1 = 8;
            prim->u1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = xpos;
            prim->y0 = 0xD4;
            prim = prim->next;
        }
        ch = *chIdx++;
        if (ch != 0) {
            prim->u0 = (ch & 0xF) * 8;
            prim->v0 = (ch & 0xF0) >> 1;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->v1 = 8;
            prim->u1 = 8;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = xpos;
            prim->y0 = 0xCC;
            prim = prim->next;
        }
        if ((u32)((ch + 0x10) & 0xFF) < 0xDU) {
            xpos += 0xC;
        } else {
            xpos += 8;
        }
    }
    g_unkGraphicsStruct.BottomCornerTextTimer = 0x130;
}
