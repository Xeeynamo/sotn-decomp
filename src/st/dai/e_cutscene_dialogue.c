// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"
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

#define DAI_CUTSCENE_ALUCARD_READY 1

// e_cutscene/cutscene_script_box
#define CUTSCENE_UNK3_RECT_X 0
#define CUTSCENE_UNK4_TPAGE 16

// e_cutscene/cutscene_script_text
#ifdef VERSION_PSP
#define CUTSCENE_UNK1_NEXT_X 0
#define CUTSCENE_UNK1_UNK17 2
#else
#define CUTSCENE_UNK1_NEXT_X 2
#define CUTSCENE_UNK1_UNK17 8
#endif

// e_cutscene/set_cutscene_script
#ifdef VERSION_PC
#define NUM_CUTSCENE_PRIM 8
#else
#define NUM_CUTSCENE_PRIM 7
#endif

#define CUTSCENE_TILEMAP_SCROLL

#ifdef VERSION_PSP
extern u8* OVL_EXPORT(cutscene_script); // Defined by st_init
#else
extern u8 OVL_EXPORT(cutscene_script)[];
#endif

extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[]; // Defined by e_init

#ifdef VERSION_PSP
extern u_long OVL_EXPORT(cutscene_script_ptr); // Defined by st_init
extern u_long gfx_portrait_alucard;
extern u_long gfx_portrait_maria;
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
static u8 u_coords[] = {0, 64, 0, 0};
#ifndef VERSION_PSP
static u8 v_coords[] = {0, 0, 0, 0};
#endif

// These cluts are based on the actor name indexing
static u16 cluts[] = {PAL_PORTRAIT_ALUCARD, PAL_PORTRAIT_MARIA,
                      PAL_PORTRAIT_SHAFT, PAL_PORTRAIT_SUCCUBUS};
static u16 x_vals[] = {0, 32};
static u16 cutscene_unk_4_cluts[] = {
    PAL_CUTSCENE_UNK_4_CLUT, PAL_CUTSCENE_UNK_4_CLUT, PAL_CUTSCENE_UNK_4_CLUT,
    PAL_CUTSCENE_UNK_4_CLUT};
// Defines the increment of each line (by pixel, not text) of the dialogue box
// background. Results in the staggered red draw in.
static s16 red_line_increment[] = {
    8,  19, 17, 49, 79, 38, 54, 29, 27, 51, 44, 33, 25, 10, 51, 31, 72, 47,
    19, 25, 77, 75, 23, 29, 18, 2,  27, 42, 80, 69, 50, 13, 42, 77, 6,  39,
    7,  72, 47, 27, 54, 34, 57, 20, 57, 29, 10, 53, 16, 27, 61, 23, 46, 11,
    73, 66, 61, 42, 1,  12, 27, 52, 65, 53, 8,  14, 77, 17, 52, 65, 41, 72};

#ifdef VERSION_PSP
static u8 actor_name_len_index[] = {
    NAME_IDX_ALUCARD, NAME_IDX_MARIA, NAME_IDX_SHAFT, NAME_IDX_SUCCUBUS,
    NAME_IDX_PAD,     NAME_IDX_PAD,   NAME_IDX_PAD,   NAME_IDX_PAD};
// This is passed to, but seems to be unused within DrawCutsceneActorName
static u8 actor_name_index[] = {
    NAME_IDX_ALUCARD, NAME_IDX_MARIA, NAME_IDX_SHAFT, NAME_IDX_SUCCUBUS,
    NAME_IDX_PAD,     NAME_IDX_PAD,   NAME_IDX_PAD,   NAME_IDX_PAD};

// bss
u32 g_CutsceneFlags; // Used by e_cutscene_actors
static bool skip_cutscene;
Dialogue g_Dialogue; // Used by e_cutscene_actors
static u8 char_buffer;
static u8 char_buffer_1[32];
static u8 cutsceneUnk3Unknown[896];
static u16 actor_names[256];
static u8 v_coords[8];
static bool dialogue_started;

// psp only, can probably be added to cutscene_actor_name.h
#include "../../get_lang.h"

// These three are reversed in order from psx
#include "../cutscene_actor_name.h"
#include "../cutscene_script_box.h"
#include "../cutscene_script_text.h"
#else
static const char* actor_names[] = {_S("Alucard"), _S("Maria")};

