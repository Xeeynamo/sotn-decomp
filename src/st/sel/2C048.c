/*
 * File: 2C048.c
 * Overlay: SEL
 * Description: Title & loading screen
 */

#include "stage.h"

#define DISP_W 512
#define DISP_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_H

typedef struct {
    u32 unk0;
    u32 unk4;
} Unkstruct_801ACBE4;

extern u8* D_80180128[];
extern u8* D_8018012C[];
extern u8* D_801803BC;
extern u8* D_801803C0;
extern s32 D_80180454[];
extern u8 D_8018046C[0x20 * 3];
extern u32 D_801822E4[];
extern RECT D_801825A4;
extern s32 D_801A75A0[];
extern s32 D_801A75C0[];
extern const char D_801A7D84[];
extern s32 D_801BAF10;
extern Unkstruct_801ACBE4 D_801BAF18[];
extern /*?*/ u8* D_801BAFD0;
extern s32 D_801BAFD4;
extern s32 D_801BAFD8;
extern s32 D_801BAFDC;
extern s32 D_801BAFE0;
extern u32 D_801BAFE4;
extern s32 D_801BAFE8;
extern s32 D_801BAFEC;
extern s32 D_801BAFF0;
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
extern s32 D_801BC8C8;
extern s32 D_801BC8E0[];
extern s32* D_801BC958[];
extern s32 D_801BCC84;
extern s32 D_801BD02C;
extern s32 D_801D6B04;
extern s32 D_801D6B08;
extern s32 D_801D6B0C;
extern s32 D_801D6B20;

void func_801B1ED0();
void func_801B3A54(s32, s32);
s32 func_801B3A94(s32);
void func_801B84F0();
s32 func_801B8A8C(s32, s32);

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
    volatile u32 pad; // FAKE

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
        g_pfnPlaySfx(0x67D);
        if (++D_801D6B0C == 5) {
            D_801D6B0C = 1;
        }
    }
    if (D_80097494 & 0x9000) {
        g_pfnPlaySfx(0x67D);
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
            g_pfnPlaySfx(0x67B);
            D_801BC3D8 = (D_801BC3D8 + 1) % 6;
        }
        if (*tmp & 0x4000) {
            g_pfnPlaySfx(0x67B);
            D_801BC3DC = (D_801BC3DC + 4) % 5;
        }
        if (*tmp & 0x8000) {
            g_pfnPlaySfx(0x67B);
            D_801BC3D8 = (D_801BC3D8 + 5) % 6;
        }
        if (*tmp & 0x1000) {
            g_pfnPlaySfx(0x67B);
            D_801BC3DC = (D_801BC3DC + 1) % 5;
        }
        if (*new_var > 0 && D_801BD02C > 0 && D_80097494 & 0xF) {
            g_pfnPlaySfx(0x67D);
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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AECA0);

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

// TODO accidentially pushed
void func_801B1F4C(s32);
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1F4C);
#else
s32 func_801B1EF4(s32, s32); /* extern */
extern /*?*/ s32 D_801BC398;

void func_801B1F4C(s32 arg0) {
    s32 temp_a2;
    s32 var_a1;
    u8* temp_a0;
    u8* temp_v0;

    *(&D_801BC398 + (arg0 * 4)) = 0;
    temp_a2 = func_801B1EF4(arg0 & 0xFF, arg0) & 0xFF;
    var_a1 = 0;
    temp_a0 = D_801BAFD0;
    do {
        temp_v0 = D_801BAFD0;
        var_a1 += 1;
        D_801BAFD0 = temp_v0 + 1;
        *temp_v0 = 0;
    } while (var_a1 < 0x800);
    LoadTPage((PixPattern*)temp_a0, 0, 0, 0x180, temp_a2, 0x100, 0x10);
}
#endif

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
        poly->code = 0;
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

    D_801BAFEC = 0;
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
    D_801BAFEC = 0;
    D_801BAFF0 = arg0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3694);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B38B4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3A54);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3A94);

void func_801B3E14(s32 arg0) {
    D_801BAFEC = 0;
    D_801BAFF0 = arg0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3E2C);

void func_801B3F7C(s32 arg0) {
    D_801BAFEC = 0;
    D_801BAFF0 = arg0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3F94);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4048);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B410C);

void func_801B4B30(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_pfnFreePolygons(entity->firstPolygonIndex);
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
        e->posY.Data.high = 0xD0;
        e->zPriority = 0x80;
        e->step = 1;
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4DE0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4FFC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B519C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B5350);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B54C8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B5548);

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B786C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B78BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B79D4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B80F0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8298);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8338);

void func_801B83BC(void) {
    TestEvent(D_80073068);
    TestEvent(D_8007306C);
    TestEvent(D_80073070);
    TestEvent(D_80073078);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8414);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8498);

void func_801B84F0(void) { D_801D6B20 = 0; }

void func_801B8500(void) {
    D_801BC650 = 0;
    D_801BC8C8 = 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8518);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8714);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B873C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B881C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B884C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B88F4);

s32 func_801B89C8(s32 memcardSlot, s32 memcardSubSlot, const char* path) {
    char buf[0x20];
    sprintf(buf, D_801A7D84, memcardSlot, memcardSubSlot, path);
    return -(erase(buf) == 0);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8A10);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8A8C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8D24);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8DB0);

void func_801B8DE8(u8* arg0, s32 arg1) {
    u8* src = (u8*)D_801822E4[arg1];
    s32 i;
    for (i = 0; i < 0x180; i++) {
        *arg0++ = *src++;
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8E20);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B94BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9698);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9744);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B97BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B988C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9924);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B994C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B99E4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9B7C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9C18);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9C80);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA460);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA498);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA524);

u16 func_801BA5C0(u16* arg0) { return *arg0; }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA5CC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA648);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA668);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA688);

void func_801BA6A8(void (*func)()) { DMACallback(0, func); }

void func_801BA6CC(void (*func)()) { DMACallback(1, func); }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA6F0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA7EC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA880);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA910);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA9A8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BAA40);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BAB70);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BABA4);
