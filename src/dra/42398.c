#include "dra.h"

#define DISP_ALL_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_ALL_H
#define DISP_MENU_W 384
#define DISP_MENU_H DISP_ALL_H
#define DISP_UNK2_W 512
#define DISP_UNK2_H DISP_ALL_H
#define PAD_RESETCOMBO ((PAD_START) | (PAD_SELECT))

void func_800E2398(const char* str);
s32 func_800E3278(void);
void func_800E385C(u32*);
void UpdateGame(void);
void func_800E7BB8(void);
void func_800E8EE4(void);
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
void AccelerateX(s32);
void func_801324B4(s8 s_num, s16 arg1, s16 arg2);
void func_801325D8(void);
void func_801353A0(void);
s32 func_80136010(void);

extern const char* aO;

void func_800E2398(const char* str) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(str);
    if (D_80136300++ & 4) {
        FntPrint(&aO); // TODO: rodata split
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void func_800E2438(const char* str) {
    while (PadRead(0))
        func_800E2398(str);
    while (!PadRead(0))
        func_800E2398(str);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E249C);

INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E2824);

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

void func_800E2E98(s32 colorAdd) {
    s32 newColorChannel;
    s32 otherColorChannels;
    u16 firstColor;
    u16* palette;

    palette = g_Clut + g_DebugCurPal * COLORS_PER_PAL + g_DebugPalIdx;
    firstColor = palette[0];
    switch (D_801362C4) {
    case 0:
        otherColorChannels = firstColor & 0xFFE0;
        newColorChannel = (firstColor + colorAdd) & 0x1F;
        break;
    case 1:
        otherColorChannels = firstColor & 0xFC1F;
        newColorChannel = (firstColor + (colorAdd << 5)) & 0x3E0;
        break;
    case 2:
        otherColorChannels = firstColor & 0x83FF;
        newColorChannel = (firstColor + (colorAdd << 10)) & 0x7C00;
        break;
    default:
        return;
    }
    *palette = otherColorChannels |= newColorChannel;
}

s32 nullsub_8(void) {}

