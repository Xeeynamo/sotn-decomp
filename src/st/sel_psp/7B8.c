// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../sel/sel.h"

extern s32 D_psp_09283BE8;
extern s32 D_psp_09283CA8;
extern s32 D_psp_09283D30;
extern s32 D_psp_09283DC8;
extern s32 D_psp_09283E48;
extern s32 D_psp_09283E80;
extern s32 D_psp_09283E98;
extern s32 D_psp_09283EB0;
extern s32 D_psp_09283EC8;
extern s32 D_psp_09283EE0;
extern char** D_psp_09285BC0;
extern char** D_psp_09285BC8;
extern s32 D_psp_09285BD0;
extern s32 D_psp_09285BD8;
extern s32 D_psp_09285C28[][2];
extern s32 D_psp_09283A78[];
extern s32 D_psp_09283A98[];
extern s32 D_psp_09283AB8[];
extern s32 D_psp_09283AD8[];
extern s32 D_psp_09283AF8[];
extern s32 D_psp_09283B18[];
extern s32 D_psp_09283A48[];
extern s32 D_psp_09283A60[];
extern s32 D_psp_09285C58;
extern s32 D_psp_09285CD0;
extern s32 D_psp_09285CD8;
extern s32 D_psp_09285CE0;
extern s32 D_psp_09285BF0;
extern s32 D_psp_09285BF8;
extern s32 D_psp_09285C00;
extern s32 D_psp_09285C10;
extern s32 D_psp_09285C18;
extern s32 D_psp_09285C20;
extern s32* D_91CE250;
extern s32* D_91CE258;
extern s32* D_91CE200;
extern s32* D_91CE208;
extern s32* D_91CE210;
extern char* D_psp_09283FF8[];
extern char* D_psp_09284000[];
extern s32 D_psp_09285CF0;
extern s32 D_psp_09285CE8;
extern s32 D_psp_0928628C;
extern s32 D_psp_09286634;
extern u8* D_9186CC8[];
extern s32 D_psp_08B42050;
extern s8* D_psp_09284098;
extern s8* D_psp_092840B0;
extern char D_psp_09285BE0[];
extern char D_psp_092840B8[];
extern char D_psp_092840C8[];
extern char D_psp_092840D8[];
extern char D_psp_092840E8[];
extern char D_psp_092840F8[];
extern char D_9186D08[];
extern s32 D_psp_08B42054;
extern s32 D_psp_09285CF8;
extern char D_psp_09284108[];
extern char* D_91CE1F0;
extern char* D_91CE1F8;
extern s32 D_psp_09285D00;
extern s32 D_psp_09285C08;
extern s32 D_psp_09285CB8;
extern s32 D_91FC478;
extern s32 D_91FC488;
extern s32 D_91FC490;
extern s32 D_8B42044;
extern s32 D_91ED288;
extern char D_psp_09284110[];
extern char D_psp_09284120[];
extern char D_psp_09284140[];
extern char D_psp_09284160[];
extern u32 D_psp_09285BB0;
extern u32 D_psp_09285BB8;

#include "../../get_lang.h"

s32 func_psp_09237ED8(char* arg0, s32 arg1, s32 arg2) {
    s32 ret = arg1 + ((arg2 - func_890CAE0(arg0)) * 16) / 2;
    return ret;
}

void func_psp_092391A0(void);

void func_psp_09237F40(void) {
    D_psp_09285C20 = 1;
    D_psp_09285C18 = 0;
    D_psp_09285C10 = 0;
    D_psp_09285C00 = 0;
    D_psp_09285BF8 = 0;
    D_psp_09285BF0 = 0;
    func_psp_092391A0();
}

static void func_psp_09237F98(s32 arg0, s32 arg1) {
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[D_psp_09285C28[arg0][0]];
    for (i = 0; i < 8; i++, prim = prim->next) {
        prim->x0 = D_psp_09283A78[i] + 0x68;
        prim->y0 = D_psp_09283A98[i] + 0x58 + arg1;
        prim->u0 = D_psp_09283AB8[i];
        prim->v0 = D_psp_09283AD8[i];
        prim->u1 = D_psp_09283AF8[i];
        prim->v1 = D_psp_09283B18[i];
        prim->tpage = 0xC;
        prim->clut = 0x200;
        prim->priority = 0x11;
        prim->drawMode = DRAW_HIDE;
    }
}

void func_psp_092380E8(void) {
    Primitive* prim;
    s32 i;

    D_psp_09285C28[GFX_UNK_0][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_0][0]];
    SetTexturedPrimRect(prim, 0xD8, 0x10, 0x90, 0x48, 0, 0);
    func_psp_0923F9B8(prim);
    prim->tpage = 0xD;
    prim->clut = 0x201;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;
    for (i = 0; i < 5; i++) {
        D_psp_09285C28[i + 1][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
        prim = &g_PrimBuf[D_psp_09285C28[i + 1][0]];
        SetTexturedPrimRect(prim, i * 0x40 - 0x20, i * 0x28, 0x7F, 0x1F,
                            D_psp_09283A48[i], D_psp_09283A60[i]);
        func_psp_0923F9B8(prim);
        prim->tpage = 0xC;
        prim->clut = 0x200;
        prim->priority = 0x10;
        if (i == 0) {
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->drawMode = DRAW_COLORS;
        }
    }
    D_psp_09285C28[GFX_UNK_6][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_6][0]];
    SetTexturedPrimRect(prim, 0x20, 0xB0, 0x10, 0x30, 0xA0, 0x50);
    func_psp_0923F9B8(prim);
    prim->tpage = 0x17;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;
    memcpy(&D_psp_09285CD0, &D_psp_09285C58, 8U);
    memcpy(&D_psp_09285CD8, &D_psp_09285C58, 8U);
    memcpy(&D_psp_09285CE0, &D_psp_09285C58, 8U);
    D_psp_09285CD0 = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285CD0];
    func_psp_0923F9B8(prim);
    prim->tpage = 0x17;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;

    D_psp_09285CD8 = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285CD8];
    func_psp_0923F9B8(prim);
    prim->tpage = 0x17;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;

    D_psp_09285CE0 = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285CE0];
    func_psp_0923F9B8(prim);
    prim->tpage = 0x17;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_DEFAULT;

    D_psp_09285C28[GFX_UNK_7][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_7][0]];
    SetTexturedPrimRect(prim, 0x70, 0x30, 0xA0, 0x30, 0, 0x50);
    func_psp_0923F9B8(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_UNK_8][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_8][0]];
    SetTexturedPrimRect(prim, 0x80, 0x48, 0xF, 0xF, 0xF0, 0xF0);
    func_psp_0923F9B8(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x30;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_UNK_9][0] = g_api.AllocPrimitives(PRIM_SPRT, 3);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_9][0]];
    for (i = 0; i < 3;) {
        prim->x0 = (i << 7) + 0x30;
        prim->y0 = 0x60;
        prim->u0 = i << 7;
        prim->v0 = 0x78;
        prim->u1 = 0x80;
        prim->v1 = 0x78;
        if (i == 2) {
            prim->u0 = 0xE0;
            prim->v0 = 0;
            prim->u1 = 0x20;
        }
        prim->tpage = 0xD;
        prim->clut = 0x202;
        prim->priority = 0x10;
        prim->drawMode = DRAW_HIDE;
        i++;
        prim = prim->next;
    }
    D_psp_09285C28[GFX_UNK_10][0] = g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_10][0]];
    SetTexturedPrimRect(prim, 0x40, 0x68, 0x20, 0x20, 0, 0x48);
    func_psp_0923F9B8(prim);
    prim->tpage = 0xD;
    prim->clut = 0x204;
    prim->priority = 0x30;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_WND_SAVE_SUMMARY][0] =
        g_api.AllocPrimitives(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_WND_SAVE_SUMMARY][0]];
    SetTexturedPrimRect(prim, 0x68, 0x58, 0xB0, 0x50, 0, 0);
    func_psp_0923F9B8(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_UNK_12][0] = g_api.AllocPrimitives(PRIM_SPRT, 8);
    func_psp_09237F98(0xC, 0);

    D_psp_09285C28[GFX_WND_CARD_1][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_WND_CARD_1][0]];
    prim->x0 = 0x18;
    prim->y0 = 0x38;
    prim->u0 = 0xB0;
    prim->v0 = 0;
    prim->u1 = 0x50;
    prim->v1 = 0x78;
    func_psp_0923F9B8(prim);
    prim->tpage = 0x17;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_WND_CARD_2][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_WND_CARD_2][0]];
    prim->x0 = 0x118;
    prim->y0 = 0x38;
    prim->u0 = 0xB0;
    prim->v0 = 0;
    prim->u1 = 0x50;
    prim->v1 = 0x78;
    func_psp_0923F9B8(prim);
    prim->tpage = 0x17;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_UNK_15][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_15][0]];
    prim->x0 = 0x98;
    prim->y0 = 0x10;
    prim->u0 = 0;
    prim->v0 = 0x40;
    prim->u1 = 0xD0;
    prim->v1 = 0x20;
    func_psp_0923F9B8(prim);
    prim->tpage = 6;
    prim->clut = 0x1A1;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_UNK_16][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_16][0]];
    prim->x0 = 0xA0;
    prim->y0 = 0x60;
    prim->u0 = 0;
    prim->v0 = 0x60;
    prim->u1 = 0x70;
    prim->v1 = 0x30;
    func_psp_0923F9B8(prim);
    prim->tpage = 6;
    prim->clut = 0x1A1;
    prim->priority = 0x20;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_UNK_17][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_17][0]];
    prim->x0 = 0x60;
    prim->y0 = 0xC0;
    prim->u0 = 0;
    prim->v0 = 0x90;
    prim->u1 = 0x70;
    prim->v1 = 0x10;
    func_psp_0923F9B8(prim);
    prim->tpage = 6;
    prim->clut = 0x1A1;
    prim->priority = 0x20;
    prim->drawMode = DRAW_DEFAULT;

    D_psp_09285C28[GFX_UNK_18][0] = g_api.AllocPrimitives(PRIM_GT4, 2);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_18][0]];
    SetTexturedPrimRect(prim, 0x68, 0x30, 0xB0, 0x50, 0, 0);
    func_psp_0923F9B8(prim);
    prim->tpage = 0xC;
    prim->clut = 0x202;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;
    prim = prim->next;
    SetTexturedPrimRect(prim, 0xA8, 0x80, 0x30, 0x10, 0xB0, 0x80);
    func_psp_0923F9B8(prim);
    prim->tpage = 0xC;
    prim->clut = 0x200;
    prim->priority = 0x10;
    prim->drawMode = DRAW_HIDE;

    D_psp_09285C28[GFX_UNK_19][0] = g_api.AllocPrimitives(PRIM_SPRT, 8);
    func_psp_09237F98(0x13, -0x28);

    D_psp_09285C28[GFX_UNK_20][0] = g_api.AllocPrimitives(PRIM_SPRT, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_20][0]];
    prim->x0 = 0xA0;
    prim->y0 = 0x38;
    prim->u0 = 0;
    prim->v0 = 0xA0;
    prim->u1 = 0x70;
    prim->v1 = 0x30;
    func_psp_0923F9B8(prim);
    prim->tpage = 6;
    prim->clut = 0x1A1;
    prim->priority = 0x20;
    prim->drawMode = DRAW_HIDE;
}

