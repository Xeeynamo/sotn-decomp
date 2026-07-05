// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"
#include <cutscene.h>

extern u32 D_801BC3E8;
extern s32 D_801D6B00;
extern Dialogue OVL_EXPORT(Dialogue);
extern s32 OVL_EXPORT(SkipCutscene);

// BSS
static u16 D_801BB0F8[0x30][0x30];

// DATA
static u8 D_80180824[2] = {0x00, 0x40};
static u8 D_80180828[2] = {0x00, 0x00};
static u16 D_8018082C[] = {0x240, 0x248, 0x250};
static u16 D_80180834[] = {0x00, 0x20};
static u16 D_80180838[] = {0x1A1, 0x1A1, 0x1A1};
static u16 D_80180840[] = {
    0x08, 0x13, 0x11, 0x31, 0x4F, 0x26, 0x36, 0x1D, 0x1B, 0x33, 0x2C, 0x21,
    0x19, 0x0A, 0x33, 0x1F, 0x48, 0x2F, 0x13, 0x19, 0x4D, 0x4B, 0x17, 0x1D,
    0x12, 0x02, 0x1B, 0x2A, 0x50, 0x45, 0x32, 0x0D, 0x2A, 0x4D, 0x06, 0x27,
    0x07, 0x48, 0x2F, 0x1B, 0x36, 0x22, 0x39, 0x14, 0x39, 0x1D, 0x0A, 0x35,
    0x10, 0x1B, 0x3D, 0x17, 0x2E, 0x0B, 0x49, 0x42, 0x3D, 0x2A, 0x01, 0x0C,
    0x1B, 0x34, 0x41, 0x35, 0x08, 0x0E, 0x4D, 0x11, 0x34, 0x41, 0x29, 0x48,
};

static const char* actor_names[] = {_S("Alucard"), _S("Maria"), _S("Richter")};

#include "../cutscene_unk1.h"

u8 SetCutsceneScript(u8* script) {
    Primitive* prim;

    OVL_EXPORT(Dialogue).primIndex[2] = g_api.AllocPrimitives(PRIM_SPRT, 7);
    if (OVL_EXPORT(Dialogue).primIndex[2] != -1) {
        OVL_EXPORT(Dialogue).scriptCur = script;
        OVL_EXPORT(Dialogue).unk3C = 0;
        OVL_EXPORT(Dialogue).primIndex[1] = -1;
        OVL_EXPORT(Dialogue).primIndex[0] = -1;
        CutsceneUnk1();

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
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
        prim->b0 = prim->b1 = 0x7F;
        prim->x0 = prim->x2 = 4;
        prim->x1 = prim->x3 = 0xF8;
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_HIDE;

        prim = prim->next;
        prim->type = PRIM_TILE;
        prim->r0 = prim->g0 = prim->b0 = 0x10;
        prim->x0 = 3;
        prim->y0 = 0x2F;
        prim->v0 = 0x4A;
        prim->priority = 0x1FC;
        prim->drawMode = DRAW_HIDE;
        return 1;
    }
    OVL_EXPORT(Dialogue).primIndex[2] = 0;
    return 0;
}

#include "../cutscene_unk3.h"

#include "../cutscene_unk4.h"

#include "../cutscene_actor_name.h"

#include "../set_cutscene_end.h"

// n.b.! unlike the stage version of this function, a `self`
// parameter is used to store the substep instead of
// `g_CurrentEntity`., entity
static void ScaleCutsceneAvatar(u8 ySteps, Entity* self) {
    const int PrimCount = 5;
    s32 primIndex = OVL_EXPORT(Dialogue).nextCharY + 1;
    Primitive* prim;
    s32 i;

    while (primIndex >= PrimCount) {
        primIndex -= PrimCount;
    }

    if (self->step_s == 0) {
        prim = OVL_EXPORT(Dialogue).prim[primIndex];
        prim->v0 = ySteps + prim->v0;
        prim->v1 -= ySteps;
        if (prim->v1 == 0) {
            self->step_s++;
            prim->drawMode = DRAW_HIDE;
        }
    }

    for (i = 0; i < PrimCount; i++) {
        if (i != primIndex) {
            prim = OVL_EXPORT(Dialogue).prim[i];
            prim->y0 -= ySteps;
        }
    }
    OVL_EXPORT(Dialogue).portraitAnimTimer++;
}

