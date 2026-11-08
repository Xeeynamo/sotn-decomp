// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz/module.h>
#include <game.h>
#include "../../st/sel/sel.h"
#include "../pc.h"
#include <string.h>
#include <cutscene.h>
#include "overlay.h"
#include "psyz/log.h"

extern const char* D_801803A8[10];

// stubs
RECT D_80182584 = {0};
RECT D_8018258C = {0};
RECT D_801825A4 = {0};
s32 D_psp_0924F800;
s32 D_psp_0924F808;

// SEL owns a copy as on PSX, so banks.c can point to it from a static table
u16 g_saveIconPal[] = {
#include "../../st/sel/gen/g_saveIconPal.h"
};

extern Overlay g_Overlay;
extern s8 D_8018BC4A;
extern s8 D_8018BC50;
extern u8 gfx_portrait_alucard[];
extern u8 gfx_portrait_maria[];
extern u8 gfx_portrait_richter[];

static void InitCutscenePc(void) {
    static const CutsceneSymbolRange symbols[] = {
        {cutscene_endings, 0x8018b304, 0x946},
        {&D_8018BC4A, 0x8018bc4a, sizeof(s8)},
        {&D_8018BC50, 0x8018bc50, sizeof(s8)},
        {gfx_portrait_alucard, 0x8018f9a8, 0xd80},
        {gfx_portrait_maria, 0x80190728, 0xd80},
        {gfx_portrait_richter, 0x801914a8, 0xd80},
    };
    CutscenePcAlloc(symbols, LEN(symbols));
}

s32 LoadFileSim(s32 fileId, s32 type);

void Psyz_ModuleStart(void* param) {
    Overlay* o = param;
    memcpy(o, &g_Overlay, sizeof(Overlay));
    InitCutscenePc();
}

void Psyz_ModuleStop(void) {}

void PlayMovie(void) {
    // handles the video playback
    // reset g_IsMoviePlaying to signal the end of video playback
    g_IsMoviePlaying = 0;
}

void func_psp_09237CB8(void) {
    // loads PSP graphics
    NOT_IMPLEMENTED;
}

void func_psp_0891CEB8(s32 x, s32 y) { NOT_IMPLEMENTED; }

void func_psp_08925F7C(s32 x, s32 y0, s32 w, s32 h) { NOT_IMPLEMENTED; }
