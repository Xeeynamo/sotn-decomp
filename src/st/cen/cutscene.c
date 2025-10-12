// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

static u8 D_801805D8[] = {0, 64, 0, 0};
static u8 D_801805DC[] = {0, 0, 0, 0};

// clut
static u16 D_801805E0[] = {
    LAYER_CLUT_ALT | 0,
    LAYER_CLUT_ALT | 8,
    LAYER_CLUT_ALT | 16,
    LAYER_CLUT_ALT | 24,
};
static u16 D_801805E8[] = {0, 32};

static u16 D_801805EC[] = {
    0x01A1,
    0x01A1,
    0x01A1,
    0x01A1,
};

// x-coords
static s16 D_801805F4[] = {
    0x08, 0x13, 0x11, 0x31, 0x4F, 0x26, 0x36, 0x1D, 0x1B, 0x33, 0x2C, 0x21,
    0x19, 0x0A, 0x33, 0x1F, 0x48, 0x2F, 0x13, 0x19, 0x4D, 0x4B, 0x17, 0x1D,
    0x12, 0x02, 0x1B, 0x2A, 0x50, 0x45, 0x32, 0x0D, 0x2A, 0x4D, 0x06, 0x27,
    0x07, 0x48, 0x2F, 0x1B, 0x36, 0x22, 0x39, 0x14, 0x39, 0x1D, 0x0A, 0x35,
    0x10, 0x1B, 0x3D, 0x17, 0x2E, 0x0B, 0x49, 0x42, 0x3D, 0x2A, 0x01, 0x0C,
    0x1B, 0x34, 0x41, 0x35, 0x08, 0x0E, 0x4D, 0x11, 0x34, 0x41, 0x29, 0x48,
};

#if !defined(VERSION_HD)
static const char* actor_names[] = {_S("Alucard"), _S("Maria")};
static const char _pad[4] = "";
#else
// clang-format off
static u16 actor_names[] = {
    0x71, 0x99, 0x76, 0x70, 0x8084,
    0x8F, 0x98, 0x71, 0x65, 0x97, 0x70, 0x88, 0x6F, 0x8084,
    0x7C, 0x6C, 0x8C, 0x84,
    0x7B, 0x77, 0x6D, 0x808A, 0x7D};
// clang-format on
static u8 actor_prims[] = {6, 10, 4, 6};
static u8 actor_name_len[] = {5, 9, 4, 5};
#endif

static s32 g_SkipCutscene;
static Dialogue g_Dialogue;
static u32 __unused0[26];
static u32 g_CutsceneFlags;
static s32 g_IsCutsceneDone;

#include "../cutscene_unk1.h"
#include "../set_cutscene_script.h"
#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"
#include "../cutscene_actor_name.h"
#include "../set_cutscene_end.h"

#define CUTSCENE_TILEMAP_SCROLL
#include "../cutscene_run.h"

#ifndef VERSION_HD
#include "../cutscene_scale_avatar.h"
#endif