void OVL_EXPORT(EntityCutscene)(Entity* self) {
    s16 x, y;
    RECT* rect;
    Primitive* prim;
    u16 nextChar;
    s32 i;
    s32 nextChar2;
    s32 var_s7;
    u32 ptr;
    switch (self->step) {
    case 0:
        if (SetCutsceneScript(OVL_EXPORT(cutscene_endings))) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = OVL_EXPORT(Dialogue).primIndex[2];
            D_801BC3E8 = 0;
            D_801D6B00 = 0;
            OVL_EXPORT(SkipCutscene) = 0;
            g_CutsceneHasControl = 1;
            self->step++;
        }
        break;

    case 1:
        while (true) {
            if (OVL_EXPORT(Dialogue).nextCharTimer &&
                !OVL_EXPORT(SkipCutscene)) {
                OVL_EXPORT(Dialogue).nextCharTimer--;
                return;
            }
            nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
            switch (nextChar) {
            case CSOP_END_CUTSCENE:
                self->step = 7;
                return;
            case CSOP_LINE_BREAK:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                OVL_EXPORT(Dialogue).nextCharX = OVL_EXPORT(Dialogue).nextLineX;
                if (!(OVL_EXPORT(Dialogue).unk12 & 1)) {
                    OVL_EXPORT(Dialogue).nextLineY += 0xC;
                }
                OVL_EXPORT(Dialogue).nextCharY++;
                if (OVL_EXPORT(Dialogue).nextCharY >= 5) {
                    OVL_EXPORT(Dialogue).nextCharY = 0;
                }
                CutsceneUnk4();
                if (!(OVL_EXPORT(Dialogue).unk12 & 1)) {
                    if (OVL_EXPORT(Dialogue).nextCharY > 3) {
                        OVL_EXPORT(Dialogue).unk12 |= 1;
                        OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
                        self->step_s = 0;
                        self->step++;
                    } else {
                        continue;
                    }
                } else {
                    OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
                    self->step_s = 0;
                    self->step++;
                }
                return;
            case CSOP_SET_SPEED:
                OVL_EXPORT(Dialogue).unk17 = *OVL_EXPORT(Dialogue).scriptCur++;
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
                for (i = 0; i < 5; i++) {
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
                prim = OVL_EXPORT(Dialogue).prim[5];
                nextChar2 = *OVL_EXPORT(Dialogue).scriptCur++;
                var_s7 = nextChar2 & 1;
                x = D_80180824[var_s7];
                y = D_80180828[var_s7];
                prim->clut = D_8018082C[i];
                prim->tpage = 0x90;
                if (nextChar2 & 0x80) {
                    prim->u0 = prim->u2 = x + 0x2F;
                    prim->u1 = prim->u3 = x;
                } else {
                    prim->u0 = prim->u2 = x;
                    prim->u1 = prim->u3 = x + 0x2F;
                }
                prim->v0 = prim->v1 = y;
                prim->v2 = prim->v3 = y + 0x48;
                prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                    OVL_EXPORT(Dialogue).startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    OVL_EXPORT(Dialogue).startY + 0x24;
                OVL_EXPORT(Dialogue).clutIndex = D_80180838[i];
                CutsceneUnk1();
                CutsceneUnk4();
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                DrawCutsceneActorName(i, self);
                OVL_EXPORT(Dialogue).portraitAnimTimer = 6;
                self->step = 3;
                return;
            case CSOP_NEXT_DIALOG:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                prim = OVL_EXPORT(Dialogue).prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[1]);
                OVL_EXPORT(Dialogue).primIndex[1] = -1;
                OVL_EXPORT(Dialogue).portraitAnimTimer = 6;
                self->step = 4;
                return;
            case CSOP_SET_POS:
                if (OVL_EXPORT(SkipCutscene)) {
                    OVL_EXPORT(Dialogue).scriptCur += 2;
                    continue;
                }
                OVL_EXPORT(Dialogue).startX = *OVL_EXPORT(Dialogue).scriptCur++;
                OVL_EXPORT(Dialogue).startY = *OVL_EXPORT(Dialogue).scriptCur++;
                prim = OVL_EXPORT(Dialogue).prim[5];
                prim = prim->next;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    OVL_EXPORT(Dialogue).startY;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->y0 = OVL_EXPORT(Dialogue).startY - 1;
                prim->u0 = 0;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                OVL_EXPORT(Dialogue).portraitAnimTimer = 24;
                self->step = 5;
                self->step_s = 0;
                return;
            case CSOP_CLOSE_DIALOG:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                OVL_EXPORT(Dialogue).portraitAnimTimer = 24;
                self->step = 6;
                return;
            case CSOP_PLAY_SOUND:
                if (OVL_EXPORT(SkipCutscene)) {
                    OVL_EXPORT(Dialogue).scriptCur += 2;
                    continue;
                }
                nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
                nextChar <<= 4;
                nextChar |= *OVL_EXPORT(Dialogue).scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_WAIT_FOR_SOUND:
                if (OVL_EXPORT(SkipCutscene) ||
                    g_api.func_80131F68() != false) {
                    continue;
                }
                OVL_EXPORT(Dialogue).scriptCur--;
                return;
            case CSOP_SCRIPT_UNKNOWN_11:
                if (OVL_EXPORT(SkipCutscene) || g_api.func_80131F68() != true) {
                    continue;
                }
                OVL_EXPORT(Dialogue).scriptCur--;
                return;
            case CSOP_SET_END:
                ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
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
                OVL_EXPORT(Dialogue).scriptCur += *((u8*)ptr + 0x100000) * 4;
                ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur;
                OVL_EXPORT(Dialogue).scriptCur = (u8*)(ptr + 0x100000);
                continue;
            case CSOP_SCRIPT_UNKNOWN_15:
                ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur;
                OVL_EXPORT(Dialogue).scriptCur = (u8*)(ptr + 0x100000);
                continue;
            case CSOP_WAIT_FOR_FLAG:
                if (!((D_801BC3E8 >> *OVL_EXPORT(Dialogue).scriptCur) & 1)) {
                    OVL_EXPORT(Dialogue).scriptCur--;
                    return;
                }
                D_801BC3E8 &= ~(1 << *OVL_EXPORT(Dialogue).scriptCur);
                OVL_EXPORT(Dialogue).scriptCur++;
                continue;
            case CSOP_SET_FLAG:
                D_801BC3E8 |= 1 << *OVL_EXPORT(Dialogue).scriptCur++;
                continue;
            case CSOP_SCRIPT_UNKNOWN_18:
                OVL_EXPORT(Dialogue).unk3C = 0;
                continue;
            case CSOP_LOAD_PORTRAIT:
                if (OVL_EXPORT(SkipCutscene)) {
                    OVL_EXPORT(Dialogue).scriptCur += 5;
                    continue;
                }
                ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr += 0x100000;
                nextChar2 = *OVL_EXPORT(Dialogue).scriptCur++;
                LoadTPage((u_long*)ptr, 1, 0, D_80180834[nextChar2], 0x100,
                          0x30, 0x48);
                continue;
            case CSOP_SCRIPT_UNKNOWN_20:
                nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
                nextChar <<= 4;
                nextChar |= *OVL_EXPORT(Dialogue).scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_SCRIPT_UNKNOWN_21:
                D_801BC3E8 = 0;
                OVL_EXPORT(SkipCutscene) = 0;
                D_801D6B00 = 0;
                continue;
            case CSOP_SCRIPT_UNKNOWN_22:
                D_801BC3E8 &= ~(1 << *OVL_EXPORT(Dialogue).scriptCur++);
                continue;
            case CSOP_SCRIPT_UNKNOWN_23:
                return;
            case CSOP_WAIT_FOR_FLAG_RESET:
                if (!((D_801BC3E8 >> *OVL_EXPORT(Dialogue).scriptCur) & 1)) {
                    OVL_EXPORT(Dialogue).scriptCur--;
                    return;
                }
                OVL_EXPORT(Dialogue).scriptCur++;
                continue;
            default:
                if (OVL_EXPORT(SkipCutscene)) {
                    OVL_EXPORT(Dialogue).scriptCur++;
                    continue;
                }
                OVL_EXPORT(Dialogue).nextCharTimer = OVL_EXPORT(Dialogue).unk17;
            }
            break;
        }

        if (nextChar == ' ') {
            OVL_EXPORT(Dialogue).nextCharX += 2;
            break;
        }
        rect->x = ((nextChar & 0x0F) << 1) + 0x380;
        rect->y = ((nextChar & 0xF0) >> 1) + 0xF0;
        rect->w = 2;
        rect->h = 8;
        y = OVL_EXPORT(Dialogue).nextCharY * 12 + 0x180;
        MoveImage(rect, OVL_EXPORT(Dialogue).nextCharX, y);
        OVL_EXPORT(Dialogue).nextCharX += 2;
        break;
    case 2:
        ScaleCutsceneAvatar(2, self);
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 6) {
            self->step--;
        }
        break;

    case 3:
        prim = OVL_EXPORT(Dialogue).prim[5];
        prim->x0 = prim->x2 -= 4;
        prim->x1 = prim->x3 += 4;
        prim->y0 = prim->y1 -= 6;
        prim->y2 = prim->y3 += 6;
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (!OVL_EXPORT(Dialogue).portraitAnimTimer) {
            self->step = 1;
            prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[1]];
            while (prim != NULL) {
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
        }
        break;

    case 4:
        prim = OVL_EXPORT(Dialogue).prim[5];
        prim->x0 = prim->x2 += 4;
        prim->x1 = prim->x3 -= 4;
        prim->y0 = prim->y1 += 6;
        prim->y2 = prim->y3 -= 6;
        if (prim->x1 >= (OVL_EXPORT(Dialogue).startX - 2)) {
            prim->x1 = prim->x3 = OVL_EXPORT(Dialogue).startX - 3;
        }
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (!OVL_EXPORT(Dialogue).portraitAnimTimer) {
            self->step = 1;
        }
        break;

    case 5:
        D_801D6B00 = 1;
        prim = OVL_EXPORT(Dialogue).prim[5];
        prim = prim->next;
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 12) {
            prim = prim->next;
            prim->u0 += 20;
            if (OVL_EXPORT(Dialogue).portraitAnimTimer & 1) {
                prim->u0++;
            }
        } else {
            if (!OVL_EXPORT(Dialogue).portraitAnimTimer) {
                self->step = 1;
            }
            prim->y2 = prim->y3 += 6;
        }
        break;

    case 6:
        prim = OVL_EXPORT(Dialogue).prim[5];
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
                self->step = 1;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->y2 = prim->y3 -= 6;
            }
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 7:
        g_CutsceneHasControl = 0;
        break;
    }
}

