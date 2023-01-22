/*
 * File: 2C048.c
 * Overlay: SEL
 * Description: Title & loading screen
 */

#include "stage.h"
#include <psxsdk/romio.h>

#define DISP_W 512
#define DISP_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_H

typedef struct {
    u32 unk0;
    u32 unk4;
} Unkstruct_801ACBE4;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8; // D_801D6A54
    s32* unkC;
    s32 unk10;
    s32 unk14; // D_801D6A60
    s16 unk18; // D_801D6A64
    s16 unk1A; // D_801D6A66
    s16 unk1C; // D_801D6A68
    s16 unk1E; // D_801D6A6A
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s32 unk28; // D_801D6A74
    s16 unk2C; // D_801D6A78
    s16 unk2E; // D_801D6A7A
    s16 unk30; // D_801D6A7C
    s16 unk32; // D_801D6A7E
    s32 unk34; // D_801D6A80
} Unkstruct_801B9B7C;

typedef struct {
    s32 unk00[16];
    s32 unk10[16];
    s32 unk20[32];
} Unkstruct_801BA498;

typedef struct {
    /* 0x000 */ s32 unk0;
    char pad4[0x3C - 0x4];
    /* 0x03C */ s32 unk3C;
    char pad40[0x78 - 0x40];
    /* 0x078 */ s32 areaId;
    char pad7C[0xB4 - 0x7C];
    /* 0x0B4 */ s32 unkB4;
    char padB8[0xF0 - 0xB8];
    /* 0x0F0 */ s32 level;
    char padF4[0x12C - 0xF4];
    /* 0x12C */ s32 money;
    char pad130[0x168 - 0x130];
    /* 0x168 */ s32 roomCount;
    char pad16C[0x1A4 - 0x16C];
    /* 0x1A4 */ s32 timerHours;
    char pad1A8[0x1E0 - 0x1A8];
    /* 0x1E0 */ s32 timerSeconds;
    char pad1E4[0x21C - 0x1E4];
    /* 0x21C */ s32 timerMinutes;
    char pad220[0x258 - 0x220];
    /* 0x258 */ s32 clearFlag;
    char pad25C[0x294 - 0x25C];
    /* 0x294 */ s32 player;
    char pad298[0x2D0 - 0x298];
    /* 0x2D0 */ char name[8];
    char pad2D8[0x3A8 - 0x2D8];
} SaveSummary; /* size=0x3A8 */

extern u8* D_80180128[];
extern u8* D_8018012C[];
extern u8* D_801803BC;
extern u8* D_801803C0;
extern s32 D_80180454[];
extern u8 D_8018046C[0x20 * 3];
extern u8 D_80180504[];
extern u8 D_80180528[];
extern /*?*/ s32 D_801808DC[];
extern u16 D_801808E4[];
extern u32 D_801822E4[];
extern RECT D_801825A4;
extern s32 D_801962F4;
extern s32 D_801962F8[16];
extern s32 D_80196338[16];
extern s32 D_80196378;
extern s32 D_8019637C[32];
extern s32* D_801963FC;
extern s32* D_80196400;
extern s32* D_80196404;
extern s32* D_80196408;
extern s32* D_8019640C;
extern s32* D_80196410;
extern s32* D_8019642C;
extern s32* D_80196430;
extern s32* D_80196434;
extern s32 D_801A75A0[];
extern s32 D_801A75C0[];
extern const char D_801A7AF8[];   // rstep:%d,%d
extern const char D_801A7B08[];   // retry:%d
extern const char D_801A7D78[];   // "bu%1d%1d:"
extern const char D_801A7D84[];   // "bu%1d%1d:%s"
extern const char D_801A802C[18]; // "BASLUS-00067DRAX00"
extern const char D_801ABF9C[];   // "MDEC_rest:bad option(%d)\n"
extern const char D_801ABFB8[];   // MDEC_in_sync
extern const char D_801ABFC8[];   // MDEC_out_sync
extern const char D_801ABFD8[];   // DMA=(%d,%d), ADDR=(0x%08x->0x%08x)
extern const char D_801AC000[];   // FIFO
extern const char D_801AC038[];   // "%s timeout:\n"
extern s32 D_801BAF10;
extern Unkstruct_801ACBE4 D_801BAF18[];
extern u8* D_801BAFD0;
extern s32 D_801BAFD4;
extern s32 D_801BAFD8;
extern s32 D_801BAFDC;
extern s32 D_801BAFE0;
extern u32 D_801BAFE4;
extern s32 D_801BAFE8;
extern s32 g_memCardRStep;
extern s32 g_memCardRStepSub; // rstep sub
extern s32 g_memCardRetryCount;
extern s32 D_801BAFFC;
extern s32 D_801BB000;
extern s32 D_801BB004;
extern s32 D_801BB008;
extern s32 D_801BB00C;
extern s32 D_801BC2F8;
extern s32 D_801BC2FC;
extern s32 D_801BC340;
extern s32 D_801BC344;
extern s16 D_801BC35A;
extern u16 D_801BC35C;
extern s16 D_801BC35E;
extern s16 D_801BC360;
extern s16 D_801BC362;
extern s16 D_801BC366;
extern s8 D_801BC36A;
extern s8 D_801BC36B;
extern s16 D_801BC390;
extern s16 D_801BC392;
extern s32 D_801BC394;
extern u32 D_801BC398[];
extern s32 D_801BC3D4[];
extern s32 D_801BC3D8;
extern s32 D_801BC3DC;
extern s32 D_801BC3E0;
extern s32 D_801BC650;
extern s32 D_801BC654[];
extern s32 D_801BC8C8;
extern s32 D_801BC8E0[];
extern SaveSummary D_801BC91C[15];
extern s32* D_801BC958[];
extern s32 D_801BCC84;
extern s32 D_801BD02C;
extern u32 D_801BD038; // StSetStream mode
extern s32 D_801BD044[];
extern s32 D_801D6B04;
extern s32 D_801D6B08;
extern s32 D_801D6B0C;
extern s32 D_801D6B20;

