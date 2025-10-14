// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

// BSS
static s32 D_801BB010;
static s32 D_801BB014;
static u8 D_801BB018[0xE0];
static s32 D_801804D0 = 0;

u8 D_801804D4[] = {STAGE_MEMORYCARD, STAGE_CAT};
const char* D_801804D8[] = {
    "NORMAL      ",
    "SPECIAL     ",
};
const char D_801A7B80[] = "SELECT ！！";

void HandleTitleScreen(void) {
    Primitive* prim;
    Primitive* prim15;
    s32 i;

    func_801B1F34();
    switch (g_GameEngineStep) {
    case 0:
        if (g_UseDisk != 0) {
            g_CdStep = 1;
            g_LoadFile = 0x8003;
            g_LoadOvlIdx = 0xFF;
        }
        D_801BB010 = g_api.AllocPrimitives(PRIM_SPRT, 0x11);
        prim = &g_PrimBuf[D_801BB010];
        for (i = 0; i < 3; i++, prim = prim->next) {
            prim->x0 = i * 0x80 + 0x70;
            prim->y0 = 0xA8;
            prim->u0 = 0x80;
            prim->v0 = i * 0x10 + 0xB0;
            prim->u1 = 0x80;
            if (i == 2) {
                prim->u1 = 0x20;
            }
            prim->v1 = 0x10;
            prim->tpage = 0x18;
            prim->clut = 0x20;
            prim->priority = 1;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 4; i++, prim = prim->next) {
            prim->x0 = i * 0x80 + 0xC;
            prim->y0 = 0xD6;
            prim->u0 = 0x80;
            prim->v0 = i * 8 + 0x90;
            prim->u1 = 0x80;
            if (i == 3) {
                prim->u1 = 0x64;
            }
            prim->v1 = 8;
            prim->tpage = 0x18;
            prim->clut = 0x21;
            prim->priority = 1;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 4; i++, prim = prim->next) {
            prim->x0 = i * 0x80;
            prim->u1 = 0x80;
            prim->v1 = 0xF0;
            prim->tpage = i + 0x88;
            prim->clut = 0x10;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 4; i++, prim = prim->next) {
            prim->x0 = i * 0x80;
            prim->u1 = 0x80;
            prim->y0 = 0x18;
            prim->v1 = 0x88;
            prim->tpage = i + 0x8C;
            prim->priority = 2;
            prim->drawMode = DRAW_HIDE;
        }
        prim->x0 = 0x101;
        prim->y0 = 0x60;
        prim->u1 = 0xFF;
        prim->v1 = 0x90;
        prim->tpage = 0x18;
        prim->clut = 0x22;
        prim->priority = 1;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        prim->v0 = 0x90;
        prim->u1 = 0x78;
        prim->v1 = 0x40;
        prim->tpage = 0x18;
        prim->clut = 0x22;
        prim->priority = 1;
        prim->drawMode = DRAW_HIDE;
        func_801B18F4();
        D_801BB014 = 0;
        g_GameEngineStep++;
        break;

    case 1:
        SetTitleDisplayBuffer();
        prim = &g_PrimBuf[D_801BB010];
        i = 0;
        D_801BB014 += 8;
        while (prim != NULL) {
            prim->drawMode = DRAW_COLORS;
            SetPrimGrey(prim, D_801BB014);
            if (i == 7 || i == 8 || i == 9 || i == 10) {
                prim->r0 = D_801BB014 * 3 / 4;
                prim->g0 = D_801BB014 * 7 / 8;
                prim->b0 = D_801BB014 * 3 / 4;
            }
            if (i == 15 || i == 16) {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
            prim = prim->next;
            i++;
        }
        if (D_801BB014 == 0x80) {
            D_801804D0 = 0x800;
            g_GameEngineStep++;
        }
        break;

    case 2:
        prim = &g_PrimBuf[D_801BB010];
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i < 3) {
                prim->drawMode = DRAW_HIDE;
                if (g_Timer & 0x30) {
                    prim->drawMode = DRAW_DEFAULT;
                }
            }
            if (i < 15 || i > 16) {
                continue;
            }
            if (i == 15) {
                prim15 = prim;
            }
            switch (prim->p1) {
            case 0:
                if (i == 0xF) {
                    if (!(rand() & 0x7F)) {
                        prim->p2 = 6;
                        prim->tpage = 0x19;
                        prim->p1++;
                    }
                } else if (
                    (prim15->p1 >= 2) || (prim15->p1 && (prim15->p2 < 3))) {
                    prim->p2 = (rand() & 3) + 6;
                    prim->tpage = 0x19;
                    prim->p1++;
                }
                break;

            case 1:
                if (!--prim->p2) {
                    prim->p2 = 6;
                    prim->tpage = 0x1A;
                    prim->p1++;
                }
                break;

            case 2:
                if (!--prim->p2) {
                    prim->p2 = (rand() & 7) + 6;
                    prim->tpage = 0x1B;
                    prim->p1++;
                }
                break;

            case 3:
                if (!--prim->p2) {
                    prim->p2 = 5;
                    prim->tpage = 0x1A;
                    prim->p1++;
                }
                break;

            case 4:
                if (!--prim->p2) {
                    prim->p2 = 5;
                    prim->tpage = 0x19;
                    prim->p1++;
                }
                break;

            case 5:
                if (!--prim->p2) {
                    prim->p2 = 6;
                    prim->tpage = 0x18;
                    prim->p1++;
                }
                break;

            case 6:
                if (!--prim->p2) {
                    if (i == 0x10) {
                        prim->p1 = 0;
                    } else {
                        prim->p1++;
                        prim->p2 = 6;
                        if (rand() & 3) {
                            prim->p1 = 1;
                            prim->tpage = 0x19;
                        }
                    }
                }
                break;

            case 7:
                if (!--prim->p2) {
                    prim->p1 = 0;
                }
                break;
            }
            if (i == 0x10) {
                if (prim->tpage == 0x18) {
                    prim->u1 = 0x78;
                } else {
                    prim->u1 = 0x70;
                }
            }
        }
        if (g_pads[0].tapped & PAD_START) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        break;

    case 3:
        g_GameEngineStep = 6;
        break;

    case 4:
        if (g_pads[0].tapped & (PAD_RIGHT | PAD_DOWN)) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4++;
            if (D_800987B4 >= 2) {
                D_800987B4 = 0;
            }
        }
        if (g_pads[0].tapped & (PAD_UP | PAD_LEFT)) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4--;
            if (D_800987B4 < 0) {
                D_800987B4 = 1;
            }
        }
        prim = &g_PrimBuf[D_801BB010];
        if (g_Timer & 0x1C) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        g_StageId = D_801804D4[D_800987B4];
        func_801B1F4C(1);
        func_801B259C(D_801804D8[D_800987B4], 1);
        if (g_pads[0].tapped & (PAD_START | PAD_CIRCLE)) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        break;

    case 5:
        func_801B18F4();
        func_801B19F4();
        func_801B1DA8();
        g_api.FreePrimitives(D_801BB010);
        STRCPY(g_Status.saveName, "alucard");
        if (g_StageId == STAGE_ST0) {
            SetGameState(Game_VideoPlayback);
        } else if (g_StageId == STAGE_MEMORYCARD) {
            SetGameState(Game_MainMenu);
        } else {
            SetGameState(Game_NowLoading);
            g_GameStep = 2;
        }
        break;

    case 6:
        prim = &g_PrimBuf[D_801BB010];
        i = 0;
        D_801BB014 -= 8;
        while (prim != NULL) {
            prim->drawMode = DRAW_COLORS;
            SetPrimGrey(prim, D_801BB014);
            if (i == 15 || i == 16) {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
            prim = prim->next;
            i++;
        }
        if (D_801BB014 == 0) {
            g_StageId = STAGE_MEMORYCARD;
            g_GameEngineStep = 5;
        }
        return;
    }
}