u8 func_801B76F0(u8* msg) {
    const int PRIM = -5;
    Primitive* prim;
    s16 i;
    s16 temp_v0;

    OVL_EXPORT(Dialogue).primIndex[PRIM] =
        g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (OVL_EXPORT(Dialogue).primIndex[PRIM] != -1) {
        OVL_EXPORT(Dialogue).scriptCur = msg;
        OVL_EXPORT(Dialogue).startY = OVL_EXPORT(Dialogue).nextCharX = 0x200;
        OVL_EXPORT(Dialogue).startY += 0xB;
        OVL_EXPORT(Dialogue).nextLineX = 0;
        OVL_EXPORT(Dialogue).nextCharY = 0;
        OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
        OVL_EXPORT(Dialogue).unk12 = 0;
        OVL_EXPORT(Dialogue).clutIndex = 0;
        OVL_EXPORT(Dialogue).prim[0] =
            &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[PRIM]];
        prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[PRIM]];
        for (i = 0; i < 0x20; i++) {
            temp_v0 = i & 1;
            if (temp_v0) {
                prim->tpage = 9;
                prim->x0 = 0xF8;
            } else {
                prim->tpage = 8;
                prim->x0 = 0x18;
            }
            temp_v0 = i >> 1;
            prim->u0 = 0;
            prim->v0 = temp_v0 * 0x10;
            prim->u1 = 0xF0;
            prim->v1 = 0x10;
            prim->y0 = temp_v0 * 0x13 + 0xF0;
            prim->clut = PAL_UNK_1A1;
            prim->x1 = 0;
            prim->priority = 3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }

        return 1;
    }
    OVL_EXPORT(Dialogue).primIndex[PRIM] = 0;
    return 0;
}

