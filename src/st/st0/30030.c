// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "dialogue2.h"
#include "disk.h"

static void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

#ifdef VERSION_PSP
#define GET_CLUT(x, y) getClut(x, y)
#else
#define GET_CLUT(x, y) GetClut(x, y)
#endif

static void func_801B0058(void) {
    s32 clutId;
    s32 i;
    s32 j;

    clutId = 0;
    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            g_ClutIds[clutId] = GET_CLUT(j, i);
            clutId++;
        }
    }
    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            g_ClutIds[clutId] = GET_CLUT(j, i);
            clutId++;
        }
    }
    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            g_ClutIds[clutId] = GET_CLUT(j, i);
            clutId++;
        }
    }
}

void func_801B0180(void) {
    RECT rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = 512;
    rect.h = 512;
    ClearImage(&rect, 0, 0, 0);
}

static void SetDisplayBufferColorsToBlack(void) {
    g_GpuBuffers[0].draw.r0 = 0;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0;
    g_GpuBuffers[1].draw.r0 = 0;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0;
}

void func_801B01F8(s32 arg0) {
    g_GpuBuffers[0].draw.clip.y = 0x0014;
    g_GpuBuffers[0].draw.clip.h = 0x00CF;
    if (!arg0) {
        g_GpuBuffers[1].draw.clip.y = 0x0014;
    } else {
        g_GpuBuffers[1].draw.clip.y = 0x0014 + DISP_STAGE_NEXT_X;
    }
    g_GpuBuffers[1].draw.clip.h = 0x00CF;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = 1;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = 0;
}

void func_801B0280(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, DISP_STAGE_NEXT_X, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, DISP_STAGE_NEXT_X, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_801B01F8(0);
}

void SetTitleDisplayBuffer(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, DISP_STAGE_NEXT_X, DISP_TITLE_W,
                  DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, DISP_STAGE_NEXT_X, DISP_TITLE_W,
                  DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    g_GpuBuffers[0].draw.clip.y = 0;
#if defined(VERSION_PSP)
    g_GpuBuffers[1].draw.clip.y = 0;
#else
    g_GpuBuffers[1].draw.clip.y = DISP_TITLE_W / 2;
#endif
    g_GpuBuffers[0].draw.clip.h = g_GpuBuffers[1].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = 1;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = 0;
}

s32 func_801B0414(void) {
    if (g_pads[0].tapped & PAD_START &&
        ((g_Settings.D_8003CB04 & 2) || g_IsTimeAttackUnlocked)) {
        return 1;
    }
    return 0;
}

typedef struct ProloguePrimitive {
    u8 u0;
    u8 v0;
    u8 u1;
    u8 v1;
    s16 x;
    s16 y;
    u16 tpage;
} ProloguePrimitive;

static ProloguePrimitive D_80181568[] = {
    {0x01, 0x80, 0xFF, 0x80, 1, 112, 0x9C},
    {0x00, 0x80, 0xFF, 0x80, 256, 112, 0x9E},
    {0x01, 0x00, 0xFF, 0x80, 1, -16, 0x9C},
    {0x00, 0x00, 0xFF, 0x80, 256, -16, 0x9E},
    {0x01, 0x80, 0xFF, 0x80, 1, -144, 0x98},
    {0x00, 0x80, 0xFF, 0x80, 256, -144, 0x9A},
    {0x01, 0x00, 0xFF, 0x80, 1, -272, 0x98},
    {0x00, 0x00, 0xFF, 0x80, 256, -272, 0x9A},
    {0x00, 0x00, 0x88, 0x70, 112, -384, 0x8C},
#if defined(VERSION_PSP)
    {0x00, 0x71, 0xA0, 0x8F, 248, -415, 0x8C},
#else
    {0x00, 0x70, 0xA0, 0x90, 248, -416, 0x8C},
#endif
};
static u8 D_801815CC_unused[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
    0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01};
extern u16 D_801BEDFC;
extern u16 D_801BEE00;
extern u16 D_801BEE04;
extern s16 D_801BEE08;
extern s16 D_801BEE0C;

