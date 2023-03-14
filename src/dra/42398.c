/*
 * File: 42398.c
 * Overlay: DRA
 * Description: Game engine.
 */

#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

#define COLORS_PER_PAL 16

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
void func_800E7AEC(void);
void func_800E7BB8(void);
s32 func_800E81FC(s32, s32);
void func_800E8EE4(void);
void func_800EA7CC(void);
void func_800EB314(void);
void func_800EBBAC(void);
void func_800ECBF8(void);
void func_800ECE58(void);
void func_800EDEDC(void);
void func_800FADC0(void);
void func_801026BC(s32);
void func_80106670(s32 blendMode);
void func_80108448(void);
s32 func_8010E27C(void);
void AccelerateX(s32);
void func_801324B4(s8 s_num, s16 arg1, s16 arg2);
void func_801325D8(void);
void func_801353A0(void);
s32 func_80136010(void);

extern const char* aO;

void func_800E2398(const char* str) {
    D_8006C37C = (GpuBuffer*)D_8006C37C->unk0;
    FntPrint(str);
    if (D_80136300++ & 4) {
        FntPrint(&aO); // TODO: rodata split
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&D_8006C37C->buf.draw);
    PutDispEnv(&D_8006C37C->buf.disp);
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

INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E2B00);

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
// https://decomp.me/scratch/y3otf
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
extern const char* aPbav;
extern const char* aPbav_0;
extern const char* aPbav_1;
extern const char* aPbav_2;
extern const char* aPqes;
extern const char* aPqes_0;
extern const char* aPqes_1;
void SsVabClose(short vab_id);
s32 func_800E3278(void) {
    SsVabClose(0);
    while (func_800219E0(0) != 1)
        ;

    if ((func_80021350(&aPbav, 0, D_800BD1C8) >= 0) &&
        (func_80021880(&D_8013B6A0, 0x41CB0, 0) >= 0)) {
        while (func_800219E0(0) != 1)
            ;
        SsVabClose(1);
        while (func_800219E0(0) != 1)
            ;
        if ((func_80021350(&aPbav_0, 1, D_800BD1CC) >= 0) &&
            (func_80021880(&D_8017D350, 0xE190, 1) >= 0)) {
            while (func_800219E0(0) != 1)
                ;
            SsVabClose(2);
            while (func_800219E0(0) != 1)
                ;
            if ((func_80021350(&aPbav_1, 2, D_800BD1D0) >= 0) &&
                (func_80021880(&D_801A9C80, 0xFBF0, 2) >= 0)) {
                while (func_800219E0(0) != 1)
                    ;
                SsVabClose(3);
                while (func_800219E0(0) != 1)
                    ;
                if ((func_80021350(&aPbav_2, 3, D_800BD1D4) < 0) ||
                    (func_80021880(&D_8018B4E0, 0x1A610, 3) < 0)) {
                    return -1;
                }
                while (func_800219E0(0) != 1)
                    ;
                func_80131EBC(&aPqes, 0x618);
                func_80131EBC(&aPqes_0, 0x201);
                func_80131EBC(&aPqes_1, 0x205);
                return 0;
            }
        }
    }
}
#endif

void func_800E346C(void) {
    D_8003CB08.buf.draw.r0 = 0;
    D_8003CB08.buf.draw.g0 = 0;
    D_8003CB08.buf.draw.b0 = 0;
    D_800542FC.buf.draw.r0 = 0;
    D_800542FC.buf.draw.g0 = 0;
    D_800542FC.buf.draw.b0 = 0;
}

void func_800E34A4(s8 arg0) {
    D_8003CB08.buf.draw.r0 = arg0;
    D_8003CB08.buf.draw.g0 = arg0;
    D_8003CB08.buf.draw.b0 = arg0;
    D_800542FC.buf.draw.r0 = arg0;
    D_800542FC.buf.draw.g0 = arg0;
    D_800542FC.buf.draw.b0 = arg0;
}

