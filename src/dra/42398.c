#include "common.h"
#include "dra.h"

#define DISP_ALL_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_ALL_H
#define DISP_MENU_W 384
#define DISP_MENU_H DISP_ALL_H
#define DISP_UNK2_W 512
#define DISP_UNK2_H DISP_ALL_H

void func_800E2398(s32 arg0);
void func_800FADC0(void);
s32 func_8010E27C(void);
void func_801324B4(s8 s_num, s16 arg1, s16 arg2);
s32 func_80136010(void);
void func_801353A0(void);
void func_800F9808(s32);
void func_801026BC(s32);
void func_8010E390(s32);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2398);
#else
u_long* FntFlush(int id); /* extern */
int FntPrint();           /* extern */
extern /*?*/ s32* D_8006C37C;
extern s32 D_80136300;
extern const char* aO;

void func_800E2398(s32 arg0) {
    s32 temp_v0;

    D_8006C37C = *D_8006C37C;
    FntPrint();
    temp_v0 = D_80136300;
    D_80136300 = temp_v0 + 1;
    if (temp_v0 & 4) {
        FntPrint(&aO); // "\no\n"
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv((DRAWENV*)(D_8006C37C + 1));
    PutDispEnv((DISPENV*)(D_8006C37C + 0x18));
    FntFlush(-1);
}
#endif

void func_800E2438(s32 arg0) {
    while (PadRead(0))
        func_800E2398(arg0);
    while (!PadRead(0))
        func_800E2398(arg0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E249C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2824);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2B00);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E2E98);

void nullsub_8(void) {}

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
    D_8003CB25 = 0;
    D_8003CB26 = 0;
    D_8003CB27 = 0;
    D_80054319 = 0;
    D_8005431A = 0;
    D_8005431B = 0;
}

void func_800E34A4(s8 arg0) {
    D_8003CB25 = arg0;
    D_8003CB26 = arg0;
    D_8003CB27 = arg0;
    D_80054319 = arg0;
    D_8005431A = arg0;
    D_8005431B = arg0;
}

void func_800E34DC(s32 arg0) {
    D_8003CB0E = 0x0014;
    D_8003CB12 = 0x00CF;
    D_80054302 = arg0 == 0 ? 0x0014 : 0x0114;
    D_80054306 = 0x00CF;
    D_80054318 = 1;
    D_8003CB24 = 1;
    func_800E346C();
    D_80054316 = 0;
    D_8003CB22 = 0;
    D_8005436D = 0;
    D_8003CB79 = 0;
}

// Set stage display buffer
void func_800E3574(void) {
    SetDefDrawEnv(&D_8003CB0C.draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(&D_80054300, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&D_8003CB0C.disp, DISP_STAGE_W, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_800E34DC(0);
}

// Set CGI display buffer?
void func_800E3618(s32 width) {
    SetDefDrawEnv(&D_8003CB0C.draw, 0, 0, width, DISP_ALL_H);
    SetDefDrawEnv(&D_80054300, 0, 256, width, DISP_ALL_H);
    SetDefDispEnv(&D_8003CB0C.disp, 0, 256, width, DISP_ALL_H);
    SetDefDispEnv(&D_8005435C, 0, 0, width, DISP_ALL_H);
    func_800E34DC(1);
}

// Set menu display buffer
void func_800E36C8(void) {
    SetDefDrawEnv(&D_8003CB0C.draw, 0, 0, DISP_MENU_W, DISP_MENU_H);
    SetDefDrawEnv(&D_80054300, 128, 256, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&D_8003CB0C.disp, 128, 256, DISP_MENU_W, DISP_MENU_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_MENU_W, DISP_MENU_H);
    func_800E34DC(1);
}

void func_800E376C(void) {
    SetDefDrawEnv(&D_8003CB0C.draw, 0, 0, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDrawEnv(&D_80054300, 0, 256, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDispEnv(&D_8003CB0C.disp, 0, 256, DISP_UNK2_W, DISP_UNK2_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_UNK2_W, DISP_UNK2_H);
    D_80054302 = DISP_UNK2_W / 2;
    D_80054306 = DISP_UNK2_H;
    D_8003CB12 = DISP_UNK2_H;
    D_8003CB0E = 0;
    D_80054318 = 1;
    D_8003CB24 = 1;
    func_800E346C();
    D_8005436D = 0;
    D_8003CB79 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E385C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E38CC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", entrypoint_sotn);

void func_800E4124(s32 context) {
    D_8003C734 = context;
    D_80073060 = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E414C);

void ClearBackbuffer(void) { ClearImage(&c_backbufferClear, 0, 0, 0); }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E451C);

void func_800E493C(void) {
    u32 var_a0;

    if (g_SettingsSoundMode == 0) { // Stereo / Mono ?
        var_a0 = 6;
        PlaySfx(var_a0);
    } else {
        var_a0 = 5;
        PlaySfx(var_a0);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E4970);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E6300);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E6358);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E6FD4);

void nullsub_9(void) {}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E738C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7458);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E768C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7AEC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7BB8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7D08);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7D4C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E7E08);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E81FC);

