// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

enum DialogueSteps {
    DIALOGUE_INIT = 0,
    DIALOGUE_RUN = 1,
    DIALOGUE_LOAD_PORTRAIT = 2,
    DIALOGUE_START_TEXT = 3,
    DIALOGUE_UNLOAD_PORTRAIT = 4,
    DIALOGUE_OPEN_DIALOG_BOX = 5,
    DIALOGUE_CLOSE_DIALOG_BOX = 6,
    DIALOGUE_END = 7,
};

enum DialogueSubsteps {
    DIALOG_BOX_INIT = 0,
    DIALOG_BOX_DRAW_RED = 1,
    DIALOG_BOX_DRAW_BLUE = 2,
};

#ifdef VERSION_PSP
extern u8* pre_fight_script_ptr1;  // Defined by st_init
extern u8* post_fight_script_ptr1; // Defined by st_init
extern u8* glasses_script_ptr1;    // Defined by st_init
extern u8* helphim_script_ptr1;    // Defined by st_init
extern u8* pre_fight_script_ptr2;  // Defined by st_init
extern u8* post_fight_script_ptr2; // Defined by st_init
extern u8* glasses_script_ptr2;    // Defined by st_init
extern u8* helphim_script_ptr2;    // Defined by st_init

extern u_long D_pspeu_09289698;
extern u_long D_pspeu_0928A418;
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

static u8 u_coords[] = {0, 64, 0, 0};
#ifndef VERSION_PSP
// PSP has this zeroed out in BSS
static u8 v_coords[] = {0, 0, 0, 0};
#endif

static u16 cluts[] = {
    LAYER_CLUT_ALT | 0,
    LAYER_CLUT_ALT | 8,
    LAYER_CLUT_ALT | 16,
    LAYER_CLUT_ALT | 24,
};
static u16 x_vals[] = {0, 32};
static u16 cutscene_unk_4_cluts[] = {
    PAL_UNK_1A1, PAL_UNK_1A1, PAL_UNK_1A1, PAL_UNK_1A1};

// Defines the increment of each line (by pixel, not text) of the dialogue box
// background. Results in the staggered red draw in.
static s16 red_line_increment[] = {
    8,  19, 17, 49, 79, 38, 54, 29, 27, 51, 44, 33, 25, 10, 51, 31, 72, 47,
    19, 25, 77, 75, 23, 29, 18, 2,  27, 42, 80, 69, 50, 13, 42, 77, 6,  39,
    7,  72, 47, 27, 54, 34, 57, 20, 57, 29, 10, 53, 16, 27, 61, 23, 46, 11,
    73, 66, 61, 42, 1,  12, 27, 52, 65, 53, 8,  14, 77, 17, 52, 65, 41, 72};

#if defined(VERSION_PSP)
static u8 actor_name_len_index[] = {
    NAME_IDX_ALUCARD, NAME_IDX_MARIA, NAME_IDX_SHAFT, NAME_IDX_SUCCUBUS,
    NAME_IDX_PAD,     NAME_IDX_PAD,   NAME_IDX_PAD,   NAME_IDX_PAD};
// This is passed to, but seems to be unused within DrawCutsceneActorName
static u8 actor_name_index[] = {
    NAME_IDX_ALUCARD, NAME_IDX_MARIA, NAME_IDX_SHAFT, NAME_IDX_SUCCUBUS,
    NAME_IDX_PAD,     NAME_IDX_PAD,   NAME_IDX_PAD,   NAME_IDX_PAD};
#elif !defined(VERSION_HD)
static const char* actor_names[] = {_S("Alucard"), _S("Maria")};
static const char _pad[4] = "";
#else
// clang-format off
static u16 actor_names[] = {
    // アルカード
    0x71, 0x99, 0x76, 0x70, 0x8084,
    // マリア・ラーネッド
    0x8F, 0x98, 0x71, 0x65, 0x97, 0x70, 0x88, 0x6F, 0x8084,
    // シャフト
    0x7C, 0x6C, 0x8C, 0x84,
    // サキュバス
    0x7B, 0x77, 0x6D, 0x808A, 0x7D,
};
// clang-format on
static u8 actor_prims[] = {6, 10, 4, 6};
static u8 actor_name_len[] = {5, 9, 4, 5};
#endif

