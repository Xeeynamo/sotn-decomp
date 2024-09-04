REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_ClutIds[index++] = GetClut(j, i);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_ClutIds[index++] = GetClut(j, i);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
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
REDACTED
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

extern s32 D_8003CB04[];
extern ProloguePrimitive D_80181568[];
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

        textPrim = D_80181568;
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
            prim->type = 4;
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
        D_8003CB04[0] |= 2;
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
REDACTED
u8 func_801B101C(const char* msg) {
    Primitive* prim;
    s16 i;

    D_801C24E4[0] = g_api.AllocPrimitives(PRIM_SPRT, 0x20);
    if (D_801C24E4[0] != -1) {
        g_Dialogue.nextCharX = 0x200;
        g_Dialogue.nextCharDialogue = msg;
        g_Dialogue.startY = 0x216;
        g_Dialogue.nextLineX = 0;
        g_Dialogue.nextCharY = 0;
        g_Dialogue.portraitAnimTimer = 0;
        D_801C24DE = 0;
        D_801C24DF = 0;
        D_801C24E0 = &g_PrimBuf[D_801C24E4[0]];
        prim = &g_PrimBuf[D_801C24E4[0]];
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
    D_801C24E4[0] = 0;
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

u16* func_801B11E8(char ch) {
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
REDACTED
INCLUDE_ASM("st/st0/nonmatchings/30030", func_801B1298);