void func_800E8D24(void) {
    s8* phi_v1;
    s32 phi_v0;
    s8 a0;

    D_80097496 = 0;
    phi_v1 = &D_80137460;
    a0 = 0x10;
    phi_v0 = 0xF;
    do {
        *phi_v1 = a0;
        phi_v1 += 1;
        phi_v0--;
    } while (phi_v0 >= 0);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E8D54);
void func_800E8D54(void);
// https://decomp.me/scratch/YhofM

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E908C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E912C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E91B0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9208);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E928C);

void func_800E92E4(void) { D_8013B660 = 0; }

void func_800E92F4(void) {
    D_8013B158 = 0;
    D_8013B3D0 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E930C);

typedef struct struct_8013B15C {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ char unk_008[0x274];
} struct_8013B15C; // size = 0x278

extern struct_8013B15C D_8013B15C[];

s32 func_800E9508(s32 arg0) {
    s32 temp = D_8013B15C[arg0].unk_000;

    return temp;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9530);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9610);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9640);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E96E8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E97BC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9804);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9880);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9B18);

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

    var_a1 = D_800A1F18[arg1];

    for (i = 0; i < 384; i++) {
        *arg0 = *var_a1;
        var_a1++;
        arg0++;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800E9C14);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA2B0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA48C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA538);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA5AC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA5E4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA720);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EA7CC);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EAD0C);
#else
void func_800EAD0C(void) {
    func_800EA5E4(4);
    func_800EA5E4(5);
    func_800EA5E4(6);
    func_800EA5E4(7);
    func_800EA5E4(8);
    if (g_CurrentPlayableCharacter == 0) {
        if (g_mapProgramId != PROGRAM_ST0) {
            func_800EA5E4(0x17);
        }
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EAD7C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EAEA4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EAEEC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EAF28);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EAFC8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB03C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB098);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB314);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB4F8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB534);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB6B4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB720);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EB758);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EBB70);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EBBAC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800ECBF8);

typedef struct unkstruct_800ECE2C {
    s32 unk0;
    s32 unk4;
} unkstruct_800ECE2C;

extern s32 D_800730A0;
extern unkstruct_800ECE2C D_800730F4[];

