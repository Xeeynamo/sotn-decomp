/*
 * File: 42398.c
 * Overlay: RIC
 * Description: Overlay for the character Richter.
 */

#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

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
void func_8010E390(s32);
void func_801324B4(s8 s_num, s16 arg1, s16 arg2);
void func_801325D8(void);
void func_801353A0(void);
s32 func_80136010(void);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2398);
#else
u_long* FntFlush(int id);
int FntPrint();
extern s32 D_80136300;
extern const char* aO;

void func_800E2398(const char* str) {
    D_8006C37C = D_8006C37C->unk0;
    FntPrint(str);
    if (D_80136300++ & 4) {
        FntPrint(&aO); // "\no\n"
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&D_8006C37C->buf.draw);
    PutDispEnv(&D_8006C37C->buf.disp);
    FntFlush(-1);
}
#endif

void func_800E2438(const char* str) {
    while (PadRead(0))
        func_800E2398(str);
    while (!PadRead(0))
        func_800E2398(str);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E249C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2824);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2B00);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2E98);

s32 nullsub_8(void) {}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2F3C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E31C0);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E3278);
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
s32 func_800E3278() {
    SsVabClose(0);
    while (func_800219E0(0) != 1)
        ;
    if ((func_80021350(&aPbav, 0, D_800BD1C8) < 0) &&
        (func_80021880(&D_8013B6A0, 0x41CB0, 0) < 0))
        return -1;
    while (func_800219E0(0) != 1)
        ;
    SsVabClose(1);
    while (func_800219E0(0) != 1)
        ;
    if ((func_80021350(&aPbav_0, 1, D_800BD1CC) < 0) &&
        (func_80021880(&D_8017D350, 0xE190, 1) < 0))
        return -1;
    while (func_800219E0(0) != 1)
        ;
    SsVabClose(2);
    while (func_800219E0(0) != 1)
        ;
    if ((func_80021350(&aPbav_1, 2, D_800BD1D0) < 0) &&
        (func_80021880(&D_801A9C80, 0xFBF0, 2) < 0))
        return -1;
    while (func_800219E0(0) != 1)
        ;
    SsVabClose(3);
    while (func_800219E0(0) != 1)
        ;
    if ((func_80021350(&aPbav_2, 3, D_800BD1D4) < 0) ||
        (func_80021880(&D_8018B4E0, 0x1A610, 3) < 0))
        return -1;
    while (func_800219E0(0) != 1)
        ;
    func_80131EBC((s32)&aPqes, 0x618);
    func_80131EBC((s32)&aPqes_0, 0x201);
    func_80131EBC((s32)&aPqes_1, 0x205);
    return 0;
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
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E385C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E38CC);

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
        (&g_pfnUpdateStageEntities)[i] = (&D_800A0004)[i];
    }
    g_blinkTimer = 0;
    D_8003C99C = 0;
    D_800987B4 = 0;
    D_8003CB00 = 0;
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
    D_801362DC.unk0 = 0U;
    D_801362E0 = 0;
    D_801362E4 = 0;
    D_801362E8 = 0;
    D_801362EC = 0;
    D_801362F0 = 0;
    D_801362F4 = 0;
    D_801362F8 = 0;
    D_801362FC = 0;
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
    D_8013900C = 0x200;
    D_800BD1C0 = 0;
    D_801362B0 = 0;
    D_801362B8 = 0;
    D_801362BC = 0;
    D_80138FB0 = 0;
    D_801362AC = 0;
    D_801362C0 = 0;
    D_801362C4 = 0;
    D_801362C8 = 0;
    D_801362D8 = 0;
    D_80097914 = 0;
    D_8003C704 = NULL;
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
        D_8009792C.unk0 = 0;
        D_8009792C.unk20 = 0U;
        D_8009792C.unk4 = 0U;
        D_8009792C.unk8 = 0U;
        D_8009792C.unkC = 0U;
        D_8009792C.unk10 = 0U;
        D_8009792C.unk14 = 0U;
        D_8009792C.unk18 = 0U;
        D_8009792C.unk1C = 0U;
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
            if (D_80097494 & PAD_START) {
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

        if (D_801362DC.unk0 < D_8009792C.unk0) {
            D_801362DC.unk0 = D_8009792C.unk0;
        }
        if (D_801362DC.unk4 < D_8009792C.unk4) {
            D_801362DC.unk4 = D_8009792C.unk4;
        }
        if (D_801362DC.unk8 < D_8009792C.unk8) {
            D_801362DC.unk8 = D_8009792C.unk8;
        }
        if (D_801362DC.unkC < D_8009792C.unkC) {
            D_801362DC.unkC = D_8009792C.unkC;
        }
        if (D_801362DC.unk10 < D_8009792C.unk10) {
            D_801362DC.unk10 = D_8009792C.unk10;
        }
        if (D_801362DC.unk14 < D_8009792C.unk14) {
            D_801362DC.unk14 = D_8009792C.unk14;
        }
        if (D_801362DC.unk18 < D_8009792C.unk18) {
            D_801362DC.unk18 = D_8009792C.unk18;
        }
        if (D_801362DC.unk1C < D_8009792C.unk1C) {
            D_801362DC.unk1C = D_8009792C.unk1C;
        }
        if (D_801362DC.unk20 < D_8009792C.unk20) {
            D_801362DC.unk20 = D_8009792C.unk20;
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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E414C);

void ClearBackbuffer(void) { ClearImage(&c_backbufferClear, 0, 0, 0); }

// TODO aspatch jump points to the wrong instruction,
// otherwise this is fully decompiled
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E451C);
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
        g_mapProgramId = 0x45;
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
            g_mapProgramId = 0x45;
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
            g_pfnTestStageEntities();
        } else {
            g_pfnLoadObjLayout();
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

void func_800E4A04(void) { s32 a[3]; }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E4A14);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E5358);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E5498);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E5584);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E5D30);

void func_800E6218(void) {
    if (D_8006CBC4 != 0) {
        D_80170000();
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E6250);

extern unkStruct_800A872C D_800A872C[];

s32 func_800E6300(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if ((D_800A872C[i].unk0 > 0) && ((D_80097964[i] & 2) != 0)) {
            return D_800A872C[i].unk0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E6358);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E6FD4);

void nullsub_9(void) {}

void func_800E738C(void) {
    if (D_80073060 == 1) {
        if ((D_800978AC != 0 && D_8006C3B0 == 0) ||
            (D_800978AC == 0 && func_800E81FC(6, 0) >= 0 &&
             func_800E81FC(7, 0) >= 0)) {
            if (func_80131F68() != 0) {
                PlaySfx(0x80);
            }
            func_800E346C();
            D_80073060++;
            return;
        }
    }
    D_8003C7B0();
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7458);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E768C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7AEC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7BB8);

void func_800E7D08(void) {
    s32 i;

    for (i = 0; i < 1024; i++) {
        D_80136460[i] = 0;
        D_80136C60[i] = 0;
    }

    D_800A04EC = 1;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7D4C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7E08);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E81FC);

void func_800E8D24(void) {
    s8* ptr;
    s32 i;

    D_80097496 = 0;
    ptr = &D_80137460;

    for (i = 0; i < 16; i++) {
        *ptr = 0x10;
        ptr++;
    }
}

// https://decomp.me/scratch/YhofM
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E8D54);
void func_800E8D54(void);

void InitializePads(void) {
    Pad* pad;
    s32 i;

    PadInit(0);
    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->tapped = 0;
        pad->previous = 0;
        pad->pressed = 0;
    }
    func_800E8D24();
}

void ReadPads(void) {
    Pad* pad;
    s32 i;
    u_long padd;

    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->previous = pad->pressed;
        padd = PadRead(i >> 1);
        if (!(i & 1))
            pad->pressed = padd;
        else
            pad->pressed = padd >> 0x10;
        pad->tapped = (pad->pressed ^ pad->previous) & pad->pressed;
    }
    func_800E8D54();
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E8EE4);

s32 func_800E908C(void) {
    if (TestEvent(D_80073068) == 1) {
        return 1;
    } else if (TestEvent(D_8007306C) == 1) {
        return 2;
    } else if (TestEvent(D_80073070) == 1) {
        return 3;
    } else if (TestEvent(D_80073078) == 1) {
        return 4;
    } else if (D_80137470-- < 0) {
        return 2;
    }
    return 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E912C);

void func_800E91B0(void) {
    TestEvent(D_80073068);
    TestEvent(D_8007306C);
    TestEvent(D_80073070);
    TestEvent(D_80073078);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9208);

void func_800E928C(void) {
    TestEvent(D_8007EFD8);
    TestEvent(D_8007EFDC);
    TestEvent(D_8007EFE0);
    TestEvent(D_80086FE4);
}

void func_800E92E4(void) { D_8013B660 = 0; }

void func_800E92F4(void) {
    D_8013B158 = 0;
    D_8013B3D0 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E930C);

extern Unkstruct_8013B15C D_8013B15C[];

s32 func_800E9508(s32 arg0) {
    s32 temp = D_8013B15C[arg0].unk000;

    return temp;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9530);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9610);

s32 func_800E9640(s32 arg0, s32 arg1, s32 arg2, s32* readBufferAddress,
                  s32 fd) {
    char file[32];
    s32 nBytes;
    s32 ret;

    sprintf(file, g_strMemcardSavePath, arg0, arg1, arg2);
    nBytes = fd << 0xD;

    if (fd == 0) {
        nBytes = 0x2B8;
    }

    fd = open(file, 0x8001);
    ret = -1;

    if (fd != (-1)) {
        D_80137474 = fd;
        func_800E91B0();
        read(fd, readBufferAddress, nBytes);
        ret = 0;
    }
    return ret;
}

// https://decomp.me/scratch/6dWJG very close (branching)
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E96E8);

s32 func_800E97BC(s32 arg0, s32 arg1, s32 arg2) {
    char buffer[0x20];

    sprintf(buffer, g_strMemcardSavePath, arg0, arg1, arg2);
    return -(erase(buffer) == 0);
}

s32 func_800E9804(s32 arg0) {
    s32 funcRet = func_800E912C();
    s32 ret = 0;

    if (funcRet != 0) {
        close(D_80137474);
        if (funcRet == 1) {
            D_8006C3AC |= funcRet << arg0;
            return 1;
        }
        ret = -3;
        return ret;
    }
    return ret;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9880);

s32 func_800E9B18(s32 arg0, s32 arg1) {
    char buffer[0x8];
    s32 ret;

    D_8006C3AC &= D_800A0510[arg0];
    sprintf(buffer, g_strMemcardRootPath, arg0, arg1);
    func_800E928C();
    format(buffer);
    ret = func_800E9208();

    if (ret != 1) {
        if (ret == 3) {
            ret = -1;
        } else {
            ret = -3;
        }
    }
    return ret;
}

// https://decomp.me/scratch/kHOQh match with struct

void func_800E9BA4(u16* arg0, s32 arg1) {
    s32 i;
    u16* var_v1 = D_800A0518[0];

    var_v1 = D_800A0518[arg1];

    for (i = 0; i < 16; i++) {
        *arg0 = *var_v1;
        var_v1++;
        arg0++;
    }
}

void func_800E9BDC(u8* arg0, s32 arg1) {
    s32 i;
    u8* var_a1;

    var_a1 = (u8*)D_800A1F18[arg1];

    for (i = 0; i < 384; i++) {
        *arg0 = *var_a1;
        var_a1++;
        arg0++;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9C14);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA2B0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA48C);

extern Unkstruct_8006C3CC D_8006C3CC[];

void func_800EA538(s32 arg0) {
    Unkstruct_8006C3CC* var_v0;
    s32 temp;
    s32 v1;
    s32 i;

    // !FAKE: 0x8000 inside a temp is weird
    temp = 0x8000;
    v1 = (temp >> (arg0 - 1));

    if (arg0 != 0) {
        for (i = 0; i < 32; i++) {
            if (v1 & D_8006C3CC[i].unk0) {
                D_8006C3CC[i].unk0 = 0;
            }
        }
        return;
    }

    D_8003C0F8 = 0;
    var_v0 = (Unkstruct_8006C3CC*)&D_8006C3C4;

    for (i = 0; i < 32; i++) {
        var_v0->unk8 = 0;
        var_v0++;
    }
}

void func_800EA5AC(u16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_8003C0EC[3] = arg0;
    D_8003C0EC[0] = arg1;
    D_8003C0EC[1] = arg2;
    D_8003C0EC[2] = arg3;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA5E4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA720);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA7CC);

s32 func_800EAD0C(void) { // the return type is needed for matching
    func_800EA5E4(4);
    func_800EA5E4(5);
    func_800EA5E4(6);
    func_800EA5E4(7);
    func_800EA5E4(8);

    if ((g_CurrentPlayableCharacter == PLAYER_ALUCARD) &&
        (g_mapProgramId != PROGRAM_ST0)) {
        func_800EA5E4(0x17);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EAD7C);

void func_800EAEA4(void) {
    u16* var_v1 = &D_801374F8;
    s32 i;

    for (i = 0; i < 32; i++) {
        *var_v1 = 0xFFFF;
        var_v1++;
    }

    var_v1 = &D_80137538;

    for (i = 0; i < 32; i++) {
        *var_v1 = 0xFFFF;
        var_v1++;
    }
}

void func_800EAEEC(void) {
    unkstruct_80072FA0* var_v1 = &D_80072FA0[0];
    s32 i;

    for (i = 0; i < 16; i++, var_v1++) {
        var_v1->unk4 = 0;
    }

    func_800EAEA4();
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EAF28);

void func_800EAFC8(s32 arg0) {
    u8 temp = arg0;

    if (D_80137584 == 0) {
        D_80137584 = 1;
        *D_8013757C = temp;
    } else {
        D_80137584 = 0;
        *D_8013757C += arg0 * 16;
        D_8013757C++;
    }
}

u32 func_800EB03C(void) {
    u8 temp_v1;

    if (D_80137580 != 0) {
        D_80137580 = 0;
        temp_v1 = *D_80137578;
        D_80137578++;
        return (temp_v1 >> 0) & 0xF;
    } else {
        D_80137580 = 1;
        temp_v1 = *D_80137578;
        return (temp_v1 >> 4) & 0xF;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB098);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB314);

void func_800EB4F8(PixPattern* pix, s32 bitDepth, s32 x, s32 y) {
    LoadTPage(pix + 1, bitDepth, 0, x, y, (int)pix->w, (int)pix->h);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB534);

void func_800EB6B4(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        func_800EB534(D_80137478[i], D_801374B8[i], i);
    }
}

// https://decomp.me/scratch/n0Z3p match with -fforce-addr

bool func_800EB720(void) {
    unkstruct_80072FA0* temp = D_80072FA0;
    s32 i;

    for (i = 0; i < 0x10; i++) {
        if (temp[i].unk4 != 0) {
            return true;
        }
    }

    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB758);