static void func_psp_09238DA8(s32 gfxId, u16 drawMode) {
    Primitive* prim;

    prim = &g_PrimBuf[D_psp_09285C28[gfxId][0]];
    while (prim != NULL) {
        prim->drawMode = drawMode;
        prim = prim->next;
    }
}

void MenuHideAllGfx(void) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        func_psp_09238DA8(i, 8);
    }
}

void func_psp_09238E68(void) {
    s32 i;
    Primitive* prim;

    D_psp_09285BD8 = g_api.AllocPrimitives(PRIM_GT4, 3);
    prim = &g_PrimBuf[D_psp_09285BD8];
    for (i = 0; i < 3; i++, prim = prim->next) {
        SetTexturedPrimRect(prim, i << 7, 0, 0x80, 0xF0, 0, 0);
        func_psp_0923F9B8(prim);
        prim->tpage = i + 0x89;
        prim->clut = 0x210;
        prim->drawMode = DRAW_COLORS;
    }
    D_psp_09285BD0 = g_api.AllocPrimitives(PRIM_TILE, 2);
    prim = &g_PrimBuf[D_psp_09285BD0];
    for (i = 0; prim != NULL; i++, prim = prim->next) {
        prim->x0 = (i & 1) * 0xC0;
        prim->u0 = 0xC0;
        prim->v0 = 0xF0;
        func_psp_0923F948(prim, 0xFF);
        prim->priority = 0x1FD;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
    }
}

s32 func_psp_09238FE8(void) {
    s32 var_s1;
    Primitive* prim;

    prim = &g_PrimBuf[D_psp_09285BD0];
    var_s1 = prim->r0;
    var_s1 -= 0x10;
    if (var_s1 < 0) {
        var_s1 = 0;
    }
    func_psp_0923F948(prim, var_s1);
    prim = prim->next;
    func_psp_0923F948(prim, var_s1);
    if (var_s1 != 0) {
        return 0;
    }
    prim = &g_PrimBuf[D_psp_09285BD0];
    prim->drawMode = DRAW_HIDE;
    prim = prim->next;
    prim->drawMode = DRAW_HIDE;
    return 1;
}

s32 func_psp_092390B8(void) {
    s32 var_s1;
    Primitive* prim;

    prim = &g_PrimBuf[D_psp_09285BD0];
    prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
    var_s1 = prim->r0;
    var_s1 += 0x10;
    if (var_s1 > 0xFF) {
        var_s1 = 0xFF;
    }
    func_psp_0923F948(prim, var_s1);
    prim = prim->next;
    prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
    func_psp_0923F948(prim, var_s1);

    if (g_api.func_80131F68()) {
        return 0;
    } else {
        return var_s1 == 0xFF;
    }
}

void func_psp_09239180(void) { func_psp_0923FB40(); }

void func_psp_092391A0(void) {
    D_psp_09285BC8 = GetLang(&D_psp_09283BE8, &D_psp_09283E48, &D_psp_09283CA8,
                             &D_psp_09283DC8, &D_psp_09283D30);
    D_psp_09285BC0 = GetLang(&D_psp_09283E80, &D_psp_09283EE0, &D_psp_09283E98,
                             &D_psp_09283EC8, &D_psp_09283EB0);
}

void PrintFileSelectPlaceName(s32 port, s32 slot, s32 arg2) {
    DrawImages8x8(D_91CE258[g_SaveSummary[port].stage[slot]], 0xA0, arg2, 1);
    DrawImages8x8(
        D_91CE250[g_SaveSummary[port].stage[slot]], 0xA0, arg2 + 8, 1);
}

void func_psp_092392F8(s32 port, s32 slot, s32 textId) {
    char playerName[0x20];
    s32 i;

    playerName[0] = '\0';
    for (i = 0; i < 8; i++) {
        s32 charIndex = func_psp_092404A8(g_SaveSummary[port].name[slot][i]);
        strcat(playerName, D_psp_09284000[charIndex]);
    }
    func_psp_09240000(playerName, textId);
    if (g_SaveSummary[port].character[slot] == 1) {
        func_psp_0923FEC0(0, textId + 2);
    } else if (g_SaveSummary[port].character[slot] == 2) {
        func_psp_0923FEC0(1, textId + 2);
    } else if (g_SaveSummary[port].kind[slot] & 1) {
        func_psp_0923FEC0(2, textId + 2);
    } else if (g_SaveSummary[port].kind[slot] & 2) {
        func_psp_0923FEC0(3, textId + 2);
    } else {
        func_psp_0923FFB8(D_psp_09283FF8, textId + 2);
    }
}

void func_psp_09239530(SaveData* arg0) {
    char playerName[0x20];
    s32 i;
    s32 id = 6;

    playerName[0] = '\0';
    for (i = 0; i < 8; i++) {
        s32 charIndex = func_psp_092404A8(arg0->info.name[i]);
        strcat(playerName, D_psp_09284000[charIndex]);
    }
    func_psp_0923FF70(playerName, id);
    func_psp_0923FEC0(4, id + 2);
}

void func_psp_092395E8(void) {
    DrawImages8x8(D_psp_09285BC8[5], 0x30, 0xC4, 1);
    DrawImages8x8(D_psp_09285BC8[6], 0x30, 0xD4, 1);
}

void func_psp_09239640(s32 gfxId, s16 x, s16 y) {
    Primitive* prim;

    func_psp_09238DA8(gfxId, 0);
    prim = &g_PrimBuf[D_psp_09285C28[gfxId][0]];
    SetTexturedPrimRect(prim, x, y, 0x10, 0x10, 0xA0, 0x50);
}

