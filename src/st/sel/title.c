// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

// BSS
static s32 D_801BB010;
static s32 D_801BB014;
#if REGION == REGION_EU
static u8 D_801BB018[0x60];
u16 g_DialoguePalTimer;
static s32 D_eu_801BB178[0x20];
#else
static u8 D_801BB018[0xE0];
#endif
static s32 D_801804D0 = 0;

// DATA
#if REGION == REGION_JP

#if VERSION != VER_JP10
#define NUM_SELECT_STAGES 33
#else
#define NUM_SELECT_STAGES 16
#endif

static u8 D_801804D4[NUM_SELECT_STAGES] = {
    STAGE_MEMORYCARD, STAGE_ST0,  STAGE_NO3,  STAGE_NP3,  STAGE_NZ0,
    STAGE_DAI,        STAGE_NO0,  STAGE_NO1,  STAGE_LIB,  STAGE_NO4,
    STAGE_NZ1,        STAGE_ARE,  STAGE_CAT,  STAGE_CHI,  STAGE_NO2,
    STAGE_TOP,
#if VERSION != VER_JP10
    STAGE_CEN,        STAGE_RNO3, STAGE_RNZ0, STAGE_RDAI, STAGE_RNO0,
    STAGE_RNO1,       STAGE_RLIB, STAGE_RNO4, STAGE_RNZ1, STAGE_RARE,
    STAGE_RCAT,       STAGE_RCHI, STAGE_RNO2, STAGE_RTOP, STAGE_RCEN,
#endif
};
static char* D_801804D8[NUM_SELECT_STAGES] = {
    "メモリーカード　　　　", "過去（リヒター編）　　",
    "城入り口　　　　　　　", "城に戻る　　　　　　　",
    "錬金研究棟　　　　　　", "礼拝堂　　　　　　　　",
    "大理石の廊下　　　　　", "崖側外壁　　　　　　　",
    "蔵書庫　　　　　　　　", "地下水脈　　　　　　　",
    "時計塔　　　　　　　　", "闘技場　　　　　　　　",
    "カタコンベ　　　　　　", "えん道　　　　　　　　",
    "オルロックの間　　　　", "最上部　　　　　　　　",
#if VERSION != VER_JP10
    "中央部　　　　　　　　", "逆　城入り口　　　　　",
    "逆　錬金研究棟　　　　", "逆　礼拝堂　　　　　　",
    "逆　大理石の廊下　　　", "逆　崖側外壁　　　　　",
    "逆　蔵書庫　　　　　　", "逆　地下水脈　　　　　",
    "逆　時計塔　　　　　　", "逆　闘技場　　　　　　",
    "逆　カタコンベ　　　　", "逆　えん道　　　　　　",
    "逆　オルロックの間　　", "逆　最上部　　　　　　",
    "逆　中央部　　　　　　",
#endif
};
#else
static u8 D_801804D4[] = {
    STAGE_MEMORYCARD,
    STAGE_CAT,
};
static char* D_801804D8[] = {
    "NORMAL      ",
    "SPECIAL     ",
};
#endif

