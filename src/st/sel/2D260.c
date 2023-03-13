#include "sel.h"

typedef enum {
    Tips_Generic,
    Tips_Input,
    Tips_YesNo,
    Tips_Confirm,
    Tips_MenuNavigation,
    Tips_NoYes,
} NavigationTips;

void DrawNavigationTips(NavigationTips mode) {
    u8** imgs;
    POLY_GT4* poly;

    func_801ACBE4(6, 8);
    imgs = &D_801803C4;
    poly = &D_80086FEC[D_801BAF48];

    switch (mode) {
    case Tips_Generic:
        func_801B2670(poly, 32, 176, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 32, 192, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 32, 208, 16, 16);
        poly->pad3 = 0;
        break;

    case Tips_Input:
        func_801B2670(poly, 288, 32, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 288, 48, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 288, 64, 16, 16);
        poly->pad3 = 0;
        poly = poly->tag;
        func_801B2670(poly, 288, 80, 16, 16);
        poly->pad3 = 0;
        break;

    case Tips_YesNo:
    case Tips_NoYes:
        poly = poly->tag;
        func_801B2670(poly, 32, 192, 16, 16);
        poly->pad3 = 0;
        poly = (POLY_GT4*)poly->tag;
        func_801B2670(poly, 32, 208, 16, 16);
        poly->pad3 = 0;
        if (mode == Tips_YesNo) {
            func_801AD1D0();
        } else {
            func_801AD218();
        }
        break;

    case Tips_Confirm:
        poly = poly->tag;
        func_801B2670(poly, 32, 192, 16, 16);
        poly->pad3 = 0;
        DrawImages8x8(*imgs, 52, 196, 1);
        break;

    case Tips_MenuNavigation:
        func_801B2670(poly, 32, 184, 16, 16);
        poly->pad3 = 0;
        poly = (POLY_GT4*)poly->tag;
        func_801B2670(poly, 32, 200, 16, 16);
        poly->pad3 = 0;
        break;
    }
}

void func_801AD490(void) {
    s32 i;

    DrawNavigationTips(Tips_MenuNavigation);
    DrawImages8x8(D_801803A8 /* "select" */, 52, 188, 1);
    DrawImages8x8(D_801803AC /* "start" */, 52, 204, 1);
    DrawString16x16("select", 240, 32, 1);
    DrawString16x16("your", 256, 48, 1);
    DrawString16x16("destiny", 232, 64, 1);

    for (i = 0; i < 5; i++) {
        POLY_GT4* poly = &D_80086FEC[D_801BAF18[i + 1].unk0];
        if (i == D_801D6B0C) {
            poly->clut = 0x203;
        } else {
            poly->clut = 0x200;
        }
    }
}

void func_801AD590(void) {
    if (g_pads[0].tapped & (PAD_RIGHT + PAD_DOWN)) {
        g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
        if (++D_801D6B0C == 5) {
            D_801D6B0C = 1;
        }
    }
    if (g_pads[0].tapped & (PAD_LEFT + PAD_UP)) {
        g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
        if (--D_801D6B0C == 0) {
            D_801D6B0C = 4;
        }
    }
    func_801B2608(D_80180454[D_801D6B0C], 9);
}

// single instruction reorder, function tested working in-game
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801AD66C);
#else
void func_801AD66C(void) {
    s32 spaceCounter;
    s32 counter;
    s32 i;

    /**
     * If the entered name contains 8 spaces, sets the default
     * name to "alucard " which is stored in D_801A7754
     */
    for (spaceCounter = 0, i = 0; i < 8; i++) {
        g_SaveName[i] = g_InputSaveName[i];
        if (g_InputSaveName[i] == ' ') {
            spaceCounter++;
        }
    }

    if (spaceCounter == 8) {
        __builtin_memcpy(g_SaveName, D_801A7754, 9);
    }

    /**
     * Checks byte by byte if the entered name is equal
     * to "richter " and if time attack is unlocked,
     * in which case enables the player to play as Richter
     */
    D_80097B98 = 0;
    D_80097B99 = 0;

    for (counter = 0; counter < 8; counter++) {
        if (g_SaveName[counter] != D_80180468[counter]) {
            break;
        }
    }

    if (g_IsTimeAttackUnlocked != false) {
        g_IsTimeAttackUnlocked = 2;
    }

    if ((counter == 8) && (g_IsTimeAttackUnlocked != false)) {
        g_CurrentPlayableCharacter = PLAYER_RICHTER;
    } else {
        g_CurrentPlayableCharacter = PLAYER_ALUCARD;
    }
}
#endif