void func_psp_092396D8(s32 gfxId, s16 x, s16 y) {
    Primitive* prim;

    func_psp_09238DA8(gfxId, 0);
    prim = &g_PrimBuf[D_psp_09285C28[gfxId][0]];
    if (D_psp_08B42050 == 0x2000) {
        SetTexturedPrimRect(prim, x, y, 0x10, 0x10, 0xA0, 0x60);
    } else {
        SetTexturedPrimRect(prim, x, y, 0x10, 0x10, 0xA0, 0x70);
    }
}

void func_psp_092397B8(s32 gfxId, s16 x, s16 y) {
    Primitive* prim;

    func_psp_09238DA8(gfxId, 0);
    prim = &g_PrimBuf[D_psp_09285C28[gfxId][0]];
    if (D_psp_08B42050 == 0x2000) {
        SetTexturedPrimRect(prim, x, y, 0x10, 0x10, 0xA0, 0x70);
    } else {
        SetTexturedPrimRect(prim, x, y, 0x10, 0x10, 0xA0, 0x60);
    }
}

void func_psp_09239898(s32 gfxId, s16 x, s16 y) {
    Primitive* prim;

    func_psp_09238DA8(gfxId, 0);
    prim = &g_PrimBuf[D_psp_09285C28[gfxId][0]];
    SetTexturedPrimRect(prim, x, y, 0x10, 0x10, 0xA0, 0x80);
}

void func_psp_09239930(s32 arg0) {
    s32 y = 0;

    func_psp_09238DA8(6, 8);
    func_psp_09238DA8(0x15, 8);
    func_psp_09238DA8(0x16, 8);
    func_psp_09238DA8(0x17, 8);
    switch (arg0) {
    case 0:
        func_psp_09239640(6, 0x20, y + 0xB0);
        y += 0x10;
        func_psp_092396D8(0x15, 0x20, y + 0xB0);
        y += 0x10;
        func_psp_092397B8(0x16, 0x20, y + 0xB0);
        y += 0x10;
        break;

    case 1:
        func_psp_09239640(6, 0x120, y + 0x20);
        y += 0x10;
        func_psp_092396D8(0x15, 0x120, y + 0x20);
        y += 0x10;
        func_psp_092397B8(0x16, 0x120, y + 0x20);
        y += 0x10;
        func_psp_09239898(0x17, 0x120, y + 0x20);
        y += 0x10;
        break;

    case 2:
        func_psp_092396D8(6, 0x20, y + 0xC0);
        y += 0x10;
        func_psp_092397B8(0x15, 0x20, y + 0xC0);
        y += 0x10;
        func_psp_092395E8();
        break;

    case 3:
        func_psp_092396D8(6, 0x18, y + 0xC0);
        y += 0x10;
        DrawImages8x8(D_psp_09285BC8[7], 0x28, 0xC4, 1);
        break;

    case 4:
        func_psp_09239640(6, 0x20, y + 0xB8);
        y += 0x10;
        func_psp_092396D8(0x15, 0x20, y + 0xB8);
        y += 0x10;
        break;
    }
}

void func_psp_09239B78(void) {
    func_psp_09238DA8(6, 8);
    func_psp_09238DA8(0x15, 8);
    func_psp_09238DA8(0x16, 8);
    func_psp_09238DA8(0x17, 8);
}

void func_psp_09239BD0(void) {
    Primitive* prim;
    s32 i;

    func_psp_09239930(4);
    DrawImages8x8(D_psp_09285BC8[0], 0x30, 0xBC, 1);
    DrawImages8x8(D_psp_09285BC8[1], 0x30, 0xCC, 1);
    func_psp_09240618(D_91CE210, 0xF0, 0x20, 0, 0x50);
    func_psp_09240618(D_91CE208, 0x100, 0x30, 0, 0x50);
    func_psp_09240618(D_91CE200, 0xE8, 0x40, 0, 0x50);

    for (i = 0; i < 5; i++) {
        prim = &g_PrimBuf[D_psp_09285C28[i + 1][0]];
        if (i == D_psp_09285C20) {
            prim->clut = 0x203;
        } else {
            prim->clut = 0x200;
        }
    }
}

void func_psp_09239D18(void) {
    if (g_pads[0].tapped & (PAD_RIGHT | PAD_DOWN)) {
        g_api.PlaySfx(SFX_UI_MP_FULL);
        D_psp_09285C20++;
        if (D_psp_09285C20 == 5) {
            D_psp_09285C20 = 1;
        }
    }
    if (g_pads[0].tapped & (PAD_LEFT | PAD_UP)) {
        g_api.PlaySfx(SFX_UI_MP_FULL);
        D_psp_09285C20--;
        if (D_psp_09285C20 == 0) {
            D_psp_09285C20 = 4;
        }
    }
    func_psp_0923FFB8(D_psp_09285BC0[D_psp_09285C20], 9);
}

void func_psp_09239E18(void) {
    s32 i;
    s32 nSpaces;
    s8* strPtr;

    // check if the name only contain spaces
    nSpaces = 0;
    for (i = 0; i < 8; i++) {
        g_Status.saveName[i] = D_psp_09285BE0[i];
        if (D_psp_09285BE0[i] == ' ') {
            nSpaces++;
        }
    }

    // if it only contain spaces, set a default name
    if (nSpaces == 8) {
        STRCPY(g_Status.saveName, D_psp_092840B8);
    }

    g_Status.saveName[8] = 0;
    g_Status.saveName[9] = 0;

    // check if the name is Richter
    strPtr = D_psp_09284098;
    for (i = 0; i < 8; i++) {
        if (g_Status.saveName[i] != *strPtr++) {
            break;
        }
    }

    if (g_IsTimeAttackUnlocked != SAVE_FLAG_NORMAL) {
        g_IsTimeAttackUnlocked = SAVE_FLAG_REPLAY;
    }

    // play as Richter only if the game was previously cleared
    if (i == 8 && g_IsTimeAttackUnlocked != SAVE_FLAG_NORMAL) {
        g_PlayableCharacter = PLAYER_RICHTER;
    } else {
        g_PlayableCharacter = PLAYER_ALUCARD;
    }

    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        strPtr = D_psp_092840B0;
        for (i = 0; i < 8; i++) {
            if (g_Status.saveName[i] != *strPtr++) {
                break;
            }
        }
        if (i == 8 && g_IsTimeAttackUnlocked != SAVE_FLAG_NORMAL) {
            g_PlayableCharacter = PLAYER_MARIA;
        }
    }
}

void func_psp_0923A010(void) {
    Primitive* prim;

    DrawImages8x8(D_psp_09285BC8[0], 0x130, 0x24, 1);
    DrawImages8x8(D_psp_09285BC8[3], 0x130, 0x34, 1);
    DrawImages8x8(D_psp_09285BC8[2], 0x130, 0x44, 1);
    DrawImages8x8(D_psp_09285BC8[1], 0x130, 0x54, 1);
    DrawString16x16(D_psp_092840C8, 0x48, 0x70, 1);
    DrawString16x16(D_psp_092840D8, 0x48, 0x88, 1);
    DrawString16x16(D_psp_092840E8, 0x48, 0xA0, 1);
    DrawString16x16(D_psp_092840F8, 0x48, 0xB8, 1);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_8][0]];
    SetTexturedPrimRect(
        prim, (D_psp_09285C18 * 0x10) + 0x80, 0x48, 0xF, 0xF, 0xF0, 0xF0);
    prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_10][0]];
    SetTexturedPrimRect(
        prim, ((D_psp_09285C10 & 7) << 5) + 0x40,
        ((D_psp_09285C10 & 0x18) * 3) + 0x68, 0x20, 0x20, 0, 0x48);
    if (g_Timer & 8) {
        func_psp_09238DA8(8, 0);
    } else {
        func_psp_09238DA8(8, 8);
    }
    DrawString16x16(D_psp_09285BE0, 0x80, 0x48, 1);
}