#ifdef VERSION_PSP
// bss
u32 g_CutsceneFlags; // Used by e_chamber and e_maria
static s32 g_SkipCutscene;
Dialogue g_Dialogue;
static u8 char_buffer;
static u8 char_buffer_1[32];
static u8 cutsceneUnk3Unknown[0x380];
static u8* cutscene_data;
static u16 actor_names[0x100];
static u8 v_coords[8];
static s32 g_IsCutsceneDone;

#include "../../get_lang.h"

// Different order on PSX/PSP
#include "../cutscene_actor_name.h"
#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"
#define CUTSCENE_UNK1_NEXT_X 0
#define CUTSCENE_UNK1_UNK17 2
#include "../cutscene_unk1.h"
#include "../set_cutscene_script.h"
#include "../set_cutscene_events.h"
#else
static s32 g_SkipCutscene;
static Dialogue g_Dialogue;
static u32 __unused0[26];
u32 g_CutsceneFlags;
static s32 g_IsCutsceneDone;

#include "../cutscene_unk1.h"
#include "../set_cutscene_script.h"
#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"
#include "../cutscene_actor_name.h"
#include "../set_cutscene_events.h"
#endif

#define CUTSCENE_TILEMAP_SCROLL
#include "../cutscene_events.h"

#if !defined(VERSION_HD)
#include "../cutscene_scale_avatar.h"
#endif

#ifndef VERSION_PSP
extern u8 cutscene_data[];
#endif

