// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"
#include "../../st/pfn_entity_update.h"
#include <cutscene.h>

#include "mar.h"

static const char* actor_names[] = {_S("Alucard"), _S("Maria")};

// bss
static s32 OVL_EXPORT(SkipCutscene);
static Dialogue OVL_EXPORT(Dialogue);
static s32 D_us_8019AEB8[26];
static u32 OVL_EXPORT(CutsceneFlags);
STATIC_PAD_BSS(4);
u16 g_Statues[];
static s16 D_us_8019AF2A;
static s32 D_us_8019AF2C;

#include "../../st/cutscene_unk1.h"

#include "../../st/set_cutscene_script.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

#include "../../st/cutscene_actor_name.h"

#include "../../st/set_cutscene_end.h"

#include "../../st/cutscene_run.h"

#include "../../st/cutscene_scale_avatar.h"

extern u8 D_us_801805D4[];
extern u8 D_us_801805D8[];
extern u16 D_us_801805DC[];
extern u16 D_us_801805E4[];
extern u16 D_us_801805E8[];
extern s16 D_us_801805F0[];

extern u8 OVL_EXPORT(cutscene_data)[];
void OVL_EXPORT(EntityCutscene)(Entity* self) {
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
    u_long ptr;

    if (self->step) {
        if ((D_us_8019AF2C != 0) && !OVL_EXPORT(SkipCutscene) &&
            ((g_Settings.D_8003CB04 & 0x80) || g_GameClearFlag) &&
            (g_pads[0].tapped & PAD_START)) {
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
        if (self->step && (OVL_EXPORT(Dialogue).unk3C != 0)) {
            CutsceneRun();
        }
    }
    switch (self->step) {
    case 0:
        if (g_PlayableCharacter) {
            DestroyEntity(self);
            return;
        }
        if (SetCutsceneScript(OVL_EXPORT(cutscene_data)) & 0xFF) {
            self->flags |= FLAG_HAS_PRIMS | FLAG_UNK_2000;
            OVL_EXPORT(CutsceneFlags) = 0;
            D_us_8019AF2C = 0;
            OVL_EXPORT(SkipCutscene) = 0;
            g_CutsceneHasControl = 1;
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
            case 0:
                self->step = 7;
                return;

            case 1:
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

            case 2:
                OVL_EXPORT(Dialogue).unk17 = *OVL_EXPORT(Dialogue).scriptCur++;
                continue;

            case 3:
                OVL_EXPORT(Dialogue).nextCharTimer =
                    *OVL_EXPORT(Dialogue).scriptCur++;
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                return;

            case 4:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                prim = OVL_EXPORT(Dialogue).prim[0];
                for (i = 0; i < 5; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                return;

            case 5:
                if (OVL_EXPORT(SkipCutscene)) {
                    OVL_EXPORT(Dialogue).scriptCur += 2;
                    continue;
                }

                // fake reuse of i?
                i = *OVL_EXPORT(Dialogue).scriptCur++;
                nextChar2 = *OVL_EXPORT(Dialogue).scriptCur++;
                prim = OVL_EXPORT(Dialogue).prim[5];
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
                    OVL_EXPORT(Dialogue).startX - 0x1E;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                    OVL_EXPORT(Dialogue).startY + 0x24;
                OVL_EXPORT(Dialogue).clutIndex = D_us_801805E8[i];
                CutsceneUnk1();
                CutsceneUnk4();
                prim->priority = PRIORITY_DIALOGUE;
                prim->drawMode = DRAW_DEFAULT;
                DrawCutsceneActorName(i & 0xFFFF, self);
                OVL_EXPORT(Dialogue).portraitAnimTimer = 6;
                self->step = 3;
                return;

            case 6:
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

            case 7:
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

            case 8:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                OVL_EXPORT(Dialogue).portraitAnimTimer = 0x18;
                self->step = 6;
                return;

            case 9:
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

            case 10:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                if (g_api.func_80131F68() != false) {
                    continue;
                }
                *OVL_EXPORT(Dialogue).scriptCur--;
                return;

            case 11:
                if (OVL_EXPORT(SkipCutscene)) {
                    continue;
                }
                if (g_api.func_80131F68() != true) {
                    continue;
                }
                *OVL_EXPORT(Dialogue).scriptCur--;
                return;

            case 12:
                ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                SetCutsceneEnd(ptr);
                continue;

            case 13:
                continue;

            case 14:
                ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                // This needs help. Casting the const to short is good.
                ptr += (u16)0x100000;
                OVL_EXPORT(Dialogue).scriptCur += *(u16*)ptr << 2;

                ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur;
                OVL_EXPORT(Dialogue).scriptCur = (const char*)ptr + 0x100000;
                continue;

            case 15:
                ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                ptr <<= 4;
                ptr |= *OVL_EXPORT(Dialogue).scriptCur;
                OVL_EXPORT(Dialogue).scriptCur = (const char*)ptr + 0x100000;
                continue;

            case 16:
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

            case 17:
                OVL_EXPORT(CutsceneFlags) |=
                    1 << *OVL_EXPORT(Dialogue).scriptCur++;
                continue;

            case 18:
                OVL_EXPORT(Dialogue).unk3C = 0;
                continue;

            case 19:
                if (OVL_EXPORT(SkipCutscene)) {
                    OVL_EXPORT(Dialogue).scriptCur += 5;
                } else {
                    ptr = *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr <<= 4;
                    ptr |= *OVL_EXPORT(Dialogue).scriptCur++;
                    ptr += 0x100000;
                    nextChar2 = OVL_EXPORT(Dialogue).scriptCur++[0];
                    LoadTPage((u_long*)ptr, 1, 0, D_us_801805E4[nextChar2],
                              0x100, 0x30, 0x48);
                }
                continue;

            case 20:
                nextChar = *OVL_EXPORT(Dialogue).scriptCur++;
                nextChar <<= 4;
                nextChar |= *OVL_EXPORT(Dialogue).scriptCur++;
                g_api.PlaySfx(nextChar);
                continue;

            case 21:
                OVL_EXPORT(CutsceneFlags) = 0;
                OVL_EXPORT(SkipCutscene) = 0;
                D_us_8019AF2C = 0;
                continue;

            case 22:
                OVL_EXPORT(CutsceneFlags) &=
                    ~(1 << *OVL_EXPORT(Dialogue).scriptCur++);
                continue;

            case 23:
                return;

            case 24:
                if (!((OVL_EXPORT(CutsceneFlags) >>
                       *OVL_EXPORT(Dialogue).scriptCur) &
                      1)) {
                    *OVL_EXPORT(Dialogue).scriptCur--;
                    return;
                }
                *OVL_EXPORT(Dialogue).scriptCur++;
                continue;
            }

            if (OVL_EXPORT(SkipCutscene)) {
                OVL_EXPORT(Dialogue).scriptCur++;
                continue;
            }
            OVL_EXPORT(Dialogue).nextCharTimer = OVL_EXPORT(Dialogue).unk17;
            break;
        }

        if (nextChar == ' ') {
            OVL_EXPORT(Dialogue).nextCharX += 2;
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

        y = ((OVL_EXPORT(Dialogue).nextCharY * 0xC) + 0x180);
        x = OVL_EXPORT(Dialogue).nextCharX;
#if defined(VERSION_PC) || defined(VERSION_PSP)
        MoveImage(&rect, x, y);
#else
        MoveImage(rect, x, y);
#endif
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
        if (--OVL_EXPORT(Dialogue).portraitAnimTimer == 0) {
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
        if (--OVL_EXPORT(Dialogue).portraitAnimTimer == 0) {
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

            OVL_EXPORT(Dialogue).primIndex[0] = primIndex;
            for (prim = &g_PrimBuf[primIndex], j = 0; prim != NULL;
                 prim = prim->next) {
                prim->r0 = prim->r1 = 0x7F;
                prim->b0 = prim->b1 = prim->g0 = prim->g1 = 0;
                prim->x0 = prim->x1 = 0xF7;
                prim->y0 = prim->y1 = OVL_EXPORT(Dialogue).startY + j;
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
            prim = &g_PrimBuf[OVL_EXPORT(Dialogue).primIndex[0]];
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
                g_api.FreePrimitives(OVL_EXPORT(Dialogue).primIndex[0]);
                OVL_EXPORT(Dialogue).primIndex[0] = -1;
                prim = OVL_EXPORT(Dialogue).prim[5];
                prim = prim->next;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                prim = prim->next;
                prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                self->step_s++;
            }
            break;

        case 2:
            j = false;
            prim = OVL_EXPORT(Dialogue).prim[5];
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
        prim = OVL_EXPORT(Dialogue).prim[5];
        prim = prim->next;
        if (--OVL_EXPORT(Dialogue).portraitAnimTimer >= 0xC) {
            prim = prim->next;
            prim->u0 -= 20;
            if (OVL_EXPORT(Dialogue).portraitAnimTimer & 1) {
                prim->u0--;
            }
        } else {
            if (OVL_EXPORT(Dialogue).portraitAnimTimer == 0) {
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
        g_CutsceneHasControl = 0;
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
        InitializeEntity(OVL_EXPORT(EInitSpawner));
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = PAD_RIGHT;
        g_Player.demo_timer = 1;
        break;
    case 1:
        if ((player->posX.i.hi >= 0x21) && !(OVL_EXPORT(CutsceneFlags) & 1)) {
            OVL_EXPORT(CutsceneFlags) |= 1;
        }
        if (player->posX.i.hi >= 0xB1) {
            g_Player.padSim = PAD_LEFT;
            self->step++;
        } else {
            g_Player.padSim = PAD_RIGHT;
        }
        g_Player.demo_timer = 1;
        break;
    case 2:
        if (OVL_EXPORT(CutsceneFlags) & 2) {
            g_PauseAllowed = true;

            if (g_unkGraphicsStruct.pauseEnemies) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }

            DestroyEntity(self);
            g_Statues[LEFT_STATUE] ^= 1; // suspicious, everywhere else we're
                                         // treating this like a boolean.
        }

        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    }
}