// clears out each entity struct 1 byte at a time
void func_800EBB70(void) {
    s8* byte;
    Entity* entity = &g_EntityArray[0];
    s32 i;
    u32 j;

    for (i = 0; i < ARRAY_COUNT(g_EntityArray); i++) {
        byte = (s8*)entity;
        for (j = 0; j < 188; j++) {
            byte[0] = 0;
            byte++;
        }
        entity++;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EBBAC);

// The loop at the end is weird, the rest is matching
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800ECBF8);
#else
typedef struct {
    s16 unk00, unk02;
    u16 unk04, unk06;
    u16 unk08, unk0A;
    u16 unk0c, unk0E;
    u16 unk10, unk12;
    u16 unk14, unk16;
    u16 unk18, unk1A;
    u16 unk1c;
    u8 unk1E, unk1F;
    u16 unk20;
    u8 unk22, unk23;
    u16 unk24, unk26;
} Unkstruct_800ECBF8_1; /* size = 0x28 */

typedef struct {
    s16 unk0, unk4;
} Unkstruct_800ECBF8_2; /* size = 0x4 */

extern POLY_GT4 D_8004077C[0x300]; // TODO D_8003CB08.polyGT4
extern POLY_G4 D_8004A37C[0x100];  // TODO D_8003CB08.polyG4
extern POLY_GT3 D_8004C77C[0x30];  // TODO D_8003CB08.polyGT3
extern LINE_G2 D_8004CEFC[0x100];  // TODO D_8003CB08.lineG2
extern SPRT_16 D_8004E2FC[0x280];  // TODO D_8003CB08.sprite16
extern TILE D_80050AFC[0x100];     // TODO D_8003CB08.tiles
extern SPRT D_80051AFC[0x200];     // TODO D_8003CB08.sprite
extern POLY_GT4 D_80057F70[0x300]; // TODO D_800542FC.polyGT4
extern POLY_G4 D_80061B70[0x100];  // TODO D_80542FC8.polyG4
extern POLY_GT3 D_80063F70[0x30];  // TODO D_800542FC.polyGT3
extern LINE_G2 D_800646F0[0x100];  // TODO D_80542FC8.lineG2
extern SPRT_16 D_80065AF0[0x280];  // TODO D_8003542FCsprite16
extern TILE D_800682F0[0x100];     // TODO D_8542FC08.tiles
extern SPRT D_800692F0[0x200];     // TODO D_80542FC8.sprite
extern Unkstruct_800ECBF8_1 D_80097D1C[0x10];
extern Unkstruct_800ECBF8_2 D_800A21B8[0x10];

void func_800ECBF8(void) {
    int i;
    POLY_GT4 *a1, *a2;
    SPRT_16 *b1, *b2;
    TILE *c1, *c2;
    LINE_G2 *d1, *d2;
    POLY_G4 *e1, *e2;
    SPRT *f1, *f2;
    POLY_GT3 *g1, *g2;

    Unkstruct_800ECBF8_1* var_v1;
    Unkstruct_800ECBF8_2 *var_a2, *var_a0;

    for (a1 = D_8004077C, a2 = D_80057F70, i = 0; i < 0x300; i++, a1++, a2++) {
        SetPolyGT4(a1);
        SetPolyGT4(a2);
    }

    for (b1 = D_8004E2FC, b2 = D_80065AF0, i = 0; i < 0x280; i++, b1++, b2++) {
        SetSprt16(b1);
        SetSprt16(b2);
    }

    for (c1 = D_80050AFC, c2 = D_800682F0, i = 0; i < 0x100; i++, c1++, c2++) {
        SetTile(c1);
        SetTile(c2);
    }

    for (d1 = D_8004CEFC, d2 = D_800646F0, i = 0; i < 0x100; i++, d1++, d2++) {
        SetLineG2(d1);
        SetLineG2(d2);
    }

    for (e1 = D_8004A37C, e2 = D_80061B70, i = 0; i < 0x100; i++, e1++, e2++) {
        SetPolyG4(e1);
        SetPolyG4(e2);
    }

    for (f1 = D_80051AFC, f2 = D_800692F0, i = 0; i < 0x200; i++, f1++, f2++) {
        SetSprt(f1);
        SetSprt(f2);
    }

    for (g1 = D_8004C77C, g2 = D_80063F70, i = 0; i < 0x30; i++, g1++, g2++) {
        SetPolyGT3(g1);
        SetPolyGT3(g2);
    }

    var_v1 = &D_80097D1C;
    i = 0;
    var_a0 = &D_800A21B8;
    var_a2 = &D_800A21B8;
    do {
        var_v1->unk00 = var_a2->unk0;
        var_v1->unk02 = var_a0->unk4 & 0x1FF;
        var_v1->unk23 = (var_a0->unk4 >> 8) & ~1;
        var_v1->unk1F = (var_v1->unk00 >> 6) + 0x10;
        var_a2++;
        i++;
        var_a0++;
        var_v1++;
    } while (i < 0x10);
}
#endif

extern Unkstruct_800ECE2C D_800730A0;

void func_800ECE2C(void) {
    s32 i;

    D_800730A0.unk00 = 0;
    for (i = 0; i < 16; i++) {
        D_800730A0.unk54[i].unk00[0] = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800ECE58);

INCLUDE_ASM("asm/dra/nonmatchings/42398", SetRoomForegroundLayer);

INCLUDE_ASM("asm/dra/nonmatchings/42398", SetRoomBackgroundLayer);

extern Unkstruct_8003C794* D_8003C794;

void LoadRoomLayer(s32 arg0) {
    s32 i;

    SetRoomForegroundLayer(D_8003C794[arg0].unk00);
    SetRoomBackgroundLayer(0, D_8003C794[arg0].unk04);

    for (i = 1; i < 16; i++) {
        D_800730A0.unk54[i].unk00[0] = 0;
    }
}

void func_800EDA70(s32* context) {
    s32 i;
    s32 n;

    for (n = 13, i = 0; i < n; i++) {
        *context++ = 0;
    }
}

void func_800EDA94(void) {
    POLY_GT4* poly;
    s32 i;

    for (i = 0, poly = D_80086FEC; i < 1280; i++) {
        func_800EDA70((s32*)poly);
        poly->code = 0;
        poly++;
    }
}

void func_800EDAE4(void) {
    s32 i;
    s32* phi_v1 = &D_800974AC;

    for (i = 0; i < 16; i++) {
        *phi_v1 = 0;
        phi_v1 += 0x10;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EDB08);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EDB58);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EDC80);
#else
s16 func_800EDC80(u8 arg0, s32 arg1) {
    s32 phi_s2 = 0;
    POLY_GT4* phi_s1 = D_80086FEC;
    u8* phi_s0 = &D_80086FEC->code;
    s16 index;
    s32 phi_v0;

loop_1:
    if (*phi_s0 == 0) {
        func_800EDA70(phi_s1);
        if (arg1 == 1) {
            *phi_s0 = arg0;
            phi_s1->tag = NULL;
            if (D_800A2438 < phi_s2) {
                D_800A2438 = phi_s2;
                phi_v0 = phi_s2 << 0x10;
            } else {
                goto block_8;
            }
            goto block_9;
        }
        *phi_s0 = arg0;
        index = func_800EDC80(arg0 & 0xFF, arg1 - 1);
        if (index == -1) {
            *phi_s0 = 0;
            return -1;
        }
        phi_s1->tag = (s32)&D_80086FEC[index];
    block_8:
        phi_v0 = phi_s2 << 0x10;
    block_9:
        return (s16)(phi_v0 >> 0x10);
    }

    phi_s2 = phi_s2 + 1;
    phi_s0 += sizeof(POLY_GT4);
    phi_s1++;
    if (phi_s2 >= 0x400) {
        return -1;
    }
    goto loop_1;
}
#endif

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EDD9C);
#else
s32 func_800EDD9C(u8 arg0, s32 arg1) {
    u8* pCode;
    u8 temp_v0;
    u8* phi_s0;
    POLY_GT4* phi_s1;
    s16 phi_s2;
    s16 polyIndex;

    phi_s1 = D_800973B8;
    phi_s2 = 0x4FF;
    phi_s0 = &D_800973B8->code;
loop_1:
    pCode = &phi_s1->code;
    temp_v0 = *phi_s0;
    if (temp_v0 == 0) {
        func_800EDA70(phi_s1);
        if (arg1 == 1) {
            *phi_s0 = arg0;
            phi_s1->tag = 0;
        } else {
            *phi_s0 = arg0;
            polyIndex = func_800EDD9C(arg0, arg1 - 1);
            phi_s1->tag = &D_80086FEC[polyIndex];
        }
        return phi_s2;
    }

    phi_s0--;
    phi_s1--;
    phi_s2--;
    if (phi_s2 < 0) {
        return (s16)temp_v0;
    }
    goto loop_1;
}
#endif

void FreePolygons(s32 polygonIndex) {
    POLY_GT4* poly = &D_80086FEC[polygonIndex];

    if (poly) {
        do {
            if (poly->code == 7) {
                *(*(s32**)&poly->r1) = 0; // does not make any sense?!
                poly->code = 0;
            } else
                poly->code = 0;
            poly = (POLY_GT4*)poly->tag;
        } while (poly);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EDEDC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", CheckCollision);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EFBF8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F0334);

extern Unkstruct_aSimCBinDemoKey aSimCBinDemoKey;

void func_800F04A4(void) {
    Unkstruct_aSimCBinDemoKey sp10[10];
    char pad[12]; // !FAKE: Intentional padding to fix the stack pointer
    s32 temp;
    s32 device;

    sp10[0] = aSimCBinDemoKey;

    device = open((char*)&sp10, 0x200);

    if (device >= 0) {
        if (write(device, (void*)0x801E8000, 0x2000) < 0) {
            close(device);
            return;
        } else if (close(device) >= 0) {
            // !FAKE:
            sp10[0].unk0 = D_800DC4C0;
            sp10[0].unk4 = (temp = D_800DC4C4);
            do {
                func_800E2438((const char*)&sp10);
            } while (0);
        }
    }
}

void func_800F0578(s32 arg0) {
    D_80137590 = (s32*)0x801E8000;
    *((s32*)0x801E8000) = 0;

    func_800EFBF8();

    switch (arg0) {
    case 0:
    case 2:
        func_800F0334(arg0);
        D_80097914 = arg0 == 0 ? 1 : 4;
        break;

    case 1:
        D_80097914 = 2;

    default:
        break;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F0608);

typedef struct {
    s32 foo[5];
} Unkstruct_800F087C;

extern Unkstruct_800F087C D_800A297C;

s32 func_800F087C(u32 chunkX, u32 chunkY) {
    Unkstruct_800F087C* phi_s1;
    Unkstruct_800F087C* phi_s0;

    phi_s1 = &D_800A297C;
    phi_s0 = (Unkstruct_800F087C*)((u32*)&D_800A297C + 4);
loop_1:
    if (phi_s1->foo[0] == 0x80)
        return 0;

    if (phi_s1->foo[0] == chunkX && phi_s0->foo[-3] == chunkY &&
        phi_s0->foo[-2] == g_mapProgramId) {
        if (phi_s0->foo[-1] == 0xFF || func_800FD4C0(phi_s0->foo[-1], 0) == 0)
            return phi_s0->foo[0] + 2;
    }

    phi_s0++;
    phi_s1++;
    goto loop_1;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F0940);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", SetNextRoomToLoad);
#else
bool SetNextRoomToLoad(u32 chunkX, u32 chunkY) {
    RoomLoadDef* pRoomLoad;
    RoomHeader* pRoom;

    if (D_80072F2C & 0x40000)
        return false;

    if (func_800F087C(chunkX, chunkY))
        return false;

    pRoom = D_8003C784;
loop_3:
    while (pRoom->left != 0x40) {
        if (chunkX >= pRoom->left && chunkY >= pRoom->top &&
            pRoom->right >= chunkX && pRoom->bottom >= chunkY) {
            pRoomLoad = &pRoom->load;
            if (pRoom->load.tilesetId == 0xFF) {
                if (D_800A2464[pRoom->load.tileLayoutId].programId == 0x1F) {
                    return false;
                }
            }
            D_801375BC = pRoomLoad;
            return true;
        }
        pRoom++;
        goto loop_3;
    }
    return false;
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F0CD8);

void func_800F1424(void) {
    if (D_8009749C[0] & 8) {
        D_800730A0.unk00 ^= 2;
    }
    if (D_8009749C[0] & 4) {
        D_800730A0.unk00 ^= 1;
    }
    if ((D_8009749C[0] & 1) && (D_800730A0.unk3C != 0)) {
        D_800730A0.unk54[0].unk00[0] ^= 1;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F14CC);

s32 func_800F16D0(void) {
    if (D_8003C730 != 0)
        return g_mapProgramId;
    else if (D_80097C98 == 4)
        return PROGRAM_TOP | PROGRAM_INVERTEDCASTLE_FLAG;
    else if (D_80097C98 == 5)
        return PROGRAM_TOP;
    else if (D_80097C98 == 6)
        return PROGRAM_LIB;
    else {
        s32 programId = D_800A2464[D_8006C374].programId;
        if (g_mapProgramId & PROGRAM_INVERTEDCASTLE_FLAG) {
            programId ^= PROGRAM_INVERTEDCASTLE_FLAG;
        }
        return programId;
    }
}

void func_800F1770(s8 arg0[], s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0 = (arg1 / 2) + (arg2 * 4);

    if (!(arg1 & 1)) {
        arg0[temp_v0] = (arg0[temp_v0] & 0xF0) + arg3;
    } else {
        arg0[temp_v0] = (arg0[temp_v0] & 0xF) + (arg3 * 0x10);
    }
}

u8 func_800F17C8(s8 arg0[], s32 arg1, s32 arg2) {
    s32 temp_v0 = (arg1 / 2) + (arg2 * 4);

    if (!(arg1 & 1)) {
        return (u8)arg0[temp_v0] & 0xF;
    } else {
        return (u8)arg0[temp_v0] >> 4;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F180C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1868);

void func_800F18C4(s32 arg0, s32 arg1) {
    s8 sp10[20];
    s32 i;
    s32 j;

    func_800F180C(arg0, arg1, &sp10);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            func_800F1770(sp10, j, i, 0);
        }
    }
    func_800F1868(arg0, arg1, &sp10);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1954);

void func_800F1A3C(s32 arg0) {
    if (arg0 == 0) {
        func_800F18C4(0xE, 0x2B);
        func_800F18C4(0x10, 0x2B);
        func_800F18C4(0x2B, 0x2A);
        func_800F18C4(0x2C, 0x2A);
        func_800F18C4(0x2D, 0x2A);
        func_800F18C4(0x30, 0x2A);
    } else {
        func_800F1954(0xE, 0x2B, 0);
        func_800F1954(0x10, 0x2B, 1);
        func_800F1954(0x2B, 0x2A, 2);
        func_800F1954(0x2C, 0x2A, 2);
        func_800F1954(0x2D, 0x2A, 2);
        func_800F1954(0x30, 0x2A, 2);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1B08);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1D54);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1EB0);

void func_800F1FC4(s32 arg0) {
    func_800F1EB0((playerX >> 8) + g_CurrentRoomLeft,
                  (playerY >> 8) + g_CurrentRoomTop, arg0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2014);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2120);

void func_800F223C(void) {
    g_mapProgramId ^= 0x20;
    func_800F2120();
    g_mapProgramId ^= 0x20;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2288);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2404);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F24F4);
