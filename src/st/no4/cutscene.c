// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"
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

// cutscene_script_box.h
#define CUTSCENE_UNK3_RECT_X 0
#define CUTSCENE_UNK3_RECT_H 12
#define CUTSCENE_UNK4_TPAGE 16
#define CUTSCENE_UNK4_V 12

extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[]; // Defined by e_init

#ifdef VERSION_PSP
extern u8* cutscene_data_ferryman_left;  // Defined by st_init
extern u8* cutscene_data_ferryman_right; // Defined by st_init

extern u32 D_893CF8C;
extern u32 D_893DD0C;
extern u32 D_893EA8C;
extern u32 D_893F80C;
extern u32 D_894058C;
extern u32 D_894130C;
extern u32 gfx_portrait_ferryman;
extern u32 D_8942E0C;
extern u32 D_8943B8C;
extern u32 D_894490C;
extern u32 D_894568C;

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

static u8 actor_name_len_index[] = {8, 0, 0, 0, 0, 0, 0, 0};
static u8 actor_name_index[] = {8, 0, 0, 0, 0, 0, 0, 0};

// bss
extern u32 g_CutsceneFlags; // Used by EntityFerrymanController
extern bool skip_cutscene;
extern Dialogue3 g_Dialogue;
extern u8 buffer_2;
extern u8 buffer_1[];
extern u8 cutsceneUnk3Unknown[0x380];
extern u16 actor_names[];
extern bool dialogue_started;
extern u8* cutscene_script_ptr; // cutscene_script?

// psp only, can probably be added to cutscene_actor_name.h
#include "../../get_lang.h"

#define CUTSCENE_UNK1_NEXT_X 0
#define CUTSCENE_UNK1_UNK17 2
#define NUM_CUTSCENE_PRIM 7

// These three are reversed in order from psx
#include "../cutscene_actor_name.h"
#include "../cutscene_script_box.h"
#include "cutscene_script_text.h"
#else
extern u8 OVL_EXPORT(cutscene_script)[];
extern u8 cutscene_data_ferryman_left[];
extern u8 cutscene_data_ferryman_right[];

static const char* actor_names[] = {_S("Ferryman")};

// bss
static bool skip_cutscene;
static Dialogue3 g_Dialogue;
STATIC_PAD_BSS(88);
u32 g_CutsceneFlags; // Used by EntityFerrymanController
static bool dialogue_started;

#define CUTSCENE_UNK1_NEXT_X 2
#define CUTSCENE_UNK1_UNK17 8
#define CUTSCENE_UNK4_HAS_ARGS
#define NUM_CUTSCENE_PRIM 5
#define DRAW_NAME_ACTOR_INDEX 0
#define DRAW_NAME_PRIM_Y0 30

// These three are reversed in order from psp
#include "cutscene_script_text.h"
#include "../cutscene_script_box.h"
#include "../cutscene_actor_name.h"
#endif

// Unused by pspeu and deadstripped
#include "../cutscene_scale_avatar.h"