void func_801B1ED0();
void func_801B3A54(s32, s32);
s32 func_801B3A94(s32);
s32 _card_event_x();
void func_801B84F0();
s32 func_801B8A8C(s32, s32);
void MDEC_rest(s32 option);
void func_801BA880();
void MDEC_in_sync();
void MDEC_out_sync();
void MDEC_print_error(const char* funcName);
void func_801BABA4(s32, s32);

void func_801AC048(void) {
    D_801D6B0C = 1;
    D_801D6B08 = 0;
    D_801BC3E0 = 0;
    D_801D6B04 = 0;
    D_801BC3D8 = 0;
    D_801BC3DC = 0;
}

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AC084);
#else
// Those arrays are weird. They do not store s32 but they are used as such.
extern s32 D_80180068[];
extern s32 D_80180088[];
extern s32 D_801800A8[];
extern s32 D_801800C8[];
extern s32 D_801800E8[];
extern s32 D_80180108[];

void func_801AC084(s32 arg0, s32 ypos) {
    POLY_GT4* poly = &D_80086FEC[D_801BAF18[arg0].unk0];
    s32 i;

    for (i = 0; i < 8; i++) {
        poly->x0 = D_80180068[i] + 0x68;
        poly->y0 = D_80180088[i] + 0x58 + ypos;
        poly->u0 = D_801800A8[i];
        poly->v0 = D_801800C8[i];
        poly->u1 = D_801800E8[i];
        poly->tpage = 0xC;
        poly->clut = 0x200;
        poly->pad2 = 0x11;
        poly->pad3 = 8;
        poly->v1 = D_80180108[i];
        poly = (POLY_GT4*)poly->tag;
    }
}
#endif

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AC174);

void func_801ACBE4(s32 arg0, u16 arg1) {
    POLY_GT4* poly = &D_80086FEC[D_801BAF18[arg0].unk0];
    while (poly != NULL) {
        poly->pad3 = arg1;
        poly = (POLY_GT4*)poly->tag;
    }
}

void func_801ACC3C(void) {
    s32 i;
    for (i = 0; i < 21; i++) {
        func_801ACBE4(i, 8);
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACC7C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACDFC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACEC0);

void func_801ACF7C(void) {
    func_801B1ED0();
    func_801B25D4(D_801A75A0, 0);
    func_801B25D4(D_801A75C0, 1);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACFBC);

void PrintFileSelectPlaceName(s32 arg0, s32 arg1, s32 y) {
    const s32 x = 160;
    const s32 row1y = 0;
    const s32 row2y = 8;
    const s32 tge = 1;
    volatile u32 pad; // !FAKE:

    s32* new_var2 = &D_801BC958[arg0 * 0xEA];
    s32 idx = new_var2[arg1] * 2;
    func_801B2AFC(D_80180128[idx], x, y + row1y, tge);
    func_801B2AFC(D_8018012C[idx], x, y + row2y, tge);
}

void func_801AD1D0(void) {
    func_801B2AFC(D_801803BC, 52, 196, 1);
    func_801B2AFC(D_801803C0, 52, 212, 1);
}

void func_801AD218(void) {
    func_801B2AFC(D_801803C0, 52, 196, 1);
    func_801B2AFC(D_801803BC, 52, 212, 1);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD260);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD490);

void func_801AD590(void) {
    if (D_80097494 & 0x6000) {
        g_api.PlaySfx(0x67D);
        if (++D_801D6B0C == 5) {
            D_801D6B0C = 1;
        }
    }
    if (D_80097494 & 0x9000) {
        g_api.PlaySfx(0x67D);
        if (--D_801D6B0C == 0) {
            D_801D6B0C = 4;
        }
    }
    func_801B2608(D_80180454[D_801D6B0C], 9);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD66C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD78C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD968);

