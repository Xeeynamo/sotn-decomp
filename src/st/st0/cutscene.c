// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

enum DialogueSteps {
    DIALOGUE_INIT,
    DIALOGUE_RUN,
    DIALOGUE_LOAD_PORTRAIT,
    DIALOGUE_START_TEXT,
    DIALOGUE_UNLOAD_PORTRAIT,
    DIALOGUE_OPEN_DIALOG_BOX,
    DIALOGUE_CLOSE_DIALOG_BOX,
    DIALOGUE_END,
};

enum DialogueSubsteps {
    DIALOG_BOX_INIT,
    DIALOG_BOX_DRAW_RED,
    DIALOG_BOX_DRAW_BLUE,
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

#ifdef VERSION_PSP
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
static u8 v_coords[] = {0, 0, 0, 0}; // bss for pspeu
#endif
static u16 cluts[] = {0x230, 0x248};
static u16 x_vals[] = {0, 32};
static u16 clut_indexes[] = {0x1A1, 0x1A1};
// Defines the increment of each line (by pixel, not text) of the dialogue box
// background. Results in the staggered red draw in.
static s16 red_line_increment[] = {
    8,  19, 17, 49, 79, 38, 54, 29, 27, 51, 44, 33, 25, 10, 51, 31, 72, 47,
    19, 25, 77, 75, 23, 29, 18, 2,  27, 42, 80, 69, 50, 13, 42, 77, 6,  39,
    7,  72, 47, 27, 54, 34, 57, 20, 57, 29, 10, 53, 16, 27, 61, 23, 46, 11,
    73, 66, 61, 42, 1,  12, 27, 52, 65, 53, 8,  14, 77, 17, 52, 65, 41, 72};

#ifdef VERSION_PSP
static u8 actor_name_len_indexes[] = {0, 1, 0, 0, 0, 0, 0, 0};
static u8 actor_name_indexes[] = {0, 1, 0, 0, 0, 0, 0, 0};

// bss
u32 OVL_EXPORT(CutsceneFlags);
bool OVL_EXPORT(SkipCutscene);
bool OVL_EXPORT(IsCutsceneDone);
// Not truely a global, but is named for alignment with us, which is a global
static Dialogue OVL_EXPORT(Dialogue);
static u8* OVL_EXPORT(cutscene_script);
static u8 buffer_2;
static u8 buffer_1[32];
static u8 cutsceneUnk3Unknown[896];
static u16 actor_names[256];
extern u8 v_coords[8];

// extern data
extern u8 cutscene_script_en;
extern u8 cutscene_script_fr;
extern u8 cutscene_script_sp;
extern u8 cutscene_script_ge;
extern u8 cutscene_script_it;

extern u32 D_893CF8C;
extern u32 D_893DD0C;
extern u32 gfx_portrait_richter;
extern u32 gfx_portrait_dracula;
extern u32 D_894058C;
extern u32 D_894130C;
extern u32 D_894208C;
extern u32 D_8942E0C;
extern u32 D_8943B8C;
extern u32 D_894490C;
extern u32 D_894568C;

#include "../cutscene_actor_name_psp.h"
#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"
#include "../cutscene_unk1.h"
#include "../set_cutscene_script.h"
#include "../set_cutscene_end.h"
#include "../cutscene_run.h"
#else
static const char* actor_names[] = {_S("Richter"), _S("Dracula")};

// bss
bool OVL_EXPORT(SkipCutscene);
Dialogue OVL_EXPORT(Dialogue);
u32 D_801C2510[26];
extern u32 OVL_EXPORT(CutsceneFlags);   // defined in 2A218
extern bool OVL_EXPORT(IsCutsceneDone); // defined in 2A218

// extern data
extern u8 OVL_EXPORT(cutscene_script)[];

#include "../cutscene_unk1.h"

static u8 SetCutsceneScript(u8* script) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 8);
    OVL_EXPORT(Dialogue).primIndex[2] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        OVL_EXPORT(Dialogue).primIndex[2] = 0;
        return 0;
    }
    OVL_EXPORT(Dialogue).scriptCur = script;
    OVL_EXPORT(Dialogue).unk3C = 0;
    OVL_EXPORT(Dialogue).primIndex[1] = -1;
    OVL_EXPORT(Dialogue).primIndex[0] = -1;
    CutsceneUnk1();

    if (prim && prim) { // !FAKE
    }

    prim = OVL_EXPORT(Dialogue).prim[0] =
        &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[2]];

    prim->drawMode = DRAW_HIDE;
    prim = OVL_EXPORT(Dialogue).prim[1] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = OVL_EXPORT(Dialogue).prim[2] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = OVL_EXPORT(Dialogue).prim[3] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = OVL_EXPORT(Dialogue).prim[4] = prim->next;

    prim->drawMode = DRAW_HIDE;
    prim = OVL_EXPORT(Dialogue).prim[5] = prim->next;

    prim->type = PRIM_GT4;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = PRIM_G4;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->drawMode = DRAW_HIDE;

    prim = prim->next;
    prim->type = PRIM_TILE;
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
#include "../cutscene_actor_name.h"
#include "../set_cutscene_end.h"
#include "../cutscene_run.h"
#include "../cutscene_scale_avatar.h"
#endif