int func_891CEB8(u16, u16);
// Post-Dracula fight prologue scroll. This is responsible for scrolling the
// prologue text and displaying the Castlevania logo.
void PrologueScroll(void) {
    Primitive* prim;
    s32 i;
    ProloguePrimitive* textPrim;
    s32 skip;
    Entity* entity;
    s32 primIndex;

#if defined(VERSION_PSP)
    const int EndTimer = 0x14C0; // approximately 110 seconds
    entity = &g_Entities[STAGE_ENTITY_START];
    func_8926498();
#else
    const int EndTimer = 0x14B0; // approximately 110 seconds
    entity = &g_Entities[STAGE_ENTITY_START];
#endif
    switch (g_GameStep) {
    case 0:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_Prologue;
        }
        D_801BEE08 = g_api.AllocPrimitives(PRIM_SPRT, 0x10);
        prim = &g_PrimBuf[D_801BEE08];
        for (i = 0; i < 2; i++, prim = prim->next) {
            prim->x0 = (i * 0xb0) + 0x50;
            prim->y0 = 0x15;
            if (i) {
                prim->u0 = 0x50;
            } else {
                prim->u0 = 0x20;
            }
            prim->v0 = 0;
            prim->u1 = 0xB0;
            prim->v1 = 0xB0;
            prim->tpage = i + 0x8D;
            prim->clut = 0x210;
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
        }

        textPrim = (ProloguePrimitive*)D_80181568;
        for (i = 0; i < 10; i++, prim = prim->next) {
            prim->u0 = textPrim->u0;
            prim->v0 = textPrim->v0;
            prim->u1 = textPrim->u1;
            prim->v1 = textPrim->v1;
            prim->x0 = textPrim->x;
            prim->y0 = textPrim->y;
            prim->tpage = textPrim->tpage;
            prim->clut = 0x200;
            prim->priority = 1;
            prim->drawMode = DRAW_HIDE;
            textPrim++;
        }

        for (i = 0; i < 4; i++, prim = prim->next) {
            prim->type = PRIM_GT4;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x80;
            if (i == 3) {
                prim->u1 = prim->u3 = 0x40;
            }
            prim->v0 = prim->v1 = i * 0x20;
            prim->v2 = prim->v3 = prim->v0 + 0x20;
            prim->x0 = prim->x2 = (i * 0x80) + 0x20;
            prim->x1 = prim->x3 = prim->x0 + 0x80;
            if (i == 3) {
                prim->x1 = prim->x3 = prim->x0 + 0x40;
            }
            prim->y0 = prim->y1 = 0x68;
            prim->y2 = prim->y3 = 0x88;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
            prim->tpage = 0xB;
            prim->clut = 0x220;
            prim->priority = 2;
            prim->drawMode = DRAW_HIDE;
        }
        D_801BEE0C = g_api.AllocPrimitives(PRIM_TILE, 3);
        prim = &g_PrimBuf[D_801BEE0C];
        for (i = 0; prim; prim = prim->next, i++) {
            prim->x0 = i * 0xC0;
            prim->y0 = 0;
            prim->u0 = 0xC0;
            if (i == 2) {
                prim->u0 = 0x80;
            }
            prim->v0 = 0xFF;
            prim->r0 = prim->b0 = prim->g0 = 0xFC;
            prim->priority = 4;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
        g_GameStep++;
        break;
    case 1:
        break;
    case 2: // 0x801B07DC
        // transition to black
        SetTitleDisplayBuffer();
        prim = &g_PrimBuf[D_801BEE08];
        for (i = 0; i < 12; i++) {
            if (prim->y0 >= -0x10 && prim->y0 < 0xF0) {
                prim->drawMode = DRAW_DEFAULT;
            }
            prim = prim->next;
        }
        DestroyEntity(entity);
        D_801BEDFC = D_801BEE00 = D_801BEE04 = 0;
        g_GpuBuffers[0].draw.r0 = 0;
        g_GpuBuffers[0].draw.g0 = 0;
        g_GpuBuffers[0].draw.b0 = 0x18;
        g_GpuBuffers[1].draw.r0 = 0;
        g_GpuBuffers[1].draw.g0 = 0;
        g_GpuBuffers[1].draw.b0 = 0x18;
#if defined(VERSION_PSP)
        func_891CEB8(0x100, 0xF0);
        func_891CEB8(0x100, 0xF1);
#endif
        g_GameStep++;
        break;
    case 3: // 0x801B08A4
        // moon appears
        prim = &g_PrimBuf[D_801BEE0C];
        for (i = 0; prim; prim = prim->next, i++) {
            prim->r0 = prim->b0 = prim->g0 -= 4;
            if (i == 0 && !prim->r0) {
                g_api.FreePrimitives(D_801BEE0C);
                g_GameStep++;
                break;
            }
        }
        break;
    case 4: // 0x801B091C
        if (!g_api.func_80131F68()) {
            g_api.PlaySfx(MU_MOONLIGHT_NOCTURNE);
            g_GameStep++;
        }
        break;
    case 5: // 0x801B0940
        if (
#if defined(VERSION_PSP)
            1
#else
            g_api.func_80131F68()
#endif
        ) {
            g_GameStep++;
        }
        break;
    case 6: // 0x801B096C
        // prologue scroll
        func_801B1298(entity);
        D_801BEDFC++;
        D_801BEE04++;
        if (D_801BEDFC == 0xB && D_801BEE00 < 0x1C0) {

            D_801BEDFC = 0;
            D_801BEE00++;
            prim = &g_PrimBuf[D_801BEE08];
            for (i = 0; i < 12; i++) {
                if (i >= 2) {
                    prim->y0++;
                }

                if (prim->y0 < -0x90 || prim->y0 > 0xF0) {
                    prim->drawMode = DRAW_HIDE;
                } else {
                    prim->drawMode = DRAW_DEFAULT;
                }
                prim = prim->next;
            }
        }
        // 110 seconds?
        if (D_801BEE04 > EndTimer) {
            prim = &g_PrimBuf[D_801BEE08];
            for (i = 0; i < 12; i++) {
                prim = prim->next;
            }
            while (prim) {
                prim->drawMode =
                    DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
            }
            DestroyEntity(entity);
            D_801BEE00 = 0;
            g_GameStep++;
#if defined(VERSION_PSP)
            func_pspeu_09246B88();
#endif
        }
        skip = func_801B0414();
        if (skip) {
            g_GameStep = Play_16;
        }
        break;
    case 7: // 0x801B0AE8
        // scroll finished, fade in castlevania
        prim = &g_PrimBuf[D_801BEE08];
        i = 0;
        while (i < 12) {
            prim = prim->next;
            i++;
        }
        while (prim) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3++;
            prim->g0 = prim->g1 = prim->g2 = prim->g3++;
            prim->b0 = prim->b1 = prim->b2 = prim->b3++;
            prim = prim->next;
        }
        D_801BEE00++;
        if (D_801BEE00 > 0xC0) {
            D_801BEE00 = 0;
            g_GameStep++;
        }
        skip = func_801B0414();
        if (skip) {
            g_GameStep = Play_16;
        }
        break;
    case 8:
        prim = &g_PrimBuf[D_801BEE08];
        for (i = 0; i < 12; i++) {
            prim = prim->next;
        }
        while (prim) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3--;
            prim->g0 = prim->g1 = prim->g2 = prim->g3--;
            prim->b0 = prim->b1 = prim->b2 = prim->b3--;
            prim->drawMode = DRAW_COLORS;
            prim = prim->next;
        }
        D_801BEE00++;
        if (D_801BEE00 > 0x40) {
            D_801BEE00 = 0;
            g_GameStep++;
        }
        skip = func_801B0414();
        if (skip) {
            g_GameStep = Play_16;
        }
        break;
    case 9:
        D_801BEE00++;
        if (D_801BEE00 > 0x230) {
            g_GameStep = Play_16;
            break;
        }
        skip = func_801B0414();
        if (skip) {
            g_GameStep = Play_16;
        }
        break;
    case 16:
        g_api.PlaySfx(0x82);
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 3);
        prim = &g_PrimBuf[D_801BEE08];
        i = 0;
        while (prim) {
            if (!prim->next) {
                prim->next = &g_PrimBuf[primIndex];
                break;
            }
            prim = prim->next;
        }
        prim = &g_PrimBuf[primIndex];
        i = 0;
        while (prim) {
            prim->x0 = i * 0xC0;
            prim->y0 = 0;
            prim->u0 = 0xC0;
            if (i == 2) {
                prim->u0 = 0x80;
            }
            prim->v0 = 0xFF;
            prim->r0 = prim->b0 = prim->g0 = 0;
            prim->priority = 4;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
            i++;
        };

        D_801BEE00 = 0;
        g_GameStep++;
        break;
    case 17:
        prim = &g_PrimBuf[D_801BEE08];
        for (i = 0; i < 16; i++) {
            prim = prim->next;
        }
        while (prim) {
            if (prim->r0 < 0xF8) {
                prim->r0 = prim->b0 = prim->g0 += 8;
            }
            prim = prim->next;
        }
        D_801BEE00++;
        if (D_801BEE00 > 0x20) {
            g_GpuBuffers[0].draw.r0 = 0;
            g_GpuBuffers[0].draw.g0 = 0;
            g_GpuBuffers[0].draw.b0 = 0;
            g_GpuBuffers[1].draw.r0 = 0;
            g_GpuBuffers[1].draw.g0 = 0;
            g_GpuBuffers[1].draw.b0 = 0;
            g_GameStep++;
        }
        break;
    case 18:
        g_Settings.D_8003CB04 |= 2;
        func_801B0058();
        g_api.FreePrimitives(D_801BEE08);
        DestroyEntitiesFromIndex(0);
        g_GameStep++;
        break;
    case 19:
        if (!g_api.func_80131F68()) {
            func_801B0280();
            func_801B0180();
            if (g_StageId == STAGE_ST0) {
                g_StageId = STAGE_NO3;
                SetGameState(Game_NowLoading);
                g_GameStep = 2;
            } else {
                SetGameState(Game_Title);
            }
        }
        break;
    }
}