void func_801ADC3C(void) {
    s32* new_var = &D_801BCC84;
    if (*new_var >= 0 || D_801BD02C >= 0) {
        u16* tmp = &D_80097496;
        if (*tmp & 0x2000) {
            g_api.PlaySfx(0x67B);
            D_801BC3D8 = (D_801BC3D8 + 1) % 6;
        }
        if (*tmp & 0x4000) {
            g_api.PlaySfx(0x67B);
            D_801BC3DC = (D_801BC3DC + 4) % 5;
        }
        if (*tmp & 0x8000) {
            g_api.PlaySfx(0x67B);
            D_801BC3D8 = (D_801BC3D8 + 5) % 6;
        }
        if (*tmp & 0x1000) {
            g_api.PlaySfx(0x67B);
            D_801BC3DC = (D_801BC3DC + 1) % 5;
        }
        if (*new_var > 0 && D_801BD02C > 0 && D_80097494 & 0xF) {
            g_api.PlaySfx(0x67D);
            D_801BC3D8 = (D_801BC3D8 + 3) % 6;
        }
        if (D_801BCC84 < 0) {
            D_801BC3D8 = (D_801BC3D8 % 3) + 3;
        }
        if (D_801BD02C < 0) {
            D_801BC3D8 %= 3;
        }
        D_801D6B04 =
            (D_801BC3D8 % 3) + (D_801BC3DC * 3) + ((D_801BC3D8 / 3) * 0xF);
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ADF94);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AE6D0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AE9A8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AEA8C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AEB74);

void func_801AECA0(void) {
    s32 i = 0;
    s32 x;
    s32 y = 0x100;
    s32 w = 0x10;
    s32 h = 0x30;
    s32 xnext = 0x180;
    u32* pix = D_801822E4;

    for (; i < 0x10; i++) {
        s32 tmp = 4;
        x = xnext;
        xnext += tmp;
        LoadTPage((PixPattern*)*pix++, 0, 0, x, y, w, tmp = 0x30);
        x = xnext;
    }

    g_api.func_800EA5E4(0x8004);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AED48);

void func_801AEE74(void) {
    s32 i = 0;
    s32* var_v0 = D_801BC8E0;
    s32* var_a1 = var_v0 + 0xEA;
    s32* var_a0 = var_v0;

    for (; i < 0xF; i++) {
        if (*var_a0 >= 0 || *var_a1 >= 0)
            break;
        var_a1++;
        var_a0++;
    }

    if (i == 0xF) {
        D_801BAF10 = 1;
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AEED8);

void func_801B17C8(void) {
    switch (D_800978F8) {
    case 0:
        if (D_80097924 == -1 || D_8006C378 == -1) {
            D_80073060++;
        } else {
            D_800978C4 = 0;
            D_800978F8++;
        }
        break;
    case 1:
        func_801B3A54(D_80097924, D_8006C378);
        D_800978F8++;
        break;
    case 2:
        D_800978C4 = 0;
        if (func_801B3A94(1) != 0) {
            D_800978C4 = 1;
            D_80073060++;
        }
        break;
    }
}

void func_801B18CC(s32 arg0) {
    D_8003C734 = arg0;
    D_80073060 = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_801B18F4(void) { ClearImage(&D_801825A4, 0, 0, 0); }

void func_801B1924(void) {
    D_8003CB08.buf.draw.r0 = 0;
    D_8003CB08.buf.draw.g0 = 0;
    D_8003CB08.buf.draw.b0 = 0;
    D_800542FC.buf.draw.r0 = 0;
    D_800542FC.buf.draw.g0 = 0;
    D_800542FC.buf.draw.b0 = 0;
}

void func_801B195C(s32 arg0) {
    D_8003CB08.buf.draw.clip.y = 0x14;
    D_8003CB08.buf.draw.clip.h = 0xCF;
    if (arg0 == 0) {
        D_800542FC.buf.draw.clip.y = 0x14;
    } else {
        D_800542FC.buf.draw.clip.y = 0x114;
    }
    D_800542FC.buf.draw.clip.h = 0xCF;
    D_800542FC.buf.draw.isbg = 1;
    D_8003CB08.buf.draw.isbg = 1;
    func_801B1924();
    D_800542FC.buf.draw.dtd = 0;
    D_8003CB08.buf.draw.dtd = 0;
    D_800542FC.buf.disp.isrgb24 = 0;
    D_8003CB08.buf.disp.isrgb24 = 0;
}

void func_801B19F4(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, DISP_STAGE_W, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, DISP_STAGE_W, 0, DISP_STAGE_W,
                  DISP_STAGE_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_801B195C(0);
}

void func_801B1A98(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, DISP_W, DISP_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, 0, 256, DISP_W, DISP_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, 0, 256, DISP_W, DISP_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_W, DISP_H);
    D_800542FC.buf.draw.clip.y = DISP_W / 2;
    D_800542FC.buf.draw.clip.h = DISP_H;
    D_8003CB08.buf.draw.clip.h = DISP_H;
    D_8003CB08.buf.draw.clip.y = 0;
    D_800542FC.buf.draw.isbg = 1;
    D_8003CB08.buf.draw.isbg = 1;
    func_801B1924();
    D_800542FC.buf.disp.isrgb24 = 0;
    D_8003CB08.buf.disp.isrgb24 = 0;
}

void func_801B1B88(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, 384, DISP_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, 0, 256, 384, DISP_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, 0, 256, 384, DISP_H);
    SetDefDispEnv(&D_8005435C, 0, 0, 384, DISP_H);
    D_800542FC.buf.draw.clip.y = 256;
    D_800542FC.buf.draw.clip.h = DISP_H;
    D_8003CB08.buf.draw.clip.h = DISP_H;
    D_8003CB08.buf.draw.clip.y = 0;
    D_800542FC.buf.draw.isbg = 1;
    D_8003CB08.buf.draw.isbg = 1;
    func_801B1924();
    D_800542FC.buf.disp.isrgb24 = 0;
    D_8003CB08.buf.disp.isrgb24 = 0;
}

