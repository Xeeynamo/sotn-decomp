// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

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

#include "../../get_lang.h"

#else
extern u8 cutscene_data[];

// bss
STATIC_PAD_BSS(0xC00);
s32 g_SkipCutscene;
Dialogue g_Dialogue;
STATIC_PAD_BSS(0x68);
u32 g_CutsceneFlags;
s32 D_us_801BC514;
static s32 g_IsCutsceneDone;
#endif

static u8 u_coords[] = {0x00, 0x40, 0x00, 0x00};
#ifndef VERSION_PSP
// PSP has this zeroed out in BSS
static u8 v_coords[] = {0x00, 0x00, 0x00, 0x00};
#endif
static u16 cluts[] = {0x0210, 0x0218, 0x0220};
static u16 x_vals[] = {0x0000, 0x0020};
static u16 cutscene_unk_4_cluts[] = {0x01A1, 0x01A1, 0x01A1, 0x01A1};
// Defines the increment of each line (by pixel, not text) of the dialogue box
// background. Results in the staggered red draw in.
static s16 red_line_increment[] = {
    0x0008, 0x0013, 0x0011, 0x0031, 0x004F, 0x0026, 0x0036, 0x001D, 0x001B,
    0x0033, 0x002C, 0x0021, 0x0019, 0x000A, 0x0033, 0x001F, 0x0048, 0x002F,
    0x0013, 0x0019, 0x004D, 0x004B, 0x0017, 0x001D, 0x0012, 0x0002, 0x001B,
    0x002A, 0x0050, 0x0045, 0x0032, 0x000D, 0x002A, 0x004D, 0x0006, 0x0027,
    0x0007, 0x0048, 0x002F, 0x001B, 0x0036, 0x0022, 0x0039, 0x0014, 0x0039,
    0x001D, 0x000A, 0x0035, 0x0010, 0x001B, 0x003D, 0x0017, 0x002E, 0x000B,
    0x0049, 0x0042, 0x003D, 0x002A, 0x0001, 0x000C, 0x001B, 0x0034, 0x0041,
    0x0035, 0x0008, 0x000E, 0x004D, 0x0011, 0x0034, 0x0041, 0x0029, 0x0048,
};

#ifdef VERSION_PSP
static u8 actor_name_len_index[] = {
    NAME_IDX_ALUCARD, NAME_IDX_MARIA, NAME_IDX_RICHTER};
// This is passed to, but seems to be unused within DrawCutsceneActorName
static u8 actor_name_index[] = {
    NAME_IDX_ALUCARD, NAME_IDX_MARIA, NAME_IDX_RICHTER};

// bss
u32 g_CutsceneFlags;
s32 g_SkipCutscene;
// not a true global, but must be named this because of the shared .h files
static Dialogue g_Dialogue;
static u8* cutscene_data;
static u8 char_buffer;
static u8 char_buffer_1[32];
static u8 cutsceneUnk3Unknown[0x380];
static u16 actor_names[0x100];
static u8 v_coords[8];
static s32 g_IsCutsceneDone;
s32 D_us_801BC514;

extern u8* post_fight_script_ptr1; // Defined by st_init
extern u8* post_fight_script_ptr2; // Defined by st_init
extern u8* talk_script_ptr1;       // Defined by st_init
extern u8* talk_script_ptr2;       // Defined by st_init
extern u8* talk_script_ptr3;       // Defined by st_init

extern u_long D_pspeu_09259A68;
extern u_long D_pspeu_0925A7E8;
extern u_long D_pspeu_0925B568;
extern u_long D_893F80C;
extern u_long D_894058C;
extern u_long D_894130C;
extern u_long D_894208C;
extern u_long D_8942E0C;
extern u_long D_8943B8C;
extern u_long D_894490C;
extern u_long D_894568C;

#include "../cutscene_actor_name.h"
#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"
#define CUTSCENE_UNK1_NEXT_X 0
#define CUTSCENE_UNK1_UNK17 2
#include "../cutscene_unk1.h"
#include "../set_cutscene_script.h"
#include "../set_cutscene_events.h"
#else
static const char* actor_names[] = {_S("Alucard"), _S("Maria"), _S("Richter")};

// Different order on PSX/PSP
#include "../cutscene_unk1.h"
#include "../set_cutscene_script.h"
#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"
#include "../cutscene_actor_name.h"
#include "../set_cutscene_events.h"
#endif

