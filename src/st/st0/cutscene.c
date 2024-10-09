// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;

#include "../cutscene_unk1.h"

static u8 SetCutsceneScript(u8* script) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 8);
    g_Dialogue.primIndex[2] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        g_Dialogue.primIndex[2] = 0;
        return 0;
    }
    g_Dialogue.scriptCur = script;
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

#include "../cutscene_unk3.h"

#include "../cutscene_unk4.h"

static const char* actor_names[] = {_S("Richter"), _S("Dracula")};

#include "../cutscene_actor_name.h"

#include "../set_cutscene_end.h"

#include "../cutscene_run.h"

#include "../cutscene_scale_avatar.h"

extern u8 OVL_EXPORT(cutscene_data)[];
void OVL_EXPORT(EntityCutscene)(Entity* self) {
    RECT rect;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 j;
    s16 uCoord;
    s16 vCoord;
    u16 nextChar;
    s32 nextChar2;
    u_long ptr;

    if (g_IsCutsceneDone && !g_SkipCutscene &&
        ((g_Settings.D_8003CB04 & 1) || g_IsTimeAttackUnlocked) &&
        (g_pads[0].tapped == PAD_START)) {
        g_SkipCutscene = 1;
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
    if (self->step && (g_Dialogue.unk3C != 0)) {
        CutsceneRun();
    }

    switch (self->step) {
    case 0:
        if (SetCutsceneScript(OVL_EXPORT(cutscene_data))) {
            self->flags |= FLAG_HAS_PRIMS;
            g_CutsceneFlags = 0;
            g_IsCutsceneDone = 0;
            g_SkipCutscene = 0;
            g_CutsceneHasControl = 1;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step += 1;
            if (g_DemoMode != Demo_None) {
                g_SkipCutscene = 1;
                g_IsCutsceneDone = 1;
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
            }
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && !g_SkipCutscene) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.scriptCur++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;
            case 1:
                if (g_SkipCutscene) {
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
                g_Dialogue.unk17 = *g_Dialogue.scriptCur++;
                continue;
            case 3:
                g_Dialogue.nextCharTimer = *g_Dialogue.scriptCur++;
                if (g_SkipCutscene) {
                    continue;
                }
                return;
            case 4:
                if (g_SkipCutscene) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;
            case 5:
                if (g_SkipCutscene) {
                    g_Dialogue.scriptCur += 2;
                    continue;
                }
                // fake reuse of i?
                i = *g_Dialogue.scriptCur++;
                nextChar2 = *g_Dialogue.scriptCur++;
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
                CutsceneUnk4();
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                DrawCutsceneActorName(i, self);
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 3;
                return;
            case 6:
                if (g_SkipCutscene) {
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
                if (g_SkipCutscene) {
                    g_Dialogue.scriptCur++;
                    g_Dialogue.scriptCur++;
                    continue;
                }
                g_Dialogue.startX = *g_Dialogue.scriptCur++;
                g_Dialogue.startY = *g_Dialogue.scriptCur++;
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
                if (g_SkipCutscene) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 6;
                return;
            case 9:
                if (g_SkipCutscene) {
                    g_Dialogue.scriptCur++;
                    g_Dialogue.scriptCur++;
                    continue;
                }
                nextChar = *g_Dialogue.scriptCur++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            case 10:
                if (g_SkipCutscene) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                *g_Dialogue.scriptCur--;
                return;
            case 11:
                if (g_SkipCutscene) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *g_Dialogue.scriptCur--;
                return;
            case 12:
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                SetCutsceneEnd((u8*)ptr);
                continue;
            case 13:
                continue;
            case 14:
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                // This needs help. Casting the const to short is good.
                ptr += (u16)0x100000;
                g_Dialogue.scriptCur += *(u16*)ptr << 2;

                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur;
                g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
                continue;

            case 15: // c64
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur;
                g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
                continue;

            case 16:
                if (!((g_CutsceneFlags >> *g_Dialogue.scriptCur) & 1)) {
                    g_Dialogue.scriptCur--;
                    return;
                }
                g_CutsceneFlags &= ~(1 << *g_Dialogue.scriptCur);
                *g_Dialogue.scriptCur++;
                continue;
            case 17:
                g_CutsceneFlags |= 1 << *g_Dialogue.scriptCur++;
                continue;
            case 18:
                g_Dialogue.unk3C = 0;
                continue;
            case 19:
                if (g_SkipCutscene) {
                    g_Dialogue.scriptCur += 5;
                } else {
                    ptr = (u_long)*g_Dialogue.scriptCur++;  // 8e4
                    ptr <<= 4;                              // 918
                    ptr |= (u_long)*g_Dialogue.scriptCur++; // 91c
                    ptr <<= 4;                              // 920
                    ptr |= (u_long)*g_Dialogue.scriptCur++; // 924
                    ptr <<= 4;                              // 928
                    ptr |= (u_long)*g_Dialogue.scriptCur++; // 92c
                    ptr += 0x100000;                        //
                    nextChar2 = g_Dialogue.scriptCur++[0];
                    LoadTPage((u32*)ptr, 1, 0, D_80180790[nextChar2], 0x100,
                              0x30, 0x48);
                }
                continue;
            case 20:
                nextChar = *g_Dialogue.scriptCur++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            // Note: Other cutscenes have Case 21-24 here, this one is missing
            // it.
            default:
                if (g_SkipCutscene) {
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
            g_IsCutsceneDone = 1;
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
        g_CutsceneHasControl = 0;
        g_Settings.D_8003CB04 |= 1;
        DestroyEntity(self);
        break;
    }
}
