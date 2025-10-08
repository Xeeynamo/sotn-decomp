// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sel/sel.h"

extern s32 D_psp_09285D48;
extern u8* D_psp_09285D58;
extern char* D_psp_09285D08[];
extern s32 D_psp_09285D50;
extern RECT D_9185278;
extern RECT D_9185258;
extern u8 D_psp_09285108[];

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/7D40", func_psp_0923F3C0);

void func_psp_0923F460(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_psp_0923F498(void) { ClearImage(&D_9185278, 0, 0, 0); }

void func_psp_0923F4D0(void) {
    g_GpuBuffers[0].draw.r0 = 0;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0;
    g_GpuBuffers[1].draw.r0 = 0;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0;
}

void func_psp_0923F508(s32 arg0) {
    g_GpuBuffers[0].draw.clip.y = 0x14;
    g_GpuBuffers[0].draw.clip.h = 0xCF;
    if (arg0 == 0) {
        g_GpuBuffers[1].draw.clip.y = 0x14;
    } else {
        g_GpuBuffers[1].draw.clip.y = 0x14;
    }
    g_GpuBuffers[1].draw.clip.h = 0xCF;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = true;
    func_psp_0923F4D0();
    g_GpuBuffers[0].draw.dtd = g_GpuBuffers[1].draw.dtd = false;
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = false;
}

void func_psp_0923F5C0(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_STAGE_W, DISP_STAGE_H);
    func_psp_0923F508(0);
}

void func_psp_0923F668(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_TITLE_W, DISP_TITLE_H);
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.clip.y = 0;
    g_GpuBuffers[0].draw.clip.h = g_GpuBuffers[1].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = true;
    func_psp_0923F4D0();
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = false;
}

void func_psp_0923F760(void) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, DISP_MENU_W, DISP_TITLE_H);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 0, DISP_MENU_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0, DISP_MENU_W, DISP_TITLE_H);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, DISP_MENU_W, DISP_TITLE_H);
    g_GpuBuffers[0].draw.clip.y = 0;
    g_GpuBuffers[1].draw.clip.y = 0;
    g_GpuBuffers[0].draw.clip.h = g_GpuBuffers[1].draw.clip.h = DISP_TITLE_H;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = true;
    func_psp_0923F4D0();
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = false;
}

void func_psp_0923F858(Primitive* prim, u8 colorIntensity, s32 vertexIndex) {
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

void func_psp_0923F948(Primitive* prim, u8 colorIntensity) {
    func_psp_0923F858(prim, colorIntensity, 0);
    func_psp_0923F858(prim, colorIntensity, 1);
    func_psp_0923F858(prim, colorIntensity, 2);
    func_psp_0923F858(prim, colorIntensity, 3);
}

void func_psp_0923F9B8(Primitive* prim) { func_psp_0923F948(prim, 0x80); }

void func_psp_0923F9E8(void) {
    s32 index = 0;
    s32 i, j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            g_ClutIds[index] = getClut(j, i);
            index++;
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            g_ClutIds[index] = getClut(j, i);
            index++;
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            g_ClutIds[index] = getClut(j, i);
            index++;
        }
    }
}

void func_psp_0923FB40(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        D_psp_09285D08[i] = 0;
    }
}

u8 func_801B1EF4(u8 arg0) {
    if (arg0 & 0x80) {
        return func_801B1EF4((arg0 & 0x7F) + 3);
    } else {
        return arg0 << 4;
    }
}

void func_psp_0923FBF0(void) { D_psp_09285D58 = g_Pix[1]; }

void func_psp_0923FC08(s32 arg0) {
    s32 i;
    u8* pix;

    D_psp_09285D08[arg0] = NULL;
    arg0 = func_801B1EF4(arg0);
    pix = D_psp_09285D58;
    for (i = 0; i < 0x800; i++) {
        *D_psp_09285D58++ = 0;
    }
    LoadTPage((u_long*)pix, 0, 0, 0x180, arg0, 0x100, 0x10);
}

void func_psp_0923FCC8(char* arg0, s32 arg1) {
    u8 sp2F;
    u32 ch16;
    s32 i;
    s32 var_s2;
    u8* chPix;

    arg1 = func_801B1EF4(arg1);
    var_s2 = 0;
    while (*arg0) {
        if (D_psp_09285D58 >= g_Pix[4]) {
            break;
        }
        ch16 = g_api.func_psp_0913F960(arg0, &sp2F);
        if (sp2F > 0) {
            arg0 = &arg0[sp2F];
        }
        chPix = (u8*)g_api.func_psp_0913FA28(ch16, 3);
        for (i = 0; i < 0x60; i++) {
            D_psp_09285D58[i] = *chPix++;
        }
        LoadTPage((u_long*)D_psp_09285D58, 0, 0, D_psp_09285D50 + var_s2,
                  D_psp_09285D48 + arg1, 0xC, 0x10);
        D_psp_09285D58 += 0x60;
        var_s2 += 3;
    }
}

