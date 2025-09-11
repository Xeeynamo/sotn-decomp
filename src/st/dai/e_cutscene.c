// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"
#include <cutscene.h>

#ifdef VERSION_PSP
extern u8* OVL_EXPORT(cutscene_script); // Defined by st_init
#else
extern u8 OVL_EXPORT(cutscene_script)[];
#endif
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[]; // Defined by e_init
#ifdef VERSION_PSP
extern u_long D_pspeu_092970B8; // Defined by st_init
extern u_long D_pspeu_0926E270;
extern u_long D_pspeu_0926EFF0;
extern u_long D_893EA8C;
extern u_long D_893F80C;
extern u_long D_894058C;
extern u_long D_894130C;
extern u_long D_894208C;
extern u_long D_8942E0C;
extern u_long D_8943B8C;
extern u_long D_894490C;
extern u_long D_894568C;

// clang-format off
static u16 actor_names_en[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('L'), CH('i'), CH('b'), CH('r'), CH('a'), CH('r'), CH('i'), CH('a'), CH('n'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), CH('u'), CH('c'), CH('c'), CH('u'), CH('b'), CH('u'), CH('s'),
    CH('F'), CH('e'), CH('r'), CH('r'), CH('y'), CH('m'), CH('a'), CH('n'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_en[] = {7, 7, 5, 7, 5, 9, 4, 8, 8, 5};

static u16 actor_names_sp[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('B'), CH('i'), CH('b'), CH('l'), CH('i'), CH('o'), CH('t'), CH('e'), CH('c'), CH('a'), CH('r'), CH('i'), CH('o'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), 0xAC, CH('c'), CH('u'), CH('b'), CH('o'),
    CH('B'), CH('a'), CH('r'), CH('q'), CH('u'), CH('e'), CH('r'), CH('o'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_sp[] = {7, 7, 5, 7, 5, 13, 4, 6, 8, 5};

static u16 actor_names_it[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('B'), CH('i'), CH('b'), CH('l'), CH('i'), CH('o'), CH('t'), CH('e'), CH('c'), CH('a'), CH('r'), CH('i'), CH('o'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), CH('u'), CH('c'), CH('c'), CH('u'), CH('b'), CH('u'), CH('s'),
    CH('T'), CH('r'), CH('a'), CH('g'), CH('h'), CH('e'), CH('t'), CH('t'), CH('a'), CH('t'), CH('o'), CH('r'), CH('e'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_it[] = {7, 7, 5, 7, 5, 13, 4, 8, 13, 5};

static u16 actor_names_fr[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('B'), CH('i'), CH('b'), CH('l'), CH('i'), CH('o'), CH('t'), CH('h'), 0xA0, CH('c'), CH('a'), CH('i'), CH('r'), CH('e'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), CH('u'), CH('c'), CH('c'), CH('u'), CH('b'), CH('e'),
    CH('P'), CH('a'), CH('s'), CH('s'), CH('e'), CH('u'), CH('r'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_fr[] = {7, 7, 5, 7, 5, 14, 4, 7, 7, 5};

static u16 actor_names_ge[] = {
    CH('R'), CH('i'), CH('c'), CH('h'), CH('t'), CH('e'), CH('r'),
    CH('D'), CH('r'), CH('a'), CH('c'), CH('u'), CH('l'), CH('a'),
    CH('D'), CH('e'), CH('a'), CH('t'), CH('h'),
    CH('A'), CH('l'), CH('u'), CH('c'), CH('a'), CH('r'), CH('d'),
    CH('M'), CH('a'), CH('r'), CH('i'), CH('a'),
    CH('B'), CH('i'), CH('b'), CH('l'), CH('i'), CH('o'), CH('t'), CH('h'), CH('e'), CH('k'), CH('a'), CH('r'),
    CH('L'), CH('i'), CH('s'), CH('a'),
    CH('S'), CH('u'), CH('k'), CH('k'), CH('u'), CH('b'), CH('u'), CH('s'),
    CH('F'), 0x9D, CH('h'), CH('r'), CH('m'), CH('a'), CH('n'), CH('n'),
    CH('S'), CH('h'), CH('a'), CH('f'), CH('t')};
static u8 actor_name_len_ge[] = {7, 7, 5, 7, 5, 12, 4, 8, 8, 5};
// clang-format on
#endif
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

#ifdef VERSION_PSP
static u8 D_pspeu_092967C8[] = {3, 4, 9, 7, 0, 0, 0, 0};
static u8 D_pspeu_092967D0[] = {3, 4, 9, 7, 0, 0, 0, 0};

// bss
u32 g_CutsceneFlags; // Used by cutscene_init
static s32 skip_cutscene;
Dialogue g_Dialogue; // Used by cutscene_init
static u8 D_pspeu_09297838;
static u8 D_pspeu_09297818[32];
static u8 cutsceneUnk3Unknown[896];
static u16 D_pspeu_09297298[256];
static u8 D_pspeu_09297290[8];
static s32 is_cutscene_done;

// psp only, can probably be added to cutscene_actor_name.h
#include "../../get_lang.h"

// These three are reversed in order from psx
#include "../cutscene_actor_name.h"
#include "../cutscene_script_box.h"
#include "../cutscene_script_text.h"
#else
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
#endif

#ifdef VERSION_PSP
// pspeu needs this to not be static
void SetCutsceneEnd(u8* ptr) {
    g_Dialogue.scriptEnd = ptr;
#else
static void SetCutsceneEnd(u8* ptr) {
    g_Dialogue.scriptEnd = ptr + 0x100000;
#endif
    g_Dialogue.timer = 0;
    g_Dialogue.unk3C = 1;
}

#define CUTSCENE_TILEMAP_SCROLL
#include "../cutscene_run.h"

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
#ifdef VERSION_PSP
    s32 sp40;
#endif
    RECT rect;
    Primitive* prim;
    s32 i, j;
    u16 nextChar;
    s32 nextChar2;
#ifdef VERSION_PSP
    u8* var_s6;
#endif
    s32 ptr;
#ifdef VERSION_PSP
    u32 var_s3;
    u8* var_s1;

    func_8926498();
#endif

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
#ifdef VERSION_PSP
        nextChar = 0;
#endif
        // this is a huge While-loop! Don't miss it!
        while (1) {
#ifdef VERSION_PSP
            nextChar = *g_Dialogue.scriptCur++;
            sp40 = 0;
            if (func_8919BA8() & 8) {
                g_Dialogue.nextCharTimer = 0;
            }
#endif
            if ((g_Dialogue.nextCharTimer) && !skip_cutscene) {
                g_Dialogue.nextCharTimer--;
#ifdef VERSION_PSP
                g_Dialogue.scriptCur--;
#endif
                return;
            }
#ifdef VERSION_PSP
            if (!(nextChar & 0x80)) {
#else
            nextChar = *g_Dialogue.scriptCur++;
#endif
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
#ifdef VERSION_PSP
                        g_Dialogue.nextLineY += 16;
#else
                    g_Dialogue.nextLineY += 12;
#endif
                    }
                    g_Dialogue.nextCharY++;
#ifdef VERSION_PSP
                    g_Dialogue.nextCharY &= 3;
#else
                if (g_Dialogue.nextCharY > 4) {
                    g_Dialogue.nextCharY = 0;
                }
#endif
                    CutsceneUnk4();
                    if (!(g_Dialogue.unk12 & 1)) {
#ifdef VERSION_PSP
                        if (g_Dialogue.nextCharY > 2) {
#else
                    if (g_Dialogue.nextCharY > 3) {
#endif
                            g_Dialogue.unk12 |= 1;
                            g_Dialogue.portraitAnimTimer = 0;
                            self->step_s = 0;
                            self->step++;
#ifdef VERSION_PSP
                        }
                    } else {
                        g_Dialogue.portraitAnimTimer = 0;
                        self->step_s = 0;
                        self->step++;
                    }
#else
                        return;
                    }
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0;
                self->step_s = 0;
                self->step++;
#endif
                    return;
                case CSOP_SET_SPEED:
#ifdef VERSION_PSP
                    g_Dialogue.scriptCur++;
#else
                g_Dialogue.unk17 = *g_Dialogue.scriptCur++;
#endif
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
#ifdef VERSION_PSP
                    for (i = 0; i < 4; i++) {
#else
                for (i = 0; i < 5; i++) {
#endif
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
#ifdef VERSION_PSP
                    prim = g_Dialogue.prim[4];
                    j = *g_Dialogue.scriptCur++;
                    nextChar2 = j & 1;
                    uCoord = D_us_80180EE0[nextChar2];
                    vCoord = D_pspeu_09297290[nextChar2];
#else
                nextChar2 = *g_Dialogue.scriptCur++;
                prim = g_Dialogue.prim[5];
                uCoord = D_us_80180EE0[nextChar2 & 1];
                vCoord = D_us_80180EE4[nextChar2 & 1];
#endif
                    prim->clut = D_us_80180EE8[i];
                    prim->tpage = 144;
#ifndef VERSION_PSP
                    if (nextChar2 & 0x80) {
                        prim->u0 = prim->u2 = uCoord + 47;
                        prim->u1 = prim->u3 = uCoord;
                    } else {
#endif
                        prim->u0 = prim->u2 = uCoord;
                        prim->u1 = prim->u3 = uCoord + 47;
#ifndef VERSION_PSP
                    }
#endif
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
#ifdef VERSION_PSP
                    DrawCutsceneActorName(
                        i, self, D_pspeu_09297298, D_pspeu_092967C8,
                        D_pspeu_092967D0, 4);
#else
                DrawCutsceneActorName(i, self);
#endif
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = 3;
                    return;
                case CSOP_NEXT_DIALOG:
                    if (skip_cutscene) {
                        continue;
                    }
#ifdef VERSION_PSP
                    for (prim = g_Dialogue.prim[0], i = 0; i < 4; i++) {
#else
                for (prim = g_Dialogue.prim[0], i = 0; i < 5; i++) {
#endif
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
#ifdef VERSION_PSP
                    prim = g_Dialogue.prim[4];
#else
                prim = g_Dialogue.prim[5];
#endif
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
#ifdef VERSION_PSP
                        g_Dialogue.scriptCur += 2;
#else
                    g_Dialogue.scriptCur++;
                    g_Dialogue.scriptCur++;
#endif
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
#ifdef VERSION_PSP
                    ptr += (u_long)D_pspeu_092970B8;
#endif
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
#ifdef VERSION_PSP
                    ptr += (u_long)D_pspeu_092970B8;
#else
                ptr += 0x100000;
#endif
                    g_Dialogue.scriptCur += *(u8*)ptr << 2;

                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur;
#ifdef VERSION_PSP
                    ptr += (u_long)D_pspeu_092970B8;
                    g_Dialogue.scriptCur = (u8*)ptr;
#else
                g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
#endif
                    continue;
                case CSOP_SCRIPT_UNKNOWN_15:
                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur;
#ifdef VERSION_PSP
                    ptr += (u_long)D_pspeu_092970B8;
                    g_Dialogue.scriptCur = (u8*)ptr;
#else
                g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
#endif
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
#ifdef VERSION_PSP
                        switch (ptr) {
                        case 0:
                            ptr = (u_long)&D_pspeu_0926E270;
                            break;
                        case 1:
                            ptr = (u_long)&D_pspeu_0926EFF0;
                            break;
                        case 2:
                            ptr = (u_long)&D_893EA8C;
                            break;
                        case 3:
                            ptr = (u_long)&D_893F80C;
                            break;
                        case 4:
                            ptr = (u_long)&D_894058C;
                            break;
                        case 5:
                            ptr = (u_long)&D_894130C;
                            break;
                        case 6:
                            ptr = (u_long)&D_894208C;
                            break;
                        case 7:
                            ptr = (u_long)&D_8942E0C;
                            break;
                        case 8:
                            ptr = (u_long)&D_8943B8C;
                            break;
                        case 9:
                            ptr = (u_long)&D_894490C;
                            break;
                        case 10:
                            ptr = (u_long)&D_894568C;
                            break;
                        }
                        j = g_Dialogue.scriptCur++[0];
                        LoadTPage(
                            (u_long*)ptr, 1, 0, D_us_80180EF0[j], 256, 48, 72);
#else
                    ptr += 0x100000;
                    nextChar2 = g_Dialogue.scriptCur++[0];
                    LoadTPage((u_long*)ptr, 1, 0, D_us_80180EF0[nextChar2], 256,
                              48, 72);
#endif
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
#ifdef VERSION_PSP
                    sp40 = 1;
                } // Close the switch
                if (sp40) {
                    break; // This breaks the big while-loop!
                }
                continue;
            } else {
                if (skip_cutscene) {
                    g_Dialogue.scriptCur++;
                    continue;
                }
                if (167 <= nextChar && nextChar < 173) {
                    nextChar = nextChar + 39;
                } else if (nextChar == 166) {
                    nextChar = 204;
                } else if (nextChar == 221) {
                    nextChar = 205;
                } else {
                    nextChar = nextChar - 17;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break;
        } // Close the giant while loop

        var_s6 = D_pspeu_09297818;
#else
            }
            break; // This breaks the big while-loop!
        }
        if (nextChar == 32) {
            g_Dialogue.nextCharX += 2;
            return;
        }
#endif
        rect.x = ((nextChar & 0xF) * 2) + 896;
        rect.y = ((nextChar & 0xF0) >> 1) + 240;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 12) + 384;
#ifdef VERSION_PSP
        StoreImage(&rect, (u_long*)var_s6);
        for (i = 0; i < 32; i++) {
            // swaps the upper and lower 4 bits of each member
            var_s6[i] = ((var_s6[i] & 0x0F) << 4) | ((var_s6[i] & 0xF0) >> 4);
        }
        while (true) {
            if (nextChar == 32) {
                break;
            }
            for (i = 0; i < 8; i++) {
                if (var_s6[(i << 3) / 2] & 0xF0) {
                    break;
                }
            }
            if (i != 8) {
                break;
            }
            for (i = 0; i < 8; i++) {
                // lots of byte shuffling here
                var_s1 = &var_s6[(i << 3) / 2];
                var_s3 = (var_s1[0] << 24);
                var_s3 |= (var_s1[1] << 16);
                var_s3 |= (var_s1[2] << 8);
                var_s3 |= (var_s1[3]);
                var_s3 <<= 4;
                var_s1[0] = (var_s3 >> 24) & 0xFF;
                var_s1[1] = (var_s3 >> 16) & 0xFF;
                var_s1[2] = (var_s3 >> 8) & 0xFF;
                var_s1[3] = (var_s3) & 0xFF;
            }
        }
        for (i = 0, nextChar2 = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if ((var_s6[j / 2 + (i << 3) / 2]) & (0xF0 >> ((j & 1) * 4))) {
                    if (j > nextChar2) {
                        nextChar2 = j;
                    }
                };
            }
        }
        nextChar2 += 2;
        for (i = 0; i < 32; i++) {
            // swaps the upper and lower 4 bits of each member
            var_s6[i] = ((var_s6[i] & 0x0F) << 4) | ((var_s6[i] & 0xF0) >> 4);
        }
        rect.w = nextChar2;
        var_s6 = D_pspeu_09297818;
        for (i = 0; i < 8; i++) {
            // lots of byte shuffling here
            var_s1 = &cutsceneUnk3Unknown
                         [((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) +
                          (i * 112)];
            if ((g_Dialogue.nextCharX - g_Dialogue.nextLineX) & 1) {
                var_s1[0] = (var_s1[0] & 0xF0) | ((var_s6[0] & 0x0F) << 4);
                var_s1[1] =
                    ((var_s6[0] & 0xF0) >> 4) | ((var_s6[1] & 0x0F) << 4);
                var_s1[2] =
                    ((var_s6[1] & 0xF0) >> 4) | ((var_s6[2] & 0x0F) << 4);
                var_s1[3] =
                    ((var_s6[2] & 0xF0) >> 4) | ((var_s6[3] & 0x0F) << 4);
                var_s1[4] = ((var_s6[3] & 0xF0) >> 4);
                var_s6 += 4;
            } else {
                var_s1[0] = var_s6[0];
                var_s1[1] = var_s6[1];
                var_s1[2] = var_s6[2];
                var_s1[3] = var_s6[3];
                var_s6 += 4;
            }
        }
        LoadTPage((u_long*)cutsceneUnk3Unknown, 0, 0, g_Dialogue.nextLineX,
                  vCoord, 224, 8);
        if (nextChar != 32) {
            g_Dialogue.nextCharX += rect.w;
        } else {
            g_Dialogue.nextCharX += 4;
        }
        // This seems like a mistake.
        if (((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) < 112) {
        };
        D_pspeu_09297838 = nextChar;
#else
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
#endif
        break;
    case 2:
#ifdef VERSION_PSP
        ptr = g_Dialogue.nextCharY;
        ptr = (ptr + 1) & 3;
        if (!self->step_s) {
            prim = g_Dialogue.prim[ptr];
            prim->v0 += 2;
            prim->v1 -= 2;
            if (!prim->v1) {
                self->step_s++;
                prim->drawMode = DRAW_HIDE;
            }
        }
        // probably 17cc
        // 1844
        for (i = 0; i < 4; i++) {
            if (i == ptr) {
                continue;
            }
            prim = g_Dialogue.prim[i];
            prim->y0 -= 2;
        }
        g_Dialogue.portraitAnimTimer++;
        if (g_Dialogue.portraitAnimTimer >= 8) {
#else
        ScaleCutsceneAvatar(2);
        if (g_Dialogue.portraitAnimTimer >= 6) {
#endif
            self->step -= 1;
        }
        break;
    case 3:
#ifdef VERSION_PSP
        prim = g_Dialogue.prim[4];
#else
        prim = g_Dialogue.prim[5];
#endif
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
#ifdef VERSION_PSP
        prim = g_Dialogue.prim[4];
#else
        prim = g_Dialogue.prim[5];
#endif
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
                 prim = prim->next) {
                prim->r0 = prim->r1 = 127;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 247;
                prim->y0 = prim->y1 = g_Dialogue.startY + uCoord;
                prim->priority = 510;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = D_us_80180EFC[uCoord];
                prim->x3 = 3952;
                uCoord++;
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
#ifdef VERSION_PSP
                prim = g_Dialogue.prim[4];
#else
                prim = g_Dialogue.prim[5];
#endif
                prim = prim->next;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                self->step_s++;
            }
            break;
        case 2:
            uCoord = 0;
#ifdef VERSION_PSP
            prim = g_Dialogue.prim[4];
#else
            prim = g_Dialogue.prim[5];
#endif
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
#ifdef VERSION_PSP
        prim = g_Dialogue.prim[4];
#else
        prim = g_Dialogue.prim[5];
#endif
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
