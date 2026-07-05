// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include "../pfn_entity_update.h"
#include <cutscene.h>

extern Dialogue OVL_EXPORT(Dialogue);

#include "../cutscene_unk1.h"
#include "../set_cutscene_script.h"
#include "../cutscene_unk3.h"
#include "../cutscene_unk4.h"
#include "../cutscene_actor_name.h"
#include "../set_cutscene_end.h"
#define CUTSCENE_TILEMAP_SCROLL
#include "../cutscene_run.h"
#include "../cutscene_skip.h"
#include "../cutscene_scale_avatar.h"

INCLUDE_RODATA("st/top/nonmatchings/cutscene", D_us_801A898C);

INCLUDE_RODATA("st/top/nonmatchings/cutscene", D_us_801A8998);

INCLUDE_RODATA("st/top/nonmatchings/cutscene", D_us_801A89A0);

extern u8 OVL_EXPORT(cutscene_data)[];
extern bool OVL_EXPORT(IsCutsceneDone);
extern u32 OVL_EXPORT(CutsceneFlags);
extern u8 D_us_80180D38[];
extern u8 D_us_80180D3C[];
extern u16 D_us_80180D40[];
extern u16 D_us_80180D48[];
extern u16 D_us_80180D4C[];
extern s16 D_us_80180D54[];

