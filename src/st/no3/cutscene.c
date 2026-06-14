// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
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

#endif

static u8 D_80181A28[] = {0, 64};
#ifndef VERSION_PSP
static u8 D_80181A2C[2] = {0, 0};
#endif
static u16 D_80181A30[] = {0x2E0, 0x2E8};
static u16 D_80181A34[] = {0x100, 0x120};
static u16 D_80181A38[] = {0x1A1, 0x1A1};
static s16 D_80181A3C[] = {
    8,  19, 17, 49, 79, 38, 54, 29, 27, 51, 44, 33, 25, 10, 51, 31, 72, 47,
    19, 25, 77, 75, 23, 29, 18, 2,  27, 42, 80, 69, 50, 13, 42, 77, 6,  39,
    7,  72, 47, 27, 54, 34, 57, 20, 57, 29, 10, 53, 16, 27, 61, 23, 46, 11,
    73, 66, 61, 42, 1,  12, 27, 52, 65, 53, 8,  14, 77, 17, 52, 65, 41, 72,
};

#ifdef VERSION_PSP
static u8 D_pspeu_09296D28[] = {3, 2};
static u8 D_pspeu_09296D30[] = {3, 2};

// BSS
u32 g_CutsceneFlags; // Not static, used in EntityDeathCutsceneManager
static s32 g_SkipCutscene;
static Dialogue g_Dialogue;
static u8 D_pspeu_09299818;
static u8* D_pspeu_092997F8[8];
static u8 cutsceneUnk3Unknown[0x380];
static u16 D_pspeu_09299278[0x100];
static s32 g_CutsceneHasControl;
static u8 D_80181A2C[2]; // Can't get this one to go where it should
static s32 g_IsCutsceneDone;

#include "../cutscene_actor_name_psp.h"

#else
static const char* actor_names[] = {_S("Alucard"), _S("Death")};

// BSS
STATIC_PAD_BSS(0xC00);
s32 g_SkipCutscene;
Dialogue g_Dialogue;
u32 D_801D7D68[26];
u32 g_CutsceneFlags;
s32 g_IsCutsceneDone;

#define CUTSCENE_UNK1_NEXT_X 0x182
#include "../cutscene_unk1.h"

#include "../set_cutscene_script.h"
#endif

#define CUTSCENE_UNK3_RECT_X 384
#define CUTSCENE_UNK3_RECT_Y 256

#include "../cutscene_unk3.h"

#define CUTSCENE_UNK4_TPAGE 0x16
#define CUTSCENE_UNK4_V_OFFSET 0

#include "../cutscene_unk4.h"

#ifdef VERSION_PSP
#define CUTSCENE_UNK1_NEXT_X 0x180
#define CUTSCENE_UNK1_UNK17 2
#include "../cutscene_unk1.h"

#include "../set_cutscene_script.h"
#else
#include "../cutscene_actor_name.h"
#endif

#include "../set_cutscene_end.h"

#include "../cutscene_run.h"

#include "../cutscene_skip.h"

#ifdef VERSION_PSP
extern u8* OVL_EXPORT(cutscene_data);

extern s32 E_ID(BG_LIGHTNING);

extern u_long cutscene_alucard;
extern u_long D_893DD0C;
extern u_long D_893EA8C;
extern u_long D_893F80C;
extern u_long cutscene_death;
extern u_long D_894130C;
extern u_long D_894208C;
extern u_long D_8942E0C;
extern u_long D_894490C;
extern u_long D_894568C;
extern u_long D_8943B8C;
#else
#include "../cutscene_scale_avatar.h"

extern u8 OVL_EXPORT(cutscene_data)[];
#endif