/* DATA */
extern u8* D_801803B0;
extern u8* D_801803B4;
/* RODATA */
extern const char* D_801A7760[]; // "a b c d e f g h"
extern const char* D_801A7770[]; // "i j k l m n o p"
extern const char* D_801A7780[]; // "q r s t u v w x"
extern const char* D_801A7790[]; // "y z & ! - . '  "
/* BSS */
extern s32 D_801BAF58;
extern s32 D_801BAF68;

void func_801AD78C(void) {
    DrawImages8x8(D_801803A8, 0x134, 0x24, 1);
    DrawImages8x8(D_801803B4, 0x134, 0x34, 1);
    DrawImages8x8(D_801803B0, 0x134, 0x44, 1);
    DrawImages8x8(D_801803AC, 0x134, 0x54, 1);
    DrawString16x16(D_801A7760, 0x48, 0x70, 1);
    DrawString16x16(D_801A7770, 0x48, 0x88, 1);
    DrawString16x16(D_801A7780, 0x48, 0xA0, 1);
    DrawString16x16(D_801A7790, 0x48, 0xB8, 1);
    func_801B26A0(&D_80086FEC[D_801BAF58], (g_InputCursorPos * 0x10) + 0x80,
                  0x48, 0x0F, 0x0F, 0xF0, 0xF0);
    func_801B26A0(&D_80086FEC[D_801BAF68], ((D_801BC3E0 & 7) << 5) + 0x40,
                  (D_801BC3E0 & 0x18) * 3 + 0x68, 0x20, 0x20, 0, 0x48);
    if (g_blinkTimer & 8) {
        func_801ACBE4(8, 0);
    } else {
        func_801ACBE4(8, 8);
    }
    DrawString16x16(g_InputSaveName, 0x80, 0x48, 1);
}

void UpdateNameEntry(void) {
    if (g_pads[0].repeat & PAD_RIGHT) {
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
        D_801BC3E0 = (D_801BC3E0 & 0x18) | ((D_801BC3E0 + 1) & 7);
    }

    if (g_pads[0].repeat & PAD_DOWN) {
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
        D_801BC3E0 = ((D_801BC3E0 + 8) & 0x18) | (D_801BC3E0 & 7);
    }

    if (g_pads[0].repeat & PAD_LEFT) {
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
        D_801BC3E0 = (D_801BC3E0 & 0x18) | ((D_801BC3E0 - 1) & 7);
    }

    if (g_pads[0].repeat & PAD_UP) {
        g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
        D_801BC3E0 = ((D_801BC3E0 - 8) & 0x18) | (D_801BC3E0 & 7);
    }

    if (g_pads[0].tapped & (PAD_R1 + PAD_R2)) {
        g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
        if (++g_InputCursorPos == 8) {
            g_InputCursorPos = 0;
        }
    }

    if (g_pads[0].tapped & (PAD_L1 + PAD_L2)) {
        g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
        if (--g_InputCursorPos == -1) {
            g_InputCursorPos = 7;
        }
    }

    if (g_pads[0].tapped & PAD_CROSS) { // Input Character
        g_api.PlaySfx(0x8CD);
        g_InputSaveName[g_InputCursorPos] = D_801823A0[D_801BC3E0];
        if (++g_InputCursorPos == 8) {
            g_InputCursorPos = 0;
        }
    }

    if (g_pads[0].tapped & PAD_TRIANGLE) { // Backspace
        if (--g_InputCursorPos == -1) {
            g_InputCursorPos = 7;
        }
        g_InputSaveName[g_InputCursorPos] = ' ';
    }
}