void func_801B1C78(POLY_GT4* poly, u8 colorIntensity, s32 vertexIndex) {
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

void func_801B1CFC(POLY_GT4* poly, u8 colorIntensity) {
    func_801B1C78(poly, colorIntensity, 0);
    func_801B1C78(poly, colorIntensity, 1);
    func_801B1C78(poly, colorIntensity, 2);
    func_801B1C78(poly, colorIntensity, 3);
}

void func_801B1D68(POLY_GT4* poly) { func_801B1CFC(poly, 0); }

void func_801B1D88(POLY_GT4* arg0) { func_801B1CFC(arg0, 0x80); }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1DA8);

void func_801B1ED0(void) {
    s32 var_v1 = 0xF;
    s32* var_v0 = D_801BC3D4;

    do {
        *var_v0-- = 0;
    } while (--var_v1 >= 0);
}

u8 func_801B1EF4(u16 arg0) {
    if (arg0 & 0x80) {
        return func_801B1EF4((arg0 & 0x7F) + 3);
    }
    return (arg0 * 0x10) & 0xF0;
}

void func_801B1F34(void) { D_801BAFD0 = &D_80080FE4; }

void func_801B1F4C(s32 arg0) {
    const s32 count = 0x200;
    PixPattern* pixPatterns;
    s32 i;

    D_801BC398[arg0] = 0;
    arg0 = func_801B1EF4((u8)arg0);
    pixPatterns = D_801BAFD0;
    for (i = 0; i < count * (s32)sizeof(PixPattern); i++) {
        *D_801BAFD0++ = 0;
    }

    LoadTPage(pixPatterns, 0, 0, 0x180, arg0, 0x100, 0x10);
}

void func_801B1FD8(u8* arg0, s32 arg1);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1FD8);

void func_801B2108(s32, s32);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2108);

void func_801B248C(s32 arg0, s32 arg1) {
    if (D_801BC398[arg1] != arg0) {
        func_801B1F4C(arg1);
        D_801BC398[arg1] = arg0;
        func_801B1FD8((u8*)arg0, arg1);
    }
}

void func_801B24F8(s32 arg0, s32 arg1) {
    if (D_801BC398[arg1] != arg0) {
        func_801B1F4C(arg1);
        D_801BC398[arg1] = (u32)arg0;
        func_801B2108(arg0, arg1);
    }
}

void func_801B2564(s32 arg0, s32 arg1) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B248C(arg0, arg1);
}

void func_801B259C(s32 arg0, s32 arg1) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B24F8(arg0, arg1);
}

void func_801B25D4(s32 arg0, s32 arg1) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B248C(arg0, arg1);
}

void func_801B2608(s32 arg0, s32 arg1) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B24F8(arg0, arg1);
}

void func_801B263C(u8* arg0, s32 arg1) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B1FD8(arg0, arg1);
}

void func_801B2670(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->x3 = x + width;
    poly->y2 = y + height;
    poly->y3 = y + height;
}

void func_801B26A0(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u,
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

extern RECT D_80182584;

void func_801B2700(s32 arg0, s32 arg1);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2700);

void func_801B27A8(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 clut, s32 arg7,
                   s32 tge, s32 c);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B27A8);

void func_801B28D4(u8* str, s32 x, s32 y, s32 tge) {
    const int w = 12;
    const int h = 16;
    u8 ch;

loop_1:
    ch = *str++;
    if (ch != 0xFF) {
        s32 u = (ch & 0xF) * w;
        s32 v = ch & 0xF0;
        func_801B27A8(x, y, w, h, u, v, 0x1A1, 6, tge, 0x40);
        x += w;
        goto loop_1;
    }
}

s32 func_801B2984(u32 arg0) {
    s32 i;
    for (i = 0, arg0 &= 0xFF; i < 0x20; i++) {
        if (D_8018046C[i * 3] == arg0)
            return i;
    }
    return 0x20;
}

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B29C0);
#else
extern u8 D_8018046D[];

void func_801B29C0(u8* str, s32 x, s32 y, s32 tga) {
    u8 ch;
    u8* new_var2 = D_8018046D;
    u8* new_var = D_8018046D + 1;
    do {
        do {
        loop_1:
            ch = *(str++);
        } while (0);
        if (ch != 0) {
            s32 temp_v1 = func_801B2984(ch) * 3;
            func_801B27A8(x, y, 16, 16, new_var[temp_v1], new_var2[temp_v1],
                          0x200, 12, tga, 0x40);
            x += 16;
            goto loop_1;
        }
    } while (0);
}
#endif

void func_801B2A9C(s32 img, s32 x, s32 y, s32 tge) {
    func_801B27A8(x, y, 8, 8, (img & 0xF) * 8, (img & 0xF0) / 2, 0x196, 0x1E,
                  tge, 0x80);
}

void func_801B2AFC(u8* imgs, s32 x, s32 y, s32 tge) {
    while (true) {
        if (*imgs == 0xFF)
            break;
        func_801B2A9C(*imgs, x, y, tge);
        x += 8;
        imgs++;
    }
}

void func_801B2B78(s32 icon, s32 x, s32 y, s32 tge) {
    func_801B27A8(x, y, 8, 8, icon * 8 + 176, 120, 0x200, 0xC, tge, 0x40);
}