void OVL_EXPORT(EntityCutscene)(Entity* self) {
    Primitive* prim;
    s32 i, j;
    s16 uCoord, vCoord;
    u16 nextByte;
#ifdef VERSION_PSP
    s32 charWidth;
    u8* buffer1;
    u8* buffer2;
    u32 buffer3;
    bool endLoopFlag;
#endif
    RECT rect;
    s32 ptr;

#ifdef VERSION_PSP
    DisableAutoPowerOff();
#endif

    // This is a big if condition, spans 4 lines
    if ((self->step && dialogue_started && !skip_cutscene) &&
        ((g_Settings.D_8003CB04 & 1 << (self->params + 5)) ||
         g_GameClearFlag) &&
        g_pads[0].tapped & PAD_START) {

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

    switch (self->step) {
    case DIALOGUE_INIT:
        if (self->params) {
            if (g_CastleFlags[MET_FERRYMAN_1]) {
                DestroyEntity(self);
                g_CutsceneFlags = 0x80;
                return;
            }
            nextByte = SetCutsceneScript(cutscene_data_ferryman_left);
#ifdef VERSION_PSP
            cutscene_script_ptr = cutscene_data_ferryman_left;
#endif
        } else if (g_CastleFlags[MET_FERRYMAN_2]) {
            DestroyEntity(self);
            g_CutsceneFlags = 0x80;
            return;
        } else {
            nextByte = SetCutsceneScript(cutscene_data_ferryman_right);
#ifdef VERSION_PSP
            cutscene_script_ptr = cutscene_data_ferryman_right;
#endif
        }
        if (nextByte) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            g_CutsceneFlags = CUTSCENE_FLAG_NONE;
            dialogue_started = false;
            skip_cutscene = false;
            self->step++;
        }
        break;
    case DIALOGUE_RUN:
        nextByte = 0;
        // us: loop breaks on on line 564 and closes on line 565
        // pspeu: loop breaks on lines 539 and 558 and closes on line 559
        while (true) {
#ifdef VERSION_PSP
            nextByte = *g_Dialogue.scriptCur++;
            endLoopFlag = false;
            if (PadReadPSP() & PAD_START) {
                g_Dialogue.nextCharTimer = 0;
            }
            if (g_Dialogue.nextCharTimer && !skip_cutscene) {
                g_Dialogue.nextCharTimer--;
                g_Dialogue.scriptCur--;
                return;
            }
            if (!(nextByte & 0x80)) {
#else
            if (g_Dialogue.nextCharTimer && !skip_cutscene) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextByte = *g_Dialogue.scriptCur++;
#endif
                // This switch is closed on line 560 for us and 534 for pspeu
                switch (nextByte) {
                case CSOP_END_CUTSCENE:
                    self->step = DIALOGUE_END;
                    return;
                case CSOP_LINE_BREAK:
                    if (skip_cutscene) {
                        continue;
                    }
                    g_Dialogue.nextCharX = CUTSCENE_UNK1_NEXT_X;
#ifdef VERSION_PSP
                    if (!(g_Dialogue.unk12 & 1)) {
                        g_Dialogue.nextLineY += CS_LINE_SPACING;
                    }
                    g_Dialogue.nextCharY++;
                    g_Dialogue.nextCharY &= CS_LINE_MAX;
                    CutsceneUnk4();
                    if (!(g_Dialogue.unk12 & 1)) {
                        if (g_Dialogue.nextCharY > CS_LINE_MAX - 1) {
                            g_Dialogue.unk12 |= 1;
                            g_Dialogue.portraitAnimTimer = 0;
                            self->step_s = DIALOG_BOX_INIT;
                            self->step++;
                        }
                    } else {
                        g_Dialogue.portraitAnimTimer = 0;
                        self->step_s = DIALOG_BOX_INIT;
                        self->step++;
                    }
#else
                g_Dialogue.nextCharY++;
                CutsceneUnk4(((g_Dialogue.nextCharY * 3) << 18) >> 16);
#endif
                    return;
                case CSOP_SET_SPEED:
#ifdef VERSION_US
                    g_Dialogue.unk17 =
#endif
                        *g_Dialogue.scriptCur++;
                    continue;
                case CSOP_SET_WAIT:
                    g_Dialogue.nextCharTimer = *g_Dialogue.scriptCur++;
                    if (skip_cutscene) {
                        continue;
                    }
                case CSOP_HIDE_DIALOG:
                    return;
                case CSOP_SET_PORTRAIT:
                    if (skip_cutscene) {
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    i = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
                    j = *g_Dialogue.scriptCur++;
                    uCoord = 0;
                    vCoord = 0;
                    prim->clut = 0x220;
                    prim->tpage = 144;
#ifdef VERSION_US
                    if (j & 0x80) {
                        prim->u0 = prim->u2 = 47;
                        prim->u1 = prim->u3 = 0;
                    } else {
                        prim->u0 = prim->u2 = 0;
                        prim->u1 = prim->u3 = 47;
                    }
#else
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 47;
#endif
                    prim->v0 = prim->v1 = 0;
                    prim->v2 = prim->v3 = 72;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 30;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 = 60;
                    CutsceneUnk1();

#ifdef VERSION_PSP
                    CutsceneUnk4();
#else
                CutsceneUnk4(0);
#endif

                    prim->priority = 510;
                    prim->drawMode = DRAW_DEFAULT;

                    DrawCutsceneActorName(
#ifdef VERSION_PSP
                        i, self, actor_names, actor_name_len_index,
                        actor_name_index, 1
#else
                    i, self
#endif
                    );

                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = DIALOGUE_START_TEXT;
                    return;
                case CSOP_NEXT_DIALOG:
                    if (skip_cutscene) {
                        continue;
                    }
                    prim = g_Dialogue.prim[0];
#ifdef VERSION_PSP
                    for (i = 0; i < LEN(g_Dialogue.prim) - 1; i++) {
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                    }
#else
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                prim->drawMode = DRAW_HIDE;
#endif
                    g_api.FreePrimitives(g_Dialogue.primIndex[1]);
                    g_Dialogue.primIndex[1] = -1;
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = DIALOGUE_UNLOAD_PORTRAIT;
                    return;
                case CSOP_SET_POS:
                    g_Dialogue.scriptCur += 2;
                    if (skip_cutscene) {
                        continue;
                    }
                    prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
                    prim = prim->next;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 = 24;
                    prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                    prim = prim->next;
                    prim->y0 = 23;
                    prim->u0 = 0;
                    prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
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
                        g_Dialogue.scriptCur += 2;
                        continue;
                    }
                    nextByte = *g_Dialogue.scriptCur++;
                    nextByte <<= 4;
                    nextByte |= *g_Dialogue.scriptCur++;
                    g_api.PlaySfx(nextByte);
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
                    continue;
                case CSOP_SCRIPT_UNKNOWN_13:
                    continue;
                case CSOP_SCRIPT_UNKNOWN_14:
                    continue;
                case CSOP_SCRIPT_UNKNOWN_15:
                    continue;
                case CSOP_WAIT_FOR_FLAG:
                    // TODO: Does & 1 mean Alucard ready?
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
                case CSOP_LOAD_PORTRAIT:
                    if (skip_cutscene) {
                        g_Dialogue.scriptCur += 5;
                    } else {
                        ptr = (u32)*g_Dialogue.scriptCur++;
                        ptr <<= 4;
                        ptr |= (u32)*g_Dialogue.scriptCur++;
                        ptr <<= 4;
                        ptr |= (u32)*g_Dialogue.scriptCur++;
                        ptr <<= 4;
                        ptr |= (u32)*g_Dialogue.scriptCur++;
#ifdef VERSION_PSP
                        switch (ptr) {
                        case 0:
                            ptr = (u32)&D_893CF8C;
                            break;
                        case 1:
                            ptr = (u32)&D_893DD0C;
                            break;
                        case 2:
                            ptr = (u32)&D_893EA8C;
                            break;
                        case 3:
                            ptr = (u32)&D_893F80C;
                            break;
                        case 4:
                            ptr = (u32)&D_894058C;
                            break;
                        case 5:
                            ptr = (u32)&D_894130C;
                            break;
                        case 6:
                            ptr = (u32)&gfx_portrait_ferryman;
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
                        // j here is used as a parameter for LoadTPage in other
                        // overlays, but is unused in no4
                        j = *g_Dialogue.scriptCur++;
                        LoadTPage((u_long*)ptr, 1, 0, 0, 256, 48, 72);
                    }
                    continue;
                case CSOP_SCRIPT_UNKNOWN_20:
                    nextByte = *g_Dialogue.scriptCur++;
                    nextByte <<= 4;
                    nextByte |= *g_Dialogue.scriptCur++;
                    g_api.PlaySfx(nextByte);
                    continue;
                case CSOP_SCRIPT_UNKNOWN_21:
                case CSOP_SCRIPT_UNKNOWN_22:
                case CSOP_SCRIPT_UNKNOWN_23:
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
                    endLoopFlag = true;
                } // This closes the CSOP switch for psp
                if (endLoopFlag) {
                    break; // This breaks the big while loop for psp
                }
                continue;
            } else {
                if (skip_cutscene) {
                    g_Dialogue.scriptCur++;
                    continue;
                }
                if (167 <= nextByte && nextByte < 173) {
                    nextByte = nextByte + 39;
                } else if (nextByte == 166) {
                    nextByte = 204;
                } else if (nextByte == 221) {
                    nextByte = 205;
                } else {
                    nextByte = nextByte - 17;
                }
                g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            }
            break; // This breaks the big while loop for psp
        } // This closes the big while loop for psp

        buffer1 = buffer_1;
#else
            } // This closes the CSOP switch for psx
            break; // This breaks the big while loop for psx
        } // This closes the big while loop for psx
        if (nextByte == ASCII_SPACE) {
            g_Dialogue.nextCharX += 2;
            return;
        }
#endif
        rect.x = ((nextByte & 0xF) * 2) + 896;
        rect.y = ((nextByte & 0xF0) >> 1) + 240;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 12) + 384;
