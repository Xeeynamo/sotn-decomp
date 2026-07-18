// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include <cutscene.h>

STATIC_PAD_BSS(0xC00);
u32 g_SkipCutscene;
Dialogue g_Dialogue;
u32 D_801CB6CC[26];
u32 g_CutsceneFlags;
#ifdef VERSION_PC
s16 D_801CB738[4]; // protect OOB for EntityMovableBox and BoxPuzzleSpikes
#else
s16 D_801CB738[2];
#endif
s32 g_IsCutsceneDone;