void OVL_EXPORT(EntityCutscene)(Entity* self) {
    RECT rect;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 j;
    s16 uCoord;
    s16 vCoord;
    u16 nextChar;
    s32 nextChar2;
    u_long ptr;

    if (self->step) {
        if (OVL_EXPORT(IsCutsceneDone) && !OVL_EXPORT(SkipCutscene)) {
            if (g_GameClearFlag) {
                CutsceneSkip(self);
            } else if (g_Settings.D_8003CB04 & 0x800000) {
                CutsceneSkip(self);
            }
        }

        if (self->step && OVL_EXPORT(Dialogue).unk3C) {
            CutsceneRun();
        }
    }

    switch (self->step) {
    case 0:
        if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED] ||
            g_PlayableCharacter != PLAYER_ALUCARD) {
            DestroyEntity(self);
            return;
        }
        if (SetCutsceneScript(OVL_EXPORT(cutscene_data))) {
            g_CutsceneHasControl = true;
            OVL_EXPORT(CutsceneFlags) = 0;
            OVL_EXPORT(IsCutsceneDone) = 0;
            OVL_EXPORT(SkipCutscene) = 0;
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = OVL_EXPORT(Dialogue).primIndex[2];
            self->step++;
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
            if ((OVL_EXPORT(Dialogue).nextCharTimer != 0) &&
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
                if (OVL_EXPORT(Dialogue).nextCharY >= 5) {
                    OVL_EXPORT(Dialogue).nextCharY = 0;
                }
                CutsceneUnk4();
                if (!(OVL_EXPORT(Dialogue).unk12 & 1)) {
                    if (OVL_EXPORT(Dialogue).nextCharY >= 4) {
                        OVL_EXPORT(Dialogue).unk12 |= 1;
                        OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
                        self->step_s = 0;
                        self->step++;
                        return;
                    }
                    continue;
                }
                OVL_EXPORT(Dialogue).portraitAnimTimer = 0;
                self->step_s = 0;
                self->step++;
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
                // fake reuse of i?
                i = *OVL_EXPORT(Dialogue).scriptCur++;
                nextChar2 = *OVL_EXPORT(Dialogue).scriptCur++;
                prim = OVL_EXPORT(Dialogue).prim[5];
                uCoord = D_us_80180D38[nextChar2 & 1];
                vCoord = D_us_80180D3C[nextChar2 & 1];
                prim->clut = D_us_80180D40[i];
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
                    OVL_EXPORT(Dialogue).startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    OVL_EXPORT(Dialogue).startY + 0x24;
                OVL_EXPORT(Dialogue).clutIndex = D_us_80180D4C[i];
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
                for (prim = OVL_EXPORT(Dialogue).prim[0], i = 0; i < 5; i++) {
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
                    OVL_EXPORT(Dialogue).scriptCur++;
                    OVL_EXPORT(Dialogue).scriptCur++;
                    continue;
                }
                OVL_EXPORT(Dialogue).startX = *OVL_EXPORT(Dialogue).scriptCur++;
                OVL_EXPORT(Dialogue).startY = *OVL_EXPORT(Dialogue).scriptCur++;
                prim = OVL_EXPORT(Dialogue).prim[5];
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
                    OVL_EXPORT(Dialogue).scriptCur++;
                    OVL_EXPORT(Dialogue).scriptCur++;
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
                *OVL_EXPORT(Dialogue).scriptCur--;
                return;
            case CSOP_SCRIPT_UNKNOWN_11:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *OVL_EXPORT(Dialogue).scriptCur--;
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
                ptr += 0x100000;
                OVL_EXPORT(Dialogue).scriptCur += *(u8*)ptr << 2;

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
                    ptr = (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*OVL_EXPORT(Dialogue).scriptCur++;
                    ptr += 0x100000;
                    nextChar2 = OVL_EXPORT(Dialogue).scriptCur++[0];
                    LoadTPage((u_long*)ptr, 1, 0, D_us_80180D48[nextChar2],
                              0x100, 48, 72);
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
                    *OVL_EXPORT(Dialogue).scriptCur--;
                    return;
                }
                *OVL_EXPORT(Dialogue).scriptCur++;
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
        rect.x = ((nextChar & 0xF) * 2) + 0x380;
        rect.y = ((u32)(nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        vCoord = (OVL_EXPORT(Dialogue).nextCharY * 0xC) + 0x180;
        MoveImage(&rect, OVL_EXPORT(Dialogue).nextCharX, vCoord);
        OVL_EXPORT(Dialogue).nextCharX += 2;
        break;
    case 2:
        ScaleCutsceneAvatar(2);
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 6) {
            self->step -= 1;
            return;
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
            for (prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[1]];
                 prim != NULL; prim = prim->next) {
                prim->drawMode = DRAW_DEFAULT;
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
            for (prim = &g_PrimBuf[primIndex], j = 0; prim != NULL;
                 prim = prim->next) {
                prim->r0 = prim->r1 = 0x7F;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 0xF7;
                prim->y0 = prim->y1 = OVL_EXPORT(Dialogue).startY + j;
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = D_us_80180D54[j];
                prim->x3 = 0xF70;

                j++;
            }
            self->step_s++;
            return;
        case 1:
            for (j = 0, prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[0]];
                 prim != NULL; prim = prim->next) {
                prim->x3 -= prim->x2;
                prim->x2 += 2;
                prim->x0 = prim->x3 / 16;
                if (prim->x0 < 5) {
                    prim->x0 = 4;
                } else {
                    j = 1;
                }
            }
            if (j == 0) {
                g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[0]);
                OVL_EXPORT(Dialogue).primIndex[0] = -1;
                prim = OVL_EXPORT(Dialogue).prim[5];
                prim = prim->next;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                self->step_s++;
                return;
            }
            break;
        case 2:
            j = 0;
            prim = OVL_EXPORT(Dialogue).prim[5];
            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 0x10;
                j = 1;
            }
            if (prim->b0 >= 0x7F) {
                prim->b0 = prim->b1 = 0x7F;
            } else {
                prim->b0 = prim->b1 += 8;
                j = 1;
            }

            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->g0 = prim->b0 = 0x10;
            } else {
                prim->r0 = prim->g0 = prim->b0 -= 0xF;
                j = 1;
            }
            if (j == 0) {
                self->step = 1;
            }
        }
        break;
    case 6:
        prim = OVL_EXPORT(Dialogue).prim[5];
        prim = prim->next;
        OVL_EXPORT(Dialogue).portraitAnimTimer--;
        if (OVL_EXPORT(Dialogue).portraitAnimTimer >= 0xC) {
            prim = prim->next;
            prim->u0 -= 20;
            if (OVL_EXPORT(Dialogue).portraitAnimTimer & 1) {
                prim->u0--;
                return;
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
            return;
        }
        break;

    case 7:
        g_CastleFlags[INVERTED_CASTLE_UNLOCKED] = 1;
        g_CutsceneHasControl = 0;
        g_Settings.D_8003CB04 |= 0x800000;
        DestroyEntity(self);
        break;
    }
}
