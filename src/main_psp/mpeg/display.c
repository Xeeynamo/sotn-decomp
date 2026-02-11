// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mpeg_private.h"
#include "../main_psp_private.h"

#include <pspgu.h>
#include <pspdisplay.h>

extern s32 D_psp_089B7140[2][0xD000];
extern s32 D_psp_08C62A30;

// BSS
static s32 D_psp_08B1FBB8;
static ScePspSRect D_psp_08B1FBB0;
static s32 frameLoss;
static s32 frameCount;

s32 func_psp_08913F5C(t_displayBuffer* pDisp) {
    s32* dispList;

    sceGuInit();
    dispList = D_psp_089B7140[0];
    sceGuStart(0, dispList, sizeof(D_psp_089B7140[0]));
    sceGuDrawBuffer(GU_PSM_5551, GU_VRAM_BP_0, GU_VRAM_WIDTH);
    sceGuDispBuffer(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_VRAM_BP_1, GU_VRAM_WIDTH);
    sceGuDepthBuffer(GU_VRAM_BP_2, GU_VRAM_WIDTH);
    sceGuOffset(0, 0);
    sceGuScissor(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuTexFilter(GU_LINEAR, GU_LINEAR);
    sceGuTexWrap(GU_REPEAT, GU_REPEAT);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuClearColor(0x00000000);
    sceGuClearDepth(0);
    sceGuClearStencil(0);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_DISPLAY_ON);
    D_psp_08B1FBB0.x = 0;
    D_psp_08B1FBB0.y = 0;
    D_psp_08B1FBB0.w = 320;
    D_psp_08B1FBB0.h = 240;
    D_psp_08B1FBB8 = 0;
    return 0;
}