#else
void func_801042C4(s32);
void func_80105428();
extern s32 D_80137598;

void func_800F24F4(void) {
    s32 castleX;
    s32 castleY;
    s32 phi_v1;
    s32 phi_a0;

    castleX = ((s32)playerX >> 8) + g_CurrentRoomLeft;
    castleY = ((s32)playerY >> 8) + g_CurrentRoomTop;
    if (D_8003C708 & 0x20) {
        phi_v1 = g_mapProgramId;
        if (phi_v1 == (PROGRAM_NO0 | PROGRAM_INVERTEDCASTLE_FLAG)) {
            if ((castleX == phi_v1) && (castleY == 0x24)) {
                if (func_800FD4C0(22, 0) == 0) {
                    func_800FD4C0(22, 1);
                }
                phi_v1 = g_mapProgramId;
            }
        }

        if (phi_v1 == (PROGRAM_NO4 | PROGRAM_INVERTEDCASTLE_FLAG) &&
            castleX == 0x12 && castleY == 0x1E) {
        } else {
            phi_a0 = 0;
            if (g_mapProgramId == PROGRAM_NO4 && castleX == 0x2D &&
                castleY == 0x21) {
                if (g_EntityArray[PLAYER_CHARACTER].posX.value == 0x80) {
                    D_8003C730 = 1;
                    phi_a0 = 1;
                } else {
                    phi_a0 = 1;
                    if (func_800FD4C0(1, 0)) {
                        goto block_18;
                    }
                }
            }

            func_801042C4(phi_a0);
            D_80137598 = 1;
            func_80105428();
            return;
        }
    }
block_18:
    D_80137598 = 0;
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2658);

bool func_800F27F4(s32 arg0) {
    if (arg0 == 0) {
        if (D_800973FC != 0 || D_8006BB00 != 0 || (D_8003C708 & 0x60)) {
            return false;
        }
        D_801375C8 = 1;
        return true;
    }
    D_801375C8 = 8;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2860);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F298C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F483C);

bool IsAlucart(void) {
    if (func_800FD7C0(0xA8, 0) && func_800FD7C0(0xA7, 0) &&
        func_800FD7C0(0x59, 2))
        return true;
    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F4994);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F4D38);

void func_800F4F48(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        player_equip_head[i + 7] =
            func_800F4D38(player_equip_head[i], player_equip_head[1 - i]);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F4FD0);

void func_800F53A4(void) {
    func_800F4994();
    func_800F4F48();
    func_800F4FD0();
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F53D4);
void func_800F53D4(s32 tpage, s32 arg1);
#else
void func_800F53D4(s32 tpage, s32 arg1) {
    DR_MODE* drawMode = &D_8006C37C->drawModes[D_8009792C];
    if (D_80137614 != 0) {
        SetDrawMode(drawMode, 0, 0, tpage, &D_800ACD80);
        AddPrim(&D_8006C37C->unk_0474[arg1], drawMode);
        D_8009792C += 1;
    }
}
#endif

u8 func_800F548C(u8 arg0) {
    u16 temp = arg0;

    if (arg0 & 0x80) {
        arg0 &= 0x7F;
        return func_800F548C(arg0 + 3);
    }
    return temp << 4;
}

bool IsOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* context) {
    if (!(x1 > context->unk1.x)) {
        return true;
    }
    if (!(context->unk1.y < y1)) {
        return true;
    }
    if (x0 < (context->unk1.x + context->unk1.w)) {
        return (y0 < (context->unk1.y + context->unk1.h)) ^ 1;
    }
    return true;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", ScissorPolyG4);
bool ScissorPolyG4(POLY_G4* arg0, MenuContext* context);
#else
bool ScissorPolyG4(POLY_G4* poly, MenuContext* context) {
    s32 scissorX;
    s32 scissorY;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, context))
        return true;

    if (poly->x0 < context->unk1.x) {
        s32 diff = context->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
    }

    if (poly->y0 < context->unk1.y) {
        s32 diff = context->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
    }

    scissorX = context->unk1.x + context->unk1.w;
    if (scissorX < poly->x1) {
        s32 diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
    }

    scissorY = context->unk1.y + context->unk1.h;
    if (scissorY < poly->y2) {
        s32 diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
    }

    return false;
}
#endif

bool ScissorPolyGT4(POLY_GT4* poly, MenuContext* context) {
    s32 scissorX;
    s32 scissorY;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, context))
        return true;

    if (poly->x0 < context->unk1.x) {
        s32 diff = context->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
        poly->u0 += diff;
        poly->u2 += diff;
    }

    if (poly->y0 < context->unk1.y) {
        s32 diff = context->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
        poly->v0 += diff;
        poly->v1 += diff;
    }

    scissorX = context->unk1.x + context->unk1.w;
    if (scissorX < poly->x1) {
        s32 diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
        poly->u1 -= diff;
        poly->u3 -= diff;
    }

    scissorY = context->unk1.y + context->unk1.h;
    if (scissorY < poly->y2) {
        s32 diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
        poly->v2 -= diff;
        poly->v3 -= diff;
    }

    return false;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", ScissorSprite);
#else
bool ScissorSprite(SPRT* sprite, MenuContext* context) {
    s16 scissorx0;
    s16 scissory0;
    s32 scissory1;
    s32 scissorx1;
    s32 spritex1;
    s32 spritey1;

    if (IsOutsideDrawArea(sprite->x0, sprite->x0 + sprite->w, sprite->y0,
                          sprite->y0 + sprite->h, context))
        return true;

    scissorx0 = context->unk1.x;
    if (sprite->x0 < scissorx0) {
        s32 diffx = scissorx0 - sprite->x0;
        sprite->x0 += diffx;
        sprite->u0 = sprite->u0 + diffx;
        sprite->w = sprite->w - diffx;
    }

    scissory0 = context->unk1.y;
    if (sprite->y0 < context->unk1.y) {
        s32 diffy = scissory0 - sprite->y0;
        sprite->y0 = sprite->y0 + diffy;
        sprite->v0 = sprite->v0 + diffy;
        sprite->h = sprite->h - diffy;
    }

    scissorx1 = context->unk1.x + context->unk1.w;
    spritex1 = sprite->x0 + sprite->w;
    if (scissorx1 < spritex1) {
        sprite->w = sprite->w - (spritex1 - scissorx1);
    }

    scissory1 = context->unk1.y + context->unk1.h;
    spritey1 = sprite->y0 + sprite->h;
    if (scissory1 < spritey1) {
        sprite->h = sprite->h - (spritey1 - scissory1);
    }

    return false;
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F5904);

void func_800F5A90(void) {
    func_800F5904(NULL, 96, 96, 64, 64, 0, 0, 0, 0x114, 1, 0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F5AE4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", DrawMenuSprite);
void DrawMenuSprite(MenuContext* context, s32 x, s32 y, s32 width, s32 height,
                    s32 u, s32 v, s32 clut, s32 tpage, s32 arg9, s32 argA,
                    s32 argB);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", DrawMenuRect);
void DrawMenuRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b);
#else
// NOTE: used to draw the menu cursor
void DrawMenuRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b) {
    POLY_G4* prim;
    s32 temp_s2;
    s32 temp_t1;

    temp_t1 = D_8006C37C;
    prim = &D_8006C37C->unk_D874[D_80097934]; // get next available primitive?
    prim->x0 = posX;
    prim->y0 = posY;
    prim->x1 = posX + width;
    prim->y1 = posY;
    prim->x2 = posX;
    prim->x3 = posX + width;
    temp_s2 = context->unk18 + 1;
    prim->y2 = posY + height;
    prim->y3 = posY + height;
    prim->code &= 0xFC;
    if (ScissorPolyG4(prim, context) == 0) { // check prim boundaries?
        prim->r0 = r;
        prim->r1 = r;
        prim->r2 = r;
        prim->r3 = r;
        prim->g0 = g;
        prim->g1 = g;
        prim->g2 = g;
        prim->g3 = g;
        prim->b0 = b;
        prim->b1 = b;
        prim->b2 = b;
        prim->b3 = b;
        AddPrim(&D_8006C37C->unk_0474[temp_s2], (void*)prim);
        D_80097934 += 1;
        func_800F53D4(0, temp_s2);
    }
}
#endif