void EntityCutscene(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i, j;
    s16 uCoord, vCoord;
    u16 nextChar;
    s32 nextChar2;
    s32 charWidth;
    u8* charBuffer1;
    u8* charBuffer2;
    u32 tempChar;
    bool endLoop;
#ifndef VERSION_HD
    RECT rect;
#endif
    u8 scriptLoaded;
    u_long ptr;

#ifdef VERSION_PSP
    DisableAutoPowerOff();
#endif

    if (self->step) {
        if (g_IsCutsceneDone && !g_SkipCutscene &&
            ((g_Settings.D_8003CB04 & 0x800) || g_GameClearFlag)) {
            if (g_pads[0].tapped & PAD_START) {
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
                self->step = DIALOGUE_RUN;
                self->step_s = DIALOG_BOX_INIT;
            }
        }
    }

    if (self->step && g_Dialogue.hasEvents) {
        RunCutsceneEvents();
    }

    switch (self->step) {
    case DIALOGUE_INIT:
#ifdef VERSION_PSP
        if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
            DestroyEntity(self);
            break;
        }
        if ((self->params != 3 && g_CastleFlags[MET_MARIA_IN_CEN]) ||
            g_DemoMode) {
            if (g_DemoMode) {
                switch (self->params) {
                case 0:
                    g_CutsceneFlags |= 8;
                    g_api.PlaySfx(0x333);
                    break;
                case 1:
                    g_CutsceneFlags |= 0x80;
                    break;
                case 2:
                    break;
                }
            }
            DestroyEntity(self);
            break;
        }
        switch (self->params) {
        case 0:
            scriptLoaded = SetCutsceneScript(pre_fight_script_ptr1);
            cutscene_data = pre_fight_script_ptr2;
            break;
        case 1:
            scriptLoaded = SetCutsceneScript(post_fight_script_ptr1);
            cutscene_data = post_fight_script_ptr2;
            break;
        case 2:
            scriptLoaded = SetCutsceneScript(glasses_script_ptr1);
            cutscene_data = glasses_script_ptr2;
            break;
        case 3:
            scriptLoaded = SetCutsceneScript(helphim_script_ptr1);
            cutscene_data = helphim_script_ptr2;
            break;
        }
#else
        if (g_CastleFlags[MET_MARIA_IN_CEN] != 0) {
            DestroyEntity(self);
            break;
        }
        scriptLoaded = SetCutsceneScript(cutscene_data);
#endif
        if (scriptLoaded) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            g_CutsceneHasControl = 1;
            g_CutsceneFlags = 0;
            g_IsCutsceneDone = 0;
            g_SkipCutscene = 0;
            self->step++;
        }
        break;
    case DIALOGUE_RUN:
        nextChar = 0;
        // this is a huge While-loop! Don't miss it!
        while (1) {
#if defined(VERSION_HD) || defined(VERSION_PSP)
            nextChar = *g_Dialogue.scriptCur++;
#endif
#ifdef VERSION_PSP
            endLoop = false;
            if (PadReadPSP() & PAD_START) {
                g_Dialogue.nextCharTimer = 0;
            }
#endif
            if (g_Dialogue.nextCharTimer && !g_SkipCutscene) {
                g_Dialogue.nextCharTimer--;
#if defined(VERSION_HD) || defined(VERSION_PSP)
                g_Dialogue.scriptCur--;
#endif
                return;
            }
#if defined(VERSION_HD) || defined(VERSION_PSP)
            if (!(nextChar & 0x80)) {
#else
            nextChar = *g_Dialogue.scriptCur++;
#endif
                switch (nextChar) {
                case CSOP_END_CUTSCENE:
                    self->step = DIALOGUE_END;
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
#if defined(VERSION_HD) || defined(VERSION_PSP)
                    g_Dialogue.nextCharY &= CS_LINE_MAX;
#else
                if (g_Dialogue.nextCharY > CS_LINE_MAX) {
                    g_Dialogue.nextCharY = 0;
                }
#endif
                    CutsceneUnk4();
                    if (!(g_Dialogue.unk12 & 1)) {
                        if (g_Dialogue.nextCharY > CS_LINE_MAX - 1) {
                            g_Dialogue.unk12 |= 1;
                            g_Dialogue.portraitAnimTimer = 0;
                            self->step_s = DIALOG_BOX_INIT;
                            self->step++;
#if !defined(VERSION_HD) && !defined(VERSION_PSP)
                            return;
#endif
                        }
#if !defined(VERSION_HD) && !defined(VERSION_PSP)
                        continue;
#endif
                    } else {
                        g_Dialogue.portraitAnimTimer = 0;
                        self->step_s = DIALOG_BOX_INIT;
                        self->step++;
                    }
                    return;
                case CSOP_SET_SPEED:
#ifdef VERSION_PSP
                    *g_Dialogue.scriptCur++;
#else
                g_Dialogue.unk17 = *g_Dialogue.scriptCur++;
#endif
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
                    for (i = 0; i < LEN(g_Dialogue.prim) - 1; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    return;
                case CSOP_SET_PORTRAIT:
                    if (g_SkipCutscene) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
#ifdef VERSION_PSP
                    i = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
                    j = *g_Dialogue.scriptCur++;
                    charWidth = j & 1;
                    uCoord = u_coords[charWidth];
                    vCoord = v_coords[charWidth];
#else
                // fake reuse of i?
                i = *g_Dialogue.scriptCur++;
                nextChar2 = *g_Dialogue.scriptCur++;
                prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
                uCoord = u_coords[nextChar2 & 1];
                vCoord = v_coords[nextChar2 & 1];
#endif
                    prim->clut = cluts[i];
                    prim->tpage = 0x90;
#ifdef VERSION_PSP
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 0x2F;
#else
                if (nextChar2 & 0x80) {
                    prim->u0 = prim->u2 = uCoord + 0x2F;
                    prim->u1 = prim->u3 = uCoord;
                } else {
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 0x2F;
                }
#endif
                    prim->v0 = prim->v1 = vCoord;
                    prim->v2 = prim->v3 = vCoord + 0x48;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                        g_Dialogue.startX - 0x1E;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        g_Dialogue.startY + 0x24;
                    g_Dialogue.clutIndex = cutscene_unk_4_cluts[i];
                    CutsceneUnk1();
                    CutsceneUnk4();
                    prim->priority = 0x1FE;
                    prim->drawMode = DRAW_DEFAULT;
#ifdef VERSION_PSP
                    DrawCutsceneActorName(
                        i, self, actor_names, actor_name_len_index,
                        actor_name_index, 4);
#else
                DrawCutsceneActorName((u16)i, self);
#endif
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = DIALOGUE_START_TEXT;
                    return;
                case CSOP_NEXT_DIALOG:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    prim = g_Dialogue.prim[0];
                    for (i = 0; i < LEN(g_Dialogue.prim) - 1; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    g_api.FreePrimitives(g_Dialogue.primIndex[1]);
                    g_Dialogue.primIndex[1] = -1;
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = DIALOGUE_UNLOAD_PORTRAIT;
                    return;
                case CSOP_SET_POS:
                    if (g_SkipCutscene) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    g_Dialogue.startX = *g_Dialogue.scriptCur++;
                    g_Dialogue.startY = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
                    prim = prim->next;
                    prim->y0 = prim->y1 = g_Dialogue.startY;
                    prim->y2 = prim->y3 = g_Dialogue.startY + 0x48;
                    prim = prim->next;
                    prim->y0 = g_Dialogue.startY - 1;
                    prim->u0 = 0xF6;
                    g_Dialogue.portraitAnimTimer = 0x18;
                    self->step = DIALOGUE_OPEN_DIALOG_BOX;
                    self->step_s = DIALOG_BOX_INIT;
                    return;
                case CSOP_CLOSE_DIALOG:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    g_Dialogue.portraitAnimTimer = 0x18;
                    self->step = DIALOGUE_CLOSE_DIALOG_BOX;
                    return;
                case CSOP_PLAY_SOUND:
                    if (g_SkipCutscene) {
                        g_Dialogue.scriptCur += 2;
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
                case CSOP_SET_EVENTS:
                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
#ifdef VERSION_PSP
                    ptr += (u_long)cutscene_data;
#endif
                    SetCutsceneEvents((u8*)ptr);
                    continue;
                case CSOP_SCRIPT_UNKNOWN_13:
                    continue;
                case CSOP_SCRIPT_SWITCH:
                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
#if defined(VERSION_PSP)
                    ptr += (u_long)cutscene_data;
                    g_Dialogue.scriptCur += *(u8*)ptr << 2;
#elif defined(VERSION_HD)
                g_Dialogue.scriptCur += *(u8*)(ptr + 0x100000) * 4;
#else
                g_Dialogue.scriptCur += *(u16*)ptr * 4;
#endif

                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur;
#ifdef VERSION_PSP
                    ptr += (u_long)cutscene_data;
#endif
                    g_Dialogue.scriptCur = CS_PTR(ptr);
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
                    ptr += (u_long)cutscene_data;
#endif
                    g_Dialogue.scriptCur = CS_PTR(ptr);
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
                case CSOP_STOP_EVENTS:
                    g_Dialogue.hasEvents = 0;
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
#ifdef VERSION_PSP
                        switch (ptr) {
                        case 0:
                            ptr = (u_long)&D_pspeu_09289698;
                            break;
                        case 1:
                            ptr = (u_long)&D_pspeu_0928A418;
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
                        j = *g_Dialogue.scriptCur++;
                        LoadTPage((u_long*)ptr, 1, 0, x_vals[j], 0x100, 48, 72);
#else
                    ptr = (u_long)CS_PTR(ptr);
                    nextChar2 = *g_Dialogue.scriptCur++;
                    LoadTPage(
                        (u_long*)ptr, 1, 0, x_vals[nextChar2], 0x100, 48, 72);
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
#ifdef VERSION_PSP
                    continue;
                default:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    g_Dialogue.nextCharTimer = g_Dialogue.unk17;
                    endLoop = true;
                } // This closes the CSOP switch for psp
                if (endLoop) {
                    break; // This breaks the big while loop for psp
                }
                continue;
            } else {
                if (g_SkipCutscene) {
                    g_Dialogue.scriptCur++;
                    continue;
                }
                if (0xA7 <= nextChar && nextChar < 0xAD) {
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
        } // This closes the big while loop for psp

        charBuffer1 = char_buffer_1;
        rect.x = ((nextChar & 0xF) * 2) + 0x380;
        rect.y = ((nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 12) + 0x180;
        StoreImage(&rect, (u_long*)charBuffer1);
        for (i = 0; i < 32; i++) {
            // swaps the upper and lower 4 bits of each member
            charBuffer1[i] =
                ((charBuffer1[i] & 0x0F) << 4) | ((charBuffer1[i] & 0xF0) >> 4);
        }
        while (true) {
            if (nextChar == 0x20) {
                break;
            }
            for (i = 0; i < 8; i++) {
                if (charBuffer1[(i << 3) / 2] & 0xF0) {
                    break;
                }
            }
            if (i != 8) {
                break;
            }
            for (i = 0; i < 8; i++) {
                // lots of byte shuffling here
                charBuffer2 = &charBuffer1[(i << 3) / 2];
                tempChar = (charBuffer2[0] << 24);
                tempChar |= (charBuffer2[1] << 16);
                tempChar |= (charBuffer2[2] << 8);
                tempChar |= (charBuffer2[3]);
                tempChar <<= 4;
                charBuffer2[0] = (tempChar >> 24) & 0xFF;
                charBuffer2[1] = (tempChar >> 16) & 0xFF;
                charBuffer2[2] = (tempChar >> 8) & 0xFF;
                charBuffer2[3] = (tempChar) & 0xFF;
            }
        }
        for (i = 0, charWidth = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if ((charBuffer1[j / 2 + (i * 8) / 2]) &
                    (0xF0 >> ((j & 1) * 4))) {
                    if (j > charWidth) {
                        charWidth = j;
                    }
                };
            }
        }
        charWidth += 2;
        for (i = 0; i < 32; i++) {
            // swaps the upper and lower 4 bits of each member
            charBuffer1[i] =
                ((charBuffer1[i] & 0x0F) << 4) | ((charBuffer1[i] & 0xF0) >> 4);
        }
        rect.w = charWidth;
        charBuffer1 = char_buffer_1;
        for (i = 0; i < 8; i++) {
            // lots of byte shuffling here
            charBuffer2 =
                &cutsceneUnk3Unknown
                    [((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) +
                     (i * 112)];
            if ((g_Dialogue.nextCharX - g_Dialogue.nextLineX) & 1) {
                charBuffer2[0] =
                    (charBuffer2[0] & 0xF0) | ((charBuffer1[0] & 0x0F) << 4);
                charBuffer2[1] = ((charBuffer1[0] & 0xF0) >> 4) |
                                 ((charBuffer1[1] & 0x0F) << 4);
                charBuffer2[2] = ((charBuffer1[1] & 0xF0) >> 4) |
                                 ((charBuffer1[2] & 0x0F) << 4);
                charBuffer2[3] = ((charBuffer1[2] & 0xF0) >> 4) |
                                 ((charBuffer1[3] & 0x0F) << 4);
                charBuffer2[4] = ((charBuffer1[3] & 0xF0) >> 4);
                charBuffer1 += 4;
            } else {
                charBuffer2[0] = charBuffer1[0];
                charBuffer2[1] = charBuffer1[1];
                charBuffer2[2] = charBuffer1[2];
                charBuffer2[3] = charBuffer1[3];
                charBuffer1 += 4;
            }
        }
        LoadTPage((u_long*)cutsceneUnk3Unknown, 0, 0, g_Dialogue.nextLineX,
                  vCoord, 224, 8);
        if (nextChar != 0x20) {
            g_Dialogue.nextCharX += rect.w;
        } else {
            g_Dialogue.nextCharX += 4;
        }
        // This seems like a mistake.
        if (((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) < 112) {
        };
        char_buffer = nextChar;
        break;
#else
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
#endif
    case DIALOGUE_LOAD_PORTRAIT:
#if defined(VERSION_HD) || defined(VERSION_PSP)
        ptr = (g_Dialogue.nextCharY + 1) & CS_LINE_MAX;
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
        if (g_Dialogue.portraitAnimTimer >= 8) {
#else
        ScaleCutsceneAvatar(2);
        if (g_Dialogue.portraitAnimTimer > 5) {
#endif
            self->step--;
        }
        break;
    case DIALOGUE_START_TEXT:
#ifdef VERSION_HD
        vCoord = (g_Dialogue.nextCharY * 0x10) + 0x180;
#endif
        prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
        prim->x0 = prim->x2 -= 4;
        prim->x1 = prim->x3 += 4;
        prim->y0 = prim->y1 -= 6;
        prim->y2 = prim->y3 += 6;
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = DIALOGUE_RUN;
            for (prim = &g_PrimBuf[g_Dialogue.primIndex[1]]; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_DEFAULT;
            }
        }
        break;
    case DIALOGUE_UNLOAD_PORTRAIT:
        prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
        prim->x0 = prim->x2 += 4;
        prim->x1 = prim->x3 -= 4;
        prim->y0 = prim->y1 += 6;
        prim->y2 = prim->y3 -= 6;
        if (prim->x1 >= (g_Dialogue.startX - 2)) {
            prim->x1 = prim->x3 = g_Dialogue.startX - 3;
        }
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = DIALOGUE_RUN;
            return;
        }
        break;
    case DIALOGUE_OPEN_DIALOG_BOX:
        switch (self->step_s) {
        case DIALOG_BOX_INIT:
            // Initializes the dialogue box background by horizontal pixel line
            // Set to red for the initial draw in
            // uCoord is used as a horizontal line offset here
            g_IsCutsceneDone = true;
            primIndex =
                g_api.AllocPrimitives(PRIM_LINE_G2, LEN(red_line_increment));
            if (primIndex == -1) {
                DestroyEntity(self);
                break;
            }
            g_Dialogue.primIndex[0] = primIndex;
            for (prim = &g_PrimBuf[primIndex], uCoord = 0; prim != NULL;
                 prim = prim->next) {
                prim->r0 = prim->r1 = 127;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                // Left (x0) and right (x1) edge of the dialogue box
                prim->x0 = prim->x1 = 247;
                prim->y0 = prim->y1 = g_Dialogue.startY + uCoord;
                prim->priority = 510;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = red_line_increment[uCoord];
                // Initialized as the right side of the dialogue box (247) * 16
                prim->x3 = 3952;
                uCoord++;
            }
            self->step_s++;
            break;
        case DIALOG_BOX_DRAW_RED:
            // prim->x0 and prim->x3 are the left side (end point) of the red
            // lines by pixel and subpixel respectively
            // prim->x2 is the interval value in subpixel for drawing each red
            // line across the screen from right to left
            // uCoord is used here as a flag to indicate line completion
            uCoord = false;
            for (prim = &g_PrimBuf[g_Dialogue.primIndex[0]]; prim != NULL;
                 prim = prim->next) {
                prim->x3 -= prim->x2;
                prim->x2 += 2;
                prim->x0 = prim->x3 / 16;
                if (prim->x0 < 5) {
                    prim->x0 = 4;
                } else {
                    uCoord = true;
                }
            }
            if (!uCoord) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                g_Dialogue.primIndex[0] = -1;
                prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
                prim = prim->next;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                self->step_s++;
            }
            break;
        case DIALOG_BOX_DRAW_BLUE:
            uCoord = false;
            prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
            prim = prim->next;
            if (prim->r0 < 16) {
                PRED(prim) = 0;
            } else {
                PRED(prim) -= 16;
                uCoord = true;
            }
            if (prim->b0 >= 127) {
                prim->b0 = prim->b1 = 127;
            } else {
                prim->b0 = prim->b1 += 8;
                uCoord = true;
            }

            prim = prim->next;
            if (prim->r0 < 16) {
                PGREY(prim, 0) = 16;
            } else {
                PGREY(prim, 0) -= 15;
                uCoord = true;
            }
            if (!uCoord) {
                self->step = DIALOGUE_RUN;
            }
        }
        break;
    case DIALOGUE_CLOSE_DIALOG_BOX:
        prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
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
                self->step = DIALOGUE_RUN;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->y2 = (prim->y3 -= 6);
            }
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            return;
        }
        break;

    case DIALOGUE_END:
#ifdef VERSION_PSP
        switch (self->params) {
        case 0:
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_GET_HOLYGLASSES, TIMEATTACK_SET_RECORD);
            g_Settings.D_8003CB04 |= 0x800;
            break;
        case 1:
            break;
        case 2:
            g_CastleFlags[MET_MARIA_IN_CEN] = 1;
            break;
        case 3:
            break;
        }
        DestroyEntity(self);
        g_CutsceneHasControl = 0;
#else
        DestroyEntity(self);
        g_CastleFlags[MET_MARIA_IN_CEN] = 1;
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_GET_HOLYGLASSES, TIMEATTACK_SET_RECORD);
        g_CutsceneHasControl = 0;
        g_Settings.D_8003CB04 |= 0x800;
#endif
        break;
    }
}
