// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

#include "../cutscene_unk1.h"

u8 CutsceneUnk2(const char* textDialogue) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 7);
    g_Dialogue.primIndex[2] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        g_Dialogue.primIndex[2] = 0;
        return false;
    }
    g_Dialogue.nextCharDialogue = textDialogue;
    g_Dialogue.unk3C = 0;
    g_Dialogue.primIndex[1] = -1;
    g_Dialogue.primIndex[0] = -1;
    CutsceneUnk1();

    //! FAKE:
    if (prim && prim) {
    }

    prim = g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[2]];

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[1] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[2] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[3] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[4] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = g_Dialogue.prim[5] = prim->next;

    prim->type = PRIM_GT4;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = PRIM_G4;
    prim->b0 = prim->b1 = 0x7F;
    prim->b2 = prim->b3 = 0;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = PRIM_TILE;
    prim->r0 = prim->g0 = prim->b0 = 16;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->priority = 0x1FC;
    prim->drawMode = DRAW_HIDE;
    return true;
}

#include "../cutscene_unk3.h"

void func_801B66A4(void) {
    Primitive* prim;

    CutsceneUnk3(g_Dialogue.nextCharY);
    prim = g_Dialogue.prim[g_Dialogue.nextCharY];
    prim->tpage = 0x10;
    prim->clut = g_Dialogue.clutIndex;
    prim->y0 = g_Dialogue.nextLineY;
    prim->u0 = 0;
    prim->x0 = g_Dialogue.startX;
    prim->x0 = prim->x0 + 4;
    prim->v0 = g_Dialogue.nextCharY * 0xC - 0x80;
    prim->u1 = 0xC0;
    prim->v1 = 0xC;
    prim->priority = 0x1FF;
    prim->drawMode = DRAW_DEFAULT;
}

u8 D_80180824[] = {
    0x00,
    0x40,
    0x00,
    0x00,
};

u8 D_80180828[] = {
    0x00,
    0x00,
    0x00,
    0x00,
};

u16 D_8018082C[] = {
    0x0240,
    0x0248,
    0x0250,
};

u16 D_80180834[] = {
    0x0000,
    0x0020,
};

u16 D_80180838[] = {
    0x01A1, 0x01A1, 0x01A1, 0x0000, 0x0008, 0x0013, 0x0011, 0x0031, 0x004F,
    0x0026, 0x0036, 0x001D, 0x001B, 0x0033, 0x002C, 0x0021, 0x0019, 0x000A,
    0x0033, 0x001F, 0x0048, 0x002F, 0x0013, 0x0019, 0x004D, 0x004B, 0x0017,
    0x001D, 0x0012, 0x0002, 0x001B, 0x002A, 0x0050, 0x0045, 0x0032, 0x000D,
    0x002A, 0x004D, 0x0006, 0x0027, 0x0007, 0x0048, 0x002F, 0x001B, 0x0036,
    0x0022, 0x0039, 0x0014, 0x0039, 0x001D, 0x000A, 0x0035, 0x0010, 0x001B,
    0x003D, 0x0017, 0x002E, 0x000B, 0x0049, 0x0042, 0x003D, 0x002A, 0x0001,
    0x000C, 0x001B, 0x0034, 0x0041, 0x0035, 0x0008, 0x000E, 0x004D, 0x0011,
    0x0034, 0x0041, 0x0029, 0x0048,
};

const char* g_DiagActors[] = {
    _S("Alucard"),
    _S("Maria"),
    _S("Richter"),
};