void func_800F5E68(MenuContext* context, s32 iOption, s32 x, s32 y, s32 w,
                   s32 h, s32 yGap, s32 bColorMode) {
    s32 r;

    if (bColorMode) {
        if (g_blinkTimer & 0x20) {
            r = (g_blinkTimer & 0x1F) + 0x60;
        } else {
            r = 0x7F - (g_blinkTimer & 0x1F);
        }
    } else {
        r = 0x80;
    }
    DrawMenuRect(context, x, y + (iOption * (h + yGap)), w, h, r, 0, 0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", DrawRelicsMenu);

void DrawMenuAlucardPortrait(MenuContext* ctx) {
    DrawMenuSprite(ctx, 0x10, 0x24, 0x40, 0x40, 0, 0x80, 0x150, 0x9C, 1, 0, 0);
    DrawMenuSprite(ctx, 0x10, 0x64, 0x40, 0x20, 0, 0xC0, 0x150, 0x9C, 0, 0, 1);
}

s32 func_800F62E8(s32 context) {
    s32 temp_v0 = context * 3;
    s32 phi_v0 = temp_v0 < 0 ? temp_v0 + 3 : temp_v0;
    return phi_v0 >> 2;
}

// Apply cloak palette
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F6304);

void DrawMenuAlucardCloakPreview(MenuContext* ctx) {
    DrawMenuSprite(ctx, 0xC0, 0x80, 0x20, 0x40, 0, 0xB0, 0x100, 7, 1, 0, 2);
    DrawMenuSprite(ctx, 0x100, 0x80, 0x40, 0x40, 0x80, 0xB0, 0x100, 7, 1, 0, 0);
}

void func_800F6508(MenuContext* context, s32 x, s32 y) {
    s32 yellow;

    if (g_blinkTimer & 0x10) {
        yellow = ((g_blinkTimer & 0xF) * 2) + 0x60;
    } else {
        yellow = 0x7F - (g_blinkTimer & 0xF);
    }
    DrawMenuRect(context, x, y, 0x70, 0xB, yellow, yellow, 0);
}

// Draw main menu cursor
void func_800F6568(MenuContext* arg0) {
    s32 height;
    s32 r;

    height = arg0->unk6 / 5;
    if (g_blinkTimer & 0x20) {
        r = (g_blinkTimer & 0x1F) + 0x40;
    } else {
        r = 0x5F - (g_blinkTimer & 0x1F);
    }
    DrawMenuRect(arg0, arg0->cursorX,
                 arg0->cursorY + (height * g_menuMainCursorIndex), arg0->unk4,
                 height, r, 0, 0);
}

// Draw equip menu cursor
void func_800F6618(s32 menuContextIndex, s32 bColorMode) {
    s32 r;
    MenuContext* context = (MenuContext*)&D_8013761C[menuContextIndex * 0x1E];

    if (bColorMode != 0) {
        r = 0x80;
    } else {
        if (g_blinkTimer & 0x20) {
            r = (g_blinkTimer & 0x1F) + 0x40;
        } else {
            r = 0x5F - (g_blinkTimer & 0x1F);
        }
    }
    DrawMenuRect(context, 0x70, (*g_menuRelicsCursorIndex * 0xD) + 0x1C, 0x71,
                 0xB, r, 0, 0);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F66BC);
void func_800F66BC(const char* str, s32 x, s32 y, MenuContext* context,
                   bool disableTexShade);
#else
void func_800F66BC(const char* str, s32 x, s32 y, MenuContext* context,
                   bool disableTexShade) {
    const int ChWidth = 12;
    const int ChHeight = 16;
    u8 ch;
    u8 unk;

loop_1:
    ch = *str++;
    if (ch == 0xFF)
        return;
    unk = ((u16)(ch & 0x10)) != 0;
    func_800F5904(context, x, y, ChWidth, ChHeight, (ch & 0xF) * ChWidth,
                  (ch >> 5) * ChHeight, 0x1A1, unk + 6, disableTexShade, 0x40);
    x += ChWidth;
    goto loop_1;
}
#endif

void DrawMenuChar(char ch, int x, int y, MenuContext* context) {
    func_800F5904(context, x, y, 8, 8, (ch & 0xF) * 8, (u32)(ch & 0xF0) >> 1,
                  0x196, 0x1E, 1, 0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", DrawMenuStr);
// https://decomp.me/scratch/S4Dzb

void DrawMenuInt(s32 digit, s32 x, s32 y, MenuContext* context) {
    do {
        DrawMenuChar((digit % 10) + 16, x, y, context);
        digit /= 10;
        x += -8;
    } while (digit != 0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F6998);

void func_800F6A48(void) {
    func_800EA538(6);
    func_800EA5E4(0x411);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F6A70);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F6BEC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F6CC0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F6DC8);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", DrawSettingsButton);
#else
extern s32 g_menuButtonSettingsCursorPos;
extern s32 g_menuButtonSettingsConfig[];
extern const u8 c_chPlaystationButtons[];
extern const u8 c_chShoulderButtons[];
void DrawSettingsButton(MenuContext* context) {
    const int ActionCount = 7;
    const char** strAction;
    s32 curX;
    s32 curY;
    s32 buttonId;
    s32 i;

    i = 0;
    strAction = &c_strButtonRightHand;
    curY = 48;
    for (; i < ActionCount; i++) {
        DrawMenuStr(*strAction, 0x98, curY, context);
        buttonId = g_menuButtonSettingsConfig[i];
        curX = buttonId * 0xC;
        DrawMenuChar(c_chPlaystationButtons[buttonId], curX + 0x30 + 0xC0, curY,
                     context);
        strAction++;
        if (buttonId >= 4) {
            DrawMenuChar(c_chShoulderButtons[buttonId], curX + 0x38 + 0xC0,
                         curY, context);
        }

        curY += 16;
    }

    func_800F5E68(context, g_menuButtonSettingsCursorPos, 0x96, 0x2E, 0x54, 0xC,
                  4, 1);
}
#endif

void DrawSettingsReverseCloak(MenuContext* context) {
    DrawMenuStr(c_strNormal, 176, 48, context);
    DrawMenuStr(c_strReversal, 176, 64, context);
    func_800F5E68(context, g_SettingsCloakMode, 174, 46, 64, 12, 4, 1);
}

void DrawSettingsSound(MenuContext* context) {
    s16 cursorX = context->cursorX;
    s16 cursorY = context->cursorY;
    s32 subMenuX = cursorX + 4;
    DrawMenuStr(c_strStereo, subMenuX, cursorY + 4, context);
    DrawMenuStr(c_strMono, subMenuX, cursorY + 0x14, context);
    func_800F5E68(context, g_SettingsSoundMode, cursorX + 2, cursorY + 2, 53,
                  12, 4, 1);
}

u8 func_800F7218(u16 arg0, u16 arg1) {
    if (arg0 == arg1) {
        return 0xE4;
    }

    if (arg0 < arg1) {
        return 0xE3;
    } else {
        return 0xE5;
    }
}

void func_800F7244(void) {
    s32 i;

    g_someValue = D_80097C1C[0];
    D_80137930 = D_80097C20;
    D_80137934 = D_80097C24;

    for (i = 0; i < 4; i++) {
        D_80137938[i] = D_80097C1C[i - 0x19] + D_80097C1C[i - 0x15];
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F72BC);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", DrawPauseMenu);
#else
void func_800F622C(MenuContext* context);
void func_800F6998(s32, s32 x, s32 y, MenuContext*, s32);
extern s32 D_8003C9FC;
extern s32 D_80097C1C;
extern s32 D_800A2D68;
extern s32 D_800A2D6C;
extern const char* D_800A83AC[];
extern s32 c_arrExpNext[];
extern s16 D_8013761C;
extern s32 /*?*/ D_8013763A;
extern s32 player_stat_str;

void DrawPauseMenu(s32 arg0) {
    MenuContext* context;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s4;
    s32 temp_v0;
    s32 playerLevel;
    s32 temp_v1_2;
    const char* strPlayerName;
    s32 expNext;
    s32 phi_s4;
    s32 phi_s3;
    s32 phi_s5;
    char phi_a0_3;
    s32 phi_a1;
    s32 phi_a0_4;
    s32 phi_a1_2;
    s32 phi_a2;
    s32 phi_s4_2;
    s32 phi_s3_2;
    s32 phi_s0;
    s32* phi_s5_2;
    s32* phi_s1;
    s32 phi_a0_5;
    s32 phi_a1_3;
    s32 phi_s5_3;

    context = &D_8013761C + (arg0 * 15);
    func_800F53A4();
    if (arg0 == 1) {
        func_800F622C(context);

        if (IsAlucart()) {
            strPlayerName = c_strALUCART;
        } else {
            strPlayerName = c_strALUCARD;
        }
        DrawMenuStr(strPlayerName, 0x80, 0x28, context);
        DrawMenuStr(c_strHP, 0x60, 0x38, context);
        DrawMenuInt(g_playerHp, 0xA8, 0x38, context);
        DrawMenuChar(0xF, 0xB0, 0x38, context);
        DrawMenuInt(g_playerHpMax, 0xD0, 0x38, context);
        DrawMenuStr(c_strMP, 0x60, 0x44, context);
        DrawMenuInt(g_playerMp.current, 0xA8, 0x44, context);
        DrawMenuChar(0xF, 0xB0, 0x44, context);
        DrawMenuInt(g_playerMp.max, 0xD0, 0x44, context);
        DrawMenuStr(c_strHEART, 0x60, 0x50, context);
        DrawMenuInt(g_playerHeart, 0xA8, 0x50, context);
        DrawMenuChar(0xF, 0xB0, 0x50, context);
        DrawMenuInt(g_playerHeart->max, 0xD0, 0x50, context);
        DrawMenuStr(c_strEXP, 0x20, 0xB0, context);
        DrawMenuInt(g_playerExp, 0x90, 0xB0, context);
        DrawMenuStr(c_strNEXT, 0x20, 0xBC, context);
        playerLevel = g_playerLevel;
        if (playerLevel != 99) {
            expNext = c_arrExpNext[playerLevel] - g_playerExp;
        } else {
            expNext = 0;
        }
        DrawMenuInt(expNext, 0x90, 0xBC, context);
        DrawMenuStr(c_strGOLD, 0x20, 0xC8, context);
        DrawMenuInt(g_playerGold, 0x90, 0xC8, context);
        DrawMenuStr(c_strLEVEL, 0xF8, 0x28, context);
        DrawMenuInt(g_playerLevel, 0x130, 0x28, context);
        DrawMenuStr(c_strSTATUS, 0xF8, 0x38, context);

        temp_v1_2 = D_80072F2C;
        phi_s4 = 0x25;
        if (temp_v1_2 & 0x8000) {
            phi_s4 = 0x28;
        }
        if (temp_v1_2 & 0x4000) {
            phi_s4 = 0x26;
        }
        if (temp_v1_2 & 0x80) {
            phi_s4 = 0x27;
        }
        if (IsAlucart()) {
            phi_s4 = 0x2D;
        }
        DrawMenuStr((&c_strGOLD)[phi_s4], 0x104, 0x44,
                    context); // TODO probably wrong
        DrawMenuStr(c_strROOMS, 0xF0, 0x96, context);
        DrawMenuInt(g_roomCount, 0x148, 0x96, context);
        DrawMenuStr(c_strKILLS, 0xF0, 0xA4, context);
        DrawMenuInt(g_killCount, 0x148, 0xA4, context);
        DrawMenuStr(c_strTIME, 0xD0, 0xC0, context);
        DrawMenuInt(g_GameTimer.hours, 0x108, 0xC0, context);
        DrawMenuChar(0x1A, 0x110, 0xC0, context);
        func_800F6998(g_GameTimer.minutes, 0x120, 0xC0, context, 2);
        DrawMenuChar(0x1A, 0x128, 0xC0, context);
        func_800F6998(g_GameTimer.seconds, 0x138, 0xC0, context, 2);
    }

    phi_s3 = 0xE8;
    if (context == &D_8013763A) {
        phi_s3 = 0xF8;
        phi_s5 = 0x58;
    } else {
        phi_s5 = 0x50;
    }
    func_800F66BC(D_800A2D68, phi_s3, phi_s5, context, 1);

    temp_s1 = g_menuButtonSettingsConfig;
    phi_a1 = phi_s3 + 0x2C;
    if (temp_s1 < 4) {
        phi_a0_3 = (s32)c_chPlaystationButtons[temp_s1];
    } else {
        DrawMenuChar((s32)c_chPlaystationButtons[temp_s1], phi_s3 + 0x28,
                     phi_s5, context);
        phi_a0_3 = (s32)c_chShoulderButtons[temp_s1];
        phi_a1 = phi_s3 + 0x30;
    }
    DrawMenuChar(phi_a0_3, phi_a1, phi_s5, context);
    DrawMenuInt(D_80097C1C, phi_s3 + 0x4C, phi_s5, context);

    temp_s1_2 = D_8003C9FC;
    phi_a1_2 = phi_s3 + 0x2C;
    if (temp_s1_2 < 4) {
        phi_a0_4 = (s32)c_chPlaystationButtons[temp_s1_2];
        phi_a2 = phi_s5 + 0xA;
    } else {
        temp_s0 = phi_s5 + 0xA;
        DrawMenuChar((s32)c_chPlaystationButtons[temp_s1_2], phi_s3 + 0x28,
                     temp_s0, context);
        phi_a0_4 = (s32)c_chShoulderButtons[temp_s1_2];
        phi_a1_2 = phi_s3 + 0x30;
        phi_a2 = temp_s0;
    }
    DrawMenuChar(phi_a0_4, phi_a1_2, phi_a2, context);
    temp_s0_2 = phi_s3 + 0x4C;
    DrawMenuInt(D_80097C20, temp_s0_2, phi_s5 + 0xA, context);
    func_800F66BC(D_800A2D6C, phi_s3, phi_s5 + 0x14, context, 1);
    DrawMenuInt(D_80097C24, temp_s0_2, phi_s5 + 0x1A, context);

    if (context == &D_8013763A) {
        phi_s3_2 = 0x20;
        phi_s5_3 = 0x78;
    } else {
        DrawMenuStr(D_800A83AC[g_menuRelicsCursorIndex], 8, 0x28, context);
        phi_s3_2 = 0xC;
        phi_s5_3 = 0x46;
    }
    phi_s4_2 = 0;
    phi_s0 = phi_s5_3;
    phi_s5_2 = &player_stat_str;
    phi_s1 = &player_stat_str + 0x10;
    do {
        DrawMenuStr(*(&c_strSTR + (phi_s4_2 * 4)), phi_s3_2, phi_s0, context);
        DrawMenuInt(*phi_s5_2, phi_s3_2 + 0x2C, phi_s0, context);
        temp_v0 = *phi_s1;
        if (temp_v0 != 0) {
            if (temp_v0 > 0) {
                DrawMenuChar(0xB, phi_s3_2 + 0x34, phi_s0, context);
                phi_a0_5 = *phi_s1;
                phi_a1_3 = phi_s3_2 + 0x44;
            } else {
                DrawMenuChar(0xD, phi_s3_2 + 0x34, phi_s0, context);
                phi_a0_5 = -(s32)*phi_s1;
                phi_a1_3 = phi_s3_2 + 0x44;
            }
            DrawMenuInt(phi_a0_5, phi_a1_3, phi_s0, context);
        }
        temp_s4 = phi_s4_2 + 1;
        phi_s4_2 = temp_s4;
        phi_s0 += 0xC;
        phi_s5_2 += 4;
        phi_s1 += 4;
    } while (temp_s4 < 4);
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", DrawSpellMenu);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F7F64);

void func_800F82F4(void) {
    RECT dstRect;

    dstRect.x = 448;
    dstRect.y = 176;
    dstRect.w = g_imgUnk8013C200->width >> 2;
    dstRect.h = g_imgUnk8013C200->height;
    LoadImage(&dstRect, (u_long*)g_imgUnk8013C200->data);

    dstRect.x = 480;
    dstRect.w = g_imgUnk8013C270->width >> 2;
    dstRect.h = g_imgUnk8013C270->height;
    LoadImage(&dstRect, (u_long*)g_imgUnk8013C270->data);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F8374);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F84CC);

void func_800F86E4(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        FreePolygons(D_801377FC[i]);
    }

    FreePolygons(D_8013783C);
    FreePolygons(D_80137840);
}

void func_800F8754(MenuContext* context, s32 x, s32 y) {
    s32 curX;
    s32 phi_a1;

    if (D_801375DC == 0) {
        D_8013784C = 1;
    }

    DrawMenuStr(c_strSpells, x + 14, y + 20, context);
    if (D_801375FC == 0) {
        D_8013784C = 1;
    } else {
        D_8013784C = 0;
    }

    phi_a1 = x + 2;
    DrawMenuStr(c_strFamiliars, phi_a1, y + 68, context);
    D_8013784C = 0;
    DrawMenuStr(c_strEquip, x + 18, y + 4, context);
    curX = x + 14;
    DrawMenuStr(c_strRelics, curX, y + 36, context);
    DrawMenuStr(c_strSystem, curX, y + 52, context);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F8858);
#else
void func_800F8858(MenuContext* context) {
    s32 i = 0;
    const char** pStrEquipTypes = c_strSSword;
    s32 phi_s2 = 8;
    s32* phi_s1 = &D_8003CACC;

    for (; i < 0xB; i++) {
        DrawMenuStr(pStrEquipTypes[*phi_s1], context->cursorX + 4,
                    context->cursorY + phi_s2, context);
        phi_s1++;
        phi_s2 += 0x10;
    }

    func_800F5E68(context, D_80137618, (s16)context->cursorX + 2,
                  (s16)context->cursorY + 4, 0x48, 0x10, 0, 1);
}
#endif

void func_800F892C(s32 index, s32 x, s32 y, MenuContext* context) {
    func_800F5904(context, x, y, 16, 16, (index & 7) * 16,
                  ((index & 0xF8) * 2) | 0x80, index + 0x1D0, 0x1A, 1, 0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F8990); // Draw menu inventory

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F8C98);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F8E18);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F8F28);

void func_800F9690(void) {
    POLY_GT4* poly = &D_80086FEC[D_8013783C];

    if (D_80137608 != 0) {
        poly->pad3 = 0x80;
    } else {
        poly->pad3 = 8;
    }
    if (D_801376B0 != 0) {
        poly->pad3 = 8;
    }
}

void func_800F96F4(void) { // !Fake:
    s32 new_var2;
    POLY_GT4* temp_a0;
    s32 temp_a2;
    unkStruct3* temp_a0_2;
    s32* temp;
    s32* new_var;

    new_var = &D_80137848;
    temp_a0 = &D_80086FEC[D_80137840];
    temp_a2 = D_80137692 == 0;
    temp = &D_80137844;

    if ((D_80137844[0] != 0) && (temp_a2 != 0)) {
        (&D_80086FEC[D_80137840])->pad3 = 0x80;
        if (D_80137844[0] == 1) {
            (&D_80086FEC[D_80137840])->clut = 0x188;
        } else {
            D_80137844[0] -= 1;
            (&D_80086FEC[D_80137840])->clut = 0x181;
        }
    } else {
        temp_a0->pad3 = 8;
    }

    temp_a0_2 = temp_a0->tag;
    temp = new_var;

    if (((*temp) != 0) && (temp_a2 != 0)) {
        temp_a0_2->unk32 = 0x80;
        new_var2 = *temp;
        if (new_var2 == 1) {
            do {
                temp_a0_2->unkE = 0x188;
            } while (0);
            return;
        }
        *temp -= 1;
        temp_a0_2->unkE = 0x181;
        return;
    }
    temp_a0_2->unk32 = 8;
}

void func_800F97DC(void) {
    D_8013794C = (s8*)&D_8007EFE4;
    D_80137950 = 0x180;
    D_80137954 = 0;
}

void func_800F9808(u32 arg0) {
    s32 temp_s0;
    s32 i;
    PixPattern* oldPos;

    temp_s0 = (arg0 == 2) ? 32 : 0;
    arg0 = func_800F548C(arg0);
    oldPos = (PixPattern*)D_8013794C;

    for (i = 0; i < ((temp_s0 + 0x100) * 8); i++) {
        *D_8013794C++ = 0;
    }

    LoadTPage(oldPos, 0, 0, 0x180, arg0, temp_s0 + 256, 16);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F98AC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F99B8);

void func_800F9D40(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = &D_80082FE4;
    }

    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F98AC(arg0, arg1);
}

void func_800F9D88(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = &D_80082FE4;
    }
    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F99B8(arg0, arg1, 0);
}

void func_800F9DD0(u8* arg0, u8* arg1) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (*arg0 == 0)
            break;
        *arg1++ = *arg0++;
        *arg1++ = *arg0++;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9E18);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9F40);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA034);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA3C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA60C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA7E8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA8C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA9DC);

