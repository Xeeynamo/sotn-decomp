// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

STATIC_PAD_BSS(0xC00); // might not be part of this file (hint: st0 bss)
s32 g_SkipCutscene;
Dialogue g_Dialogue;
u32 __unused0[26];
u32 g_CutsceneFlags;
s32 g_IsCutsceneDone;