// Creates primitives for the actor name at the head of the dialogue
void func_801B675C(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = g_DiagActors[actorIndex];
    chCount = 0;
    while (true) {
        ch = *actorName++;
        if (ch == DIAG_EOL) {
            ch = *actorName++;
            if (ch == DIAG_EOS) {
                break;
            }
        }
        if (ch == MENUCHAR(' ')) {
            continue;
        }
        chCount++;
    }

    // Create chCount amount of sprites based on the actor name's letter count
    primIndex = g_api.AllocPrimitives(PRIM_SPRT, chCount);
    if (primIndex == -1) {
        DestroyEntity(self);
        return;
    }

    // Fill prims to render the actor name on screen
    prim = &g_PrimBuf[primIndex];
    g_Dialogue.primIndex[1] = primIndex;
    actorName = g_DiagActors[actorIndex];
    x = 0x38;
    while (prim != NULL) {
        ch = *actorName++;
        if (ch == MENUCHAR(' ')) {
            x += FONT_SPACE;
        } else {
            prim->type = PRIM_SPRT;
            prim->tpage = 0x1E;
            prim->clut = 0x196;
            prim->u0 = (ch & 0x0F) * FONT_W;
            prim->v0 = (ch & 0xF0) / (FONT_H / 4);
            prim->v1 = FONT_H;
            prim->u1 = FONT_W;
            prim->priority = 0x1FF;
            prim->drawMode = DRAW_HIDE;
            prim->x0 = x;
            prim->y0 = g_Dialogue.startY + 6;
            prim = prim->next;
            x += FONT_GAP;
        }
    }
}