void func_800FAB1C(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_4];
    s32 i;

    for (i = 4; i < 64; i++) {
        if ((u32)((entity->objectId + 0xFF30) & 0xFFFF) < 16) {
            func_80106590(entity);
        }
        entity++;
    }
}

Unkstruct_80137638 D_80137638[];

void func_800FAB8C(s32 arg0) {
    D_80137638[arg0].unk0 = 1;
    D_80137638[arg0].unk1 = 0;
}

void func_800FABBC(s32 arg0) {
    D_80137638[arg0].unk0 = 3;
    D_80137638[arg0].unk1 = 0;
}

void func_800FABEC(s32 context) { D_80137638[context].unk0 = 0; }

void func_800FAC0C(s32 context) { D_80137638[context].unk0 = 2; }

void func_800FAC30(void) {
    D_80137844[0] = 0;
    D_80137848 = 0;
}

void func_800FAC48(void) {
    ClearImage(&D_800ACD90, 0, 0, 0);
    ClearImage(&D_800ACD90 + 7, 0, 0, 0);
}

void func_800FAC98(void) { func_800F9808(2); }

bool func_800FACB8(void) {
    if (D_80097494 & 2) {
        (*g_menuRelicsCursorIndex)++;
        if (*g_menuRelicsCursorIndex == 7) {
            *g_menuRelicsCursorIndex = 0;
        }
        return true;
    }
    if (D_80097494 & 1) {
        g_menuRelicsCursorIndex[0]--;
        if (*g_menuRelicsCursorIndex == -1) {
            *g_menuRelicsCursorIndex = 6;
        }
        return true;
    }
    return false;
}

void func_800FAD34(s32 arg0, u8 arg1, u16 arg2, u16 arg3) {
    D_80137608 = 0;
    func_800F9808(2);

    if (arg1) {
        D_80137608 = 1;
        func_800F99B8(arg0, 2, 0);
        func_800EB534(arg2, arg3, 0x1F);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FADC0);

void func_800FAE98(void) {
    func_800FADC0();
    D_800978F8 = 0x40;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FAEC4);

// https://decomp.me/scratch/HEhaF by @pixel-stuck
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FAF44);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB004);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB0FC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB160);

bool func_800FB1EC(s32 arg0) {
    if (D_801375CC == 0) {
        if (arg0 == 0) {
            return true;
        }
    } else if ((arg0 == 0x1A) || (arg0 == 0) || (arg0 == 0x30) ||
               (arg0 == 0x39)) {
        return true;
    }

    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB23C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB9BC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FBAC4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FBC24);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD39C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD4C0);

s32 func_800FD5BC(Unkstruct_800FD5BC* arg0) {
    s32 temp;

    if (arg0->arg4 != 5) {
        if (((u32)arg0->arg4) >= 0x10U) {
            temp = g_playerHp.max;
            if (g_playerHp.max < 0) {
                temp += 7;
            }
            arg0->arg8 = temp >> 3;
        } else if (g_playerHp.max >= (arg0->arg8 * 0x14)) {
            arg0->arg4 = 3;
        } else {
            arg0->arg4 = 2;
        }
    }
    if (g_playerHp.current <= arg0->arg8) {
        g_playerHp.current = 0;
        return 1;
    } else {
        g_playerHp.current -= arg0->arg8;
        return 0;
    }
}

s32 func_800FD664(s32 context) {
    s32 phi_a0 = context;

    if (g_mapProgramId & 0x20) {
        phi_a0 <<= 1;
    }
    return phi_a0;
}

extern Unkstruct_800A4B12 D_800A4B12[];

u8 func_800FD688(s32 arg0) { return D_800A4B12[player_equip_head[arg0]].unk0; }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD6C4);

u8* func_800FD744(s32 context) {
    u8* phi_v0 = &D_80097A8D;
    if (context != 0) {
        phi_v0 += 0xA9;
    }
    return phi_v0;
}

u8* func_800FD760(s32 context) {
    s8* phi_v0 = &D_8009798A;
    if (context != 0) {
        phi_v0 += 0xA9;
    }
    return phi_v0;
}

s32 func_800FD77C(s32 context, s32 arg1) {
    if (context == 0) {
        return *(&D_800A4B04 + (arg1 * 13));
    }

    return *(&D_800A7718 + (arg1 << 3));
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD7C0);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD874);
#else
void func_800FD874(u16 context, s32 arg1) {
    u8* temp_a0_2;
    u8* temp_v0;
    u8 temp_a1;
    u8 temp_v1;
    u8* phi_a0;
    u8* phi_a0_2;
    u16 i;
    s32 phi_a1;
    s32 phi_a1_2;

    u8* cursorY = func_800FD744(arg1);
    u8* temp_a3 = func_800FD760(arg1);
    u16 temp_a2 = context & 0xFFFF;
    u8* temp_a0 = temp_a3 + temp_a2;
    if (*temp_a0 < 0x63) {
        temp_a1 = *temp_a0;
        *temp_a0 = temp_a1 + 1;
        if (*temp_a0 == 1) {
            *temp_a0 = temp_a1;
            if (arg1 != 0) {
                i = *(&D_800A7734 + (temp_a2 << 5));
            }

            phi_a0 = cursorY;
            phi_a1 = 0;
            phi_a1_2 = 0;
            while (true) {
                if (*++phi_a0 == temp_a2)
                    break;
                phi_a1_2 += 1;
            }

            phi_a0_2 = cursorY;
        loop_8:
            temp_v1 = *phi_a0_2;
            if (*((s8*)temp_a3 + temp_v1) != 0) {
            block_12:
                phi_a0_2 += 1;
                phi_a1 += 1;
                goto loop_8;
            }
            if ((arg1 != 0) && (i != *(&D_800A7734 + (temp_v1 << 5)))) {
                goto block_12;
            }

            temp_v0 = temp_a3 + (context & 0xFFFF);
            *temp_v0 += 1;
            temp_a0_2 = &cursorY[phi_a1];
            if (phi_a1 < phi_a1_2) {
                cursorY[phi_a1_2] = *temp_a0_2;
                *temp_a0_2 = context;
            }
        }
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD9D4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FDB18);

bool func_800FDC94(s32 arg0) {
    u8 temp = D_800A841C[arg0 * 0x1C];

    if (g_playerMp.current < (s32)temp) {
        return false;
    } else {
        g_playerMp.current -= temp;
        return true;
    }
}

// https://decomp.me/scratch/5ufgy
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FDCE0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FDD44);

void func_800FDE00(void) {
    D_80137960 = 0;
    D_80137964 = 0;
    D_80137968 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FDE20);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FE044);

s32 func_800FE3A8(s32 arg0) {
    /*
     * also matches without the temp like this:
     * return (D_80097964[arg0] & ~0xfd) != 0;
     * if that array contains a bitmask, it would make
     * more sense that way.
     */
    s32 temp = 2;

    return (D_80097964[arg0] & temp) != 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FE3C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FE728);

bool func_800FE8B4(s32 arg0, s32 arg1) {
    if (g_playerMp.current >= arg0) {
        if (arg1 != 0) {
            g_playerMp.current -= arg0;
        }
        return false;
    }
    return true;
}

void func_800FE8F0(void) {
    if (D_8013B5E8 == 0) {
        D_8013B5E8 = 0x40;
    }
}

void func_800FE914(s32 arg0) {
    if (g_playerHeart->current < g_playerHeart->max) {
        g_playerHeart->current = arg0 + g_playerHeart->current;
        if (g_playerHeart->max < g_playerHeart->current) {
            g_playerHeart->current = g_playerHeart->max;
        }
        func_8011AAFC(g_EntityArray, 0x63, 0);
        PlaySfx(NA_SE_PL_COLLECT_HEART);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FE97C);

// !FAKE: explicitly casting two pointers to s32
// before comparing them, that's weird
void func_800FEE6C(void) {
    s32* var_v1 = D_80139828;

    do {
        if (*var_v1 != 0) {
            *var_v1 -= 1;
        }
        var_v1++;
    } while ((s32)var_v1 < (s32)&D_80139828[0x10]);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FEEA4);

s32 func_800FF064(s32 arg0) {
    s32 playerMp;

    playerMp = g_playerMp.current - 4;

    if (playerMp > 0) {
        if (arg0 != 0) {
            g_playerMp.current = playerMp;
        }
        return 0;
    }
    return -1;
}

void func_800FF0A0(s32 context) { D_80139828[context] = 0; }

void func_800FF0B8(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        func_800FF0A0(i);
    }
}

void func_800FF0F4(s32 arg0) { D_80139828[arg0] = 0x1000; }

s32 func_800FF110(s32 arg0) { return D_80139828[arg0]; }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF128);

s32 func_800FF460(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return arg0 + ((arg0 * D_80097BE4) >> 7);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF494);

void func_800FF60C(void) {
    s32 var_a0_2;
    s32 i;

    func_800EA538(6);

    i = 0;
    while (1) {
        if (player_equip_ring2 == D_800A2FBC[i]) {
            break;
        }

        if (D_800A2FBC[i] == -1) {
            break;
        }
        i += 2;
    }

    var_a0_2 = D_800A2FC0[i];
    if ((player_equip_ring2 == 0x32) && (g_SettingsCloakMode != 0)) {
        var_a0_2++;
    }
    func_800EA5E4(var_a0_2);
    if (player_equip_ring2 == 0x38) {
        func_800EA5E4(0x415);
    }
}

void func_800FF60C();

void func_800FF6C4(void) {
    if ((g_mapProgramId != 0x1F) &&
        (g_CurrentPlayableCharacter == PLAYER_ALUCARD)) {
        func_800FF60C();
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF708);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF7B8);

extern Unkstruct_80137990 D_80137990;

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", DrawHudRichter);
#else
void DrawHudRichter(void) {
    POLY_GT4* poly;

    D_80137978 = 0x190;
    D_8013797C = 0x190;
    D_801397FC = 0;
    D_80139008 = 0;
    D_80137994 = 0;
    D_8003C744 = NULL;
    D_80137980 = 50;
    D_80137984 = 0;
    D_80137990.unk0 = 0;
    D_8013798C = 0x9C40U / 400U;
    D_80137988 = 0x9C40U / 400U;
    D_80137970 = func_800EDD9C(4, 9);
    poly = &D_80086FEC[D_80137970];

    func_80107360(poly, 2, 22, 32, 96, 0, 0);
    poly->tpage = 0x1B;
    poly->clut = 0x101;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 216, 22, 32, 96, 32, 0);
    poly->tpage = 0x1BU;
    poly->clut = 0x100;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 4, 112, 9, 3, 64, 89);
    poly->tpage = 0x1B;
    poly->clut = 0x105;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 228, 112, 9, 3, 64, 89);
    poly->tpage = 0x1BU;
    poly->clut = 0x103U;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly->p1 = 0;
    poly->p2 = 6;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 236, 112, 9, 3, 64, 89);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, 14, 27, 8, 8, 0, 96);
    poly->tpage = 0x1BU;
    poly->clut = 0x103U;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 22, 27, 8, 8, 0, 96);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, 18, 38, 8, 8, 0, 0);
    poly->tpage = 0x1BU;
    poly->clut = 0x102;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 33, 20, 64, 24, 64, 40);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000;

    D_80137974 = func_800EDD9C(4, 16);
    poly = &D_80086FEC[D_80137974];
    if (poly != 0) {
        s32 phi_s1 = 0x20;
        s32 phi_s0 = 0xD8;
        do {
            func_80107360(poly, phi_s0, 22, 2, 96, phi_s1, 0);
            func_801072DC(poly);
            poly->tpage = 0x1B;
            poly->clut = 0x100;
            poly->pad2 = 0x1EE;
            poly->pad3 = 8;
            poly->p1 = (rand() & 0x3F) + 1;
            poly->p2 = 0;
            poly = poly->tag;
            phi_s0 += 2;
            phi_s1 += 2;
        } while (poly != 0);
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80100B50);

extern Unkstruct_80137990 D_80137990;

bool func_8010183C(s32 arg0) {
    if (arg0 == 0) {
        if (D_80137990.unk0 == 0) {
            D_80137990.unk0 = 1;
            return true;
        }
        return false;
    } else if (arg0 == 1) {
        if (D_80137990.unk0 == 0x15) {
            D_80137990.unk0 = 0x33;
            return true;
        }
        return false;
    }
    return true;
}
void DrawHudRichter(void);

void func_8010189C() {
    POLY_GT4* poly;
    s32 i;
    u16* new_var;

    D_8013B5E8 = 0;
    D_80137998 = 0;
    D_8013796C = g_playerHp.current;

    if ((g_mapProgramId == PROGRAM_ST0) ||
        (g_CurrentPlayableCharacter != PLAYER_ALUCARD)) {
        DrawHudRichter();
        return;
    }

    D_80137970 = func_800EDD9C(4, 14);
    poly = &D_80086FEC[D_80137970];

    if (poly != NULL) {
        for (i = 0; poly != NULL; i++) {
            func_80107360(poly, D_800A2EE8[i], D_800A2EF8[i], D_800A2F28[i],
                          D_800A2F38[i], D_800A2F08[i], D_800A2F18[i]);
            poly->tpage = 0x1F;
            new_var = &D_800A2F48[i];
            poly->clut = *new_var;
            poly->pad2 = 0x1F0;
            poly->pad3 = D_800A2F64[i];

            if (i == 5) {
                SetPolyRect(poly, D_800A2EED, D_800A2EFD, D_800A2F3D,
                            D_800A2F2D);
                poly->y0 = poly->y2;
                poly->x1 = poly->x0;
                poly->x2 = poly->x3;
                poly->y3 = poly->y1;
            }

            if (i == 1) {
                poly->p1 = 0;
                poly->p2 = rand() + 8;
                poly->p3 = (7 & rand()) + 1;
            }

            poly = (POLY_GT4*)poly->tag;
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80101A80);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801024DC);

extern Unkstruct_80086FFA D_80086FFA[];

u16 func_801025F4(void) { return D_80086FFA[D_8013799C].unk0; }

void func_80102628(s32 arg0) {
    POLY_GT4* poly;
    s32 temp;
    s32 i = 0;

    poly = &D_80086FEC[D_8013799C];

    if (poly != NULL) {
        temp = arg0 / 2;
        while (poly != NULL) {
            poly->y0 = 0;
            poly->u0 = (u8)temp;
            poly->v0 = 0xF0;
            poly->b0 = 0;
            poly->g0 = 0;
            poly->r0 = 0;
            poly->pad2 = 0x1FD;
            poly->pad3 = 8;
            poly->x0 = temp * (i & 1);
            poly = (POLY_GT4*)poly->tag;
            i++;
        }
    }
}

void func_801026BC(s32 arg0) {
    POLY_GT4* poly;
    u16 pad3;

    poly = &D_80086FEC[D_801379A0];
    if (arg0 == 0) {
        pad3 = 8;
        goto block_7;
    }
    if (!(g_mapProgramId & 0x20)) {
        SetPolyRect(poly, 0, 1, 255, 255);
    } else {
        poly->x2 = 255;
        poly->x0 = 255;
        poly->y1 = 240;
        poly->y0 = 240;
        poly->x3 = 0;
        poly->x1 = 0;
        poly->y3 = -15;
        poly->y2 = -15;
    }
    func_80107250(poly, arg0 * 2);
    if (arg0 == 0x40) {
        poly->pad3 = 0;
        return;
    }
    pad3 = 0x35;
block_7:
    poly->pad3 = pad3;
}

void func_801027A4(void) { func_801026BC(0); }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801027C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801028AC);

