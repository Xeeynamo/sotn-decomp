// SPDX-License-Identifier: AGPL-3.0-or-later
// #include "sel.h"
#include <game.h>
#include <cutscene.h>

#define OVL_EXPORT(x) SEL_##x

u32 OVL_EXPORT(SkipCutscene);
u32 OVL_EXPORT(Dialogue);
u16 D_801BC358;
u16 D_801BC35A;
u16 D_801BC35C;
u16 D_801BC35E;
u16 D_801BC360;
u16 D_801BC362;
u16 D_801BC364;
u16 D_801BC366;
u16 D_801BC368;
u8 D_801BC36A;
u8 D_801BC36B;
u32 D_801BC36C;
u32 D_801BC370;
u32 D_801BC374;
u32 D_801BC378;
u32 D_801BC37C;
u32 D_801BC380;
u32 D_801BC384;
u32 D_801BC388;
u32 D_801BC38C;
u16 D_801BC390;
u16 D_801BC392;
u32 D_801BC394;
char* D_801BC398[16];
u32 g_MemCardSelectorX;
u32 g_MemCardSelectorY;
u32 D_801BC3E0;
s32 D_801BC3E4;
u32 D_801BC3E8;
u32 D_801BC3EC;
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
u32 D_801D6B04;
u32 g_InputCursorPos;
u32 g_MainMenuCursor;
#ifndef HARD_LINK
s32 g_MemcardBlockRead;
#endif
u8 g_InputSaveName[12];
#ifndef HARD_LINK
s32 g_MemcardStep;
#endif
s32 D_801D6B24;