void draw_frame(t_displayBuffer* pDisp, u8* buffer) {
    s32* dispList = D_psp_089B7140[0];
    s32 x, y;
    s32 w, h;

    sceGuStart(GU_IMMEDIATE, dispList, sizeof(D_psp_089B7140[0]));
    sceGuClear(GU_CLEAR_ALL);
    sceGuTexMode(GU_PSM_T8, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
    sceGuTexImage(0, 0x200, 0x200, 0x200, (u8*)(WALLPAPER_TEX_ADDR));
    sceGuClutMode(GU_PSM_5551, 0, 0xFF, 0);
    sceGuClutLoad(32, (u8*)(WALLPAPER_CLUT_ADDR));
    sceGuEnable(GU_TEXTURE_2D);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0x00000000);
    sceGuEnable(GU_BLEND);
    sceGuColor(0xFFFFFFFF);
    sceGuSpriteMode(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuDrawSprite(0, 0, 0, 0, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    {
        const ScePspIMatrix4 dither = {
            {-4, 0, -3, 1}, {2, -2, 3, -1}, {-3, 1, -4, 0}, {3, -1, 2, -2}};
        sceGuSetDither(&dither);
        sceGuEnable(GU_DITHER);
    }
    switch (pDisp->pixelFormat) {
    case GU_PSM_8888:
        sceGuTexMode(GU_PSM_8888, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
        break;
    case GU_PSM_5650:
        sceGuTexMode(GU_PSM_5650, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
        break;
    case GU_PSM_5551:
        sceGuTexMode(GU_PSM_5551, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
        break;
    case GU_PSM_4444:
        sceGuTexMode(GU_PSM_4444, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
        break;
    }
    sceGuTexImage(0, 0x200, 0x200, 0x200, buffer);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0x00000000);
    sceGuEnable(GU_BLEND);
    sceGuColor(0xFFFFFFFF);
    switch (D_psp_08C62A30) {
    case SCREEN_MODE_FULL:
        w = 418;
        h = 272;
        break;
    case SCREEN_MODE_PERFECT:
        w = 369;
        h = 240;
        break;
    }
    x = (GU_SCR_WIDTH - w) / 2;
    y = (GU_SCR_HEIGHT - h) / 2;
    sceGuSpriteMode(D_psp_08B1FBB0.w, D_psp_08B1FBB0.h, w, h);
    sceGuDrawSprite(x, y, 0, 0, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
}

void func_psp_089144BC(void) {
    s32* dispList = D_psp_089B7140[0];

    sceGuStart(0, dispList, sizeof(D_psp_089B7140[0]));
    sceGuTexMode(GU_PSM_T8, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
    sceGuTexImage(0, 0x200, 0x200, 0x200, (u8*)(WALLPAPER_TEX_ADDR));
    sceGuClutMode(GU_PSM_5551, 0, 0xFF, 0);
    sceGuClutLoad(32, (u8*)(WALLPAPER_CLUT_ADDR));
    sceGuEnable(GU_TEXTURE_2D);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0x00000000);
    sceGuEnable(GU_BLEND);
    sceGuColor(0xFFFFFFFF);
    sceGuSpriteMode(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuDrawSprite(0, 0, 0, 0, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    sceDisplayWaitVblankStartCB();
    EndFrame();
}

s32 dispbuf_create(
    t_displayBuffer* pDisp, s32 arg1, s32 dispNum, s32 pixelFormat) {
    s32 ret = 0;
    u8* ge_addr;

    pDisp->buf = NULL;
    pDisp->startSema = sceKernelCreateSema("start_sema", 0, 0, 1, NULL);
    pDisp->lockSema = sceKernelCreateSema("lock_sema", 0, 1, 1, NULL);
    pDisp->displayWaitSema =
        sceKernelCreateSema("display_wait_sema", 0, 0, 1, NULL);
    pDisp->buf = (u8**)func_psp_0891275C(dispNum * 4);
    if (pDisp->buf == NULL) {
        ret = -1;
        goto error;
    }
    pDisp->pts = (u32*)func_psp_0891275C(dispNum * 4);
    if (pDisp->pts == NULL) {
        ret = -1;
        goto error;
    }
    pDisp->pixelFormat = pixelFormat;
    if (func_psp_08913F5C(pDisp) != 0) {
        ret = -1;
        goto error;
    }
    ge_addr = sceGeEdramGetAddr();
    ge_addr += GU_VRAM_BUFSIZE * 3;
    *pDisp->buf = ge_addr;
    {
        static s32 D_psp_08B1FB94;
        static s32 D_psp_08B1FB98;
        static s32 D_psp_08B1FB9C;
        static s32 D_psp_08B1FBA0;
        static s32 D_psp_08B1FBA4;

        pDisp->write = &D_psp_08B1FB94;
        pDisp->read = &D_psp_08B1FB98;
        pDisp->count = &D_psp_08B1FB9C;
        pDisp->size = &D_psp_08B1FBA0;
        pDisp->displayMode = &D_psp_08B1FBA4;
    }
    ge_addr = ge_addr; // FAKE
    *pDisp->size = dispNum;
    goto term;
error:
    if (pDisp->buf != NULL) {
        func_psp_089127D8(pDisp->buf);
    }
    if (pDisp->pts != NULL) {
        func_psp_089127D8(pDisp->pts);
    }
term:
    return ret;
}

s32 dispbuf_reset(t_displayBuffer* pDisp) {
    u8* ge_addr;

    frameCount = 0;
    frameLoss = 0;

    *pDisp->write = 0;
    *pDisp->read = 0;
    *pDisp->count = 0;
    *pDisp->displayMode = DISPLAY_MODE_NORMAL;
    sceKernelPollSema(pDisp->startSema, 1);
    sceKernelPollSema(pDisp->displayWaitSema, 1);
    ge_addr = (u8*)sceGeEdramGetAddr();
    sceDisplaySetFrameBuf(ge_addr, GU_VRAM_WIDTH, PSP_DISPLAY_PIXEL_FORMAT_5551,
                          PSP_DISPLAY_SETBUF_NEXTFRAME);
    return 0;
}

s32 dispbuf_delete(t_displayBuffer* pDisp) {
    sceKernelDeleteSema(pDisp->startSema);
    sceKernelDeleteSema(pDisp->lockSema);
    sceKernelDeleteSema(pDisp->displayWaitSema);
    if (pDisp->buf != NULL) {
        func_psp_089127D8(pDisp->buf);
    }
    if (pDisp->pts != NULL) {
        func_psp_089127D8(pDisp->pts);
    }
    return 0;
}

s32 dispbuf_getDrawbuf(t_displayBuffer* pDisp, u8** buffer) {
    s32 ret;

    ret = dispbuf_getCapacity(pDisp);
    if (ret > 0) {
        *buffer = pDisp->buf[*pDisp->write];
    } else {
        *buffer = NULL;
    }
    return ret;
}

s32 dispbuf_dataSet(t_displayBuffer* pDisp) {
    sceKernelWaitSema(pDisp->lockSema, 1, NULL);
    (*pDisp->count)++;
    *pDisp->write = (*pDisp->write + 1) % *pDisp->size;
    sceKernelSignalSema(pDisp->lockSema, 1);
    return 0;
}

s32 dispbuf_getCapacity(t_displayBuffer* pDisp) {
    return *pDisp->size - *pDisp->count;
}

s32 dispbuf_getCurrentCount(t_displayBuffer* pDisp) { return *pDisp->count; }

s32 func_psp_08914B08(t_displayBuffer* pDisp) {
    s32 ret;

    if (dispbuf_getMode(pDisp) == DISPLAY_MODE_END) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 dispbuf_setPts(t_displayBuffer* pDisp, u32 pts) {
    s32 ret = 0;

    pDisp->pts[*pDisp->write] = pts;

    return ret;
}

s32 dispbuf_getPts(t_displayBuffer* pDisp, u32* pPts) {
    s32 ret = 0;

    *pPts = pDisp->pts[*pDisp->read];

    return ret;
}

s32 dispbuf_setMode(t_displayBuffer* pDisp, s32 mode) {
    *pDisp->displayMode = mode;
    return 0;
}

s32 dispbuf_getMode(t_displayBuffer* pDisp) { return *pDisp->displayMode; }

s32 dispbuf_func(s32 size, void* argp) {
    s32 currentMode;
    t_avSyncControl* pAvSync;
    t_displayBuffer* pDisp;

    pAvSync = (t_avSyncControl*)argp;
    pDisp = pAvSync->pDisp;
    sceKernelWaitSema(pDisp->startSema, 1, NULL);
    while (func_psp_08914B08(pDisp) == 0) {
        if (func_psp_089123B8() != 0) {
            currentMode = dispbuf_getMode(pDisp);
            if (currentMode != DISPLAY_MODE_UNK) {
                currentMode = avsync_Compare(pAvSync);
                dispbuf_setMode(pDisp, currentMode);
            }
            if (dispbuf_getCurrentCount(pDisp) > 0) {
                if (currentMode == DISPLAY_MODE_NORMAL ||
                    currentMode == DISPLAY_MODE_SKIP) {
                    dispbuf_show(pDisp);
                    sceKernelWaitSema(pDisp->lockSema, 1, NULL);
                    (*pDisp->count)--;
                    sceKernelSignalSema(pDisp->lockSema, 1);
                }
                sceKernelSignalSema(pDisp->displayWaitSema, 1);
                frameCount++;
            } else {
                frameLoss++;
            }
        }
        sceDisplayWaitVblankStartCB();
    }
    while (dispbuf_getCurrentCount(pDisp) > 0) {
        dispbuf_show(pDisp);
        sceKernelWaitSema(pDisp->lockSema, 1, NULL);
        (*pDisp->count)--;
        sceKernelSignalSema(pDisp->lockSema, 1);
        sceDisplayWaitVblankStartCB();
        frameCount++;
    }
    sceDisplayWaitVblankStartCB();
    sceKernelExitThread(0);
    return 0;
}

void dispbuf_startVideo(t_displayBuffer* pDisp) {
    sceKernelSignalSema(pDisp->startSema, 1);
}

s32 dispbuf_show(t_displayBuffer* pDisp) {
    u8* buffer;

    if (*pDisp->displayMode == DISPLAY_MODE_NORMAL) {
        u8* buffer = *pDisp->buf;
        draw_frame(pDisp, buffer);
        sceDisplayWaitVblankStartCB();
        EndFrame();
    }
    return 0;
}

void func_psp_08914EE0(s32 w, s32 h) {
    D_psp_08B1FBB0.w = w;
    D_psp_08B1FBB0.h = h;
}
