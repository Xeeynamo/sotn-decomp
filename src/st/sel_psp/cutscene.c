// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sel/sel.h"
#include <cutscene.h>

extern u16 D_psp_092855F0[];
extern u8 D_psp_09285678[];
extern u16 D_psp_09285688[];
extern u8 D_psp_09285710[];
extern u16 D_psp_09285720[];
extern u8 D_psp_092857B8[];
extern u16 D_psp_092857C8[];
extern u8 D_psp_09285850[];
extern u16 D_psp_09285860[];
extern u8 D_psp_092858E8[];
extern u8 D_psp_09286868[];
extern Dialogue4 D_psp_09287E60;
extern u32 D_893F80C;
extern u32 D_894058C;
extern u32 D_894130C;
extern u32 D_894208C;
extern u32 D_8942E0C;
extern u32 D_8943B8C;
extern u32 D_894490C;
extern u32 D_894568C;
extern u32 D_psp_0927C7F8;
extern u32 D_psp_0927D578;
extern u32 D_psp_0927E2F8;
extern u8 D_psp_092858F8[];
extern u16 D_psp_09285900[];
extern u16 D_psp_09285908[];
extern u16 D_psp_09285910[];
extern u8 D_psp_09285918[];
extern u8 D_psp_09285920[];
extern s32 D_psp_09285BA0;
extern u8* D_psp_09285BA8;
extern s32 D_psp_09286650;
extern u8 D_psp_09286658[];
extern u16 D_psp_09286660[];
extern s32 D_psp_09286860;
extern u8 D_psp_09286BE8[];
extern u8 D_psp_09286C08;
extern s32 D_psp_09286C50;
extern u32 D_psp_09286C58;
extern u16 D_psp_09286C60[][0x30];
extern u32 D_psp_09285928[];
extern u8* D_psp_09285B98;

#include "../../get_lang.h"

void DrawCutsceneActorName(u16 actorIndex, Entity* self, u16* actorNames,
                           u8* arg3, u8* arg4, s32 nActors) {
    Primitive* prim;
    u16 ch;
    u16 i;
    s16 x;
    u8* actorNameLength;
    u16 actorNameStartIndex;
    u16* actorName;
    s32 primIndex;
    u8* len;

    actorNameLength =
        (u8*)GetLang(D_psp_09285678, D_psp_09285850, D_psp_09285710,
                     D_psp_092858E8, D_psp_092857B8);
    ch = actorNameLength[arg3[actorIndex]];
    primIndex = g_api.AllocPrimitives(PRIM_SPRT, ch);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }
    x = 0x38;
    g_Dialogue.primIndex[1] = primIndex;
    prim = &g_PrimBuf[primIndex];
    len = actorNameLength;
    actorNameStartIndex = 0;
    for (i = 0; i < arg3[actorIndex]; i++) {
        actorNameStartIndex += actorNameLength[i];
    }
    actorNames = (u16*)GetLang(D_psp_092855F0, D_psp_092857C8, D_psp_09285688,
                               D_psp_09285860, D_psp_09285720);
    actorName = &actorNames[actorNameStartIndex];
    while (prim != NULL) {
        prim->type = PRIM_SPRT;
        prim->tpage = 0x1E;
        prim->clut = 0x196;
        ch = *actorName++;
        prim->u0 = (s8)((ch & 0x0F) << 3);
        prim->v0 = (s8)((ch & 0xF0) >> 1);
        prim->u1 = prim->v1 = 8;
        prim->priority = 0x1FF;
        prim->drawMode = DRAW_HIDE;
        prim->x0 = x;
        prim->y0 = g_Dialogue.startY + 6;
        if (ch & 0xF000) {
            prim = prim->next;
            prim->type = PRIM_SPRT;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            if (ch & 0x4000) {
                prim->u0 = 0x78;
            } else {
                prim->u0 = 0x70;
            }
            prim->v0 = 0x48;
            prim->u1 = prim->v1 = 8;
            prim->priority = 0x1FF;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = x;
            prim->y0 = g_Dialogue.startY - 2;
        }
        x += 8;
        prim = prim->next;
    }
}

void CutsceneUnk3(s16 nextCharY) {
    RECT rect;

    rect.x = 0;
    rect.y = (nextCharY * 0xC) + 0x180;
    rect.w = 0x40;
    rect.h = 0xC;
    ClearImage(&rect, 0, 0, 0);
    func_890A3C0(D_psp_09286868, 0, 0x380);
}

