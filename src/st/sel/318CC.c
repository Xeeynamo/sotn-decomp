// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

extern RECT D_801825A4;
extern RECT D_80182584;
extern char* D_801BC398[0x10];

// BSS
static u8* D_801BAFD0; // Pointer to texture pattern
static s32 D_801BAFD4;
static s32 D_801BAFD8;

// DATA
static u8 D_8018046C[] = {
    'a', 0x80, 0xB0, 'b',  0x90, 0xB0, 'c',  0xA0, 0xB0, 'd', 0xB0, 0xB0,
    'e', 0xC0, 0xB0, 'f',  0xD0, 0xB0, 'g',  0xE0, 0xB0, 'h', 0xF0, 0xB0,
    'i', 0x80, 0xC0, 'j',  0x90, 0xC0, 'k',  0xA0, 0xC0, 'l', 0xB0, 0xC0,
    'm', 0xC0, 0xC0, 'n',  0xD0, 0xC0, 'o',  0xE0, 0xC0, 'p', 0xF0, 0xC0,
    'q', 0x80, 0xD0, 'r',  0x90, 0xD0, 's',  0xA0, 0xD0, 't', 0xB0, 0xD0,
    'u', 0xC0, 0xD0, 'v',  0xD0, 0xD0, 'w',  0xE0, 0xD0, 'x', 0xF0, 0xD0,
    'y', 0x80, 0xE0, 'z',  0x90, 0xE0, '&',  0xA0, 0xE0, '!', 0xB0, 0xE0,
    '-', 0xC0, 0xE0, '.',  0xD0, 0xE0, '\'', 0xE0, 0xE0, '?', 0xF0, 0xE0,
    ' ', 0xE0, 0xF0, 0x00,
};

#ifndef HARD_LINK
void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}
#endif

void func_801B18F4(void) { ClearImage(&D_801825A4, 0, 0, 0); }

void SetDisplayBufferColorsToBlack(void) {
    g_GpuBuffers[0].draw.r0 = 0;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0;
    g_GpuBuffers[1].draw.r0 = 0;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0;
}

void func_801B195C(s32 arg0) {
    g_GpuBuffers[0].draw.clip.y = 0x14;
    g_GpuBuffers[0].draw.clip.h = 0xCF;
    if (arg0 == 0) {
        g_GpuBuffers[1].draw.clip.y = 0x14;
    } else {
        g_GpuBuffers[1].draw.clip.y = 0x114;
    }
    g_GpuBuffers[1].draw.clip.h = 0xCF;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = true;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[0].draw.dtd = g_GpuBuffers[1].draw.dtd = false;
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = false;
}

void func_801B19F4(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(
        &g_GpuBuffers[1].draw, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(
        &g_GpuBuffers[0].disp, DISP_STAGE_W, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_801B195C(0);
}

void SetTitleDisplayBuffer(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.clip.y = 256;
    g_GpuBuffers[0].draw.clip.h = g_GpuBuffers[1].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = true;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = false;
}

// same as SetTitleDisplayBuffer, but clips at 256 vertical height
void SetTitleDisplayBuffer256(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_MENU_W, DISP_TITLE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, DISP_MENU_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, DISP_MENU_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_MENU_W, DISP_TITLE_H);
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.clip.y = 256;
    g_GpuBuffers[0].draw.clip.h = g_GpuBuffers[1].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = true;
    SetDisplayBufferColorsToBlack();
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = false;
}

// For the given prim, sets one of the vertices (0-3) to r,g,b values of
// the given colorIntensity. All of r,g,b are set, so limited to grey shades.
void SetPrimVertexGrey(Primitive* prim, u8 colorIntensity, s32 vertexIndex) {
    switch (vertexIndex) {
    case 0:
        PGREY(prim, 0) = colorIntensity;
        break;
    case 1:
        PGREY(prim, 1) = colorIntensity;
        break;
    case 2:
        PGREY(prim, 2) = colorIntensity;
        break;
    case 3:
        PGREY(prim, 3) = colorIntensity;
        break;
    }
}

// Sets each of the 4 vertices of a prim to the specified grey level, thus
// making the whole primitive that level.
void SetPrimGrey(Primitive* prim, u8 colorIntensity) {
    SetPrimVertexGrey(prim, colorIntensity, 0);
    SetPrimVertexGrey(prim, colorIntensity, 1);
    SetPrimVertexGrey(prim, colorIntensity, 2);
    SetPrimVertexGrey(prim, colorIntensity, 3);
}

void func_801B1D68(Primitive* prim) { SetPrimGrey(prim, 0); }

void func_801B1D88(Primitive* prim) { SetPrimGrey(prim, 0x80); }

void func_801B1DA8(void) {
    s32 index = 0;
    s32 i, j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            g_ClutIds[index] = GetClut(j, i);
            index++;
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            g_ClutIds[index] = GetClut(j, i);
            index++;
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            g_ClutIds[index] = GetClut(j, i);
            index++;
        }
    }
}

