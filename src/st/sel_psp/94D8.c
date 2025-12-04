// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sel/sel.h"

extern s32 D_psp_0924F800;
extern s32 D_psp_0924F808;

// BSS
static s32 D_801BB010;
static s32 D_psp_09285E70;
static s32 D_801BB014;
static u8 D_801BB018[0x100];
static s32 D_801804D0 = 0;

// DATA
static u8 D_801804D4[] = {
    STAGE_MEMORYCARD, STAGE_ST0,  STAGE_NO3,  STAGE_NP3,  STAGE_NZ0,
    STAGE_DAI,        STAGE_NO0,  STAGE_NO1,  STAGE_LIB,  STAGE_NO4,
    STAGE_NZ1,        STAGE_ARE,  STAGE_CAT,  STAGE_CHI,  STAGE_NO2,
    STAGE_TOP,        STAGE_CEN,  STAGE_RNO3, STAGE_RNZ0, STAGE_RDAI,
    STAGE_RNO0,       STAGE_RNO1, STAGE_RLIB, STAGE_RNO4, STAGE_RNZ1,
    STAGE_RARE,       STAGE_RCAT, STAGE_RCHI, STAGE_RNO2, STAGE_RTOP,
    STAGE_RCEN,       0x00,       0x00,
};
static char* D_801804D8[] = {
    "メモリーカード　　　　",
    "過去（リヒター編）　　",
    "城入り口　　　　　　　",
    "城に戻る　　　　　　　",
    "錬金研究棟　　　　　　",
    "礼拝堂　　　　　　　　",
    "大理石の廊下　　　　　",
    "崖側外壁　　　　　　　",
    "蔵書庫　　　　　　　　",
    "地下水脈　　　　　　　",
    "時計塔　　　　　　　　",
    "闘技場　　　　　　　　",
    "カタコンベ　　　　　　",
    "えん道　　　　　　　　",
    "オルロックの間　　　　",
    "最上部　　　　　　　　",
    "中央部　　　　　　　　",
    "逆　城入り口　　　　　",
    "逆　錬金研究棟　　　　",
    "逆　礼拝堂　　　　　　",
    "逆　大理石の廊下　　　",
    "逆　崖側外壁　　　　　",
    "逆　蔵書庫　　　　　　",
    "逆　地下水脈　　　　　",
    "逆　時計塔　　　　　　",
    "逆　闘技場　　　　　　",
    "逆　カタコンベ　　　　",
    "逆　えん道　　　　　　",
    "逆　オルロックの間　　",
    "逆　最上部　　　　　　",
    "逆　中央部　　　　　　",
    NULL,
    NULL,
};