// https://decomp.me/scratch/8D47k
// That's either a compiler flag, wrong compiler, or aspsx issue
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80102CD8);
#else
extern s32 D_800A3194[];
extern u16 D_801379AC[2];
extern s32 D_801379B0;

void func_80102CD8(s32 arg0) {
    D_801379AC[0] = arg0;
    D_801379AC[1] = 0;
    D_801379B0 = D_800A3194[arg0];
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80102D08);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80102D70);

void func_80102DEC(s32 context) {
    D_80137E64 = 0;
    D_80137E68 = context;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80102E04);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80102EB8);

void func_801030B4(s32 arg0, unkStruct3* unkstruct3, s32 arg2) {
    s32 var_v1;

    if (arg2 == arg0) {
        if (g_blinkTimer & 0x20) {
            var_v1 = (g_blinkTimer & 0x1F) + 0x60;
        } else {
            var_v1 = 0x7F - (g_blinkTimer & 0x1F);
        }

        unkstruct3->unk4 = unkstruct3->unk10.data1.unk0 = var_v1 - 0x10;
        unkstruct3->unk1C.data1.unk0 = unkstruct3->unk28 = var_v1 + 0x10;
        unkstruct3->unk2A = 0;
        unkstruct3->unk1E.data1.unk0 = 0;
        unkstruct3->unk12.data1.unk0 = 0;
        unkstruct3->unk6 = 0;
        unkstruct3->unk32 = 0x404;
    } else {
        unkstruct3->unk12.data1.unk0 = 0x60;
        unkstruct3->unk6 = 0x60;
        unkstruct3->unk2A = 0x80;
        unkstruct3->unk1E.data1.unk0 = 0x80;
        unkstruct3->unk28 = 0;
        unkstruct3->unk1C.data1.unk0 = 0;
        unkstruct3->unk10.data1.unk0 = 0;
        unkstruct3->unk4 = 0;
        unkstruct3->unk32 = 0x415;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80103148);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80103238);

void func_80103EAC(void) {
    D_80137E4C = 0;
    func_800E92F4();
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80103ED4);

void func_8010427C(void) {
    FreePolygons(D_80137E40);
    FreePolygons(D_80137E44);
    FreePolygons(D_80137E48);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801042C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80104790);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80105078);

void func_80105408(void) {
    D_80072EF4 = 0x1000;
    D_80072EFC = 1;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80105428);

void func_80106590(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        FreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = NULL;
}

void func_801065F4(s16 startIndex) {
    Entity* pItem;

    for (pItem = &g_EntityArray[startIndex];
         pItem < &g_EntityArray[TOTAL_ENTITY_COUNT]; pItem++)
        func_80106590(pItem);
}

// Print debug hitboxes
void func_80106670(s32 blendMode);
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80106670);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80106A28);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010715C);

void func_801071CC(POLY_GT4* poly, u8 colorIntensity, s32 vertexIndex) {
    switch (vertexIndex) {
    case 0:
        poly->b0 = colorIntensity;
        poly->g0 = colorIntensity;
        poly->r0 = colorIntensity;
        break;
    case 1:
        poly->b1 = colorIntensity;
        poly->g1 = colorIntensity;
        poly->r1 = colorIntensity;
        break;
    case 2:
        poly->b2 = colorIntensity;
        poly->g2 = colorIntensity;
        poly->r2 = colorIntensity;
        break;
    case 3:
        poly->b3 = colorIntensity;
        poly->g3 = colorIntensity;
        poly->r3 = colorIntensity;
        break;
    }
}

void func_80107250(POLY_GT4* poly, s32 arg1) {
    func_801071CC(poly, arg1, 0);
    func_801071CC(poly, arg1, 1);
    func_801071CC(poly, arg1, 2);
    func_801071CC(poly, arg1, 3);
}

void func_801072BC(POLY_GT4* poly) { func_80107250(poly, 0); }

void func_801072DC(POLY_GT4* poly) { func_80107250(poly, 0x80); }

void func_801072FC(POLY_G4* poly) {
    poly->r0 = 0;
    poly->g0 = 0;
    poly->b0 = 0;

    poly->r1 = 0;
    poly->g1 = 0;
    poly->b1 = 0;

    poly->r2 = 0;
    poly->g2 = 0;
    poly->b2 = 0;

    poly->r3 = 0;
    poly->g3 = 0;
    poly->b3 = 0;
}

void SetPolyRect(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->x3 = x + width;
    poly->y2 = y + height;
    poly->y3 = y + height;
}

void func_80107360(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u,
                   s32 v) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->y2 = y + height;
    poly->x3 = x + width;
    poly->y3 = y + height;
    poly->v0 = v;
    poly->v1 = v;
    poly->u0 = u;
    poly->u1 = u + width;
    poly->u2 = u;
    poly->v2 = v + height;
    poly->u3 = u + width;
    poly->v3 = v + height;
}

void func_801073C0(void) {
    CdReadyCallback(NULL);
    CdDataCallback(NULL);
}

s32 func_801073E8(void) {
    u8 sp10;

    if (CdSync(1, &sp10) == 0) {
        D_80137F9C = 0;
        return D_80137F9C;
    } else {
        if ((((u32)(func_80019444() - 0x10)) < 2) || (!(sp10 & 0x10))) {
            CdControlF(1, 0);
            D_80137F9C = 0;
            return D_80137F9C;
        }
        D_80137F9C = 1;
        return D_80137F9C;
    }
}

void func_80107460(void) {
    D_80137F7C = &D_801EC000[D_80137F6C << 0x9];
    CdGetSector(D_80137F7C, 0x200);
    D_80137F6C = (D_80137F6C + 1) & 7;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", CopyMapOverlayCallback);
// https://decomp.me/scratch/1AWN1

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80107614);
// https://decomp.me/scratch/U0IGY

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80107750);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801078C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80107B04);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80107C6C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80107DB4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80107EF0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801080DC);

void func_8010838C(s32 arg0) {
    func_801073C0();
    D_8006C398 = arg0;
}

void func_801083BC(void) {
    D_8006C398 = 1;
    D_8006BAFC = 25;
    D_8013AE9C = 10;
    D_800ACC64[0] = 0;
}

bool func_801083F0(void) {
    D_8006C398 = 1;
    D_8006BAFC = 0x19;

    if (D_8013AE9C == 0) {
        return false;
    } else {
        D_8013AE9C--;
        D_800ACC64[0] += 4;
    }

    return true;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80108448);

// https://decomp.me/scratch/QZk8K
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801092E8);

void func_80109328(void) {
    s16* player_unk1E = &g_EntityArray[PLAYER_CHARACTER].unk1E;

    D_80072F86 = 0;
    if ((*player_unk1E == 0x800) &&
        (g_EntityArray[PLAYER_CHARACTER].step == 8)) {
        g_EntityArray[PLAYER_CHARACTER].unk1E = 0;
        g_EntityArray[PLAYER_CHARACTER].animationFrame = 0x9D;
        g_EntityArray[PLAYER_CHARACTER].facing =
            (g_EntityArray[PLAYER_CHARACTER].facing + 1) & 1;
    }

    if (D_80072F16[0] != 0) {
        D_80072F16[0] = 0;
        func_801092E8(0);
    }
    g_EntityArray[PLAYER_CHARACTER].blendMode = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801093C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80109594);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80109990);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80109A44);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010A234);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010A3F0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010A4A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", UpdateEntityAlucard);

void func_8010BF64(Unkstruct_8010BF64* arg0) {
    if (g_CurrentPlayableCharacter == PLAYER_ALUCARD) {
        arg0->unk14 = D_800ACEC6.unk1A - ((D_80072F2C >> 1) & 2);
        arg0->unk1C = D_800ACEC6.unk1C + ((D_80072F2C >> 1) & 2);
        arg0->unk18 = D_800ACEC6.unk10 - 1;
        arg0->unk20 = D_800ACEC6.unk0 + 1;
        return;
    }
    D_8013C00C();
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010BFFC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010C36C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010C9F4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010D010);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010D2C8);

void func_8010D584(s16 context) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->step = context;
    player->unk2E = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010D59C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010D800);

void func_8010DA2C(s32* arg0) {
    g_CurrentEntity->unk4C = arg0;
    g_CurrentEntity->animationFrameDuration = 0;
    g_CurrentEntity->animationFrameIndex = 0;
}

void func_8010DA48(u32 arg0) {
    g_CurrentEntity->unkAC = arg0;
    g_CurrentEntity->animationFrameDuration = 0;
    g_CurrentEntity->animationFrameIndex = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DA70);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DB38);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DBFC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DDA0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DF70);

void func_8010DFF0(s32 arg0, s32 arg1) {
    POLY_GT4* poly;
    s32 i;

    if (arg0 != 0) {
        g_EntityArray[UNK_ENTITY_1].unk7C.modeU8.unk1 = 1;
        g_EntityArray[UNK_ENTITY_3].animationFrame = 0;
        g_EntityArray[UNK_ENTITY_2].animationFrame = 0;
        g_EntityArray[UNK_ENTITY_1].animationFrame = 0;
        poly = &D_80086FEC[g_EntityArray[UNK_ENTITY_1].firstPolygonIndex];

        for (i = 0; i < 6; i++) {
            poly->x1 = 0;
            poly = (POLY_GT4*)poly->tag;
        }
    }

    g_EntityArray[UNK_ENTITY_1].unk7C.modeU8.unk0 = 1;
    g_EntityArray[UNK_ENTITY_1].unk7E = 10;

    if (arg1 != 0) {
        if (arg1 < 4) {
            D_80072F1E = 4;
        } else {
            D_80072F1E = arg1;
        }
    }
}

void func_8010E0A8(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_1];

    entity->unk7E = 0;
}

void func_8010E0B8(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_1];

    entity->unk7C.modeU8.unk1 = 0;
    entity->unk7C.modeU8.unk0 = 0;
}

void func_8010E0D0(s32 arg0) {
    Entity* entity;

    if (arg0 == 1) {
        entity = func_8011AAFC(g_EntityArray, 0x47002C, 0);

        if (entity != NULL) {
            entity->unk34 = entity->unk34 | 0x10000;
        }

        entity = func_8011AAFC(g_EntityArray, 0x40002C, 0);

        if (entity != NULL) {
            entity->unk34 = entity->unk34 | 0x10000;
        }
    }
    func_8010DFF0(1, 1);
}

void func_8010E168(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        func_8011AAFC(g_CurrentEntity, 0x15002C, 0);
        if (arg1 >= D_80072F1A[0]) {
            D_80072F1A[0] = arg1;
        }
    } else if (D_80072F1C[0] <= arg1) {
        D_80072F1C[0] = arg1;
    }
}

void func_8010E1EC(s32 speed) {
    if (g_CurrentEntity->accelerationX < 0) {
        g_CurrentEntity->accelerationX += speed;
        if (g_CurrentEntity->accelerationX > 0) {
            g_CurrentEntity->accelerationX = 0;
        }
    } else {
        g_CurrentEntity->accelerationX -= speed;
        if (g_CurrentEntity->accelerationX < 0)
            g_CurrentEntity->accelerationX = 0;
    }
}

void func_8010E234(s32 speed) {
    if (g_CurrentEntity->accelerationY < 0) {
        g_CurrentEntity->accelerationY += speed;
        if (g_CurrentEntity->accelerationY > 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    } else {
        g_CurrentEntity->accelerationY -= speed;
        if (g_CurrentEntity->accelerationY < 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    }
}

s32 func_8010E27C(void) {
    u16* facing;

    if (*D_80072F64 & 2) {
        return 0;
    }

    facing = &g_EntityArray->facing;
    if (*facing == 1) {
        if (D_80072EE8 & 0x2000) {
            *facing = 0;
            D_80072F6C = 1;
            return -1;
        } else if (D_80072EE8 & 0x8000) {
            return 1;
        }
    } else {
        if (!(D_80072EE8 & 0x2000)) {
            if (D_80072EE8 & 0x8000) {
                *facing = 1;
                D_80072F6C = 1;
                return -1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

// https://decomp.me/scratch/YvoMU
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E334);

/*
 * Updates the Entity acceleration in the X Axis
 */
void func_8010E390(s32 accelerationX) {
    if (g_CurrentEntity->facing == 1) {
        accelerationX = -accelerationX;
    }
    g_CurrentEntity->accelerationX = accelerationX;
}

/*
 * Updates the Player acceleration in the X Axis
 */
void func_8010E3B8(s32 accelerationX) {
    Entity* player = GET_PLAYER(g_EntityArray);

    if (player->objectRoomIndex == 1) {
        accelerationX = -accelerationX;
    }
    player->accelerationX = accelerationX;
}

void func_8010E3E0(void) {
    if (D_80072F68[0] != 0) {
        func_80106590(&D_80073F98);
        D_80072F68[0] = 0;
    }
}

void func_8010E42C(u16 arg0) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->unk2E = arg0;
    player->step = 0x12;

    if (!(arg0 & 1)) {
        func_8010DA48(0xF4);
    } else {
        func_8010DA48(0xF5);
    }
}

// https://decomp.me/scratch/wgVVw // nop in between array assignments
// aspsx
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E470);
#else
void func_8010E470(s32 arg0, s32 arg1) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationX = arg1;
    player->accelerationY = 0;
    player->step = ENTITY_STEP_2;
    player->unk2E = D_800ACF4C[arg0 * 2 + 0];
    func_8010DA48(D_800ACF4C[arg0 * 2 + 1]);
}
#endif

void func_8010E4D0(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    func_80111CC0();

    player->palette = 0x8100;
    player->zPriority = g_zEntityCenter;

    if ((u32)(D_80072F92 - 1) < 2U) {
        func_8010DA48(0xC7);
        player->accelerationY = 0;
        player->accelerationX = 0;
        func_8010D584(6);
        func_80111CC0();
        PlaySfx(0x6F2);
        return;
    }
    func_80111CC0();
    func_8010E470(0, 0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E570);
void func_8010E570(/*?*/ s32);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E6AC);

void func_8010E7AC(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    func_8010D584(3);

    if (D_80072F70 != 1) {
        func_8010DA48(0x1C);
    }

    player->accelerationY = 0x20000;
    player->accelerationX = 0;
    D_80072F0C = 8;

    if (D_80072F24 & 1) {
        D_80072F0A = 8;
    } else {
        D_80072F0A = 0;
    }

    D_80072F64[0] = 0x10;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E83C);

void func_8010E940(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    D_80072F64[0] |= 0x21;
    func_8010DA48(0x20);
    player->unk2E = 0;
    player->accelerationY = -0x44000;
    if (D_80072F92 != 0) {
        player->accelerationY = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E9A4);

// https://decomp.me/scratch/9jKqU
// matching in decomp.me, probably aspsx
// TODO: aspatch div macro
// https://discord.com/channels/710646040331681844/815529862604390411/1051628313073958992
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EA54);
#else
void func_8010EA54(s32 arg0) {
    s16 temp_hi;

    if (arg0 != 0) {
        temp_hi = rand() % arg0;

        if (temp_hi < 4) {
            PlaySfx(D_800ACF60[temp_hi]);
        }
    }
}
#endif

s32 func_8010EADC(s16 arg0, s16 arg1) {
    Entity* var_v1 = D_80074C08;
    s32 i;
    s32 var_a2;
    s32 ret;

    for (i = 0, var_a2 = 0, ret = 0; i < 16; i++) {
        if (var_v1[i - 1].objectRoomIndex == 0) {
            ret++;
        }

        if (var_v1[i].posX.Data.low != 0) {
            if (var_v1[i].posX.Data.low == arg0) {
                var_a2++;
            }
        }

        if (var_a2 >= arg1) {
            return -1;
        }
    }

    return (ret == 0) ? -1 : 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EB5C);

// https://decomp.me/scratch/N8Srk
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EC8C);

void func_8010ED54(u8 arg0) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationY = 0;
    player->accelerationX = 0;
    func_8010D584(0xF);
    func_8010DA48(arg0);
    func_8011AAFC(g_CurrentEntity, 0x14003D, 0);
    D_80072F68[0] = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EDB8);