void CutsceneUnk4(void) {
    Primitive* prim;

    CutsceneUnk3(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = 0x10;
    prim->clut = g_Dialogue.clutIndex;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = (g_Dialogue.startX + 4);
    prim->v0 = (g_Dialogue.nextCharY * 0xC) + 0x80;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}

void CutsceneUnk1(void) {
    g_Dialogue.nextLineY = g_Dialogue.startY + 0x14;
    g_Dialogue.nextCharX = g_Dialogue.nextLineX = 0;
    g_Dialogue.nextCharY = 0;
    g_Dialogue.unk12 = 0;
    g_Dialogue.nextCharTimer = 0;
    g_Dialogue.unk17 = 2;
}

u8 SetCutsceneScript(u8* script) {
    Primitive* prim;

    g_Dialogue.primIndex[2] = g_api.AllocPrimitives(PRIM_SPRT, 7);
    if (g_Dialogue.primIndex[2] != -1) {
        g_Dialogue.scriptCur = script;
        g_Dialogue.unk3C = 0;
        g_Dialogue.primIndex[1] = -1;
        g_Dialogue.primIndex[0] = -1;
        CutsceneUnk1();

        prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[1] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[2] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[3] = prim->next;

        prim->drawMode = DRAW_HIDE;
        prim = g_Dialogue.prim[4] = prim->next;

        prim->type = PRIM_GT4;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_G4;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
        prim->b0 = prim->b1 = 0x7F;
        prim->x0 = prim->x2 = 4;
        prim->x1 = prim->x3 = 0xF8;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->r0 = prim->g0 = prim->b0 = 0x10;
        prim->x0 = 3;
        prim->y0 = 0x2F;
        prim->v0 = 0x4A;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_HIDE;
        return 1;
    }
    g_Dialogue.primIndex[2] = 0;
    return 0;
}

#include "../set_cutscene_end.h"

void SEL_EntityCutscene(Entity* entity) {
    s16 x, y;
    s32 sp38;
    RECT rect;
    Primitive* prim;
    u16 nextChar;
    s32 i;
    s32 var_s4;
    s32 var_s7;
    u32 ptr;
    u32 var_s3_2;
    u8* var_s5;
    u8* var_s1;

    func_8926498();
    switch (entity->step) {
    case 0:
        D_psp_09286860 = D_psp_09285BA0;
        if (SetCutsceneScript(D_psp_09285BA8)) {
            entity->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            entity->primIndex = g_Dialogue.primIndex[2];
            D_psp_09286C58 = 0;
            D_psp_09286650 = 0;
            D_psp_09286C50 = 0;
            g_CutsceneHasControl = 1;
            entity->step++;
        }
        break;

    case 1:
        nextChar = 0;
        while (true) {
            nextChar = *g_Dialogue.scriptCur++;
            sp38 = 0;
            if (func_8919BA8() & 8) {
                g_Dialogue.nextCharTimer = 0;
            }
            if (g_Dialogue.nextCharTimer && !D_psp_09286C50) {
                g_Dialogue.nextCharTimer--;
                g_Dialogue.scriptCur--;
                return;
            }
            if (!(nextChar & 0x80)) {
                switch (nextChar) {
                case 0:
                    entity->step = 7;
                    return;

                case 1:
                    if (D_psp_09286C50) {
                        continue;
                    }
                    g_Dialogue.nextCharX = g_Dialogue.nextLineX;
                    if (!(g_Dialogue.unk12 & 1)) {
                        g_Dialogue.nextLineY += 0x10;
                    }
                    g_Dialogue.nextCharY++;
                    g_Dialogue.nextCharY &= 3;
                    CutsceneUnk4();
                    if (!(g_Dialogue.unk12 & 1)) {
                        if (g_Dialogue.nextCharY > 2) {
                            g_Dialogue.unk12 |= 1;
                            g_Dialogue.portraitAnimTimer = 0;
                            entity->step_s = 0;
                            entity->step++;
                        }
                    } else {
                        g_Dialogue.portraitAnimTimer = 0;
                        entity->step_s = 0;
                        entity->step++;
                    }
                    return;

                case 2:
                    g_Dialogue.scriptCur++;
                    continue;

                case 3:
                    g_Dialogue.nextCharTimer = *g_Dialogue.scriptCur++;
                    if (D_psp_09286C50) {
                        continue;
                    }
                    return;

                case 4:
                    if (D_psp_09286C50) {
                        continue;
                    }
                    prim = g_Dialogue.prim[0];
                    for (i = 0; i < 4; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    return;

                case 5:
                    if (D_psp_09286C50) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    i = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[4];
                    var_s4 = *g_Dialogue.scriptCur++;
                    var_s7 = var_s4 & 1;
                    x = D_psp_092858F8[var_s7];
                    y = D_psp_09286658[var_s7];
                    prim->clut = D_psp_09285900[i];
                    prim->tpage = 0x90;
                    prim->u0 = prim->u2 = x;
                    prim->u1 = prim->u3 = x + 0x2F;
                    prim->v0 = prim->v1 = y;
                    prim->v2 = prim->v3 = y + 0x48;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                        g_Dialogue.startX - 0x1E;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        g_Dialogue.startY + 0x24;
                    g_Dialogue.clutIndex = D_psp_09285910[i];
                    CutsceneUnk1();
                    CutsceneUnk4();
                    prim->priority = 0x1FE;
                    prim->drawMode = DRAW_DEFAULT;
                    DrawCutsceneActorName(i, entity, D_psp_09286660,
                                          D_psp_09285918, D_psp_09285920, 3);
                    g_Dialogue.portraitAnimTimer = 6;
                    entity->step = 3;
                    return;

                case 6:
                    if (D_psp_09286C50) {
                        continue;
                    }
                    prim = g_Dialogue.prim[0];
                    for (i = 0; i < 4; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    g_api.FreePrimitives(g_Dialogue.primIndex[1]);
                    g_Dialogue.primIndex[1] = -1;
                    g_Dialogue.portraitAnimTimer = 6;
                    entity->step = 4;
                    return;

                case 7:
                    if (D_psp_09286C50) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    g_Dialogue.startX = *g_Dialogue.scriptCur++;
                    g_Dialogue.startY = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[4];
                    prim = prim->next;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        g_Dialogue.startY;
                    prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                    prim = prim->next;
                    prim->y0 = g_Dialogue.startY - 1;
                    prim->u0 = 0;
                    prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                    g_Dialogue.portraitAnimTimer = 0x18;
                    entity->step = 5;
                    entity->step_s = 0;
                    return;

                case 8:
                    if (D_psp_09286C50) {
                        continue;
                    }
                    g_Dialogue.portraitAnimTimer = 0x18;
                    entity->step = 6;
                    return;

                case 9:
                    if (D_psp_09286C50) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    nextChar = *g_Dialogue.scriptCur++;
                    nextChar <<= 4;
                    nextChar |= *g_Dialogue.scriptCur++;
                    g_api.PlaySfx(nextChar);
                    continue;

                case 10:
                    if (D_psp_09286C50 || g_api.func_80131F68() != 0) {
                        continue;
                    }
                    g_Dialogue.scriptCur--;
                    return;

                case 11:
                    if (D_psp_09286C50 || g_api.func_80131F68() != 1) {
                        continue;
                    }
                    g_Dialogue.scriptCur--;
                    return;

                case 12:
                    ptr = *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr += D_psp_09286860;
                    SetCutsceneEnd((u8*)ptr);
                    continue;

                case 13:
                    continue;

                case 14:
                    ptr = *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr += D_psp_09286860;
                    g_Dialogue.scriptCur += *((u8*)ptr) * 4;
                    ptr = *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur;
                    ptr += D_psp_09286860;
                    g_Dialogue.scriptCur = (u8*)ptr;
                    continue;

                case 15:
                    ptr = *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur;
                    ptr += D_psp_09286860;
                    g_Dialogue.scriptCur = (u8*)ptr;
                    continue;

                case 16:
                    if (!((D_psp_09286C58 >> (*g_Dialogue.scriptCur)) & 1)) {
                        g_Dialogue.scriptCur--;
                        return;
                    }
                    D_psp_09286C58 &= ~(1 << (*g_Dialogue.scriptCur));
                    g_Dialogue.scriptCur++;
                    continue;

                case 17:
                    D_psp_09286C58 |= 1 << (*g_Dialogue.scriptCur++);
                    continue;

                case 18:
                    g_Dialogue.unk3C = 0;
                    continue;

                case 19:
                    if (D_psp_09286C50) {
                        g_Dialogue.scriptCur += 5;
                        continue;
                    }
                    ptr = *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= *g_Dialogue.scriptCur++;
                    switch (ptr) {
                    case 0:
                        ptr = (u32)&D_psp_0927C7F8;
                        break;
                    case 1:
                        ptr = (u32)&D_psp_0927D578;
                        break;
                    case 2:
                        ptr = (u32)&D_psp_0927E2F8;
                        break;
                    case 3:
                        ptr = (u32)&D_893F80C;
                        break;
                    case 4:
                        ptr = (u32)&D_894058C;
                        break;
                    case 5:
                        ptr = (u32)&D_894130C;
                        break;
                    case 6:
                        ptr = (u32)&D_894208C;
                        break;
                    case 7:
                        ptr = (u32)&D_8942E0C;
                        break;
                    case 8:
                        ptr = (u32)&D_8943B8C;
                        break;
                    case 9:
                        ptr = (u32)&D_894490C;
                        break;
                    case 10:
                        ptr = (u32)&D_894568C;
                        break;
                    }
                    var_s4 = *g_Dialogue.scriptCur++;
                    LoadTPage((u_long*)ptr, 1, 0, D_psp_09285908[var_s4], 0x100,
                              0x30, 0x48);
                    continue;

                case 20:
                    nextChar = *g_Dialogue.scriptCur++;
                    nextChar <<= 4;
                    nextChar |= *g_Dialogue.scriptCur++;
                    g_api.PlaySfx(nextChar);
                    continue;

                case 21:
                    D_psp_09286C58 = 0;
                    D_psp_09286C50 = 0;
                    D_psp_09286650 = 0;
                    continue;

                case 22:
                    D_psp_09286C58 &= ~(1 << (*g_Dialogue.scriptCur++));
                    continue;

                case 23:
                    return;

                case 24:
                    if (!((D_psp_09286C58 >> (*g_Dialogue.scriptCur)) & 1)) {
                        g_Dialogue.scriptCur--;
                        return;
                    }
                    g_Dialogue.scriptCur++;
                    continue;

                default:
                    if (D_psp_09286C50) {
                        continue;
                    }
                    g_Dialogue.nextCharTimer = g_Dialogue.unk17;
                    sp38 = 1;
                }
                if (sp38 != 0) {
                    break;
                }
                continue;
            } else {
                if (D_psp_09286C50) {
                    g_Dialogue.scriptCur++;
                    continue;
                }
                if (nextChar >= 0xA7 && nextChar < 0xAD) {
                    nextChar = nextChar + 0x27;
                } else if (nextChar == 0xA6) {
                    nextChar = 0xCC;
                } else if (nextChar == 0xDD) {
                    nextChar = 0xCD;
                } else {
                    nextChar = nextChar - 0x11;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break;
        }
        var_s5 = D_psp_09286BE8;
        rect.x = ((nextChar & 0x0F) << 1) + 0x380;
        rect.y = ((nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        y = g_Dialogue.nextCharY * 12 + 0x180;
        StoreImage(&rect, (u_long*)var_s5);
        for (i = 0; i < 0x20; i++) {
            var_s5[i] = ((var_s5[i] & 0x0F) << 4) | ((var_s5[i] & 0xF0) >> 4);
        }
        while (true) {
            if (nextChar == ' ') {
                break;
            }
            for (i = 0; i < 8; i++) {
                if (var_s5[i * 8 / 2] & 0xF0) {
                    break;
                }
            }
            if (i != 8) {
                break;
            }
            for (i = 0; i < 8; i++) {
                var_s1 = &var_s5[i * 8 / 2];
                var_s3_2 = var_s1[0] << 0x18;
                var_s3_2 |= var_s1[1] << 0x10;
                var_s3_2 |= var_s1[2] << 0x08;
                var_s3_2 |= var_s1[3] << 0x00;
                var_s3_2 <<= 4;
                var_s1[0] = (var_s3_2 >> 0x18) & 0xFF;
                var_s1[1] = (var_s3_2 >> 0x10) & 0xFF;
                var_s1[2] = (var_s3_2 >> 0x08) & 0xFF;
                var_s1[3] = (var_s3_2 >> 0x00) & 0xFF;
            }
        }
        for (i = 0, var_s7 = 0; i < 8; i++) {
            for (var_s4 = 0; var_s4 < 8; var_s4++) {
                if ((var_s5[var_s4 / 2 + i * 8 / 2] &
                     (0xF0 >> ((var_s4 & 1) * 4))) &&
                    (var_s7 < var_s4)) {
                    var_s7 = var_s4;
                }
            }
        }
        var_s7 += 2;
        for (i = 0; i < 0x20; i++) {
            var_s5[i] = ((var_s5[i] & 0x0F) << 4) | ((var_s5[i] & 0xF0) >> 4);
        }
        rect.w = var_s7;
        var_s5 = D_psp_09286BE8;
        for (i = 0; i < 8; i++) {
            var_s1 =
                &D_psp_09286868[(g_Dialogue.nextCharX - g_Dialogue.nextLineX) /
                                    2 +
                                (i * 0x70)];
            if ((g_Dialogue.nextCharX - g_Dialogue.nextLineX) & 1) {
                var_s1[0] = (var_s1[0] & 0xF0) | ((var_s5[0] & 0x0F) << 4);
                var_s1[1] =
                    ((var_s5[0] & 0xF0) >> 4) | ((var_s5[1] & 0x0F) << 4);
                var_s1[2] =
                    ((var_s5[1] & 0xF0) >> 4) | ((var_s5[2] & 0x0F) << 4);
                var_s1[3] =
                    ((var_s5[2] & 0xF0) >> 4) | ((var_s5[3] & 0x0F) << 4);
                var_s1[4] = (var_s5[3] & 0xF0) >> 4;
                var_s5 += 4;
            } else {
                var_s1[0] = var_s5[0];
                var_s1[1] = var_s5[1];
                var_s1[2] = var_s5[2];
                var_s1[3] = var_s5[3];
                var_s5 += 4;
            }
        }
        LoadTPage(
            (u_long*)D_psp_09286868, 0, 0, g_Dialogue.nextLineX, y, 0xE0, 8);
        if (nextChar != ' ') {
            g_Dialogue.nextCharX += rect.w;
        } else {
            g_Dialogue.nextCharX += 4;
        }
        if ((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2 < 0x70) {
        }
        D_psp_09286C08 = nextChar;
        break;

    case 2:
        ptr = (g_Dialogue.nextCharY + 1) & 3;
        if (!entity->step_s) {
            prim = g_Dialogue.prim[ptr];
            prim->v0 += 2;
            prim->v1 -= 2;
            if (!prim->v1) {
                entity->step_s++;
                prim->drawMode = DRAW_HIDE;
            }
        }
        for (i = 0; i < 4; i++) {
            if (i != ptr) {
                prim = g_Dialogue.prim[i];
                prim->y0 -= 2;
            }
        }
        g_Dialogue.portraitAnimTimer++;
        if (g_Dialogue.portraitAnimTimer >= 8) {
            entity->step--;
        }
        break;

    case 3:
        prim = g_Dialogue.prim[4];
        prim->x0 = prim->x2 -= 4;
        prim->x1 = prim->x3 += 4;
        prim->y0 = prim->y1 -= 6;
        prim->y2 = prim->y3 += 6;
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            entity->step = 1;
            prim = &g_PrimBuf[g_Dialogue.primIndex[1]];
            while (prim != NULL) {
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
        }
        break;

    case 4:
        prim = g_Dialogue.prim[4];
        prim->x0 = prim->x2 += 4;
        prim->x1 = prim->x3 -= 4;
        prim->y0 = prim->y1 += 6;
        prim->y2 = prim->y3 -= 6;
        if (prim->x1 >= (g_Dialogue.startX - 2)) {
            prim->x1 = prim->x3 = g_Dialogue.startX - 3;
        }
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            entity->step = 1;
        }
        break;

    case 5:
        D_psp_09286650 = 1;
        prim = g_Dialogue.prim[4];
        prim = prim->next;
        g_Dialogue.portraitAnimTimer--;
        if (g_Dialogue.portraitAnimTimer >= 12) {
            prim = prim->next;
            prim->u0 += 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                prim->u0++;
            }
        } else {
            if (!g_Dialogue.portraitAnimTimer) {
                entity->step = 1;
            }
            prim->y2 = prim->y3 += 6;
        }
        break;

    case 6:
        prim = g_Dialogue.prim[4];
        prim = prim->next;
        g_Dialogue.portraitAnimTimer--;
        if (g_Dialogue.portraitAnimTimer >= 12) {
            prim = prim->next;
            prim->u0 -= 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                prim->u0--;
            }
        } else {
            if (!g_Dialogue.portraitAnimTimer) {
                entity->step = 1;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->y2 = prim->y3 -= 6;
            }
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 7:
        g_CutsceneHasControl = 0;
        break;
    }
}

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
            prim->clut = 0x1A1;
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

    func_8926498();
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
                    var_s4 = D_psp_09286C60[glyphIndex];
                    for (i = 0; i < 0x30; i++) {
                        *var_s4++ = *glyph++;
                    }
                    glyph = D_psp_09286C60[glyphIndex];
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