void func_800ECE2C(void) {
    // !FAKE: iterator values are likely wrong
    // TODO: fix once the real struct type is found
    s32 i;

    for (D_800730A0 = 0, i = 90; i >= 0; i -= 6) {
        D_800730F4[i].unk0 = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800ECE58);

INCLUDE_ASM("asm/dra/nonmatchings/42398", SetRoomForegroundLayer);

INCLUDE_ASM("asm/dra/nonmatchings/42398", SetRoomBackgroundLayer);

INCLUDE_ASM("asm/dra/nonmatchings/42398", LoadRoomLayer);

void func_800EDA70(s32* context) {
    s32 i;
    s32 n;

    for (n = 13, i = 0; i < n; i++) {
        *context++ = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800EDA94);

void func_800EDAE4(void) {
    s32 i;
    s32* phi_v1 = &D_800974AC;

    for (i = 15; i >= 0; i--) {
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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F04A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F0578);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F0608);

typedef struct {
    s32 foo[5];
} Unkstruct_800F087C;

extern Unkstruct_800F087C D_800A297C;

s32 func_800F087C(u32 chunkX, u32 chunkY) {
    s32 temp_a0;
    s32 temp_v1;
    Unkstruct_800F087C* phi_s1;
    Unkstruct_800F087C* phi_s0;

    phi_s1 = &D_800A297C;
    phi_s0 = (Unkstruct_800F087C*)((u32*)&D_800A297C + 4);
loop_1:
    temp_v1 = phi_s1->foo[0];
    if (temp_v1 == 0x80)
        return 0;

    if (temp_v1 == chunkX && phi_s0->foo[-3] == chunkY &&
        phi_s0->foo[-2] == g_mapProgramId) {
        temp_a0 = phi_s0->foo[-1];
        if (temp_a0 == 0xFF || func_800FD4C0(temp_a0, 0) == 0)
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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1424);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1770);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F17C8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F180C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1868);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F18C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1954);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F1A3C);

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
    g_mapProgramId = g_mapProgramId ^ 0x20;
    func_800F2120();
    g_mapProgramId = g_mapProgramId ^ 0x20;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2288);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2404);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F24F4);
#else
void func_801042C4(s32);
void func_80105428();
extern s16 D_800733DA;
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
                if (D_800733DA == 0x80) {
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

s32 func_800F27F4(s32 arg0) {
    if (arg0 == 0) {
        if ((D_800973FC == 0) && (D_8006BB00 == 0) && (!(D_8003C708 & 0x60))) {
            D_801375C8 = 1;
            return true;
        } else {
            return false;
        }
    } else {
        D_801375C8 = 8;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F2860);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F298C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F483C);

s32 IsAlucart(void) {
    if (func_800FD7C0(0xA8, 0) && func_800FD7C0(0xA7, 0) &&
        func_800FD7C0(0x59, 2))
        return true;
    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F4994);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F4D38);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F4F48);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F548C)

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", IsOutsideDrawArea);
bool IsOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* context);
#else
bool IsOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* context) {
    s16 scissorX = (s16)context->unk1.x;
    if (scissorX < x1) {
        s16 scissorY = (s16)context->unk1.y;
        if (scissorY < y1 && x0 < (scissorX + (s16)context->unk1.w))
            return (y0 < scissorY + (s16)context->unk1.h) ^ 1;
    }

    return true;
}
#endif

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
    s32 temp_v1;
    s32 r;
    MenuContext* context = &D_8013761C[menuContextIndex * 0x1E];

    if (bColorMode != 0) {
        r = 0x80;
    } else {
        if (g_blinkTimer & 0x20) {
            r = (g_blinkTimer & 0x1F) + 0x40;
        } else {
            r = 0x5F - (g_blinkTimer & 0x1F);
        }
    }
    DrawMenuRect(context, 0x70, (g_menuRelicsCursorIndex * 0xD) + 0x1C, 0x71,
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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F7244);

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
        DrawMenuInt(g_playerMp, 0xA8, 0x44, context);
        DrawMenuChar(0xF, 0xB0, 0x44, context);
        DrawMenuInt(g_playerMpMax, 0xD0, 0x44, context);
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
        DrawMenuInt(g_timeHours, 0x108, 0xC0, context);
        DrawMenuChar(0x1A, 0x110, 0xC0, context);
        func_800F6998(g_timeMinutes, 0x120, 0xC0, context, 2);
        DrawMenuChar(0x1A, 0x128, 0xC0, context);
        func_800F6998(g_timeSeconds, 0x138, 0xC0, context, 2);
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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F86E4);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9690);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F96F4);

