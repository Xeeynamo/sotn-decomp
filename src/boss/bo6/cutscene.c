// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"
#include <cutscene.h>

extern Dialogue g_Dialogue;
extern const char* actor_names[];

#define CUTSCENE_UNK1_NEXT_X (DISP_STAGE_W + 2)
#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

#define CUTSCENE_UNK3_RECT_X DISP_STAGE_W
#include "../../st/cutscene_unk3.h"

#define CUTSCENE_UNK4_TPAGE 0x14
#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/set_cutscene_end.h"

#define CUTSCENE_TILEMAP_SCROLL
#include "../../st/cutscene_run.h"

#include "../../st/cutscene_skip.h"

#include "../../st/cutscene_scale_avatar.h"

// INCLUDE_ASM("boss/bo6/nonmatchings/cutscene", func_us_801A7DC0);
// target    current
//    s4        s5
//    s3        s4
//    s0        s3
//    s1        s1
//    s0/t1     s0


extern s32 D_8019D374;        
extern Dialogue g_Dialogue;   
extern s32 g_IsCutsceneDone;
extern s32 g_SkipCutscene;
extern u32 g_CutsceneFlags;
extern u32 D_8019D428;     
extern u8 OVL_EXPORT(cutscene_data)[];  

extern u8 OVL_EXPORT(PrizeDrops)[];
extern u8 D_us_80180614[];
extern u8 D_us_8019A0D0[];
extern u8 D_us_8019A2E1[];
extern u8 D_us_8019A2FB[];

// clut                                                                         
extern u16 D_us_80180618[];                                                         
extern u16 D_us_80180620[];
                                                                                
extern u16 D_us_80180624[];
                                                 
// x-coords                                                                     
extern s16 D_us_8018062C[];    

extern s8 D_us_8019A0C8;
extern s8 D_us_8019A0CC;

u8 SetCutsceneScript(u8* script);
void DrawCutsceneActorName(u16 actorIndex, Entity* self);