void func_psp_0923A230(void) {
    if (g_pads[0].repeat & PAD_RIGHT) {
        g_api.PlaySfx(SFX_UI_MOVE);
        D_psp_09285C10 = (D_psp_09285C10 & 0x18) | ((D_psp_09285C10 + 1) & 7);
    }

    if (g_pads[0].repeat & PAD_DOWN) {
        g_api.PlaySfx(SFX_UI_MOVE);
        D_psp_09285C10 = ((D_psp_09285C10 + 8) & 0x18) | (D_psp_09285C10 & 7);
    }

    if (g_pads[0].repeat & PAD_LEFT) {
        g_api.PlaySfx(SFX_UI_MOVE);
        D_psp_09285C10 = (D_psp_09285C10 & 0x18) | ((D_psp_09285C10 - 1) & 7);
    }

    if (g_pads[0].repeat & PAD_UP) {
        g_api.PlaySfx(SFX_UI_MOVE);
        D_psp_09285C10 = ((D_psp_09285C10 - 8) & 0x18) | (D_psp_09285C10 & 7);
    }

    if (g_pads[0].tapped & (PAD_R1 | PAD_R2)) {
        g_api.PlaySfx(SFX_UI_MP_FULL);
        D_psp_09285C18++;
        if (D_psp_09285C18 == 8) {
            D_psp_09285C18 = 0;
        }
    }

    if (g_pads[0].tapped & (PAD_L1 | PAD_L2)) {
        g_api.PlaySfx(SFX_UI_MP_FULL);
        D_psp_09285C18--;
        if (D_psp_09285C18 == -1) {
            D_psp_09285C18 = 7;
        }
    }

    if (g_pads[0].tapped & D_psp_08B42050) {
        g_api.PlaySfx(0x8CD);
        D_psp_09285BE0[D_psp_09285C18] = D_9186D08[D_psp_09285C10];
        D_psp_09285C18++;
        if (D_psp_09285C18 == 8) {
            D_psp_09285C18 = 0;
        }
    }

    if (g_pads[0].tapped & D_psp_08B42054) {
        D_psp_09285C18--;
        if (D_psp_09285C18 == -1) {
            D_psp_09285C18 = 7;
        }
        D_psp_09285BE0[D_psp_09285C18] = ' ';
    }
}

void func_psp_0923A558(s32 arg0) {
    s32 temp_s0;

    temp_s0 = D_psp_09285C00;
    if ((D_psp_0928628C >= 0) || (D_psp_09286634 >= 0)) {
        if (g_pads[0].repeat & PAD_RIGHT) {
            g_api.PlaySfx(SFX_UI_MOVE);
            D_psp_09285BF8 = (D_psp_09285BF8 + 1) % 3;
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            g_api.PlaySfx(SFX_UI_MOVE);
            D_psp_09285BF0 = (D_psp_09285BF0 + 4) % 5;
        }
        if (g_pads[0].repeat & PAD_LEFT) {
            g_api.PlaySfx(SFX_UI_MOVE);
            D_psp_09285BF8 = (D_psp_09285BF8 + 2) % 3;
        }
        if (g_pads[0].repeat & PAD_UP) {
            g_api.PlaySfx(SFX_UI_MOVE);
            D_psp_09285BF0 = (D_psp_09285BF0 + 1) % 5;
        }
        D_psp_09285C00 = (D_psp_09285BF8 % 3) + (D_psp_09285BF0 * 3) +
                         (D_psp_09285BF8 / 3) * 0xF;
        if (temp_s0 != D_psp_09285C00 && arg0) {
            if (g_SaveSummary[temp_s0 / 15].slot[temp_s0 % 15] ==
                func_8919560()) {
                D_psp_09285CF8 = 0xFF;
            }
        }
    }
}

void func_psp_0923A7C8(s32 flags, s32 arg1) {
    s32 slot;
    Primitive* prim;
    s32 percLo;
    s32 hideButtons;
    s32 sp4c;
    SaveData* save;

    s32 icon;
    s32 x;
    s32 y;
    s32 port;
    s32 temp_v1;
    s32 percHi;
    s32 color;
    s32 tge;
    s32 i;

    temp_v1 = flags & 0x7F;
    hideButtons = flags & 0x80;
    port = D_psp_09285C00 / 15;
    slot = D_psp_09285C00 % 15;
    y = arg1 * 0x38;
    prim = &g_PrimBuf[D_psp_09285C28[11][0]];
    SetTexturedPrimRect(prim, 0x68, y + 0x58, 0xB0, 0x50, 0, 0);
    if (temp_v1 > 0) {
        if ((g_SaveSummary[port].padding == -3) || (temp_v1 == 3)) {
            func_psp_09238DA8(0xC, 8);
            func_psp_09238DA8(0x10, 8);
            sp4c = func_psp_09237ED8(D_91CE1F8, 0x80, 8);
            DrawString16x16(D_91CE1F8, sp4c, y + 0x78, 1);
        } else if (
            (temp_v1 == 4) ||
            ((port == 0) && g_SaveSummary[port].slot[slot] == func_8919560())) {
            func_8919638(g_Pix, 0x2000);
            save = (SaveData*)g_Pix;
            func_psp_09237F98(0xC, y);
            func_psp_09238DA8(0xC, 0);
            func_psp_09238DA8(0x10, 0);
            prim = &g_PrimBuf[D_psp_09285C28[16][0]];
            prim->y0 = y + 0x60;
            func_psp_09239530(save);
            PrintFileSelectPlaceName(port, slot, y + 0x70);
            func_psp_09240888(save->info.level, 0x94, y + 0x90, 1);
            func_psp_09240888(save->info.playHours, 0xC8, y + 0x90, 1);
            func_psp_09240920(save->info.playMinutes, 0xE0, y + 0x90, 1);
            func_psp_09240920(save->info.playSeconds, 0xF8, y + 0x90, 1);
            func_psp_09240888(save->info.gold, 0xB4, y + 0x98, 1);
            percHi = save->info.nRoomsExplored;
            percHi = (percHi * 1000) / 942;
            percLo = percHi % 10;
            percHi = percHi / 10;
            func_psp_09240888(percHi, 0xE8, y + 0x98, 1);
            func_psp_09240330(
                0xF0, y + 0x9C, 8, 4, 0xE0, 0x8C, 0x200, 0xC, 1, 0x80);
            func_psp_09240888(percLo, 0xF8, y + 0x98, 1);
        } else {
            icon = g_SaveSummary[port].icon[slot];
            if ((icon >= 0) && (g_SaveSummary[port].padding != -3)) {
                func_psp_09237F98(0xC, y);
                func_psp_09238DA8(0xC, 0);
                func_psp_09238DA8(0x10, 0);
                prim = &g_PrimBuf[D_psp_09285C28[16][0]];
                prim->y0 = y + 0x60;
                func_psp_092392F8(port, slot, 6);
                PrintFileSelectPlaceName(port, slot, y + 0x70);
                func_psp_09240888(
                    g_SaveSummary[port].level[slot], 0x94, y + 0x90, 1);
                func_psp_09240888(
                    g_SaveSummary[port].playHours[slot], 0xC8, y + 0x90, 1);
                func_psp_09240920(
                    g_SaveSummary[port].playMinutes[slot], 0xE0, y + 0x90, 1);
                func_psp_09240920(
                    g_SaveSummary[port].playSeconds[slot], 0xF8, y + 0x90, 1);
                func_psp_09240888(
                    g_SaveSummary[port].gold[slot], 0xB4, y + 0x98, 1);
                percHi = g_SaveSummary[port].nRoomsExplored[slot];
                percHi = (percHi * 1000) / 942;
                percLo = percHi % 10;
                percHi = percHi / 10;
                func_psp_09240888(percHi, 0xE8, y + 0x98, 1);
                func_psp_09240330(
                    0xF0, y + 0x9C, 8, 4, 0xE0, 0x8C, 0x200, 0xC, 1, 0x80);
                func_psp_09240888(percLo, 0xF8, y + 0x98, 1);
            } else {
                func_psp_09238DA8(0xC, 8);
                func_psp_09238DA8(0x10, 8);
                if (icon == -2) {
                    DrawString16x16(D_psp_09284108, 0xA0, y + 0x78, 1);
                } else if (temp_v1 == 2) {
                    sp4c = func_psp_09237ED8(D_91CE1F0, 0x88, 7);
                    DrawString16x16(D_91CE1F0, sp4c, y + 0x78, 1);
                } else {
                    sp4c = func_psp_09237ED8(D_91CE1F8, 0x80, 8);
                    DrawString16x16(D_91CE1F8, sp4c, y + 0x78, 1);
                }
            }
        }
    }

    if (!hideButtons) {
        DrawImages8x8(D_psp_09285BC8[0], 0x30, 0xB4, 1);
        DrawImages8x8(D_psp_09285BC8[1], 0x30, 0xC4, 1);
        DrawImages8x8(D_psp_09285BC8[2], 0x30, 0xD4, 1);
    }

    for (port = 0; port < 2; port++) {
        switch (g_SaveSummary[port].padding) {
        case -1:
            break;
        case -2:
            DrawImages8x8(D_psp_09285BC8[4], (port << 8) + 0x28, 0x6C, 1);
            break;
        case -3:
            DrawImages8x8(D_psp_09285BC8[8], (port << 8) + 0x32, 0x6C, 1);
            break;
        default:
            for (i = 0; i < 0xF; i++) {
                icon = g_SaveSummary[port].icon[i];
                x = 0x20 + (i % 3) * 0x18 + port * 0x100;
                y = 0x90 - (i / 3) * 0x10;
                if ((D_psp_09285BF8 == ((i % 3) + (port * 3))) &&
                    (temp_v1 != 3) && ((i / 3) == D_psp_09285BF0) &&
                    (temp_v1 > 0) && (D_psp_09285CF0 == 0)) {
                    tge = 0;
                    if (g_Timer & 0x10) {
                        color = g_Timer & 0xF;
                    } else {
                        color = 0xF - (g_Timer & 0xF);
                    }
                    color = color * 8 + 0x80;
                } else {
                    tge = 0;
                    color = 0x40;
                }
                if (icon == -3) {
                    func_psp_09240330(
                        x, y, 0x10, 0x10, 0x80, 0x80, 0x200, 0xC, tge, color);
                }
                if (icon >= 0) {
                    if (g_SaveSummary[i / 15].slot[i % 15] == func_8919560()) {
                        func_psp_09240330(x, y, 0x10, 0x10, 0x90, 0x80, 0x200,
                                          0x17, tge, color);
                    }
                    func_psp_09240330(x, y, 0x10, 0x10, icon * 0x10,
                                      (D_psp_09285D00 % 3) * 0x10, icon + 0x220,
                                      0x16, tge, color);
                }
            }
            break;
        }
    }
}