void func_800F97DC(void) {
    D_8013794C = &D_8007EFE4;
    D_80137950 = 0x180;
    D_80137954 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9808);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F98AC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F99B8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9D40);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9D88);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9DD0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9E18);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800F9F40);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA034);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA3C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA60C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA7E8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA8C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FA9DC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FAB1C);

typedef struct Unkstruct_80137638 {
    u8 unk0;
    u8 unk1;
    u8 pad2[0x1E - 0x02];
} Unkstruct_80137638; // size = 0x1E

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
    D_80137844 = 0;
    D_80137848 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FAC48);

void func_800FAC98(void) { func_800F9808(2); }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FACB8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FAD34);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FADC0);

void func_800FAE98(void) {
    func_800FADC0();
    D_800978F8 = 0x40;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FAEC4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FAF44);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB004);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB0FC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB160);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB1EC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB23C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FB9BC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FBAC4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FBC24);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD39C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD4C0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD5BC);

s32 func_800FD664(s32 context) {
    s32 phi_a0 = context;
    if (g_mapProgramId & 0x20) {
        phi_a0 <<= 1;
    }
    return phi_a0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FD688);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FDC94);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FE8B4);

void func_800FE8F0(void) {
    if (D_8013B5E8 == 0) {
        D_8013B5E8 = 0x40;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FE914);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FE97C);

// !FAKE:
void func_800FEE6C(void) {
    s32* var_v1;

    var_v1 = &D_80139828;

    do {
        if (*var_v1 != 0) {
            *var_v1 -= 1;
        }
        var_v1++;
    } while ((s32)var_v1 < (s32)&D_80139828[0x10]);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FEEA4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF064);

void func_800FF0A0(s32 context) { D_80139828[context] = 0; }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF0B8);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF60C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF6C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF708);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_800FF7B8);

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
    D_80137990 = 0;
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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010183C);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010189C);
#else
extern u8 D_800A2EE8[];
extern u8 D_800A2EED;
extern u8 D_800A2EF8[];
extern u8 D_800A2EFD;
extern u8 D_800A2F08[];
extern u8 D_800A2F18[];
extern u8 D_800A2F28[];
extern u8 D_800A2F2D;
extern u8 D_800A2F38[];
extern u8 D_800A2F3D;
extern u16 D_800A2F48[];
extern u16 D_800A2F64[];
extern s32 D_8013796C;
extern s32 D_80137970;
extern s32 D_80137998;

void func_8010189C() {
    POLY_GT4* poly;
    s32 i;

    D_8013B5E8 = 0;
    D_80137998 = 0;
    D_8013796C = g_playerHp;
    if (g_mapProgramId == PROGRAM_ST0 || g_CurrentPlayableCharacter != 0) {
        DrawHudRichter();
        return;
    }

    D_80137970 = func_800EDD9C(4U, 14);
    poly = &D_80086FEC[D_80137970];
    i = 0;
    if (poly != NULL) {
        do {
            func_80107360(poly, D_800A2EE8[i], D_800A2EF8[i], D_800A2F28[i],
                          D_800A2F38[i], D_800A2F08[i], D_800A2F18[i]);
            poly->tpage = 0x1F;
            poly->clut = D_800A2F48[i];
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
                poly->p3 = (rand() & 7) + 1;
            }

            poly = poly->tag;
            i++;
        } while (poly != NULL);
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80101A80);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801024DC);

typedef struct Unkstruct_80086FFA {
    /* 0x00*/ u16 unk0;
    /* 0x02 */ char unk2[0x32];
} Unkstruct_80086FFA; // size = 0x34

extern Unkstruct_80086FFA D_80086FFA[];

u16 func_801025F4(void) { return D_80086FFA[D_8013799C].unk0; }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80102628);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801026BC);

