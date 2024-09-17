// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * Overlay: ST0
 * Description: Cutscene of Richter talking to Dracula
 */

#include "st0.h"

#include "../cutscene_unk1.h"

s32 func_801A89D8(const char* textDialogue) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 8);
    g_Dialogue.primIndex[2] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        g_Dialogue.primIndex[2] = 0;
        return 0;
    }
    g_Dialogue.nextCharDialogue = textDialogue;
    g_Dialogue.unk3C = 0;
    g_Dialogue.primIndex[1] = -1;
    g_Dialogue.primIndex[0] = -1;
    CutsceneUnk1();

    if (prim && prim) { // !FAKE
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

    prim->type = 4;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = 3;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = 1;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->r0 = prim->g0 = prim->b0 = 0xFF;
    prim->priority = 0x1FC;
    prim->drawMode = DRAW_HIDE;
    return 1;
}

void func_801A8B9C(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

void func_801A8BF8(void) {
    Primitive* prim;

    func_801A8B9C(g_Dialogue.nextCharY);
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

const char* D_80180828[] = {_S("Richter"), _S("Dracula")};

// Creates primitives for the actor name at the head of the dialogue
void func_801A8CB0(u16 actorIndex, Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 x;
    u16 chCount;
    const char* actorName;
    char ch;

    actorName = D_80180828[actorIndex];
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
    actorName = D_80180828[actorIndex];
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

void func_801A8E34(s32 arg0) {
    g_Dialogue.unk40 = arg0 + 0x100000;
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

#include "../../st/cutscene.h"

// Animates the portrait size of the actor by enlarging or shrinking it
void func_801A910C(u8 ySteps) {
    Primitive* prim;
    s32 primIndex;
    s32 i;

    primIndex = g_Dialogue.nextCharY + 1;
    while (primIndex >= 5) {
        primIndex -= 5;
    }
    if (g_CurrentEntity->step_s == 0) {
        prim = g_Dialogue.prim[primIndex];
        prim->v1 -= ySteps;
        prim->v0 += ySteps;
        if (prim->v1 == 0) {
            g_CurrentEntity->step_s++;
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

void EntityDraculaCutscene(Entity* self) {
    RECT rect;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 j;
    s16 uCoord;
    s16 vCoord;
    u16 nextChar;
    s32 nextChar2;
    s32 bit_shifty;

    if ((D_801C2580 != 0) && (D_801C24C8 == 0) &&
        ((g_Settings.D_8003CB04 & 1) || (g_IsTimeAttackUnlocked != 0)) &&
        (g_pads[0].tapped == PAD_START)) {
        D_801C24C8 = 1;
        g_api.FreePrimitives(self->primIndex);
        self->flags &= ~FLAG_HAS_PRIMS;
        if (g_Dialogue.primIndex[1] != -1) {
            g_api.FreePrimitives(g_Dialogue.primIndex[1]);
        }
        if (g_Dialogue.primIndex[0] != -1) {
            g_api.FreePrimitives(g_Dialogue.primIndex[0]);
        }
        g_api.PlaySfx(0x80);
        self->step = 1;
        self->step_s = 0;
    }
    if ((self->step) && (g_Dialogue.unk3C != 0)) {
        CutsceneRun();
    }

    switch (self->step) {
    case 0:
        if (func_801A89D8(D_801829D8) & 0xFF) {
            self->flags |= FLAG_HAS_PRIMS;
            g_CutsceneFlags = 0;
            D_801C2580 = 0;
            D_801C24C8 = 0;
            D_8003C704 = 1;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step += 1;
            if (g_DemoMode != Demo_None) {
                D_801C24C8 = 1;
                D_801C2580 = 1;
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
            }
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && (D_801C24C8 == 0)) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.nextCharDialogue++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;
            case 1:
                if (D_801C24C8 != 0) {
                    continue;
                }
                g_Dialogue.nextCharX = g_Dialogue.nextLineX;
                if (!(g_Dialogue.unk12 & 1)) {
                    g_Dialogue.nextLineY += 12;
                }
                g_Dialogue.nextCharY++;
                if (g_Dialogue.nextCharY >= 5) {
                    g_Dialogue.nextCharY = 0;
                }
                func_801A8BF8();
                if (!(g_Dialogue.unk12 & 1)) {
                    if (g_Dialogue.nextCharY >= 4) {
                        g_Dialogue.unk12 |= 1;
                        g_Dialogue.portraitAnimTimer = 0;
                        self->step_s = 0;
                        self->step++;
                        return;
                    }
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0;
                self->step_s = 0;
                self->step++;
                return;
            case 2:
                g_Dialogue.unk17 = *g_Dialogue.nextCharDialogue++;
                continue;
            case 3:
                g_Dialogue.nextCharTimer = *g_Dialogue.nextCharDialogue++;
                if (D_801C24C8 != 0) {
                    continue;
                }
                return;
            case 4:
                if (D_801C24C8 != 0) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;
            case 5:
                if (D_801C24C8 != 0) {
                    g_Dialogue.nextCharDialogue += 2;
                    continue;
                }
                // fake reuse of i?
                i = *g_Dialogue.nextCharDialogue++;
                nextChar2 = *g_Dialogue.nextCharDialogue++;
                prim = g_Dialogue.prim[5];
                uCoord = D_80180784[nextChar2 & 1]; // a1
                vCoord = D_80180788[nextChar2 & 1]; // a2
                prim->clut = D_8018078C[i];
                prim->tpage = 0x90;
                if (nextChar2 & 0x80) {
                    prim->u0 = prim->u2 = uCoord + 0x2F;
                    prim->u1 = prim->u3 = uCoord;
                } else {
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 0x2F;
                }
                prim->v0 = prim->v1 = vCoord;
                prim->v2 = prim->v3 = vCoord + 0x48;
                prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                    g_Dialogue.startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    g_Dialogue.startY + 0x24;
                g_Dialogue.clutIndex = D_80180794[i];
                CutsceneUnk1();
                func_801A8BF8();
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                func_801A8CB0(i, self);
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 3;
                return;
            case 6:
                if (D_801C24C8 != 0) {
                    continue;
                }
                for (prim = g_Dialogue.prim[0], i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                g_api.FreePrimitives(g_Dialogue.primIndex[1]);
                g_Dialogue.primIndex[1] = -1;
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 4;
                return;
            case 7:
                if (D_801C24C8 != 0) {
                    g_Dialogue.nextCharDialogue++;
                    g_Dialogue.nextCharDialogue++;
                    continue;
                }
                g_Dialogue.startX = *g_Dialogue.nextCharDialogue++;
                g_Dialogue.startY = *g_Dialogue.nextCharDialogue++;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->y0 = prim->y1 = g_Dialogue.startY;
                prim->y2 = prim->y3 = g_Dialogue.startY + 0x48;
                prim = prim->next;
                prim->y0 = g_Dialogue.startY - 1;
                prim->u0 = 0xF6;
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 5;
                self->step_s = 0;
                return;

            case 8:
                if (D_801C24C8 != 0) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 6;
                return;
            case 9:
                if (D_801C24C8 != 0) {
                    g_Dialogue.nextCharDialogue++;
                    g_Dialogue.nextCharDialogue++;
                    continue;
                }
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;
            case 10:
                if (D_801C24C8 != 0) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;
            case 11:
                if (D_801C24C8 != 0) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;
            case 12:
                bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                func_801A8E34((u8*)bit_shifty);
                continue;
            case 13:
                continue;
            case 14:
                bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                // This needs help. Casting the const to short is good.
                bit_shifty += (u16)0x100000;
                g_Dialogue.nextCharDialogue += *(u16*)bit_shifty << 2;

                bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue;
                g_Dialogue.nextCharDialogue = (u8*)bit_shifty + 0x100000;
                continue;

            case 15: // c64
                bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= (s32)*g_Dialogue.nextCharDialogue;
                g_Dialogue.nextCharDialogue = (u8*)bit_shifty + 0x100000;
                continue;

            case 16:
                if (!((g_CutsceneFlags >> *g_Dialogue.nextCharDialogue) & 1)) {
                    g_Dialogue.nextCharDialogue--;
                    return;
                }
                g_CutsceneFlags &= ~(1 << *g_Dialogue.nextCharDialogue);
                *g_Dialogue.nextCharDialogue++;
                continue;
            case 17:
                g_CutsceneFlags |= 1 << *g_Dialogue.nextCharDialogue++;
                continue;
            case 18:
                g_Dialogue.unk3C = 0;
                continue;
            case 19:
                if (D_801C24C8 != 0) {
                    g_Dialogue.nextCharDialogue += 5;
                } else {
                    bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;  // 8e4
                    bit_shifty <<= 4;                                  // 918
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++; // 91c
                    bit_shifty <<= 4;                                  // 920
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++; // 924
                    bit_shifty <<= 4;                                  // 928
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++; // 92c
                    bit_shifty += 0x100000;                            //
                    nextChar2 = g_Dialogue.nextCharDialogue++[0];
                    LoadTPage((u32*)bit_shifty, 1, 0, D_80180790[nextChar2],
                              0x100, 0x30, 0x48);
                }
                continue;
            case 20:
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;
            // Note: Other cutscenes have Case 21-24 here, this one is missing
            // it.
            default:
                if (D_801C24C8 != 0) {
                    continue;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break; // This breaks the big while-loop!
        }
        // End of while loop, comes at a58
        if (nextChar == 0x20) {
            g_Dialogue.nextCharX += 2;
            return;
        }
        rect.x = ((nextChar & 0xF) * 2) + 0x380;
        rect.y = ((u32)(nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 0xC) + 0x180;
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
        break;
    case 2:
        func_801A910C(2U);
        if (g_Dialogue.portraitAnimTimer >= 6) {
            self->step -= 1;
            return;
        }
        break;
    case 3:
        prim = g_Dialogue.prim[5];
        prim->x0 = prim->x2 -= 4;
        prim->x1 = prim->x3 += 4;
        prim->y0 = prim->y1 -= 6;
        prim->y2 = prim->y3 += 6;
        // This block is in case 4 for other cutscenes, case 3 for this one
        if (prim->x1 >= (g_Dialogue.startX - 2)) {
            prim->x1 = prim->x3 = g_Dialogue.startX - 3;
        }
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = 1;
            for (prim = &g_PrimBuf[g_Dialogue.primIndex[1]]; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_DEFAULT;
            }
        }
        break;
    case 4:
        prim = g_Dialogue.prim[5];
        prim->x0 = prim->x2 += 4;
        prim->x1 = prim->x3 -= 4;
        prim->y0 = prim->y1 += 6;
        prim->y2 = prim->y3 -= 6;
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = 1;
            return;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            D_801C2580 = 1;
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x48);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            g_Dialogue.primIndex[0] = primIndex;
            for (prim = &g_PrimBuf[primIndex], j = 0; prim != NULL;
                 prim = prim->next) {
                prim->r0 = prim->r1 = 0x7F;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 0xF7;
                prim->y0 = prim->y1 = g_Dialogue.startY + j;
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = D_80180798[j];
                prim->x3 = 0xF70;

                j++;
            }
            self->step_s++;
            return;
        case 1: /* switch 3 */
            for (j = 0, prim = &g_PrimBuf[g_Dialogue.primIndex[0]];
                 prim != NULL; prim = prim->next) {
                prim->x3 -= prim->x2;
                prim->x2 += 2;
                prim->x0 = prim->x3 / 16;
                if (prim->x0 < 5) {
                    prim->x0 = 4;
                } else {
                    j = 1;
                }
            }
            if (j == 0) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                g_Dialogue.primIndex[0] = -1;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->blendMode = 0x11;
                prim = prim->next;
                prim->blendMode = 0x51;
                self->step_s++;
                return;
            }
            break;
        case 2:
            j = 0;
            prim = g_Dialogue.prim[5];
            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 0x10;
                j = 1;
            }
            if (prim->b0 >= 0x7F) {
                prim->b0 = prim->b1 = 0x7F;
            } else {
                prim->b0 = prim->b1 += 8;
                j = 1;
            }

            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->g0 = prim->b0 = 0x10;
            } else {
                prim->r0 = prim->g0 = prim->b0 -= 0xF;
                j = 1;
            }
            if (j == 0) {
                self->step = 1;
            }
        }
        break;
    case 6:
        prim = g_Dialogue.prim[5];
        prim = prim->next;
        g_Dialogue.portraitAnimTimer--;
        if (g_Dialogue.portraitAnimTimer >= 0xC) {
            prim = prim->next;
            prim->u0 -= 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                prim->u0--;
                return;
            }
        } else {
            if (!g_Dialogue.portraitAnimTimer) {
                self->step = 1;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->y2 = (prim->y3 -= 6);
            }
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            return;
        }
        break;

    case 7:
        D_8003C704 = 0;
        g_Settings.D_8003CB04 |= 1;
        DestroyEntity(self);
        break;
    }
}