void UpdateFileSelect(void) {
    if (D_801BCC84[0] >= 0 || D_801BD02C >= 0) {
        if (g_pads[0].repeat & PAD_RIGHT) { // move selector to the right
            g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 1) % 6;
        }

        if (g_pads[0].repeat & PAD_DOWN) { // move selector down
            g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
            // clamp selector inside the 5 possible Y coord positions
            g_MemCardSelectorY = (g_MemCardSelectorY + 4) % 5;
        }

        if (g_pads[0].repeat & PAD_LEFT) { // move selector to the left
            g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 5) % 6;
        }

        if (g_pads[0].repeat & PAD_UP) { // move selector up
            g_api.PlaySfx(NA_SE_SY_MOVE_MENU_CURSOR);
            // clamp selector inside the 5 possible Y coord positions
            g_MemCardSelectorY = (g_MemCardSelectorY + 1) % 5;
        }

        if ((D_801BCC84[0] > 0) && (D_801BD02C > 0) &&
            (g_pads[0].tapped & (PAD_L2 + PAD_R2 + PAD_L1 + PAD_R1))) {
            g_api.PlaySfx(NA_SE_PL_MP_GAUGE);
            // clamp selector inside the 6 possible X coord positions
            g_MemCardSelectorX = (g_MemCardSelectorX + 3) % 6;
        }

        if (D_801BCC84[0] < 0) {
            g_MemCardSelectorX = (g_MemCardSelectorX % 3) + 3;
        }

        if (D_801BD02C < 0) {
            g_MemCardSelectorX %= 3;
        }

        D_801D6B04 = (g_MemCardSelectorX % 3) + (g_MemCardSelectorY * 3) +
                     ((g_MemCardSelectorX / 3) * 0xF);
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801ADF94);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801AE6D0);

void func_801AE9A8(void) {
    s32 i;

    func_801ACC3C();
    func_801ACBE4(0, 0);

    for (i = 1; i < 5; i++) {
        func_801ACBE4(i + 1, 4);
        func_801B26A0(&D_80086FEC[D_801BAF18[i + 1].unk0], (i * 64) - 32,
                      (i * 5) * 8, 127, 31, D_80180040[i], D_80180054[i]);
    }

    DrawNavigationTips(0);
    func_801ACBE4(0x11, 0);
}

void func_801AEA8C(s32 arg0) {
    g_InputCursorPos = 0;
    D_801BC3E0 = 0;
    func_801ACC3C();
    func_801ACBE4(7, 0x11);
    func_801ACBE4(8, 0);
    func_801ACBE4(9, 0x11);
    func_801ACBE4(10, 0);

    if (arg0 == 0) {
        func_801ACBE4(1, 0);
        func_801B2670(&D_80086FEC[D_801BAF20], 24, 24, 127, 31);
    } else {
        func_801ACBE4(3, 0);
        func_801B2670(&D_80086FEC[D_801BAF30], 24, 24, 127, 31);
    }

    DrawNavigationTips(1);
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801AEB74);

void func_801AECA0(void) {
    s32 i = 0;
    s32 x;
    s32 y = 256;
    s32 w = 16;
    s32 h = 48;
    s32 xnext = 384;
    u32* pix = D_801822E4;

    for (; i < 16; i++) {
        s32 tmp = 4;
        x = xnext;
        xnext += tmp;
        LoadTPage((PixPattern*)*pix++, 0, 0, x, y, w, tmp = 0x30);
        x = xnext;
    }

    g_api.func_800EA5E4(0x8004);
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801AED48);

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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", Update);

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
    D_8003CB08.buf.draw.clip.y = 20;
    D_8003CB08.buf.draw.clip.h = 207;
    if (arg0 == 0) {
        D_800542FC.buf.draw.clip.y = 20;
    } else {
        D_800542FC.buf.draw.clip.y = 276;
    }
    D_800542FC.buf.draw.clip.h = 207;
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
        poly->r0 = poly->g0 = poly->b0 = colorIntensity;
        break;
    case 1:
        poly->r1 = poly->g1 = poly->b1 = colorIntensity;
        break;
    case 2:
        poly->r2 = poly->g2 = poly->b2 = colorIntensity;
        break;
    case 3:
        poly->r3 = poly->g3 = poly->b3 = colorIntensity;
        break;
    }
}

