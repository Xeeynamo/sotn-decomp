// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"
#include <cutscene.h>

#include "../cutscene_unk1.h"

#include "../set_cutscene_script.h"

#include "../cutscene_unk3.h"

#include "../cutscene_unk4.h"

// This array is in Data, but the strings within it are rodata. That rodata
// lives between the jump tables in this file, so we have to import the rodata,
// and also the data.
static const char* g_ActorNames[] = {_S("Alucard"), _S("Lisa"), _S("Succubus")};

#include "../cutscene_actor_name.h"

#include "../set_cutscene_end.h"

static void CutsceneRun(void) {
    Entity* entity;
    u16 startTimer;

    g_Dialogue.timer++;
    // protect from overflows
    if (g_Dialogue.timer >= 0xFFFF) {
        g_Dialogue.unk3C = 0;
        return;
    }
    while (true) {
        // Start the dialogue script only if the start timer has passed
        startTimer = *g_Dialogue.scriptEnd++ << 8;
        startTimer |= *g_Dialogue.scriptEnd++;
        if (g_Dialogue.timer < startTimer) {
            // Re-evaluate the condition at the next frame
            g_Dialogue.scriptEnd -= 2;
            return;
        }
        switch (*g_Dialogue.scriptEnd++) {
        case 0:
            entity = &g_Entities[*g_Dialogue.scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            entity->entityId = *g_Dialogue.scriptEnd++;
            entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
            entity->posX.i.hi = *g_Dialogue.scriptEnd++ * 0x10;
            entity->posX.i.hi |= *g_Dialogue.scriptEnd++;
            entity->posY.i.hi = *g_Dialogue.scriptEnd++ * 0x10;
            entity->posY.i.hi |= *g_Dialogue.scriptEnd++;
            break;
        case 1:
            entity = &g_Entities[*g_Dialogue.scriptEnd++ & 0xFF] +
                     STAGE_ENTITY_START;
            DestroyEntity(entity);
            break;
        case 2:
            if (!((g_CutsceneFlags >> *g_Dialogue.scriptEnd) & 1)) {
                g_Dialogue.scriptEnd -= 3;
                g_Dialogue.timer--;
                return;
            }
            g_CutsceneFlags &= ~(1 << *g_Dialogue.scriptEnd++);
            break;
        case 3:
            g_CutsceneFlags |= 1 << *g_Dialogue.scriptEnd++;
            break;
        }
    }
}

void func_80194F14(Entity* self) {
    if (g_pads[0].tapped == PAD_START) {
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
        self->step = 1;
        self->step_s = 0;
    }
}

#include "../cutscene_scale_avatar.h"

// dialogue with mother opens as alucard walks right ID 20
// Same pattern as a lot of other cutscenes, main differences
// are related to the self->params if-else statements.
extern u8 OVL_EXPORT(cutscene_data)[];
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
        if (g_IsCutsceneDone && !g_SkipCutscene) {
            if (g_IsTimeAttackUnlocked) {
                func_80194F14(self);
            } else {
                if (self->params) {
                    if (g_Settings.D_8003CB04 & 0x2000) {
                        func_80194F14(self);
                    }
                } else if (g_Settings.D_8003CB04 & 0x1000) {
                    func_80194F14(self);
                }
            }
        }
        if ((self->step != 0) && (g_Dialogue.unk3C != 0)) {
            CutsceneRun();
        }
    }
    switch (self->step) {
    case 0:
        if ((g_CastleFlags[SUCC_CS_DONE]) ||
            (g_PlayableCharacter != PLAYER_ALUCARD) ||
            (g_DemoMode != Demo_None)) {
            if (!self->params) {
                DestroyEntity(self);
                break;
            }
        }
        if (self->params) {
            ptr = SetCutsceneScript(OVL_EXPORT(cutscene_data) + 0x49D);
        } else {
            ptr = SetCutsceneScript(OVL_EXPORT(cutscene_data));
        }
        if (ptr) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            g_CutsceneFlags = 0;
            g_IsCutsceneDone = 0;
            g_SkipCutscene = 0;
            D_8003C704 = 1;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step++;
        }
        if ((g_CastleFlags[SUCC_CS_DONE] != 0) ||
            (g_PlayableCharacter != PLAYER_ALUCARD) ||
            (g_DemoMode != Demo_None)) {
            g_SkipCutscene = 1;
        }
        break;
    case 1:
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
            case CSOP_SCRIPT_UNKNOWN_4:
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
                uCoord = D_8018088C[nextChar2 & 1];
                vCoord = D_80180890[nextChar2 & 1];
                prim->clut = D_80180894[i];
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
                    g_Dialogue.startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    g_Dialogue.startY + 0x24;
                g_Dialogue.clutIndex = D_801808A0[i];
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
                for (prim = g_Dialogue.prim[0], i = 0; i < 5; i++) {
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
            case CSOP_UNK_11:
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
                    LoadTPage((u32*)ptr, 1, 0, D_8018089C[nextChar2], 0x100,
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
            case CSOP_SCRIPT_UNKNOWN_24:
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
                prim->x2 = D_801808A8[j];
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
                prim->blendMode = 0x11;
                prim = prim->next;
                prim->blendMode = 0x51;
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
        if (self->params) {
            g_CastleFlags[SUCC_CS_DONE] = 1;
            g_Settings.D_8003CB04 |= 0x2000;
        } else {
            g_Settings.D_8003CB04 |= 0x1000;
        }
        D_8003C704 = 0;
        DestroyEntity(self);
        break;
    }
}
