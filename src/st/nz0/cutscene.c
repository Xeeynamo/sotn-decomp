// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

static u8 D_801813C8[] = {0x00, 0x40, 0x00, 0x00};
static u8 D_801813CC[] = {0x00, 0x00, 0x00, 0x00};
static u16 D_801813D0[] = {0x0238, 0x0240};
static u16 D_801813D4[] = {0x0000, 0x0020};
static u16 D_801813D8[] = {0x01A1, 0x01A1};
static s16 D_801813DC[] = {
    0x0008, 0x0013, 0x0011, 0x0031, 0x004F, 0x0026, 0x0036, 0x001D, 0x001B,
    0x0033, 0x002C, 0x0021, 0x0019, 0x000A, 0x0033, 0x001F, 0x0048, 0x002F,
    0x0013, 0x0019, 0x004D, 0x004B, 0x0017, 0x001D, 0x0012, 0x0002, 0x001B,
    0x002A, 0x0050, 0x0045, 0x0032, 0x000D, 0x002A, 0x004D, 0x0006, 0x0027,
    0x0007, 0x0048, 0x002F, 0x001B, 0x0036, 0x0022, 0x0039, 0x0014, 0x0039,
    0x001D, 0x000A, 0x0035, 0x0010, 0x001B, 0x003D, 0x0017, 0x002E, 0x000B,
    0x0049, 0x0042, 0x003D, 0x002A, 0x0001, 0x000C, 0x001B, 0x0034, 0x0041,
    0x0035, 0x0008, 0x000E, 0x004D, 0x0011, 0x0034, 0x0041, 0x0029, 0x0048};
static const char* actor_names[] = {_S("Alucard"), _S("Maria")};

extern u32 OVL_EXPORT(SkipCutscene);
extern Dialogue OVL_EXPORT(Dialogue);
extern u32 OVL_EXPORT(CutsceneFlags);
extern s32 OVL_EXPORT(IsCutsceneDone); // bss
// This file consists of NZ0_EntityCutscene, and all the functions it calls.
// No function in NZ0 calls anything in there, nor does anything in here call
// any NZ0 functions, besides the ones in this file.

#include "../cutscene_unk1.h"

#include "../set_cutscene_script.h"

#include "../cutscene_unk3.h"

#include "../cutscene_unk4.h"

#include "../cutscene_actor_name.h"

#include "../set_cutscene_end.h"

#include "../cutscene_run.h"

#include "../cutscene_scale_avatar.h"