void OVL_EXPORT(EntityCutscene)(Entity* self) {
    u16 nextByte;
    s32 primIndex;
    bool endLoopFlag;
    s16 vCoord, uCoord;
    Primitive* prim;
    s32 i, j;
#ifdef VERSION_PSP
    s32 charWidth;
    u8* buffer1;
    u8* buffer2;
    u32 buffer3;
#endif
    RECT rect;
    s32 ptr;

    if (OVL_EXPORT(IsCutsceneDone) && !OVL_EXPORT(SkipCutscene) &&
        ((g_Settings.D_8003CB04 & 1) || g_GameClearFlag) &&
        (g_pads[0].tapped == PAD_START)) {
        OVL_EXPORT(SkipCutscene) = true;
        g_api.FreePrimitives(self->primIndex);
        self->flags &= ~FLAG_HAS_PRIMS;
        if (OVL_EXPORT(Dialogue).primIndex[1] != -1) {
            g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[1]);
        }
        if (OVL_EXPORT(Dialogue).primIndex[0] != -1) {
            g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[0]);
        }
        g_api.PlaySfx(SET_UNK_80);
        self->step = 1;
        self->step_s = 0;
    }
    if (self->step && OVL_EXPORT(Dialogue).unk3C) {
        CutsceneRun();
    }

    switch (self->step) {
    case DIALOGUE_INIT:
#ifdef VERSION_PSP
        OVL_EXPORT(cutscene_script) = GetLangAt(
            0, &cutscene_script_en, &cutscene_script_fr, &cutscene_script_sp,
            &cutscene_script_ge, &cutscene_script_it);
#endif
        if (SetCutsceneScript(OVL_EXPORT(cutscene_script))) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = OVL_EXPORT(Dialogue).primIndex[2];
            OVL_EXPORT(CutsceneFlags) = CUTSCENE_FLAG_NONE;
            OVL_EXPORT(IsCutsceneDone) = false;
            OVL_EXPORT(SkipCutscene) = false;
            g_CutsceneHasControl = true;
            self->step++;
            if (g_DemoMode != Demo_None) {
                OVL_EXPORT(SkipCutscene) = true;
                OVL_EXPORT(IsCutsceneDone) = true;
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
            }
        }
        break;
    case DIALOGUE_RUN:
        nextByte = 0;
        // this is a huge While-loop! Don't miss it!
        while (true) {
            if (OVL_EXPORT(Dialogue).nextCharTimer &&
                !OVL_EXPORT(SkipCutscene)) {
                OVL_EXPORT(Dialogue).nextCharTimer--;
                return;
            }
            nextByte = *OVL_EXPORT(Dialogue).scriptCur++;
#ifdef VERSION_PSP
            endLoopFlag = false;
            if (!(nextByte & 0x80)) {
#endif
                // This switch is closed on line ??? for us and ??? for pspeu
                switch (nextByte) {
                case CSOP_END_CUTSCENE:
                    self->step = DIALOGUE_END;
                    return;
                case CSOP_LINE_BREAK:
                    if (OVL_EXPORT(SkipCutscene)) {
                        continue;
                    }
                    OVL_EXPORT(Dialogue).nextCharX =
                        OVL_EXPORT(Dialogue).nextLineX;
                    if (!(OVL_EXPORT(Dialogue).unk12 & 1)) {
                        OVL_EXPORT(Dialogue).nextLineY += CS_LINE_SPACING;
                    }
                    OVL_EXPORT(Dialogue).nextCharY++;
#ifdef VERSION_PSP
                    OVL_EXPORT(Dialogue).nextCharY &= CS_LINE_MAX;
#else
                if (OVL_EXPORT(Dialogue).nextCharY >= 5) {
                    OVL_EXPORT(Dialogue).nextCharY = 0;
                }
#endif
                    CutsceneUnk4();
                    if (!(OVL_EXPORT(Dialogue).unk12 & 1)) {
                        if (OVL_EXPORT(Dialogue).nextCharY > CS_LINE_MAX - 1) {
                            OVL_EXPORT(Dialogue).unk12 |= 1;
                            OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
                            self->step_s = DIALOG_BOX_INIT;
                            self->step++;
#ifdef VERSION_US
                            return;
                        }
                        continue;
#else
                    }
#endif
                    } else {
                        OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
                        self->step_s = DIALOG_BOX_INIT;
                        self->step++;
                    }
                    return;
                case CSOP_SET_SPEED:
#ifdef VERSION_US
                    OVL_EXPORT(Dialogue).unk17 =
#endif
                        *OVL_EXPORT(Dialogue).scriptCur++;
                    continue;
                case CSOP_SET_WAIT:
                    OVL_EXPORT(Dialogue).nextCharTimer =
                        *OVL_EXPORT(Dialogue).scriptCur++;
                    if (OVL_EXPORT(SkipCutscene)) {
                        continue;
                    }
                    return;
                case CSOP_HIDE_DIALOG:
                    if (OVL_EXPORT(SkipCutscene)) {
                        continue;
                    }
                    prim = OVL_EXPORT(Dialogue).prim[0];
                    for (i = 0; i < LEN(OVL_EXPORT(Dialogue).prim) - 1; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    return;
                case CSOP_SET_PORTRAIT:
                    if (OVL_EXPORT(SkipCutscene)) {
                        OVL_EXPORT(Dialogue).scriptCur += 2;
                        continue;
                    }
                    i = *OVL_EXPORT(Dialogue).scriptCur++;
                    prim = OVL_EXPORT(Dialogue)
                               .prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
                    j = *OVL_EXPORT(Dialogue).scriptCur++;
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
                    if (j & 0x80) {
                        prim->u0 = prim->u2 = uCoord + 47;
                        prim->u1 = prim->u3 = uCoord;
                    } else {
                        prim->u0 = prim->u2 = uCoord;
                        prim->u1 = prim->u3 = uCoord + 47;
                    }
                    prim->v0 = prim->v1 = vCoord;
                    prim->v2 = prim->v3 = vCoord + 72;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                        OVL_EXPORT(Dialogue).startX - 30;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        OVL_EXPORT(Dialogue).startY + 36;
                    OVL_EXPORT(Dialogue).clutIndex = clut_indexes[i];
                    CutsceneUnk1();
                    CutsceneUnk4();
                    prim->priority = 510;
                    prim->drawMode = DRAW_DEFAULT;

                    DrawCutsceneActorName(
#ifdef VERSION_PSP
                        i, self, actor_names, actor_name_len_indexes,
                        actor_name_indexes, 2
#else
                    i, self
#endif
                    );

                    OVL_EXPORT(Dialogue).portraitAnimTimer = 6;
                    self->step = DIALOGUE_START_TEXT;
                    return;
                case CSOP_NEXT_DIALOG:
                    if (OVL_EXPORT(SkipCutscene)) {
                        continue;
                    }
                    prim = OVL_EXPORT(Dialogue).prim[0];
                    for (i = 0; i < LEN(OVL_EXPORT(Dialogue).prim) - 1; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
                    g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[1]);
                    OVL_EXPORT(Dialogue).primIndex[1] = -1;
                    OVL_EXPORT(Dialogue).portraitAnimTimer = 6;
                    self->step = DIALOGUE_UNLOAD_PORTRAIT;
                    return;
                case CSOP_SET_POS:
                    if (OVL_EXPORT(SkipCutscene)) {
                        OVL_EXPORT(Dialogue).scriptCur += 2;
                        continue;
                    }
                    OVL_EXPORT(Dialogue).startX =
                        *OVL_EXPORT(Dialogue).scriptCur++;
                    OVL_EXPORT(Dialogue).startY =
                        *OVL_EXPORT(Dialogue).scriptCur++;
                    prim = OVL_EXPORT(Dialogue)
                               .prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
                    prim = prim->next;
                    prim->y0 = prim->y1 = OVL_EXPORT(Dialogue).startY;
                    prim->y2 = prim->y3 = OVL_EXPORT(Dialogue).startY + 72;
                    prim = prim->next;
                    prim->y0 = OVL_EXPORT(Dialogue).startY - 1;
                    prim->u0 = 246;
                    OVL_EXPORT(Dialogue).portraitAnimTimer = 24;
                    self->step = DIALOGUE_OPEN_DIALOG_BOX;
                    self->step_s = DIALOG_BOX_INIT;
                    return;
                case CSOP_CLOSE_DIALOG:
                    if (OVL_EXPORT(SkipCutscene)) {
                        continue;
                    }
                    OVL_EXPORT(Dialogue).portraitAnimTimer = 24;
                    self->step = DIALOGUE_CLOSE_DIALOG_BOX;
                    return;
                case CSOP_PLAY_SOUND:
                    if (OVL_EXPORT(SkipCutscene)) {
                        OVL_EXPORT(Dialogue).scriptCur += 2;
                        continue;
                    }
                    nextByte = *OVL_EXPORT(Dialogue).scriptCur++;
                    nextByte <<= 4;
                    nextByte |= *OVL_EXPORT(Dialogue).scriptCur++;
                    g_api.PlaySfx(nextByte);
                    continue;
                case CSOP_WAIT_FOR_SOUND:
                    if (OVL_EXPORT(SkipCutscene)) {
                        continue;
                    }
                    if (g_api.func_80131F68()) {
                        continue;
                    }
                    *OVL_EXPORT(Dialogue).scriptCur--;
                    return;
                case CSOP_SCRIPT_UNKNOWN_11:
                    if (OVL_EXPORT(SkipCutscene)) {
                        continue;
                    }
                    if (g_api.func_80131F68() != 1) {
                        continue;
                    }
                    *OVL_EXPORT(Dialogue).scriptCur--;
                    return;
                case CSOP_SET_END:
                    ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
#ifdef VERSION_PSP
                    ptr += (u32)OVL_EXPORT(cutscene_script);
#endif
                    SetCutsceneEnd((u8*)ptr);
                    continue;
                case CSOP_SCRIPT_UNKNOWN_13:
                    continue;
                case CSOP_SCRIPT_SWITCH:
                    ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    // This needs help. Casting the const to short is good.
                    ptr += (u16)0x100000;
#ifdef VERSION_PSP
                    OVL_EXPORT(Dialogue).scriptCur += *(u8*)ptr * 4;
#else
                OVL_EXPORT(Dialogue).scriptCur += *(u16*)ptr * 4;
#endif

                    ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur;
#ifdef VERSION_PSP
                    OVL_EXPORT(Dialogue).scriptCur = (u8*)ptr;
#else
                OVL_EXPORT(Dialogue).scriptCur = (u8*)ptr + 0x100000;
#endif
                    continue;
                case CSOP_SCRIPT_UNKNOWN_15:
                    ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur;
#ifdef VERSION_PSP
                    OVL_EXPORT(Dialogue).scriptCur = (u8*)ptr;
#else
                OVL_EXPORT(Dialogue).scriptCur = (u8*)ptr + 0x100000;
#endif
                    continue;
                case CSOP_WAIT_FOR_FLAG:
                    // TODO: Does & 1 mean Alucard ready?
                    if (!((OVL_EXPORT(CutsceneFlags) >>
                           *OVL_EXPORT(Dialogue).scriptCur) &
                          1)) {
                        OVL_EXPORT(Dialogue).scriptCur--;
                        return;
                    }
                    OVL_EXPORT(CutsceneFlags) &=
                        ~(1 << *OVL_EXPORT(Dialogue).scriptCur);
                    *OVL_EXPORT(Dialogue).scriptCur++;
                    continue;
                case CSOP_SET_FLAG:
                    OVL_EXPORT(CutsceneFlags) |=
                        1 << *OVL_EXPORT(Dialogue).scriptCur++;
                    continue;
                case CSOP_SCRIPT_UNKNOWN_18:
                    OVL_EXPORT(Dialogue).unk3C = 0;
                    continue;
                case CSOP_LOAD_PORTRAIT:
                    if (OVL_EXPORT(SkipCutscene)) {
                        OVL_EXPORT(Dialogue).scriptCur += 5;
                    } else {
                        ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                        ptr <<= 4;
                        ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                        ptr <<= 4;
                        ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                        ptr <<= 4;
                        ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
#ifdef VERSION_PSP
                        switch (ptr) {
                        case 0:
                            ptr = (u32)&D_893CF8C;
                            break;
                        case 1:
                            ptr = (u32)&D_893DD0C;
                            break;
                        case 2:
                            ptr = (u32)&gfx_portrait_richter;
                            break;
                        case 3:
                            ptr = (u32)&gfx_portrait_dracula;
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
#else
                    ptr += 0x100000;
#endif
                        j = *OVL_EXPORT(Dialogue).scriptCur++;
                        // Load the portrait into the buffer
                        LoadTPage((u_long*)ptr, 1, 0, x_vals[j], 256, 48, 72);
                    }
                    continue;
                case CSOP_SCRIPT_UNKNOWN_20:
                    nextByte = *OVL_EXPORT(Dialogue).scriptCur++;
                    nextByte <<= 4;
                    nextByte |= *OVL_EXPORT(Dialogue).scriptCur++;
                    g_api.PlaySfx(nextByte);
                    continue;
                // Note: Other cutscenes have Case 21-24 here, this one is
                // missing it.
                default:
                    if (OVL_EXPORT(SkipCutscene)) {
                        continue;
                    }
                    OVL_EXPORT(Dialogue).nextCharTimer =
                        OVL_EXPORT(Dialogue).unk17;

#ifdef VERSION_PSP
                    endLoopFlag = true;
                } // This closes the CSOP switch for psp
                if (endLoopFlag) {
                    break; // This breaks the big while loop for psp
                }
                continue;
            } else {
                if (OVL_EXPORT(SkipCutscene)) {
                    OVL_EXPORT(Dialogue).scriptCur++;
                    continue;
                }
                if (167 <= nextByte && nextByte < 173) {
                    nextByte = nextByte + 39;
                } else if (nextByte == 166) {
                    LOH(nextByte) = 204;
                } else if (nextByte == 221) {
                    nextByte = 205;
                } else {
                    nextByte = nextByte - 17;
                }
                OVL_EXPORT(Dialogue).nextCharTimer = OVL_EXPORT(Dialogue).unk17;
            }
            break; // This breaks the big while loop for psp
        } // This closes the big while loop for psp

        buffer1 = buffer_1;
#else
            } // This closes the CSOP switch for psx
            break; // This breaks the big while loop for psx
        } // This closes the big while loop for psx
        if (nextByte == ' ') {
            OVL_EXPORT(Dialogue).nextCharX += 2;
            return;
        }
