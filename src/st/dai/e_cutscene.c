// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"
#include <cutscene.h>

extern u8 OVL_EXPORT(cutscene_script)[];
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[]; // Defined by e_init

// data
static u8 D_us_80180EE0[] = {0, 64, 0, 0};
static u8 D_us_80180EE4[] = {0, 0, 0, 0};
static u16 D_us_80180EE8[] = {600, 608, 528, 536};
static u16 D_us_80180EF0[] = {0, 32};
static u16 D_us_80180EF4[] = {417, 417, 417, 417};
static s16 D_us_80180EFC[] = {
    8,  19, 17, 49, 79, 38, 54, 29, 27, 51, 44, 33, 25, 10, 51, 31, 72, 47,
    19, 25, 77, 75, 23, 29, 18, 2,  27, 42, 80, 69, 50, 13, 42, 77, 6,  39,
    7,  72, 47, 27, 54, 34, 57, 20, 57, 29, 10, 53, 16, 27, 61, 23, 46, 11,
    73, 66, 61, 42, 1,  12, 27, 52, 65, 53, 8,  14, 77, 17, 52, 65, 41, 72};

static const char* actor_names[] = {_S("Alucard"), _S("Maria")};

// bss
static s32 skip_cutscene;
Dialogue g_Dialogue; // Used by cutscene_init
STATIC_PAD_BSS(104);
u32 g_CutsceneFlags; // Used by cutscene_init
static s32 is_cutscene_done;

// These three are reversed in order from psp
#include "../cutscene_script_text.h"
#include "../cutscene_script_box.h"
#include "../cutscene_actor_name.h"

