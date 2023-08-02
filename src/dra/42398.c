#include "dra.h"

#define DISP_ALL_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_ALL_H
#define DISP_MENU_W 384
#define DISP_MENU_H DISP_ALL_H
#define DISP_UNK2_W 512
#define DISP_UNK2_H DISP_ALL_H

#if defined(VERSION_US)
#define PAD_RESETCOMBO ((PAD_START) | (PAD_SELECT))
#elif defined(VERSION_HD)
#define PAD_RESETCOMBO                                                         \
    ((PAD_START) | (PAD_SELECT) | (PAD_L2) | (PAD_R2) | (PAD_L1) | (PAD_R1))
#endif

s32 LoadVabData(void);
void func_800E385C(u32*);
void UpdateGame(void);
void func_800E7BB8(void);
void SetupEvents(void);
void func_800EA7CC(void);
void func_800EB314(void);
void RenderEntities(void);
void func_800ECBF8(void);
void RenderTilemap(void);
void RenderPrimitives(void);
void func_800FADC0(void);
void func_801026BC(s32);
void DrawEntitiesHitbox(s32 blendMode);
void UpdateCd(void);
s32 func_8010E27C(void);
void SetSpeedX(s32);
void func_801324B4(s8 s_num, s16 arg1, s16 arg2);
void SoundInit(void);
void func_801353A0(void);
s32 func_80136010(void);

const char aO[] = "\no\n";
const char D_800DB3B8[] = "sim:c:\\bin\\dra000.bmp";
const char D_800DB3D0[] = "cre err:%s\n";
const char D_800DB3DC[] = "wr err\n";
const char D_800DB3E4[] = "clo err\n";
const char D_800DB3F0[] = "sim:c:\\bin\\dra000.mov";
const char D_800DB408[] = "pale";
const char D_800DB410[] = "reverse";
const char D_800DB418[] = "light";
const char D_800DB420[] = "dark";
const char D_800DB428[] = "normal";

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (g_DebugWaitInfoTimer++ & 4) {
        FntPrint(&aO); // TODO: inline
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

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

    StoreImage(&g_CurrentBuffer->disp.disp, (u32*)0x80200000);
    DrawSync(0);

    for (i = 0; i < MaxScreenshotCount; i++) {
        __builtin_memcpy(fileName, D_800DB3B8, sizeof(D_800DB3B8));
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
        FntPrint(D_800DB3D0, &fileName);
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
        FntPrint(D_800DB3DC);
        return;
    }

    bufferPos = 0;
    dst = buffer;
    src = 0x80200000;
    for (i = height - 1; i >= 0; i--) {
        u16* start = buffer;
        for (j = 0; j < width; j++) {
            u16 pixelColor = src[j + i * width];
            *dst++ = (pixelColor >> 7) & 0xF8; // B
            *dst++ = (pixelColor >> 2) & 0xF8; // G
            *dst++ = (pixelColor & 0x1F) << 3; // R
            if (++bufferPos == 0x10) {
                if (write(fid, start, bufferPos * BytesPerPixel) < 0) {
                    FntPrint(D_800DB3DC);
                    return;
                }
                bufferPos = 0;
                dst = start;
            }
        }
    }

    if (bufferPos != 0) {
        if (write(fid, &buffer, bufferPos * BytesPerPixel) < 0) {
            FntPrint(D_800DB3DC);
            return;
        }
    }
    if (close(fid) < 0) {
        FntPrint(D_800DB3E4);
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
            __builtin_memcpy(fileName, D_800DB3F0, sizeof(D_800DB3F0));
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
            FntPrint(D_800DB3D0, fileName);
            return;
        }
        g_DebugIsRecordingVideo = true;
    } else if (g_pads[0].tapped & PAD_TRIANGLE) {
        g_DebugIsRecordingVideo = false;
        if (close(g_DebugRecordVideoFid) < 0) {
            FntPrint(D_800DB3E4);
        }
        return;
    }

    StoreImage(&g_CurrentBuffer->disp.disp, (u_long*)0x80200000);
    DrawSync(0);

    src = 0x80200000;
    i = 0;
    bufferPos = 0;
    dst = buffer;
    start = buffer;
    for (; i < 0x40; i++) {
        for (j = 0; j < 0x40; j++) {
            *dst++ = src[0x6060 + i * 0x100 + j];
            if (++bufferPos == 0x10) {
                if (write(g_DebugRecordVideoFid, start, bufferPos * 2) < 0) {
                    FntPrint(D_800DB3DC);
                    return;
                }
                bufferPos = 0;
                dst = start;
            }
        }
    }

    if (bufferPos != 0) {
        if (write(g_DebugRecordVideoFid, buffer, bufferPos * 2) < 0) {
            FntPrint(D_800DB3DC);
            return;
        }
    }
}

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
        var_s7 = (((u16)D_801362C8) << 5) - 0x20;
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
    sprite->clut = D_8003C104[g_DebugCurPal];
    AddPrim(&g_CurrentOT[0x1FE], sprite);
    g_GpuUsage.sp++;
    SetDrawMode(
        drMode, 0, 0, (((u32)D_801362B4) >> 2) + var_s7, &g_Vram.D_800ACD80);
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