#endif
        rect.x = ((nextByte & 0xF) * 2) + 896;
        rect.y = ((nextByte & 0xF0) >> 1) + 240;
        rect.w = 2;
        rect.h = 8;
        vCoord = (OVL_EXPORT(Dialogue).nextCharY * 12) + 384;
#ifdef VERSION_PSP
        StoreImage(&rect, (u_long*)buffer1);
        for (i = 0; i < 32; i++) {
            // Swaps the upper and lower 4 bits of each member
            buffer1[i] =
                ((buffer1[i] & 0x0F) << 4) | ((buffer1[i] & 0xF0) >> 4);
        }
        while (true) {
            if (nextByte == ' ') {
                break;
            }
            for (i = 0; i < 8; i++) {
                if (buffer1[(i * 8) / 2] & 0xF0) {
                    break;
                }
            }
            if (i != 8) {
                break;
            }
            for (i = 0; i < 8; i++) {
                // Pack the bytes
                buffer2 = &buffer1[(i * 8) / 2];
                buffer3 = (buffer2[0] << 24);
                buffer3 |= (buffer2[1] << 16);
                buffer3 |= (buffer2[2] << 8);
                buffer3 |= (buffer2[3]);
                buffer3 *= CS_LINE_SPACING;
                // Unpack the bytes
                buffer2[0] = (buffer3 >> 24) & 0xFF;
                buffer2[1] = (buffer3 >> 16) & 0xFF;
                buffer2[2] = (buffer3 >> 8) & 0xFF;
                buffer2[3] = (buffer3) & 0xFF;
            }
        }
        for (i = 0, charWidth = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if ((buffer1[j / 2 + (i * 8) / 2]) & (0xF0 >> ((j & 1) * 4))) {
                    if (j > charWidth) {
                        charWidth = j;
                    }
                };
            }
        }
        charWidth += 2;
        for (i = 0; i < 32; i++) {
            // Swap upper and lower
            buffer1[i] =
                ((buffer1[i] & 0x0F) << 4) | ((buffer1[i] & 0xF0) >> 4);
        }
        rect.w = charWidth;
        buffer1 = buffer_1;
        for (i = 0; i < 8; i++) {
            buffer2 = &cutsceneUnk3Unknown[((OVL_EXPORT(Dialogue).nextCharX -
                                             OVL_EXPORT(Dialogue).nextLineX) /
                                            2) +
                                           (i * 112)];
            if ((OVL_EXPORT(Dialogue).nextCharX -
                 OVL_EXPORT(Dialogue).nextLineX) &
                1) {
                // Swap upper and lower while shifting a byte to the right
                buffer2[0] = (buffer2[0] & 0xF0) | ((buffer1[0] & 0x0F) << 4);
                buffer2[1] =
                    ((buffer1[0] & 0xF0) >> 4) | ((buffer1[1] & 0x0F) << 4);
                buffer2[2] =
                    ((buffer1[1] & 0xF0) >> 4) | ((buffer1[2] & 0x0F) << 4);
                buffer2[3] =
                    ((buffer1[2] & 0xF0) >> 4) | ((buffer1[3] & 0x0F) << 4);
                buffer2[4] = ((buffer1[3] & 0xF0) >> 4);
                buffer1 += 4;
            } else {
                buffer2[0] = buffer1[0];
                buffer2[1] = buffer1[1];
                buffer2[2] = buffer1[2];
                buffer2[3] = buffer1[3];
                buffer1 += 4;
            }
        }
        LoadTPage((u_long*)cutsceneUnk3Unknown, 0, 0,
                  OVL_EXPORT(Dialogue).nextLineX, vCoord, 224, 8);
        if (nextByte != ' ') {
            OVL_EXPORT(Dialogue).nextCharX += rect.w;
        } else {
            OVL_EXPORT(Dialogue).nextCharX += 4;
        }
        // This seems like a mistake.
        if (((OVL_EXPORT(Dialogue).nextCharX - OVL_EXPORT(Dialogue).nextLineX) /
             2) < 112) {
        };
        buffer_2 = nextByte;
