// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "../../st/sel/sel.h"
#include "../pc.h"
#include "sfx.h"
#include <string.h>

void* SEL_g_EntityGfxs[] = {NULL, NULL};

// stubs
RECT D_80182584 = {0};
RECT D_8018258C = {0};
RECT D_801825A4 = {0};
void* D_8018C404[100] = {NULL};
s8 D_8018BC4A = 0;
s8 D_8018BC50 = 0;

s16 g_FakePal[0x100] = {0};
s16* D_8018DBD4[] = {NULL,      g_FakePal, g_FakePal, g_FakePal,
                     g_FakePal, g_FakePal, NULL};
s16* D_8018EFB4[] = {NULL,      g_FakePal, g_FakePal, g_FakePal,
                     g_FakePal, g_FakePal, NULL};
s16* D_8018DC30[] = {NULL,      g_FakePal, g_FakePal, g_FakePal,
                     g_FakePal, g_FakePal, NULL};
s16* D_8018E3B4[] = {NULL,      g_FakePal, g_FakePal, g_FakePal,
                     g_FakePal, g_FakePal, NULL};

unsigned short D_80180764[16] = {
    0x0000, 0x8C63, 0xAD6B, 0xD6B5, 0xFFFF, 0xFFFF, 0xA840, 0xB8C4,
    0xD9CC, 0x80EE, 0x81F4, 0x8F5F, 0xBFFF, 0x800A, 0x8010, 0x8016,
};
unsigned short D_80180784[16] = {
    0x0000, 0xAD6B, 0xD6B5, 0xFFFF, 0xFFFF, 0xFFFF, 0xB8C4, 0xD9CC,
    0xE9CC, 0x81F4, 0x8F5F, 0xBFFF, 0xF3FF, 0x800A, 0x8010, 0x8016,
};
unsigned short D_801807A4[16] = {
    0x0000, 0x8421, 0x8C63, 0xAD6B, 0xD6B5, 0xFFFF, 0xA840, 0xB8C4,
    0xD9CC, 0x81F4, 0x8F5F, 0xBFFF, 0x80EE, 0x800A, 0x8010, 0x8016,
};
unsigned short D_801807C4[16] = {
    0x0000, 0x8421, 0x8C63, 0xAD6B, 0xD6B5, 0xFFFF, 0xA840, 0xB8C4,
    0xD9CC, 0x8F5F, 0xBFFF, 0x80EE, 0x81F4, 0x800A, 0x8010, 0x8016,
};
unsigned short D_801807E4[16] = {
    0x0000, 0x8421, 0x8C63, 0xAD6B, 0xD6B5, 0xFFFF, 0xA840, 0xB8C4,
    0xD9CC, 0xBFFF, 0x80EE, 0x81F4, 0x8F5F, 0x800A, 0x8010, 0x8016,
};
unsigned short D_80180804[16] = {
    0x0000, 0x8421, 0x8C63, 0xAD6B, 0xD6B5, 0xFFFF, 0xA840, 0xB8C4,
    0xD9CC, 0x80EE, 0x81F4, 0x8F5F, 0xBFFF, 0x800A, 0x8010, 0x8016,
};
u16 D_801808E4[256]; // memcard palette

const char D_801ABF9C[] = "MDEC_rest:bad option(%d)\n";
const char D_801ABFB8[] = "MDEC_in_sync";
const char D_801ABFC8[] = "MDEC_out_sync";
const char D_801ABFD8[] = "DMA=(%d,%d), ADDR=(0x%08x->0x%08x)";
const char D_801AC000[] = "FIFO";
const char D_801AC038[] = "%s timeout:\n";
s32 D_801BAEE4[9];
s32 D_801BAF08; // block icon animation index
s32 D_801BAF0C;
s32 D_801BAF10;
s32 D_801BAF14;
s32 D_801BAF18[NUM_GFX][2];
s32 D_801BAFC0;
s32 MainMenuMaskPrimIndex;
s32 g_SelNextCrossPressEngStep;
s32 g_SelEng220NextStep;
u8* D_801BAFD0; // Pointer to texture pattern
s32 D_801BAFD4;
s32 D_801BAFD8;
s32 D_801BAFDC;
s32 D_801BAFE0;
u32 D_801BAFE4;
s32 D_801BAFE8;
s32 D_801BAFF4;
s32 D_801BAFFC;
s32 D_801BB000;
s32 D_801BB004;
s32 D_801BB008;
s32 D_801BB00C;
s32 D_801BB010;
s32 D_801BB014;
u16 D_801BB0F8[0x30][0x30];
s32 D_801BC340;
s32 g_StreamDiscStatus;
s32 D_801BC348;
s32 D_801BC34C;
Dialogue g_Dialogue;
u32 D_801BC398[16];
s32 g_MemCardSelectorX;
s32 g_MemCardSelectorY;
s32 D_801BC3E0; // on-screen keyboard key position
s32 D_801BC3E4;
u32 D_801BC3E8;
s32 D_801BC3EC; // selected memory card block
s32 D_801BC650;
SaveSummary g_SaveSummary[PORT_COUNT];
u32 D_801BD030;
u32 g_StreamEndFrame;
u32 g_StreamIsRGB24[1];
u32 D_801BD03C;
u32 D_801BD040;
s32 g_StreamRewindSwitch[1];
s32 D_801D104C[0x1680];
s32 D_801D6B04;
s32 g_InputCursorPos;
s32 g_MainMenuCursor;
char g_InputSaveName[12];
s32 D_801D6B24;

extern Overlay g_StageSel;

s32 LoadFileSim(s32 fileId, s32 type);

static bool g_WereStringsInitialised = false;
void InitStageSEL(Overlay* o) {
    memcpy(o, &g_StageSel, sizeof(Overlay));
    if (!g_WereStringsInitialised) {
        g_WereStringsInitialised = true;
        for (int i = 0; i < LEN(D_80180128); i++) {
            D_80180128[i].line1 = AnsiToSotnMenuString(D_80180128[i].line1);
            D_80180128[i].line2 = AnsiToSotnMenuString(D_80180128[i].line2);
        }
        for (int i = 0; i < LEN(D_801803A8); i++) {
            D_801803A8[i] = AnsiToSotnMenuString(D_801803A8[i]);
        }
    }
}

void func_801B9C80(void) {
    // handles the video playback
    // reset D_8003C728 to signal the end of video playback
    D_8003C728 = 0;
}
void SEL_EntityCutscene(Entity* e) { NOT_IMPLEMENTED; }
void func_801B79D4(Entity* e) { NOT_IMPLEMENTED; }