void func_psp_0923B498(void) {
    Primitive* prim;
    s32 port;
    s32 slot;
    s32 percLo;
    s32 percHi;
    s32 icon;

    port = D_psp_09285C08 / 15;
    slot = D_psp_09285C08 % 15;
    icon = g_SaveSummary[port].icon[slot];
    func_psp_09238DA8(0x12, 0x11);
    prim = &g_PrimBuf[D_psp_09285CB8];
    prim = prim->next;
    SetTexturedPrimRect(
        prim, 0xA8, (D_psp_09285D00 % 3) + 0x7F, 0x30, 0x10, 0xB0, 0x80);
    prim->drawMode = DRAW_DEFAULT;
    func_psp_09238DA8(0x13, 0);
    func_psp_09238DA8(0x14, 0);
    func_psp_092392F8(port, slot, 0xA);
    PrintFileSelectPlaceName(port, slot, 0x48);
    func_psp_09240888(g_SaveSummary[port].level[slot], 0x94, 0x68, 1);
    func_psp_09240888(g_SaveSummary[port].playHours[slot], 0xC8, 0x68, 1);
    func_psp_09240920(g_SaveSummary[port].playMinutes[slot], 0xE0, 0x68, 1);
    func_psp_09240920(g_SaveSummary[port].playSeconds[slot], 0xF8, 0x68, 1);
    func_psp_09240888(g_SaveSummary[port].gold[slot], 0xB4, 0x70, 1);
    percHi = g_SaveSummary[port].nRoomsExplored[slot];
    percHi = (percHi * 1000) / 942;
    percLo = percHi % 10;
    percHi = percHi / 10;
    func_psp_09240888(percHi, 0xE8, 0x70, 1);
    func_psp_09240330(0xF0, 0x74, 8, 4, 0xE0, 0x8C, 0x200, 0xC, 1, 0x80);
    func_psp_09240888(percLo, 0xF8, 0x70, 1);
}

void func_psp_0923B800(void) {
    Primitive* prim;
    s32 i;

    MenuHideAllGfx();
    func_psp_09238DA8(0, 0);

    for (i = 1; i < 5; i++) {
        func_psp_09238DA8(i + 1, 4);
        prim = &g_PrimBuf[D_psp_09285C28[i + 1][0]];
        SetTexturedPrimRect(prim, (i << 6) - 0x20, i * 0x28, 0x7F, 0x1F,
                            D_psp_09283A48[i], D_psp_09283A60[i]);
    }

    func_psp_09239930(0);
    func_psp_09238DA8(0x11, 0);
}

void func_psp_0923B908(s32 arg0) {
    Primitive* prim;

    D_psp_09285C18 = 0;
    D_psp_09285C10 = 0;
    MenuHideAllGfx();
    func_psp_09238DA8(GFX_UNK_7, 0x11);
    func_psp_09238DA8(GFX_UNK_8, 0);
    func_psp_09238DA8(GFX_UNK_9, 0x11);
    func_psp_09238DA8(GFX_UNK_10, 0);
    if (arg0 == 0) {
        func_psp_09238DA8(1, 0);
        prim = &g_PrimBuf[D_psp_09285C28[GFX_UNK_1][0]];
        SetPrimRect(prim, 0x18, 0x18, 0x7F, 0x1F);
    } else {
        func_psp_09238DA8(3, 0);
        prim = &g_PrimBuf[D_psp_09285C28[GFX_FILE_DELETE][0]];
        SetPrimRect(prim, 0x18, 0x18, 0x7F, 0x1F);
    }

    func_psp_09239930(1);
}

void func_psp_0923BA40(s32 cursor) {
    Primitive* prim;
    s32 gfxId;

    g_SaveSummary[0].padding = 0;
    g_SaveSummary[1].padding = 0;
    MenuHideAllGfx();
    func_psp_09238DA8(GFX_WND_SAVE_SUMMARY, 0x11);
    func_psp_09238DA8(GFX_WND_CARD_1, 0x11);
    func_psp_09238DA8(GFX_WND_CARD_2, 0x11);
    func_psp_09238DA8(GFX_UNK_15, 0);

    switch (cursor) {
    case MAIN_MENU_CURSOR_FILE_SELECT:
        gfxId = GFX_FILE_SELECT;
        break;
    case MAIN_MENU_CURSOR_NAME_CHANGE:
        gfxId = GFX_NAME_CHANGE;
        break;
    case MAIN_MENU_CURSOR_FILE_COPY:
        gfxId = GFX_FILE_COPY;
        break;
    case MAIN_MENU_CURSOR_FILE_DELETE:
        gfxId = GFX_FILE_DELETE;
        break;
    }
    func_psp_09238DA8(gfxId, 0);
    // Relocate the graphics at the top-left of the screen
    prim = &g_PrimBuf[D_psp_09285C28[gfxId][0]];
    SetPrimRect(prim, 0x10, 0x10, 0x7F, 0x1F);
    prim->clut = 0x200;
}

void func_psp_0923BB88(void) {
    s32 i;
    u8* ptr;

    for (i = 0; i < 0x10; i++) {
        ptr = D_9186CC8[i];
        LoadTPage((u_long*)ptr, 0, 0, (i * 4) + 0x180, 0x100, 0x10, 0x30);
    }

    g_api.func_800EA5E4(ANIMSET_OVL(4));
}

static void func_psp_0923BC20(void) {
    s32 isCard0Full;
    s32 isCard1Full;
    s32 i;

    isCard0Full = true;
    isCard1Full = true;
    for (i = 0; i < BLOCK_PER_CARD; i++) {
        if (g_SaveSummary[0].icon[i] != -2) {
            isCard0Full = false;
        }
        if (g_SaveSummary[1].icon[i] != -2) {
            isCard1Full = false;
        }
    }

    D_psp_09285CF0 = 0;
    if ((g_SaveSummary[0].padding < 0 || isCard0Full) &&
        (g_SaveSummary[1].padding < 0 || isCard1Full)) {
        D_psp_09285CF0 = 1;
    }

    D_psp_09285CE8 = 0;
    for (i = 0; i < BLOCK_PER_CARD; i++) {
        if ((g_SaveSummary[0].padding > 0 && g_SaveSummary[0].icon[i] == -3) ||
            (g_SaveSummary[1].padding > 0 && g_SaveSummary[1].icon[i] == -3)) {
            break;
        }
    }
    if (i == BLOCK_PER_CARD) {
        D_psp_09285CE8 = 1;
    }
}

static void func_psp_0923BD98(void) {
    s32 i;

    for (i = 0; i < BLOCK_PER_CARD; i++) {
        if (g_SaveSummary[0].icon[i] >= 0 || g_SaveSummary[1].icon[i] >= 0) {
            break;
        }
    }

    if (i == BLOCK_PER_CARD) {
        D_psp_09285CF0 = 1;
    }
}