void func_801B68E0(s32 arg0) {
    g_Dialogue.unk40 = arg0 + 0x100000;
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

void func_801B690C(u8 ySteps, Entity* self) {
    s32 primIndex = g_Dialogue.nextCharY + 1;
    Primitive* prim;
    s32 i;

    while (primIndex >= 5) {
        primIndex -= 5;
    }

    if (self->step_s == 0) {
        prim = g_Dialogue.prim[primIndex];
        prim->v1 -= ySteps;
        prim->v0 = ySteps + prim->v0;
        if (prim->v1 == 0) {
            self->step_s++;
            prim->drawMode = DRAW_HIDE;
        }
    }

    for (i = 0; i < 5; i++) {
        if (i != primIndex) {
            prim = g_Dialogue.prim[i];
            prim->y0 -= ySteps;
        }
    }
    g_Dialogue.portraitAnimTimer++;
}

// Strong resemblence to NZ0 EntityMariaCutscene and others
void func_801B69F8(Entity* entity) {
    Primitive* prim;
    s32 i;
    s32 j;
    s16 y;
    u16 nextChar;
    s32 nextChar2;
    RECT* rect;

    switch (entity->step) {
    case 0:
        if (CutsceneUnk2(D_8018B304)) {
            D_801BC350 = D_801D6B00 = D_801BC3E8 = 0;
            D_8003C704 = 1;
            entity->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            entity->primIndex = g_Dialogue.primIndex[2];
            ++entity->step;
        }
        break;
    case 1:
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && (D_801BC350 == 0)) {
                --g_Dialogue.nextCharTimer;
                return;
            }
            nextChar = g_Dialogue.nextCharDialogue++[0];
            switch (nextChar) {
            case 0:
                entity->step = 7;
                return;
            case 1:
                if (D_801BC350 != 0) {
                    continue;
                }
                g_Dialogue.nextCharX = g_Dialogue.nextLineX;
                if (!(g_Dialogue.unk12 & 1)) {
                    g_Dialogue.nextLineY += 0xC;
                }
                if (++g_Dialogue.nextCharY >= 5) {
                    g_Dialogue.nextCharY = 0;
                }
                func_801B66A4();
                if (!(g_Dialogue.unk12 & 1)) {
                    if (g_Dialogue.nextCharY < 4) {
                        continue;
                    }
                    g_Dialogue.unk12 |= 1;
                }
                g_Dialogue.portraitAnimTimer = 0;
                entity->step_s = 0;
                ++entity->step;
                return;
            case 2:
                g_Dialogue.unk17 = g_Dialogue.nextCharDialogue++[0];
                continue;
            case 3:
                g_Dialogue.nextCharTimer = g_Dialogue.nextCharDialogue++[0];
                if (D_801BC350 != 0) {
                    continue;
                }
                return;
            case 4: {
                if (D_801BC350 != 0) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (j = 0; j < 5; ++j) {
                    prim->blendMode = 8;
                    prim = prim->next;
                }
                return;
            }
            case 5: {
                s16 temp_a0;
                s16 temp_a1;
                if (D_801BC350 != 0) {
                    g_Dialogue.nextCharDialogue += 2;
                    continue;
                }
                j = g_Dialogue.nextCharDialogue++[0];
                nextChar2 = g_Dialogue.nextCharDialogue++[0];
                prim = g_Dialogue.prim[5];
                temp_a0 = D_80180824[nextChar2 & 1];
                temp_a1 = D_80180828[nextChar2 & 1];
                prim->clut = D_8018082C[j];
                prim->tpage = 0x90;
                if (nextChar2 & 0x80) {
                    prim->u0 = prim->u2 = temp_a0 + 0x2F;
                    prim->u1 = prim->u3 = temp_a0;
                } else {
                    prim->u0 = prim->u2 = temp_a0;
                    prim->u1 = prim->u3 = temp_a0 + 0x2F;
                }
                prim->v0 = prim->v1 = temp_a1;
                prim->v2 = prim->v3 = temp_a1 + 0x48;
                prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                    g_Dialogue.startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    g_Dialogue.startY + 0x24;
                g_Dialogue.clutIndex = D_80180838[j];
                CutsceneUnk1();
                func_801B66A4();
                prim->priority = 0x1FE;
                prim->blendMode = 0;
                func_801B675C(j, entity);
                g_Dialogue.portraitAnimTimer = 6;
                entity->step = 3;
                return;
            }
            case 6:
                if (D_801BC350 != 0) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (j = 0; j < 5; ++j) {
                    prim->blendMode = 8;
                    prim = prim->next;
                };
                g_api.FreePrimitives(g_Dialogue.primIndex[1]);
                g_Dialogue.primIndex[1] = -1;
                g_Dialogue.portraitAnimTimer = 6;
                entity->step = 4;
                return;
            case 7:
                if (D_801BC350 != 0) {
                    g_Dialogue.nextCharDialogue += 2;
                    continue;
                }
                g_Dialogue.startX = g_Dialogue.nextCharDialogue++[0];
                g_Dialogue.startY = g_Dialogue.nextCharDialogue++[0];
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = g_Dialogue.startY;
                prim->blendMode = 17;
                prim = prim->next;
                prim->y0 = g_Dialogue.startY - 1;
                prim->blendMode = 81;
                prim->u0 = 0;
                g_Dialogue.portraitAnimTimer = 24;
                entity->step = 5;
                entity->step_s = 0;
                return;
            case 8:
                if (D_801BC350 != 0) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0x18;
                entity->step = 6;
                return;
            case 9:
                if (D_801BC350 != 0) {
                    g_Dialogue.nextCharDialogue += 2;
                    continue;
                }
                nextChar = g_Dialogue.nextCharDialogue++[0];
                g_api.PlaySfx(
                    g_Dialogue.nextCharDialogue++[0] | (nextChar << 4));
                continue;
            case 10:
                if (D_801BC350 != 0 || g_api.func_80131F68() != false) {
                    continue;
                }
                --g_Dialogue.nextCharDialogue;
                return;
            case 11:
                if (D_801BC350 != 0 || g_api.func_80131F68() != true) {
                    continue;
                }
                --g_Dialogue.nextCharDialogue;
                return;
            case 12:
                i = g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                func_801B68E0(i);
                continue;
            case 13:
                continue;
            case 14:
                i = g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                g_Dialogue.nextCharDialogue +=
                    ((const char*)i + 0x100000)[0] * 4;
                i = g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue[0];
                g_Dialogue.nextCharDialogue = (const char*)(i + 0x100000);
                continue;
            case 15:
                i = g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue++[0];
                i <<= 4;
                i |= g_Dialogue.nextCharDialogue[0];
                g_Dialogue.nextCharDialogue = (const char*)(i + 0x100000);
                continue;
            case 16:
                if (!((D_801BC3E8 >> g_Dialogue.nextCharDialogue[0]) & 1)) {
                    --g_Dialogue.nextCharDialogue;
                    return;
                }
                D_801BC3E8 &= ~(1 << g_Dialogue.nextCharDialogue[0]);
                ++g_Dialogue.nextCharDialogue;
                continue;
            case 17:
                D_801BC3E8 |= 1 << g_Dialogue.nextCharDialogue++[0];
                continue;
            case 18:
                g_Dialogue.unk3C = 0;
                continue;
            case 19:
                if (D_801BC350 != 0) {
                    g_Dialogue.nextCharDialogue += 5;
                } else {
                    i = g_Dialogue.nextCharDialogue++[0];
                    i <<= 4;
                    i |= g_Dialogue.nextCharDialogue++[0];
                    i <<= 4;
                    i |= g_Dialogue.nextCharDialogue++[0];
                    i <<= 4;
                    i |= g_Dialogue.nextCharDialogue++[0];
                    i += 0x100000;
                    nextChar2 = g_Dialogue.nextCharDialogue++[0];
                    LoadTPage((u_long*)i, 1, 0, D_80180834[nextChar2], 0x100,
                              0x30, 0x48);
                }
                continue;
            case 20:
                nextChar = g_Dialogue.nextCharDialogue++[0];
                g_api.PlaySfx(
                    g_Dialogue.nextCharDialogue++[0] | (nextChar << 4));
                continue;
            case 21:
                D_801D6B00 = D_801BC350 = D_801BC3E8 = 0;
                continue;
            case 22:
                D_801BC3E8 &= ~(1 << g_Dialogue.nextCharDialogue++[0]);
                continue;
            case 23:
                return;
            case 24:
                if (!((D_801BC3E8 >> g_Dialogue.nextCharDialogue[0]) & 1)) {
                    --g_Dialogue.nextCharDialogue;
                    return;
                }
                ++g_Dialogue.nextCharDialogue;
                continue;
            default:
                if (D_801BC350 != 0) {
                    ++g_Dialogue.nextCharDialogue;
                    continue;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break;
        }

        if (nextChar == 0x20) {
            g_Dialogue.nextCharX += 2;
            break;
        }
        rect->x = ((nextChar & 0xF) * 2) + 0x380;
        rect->y = ((nextChar & 0xF0) / 2) + 0xF0;
        rect->w = 2;
        rect->h = 8;
        y = g_Dialogue.nextCharY * 12 + 0x180;
        MoveImage(rect, g_Dialogue.nextCharX, y);
        g_Dialogue.nextCharX += 2;
        break;
    case 2:
        func_801B690C(2, entity);
        if (g_Dialogue.portraitAnimTimer >= 6) {
            entity->step -= 1;
        }
        break;
    case 3:
        prim = g_Dialogue.prim[5];
        prim->x0 = prim->x2 = prim->x2 - 4;
        prim->x1 = prim->x3 = prim->x3 + 4;
        prim->y0 = prim->y1 = prim->y1 - 6;
        prim->y2 = prim->y3 = prim->y3 + 6;

        if (--g_Dialogue.portraitAnimTimer == 0) {
            entity->step = 1;
            for (prim = &g_PrimBuf[g_Dialogue.primIndex[1]]; prim;
                 prim = prim->next) {
                prim->blendMode = 0;
            }
        }
        break;
    case 4:
        prim = g_Dialogue.prim[5];
        prim->x0 = prim->x2 = prim->x2 + 4;
        prim->x1 = prim->x3 = prim->x3 - 4;
        prim->y0 = prim->y1 = prim->y1 + 6;
        prim->y2 = prim->y3 = prim->y3 - 6;
        if (prim->x1 >= (g_Dialogue.startX - 2)) {
            prim->x1 = prim->x3 = g_Dialogue.startX - 3;
        }
        if (--g_Dialogue.portraitAnimTimer == 0) {
            entity->step = 1;
        }
        break;
    case 5:
        D_801D6B00 = 1;
        prim = g_Dialogue.prim[5];
        prim = prim->next;
        if (--g_Dialogue.portraitAnimTimer >= 12) {
            prim = prim->next;
            prim->u0 += 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                ++prim->u0;
                break;
            }
        } else {
            if (g_Dialogue.portraitAnimTimer == 0) {
                entity->step = 1;
            }
            prim->y2 = prim->y3 = prim->y3 + 6;
        }
        break;
    case 6:
        prim = g_Dialogue.prim[5];
        prim = prim->next;
        if (--g_Dialogue.portraitAnimTimer >= 12) {
            prim = prim->next;
            prim->u0 += 0xEC;
            if (g_Dialogue.portraitAnimTimer & 1) {
                --prim->u0;
                break;
            }
        } else {
            if (g_Dialogue.portraitAnimTimer == 0) {
                entity->step = 1;
                prim->blendMode = 8;
            } else {
                prim->y2 = prim->y3 = prim->y3 - 6;
            }
            prim = prim->next;
            prim->blendMode = 8;
        }
        break;
    case 7:
        D_8003C704 = 0;
        break;
    }
}