void func_800E34DC(s32 arg0) {
    D_8003CB08.buf.draw.clip.y = 0x0014;
    D_8003CB08.buf.draw.clip.h = 0x00CF;
    D_80054302 = arg0 == 0 ? 0x0014 : 0x0114;
    D_800542FC.buf.draw.clip.h = 0x00CF;
    D_800542FC.buf.draw.isbg = 1;
    D_8003CB08.buf.draw.isbg = 1;
    func_800E346C();
    D_800542FC.buf.draw.dtd = 0;
    D_8003CB08.buf.draw.dtd = 0;
    D_800542FC.buf.disp.isrgb24 = 0;
    D_8003CB08.buf.disp.isrgb24 = 0;
}

// Set stage display buffer
void func_800E3574(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, DISP_STAGE_W, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, DISP_STAGE_W, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_800E34DC(0);
}

// Set CGI display buffer?
void func_800E3618(s32 width) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, width, DISP_ALL_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, 0, 256, width, DISP_ALL_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, 0, 256, width, DISP_ALL_H);
    SetDefDispEnv(&D_8005435C, 0, 0, width, DISP_ALL_H);
    func_800E34DC(1);
}

// Set menu display buffer
void func_800E36C8(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, DISP_MENU_W, DISP_MENU_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, 128, 256, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, 128, 256, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_MENU_W, DISP_MENU_H);
    func_800E34DC(1);
}

void func_800E376C(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, 0, 256, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, 0, 256, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_UNK2_W, DISP_UNK2_H);
    D_800542FC.buf.draw.clip.y = DISP_UNK2_W / 2;
    D_800542FC.buf.draw.clip.h = DISP_UNK2_H;
    D_8003CB08.buf.draw.clip.h = DISP_UNK2_H;
    D_8003CB08.buf.draw.clip.y = 0;
    D_800542FC.buf.draw.isbg = 1;
    D_8003CB08.buf.draw.isbg = 1;
    func_800E346C();
    D_800542FC.buf.disp.isrgb24 = 0;
    D_8003CB08.buf.disp.isrgb24 = 0;
}

// https://decomp.me/scratch/Ocshz
// mips to c doesn't support this function very well
INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E385C);

void func_800E38CC(void) {
    if (D_800A015C != 0) {
        if (D_800A0158 >= 0x24) {
            D_801390D4->buf.disp.screen.x = 0;
            PutDispEnv(&D_801390D4->buf.disp);
        } else {
            D_801390D4->buf.disp.screen.x = D_80136308[D_800A0158 + D_800A04F8];
            PutDispEnv(&D_801390D4->buf.disp);
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
    D_8003CB08.unk0 = &D_800542FC;
    D_800542FC.unk0 = &D_8003CB08;
    ClearImage(&D_800ACD88[0], 0x5A, 0x50, 0x46);
    ClearImage(&D_800ACD88[1], 0, 0, 0);
    for (i = 0; i < 0x50; i++) {
        ((void**)&g_api)[i] = (&D_800A0004)[i];
    }
    g_blinkTimer = 0;
    D_8003C99C = 0;
    D_800987B4 = 0;
    D_8003CB00[0] = 0;
    D_8003CB04 = 0;
    D_8006C37C = &D_8003CB08;
    func_80131ED8(0xB9B6);
    func_801325D8();
    while (func_800E3278() < 0)
        ;
    VSyncCallback(func_800E7BB8);
    FntLoad(0x380, 0x100);
    SetDumpFnt(FntOpen(8, 0x30, 0x200, 0x100, 0, 0x200));
    SetDispMask(1);
    func_800E4124(0);

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
    D_80097914 = 0;
    D_8003C704 = 0;
    D_800973EC = 0;
    D_800974A4 = 0;
    D_8006C398 = 0;
    D_80097928 = 0;
    D_80097910 = 0;
    D_80097904 = 0;
    D_8006C3AC = 0;
    D_80097C98 = 0;
    g_softResetTimer = 0;
    D_800978C4 = 1;

    while (true) {
        GpuBuffer* temp_v1_2;

        D_801390D4 = D_8006C37C;
        temp_v1_2 = D_8006C37C->unk0;
        g_blinkTimer++;
        D_8006C37C = temp_v1_2;
        D_801362CC = temp_v1_2->_unk_0474;
        ClearOTag(temp_v1_2->_unk_0474, 0x200);
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
            func_800E7AEC();
        }
        if (D_8003C0F8 == 0 && D_800973EC == 0) {
            func_800ECE58();
            func_800EBBAC();
            if (D_8003C734 == 2 && D_800BD1C0 != 0) {
                if (D_801362B0 != 0) {
                    func_80106670(D_801362B0);
                }
            }
        }
        func_800EDEDC();
        func_80108448();
        func_800E385C(D_801362CC);
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
            func_800E4124(1);
            goto loop_5;
        }
        PutDrawEnv(&D_8006C37C->buf.draw);
        PutDispEnv(&D_8006C37C->buf.disp);
        DrawOTag(D_801362CC);
        func_800EA7CC();
        func_801361F8();
        if (func_80131F28() >= 0x385) {
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
            g_GameTimer.frames += D_801362D4;
            if (g_GameTimer.frames >= 60) {
                g_GameTimer.frames -= 60;
                g_GameTimer.seconds++;
                if (g_GameTimer.seconds >= 60) {
                    g_GameTimer.seconds -= 60;
                    g_GameTimer.minutes++;
                    if (g_GameTimer.minutes >= 60) {
                        g_GameTimer.minutes -= 60;
                        g_GameTimer.hours++;
                        if (g_GameTimer.hours >= 100) {
                            g_GameTimer.seconds = 59;
                            g_GameTimer.minutes = 59;
                            g_GameTimer.hours = 99;
                        }
                    }
                }
            }
        }
        rand();
    }
}

