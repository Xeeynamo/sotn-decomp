// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include <cutscene.h>

static u8 __unused[0xC00];
static s32 skip_cutscene;
static Dialogue g_Dialogue;
static u32 __unused0[26];
u32 g_CutsceneFlags;
u32 D_8019D428;

// Bizarre variable - u8 here, but u16 in EntityHeartDrop
// Possible that since EntityHeartDrop is not used in CEN, that data
// is reused here for the holy glasses cutscene? Very unusual.
u8 g_HeartDropArray[] = {0, 64, 0, 0};
static u8 D_801805DC[] = {0, 0, 0, 0};

// clut
static u16 D_801805E0[] = {
    LAYER_CLUT_ALT | 0,
    LAYER_CLUT_ALT | 8,
    LAYER_CLUT_ALT | 16,
    LAYER_CLUT_ALT | 24,
};
static u16 D_801805E8[] = {0, 32};

static u16 D_801805EC[] = {
    0x01A1,
    0x01A1,
    0x01A1,
    0x01A1,
};

// x-coords
static s16 D_801805F4[] = {
    0x08, 0x13, 0x11, 0x31, 0x4F, 0x26, 0x36, 0x1D, 0x1B, 0x33, 0x2C, 0x21,
    0x19, 0x0A, 0x33, 0x1F, 0x48, 0x2F, 0x13, 0x19, 0x4D, 0x4B, 0x17, 0x1D,
    0x12, 0x02, 0x1B, 0x2A, 0x50, 0x45, 0x32, 0x0D, 0x2A, 0x4D, 0x06, 0x27,
    0x07, 0x48, 0x2F, 0x1B, 0x36, 0x22, 0x39, 0x14, 0x39, 0x1D, 0x0A, 0x35,
    0x10, 0x1B, 0x3D, 0x17, 0x2E, 0x0B, 0x49, 0x42, 0x3D, 0x2A, 0x01, 0x0C,
    0x1B, 0x34, 0x41, 0x35, 0x08, 0x0E, 0x4D, 0x11, 0x34, 0x41, 0x29, 0x48,
};

static const char* g_ActorNames[] = {
    _S("Alucard"),
    _S("Maria"),
};

static const char _pad[4] = "";

#include "../cutscene_unk1.h"

#include "../set_cutscene_script.h"

#include "../cutscene_unk3.h"

#include "../cutscene_unk4.h"

#include "../cutscene_avatar.h"

#include "../cutscene_unk6.h"

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
        startTimer = *g_Dialogue.unk40++ << 8;
        startTimer |= *g_Dialogue.unk40++;
        if (g_Dialogue.timer < startTimer) {
            // Re-evaluate the condition at the next frame
            g_Dialogue.unk40 -= 2;
            return;
        }
        switch (*g_Dialogue.unk40++) {
        case 0:
            entity =
                &g_Entities[*g_Dialogue.unk40++ & 0xFF] + STAGE_ENTITY_START;
            DestroyEntity(entity);
            entity->entityId = *g_Dialogue.unk40++;
            entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
            entity->posX.i.hi = *g_Dialogue.unk40++ * 0x10;
            entity->posX.i.hi |= *g_Dialogue.unk40++;
            entity->posY.i.hi = *g_Dialogue.unk40++ * 0x10;
            entity->posY.i.hi |= *g_Dialogue.unk40++;
            entity->posX.i.hi -= g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi -= g_Tilemap.scrollY.i.hi;
            break;
        case 1:
            entity =
                &g_Entities[*g_Dialogue.unk40++ & 0xFF] + STAGE_ENTITY_START;
            DestroyEntity(entity);
            break;
        case 2:
            if (!((g_CutsceneFlags >> *g_Dialogue.unk40) & 1)) {
                g_Dialogue.unk40--;
                return;
            }
            g_CutsceneFlags &= ~(1 << *g_Dialogue.unk40++);
            break;
        case 3:
            g_CutsceneFlags |= 1 << *g_Dialogue.unk40++;
            break;
        }
    }
}

#include "../cutscene_scale_avatar.h"