void func_801027A4(void) { func_801026BC(0); }

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801027C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801028AC);

// https://decomp.me/scratch/8D47k
// That's either a compiler flag, wrong compiler, or asspsx issue
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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801030B4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80103148);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80103238);

void func_80103EAC(void) {
    D_80137E4C = 0;
    func_800E92F4();
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80103ED4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010427C);

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

    for (pItem = &D_800733D8[startIndex];
         pItem < D_800733D8 + TOTAL_ENTITY_COUNT; pItem++)
        func_80106590(pItem);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80106670);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80106A28);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010715C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801071CC);

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

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80107360);
#else
void func_80107360(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, u8 u,
                   u8 v) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->x3 = x + width;
    poly->v0 = v;
    poly->v1 = v;
    poly->y2 = y + height;
    poly->y3 = y + height;
    poly->u0 = u;
    poly->u1 = u + width;
    poly->u2 = u;
    poly->v2 = v + height;
    poly->u3 = u + width;
    poly->v3 = v + height;
}
#endif

void func_801073C0(void) {
    CdReadyCallback(NULL);
    CdDataCallback(NULL);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801073E8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80107460);

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
    D_800ACC64 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801083F0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80108448);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801092E8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80109328);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801093C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80109594);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80109990);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80109A44);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010A234);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010A3F0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010A4A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", UpdateEntityAlucard);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010BF64);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010BFFC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010C36C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010C9F4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010D010);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010D2C8);

void func_8010D584(s16 context) {
    D_80073404 = context;
    D_80073406 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010D59C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010D800);

void func_8010DA2C(s32* arg0) {
    D_8006C3B8->unk4C = arg0;
    D_8006C3B8->animationFrameDuration = 0;
    D_8006C3B8->animationFrameIndex = 0;
}

void func_8010DA48(s32 arg0) {
    D_8006C3B8->unkAC = arg0;
    D_8006C3B8->animationFrameDuration = 0;
    D_8006C3B8->animationFrameIndex = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DA70);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DB38);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DBFC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DDA0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DF70);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010DFF0);

void func_8010E0A8(void) { D_80073512 = 0; }

void func_8010E0B8(void) {
    D_80073511 = 0;
    D_80073510 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E0D0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E168);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E1EC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E234);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E27C);
#else
s32 func_8010E27C(void) {
    s32 retValue;
    u16* tmp;

    if (D_80072F64 & 2)
        return 0;

    retValue = 1;
    tmp = &D_800733EC;
    if (*tmp == 1) {
        if (D_80072EE8 & 0x2000) {
            *tmp = 0;
            D_80072F6C = 1;
            return -1;
        }
        if (D_80072EE8 & 0x8000) {
            return 1;
        }
    } else {
        if (!(D_80072EE8 & 0x2000)) {
            if (D_80072EE8 & 0x8000) {
                *tmp = 1;
                D_80072F6C = 1;
                return -1;
            }
        }
    }
    return retValue;
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E334);

void func_8010E390(s32 arg0) {
    if (D_8006C3B8->unk14 == 1) {
        arg0 = -arg0;
    }
    D_8006C3B8->accelerationX = arg0;
}

void func_8010E3B8(s32 arg0) {
    if (D_8007340A == 1) {
        arg0 = -arg0;
    }
    D_800733E0 = arg0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E3E0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E42C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E470);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E4D0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E570);
/*?*/ void func_8010E570(/*?*/ s32);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E6AC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E7AC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E83C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E940);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010E9A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EA54);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EADC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EB5C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EC8C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010ED54);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010EDB8);

void func_8010FAF4(void) {
    func_80106590(&D_80073F98);
    D_80072F66 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010FB24);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010FB68);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010FBF4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010FC50);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010FCB8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010FD24);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8010FD88);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80111938);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011197C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801119C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80111CC0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80111D24);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80111DE8);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011203C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801120B4);