void func_800E4124(s32 context) {
    D_8003C734 = context;
    D_80073060 = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E414C);

void ClearBackbuffer(void) { ClearImage(&c_backbufferClear, 0, 0, 0); }

// TODO aspatch jump points to the wrong instruction,
// otherwise this is fully decompiled
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E451C);
#else

void func_800E451C(void) {
    switch (D_80073060) {
    case 0x0:
        ClearBackbuffer();
        func_800ECBF8();
        func_800EAD7C();
        func_800ECE2C();
        func_800EDA94();
        func_800EDAE4();
        func_800EBB70();
        func_801065F4(0);
        func_800EA538(0);
        func_800EAEEC();
        func_800E3574();
        g_StageId = 0x45;
        if (D_800978AC != 0) {
            if (D_8006C3B0 == 0) {
                D_8006C398 = 1;
                D_8006BAFC = 1;
                goto block_15;
            }
            return;
        }
    block_15:
        D_80073060++;
        break;
    case 0x64:
        if (D_8006C3B0 == 0) {
            RECT sp18;
            sp18.x = 0;
            sp18.y = 0;
            sp18.w = 0x280;
            sp18.h = 0x100;
            LoadImage(&sp18, (u32*)0x80180014);

            sp18.x = 0;
            sp18.y = 0x100;
            LoadImage(&sp18, (u32*)0x80180014);

            SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, 0x280, 0x100);
            SetDefDrawEnv(&D_800542FC.buf.draw, 0, 0x100, 0x280, 0x100);
            SetDefDispEnv(&D_8003CB08.buf.disp, 0, 0x100, 0x280, 0x100);
            SetDefDispEnv(&D_8005435C, 0, 0, 0x280, 0x100);
            SetDispMask(0);
            D_8013640C = 0x6E;
            D_80073060++;
        }
        break;
    case 0x65:
        SetDispMask(1);
        if (D_8013640C == 0 || --D_8013640C == 0) {
            ClearImage(&D_800ACDF0, 0, 0, 0);
            func_800E3574();
            g_StageId = 0x45;
            if (D_800978AC != 0) {
                if (D_8006C3B0 != 0) {
                    break;
                }
                D_8006C398 = 1;
                D_8006BAFC = 1;
            }
            D_80073060 = 1;
        }
        break;
    case 0x1:
        if ((D_800978AC != 0 && D_8006C3B0 == 0) ||
            (D_800978AC == 0 && func_800E81FC(2, 0) >= 0 &&
             func_800E81FC(0, 0) >= 0)) {
            D_80073060++;
        }
        break;
    case 0x2:
        D_80073060 = 3;
        break;
    case 0x3:
        D_80073060 = 4;
        break;
    case 0x4:
        if (D_800978AC != 0) {
            D_8006C398 = 1;
            D_8006BAFC = 0x100;
        }
        D_80073060 = 5;
        break;
    case 0x5:
        if ((D_800978AC != 0 && D_8006C3B0 == 0) ||
            (D_800978AC == 0 && func_800E81FC(0, 1) >= 0)) {
            D_8003C9A4 = 0;
            D_80073060++;
        }
        break;
    case 0x6:
        if (D_8003C734 == 1) {
            g_api.o.TestCollisions();
        } else {
            g_pfnInitRoomEntities();
        }
        break;
    }
}
#endif