void func_801B1ED0(void) {
    s32 i;

    for (i = 0; i < LEN(D_801BC398); i++) {
        D_801BC398[i] = 0;
    }
}

u8 func_801B1EF4(u8 arg0) {
    if (arg0 & 0x80) {
        return func_801B1EF4((arg0 & 0x7F) + 3);
    } else {
        return arg0 * 0x10;
    }
}

void func_801B1F34(void) { D_801BAFD0 = g_Pix[1]; }

void func_801B1F4C(s32 arg0) {
    s32 i;
    u8* pix;

    D_801BC398[arg0] = NULL;
    arg0 = func_801B1EF4(arg0);
    pix = D_801BAFD0;
    for (i = 0; i < 0x800; i++) {
        *D_801BAFD0++ = 0;
    }

    LoadTPage((u_long*)pix, 0, 0, 0x180, arg0, 0x100, 0x10);
}

void func_801B1FD8(char* str, s32 y) {
    const int W = 12;
    const int H = 16;
    const int LEN = W * H / 2;
    u32 ch16;
    s32 i;
    s32 x;
    u8* chPix;

#ifdef VERSION_PC
    NOT_IMPLEMENTED;
    return;
#endif
    y = func_801B1EF4(y);
    x = 0;
    while (*str) {
        if (D_801BAFD0 >= g_Pix[4]) {
            break;
        }
        ch16 = *str++ << 8;
        ch16 += *str++;
        chPix = (u8*)g_api.func_80106A28(ch16, 3);
        for (i = 0; i < LEN; i++) {
            D_801BAFD0[i] = *chPix++;
        }
        LoadTPage(
            (u_long*)D_801BAFD0, 0, 0, D_801BAFD4 + x, D_801BAFD8 + y, W, H);
        D_801BAFD0 += LEN;
        x += 3;
    }
}

// Variant of func_800F99B8, with the third argument stripped
void func_801B2108(const char* str, s32 arg1) {
    // See src/st/blit_char.h
    const u16 DOUBLE_SPACE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    const int FontStride = FontWidth / 2;

    s32 ch16;
    u8* chPix;
    s32 var_a3;
    u8 ch;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;
    s32 i;
    s32 j;
    u8* dest_addr;

    var_s4 = 0x90;
    for (i = 0; i < var_s4 * FontHeight; i++) {
        D_801BAFD0[i] = 0;
    }
    var_s6 = ((u32)arg1 >> 2) & 0x40;
    var_s3 = 0;
    if (arg1 & 0x200) {
        var_s6 += 0x20;
        arg1 &= ~0x200;
    }
#ifdef VERSION_PC
    NOT_IMPLEMENTED;
    return;
#endif
    arg1 = func_801B1EF4(arg1);
    while (*str) {
        var_s2 = 0;
        ch = *str++;
        if ('a' <= ch && ch <= 'z') {
            ch16 = ch + 0x8220;
        } else if ('A' <= ch && ch <= 'Z') {
            ch16 = ch + 0x821F;
        } else if (ch == ' ') {
            ch16 = DOUBLE_SPACE;
            var_s2 = 2;
        } else {
            // load ch16 as a big-endian value corresponding with shift-jis
            ch16 = (ch << 8);
            ch16 += *str++;
            if (ch16 == RIGHT_DOUBLE_QUOTATION_MARK) {
                str += 2;
            }
            if (ch16 == DOUBLE_SPACE) {
                ch = ' ';
                var_s2 = 2;
            }
        }
        chPix = g_api.func_80106A28(ch16, 3);
        while (1) {
            if (ch == ' ') {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                // probably fake, i think chPix is a 2d array like [6][??]
                if (chPix[i * FontStride] != 0) {
                    break;
                }
            }
            if (i != FontHeight) {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                dest_addr = &chPix[i * FontStride];
                // Effectively shift everything down an index
                for (j = 0; j < 5; j++) {
                    dest_addr[0] = dest_addr[1];
                    dest_addr += 1;
                }
                // Set last index to 0
                *dest_addr = 0;
            }
        }
        for (i = 0, var_a3 = 0; i < FontHeight; i++) {
            for (j = 0; j < FontStride; j++) {
                // similar to above comment, this could be chPix[i][j]
                if ((chPix[i * FontStride + j] != 0) && (var_a3 < j)) {
                    var_a3 = j;
                }
            }
        }
        for (i = 0; i < FontHeight; i++) {
            if (chPix[i * FontStride + var_a3] & 0xF0) {
                break;
            }
        }
        if (i != FontHeight) {
            var_a3 += 1;
        }
        if (var_a3 < FontStride) {
            var_a3 += 1;
        }
        for (i = 0; i < FontHeight; i++) {
            dest_addr = &D_801BAFD0[var_s3 + var_s4 * i];
            *dest_addr++ = *chPix++;
            *dest_addr++ = *chPix++;
            *dest_addr++ = *chPix++;
            *dest_addr++ = *chPix++;
            *dest_addr++ = *chPix++;
            *dest_addr++ = *chPix++;
        }
        var_s3 += var_a3 + var_s2;
        if (var_s3 >= var_s4) {
            break;
        }
    }

    LoadTPage(D_801BAFD0, 0, 0, D_801BAFD4 + var_s6, D_801BAFD8 + arg1,
              var_s4 * 2, 0x10);
    D_801BAFD0 += var_s4 * 0x10;
}