void func_80112B64() {
    if (func_8010FDF8(0x4301C) == 0) {
        func_8010E390(0x18000);
        if (func_8010E27C() == 0) {
            func_8010E570(0);
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80112BB0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113148);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801131C4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801139CC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113AAC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113D7C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113E68);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113EE0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80113F7C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011405C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80114DF4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115394);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115BB0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115C50);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115DA0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80115F54);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116208);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116408);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801166A4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011678C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801167D0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116838);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011690C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116994);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80116B0C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801177A0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80117AC0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80117D3C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80117DEC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801182F8);

void func_80118614(void) {
    if (D_8007342A < 0) {
        func_8010E570(0);
    }
}

void func_80118640(void) {
    if (D_8007342A < 0) {
        func_8010E470(0, 0);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118670);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801186EC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011879C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118810);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118894);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118970);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118B18);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118C28);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118C84);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80118D0C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80119588);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80119D3C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80119E78);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80119F70);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011A290);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011A328);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8011B530);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80121F14);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80121F58);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012231C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80123788);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801238CC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80123A60);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80127EAC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80127EF0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80127F40);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80128714);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80128BBC);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CB0C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CB4C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CC30);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CCE4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CED4);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012CFA8);

void func_8012CFF0(void) {
    D_80073406 = 3;
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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8012F83C);

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

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132134);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8013216C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801321FC);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132264);

void func_801324B4(s8 s_num, s16 arg1, s16 arg2) {
    short voll = D_800BD07C[arg1];
    short volr = D_800BD07C[arg2];

    SsSetSerialVol(s_num, voll, volr);
}

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132500);

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

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80132E38);
#else
u16 func_80132E38(void) {
    s32 temp_a1;
    s32 phi_a1 = 0;
    u16* phi_v1 = &D_80139868;
    u16* phi_a0 = &D_80139868 + 1;

    do {
        temp_a1 = phi_a1 + 1;
        *phi_v1 = *phi_a0;
        phi_a0++;
        phi_v1++;
        phi_a1 = temp_a1;
    } while (temp_a1 < 0xFF);

    return --D_801396F4;
}
#endif

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
void func_80133FCC();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134104);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8013415C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801341B4);
void func_801341B4();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134388);
void func_80134388();

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134508);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134564);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_801345C0);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_8013461C);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134678);

INCLUDE_ASM("asm/dra/nonmatchings/42398", func_80134714);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/42398", PlaySfx);
#else
void PlaySfx(s32 arg0) {
    if (D_8013AEEC == 0)
        return;

    if (((arg0 - 0x601) & 0xFFFF) < 0x2E0) {
        s16 playerLevel = D_80139000;
        s32 temp_v0 = playerLevel * 3;
        *(&D_801390DC + temp_v0) = arg0 - 0x600;
        D_80139000 = ++playerLevel;
        *(&D_801390DE + temp_v0) = 0xFFFF;
        *(&D_801390E0 + temp_v0) = 0;
        if (playerLevel == 0x100) {
            D_80139000 = 0;
        }
    } else {
        s16 temp_v0_2;
        s16 temp_v0_3;
        if (arg0 < 0x85) {
            if (arg0 < 0x80) {
                if (arg0 < 0x12 && arg0 >= 0x10) {
                    D_8013980C = 1;
                }
            } else {
                D_8013B61C = 1;
            }
        } else if (arg0 < 0x95 && arg0 >= 0x90) {
            D_8013B61C = 1;
        }

        temp_v0_2 = D_80139A70;
        temp_v0_3 = temp_v0_2 + 1;
        D_80139A70 = temp_v0_3;
        D_8013B3E8[temp_v0_2] = arg0;
        if (temp_v0_3 == 0x100) {
            D_80139A70 = 0;
        }
    }
}
#endif

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
void func_801353A0() {
    if (D_801396F4 == 0)
        return;

    switch (D_80139868) {
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
