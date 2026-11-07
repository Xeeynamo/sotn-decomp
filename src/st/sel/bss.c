// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

// sel.h is not imported as it would change the BSS order

#define STAGE_IS_SEL
#include <cutscene.h>

#if VERSION >= VER_HK
s32 vlc_dc_cr;
#endif
u32 g_SkipCutscene;
Dialogue g_Dialogue;
char* D_801BC398[16];
u32 g_MemCardSelectorX;
u32 g_MemCardSelectorY;
u32 D_801BC3E0;
s32 D_801BC3E4;
#if VERSION >= VER_HK
u16* vlc_src;
#endif
u32 D_801BC3E8;
u32 D_801BC3EC;
#if VERSION >= VER_HK
u32 vlc_block;
u32 vlc_bits;
#endif
#ifndef HARD_LINK
MemcardInfo g_MemcardInfo[2];
#endif
SaveSummary g_SaveSummary[PORT_COUNT];
u32 D_801BD030;
u32 g_StreamEndFrame;
u32 g_StreamIsRGB24;
u32 D_801BD03C;
u32 D_801BD040;
s32 g_StreamRewindSwitch[1];
u8 g_StreamImageBuffer[0x14000];
static s32 D_801D1048;
s32 D_801D104C[0x1680];
StreamEnv g_StreamEnv;
u32 D_801D6B00;
#if VERSION >= VER_HK
u32 vlc_bit_count;
#endif
u32 D_801D6B04;
u32 g_InputCursorPos;
u32 g_MainMenuCursor;
#ifndef HARD_LINK
s32 g_MemcardBlockRead;
#endif
u8 g_InputSaveName[12];
#if VERSION >= VER_HK
s32 vlc_dc_y;
#endif
#ifndef HARD_LINK
s32 g_MemcardStep;
#endif
s32 D_801D6B24;
#if VERSION >= VER_HK
s32 vlc_dc_cb;
#endif