#else
        MoveImage(&rect, OVL_EXPORT(Dialogue).nextCharX, vCoord);
        OVL_EXPORT(Dialogue).nextCharX += 2;
#endif
        break;
    case DIALOGUE_LOAD_PORTRAIT:
#ifdef VERSION_PSP
        ptr = (OVL_EXPORT(Dialogue).nextCharY + 1) & CS_LINE_MAX;
        if (!self->step_s) {
            prim = OVL_EXPORT(Dialogue).prim[ptr];
            prim->v0 += 2;
            prim->v1 -= 2;
            if (!prim->v1) {
                self->step_s++;
                prim->drawMode = DRAW_HIDE;
            }
        }
        for (i = 0; i < LEN(OVL_EXPORT(Dialogue).prim) - 1; i++) {
            if (i != ptr) {
                prim = OVL_EXPORT(Dialogue).prim[i];
                prim->y0 -= 2;
            }
        }
        OVL_EXPORT(Dialogue).portraitAnimTimer++;
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 8) {
#else
        ScaleCutsceneAvatar(2);
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 6) {
#endif
            self->step--;
        }
        break;
    case DIALOGUE_START_TEXT:
        prim = OVL_EXPORT(Dialogue).prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
        prim->x0 = prim->x2 -= 4;
        prim->x1 = prim->x3 += 4;
        prim->y0 = prim->y1 -= 6;
        prim->y2 = prim->y3 += 6;
        // This block is in DIALOGUE_UNLOAD_PORTRAIT for other cutscenes,
        // DIALOGUE_START_TEXT for this one
        if (prim->x1 >= (OVL_EXPORT(Dialogue).startX - 2)) {
            prim->x1 = prim->x3 = OVL_EXPORT(Dialogue).startX - 3;
        }
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (!OVL_EXPORT(Dialogue).portraitAnimTimer) {
            self->step = DIALOGUE_RUN;
            for (prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[1]];
                 prim != NULL; prim = prim->next) {
                prim->drawMode = DRAW_DEFAULT;
            }
        }
        break;
    case DIALOGUE_UNLOAD_PORTRAIT:
        prim = OVL_EXPORT(Dialogue).prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
        prim->x0 = prim->x2 += 4;
        prim->x1 = prim->x3 -= 4;
        prim->y0 = prim->y1 += 6;
        prim->y2 = prim->y3 -= 6;
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (!OVL_EXPORT(Dialogue).portraitAnimTimer) {
            self->step = DIALOGUE_RUN;
        }
        break;
    case DIALOGUE_OPEN_DIALOG_BOX:
        switch (self->step_s) {
        case DIALOG_BOX_INIT:
            OVL_EXPORT(IsCutsceneDone) = true;
            primIndex =
                g_api.AllocPrimitives(PRIM_LINE_G2, LEN(red_line_increment));
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            OVL_EXPORT(Dialogue).primIndex[0] = primIndex;
            for (prim = &g_PrimBuf[primIndex], uCoord = 0; prim != NULL;
                 uCoord++, prim = prim->next) {
                prim->r0 = prim->r1 = 127;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 247;
                prim->y0 = prim->y1 = OVL_EXPORT(Dialogue).startY + uCoord;
                prim->priority = 510;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = red_line_increment[uCoord];
                prim->x3 = 3952;
            }
            self->step_s++;
            break;
        case DIALOG_BOX_DRAW_RED:
            uCoord = false;
            for (prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[0]];
                 prim != NULL; prim = prim->next) {
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
                g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[0]);
                OVL_EXPORT(Dialogue).primIndex[0] = -1;
                prim = OVL_EXPORT(Dialogue)
                           .prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
                prim = prim->next;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                self->step_s++;
            }
            break;
        case DIALOG_BOX_DRAW_BLUE:
            uCoord = false;
            prim =
                OVL_EXPORT(Dialogue).prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
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
        prim = OVL_EXPORT(Dialogue).prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
        prim = prim->next;
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 12) {
            prim = prim->next;
            prim->u0 -= 20;
            if (OVL_EXPORT(Dialogue).portraitAnimTimer & 1) {
                prim->u0--;
            }
        } else {
            if (!OVL_EXPORT(Dialogue).portraitAnimTimer) {
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
        g_Settings.D_8003CB04 |= 1;
        g_CutsceneHasControl = false;
        DestroyEntity(self);
        break;
    }
}