void func_8010FAF4(void) {
    func_80106590(&D_80073F98);
    D_80072F66 = 0;
}

void func_8010FB24(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationY = 0;
    player->accelerationX = 0;
    func_8010D584(0x22);
    func_8010E168(1, 0x10);
    func_8010E3E0();
}

void func_8010FB68(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationY = 0;
    player->accelerationX = 0;
    func_8010D584(0x20);
    func_8010E3E0();
    func_8010DA48(0xBA);
    PlaySfx(0x6F3);
    PlaySfx(0x67D);
    D_80072F16[0] = func_800FDB18(3, 0x400);
    func_801092E8(1);
    func_8011AAFC(g_CurrentEntity, 0x110028, 0);
    func_80118C28(0xB);
}

void func_8010FBF4(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationY = 0;
    player->accelerationX = 0;
    func_8010D584(0x25);
    func_8010E3E0();
    func_8010DA48(0xDA);
    PlaySfx(0x6F4);
    func_80118C28(0xC);
    D_80072F18 = 4;
}

void func_8010FC50(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationY = 0;
    player->accelerationX = 0;
    func_8010D584(0x21);
    func_8010E3E0();
    func_8011AAFC(g_CurrentEntity, 0x75, 0);
    func_8010DA48(0xF0);
    PlaySfx(0x6F1);
    D_80072F18 = 4;
}

void func_8010FCB8(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationY = 0;
    player->accelerationX = 0;
    func_8010D584(0x23);
    func_8010E3E0();
    func_8011AAFC(g_CurrentEntity, 0x10075, 0);
    func_8010DA48(0xF1);
    PlaySfx(0x6F1);
    D_80072F18 = 4;
}

void func_8010FD24(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationY = 0;
    player->accelerationX = 0;
    func_8010D584(0x27);
    func_8010E3E0();
    func_8010DA48(0xF1);
    func_8011AAFC(g_CurrentEntity, 0x170028, 0);
    D_80072F18 = 4;
}

void func_8010FD88(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->step = ENTITY_STEP_0;
    player->unk2E = 3;
    func_8010E390(0xFFFC8000);
    g_CurrentEntity->accelerationY = 0;
    func_8010DA48(0xDB);
    func_8011AAFC(g_CurrentEntity, 0, 0);
    D_80072F66 = 0;
    PlaySfx(0x617);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010FDF8);
s32 func_8010FDF8(/*?*/ s32);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80110394);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801104D0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801106A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011081C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80110968);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80110BC8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80110DF8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80111018);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801112AC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011151C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80111830);

void func_80111928(void) { D_801396EA = 0; }

void func_80111938(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    D_801396EA = 1;
    D_801396E4 = player->animationFrame;
    D_801396E6.typeShort = player->unk19;
    D_801396E8 = player->palette;
}

void func_8011197C(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    D_801396EA = 0;
    player->unk44 = 0;
    player->animationFrame = D_801396E4;
    player->unk19 = D_801396E6.typeByte;
    player->palette = D_801396E8;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801119C4);

void func_80111CC0(void) {
    if (D_80072F00[1] != 0) {
        func_8011AAFC(g_CurrentEntity, 0x17002C, 0);
    }
    if (D_80072F00[0] != 0) {
        func_8011AAFC(g_CurrentEntity, 0x16002C, 0);
    }
}

bool func_80111D24(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s32 sp10[9]; // !FAKE: There's a struct inside the stack.
    s32 speed = 0xC000;
    s16 posX = player->posX.Data.high;
    s16 posY = player->posY.Data.high;
    s32 hitboxLeftMargin;
    s32 hitboxRightMargin;

    CheckCollision(posX - 7, posY, (s32*)&sp10, 0);
    hitboxLeftMargin = sp10[0] & 0x10;
    CheckCollision(posX + 7, posY, (s32*)&sp10, 0);
    hitboxRightMargin = sp10[0] & 0x10;

    if (hitboxRightMargin & hitboxLeftMargin) {
        func_8010E390(speed);
        return true;
    } else if (hitboxRightMargin != 0) {
        player->accelerationX = -speed;
        return true;
    } else if (hitboxLeftMargin != 0) {
        player->accelerationX = speed;
        return true;
    }
    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80111DE8);

bool func_8011203C(void) {
    s32 collision = func_80111D24();

    if (g_EntityArray[UNK_ENTITY_10].step == ENTITY_STEP_5) {
        if (collision == false) {
            func_80106590(&g_EntityArray[UNK_ENTITY_10]);
            return true;
        }
        return false;
    } else if (g_EntityArray[UNK_ENTITY_10].step <= ENTITY_STEP_2) {
        if (g_EntityArray[UNK_ENTITY_10].step != ENTITY_STEP_0) {
            D_80072F66 = 0;
            g_EntityArray[UNK_ENTITY_10].step = ENTITY_STEP_3;
        }
    }
    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801120B4);

void func_80112B64(void) {
    if (func_8010FDF8(0x4301C) == 0) {
        func_8010E390(0x18000);
        if (func_8010E27C() == 0) {
            func_8010E570(0);
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80112BB0);

void func_80113148(void) {
    if ((D_80072F0A != 0) && (D_80072EEC & 0x40)) {
        func_8010E83C(1);
    } else if (func_8010FDF8(0x9029) == 0) {
        func_8010E1EC(0x1000);
        if (func_8010E27C() != 0) {
            func_8010E390(0xC000);
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801131C4);

void func_801139CC(s32 arg0) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s32 move = player->facing != 0 ? -3 : 3;

    player->posY.Data.high -= 22;
    player->posX.Data.high = move + player->posX.Data.high;
    func_8011AAFC(g_CurrentEntity, 0x10004, 0);
    player->posY.Data.high = player->posY.Data.high + 22;
    player->posX.Data.high = player->posX.Data.high - move;

    if (arg0 & 1) {
        func_80102CD8(3);
        PlaySfx(NA_SE_SECRET_STAIRS);
    }
    if (arg0 & 2) {
        player->accelerationX = 0;
        player->accelerationY = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113AAC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113D7C);

// !FAKE: too many temps
s16 func_80113E68(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s16 rnd = rand();
    s32 temp_v0;
    s32 var_a1;

    temp_v0 = rnd;
    player->unkAC = (rnd % 3) + 0x2E;
    var_a1 = rnd;
    if (rnd < 0) {
        var_a1 = rnd + 0xF;
    }
    return (temp_v0 - ((var_a1 >> 4) * 0x10));
}

void func_80113EE0(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->unk19 &= 0xF3;
    player->animationSet = 1;
    player->animationFrameDuration = 0;
    player->animationFrameIndex = 0;
    player->objectId = 0;
    player->blendMode = 0;
    *D_80072F64 = 0;
    D_80072F66 = 0;
    player->unk1E = 0;
    player->zPriority = g_zEntityCenter;
    if (g_EntityArray[UNK_ENTITY_10].objectId == 0x22) {
        func_8010FAF4();
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113F7C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011405C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80114DF4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115394);

void func_80115BB0(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->unk19 = 4;
    player->accelerationY = 0;
    player->accelerationX = 0;
    player->animationFrameDuration = 4;

    if (D_80097420 == 0) {
        if (D_80072F20 & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        func_8011AAFC(g_CurrentEntity, 0x4A0000 | 0x2C, 0);
        D_80097D37 = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115C50);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115DA0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115F54);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116208);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116408);

void func_801166A4(void) {
    switch (g_EntityArray[PLAYER_CHARACTER].unk2E) {
    case 0:
        func_80113EE0();
        D_80072F60 = 0x8166;
        D_80072F04 = 6;
        g_EntityArray[PLAYER_CHARACTER].accelerationX = 0;
        g_EntityArray[PLAYER_CHARACTER].accelerationY = 0;
        g_EntityArray[PLAYER_CHARACTER].unkAC = 0x33;
        func_8011AAFC(g_CurrentEntity, 0, 0);
        func_8011AAFC(g_CurrentEntity, 0x58002C, 0);
        g_EntityArray[PLAYER_CHARACTER].unk2E += 1;
        break;

    case 1:
        if (g_EntityArray[PLAYER_CHARACTER].animationFrameDuration < 0) {
            PlaySfx(0x6F2);
            func_8010E570(0);
        }
        break;

    default:
        break;
    }
}

void func_8011678C(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->accelerationY = 0;
    player->accelerationX = 0;
    if (D_80072EF6 != 2) {
        func_8010E570(0);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801167D0);

bool func_80116838(void) {
    if ((g_EntityArray->unk2E != 0) &&
        ((D_8009744C != 0) || (D_80072EEC & 8) || (func_800FEEA4(0, 1) < 0))) {
        func_8010D584(9);
        func_8010DA48(0xCA);
        D_800AFDA6 = 6;
        g_EntityArray->palette = 0x810D;
        D_80072F86 = 0;
        D_80072F88 = 0;
        func_8011AAFC(g_CurrentEntity, 0x21002C, 0);
        g_EntityArray->accelerationY = g_EntityArray->accelerationY >> 1;
        return true;
    }
    return false;
}

void func_8011690C(s16 arg0) {
    s16* player_unk1E = &g_EntityArray[PLAYER_CHARACTER].unk1E;

    if (*player_unk1E < arg0) {
        *player_unk1E += 16;
        if (arg0 < *player_unk1E) {
            *player_unk1E = arg0;
        }
    }
    if (arg0 < *player_unk1E) {
        *player_unk1E -= 16;
        if (*player_unk1E < arg0) {
            *player_unk1E = arg0;
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116994);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116B0C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801177A0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80117AC0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80117D3C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80117DEC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801182F8);

void func_80118614(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    if (player->animationFrameDuration < 0) {
        func_8010E570(0);
    }
}

void func_80118640(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    if (player->animationFrameDuration < 0) {
        func_8010E470(0, 0);
    }
}

void func_80118670(void) {
    Entity* player = GET_PLAYER(g_EntityArray);
    s32* animationFrameIndex = (s32*)&player->animationFrameIndex;

    if (*animationFrameIndex == 0x10007) {
        func_8011AAFC(g_CurrentEntity, 0x160028, 0);
        PlaySfx(0x67D);
        func_8011AAFC(g_CurrentEntity, 0x70, 0);
    }
    if (player->animationFrameDuration < 0) {
        func_8010E570(0);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801186EC);

Entity* func_8011879C(s16 entityIndex, s16 arg1) {
    Entity* entity = &g_EntityArray[entityIndex];
    s16 var_a0 = entityIndex;

    if (entityIndex < arg1) {
        while (var_a0 < arg1) {
            if (entity->objectId == ENTITY_MIN) {
                return entity;
            }
            var_a0++;
            entity++;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118810);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118894);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118970);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118B18);

// https://decomp.me/scratch/LmXYY
// nops between assignments probably aspsx
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118C28);
#else
extern u8 D_800ACFB4[];
extern u8 D_800ACFB5[];
extern u8 D_800ACFB6[];
extern u8 D_800ACFB7[];
extern u8 D_8013803C;
extern u8 D_80138040;
extern u8 D_80138044;
extern u8 D_80138048;

void func_80118C28(s32 arg0) {
    s32 temp_a0;

    temp_a0 = arg0 * 4;
    D_8013803C = D_800ACFB4[temp_a0];
    D_80138040 = D_800ACFB5[temp_a0];
    D_80138044 = D_800ACFB6[temp_a0];
    D_80138048 = D_800ACFB7[temp_a0];
}
#endif

s32 func_80118C84(s16 arg0, s16 arg1) {
    Entity* entity = func_8011879C(0x38, 0x40);
    Entity* player = GET_PLAYER(g_EntityArray);

    if (entity != NULL) {
        func_80106590(entity);
        entity->objectId = ENTITY_13;
        entity->posX.value = player->posX.value;
        entity->posY.value = player->posY.value;
        entity->unk80.modeS16.unk0 = arg0;
        entity->unk80.modeS16.unk2 = arg1;
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118D0C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80119588);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80119D3C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80119E78);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80119F70);

void func_8011A290(Entity* entity) {
    Unkstruct_8011A290 sp10;

    func_800FE3C4(&sp10, entity->unkB0, 0);
    entity->unk40 = sp10.sp10;
    entity->unk42 = sp10.sp14;
    entity->unk3C = sp10.sp1C;
    entity->unk49 = sp10.sp17;
    entity->unk58 = sp10.sp18;
    entity->unk6A = sp10.sp1E;
    entity->objectRoomIndex = sp10.sp22;
    entity->unkB2 = sp10.sp20;
    func_80118894(entity);
}

void func_800FD9D4(Unkstruct_8011A328*, s32 arg1);

void func_8011A328(Entity* entity, s32 arg1) {
    Unkstruct_8011A328 sp10;

    func_800FD9D4(&sp10, arg1);
    entity->unk40 = sp10.sp28;
    entity->unk42 = sp10.sp26;
    entity->unk3C = sp10.sp20;
    entity->unk49 = sp10.sp1D;
    entity->unk58 = sp10.sp1E;
    entity->unk6A = sp10.sp22;
    entity->objectRoomIndex = sp10.sp24;
    func_80118894(entity);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011A3AC);

void func_8011A4C8(void) {}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011A4D0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011A870);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011A9D8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011AAFC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011AC3C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011B190);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011B334);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011B480);