// bss
static bool skip_cutscene;
Dialogue g_Dialogue; // Used by e_cutscene_actors
STATIC_PAD_BSS(104);
u32 g_CutsceneFlags; // Used by e_cutscene_actors
static bool dialogue_started;

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
    // Cutscene has control/cutscene running?
    g_Dialogue.unk3C = 1;
}

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
    if (g_CurrentEntity->step_s == DIALOG_BOX_INIT) {
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

void OVL_EXPORT(EntityCutsceneDialogue)(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i, j;
    s16 uCoord, vCoord;
    u16 nextChar;
#ifdef VERSION_PSP
    s32 charWidth;
    u8* charBuffer1;
    u8* charBuffer2;
    u32 tempChar;
    bool endLoop;
#endif
    RECT rect;
    s32 ptr;

#ifdef VERSION_PSP
    func_8926498();
#endif

    if (self->step) {
        if (dialogue_started && !skip_cutscene &&
            ((g_Settings.D_8003CB04 & 0x400) || g_IsTimeAttackUnlocked)) {
            if (g_pads[0].tapped & PAD_START) {
                skip_cutscene = true;
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

    if (self->step && g_Dialogue.unk3C) {
        CutsceneRun();
    }

    switch (self->step) {
    case DIALOGUE_INIT:
        if (g_CastleFlags[MET_MARIA_IN_DAI] ||
            g_PlayableCharacter != PLAYER_ALUCARD) {
            DestroyEntity(self);
            break;
        }
        if (SetCutsceneScript(OVL_EXPORT(cutscene_script))) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            g_CutsceneHasControl = true;
            g_CutsceneFlags = CUTSCENE_FLAG_NONE;
            dialogue_started = false;
            skip_cutscene = false;
            self->step++;
        }
        break;
    case DIALOGUE_RUN:
        nextChar = 0;
        // This is a big while loop which ends in the ifdef on line 639
        while (true) {
#ifdef VERSION_PSP
            nextChar = *g_Dialogue.scriptCur++;
            endLoop = false;
            if (func_8919BA8() & 8) {
                g_Dialogue.nextCharTimer = 0;
            }
            if ((g_Dialogue.nextCharTimer) && !skip_cutscene) {
                g_Dialogue.nextCharTimer--;
                g_Dialogue.scriptCur--;
                return;
            }
            if (!(nextChar & 0x80)) {
#else
            if ((g_Dialogue.nextCharTimer) && !skip_cutscene) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.scriptCur++;
#endif
                switch (nextChar) {
                case CSOP_END_CUTSCENE:
                    self->step = DIALOGUE_END;
                    return;
                case CSOP_LINE_BREAK:
                    if (skip_cutscene) {
                        continue;
                    }
                    g_Dialogue.nextCharX = g_Dialogue.nextLineX;
                    if (!(g_Dialogue.unk12 & 1)) {
                        g_Dialogue.nextLineY += CS_LINE_SPACING;
                    }
                    // This is line number increment
                    g_Dialogue.nextCharY++;
#ifdef VERSION_PSP
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
#ifndef VERSION_PSP
                            return;
#endif
                        }
#ifndef VERSION_PSP
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
                    if (skip_cutscene) {
                        continue;
                    }
                    return;
                case CSOP_HIDE_DIALOG:
                    if (skip_cutscene) {
                        continue;
                    }
                    prim = g_Dialogue.prim[0];
                    for (i = 0; i < LEN(g_Dialogue.prim) - 1; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    return;
                case CSOP_SET_PORTRAIT:
                    if (skip_cutscene) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    i = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
                    j = *g_Dialogue.scriptCur++;
#ifdef VERSION_PSP
                    charWidth = j & 1;
                    uCoord = u_coords[charWidth];
                    vCoord = v_coords[charWidth];
#else
                uCoord = u_coords[j & 1];
                vCoord = v_coords[j & 1];
#endif
                    prim->clut = cluts[i];
                    prim->tpage = 144;
#ifdef VERSION_PSP
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 47;
#else
                if (j & 0x80) {
                    prim->u0 = prim->u2 = uCoord + 47;
                    prim->u1 = prim->u3 = uCoord;
                } else {
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 47;
                }
#endif
                    prim->v0 = prim->v1 = vCoord;
                    prim->v2 = prim->v3 = vCoord + 72;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                        g_Dialogue.startX - 30;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        g_Dialogue.startY + 36;
                    g_Dialogue.clutIndex = cutscene_unk_4_cluts[i];
                    CutsceneUnk1();
                    CutsceneUnk4();
                    prim->priority = 510;
                    prim->drawMode = DRAW_DEFAULT;
#ifdef VERSION_PSP
                    DrawCutsceneActorName(
                        i, self, actor_names, actor_name_len_index,
                        actor_name_index, 4);
#else
                DrawCutsceneActorName(i, self);
#endif
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = DIALOGUE_START_TEXT;
                    return;
                case CSOP_NEXT_DIALOG:
                    if (skip_cutscene) {
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
                    if (skip_cutscene) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    g_Dialogue.startX = *g_Dialogue.scriptCur++;
                    g_Dialogue.startY = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
                    prim = prim->next;
                    prim->y0 = prim->y1 = g_Dialogue.startY;
                    prim->y2 = prim->y3 = g_Dialogue.startY + 72;
                    prim = prim->next;
                    prim->y0 = g_Dialogue.startY - 1;
                    prim->u0 = 246;
                    g_Dialogue.portraitAnimTimer = 24;
                    self->step = DIALOGUE_OPEN_DIALOG_BOX;
                    self->step_s = DIALOG_BOX_INIT;
                    return;
                case CSOP_CLOSE_DIALOG:
                    if (skip_cutscene) {
                        continue;
                    }
                    g_Dialogue.portraitAnimTimer = 24;
                    self->step = DIALOGUE_CLOSE_DIALOG_BOX;
                    return;
                case CSOP_PLAY_SOUND:
                    if (skip_cutscene) {
// psp and psx refuse to agree on this particular increment
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
                    if (g_api.func_80131F68() != 1) {
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
                    ptr += (u_long)OVL_EXPORT(cutscene_script_ptr);
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
                    ptr += (u_long)OVL_EXPORT(cutscene_script_ptr);
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
                    ptr += (u_long)OVL_EXPORT(cutscene_script_ptr);
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
                    ptr += (u_long)OVL_EXPORT(cutscene_script_ptr);
                    g_Dialogue.scriptCur = (u8*)ptr;
#else
                g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
#endif
                    continue;
                case CSOP_WAIT_FOR_FLAG:
                    if (!((g_CutsceneFlags >> *g_Dialogue.scriptCur) &
                          DAI_CUTSCENE_ALUCARD_READY)) {
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
                            ptr = (u_long)&gfx_portrait_alucard;
                            break;
                        case 1:
                            ptr = (u_long)&gfx_portrait_maria;
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
#else
                    ptr += 0x100000;
#endif
                        j = *g_Dialogue.scriptCur++;
                        LoadTPage((u_long*)ptr, 1, 0, x_vals[j], 256, 48, 72);
                    }
                    continue;
                case CSOP_SCRIPT_UNKNOWN_20:
                    nextChar = *g_Dialogue.scriptCur++;
                    nextChar <<= 4;
                    nextChar |= *g_Dialogue.scriptCur++;
                    g_api.PlaySfx(nextChar);
                    continue;
                case CSOP_SCRIPT_UNKNOWN_21:
                    g_CutsceneFlags = CUTSCENE_FLAG_NONE;
                    skip_cutscene = false;
                    dialogue_started = false;
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
                    endLoop = true;
                } // This closes the CSOP switch for psp
                if (endLoop) {
                    break; // This breaks the big while loop for psp
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
        } // This closes the big while loop for psp

        charBuffer1 = char_buffer_1;
#else
            } // This closes the CSOP switch for psx
            break; // This breaks the big while loop for psx
        } // This closes the big while loop for psx
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
        StoreImage(&rect, (u_long*)charBuffer1);
        for (i = 0; i < 32; i++) {
            // swaps the upper and lower 4 bits of each member
            charBuffer1[i] =
                ((charBuffer1[i] & 0x0F) << 4) | ((charBuffer1[i] & 0xF0) >> 4);
        }
        while (true) {
            if (nextChar == 32) {
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
        if (nextChar != 32) {
            g_Dialogue.nextCharX += rect.w;
        } else {
            g_Dialogue.nextCharX += 4;
        }
        // This seems like a mistake.
        if (((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) < 112) {
        };
        char_buffer = nextChar;
#else
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
#endif
        break;
    case DIALOGUE_LOAD_PORTRAIT:
#ifdef VERSION_PSP
        ptr = g_Dialogue.nextCharY;
        ptr = (ptr + 1) & CS_LINE_MAX;
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
        if (g_Dialogue.portraitAnimTimer >= 6) {
#endif
            self->step--;
        }
        break;
    case DIALOGUE_START_TEXT:
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
        }
        break;
    case DIALOGUE_OPEN_DIALOG_BOX:
        switch (self->step_s) {
        case DIALOG_BOX_INIT:
            // Initializes the dialogue box background by horizontal pixel line
            // Set to red for the initial draw in
            // uCoord is used as a horizontal line offset here
            dialogue_started = true;
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
        if (g_Dialogue.portraitAnimTimer >= 12) {
            prim = prim->next;
            prim->u0 -= 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                prim->u0--;
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
        }
        break;
    case DIALOGUE_END:
        DestroyEntity(self);
        g_CastleFlags[MET_MARIA_IN_DAI] = true;
        g_Settings.D_8003CB04 |= 0x400;
        g_CutsceneHasControl = false;
        break;
    }
}