#define CUTSCENE_TILEMAP_SCROLL
#include "../cutscene_events.h"
#include "../cutscene_skip.h"
#include "../cutscene_scale_avatar.h"

void EntityCutscene(Entity* self) {
    s16 uCoord;
    s16 vCoord;
    s32 primIndex;
    u16* charData;
    bool endLoop;
    RECT rect;
    u16 nextChar;
    s32 charWidth;
    u8* charBuffer1;
    s32 j;
    u_long ptr;
    u32 tempChar;
    Primitive* prim;
    u8* charBuffer2;
    s32 i;
    s32 nextChar2;

    if (self->step && g_IsCutsceneDone && !g_SkipCutscene) {
        if (g_GameClearFlag) {
            CutsceneSkip(self);
#ifdef VERSION_PSP
        } else if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
            if (g_CastleFlags[TOP_FIGHT_CS_UNK1]) {
                if (g_Settings.D_8003CB04 & 0x2000000) {
                    CutsceneSkip(self);
                }
            } else if (g_Settings.D_8003CB04 & 0x1000000) {
                CutsceneSkip(self);
            }
#endif
        } else if (g_Settings.D_8003CB04 & 0x800000) {
            CutsceneSkip(self);
        }
    }

    if (self->step && g_Dialogue.hasEvents) {
        RunCutsceneEvents();
    }

    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        // Skip the cutscene if 2 or more of these bosses have been defeated
        uCoord = 0;
        if (g_api.TimeAttackController(
                TIMEATTACK_EVENT_DARKWING_BAT_DEFEAT, TIMEATTACK_GET_RECORD)) {
            uCoord++;
        }
        if (g_api.TimeAttackController(
                TIMEATTACK_EVENT_AKMODAN_II_DEFEAT, TIMEATTACK_GET_RECORD)) {
            uCoord++;
        }
        if (g_api.TimeAttackController(
                TIMEATTACK_EVENT_MEDUSA_DEFEAT, TIMEATTACK_GET_RECORD)) {
            uCoord++;
        }
        if (g_api.TimeAttackController(
                TIMEATTACK_EVENT_THE_CREATURE_DEFEAT, TIMEATTACK_GET_RECORD)) {
            uCoord++;
        }
        if (g_api.TimeAttackController(
                TIMEATTACK_EVENT_DEATH_DEFEAT, TIMEATTACK_GET_RECORD)) {
            uCoord++;
        }
        if (g_PlayableCharacter != PLAYER_ALUCARD || uCoord >= 2) {
            DestroyEntity(self);
            break;
        }
        if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
            i = SetCutsceneScript(talk_script_ptr1);
            cutscene_data = talk_script_ptr2;
            *talk_script_ptr3 = g_CastleFlags[TOP_FIGHT_CS_UNK1];
        } else {
            i = SetCutsceneScript(post_fight_script_ptr1);
            cutscene_data = post_fight_script_ptr2;
        }
        if (i) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            g_CutsceneHasControl = 1;
            g_CutsceneFlags = 0;
            g_IsCutsceneDone = 0;
            g_SkipCutscene = 0;
            self->step++;
        }
        // fallthrough
#else
        if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED] ||
            g_PlayableCharacter != PLAYER_ALUCARD) {
            DestroyEntity(self);
            return;
        }
        if (SetCutsceneScript(cutscene_data)) {
            g_CutsceneHasControl = true;
            g_CutsceneFlags = 0;
            g_IsCutsceneDone = 0;
            g_SkipCutscene = 0;
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step++;
        }
        break;
#endif
    case 1:
        nextChar = 0;
        // this is a huge While-loop! Don't miss it!
        while (1) {
#ifdef VERSION_PSP
            nextChar = *g_Dialogue.scriptCur++;
            endLoop = false;
            if (PadReadPSP() & PAD_START) {
                g_Dialogue.nextCharTimer = 0;
            }
            if (g_Dialogue.nextCharTimer && !g_SkipCutscene) {
                g_Dialogue.nextCharTimer--;
                g_Dialogue.scriptCur--;
                return;
            }
            if (!(nextChar & 0x80)) {
#else
            if ((g_Dialogue.nextCharTimer != 0) && !g_SkipCutscene) {
                g_Dialogue.nextCharTimer--;
                return;
            }
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
                            self->step_s = 0;
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
                        self->step_s = 0;
                        self->step++;
                    }
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
                        actor_name_index, 3);