#if VERSION >= VER_JP12
static void AnimateTitleLogo(Primitive* prim, s32 i) {
    Primitive* prim15;

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
        } else if ((prim15->p1 >= 2) || (prim15->p1 && (prim15->p2 < 3))) {
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

// x, y, u, v, w, h of the sound mode option sprites
static s32 soundModeSprites[][6] = {
    {0x90, 0xA0, 0x00, 0x90, 0x58, 0x10},
    {0xF0, 0xA0, 0x00, 0xA0, 0x90, 0x10},
};
#endif

#if REGION == REGION_JP
const char D_801A7B80[] = "ステージセレクト";
#else
const char D_801A7B80[] = "SELECT ！！";
#endif

void HandleTitleScreen(void) {
    Primitive* prim;
    Primitive* prim15;
    s32 i;
#if VERSION == VER_USPROTO
    s32 grey;
    s32 done;
#endif
#if VERSION >= VER_JP12
    s32* sprite;
#endif

    func_801B1F34();
    switch (g_GameEngineStep) {
    case 0:
        if (g_UseDisk != 0) {
            g_CdStep = 1;
            g_LoadFile = 0x8003;
            g_LoadOvlIdx = 0xFF;
        }
#if VERSION >= VER_JP12
        D_801BB010 = g_api.AllocPrimitives(PRIM_SPRT, 0x13);
#else
        D_801BB010 = g_api.AllocPrimitives(PRIM_SPRT, 0x11);
#endif
        prim = &g_PrimBuf[D_801BB010];
        for (i = 0; i < 3; i++, prim = prim->next) {
            prim->x0 = i * 0x80 + 0x70;
#if REGION == REGION_JP
            prim->y0 = 0xA0;
#else
            prim->y0 = 0xA8;
#endif
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
#if VERSION == VER_JP12
            prim->u1 = 0x80;
            prim->y0 = 0x30;
            prim->v1 = 0x68;
#elif REGION == REGION_JP
            prim->y0 = 0x30;
            prim->u1 = 0x80;
            prim->v1 = 0x68;
#else
            prim->u1 = 0x80;
            prim->y0 = 0x18;
            prim->v1 = 0x88;
#endif
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
#if VERSION >= VER_JP12
        prim = prim->next;
        sprite = soundModeSprites[0];
        for (i = 0; i < 2; i++, prim = prim->next) {
            prim->x0 = *sprite++;
            prim->y0 = *sprite++;
            prim->u0 = *sprite++;
            prim->v0 = *sprite++;
            prim->u1 = *sprite++;
            prim->v1 = *sprite++;
            prim->tpage = 0x1C;
            prim->clut = 0x20;
            prim->priority = 2;
            prim->drawMode = DRAW_HIDE;
        }
#endif
        func_801B18F4();
        D_801BB014 = 0;
#if VERSION >= VER_JP12
        g_Settings.isSoundMono = 0;
        g_api.ApplySoundMode();
#endif
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
#if IS_VER_INTL
            if (i == 7 || i == 8 || i == 9 || i == 10) {
                prim->r0 = D_801BB014 * 3 / 4;
                prim->g0 = D_801BB014 * 7 / 8;
                prim->b0 = D_801BB014 * 3 / 4;
            }
#endif
            if (i == 15 || i == 16) {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
#if VERSION >= VER_JP12
            if (i >= 17) {
                prim->drawMode = DRAW_HIDE;
            }
#endif
            prim = prim->next;
            i++;
        }
        if (D_801BB014 == 0x80) {
            D_801804D0 = 0x800;
            g_GameEngineStep++;
        }
        break;

    case 2:
#if VERSION >= VER_JP12
        prim = &g_PrimBuf[D_801BB010];
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i < 3) {
                prim->drawMode = DRAW_HIDE;
                if (g_Timer & 0x30) {
                    prim->drawMode = DRAW_DEFAULT;
                }
            }
            if (i == 15 || i == 16) {
                AnimateTitleLogo(prim, i);
            }
            if (i >= 17) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        if (g_pads[0].tapped & PAD_START) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        if (g_pads[0].tapped & PAD_SELECT) {
            g_api.PlaySfx(SFX_UI_MP_FULL);
            g_GameEngineStep = 7;
        }
        break;
#else
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
        if (g_pads[0].tapped & PAD_START) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        break;
#endif

    case 3:
#if VERSION != VER_USPROTO
        g_GameEngineStep = 6;
#else
        i = 0;
        D_8003C730 = 0;
        D_80097924 = -1;
        prim = &g_PrimBuf[D_801BB010];
        done = 0;
        while (prim != NULL) {
            if (i < 3) {
                prim->drawMode = DRAW_DEFAULT;
                if (g_Timer & 4) {
                    prim->drawMode = DRAW_HIDE;
                }
            } else if ((i >= 3 && i < 11) || i == 15 || i == 16) {
                grey = prim->r0 - 2;
                SetPrimGrey(prim, grey);
                if (i == 16 && grey <= 0) {
                    done = 1;
                }
            }
            prim = prim->next;
            i++;
        }
        if (done) {
            g_api.func_800EA5E4(ANIMSET_DRA(0));
            prim = &g_PrimBuf[D_801BB010];
            prim->x0 = 0x90;
            prim->y0 = 0xA0;
            prim->u0 = 0;
            prim->v0 = 0;
            prim->u1 = 0xF0;
            prim->v1 = 0x10;
            prim->tpage = 0x1F;
            prim->clut = PAL_UNK_1A1;
            prim->priority = 0;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            prim->x0 = 0xA0;
            prim->y0 = 0xB0;
            prim->u0 = 0;
            prim->v0 = 0x10;
            prim->u1 = 0xF0;
            prim->v1 = 0x10;
            prim->tpage = 0x1F;
            prim->clut = PAL_UNK_1A1;
            prim->priority = 0;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            func_801B259C(D_801A7B80, 0);
            g_GameEngineStep++;
        }
#endif
        break;

    case 4:
        if (g_pads[0].tapped & (PAD_RIGHT | PAD_DOWN)) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4++;
            if (D_800987B4 >= LEN(D_801804D4)) {
                D_800987B4 = 0;
            }
        }
        if (g_pads[0].tapped & (PAD_UP | PAD_LEFT)) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4--;
            if (D_800987B4 < 0) {
                D_800987B4 = LEN(D_801804D4) - 1;
            }
        }
#if VERSION >= VER_USPROTO
        prim = &g_PrimBuf[D_801BB010];
        if (g_Timer & 0x1C) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
#endif
        g_StageId = D_801804D4[D_800987B4];
        func_801B1F4C(1);
#if REGION == REGION_JP
        func_801B2564(D_801804D8[D_800987B4], 1);
#else
        func_801B259C(D_801804D8[D_800987B4], 1);
#endif
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
        prim = &g_PrimBuf[D_801BB010];
        i = 0;
        D_801BB014 -= 8;
        while (prim != NULL) {
            prim->drawMode = DRAW_COLORS;
#if VERSION >= VER_JP12
            if (i >= 17) {
                prim->drawMode = DRAW_HIDE;
            }
#endif
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
#if VERSION >= VER_JP12
    // allow selecting between MONO and STEREO when pressing SELECT
    case 7:
        prim = &g_PrimBuf[D_801BB010];
        for (i = 0; i < 3; i++) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        for (i = 13; i >= 0; i--) {
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        g_GameEngineStep = 8;
        break;
    case 8:
        prim = &g_PrimBuf[D_801BB010];
        for (i = 0; i < 17; i++) {
            if (i == 15 || i == 16) {
                AnimateTitleLogo(prim, i);
            }
            prim = prim->next;
        }
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        if (g_Settings.isSoundMono) {
            prim->v0 = 0xC0;
        } else {
            prim->v0 = 0xA0;
        }
        if (g_pads[0].tapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)) {
            g_Settings.isSoundMono ^= 1;
            g_api.ApplySoundMode();
            g_api.PlaySfx(SFX_UI_MOVE);
        }
        if (g_pads[0].tapped & (PAD_START | PAD_SELECT | PAD_CIRCLE)) {
            g_GameEngineStep = 2;
            g_api.PlaySfx(SFX_UI_MP_FULL);
        }
        break;
#endif
    }
}