void func_801B2BD4(s32 digit, s32 x, s32 y, s32 tge) {
    do {
        func_801B2B78(digit % 10, x, y, tge);
        digit /= 10;
        x -= 8;
    } while (digit != 0);
}

void func_801B2C70(s32 arg0, s32 x, s32 y, s32 tge) {
    func_801B2B78(arg0 % 10, x, y, tge);
    func_801B2B78(arg0 / 10, x - 8, y, tge);
}

void func_801B2CF8(POLY_GT4* poly) {
    u32* data = poly;
    s32 n = sizeof(POLY_GT4) / sizeof(*data);
    s32 i;

    for (i = 0; i < n; i++) {
        *data++ = 0;
    }
}

void func_801B2D1C(void) {
    s32 i;
    POLY_GT4* poly;

    for (i = 0, poly = D_80086FEC; i < 0x500; i++) {
        func_801B2CF8((s32*)poly);
        setcode(poly, 0);
        poly++;
    }
}

void func_801B2D6C(void) {
    func_801B84F0();
    D_801BAFDC = 0;
    D_801BAFE0 = 0;
    D_801BAFE4 = 0;
    D_801BAFE8 = 0;
}

s32 func_801B2DAC(void) { return D_801BAFE4 < 2 || D_801BAFE4 == 2; }

void func_801B2DDC(void) {}

void func_801B2DE4(void) {}

void func_801B2DEC(void) {}

void func_801B2DF4(void) {
    if (func_801B2DAC() != 0) {
        D_801BAFDC = func_801B8A8C(D_801BAFE8, 0);
        if (D_801BAFDC != 0) {
            D_801BAFE0 = D_801BAFDC;
        }
    }

    func_801B2DDC();
    func_801B2DE4();
    func_801B2DEC();
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2E5C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2F50);

void func_801B3120(void) {
    s32* var_a0;
    s32* var_v0;
    s32* var_v1;
    s32 i;
    s32 n;

    g_memCardRStep = 0;
    i = 0;
    n = -1;
    var_v0 = D_801BC8E0;
    var_a0 = var_v0 + 0xEA;
    var_v1 = var_v0;
    for (; i < 0xF; i++) {
        *var_v1 = n;
        *var_a0 = n;
        var_a0++;
        var_v1++;
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3164);

void func_801B367C(s32 arg0) {
    g_memCardRStep = 0;
    g_memCardRStepSub = arg0;
}

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3694);
#else
s32 func_801B3694(void) {
    char saveFile[0x20];
    s32 nCardSlot;
    s32 temp_v0;
    SaveSummary* temp_a1;
    FntPrint(D_801A7AF8, g_memCardRStep, g_memCardRStepSub);
    FntPrint(D_801A7B08, g_memCardRetryCount);
    nCardSlot = g_memCardRStepSub / 15;
    nCardSlot += g_memCardRStepSub % 15;
    temp_a1 = &D_801BC91C[nCardSlot];
    switch (g_memCardRStep) {
    case 0:
        func_801B84F0();
        g_memCardRetryCount = 10;
        g_memCardRStep = 3;
        break;

    case 3:
        func_801B9698(saveFile, temp_a1);
        if (func_801B884C(nCardSlot, 0, saveFile, &D_8007EFE4, 1) != 0) {
            g_memCardRetryCount--;
            if (g_memCardRetryCount == (-1)) {
                temp_v0 = -1;
            } else {
                return 0;
            }
            return temp_v0;
        }
        g_memCardRStep++;
        break;

    case 4:
        temp_v0 = func_801B8A10(nCardSlot);
        if (temp_v0 != 0) {
            if (temp_v0 == -3) {
                g_memCardRetryCount--;
                if (g_memCardRetryCount == -1) {
                    return -1;
                } else {
                    g_memCardRStep--;
                    do {
                        return 0;
                    } while (0);
                }
            }
            if (LoadSaveData((SaveData*)(&D_8007EFE4)) < 0) {
                return -2;
            } else {
                return 1;
            }
        }
        break;
    }

    temp_v0 = 0;
    return temp_v0;
}
#endif

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B38B4);

void func_801B3A54(s32 arg0, s32 arg1) {
    char pad[0x20];

    g_memCardRStep = 0;
    D_801BAFFC = arg0;
    D_801BB000 = arg1;
    D_801BB004 = arg0;
    D_801BB00C = arg1;
    D_801BB008 = arg1;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3A94);

void func_801B3E14(s32 arg0) {
    g_memCardRStep = 0;
    g_memCardRStepSub = arg0;
}

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3E2C);
#else
s32 func_801B3E2C(void) {
    char saveFile[0x20];
    s32 nCardSlot;
    s32 nCardBlock;
    SaveSummary* save;
    s32 blockId;

    nCardSlot = g_memCardRStepSub / 15;
    save = &D_801BC91C[nCardSlot + (g_memCardRStepSub % 15)];
    blockId = save->unk0;
    switch (g_memCardRStep) {
    case 0:
        func_801B84F0();
        g_memCardRetryCount = 10;
        g_memCardRStep++;
        break;
    case 1:
        func_801B9698(saveFile, blockId);
        if (func_801B89C8(nCardSlot, 0, saveFile) != 0) {
            g_memCardRetryCount--;
            if (g_memCardRetryCount == -1) {
                return -1;
            }
        } else {
            // D_801BC91C[temp_s2 + nCardBlock - 0x3C] = -3;
            return 1;
        }
    }
    return 0;
}
#endif