void func_801B1CFC(POLY_GT4* poly, s32 colorIntensity) {
    func_801B1C78(poly, colorIntensity, 0);
    func_801B1C78(poly, colorIntensity, 1);
    func_801B1C78(poly, colorIntensity, 2);
    func_801B1C78(poly, colorIntensity, 3);
}

void func_801B1D68(POLY_GT4* poly) { func_801B1CFC(poly, 0); }

void func_801B1D88(POLY_GT4* arg0) { func_801B1CFC(arg0, 0x80); }

void func_801B1DA8(void) {
    s32 index = 0;
    s32 i, j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }
}

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
    } else {
        return (arg0 * 0x10) & 0xF0;
    }
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
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B1FD8);

void func_801B2108(s32, s32);
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B2108);

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
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B2700);

void func_801B27A8(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 clut, s32 arg7,
                   s32 tge, s32 c);
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B27A8);

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

s32 func_801B2984(u8 ch) {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        if (D_8018046C[i * 3] == ch)
            return i;
    }
    return 0x20;
}

// reg swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", DrawString16x16);
#else
extern u8 D_8018046D[];

void DrawString16x16(const char* str, s32 x, s32 y, s32 tga) {
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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B2E5C);

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B2F50);

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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B3164);

void func_801B367C(s32 arg0) {
    g_memCardRStep = 0;
    g_memCardRStepSub = arg0;
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B3694);
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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B38B4);

void func_801B3A54(s32 arg0, s32 arg1) {
    char pad[0x20];

    g_memCardRStep = 0;
    D_801BAFFC = arg0;
    D_801BB000 = arg1;
    D_801BB004 = arg0;
    D_801BB00C = arg1;
    D_801BB008 = arg1;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B3A94);

void func_801B3E14(s32 arg0) {
    g_memCardRStep = 0;
    g_memCardRStepSub = arg0;
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B3E2C);
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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B3F94);