u8 func_801B76F0(const char* msg) {
    const int PRIM = -5;
    Primitive* prim;
    s16 i;

    g_Dialogue.primIndex[PRIM] = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (g_Dialogue.primIndex[PRIM] != -1) {
        g_Dialogue.nextCharX = 0x200;
        g_Dialogue.nextCharDialogue = msg;
        g_Dialogue.startY = 0x20B;
        g_Dialogue.nextLineX = 0;
        g_Dialogue.nextCharY = 0;
        g_Dialogue.portraitAnimTimer = 0;
        g_Dialogue.unk12 = 0;
        g_Dialogue.clutIndex = 0;
        g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[PRIM]];
        prim = &g_PrimBuf[g_Dialogue.primIndex[PRIM]];
        for (i = 0; i < 0x20; i++) {
            if (i & 1) {
                prim->tpage = 9;
                prim->x0 = 0xF8;
            } else {
                prim->tpage = 8;
                prim->x0 = 0x18;
            }
            prim->v0 = (i >> 1) * 0x10;
            prim->u0 = 0;
            prim->u1 = 0xF0;
            prim->x1 = 0;
            prim->v1 = 0x10;
            prim->y0 = (i >> 1) * 0x13 + 0xF0;
            prim->clut = 0x1A1;
            prim->priority = 3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }

        return true;
    }
    g_Dialogue.primIndex[PRIM] = 0;
    return false;
}