void func_psp_0923BE20(void) {
    s32 port;
    s32 slot;
    s32 var_s5;
    s32 temp_s1;
    s32 i;
    s32 var_s4;

    func_psp_0923FBF0();
    switch (g_GameEngineStep) {
    case 0x0:
        g_api.PlaySfx(0x32F);
        g_GameTimer = 0;
        D_psp_09285D00 = 0;
        func_psp_09241BF8();
        func_psp_0923F760();
        g_api.func_800EA5E4(0);
        g_api.func_800EA5E4(0x8000);
        g_api.func_800EA5E4(0x8001);
        g_api.func_800EA5E4(0x8002);
        g_api.func_800EA5E4(0x8003);
        func_psp_09237F40();
        func_psp_09238E68();
        func_psp_092380E8();
        func_psp_09239180();
        func_psp_09237C38();
        func_psp_0923BB88();
        func_psp_0923FC08(9);
        func_psp_09239BD0();
        D_8B42044 = 0;
        g_GameEngineStep++;
        break;
    case 0x1:
        func_psp_09239D18();
        func_psp_09239BD0();
        if (func_psp_09238FE8()) {
            g_GameEngineStep++;
        }
        break;
    case 0x2:
        func_psp_09239D18();
        func_psp_09239BD0();
        if (g_pads[0].tapped & D_psp_08B42050) {
            switch (D_psp_09285C20) {
            case 0:
                g_api.PlaySfx(0x633);
                g_GameEngineStep = 0x10;
                break;
            case 1:
                g_api.PlaySfx(0x633);
                g_GameEngineStep = 0x30;
                break;
            case 2:
                g_api.PlaySfx(0x633);
                g_GameEngineStep = 0x90;
                break;
            case 3:
                g_api.PlaySfx(0x633);
                g_GameEngineStep = 0x50;
                break;
            case 4:
                g_api.PlaySfx(0x633);
                g_GameEngineStep = 0x70;
                break;
            default:
                g_api.PlaySfx(0x686);
                break;
            }
        }
        break;
    case 0x3:
        func_psp_09239D18();
        func_psp_09239BD0();
        if (func_psp_092390B8()) {
            func_psp_0923F460(1);
        }
        break;
    case 0x10:
        STRCPY(D_psp_09285BE0, D_psp_09284110);
        func_psp_0923B908(0);
        g_GameEngineStep++;
        /* fallthrough */
    case 0x11:
        for (i = 0; i < 8; i++) {
            if (D_psp_09285BE0[i] != ' ') {
                break;
            }
        }
        if ((g_pads[0].tapped & 1) || ((g_pads[0].tapped & D_psp_08B42054) &&
                                       (i == 8) && (D_psp_09285C18 == 0))) {
            g_GameEngineStep = 0x30;
        } else {
            func_psp_0923A230();
            func_psp_0923A010();
            if (g_pads[0].tapped & 8) {
                g_api.PlaySfx(0x633);
                func_psp_09239E18();
                if (g_PlayableCharacter == 0) {
                    g_StageId = STAGE_ST0;
                } else {
                    g_StageId = STAGE_NO3;
                }
                D_8003C730 = 0;
                D_91FC488 = -1;
                if (D_psp_09285CF0 != NULL) {
                    D_91FC490 = -1;
                } else {
                    D_91FC490 = D_psp_09285C00 / 15;
                }
                g_api.PlaySfx(0x80);
                g_GameEngineStep++;
            }
        }
        break;
    case 0x12:
        func_psp_0923A010();
        if (func_psp_092390B8()) {
            func_psp_0923F498();
            func_psp_0923F5C0();
            func_psp_0923F9E8();
            func_psp_09240A28();
            g_api.func_800EA538(0);
            if (g_PlayableCharacter == 0) {
                func_psp_0923F460(5);
            } else {
                g_GameStep++;
            }
        }
        break;
    case 0x30:
        func_psp_0923BA40(0);
        func_psp_0923FEC0(5, 4);
        func_psp_0923FEC0(6, 5);
        func_psp_09241F70();
        g_GameEngineStep++;
        /* fallthrough */
    case 0x31:
        func_psp_0923A7C8(0x80, 0);
        D_91FC478 = 0;
        if (func_psp_09242010()) {
            D_91FC478 = 1;
            g_GameEngineStep++;
            func_psp_0923BC20();
        }
        break;
    case 0x32:
        if (g_IsTimeAttackUnlocked == 0) {
            D_psp_09285CF8 = 0xFF;
        } else {
            D_psp_09285CF8 = 0x2FF;
        }
        if (D_psp_0928628C < 0) {
            D_psp_09285BF8 = (D_psp_09285BF8 % 3) + 3;
        }
        if (D_psp_09286634 < 0) {
            D_psp_09285BF8 = D_psp_09285BF8 % 3;
        }
        if (D_psp_09285CF0 != NULL) {
            func_psp_0923FEC0(7, 4);
            func_psp_0923FEC0(8, 5);
            func_psp_0923A7C8(0x83, 0);
            func_psp_09239930(2);
            g_GameEngineStep = 0x40;
        } else if (func_8919560() == -1) {
            func_psp_0923FEC0(D_psp_09284120, 4);
            func_psp_0923FEC0(D_psp_09284140, 5);
            func_psp_0923A7C8(0x83, 0);
            func_psp_09239930(2);
            g_GameEngineStep = 0x1000;
        } else {
            func_psp_09239930(0);
            func_psp_0923A7C8(1, 0);
            func_psp_0923FFB8(D_psp_09283FF8, 4);
            func_psp_0923FFB8(D_psp_09283FF8, 5);
            g_GameEngineStep++;
        }
        break;
    case 0x1000:
        func_psp_0923A7C8(0x84, 0);
        func_psp_09239930(2);
        if (g_pads[0].tapped & D_psp_08B42054) {
            func_psp_09239930(0);
            func_psp_0923A7C8(1, 0);
            func_psp_0923FFB8(D_psp_09283FF8, 4);
            func_psp_0923FFB8(D_psp_09283FF8, 5);
            g_GameEngineStep = 0x33;
        } else if (g_pads[0].tapped & D_psp_08B42050) {
            func_8919638(g_Pix, 0x2000);
            func_913E220(g_Pix);
            if (g_Pix[0][0x1FFF] == 0xFF) {
                (void)0; // fake
            } else {
                D_8003C730 = 4;
                D_91ED288 = g_Pix[0][0x1FFE];
                D_91FC490 = 0;
                D_91FC488 = -1;
            }

            g_api.PlaySfx(0x80);
            g_GameEngineStep = 0x104;
        }
        break;
    case 0x40:
        func_psp_0923A7C8(0x81, 0);
        func_psp_09239930(2);
        if (g_pads[0].tapped & D_psp_08B42054) {
            func_psp_0923B800();
            func_psp_09239BD0();
            g_GameEngineStep = 2;
        } else if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            g_GameEngineStep = 0x10;
        }
        break;
    case 0x41:
        func_psp_0923A7C8(0x83, 0);
        func_psp_09239930(2);
        if (g_pads[0].tapped & D_psp_08B42054) {
            D_psp_09285CF8 = 0xFF;
            func_psp_09239930(0);
            func_psp_0923FEC0(9, 4);
            func_psp_0923FEC0(0xA, 5);
            g_GameEngineStep = 0x33;
        } else if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            g_GameEngineStep = 0x10;
        }
        break;
    case 0x33:
        if (g_pads[0].tapped & D_psp_08B42054) {
            func_psp_0923B800();
            func_psp_09239BD0();
            g_GameEngineStep = 2;
        } else {
            func_psp_0923A558(1);
            func_psp_0923A7C8(1, 0);
            D_psp_09285CF8++;
            if (D_psp_09285CF8 == 0x100) {
                func_psp_0923FEC0(9, 4);
                func_psp_0923FEC0(0xA, 5);
            }
            if (D_psp_09285CF8 == 0x200) {
                if (D_psp_09285CE8 != NULL) {
                    func_psp_0923FEC0(0xB, 4);
                    func_psp_0923FEC0(0xC, 5);
                } else {
                    func_psp_0923FEC0(0xD, 4);
                    func_psp_0923FEC0(0xE, 5);
                }
                if (g_IsTimeAttackUnlocked == 0) {
                    D_psp_09285CF8 = 0;
                }
            }
            if (D_psp_09285CF8 == 0x300) {
                func_psp_0923FEC0(0xF, 4);
                func_psp_0923FEC0(0x10, 5);
            }
            if (D_psp_09285CF8 == 0x400) {
                func_psp_0923FEC0(0x11, 4);
                func_psp_0923FEC0(0x12, 5);
                D_psp_09285CF8 = 0;
            }
            if ((g_pads[0].tapped & 8) && (D_psp_09285CE8 != NULL)) {
                g_api.PlaySfx(0x633);
                func_psp_0923FEC0(7, 4);
                func_psp_0923FEC0(8, 5);
                func_psp_0923A7C8(0x81, 0);
                func_psp_09239930(2);
                g_GameEngineStep = 0x41;
            } else if (g_pads[0].tapped & D_psp_08B42050) {
                port = D_psp_09285C00 / 15;
                slot = D_psp_09285C00 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    g_api.PlaySfx(0x633);
                    g_GameEngineStep = 0x100;
                } else if (g_SaveSummary[port].icon[slot] == -3) {
                    g_api.PlaySfx(0x633);
                    g_GameEngineStep = 0x10;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 0x90:
        func_psp_0923BA40(3);
        func_psp_09238DA8(0xF, 0);
        func_psp_0923FEC0(5, 4);
        func_psp_0923FEC0(6, 5);
        func_psp_09241F70();
        g_GameEngineStep++;
        /* fallthrough */
    case 0x91:
        func_psp_0923A7C8(0x80, 0);
        D_91FC478 = 0;
        if (func_psp_09242010()) {
            D_91FC478 = 1;
            g_GameEngineStep++;
            func_psp_0923BC20();
        }
        break;
    case 0x92:
        func_psp_09238DA8(0xF, 0);
        if (D_psp_0928628C < 0) {
            D_psp_09285BF8 = (D_psp_09285BF8 % 3) + 3;
        }

        if (D_psp_09286634 < 0) {
            D_psp_09285BF8 = D_psp_09285BF8 % 3;
        }
        func_psp_0923BD98();
        if (D_psp_09285CF0 != NULL) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x13, 4);
            func_psp_0923A7C8(0x82, 0);
            func_psp_09239930(3);
            g_GameEngineStep = 0xA0;
        } else {
            func_psp_09239930(0);
            func_psp_0923A7C8(2, 0);
            func_psp_0923FEC0(0x14, 4);
            func_psp_0923FEC0(0x15, 5);
            g_GameEngineStep++;
        }
        break;
    case 0xA0:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 0);
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            func_psp_0923B800();
            func_psp_09239BD0();
            g_GameEngineStep = 2;
        }
        break;
    case 0x93:
        if (g_pads[0].tapped & D_psp_08B42054) {
            func_psp_0923B800();
            func_psp_09239BD0();
            g_GameEngineStep = 2;
        } else {
            func_psp_0923A558(0);
            func_psp_0923A7C8(2, 0);
            if (g_pads[0].tapped & D_psp_08B42050) {
                port = D_psp_09285C00 / 15;
                slot = D_psp_09285C00 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    g_api.PlaySfx(0x633);
                    g_GameEngineStep++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 0x94:
        STRCPY(D_psp_09285BE0, D_psp_09284110);
        func_psp_0923B908(1);
        g_GameEngineStep++;
        /* fallthrough */
    case 0x95:
        for (i = 0; i < 8; i++) {
            if (D_psp_09285BE0[i] != ' ') {
                break;
            }
        }
        if ((g_pads[0].tapped & 1) || ((g_pads[0].tapped & D_psp_08B42054) &&
                                       (i == 8) && (D_psp_09285C18 == 0))) {
            func_psp_0923BA40(3);
            g_GameEngineStep = 0x92;
        } else {
            func_psp_0923A230();
            func_psp_0923A010();
            if (g_pads[0].tapped & 8) {
                func_psp_0923BA40(3);
                var_s4 = 0;
                for (i = 0; i < 8; i++) {
                    if (D_psp_09285BE0[i] == ' ') {
                        var_s4++;
                    }
                }
                if (var_s4 == 8) {
                    g_GameEngineStep = 0x92;
                } else {
                    func_psp_09238DA8(0xF, 0);
                    func_psp_0923FEC0(0x16, 4);
                    func_psp_0923FEC0(0x17, 5);
                    g_api.PlaySfx(0x633);
                    g_GameEngineStep++;
                    if (g_SaveSummary[D_psp_09285C00 / 15]
                            .slot[D_psp_09285C00 % 15] == func_8919560()) {
                        var_s5 = func_8919570();
                    }
                }
            }
        }
        break;
    case 0x96:
        func_psp_09239B78();
        func_psp_0923A7C8(0x82, 0);
        func_psp_09242920(D_psp_09285C00, D_psp_09285C00);
        g_GameEngineStep++;
        break;
    case 0x97:
        func_psp_0923A7C8(0x82, 0);
        D_91FC478 = 0;
        temp_s1 = func_psp_09242BA0(&D_psp_09285BE0);
        if (temp_s1 != 0) {
            D_91FC478 = 1;
        }
        if (temp_s1 == 1) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x18, 4);
            func_psp_0923FEC0(0x19, 5);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep += 2;
        }
        if (temp_s1 == -1) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x1A, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep++;
        }
        if (temp_s1 == -3) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x1B, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep++;
        }
        break;
    case 0x98:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 0);
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            func_psp_09238DA8(0xF, 8);
            g_GameEngineStep = 0x90;
        }
        break;
    case 0x99:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 0);
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            g_GameEngineStep = 0x92;
        }
        break;
    case 0x50:
        func_psp_0923BA40(1);
        func_psp_0923FEC0(5, 4);
        func_psp_0923FEC0(6, 5);
        func_psp_09241F70();
        g_GameEngineStep++;
        /* fallthrough */
    case 0x51:
        func_psp_0923A7C8(0x80, 0);
        D_91FC478 = 0;
        if (func_psp_09242010()) {
            D_91FC478 = 1;
            g_GameEngineStep++;
            func_psp_0923BC20();
        }
        break;
    case 0x52:
        if (D_psp_0928628C < 0) {
            D_psp_09285BF8 = (D_psp_09285BF8 % 3) + 3;
        }
        if (D_psp_09286634 < 0) {
            D_psp_09285BF8 = D_psp_09285BF8 % 3;
        }
        func_psp_0923BD98();
        if (D_psp_09285CF0 != NULL) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x13, 4);
            func_psp_0923A7C8(0x82, 0);
            func_psp_09239930(3);
            g_GameEngineStep = 0x60;
        } else {
            func_psp_09239930(0);
            func_psp_0923A7C8(2, 0);
            func_psp_0923FEC0(0x1C, 4);
            func_psp_0923FEC0(0x1D, 5);
            g_GameEngineStep++;
        }
        break;
    case 0x60:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 0);
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            func_psp_0923B800();
            func_psp_09239BD0();
            g_GameEngineStep = 2;
        }
        break;
    case 0x53:
        if (g_pads[0].tapped & D_psp_08B42054) {
            func_psp_0923B800();
            func_psp_09239BD0();
            g_GameEngineStep = 2;
        } else {
            func_psp_0923A558(0);
            func_psp_0923A7C8(2, 0);
            if (g_pads[0].tapped & D_psp_08B42050) {
                port = D_psp_09285C00 / 15;
                slot = D_psp_09285C00 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    func_psp_0923FC08(5);
                    func_psp_0923FEC0(0x1E, 4);
                    func_psp_0923FEC0(0x1F, 5);
                    D_psp_09285C08 = D_psp_09285C00;
                    g_api.PlaySfx(0x633);
                    g_GameEngineStep++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 0x54:
        func_psp_0923A558(0);
        func_psp_0923A7C8(2, 1);
        func_psp_0923B498();
        if (g_pads[0].tapped & D_psp_08B42054) {
            func_psp_09238DA8(0x12, 8);
            func_psp_09238DA8(0x13, 8);
            func_psp_09238DA8(0x14, 8);
            func_psp_0923FEC0(0x1C, 4);
            func_psp_0923FEC0(0x1D, 5);
            g_GameEngineStep--;
        } else {
            if (g_pads[0].tapped & D_psp_08B42050) {
                port = D_psp_09285C00 / 15;
                slot = D_psp_09285C00 % 15;
                if (D_psp_09285C08 != D_psp_09285C00) {
                    if (g_SaveSummary[port].icon[slot] >= 0) {
                        func_psp_0923FEC0(0x20, 4);
                        func_psp_0923FEC0(0x21, 5);
                        g_api.PlaySfx(0x633);
                        g_GameEngineStep = 0x59;
                    } else if (g_SaveSummary[port].icon[slot] != -2) {
                        func_psp_0923FEC0(0x22, 4);
                        func_psp_0923FEC0(0x23, 5);
                        g_api.PlaySfx(0x633);
                        g_GameEngineStep++;
                    }
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 0x55:
        func_psp_09239B78();
        func_psp_0923A7C8(0x82, 1);
        func_psp_0923B498();
        func_psp_09242920(D_psp_09285C08, D_psp_09285C00);
        g_GameEngineStep++;
        break;
    case 0x56:
        func_psp_0923B498();
        D_91FC478 = 0;
        temp_s1 = func_psp_09242BA0(NULL);
        if (temp_s1 != 0) {
            D_91FC478 = 1;
        }
        if (temp_s1 == 1) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x24, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep += 2;
        }
        if (temp_s1 == -1) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x1A, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep++;
        }
        if (temp_s1 == -3) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x1B, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep++;
        }
        break;
    case 0x57:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 1);
        func_psp_0923B498();
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            func_psp_09238DA8(0xF, 8);
            g_GameEngineStep = 0x50;
        }
        break;
    case 0x58:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 1);
        func_psp_0923B498();
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            func_psp_09238DA8(0x12, 8);
            func_psp_09238DA8(0x13, 8);
            func_psp_09238DA8(0x14, 8);
            g_GameEngineStep = 0x52;
        }
        break;
    case 0x59:
        func_psp_09239930(2);
        func_psp_0923A7C8(0x82, 1);
        func_psp_0923B498();
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            func_psp_0923FEC0(0x22, 4);
            func_psp_0923FEC0(0x23, 5);
            g_GameEngineStep = 0x55;
        } else {
            if (g_pads[0].tapped & D_psp_08B42054) {
                func_psp_0923FC08(5);
                func_psp_0923FEC0(0x1E, 4);
                func_psp_0923FEC0(0x1F, 5);
                func_psp_09239930(0);
                g_GameEngineStep = 0x54;
            }
            func_psp_092395E8();
        }
        break;
    case 0x70:
        func_psp_0923BA40(2);
        func_psp_0923FEC0(5, 4);
        func_psp_0923FEC0(6, 5);
        func_psp_09241F70();
        g_GameEngineStep++;
        /* fallthrough */
    case 0x71:
        func_psp_0923A7C8(0x80, 0);
        D_91FC478 = 0;
        if (func_psp_09242010()) {
            D_91FC478 = 1;
            g_GameEngineStep++;
            func_psp_0923BC20();
        }
        break;
    case 0x72:
        if (D_psp_0928628C < 0) {
            D_psp_09285BF8 = (D_psp_09285BF8 % 3) + 3;
        }
        if (D_psp_09286634 < 0) {
            D_psp_09285BF8 = D_psp_09285BF8 % 3;
        }
        func_psp_0923BD98();
        if (D_psp_09285CF0 != NULL) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x13, 4);
            func_psp_0923A7C8(0x82, 0);
            func_psp_09239930(3);
            g_GameEngineStep = 0x80;
        } else {
            func_psp_09239930(0);
            func_psp_0923A7C8(2, 0);
            func_psp_0923FEC0(0x25, 4);
            func_psp_0923FEC0(0x26, 5);
            g_GameEngineStep++;
        }
        break;
    case 0x80:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 0);
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            func_psp_0923B800();
            func_psp_09239BD0();
            g_GameEngineStep = 2;
        }
        break;
    case 0x73:
        if (g_pads[0].tapped & D_psp_08B42054) {
            func_psp_0923B800();
            func_psp_09239BD0();
            g_GameEngineStep = 2;
        } else {
            func_psp_0923A558(0);
            func_psp_0923A7C8(2, 0);
            func_psp_09239930(0);
            if (g_pads[0].tapped & D_psp_08B42050) {
                port = D_psp_09285C00 / 15;
                slot = D_psp_09285C00 % 15;
                if (g_SaveSummary[port].icon[slot] >= 0) {
                    func_psp_0923FC08(5);
                    func_psp_0923FEC0(0x27, 4);
                    g_api.PlaySfx(0x633);
                    g_GameEngineStep++;
                } else {
                    g_api.PlaySfx(0x686);
                }
            }
        }
        break;
    case 0x74:
        func_psp_09239930(2);
        func_psp_0923A7C8(0x82, 0);
        if (g_pads[0].tapped & D_psp_08B42054) {
            func_psp_0923FEC0(0x25, 4);
            func_psp_0923FEC0(0x26, 5);
            g_GameEngineStep--;
        } else if (g_pads[0].tapped & D_psp_08B42050) {
            port = D_psp_09285C00 / 15;
            slot = D_psp_09285C00 % 15;
            func_psp_09238DA8(0xF, 8);
            g_api.PlaySfx(0x633);
            g_GameEngineStep++;
        }
        break;
    case 0x75:
        func_psp_09239B78();
        func_psp_0923A7C8(0x82, 0);
        func_psp_09243000(D_psp_09285C00);
        g_GameEngineStep++;
        break;
    case 0x76:
        func_psp_0923A7C8(0x82, 0);
        D_91FC478 = 0;
        temp_s1 = func_psp_09243028();
        if (temp_s1 != 0) {
            D_91FC478 = 1;
        }
        if (temp_s1 == 1) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x28, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep += 2;
        }
        if (temp_s1 == -1) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x29, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep++;
        }
        break;
    case 0x77:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 0);
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            func_psp_09238DA8(0xF, 8);
            g_GameEngineStep = 0x70;
        }
        break;
    case 0x78:
        func_psp_09239930(3);
        func_psp_0923A7C8(0x82, 0);
        if (g_pads[0].tapped & D_psp_08B42050) {
            g_api.PlaySfx(0x633);
            g_GameEngineStep = 0x72;
        }
        break;
    case 0x100:
        func_psp_09239B78();
        func_psp_0923A7C8(0x81, 0);
        func_psp_0923FEC0(0x2A, 4);
        func_psp_0923FEC0(0x2B, 5);
        func_psp_09238DA8(0xF, 0);
        func_psp_092426B0(D_psp_09285C00);
        g_GameEngineStep++;
        break;
    case 0x101:
        func_psp_0923A7C8(0x81, 0);
        D_91FC478 = 0;
        temp_s1 = func_psp_092426D8();
        if (temp_s1 != 0) {
            D_91FC478 = 1;
        }
        if (temp_s1 == 1) {
            if (g_SaveSummary[D_psp_09285C00 / 15].slot[D_psp_09285C00 % 15] ==
                func_8919560()) {
                func_8919638(g_Pix, 0x2000);
                func_913E220(g_Pix);
                if (g_Pix[0][0x1FFF] == 0xFF) {
                    D_8003C730 = 4;
                    D_91ED288 = g_Pix[0][0x1FFE];
                } else {
                    D_8003C730 = 1;
                    D_8B42044 = 2;
                }
                var_s5 = func_8919570();
                func_8919770(3);
                func_89195A0(var_s5);
            } else {
                D_8B42044 = 1;
                D_8003C730 = 1;
            }
            D_91FC490 = D_psp_09285C00 / 15;
            D_91FC488 = g_SaveSummary[D_91FC490].slot[D_psp_09285C00 % 15];
            g_api.PlaySfx(0x80);
            g_GameEngineStep = 0x104;
        }
        if (temp_s1 == -1) {
            func_psp_0923FC08(5);
            func_psp_0923FEC0(0x1A, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep++;
        }
        if (temp_s1 == -2) {
            func_psp_0923FC08(5);
            func_psp_0923FFB8(D_psp_09284160, 4);
            func_psp_09238DA8(0xF, 0);
            g_GameEngineStep++;
        }
        break;
    case 0x102:
        func_psp_0923A7C8(0x81, 0);
        if (g_pads[0].tapped) {
            func_psp_09238DA8(0xF, 8);
            g_GameEngineStep = 0x30;
        }
        break;
    case 0x104:
        if (D_8003C730 == 4) {
            func_psp_0923A7C8(0x84, 0);
        } else {
            func_psp_0923A7C8(0x81, 0);
        }
        if (func_psp_092390B8()) {
            g_GameStep++;
        }
        break;
    case 0x200:
    case 0x201:
    case 0x202:
    case 0x203:
    case 0x204:
    case 0x210:
    case 0x211:
    case 0x212:
    case 0x213:
    case 0x214:
        g_GameEngineStep = D_psp_09285BB8;
        break;
    case 0x220:
        g_GameEngineStep = D_psp_09285BB0;
        break;
    }
    g_GameTimer++;
    if (g_GameTimer == 0xA) {
        g_GameTimer = 0;
        D_psp_09285D00++;
        D_psp_09285D00 = D_psp_09285D00 % 3;
    }
}

void func_psp_0923F290(void) {
    s32 var_s0;

    switch (g_MenuStep) {
    case 0:
        if (D_91FC490 == -1 || D_91FC488 == -1) {
            g_GameStep++;
        } else {
            D_91FC478 = 0;
            g_MenuStep++;
        }
        break;

    case 1:
        func_psp_09242B40(D_91FC490, D_91FC488);
        g_MenuStep++;
        break;

    case 2:
        D_91FC478 = 0;
        var_s0 = func_psp_09242BA0(1);
        if (var_s0) {
            D_91FC478 = 1;
            g_GameStep++;
        }
        break;
    }
}