void HandleTitleScreen(void) {
    RECT rect;
    Primitive* prim;
    Primitive* prim15;
    s32 i;
    s32 var_s3;

    if (0) {
        s32 var_s4 = 0; // fake
    }

    func_801B1F34();
    switch (g_GameEngineStep) {
    case 0:
        if (g_UseDisk != 0) {
            g_CdStep = 1;
            g_LoadFile = 0x8003;
            g_LoadOvlIdx = 0xFF;
        }
        rect.x = 0x220;
        rect.y = 0x1AF;
        rect.w = 2;
        rect.h = 1;
        StoreImage(&rect, (u_long*)D_801BB018);
        func_psp_09237CB8();
        D_801BB010 = g_api.AllocPrimitives(PRIM_SPRT, 0x15);
        prim = &g_PrimBuf[D_801BB010];
        for (i = 0; i < 3; i++, prim = prim->next) {
            prim->x0 = i * 0x80 + 0x70;
            prim->y0 = 0xA0;
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
            prim->y0 = 8;
            prim->v1 = 0x80;
            switch (i) {
            case 0:
            case 1:
                prim->tpage = (D_psp_0924F800 | 0x80) + i;
                break;
            case 2:
            case 3:
                prim->tpage = ((D_psp_0924F808 | 0x80) + i) - 2;
                break;
            }
            prim->clut = 0;
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
        prim = prim->next;

        for (i = 0; i < 2; i++, prim = prim->next) {
            prim->x0 = (i * 0x80) + 0xA0;
            prim->y0 = 0x9C;
            if (i == 0) {
                prim->u0 = 0;
                prim->v0 = 0;
                prim->u1 = 0x80;
                prim->v1 = 0x10;
                prim->tpage = 0x1F;
            } else if (g_UserLanguage != 1) {
                prim->u0 = 0;
                prim->v0 = 0x10;
                prim->u1 = 0x80;
                prim->v1 = 0x14;
                prim->tpage = 0x1F;
            } else {
                prim->u0 = 0x85;
                prim->v0 = 0xC0;
                prim->u1 = 0x24;
                prim->v1 = 0x10;
                prim->tpage = 0x18;
            }
            prim->clut = 0x20;
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 1; i++, prim = prim->next) {
            prim->x0 = 0xA0;
            prim->y0 = 0xBC;
            prim->u0 = 0;
            prim->v0 = 0x60;
            prim->u1 = 0x80;
            prim->v1 = 0x10;
            prim->tpage = 0x1F;
            prim->clut = 0x20;
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }
        for (i = 0; i < 1; i++, prim = prim->next) {
            prim->x0 = 0x78;
            prim->y0 = 0x9C;
            prim->u0 = 0x30;
            prim->v0 = 0x50;
            prim->u1 = 0x20;
            prim->v1 = 0x10;
            prim->tpage = 0x1F;
            prim->clut = 0x20;
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }
        D_psp_09285E70 = 0;
        func_801B18F4();
        D_801BB014 = 0;
        g_GameEngineStep++;
        func_psp_0891CEB8(0x200, 0xF0);
        func_psp_0891CEB8(0x200, 0xF1);
        func_psp_08925F7C(0x200, 0xF2, 0x10, 1);
        func_psp_08925F7C(0x210, 0xF2, 0x10, 1);
        func_psp_08925F7C(0x220, 0xF2, 0x10, 1);
        break;

    case 1:
        SetTitleDisplayBuffer();
        prim = &g_PrimBuf[D_801BB010];
        i = 0;
        D_801BB014 += 8;
        while (prim != NULL) {
            prim->drawMode = DRAW_COLORS;
            SetPrimGrey(prim, D_801BB014);
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
            if ((i != 15) && (i != 16)) {
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
        var_s3 = 0;
        if (g_pads[0].tapped & PAD_START) {
            var_s3++;
        }
        if (var_s3 != 0) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        break;

    case 3:
        g_GameEngineStep = 7;
        break;

    case 4:
        if (g_pads[0].tapped & (PAD_RIGHT | PAD_DOWN)) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4++;
            if (D_800987B4 >= 0x21) {
                D_800987B4 = 0;
            }
        }
        if (g_pads[0].tapped & (PAD_UP | PAD_LEFT)) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4--;
            if (D_800987B4 < 0) {
                D_800987B4 = 0x20;
            }
        }
        g_StageId = D_801804D4[D_800987B4];
        func_801B1F4C(1);
        func_90F0DD8(D_801804D8[D_800987B4], 1);
        if (g_pads[0].tapped & (D_psp_08B42050 | PAD_START)) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        break;

    case 5:
        func_801B18F4();
        func_801B19F4();
        func_801B1DA8();
        g_api.FreePrimitives(D_801BB010);
        strcpy(g_Status.saveName, "alucard");
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
        prim = &g_PrimBuf[D_801BB010] + 3;
        i = 3;
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
        if (D_psp_09285E70 == 1) {
            SetGameState(Game_Boot);
        }
        break;

    case 7:
        prim = &g_PrimBuf[D_801BB010];
        for (i = 0; i < 3; i++, prim = prim->next) {
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }
        prim = &g_PrimBuf[D_801BB010] + 17;
        for (i = 0; i < 3; i++, prim = prim->next) {
            prim->priority = 2;
        }
        prim = &g_PrimBuf[D_801BB010] + 20;
        for (i = 0; i < 1; i++, prim = prim->next) {
            prim->priority = 2;
            prim->x0 = 0x78;
            prim->y0 = (D_psp_09285E70 << 5) + 0x9C;
        }
        if (g_pads[0].tapped & PAD_DOWN) {
            D_psp_09285E70++;
            if (D_psp_09285E70 >= 2) {
                D_psp_09285E70 = 1;
            } else {
                g_api.PlaySfx(SFX_UI_MOVE);
            }
        }
        if (g_pads[0].tapped & PAD_UP) {
            D_psp_09285E70--;
            if (D_psp_09285E70 < 0) {
                D_psp_09285E70 = 0;
            } else {
                g_api.PlaySfx(SFX_UI_MOVE);
            }
        }
        if (g_pads[0].tapped & (D_psp_08B42050 | PAD_START)) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep = 6;
        }
        break;
    }
}