#ifdef VERSION_PSP
        StoreImage(&rect, (u_long*)buffer1);
        for (i = 0; i < 32; i++) {
            // Swaps the upper and lower 4 bits of each member
            buffer1[i] =
                ((buffer1[i] & 0x0F) << 4) | ((buffer1[i] & 0xF0) >> 4);
        }
        while (true) {
            if (nextByte == ASCII_SPACE) {
                break;
            }
            for (i = 0; i < 8; i++) {
                if (buffer1[(i << 3) / 2] & 0xF0) {
                    break;
                }
            }
            if (i != 8) {
                break;
            }
            for (i = 0; i < 8; i++) {
                // Pack the bytes
                buffer2 = &buffer1[(i << 3) / 2];
                buffer3 = (buffer2[0] << 0x18);
                buffer3 |= (buffer2[1] << 0x10);
                buffer3 |= (buffer2[2] << 0x08);
                buffer3 |= (buffer2[3]);
                buffer3 *= CS_LINE_SPACING;
                // Unack the bytes
                buffer2[0] = (buffer3 >> 0x18) & 0xFF;
                buffer2[1] = (buffer3 >> 0x10) & 0xFF;
                buffer2[2] = (buffer3 >> 0x08) & 0xFF;
                buffer2[3] = (buffer3) & 0xFF;
            }
        }
        for (i = 0, charWidth = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if ((buffer1[j / 2 + (i << 3) / 2]) & (0xF0 >> ((j & 1) * 4))) {
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
            buffer2 = &cutsceneUnk3Unknown
                          [((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) +
                           (i * 112)];
            if ((g_Dialogue.nextCharX - g_Dialogue.nextLineX) & 1) {
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
        LoadTPage((u_long*)cutsceneUnk3Unknown, 0, 0, g_Dialogue.nextLineX,
                  vCoord, 224, 8);
        if (nextByte != ASCII_SPACE) {
            g_Dialogue.nextCharX += rect.w;
        } else {
            g_Dialogue.nextCharX += 4;
        }
        // This seems like a mistake.
        if (((g_Dialogue.nextCharX - g_Dialogue.nextLineX) / 2) < 112) {
        };
        buffer_2 = nextByte;
#else
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
#endif
        break;
#ifdef VERSION_PSP
    case DIALOGUE_LOAD_PORTRAIT:
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
        if (g_Dialogue.portraitAnimTimer >= 8) {
            self->step--;
        }
        break;
#endif
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
        if (prim->x1 >= 58) {
            prim->x1 = prim->x3 = 57;
        }
        g_Dialogue.portraitAnimTimer--;
        if (!g_Dialogue.portraitAnimTimer) {
            self->step = DIALOGUE_RUN;
        }
        break;
    case DIALOGUE_OPEN_DIALOG_BOX:
        dialogue_started = true;
        prim = g_Dialogue.prim[LEN(g_Dialogue.prim) - 1];
        prim = prim->next;
        g_Dialogue.portraitAnimTimer--;
        if (g_Dialogue.portraitAnimTimer >= 12) {
            prim = prim->next;
            prim->u0 += 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                prim->u0++;
            }
        } else {
            if (!g_Dialogue.portraitAnimTimer) {
                self->step = DIALOGUE_RUN;
            }
            prim->y2 = (prim->y3 += 6);
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
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
        if (self->params) {
            g_CastleFlags[MET_FERRYMAN_1] = true;
        } else {
            g_CastleFlags[MET_FERRYMAN_2] = true;
        }
        g_Settings.D_8003CB04 |= (1 << (self->params + 5));
        DestroyEntity(self);
        break;
    }
}