void func_8011B530(Entity* entity) {
    Entity* player = GET_PLAYER(g_EntityArray);

    if (player->step != 0x25) {
        func_80106590(entity);
    } else if (entity->step == ENTITY_STEP_0) {
        entity->unk34 = 0x60000;
        func_8011A328(entity, 5);
        entity->step++;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011B5A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011BBE0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011BD48);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011BDA4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011D9F8);

void func_8011E0E4(void) {}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011E0EC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011E390);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011E4BC);

void func_8011EDA0(void) {}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011EDA8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011F074);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011F24C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011F934);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801200AC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80120AF8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80120DD0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80121980);

extern Unkstruct_80138094 D_80138094[];

void func_80121F14(s32 arg0, s32 arg1) {
    Unkstruct_80138094* ptr = D_80138094;
    s32 i;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->unk0 = arg0 + ptr->unk0;
        ptr->unk4 = arg1 + ptr->unk4;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80121F58);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012231C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80123788);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801238CC);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80123A60);
#else
void func_80123A60(Entity* entity) {
    Entity* player = GET_PLAYER(g_EntityArray);

    if (D_80072F2C & 0x01000000) {

#if 1
        entity->posX.Data.high = player->posX.Data.high; //(u16) D_800733DA;
        entity->posY.Data.high = player->posY.Data.high; //(u16) D_800733DE;
#else // This one generates the  first missing move a0, s0 for some reason?
        entity->posX.Data.high = (u16)D_800733DA;
        entity->posY.Data.high = (u16)D_800733DE;
#endif
        if (entity->step == 0) {
            func_8011A328(entity, 0xB);
            entity->unk34 = 0x04060000;
            entity->step++;
        }
        if (player->animationFrame == 5) {
            entity->hitboxWidth = 12;
            entity->hitboxHeight = 32;
            entity->unk10 = 0x1C;
            entity->unk12 = -0xC;
            return;
        }
        if (player->animationFrame == 6) {
            entity->hitboxWidth = 10;
            entity->hitboxHeight = 10;
            entity->unk10 = 0x1C;
            entity->unk12 = 0x10;
            return;
        }
        goto block_7;
    }
block_7:
    func_80106590(entity);
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80123B40);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80123F78);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80124164);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801243B0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80124A8C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80124B88);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80125330);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80125A30);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80125B6C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80125C2C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80125E68);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801262AC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801267B0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80126C48);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80126ECC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801274DC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012768C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80127840);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801279FC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80127CC8);

void func_80127EAC(s16 arg0) {
    g_CurrentEntity->unk7C.modeS16 =
        (arg0 * 2) - g_CurrentEntity->unk7C.modeS16;
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

void func_80127EF0(s16 arg0) {
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk7C.modeS16 =
            (arg0 * 2) - g_CurrentEntity->unk7C.modeS16;
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80127F40);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80128714);

s32 func_80128BBC(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] < 16) {
                temp->unk00[j] = 16;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80128C2C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801291C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80129864);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012A0A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012A528);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012A89C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012B78C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012B990);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012BEF8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012C600);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012C88C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012C97C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CA64);

void func_8012CB0C(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->unkAC = 0xDE;
    player->accelerationY = 0;
    D_800B0914 = 0;
    player->animationFrameIndex = 0;
    player->animationFrameDuration = 0;
    player->unk2E = 7;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CB4C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CC30);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CCE4);

void func_8012CED4(void) {
    if ((g_EntityArray[PLAYER_CHARACTER].unk2E == 2) &&
        (D_800B0914 == g_EntityArray[PLAYER_CHARACTER].unk2E)) {
        func_8010DA48(0xE7);
        D_800B0914 = 1;
    } else {
        func_8010DA48(0xE8);
        func_8010E390(0x10000);
        D_800B0914 = 0;
        if (D_80138438 & 0x40) {
            g_EntityArray[PLAYER_CHARACTER].animationFrameIndex = 4;
            g_EntityArray[PLAYER_CHARACTER].accelerationX = 0;
            g_EntityArray[PLAYER_CHARACTER].animationFrameDuration = 1;
        }
    }
    g_EntityArray[PLAYER_CHARACTER].unk2E = 5;
    D_80072F0A = 8;
    g_EntityArray[PLAYER_CHARACTER].accelerationY = 0;
    D_80138430 -= 0x100;
}

void func_8012CFA8(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    func_8010DA48(0xEA);
    player->unk2E = 6;
    D_800B0914 = 0;
    player->accelerationX = 0;
    D_80072F0A = 8;
}

void func_8012CFF0(void) {
    Entity* player = GET_PLAYER(g_EntityArray);

    player->unk2E = 3;
    func_8010DA48(0xE3);
    D_800B0914 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012D024);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012D178);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012D28C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012D3E8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012DBBC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012DF04);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012E040);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012E550);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012E7A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012E9C0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012EAD0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012ED30);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012EF2C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012F178);

s32 func_8012F83C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a0 = arg0 - arg2;
    s32 temp_a1 = arg1 - arg3;

    return ((SquareRoot12((SQ(temp_a0) + SQ(temp_a1)) << 12, temp_a1) >> 12) <
            arg4) ^
           1;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012F894);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80130264);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80130618);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801309B4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80130E94);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8013136C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801315F8);

void func_80131EBC(const char* str, s16 id) { D_80138784[id] = str; }

void func_80131ED8(s32 value) { D_80138F20 = value; }

void func_80131EE8(void) {
    D_80139020 = 1;
    D_8013B694 = 0;
}

void func_80131F04(void) {
    D_80139020 = 0;
    D_8013B694++;
}

s32 func_80131F28(void) { return D_80138F7C; }

u16 func_80131F38(void) {
    if (D_80139810 == 0) {
        return 0;
    }
    return D_80139810 | 0x200;
}

bool func_80131F68(void) {
    if (D_8013B61C == 0) {
        return D_8013901C != 0;
    }
    return true;
}

s16 func_80131F94(void) { return D_8013B668; }

void func_80131FA4(s16 arg0) { func_80021F6C(arg0, arg0); }

void func_80131FCC(void) {
    if (D_8013B680 == 0) {
        D_80138F7C = 0;
    } else {
        s32 temp_v1 = D_8013B680;
        s32 temp_v0 = D_8013B680;
        if (temp_v0 >= 0 && temp_v1 < 3)
            D_80138F7C++;
    }
    D_8013B680 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132028);

void func_80132134(void) {
    g_volumeL = 127;
    g_volumeR = 127;
    SsSetMVol(g_volumeL, g_volumeR);
}

void func_8013216C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8013B620[i] = 0;
        D_8013B614[i] = 0;
        D_8013AE84[i] = 0;
        D_8013B66C[i] = 0;
        D_8013B5EC[i] = 0;
        D_8013B628[i] = 0;
        D_8013B648[i] = 0;
        D_8013AEA0[i] = 0;
    }
}

void func_801321FC(void) {
    s32 i;

    func_8013216C();
    D_8013B690 = 0;

    for (i = 0; i < 4; i++) {
        D_8013B650[i] = 0;
        D_8013AED4[i] = 0;
    }
    D_80139804 = 0;
    D_8013B664 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132264);

void func_801324B4(s8 s_num, s16 arg1, s16 arg2) {
    short voll = D_800BD07C[arg1];
    short volr = D_800BD07C[arg2];

    SsSetSerialVol(s_num, voll, volr);
}

void func_80132500(u8 soundMode) {
    CdlATV audioVolume;

    switch (soundMode) {
    case MONO:
        if (D_801390A8 != 0) { // D_801390A8 fake symbol or part of another
            func_80021174();
            audioVolume.val2 = 128; // CD (R) --> SPU (R)
            audioVolume.val0 = 128; // CD (L) --> SPU (L)
            audioVolume.val3 = 128; // CD Right sound transferred to left
            audioVolume.val1 = 128; // CD Left sound transferred to right
            CdMix(&audioVolume);
            D_8013AE7C = 108;
            D_801390A8 = 0;
        }
        break;
    case STEREO:
        if (D_801390A8 != 1) {
            func_80021188();
            audioVolume.val2 = 224; // CD (R) --> SPU (R)
            audioVolume.val0 = 224; // CD (L) --> SPU (L)
            audioVolume.val3 = 0;
            audioVolume.val1 = 0;
            CdMix(&audioVolume);
            D_8013AE7C = 127;
            D_801390A8 = 1;
        }
        break;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801325D8);

s32 func_801326D8(void) {
    if (D_8013901C != 0)
        return 1;
    if (D_80139810 != 0)
        return 3;
    return (D_801390D8 != 0) * 2;
}

void func_8013271C(void) {
    while (!(func_801326D8() & 0xFF) == 0) {
        VSync(0);
        func_801361F8();
    }
}

void func_80132760(void) {
    SsSetMVol(0, 0);
    SsSetSerialAttr(0, 0, 0);
    func_801324B4(0, 0, 0);
    func_80132134();
    func_80132264();
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801327B4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132A04);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132C2C);

extern s16 D_80139868[];

u16 func_80132E38(void) {
    s32 i;

    for (i = 0; i < 255; i++) {
        D_80139868[i] = D_80139868[i + 1];
    }
    D_801396F4--;

    return D_801396F4;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132E90);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132F60);
void func_80132F60();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80133290);
void func_80133290();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80133488);
void func_80133488();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80133604);
void func_80133604();

void func_80133780(s8 arg0) { SsSetSerialAttr(0, 1, arg0 == 1); }

void func_801337B4(void) {
    if (D_80139810 != 0) {
        func_80020F44(D_8013B658);
        SsSeqClose(D_8013B658);
        func_8013415C();
        D_80139810 = 0;
        D_801390C4 = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80133810);

s32 func_80133940(void) { return D_801396F4 == 0; }

s32 func_80133950(void) { return D_8013980C == 0; }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80133960);
void func_80133960();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80133BDC);
void func_80133BDC();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80133FCC);

extern Unkstruct_80138FB4* D_80138FB4;

void func_80134104(void) {
    D_80138FB4->unk4 = 0x4000;
    D_80138FB4->unk0 = 0xFFFFFF;
    D_80138FB4->unk36 = 0xE;
    func_8002A09C(D_80138FB4);
    D_80138F28 = 0xFFFFFF;
    func_801321FC();
}

void func_8013415C(void) {
    D_80138FB4->unk4 = 0x4000;
    D_80138FB4->unk0 = 0xFFFFFF;
    D_80138FB4->unk36 = 8;
    func_8002A09C(D_80138FB4);
    D_80138F28 = 0xFFFFFF;
    func_801321FC();
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801341B4);
void func_801341B4();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134388);
void func_80134388();

extern Unkstruct_80138FB4* D_801390C8;

void func_80134508(void) {
    D_801390C8->unk0 = 0x300000;
    D_801390C8->unk4 = 0x4000;
    D_801390C8->unk36 = 0xE;
    func_8002A09C(D_801390C8);
    D_80138F28 |= 0x300000;
}

extern Unkstruct_80138FB4* D_801390CC;

void func_80134564(void) {
    D_801390CC->unk0 = 0xC00000;
    D_801390CC->unk4 = 0x4000;
    D_801390CC->unk36 = 0xE;
    func_8002A09C(D_801390CC);
    D_80138F28 |= 0xC00000;
}

extern Unkstruct_80138FB4* D_801390C8;

void func_801345C0(void) {
    D_801390C8->unk0 = 0x300000;
    D_801390C8->unk4 = 0x4000;
    D_801390C8->unk36 = 8;
    func_8002A09C(D_801390C8);
    D_80138F28 |= 0x300000;
}

extern Unkstruct_80138FB4* D_801390CC;

void func_8013461C(void) {
    D_801390CC->unk0 = 0xC00000;
    D_801390CC->unk4 = 0x4000;
    D_801390CC->unk36 = 8;
    func_8002A09C(D_801390CC);
    D_80138F28 |= 0xC00000;
}

s32 func_80134678(s16 arg0, u16 arg1) {
    s32 ret = -2;
    u16 temp;

    if (D_80139804 != 0) {
        ret = 0;
        temp = arg1 + 8;

        if ((temp) >= 0x11) {
            arg1 = 0;
            ret = -1;
        }

        D_8013AE94 = arg1;
        D_8013AEE0 = arg0;
        D_8013B3E8[D_80139A70] = 1;
        D_80139A70++;

        if (D_80139A70 == 0x100) {
            D_80139A70 = 0;
        }
    }
    return ret;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134714);

void PlaySfx(s16 sfxId) {
    u16 offset;

    if (D_8013AEEC != 0) {
        offset = (u32)(sfxId - 0x601);
        if (offset < 0x2E0) {
            D_801390DC[D_80139000].unk00 = sfxId - 0x600;
            D_801390DC[D_80139000].unk02 = 0xFFFF;
            D_801390DC[D_80139000].unk04 = 0;
            D_80139000++;
            if (D_80139000 == 0x100) {
                D_80139000 = 0;
            }
        } else {
            switch (sfxId) {
            case 0x10:
            case 0x11:
                D_8013980C = 1;
                break;

            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x90:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
                D_8013B61C = 1;
                break;

            default:
                break;
            }

            D_8013B3E8[D_80139A70] = sfxId;
            D_80139A70++;
            if (D_80139A70 == 0x100) {
                D_80139A70 = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8013493C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801349F4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134B48);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134C60);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134D14);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134E64);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134F50);
void func_80134F50();

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801353A0);
#else
void func_801353A0(void) {
    if (D_801396F4 == 0)
        return;

    switch (D_80139868[0]) {
    case 2:
        func_80133604();
        break;
    case 3:
        func_80133488();
        break;
    case 4:
        func_80132F60();
        break;
    case 6:
        func_80133290();
        break;
    case 8:
        func_80134388();
        break;
    case 10:
        func_801341B4();
        break;
    case 12:
        func_80133960();
        break;
    case 14:
        func_80133BDC();
        break;
    case 16:
        D_8013B684 = 0;
    case 0:
        func_80132E38();
        break;
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80135484);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80135624);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8013572C);

s16 func_80135C00(s16 arg0) {
    arg0++;

    if (arg0 == 0x100) {
        arg0 = 0;
    }

    return arg0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80135C2C);
void func_80135C2C();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80135D8C);
void func_80135D8C();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80136010);

void func_801361F8(void) {
    if (D_8013AEEC != 0) {
        func_80136010();
        func_80135C2C();
        func_80135D8C();
        func_80134F50();
        func_80133FCC();
        func_801353A0();
        func_8002A024(0, D_80138F28);
        D_80138F28 = 0;
        func_80131FCC();

        if (D_80139020) {
            func_801324B4(0, 0, 0);
        } else {
            func_801324B4(0, D_8013B668, D_8013B668);
        }
    }
}

void nullsub_10(void) {}