extern u8 OVL_EXPORT(cutscene_data)[];
void OVL_EXPORT(EntityCutscene)(Entity* self) {
#ifdef VERSION_US
    RECT rect;
#endif
    Primitive* prim;
    s32 primIndex;
    s32 i, j;
    s16 uCoord;
    s16 vCoord;
    u16 nextChar;
    s32 nextChar2;
    u_long ptr;

    if (self->step) {
        if (g_IsCutsceneDone && !g_SkipCutscene &&
            ((g_Settings.D_8003CB04 & 0x800) || g_IsTimeAttackUnlocked) &&
            (g_pads[0].tapped & PAD_START)) {
            g_SkipCutscene = 1;
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
        if (self->step && g_Dialogue.unk3C) {
            CutsceneRun();
        }
    }
    switch (self->step) {
    case 0:
        if (g_CastleFlags[MET_MARIA_IN_CEN] != 0) {
            DestroyEntity(self);
            return;
        }
#ifdef VERSION_HD
        if (SetCutsceneScript(OVL_EXPORT(cutscene_data)) & 0xFF) {
#else
        if (SetCutsceneScript(OVL_EXPORT(cutscene_data))) {
#endif
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            g_CutsceneHasControl = 1;
            g_CutsceneFlags = 0;
            g_IsCutsceneDone = 0;
            g_SkipCutscene = 0;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step++;
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
#ifdef VERSION_HD
            nextChar = *g_Dialogue.scriptCur++;
#endif
            if ((g_Dialogue.nextCharTimer != 0) && !g_SkipCutscene) {
                g_Dialogue.nextCharTimer--;
#ifdef VERSION_HD
                g_Dialogue.scriptCur--;
#endif
                return;
            }
#ifdef VERSION_HD
            if (!(nextChar & 0x80)) {
#else
            nextChar = *g_Dialogue.scriptCur++;
#endif
                switch (nextChar) {
                case CSOP_END_CUTSCENE:
                    self->step = 7;
                    return;
                case CSOP_LINE_BREAK:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    g_Dialogue.nextCharX = g_Dialogue.nextLineX;
                    if (!(g_Dialogue.unk12 & 1)) {
                        g_Dialogue.nextLineY += CS_LINE_SPACING;
                    }
                    g_Dialogue.nextCharY++;
#ifdef VERSION_HD
                    g_Dialogue.nextCharY &= CS_LINE_MAX;
#else
                if (g_Dialogue.nextCharY > CS_LINE_MAX) {
                    g_Dialogue.nextCharY = 0;
                }
#endif
                    CutsceneUnk4();
                    if (!(g_Dialogue.unk12 & 1)) {
                        if (g_Dialogue.nextCharY >= CS_LINE_MAX) {
                            g_Dialogue.unk12 |= 1;
                            g_Dialogue.portraitAnimTimer = 0;
                            self->step_s = 0;
                            self->step++;
#ifdef VERSION_HD
                        }
                        return;
#else
                        return;
                    }
                    continue;
#endif
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
                    if (g_SkipCutscene) {
                        continue;
                    }
                    return;
                case CSOP_HIDE_DIALOG:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    prim = g_Dialogue.prim[0];
                    for (i = 0; i <= CS_LINE_MAX; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    return;
                case CSOP_SET_PORTRAIT:
                    if (g_SkipCutscene) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    // fake reuse of i?
                    i = *g_Dialogue.scriptCur++;
                    nextChar2 = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[CS_LINE_MAX + 1];
                    uCoord = D_801805D8[nextChar2 & 1];
                    vCoord = D_801805DC[nextChar2 & 1];
                    prim->clut = D_801805E0[i];
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
                    g_Dialogue.clutIndex = D_801805EC[i];
                    CutsceneUnk1();
                    CutsceneUnk4();
                    prim->priority = 0x1FE;
                    prim->drawMode = DRAW_DEFAULT;
                    DrawCutsceneActorName((u16)i, self);
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = 3;
                    return;
                case CSOP_NEXT_DIALOG:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    for (prim = g_Dialogue.prim[0], i = 0; i <= CS_LINE_MAX;
                         i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    g_api.FreePrimitives(g_Dialogue.primIndex[1]);
                    g_Dialogue.primIndex[1] = -1;
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = 4;
                    return;
                case CSOP_SET_POS:
                    if (g_SkipCutscene) {
                        g_Dialogue.scriptCur++;
                        g_Dialogue.scriptCur++;
                        continue;
                    }
                    g_Dialogue.startX = *g_Dialogue.scriptCur++;
                    g_Dialogue.startY = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[CS_LINE_MAX + 1];
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
                case CSOP_CLOSE_DIALOG:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    g_Dialogue.portraitAnimTimer = 0x18;
                    self->step = 6;
                    return;
                case CSOP_PLAY_SOUND:
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
                case CSOP_WAIT_FOR_SOUND:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    if (g_api.func_80131F68() != false) {
                        continue;
                    }
                    *g_Dialogue.scriptCur--;
                    return;
                case CSOP_SCRIPT_UNKNOWN_11:
                    if (g_SkipCutscene) {
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
#ifdef VERSION_HD
                    g_Dialogue.scriptCur += *(u8*)(ptr + 0x100000) << 2;
#else
                g_Dialogue.scriptCur += *(u16*)ptr << 2;
#endif

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
                    if (g_SkipCutscene) {
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
                        nextChar2 = *g_Dialogue.scriptCur++;
                        LoadTPage((u_long*)ptr, 1, 0, D_801805E8[nextChar2],
                                  0x100, 48, 72);
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
                    g_SkipCutscene = 0;
                    g_IsCutsceneDone = 0;
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
#ifndef VERSION_HD
                    continue;
                default:
                    if (g_SkipCutscene) {
#endif

                        continue;
                    }
#ifdef VERSION_HD
                    continue;
                }
                if (g_SkipCutscene) {
                    *g_Dialogue.scriptCur++;
                    continue;
                } else {
                    nextChar <<= 8;
                    nextChar |= *g_Dialogue.scriptCur++;
#endif
                    g_Dialogue.nextCharTimer = g_Dialogue.unk17;
                }

                break; // This breaks the big while-loop!
            }
#ifdef VERSION_HD
            j = g_api.func_80106A28(nextChar, 1);
            if (j) {
                vCoord = (LOHU(g_Dialogue.nextCharY) * 16) + 0x180;
                LoadTPage(
                    (u_long*)j, 0, 0, g_Dialogue.nextCharX, vCoord, 0xC, 0x10);
                g_Dialogue.nextCharX += 3;
#else
    if (nextChar == 0x20) {
        g_Dialogue.nextCharX += 2;
#endif
                return;
            }
#ifndef VERSION_HD
            rect.x = ((nextChar & 0xF) * 2) + 0x380;
            rect.y = ((u32)(nextChar & 0xF0) >> 1) + 0xF0;
            rect.w = 2;
            rect.h = 8;
            vCoord = (g_Dialogue.nextCharY * 0xC) + 0x180;
            MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
            g_Dialogue.nextCharX += 2;
#endif
            break;
        case 2:
#ifdef VERSION_HD
            ptr = (g_Dialogue.nextCharY + 1) & 3;
            if (!self->step_s) {
                prim = g_Dialogue.prim[ptr];
                prim->v0 += 2;
                prim->v1 -= 2;
                if (!prim->v1) {
                    self->step_s++;
                    prim->drawMode = DRAW_HIDE;
                }
            }
            for (i = 0; i < LEN(g_Dialogue.prim) - 1; i++) {
                if (i == ptr) {
                    continue;
                }
                prim = g_Dialogue.prim[i];
                prim->y0 -= 2;
            }
            g_Dialogue.portraitAnimTimer++;
            if (g_Dialogue.portraitAnimTimer > 7) {
#else
    ScaleCutsceneAvatar(2);
    if (g_Dialogue.portraitAnimTimer > 5) {
#endif
                self->step--;
                return;
            }
            break;
        case 3:
#ifdef VERSION_HD
            vCoord = (g_Dialogue.nextCharY * 0x10) + 0x180;
#endif
            prim = g_Dialogue.prim[CS_LINE_MAX + 1];
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
            prim = g_Dialogue.prim[CS_LINE_MAX + 1];
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
                g_IsCutsceneDone = 1;
                primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x48);
                if (primIndex == -1) {
                    DestroyEntity(self);
                    return;
                }
                g_Dialogue.primIndex[0] = primIndex;
                for (prim = &g_PrimBuf[primIndex], uCoord = 0; prim != NULL;
                     prim = prim->next) {
                    prim->r0 = prim->r1 = 0x7F;
                    prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                    prim->x0 = prim->x1 = 0xF7;
                    prim->y0 = prim->y1 = g_Dialogue.startY + uCoord;
                    prim->priority = 0x1FE;
                    prim->drawMode = DRAW_DEFAULT;
                    prim->x2 = D_801805F4[uCoord];
                    prim->x3 = 0xF70;

                    uCoord++;
                }
                self->step_s++;
                return;
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
                if (uCoord == 0) {
                    g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                    g_Dialogue.primIndex[0] = -1;
                    prim = g_Dialogue.prim[CS_LINE_MAX + 1];
                    prim = prim->next;
                    prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                    prim = prim->next;
                    prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                    self->step_s++;
                    return;
                }
                break;
            case 2:
                uCoord = 0;
                prim = g_Dialogue.prim[CS_LINE_MAX + 1];
                prim = prim->next;
                if (prim->r0 < 0x10) {
                    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                } else {
                    prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 0x10;
                    uCoord = 1;
                }
                if (prim->b0 >= 0x7F) {
                    prim->b0 = prim->b1 = 0x7F;
                } else {
                    prim->b0 = prim->b1 += 8;
                    uCoord = 1;
                }

                prim = prim->next;
                if (prim->r0 < 0x10) {
                    prim->r0 = prim->g0 = prim->b0 = 0x10;
                } else {
                    prim->r0 = prim->g0 = prim->b0 -= 0xF;
                    uCoord = 1;
                }
                if (uCoord == 0) {
                    self->step = 1;
                }
            }
            break;
        case 6:
            prim = g_Dialogue.prim[CS_LINE_MAX + 1];
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
            g_CastleFlags[MET_MARIA_IN_CEN] = 1;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_GET_HOLYGLASSES, TIMEATTACK_SET_RECORD);
            g_CutsceneHasControl = 0;
            g_Settings.D_8003CB04 |= 0x800;
            break;
        }
    }
