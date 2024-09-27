// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#include "mar.h"

extern Dialogue g_Dialogue;

#include "../../st/cutscene_unk1.h"

#include "../../st/cutscene_unk2.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_avatar.h"

#include "../../st/cutscene_unk6.h"

#include "../../st/cutscene.h"

#include "../../st/cutscene_scale_avatar.h"

extern s32 D_us_8019AE70;
extern s32 D_us_8019AF2C;
extern s32 D_8003CB04;
extern u8 D_us_801805D4[];
extern u8 D_us_801805D8[];
extern u16 D_us_801805DC[];
extern u16 D_us_801805E4[];
extern u16 D_us_801805E8[];
extern s16 D_us_801805F0[];
extern const char D_us_80181424[];

void EntityMariaCutscene(Entity* self) {
    const int PrimCount = 72;
    Primitive* prim;
#if defined(VERSION_PC) || defined(VERSION_PSP)
    RECT rect;
#else
    // BUG! the PSX version uses this uninitialized `rect` pointer
    RECT* rect;
#endif
    s32 primIndex;
    s32 i;
    s16 j;
    s16 x;
    s16 y;
    u16 nextChar;
    s32 nextChar2;
    s32 bit_shifty;

    if (self->step != 0) {
        if ((D_us_8019AF2C != 0) && (D_us_8019AE70 == 0) &&
            ((D_8003CB04 & 0x80) || (g_IsTimeAttackUnlocked != 0)) &&
            (g_pads[0].tapped & PAD_START)) {
            D_us_8019AE70 = 1;
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
        if ((self->step) && (g_Dialogue.unk3C != 0)) {
            CutsceneRun();
        }
    }
    switch (self->step) {
    case 0:
        if (g_PlayableCharacter) {
            DestroyEntity(self);
            return;
        }
        if (SetCutsceneScript(D_us_80181424) & 0xFF) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            g_CutsceneFlags = 0;
            D_us_8019AF2C = 0;
            D_us_8019AE70 = 0;
            D_8003C704 = 1;
            self->primIndex = g_Dialogue.primIndex[2];
            self->step++;
        }
        break;

    case 1:
        // this is a huge While-loop! Don't miss it!
        while (1) {
            if ((g_Dialogue.nextCharTimer != 0) && (D_us_8019AE70 == 0)) {
                g_Dialogue.nextCharTimer--;
                return;
            }

            nextChar = *g_Dialogue.nextCharDialogue++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;

            case 1:
                if (D_us_8019AE70 != 0) {
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

            case 2:
                g_Dialogue.unk17 = *g_Dialogue.nextCharDialogue++;
                continue;

            case 3:
                g_Dialogue.nextCharTimer = *g_Dialogue.nextCharDialogue++;
                if (D_us_8019AE70 != 0) {
                    continue;
                }
                return;

            case 4:
                if (D_us_8019AE70 != 0) {
                    continue;
                }
                prim = g_Dialogue.prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;

            case 5:
                if (D_us_8019AE70 != 0) {
                    g_Dialogue.nextCharDialogue += 2;
                    continue;
                }

                // fake reuse of i?
                i = *g_Dialogue.nextCharDialogue++;
                nextChar2 = *g_Dialogue.nextCharDialogue++;
                prim = g_Dialogue.prim[5];
                x = D_us_801805D4[nextChar2 & 1];
                y = D_us_801805D8[nextChar2 & 1];
                prim->clut = D_us_801805DC[i];
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
                    g_Dialogue.startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    g_Dialogue.startY + 0x24;
                g_Dialogue.clutIndex = D_us_801805E8[i];
                CutsceneUnk1();
                CutsceneUnk4();
                prim->priority = PRIORITY_DIALOGUE;
                prim->drawMode = DRAW_DEFAULT;
                DrawCutsceneAvatar(i & 0xFFFF, self);
                g_Dialogue.portraitAnimTimer = 6;
                self->step = 3;
                return;

            case 6:
                if (D_us_8019AE70 != 0) {
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

            case 7:
                if (D_us_8019AE70 != 0) {
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

            case 8:
                if (D_us_8019AE70 != 0) {
                    continue;
                }
                g_Dialogue.portraitAnimTimer = 0x18;
                self->step = 6;
                return;

            case 9:
                if (D_us_8019AE70 != 0) {
                    g_Dialogue.nextCharDialogue++;
                    g_Dialogue.nextCharDialogue++;
                    continue;
                }
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;

            case 10:
                if (D_us_8019AE70 != 0) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;

            case 11:
                if (D_us_8019AE70 != 0) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *g_Dialogue.nextCharDialogue--;
                return;

            case 12:
                bit_shifty = *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                CutsceneUnk6(bit_shifty);
                continue;

            case 13:
                continue;

            case 14:
                bit_shifty = *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                // This needs help. Casting the const to short is good.
                bit_shifty += (u16)0x100000;
                g_Dialogue.nextCharDialogue += *(u16*)bit_shifty << 2;

                bit_shifty = *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue;
                g_Dialogue.nextCharDialogue =
                    (const char*)bit_shifty + 0x100000;
                continue;

            case 15:
                bit_shifty = *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue++;
                bit_shifty <<= 4;
                bit_shifty |= *g_Dialogue.nextCharDialogue;
                g_Dialogue.nextCharDialogue =
                    (const char*)bit_shifty + 0x100000;
                continue;

            case 16:
                if (!((g_CutsceneFlags >> *g_Dialogue.nextCharDialogue) & 1)) {
                    g_Dialogue.nextCharDialogue--;
                    return;
                }
                g_CutsceneFlags &= ~(1 << *g_Dialogue.nextCharDialogue);
                *g_Dialogue.nextCharDialogue++;
                continue;

            case 17:
                g_CutsceneFlags |= 1 << *g_Dialogue.nextCharDialogue++;
                continue;

            case 18:
                g_Dialogue.unk3C = 0;
                continue;

            case 19:
                if (D_us_8019AE70 != 0) {
                    g_Dialogue.nextCharDialogue += 5;
                } else {
                    bit_shifty = *g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= *g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= *g_Dialogue.nextCharDialogue++;
                    bit_shifty <<= 4;
                    bit_shifty |= *g_Dialogue.nextCharDialogue++;
                    bit_shifty += 0x100000;
                    nextChar2 = g_Dialogue.nextCharDialogue++[0];
                    LoadTPage((u_long*)bit_shifty, 1, 0,
                              D_us_801805E4[nextChar2], 0x100, 0x30, 0x48);
                }
                continue;

            case 20:
                nextChar = *g_Dialogue.nextCharDialogue++;
                nextChar <<= 4;
                nextChar |= *g_Dialogue.nextCharDialogue++;
                g_api.PlaySfx(nextChar);
                continue;

            case 21:
                g_CutsceneFlags = 0;
                D_us_8019AE70 = 0;
                D_us_8019AF2C = 0;
                continue;

            case 22:
                g_CutsceneFlags &= ~(1 << *g_Dialogue.nextCharDialogue++);
                continue;

            case 23:
                return;

            case 24:
                if (!((g_CutsceneFlags >> *g_Dialogue.nextCharDialogue) & 1)) {
                    *g_Dialogue.nextCharDialogue--;
                    return;
                }
                *g_Dialogue.nextCharDialogue++;
                continue;
            }

            if (D_us_8019AE70) {
                g_Dialogue.nextCharDialogue++;
                continue;
            }
            g_Dialogue.nextCharTimer = g_Dialogue.unk17;
            break;
        }

        if (nextChar == ' ') {
            g_Dialogue.nextCharX += 2;
            return;
        }

#if defined(VERSION_PC) || defined(VERSION_PSP)
        rect.x = ((nextChar & 0xF) * 2) + 0x380;
        rect.y = ((nextChar & 0xF0) >> 1) + 0xF0;
        rect.w = 2;
        rect.h = 8;
#else
        rect->x = ((nextChar & 0xF) * 2) + 0x380;
        rect->y = ((nextChar & 0xF0) >> 1) + 0xF0;
        rect->w = 2;
        rect->h = 8;
#endif

        y = ((g_Dialogue.nextCharY * 0xC) + 0x180);
        x = g_Dialogue.nextCharX;
#if defined(VERSION_PC) || defined(VERSION_PSP)
        MoveImage(&rect, x, y);
#else
        MoveImage(rect, x, y);
#endif
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
        if (--g_Dialogue.portraitAnimTimer == 0) {
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
        if (--g_Dialogue.portraitAnimTimer == 0) {
            self->step = 1;
            return;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            D_us_8019AF2C = 1;
            primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, PrimCount);
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
                prim->priority = PRIORITY_DIALOGUE;
                prim->drawMode = DRAW_DEFAULT;
                prim->x2 = D_us_801805F0[j];
                prim->x3 = 0xF70;

                j++;
            }
            self->step_s++;
            break;

        case 1:
            j = false;
            prim = &g_PrimBuf[g_Dialogue.primIndex[0]];
            while (prim != NULL) {
                prim->x3 -= prim->x2;
                prim->x2 += 2;
                prim->x0 = prim->x3 / 16;
                if (prim->x0 < 5) {
                    prim->x0 = 4;
                } else {
                    j = true;
                }
                prim = prim->next;
            }

            if (!j) {
                g_api.FreePrimitives(g_Dialogue.primIndex[0]);
                g_Dialogue.primIndex[0] = -1;
                prim = g_Dialogue.prim[5];
                prim = prim->next;
                prim->blendMode = 0x11;
                prim = prim->next;
                prim->blendMode = 0x51;
                self->step_s++;
            }
            break;

        case 2:
            j = false;
            prim = g_Dialogue.prim[5];
            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 0x10;
                j = true;
            }
            if (prim->b0 >= 0x7F) {
                prim->b0 = prim->b1 = 0x7F;
            } else {
                prim->b0 = prim->b1 += 8;
                j = true;
            }

            prim = prim->next;
            if (prim->r0 < 0x10) {
                prim->r0 = prim->g0 = prim->b0 = 0x10;
            } else {
                prim->r0 = prim->g0 = prim->b0 -= 0xF;
                j = true;
            }
            if (!j) {
                self->step = 1;
            }
        }
        break;

    case 6:
        prim = g_Dialogue.prim[5];
        prim = prim->next;
        if (--g_Dialogue.portraitAnimTimer >= 0xC) {
            prim = prim->next;
            prim->u0 -= 20;
            if (g_Dialogue.portraitAnimTimer & 1) {
                prim->u0--;
            }
        } else {
            if (g_Dialogue.portraitAnimTimer == 0) {
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
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_FIRST_MARIA_MEET, TIMEATTACK_SET_RECORD);
        D_8003C704 = 0;
        g_Settings.D_8003CB04 |= 0x80;
        DestroyEntity(self);
        break;
    }
}

// func_psp_092467F8
void func_us_8018C90C(Entity* self) {
    Entity* player;
    Tilemap* tilemap; // unused but shows up in the psp code.

    tilemap = &g_Tilemap;
    player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A60);
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.unk0 = 1;
        g_Player.padSim = PAD_RIGHT;
        g_Player.D_80072EFC = 1;
        break;
    case 1:
        if ((player->posX.i.hi >= 0x21) && !(g_CutsceneFlags & 1)) {
            g_CutsceneFlags |= 1;
        }
        if (player->posX.i.hi >= 0xB1) {
            g_Player.padSim = PAD_LEFT;
            self->step++;
        } else {
            g_Player.padSim = PAD_RIGHT;
        }
        g_Player.D_80072EFC = 1;
        break;
    case 2:
        if (g_CutsceneFlags & 2) {
            D_8003C8B8 = 1;

            if (g_unkGraphicsStruct.unk0) {
                g_unkGraphicsStruct.unk0 = 0;
            }

            DestroyEntity(self);
            g_Statues[LEFT_STATUE] ^= 1; // suspicious, everywhere else we're
                                         // treating this like a boolean.
        }

        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}