static void SetCutsceneEnd(u8* ptr) {
    g_Dialogue.scriptEnd = ptr + 0x100000;
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

static void CutsceneRun(void) {
    Entity* entity;
    u16 startTimer;

    g_Dialogue.timer++;
    // protect from overflows
    if (g_Dialogue.timer >= 0xFFFF) {
        g_Dialogue.unk3C = 0;
        return;
    }
    while (true) {
        // Start the dialogue script only if the start timer has passed
        startTimer = *g_Dialogue.scriptEnd++ << 8;
        startTimer |= *g_Dialogue.scriptEnd++;
        if (g_Dialogue.timer < startTimer) {
            // Re-evaluate the condition at the next frame
            g_Dialogue.scriptEnd -= 2;
            return;
        }
        switch (*g_Dialogue.scriptEnd++) {
        case 0:
            entity = &g_Entities[*g_Dialogue.scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            entity->entityId = *g_Dialogue.scriptEnd++;
            entity->pfnUpdate = OVL_EXPORT(EntityUpdates)[entity->entityId - 1];
            entity->posX.i.hi = *g_Dialogue.scriptEnd++ * 16;
            entity->posX.i.hi |= *g_Dialogue.scriptEnd++;
            entity->posY.i.hi = *g_Dialogue.scriptEnd++ * 16;
            entity->posY.i.hi |= *g_Dialogue.scriptEnd++;
            entity->posX.i.hi -= g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi -= g_Tilemap.scrollY.i.hi;
            break;
        case 1:
            entity = &g_Entities[*g_Dialogue.scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            break;
        case 2:
            if (!((g_CutsceneFlags >> *g_Dialogue.scriptEnd) & 1)) {
                g_Dialogue.scriptEnd--;
                return;
            }
            g_CutsceneFlags &= ~(1 << *g_Dialogue.scriptEnd++);
            break;
        case 3:
            g_CutsceneFlags |= 1 << *g_Dialogue.scriptEnd++;
            break;
        }
    }
}

// Animates the portrait size of the actor by enlarging or shrinking it
static void ScaleCutsceneAvatar(const u8 ySteps) {
    const int PrimCount = 5;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    primIndex = g_Dialogue.nextCharY + 1;
    while (primIndex >= PrimCount) {
        primIndex -= PrimCount;
    }
    if (g_CurrentEntity->step_s == 0) {
        prim = g_Dialogue.prim[primIndex];
        prim->v0 += ySteps;
        prim->v1 -= ySteps;
        if (prim->v1 == 0) {
            g_CurrentEntity->step_s++;
            prim->drawMode = DRAW_HIDE;
        }
    }

    for (i = 0; i < PrimCount; i++) {
        if (i != primIndex) {
            prim = g_Dialogue.prim[i];
            prim->y0 -= ySteps;
        }
    }
    g_Dialogue.portraitAnimTimer++;
}

void OVL_EXPORT(EntityCutscene)(Entity* self) {
    s16 uCoord, vCoord;
    s32 primIndex;
    RECT rect;
    Primitive* prim;
    s32 i, j;
    u16 nextChar;
    s32 nextChar2;
    s32 ptr;

    if (self->step) {
        if (is_cutscene_done && !skip_cutscene &&
            ((g_Settings.D_8003CB04 & 0x400) || g_IsTimeAttackUnlocked)) {
            if (g_pads[0].tapped & PAD_START) {
                skip_cutscene = 1;
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
        }
    }

    if (self->step && g_Dialogue.unk3C) {
        CutsceneRun();
    }

    switch (self->step) {
    case 0:
        if (g_CastleFlags[MET_MARIA_IN_DAI] ||
            g_PlayableCharacter != PLAYER_ALUCARD) {
            DestroyEntity(self);
            break;
        }
        if (SetCutsceneScript(OVL_EXPORT(cutscene_script))) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            g_CutsceneHasControl = 1;
            g_CutsceneFlags = 0;
            is_cutscene_done = 0;
            skip_cutscene = 0;
            self->step++;
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && !skip_cutscene) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.scriptCur++;
            switch (nextChar) {
            case CSOP_END_CUTSCENE:
                self->step = 7;
                return;
            case CSOP_LINE_BREAK:
                if (skip_cutscene) {
                    continue;
                }
                g_Dialogue.nextCharX = g_Dialogue.nextLineX;
                if (!(g_Dialogue.unk12 & 1)) {
                    g_Dialogue.nextLineY += 12;
                }
                g_Dialogue.nextCharY++;
                if (g_Dialogue.nextCharY > 4) {
                    g_Dialogue.nextCharY = 0;
                }
                CutsceneUnk4();
                if (!(g_Dialogue.unk12 & 1)) {
                    if (g_Dialogue.nextCharY > 3) {
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
            case CSOP_SET_SPEED:
                g_Dialogue.unk17 = *g_Dialogue.scriptCur++;
                continue;
            case CSOP_SET_WAIT:
                g_Dialogue.nextCharTimer = *g_Dialogue.scriptCur++;
                if (skip_cutscene) {
                    continue;
                }
                return;
            case CSOP_HIDE_DIALOG:
                if (skip_cutscene) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;
            case CSOP_SET_PORTRAIT:
                if (skip_cutscene) {
                    g_Dialogue.scriptCur += 2;
                    continue;
                }
                // fake reuse of i?
                i = *g_Dialogue.scriptCur++;
                nextChar2 = *g_Dialogue.scriptCur++;
                prim = g_Dialogue.prim[5];
                uCoord = D_us_80180EE0[nextChar2 & 1];
                vCoord = D_us_80180EE4[nextChar2 & 1];
                prim->clut = D_us_80180EE8[i];
                prim->tpage = 144;
                if (nextChar2 & 0x80) {
                    prim->u0 = prim->u2 = uCoord + 47;
                    prim->u1 = prim->u3 = uCoord;
                } else {
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 47;
                }
                prim->v0 = prim->v1 = vCoord;
                prim->v2 = prim->v3 = vCoord + 72;
                prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                    g_Dialogue.startX - 30;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    g_Dialogue.startY + 36;
                g_Dialogue.clutIndex = D_us_80180EF4[i];
                CutsceneUnk1();
                CutsceneUnk4();
                prim->priority = 510;
                prim->drawMode = DRAW_DEFAULT;
                DrawCutsceneActorName(i, self);
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 3;
                return;
            case CSOP_NEXT_DIALOG:
                if (skip_cutscene) {
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
            case CSOP_SET_POS:
                if (skip_cutscene) {
                    g_Dialogue.scriptCur += 2;
                    continue;
                }
                g_Dialogue.startX = *g_Dialogue.scriptCur++;
                g_Dialogue.startY = *g_Dialogue.scriptCur++;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->y0 = prim->y1 = g_Dialogue.startY;
                prim->y2 = prim->y3 = g_Dialogue.startY + 72;
                prim = prim->next;
                prim->y0 = g_Dialogue.startY - 1;
                prim->u0 = 246;
                g_Dialogue.portraitAnimTimer = 24;
                self->step = 5;
                self->step_s = 0;
                return;
            case CSOP_CLOSE_DIALOG:
                if (skip_cutscene) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 24;
                self->step = 6;
                return;
            case CSOP_PLAY_SOUND:
                if (skip_cutscene) {
                    g_Dialogue.scriptCur++;
                    g_Dialogue.scriptCur++;
                    continue;
                }
                nextChar = *g_Dialogue.scriptCur++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_WAIT_FOR_SOUND:
                if (skip_cutscene) {
                    continue;
                }
                if (g_api.func_80131F68()) {
                    continue;
                }
                *g_Dialogue.scriptCur--;
                return;
            case CSOP_SCRIPT_UNKNOWN_11:
                if (skip_cutscene) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *g_Dialogue.scriptCur--;
                return;
            case CSOP_SET_END:
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                SetCutsceneEnd((u8*)ptr);
                continue;
            case CSOP_SCRIPT_UNKNOWN_13:
                continue;
            case CSOP_SCRIPT_UNKNOWN_14:
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr += 0x100000;
                g_Dialogue.scriptCur += *(u8*)ptr << 2;

                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur;
                g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
                continue;
            case CSOP_SCRIPT_UNKNOWN_15:
                ptr = (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.scriptCur;
                g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
                continue;
            case CSOP_WAIT_FOR_FLAG:
                if (!((g_CutsceneFlags >> *g_Dialogue.scriptCur) & 1)) {
                    g_Dialogue.scriptCur--;
                    return;
                }
                g_CutsceneFlags &= ~(1 << *g_Dialogue.scriptCur);
                *g_Dialogue.scriptCur++;
                continue;
            case CSOP_SET_FLAG:
                g_CutsceneFlags |= 1 << *g_Dialogue.scriptCur++;
                continue;
            case CSOP_SCRIPT_UNKNOWN_18:
                g_Dialogue.unk3C = 0;
                continue;
            case CSOP_LOAD_PORTRAIT:
                if (skip_cutscene) {
                    g_Dialogue.scriptCur += 5;
                } else {
                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr += 0x100000;
                    nextChar2 = g_Dialogue.scriptCur++[0];
                    LoadTPage((u_long*)ptr, 1, 0, D_us_80180EF0[nextChar2], 256,
                              48, 72);
                }
                continue;
            case CSOP_SCRIPT_UNKNOWN_20:
                nextChar = *g_Dialogue.scriptCur++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_SCRIPT_UNKNOWN_21:
                g_CutsceneFlags = 0;
                skip_cutscene = 0;
                is_cutscene_done = 0;
                continue;
            case CSOP_SCRIPT_UNKNOWN_22:
                g_CutsceneFlags &= ~(1 << *g_Dialogue.scriptCur++);
                continue;
            case CSOP_SCRIPT_UNKNOWN_23:
                return;
            case CSOP_WAIT_FOR_FLAG_RESET:
                if (!((g_CutsceneFlags >> *g_Dialogue.scriptCur) & 1)) {
                    *g_Dialogue.scriptCur--;
                    return;
                }
                *g_Dialogue.scriptCur++;
                continue;
            default:
                if (skip_cutscene) {
                    continue;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break; // This breaks the big while-loop!
        }
        if (nextChar == 32) {
            g_Dialogue.nextCharX += 2;
            return;
        }
        rect.x = ((nextChar & 0xF) * 2) + 896;
        rect.y = ((nextChar & 0xF0) >> 1) + 240;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 12) + 384;
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
        break;
    case 2:
        ScaleCutsceneAvatar(2);
        if (g_Dialogue.portraitAnimTimer >= 6) {
            self->step -= 1;
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
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            is_cutscene_done = 1;
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 72);
            if (primIndex == -1) {
                DestroyEntity(self);
                break;
            }
            g_Dialogue.primIndex[0] = primIndex;
            for (prim = &g_PrimBuf[primIndex], uCoord = 0; prim != NULL;
                 prim = prim->next, uCoord++) {
                prim->r0 = prim->r1 = 127;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 247;
                prim->y0 = prim->y1 = g_Dialogue.startY + uCoord;
                prim->priority = 510;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = D_us_80180EFC[uCoord];
                prim->x3 = 3952;
            }
            self->step_s++;
            break;
        case 1:
            for (uCoord = 0, prim = &g_PrimBuf[g_Dialogue.primIndex[0]];
                 prim != NULL; prim = prim->next) {
                prim->x3 -= prim->x2;
                prim->x2 += 2;
                prim->x0 = prim->x3 / 16;
                if (prim->x0 < 5) {
                    prim->x0 = 4;
                } else {
                    uCoord = 1;
                }
            }
            if (!uCoord) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                g_Dialogue.primIndex[0] = -1;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                self->step_s++;
            }
            break;
        case 2:
            uCoord = 0;
            prim = g_Dialogue.prim[5];
            prim = prim->next;
            if (prim->r0 < 16) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 16;
                uCoord = 1;
            }
            if (prim->b0 >= 127) {
                prim->b0 = prim->b1 = 127;
            } else {
                prim->b0 = prim->b1 += 8;
                uCoord = 1;
            }

            prim = prim->next;
            if (prim->r0 < 16) {
                prim->r0 = prim->g0 = prim->b0 = 16;
            } else {
                prim->r0 = prim->g0 = prim->b0 -= 15;
                uCoord = 1;
            }
            if (!uCoord) {
                self->step = 1;
            }
        }
        break;
    case 6:
        prim = g_Dialogue.prim[5];
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
                self->step = 1;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->y2 = (prim->y3 -= 6);
            }
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 7:
        DestroyEntity(self);
        g_CastleFlags[MET_MARIA_IN_DAI] = 1;
        g_Settings.D_8003CB04 |= 0x400;
        g_CutsceneHasControl = 0;
        break;
    }
}