void func_us_801A7DC0(Entity* self) {
// void BO6_EntityCutscene(Entity* self) {
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
        if (g_IsCutsceneDone && !g_SkipCutscene) {
            if (g_IsTimeAttackUnlocked) {
                CutsceneSkip(self);
            } else {
                switch (self->params) {
                case 0:
                    if (g_Settings.D_8003CB04 & 0x8000) {
                        CutsceneSkip(self);
                    }
                    break;
                case 2:
                    if (g_Settings.D_8003CB04 & 0x10000) {
                        CutsceneSkip(self);
                    }
                    break;
                case 3:
                    if (g_Settings.D_8003CB04 & 0x20000) {
                        CutsceneSkip(self);
                    }
                    break;
                }
                
            }
        }
    }

    if (self->step && g_Dialogue.unk3C) {
        CutsceneRun();
    }
    
    switch (self->step) {
    case 0:
        switch (self->params) {
        case 0:
            if (g_DemoMode != Demo_None || g_CastleFlags[SHAFT_ORB_DEFEATED] || g_PlayableCharacter != 0) {                
                DestroyEntity(self);
                return;
            }

            ptr = SetCutsceneScript(D_us_8019A0D0);
            D_us_8019A0C8 = 0;
            if (g_CastleFlags[MET_MARIA_IN_CEN]) {
                D_us_8019A0C8 = 1;
            }
            D_us_8019A0CC = 0;
            if (g_api.CheckEquipmentItemCount(0x22, 1) != 0) {
                D_us_8019A0CC = 1;
            }
            break;

        case 1:
            ptr = SetCutsceneScript(D_us_8019A2E1);
            break;

        case 2:
        case 3:
            if (g_DemoMode != Demo_None || g_CastleFlags[SHAFT_ORB_DEFEATED]) {
                DestroyEntity(self);
                return;
            }
            ptr = SetCutsceneScript(D_us_8019A2FB);
            D_us_8019A0CC = self->params - 2;

            break;
        }

        if (ptr) { 
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            self->primIndex = g_Dialogue.primIndex[2];
            g_CutsceneHasControl = 1;
            g_CutsceneFlags = 0;
            g_IsCutsceneDone = false;
            g_SkipCutscene = false;
            self->step++;
            self->flags |= FLAG_UNK_10000;
        }
        break;

    case 1:
        nextChar = 0;
        // this is a huge While-loop! Don't miss it!
        while (1) {

            if ((g_Dialogue.nextCharTimer != 0) && !g_SkipCutscene) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.scriptCur++;
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
                        g_Dialogue.nextLineY += 12;
                    }
                    g_Dialogue.nextCharY++;
                    if (g_Dialogue.nextCharY >= 5) {
                        g_Dialogue.nextCharY = 0;
                    }
                    CutsceneUnk4();
                    if (!(g_Dialogue.unk12 & 1)) {
                        if (g_Dialogue.nextCharY >= 4) {
                            g_Dialogue.unk12 |= 1;
                            g_Dialogue.portraitAnimTimer = 0;
                            self->step_s = 0;
                            self->step++;
                            return;
                        }
                        continue;
                    }
                    g_Dialogue.portraitAnimTimer = 0;
                    self->step_s = 0;
                    self->step++;
                    return;
                case CSOP_SET_SPEED:
                    g_Dialogue.unk17 = *g_Dialogue.scriptCur++;
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
                    for (i = 0; i < 5; i++) {
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
                    nextChar2 = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[5];
                    uCoord = OVL_EXPORT(PrizeDrops)[nextChar2 & 1];
                    vCoord = D_us_80180614[nextChar2 & 1];
                    prim->clut = D_us_80180618[i];
                    prim->tpage = 0x94;
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
                        g_Dialogue.startX - 0x1E;
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        g_Dialogue.startY + 0x24;
                    g_Dialogue.clutIndex = D_us_80180624[i];
                    CutsceneUnk1();
                    CutsceneUnk4();
                    prim->priority = 0x1FE;
                    prim->drawMode = DRAW_DEFAULT;
                    DrawCutsceneActorName(i, self);
                    g_Dialogue.portraitAnimTimer = 6;
                    self->step = 3;
                    return;
                case CSOP_NEXT_DIALOG:
                    if (g_SkipCutscene) {
                        continue;
                    }
                    prim = g_Dialogue.prim[0];
                    for (i = 0; i < 5; i++) {
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
                        g_Dialogue.scriptCur++;
                        g_Dialogue.scriptCur++;
                        continue;
                    }
                    g_Dialogue.startX = *g_Dialogue.scriptCur++;
                    g_Dialogue.startY = *g_Dialogue.scriptCur++;
                    prim = g_Dialogue.prim[5];
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
                        g_Dialogue.scriptCur++;
                        g_Dialogue.scriptCur++;
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
                    ptr += 0x100000;
                    g_Dialogue.scriptCur += *(u8*)ptr << 2;
    
                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur;
                    g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
                    continue;
                case CSOP_SCRIPT_UNKNOWN_15:
                    ptr = (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.scriptCur;
                    g_Dialogue.scriptCur = (u8*)ptr + 0x100000;
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
                        ptr += 0x100000;
                        nextChar2 = g_Dialogue.scriptCur++[0];
                        LoadTPage((u_long*)ptr, 1, 0, D_us_80180620[nextChar2], 0x100,
                                  48, 72);
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
                }
            break; // This breaks the big while-loop!
        }
        if (nextChar == 0x20) {
            g_Dialogue.nextCharX += 2;
            return;
        }
        rect.x = ((nextChar & 0xF) * 2) + 0x380;
        rect.y = ((u32)(nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
        vCoord = (g_Dialogue.nextCharY * 0xC) + 0x180;
        MoveImage(&rect, g_Dialogue.nextCharX, vCoord);
        g_Dialogue.nextCharX += 2;
        break;
    case 2:
        ScaleCutsceneAvatar(2);
        if (g_Dialogue.portraitAnimTimer >= 6) {
            self->step -= 1;
            return;
        }
        break;
    case 3:
        prim = g_Dialogue.prim[5];
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
        prim = g_Dialogue.prim[5];
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
            for (prim = &g_PrimBuf[primIndex], j = 0; prim != NULL;
                 prim = prim->next) {
                prim->r0 = prim->r1 = 0x7F;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 0xF7;
                prim->y0 = prim->y1 = g_Dialogue.startY + j;
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = D_us_8018062C[j];
                prim->x3 = 0xF70;

                j++;
            }
            self->step_s++;
            return;
        case 1:
            for (j = 0, prim = &g_PrimBuf[g_Dialogue.primIndex[0]];
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
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                g_Dialogue.primIndex[0] = -1;
                prim = g_Dialogue.prim[5];
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
            prim = g_Dialogue.prim[5];
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
        prim = g_Dialogue.prim[5];
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
        switch (self->params) {
        case 0:
            g_Settings.D_8003CB04 |= 0x8000;
            break;
        case 2:
            g_Settings.D_8003CB04 |= 0x10000;
            break;
        case 3:
            g_Settings.D_8003CB04 |= 0x20000;
            g_CastleFlags[SHAFT_ORB_DEFEATED] = true;
            break;
        }
#ifndef VERSION_PSP
        DestroyEntity(self);
#endif
        g_CutsceneHasControl = 0;
        break;
    }
}