void OVL_EXPORT(EntityCutscene)(Entity* self) {
#ifdef VERSION_PSP
    const int PRIM_COUNT = 4;
    const int TIMER_DELAY = 8;
#else
    const int PRIM_COUNT = 5;
    const int TIMER_DELAY = 6;
#endif

    s16 uCoord;
    s16 vCoord;
    s32 primIndex;
    Entity* entity;
#ifdef VERSION_PSP
    s32 sp40;
#endif
    RECT rect;
    s32 i;
    s32 j;
    u16 nextChar;
    u_long ptr;
    Primitive* prim;
    s32 var_s7;
#ifdef VERSION_PSP
    u8* var_s6;
    u32 var_s3;
    u8* var_s1;
#endif

#ifdef VERSION_PSP
    DisableAutoPowerOff();
#endif

    if (self->step) {
        if (g_IsCutsceneDone && !g_SkipCutscene &&
            ((g_GameClearFlag) || (g_Settings.D_8003CB04 & 4))) {
            CutsceneSkip(self);
        }
    }
    if (self->step && g_Dialogue.unk3C) {
        CutsceneRun();
    }
    switch (self->step) {
    case 0:
        entity = &g_Entities[192];
        CreateEntityFromCurrentEntity(E_ID(BG_LIGHTNING), entity);
#ifdef VERSION_PSP
        if ((!g_CutsceneHasControl && g_CastleFlags[IVE_BEEN_ROBBED]) ||
#else
        if (g_CastleFlags[IVE_BEEN_ROBBED] ||
#endif
            (g_PlayableCharacter != PLAYER_ALUCARD)) {
#ifdef VERSION_PSP
            g_PauseAllowed = true;
#endif
            DestroyEntity(self);
            entity->params = 0;
            return;
        }
        entity->params = 0x100;
        if (SetCutsceneScript(OVL_EXPORT(cutscene_data))) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            g_CutsceneFlags = 0;
            g_IsCutsceneDone = 0;
            g_SkipCutscene = 0;
            self->step++;
#ifdef VERSION_PSP
            if (!g_CastleFlags[IVE_BEEN_ROBBED] &&
                (g_PlayableCharacter == PLAYER_ALUCARD)) {
                g_CutsceneHasControl = 1;
            } else {
                g_CutsceneHasControl = 0;
            }
            g_CastleFlags[IVE_BEEN_ROBBED] = 1;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_MEET_DEATH, TIMEATTACK_SET_RECORD);
            g_Settings.D_8003CB04 |= 4;
#else
            g_CutsceneHasControl = 1;
#endif
        }
        break;
    case 1:
        nextChar = 0;
        // this is a huge While-loop! Don't miss it!
        while (1) {
#ifdef VERSION_PSP
            nextChar = *g_Dialogue.scriptCur++;
            sp40 = 0;
            if (PadReadPSP() & PAD_START) {
                g_Dialogue.nextCharTimer = 0;
            }
#endif
            if (g_Dialogue.nextCharTimer && !g_SkipCutscene) {
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
            {
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
                    if (g_Dialogue.nextCharY >= 5) {
                        g_Dialogue.nextCharY = 0;
                    }
#endif
                    CutsceneUnk4();
                    if (!(g_Dialogue.unk12 & 1)) {
#ifdef VERSION_PSP
                        if (g_Dialogue.nextCharY > 2)
#else
                        if (g_Dialogue.nextCharY >= 4)
#endif
                        {
                            g_Dialogue.unk12 |= 1;
                            g_Dialogue.portraitAnimTimer = 0;
                            self->step_s = 0;
                            self->step++;
#ifndef VERSION_PSP
                        } else {
                            continue;
#endif
                        }
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
                    for (i = 0; i < PRIM_COUNT; i++) {
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
                    prim = g_Dialogue.prim[PRIM_COUNT];
                    j = *g_Dialogue.scriptCur++;
                    var_s7 = j & 1;
                    uCoord = D_80181A28[var_s7];
                    vCoord = D_80181A2C[var_s7];
                    prim->clut = D_80181A30[i];
                    prim->tpage =
                        0x94; // Weird, this is 0x90 in other cutscenes
#ifdef VERSION_PSP
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 0x2F;
#else
                    if (j & 0x80) {
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
                    g_Dialogue.clutIndex = D_80181A38[i];
                    CutsceneUnk1();
                    CutsceneUnk4();
                    prim->priority = 0x1FE;
                    prim->drawMode = DRAW_DEFAULT;
#ifdef VERSION_PSP
                    DrawCutsceneActorName(
                        i, self, D_pspeu_09299278, D_pspeu_09296D28,
                        D_pspeu_09296D30, 2);
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
                    for (prim = g_Dialogue.prim[0], i = 0; i < PRIM_COUNT;
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
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    g_Dialogue.startX = *g_Dialogue.scriptCur++;
                    g_Dialogue.startY = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[PRIM_COUNT];
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
                case CSOP_SET_END:
                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
#ifdef VERSION_PSP
                    ptr += (u_long)OVL_EXPORT(cutscene_data);
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
                    ptr += (u_long)OVL_EXPORT(cutscene_data);
                    g_Dialogue.scriptCur += *(u8*)ptr << 2;
#else
                    ptr += (u16)0x100000;
                    g_Dialogue.scriptCur += *(u16*)ptr << 2;
#endif

                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur;
#ifdef VERSION_PSP
                    ptr += (u_long)OVL_EXPORT(cutscene_data);
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
                    ptr += (u_long)OVL_EXPORT(cutscene_data);
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
                            ptr = (u_long)&cutscene_alucard;
                            break;
                        case 1:
                            ptr = (u_long)&D_893DD0C;
                            break;
                        case 2:
                            ptr = (u_long)&D_893EA8C;
                            break;
                        case 3:
                            ptr = (u_long)&D_893F80C;
                            break;
                        case 4:
                            ptr = (u_long)&cutscene_death;
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
                        j = g_Dialogue.scriptCur++[0];
                        LoadTPage((u_long*)ptr, 1, 0, D_80181A34[j], 0x100,
                                  0x30, 0x48);
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
                    sp40 = 1;
#endif
                } // Close the switch

#ifdef VERSION_PSP
                if (sp40 != 0) {
                    break; // This breaks the big while-loop!
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
#endif
            }
            break;
        } // Close the giant while loop

#ifdef VERSION_PSP
        var_s6 = (u8*)&D_pspeu_092997F8;
#else
        if (nextChar == ' ') {
            g_Dialogue.nextCharX += 2;
            return;
        }
#endif

        rect.x = ((nextChar & 0xF) * 2) + 0x380;
        rect.y = ((s32)(nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        // Other cutscenes have + 0x180 here
        vCoord = (g_Dialogue.nextCharY * 0xC) + 0x100;
#ifdef VERSION_PSP
        StoreImage(&rect, (u_long*)var_s6);
        for (i = 0; i < 32; i++) {
            // swaps the upper and lower 4 bits of each member
            var_s6[i] = ((var_s6[i] & 0x0F) << 4) | ((var_s6[i] & 0xF0) >> 4);
        }
        while (true) {
            if (nextChar == 0x20) {
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
                var_s3 = (var_s1[0] << 0x18);
                var_s3 |= (var_s1[1] << 0x10);
                var_s3 |= (var_s1[2] << 0x08);
                var_s3 |= (var_s1[3]);
                var_s3 <<= 4;
                var_s1[0] = (var_s3 >> 0x18) & 0xFF;
                var_s1[1] = (var_s3 >> 0x10) & 0xFF;
                var_s1[2] = (var_s3 >> 0x08) & 0xFF;
                var_s1[3] = (var_s3) & 0xFF;
            }
        }
        for (i = 0, var_s7 = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if ((var_s6[j / 2 + (i << 3) / 2]) & (0xF0 >> ((j & 1) * 4))) {
                    if (j > var_s7) {
                        var_s7 = j;
                    }
                };
            }
        }
        var_s7 += 2;
        for (i = 0; i < 32; i++) {
            // swaps the upper and lower 4 bits of each member
            var_s6[i] = ((var_s6[i] & 0x0F) << 4) | ((var_s6[i] & 0xF0) >> 4);
        }
        rect.w = var_s7;
        var_s6 = (u8*)&D_pspeu_092997F8;
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
                  vCoord, 0xE0, 8);
        if (nextChar != 0x20) {
            g_Dialogue.nextCharX += rect.w;
        } else {
            g_Dialogue.nextCharX += 4;
        }
        // This seems like a mistake.
        if (((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) < 0x70) {
        };
        D_pspeu_09299818 = nextChar;
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
        for (i = 0; i < PRIM_COUNT; i++) {
            if (i == ptr) {
                continue;
            }
            prim = g_Dialogue.prim[i];
            prim->y0 -= 2;
        }
        g_Dialogue.portraitAnimTimer++;
#else
        ScaleCutsceneAvatar(2);
#endif
        if (g_Dialogue.portraitAnimTimer >= TIMER_DELAY) {
            self->step--;
        }
        break;
    case 3:
        prim = g_Dialogue.prim[PRIM_COUNT];
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
        prim = g_Dialogue.prim[PRIM_COUNT];
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
                prim->x2 = D_80181A3C[uCoord];
                prim->x3 = 0xF70;
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
                prim = g_Dialogue.prim[PRIM_COUNT];
                prim = prim->next;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                self->step_s++;
            }
            break;
        case 2:
            uCoord = 0;
            prim = g_Dialogue.prim[PRIM_COUNT];
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
        prim = g_Dialogue.prim[PRIM_COUNT];
        prim = prim->next;
        g_Dialogue.portraitAnimTimer--;
        if (g_Dialogue.portraitAnimTimer >= 0xC) {
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
#ifdef VERSION_PSP
        DestroyEntity(self);
#endif
        g_CastleFlags[IVE_BEEN_ROBBED] = 1;
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_MEET_DEATH, TIMEATTACK_SET_RECORD);
#ifndef VERSION_PSP
        g_CutsceneHasControl = 0;
#endif
        g_Settings.D_8003CB04 |= 4;
#ifndef VERSION_PSP
        DestroyEntity(self);
#endif
        break;
    }
}