void func_800E493C(void) {
    if (g_SettingsSoundMode == 0) { // Stereo / Mono ?
        PlaySfx(6);
    } else {
        PlaySfx(5);
    }
}

void func_800E4970(void) {
    func_800E4124(4);
    D_80073060 = 2;
    ClearBackbuffer();
    func_800E3574();
    func_800EAD7C();
    func_801065F4(0);
    func_800EDA94();
    func_800EA538(0);
    func_800ECE2C();
    func_800EAEEC();
    func_800EDAE4();
    PlaySfx(0x12);
    PlaySfx(0xB);
    func_80132760();
    func_800E493C();
}

void func_800E4A04(void) { s32 pad[3]; }

INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E4A14);

void func_800E5358(void) {
    POLY_GT4* poly = &D_80086FEC[D_8013640C];
    s32 i;

    for (i = -3; i < 256; i++, poly = (POLY_GT4*)poly->tag) {
        if ((i >= 0) && (poly->y0 <= 256)) {
            if (poly->p1 != 0) {
                poly->p1--;
            } else {
                if ((poly->p2 < 10) && (rand() & 1)) {
                    poly->p2++;
                } else {
                    if (!(rand() & 3)) {
                        poly->y0++;
                        poly->y1++;
                    }
                    poly->y0++;
                    poly->y1++;
                }
                poly->y2++;
                poly->y3++;
            }
        }
    }
}

void func_800E5498(void) {
    POLY_GT4* poly = &D_8006C37C->polyGT4[D_80097930[0]];
    GpuBuffer* buffer = D_8006C37C;

    setSemiTrans(poly, true);
    setShadeTex(poly, false);
    SetPolyRect(poly, 0, 0, 256, 256);
    setUV4(poly, 16, 16, 24, 16, 16, 24, 24, 24);
    func_801072BC(poly);
    poly->tpage = 0x5A;
    poly->clut = D_8003C3C2[0];
    AddPrim(&buffer->_unk_0474[0x1FF], poly);
    D_80097930[0]++;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E5584);

INCLUDE_ASM("asm/us/dra/nonmatchings/42398", func_800E5D30);

void func_800E6218(void) {
    if (D_8006CBC4 != 0) {
        D_80170000();
    }
}

void func_800E6250(void) {
    if (D_8006CBC4 != 0) {
        while (func_800E81FC(D_8006CBC4 - 1, 0xB) != 0)
            ;
        while (func_800E81FC(D_8006CBC4 - 1, 0xC) != 0)
            ;
        while (func_800E81FC(((D_8006CBC4 + 2) * 2) + 0x8000, 2) != 0)
            ;
        while (func_800E81FC(((D_8006CBC4 + 2) * 2) + 0x8001, 3) != 0)
            ;
    }
}

extern unkStruct_800A872C D_800A872C[];

s32 func_800E6300(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if ((D_800A872C[i].unk0 > 0) && (D_80097964[i] & 2)) {
            return D_800A872C[i].unk0;
        }
    }
    return 0;
}
