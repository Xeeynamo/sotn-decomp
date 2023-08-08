#include "st0.h"

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
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
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

void func_801B01C0(void) {
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
#ifndef NON_MATCHING
    g_GpuBuffers_1_buf_draw_clip_y = arg0 == 0 ? 0x0014 : 0x0114;
#else
    g_GpuBuffers[1].draw.clip.y = 0x0014;
#endif
    g_GpuBuffers[1].draw.clip.h = 0x00CF;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_801B01C0();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
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

void func_801B0324(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_UNK2_W, DISP_UNK2_H);
    g_GpuBuffers[1].draw.clip.y = DISP_UNK2_W / 2;
    g_GpuBuffers[1].draw.clip.h = DISP_UNK2_H;
    g_GpuBuffers[0].draw.clip.h = DISP_UNK2_H;
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_801B01C0();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/30030", func_801B0414);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/30030", func_801B0464);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/30030", func_801B101C);

void func_801B1198(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/30030", func_801B11E8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/30030", func_801B1298);

