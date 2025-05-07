// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"


#include "../get_lang.h"

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

s32 LoadVabData(void) {
    char sp10[0x100];

    sprintf(&sp10, "%sSE/sd_j010.spk;1", D_psp_08B42060);
    func_892EAFC(&sp10, 0);
    sprintf(&sp10, "%sSE/sd_alk.spk;1", D_psp_08B42060);
    func_892EAFC(&sp10, 1);
    sprintf(&sp10, "%sSE/sd_mak.spk;1", D_psp_08B42060);
    func_892EAFC(&sp10, 2);
    sprintf(&sp10, "%sSE/sd_rou.spk;1", D_psp_08B42060);
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
void VSyncHandler(void) {
    if (D_psp_091CE1E8 != 0) {
        func_891AEC8();
        D_psp_091CE1E8 = 0;
    }
    func_psp_090FA740();
}

void func_psp_090F5520(void) {
    while (D_psp_091CE1E8 != 0) {
        func_8939EB8(1);
    }
}

extern s32 g_UserLanguage;

extern u8 D_psp_09192EB0;
extern u8 D_psp_091A4CE8;
extern u8 D_psp_09197640;
extern u8 D_psp_091A04E0;
extern u8 D_psp_0919BE58;

extern u8 D_psp_091A8798;
extern u8 D_psp_091AED90;
extern u8 D_psp_091AA130;
extern u8 D_psp_091AD410;
extern u8 D_psp_091ABB00;

extern u8 D_psp_091B00F0;
extern u8 D_psp_091C1690;
extern u8 D_psp_091B4660;
extern u8 D_psp_091BD110;
extern u8 D_psp_091B8BB0;

extern u8 D_psp_091C59C0;
extern u8 D_psp_091C7080;
extern u8 D_psp_091C5F58;
extern u8 D_psp_091C6AF0;
extern u8 D_psp_091C6550;

extern u8 D_psp_091C7398;
extern u8 D_psp_091C85F8;
extern u8 D_psp_091C7828;
extern u8 D_psp_091C8158;
extern u8 D_psp_091C7CD8;

extern u8 D_psp_091C8E40;
extern u8 D_psp_091CAB00;
extern u8 D_psp_091C9560;
extern u8 D_psp_091CA398;
extern u8 D_psp_091C9C90;

extern u8 D_psp_0914A918;
extern u8 D_psp_0914BBE0;
extern u8 D_psp_0914ADB8;
extern u8 D_psp_0914B748;
extern u8 D_psp_0914B260;

extern u8 D_psp_0914AB00;
extern u8 D_psp_0914BE60;
extern u8 D_psp_0914AFF8;
extern u8 D_psp_0914B960;
extern u8 D_psp_0914B4A0;

extern void* D_psp_091CE250;

extern s32* D_psp_091CE248;
extern s32* D_psp_091CE240;
extern s32* D_psp_091CE238;
extern s32* D_psp_091CE230;
extern s32* D_psp_091CE228;
extern s32* D_psp_091CE220;
extern s32* D_psp_091CE218;
extern s32* D_psp_091CE210;
extern s32* D_psp_091CE208;
extern s32* D_psp_091CE200;
extern s32* D_psp_091CE1F8;
extern s32* D_psp_091CE1F0;

extern s32 D_psp_0914C240;
extern s32 D_psp_0914C250;
extern s32 D_psp_0914C268;
extern s32 D_psp_0914C278;
extern s32 D_psp_0914C288;
extern s32 D_psp_0914C298;
extern s32 D_psp_0914C000;
extern s32 D_psp_0914C2A0;
extern s32 D_psp_0914C2A8;
extern s32 D_psp_0914C170;
extern s32 D_psp_0914C2B0;
extern s32 D_psp_0914C2C0;

extern s32 D_psp_0914C190;
extern s32 D_psp_0914C1A8;
extern s32 D_psp_0914C1C0;
extern s32 D_psp_0914C1D8;
extern s32 D_psp_0914C1F0;
extern s32 D_psp_0914C200;
extern s32 D_psp_0914C208;
extern s32 D_psp_0914C210;
extern s32 D_psp_0914C218;
extern s32 D_psp_0914C220;
extern s32 D_psp_0914C228;
extern s32 D_psp_0914C230;

extern s32 D_psp_0914C0F0;
extern s32 D_psp_0914C108;
extern s32 D_psp_0914C120;
extern s32 D_psp_0914C138;
extern s32 D_psp_0914C148;
extern s32 D_psp_0914C158;
extern s32 D_psp_0914C000;
extern s32 D_psp_0914C160;
extern s32 D_psp_0914C168;
extern s32 D_psp_0914C170;
extern s32 D_psp_0914C178;
extern s32 D_psp_0914C180;

extern s32 D_psp_0914C038;
extern s32 D_psp_0914C048;
extern s32 D_psp_0914C060;
extern s32 D_psp_0914C078;
extern s32 D_psp_0914C090;
extern s32 D_psp_0914C0A8;
extern s32 D_psp_0914C0B0;
extern s32 D_psp_0914C0B8;
extern s32 D_psp_0914C0C0;
extern s32 D_psp_0914C0C8;
extern s32 D_psp_0914C0D0;
extern s32 D_psp_0914C0E0;

extern s32 D_psp_0914BFA0;
extern s32 D_psp_0914BFB0;
extern s32 D_psp_0914BFC0;
extern s32 D_psp_0914BFD0;
extern s32 D_psp_0914BFE8;
extern s32 D_psp_0914BFF8;
extern s32 D_psp_0914C000;
extern s32 D_psp_0914C008;
extern s32 D_psp_0914C010;
extern s32 D_psp_0914C018;
extern s32 D_psp_0914C020;
extern s32 D_psp_0914C030;

void func_psp_090F5560(void) {
    g_EquipDefs = GetLang(&D_psp_09192EB0, &D_psp_091A4CE8, &D_psp_09197640,
                          &D_psp_091A04E0, &D_psp_0919BE58);
    g_AccessoryDefs = GetLang(&D_psp_091A8798, &D_psp_091AED90, &D_psp_091AA130,
                              &D_psp_091AD410, &D_psp_091ABB00);
    g_EnemyDefs = GetLang(&D_psp_091B00F0, &D_psp_091C1690, &D_psp_091B4660,
                          &D_psp_091BD110, &D_psp_091B8BB0);
    g_MenuStr = GetLang(&D_psp_091C59C0, &D_psp_091C7080, &D_psp_091C5F58,
                        &D_psp_091C6AF0, &D_psp_091C6550);
    g_SpellDefs = GetLang(&D_psp_091C7398, &D_psp_091C85F8, &D_psp_091C7828,
                          &D_psp_091C8158, &D_psp_091C7CD8);
    g_RelicDefs = GetLang(&D_psp_091C8E40, &D_psp_091CAB00, &D_psp_091C9560,
                          &D_psp_091CA398, &D_psp_091C9C90);
    g_SaveAreaNames = GetLang(&D_psp_0914A918, &D_psp_0914BBE0, &D_psp_0914ADB8,
                              &D_psp_0914B748, &D_psp_0914B260);
    g_SaveAreaNamesSecondPart =
        GetLang(&D_psp_0914AB00, &D_psp_0914BE60, &D_psp_0914AFF8,
                &D_psp_0914B960, &D_psp_0914B4A0);
    switch (g_UserLanguage) {
    case LANG_EN:
    default:
        D_psp_091CE248 = &D_psp_0914BFA0;
        D_psp_091CE240 = &D_psp_0914BFB0;
        D_psp_091CE238 = &D_psp_0914BFC0;
        D_psp_091CE230 = &D_psp_0914BFD0;
        D_psp_091CE228 = &D_psp_0914BFE8;
        D_psp_091CE220 = &D_psp_0914BFF8;
        D_psp_091CE218 = &D_psp_0914C000;
        D_psp_091CE210 = &D_psp_0914C008;
        D_psp_091CE208 = &D_psp_0914C010;
        D_psp_091CE200 = &D_psp_0914C018;
        D_psp_091CE1F8 = &D_psp_0914C020;
        D_psp_091CE1F0 = &D_psp_0914C030;
        break;
    case LANG_FR:
        D_psp_091CE248 = &D_psp_0914C038;
        D_psp_091CE240 = &D_psp_0914C048;
        D_psp_091CE238 = &D_psp_0914C060;
        D_psp_091CE230 = &D_psp_0914C078;
        D_psp_091CE228 = &D_psp_0914C090;
        D_psp_091CE220 = &D_psp_0914C0A8;
        D_psp_091CE218 = &D_psp_0914C0B0;
        D_psp_091CE210 = &D_psp_0914C0B8;
        D_psp_091CE208 = &D_psp_0914C0C0;
        D_psp_091CE200 = &D_psp_0914C0C8;
        D_psp_091CE1F8 = &D_psp_0914C0D0;
        D_psp_091CE1F0 = &D_psp_0914C0E0;
        break;
    case LANG_SP:
        D_psp_091CE248 = &D_psp_0914C0F0;
        D_psp_091CE240 = &D_psp_0914C108;
        D_psp_091CE238 = &D_psp_0914C120;
        D_psp_091CE230 = &D_psp_0914C138;
        D_psp_091CE228 = &D_psp_0914C148;
        D_psp_091CE220 = &D_psp_0914C158;
        D_psp_091CE218 = &D_psp_0914C000;
        D_psp_091CE210 = &D_psp_0914C160;
        D_psp_091CE208 = &D_psp_0914C168;
        D_psp_091CE200 = &D_psp_0914C170;
        D_psp_091CE1F8 = &D_psp_0914C178;
        D_psp_091CE1F0 = &D_psp_0914C180;
        break;
    case LANG_GE:
        D_psp_091CE248 = &D_psp_0914C190;
        D_psp_091CE240 = &D_psp_0914C1A8;
        D_psp_091CE238 = &D_psp_0914C1C0;
        D_psp_091CE230 = &D_psp_0914C1D8;
        D_psp_091CE228 = &D_psp_0914C1F0;
        D_psp_091CE220 = &D_psp_0914C200;
        D_psp_091CE218 = &D_psp_0914C208;
        D_psp_091CE210 = &D_psp_0914C210;
        D_psp_091CE208 = &D_psp_0914C218;
        D_psp_091CE200 = &D_psp_0914C220;
        D_psp_091CE1F8 = &D_psp_0914C228;
        D_psp_091CE1F0 = &D_psp_0914C230;
        break;
    case LANG_IT:
        D_psp_091CE248 = &D_psp_0914C240;
        D_psp_091CE240 = &D_psp_0914C250;
        D_psp_091CE238 = &D_psp_0914C268;
        D_psp_091CE230 = &D_psp_0914C278;
        D_psp_091CE228 = &D_psp_0914C288;
        D_psp_091CE220 = &D_psp_0914C298;
        D_psp_091CE218 = &D_psp_0914C000;
        D_psp_091CE210 = &D_psp_0914C2A0;
        D_psp_091CE208 = &D_psp_0914C2A8;
        D_psp_091CE200 = &D_psp_0914C170;
        D_psp_091CE1F8 = &D_psp_0914C2B0;
        D_psp_091CE1F0 = &D_psp_0914C2C0;
        break;
    }
}

// No idea what's going on here, none of these seem to be touched
// outside of this function? Maybe some fake syms. Weird.
extern EnemyDef* D_psp_091CF7CC;
extern Equipment* D_psp_091CF7F4;
extern Accessory* D_psp_091CF7F8;
extern RelicDesc* D_psp_091CF814;
void func_psp_090F5B10(void) {
    D_psp_091CF7F4 = g_EquipDefs;
    D_psp_091CF7F8 = g_AccessoryDefs;
    D_psp_091CF7CC = g_EnemyDefs;
    D_psp_091CF814 = g_RelicDefs;
}

extern void* g_ApiInit[sizeof(GameApi) / sizeof(void*)];
extern GpuUsage g_GpuMaxUsage;
extern s32 g_DebugFreeze;
extern s32 g_DebugHitboxViewMode;
extern u32 D_801362B4;
extern s32 D_801362B8;
extern s32 D_801362BC;
extern s32 g_DebugPalIdx;
extern DebugColorChannel g_DebugColorChannel;
extern u32 D_801362C8;
extern s32 g_DebugIsRecordingVideo;
extern OT_TYPE* g_CurrentOT;


extern s32 D_psp_091FC4A0;
extern s32 D_psp_091CE1E8;
extern s32 D_psp_091CE2A0;
extern s32 D_psp_091FC3F8;
extern s32 D_psp_091FC400;
extern s32 D_psp_091FC408;
extern s32 D_psp_091FC410;

INCLUDE_ASM("dra_psp/psp/dra_psp/186E8", MainGame);

INCLUDE_ASM("dra_psp/psp/dra_psp/186E8", func_psp_090F6368);

INCLUDE_ASM("dra_psp/psp/dra_psp/186E8", SetGameState);