void CEN_CutsceneExec(Entity* self) {
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
        if (D_8019D428 && !skip_cutscene &&
            ((g_Settings.D_8003CB04 & 0x800) || g_IsTimeAttackUnlocked) &&
            (g_pads[0].tapped & PAD_START)) {
            skip_cutscene = 1;
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
        if (self->step && (g_Dialogue.unk3C != 0)) {
            CutsceneRun();
        }
    }
    switch (self->step) {
    case 0:
        if (g_CastleFlags[HG_CS_DONE] != 0) {
            DestroyEntity(self);
            return;
        }
        if (SetCutsceneScript(g_CutsceneScript)) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            D_8003C704 = 1;
            g_CutsceneFlags = 0;
            D_8019D428 = 0;
            skip_cutscene = 0;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step++;
        }
        break;
    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && !skip_cutscene) {
                g_Dialogue.nextCharTimer--;
                return;
            }
            nextChar = *g_Dialogue.nextCharDialogue++;
            switch (nextChar) {
            case CSOP_END_CUTSCENE:
                self->step = 7;
                return;
            case CSOP_LINE_BREAK:
                if (skip_cutscene) {
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
                g_Dialogue.unk17 = *g_Dialogue.nextCharDialogue++;
                continue;
            case CSOP_SET_WAIT:
                g_Dialogue.nextCharTimer = *g_Dialogue.nextCharDialogue++;
                if (skip_cutscene) {
                    continue;
                }
                return;
            case CSOP_SCRIPT_UNKNOWN_4:
                if (skip_cutscene) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;
            case CSOP_SET_PORTRAIT:
                if (skip_cutscene) {
                    g_Dialogue.nextCharDialogue += 2;
                    continue;
                }
                // fake reuse of i?
                i = *g_Dialogue.nextCharDialogue++;
                nextChar2 = *g_Dialogue.nextCharDialogue++;
                prim = g_Dialogue.prim[5];
                uCoord = g_HeartDropArray[nextChar2 & 1];
                vCoord = D_801805DC[nextChar2 & 1];
                prim->clut = D_801805E0[i];
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
                g_Dialogue.clutIndex = D_801805EC[i];
                CutsceneUnk1();
                CutsceneUnk4();
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_DEFAULT;
                DrawCutsceneAvatar(i, self);
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 3;
                return;
            case CSOP_NEXT_DIALOG:
                if (skip_cutscene) {
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
                if (skip_cutscene) {
                    g_Dialogue.nextCharDialogue++;
                    g_Dialogue.nextCharDialogue++;
                    continue;
                }
                g_Dialogue.startX = *g_Dialogue.nextCharDialogue++;
                g_Dialogue.startY = *g_Dialogue.nextCharDialogue++;
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
                if (skip_cutscene) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 6;
                return;
            case CSOP_PLAY_SOUND:
                if (skip_cutscene) {
                    g_Dialogue.nextCharDialogue++;
                    g_Dialogue.nextCharDialogue++;
                    continue;
                }
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_WAIT_FOR_SOUND:
                if (skip_cutscene) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;
            case CSOP_UNK_11:
                if (skip_cutscene) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;
            case CSOP_SCRIPT_UNKNOWN_12:
                ptr = (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                CutsceneUnk6((u8*)ptr);
                continue;
            case CSOP_SCRIPT_UNKNOWN_13:
                continue;
            case CSOP_SCRIPT_UNKNOWN_14:
                ptr = (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr += (u16)0x100000;
                g_Dialogue.nextCharDialogue += *(u16*)ptr << 2;

                ptr = (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue;
                g_Dialogue.nextCharDialogue = (u8*)ptr + 0x100000;
                continue;
            case CSOP_SCRIPT_UNKNOWN_15:
                ptr = (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                ptr <<= 4;
                ptr |= (u_long)*g_Dialogue.nextCharDialogue;
                g_Dialogue.nextCharDialogue = (u8*)ptr + 0x100000;
                continue;
            case CSOP_WAIT_FOR_FLAG:
                if (!((g_CutsceneFlags >> *g_Dialogue.nextCharDialogue) & 1)) {
                    g_Dialogue.nextCharDialogue--;
                    return;
                }
                g_CutsceneFlags &= ~(1 << *g_Dialogue.nextCharDialogue);
                *g_Dialogue.nextCharDialogue++;
                continue;
            case CSOP_SET_FLAG:
                g_CutsceneFlags |= 1 << *g_Dialogue.nextCharDialogue++;
                continue;
            case CSOP_SCRIPT_UNKNOWN_18:
                g_Dialogue.unk3C = 0;
                continue;
            case CSOP_LOAD_PORTRAIT:
                if (skip_cutscene) {
                    g_Dialogue.nextCharDialogue += 5;
                } else {
                    ptr = (u_long)*g_Dialogue.nextCharDialogue++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                    ptr <<= 4;
                    ptr |= (u_long)*g_Dialogue.nextCharDialogue++;
                    ptr += 0x100000;
                    nextChar2 = g_Dialogue.nextCharDialogue++[0];
                    LoadTPage((u_long*)ptr, 1, 0, D_801805E8[nextChar2], 0x100,
                              48, 72);
                }
                continue;
            case CSOP_SCRIPT_UNKNOWN_20:
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;
            case CSOP_SCRIPT_UNKNOWN_21:
                g_CutsceneFlags = 0;
                skip_cutscene = 0;
                D_8019D428 = 0;
                continue;
            case CSOP_SCRIPT_UNKNOWN_22:
                g_CutsceneFlags &= ~(1 << *g_Dialogue.nextCharDialogue++);
                continue;
            case CSOP_SCRIPT_UNKNOWN_23:
                return;
            case CSOP_SCRIPT_UNKNOWN_24:
                if (!((g_CutsceneFlags >> *g_Dialogue.nextCharDialogue) & 1)) {
                    *g_Dialogue.nextCharDialogue--;
                    return;
                }
                *g_Dialogue.nextCharDialogue++;
                continue;
            default:
                if (skip_cutscene) {
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
            D_8019D428 = 1;
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
                prim->x2 = D_801805F4[j];
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
        DestroyEntity(self);
        g_CastleFlags[HG_CS_DONE] = 1;
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_GET_HOLYGLASSES, TIMEATTACK_SET_RECORD);
        D_8003C704 = 0;
        g_Settings.D_8003CB04 |= 0x800;
        break;
    }
}