// cutscene where alucard and maria discuss castle changing
extern u8 OVL_EXPORT(cutscene_data)[];
void OVL_EXPORT(EntityCutscene)(Entity* self) {
    s16 uCoord;
    s16 vCoord;
    s32 primIndex;
    u16* sp44;
    s32 sp40;
    RECT rect;
    u16 nextChar;
    s32 var_s7;
    u8* var_s6;
    s32 var_s5;
    u_long ptr;
    u32 var_s3;
    Primitive* prim;
    u8* var_s1;
    s32 i;

    if (self->step) {
        if (OVL_EXPORT(IsCutsceneDone) && !OVL_EXPORT(SkipCutscene) &&
            (g_Settings.D_8003CB04 & 0x100 || g_GameClearFlag)) {
            // CutsceneSkip function inlined
            if (g_pads[0].tapped == PAD_START) {
                OVL_EXPORT(SkipCutscene) = 1;
                g_api.FreePrimitives(self->primIndex);
                self->flags ^= FLAG_HAS_PRIMS;
                if (OVL_EXPORT(Dialogue).primIndex[1] != -1) {
                    g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[1]);
                }
                if (OVL_EXPORT(Dialogue).primIndex[0] != -1) {
                    g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[0]);
                }
                g_api.PlaySfx(SET_STOP_MUSIC);
                self->step = 1;
                self->step_s = 0;
            }
        }
    }
    if (self->step && OVL_EXPORT(Dialogue).unk3C) {
        CutsceneRun();
    }
    switch (self->step) {
    case 0:
        if (g_CastleFlags[MET_MARIA_IN_NZ0] ||
            g_PlayableCharacter != PLAYER_ALUCARD) {
            DestroyEntity(self);
            return;
        }
        if (SetCutsceneScript(OVL_EXPORT(cutscene_data))) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = OVL_EXPORT(Dialogue).primIndex[2];
            OVL_EXPORT(CutsceneFlags) = 0;
            OVL_EXPORT(IsCutsceneDone) = 0;
            OVL_EXPORT(SkipCutscene) = 0;
            g_CutsceneHasControl = 1;
            self->step++;
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
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
                    OVL_EXPORT(Dialogue).nextLineY += 12;
                }
                OVL_EXPORT(Dialogue).nextCharY++;
                if (OVL_EXPORT(Dialogue).nextCharY > 4) {
                    OVL_EXPORT(Dialogue).nextCharY = 0;
                }
                CutsceneUnk4();
                if (!(OVL_EXPORT(Dialogue).unk12 & 1)) {
                    if (OVL_EXPORT(Dialogue).nextCharY > 3) {
                        OVL_EXPORT(Dialogue).unk12 |= 1;
                        OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
                        self->step_s = 0;
                        self->step++;
                        return;
                    }
                } else {
                    OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
                    self->step_s = 0;
                    self->step++;
                    return;
                }
                continue;
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
                var_s5 = *OVL_EXPORT(Dialogue).scriptCur++;
                var_s7 = var_s5 & 1;
                uCoord = D_801813C8[var_s7];
                vCoord = D_801813CC[var_s7];
                prim->clut = D_801813D0[i];
                prim->tpage = 0x90;
                if (var_s5 & 0x80) {
                    prim->u0 = prim->u2 = uCoord + 0x2F;
                    prim->u1 = prim->u3 = uCoord;
                } else {
                    prim->u0 = prim->u2 = uCoord;
                    prim->u1 = prim->u3 = uCoord + 0x2F;
                }
                prim->v0 = prim->v1 = vCoord;
                prim->v2 = prim->v3 = vCoord + 0x48;
                prim->x0 = prim->x1 = prim->x2 = prim->x3 =
                    OVL_EXPORT(Dialogue).startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    OVL_EXPORT(Dialogue).startY + 0x24;
                OVL_EXPORT(Dialogue).clutIndex = D_801813D8[i];
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
                for (prim = OVL_EXPORT(Dialogue).prim[0], i = 0;
                     i < LEN(OVL_EXPORT(Dialogue).prim) - 1; i++) {
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
                prim = OVL_EXPORT(Dialogue)
                           .prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
                prim = prim->next;
                prim->y0 = prim->y1 = OVL_EXPORT(Dialogue).startY;
                prim->y2 = prim->y3 = OVL_EXPORT(Dialogue).startY + 0x48;
                prim = prim->next;
                prim->y0 = OVL_EXPORT(Dialogue).startY - 1;
                prim->u0 = 0xF6;
                OVL_EXPORT(Dialogue).portraitAnimTimer = 0x18;
                self->step = 5;
                self->step_s = 0;
                return;
            case CSOP_CLOSE_DIALOG:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                OVL_EXPORT(Dialogue).portraitAnimTimer = 0x18;
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
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                OVL_EXPORT(Dialogue).scriptCur--;
                return;
            case CSOP_SCRIPT_UNKNOWN_11:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                OVL_EXPORT(Dialogue).scriptCur--;
                return;
            case CSOP_SET_END:
                ptr = (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                SetCutsceneEnd((u8*)ptr);
                continue;
            case CSOP_SCRIPT_UNKNOWN_13:
                continue;
            case CSOP_SCRIPT_SWITCH:
                ptr = (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr += (u16)0x100000;
                OVL_EXPORT(Dialogue).scriptCur += *(u16*)ptr << 2;

                ptr = (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur;
                OVL_EXPORT(Dialogue).scriptCur = (u8*)ptr + 0x100000;
                continue;
            case CSOP_SCRIPT_UNKNOWN_15:
                ptr = (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur;
                OVL_EXPORT(Dialogue).scriptCur = (u8*)ptr + 0x100000;
                continue;
            case CSOP_WAIT_FOR_FLAG:
                if (!((OVL_EXPORT(CutsceneFlags) >>
                       *OVL_EXPORT(Dialogue).scriptCur) &
                      1)) {
                    OVL_EXPORT(Dialogue).scriptCur--;
                    return;
                }
                OVL_EXPORT(CutsceneFlags) &=
                    ~(1 << *OVL_EXPORT(Dialogue).scriptCur);
                OVL_EXPORT(Dialogue).scriptCur++;
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
                    ptr = (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                    ptr += 0x100000;
                    var_s5 = OVL_EXPORT(Dialogue).scriptCur++[0];
                    LoadTPage((u_long*)ptr, 1, 0, D_801813D4[var_s5], 0x100,
                              0x30, 0x48);
                }
                continue;
            case CSOP_SCRIPT_UNKNOWN_20:
                nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
                nextChar <<= 4;
                nextChar |= *OVL_EXPORT(Dialogue).scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_SCRIPT_UNKNOWN_21:
                OVL_EXPORT(CutsceneFlags) = 0;
                OVL_EXPORT(SkipCutscene) = 0;
                OVL_EXPORT(IsCutsceneDone) = 0;
                continue;
            case CSOP_SCRIPT_UNKNOWN_22:
                OVL_EXPORT(CutsceneFlags) &=
                    ~(1 << *OVL_EXPORT(Dialogue).scriptCur++);
                continue;
            case CSOP_SCRIPT_UNKNOWN_23:
                return;
            case CSOP_WAIT_FOR_FLAG_RESET:
                if (!((OVL_EXPORT(CutsceneFlags) >>
                       *OVL_EXPORT(Dialogue).scriptCur) &
                      1)) {
                    OVL_EXPORT(Dialogue).scriptCur--;
                    return;
                }
                OVL_EXPORT(Dialogue).scriptCur++;
                continue;
            default:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                OVL_EXPORT(Dialogue).nextCharTimer = OVL_EXPORT(Dialogue).unk17;
            }
            break; // This breaks the big while-loop!
        }
        if (nextChar == 0x20) {
            OVL_EXPORT(Dialogue).nextCharX += 2;
            return;
        }
        rect.x = ((nextChar & 0xF) << 1) + 0x380;
        rect.y = ((s32)(nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        vCoord = (OVL_EXPORT(Dialogue).nextCharY * 0xC) + 0x180;
        MoveImage(&rect, OVL_EXPORT(Dialogue).nextCharX, vCoord);
        OVL_EXPORT(Dialogue).nextCharX += 2;
        break;
    case 2:
        ScaleCutsceneAvatar(2);
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 6) {
            self->step--;
        }
        break;
    case 3:
        prim = OVL_EXPORT(Dialogue).prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
        prim->x0 = prim->x2 -= 4;
        prim->x1 = prim->x3 += 4;
        prim->y0 = prim->y1 -= 6;
        prim->y2 = prim->y3 += 6;
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (!OVL_EXPORT(Dialogue).portraitAnimTimer) {
            self->step = 1;
            for (prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[1]];
                 prim != NULL; prim = prim->next) {
                prim->drawMode = DRAW_DEFAULT;
            }
        }
        break;
    case 4:
        prim = OVL_EXPORT(Dialogue).prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
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
            return;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            OVL_EXPORT(IsCutsceneDone) = 1;
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 0x48);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            OVL_EXPORT(Dialogue).primIndex[0] = primIndex;
            for (prim = &g_PrimBuf[primIndex], uCoord = 0; prim != NULL;
                 prim = prim->next) {
                prim->r0 = prim->r1 = 0x7F;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 0xF7;
                prim->y0 = prim->y1 = OVL_EXPORT(Dialogue).startY + uCoord;
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = D_801813DC[uCoord];
                prim->x3 = 0xF70;
                uCoord++;
            }
            self->step_s++;
            break;
        case 1:
            for (uCoord = 0,
                prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[0]];
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
        case 2:
            uCoord = 0;
            prim =
                OVL_EXPORT(Dialogue).prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
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
        prim = OVL_EXPORT(Dialogue).prim[LEN(OVL_EXPORT(Dialogue).prim) - 1];
        prim = prim->next;
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 0xC) {
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
                prim->y2 = (prim->y3 -= 6);
            }
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
        }
        break;
    case 7:
        DestroyEntity(self);
        g_CastleFlags[MET_MARIA_IN_NZ0] = 1;
        g_CutsceneHasControl = 0;
        g_Settings.D_8003CB04 |= 0x100;
        break;
    }
}
