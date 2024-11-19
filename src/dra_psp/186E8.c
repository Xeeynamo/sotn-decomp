// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

extern s32 g_DebugWaitInfoTimer;

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (g_DebugWaitInfoTimer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
#if !defined(VERSION_PSP)
    FntFlush(-1);
#endif
}

void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

#ifndef PSP_DEADSTRIP

void DebugCaptureScreen(void) {
    const int BmpHeaderLen = 0x36;
    const int MaxScreenshotCount = 1000;
    const int BytesPerPixel = 3;
    char fileName[0x100];
    u8 bmp[0x100];
    s8 buffer[0x30];
    s32 fid;
    s32 width;
    s32 height;
    u32 fileSize;
    s32 bufferPos;
    s8* dst;
    u16* src;
    s32 i;
    s32 j;

    if (!(g_pads[1].tapped & PAD_SELECT && g_pads[1].pressed & PAD_UP)) {
        return;
    }

    StoreImage(&g_CurrentBuffer->disp.disp, (u_long*)0x80200000);
    DrawSync(0);

    for (i = 0; i < MaxScreenshotCount; i++) {
        STRCPY(fileName, "sim:c:\\bin\\dra000.bmp");
        fileName[14] += i / 100;
        fileName[15] += i / 10 - i / 100 * 10;
        fileName[16] += i % 10;
        fid = open(fileName, O_RDONLY);
        if (fid < 0) {
            break;
        }
        close(fid);
    }

    fid = open(fileName, O_CREAT);
    if (fid < 0) {
        FntPrint("cre err:%s\n", &fileName);
        return;
    }

    width = g_CurrentBuffer->disp.disp.w;
    height = g_CurrentBuffer->disp.disp.h;
    for (i = 0; i < BmpHeaderLen; i++) {
        bmp[i] = 0;
    }
    fileSize = BmpHeaderLen + width * height * BytesPerPixel;
    bmp[0x00] = 'B';               // Bitmap signature
    bmp[0x01] = 'M';               // for Windows OS
    bmp[0x02] = fileSize;          // total file size of
    bmp[0x03] = fileSize >> 8;     // the bitmap file
    bmp[0x04] = fileSize >> 16;    // in little endian
    bmp[0x05] = fileSize >> 24;    //
    bmp[0x0A] = BmpHeaderLen;      // Data offset
    bmp[0x0E] = 40;                // header size
    bmp[0x1A] = 1;                 // number of color planes
    bmp[0x1C] = BytesPerPixel * 8; // bits per pixel
    bmp[0x12] = width;
    bmp[0x13] = width / 256;
    bmp[0x16] = height;
    bmp[0x17] = height / 256;
    if (write(fid, &bmp, BmpHeaderLen) < 0) {
        FntPrint("wr err\n");
        return;
    }

    bufferPos = 0;
    dst = buffer;
    src = (u16*)0x80200000;
    for (i = height - 1; i >= 0; i--) {
        u16* start = buffer;
        for (j = 0; j < width; j++) {
            u16 pixelColor = src[j + i * width];
            *dst++ = (pixelColor >> 7) & 0xF8; // B
            *dst++ = (pixelColor >> 2) & 0xF8; // G
            *dst++ = (pixelColor & 0x1F) << 3; // R
            if (++bufferPos == 0x10) {
                if (write(fid, start, bufferPos * BytesPerPixel) < 0) {
                    FntPrint("wr err\n");
                    return;
                }
                bufferPos = 0;
                dst = start;
            }
        }
    }

    if (bufferPos != 0) {
        if (write(fid, &buffer, bufferPos * BytesPerPixel) < 0) {
            FntPrint("wr err\n");
            return;
        }
    }
    if (close(fid) < 0) {
        FntPrint("clo err\n");
        return;
    }
    DebugInputWait(fileName);
}

