// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

// This file consists of EntityMariaCutscene, and all the functions it calls.
// No function in NZ0 calls anything in there, nor does anything in here call
// any NZ0 functions, besides the ones in this file.

#include "../cutscene_unk1.h"

#include "../cutscene_unk2.h"

#include "../cutscene_unk3.h"

#include "../cutscene_unk4.h"

#include "../cutscene_avatar.h"

#include "../cutscene_unk6.h"

#include "../cutscene.h"

#include "../cutscene_scale_avatar.h"

// cutscene where alucard and maria discuss castle changing
void EntityMariaCutscene(Entity* self) {
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

    if (self->step != 0) {
        if ((D_801CB73C != 0) && (D_801CB684 == 0) &&
            ((g_Settings.D_8003CB04 & 0x100) ||
             (g_IsTimeAttackUnlocked != 0)) &&
            (g_pads[0].tapped == PAD_START)) {
            D_801CB684 = 1;
            g_api.FreePrimitives(self->primIndex);
            self->flags ^= FLAG_HAS_PRIMS;
            if (g_Dialogue.primIndex[1] != -1) {
                g_api.FreePrimitives(g_Dialogue.primIndex[1]);
            }
            if (g_Dialogue.primIndex[0] != -1) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
            }
            g_api.PlaySfx(SET_STOP_MUSIC);
            self->step = 1;
            self->step_s = 0;
        }
        if ((self->step) && (g_Dialogue.unk3C != 0)) {
            CutsceneRun();
        }
    }
    switch (self->step) {
    case 0:
        if ((g_CastleFlags[CASTLE_FLAG_133] != 0) ||
            (g_PlayableCharacter != PLAYER_ALUCARD)) {
            DestroyEntity(self);
            return;
        }
        if (SetCutsceneScript(D_80183B0C)) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            g_CutsceneFlags = 0;
            D_801CB73C = 0;
            D_801CB684 = 0;
            D_8003C704 = 1;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step++;
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && (D_801CB684 == 0)) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.nextCharDialogue++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;
            case 1:
                if (D_801CB684 != 0) {
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
                CutsceneUnk4();
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
                if (D_801CB684 != 0) {
                    continue;
                }
                return;
            case 4:
                if (D_801CB684 != 0) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;
            case 5:
                if (D_801CB684 != 0) {
                    g_Dialogue.nextCharDialogue += 2;
                    continue;
                }
                // fake reuse of i?
                i = *g_Dialogue.nextCharDialogue++;
                nextChar2 = *g_Dialogue.nextCharDialogue++;
                prim = g_Dialogue.prim[5];
                uCoord = D_801813C8[nextChar2 & 1];
                vCoord = D_801813CC[nextChar2 & 1];
                prim->clut = D_801813D0[i];
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
                g_Dialogue.clutIndex = D_801813D8[i];
                CutsceneUnk1();
                CutsceneUnk4();
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                DrawCutsceneAvatar(i, self);
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 3;
                return;
            case 6:
                if (D_801CB684 != 0) {
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
                if (D_801CB684 != 0) {
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
                if (D_801CB684 != 0) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 6;
                return;
            case 9:
                if (D_801CB684 != 0) {
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
                if (D_801CB684 != 0) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;
            case 11:
                if (D_801CB684 != 0) {
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
                CutsceneUnk6((u8*)bit_shifty);
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

            case 15:
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
                if (D_801CB684 != 0) {
                    g_Dialogue.nextCharDialogue += 5;
                } else {
                    bit_shifty = (s32)*g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= (s32)*g_Dialogue.nextCharDialogue++;
                    bit_shifty += 0x100000;
                    nextChar2 = g_Dialogue.nextCharDialogue++[0];
                    LoadTPage((u32*)bit_shifty, 1, 0, D_801813D4[nextChar2],
                              0x100, 0x30, 0x48);
                }
                continue;
            case 20:
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;
            case 21:
                g_CutsceneFlags = 0;
                D_801CB684 = 0;
                D_801CB73C = 0;
                continue;
            case 22:
                g_CutsceneFlags &= ~(1 << *g_Dialogue.nextCharDialogue++);
                continue;
            case 23:
                return;
            case 24:
                if (!((g_CutsceneFlags >> *g_Dialogue.nextCharDialogue) & 1)) {
                    *g_Dialogue.nextCharDialogue--;
                    return;
                }
                *g_Dialogue.nextCharDialogue++;
                continue;
            default:
                if (D_801CB684 != 0) {
                    continue;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break; // This breaks the big while-loop!
        }
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
        ScaleCutsceneAvatar(2);
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
        if (prim->x1 >= (g_Dialogue.startX - 2)) {
            prim->x1 = prim->x3 = g_Dialogue.startX - 3;
        }
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = 1;
            return;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            D_801CB73C = 1;
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
                prim->x2 = D_801813DC[j];
                prim->x3 = 0xF70;

                j++;
            }
            self->step_s++;
            return;
        case 1:
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
        DestroyEntity(self);
        g_CastleFlags[CASTLE_FLAG_133] = 1;
        D_8003C704 = 0;
        g_Settings.D_8003CB04 |= 0x100;
        break;
    }
}