void InitRoomEntities(s32 objLayoutId) {
    s32 temp_s0 = D_8003C9A4;

    switch (temp_s0) {
    case 0:
        if (D_8006C3B0 == 0) {
            g_IsTimeAttackUnlocked = true;
            D_8003C728 = 1;
            D_8003C100 = 0;
            D_8003C9A4 = 1;
        }
        break;

    case 1:
        func_801B9C80();
        if (D_8003C728 == 0) {
            g_IsTimeAttackUnlocked = false;
            D_8003C100 = 0;
            func_801B18F4();
            D_8003C734 = temp_s0;
            D_8003C9A4 = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", TestCollisions);

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_FREE_POLYGONS) {
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
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

s32 AnimateEntity(const u8 frames[], Entity* entity) {
    s32 flag = 0;
    u16 currentFrameIndex = entity->animFrameIdx * 2;
    u8* currentFrame = frames + currentFrameIndex;

    if (entity->animFrameDuration == 0) {
        if (currentFrame[0] > 0) {
            flag = 0x80;
            if (currentFrame[0] == 0xFF) {
                return false;
            }

            entity->animFrameDuration = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->animFrameIdx++;
        } else {
            currentFrame = frames;
            entity->animFrameIdx = 0;
            entity->animFrameDuration = 0;
            entity->animFrameDuration = *currentFrame++;
            entity->animCurFrame = *currentFrame++;
            entity->animFrameIdx++;
            return false;
        }
    }

    entity->animFrameDuration = entity->animFrameDuration - 1;
    entity->animCurFrame = currentFrame[-1];
    flag |= true;

    return (u8)flag;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B4C68);

void func_801B4D78(void) {
    Entity* e = &g_EntityArray[UNK_ENTITY_3];

    if (e->step == 0) {
        e->animSet = -0x7FFF;
        e->animCurFrame = 1;
        e->palette = 0x200;
        e->unk80.modeS32 = 0x5C0000;
        e->posY.i.hi = 208;
        e->zPriority = 0x80;
        e->step = 1;
    }
}

void func_801B4DE0(void) {
    Entity* unkEntity = &g_EntityArray[UNK_ENTITY_2];
    s16 firstPolygonIndex;
    POLY_GT4* poly;

    switch (unkEntity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPolygons(3, 1);
        if (firstPolygonIndex != -1) {
            poly = &D_80086FEC[firstPolygonIndex];
            unkEntity->firstPolygonIndex = firstPolygonIndex;
            unkEntity->flags |= FLAG_FREE_POLYGONS;
            *(s32*)&unkEntity->unk7C = poly;

            poly->x1 = poly->x3 = 255;
            poly->y0 = poly->y1 = 4;
            poly->y2 = poly->y3 = 228;

            poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
                poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 =
                    poly->b3 = 255;

            poly->pad2 = 0xC8;
            poly->x0 = poly->x2 = 0;
            poly->pad3 = 81;
            D_801BC3E4 = 0;
            unkEntity->step++;
        }
        break;

    case 1:
        poly = *(s32*)&unkEntity->unk7C;
        if (D_801BC3E4 != 0) {
            poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
                poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                    poly->r0 = poly->b3 - 2;
            if (poly->r0 < 5) {
                D_801BC3E4 = 0;
                unkEntity->step++;
            }
        }
        break;

    case 2:
        poly = *(s32*)&unkEntity->unk7C;
        if (D_801BC3E4 != 0) {
            poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
                poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                    poly->r0 = poly->b3 + 1;
            if (poly->r0 >= 254) {
                D_801BC3E4 = 0;
                unkEntity->step++;
            }
        }
    }
}

void func_801B4FFC(void) {
    Entity* unkEntity = &g_EntityArray[UNK_ENTITY_2];
    s16 firstPolygonIndex;
    POLY_GT4* poly;

    switch (unkEntity->step) {
    case 0:
        firstPolygonIndex = g_api.AllocPolygons(3, 1);
        if (firstPolygonIndex != -1) {
            poly = &D_80086FEC[firstPolygonIndex];
            unkEntity->firstPolygonIndex = firstPolygonIndex;
            unkEntity->flags |= FLAG_FREE_POLYGONS;
            *(s32*)&unkEntity->unk7C = poly;

            poly->x1 = poly->x3 = 384;
            poly->y0 = poly->y1 = 4;
            poly->y2 = poly->y3 = 228;

            poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
                poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 =
                    poly->b3 = poly->x0 = poly->x2 = 0;

            poly->pad2 = 0xC8;
            poly->pad3 = 0x51;

            unkEntity->step++;
        }
        break;

    case 1:
        poly = *(s32*)&unkEntity->unk7C;
        if (D_801BC3E4 != 0) {
            poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
                poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                    poly->r0 = poly->b3 + 2;
            if (poly->r0 >= 254) {
                D_801BC3E4 = 0;
                unkEntity->step++;
            }
        }

    case 2:
        break;
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B519C);

void func_801B5350(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_5];

    switch (entity->step) {
    case 0:
        entity->animSet = 1;
        entity->animCurFrame = 142;
        entity->unk80.modeS32 = 0x800000;
        entity->posY.i.hi = 159;
        entity->zPriority = 0xC0;
        entity->unk5A = 0;
        entity->palette = 0x8100;
        entity->step = 1;
        break;

    case 1:
        entity->animCurFrame = 142;
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
            entity->step = 255;
        }
        break;
    }
}

void func_801B54C8(void) {
    Entity* e = &g_EntityArray[UNK_ENTITY_7];

    if (e->step == 0) {
        e->animSet = -0x7FFE;
        e->animCurFrame = 38;
        e->facing = 1;
        e->unk5A = 0xF;
        e->unk80.modeS32 = 0x780000;
        e->posY.i.hi = 158;
        e->zPriority = 0xC0;
        e->palette = 0x8210;
        e->step = 1;
    }
}

void func_801B5548(void) {
    Entity* e = &g_EntityArray[UNK_ENTITY_7];

    if (e->step == 0) {
        e->animSet = -0x7FFE;
        e->animCurFrame = 7;
        e->unk5A = 0xF;
        e->unk80.modeS32 = 0x780000;
        e->posY.i.hi = 158;
        e->zPriority = 0xC0;
        e->palette = 0x8210;
        e->facing = 0;
        e->step = 1;
    }
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/2D260", func_801B55C8);