void DebugCaptureVideo(void) {
    const int MaxVideoFramesCount = 1000;
    char fileName[0x100];
    u8 bmp[0x100];
    u16 buffer[0x10];
    s32 fid;
    s32 bufferPos;
    s32 i;
    s32 j;
    u16* start;
    u16* src;
    u16* dst;

    for (i = 0; i < 4; i++) {
        if (g_Settings.buttonConfig[i] != 3 - i) {
            return;
        }
    }

    if (g_DebugIsRecordingVideo == false) {
        if (!(g_pads[0].tapped & PAD_TRIANGLE)) {
            return;
        }

        for (i = 0; i < MaxVideoFramesCount; i++) {
            STRCPY(fileName, "sim:c:\\bin\\dra000.mov");
            fileName[14] += i / 100;
            fileName[15] += i / 10 - i / 100 * 10;
            fileName[16] += i % 10;
            g_DebugRecordVideoFid = open(fileName, O_RDONLY);
            if (g_DebugRecordVideoFid < 0) {
                break;
            }
            close(g_DebugRecordVideoFid);
        }

        g_DebugRecordVideoFid = open(fileName, O_CREAT);
        if (g_DebugRecordVideoFid < 0) {
            FntPrint("cre err:%s\n", fileName);
            return;
        }
        g_DebugIsRecordingVideo = true;
    } else if (g_pads[0].tapped & PAD_TRIANGLE) {
        g_DebugIsRecordingVideo = false;
        if (close(g_DebugRecordVideoFid) < 0) {
            FntPrint("clo err\n");
        }
        return;
    }

    StoreImage(&g_CurrentBuffer->disp.disp, (u_long*)0x80200000);
    DrawSync(0);

    src = (u16*)0x80200000;
    i = 0;
    bufferPos = 0;
    dst = buffer;
    start = buffer;
    for (; i < 0x40; i++) {
        for (j = 0; j < 0x40; j++) {
            *dst++ = src[0x6060 + i * 0x100 + j];
            if (++bufferPos == 0x10) {
                if (write(g_DebugRecordVideoFid, start, bufferPos * 2) < 0) {
                    FntPrint("wr err\n");
                    return;
                }
                bufferPos = 0;
                dst = start;
            }
        }
    }

    if (bufferPos != 0) {
        if (write(g_DebugRecordVideoFid, buffer, bufferPos * 2) < 0) {
            FntPrint("wr err\n");
            return;
        }
    }
}

const char* D_800A0144[] = {
    "normal", "dark", "light", "reverse", "pale",
};
void func_800E2B00(void) {
    DR_MODE* drMode;
    SPRT* sprite;
    TILE* tile;
    TILE* curTile;
    s32 i;
    u16 var_s7;
    u16* palette;
    u32 new_var;

    u32 color;
    u32 new_var3;
    u16 color_fake;
    u16 new_var4;

    drMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];
    sprite = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
    tile = &g_CurrentBuffer->tiles[g_GpuUsage.tile];
    FntPrint("file:%02x,%03x\n", D_801362B4, g_DebugCurPal);
    FntPrint("half:%s\n", D_800A0144[D_801362C8]);

    if (D_801362C8 == 0) {
        SetSemiTrans(sprite, 0);
        var_s7 = 0;
    } else {
        SetSemiTrans(sprite, 1);
        var_s7 = (D_801362C8 << 5) - 0x20;
    }

    SetShadeTex(sprite, 1);
    sprite->r0 = 0;
    sprite->g0 = 0;
    sprite->b0 = 0;
    sprite->x0 = 112;
    sprite->u0 = (D_801362B4 & 1) << (new_var = 7);
    sprite->y0 = 80;
    sprite->v0 = (D_801362B4 & 2) << (new_var = 6);
    sprite->w = 128;
    sprite->h = 128;
    sprite->clut = g_ClutIds[g_DebugCurPal];
    AddPrim(&g_CurrentOT[0x1FE], sprite);
    g_GpuUsage.sp++;
    SetDrawMode(drMode, 0, 0, (D_801362B4 >> 2) + var_s7, &g_Vram.D_800ACD80);
    AddPrim(&g_CurrentOT[0x1FE], drMode++);

    i = 0;
    palette = g_Clut + g_DebugCurPal * 16;
    curTile = tile;
    g_GpuUsage.drawModes++;
    while (i < 0x10) {
        SetSemiTrans(tile, 0);

        color = *palette;
        color_fake = *palette;
        new_var4 = (color_fake & 0x1F) << 3;
        curTile->r0 = new_var4;

        color_fake = color;
        new_var4 = color_fake >> 2;
        curTile->g0 = new_var4 & 0xF8;

        color_fake = color;
        new_var3 = color_fake >> 7;
        curTile->b0 = new_var3 & 0xF8;

        if (i == g_DebugPalIdx) {
            color_fake = (i * 15) + 8;
            curTile->x0 = (i * 15) + 8;
            curTile->y0 = 0xD4;
        } else {
            curTile->x0 = (i * 15) + 10;
            curTile->y0 = 0xD6;
        }
        if (i == g_DebugPalIdx) {
            curTile->w = 14;
            curTile->h = 15;
        } else {
            curTile->w = 10;
            curTile->h = 11;
        }
        AddPrim(&g_CurrentOT[0x1FE], tile);
        g_GpuUsage.tile++;
        curTile++;
        tile++;
        palette++;
        i++;
    }

    SetDrawMode(drMode, 0, 0, 0, &g_Vram.D_800ACD80);
    AddPrim(&g_CurrentOT[0x1FE], drMode);
    g_GpuUsage.drawModes++;
}

