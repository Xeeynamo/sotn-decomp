// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../../maria/maria.h"

// To use Maria as a playable character, add -DUSE_PLAYER_MARIA=1 in cmake

void MARIA_Load();
void InitPlayerMaria(void) {
    g_CurrentEntity = &PLAYER;
    MARIA_Load();
}

int PadReadPSP() { return 0; }
int func_90E4C58() { return 0; }
void func_90E4C18() {}
void func_90E4C68() {}
void func_9101FC8() {}

void LoadPendingGfx();
void ResetPendingGfxLoad();
void func_91040A0(u_long** bank) {
    GfxBank* gfxBank = (GfxBank*)bank;
    for (int i = 0; i < LEN(g_GfxLoad); i++) {
        GfxLoad* gfxLoad = &g_GfxLoad[i];
        if (gfxLoad->kind == GFX_BANK_NONE) {
            gfxLoad->kind = gfxBank->kind;
            gfxLoad->unk6 = 0;
            gfxLoad->unk8 = 0;
            gfxLoad->next = gfxBank->entries;
            return;
        }
    }
    LoadPendingGfx();
    ResetPendingGfxLoad();
}

void func_892667C(s32 paletteID, u16* paletteData) {
    int x = (paletteID & 15) * 16;
    int y = (paletteID >> 4) & 15;
    RECT rect = {x, 240 + y, 16, 1};
    LoadImage(&rect, (u_long*)paletteData);
}

void func_9142FC8(int sfx) {}

void func_89285A0(s32 angle, MATRIX* out) {
    short c = (short)rcos(angle);
    short s = (short)rsin(angle);
    out->m[0][0] = c;
    out->m[0][1] = (s16)-s;
    out->m[0][2] = 0;
    out->m[1][0] = s;
    out->m[1][1] = c;
    out->m[1][2] = 0;
    out->m[2][0] = 0;
    out->m[2][1] = 0;
    out->m[2][2] = 4096;
    out->t[2] = 0;
    out->t[1] = 0;
    out->t[0] = 0;
}

s16 func_90E0E30(PrimitiveType kind, s32 count) {
    return g_api.AllocPrimitives(kind, count);
}