void func_801B786C(s16 nextCharY) {
    RECT rect;

    rect.x = 0x200;
    rect.y = nextCharY * 0x10;
    rect.w = 0x80;
    rect.h = 0x10;
    ClearImage(&rect, 0, 0, 0);
}

u16* func_801B78BC(char ch) {
    u16 jCh;
#ifndef VERSION_PC

    if (ch >= 'a') {
        jCh = ('ａ' - 'a') + ch;
    } else if (ch >= 'A') {
        jCh = ('Ａ' - 'A') + ch;
    } else if (ch == ',') {
        jCh = '，';
    } else if (ch == '/') {
        jCh = '／';
    } else if (ch == '.') {
        jCh = '．';
    } else if (ch == '-') {
        jCh = '−';
    } else if (ch == '(') {
        jCh = '（';
    } else if (ch == ')') {
        jCh = '）';
    } else if (ch == '\'') {
        jCh = '’';
    } else if (ch == '&') {
        jCh = '＆';
    } else if (ch == '"') {
        jCh = '”';
    } else if (ch == ' ') {
        return NULL;
    } else {
        jCh = ('Ａ' - 'A') + ch;
        if (ch >= 'a') {
            ++jCh;
        }
    }
#else
    jCh = 'A';
#endif

    return g_api.func_80106A28(jCh, 0);
}