void func_801B248C(char* str, s32 id) {
    if (D_801BC398[id] != str) {
        func_801B1F4C(id);
        D_801BC398[id] = str;
        func_801B1FD8(str, id);
    }
}

void func_801B24F8(char* str, s32 id) {
    if (D_801BC398[id] != str) {
        func_801B1F4C(id);
        D_801BC398[id] = str;
        func_801B2108(str, id);
    }
}

void func_801B2564(char* str, s32 id) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B248C(str, id);
}

void func_801B259C(char* str, s32 id) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B24F8(str, id);
}

void func_801B25D4(char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B248C(str, id);
}

void func_801B2608(char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B24F8(str, id);
}

void func_801B263C(char* str, s32 id) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B1FD8(str, id);
}

#ifndef HARD_LINK
#include "../../set_prim_rect.h"
#endif

void func_801B2700(s32 tpage, s32 otIdx) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    DR_MODE* drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];

    SetDrawMode(drawMode, 0, 0, tpage, &D_80182584);
    AddPrim(&ot[otIdx], drawMode);
    g_GpuUsage.drawModes++;
}

void func_801B27A8(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 clut,
                   s32 tpage, s32 tge, s32 c) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    SPRT* sprite = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
    s32 otIdx = 0x20;

    SetSemiTrans(sprite, 0);
    SetShadeTex(sprite, tge);
    sprite->x0 = x;
    sprite->y0 = y;
    sprite->w = w;
    sprite->h = h;
    sprite->u0 = u;
    sprite->v0 = v;
    sprite->r0 = c;
    sprite->g0 = c;
    sprite->b0 = c;
    sprite->clut = g_ClutIds[clut];
    AddPrim(&ot[otIdx], sprite);
    g_GpuUsage.sp++;
    func_801B2700(tpage, otIdx);
}

void func_801B28D4(u8* str, s32 x, s32 y, s32 tge) {
    const int w = 12;
    const int h = 16;
    u8 ch;

    while (true) {
        ch = *str++;
        if (ch == 0xFF) {
            break;
        }
        func_801B27A8(
            x, y, w, h, (ch & 0x0F) * w, (ch & 0xF0), 0x1A1, 6, tge, 0x40);
        x += w;
    }
}

s32 func_801B2984(char ch) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (D_8018046C[i * 3] == ch) {
            return i;
        }
    }
    return 0x20;
}

void DrawString16x16(char* str, s32 x, s32 y, s32 tge) {
    const s32 W = 16;
    const s32 H = 16;
    char ch;
    s32 uvIndex;

    while (true) {
        ch = *str++;
        if (!ch) {
            break;
        }

        uvIndex = func_801B2984(ch);
        func_801B27A8(x, y, W, H, D_8018046C[uvIndex * 3 + 1],
                      D_8018046C[uvIndex * 3 + 2], 0x200, 12, tge, 0x40);
        x += W;
    }
}

void func_801B2A9C(s32 img, s32 x, s32 y, s32 tge) {
    func_801B27A8(
        x, y, 8, 8, (img & 0xF) * 8, (img & 0xF0) / 2, 0x196, 0x1E, tge, 0x80);
}

void DrawImages8x8(u8* imgs, s32 x, s32 y, s32 tge) {
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

void func_801B2BD4(s32 num, s32 x, s32 y, s32 tge) {
    do {
        s32 digit = num % 10;
        func_801B2B78(digit, x, y, tge);
        x -= 8;
        num /= 10;
    } while (num != 0);
}

void func_801B2C70(s32 num, s32 x, s32 y, s32 tge) {
    s32 digit = num % 10;
    func_801B2B78(digit, x, y, tge);
    x -= 8;
    num /= 10;
    func_801B2B78(num, x, y, tge);
}

void func_801B2CF8(Primitive* prim) {
    s32 i;

    s32* ptr = (s32*)prim;
    s32 size = sizeof(Primitive) / sizeof(ptr);

    for (i = 0; i < size; i++) {
        *ptr++ = 0;
    }
}

void func_801B2D1C(void) {
    Primitive* prim;
    s32 i;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++, prim++) {
        func_801B2CF8(prim);
        prim->type = PRIM_NONE;
    }
}