void func_psp_0923FE40(char* arg0, s32 arg1) {
    if (D_psp_09285D08[arg1] != arg0) {
        func_psp_0923FC08(arg1);
        D_psp_09285D08[arg1] = arg0;
        func_psp_0923FCC8(arg0, arg1);
    }
}

INCLUDE_ASM("st/sel_psp/nonmatchings/sel_psp/7D40", func_psp_0923FEC0);

void func_psp_0923FF70(char* arg0, s32 arg1) {
    D_psp_09285D50 = 0x180;
    D_psp_09285D48 = 0;
    func_psp_0923FCC8(arg0, arg1);
}

void func_psp_0923FFB8(char* arg0, s32 arg1) {
    D_psp_09285D50 = 0x180;
    D_psp_09285D48 = 0;
    func_psp_0923FE40(arg0, arg1);
}

void func_psp_09240000(char* arg0, s32 arg1) {
    D_psp_09285D50 = 0x180;
    D_psp_09285D48 = 0;
    func_psp_0923FCC8(arg0, arg1);
}

void SetPrimRect(Primitive* poly, s32 x, s32 y, s32 width, s32 height) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->y2 = y + height;
    poly->x3 = x + width;
    poly->y3 = y + height;
}

void SetTexturedPrimRect(
    Primitive* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->y2 = y + height;
    poly->x3 = x + width;
    poly->y3 = y + height;
    poly->u0 = u;
    poly->v0 = v;
    poly->u1 = u + width;
    poly->v1 = v;
    poly->u2 = u;
    poly->v2 = v + height;
    poly->u3 = u + width;
    poly->v3 = v + height;
}

void func_psp_09240280(s32 tpage, s32 otIdx) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    DR_MODE* drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];

    SetDrawMode(drawMode, 0, 0, tpage, &D_9185258);
    AddPrim(&ot[otIdx], drawMode);
    g_GpuUsage.drawModes++;
}

void func_psp_09240330(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 clut,
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
    func_psp_09240280(tpage, otIdx);
}

s32 func_psp_092404A8(u8 arg0) {
    s32 i;

    for (i = 0; i < 0x22; i++) {
        if (D_psp_09285108[i * 3] == arg0) {
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
        if (ch != ' ') {
            uvIndex = func_psp_092404A8(ch);
            func_psp_09240330(
                x, y, W, H, D_psp_09285108[uvIndex * 3 + 1],
                D_psp_09285108[uvIndex * 3 + 2], 0x200, 12, tge, 0x40);
        }
        x += W;
    }
}

void func_psp_09240618(char* str, s32 x, s32 y, s32 tge, s32 c) {
    const s32 W = 16;
    const s32 H = 16;
    char ch;
    s32 uvIndex;

    while (true) {
        ch = *str++;
        if (!ch) {
            break;
        }
        if (ch != ' ') {
            uvIndex = func_psp_092404A8(ch);
            func_psp_09240330(
                x, y, W, H, D_psp_09285108[uvIndex * 3 + 1],
                D_psp_09285108[uvIndex * 3 + 2], 0x200, 12, tge, c);
        }
        x += W;
    }
}

void func_psp_09240718(s32 img, s32 x, s32 y, s32 tge) {
    func_psp_09240330(
        x, y, 8, 8, (img & 0xF) * 8, (img & 0xF0) / 2, 0x196, 0x1D, tge, 0x80);
}

void DrawImages8x8(u8* imgs, s32 x, s32 y, s32 tge) {
    while (true) {
        if (*imgs == 0xFF)
            break;
        func_psp_09240718(*imgs, x, y, tge);
        x += 8;
        imgs++;
    }
}

void func_psp_09240820(s32 icon, s32 x, s32 y, s32 tge) {
    func_psp_09240330(x, y, 8, 8, icon * 8 + 176, 120, 0x200, 0xC, tge, 0x40);
}

void func_psp_09240888(s32 num, s32 x, s32 y, s32 tge) {
    do {
        s32 digit = num % 10;
        func_psp_09240820(digit, x, y, tge);
        x -= 8;
        num /= 10;
    } while (num != 0);
}

void func_psp_09240920(s32 num, s32 x, s32 y, s32 tge) {
    s32 digit = num % 10;
    func_psp_09240820(digit, x, y, tge);
    x -= 8;
    num /= 10;
    func_psp_09240820(num, x, y, tge);
}

void func_psp_092409C8(Primitive* prim) {
    s32 i;

    s32* ptr = (s32*)prim;
    s32 size = sizeof(Primitive) / sizeof(ptr);

    for (i = 0; i < size; i++) {
        *ptr++ = 0;
    }
}

void func_psp_09240A28(void) {
    Primitive* prim;
    s32 i;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++, prim++) {
        func_psp_092409C8(prim);
        prim->type = PRIM_NONE;
    }
}