void func_801B3F7C(s32 arg0) {
    g_memCardRStep = 0;
    g_memCardRStepSub = arg0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3F94);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4048);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B410C);

void func_801B4B30(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_api.FreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void func_801B4B9C(Entity* entity, s16 step) {
    entity->step = step;
    entity->unk2E = 0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

s32 AnimateEntity(const u8 frames[], Entity* entity) {
    s32 flag = 0;
    u16 currentFrameIndex = entity->animationFrameIndex * 2;
    u8* currentFrame = frames + currentFrameIndex;

    if (entity->animationFrameDuration == 0) {
        if (currentFrame[0] > 0) {
            flag = 0x80;
            if (currentFrame[0] == 0xFF) {
                return false;
            }

            entity->animationFrameDuration = *currentFrame++;
            entity->animationFrame = *currentFrame++;
            entity->animationFrameIndex++;
        } else {
            currentFrame = frames;
            entity->animationFrameIndex = 0;
            entity->animationFrameDuration = 0;
            entity->animationFrameDuration = *currentFrame++;
            entity->animationFrame = *currentFrame++;
            entity->animationFrameIndex++;
            return false;
        }
    }

    entity->animationFrameDuration = entity->animationFrameDuration - 1;
    entity->animationFrame = currentFrame[-1];
    flag |= true;

    return (u8)flag;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4C68);

void func_801B4D78(void) {
    Entity* e = &g_EntityArray[3];
    if (e->step == 0) {
        e->animationSet = -0x7FFF;
        e->animationFrame = 1;
        e->palette = 0x200;
        e->unk80.modeS32 = 0x5C0000;
        e->posY.i.hi = 0xD0;
        e->zPriority = 0x80;
        e->step = 1;
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4DE0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4FFC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B519C);

void func_801B5350(void) {
    Entity* entity = &g_EntityArray[5];
    switch (entity->step) {
    case 0:
        entity->animationSet = 1;
        entity->animationFrame = 0x8E;
        entity->unk80.modeS32 = 0x800000;
        entity->posY.i.hi = 0x9F;
        entity->zPriority = 0xC0;
        entity->unk5A = 0;
        entity->palette = 0x8100;
        entity->step = 1;
        break;
    case 1:
        entity->animationFrame = 0x8E;
        break;
    case 2:
        if (!(AnimateEntity(D_80180528, entity) & 0xFF)) {
            func_801B4B9C(entity, 3);
        }
        entity->unk80.modeS32 += 0xFFFE8000;
        break;
    case 3:
        AnimateEntity(D_80180504, entity);
        entity->unk80.modeS32 += 0xFFFE8000;
        if (entity->unk80.modeS16.unk2 < 0x40) {
            entity->step = 0xFF;
        }
        break;
    }
}

void func_801B54C8(void) {
    Entity* e = &g_EntityArray[7];
    if (e->step == 0) {
        e->animationSet = -0x7FFE;
        e->animationFrame = 0x26;
        e->facing = 1;
        e->unk5A = 0xF;
        e->unk80.modeS32 = 0x780000;
        e->posY.i.hi = 0x9E;
        e->zPriority = 0xC0;
        e->palette = 0x8210;
        e->step = 1;
    }
}

void func_801B5548(void) {
    Entity* e = &g_EntityArray[7];
    if (e->step == 0) {
        e->animationSet = -0x7FFE;
        e->animationFrame = 7;
        e->unk5A = 0xF;
        e->unk80.modeS32 = 0x780000;
        e->posY.i.hi = 0x9E;
        e->zPriority = 0xC0;
        e->palette = 0x8210;
        e->facing = 0;
        e->step = 1;
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B55C8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B585C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B5A7C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B60D4);

void func_801B642C(void) {
    D_801BC360 = 2;
    D_801BC35E = 2;
    D_801BC362 = 0;
    D_801BC366 = 0;
    D_801BC36A = 0;
    D_801BC36B = 8;
    D_801BC35A = D_801BC35C + 0x14;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B6480);

void func_801B6648(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B66A4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B675C);

void func_801B68E0(s32 arg0) {
    D_801BC394 = arg0 + 0x100000;
    D_801BC392 = 0;
    D_801BC390 = 1;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B690C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B69F8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B76F0);

void func_801B786C(s16 arg0) {
    RECT rect;
    rect.x = 0x200;
    rect.y = arg0 * 16;
    rect.w = 0x80;
    rect.h = 0x10;

    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B78BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B79D4);

void func_801B80F0(void) {
    EnterCriticalSection();
    D_80073068 = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_8007306C = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_80073070 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80073078 = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    D_8007EFD8 = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_8007EFDC = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_8007EFE0 = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80086FE4 = OpenEvent(HwCARD, EvSpNEW, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(D_80073068);
    EnableEvent(D_8007306C);
    EnableEvent(D_80073070);
    EnableEvent(D_80073078);
    EnableEvent(D_8007EFD8);
    EnableEvent(D_8007EFDC);
    EnableEvent(D_8007EFE0);
    EnableEvent(D_80086FE4);
}

s32 _peek_event_with_retry(void) {
    if (TestEvent(D_80073068) == 1) {
        return 1;
    } else if (TestEvent(D_8007306C) == 1) {
        return 2;
    } else if (TestEvent(D_80073070) == 1) {
        return 3;
    } else if (TestEvent(D_80073078) == 1) {
        return 4;
    } else if (D_801BC2F8-- < 0) {
        return 2;
    }
    return 0;
}

s32 _peek_event(void) {
    if (TestEvent(D_80073068) == 1) {
        return 1;
    } else if (TestEvent(D_8007306C) == 1) {
        return 2;
    } else if (TestEvent(D_80073070) == 1) {
        return 3;
    } else if (TestEvent(D_80073078) == 1) {
        return 4;
    }
    return 0;
}

void _clear_event(void) {
    TestEvent(D_80073068);
    TestEvent(D_8007306C);
    TestEvent(D_80073070);
    TestEvent(D_80073078);
}

s32 _card_event_x(void) {
    while (1) {
        if (TestEvent(D_8007EFD8) == 1) {
            return 1;
        } else if (TestEvent((u32)D_8007EFDC) == 1) {
            return 2;
        } else if (TestEvent((u32)D_8007EFE0) == 1) {
            return 3;
        } else if (TestEvent((u32)D_80086FE4) == 1) {
            return 4;
        }
    }
}

void _clear_event_x(void) {
    TestEvent(D_8007EFD8);
    TestEvent(D_8007EFDC);
    TestEvent(D_8007EFE0);
    TestEvent(D_80086FE4);
}

void func_801B84F0(void) { D_801D6B20 = 0; }

void func_801B8500(void) {
    D_801BC650 = 0;
    D_801BC8C8 = 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8518);

s32 func_801B8714(s32 arg0) { return D_801BC654[arg0 * 0x9E]; }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B873C);

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B881C);
#else
extern volatile u8 D_801BC658[];
u8 func_801B881C(s32 arg0, s32 arg1) {
    s32 idx = arg0 * 0x9E * 4;
    return D_801BC658[idx + arg1];
}
#endif

s32 func_801B884C(s32 cardSlot, s32 cardSubSlot, const char* saveFile,
                  void* saveData, s32 saveLen) {
    char savePath[32];
    s32 fd;
    s32 actualSaveLen;

    sprintf(savePath, D_801A7D84, cardSlot, cardSubSlot, saveFile);
    if (saveLen == 0) {
        actualSaveLen = 0x2B8;
    } else {
        actualSaveLen = saveLen * 0x2000;
    }

    fd = open(savePath, O_RDONLY | O_NOWAIT);
    if (fd == -1) {
        return -1;
    }

    D_801BC2FC = fd;
    _clear_event();
    read(fd, saveData, actualSaveLen);
    return 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B88F4);

s32 func_801B89C8(s32 cardSlot, s32 cardBlock, const char* path) {
    char buf[0x20];
    sprintf(buf, D_801A7D84, cardSlot, cardBlock, path);
    return -(erase(buf) == 0);
}

s32 func_801B8A10(s32 nCardSlot) {
    s32 unk = _peek_event();

    if (unk == 0) {
        return 0;
    }

    close(D_801BC2FC);
    if (unk != 1) {
        return -3;
    }

    D_8006C3AC |= unk << nCardSlot;
    return 1;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8A8C);

s32 func_801B8D24(s32 cardSlot, s32 cardSubSlot);
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8D24);
#else
s32 func_801B8D24(s32 cardSlot, s32 cardSubSlot) {
    s8 cardPath[0x8];
    s32 ret;

    D_8006C3AC &= D_801808DC[cardSlot];
    sprintf(cardPath, D_801A7D78, cardSlot, cardSubSlot);
    _clear_event_x();
    format(cardPath);

    ret = _card_event_x();
    if (ret != 1) {
        if (ret == 3) {
            return -1;
        }
        return -3;
    }
    return ret;
}
#endif

void func_801B8DB0(u16* arg0, s32 arg1) {
    s32 i;
    u16* var_v1;

    var_v1 = &(D_801808E4 - 1)[arg1 * 0x10]; // FAKE
    var_v1++;
    for (i = 0; i < 0x10; i++)
        *arg0++ = *var_v1++;
}

void func_801B8DE8(u8* dst, s32 arg1) {
    s32 i;
    u8* src = (u8*)D_801822E4[arg1];

    for (i = 0; i < 0x180; i++) {
        *dst++ = *src++;
    }
}

void StoreSaveData(SaveData* save, s32 arg1, s32 arg2);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", StoreSaveData);

s32 LoadSaveData(SaveData* save); // LoadSaveData
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", LoadSaveData);

void func_801B9698(char* dstSaveName, s32 saveSlot);
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9698);
#else
void func_801B9698(char* dstSaveName, s32 saveSlot) {
    strncpy(dstSaveName, D_801A802C, sizeof(D_801A802C));
    dstSaveName[0x10] += saveSlot / 10;
    dstSaveName[0x11] += saveSlot % 10;
}
#endif

s32 func_801B9744(void) {
    u8 res;

    if (CdSync(1, &res) == 0) {
        D_801BC344 = 0;
        return 0;
    }

    if (func_80019444() - 0x10 < 2U || !(res & 0x10)) {
        CdControlF(1, NULL);
        D_801BC344 = 0;
        return 0;
    }

    D_801BC344 = 1;
    return 1;
}

s32 func_801B97BC(s32*);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B97BC);