s32 DebugUpdate(void) {
#if defined(VERSION_HD)
    DebugCaptureScreen();
    DebugCaptureVideo();
    if (g_DebugEnabled) {
        FntPrint("debug on\n");
        if (g_DebugEnabled && g_DebugMode != DEBUG_NORMAL) {
            if (g_DebugMode == DEBUG_PALETTE_VIEWER) {
                // control debug palette menu
                if (g_pads[1].tapped & PAD_UP) {
                    if (g_pads[1].pressed & PAD_R2) {
                        g_DebugCurPal -= COLORS_PER_PAL;
                        if (g_DebugCurPal > 0x800) {
                            g_DebugCurPal += 0x300;
                        }
                    } else if (g_pads[1].pressed & PAD_R1) {
                        DebugEditColorChannel(-1);
                    } else {
                        D_801362B4 -= COLORS_PER_PAL;
                        if (D_801362B4 < 0x20) {
                            D_801362B4 += 0x60;
                        }
                    }
                }
                if (g_pads[1].tapped & PAD_DOWN) {
                    if (g_pads[1].pressed & PAD_R2) {
                        g_DebugCurPal += COLORS_PER_PAL;
                        if (g_DebugCurPal >= 0x300) {
                            g_DebugCurPal -= 0x300;
                        }
                    } else if (g_pads[1].pressed & PAD_R1) {
                        DebugEditColorChannel(1);
                    } else {
                        D_801362B4 += COLORS_PER_PAL;
                        if (D_801362B4 >= 0x80) {
                            D_801362B4 -= 0x60;
                        }
                    }
                }
                if (g_pads[1].tapped & PAD_LEFT) {
                    if (g_pads[1].pressed & PAD_R2) {
                        g_DebugCurPal--;
                        if (g_DebugCurPal > 0x800) {
                            g_DebugCurPal += 0x300;
                        }
                    } else if (g_pads[1].pressed & PAD_R1) {
                        g_DebugPalIdx--;
                        g_DebugPalIdx &= COLORS_PER_PAL - 1;
                    } else {
                        D_801362B4--;
                        if (D_801362B4 < 0x20) {
                            D_801362B4 += 0x60;
                        }
                    }
                }
                if (g_pads[1].tapped & PAD_RIGHT) {
                    if (g_pads[1].pressed & PAD_R2) {
                        g_DebugCurPal++;
                        if (g_DebugCurPal >= 0x300) {
                            g_DebugCurPal -= 0x300;
                        }
                    } else if (g_pads[1].pressed & PAD_R1) {
                        g_DebugPalIdx++;
                        g_DebugPalIdx &= COLORS_PER_PAL - 1;
                    } else {
                        D_801362B4++;
                        if (D_801362B4 >= 0x80) {
                            D_801362B4 -= 0x60;
                        }
                    }
                }
                if (g_pads[1].pressed & PAD_R1) {
                    if (g_pads[1].tapped & PAD_CIRCLE) {
                        g_DebugColorChannel = DEBUG_COLOR_CHANNEL_RED;
                    }
                    if (g_pads[1].tapped & PAD_TRIANGLE) {
                        g_DebugColorChannel = DEBUG_COLOR_CHANNEL_GREEN;
                    }
                    if (g_pads[1].tapped & PAD_CROSS) {
                        g_DebugColorChannel = DEBUG_COLOR_CHANNEL_BLUE;
                    }
                    if (g_pads[1].tapped & PAD_SQUARE) {
                        D_801362C8 = (D_801362C8 + 1) % 5;
                    }
                }
                if (g_pads[1].pressed & PAD_R2 &&
                    g_pads[1].tapped & PAD_SQUARE) {
                    g_Clut[g_DebugCurPal * 0x10 + g_DebugPalIdx] ^= 0x8000;
                }
            } else {
                // tileset viewer debug cont
                FntPrint("dd on\n");
                if (g_pads[1].tapped & PAD_UP) {
                    D_801362BC -= 0x80;
                    if (D_801362BC < 0) {
                        D_801362BC = 0x180;
                    }
                }
                if (g_pads[1].tapped & PAD_DOWN) {
                    D_801362BC += 0x80;
                    if (D_801362BC > 0x180) {
                        D_801362BC = 0;
                    }
                }
                if (g_pads[1].tapped & PAD_LEFT) {
                    D_801362B8 -= 0x80;
                    if (D_801362B8 < 0) {
                        D_801362B8 = 0x380;
                    }
                }
                if (g_pads[1].tapped & PAD_RIGHT) {
                    D_801362B8 += 0x80;
                    if (D_801362B8 > 0x380) {
                        D_801362B8 = 0;
                    }
                }
            }

            // each debug mode has its own viewport resolution
            switch (g_DebugMode) {
            case DEBUG_TEXTURE_VIEWER:
                SetDefDispEnv(&g_GpuBuffers[0].disp, D_801362B8, D_801362BC,
                              0x200, 0x1E0);
                SetDefDispEnv(&g_GpuBuffers[1].disp, D_801362B8, D_801362BC,
                              0x200, 0x1E0);
                break;
            case DEBUG_TILESET_VIEWER:
                SetDefDispEnv(&g_GpuBuffers[0].disp, D_801362B8, D_801362BC,
                              DISP_STAGE_W, DISP_STAGE_H);
                SetDefDispEnv(&g_GpuBuffers[1].disp, D_801362B8, D_801362BC,
                              DISP_STAGE_W, DISP_STAGE_H);
                break;
            case 3: // palette viewer at 256x240
                SetDefDispEnv(&g_GpuBuffers[0].disp, DISP_STAGE_W, 0,
                              DISP_STAGE_W, DISP_STAGE_H);
                SetDefDispEnv(
                    &g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
                func_800E2B00();
                break;
            }
        }
    }
    if (g_pads[1].tapped & PAD_START) {
        g_DebugEnabled ^= 1;
        if (!g_DebugEnabled) {
            // when disabled, revert into the Stage resolution mode
            SetDefDispEnv(&g_GpuBuffers[0].disp, DISP_STAGE_W, 0, DISP_STAGE_W,
                          DISP_STAGE_H);
            SetDefDispEnv(
                &g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
            return 1;
        }
    }
    if (g_DebugEnabled) {
        if (g_DebugMode != DEBUG_PALETTE_VIEWER) {
            if (g_pads[1].tapped & PAD_CROSS) {
                g_DebugHitboxViewMode++;
                if (g_DebugHitboxViewMode == 5) {
                    g_DebugHitboxViewMode = 0;
                }
            }
            if (g_pads[1].tapped & PAD_SQUARE) {
                // enable or disable advancing frame by frame
                g_DebugFreeze ^= 1;
            }
        }

        // rotate between the different debug modes
        if (g_pads[1].tapped & PAD_TRIANGLE) {
            if (!(g_pads[1].pressed & PAD_R1)) {
                g_DebugMode++;
                g_DebugMode %= DEBUG_END;
                if (g_DebugMode == 0) {
                    SetDefDispEnv(&g_GpuBuffers[0].disp, DISP_STAGE_W, 0,
                                  DISP_STAGE_W, DISP_STAGE_H);
                    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W,
                                  DISP_STAGE_H);
                }
            }
        }
    }

    if (g_DebugEnabled && g_DebugFreeze != 0 &&
        !(g_pads[1].tapped & PAD_CIRCLE) &&
        g_DebugMode != DEBUG_PALETTE_VIEWER) {
        return 0; // do not run next frame
    }
    return 1; // run next frame
#endif
}

void PrintGpuInfo(void) {
    if (!g_DebugEnabled)
        return;

    if (g_pads[1].pressed & PAD_SELECT) {
        FntPrint("dr  :%03x\n", g_GpuMaxUsage.drawModes);
        FntPrint("gt4 :%03x\n", g_GpuMaxUsage.gt4);
        FntPrint("g4  :%03x\n", g_GpuMaxUsage.g4);
        FntPrint("gt3 :%03x\n", g_GpuMaxUsage.gt3);
        FntPrint("line:%03x\n", g_GpuMaxUsage.line);
        FntPrint("sp16:%03x\n", g_GpuMaxUsage.sp16);
        FntPrint("sp  :%03x\n", g_GpuMaxUsage.sp);
        FntPrint("tile:%03x\n", g_GpuMaxUsage.tile);
        FntPrint("env :%03x\n", g_GpuMaxUsage.env);
        FntPrint("eff :%03x\n", D_800A2438);
    }

    if (g_DebugMode == DEBUG_PALETTE_VIEWER) {
        u16 r, g, b;

        switch (g_DebugColorChannel) {
        case DEBUG_COLOR_CHANNEL_RED:
            FntPrint("red");
            break;
        case DEBUG_COLOR_CHANNEL_GREEN:
            FntPrint("green");
            break;

        case DEBUG_COLOR_CHANNEL_BLUE:
            FntPrint("blue");
            break;
        }

        if (g_Clut[g_DebugCurPal * COLORS_PER_PAL + g_DebugPalIdx] & 0x8000) {
            FntPrint("  half on\n");
        } else {
            FntPrint("  half off\n");
        };

        r = g_Clut[g_DebugCurPal * COLORS_PER_PAL + g_DebugPalIdx] & 0x1F;
        g = g_Clut[g_DebugCurPal * COLORS_PER_PAL + g_DebugPalIdx] >> 5 & 0x1F;
        b = g_Clut[g_DebugCurPal * COLORS_PER_PAL + g_DebugPalIdx] >> 10 & 0x1F;
        FntPrint("rgb:%02X,%02X,%02X\n", r, g, b);
    } else {
        FntPrint("01:%04x,%04x\n", D_8006C384, D_8006C388);
        FntPrint("23:%04x,%04x\n", D_8006C38C, D_8006C390);
    }
}

void PrintHBlankInfo(void) {
    if (g_DebugEnabled && g_DebugMode != DEBUG_PALETTE_VIEWER) {
        if (g_blinkTimer & 1) {
            FntPrint("l=%03x/100\n", D_801362D0[1]);
            FntPrint("l=%03x/100\n", D_801362D0[0]);
        } else {
            FntPrint("l=%03x/100\n", D_801362D0[0]);
            FntPrint("l=%03x/100\n", D_801362D0[1]);
        }
        D_801362D0[0] = D_801362D0[1];
    }
}

extern const char aPqes[];
extern const char aPqes_0[];
extern const char aPqes_1[];

void SsVabClose(short vab_id);
#define LOAD_VAB(vab_id, name, addr, data, dataLen)                            \
    SsVabClose(vab_id);                                                        \
    while (SsVabTransCompleted(SS_IMEDIATE) != 1)                              \
        ;                                                                      \
                                                                               \
    if (SsVabOpenHeadSticky(name, vab_id, addr) < 0) {                         \
        return -1;                                                             \
    }                                                                          \
    if (SsVabTransBodyPartly(data, dataLen, vab_id) < 0) {                     \
        return -1;                                                             \
    }                                                                          \
    while (SsVabTransCompleted(SS_IMEDIATE) != 1)

s32 LoadVabData(void) {
    const int vab0Len = 269488;
#if defined(VERSION_US)
    const int vab1Len = 57744;
    const int vab2Len = 64496;
    const int vab3Len = 108048;
#elif defined(VERSION_HD)
    const int vab1Len = 57808;
    const int vab2Len = 65200;
    const int vab3Len = 107792;
#endif

    LOAD_VAB(0, &aPbav, g_VabAddrs[0], D_8013B6A0, vab0Len);
    LOAD_VAB(1, &aPbav_0, g_VabAddrs[1], D_8017D350, vab1Len);
    LOAD_VAB(2, &aPbav_1, g_VabAddrs[2], D_801A9C80, vab2Len);
    LOAD_VAB(3, &aPbav_2, g_VabAddrs[3], D_8018B4E0, vab3Len);
    func_80131EBC(&aPqes, 0x618);
    func_80131EBC(&aPqes_0, 0x201);
    func_80131EBC(&aPqes_1, 0x205);
    return 0;
}

void func_800E346C(void) {
    g_GpuBuffers[0].draw.r0 = 0;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0;
    g_GpuBuffers[1].draw.r0 = 0;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0;
}

void func_800E34A4(s8 arg0) {
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
#ifndef NON_MATCHING
    g_GpuBuffers_1_buf_draw_clip_y = arg0 == 0 ? 0x0014 : 0x0114;
#else
    g_GpuBuffers[1].draw.clip.y = 0x0014;
#endif
    g_GpuBuffers[1].draw.clip.h = 0x00CF;
    g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.isbg = 1;
    func_800E346C();
    g_GpuBuffers[1].draw.dtd = 0;
    g_GpuBuffers[0].draw.dtd = 0;
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

void SetStageDisplayBuffer(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(
        &g_GpuBuffers[1].draw, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(
        &g_GpuBuffers[0].disp, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_800E34DC(0);
}

void SetCgiDisplayBuffer(s32 width) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, width, DISP_ALL_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, width, DISP_ALL_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, width, DISP_ALL_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, width, DISP_ALL_H);
    func_800E34DC(1);
}

void SetMenuDisplayBuffer(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_MENU_W, DISP_MENU_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 128, 256, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 128, 256, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_MENU_W, DISP_MENU_H);
    func_800E34DC(1);
}

void SetTitleDisplayBuffer(void) {
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
    func_800E346C();
    g_GpuBuffers[1].disp.isrgb24 = 0;
    g_GpuBuffers[0].disp.isrgb24 = 0;
}

void func_800E385C(u_long* ot) {
    s32 i;
    s32 var_t0;
    u_long* var_t1;

    var_t0 = false;
    for (i = 0; i < OTSIZE; i++, ot++) {
        if (var_t0 == false) {
            if (getaddr(ot) == ((u_long)ot & 0xffffff) + 4) {
                var_t0 = true;
                var_t1 = ot;
            }
        } else {
            if (getaddr(ot) != ((u_long)ot & 0xffffff) + 4) {
                *var_t1 = (u_long)ot & 0xffffff;
                var_t0 = false;
            }
        }
    }
}

void func_800E38CC(void) {
    if (D_800A015C != 0) {
        if (D_800A0158 >= 0x24) {
            g_BackBuffer->disp.screen.x = 0;
            PutDispEnv(&g_BackBuffer->disp);
        } else {
            g_BackBuffer->disp.screen.x = D_80136308[D_800A0158 + D_800A04F8];
            PutDispEnv(&g_BackBuffer->disp);
            D_800A0158++;
            SetRCnt(0xF2000001, 6, 0x1000);
        }
    }
}

void entrypoint_sotn(void) {
#if defined(VERSION_HD)
    CdlFILE fp;
#endif
    s32 i;

#if defined(VERSION_US)
    SetVideoMode(0);
#endif
    InitializePads();
    InitCARD(1);
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
    SetupEvents();
    ResetGraph(0);
    SetGraphDebug(0);
    InitGeom();
    GsInitVcount();
    g_GpuBuffers[0].next = &g_GpuBuffers[1];
    g_GpuBuffers[1].next = &g_GpuBuffers[0];
    ClearImage(&g_Vram.D_800ACD88, 0x5A, 0x50, 0x46);
    ClearImage(&g_Vram.D_800ACD90, 0, 0, 0);
    for (i = 0; i < 0x50; i++) {
        ((void**)&g_api)[i] = (&D_800A0004)[i];
    }
    g_blinkTimer = 0;
    D_8003C99C = 0;
    D_800987B4 = 0;
    g_Settings.D_8003CB00 = 0;
    g_Settings.D_8003CB04 = 0;
    g_CurrentBuffer = &g_GpuBuffers[0];
#if defined(VERSION_US)
    func_80131ED8(0xB9B6);
#elif defined(VERSION_HD)
    do {

    } while (CdSearchFile(&fp, "\\SD\\XA_STR1.;1") == 0);
    func_80131ED8(CdPosToInt(&fp));
#endif
    SoundInit();
    while (LoadVabData() < 0)
        ;
    VSyncCallback(func_800E7BB8);
    FntLoad(0x380, 0x100);
    SetDumpFnt(FntOpen(8, 0x30, 0x200, 0x100, 0, 0x200));
    SetDispMask(1);
    SetGameState(Game_Init);

    g_GpuMaxUsage.drawModes = 0;
    g_GpuMaxUsage.gt4 = 0;
    g_GpuMaxUsage.g4 = 0;
    g_GpuMaxUsage.gt3 = 0;
    g_GpuMaxUsage.line = 0;
    g_GpuMaxUsage.sp16 = 0;
    g_GpuMaxUsage.tile = 0;
    g_GpuMaxUsage.sp = 0;
    g_GpuMaxUsage.env = 0;
#if defined(VERSION_US)
    g_DebugPlayer = 0;
#elif defined(VERSION_HD)
    g_DebugPlayer = 1;
#endif
loop_5:
    D_8003C73C = 0;
    SetStageDisplayBuffer();
    func_800ECBF8();
    func_800EAD7C();
    HideAllBackgroundLayers();
    DestroyAllPrimitives();
    func_800EDAE4();
    DestroyEntities(0);
    func_800EA538(0);
    func_800EAEEC();
    D_801362B4 = 0x20;
    g_DebugCurPal = 0x200;
    g_DebugEnabled = 0;
    g_DebugHitboxViewMode = 0;
    D_801362B8 = 0;
    D_801362BC = 0;
    g_DebugMode = DEBUG_NORMAL;
    g_DebugFreeze = 0;
    g_DebugPalIdx = 0;
    g_DebugColorChannel = DEBUG_COLOR_CHANNEL_RED;
    D_801362C8 = 0;
    g_DebugIsRecordingVideo = false;
    g_DemoMode = Demo_None;
    D_8003C704 = 0;
    D_800973EC = 0;
    D_800974A4 = 0;
    g_CdStep = CdStep_None;
    D_80097928 = 0;
    D_80097910 = 0;
    D_80097904 = 0;
    D_8006C3AC = 0;
    D_80097C98 = 0;
#if defined(VERSION_US)
    g_softResetTimer = 0;
#endif
    D_800978C4 = 1;

    while (true) {
        g_BackBuffer = g_CurrentBuffer;
        g_CurrentBuffer = g_CurrentBuffer->next;
        g_blinkTimer++;
        g_CurrentOT = g_CurrentBuffer->ot;
        ClearOTag(g_CurrentOT, OTSIZE);
        g_GpuUsage.drawModes = 0;
        g_GpuUsage.env = 0;
        g_GpuUsage.gt4 = 0;
        g_GpuUsage.g4 = 0;
        g_GpuUsage.gt3 = 0;
        g_GpuUsage.line = 0;
        g_GpuUsage.sp16 = 0;
        g_GpuUsage.tile = 0;
        g_GpuUsage.sp = 0;
        if (DebugUpdate() != 0) {
            UpdateGame();
        }
        if (D_8003C0F8 == 0 && D_800973EC == 0) {
            RenderTilemap();
            RenderEntities();
            if (g_GameState == Game_Play && g_DebugEnabled) {
                if (g_DebugHitboxViewMode != 0) {
                    DrawEntitiesHitbox(g_DebugHitboxViewMode);
                }
            }
        }
        RenderPrimitives();
        UpdateCd();
#if defined(VERSION_HD)
        PrintGpuInfo();
#endif
        func_800E385C(g_CurrentOT);
        DrawSync(0);
        D_801362D4 = GsGetVcount();
#if defined(VERSION_HD)
        PrintHBlankInfo();
#endif
        VSync(D_8003C73C);
        GsClearVcount();
        func_800EB314();
        ReadPads();
#if defined(VERSION_US)
        if ((g_pads->pressed & PAD_RESETCOMBO) == PAD_RESETCOMBO) {
            if (g_pads[0].tapped & PAD_START) {
                g_softResetTimer = 1;
            }
            if (g_softResetTimer != 0) {
                g_softResetTimer++;
            } else {
                g_softResetTimer = 0;
            }
        } else {
            g_softResetTimer = 0;
        }
        if (g_softResetTimer >= 0x80) {
            g_softResetTimer = 0;
#elif defined(VERSION_HD)
        if (g_pads->pressed == PAD_RESETCOMBO && g_pads->tapped & PAD_START &&
            D_800978C4 != 0) {
#endif
            ClearBackbuffer();
            func_801073C0();
            PlaySfx(0x12);
            PlaySfx(0xB);
            func_801361F8();
            VSync(D_8003C73C);
            func_80132760();
            SetGameState(Game_Title);
#if defined(VERSION_HD)
            FntFlush(-1);
#endif
            goto loop_5;
        }
        PutDrawEnv(&g_CurrentBuffer->draw);
        PutDispEnv(&g_CurrentBuffer->disp);
        DrawOTag(g_CurrentOT);
        func_800EA7CC();
        func_801361F8();
        if (func_80131F28() > 900) {
            CdInit();
            func_80132760();
        }

        if (g_GpuMaxUsage.drawModes < g_GpuUsage.drawModes) {
            g_GpuMaxUsage.drawModes = g_GpuUsage.drawModes;
        }
        if (g_GpuMaxUsage.gt4 < g_GpuUsage.gt4) {
            g_GpuMaxUsage.gt4 = g_GpuUsage.gt4;
        }
        if (g_GpuMaxUsage.g4 < g_GpuUsage.g4) {
            g_GpuMaxUsage.g4 = g_GpuUsage.g4;
        }
        if (g_GpuMaxUsage.gt3 < g_GpuUsage.gt3) {
            g_GpuMaxUsage.gt3 = g_GpuUsage.gt3;
        }
        if (g_GpuMaxUsage.line < g_GpuUsage.line) {
            g_GpuMaxUsage.line = g_GpuUsage.line;
        }
        if (g_GpuMaxUsage.sp16 < g_GpuUsage.sp16) {
            g_GpuMaxUsage.sp16 = g_GpuUsage.sp16;
        }
        if (g_GpuMaxUsage.tile < g_GpuUsage.tile) {
            g_GpuMaxUsage.tile = g_GpuUsage.tile;
        }
        if (g_GpuMaxUsage.sp < g_GpuUsage.sp) {
            g_GpuMaxUsage.sp = g_GpuUsage.sp;
        }
        if (g_GpuMaxUsage.env < g_GpuUsage.env) {
            g_GpuMaxUsage.env = g_GpuUsage.env;
        }

        // Update game timer
        D_801362D4 = (D_801362D4 + 0xFF) >> 8;
        D_8003C99C += D_801362D4;
        if (D_800973EC == 0 && D_800974A4 == 0) {
            g_Status.timerFrames += D_801362D4;
            if (g_Status.timerFrames >= 60) {
                g_Status.timerFrames -= 60;
                g_Status.timerSeconds++;
                if (g_Status.timerSeconds >= 60) {
                    g_Status.timerSeconds -= 60;
                    g_Status.timerMinutes++;
                    if (g_Status.timerMinutes >= 60) {
                        g_Status.timerMinutes -= 60;
                        g_Status.timerHours++;
                        if (g_Status.timerHours >= 100) {
                            g_Status.timerSeconds = 59;
                            g_Status.timerMinutes = 59;
                            g_Status.timerHours = 99;
                        }
                    }
                }
            }
        }
        rand();
#if defined(VERSION_HD)
        FntFlush(-1);
#endif
    }
}

void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_800E414C(void) {
    RoomTeleport* temp_a1;
    s32 temp_a0;

    if (!(D_8003C708.flags & 0x40)) {
        return;
    }

    func_8010DFF0(1, 1);
    if (D_8003C708.unk2 != 0 &&
        !(PLAYER.posX.i.hi >= 8 && PLAYER.posX.i.hi < 249)) {
        return;
    }

    switch (D_8003C708.unk2) {
    case 0:
        func_800EA538(1);
        temp_a1 = &D_800A245C[D_8003C708.zPriority];
        temp_a0 = g_StageId & STAGE_INVERTEDCASTLE_FLAG;
        D_8003C710 = temp_a1->stageId;
        if (temp_a0 != 0) {
            D_8003C710 ^= STAGE_INVERTEDCASTLE_FLAG;
        }
        D_8003C712 = temp_a1->unk6;
        if (temp_a0 != 0) {
            D_8003C712 ^= STAGE_INVERTEDCASTLE_FLAG;
        }
        PlaySfx(0x80);
        D_80097928 = 1;
        if (D_8003C708.flags == 0x40) {
            g_Player.D_80072EFC = 0x18;
            g_Player.D_80072EF4 = 0x8000;
        } else {
            g_Player.D_80072EFC = 0x18;
            g_Player.D_80072EF4 = 0x2000;
        }
        D_8003C708.unk2++;
        return;
    case 1:
        if (!func_80131F68()) {
            if (g_UseDisk != 0) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr | 0x8000;
            }
            g_mapTilesetId = D_8003C710;
            D_8003C708.unk2++;
            return;
        }
        break;
    case 2:
        if (!g_UseDisk) {
            break;
        }
        if (D_8003C708.flags == 0x40 && PLAYER.posX.i.hi < 0x78) {
            func_801073C0();
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_mapTilesetId = D_8003C710;
            D_8003C708.unk2++;
        }
        if (D_8003C708.flags == 0x41 && PLAYER.posX.i.hi >= 0x89) {
            func_801073C0();
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_mapTilesetId = D_8003C710;
            D_8003C708.unk2++;
            return;
        }
        break;
    case 3:
        if (!g_UseDisk) {
            break;
        }
        if (D_8003C708.flags == 0x40 && PLAYER.posX.i.hi >= 0x89) {
            func_801073C0();
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_mapTilesetId = D_8003C712;
            D_8003C708.unk2 = 2;
        }
        if (D_8003C708.flags == 0x41 && PLAYER.posX.i.hi < 0x78) {
            func_801073C0();
            g_CdStep = 1;
            g_LoadFile = CdFile_StageChr;
            g_mapTilesetId = D_8003C712;
            D_8003C708.unk2 = 2;
        }
        break;
    }
}

void ClearBackbuffer(void) { ClearImage(&g_Vram.D_800ACDA0, 0, 0, 0); }

void HandleTitle(void) {
    void (*callback)(void);

    switch (g_GameStep) {
    case 0:
        ClearBackbuffer();
        func_800ECBF8();
        func_800EAD7C();
        HideAllBackgroundLayers();
        DestroyAllPrimitives();
        func_800EDAE4();
        ResetEntityArray();
        DestroyEntities(0);
        func_800EA538(0);
        func_800EAEEC();
        SetStageDisplayBuffer();
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                return;
            }
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_Sel;
        }
        g_GameStep++;
        break;
#if defined(VERSION_US)
    case 100:
        if (!g_IsUsingCd) {
            RECT rect;
            rect.x = 0;
            rect.y = 0;
            rect.w = 0x280;
            rect.h = 0x100;
            LoadImage(&rect, (u32*)0x80180014);

            rect.x = 0;
            rect.y = 0x100;
            LoadImage(&rect, (u32*)0x80180014);

            SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, 0x280, 0x100);
            SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 0x100, 0x280, 0x100);
            SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0x100, 0x280, 0x100);
            SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, 0x280, 0x100);
            SetDispMask(0);
            D_8013640C = 110;
            g_GameStep++;
        }
        break;
    case 101:
        SetDispMask(1);
        if (D_8013640C == 0 || --D_8013640C == 0) {
            ClearImage(&g_Vram.D_800ACDF0, 0, 0, 0);
            SetStageDisplayBuffer();
            g_StageId = STAGE_SEL;
            if (g_UseDisk) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_Sel;
            }
            g_GameStep = 1;
        }
        break;
#endif
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(2, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(0, SimFileType_System) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 2:
#if defined(VERSION_US)
        g_GameStep = 3;
#else
        g_GameStep++;
#endif
        break;
    case 3:
#if defined(VERSION_US)
        g_GameStep = 4;
#else
        g_GameStep++;
#endif
        break;
    case 4:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
#if defined(VERSION_US)
        g_GameStep = 5;
#else
        g_GameStep++;
#endif
        break;
    case 5:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_StagePrg) < 0) {
                break;
            }
        }
        D_8003C9A4 = 0;
        g_GameStep++;
        break;
    case 6:
#if defined(VERSION_US)
        if (g_GameState == Game_Title) {
            callback = g_api.o.TestCollisions;
        } else {
            callback = g_api.o.InitRoomEntities;
        }
#else
        if (g_GameState == Game_Init) {
            callback = g_api.o.InitRoomEntities;
        } else {
            callback = g_api.o.TestCollisions;
        }
#endif
        callback();
        break;
    }
}

#if defined(VERSION_HD)
const int filesplit_42398_rodata = 0x00000000;
#endif