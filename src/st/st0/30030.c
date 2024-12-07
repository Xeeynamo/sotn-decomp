// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "dialogue2.h"
#include "disk.h"

void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_801B0058(void) {
    s32 index = 0;
    s32 i;
    s32 j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            g_ClutIds[index++] = GetClut(j, i);
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

void SetDisplayBufferColorsToBlack(void) {
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
        g_GpuBuffers[1].draw.clip.y = 0x0114;
    }
    g_GpuBuffers[1].draw.clip.h = 0x00CF;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = 1;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = 0;
}

// Set stage display buffer
void func_801B0280(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(
        &g_GpuBuffers[1].draw, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(
        &g_GpuBuffers[0].disp, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_801B01F8(0);
}

void SetTitleDisplayBuffer(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    g_GpuBuffers[1].draw.clip.y = DISP_TITLE_W / 2;
    g_GpuBuffers[1].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

u16 func_801B0414(void) {
    int ret;

    if (!(g_pads[0].tapped & PAD_START)) {
        return 0;
    }
    ret = 1;
    if (!(g_Settings.D_8003CB04 & 2) && (g_IsTimeAttackUnlocked == 0)) {
        return 0;
    }

    return ret;
}

// func_801B0414 is undeclared to PrologueScroll. This emulates the
// undefined signature to avoid splitting the file at this time.
#define fake_func_801B0414 ((s32(*)())func_801B0414)
void func_801B1298(Entity*);

typedef struct ProloguePrimitive {
    s8 u0;
    s8 v0;
    s8 u1;
    s8 v1;
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
    {0x00, 0x70, 0xA0, 0x90, 248, -416, 0x8C},
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

// Post-Dracula fight prologue scroll. This is responsible for scrolling the
// prologue text and displaying the Castlevania logo.
void PrologueScroll(void) {
    Entity* entity;
    ProloguePrimitive* textPrim;
    Primitive* prim;
    s32 primIndex;
    s32 condition;
    s32 i;

    entity = &g_Entities[STAGE_ENTITY_START];

    switch (g_GameStep) {
    case 0: // 0x801B04A4
        if (g_UseDisk) {
            if (!g_IsUsingCd) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_Prologue;
            } else {
                break;
            }
        }

        D_801BEE08 = g_api.AllocPrimitives(PRIM_SPRT, 0x10);
        prim = &g_PrimBuf[D_801BEE08];

        for (i = 0; i < 2; i++) {
            prim->x0 = (i * 0xb0) + 0x50;
            prim->y0 = 0x15;
            prim->u0 = i ? 0x50 : 0x20;

            prim->v0 = 0;
            prim->v1 = prim->u1 = 0xB0;
            prim->tpage = i + 0x8D;
            prim->clut = 0x210;
            prim->priority = 0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        textPrim = (ProloguePrimitive*)D_80181568;
        for (i = 0; i < 10; i++) {
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
            prim = prim->next;
        }

        for (i = 0; i < 4; i++) {
            prim->type = PRIM_GT4;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x80;

            if (i == 3) {
                prim->u1 = prim->u3 = 0x40;
            }

            prim->v0 = prim->v1 = i << 5;
            prim->v2 = prim->v3 = (i * 0x20) + 0x20;
            prim->x0 = prim->x2 = (i * 0x80) + 0x20;
            prim->x1 = prim->x3 = (i * 0x80) + 0xA0;

            if (i == 3) {
                prim->x1 = prim->x3 = prim->x0 + 0x40;
            }

            prim->tpage = 0xB;
            prim->clut = 0x220;
            prim->priority = 2;
            prim->drawMode = DRAW_HIDE;
            prim->y0 = prim->y1 = 0x68;
            prim->y2 = prim->y3 = 0x88;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;

            prim = prim->next;
        }

        D_801BEE0C = g_api.AllocPrimitives(PRIM_TILE, 3);
        prim = &g_PrimBuf[D_801BEE0C];
        i = 0;
        if (prim) {
            while (prim) {
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
                i++;
                prim = prim->next;
            }
        }

        g_GameStep++;
        break;

    case 2: // 0x801B07DC
        // transition to black
        SetTitleDisplayBuffer();

        prim = &g_PrimBuf[D_801BEE08];
        for (i = 0; i < 12; i++) {
            if (((u16)(prim->y0 + 0x10)) < 0x100) {
                prim->drawMode = DRAW_DEFAULT;
            }
            prim = prim->next;
        }
        DestroyEntity(entity);
        D_801BEE04 = 0;
        D_801BEE00 = 0;
        D_801BEDFC = 0;
        g_GpuBuffers[0].draw.r0 = 0;
        g_GpuBuffers[0].draw.g0 = 0;
        g_GpuBuffers[0].draw.b0 = 0x18;
        g_GpuBuffers[1].draw.r0 = 0;
        g_GpuBuffers[1].draw.g0 = 0;
        g_GpuBuffers[1].draw.b0 = 0x18;
        g_GameStep++;
        break;

    case 3: // 0x801B08A4
        // moon appears
        prim = &g_PrimBuf[D_801BEE0C];
        i = 0;
        while (prim) {
            prim->r0 = prim->b0 = prim->g0 = prim->g0 - 4;

            if (i == 0 && prim->r0 == 0) {
                g_api.FreePrimitives(D_801BEE0C);
                g_GameStep++;
                break;
            }

            i++;
            prim = prim->next;
        }
        break;
    case 4: // 0x801B091C
        if (!g_api.func_80131F68()) {
            g_api.PlaySfx(0x340);
            g_GameStep++;
        }
        break;
    case 5: // 0x801B0940
        if (g_api.func_80131F68()) {
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

                if ((u32)(((u16)prim->y0 + 0x90) & 0xFFFF) >= 0x181U) {
                    prim->drawMode = DRAW_HIDE;
                } else {
                    prim->drawMode = DRAW_DEFAULT;
                }
                prim = prim->next;
            }
        }
        // 110 seconds?
        if (D_801BEE04 >= 0x14B1) {
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
            goto step_return;
        }

        if (fake_func_801B0414()) {
            g_GameStep = Play_16;
        }
        break;
    case 7: // 0x801B0AE8
        // scroll finished, fade in castlevania
        prim = &g_PrimBuf[D_801BEE08];
        for (i = 0; i < 12; i++) {
            prim = prim->next;
        }
        while (prim) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3++;
            prim->g0 = prim->g1 = prim->g2 = prim->g3++;
            prim->b0 = prim->b1 = prim->b2 = prim->b3++;
            prim = prim->next;
        }
        D_801BEE00++;
        condition = D_801BEE00 < 0xC1;
        goto check_step_return;

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
        condition = !(D_801BEE00 >= 0x41);
    check_step_return:
        if (!condition) {
        step_return:
            D_801BEE00 = 0;
            g_GameStep++;
        }

        if (fake_func_801B0414()) {
            g_GameStep = Play_16;
        }

        break;
    case 9:
        D_801BEE00++;
        if (D_801BEE00 < 0x231 && !fake_func_801B0414()) {
            return;
        }
        g_GameStep = Play_16;
        break;

    case 16:
        g_api.PlaySfx(0x82);
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 3);
        prim = &g_PrimBuf[D_801BEE08];

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
                prim->r0 = prim->b0 = prim->g0 = prim->g0 + 8;
            }
            prim = prim->next;
        }
        D_801BEE00++;
        if (D_801BEE00 >= 0x21) {
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

// This file uses g_Dialogue with a different struct than the usual.
// It is based on struct Dialogue, which is used in cutscene.c
extern Dialogue2 g_Dialogue;
u8 func_801B101C(u8* script) {
    Primitive* prim;
    s16 i;

    g_Dialogue.primIndex[0] = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (g_Dialogue.primIndex[0] != -1) {
        g_Dialogue.nextCharX = 0x200;
        g_Dialogue.scriptCur = script;
        g_Dialogue.startY = 0x216;
        g_Dialogue.nextLineX = 0;
        g_Dialogue.nextCharY = 0;
        g_Dialogue.portraitAnimTimer = 0;
        g_Dialogue.unk12 = 0;
        g_Dialogue.clutIndex = 0;
        g_Dialogue.prim[0] = &g_PrimBuf[g_Dialogue.primIndex[0]];
        prim = &g_PrimBuf[g_Dialogue.primIndex[0]];
        for (i = 0; i < 0x20; i++) {
            if (i & 1) {
                prim->tpage = 9;
                prim->x0 = 0x100;
            } else {
                prim->tpage = 8;
                prim->x0 = 0x20;
            }
            prim->v0 = (i >> 1) * 0x10;
            prim->u0 = 0;
            prim->u1 = 0xF0;
            prim->v1 = 0x10;
            prim->y0 = (i >> 1) * 0x16 + 0xF0;
            prim->clut = 0x221;
            prim->priority = 3;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }

        return true;
    }
    g_Dialogue.primIndex[0] = 0;
    return false;
}

void func_801B1198(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

u16* func_801B11E8(unsigned char ch) {
    u16 jCh;
#ifndef VERSION_PC

    if (ch >= 'a') {
        jCh = ('ａ' - 'a') + ch;
    } else if (ch >= 'A') {
        jCh = ('Ａ' - 'A') + ch;
    } else if (ch == ',') {
        jCh = '，';
    } else if (ch == '.') {
        jCh = '．';
    } else if (ch == '\'') {
        jCh = '’';
    } else if (ch == ' ') {
        return NULL;
    } else {
        jCh = ('Ａ' - 'A') + ch;
        if (ch >= 'a') {
            ++jCh;
        }
    }
#else
    jCh = 'A';
#endif

    return g_api.func_80106A28(jCh, 0);
}

extern u8 D_80182C58[];
extern u16 D_801BEE90[][0x30];
// Resembles SEL func_801B79D4
void func_801B1298(Entity* self) {
    s32 i;
    Primitive* prim;
    u16 y;
    u16 glyphIndex;
    u16* var_v1;
    u16 nextChar;
    u16* glyph;
    s16 y0;

    switch (self->step) {
    case 0:
        if (func_801B101C(D_80182C58)) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = g_Dialogue.primIndex[0];
            ++self->step;
            func_801B1198(0);
            glyphIndex = 0;
            while (1) {
                nextChar = *g_Dialogue.scriptCur++;
                if (nextChar == 1) {
                    // Gets weirdly relocated in the asm.
                    g_Dialogue.startY =
                        g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
                    ++g_Dialogue.nextLineX;
                    break;
                }
                glyph = func_801B11E8(nextChar);
                if (glyph) {
                    var_v1 = &D_801BEE90[glyphIndex][0];
                    for (i = 0; i < 0x30; ++i) {
                        var_v1++[0] = glyph++[0];
                    }
                    glyph = D_801BEE90[glyphIndex];
                    y = g_Dialogue.nextLineX * 16;
                    LoadTPage(
                        (u_long*)glyph, 0, 0, g_Dialogue.startY, y, 12, 16);
                    g_Dialogue.startY += 3;
                    y = g_Dialogue.startY - g_Dialogue.nextCharX;
                    if (0x38 <= y && y < 0x40) {
                        g_Dialogue.startY += 8;
                    }
                    ++glyphIndex;
                } else {
                    g_Dialogue.startY += 2;
                    y = g_Dialogue.startY - g_Dialogue.nextCharX;
                    if (0x38 <= y && y < 0x40) {
                        g_Dialogue.startY += 8;
                    }
                }
            }
        }
        break;
    case 1:
        if (!g_Dialogue.nextCharY) {
            break;
        }
        nextChar = 0;
        glyphIndex = 0;
        do {
            nextChar = *g_Dialogue.scriptCur++;
            switch (nextChar) {
            case 0:
                self->step = 7;
                return;
            case 1:
                g_Dialogue.startY =
                    g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
                g_Dialogue.nextLineX++;
                if (g_Dialogue.nextLineX > 15) {
                    g_Dialogue.nextLineX = 0;
                }
                g_Dialogue.nextCharY = 0;
                return;
            case 2:
                g_Dialogue.startY =
                    g_Dialogue.nextCharX + *g_Dialogue.scriptCur++;
                g_Dialogue.nextLineX++;
                if (g_Dialogue.nextLineX > 15) {
                    g_Dialogue.nextLineX = 0;
                }

                prim = g_Dialogue.prim[0];
                for (i = 0; i < g_Dialogue.nextLineX; ++i) {
                    prim = prim->next;
                    prim = prim->next;
                }

                y0 = prim->y0;
                for (prim = g_Dialogue.prim[0]; prim != NULL;
                     prim = prim->next) {
                    if (y0 <= prim->y0) {
                        prim->y0 += 0x16;
                        prim->p1 += 0x16;
                    }
                }
                g_Dialogue.unk12 += 0x58;
                g_Dialogue.portraitAnimTimer += 0x16;
                g_Dialogue.nextCharY = 0;
                return;
            }
        } while (0);
        glyph = func_801B11E8(nextChar);

        if (glyph) {
            y = g_Dialogue.nextLineX * 16;
            LoadTPage((u_long*)glyph, 0, 0, g_Dialogue.startY, y, 0xC, 0x10);
            g_Dialogue.startY += 3;
        } else {
            g_Dialogue.startY += 2;
        }
        y = g_Dialogue.startY - g_Dialogue.nextCharX;
        if (0x38 <= y && y < 0x40) {
            g_Dialogue.startY += 8;
        }
        break;
    case 2:
        break;
    case 7:
        if (g_Dialogue.nextCharY) {
            g_Dialogue.nextLineX++;
            if (g_Dialogue.nextLineX > 15) {
                g_Dialogue.nextLineX = 0;
            }
            g_Dialogue.nextCharY = 0;
        }
    }

    if (!g_Dialogue.unk12) {
        func_801B1198(g_Dialogue.nextLineX);
        g_Dialogue.nextCharY = 1;
        g_Dialogue.unk12 = 88;
    }
    --g_Dialogue.unk12;
    if (!g_Dialogue.clutIndex) {
        for (prim = g_Dialogue.prim[0], i = 0; i < 32; ++i) {
            prim->y0--;
            if (prim->y0 == -22) {
                prim->y0 = g_Dialogue.portraitAnimTimer - prim->p1 + 330;
                prim->p1 = g_Dialogue.portraitAnimTimer;
            }
            prim = prim->next;
        }
        g_Dialogue.clutIndex = 4;
    }
    --g_Dialogue.clutIndex;
}