void func_801B988C(u32* arg0) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 4;
loop_1:
    temp_v0 = func_801B97BC(arg0);
    if (temp_v0 == 0) {
        var_s0 -= 1;
        if (var_s0 != 0) {
            goto loop_1;
        }
    } else {
        s32 temp_v0_2 = arg0[2] == 0;
        arg0[2] = temp_v0_2;
        D_801BC340++;
        func_801BABA4(temp_v0, *((temp_v0_2) + arg0));
        func_8001C550(temp_v0);
    }
}

void func_801B9924(void) {
    volatile u32 pad[4]; // FAKE
    SetDispMask(0);
    func_801B18F4();
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B994C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B99E4);

// func_801B9B7C(Unkstruct_801B9B7C* arg0, s16 arg1, s16 arg2, s16 arg3, s32
// arg4);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9B7C);

void func_801B9C18(s32 unused, void (*callback)()) {
    s32* s0 = D_801BD044;
    func_801BA460(0);
    *s0 = 0;
    func_801BA6CC(callback);
    func_800192DC((s32)(s0 + 2), 0x28);
    StSetStream(D_801BD038, 1, -1, NULL, NULL);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9C80);

void func_801BA460(s32 option) {
    if (option == 0) {
        ResetCallback();
    }

    MDEC_rest(option);
}