#else
                DrawCutsceneActorName(i, self);
#endif
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = 3;
                    return;
                case CSOP_NEXT_DIALOG:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    for (prim = g_Dialogue.prim[0], i = 0;
                         i < LEN(g_Dialogue.prim) - 1; i++) {
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
#ifdef VERSION_PSP
                    ptr += (u_long)cutscene_data;
#else
                ptr += 0x100000;
#endif
                    g_Dialogue.scriptCur += *(u8*)CS_NEXT(ptr) << 2;

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
                            ptr = (u_long)&D_pspeu_09259A68;
                            break;
                        case 1:
                            ptr = (u_long)&D_pspeu_0925A7E8;
                            break;
                        case 2:
                            ptr = (u_long)&D_pspeu_0925B568;
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
                        LoadTPage((u_long*)ptr, 1, 0, x_vals[j], 0x100, 48, 72);
#else
                    ptr = (u_long)CS_PTR(ptr);
                    nextChar2 = g_Dialogue.scriptCur++[0];
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
                    continue;
                default:
                    if (g_SkipCutscene) {
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

        charData = g_api.func_80106A28(nextChar, 1);
        charBuffer1 = char_buffer_1;
#else
            } // This closes the CSOP switch for psx
            break; // This breaks the big while loop for psx
        } // This closes the big while loop for psx
        if (nextChar == 0x20) {
            g_Dialogue.nextCharX += 2;
            return;
        }
#endif
        rect.x = ((nextChar & 0xF) << 1) + 0x380;
        rect.y = ((s32)(nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 0xC) + 0x180;
#ifdef VERSION_PSP
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
                tempChar = (charBuffer2[0] << 0x18);
                tempChar |= (charBuffer2[1] << 0x10);
                tempChar |= (charBuffer2[2] << 0x08);
                tempChar |= (charBuffer2[3]);
                tempChar <<= 4;
                charBuffer2[0] = (tempChar >> 0x18) & 0xFF;
                charBuffer2[1] = (tempChar >> 0x10) & 0xFF;
                charBuffer2[2] = (tempChar >> 0x08) & 0xFF;
                charBuffer2[3] = (tempChar) & 0xFF;
            }
        }
        for (i = 0, charWidth = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if ((charBuffer1[j / 2 + (i << 3) / 2]) &
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
                  vCoord, 0xE0, 8);
        if (nextChar != 0x20) {
            g_Dialogue.nextCharX += rect.w;
        } else {
            g_Dialogue.nextCharX += 4;
        }
        // This seems like a mistake.
        if (((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) < 0x70) {
        };
        char_buffer = nextChar;
#else
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
#endif
        break;
    case 2:
#ifdef VERSION_PSP
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
            self->step--;
        }
#else
        ScaleCutsceneAvatar(2);
        if (g_Dialogue.portraitAnimTimer >= 6) {
            self->step -= 1;
            return;
        }
#endif
        break;
    case 3:
        prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
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
                prim->x2 = red_line_increment[uCoord];
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
            if (!uCoord) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                g_Dialogue.primIndex[0] = -1;
                prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
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
            prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
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
            if (!uCoord) {
                self->step = 1;
            }
        }
        break;
    case 6:
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
#ifdef VERSION_PSP
        g_CutsceneHasControl = 0;
        if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
            if (g_CastleFlags[TOP_FIGHT_CS_UNK1]) {
                g_Settings.D_8003CB04 |= 0x2000000;
            } else {
                g_Settings.D_8003CB04 |= 0x1000000;
                g_CastleFlags[TOP_FIGHT_CS_UNK2] = 1;
            }
            g_CastleFlags[TOP_FIGHT_CS_UNK1] ^= 1;
            SetStep(0);
        } else {
            g_CastleFlags[INVERTED_CASTLE_UNLOCKED] = 1;
            g_Settings.D_8003CB04 |= 0x800000;
            g_CastleFlags[TOP_FIGHT_CS_UNK1] = 0;
            DestroyEntity(self);
        }
#else
        g_CastleFlags[INVERTED_CASTLE_UNLOCKED] = 1;
        g_CutsceneHasControl = 0;
        g_Settings.D_8003CB04 |= 0x800000;
        DestroyEntity(self);
#endif
        break;
    }
}