void DebugEditColorChannel(s32 colorAdd) {
    s32 newColorChannel;
    s32 color;
    u16 originalColor;
    u16* palette;

    palette = g_Clut + g_DebugCurPal * COLORS_PER_PAL + g_DebugPalIdx;
    originalColor = palette[0];
    switch (g_DebugColorChannel) {
    case DEBUG_COLOR_CHANNEL_RED:
        color = originalColor & 0xFFE0;
        color |= (originalColor + colorAdd) & 0x1F;
        *palette = color;
        break;
    case DEBUG_COLOR_CHANNEL_GREEN:
        color = originalColor & 0xFC1F;
        color |= (originalColor + (colorAdd << 5)) & 0x3E0;
        *palette = color;
        break;
    case DEBUG_COLOR_CHANNEL_BLUE:
        color = originalColor & 0x83FF;
        color |= (originalColor + (colorAdd << 10)) & 0x7C00;
        *palette = color;
        break;
    }
}

#endif

s32 DebugUpdate() { return 1; }

extern s32 D_psp_08B42060;

s32 func_psp_090F5188(void) {
    char sp10[0x100];

    psp_sprintf(&sp10, "%sSE/sd_j010.spk;1", D_psp_08B42060);
    func_892EAFC(&sp10, 0);
    psp_sprintf(&sp10, "%sSE/sd_alk.spk;1", D_psp_08B42060);
    func_892EAFC(&sp10, 1);
    psp_sprintf(&sp10, "%sSE/sd_mak.spk;1", D_psp_08B42060);
    func_892EAFC(&sp10, 2);
    psp_sprintf(&sp10, "%sSE/sd_rou.spk;1", D_psp_08B42060);
    func_892EAFC(&sp10, 3);
    return 0;
}

void SetGPUBuffRGBZero(void) {
    g_GpuBuffers[0].draw.r0 = 0;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0;
    g_GpuBuffers[1].draw.r0 = 0;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0;
}
void SetGPUBuffRGB(u8 arg0) {
    g_GpuBuffers[0].draw.r0 = arg0;
    g_GpuBuffers[0].draw.g0 = arg0;
    g_GpuBuffers[0].draw.b0 = arg0;
    g_GpuBuffers[1].draw.r0 = arg0;
    g_GpuBuffers[1].draw.g0 = arg0;
    g_GpuBuffers[1].draw.b0 = arg0;
}

void func_800E34DC(s32 arg0) {
    g_GpuBuffers[0].draw.clip.y = 0x0014;
    g_GpuBuffers[0].draw.clip.h = 0x00CF;
    g_GpuBuffers[1].draw.clip.y = 0x0014;
    g_GpuBuffers[1].draw.clip.h = 0x00CF;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = 1;
    SetGPUBuffRGBZero();
    g_GpuBuffers[0].draw.dtd = g_GpuBuffers[1].draw.dtd = 0;
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = 0;
}

void SetStageDisplayBuffer(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_800E34DC(0);
}

void SetCgiDisplayBuffer(s32 width) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, width, DISP_ALL_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 0, width, DISP_ALL_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0, width, DISP_ALL_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, width, DISP_ALL_H);
    func_800E34DC(1);
}

void SetMenuDisplayBuffer(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_MENU_W, DISP_MENU_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 0, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_MENU_W, DISP_MENU_H);
    func_800E34DC(1);
    g_GpuBuffers[0].draw.dtd = g_GpuBuffers[1].draw.dtd = 1;
}

extern s32 D_psp_091CE1E8;
void func_psp_090F54E0(void) {
    if (D_psp_091CE1E8 != 0) {
        func_891AEC8();
        D_psp_091CE1E8 = 0;
    }
    func_psp_090FA740();
}