s32 func_801B79D4(Entity* entity) {
    Primitive* prim;
    int bitDepth;
    u16 nextChar;
    u16 glyphIndex;
    u16* glyph;
    u16 y;
    s16 y0;
    s32 i;
    u16* var_s4;

    switch (entity->step) {
    case 0:
        if (func_801B76F0(OVL_EXPORT(credits))) {
            entity->flags |= FLAG_HAS_PRIMS;
            entity->primIndex = (s32)OVL_EXPORT(Dialogue).prim[1];
            entity->step++;
            func_801B786C(0);
            glyphIndex = 0;
            while (true) {
                nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
                if (nextChar == 1) {
                    OVL_EXPORT(Dialogue).startY =
                        OVL_EXPORT(Dialogue).nextCharX +
                        *OVL_EXPORT(Dialogue).scriptCur++;
                    OVL_EXPORT(Dialogue).nextLineX++;
                    break;
                }
                glyph = func_801B78BC(nextChar);
                if (glyph != NULL) {
                    var_s4 = D_801BB0F8[glyphIndex];
                    for (i = 0; i < 0x30; i++) {
                        *var_s4++ = *glyph++;
                    }
                    glyph = D_801BB0F8[glyphIndex];
                    y = OVL_EXPORT(Dialogue).nextLineX * 0x10;
                    LoadTPage((u_long*)glyph, 0, 0, OVL_EXPORT(Dialogue).startY,
                              y, 12, 16);
                    OVL_EXPORT(Dialogue).startY += 3;
                    nextChar = OVL_EXPORT(Dialogue).startY -
                               OVL_EXPORT(Dialogue).nextCharX;
                    if (nextChar >= 0x38 && nextChar < 0x40) {
                        OVL_EXPORT(Dialogue).startY += 8;
                    }
                    glyphIndex++;
                } else {
                    OVL_EXPORT(Dialogue).startY += 2;
                    nextChar = OVL_EXPORT(Dialogue).startY -
                               OVL_EXPORT(Dialogue).nextCharX;
                    if (nextChar >= 0x38 && nextChar < 0x40) {
                        OVL_EXPORT(Dialogue).startY += 8;
                    }
                }
            }
        }
        break;
    case 1:
        if (!LOHU(OVL_EXPORT(Dialogue).nextCharY)) {
            break;
        }
        nextChar = 0;
        glyphIndex = 0;
        nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
        bitDepth = 0;

        switch (nextChar) {
        case CSOP_END_CREDITS:
            entity->step = 7;
            OVL_EXPORT(Dialogue).unk12 = 0x400;
            return 0;
        case CSOP_SUBTEXT:
            OVL_EXPORT(Dialogue).startY = OVL_EXPORT(Dialogue).nextCharX +
                                          *OVL_EXPORT(Dialogue).scriptCur++;
            OVL_EXPORT(Dialogue).nextLineX++;
            if (OVL_EXPORT(Dialogue).nextLineX > 0xF) {
                OVL_EXPORT(Dialogue).nextLineX = 0;
            }
            OVL_EXPORT(Dialogue).nextCharY = 0;
            return 0;
        case CSOP_ENTRY:
            OVL_EXPORT(Dialogue).startY = OVL_EXPORT(Dialogue).nextCharX +
                                          *OVL_EXPORT(Dialogue).scriptCur++;
            OVL_EXPORT(Dialogue).nextLineX++;
            if (OVL_EXPORT(Dialogue).nextLineX > 0xF) {
                OVL_EXPORT(Dialogue).nextLineX = 0;
            }

            prim = OVL_EXPORT(Dialogue).prim[0];
            for (i = 0; i < OVL_EXPORT(Dialogue).nextLineX; i++) {
                prim = prim->next;
                prim = prim->next;
            }

            y0 = prim->y0;
            prim = OVL_EXPORT(Dialogue).prim[0];
            while (prim != NULL) {
                if (y0 <= prim->y0) {
                    prim->y0 += 6;
                    prim->x1 += 6;
                }
                prim = prim->next;
            }
            OVL_EXPORT(Dialogue).unk12 += 0x18;
            OVL_EXPORT(Dialogue).portraitAnimTimer += 6;
            OVL_EXPORT(Dialogue).nextCharY = 0;
            return 0;
        case CSOP_SECTION:
            OVL_EXPORT(Dialogue).startY = OVL_EXPORT(Dialogue).nextCharX +
                                          *OVL_EXPORT(Dialogue).scriptCur++;
            OVL_EXPORT(Dialogue).nextLineX++;
            if (OVL_EXPORT(Dialogue).nextLineX > 0xF) {
                OVL_EXPORT(Dialogue).nextLineX = 0;
            }
            prim = OVL_EXPORT(Dialogue).prim[0];
            for (i = 0; i < OVL_EXPORT(Dialogue).nextLineX; i++) {
                prim = prim->next;
                prim = prim->next;
            }

            y0 = prim->y0;
            prim = OVL_EXPORT(Dialogue).prim[0];
            while (prim != NULL) {
                if (y0 <= prim->y0) {
                    prim->y0 += 12;
                    prim->x1 += 12;
                }
                prim = prim->next;
            }
            OVL_EXPORT(Dialogue).unk12 += 0x30;
            OVL_EXPORT(Dialogue).portraitAnimTimer += 12;
            OVL_EXPORT(Dialogue).nextCharY = 0;
            return 0;
        default:
            if (nextChar & 0x80) {
                nextChar <<= 8;
                nextChar += *OVL_EXPORT(Dialogue).scriptCur++;
                glyph = g_api.func_80106A28(nextChar, 0);
            } else {
                glyph = func_801B78BC(nextChar);
            }
            if (glyph != NULL) {
                y = OVL_EXPORT(Dialogue).nextLineX * 0x10;
                LoadTPage((u_long*)glyph, bitDepth, 0,
                          OVL_EXPORT(Dialogue).startY, y, 12, 16);
                OVL_EXPORT(Dialogue).startY += 3;
                nextChar = OVL_EXPORT(Dialogue).startY -
                           OVL_EXPORT(Dialogue).nextCharX;
                if (nextChar >= 0x38 && nextChar < 0x40) {
                    OVL_EXPORT(Dialogue).startY += 8;
                }
            } else {
                OVL_EXPORT(Dialogue).startY += 3;
                nextChar = OVL_EXPORT(Dialogue).startY -
                           OVL_EXPORT(Dialogue).nextCharX;
                if (nextChar >= 0x38 && nextChar < 0x40) {
                    do {
                        OVL_EXPORT(Dialogue).startY += 8;
                    } while (0);
                }
            }
            break;
        }
        break;
    case 2:
        break;
    case 7:
        if (!--OVL_EXPORT(Dialogue).unk12) {
            return 1;
        } else {
            return 0;
        }
    }

    if (!OVL_EXPORT(Dialogue).unk12) {
        func_801B786C(OVL_EXPORT(Dialogue).nextLineX);
        OVL_EXPORT(Dialogue).nextCharY = 1;
        OVL_EXPORT(Dialogue).unk12 = 76;
    }
    OVL_EXPORT(Dialogue).unk12--;
    if (!OVL_EXPORT(Dialogue).clutIndex) {
        prim = OVL_EXPORT(Dialogue).prim[0];
        for (i = 0; i < 0x20; i++) {
            prim->y0--;
            if (prim->y0 == -19) {
                prim->y0 =
                    OVL_EXPORT(Dialogue).portraitAnimTimer - prim->x1 + 0x11D;
                prim->x1 = OVL_EXPORT(Dialogue).portraitAnimTimer;
            }
            prim = prim->next;
        }
        OVL_EXPORT(Dialogue).clutIndex = 4;
    }
    OVL_EXPORT(Dialogue).clutIndex--;
    return 0;
}