s32* func_801BA498(Unkstruct_801BA498* arg0) {
    s32 i;
    s32 *src1, *dst1;
    s32 *src2, *dst2;
    s32 *src3, *dst3;

    dst1 = &arg0->unk00;
    src1 = D_801962F8;
    for (i = 15; i != -1; i--) {
        *dst1++ = *src1++;
    }

    dst2 = &arg0->unk10;
    src2 = D_80196338;
    for (i = 15; i != -1; i--) {
        *dst2++ = *src2++;
    }

    dst3 = &arg0->unk20;
    src3 = D_8019637C;
    for (i = 31; i != -1; i--) {
        *dst3++ = *src3++;
    }

    return arg0;
}

s32* func_801BA524(Unkstruct_801BA498* arg0) {
    s32 i;
    s32 *src1, *dst1;
    s32 *src2, *dst2;

    dst1 = D_801962F8;
    src1 = &arg0->unk00;
    for (i = 15; i != -1; i--) {
        *dst1++ = *src1++;
    }

    dst2 = D_80196338;
    src2 = &arg0->unk10;
    for (i = 15; i != -1; i--) {
        *dst2++ = *src2++;
    }

    func_801BA7EC(&D_801962F4, 0x20);
    func_801BA7EC(&D_80196378, 0x20);

    return arg0;
}

u16 func_801BA5C0(u16* arg0) { return *arg0; }

void func_801BA5CC(s32* arg0, s32 arg1) {
    s32 new_var2;
    s32 var_v0;
    s32 var_v0_2;

    if (arg1 & 1) {
        var_v0 = (*arg0) & 0xF7FFFFFF;
    } else {
        new_var2 = 0x08000000;
        var_v0 = 0x08000000;
        var_v0 = (*arg0) | var_v0;
    }

    *arg0 = var_v0;
    var_v0 = 0x02000000;
    if (arg1 & 2) {
        new_var2 = var_v0;
        var_v0_2 = (*arg0) | new_var2;
    } else {
        var_v0_2 = (*arg0) & 0xFDFFFFFF;
    }

    *arg0 = var_v0_2;
    func_801BA7EC(arg0, *(u16*)arg0);
}

void func_801BA648(s32 arg0, u32 arg1) { func_801BA880(arg0, arg1); }

void func_801BA668(void) { MDEC_in_sync(); }

void func_801BA688(void) { MDEC_out_sync(); }

void func_801BA6A8(void (*func)()) { DMACallback(0, func); }

void func_801BA6CC(void (*func)()) { DMACallback(1, func); }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", MDEC_rest);

void func_801BA7EC(s32* arg0, u32 arg1) {
    MDEC_in_sync();
    *D_80196434 |= 0x88;
    *D_801963FC = arg0 + 1;
    *D_80196400 = ((arg1 >> 5) << 0x10) | 0x20;
    *D_8019642C = *arg0;
    *D_80196404 = 0x01000201;
}
void func_801BA880(s32 arg0, u32 arg1) {
    MDEC_out_sync();
    *D_80196434 |= 0x88;
    *D_80196410 = 0;
    *D_80196408 = arg0;
    *D_8019640C = ((arg1 >> 5) << 0x10) | 0x20;
    *D_80196410 = 0x01000200;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", MDEC_in_sync);

#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", MDEC_out_sync);
#else
void MDEC_out_sync(void) {
    volatile s32 sp10 = 0x100000;

    while (*D_80196410 & 0x01000000) {
        if (--sp10 == -1) {
            MDEC_print_error(D_801ABFC8);
            break;
        }
    }
}
#endif

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", MDEC_print_error);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BAB70);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BABA4);