void func_800E2F3C(void) {
    if (D_800BD1C0 == 0)
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

    if (D_80138FB0 == 3) {
        u16 r, g, b;

        switch (D_801362C4) {
        case 0:
            FntPrint("red");
            break;

        case 1:
            FntPrint("green");
            break;

        case 2:
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

void func_800E31C0(void) {
    if ((D_800BD1C0 != 0) && (D_80138FB0 != 3)) {
        if (g_blinkTimer & 1) {
            FntPrint(D_800DB524, D_801362D0[1]);
            FntPrint(D_800DB524, D_801362D0[0]);
        } else {
            FntPrint(D_800DB524, D_801362D0[0]);
            FntPrint(D_800DB524, D_801362D0[1]);
        }
        D_801362D0[0] = D_801362D0[1];
    }
}

// TODO: fix branching
// DECOMP_ME_WIP func_800E3278 https://decomp.me/scratch/y3otf
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E3278);
#else
extern s32 D_800BD1C8;
extern s32 D_800BD1CC;
extern s32 D_800BD1D0;
extern s32 D_800BD1D4;
extern s32 D_8013B6A0;
extern s32 D_8017D350;
extern s32 D_8018B4E0;
extern s32 D_801A9C80;
extern const char aPqes[];
extern const char aPqes_0[];
extern const char aPqes_1[];
void SsVabClose(short vab_id);
s32 func_800E3278(void) {
    SsVabClose(0);
    while (func_800219E0(0) != 1)
        ;

    if (func_80021350(&aPbav, 0, D_800BD1C8) < 0) {
        return;
    }
    if (func_80021880(&D_8013B6A0, 0x41CB0, 0) < 0) {
        return;
    }

    while (func_800219E0(0) != 1)
        ;
    SsVabClose(1);
    while (func_800219E0(0) != 1)
        ;

    if (func_80021350(&aPbav_0, 1, D_800BD1CC) < 0) {
        return;
    }
    if (func_80021880(&D_8017D350, 0xE190, 1) < 0) {
        return;
    }

    while (func_800219E0(0) != 1)
        ;
    SsVabClose(2);
    while (func_800219E0(0) != 1)
        ;

    if (func_80021350(&aPbav_1, 2, D_800BD1D0) < 0) {
        return;
    }
    if (func_80021880(&D_801A9C80, 0xFBF0, 2) < 0) {
        return;
    }

    while (func_800219E0(0) != 1)
        ;
    SsVabClose(3);
    while (func_800219E0(0) != 1)
        ;

    if (func_80021350(&aPbav_2, 3, D_800BD1D4) < 0 ||
        func_80021880(&D_8018B4E0, 0x1A610, 3) < 0) {
        return -1;
    }
    while (func_800219E0(0) != 1)
        ;
    func_80131EBC(&aPqes, 0x618);
    func_80131EBC(&aPqes_0, 0x201);
    func_80131EBC(&aPqes_1, 0x205);
    return 0;
}
#endif

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

// Set stage display buffer
void func_800E3574(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(
        &g_GpuBuffers[1].draw, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(
        &g_GpuBuffers[0].disp, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_800E34DC(0);
}

// Set CGI display buffer?
void func_800E3618(s32 width) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, width, DISP_ALL_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, width, DISP_ALL_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, width, DISP_ALL_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, width, DISP_ALL_H);
    func_800E34DC(1);
}

// Set menu display buffer
void func_800E36C8(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_MENU_W, DISP_MENU_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 128, 256, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 128, 256, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_MENU_W, DISP_MENU_H);
    func_800E34DC(1);
}

void func_800E376C(void) {
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
    s32 i;

    SetVideoMode(0);
    InitializePads();
    InitCARD(1);
    StartCARD();
    _bu_init();
    ChangeClearPAD(0);
    func_800E8EE4();
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
    func_80131ED8(0xB9B6);
    func_801325D8();
    while (func_800E3278() < 0)
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
    D_80098850 = 0;
loop_5:
    D_8003C73C = 0;
    func_800E3574();
    func_800ECBF8();
    func_800EAD7C();
    func_800ECE2C();
    func_800EDA94();
    func_800EDAE4();
    func_801065F4(0);
    func_800EA538(0);
    func_800EAEEC();
    D_801362B4 = 0x20;
    g_DebugCurPal = 0x200;
    D_800BD1C0 = 0;
    D_801362B0 = 0;
    D_801362B8 = 0;
    D_801362BC = 0;
    D_80138FB0 = 0;
    D_801362AC = 0;
    g_DebugPalIdx = 0;
    D_801362C4 = 0;
    D_801362C8 = 0;
    D_801362D8 = 0;
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
    g_softResetTimer = 0;
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
        if (nullsub_8() != 0) {
            UpdateGame();
        }
        if (D_8003C0F8 == 0 && D_800973EC == 0) {
            RenderTilemap();
            RenderEntities();
            if (g_GameState == Game_Play && D_800BD1C0 != 0) {
                if (D_801362B0 != 0) {
                    DrawEntitiesHitbox(D_801362B0);
                }
            }
        }
        RenderPrimitives();
        UpdateCd();
        func_800E385C(g_CurrentOT);
        DrawSync(0);
        D_801362D4 = GsGetVcount();
        VSync(D_8003C73C);
        GsClearVcount();
        func_800EB314();
        ReadPads();
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
            ClearBackbuffer();
            func_801073C0();
            PlaySfx(0x12);
            PlaySfx(0xB);
            func_801361F8();
            VSync(D_8003C73C);
            func_80132760();
            SetGameState(Game_Title);
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
        func_800ECE2C();
        func_800EDA94();
        func_800EDAE4();
        ResetEntityArray();
        func_801065F4(0);
        func_800EA538(0);
        func_800EAEEC();
        func_800E3574();
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
            func_800E3574();
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
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (func_800E81FC(2, SimFileType_System) < 0) {
                break;
            }
            if (func_800E81FC(0, SimFileType_System) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 2:
        g_GameStep = 3;
        break;
    case 3:
        g_GameStep = 4;
        break;
    case 4:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep = 5;
        break;
    case 5:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (func_800E81FC(0, SimFileType_StagePrg) < 0) {
                break;
            }
        }
        D_8003C9A4 = 0;
        g_GameStep++;
        break;
    case 6:
        if (g_GameState == Game_Title) {
            callback = g_api.o.TestCollisions;
        } else {
            callback = g_api.o.InitRoomEntities;
        }
        callback();
        break;
    }
}