void func_801B786C(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

u16* func_801B78BC(char ch) {
    u16 jCh;
#ifndef VERSION_PC

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

s32 func_801B79D4(Entity* entity) {
    Primitive* prim;
    int bitDepth;
    u16 nextChar;
    u16 glyphIndex;
    u16* glyph;
    u16 y;
    s16 y0;
    s32 i;
    u16* var_v1;
    const char* temp_a0_5;

    switch (entity->step) {
    case 0:
        if (func_801B76F0(D_8018BC54)) {
            entity->flags |= FLAG_HAS_PRIMS;
            entity->primIndex = (s32)g_Dialogue.prim[1];
            ++entity->step;
            func_801B786C(0);
            glyphIndex = 0;
            while (1) {
                nextChar = g_Dialogue.nextCharDialogue++[0];
                if (nextChar == 1) {
                    g_Dialogue.startY =
                        g_Dialogue.nextCharDialogue++[0] + g_Dialogue.nextCharX;
                    ++g_Dialogue.nextLineX;
                    break;
                }
                glyph = func_801B78BC(nextChar);
                if (glyph) {
                    var_v1 = D_801BB0F8[glyphIndex];
                    for (i = 0; i < 0x30; ++i) {
                        var_v1++[0] = glyph++[0];
                    }
                    y = g_Dialogue.nextLineX * 16;
                    LoadTPage((u_long*)D_801BB0F8[glyphIndex], 0, 0,
                              g_Dialogue.startY, y, 12, 16);
                    g_Dialogue.startY += 3;
                    y = g_Dialogue.startY - g_Dialogue.nextCharX - 0x38;
                    if (y < 8) {
                        g_Dialogue.startY += 8;
                    }
                    ++glyphIndex;
                } else {
                    g_Dialogue.startY += 2;
                    y = g_Dialogue.startY - g_Dialogue.nextCharX - 0x38;

                    if (y < 8) {
                        g_Dialogue.startY += 8;
                    }
                }
            }
        }
        break;
    case 1:
        if (g_Dialogue.nextCharY == 0u) {
            break;
        }
        temp_a0_5 = g_Dialogue.nextCharDialogue++;
        nextChar = temp_a0_5[0];
        bitDepth = 0;

        switch (nextChar) {
        case 0:
            entity->step = 7U;
            g_Dialogue.unk12 = 0x400;
            return 0;
        case 1:
            g_Dialogue.nextCharDialogue = temp_a0_5 + 2;
            g_Dialogue.startY = temp_a0_5[1] + g_Dialogue.nextCharX;
            if (++g_Dialogue.nextLineX >= 0x10) {
                g_Dialogue.nextLineX = 0;
            }
            g_Dialogue.nextCharY = 0;
            return 0;
        case 2:
            g_Dialogue.nextCharDialogue = temp_a0_5 + 2;
            g_Dialogue.startY = temp_a0_5[1] + g_Dialogue.nextCharX;
            if (++g_Dialogue.nextLineX >= 0x10) {
                g_Dialogue.nextLineX = 0;
            }

            prim = g_Dialogue.prim[0];
            for (i = 0; i < g_Dialogue.nextLineX; ++i) {
                prim = prim->next;
                prim = prim->next;
            }

            y0 = prim->y0;
            prim = g_Dialogue.prim[0];
            while (prim) {
                if (prim->y0 >= y0) {
                    prim->y0 += 6;
                    prim->x1 += 6;
                }
                prim = prim->next;
            }
            g_Dialogue.unk12 += 0x18;
            g_Dialogue.nextCharY = 0;
            g_Dialogue.portraitAnimTimer += 6;
            return 0;
        case 3:
            g_Dialogue.nextCharDialogue = temp_a0_5 + 2;
            g_Dialogue.startY = temp_a0_5[1] + g_Dialogue.nextCharX;
            if (++g_Dialogue.nextLineX >= 0x10) {
                g_Dialogue.nextLineX = 0;
            }
            prim = g_Dialogue.prim[0];
            for (i = 0; i < g_Dialogue.nextLineX; ++i) {
                prim = prim->next;
                prim = prim->next;
            }

            y0 = prim->y0;
            prim = g_Dialogue.prim[0];
            while (prim) {
                if (prim->y0 >= y0) {
                    prim->y0 += 12;
                    prim->x1 += 12;
                }
                prim = prim->next;
            }

            g_Dialogue.unk12 += 0x30;
            g_Dialogue.nextCharY = 0;
            g_Dialogue.portraitAnimTimer += 0xC;
            return 0;
        }
        if (nextChar & 0x80) {
            nextChar = g_Dialogue.nextCharDialogue++[0] | (nextChar << 8);
            glyph = g_api.func_80106A28(nextChar, 0);
        } else {
            glyph = func_801B78BC(nextChar & 0xFF);
        }
        if (glyph) {
            y = g_Dialogue.nextLineX * 16;
            LoadTPage(
                (u_long*)glyph, bitDepth, 0, g_Dialogue.startY, y, 0xC, 0x10);
            g_Dialogue.startY += 3;
            y = g_Dialogue.startY - g_Dialogue.nextCharX - 0x38;
            if (y < 8) {
                g_Dialogue.startY += 8;
            }
        } else {
            g_Dialogue.startY += 3;
            y = g_Dialogue.startY - g_Dialogue.nextCharX - 0x38;
            if (y < 8) {
                do {
                    g_Dialogue.startY += 8;
                } while (0);
            }
        }
        break;
    case 2:
        break;
    case 7:
        return --g_Dialogue.unk12 == 0;
    }

    if (g_Dialogue.unk12 == 0) {
        func_801B786C(g_Dialogue.nextLineX);
        g_Dialogue.nextCharY = 1;
        g_Dialogue.unk12 = 76;
    }
    --g_Dialogue.unk12;
    if (g_Dialogue.clutIndex == 0) {
        prim = g_Dialogue.prim[0];
        for (i = 0; i < 32; ++i) {
            if (--prim->y0 == -19) {
                prim->y0 = g_Dialogue.portraitAnimTimer - prim->x1 + 285;
                prim->x1 = g_Dialogue.portraitAnimTimer;
            }
            prim = prim->next;
        };
        g_Dialogue.clutIndex = 4;
    }
    --g_Dialogue.clutIndex;
    return 0;
}
